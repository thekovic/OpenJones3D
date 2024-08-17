#include "stdMemory.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdMemory_aZoneData J3D_DECL_FAR_ARRAYVAR(stdMemory_aZoneData, tMemoryBlock(*)[8456])
#define stdMemory_bStartup J3D_DECL_FAR_VAR(stdMemory_bStartup, int)
#define stdMemory_bOpen J3D_DECL_FAR_VAR(stdMemory_bOpen, int)

void stdMemory_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdMemory_Startup);
    // J3D_HOOKFUNC(stdMemory_Shutdown);
    // J3D_HOOKFUNC(stdMemory_Open);
    // J3D_HOOKFUNC(stdMemory_Close);
    // J3D_HOOKFUNC(stdMemory_Malloc);
    // J3D_HOOKFUNC(stdMemory_Free);
    // J3D_HOOKFUNC(stdMemory_Realloc);
    // J3D_HOOKFUNC(stdMemory_BlockMalloc);
    // J3D_HOOKFUNC(stdMemory_BlockFree);
    // J3D_HOOKFUNC(stdMemory_BlockRealloc);
    // J3D_HOOKFUNC(stdMemory_BlockAlloc);
}

void stdMemory_ResetGlobals(void)
{
    memset(&stdMemory_aZoneData, 0, sizeof(stdMemory_aZoneData));
    memset(&stdMemory_bStartup, 0, sizeof(stdMemory_bStartup));
    memset(&stdMemory_bOpen, 0, sizeof(stdMemory_bOpen));
    memset(&stdMemory_g_curState, 0, sizeof(stdMemory_g_curState));
}

int stdMemory_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_Startup);
}

void stdMemory_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(stdMemory_Shutdown);
}

int stdMemory_Open(void)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_Open);
}

void stdMemory_Close(void)
{
    J3D_TRAMPOLINE_CALL(stdMemory_Close);
}

void* J3DAPI stdMemory_Malloc(size_t size, const char* pFilename, size_t line)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_Malloc, size, pFilename, line);
}

void J3DAPI stdMemory_Free(void* pBytes)
{
    J3D_TRAMPOLINE_CALL(stdMemory_Free, pBytes);
}

void* J3DAPI stdMemory_Realloc(void* pBytes, size_t size, const char* pFilename, size_t line)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_Realloc, pBytes, size, pFilename, line);
}

void* J3DAPI stdMemory_BlockMalloc(size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockMalloc, size);
}

void J3DAPI stdMemory_BlockFree(void* pMemory)
{
    J3D_TRAMPOLINE_CALL(stdMemory_BlockFree, pMemory);
}

void* J3DAPI stdMemory_BlockRealloc(void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockRealloc, pData, size);
}

void* J3DAPI stdMemory_BlockAlloc(int size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockAlloc, size);
}
