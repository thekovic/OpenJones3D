#include "sithCogFunctionSound.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogFunctionSound_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionSound_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlaySoundThing);
    // J3D_HOOKFUNC(sithCogFunctionSound_StopSoundThing);
    // J3D_HOOKFUNC(sithCogFunctionSound_StopAllSoundsThing);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlaySoundPos);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlaySoundLocal);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlaySoundGlobal);
    // J3D_HOOKFUNC(sithCogFunctionSound_StopSound);
    // J3D_HOOKFUNC(sithCogFunctionSound_LoadSound);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlaySoundClass);
    // J3D_HOOKFUNC(sithCogFunctionSound_StopSoundClass);
    // J3D_HOOKFUNC(sithCogFunctionSound_PlayVoiceMode);
    // J3D_HOOKFUNC(sithCogFunctionSound_ChangeVolume);
    // J3D_HOOKFUNC(sithCogFunctionSound_ChangePitch);
    // J3D_HOOKFUNC(sithCogFunctionSound_SectorSound);
    // J3D_HOOKFUNC(sithCogFunctionSound_GetSoundLen);
    // J3D_HOOKFUNC(sithCogFunctionSound_WaitForSound);
}

void sithCogFunctionSound_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionSound_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionSound_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunctionSound_PlaySoundThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlaySoundThing, pCog);
}

void J3DAPI sithCogFunctionSound_StopSoundThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_StopSoundThing, pCog);
}

void J3DAPI sithCogFunctionSound_StopAllSoundsThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_StopAllSoundsThing, pCog);
}

void J3DAPI sithCogFunctionSound_PlaySoundPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlaySoundPos, pCog);
}

void J3DAPI sithCogFunctionSound_PlaySoundLocal(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlaySoundLocal, pCog);
}

void J3DAPI sithCogFunctionSound_PlaySoundGlobal(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlaySoundGlobal, pCog);
}

void J3DAPI sithCogFunctionSound_StopSound(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_StopSound, pCog);
}

void J3DAPI sithCogFunctionSound_LoadSound(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_LoadSound, pCog);
}

void J3DAPI sithCogFunctionSound_PlaySoundClass(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlaySoundClass, pCog);
}

void J3DAPI sithCogFunctionSound_StopSoundClass(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_StopSoundClass, pCog);
}

void J3DAPI sithCogFunctionSound_PlayVoiceMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_PlayVoiceMode, pCog);
}

void J3DAPI sithCogFunctionSound_ChangeVolume(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_ChangeVolume, pCog);
}

void J3DAPI sithCogFunctionSound_ChangePitch(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_ChangePitch, pCog);
}

void J3DAPI sithCogFunctionSound_SectorSound(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_SectorSound, pCog);
}

void J3DAPI sithCogFunctionSound_GetSoundLen(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_GetSoundLen, pCog);
}

void J3DAPI sithCogFunctionSound_WaitForSound(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSound_WaitForSound, pCog);
}
