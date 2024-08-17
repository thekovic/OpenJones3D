#include "stdEffect.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdEffect_fadeFactor J3D_DECL_FAR_VAR(stdEffect_fadeFactor, tStdFadeFactor)

void stdEffect_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdEffect_ResetImpl);
    // J3D_HOOKFUNC(stdEffect_SetFadeFactor);
    // J3D_HOOKFUNC(stdEffect_GetFadeFactor);
}

void stdEffect_ResetGlobals(void)
{
    memset(&stdEffect_fadeFactor, 0, sizeof(stdEffect_fadeFactor));
}

void J3DAPI stdEffect_ResetImpl()
{
    J3D_TRAMPOLINE_CALL(stdEffect_ResetImpl);
}

void J3DAPI stdEffect_SetFadeFactor(int bEnabled, float factor)
{
    J3D_TRAMPOLINE_CALL(stdEffect_SetFadeFactor, bEnabled, factor);
}

const tStdFadeFactor* J3DAPI stdEffect_GetFadeFactor()
{
    return J3D_TRAMPOLINE_CALL(stdEffect_GetFadeFactor);
}
