#include "sithConsole.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithConsole_startIndex J3D_DECL_FAR_VAR(sithConsole_startIndex, int)
#define sithConsole_endIndex2 J3D_DECL_FAR_VAR(sithConsole_endIndex2, int)
#define sithConsole_apCommands J3D_DECL_FAR_VAR(sithConsole_apCommands, SithConsoleCommand*)
#define sithConsole_endIndex J3D_DECL_FAR_VAR(sithConsole_endIndex, int)
#define sithConsole_aBuffers J3D_DECL_FAR_ARRAYVAR(sithConsole_aBuffers, char(*)[32][128])
#define sithConsole_pTable J3D_DECL_FAR_VAR(sithConsole_pTable, tHashTable*)
#define sithConsole_bOpen J3D_DECL_FAR_VAR(sithConsole_bOpen, int)
#define sithConsole_bStarted J3D_DECL_FAR_VAR(sithConsole_bStarted, int)
#define sithConsole_maxRegisteredCommands J3D_DECL_FAR_VAR(sithConsole_maxRegisteredCommands, int)
#define sithConsole_numRegistredCommands J3D_DECL_FAR_VAR(sithConsole_numRegistredCommands, int)
#define sithConsole_bufferSize J3D_DECL_FAR_VAR(sithConsole_bufferSize, int)
#define sithConsole_pfPrintString J3D_DECL_FAR_VAR(sithConsole_pfPrintString, SithConsoleWriteTextFunc)
#define sithConsole_pfPrintWString J3D_DECL_FAR_VAR(sithConsole_pfPrintWString, SithConsoleWriteWideTextFunc)
#define sithConsole_pfFlush J3D_DECL_FAR_VAR(sithConsole_pfFlush, SithConsoleFlush)

void sithConsole_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithConsole_Startup);
    // J3D_HOOKFUNC(sithConsole_Shutdown);
    // J3D_HOOKFUNC(sithConsole_Open);
    // J3D_HOOKFUNC(sithConsole_Close);
    // J3D_HOOKFUNC(sithConsole_PrintString);
    // J3D_HOOKFUNC(sithConsole_PrintWString);
    // J3D_HOOKFUNC(sithConsole_ExeCommand);
    // J3D_HOOKFUNC(sithConsole_Flush);
    // J3D_HOOKFUNC(sithConsole_RegisterCommand);
    // J3D_HOOKFUNC(sithConsole_RegisterPrintFunctions);
    // J3D_HOOKFUNC(sithConsole_CreateCommandTable);
    // J3D_HOOKFUNC(sithConsole_FreeCommandTable);
}

void sithConsole_ResetGlobals(void)
{
    memset(&sithConsole_startIndex, 0, sizeof(sithConsole_startIndex));
    memset(&sithConsole_endIndex2, 0, sizeof(sithConsole_endIndex2));
    memset(&sithConsole_apCommands, 0, sizeof(sithConsole_apCommands));
    memset(&sithConsole_endIndex, 0, sizeof(sithConsole_endIndex));
    memset(&sithConsole_aBuffers, 0, sizeof(sithConsole_aBuffers));
    memset(&sithConsole_pTable, 0, sizeof(sithConsole_pTable));
    memset(&sithConsole_bOpen, 0, sizeof(sithConsole_bOpen));
    memset(&sithConsole_bStarted, 0, sizeof(sithConsole_bStarted));
    memset(&sithConsole_maxRegisteredCommands, 0, sizeof(sithConsole_maxRegisteredCommands));
    memset(&sithConsole_numRegistredCommands, 0, sizeof(sithConsole_numRegistredCommands));
    memset(&sithConsole_bufferSize, 0, sizeof(sithConsole_bufferSize));
    memset(&sithConsole_pfPrintString, 0, sizeof(sithConsole_pfPrintString));
    memset(&sithConsole_pfPrintWString, 0, sizeof(sithConsole_pfPrintWString));
    memset(&sithConsole_pfFlush, 0, sizeof(sithConsole_pfFlush));
}

int J3DAPI sithConsole_Startup()
{
    return J3D_TRAMPOLINE_CALL(sithConsole_Startup);
}

void J3DAPI sithConsole_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithConsole_Shutdown);
}

int J3DAPI sithConsole_Open(int bufSize, int numCommands)
{
    return J3D_TRAMPOLINE_CALL(sithConsole_Open, bufSize, numCommands);
}

void sithConsole_Close()
{
    J3D_TRAMPOLINE_CALL(sithConsole_Close);
}

void J3DAPI sithConsole_PrintString(const char* pString)
{
    J3D_TRAMPOLINE_CALL(sithConsole_PrintString, pString);
}

void J3DAPI sithConsole_PrintWString(wchar_t* pwString)
{
    J3D_TRAMPOLINE_CALL(sithConsole_PrintWString, pwString);
}

int J3DAPI sithConsole_ExeCommand(const char* pLine)
{
    return J3D_TRAMPOLINE_CALL(sithConsole_ExeCommand, pLine);
}

void sithConsole_Flush(void)
{
    J3D_TRAMPOLINE_CALL(sithConsole_Flush);
}

int J3DAPI sithConsole_RegisterCommand(SithConsoleFunction pfFunc, const char* pName, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithConsole_RegisterCommand, pfFunc, pName, flags);
}

void J3DAPI sithConsole_RegisterPrintFunctions(SithConsoleWriteTextFunc pfWriteText, SithConsoleWriteWideTextFunc pfWriteWText, SithConsoleFlush pfFlush)
{
    J3D_TRAMPOLINE_CALL(sithConsole_RegisterPrintFunctions, pfWriteText, pfWriteWText, pfFlush);
}

int J3DAPI sithConsole_CreateCommandTable(int size)
{
    return J3D_TRAMPOLINE_CALL(sithConsole_CreateCommandTable, size);
}

void J3DAPI sithConsole_FreeCommandTable()
{
    J3D_TRAMPOLINE_CALL(sithConsole_FreeCommandTable);
}
