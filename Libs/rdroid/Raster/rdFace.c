#include "rdFace.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdFace_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdFace_NewEntry);
    // J3D_HOOKFUNC(rdFace_FreeEntry);
}

void rdFace_ResetGlobals(void)
{

}

int J3DAPI rdFace_NewEntry(rdFace* pFace)
{
    return J3D_TRAMPOLINE_CALL(rdFace_NewEntry, pFace);
}

void J3DAPI rdFace_FreeEntry(rdFace* pFace)
{
    J3D_TRAMPOLINE_CALL(rdFace_FreeEntry, pFace);
}
