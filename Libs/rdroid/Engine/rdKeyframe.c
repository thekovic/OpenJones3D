#include "rdKeyframe.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdKeyframe_pKeyframeLoader J3D_DECL_FAR_VAR(rdKeyframe_pKeyframeLoader, rdKeyframeLoadFunc)

void rdKeyframe_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdKeyframe_RegisterLoader);
    // J3D_HOOKFUNC(rdKeyframe_NewEntry);
    // J3D_HOOKFUNC(rdKeyframe_LoadEntry);
    // J3D_HOOKFUNC(rdKeyframe_FreeEntry);
}

void rdKeyframe_ResetGlobals(void)
{
    memset(&rdKeyframe_pKeyframeLoader, 0, sizeof(rdKeyframe_pKeyframeLoader));
}

rdKeyframeLoadFunc J3DAPI rdKeyframe_RegisterLoader(rdKeyframeLoadFunc pFunc)
{
    return J3D_TRAMPOLINE_CALL(rdKeyframe_RegisterLoader, pFunc);
}

void J3DAPI rdKeyframe_NewEntry(rdKeyframe* pKeyframe)
{
    J3D_TRAMPOLINE_CALL(rdKeyframe_NewEntry, pKeyframe);
}

int J3DAPI rdKeyframe_LoadEntry(const char* pFilename, rdKeyframe* pKeyframe)
{
    return J3D_TRAMPOLINE_CALL(rdKeyframe_LoadEntry, pFilename, pKeyframe);
}

void J3DAPI rdKeyframe_FreeEntry(rdKeyframe* pKeyfreame)
{
    J3D_TRAMPOLINE_CALL(rdKeyframe_FreeEntry, pKeyfreame);
}
