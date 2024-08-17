#include "stdFnames.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdFnames_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdFnames_FindMedName);
    // J3D_HOOKFUNC(stdFnames_FindExt);
    // J3D_HOOKFUNC(stdFnames_StripExtAndDot);
    // J3D_HOOKFUNC(stdFnames_ChangeExt);
    // J3D_HOOKFUNC(stdFnames_Concat);
    // J3D_HOOKFUNC(stdFnames_MakePath);
}

void stdFnames_ResetGlobals(void)
{

}

const char* J3DAPI stdFnames_FindMedName(const char* pFilePath)
{
    return J3D_TRAMPOLINE_CALL(stdFnames_FindMedName, pFilePath);
}

char* J3DAPI stdFnames_FindExt(const char* pFilePath)
{
    return J3D_TRAMPOLINE_CALL(stdFnames_FindExt, pFilePath);
}

void J3DAPI stdFnames_StripExtAndDot(char* pPath)
{
    J3D_TRAMPOLINE_CALL(stdFnames_StripExtAndDot, pPath);
}

void J3DAPI stdFnames_ChangeExt(char* pPath, const char* pExt)
{
    J3D_TRAMPOLINE_CALL(stdFnames_ChangeExt, pPath, pExt);
}

void J3DAPI stdFnames_Concat(char* dst, const char* src, int size)
{
    J3D_TRAMPOLINE_CALL(stdFnames_Concat, dst, src, size);
}

void J3DAPI stdFnames_MakePath(char* aOutPath, int size, const char* pPath1, const char* pPath2)
{
    J3D_TRAMPOLINE_CALL(stdFnames_MakePath, aOutPath, size, pPath1, pPath2);
}
