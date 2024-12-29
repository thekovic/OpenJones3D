#include "sithConsole.h"
#include <j3dcore/j3dhook.h>

#include <sith/Main/sithCommand.h>
#include <sith/RTI/symbols.h>

#include <std/General/stdHashtbl.h>
#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

#include <string.h>

#define sithCommand_LINELEN 128

static bool bOpen;
static bool bStarted;

static char aBuffers[32][128];
static size_t bufferSize;
static size_t curFlushIndex;
static size_t endPrintIndex;
static size_t curPrintIndex;

static tHashTable* pCommandTable;
static SithConsoleCommand* apCommands;
static size_t maxRegisteredCommands;
static size_t numRegistredCommands;

static SithConsoleWriteTextFunc pfPrintString;
static SithConsoleWriteWideTextFunc pfPrintWString;
static SithConsoleFlush pfFlush;

int J3DAPI sithConsole_CreateCommandTable(size_t size);
void sithConsole_FreeCommandTable(void);

void sithConsole_InstallHooks(void)
{
    J3D_HOOKFUNC(sithConsole_Startup);
    J3D_HOOKFUNC(sithConsole_Shutdown);
    J3D_HOOKFUNC(sithConsole_Open);
    J3D_HOOKFUNC(sithConsole_Close);
    J3D_HOOKFUNC(sithConsole_PrintString);
    J3D_HOOKFUNC(sithConsole_PrintWString);
    J3D_HOOKFUNC(sithConsole_ExeCommand);
    J3D_HOOKFUNC(sithConsole_Flush);
    J3D_HOOKFUNC(sithConsole_RegisterCommand);
    J3D_HOOKFUNC(sithConsole_RegisterPrintFunctions);
    J3D_HOOKFUNC(sithConsole_CreateCommandTable);
    J3D_HOOKFUNC(sithConsole_FreeCommandTable);
}

void sithConsole_ResetGlobals(void)
{}

int sithConsole_Startup(void)
{
    SITH_ASSERTREL(!bStarted);

    bufferSize            = 0;
    maxRegisteredCommands = 0;
    numRegistredCommands  = 0;

    pfPrintString  = NULL;
    pfPrintWString = NULL;
    pfFlush        = NULL;

    bStarted = true;
    return 0;
}

void sithConsole_Shutdown(void)
{
    bufferSize            = 0;
    maxRegisteredCommands = 0;
    numRegistredCommands  = 0;

    pfPrintString  = NULL;
    pfPrintWString = NULL;
    pfFlush        = NULL;

    if ( bOpen ) {
        sithConsole_Close();
    }

    bStarted = false;
}

int J3DAPI sithConsole_Open(size_t numLines, size_t numCommands)
{
    if ( !bStarted ) {
        return 1;
    }

    if ( bOpen ) {
        return 1;
    }

    // TODO: Add bound check
    memset(aBuffers, 0, numLines * sithCommand_LINELEN);
    bufferSize = numLines;

    endPrintIndex = 0;
    curPrintIndex = 0;
    curFlushIndex = 0;

    if ( !sithConsole_CreateCommandTable(numCommands) )
    {
        SITHLOG_ERROR("Failed to create console.\n");
        return 1;
    }

    sithCommand_RegisterCommands();

    bOpen = true;
    return 0;
}

void sithConsole_Close(void)
{
    if ( !bOpen ) {
        SITHLOG_STATUS("sithConsole closed when not opened.\n");
    }

    bufferSize            = 0;
    maxRegisteredCommands = 0;
    numRegistredCommands  = 0;

    sithConsole_FreeCommandTable();
    bOpen = false;
}

void J3DAPI sithConsole_PrintString(const char* pString)
{
    SITH_ASSERTREL(pString);

    if ( bOpen )
    {
        if ( pfPrintString )
        {
            pfPrintString(pString);
        }
        else
        {
            const size_t len = strlen(pString);
            if ( len > sithCommand_LINELEN - 1 )
            {
                SITHLOG_ERROR("Console string too long (%d).  Truncated.\n", len);
            }

            curPrintIndex = (curPrintIndex + 1) % bufferSize;
            if ( curPrintIndex == endPrintIndex )
            {
                endPrintIndex = (endPrintIndex + 1) % bufferSize;
            }

            STD_STRCPY(aBuffers[curPrintIndex], pString);
        }
    }
}

void J3DAPI sithConsole_PrintWString(const wchar_t* pwString)
{
    SITH_ASSERTREL(pwString && bOpen);
    if ( pfPrintWString )
    {
        pfPrintWString(pwString);
    }
}

int J3DAPI sithConsole_ExeCommand(const char* pLine)
{
    SITH_ASSERTREL(bOpen);
    SITH_ASSERTREL(pLine);

    // TODO: copy to buffer before strlwr
    //_strlwr_s((char*)pLine);
    stdUtil_ToLower((char*)pLine);

    const char* pCmdName = strtok((char*)pLine, ", \t\n\r");
    if ( !pCmdName )
    {
        return 0;
    }

    SithConsoleCommand* pFunc = (SithConsoleCommand*)stdHashtbl_Find(pCommandTable, pCmdName);
    if ( !pFunc )
    {
        STD_FORMAT(std_g_genBuffer, "Console command %s not recognized.", pCmdName);
        sithConsole_PrintString(std_g_genBuffer);
        return 0;
    }

    SITH_ASSERTREL(pFunc->pfFunc);
    const char* pArg = strtok(NULL, "\n\r");
    pFunc->pfFunc(pFunc, pArg);
    return 1;
}

void sithConsole_Flush(void)
{
    if ( pfFlush )
    {
        pfFlush();
    }
    else
    {
        while ( curFlushIndex != curPrintIndex )
        {
            curFlushIndex = (curFlushIndex + 1) % bufferSize;
            SITHLOG_STATUS("%s", aBuffers[curFlushIndex]);
        }
    }
}

int J3DAPI sithConsole_RegisterCommand(SithConsoleFunction pfFunc, const char* pName, int flags)
{
    SithConsoleCommand* pCommand;

    SITH_ASSERTREL(pfFunc && pName);
    if ( numRegistredCommands == maxRegisteredCommands )
    {
        SITHLOG_ERROR("Tried to register > %d console funcs.\n", maxRegisteredCommands);
        return 0;
    }

    pCommand = (SithConsoleCommand*)stdHashtbl_Find(pCommandTable, pName);
    if ( pCommand )
    {
        // TODO: Add log for func getting overridden
        pCommand->pfFunc = pfFunc;
        pCommand->flags  = flags;
    }
    else
    {
        STD_STRCPY(apCommands[numRegistredCommands].aName, pName);

        apCommands[numRegistredCommands].pfFunc = pfFunc;
        apCommands[numRegistredCommands].flags  = flags;

        stdHashtbl_Add(
            pCommandTable,
            apCommands[numRegistredCommands].aName,
            &apCommands[numRegistredCommands]
        );
        ++numRegistredCommands;
    }

    return 1;
}

void J3DAPI sithConsole_RegisterPrintFunctions(SithConsoleWriteTextFunc pfWriteText, SithConsoleWriteWideTextFunc pfWriteWText, SithConsoleFlush pfFlush)
{
    pfPrintString = pfWriteText;
    pfPrintWString = pfWriteWText;
    pfFlush = pfFlush;
}

int J3DAPI sithCommand_Help(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    char aLine[56] = { 0 }; // Added: Init to 0

    // Removed
    //*(uint16_t*)aLine = word_5FA420;              // ???
    //memset(&aLine[2], 0, 54);

    size_t curPos = 0;
    sithConsole_PrintString("The following commands are available:");
    for ( size_t i = 0; i < numRegistredCommands; ++i )
    {
        if ( curPos + strlen(apCommands[i].aName) + 5 >= 56 )
        {
            sithConsole_PrintString(aLine);
            curPos = 0;
        }

        curPos += sprintf_s(&aLine[curPos], STD_ARRAYLEN(aLine) - curPos, "    %s", apCommands[i].aName);
    }

    sithConsole_PrintString(aLine);
    return 1;
}

int J3DAPI sithConsole_CreateCommandTable(size_t size)
{
    SITH_ASSERTREL(size > 0);
    apCommands = (SithConsoleCommand*)STDMALLOC(sizeof(SithConsoleCommand) * size);
    pCommandTable = stdHashtbl_New(2 * size);

    if ( !apCommands || !pCommandTable )
    {
        if ( apCommands )
        {
            stdMemory_Free(apCommands);
            apCommands = NULL;
        }

        if ( !pCommandTable )
        {
            return 0;
        }

        stdHashtbl_Free(pCommandTable);
        pCommandTable = NULL;
        return 0;
    }
    else
    {
        memset(apCommands, 0, sizeof(SithConsoleCommand) * size);
        maxRegisteredCommands = size;
        return 1;
    }
}

void sithConsole_FreeCommandTable(void)
{
    if ( apCommands )
    {
        stdMemory_Free(apCommands);
        apCommands = NULL;
    }

    if ( pCommandTable )
    {
        stdHashtbl_Free(pCommandTable);
        pCommandTable = NULL;
    }
}
