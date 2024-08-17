#include "stdBmp.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdBmp_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdBmp_WriteVBuffer);
    // J3D_HOOKFUNC(stdBmp_Load);
}

void stdBmp_ResetGlobals(void)
{

}

int J3DAPI stdBmp_WriteVBuffer(const char* pFilename, tVBuffer* pVBuffer)
{
    return J3D_TRAMPOLINE_CALL(stdBmp_WriteVBuffer, pFilename, pVBuffer);
}

HBITMAP J3DAPI stdBmp_Load(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdBmp_Load, pFilename);
}
