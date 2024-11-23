#include "sithExplosion.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithExplosion_bExpandFadeSet J3D_DECL_FAR_VAR(sithExplosion_bExpandFadeSet, int)

void sithExplosion_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithExplosion_Initialize);
    // J3D_HOOKFUNC(sithExplosion_CreateSpriteThing);
    // J3D_HOOKFUNC(sithExplosion_UpdateExpandFade);
    // J3D_HOOKFUNC(sithExplosion_GetDeltaValue);
    // J3D_HOOKFUNC(sithExplosion_Update);
    // J3D_HOOKFUNC(sithExplosion_MakeBlast);
    // J3D_HOOKFUNC(sithExplosion_ParseArg);
}

void sithExplosion_ResetGlobals(void)
{
    memset(&sithExplosion_bExpandFadeSet, 0, sizeof(sithExplosion_bExpandFadeSet));
}

void J3DAPI sithExplosion_Initialize(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithExplosion_Initialize, pThing);
}

void J3DAPI sithExplosion_CreateSpriteThing(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithExplosion_CreateSpriteThing, pThing);
}

void J3DAPI sithExplosion_UpdateExpandFade(SithExplosionInfo* pExplode)
{
    J3D_TRAMPOLINE_CALL(sithExplosion_UpdateExpandFade, pExplode);
}

float J3DAPI sithExplosion_GetDeltaValue(float min, float max, float maxTime, float deltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithExplosion_GetDeltaValue, min, max, maxTime, deltaTime);
}

void J3DAPI sithExplosion_Update(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithExplosion_Update, pThing, secDeltaTime);
}

void J3DAPI sithExplosion_MakeBlast(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithExplosion_MakeBlast, pThing);
}

int J3DAPI sithExplosion_ParseArg(StdConffileArg* pArg, SithThing* pThing, signed int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithExplosion_ParseArg, pArg, pThing, adjNum);
}
