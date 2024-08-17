#include "stdStrTable.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdStrTable_aBuffer J3D_DECL_FAR_ARRAYVAR(stdStrTable_aBuffer, wchar_t(*)[64])

void stdStrTable_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdStrTable_Load);
    // J3D_HOOKFUNC(stdStrTable_ParseLiteral);
    // J3D_HOOKFUNC(stdStrTable_Free);
    // J3D_HOOKFUNC(stdStrTable_GetValue);
    // J3D_HOOKFUNC(stdStrTable_GetValueOrKey);
    // J3D_HOOKFUNC(stdStrTable_ReadLine);
}

void stdStrTable_ResetGlobals(void)
{
    memset(&stdStrTable_aBuffer, 0, sizeof(stdStrTable_aBuffer));
}

int J3DAPI stdStrTable_Load(tStringTable* pStrTable, const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdStrTable_Load, pStrTable, pFilename);
}

char* J3DAPI stdStrTable_ParseLiteral(const char* pStr, char** ppBegin, char** ppEnd)
{
    return J3D_TRAMPOLINE_CALL(stdStrTable_ParseLiteral, pStr, ppBegin, ppEnd);
}

void J3DAPI stdStrTable_Free(tStringTable* pStrTable)
{
    J3D_TRAMPOLINE_CALL(stdStrTable_Free, pStrTable);
}

wchar_t* J3DAPI stdStrTable_GetValue(const tStringTable* pStrTable, const char* pKey)
{
    return J3D_TRAMPOLINE_CALL(stdStrTable_GetValue, pStrTable, pKey);
}

wchar_t* J3DAPI stdStrTable_GetValueOrKey(const tStringTable* pStrTable, const char* pKey)
{
    return J3D_TRAMPOLINE_CALL(stdStrTable_GetValueOrKey, pStrTable, pKey);
}

int J3DAPI stdStrTable_ReadLine(tFileHandle fh, char* pStr, int size)
{
    return J3D_TRAMPOLINE_CALL(stdStrTable_ReadLine, fh, pStr, size);
}
