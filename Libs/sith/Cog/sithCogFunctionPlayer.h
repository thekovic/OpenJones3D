#ifndef SITH_SITHCOGFUNCTIONPLAYER_H
#define SITH_SITHCOGFUNCTIONPLAYER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunctionPlayer_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunctionPlayer_IMPStartFiring(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IMPEndFiring(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetPlayerInPor(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_JewelFlyingStatus(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_StartJewelFlying(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_MakeMeStop(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetInvActivated(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetInvAvailable(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetInvDisabled(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IsInvActivated(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IsInvAvailable(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetGoalFlags(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_ClearGoalFlags(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetNumPlayers(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetMaxPlayers(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetAbsoluteMaxPlayers(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetLocalPlayerThing(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetPlayerThing(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetPlayerNum(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_PickupBackpack(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_NthBackpackBin(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_NthBackpackValue(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetNumBackbackItems(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_CreateBackpack(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetRespawnMask(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetRespawnMask(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SyncScores(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetCurItem(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IsAming(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetSwimmingInventory(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IsInvisible(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_ResetInventory(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_IsItemFound(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_SetElectricWhip(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetCutsceneMode(SithCog* pCog);
void J3DAPI sithCogFunctionPlayer_GetLastWeapon(SithCog* pCog);

// Helper hooking functions
void sithCogFunctionPlayer_InstallHooks(void);
void sithCogFunctionPlayer_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTIONPLAYER_H
