#include "sithCogFunction.h"
#include <j3dcore/j3dhook.h>

#include <sith/Cog/sithCog.h>
#include <sith/Cog/sithCogExec.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/RTI/symbols.h>

#include <std/General/stdUtil.h>


void sithCogFunction_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunction_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunction_GetSenderID);
    // J3D_HOOKFUNC(sithCogFunction_GetSenderRef);
    // J3D_HOOKFUNC(sithCogFunction_GetSenderType);
    // J3D_HOOKFUNC(sithCogFunction_GetSourceRef);
    // J3D_HOOKFUNC(sithCogFunction_GetSourceType);
    // J3D_HOOKFUNC(sithCogFunction_GetSysDate);
    // J3D_HOOKFUNC(sithCogFunction_GetSysTime);
    J3D_HOOKFUNC(sithCogFunction_Sleep);
    // J3D_HOOKFUNC(sithCogFunction_Print);
    // J3D_HOOKFUNC(sithCogFunction_PrintVector);
    // J3D_HOOKFUNC(sithCogFunction_PrintFlex);
    // J3D_HOOKFUNC(sithCogFunction_PrintInt);
    // J3D_HOOKFUNC(sithCogFunction_SurfaceAnim);
    // J3D_HOOKFUNC(sithCogFunction_MaterialAnim);
    // J3D_HOOKFUNC(sithCogFunction_StopMaterialAnim);
    // J3D_HOOKFUNC(sithCogFunction_StopAnim);
    // J3D_HOOKFUNC(sithCogFunction_StopSurfaceAnim);
    // J3D_HOOKFUNC(sithCogFunction_GetSurfaceAnim);
    // J3D_HOOKFUNC(sithCogFunction_LoadTemplate);
    // J3D_HOOKFUNC(sithCogFunction_LoadKeyframe);
    // J3D_HOOKFUNC(sithCogFunction_LoadModel);
    // J3D_HOOKFUNC(sithCogFunction_SetPulse);
    // J3D_HOOKFUNC(sithCogFunction_SetTimer);
    // J3D_HOOKFUNC(sithCogFunction_SetTimerEx);
    // J3D_HOOKFUNC(sithCogFunction_KillTimerEx);
    // J3D_HOOKFUNC(sithCogFunction_Reset);
    // J3D_HOOKFUNC(sithCogFunction_VectorSet);
    // J3D_HOOKFUNC(sithCogFunction_VectorAdd);
    // J3D_HOOKFUNC(sithCogFunction_VectorSub);
    // J3D_HOOKFUNC(sithCogFunction_VectorDot);
    // J3D_HOOKFUNC(sithCogFunction_VectorCross);
    // J3D_HOOKFUNC(sithCogFunction_VectorLen);
    // J3D_HOOKFUNC(sithCogFunction_VectorScale);
    // J3D_HOOKFUNC(sithCogFunction_VectorDist);
    // J3D_HOOKFUNC(sithCogFunction_VectorEqual);
    // J3D_HOOKFUNC(sithCogFunction_VectorRotate);
    // J3D_HOOKFUNC(sithCogFunction_VectorTransformToOrient);
    // J3D_HOOKFUNC(sithCogFunction_SendMessage);
    // J3D_HOOKFUNC(sithCogFunction_SendMessageEx);
    // J3D_HOOKFUNC(sithCogFunction_GetKeyLen);
    // J3D_HOOKFUNC(sithCogFunction_GetSithMode);
    // J3D_HOOKFUNC(sithCogFunction_GetGameTime);
    // J3D_HOOKFUNC(sithCogFunction_GetFlexGameTime);
    // J3D_HOOKFUNC(sithCogFunction_GetDifficulty);
    // J3D_HOOKFUNC(sithCogFunction_SetSubModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_ClearSubModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_GetSubModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_SetDebugModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_ClearDebugModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_GetDebugModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_BitSet);
    // J3D_HOOKFUNC(sithCogFunction_BitTest);
    // J3D_HOOKFUNC(sithCogFunction_BitClear);
    // J3D_HOOKFUNC(sithCogFunction_GetLevelTime);
    // J3D_HOOKFUNC(sithCogFunction_GetThingCount);
    // J3D_HOOKFUNC(sithCogFunction_GetThingTemplateCount);
    // J3D_HOOKFUNC(sithCogFunction_GetGravity);
    // J3D_HOOKFUNC(sithCogFunction_SetGravity);
    // J3D_HOOKFUNC(sithCogFunction_ReturnEx);
    // J3D_HOOKFUNC(sithCogFunction_GetParam);
    // J3D_HOOKFUNC(sithCogFunction_SetParam);
    // J3D_HOOKFUNC(sithCogFunction_VectorX);
    // J3D_HOOKFUNC(sithCogFunction_VectorY);
    // J3D_HOOKFUNC(sithCogFunction_VectorZ);
    // J3D_HOOKFUNC(sithCogFunction_VectorNorm);
    // J3D_HOOKFUNC(sithCogFunction_SetMaterialCel);
    // J3D_HOOKFUNC(sithCogFunction_GetMaterialCel);
    // J3D_HOOKFUNC(sithCogFunction_SetInvFlags);
    // J3D_HOOKFUNC(sithCogFunction_SetMapModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_GetMapModelFlags);
    // J3D_HOOKFUNC(sithCogFunction_ClearMapModeFlags);
    // J3D_HOOKFUNC(sithCogFunction_SetCameraFocus);
    // J3D_HOOKFUNC(sithCogFunction_SetCameraSecondaryFocus);
    // J3D_HOOKFUNC(sithCogFunction_GetPrimaryFocus);
    // J3D_HOOKFUNC(sithCogFunction_GetSecondaryFocus);
    // J3D_HOOKFUNC(sithCogFunction_SetCameraMode);
    // J3D_HOOKFUNC(sithCogFunction_GetCameraMode);
    // J3D_HOOKFUNC(sithCogFunction_SetPOVShake);
    // J3D_HOOKFUNC(sithCogFunction_HeapNew);
    // J3D_HOOKFUNC(sithCogFunction_HeapSet);
    // J3D_HOOKFUNC(sithCogFunction_HeapGet);
    // J3D_HOOKFUNC(sithCogFunction_HeapFree);
    // J3D_HOOKFUNC(sithCogFunction_GetSelfCog);
    // J3D_HOOKFUNC(sithCogFunction_GetMasterCog);
    // J3D_HOOKFUNC(sithCogFunction_SetMasterCog);
    // J3D_HOOKFUNC(sithCogFunction_GetCogByIndex);
    // J3D_HOOKFUNC(sithCogFunction_FireProjectile);
    // J3D_HOOKFUNC(sithCogFunction_SendTrigger);
    // J3D_HOOKFUNC(sithCogFunction_ActivateWeapon);
    // J3D_HOOKFUNC(sithCogFunction_DeactivateWeapon);
    // J3D_HOOKFUNC(sithCogFunction_DeactivateCurrentWeapon);
    // J3D_HOOKFUNC(sithCogFunction_SetFireWait);
    // J3D_HOOKFUNC(sithCogFunction_SetMountWait);
    // J3D_HOOKFUNC(sithCogFunction_SetAimWait);
    // J3D_HOOKFUNC(sithCogFunction_SelectWeapon);
    // J3D_HOOKFUNC(sithCogFunction_SelectWeaponWait);
    // J3D_HOOKFUNC(sithCogFunction_DeselectWeapon);
    // J3D_HOOKFUNC(sithCogFunction_DeselectWeaponWait);
    // J3D_HOOKFUNC(sithCogFunction_SetCurWeapon);
    // J3D_HOOKFUNC(sithCogFunction_GetCurWeapon);
    // J3D_HOOKFUNC(sithCogFunction_GetCameraStateFlags);
    // J3D_HOOKFUNC(sithCogFunction_SetCameraStateFlags);
    // J3D_HOOKFUNC(sithCogFunction_IsMulti);
    // J3D_HOOKFUNC(sithCogFunction_IsServer);
    // J3D_HOOKFUNC(sithCogFunction_AutoSavegame);
    // J3D_HOOKFUNC(sithCogFunction_GetHintSolved);
    // J3D_HOOKFUNC(sithCogFunction_SetHintSolved);
    // J3D_HOOKFUNC(sithCogFunction_SetHintUnsolved);
    // J3D_HOOKFUNC(sithCogFunction_Rand);
    // J3D_HOOKFUNC(sithCogFunction_RandBetween);
    // J3D_HOOKFUNC(sithCogFunction_RandVec);
    // J3D_HOOKFUNC(sithCogFunction_Round);
    // J3D_HOOKFUNC(sithCogFunction_Truncate);
    // J3D_HOOKFUNC(sithCogFunction_Abs);
    // J3D_HOOKFUNC(sithCogFunction_Pow);
    // J3D_HOOKFUNC(sithCogFunction_Sin);
    // J3D_HOOKFUNC(sithCogFunction_Cos);
    // J3D_HOOKFUNC(sithCogFunction_ArcTan);
    // J3D_HOOKFUNC(sithCogFunction_SetWeaponModel);
    // J3D_HOOKFUNC(sithCogFunction_ResetWeaponModel);
    // J3D_HOOKFUNC(sithCogFunction_LoadHolsterModel);
    // J3D_HOOKFUNC(sithCogFunction_SetHolsterModel);
    // J3D_HOOKFUNC(sithCogFunction_ResetHolsterModel);
    // J3D_HOOKFUNC(sithCogFunction_GetLastPistol);
    // J3D_HOOKFUNC(sithCogFunction_GetLastRifle);
    // J3D_HOOKFUNC(sithCogFunction_InEditor);
    // J3D_HOOKFUNC(sithCogFunction_CopyPlayerHolsters);
    // J3D_HOOKFUNC(sithCogFunction_GetPerformanceLevel);
    // J3D_HOOKFUNC(sithCogFunction_IsLevelName);
    // J3D_HOOKFUNC(sithCogFunction_SetFog);
    // J3D_HOOKFUNC(sithCogFunction_FindNewSector);
    // J3D_HOOKFUNC(sithCogFunction_FindNewSectorFromThing);
}

void sithCogFunction_ResetGlobals(void)
{

}

int J3DAPI sithCogFunction_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunction_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunction_GetSenderID(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSenderID, pCog);
}

void J3DAPI sithCogFunction_GetSenderRef(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSenderRef, pCog);
}

void J3DAPI sithCogFunction_GetSenderType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSenderType, pCog);
}

void J3DAPI sithCogFunction_GetSourceRef(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSourceRef, pCog);
}

void J3DAPI sithCogFunction_GetSourceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSourceType, pCog);
}

void J3DAPI sithCogFunction_GetSysDate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSysDate, pCog);
}

void J3DAPI sithCogFunction_GetSysTime(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSysTime, pCog);
}

//void J3DAPI sithCogFunction_Sleep(SithCog* pCog)
//{
//    J3D_TRAMPOLINE_CALL(sithCogFunction_Sleep, pCog);
//}

void J3DAPI sithCogFunction_Print(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Print, pCog);
}

void J3DAPI sithCogFunction_PrintVector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_PrintVector, pCog);
}

void J3DAPI sithCogFunction_PrintFlex(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_PrintFlex, pCog);
}

void J3DAPI sithCogFunction_PrintInt(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_PrintInt, pCog);
}

void J3DAPI sithCogFunction_SurfaceAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SurfaceAnim, pCog);
}

void J3DAPI sithCogFunction_MaterialAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_MaterialAnim, pCog);
}

void J3DAPI sithCogFunction_StopMaterialAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_StopMaterialAnim, pCog);
}

void J3DAPI sithCogFunction_StopAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_StopAnim, pCog);
}

void J3DAPI sithCogFunction_StopSurfaceAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_StopSurfaceAnim, pCog);
}

void J3DAPI sithCogFunction_GetSurfaceAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSurfaceAnim, pCog);
}

void J3DAPI sithCogFunction_LoadTemplate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_LoadTemplate, pCog);
}

void J3DAPI sithCogFunction_LoadKeyframe(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_LoadKeyframe, pCog);
}

void J3DAPI sithCogFunction_LoadModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_LoadModel, pCog);
}

void J3DAPI sithCogFunction_SetPulse(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetPulse, pCog);
}

void J3DAPI sithCogFunction_SetTimer(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetTimer, pCog);
}

void J3DAPI sithCogFunction_SetTimerEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetTimerEx, pCog);
}

void J3DAPI sithCogFunction_KillTimerEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_KillTimerEx, pCog);
}

void J3DAPI sithCogFunction_Reset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Reset, pCog);
}

void J3DAPI sithCogFunction_VectorSet(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorSet, pCog);
}

void J3DAPI sithCogFunction_VectorAdd(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorAdd, pCog);
}

void J3DAPI sithCogFunction_VectorSub(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorSub, pCog);
}

void J3DAPI sithCogFunction_VectorDot(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorDot, pCog);
}

void J3DAPI sithCogFunction_VectorCross(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorCross, pCog);
}

void J3DAPI sithCogFunction_VectorLen(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorLen, pCog);
}

void J3DAPI sithCogFunction_VectorScale(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorScale, pCog);
}

void J3DAPI sithCogFunction_VectorDist(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorDist, pCog);
}

void J3DAPI sithCogFunction_VectorEqual(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorEqual, pCog);
}

void J3DAPI sithCogFunction_VectorRotate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorRotate, pCog);
}

void J3DAPI sithCogFunction_VectorTransformToOrient(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorTransformToOrient, pCog);
}

void J3DAPI sithCogFunction_SendMessage(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SendMessage, pCog);
}

void J3DAPI sithCogFunction_SendMessageEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SendMessageEx, pCog);
}

void J3DAPI sithCogFunction_GetKeyLen(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetKeyLen, pCog);
}

void J3DAPI sithCogFunction_GetSithMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSithMode, pCog);
}

void J3DAPI sithCogFunction_GetGameTime(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetGameTime, pCog);
}

void J3DAPI sithCogFunction_GetFlexGameTime(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetFlexGameTime, pCog);
}

void J3DAPI sithCogFunction_GetDifficulty(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetDifficulty, pCog);
}

void J3DAPI sithCogFunction_SetSubModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetSubModeFlags, pCog);
}

void J3DAPI sithCogFunction_ClearSubModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ClearSubModeFlags, pCog);
}

void J3DAPI sithCogFunction_GetSubModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSubModeFlags, pCog);
}

void J3DAPI sithCogFunction_SetDebugModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetDebugModeFlags, pCog);
}

void J3DAPI sithCogFunction_ClearDebugModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ClearDebugModeFlags, pCog);
}

void J3DAPI sithCogFunction_GetDebugModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetDebugModeFlags, pCog);
}

void J3DAPI sithCogFunction_BitSet(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_BitSet, pCog);
}

void J3DAPI sithCogFunction_BitTest(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_BitTest, pCog);
}

void J3DAPI sithCogFunction_BitClear(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_BitClear, pCog);
}

void J3DAPI sithCogFunction_GetLevelTime(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetLevelTime, pCog);
}

void J3DAPI sithCogFunction_GetThingCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetThingCount, pCog);
}

void J3DAPI sithCogFunction_GetThingTemplateCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetThingTemplateCount, pCog);
}

void J3DAPI sithCogFunction_GetGravity(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetGravity, pCog);
}

void J3DAPI sithCogFunction_SetGravity(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetGravity, pCog);
}

void J3DAPI sithCogFunction_ReturnEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ReturnEx, pCog);
}

void J3DAPI sithCogFunction_GetParam(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetParam, pCog);
}

void J3DAPI sithCogFunction_SetParam(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetParam, pCog);
}

void J3DAPI sithCogFunction_VectorX(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorX, pCog);
}

void J3DAPI sithCogFunction_VectorY(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorY, pCog);
}

void J3DAPI sithCogFunction_VectorZ(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorZ, pCog);
}

void J3DAPI sithCogFunction_VectorNorm(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_VectorNorm, pCog);
}

void J3DAPI sithCogFunction_SetMaterialCel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetMaterialCel, pCog);
}

void J3DAPI sithCogFunction_GetMaterialCel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetMaterialCel, pCog);
}

// Set For inventory Inventory
void J3DAPI sithCogFunction_SetInvFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetInvFlags, pCog);
}

void J3DAPI sithCogFunction_SetMapModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetMapModeFlags, pCog);
}

void J3DAPI sithCogFunction_GetMapModelFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetMapModelFlags, pCog);
}

void J3DAPI sithCogFunction_ClearMapModeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ClearMapModeFlags, pCog);
}

void J3DAPI sithCogFunction_SetCameraFocus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetCameraFocus, pCog);
}

void J3DAPI sithCogFunction_SetCameraSecondaryFocus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetCameraSecondaryFocus, pCog);
}

void J3DAPI sithCogFunction_GetPrimaryFocus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetPrimaryFocus, pCog);
}

void J3DAPI sithCogFunction_GetSecondaryFocus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSecondaryFocus, pCog);
}

void J3DAPI sithCogFunction_SetCameraMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetCameraMode, pCog);
}

void J3DAPI sithCogFunction_GetCameraMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetCameraMode, pCog);
}

void J3DAPI sithCogFunction_SetPOVShake(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetPOVShake, pCog);
}

void J3DAPI sithCogFunction_HeapNew(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_HeapNew, pCog);
}

void J3DAPI sithCogFunction_HeapSet(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_HeapSet, pCog);
}

void J3DAPI sithCogFunction_HeapGet(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_HeapGet, pCog);
}

void J3DAPI sithCogFunction_HeapFree(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_HeapFree, pCog);
}

void J3DAPI sithCogFunction_GetSelfCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetSelfCog, pCog);
}

void J3DAPI sithCogFunction_GetMasterCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetMasterCog, pCog);
}

void J3DAPI sithCogFunction_SetMasterCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetMasterCog, pCog);
}

void J3DAPI sithCogFunction_GetCogByIndex(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetCogByIndex, pCog);
}

void J3DAPI sithCogFunction_FireProjectile(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_FireProjectile, pCog);
}

void J3DAPI sithCogFunction_SendTrigger(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SendTrigger, pCog);
}

void J3DAPI sithCogFunction_ActivateWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ActivateWeapon, pCog);
}

void J3DAPI sithCogFunction_DeactivateWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_DeactivateWeapon, pCog);
}

void J3DAPI sithCogFunction_DeactivateCurrentWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_DeactivateCurrentWeapon, pCog);
}

void J3DAPI sithCogFunction_SetFireWait(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetFireWait, pCog);
}

void J3DAPI sithCogFunction_SetMountWait(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetMountWait, pCog);
}

void J3DAPI sithCogFunction_SetAimWait(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetAimWait, pCog);
}

void J3DAPI sithCogFunction_SelectWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SelectWeapon, pCog);
}

void J3DAPI sithCogFunction_SelectWeaponWait(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SelectWeaponWait, pCog);
}

void J3DAPI sithCogFunction_DeselectWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_DeselectWeapon, pCog);
}

void J3DAPI sithCogFunction_DeselectWeaponWait(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_DeselectWeaponWait, pCog);
}

void J3DAPI sithCogFunction_SetCurWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetCurWeapon, pCog);
}

void J3DAPI sithCogFunction_GetCurWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetCurWeapon, pCog);
}

void J3DAPI sithCogFunction_GetCameraStateFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetCameraStateFlags, pCog);
}

void J3DAPI sithCogFunction_SetCameraStateFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetCameraStateFlags, pCog);
}

void J3DAPI sithCogFunction_IsMulti(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_IsMulti, pCog);
}

void J3DAPI sithCogFunction_IsServer(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_IsServer, pCog);
}

void J3DAPI sithCogFunction_AutoSavegame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_AutoSavegame, pCog);
}

void J3DAPI sithCogFunction_GetHintSolved(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetHintSolved, pCog);
}

void J3DAPI sithCogFunction_SetHintSolved(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetHintSolved, pCog);
}

void J3DAPI sithCogFunction_SetHintUnsolved(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetHintUnsolved, pCog);
}

void J3DAPI sithCogFunction_Rand(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Rand, pCog);
}

void J3DAPI sithCogFunction_RandBetween(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_RandBetween, pCog);
}

void J3DAPI sithCogFunction_RandVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_RandVec, pCog);
}

void J3DAPI sithCogFunction_Round(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Round, pCog);
}

void J3DAPI sithCogFunction_Truncate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Truncate, pCog);
}

void J3DAPI sithCogFunction_Abs(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Abs, pCog);
}

void J3DAPI sithCogFunction_Pow(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Pow, pCog);
}

void J3DAPI sithCogFunction_Sin(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Sin, pCog);
}

void J3DAPI sithCogFunction_Cos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_Cos, pCog);
}

void J3DAPI sithCogFunction_ArcTan(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ArcTan, pCog);
}

void J3DAPI sithCogFunction_SetWeaponModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetWeaponModel, pCog);
}

void J3DAPI sithCogFunction_ResetWeaponModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ResetWeaponModel, pCog);
}

void J3DAPI sithCogFunction_LoadHolsterModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_LoadHolsterModel, pCog);
}

void J3DAPI sithCogFunction_SetHolsterModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetHolsterModel, pCog);
}

void J3DAPI sithCogFunction_ResetHolsterModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_ResetHolsterModel, pCog);
}

void J3DAPI sithCogFunction_GetLastPistol(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetLastPistol, pCog);
}

void J3DAPI sithCogFunction_GetLastRifle(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetLastRifle, pCog);
}

void J3DAPI sithCogFunction_InEditor(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_InEditor, pCog);
}

void J3DAPI sithCogFunction_CopyPlayerHolsters(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_CopyPlayerHolsters, pCog);
}

void J3DAPI sithCogFunction_GetPerformanceLevel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_GetPerformanceLevel, pCog);
}

void J3DAPI sithCogFunction_IsLevelName(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_IsLevelName, pCog);
}

void J3DAPI sithCogFunction_SetFog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_SetFog, pCog);
}

void J3DAPI sithCogFunction_FindNewSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_FindNewSector, pCog);
}

void J3DAPI sithCogFunction_FindNewSectorFromThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunction_FindNewSectorFromThing, pCog);
}

void J3DAPI sithCogFunction_Sleep(SithCog* pCog)
{
    float secWait = sithCogExec_PopFlex(pCog);
    if ( secWait <= 0.0f )
    {
        SITHLOG_ERROR("Cog %s: Wait time less than 0 in Sleep(); assuming .1 seconds\n", pCog->aName);
        secWait = 0.1f;
    }

    if ( (pCog->flags & SITHCOG_DEBUG) != 0 )
    {
        STD_FORMAT(std_g_genBuffer, "Cog %s: Sleeping for %f seconds.\n", pCog->aName, secWait);
        sithConsole_PrintString(std_g_genBuffer);
    }

    pCog->status = SITHCOG_STATUS_SLEEPING;
    pCog->statusParams[0] = (sithTime_g_msecGameTime + (uint32_t)(secWait * 1000.0f));
}
