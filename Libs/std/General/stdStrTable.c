
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#include "std.h"
#include "stdHashtbl.h"
#include "stdMemory.h"
#include "stdStrTable.h"
#include "stdUtil.h"

static wchar_t stdStrTable_aBuffer[64] = { 0 };

void stdStrTable_InstallHooks(void)
{

    J3D_HOOKFUNC(stdStrTable_Load);
    J3D_HOOKFUNC(stdStrTable_ParseLiteral);
    J3D_HOOKFUNC(stdStrTable_Free);
    J3D_HOOKFUNC(stdStrTable_GetValue);
    J3D_HOOKFUNC(stdStrTable_GetValueOrKey);
    J3D_HOOKFUNC(stdStrTable_ReadLine);
}

void stdStrTable_ResetGlobals(void)
{
    //memset(&stdStrTable_aBuffer, 0, sizeof(stdStrTable_aBuffer));
}

int J3DAPI stdStrTable_Load(tStringTable* pStrTable, const char* pFilename)
{
    tFileHandle fh;
    tHashTable* pTbl;
    char* pCur;
    char* pKey;
    int bSuccess;
    char* pValBegin;
    char* pValEnd;
    char aLine[276] = { 0 };
    char aBuf[256]  = { 0 };

    STD_ASSERTREL(pStrTable != ((void*)0));
    STD_ASSERTREL(pStrTable->magic != 'sTbl');
    STD_ASSERTREL(pFilename != ((void*)0));

    pStrTable->nMsgs    = 0;
    pStrTable->pData    = NULL;
    pStrTable->pHashtbl = NULL;
    pStrTable->magic    = 0;
    fh = std_g_pHS->pFileOpen(pFilename, "rt");
    if ( !fh ) {
        return 0;
    }

    int numMsgs = 0;
    if ( !stdStrTable_ReadLine(fh, aLine, sizeof(aLine) - 1) || sscanf_s(aLine, "MSGS %d", &numMsgs) != 1 )
    {
        std_g_pHS->pFileClose(fh);
        std_g_pHS->pErrorPrint("Bad 'MSG n' line in string table file '%s'\n", pFilename);
        return 0;
    }

    pStrTable->nMsgs = numMsgs;

    tStringTableNode* aData = (tStringTableNode*)STDMALLOC(sizeof(tStringTableNode) * numMsgs);
    pStrTable->pData = aData;
    if ( !aData ) {
        STDLOG_FATAL("Out of memory--cannot load string table");
    }

    memset(pStrTable->pData, 0, sizeof(tStringTableNode) * numMsgs);

    pTbl = stdHashtbl_New((int32_t)((double)numMsgs * 1.5f));
    pStrTable->pHashtbl = pTbl;
    if ( !pTbl ) {
        STDLOG_FATAL("Out of memory--cannot load string table");
    }

    bSuccess = 1;
    for ( int i = 0; bSuccess && (i < numMsgs); i++ )
    {
        bSuccess = stdStrTable_ReadLine(fh, aLine, sizeof(aLine) - 1);
        if ( strncmpi(aLine, "end", 3u) == 0 ) // hit end
        {
            bSuccess = 0;
            pStrTable->nMsgs = i;
            std_g_pHS->pErrorPrint("Premature 'END' found after only %d lines in '%s'.  Check number in 'MSG xxx' header.\n", i, pFilename);
        }

        if ( bSuccess )
        {
            pCur = stdUtil_ParseLiteral(aLine, aBuf, sizeof(aBuf));
            if ( pCur )
            {
                pKey = (char*)STDMALLOC(strlen(aBuf) + 1);
                stdUtil_StringCopy(pKey, strlen(aBuf) + 1, aBuf);
                aData[i].pKey = pKey;

                pCur = stdUtil_StringSplit(pCur, aBuf, sizeof(aBuf), " \t");
                if ( pCur )
                {
                    aData[i].unknown = atoi(aBuf);

                    stdStrTable_ParseLiteral(pCur, &pValBegin, &pValEnd);
                    memset(aBuf, 0, sizeof(aBuf));
                    stdUtil_StringNumCopy(aBuf, sizeof(aBuf), pValBegin, (pValEnd - pValBegin));
                    aData[i].value = stdUtil_ToWString(aBuf);

                    if ( !stdHashtbl_Add(pStrTable->pHashtbl, aData[i].pKey, &aData[i]) )
                    {
                        STDLOG_ERROR("The key '%s' is in the string table '%s' more than once.\n   >>>%s\n", aData[i].pKey, pFilename, aLine);
                    }
                }
                else
                {
                    STDLOG_ERROR("Cannot understand this line in string table '%s'.\n   >>> %s\n", pFilename, aLine);
                }
            }
            else
            {
                STDLOG_ERROR("Cannot understand this line in string table '%s'.\n   >>> %s\n", pFilename, aLine);
            }
        }
    }

    if ( bSuccess )
    {
        aLine[0] = 0;
        stdStrTable_ReadLine(fh, aLine, STD_ARRAYLEN(aLine) - 1);
        const char* ptok = strtok(aLine, " \t\n\r");
        if ( strcmpi(ptok, "end") )
        {
            bSuccess = 0;
            std_g_pHS->pErrorPrint("'END' not found in '%s'.  Enlarge number in 'MSG xxx' header.\n", pFilename);
        }
    }

    pStrTable->magic = 'sTbl';
    std_g_pHS->pFileClose(fh);
    return bSuccess;
}

char* J3DAPI stdStrTable_ParseLiteral(const char* pStr, char** ppBegin, char** ppEnd)
{
    char* pCur;

    pCur = strchr(pStr, '"') + 1;
    *ppBegin = pCur;
    while ( pCur )
    {
        pCur = strchr(pCur, '"');
        if ( !pCur )
        {
            break;
        }

        *ppEnd = pCur;
        if ( *pCur == '"' )
        {
            ++pCur;
        }
    }

    return pCur;
}

void J3DAPI stdStrTable_Free(tStringTable* pStrTable)
{
    int nMsgs;
    tStringTableNode* aData;

    STD_ASSERTREL(pStrTable != ((void*)0));

    if ( pStrTable->magic == 'sTbl' )
    {
        nMsgs = pStrTable->nMsgs;
        aData = pStrTable->pData;

        pStrTable->magic = 0;
        pStrTable->nMsgs = 0;
        pStrTable->pData = NULL;
        stdHashtbl_Free(pStrTable->pHashtbl);

        if ( aData )
        {
            for ( int i = 0; i < nMsgs; ++i )
            {
                if ( aData[i].value ) {
                    stdMemory_Free(aData[i].value);
                }

                if ( aData[i].pKey ) {
                    stdMemory_Free((void*)aData[i].pKey);
                }
            }

            stdMemory_Free(aData);
        }
    }
}

wchar_t* J3DAPI stdStrTable_GetValue(const tStringTable* pStrTable, const char* pKey)
{
    tStringTableNode* pStrNode;
    STD_ASSERTREL(pStrTable != ((void*)0));

    if ( pStrTable->nMsgs && (pStrNode = (tStringTableNode*)stdHashtbl_Find(pStrTable->pHashtbl, pKey)) != 0 )
    {
        return pStrNode->value;
    }

    return NULL;
}

wchar_t* J3DAPI stdStrTable_GetValueOrKey(const tStringTable* pStrTable, const char* pKey)
{
    wchar_t* pVal;

    STD_ASSERTREL(pStrTable != ((void*)0));
    pVal = stdStrTable_GetValue(pStrTable, pKey);
    if ( pVal )
    {
        return pVal;
    }

    STD_TOWSTR(stdStrTable_aBuffer, pKey);
    return stdStrTable_aBuffer;
}

int J3DAPI stdStrTable_ReadLine(tFileHandle fh, char* pStr, int size)
{
    bool bFinish = false;
    while ( !bFinish )
    {
        char* pReadStr = std_g_pHS->pFileGets(fh, pStr, size);
        if ( pReadStr != NULL && strchr(pStr, '\n') == NULL ) // Added: Added check for no data read from file
        {
            char aBuf[64] = { 0 };
            do {
                pReadStr = std_g_pHS->pFileGets(fh, aBuf, sizeof(aBuf));
            } while ( pReadStr != NULL && strchr(aBuf, '\n') == NULL ); // Fixed: Added check for no data read from file. This fixes potential infinitive loop bug when there is no line break at the end of the file
        }

        // Skip spaces
        char* pch = pStr;
        for ( ; isspace(*pch); ++pch ) {
            ;
        }

        if ( pReadStr == NULL || (*pch != '#' && *pch && *pch != '\r' && *pch != '\n') ) // Fixed: Added check for no data read from file to prevent potential infinitive loop bug
        {
            bFinish = true;
        }
    };

    return 1;
}
