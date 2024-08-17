#include "sithCogFunctionPlayer.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogFunctionPlayer_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionPlayer_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IMPStartFiring);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IMPEndFiring);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetPlayerInPor);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_JewelFlyingStatus);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_StartJewelFlying);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_MakeMeStop);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvActivated);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvAvailable);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetInvDisabled);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvActivated);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvAvailable);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetGoalFlags);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_ClearGoalFlags);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetNumPlayers);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetMaxPlayers);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetAbsoluteMaxPlayers);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetLocalPlayerThing);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetPlayerThing);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetPlayerNum);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_PickupBackpack);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_NthBackpackBin);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_NthBackpackValue);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetNumBackbackItems);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_CreateBackpack);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetRespawnMask);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetRespawnMask);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SyncScores);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetCurItem);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IsAming);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetSwimmingInventory);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IsInvisible);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_ResetInventory);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_IsItemFound);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_SetElectricWhip);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetCutsceneMode);
    // J3D_HOOKFUNC(sithCogFunctionPlayer_GetLastWeapon);
}

void sithCogFunctionPlayer_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionPlayer_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunctionPlayer_IMPStartFiring(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IMPStartFiring, pCog);
}

void J3DAPI sithCogFunctionPlayer_IMPEndFiring(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IMPEndFiring, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetPlayerInPor(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetPlayerInPor, pCog);
}

void J3DAPI sithCogFunctionPlayer_JewelFlyingStatus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_JewelFlyingStatus, pCog);
}

void J3DAPI sithCogFunctionPlayer_StartJewelFlying(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_StartJewelFlying, pCog);
}

void J3DAPI sithCogFunctionPlayer_MakeMeStop(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_MakeMeStop, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetInvActivated(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetInvActivated, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetInvAvailable(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetInvAvailable, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetInvDisabled(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetInvDisabled, pCog);
}

void J3DAPI sithCogFunctionPlayer_IsInvActivated(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IsInvActivated, pCog);
}

void J3DAPI sithCogFunctionPlayer_IsInvAvailable(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IsInvAvailable, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetGoalFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetGoalFlags, pCog);
}

void J3DAPI sithCogFunctionPlayer_ClearGoalFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_ClearGoalFlags, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetNumPlayers(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetNumPlayers, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetMaxPlayers(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetMaxPlayers, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetAbsoluteMaxPlayers(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetAbsoluteMaxPlayers, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetLocalPlayerThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetLocalPlayerThing, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetPlayerThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetPlayerThing, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetPlayerNum(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetPlayerNum, pCog);
}

void J3DAPI sithCogFunctionPlayer_PickupBackpack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_PickupBackpack, pCog);
}

void J3DAPI sithCogFunctionPlayer_NthBackpackBin(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_NthBackpackBin, pCog);
}

void J3DAPI sithCogFunctionPlayer_NthBackpackValue(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_NthBackpackValue, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetNumBackbackItems(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetNumBackbackItems, pCog);
}

void J3DAPI sithCogFunctionPlayer_CreateBackpack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_CreateBackpack, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetRespawnMask(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetRespawnMask, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetRespawnMask(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetRespawnMask, pCog);
}

void J3DAPI sithCogFunctionPlayer_SyncScores(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SyncScores, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetCurItem(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetCurItem, pCog);
}

void J3DAPI sithCogFunctionPlayer_IsAming(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IsAming, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetSwimmingInventory(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetSwimmingInventory, pCog);
}

void J3DAPI sithCogFunctionPlayer_IsInvisible(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IsInvisible, pCog);
}

void J3DAPI sithCogFunctionPlayer_ResetInventory(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_ResetInventory, pCog);
}

void J3DAPI sithCogFunctionPlayer_IsItemFound(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_IsItemFound, pCog);
}

void J3DAPI sithCogFunctionPlayer_SetElectricWhip(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_SetElectricWhip, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetCutsceneMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetCutsceneMode, pCog);
}

void J3DAPI sithCogFunctionPlayer_GetLastWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionPlayer_GetLastWeapon, pCog);
}
