#include "stdGob.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdGob_aEntryNameBuff J3D_DECL_FAR_ARRAYVAR(stdGob_aEntryNameBuff, char(*)[128])
#define stdGob_hs J3D_DECL_FAR_VAR(stdGob_hs, tHostServices)
#define stdGob_bStartup J3D_DECL_FAR_VAR(stdGob_bStartup, int)
#define stdGob_pHS J3D_DECL_FAR_VAR(stdGob_pHS, tHostServices*)

void stdGob_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdGob_Startup);
    // J3D_HOOKFUNC(stdGob_Shutdown);
    // J3D_HOOKFUNC(stdGob_Load);
    // J3D_HOOKFUNC(stdGob_LoadEntry);
    // J3D_HOOKFUNC(stdGob_Free);
    // J3D_HOOKFUNC(stdGob_FreeEntry);
    // J3D_HOOKFUNC(stdGob_FileOpen);
    // J3D_HOOKFUNC(stdGob_FileClose);
    // J3D_HOOKFUNC(stdGob_FileSeek);
    // J3D_HOOKFUNC(stdGob_FileTell);
    // J3D_HOOKFUNC(stdGob_FileEOF);
    // J3D_HOOKFUNC(stdGob_FileRead);
    // J3D_HOOKFUNC(stdGob_FileGets);
}

void stdGob_ResetGlobals(void)
{
    memset(&stdGob_aEntryNameBuff, 0, sizeof(stdGob_aEntryNameBuff));
    memset(&stdGob_hs, 0, sizeof(stdGob_hs));
    memset(&stdGob_bStartup, 0, sizeof(stdGob_bStartup));
    memset(&stdGob_pHS, 0, sizeof(stdGob_pHS));
}

void J3DAPI stdGob_Startup(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(stdGob_Startup, pHS);
}

void stdGob_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(stdGob_Shutdown);
}

Gob* J3DAPI stdGob_Load(const char* pFilename, int numFileHandles, int bMMapFile)
{
    return J3D_TRAMPOLINE_CALL(stdGob_Load, pFilename, numFileHandles, bMMapFile);
}

int J3DAPI stdGob_LoadEntry(Gob* pGob, const char* pFilename, int numFileHandles, int bMMapFile)
{
    return J3D_TRAMPOLINE_CALL(stdGob_LoadEntry, pGob, pFilename, numFileHandles, bMMapFile);
}

void J3DAPI stdGob_Free(Gob* pGob)
{
    J3D_TRAMPOLINE_CALL(stdGob_Free, pGob);
}

void J3DAPI stdGob_FreeEntry(Gob* pGob)
{
    J3D_TRAMPOLINE_CALL(stdGob_FreeEntry, pGob);
}

GobFileHandle* J3DAPI stdGob_FileOpen(Gob* pGob, const char* aName)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileOpen, pGob, aName);
}

void J3DAPI stdGob_FileClose(GobFileHandle* pHandle)
{
    J3D_TRAMPOLINE_CALL(stdGob_FileClose, pHandle);
}

int J3DAPI stdGob_FileSeek(GobFileHandle* pHandle, int offset, int origin)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileSeek, pHandle, offset, origin);
}

int J3DAPI stdGob_FileTell(GobFileHandle* pHandle)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileTell, pHandle);
}

int J3DAPI stdGob_FileEOF(GobFileHandle* pHandle)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileEOF, pHandle);
}

size_t J3DAPI stdGob_FileRead(GobFileHandle* pHandle, void* data, const size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileRead, pHandle, data, size);
}

const char* J3DAPI stdGob_FileGets(GobFileHandle* pGobFileHandle, char* pStr, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdGob_FileGets, pGobFileHandle, pStr, size);
}
