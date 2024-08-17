#include "stdFileUtil.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdFileUtil_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdFileUtil_NewFind);
    // J3D_HOOKFUNC(stdFileUtil_DisposeFind);
    // J3D_HOOKFUNC(stdFileUtil_FindNext);
    // J3D_HOOKFUNC(stdFileUtil_MkDir);
    // J3D_HOOKFUNC(stdFileUtil_FileExists);
}

void stdFileUtil_ResetGlobals(void)
{

}

FindFileData* J3DAPI stdFileUtil_NewFind(const char* path, int mode, const char* pFilter)
{
    return J3D_TRAMPOLINE_CALL(stdFileUtil_NewFind, path, mode, pFilter);
}

void J3DAPI stdFileUtil_DisposeFind(FindFileData* pFileData)
{
    J3D_TRAMPOLINE_CALL(stdFileUtil_DisposeFind, pFileData);
}

int J3DAPI stdFileUtil_FindNext(FindFileData* ffStruct, tFoundFileInfo* pFileInfo)
{
    return J3D_TRAMPOLINE_CALL(stdFileUtil_FindNext, ffStruct, pFileInfo);
}

int J3DAPI stdFileUtil_MkDir(const char* lpPathName)
{
    return J3D_TRAMPOLINE_CALL(stdFileUtil_MkDir, lpPathName);
}

int J3DAPI stdFileUtil_FileExists(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdFileUtil_FileExists, pFilename);
}
