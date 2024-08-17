#include "JonesFile.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesFile_aResources J3D_DECL_FAR_ARRAYVAR(JonesFile_aResources, JonesResource(*)[3])
#define JonesFile_sysHS J3D_DECL_FAR_VAR(JonesFile_sysHS, tHostServices)
#define JonesFile_aPathBuf J3D_DECL_FAR_ARRAYVAR(JonesFile_aPathBuf, char(*)[48])
#define JonesFile_aFileHandles J3D_DECL_FAR_ARRAYVAR(JonesFile_aFileHandles, JonesFileHandle(*)[33])
#define JonesFile_bStartup J3D_DECL_FAR_VAR(JonesFile_bStartup, int)
#define JonesFile_bOpened J3D_DECL_FAR_VAR(JonesFile_bOpened, int)
#define JonesFile_pSysEnv J3D_DECL_FAR_VAR(JonesFile_pSysEnv, tHostServices*)
#define JonesFile_pHS J3D_DECL_FAR_VAR(JonesFile_pHS, tHostServices*)
#define JonesFile_hsInitCount J3D_DECL_FAR_VAR(JonesFile_hsInitCount, int)

void JonesFile_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesFile_Startup);
    // J3D_HOOKFUNC(JonesFile_Shutdown);
    // J3D_HOOKFUNC(JonesFile_Open);
    // J3D_HOOKFUNC(JonesFile_Close);
    // J3D_HOOKFUNC(JonesFile_GetCurrentCDNum);
    // J3D_HOOKFUNC(JonesFile_FileExists);
    // J3D_HOOKFUNC(JonesFile_AddInstallPath);
    // J3D_HOOKFUNC(JonesFile_AddCDPath);
    // J3D_HOOKFUNC(JonesFile_InitServices);
    // J3D_HOOKFUNC(JonesFile_ResetServices);
    // J3D_HOOKFUNC(JonesFile_AddResourcePath);
    // J3D_HOOKFUNC(JonesFile_CloseResource);
    // J3D_HOOKFUNC(JonesFile_OpenFile);
    // J3D_HOOKFUNC(JonesFile_CloseFile);
    // J3D_HOOKFUNC(JonesFile_FileRead);
    // J3D_HOOKFUNC(JonesFile_FileWrite);
    // J3D_HOOKFUNC(JonesFile_FileGets);
    // J3D_HOOKFUNC(JonesFile_FileEOF);
    // J3D_HOOKFUNC(JonesFile_FileTell);
    // J3D_HOOKFUNC(JonesFile_FileSeek);
    // J3D_HOOKFUNC(JonesFile_FileSize);
    // J3D_HOOKFUNC(JonesFile_FilePrintf);
}

void JonesFile_ResetGlobals(void)
{
    memset(&JonesFile_aResources, 0, sizeof(JonesFile_aResources));
    memset(&JonesFile_sysHS, 0, sizeof(JonesFile_sysHS));
    memset(&JonesFile_aPathBuf, 0, sizeof(JonesFile_aPathBuf));
    memset(&JonesFile_aFileHandles, 0, sizeof(JonesFile_aFileHandles));
    memset(&JonesFile_bStartup, 0, sizeof(JonesFile_bStartup));
    memset(&JonesFile_bOpened, 0, sizeof(JonesFile_bOpened));
    memset(&JonesFile_pSysEnv, 0, sizeof(JonesFile_pSysEnv));
    memset(&JonesFile_pHS, 0, sizeof(JonesFile_pHS));
    memset(&JonesFile_hsInitCount, 0, sizeof(JonesFile_hsInitCount));
}

void J3DAPI JonesFile_Startup(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(JonesFile_Startup, pHS);
}

void JonesFile_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesFile_Shutdown);
}

int J3DAPI JonesFile_Open(tHostServices* pEnv, const char* pInstallPath, const char* pPathCD)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_Open, pEnv, pInstallPath, pPathCD);
}

void J3DAPI JonesFile_Close()
{
    J3D_TRAMPOLINE_CALL(JonesFile_Close);
}

int J3DAPI JonesFile_GetCurrentCDNum()
{
    return J3D_TRAMPOLINE_CALL(JonesFile_GetCurrentCDNum);
}

int J3DAPI JonesFile_FileExists(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileExists, pFilename);
}

void J3DAPI JonesFile_AddInstallPath(const char* pPath)
{
    J3D_TRAMPOLINE_CALL(JonesFile_AddInstallPath, pPath);
}

void J3DAPI JonesFile_AddCDPath(const char* pPath)
{
    J3D_TRAMPOLINE_CALL(JonesFile_AddCDPath, pPath);
}

void JonesFile_InitServices(void)
{
    J3D_TRAMPOLINE_CALL(JonesFile_InitServices);
}

void JonesFile_ResetServices(void)
{
    J3D_TRAMPOLINE_CALL(JonesFile_ResetServices);
}

void J3DAPI JonesFile_AddResourcePath(JonesResource* pRsource, const char* pPath)
{
    J3D_TRAMPOLINE_CALL(JonesFile_AddResourcePath, pRsource, pPath);
}

void J3DAPI JonesFile_CloseResource(JonesResource* pResource)
{
    J3D_TRAMPOLINE_CALL(JonesFile_CloseResource, pResource);
}

tFileHandle J3DAPI JonesFile_OpenFile(const char* pFilename, const char* mode)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_OpenFile, pFilename, mode);
}

int J3DAPI JonesFile_CloseFile(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_CloseFile, fh);
}

size_t J3DAPI JonesFile_FileRead(tFileHandle fh, void* pDst, size_t size)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileRead, fh, pDst, size);
}

size_t J3DAPI JonesFile_FileWrite(tFileHandle fh, const void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileWrite, fh, pData, size);
}

char* J3DAPI JonesFile_FileGets(tFileHandle fh, char* pStr, size_t size)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileGets, fh, pStr, size);
}

int J3DAPI JonesFile_FileEOF(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileEOF, fh);
}

int J3DAPI JonesFile_FileTell(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileTell, fh);
}

int J3DAPI JonesFile_FileSeek(tFileHandle fh, int offset, int origin)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileSeek, fh, offset, origin);
}

size_t J3DAPI JonesFile_FileSize(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FileSize, pFilename);
}

int JonesFile_FilePrintf(tFileHandle fh, const char* aFormat, ...)
{
    return J3D_TRAMPOLINE_CALL(JonesFile_FilePrintf, fh, aFormat);
}
