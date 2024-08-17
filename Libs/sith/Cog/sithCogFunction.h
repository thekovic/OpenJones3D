#ifndef SITH_SITHCOGFUNCTION_H
#define SITH_SITHCOGFUNCTION_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunction_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunction_GetSenderID(SithCog* pCog);
void J3DAPI sithCogFunction_GetSenderRef(SithCog* pCog);
void J3DAPI sithCogFunction_GetSenderType(SithCog* pCog);
void J3DAPI sithCogFunction_GetSourceRef(SithCog* pCog);
void J3DAPI sithCogFunction_GetSourceType(SithCog* pCog);
void J3DAPI sithCogFunction_GetSysDate(SithCog* pCog);
void J3DAPI sithCogFunction_GetSysTime(SithCog* pCog);
void J3DAPI sithCogFunction_Sleep(SithCog* pCog);
void J3DAPI sithCogFunction_Print(SithCog* pCog);
void J3DAPI sithCogFunction_PrintVector(SithCog* pCog);
void J3DAPI sithCogFunction_PrintFlex(SithCog* pCog);
void J3DAPI sithCogFunction_PrintInt(SithCog* pCog);
void J3DAPI sithCogFunction_SurfaceAnim(SithCog* pCog);
void J3DAPI sithCogFunction_MaterialAnim(SithCog* pCog);
void J3DAPI sithCogFunction_StopMaterialAnim(SithCog* pCog);
void J3DAPI sithCogFunction_StopAnim(SithCog* pCog);
void J3DAPI sithCogFunction_StopSurfaceAnim(SithCog* pCog);
void J3DAPI sithCogFunction_GetSurfaceAnim(SithCog* pCog);
void J3DAPI sithCogFunction_LoadTemplate(SithCog* pCog);
void J3DAPI sithCogFunction_LoadKeyframe(SithCog* pCog);
void J3DAPI sithCogFunction_LoadModel(SithCog* pCog);
void J3DAPI sithCogFunction_SetPulse(SithCog* pCog);
void J3DAPI sithCogFunction_SetTimer(SithCog* pCog);
void J3DAPI sithCogFunction_SetTimerEx(SithCog* pCog);
void J3DAPI sithCogFunction_KillTimerEx(SithCog* pCog);
void J3DAPI sithCogFunction_Reset(SithCog* pCog);
void J3DAPI sithCogFunction_VectorSet(SithCog* pCog);
void J3DAPI sithCogFunction_VectorAdd(SithCog* pCog);
void J3DAPI sithCogFunction_VectorSub(SithCog* pCog);
void J3DAPI sithCogFunction_VectorDot(SithCog* pCog);
void J3DAPI sithCogFunction_VectorCross(SithCog* pCog);
void J3DAPI sithCogFunction_VectorLen(SithCog* pCog);
void J3DAPI sithCogFunction_VectorScale(SithCog* pCog);
void J3DAPI sithCogFunction_VectorDist(SithCog* pCog);
void J3DAPI sithCogFunction_VectorEqual(SithCog* pCog);
void J3DAPI sithCogFunction_VectorRotate(SithCog* pCog);
void J3DAPI sithCogFunction_VectorTransformToOrient(SithCog* pCog);
void J3DAPI sithCogFunction_SendMessage(SithCog* pCog);
void J3DAPI sithCogFunction_SendMessageEx(SithCog* pCog);
void J3DAPI sithCogFunction_GetKeyLen(SithCog* pCog);
void J3DAPI sithCogFunction_GetSithMode(SithCog* pCog);
void J3DAPI sithCogFunction_GetGameTime(SithCog* pCog);
void J3DAPI sithCogFunction_GetFlexGameTime(SithCog* pCog);
void J3DAPI sithCogFunction_GetDifficulty(SithCog* pCog);
void J3DAPI sithCogFunction_SetSubModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_ClearSubModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_GetSubModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_SetDebugModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_ClearDebugModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_GetDebugModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_BitSet(SithCog* pCog);
void J3DAPI sithCogFunction_BitTest(SithCog* pCog);
void J3DAPI sithCogFunction_BitClear(SithCog* pCog);
void J3DAPI sithCogFunction_GetLevelTime(SithCog* pCog);
void J3DAPI sithCogFunction_GetThingCount(SithCog* pCog);
void J3DAPI sithCogFunction_GetThingTemplateCount(SithCog* pCog);
void J3DAPI sithCogFunction_GetGravity(SithCog* pCog);
void J3DAPI sithCogFunction_SetGravity(SithCog* pCog);
void J3DAPI sithCogFunction_ReturnEx(SithCog* pCog);
void J3DAPI sithCogFunction_GetParam(SithCog* pCog);
void J3DAPI sithCogFunction_SetParam(SithCog* pCog);
void J3DAPI sithCogFunction_VectorX(SithCog* pCog);
void J3DAPI sithCogFunction_VectorY(SithCog* pCog);
void J3DAPI sithCogFunction_VectorZ(SithCog* pCog);
void J3DAPI sithCogFunction_VectorNorm(SithCog* pCog);
void J3DAPI sithCogFunction_SetMaterialCel(SithCog* pCog);
void J3DAPI sithCogFunction_GetMaterialCel(SithCog* pCog);
// Set For inventory Inventory
void J3DAPI sithCogFunction_SetInvFlags(SithCog* pCog);
void J3DAPI sithCogFunction_SetMapModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_GetMapModelFlags(SithCog* pCog);
void J3DAPI sithCogFunction_ClearMapModeFlags(SithCog* pCog);
void J3DAPI sithCogFunction_SetCameraFocus(SithCog* pCog);
void J3DAPI sithCogFunction_SetCameraSecondaryFocus(SithCog* pCog);
void J3DAPI sithCogFunction_GetPrimaryFocus(SithCog* pCog);
void J3DAPI sithCogFunction_GetSecondaryFocus(SithCog* pCog);
void J3DAPI sithCogFunction_SetCameraMode(SithCog* pCog);
void J3DAPI sithCogFunction_GetCameraMode(SithCog* pCog);
void J3DAPI sithCogFunction_SetPOVShake(SithCog* pCog);
void J3DAPI sithCogFunction_HeapNew(SithCog* pCog);
void J3DAPI sithCogFunction_HeapSet(SithCog* pCog);
void J3DAPI sithCogFunction_HeapGet(SithCog* pCog);
void J3DAPI sithCogFunction_HeapFree(SithCog* pCog);
void J3DAPI sithCogFunction_GetSelfCog(SithCog* pCog);
void J3DAPI sithCogFunction_GetMasterCog(SithCog* pCog);
void J3DAPI sithCogFunction_SetMasterCog(SithCog* pCog);
void J3DAPI sithCogFunction_GetCogByIndex(SithCog* pCog);
void J3DAPI sithCogFunction_FireProjectile(SithCog* pCog);
void J3DAPI sithCogFunction_SendTrigger(SithCog* pCog);
void J3DAPI sithCogFunction_ActivateWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_DeactivateWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_DeactivateCurrentWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_SetFireWait(SithCog* pCog);
void J3DAPI sithCogFunction_SetMountWait(SithCog* pCog);
void J3DAPI sithCogFunction_SetAimWait(SithCog* pCog);
void J3DAPI sithCogFunction_SelectWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_SelectWeaponWait(SithCog* pCog);
void J3DAPI sithCogFunction_DeselectWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_DeselectWeaponWait(SithCog* pCog);
void J3DAPI sithCogFunction_SetCurWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_GetCurWeapon(SithCog* pCog);
void J3DAPI sithCogFunction_GetCameraStateFlags(SithCog* pCog);
void J3DAPI sithCogFunction_SetCameraStateFlags(SithCog* pCog);
void J3DAPI sithCogFunction_IsMulti(SithCog* pCog);
void J3DAPI sithCogFunction_IsServer(SithCog* pCog);
void J3DAPI sithCogFunction_AutoSavegame(SithCog* pCog);
void J3DAPI sithCogFunction_GetHintSolved(SithCog* pCog);
void J3DAPI sithCogFunction_SetHintSolved(SithCog* pCog);
void J3DAPI sithCogFunction_SetHintUnsolved(SithCog* pCog);
void J3DAPI sithCogFunction_Rand(SithCog* pCog);
void J3DAPI sithCogFunction_RandBetween(SithCog* pCog);
void J3DAPI sithCogFunction_RandVec(SithCog* pCog);
void J3DAPI sithCogFunction_Round(SithCog* pCog);
void J3DAPI sithCogFunction_Truncate(SithCog* pCog);
void J3DAPI sithCogFunction_Abs(SithCog* pCog);
void J3DAPI sithCogFunction_Pow(SithCog* pCog);
void J3DAPI sithCogFunction_Sin(SithCog* pCog);
void J3DAPI sithCogFunction_Cos(SithCog* pCog);
void J3DAPI sithCogFunction_ArcTan(SithCog* pCog);
void J3DAPI sithCogFunction_SetWeaponModel(SithCog* pCog);
void J3DAPI sithCogFunction_ResetWeaponModel(SithCog* pCog);
void J3DAPI sithCogFunction_LoadHolsterModel(SithCog* pCog);
void J3DAPI sithCogFunction_SetHolsterModel(SithCog* pCog);
void J3DAPI sithCogFunction_ResetHolsterModel(SithCog* pCog);
void J3DAPI sithCogFunction_GetLastPistol(SithCog* pCog);
void J3DAPI sithCogFunction_GetLastRifle(SithCog* pCog);
void J3DAPI sithCogFunction_InEditor(SithCog* pCog);
void J3DAPI sithCogFunction_CopyPlayerHolsters(SithCog* pCog);
void J3DAPI sithCogFunction_GetPerformanceLevel(SithCog* pCog);
void J3DAPI sithCogFunction_IsLevelName(SithCog* pCog);
void J3DAPI sithCogFunction_SetFog(SithCog* pCog);
void J3DAPI sithCogFunction_FindNewSector(SithCog* pCog);
void J3DAPI sithCogFunction_FindNewSectorFromThing(SithCog* pCog);

// Helper hooking functions
void sithCogFunction_InstallHooks(void);
void sithCogFunction_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTION_H
