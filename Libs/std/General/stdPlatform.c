#include "stdPlatform.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdPlatform_bAssert J3D_DECL_FAR_VAR(stdPlatform_bAssert, int)

void stdPlatform_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdPlatform_InitServices);
    // J3D_HOOKFUNC(stdPlatform_ClearServices);
    // J3D_HOOKFUNC(stdPlatform_Assert);
    // J3D_HOOKFUNC(stdPlatform_Printf);
    // J3D_HOOKFUNC(stdPlatform_AllocHandle);
    // J3D_HOOKFUNC(stdPlatform_FreeHandle);
    // J3D_HOOKFUNC(stdPlatform_ReallocHandle);
    // J3D_HOOKFUNC(stdPlatform_LockHandle);
}

void stdPlatform_ResetGlobals(void)
{
    memset(&stdPlatform_bAssert, 0, sizeof(stdPlatform_bAssert));
}

int J3DAPI stdPlatform_InitServices(tHostServices* pHS)
{
    return J3D_TRAMPOLINE_CALL(stdPlatform_InitServices, pHS);
}

void J3DAPI stdPlatform_ClearServices(tHostServices* pHS)
{
    J3D_TRAMPOLINE_CALL(stdPlatform_ClearServices, pHS);
}

J3DNORETURN void J3DAPI stdPlatform_Assert(const char* pErrorStr, const char* pFilename, int linenum)
{
    J3D_TRAMPOLINE_CALL(stdPlatform_Assert, pErrorStr, pFilename, linenum);
}

int stdPlatform_Printf(const char* format, ...)
{
    return J3D_TRAMPOLINE_CALL(stdPlatform_Printf, format);
}

void* J3DAPI stdPlatform_AllocHandle(unsigned int size)
{
    return J3D_TRAMPOLINE_CALL(stdPlatform_AllocHandle, size);
}

void J3DAPI stdPlatform_FreeHandle(void* pData)
{
    J3D_TRAMPOLINE_CALL(stdPlatform_FreeHandle, pData);
}

void* J3DAPI stdPlatform_ReallocHandle(void* pMemory, unsigned int newSize)
{
    return J3D_TRAMPOLINE_CALL(stdPlatform_ReallocHandle, pMemory, newSize);
}

int J3DAPI stdPlatform_LockHandle(int a1)
{
    return J3D_TRAMPOLINE_CALL(stdPlatform_LockHandle, a1);
}
