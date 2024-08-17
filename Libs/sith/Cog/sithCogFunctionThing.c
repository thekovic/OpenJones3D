#include "sithCogFunctionThing.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogFunctionThing_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionThing_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsGhostVisible);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingAlpha);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingAlpha);
    // J3D_HOOKFUNC(sithCogFunctionThing_CreatePolylineThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetMoveStatus);
    // J3D_HOOKFUNC(sithCogFunctionThing_CopyOrient);
    // J3D_HOOKFUNC(sithCogFunctionThing_CopyOrientAndPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_CreateLaser);
    // J3D_HOOKFUNC(sithCogFunctionThing_CreateLightning);
    // J3D_HOOKFUNC(sithCogFunctionThing_AnimateSpriteSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingType);
    // J3D_HOOKFUNC(sithCogFunctionThing_PlayForceMoveMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetMoveMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_CreateThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_CreateThingAtPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_DamageThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_HealThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetHealth);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetMaxHealth);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetHealth);
    // J3D_HOOKFUNC(sithCogFunctionThing_DestroyThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_JumpToFrame);
    // J3D_HOOKFUNC(sithCogFunctionThing_MoveToFrame);
    // J3D_HOOKFUNC(sithCogFunctionThing_SkipToFrame);
    // J3D_HOOKFUNC(sithCogFunctionThing_RotatePivot);
    // J3D_HOOKFUNC(sithCogFunctionThing_Rotate);
    // J3D_HOOKFUNC(sithCogFunctionThing_RotateToPYR);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingLight);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamOffsetToThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamLookOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamLookOffsetToThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_MakeCamera2LikeCamera1);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraPosition);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraLookInterp);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraPosInterp);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetCameraFOV);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetCameraPosition);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraInterpSpeed);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraFOV);
    // J3D_HOOKFUNC(sithCogFunctionThing_ResetCameraFOV);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCameraFadeThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_ThingLight);
    // J3D_HOOKFUNC(sithCogFunctionThing_ThingLightAnim);
    // J3D_HOOKFUNC(sithCogFunctionThing_ThingFadeAnim);
    // J3D_HOOKFUNC(sithCogFunctionThing_WaitForStop);
    // J3D_HOOKFUNC(sithCogFunctionThing_WaitForAnimStop);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingSector);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetCurFrame);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetGoalFrame);
    // J3D_HOOKFUNC(sithCogFunctionThing_StopThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsThingMoving);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingPulse);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingTimer);
    // J3D_HOOKFUNC(sithCogFunctionThing_CaptureThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_ReleaseThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingParent);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetInventory);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetInventory);
    // J3D_HOOKFUNC(sithCogFunctionThing_ChangeInventory);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryCog);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingVelocity);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_ApplyForce);
    // J3D_HOOKFUNC(sithCogFunctionThing_AddThingVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingLVec);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingUVec);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingRVec);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetActorHeadPYR);
    // J3D_HOOKFUNC(sithCogFunctionThing_DetachThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingAttachFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToSurf);
    // J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThingEx);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingAttachedThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_WaitMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_PlayMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_StopMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_SynchMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsModePlaying);
    // J3D_HOOKFUNC(sithCogFunctionThing_PauseMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_ResumeMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_TrackToMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_PlayKey);
    // J3D_HOOKFUNC(sithCogFunctionThing_PlayKeyEx);
    // J3D_HOOKFUNC(sithCogFunctionThing_PauseKey);
    // J3D_HOOKFUNC(sithCogFunctionThing_ResumeKey);
    // J3D_HOOKFUNC(sithCogFunctionThing_StopKey);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMesh);
    // J3D_HOOKFUNC(sithCogFunctionThing_RestoreThingMesh);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingModel);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingModel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetArmedMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_ClearThingFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_TeleportThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingType);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetCollideType);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetCollideType);
    // J3D_HOOKFUNC(sithCogFunctionThing_FirstThingInSector);
    // J3D_HOOKFUNC(sithCogFunctionThing_NextThingInSector);
    // J3D_HOOKFUNC(sithCogFunctionThing_PrevThingInSector);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryMinimum);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryMaximum);
    // J3D_HOOKFUNC(sithCogFunctionThing_PathMovePause);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetHeadLightIntensity);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetHeadLightIntensity);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsThingVisible);
    // J3D_HOOKFUNC(sithCogFunctionThing_PathMoveResume);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingCurLightMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingCurLightMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetActorExtraSpeed);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingTemplate);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetLifeleft);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetLifeleft);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingThrust);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingThrust);
    // J3D_HOOKFUNC(sithCogFunctionThing_AmputateJoint);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetActorWeapon);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetActorWeapon);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetPhysicsFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetPhysicsFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_ClearPhysicsFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_ParseArg);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingRotVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingRotVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetRotThrust);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetRotThrust);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingLook);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLook);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLookPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLookThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsThingCrouching);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingClassCog);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingClassCog);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingCaptureCog);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingCaptureCog);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingRespawn);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingSignature);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingAttachFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_ClearThingAttachFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetParticleSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetParticleSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetParticleGrowthSpeed);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetParticleGrowthSpeed);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetParticleTimeoutRate);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetParticleTimeoutRate);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetTypeFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetTypeFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_ClearTypeFlags);
    // J3D_HOOKFUNC(sithCogFunctionThing_TakeItem);
    // J3D_HOOKFUNC(sithCogFunctionThing_HasLOS);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetFireOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetFireOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingUserData);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingUserData);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingCollideSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingCollideSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMoveSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMoveSize);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMass);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMass);
    // J3D_HOOKFUNC(sithCogFunctionThing_SyncThingPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_SyncThingAttachment);
    // J3D_HOOKFUNC(sithCogFunctionThing_SyncThingState);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetMajorMode);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingPosEx);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingGuid);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetGuidThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxAngVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxAngVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetJointAngle);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetJointAngle);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetMaxHeadPitch);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetMinHeadPitch);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadPitch);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMinHeadPitch);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetMaxHeadYaw);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadYaw);
    // J3D_HOOKFUNC(sithCogFunctionThing_InterpolatePYR);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingLVecPYR);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingLVec);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetHeadPYR);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingAirDrag);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingJointPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_IsThingModelName);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetMeshByName);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetNodeByName);
    // J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThingMesh);
    // J3D_HOOKFUNC(sithCogFunctionThing_DetachThingMesh);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxRotVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxRotVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxHeadVel);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetPuppetModeFPS);
    // J3D_HOOKFUNC(sithCogFunctionThing_ResetThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingInsertOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingInsertOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_GetThingEyeOffset);
    // J3D_HOOKFUNC(sithCogFunctionThing_CheckFloorDistance);
    // J3D_HOOKFUNC(sithCogFunctionThing_CheckPathToPoint);
    // J3D_HOOKFUNC(sithCogFunctionThing_MoveThing);
    // J3D_HOOKFUNC(sithCogFunctionThing_MoveThingToPos);
    // J3D_HOOKFUNC(sithCogFunctionThing_SetThingStateChange);
    // J3D_HOOKFUNC(sithCogFunctionThing_StartQuetzAnim);
    // J3D_HOOKFUNC(sithCogFunctionThing_BoardVehicle);
    // J3D_HOOKFUNC(sithCogFunctionThing_FadeInTrack);
    // J3D_HOOKFUNC(sithCogFunctionThing_MakeFairyDust);
    // J3D_HOOKFUNC(sithCogFunctionThing_MakeFairyDustDeluxe);
}

void sithCogFunctionThing_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionThing_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionThing_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunctionThing_IsGhostVisible(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsGhostVisible, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingAlpha(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingAlpha, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingAlpha(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingAlpha, pCog);
}

void J3DAPI sithCogFunctionThing_CreatePolylineThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CreatePolylineThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetMoveStatus(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetMoveStatus, pCog);
}

void J3DAPI sithCogFunctionThing_CopyOrient(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CopyOrient, pCog);
}

void J3DAPI sithCogFunctionThing_CopyOrientAndPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CopyOrientAndPos, pCog);
}

void J3DAPI sithCogFunctionThing_CreateLaser(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CreateLaser, pCog);
}

void J3DAPI sithCogFunctionThing_CreateLightning(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CreateLightning, pCog);
}

void J3DAPI sithCogFunctionThing_AnimateSpriteSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AnimateSpriteSize, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingType, pCog);
}

void J3DAPI sithCogFunctionThing_PlayForceMoveMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PlayForceMoveMode, pCog);
}

void J3DAPI sithCogFunctionThing_SetMoveMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetMoveMode, pCog);
}

void J3DAPI sithCogFunctionThing_CreateThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CreateThing, pCog);
}

void J3DAPI sithCogFunctionThing_CreateThingAtPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CreateThingAtPos, pCog);
}

void J3DAPI sithCogFunctionThing_DamageThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_DamageThing, pCog);
}

void J3DAPI sithCogFunctionThing_HealThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_HealThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetHealth(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetHealth, pCog);
}

void J3DAPI sithCogFunctionThing_GetMaxHealth(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetMaxHealth, pCog);
}

void J3DAPI sithCogFunctionThing_SetHealth(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetHealth, pCog);
}

void J3DAPI sithCogFunctionThing_DestroyThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_DestroyThing, pCog);
}

void J3DAPI sithCogFunctionThing_JumpToFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_JumpToFrame, pCog);
}

void J3DAPI sithCogFunctionThing_MoveToFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MoveToFrame, pCog);
}

void J3DAPI sithCogFunctionThing_SkipToFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SkipToFrame, pCog);
}

void J3DAPI sithCogFunctionThing_RotatePivot(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_RotatePivot, pCog);
}

void J3DAPI sithCogFunctionThing_Rotate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_Rotate, pCog);
}

void J3DAPI sithCogFunctionThing_RotateToPYR(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_RotateToPYR, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingLight, pCog);
}

void J3DAPI sithCogFunctionThing_SetExtCamOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetExtCamOffset, pCog);
}

void J3DAPI sithCogFunctionThing_SetExtCamOffsetToThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetExtCamOffsetToThing, pCog);
}

void J3DAPI sithCogFunctionThing_SetExtCamLookOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetExtCamLookOffset, pCog);
}

void J3DAPI sithCogFunctionThing_SetExtCamLookOffsetToThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetExtCamLookOffsetToThing, pCog);
}

void J3DAPI sithCogFunctionThing_MakeCamera2LikeCamera1(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MakeCamera2LikeCamera1, pCog);
}

void J3DAPI sithCogFunctionThing_SetCameraPosition(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraPosition, pCog);
}

void J3DAPI sithCogFunctionThing_SetCameraLookInterp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraLookInterp, pCog);
}

// Function enables/disables dolly mode for specified camera.
// 
// Dolly mode: when camera primary focus is changed the camera will interpolate move to the new focused thing instead of teleporte to it.
void J3DAPI sithCogFunctionThing_SetCameraPosInterp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraPosInterp, pCog);
}

void J3DAPI sithCogFunctionThing_GetCameraFOV(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetCameraFOV, pCog);
}

void J3DAPI sithCogFunctionThing_GetCameraPosition(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetCameraPosition, pCog);
}

void J3DAPI sithCogFunctionThing_SetCameraInterpSpeed(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraInterpSpeed, pCog);
}

void J3DAPI sithCogFunctionThing_SetCameraFOV(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraFOV, pCog);
}

void J3DAPI sithCogFunctionThing_ResetCameraFOV(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ResetCameraFOV, pCog);
}

void J3DAPI sithCogFunctionThing_SetCameraFadeThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCameraFadeThing, pCog);
}

void J3DAPI sithCogFunctionThing_ThingLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ThingLight, pCog);
}

void J3DAPI sithCogFunctionThing_ThingLightAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ThingLightAnim, pCog);
}

void J3DAPI sithCogFunctionThing_ThingFadeAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ThingFadeAnim, pCog);
}

void J3DAPI sithCogFunctionThing_WaitForStop(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_WaitForStop, pCog);
}

void J3DAPI sithCogFunctionThing_WaitForAnimStop(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_WaitForAnimStop, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingSector, pCog);
}

void J3DAPI sithCogFunctionThing_GetCurFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetCurFrame, pCog);
}

void J3DAPI sithCogFunctionThing_GetGoalFrame(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetGoalFrame, pCog);
}

void J3DAPI sithCogFunctionThing_StopThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_StopThing, pCog);
}

void J3DAPI sithCogFunctionThing_IsThingMoving(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsThingMoving, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingPulse(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingPulse, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingTimer(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingTimer, pCog);
}

void J3DAPI sithCogFunctionThing_CaptureThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CaptureThing, pCog);
}

void J3DAPI sithCogFunctionThing_ReleaseThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ReleaseThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingParent(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingParent, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingPos, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingPos, pCog);
}

void J3DAPI sithCogFunctionThing_GetInventory(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetInventory, pCog);
}

void J3DAPI sithCogFunctionThing_SetInventory(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetInventory, pCog);
}

void J3DAPI sithCogFunctionThing_ChangeInventory(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ChangeInventory, pCog);
}

void J3DAPI sithCogFunctionThing_GetInventoryCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetInventoryCog, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingVelocity(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingVelocity, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingVel, pCog);
}

void J3DAPI sithCogFunctionThing_ApplyForce(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ApplyForce, pCog);
}

void J3DAPI sithCogFunctionThing_AddThingVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AddThingVel, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingLVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingLVec, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingUVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingUVec, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingRVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingRVec, pCog);
}

void J3DAPI sithCogFunctionThing_GetActorHeadPYR(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetActorHeadPYR, pCog);
}

void J3DAPI sithCogFunctionThing_DetachThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_DetachThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingAttachFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingAttachFlags, pCog);
}

void J3DAPI sithCogFunctionThing_AttachThingToSurf(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AttachThingToSurf, pCog);
}

void J3DAPI sithCogFunctionThing_AttachThingToThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AttachThingToThing, pCog);
}

void J3DAPI sithCogFunctionThing_AttachThingToThingEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AttachThingToThingEx, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingAttachedThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingAttachedThing, pCog);
}

void J3DAPI sithCogFunctionThing_WaitMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_WaitMode, pCog);
}

void J3DAPI sithCogFunctionThing_PlayMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PlayMode, pCog);
}

void J3DAPI sithCogFunctionThing_StopMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_StopMode, pCog);
}

void J3DAPI sithCogFunctionThing_SynchMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SynchMode, pCog);
}

void J3DAPI sithCogFunctionThing_IsModePlaying(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsModePlaying, pCog);
}

void J3DAPI sithCogFunctionThing_PauseMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PauseMode, pCog);
}

void J3DAPI sithCogFunctionThing_ResumeMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ResumeMode, pCog);
}

void J3DAPI sithCogFunctionThing_TrackToMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_TrackToMode, pCog);
}

void J3DAPI sithCogFunctionThing_PlayKey(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PlayKey, pCog);
}

void J3DAPI sithCogFunctionThing_PlayKeyEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PlayKeyEx, pCog);
}

void J3DAPI sithCogFunctionThing_PauseKey(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PauseKey, pCog);
}

void J3DAPI sithCogFunctionThing_ResumeKey(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ResumeKey, pCog);
}

void J3DAPI sithCogFunctionThing_StopKey(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_StopKey, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMesh(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMesh, pCog);
}

void J3DAPI sithCogFunctionThing_RestoreThingMesh(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_RestoreThingMesh, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingModel, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingModel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingModel, pCog);
}

void J3DAPI sithCogFunctionThing_SetArmedMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetArmedMode, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingFlags, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingFlags, pCog);
}

void J3DAPI sithCogFunctionThing_ClearThingFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ClearThingFlags, pCog);
}

void J3DAPI sithCogFunctionThing_TeleportThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_TeleportThing, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingType, pCog);
}

void J3DAPI sithCogFunctionThing_GetCollideType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetCollideType, pCog);
}

void J3DAPI sithCogFunctionThing_SetCollideType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetCollideType, pCog);
}

void J3DAPI sithCogFunctionThing_FirstThingInSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_FirstThingInSector, pCog);
}

void J3DAPI sithCogFunctionThing_NextThingInSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_NextThingInSector, pCog);
}

void J3DAPI sithCogFunctionThing_PrevThingInSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PrevThingInSector, pCog);
}

void J3DAPI sithCogFunctionThing_GetInventoryMinimum(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetInventoryMinimum, pCog);
}

void J3DAPI sithCogFunctionThing_GetInventoryMaximum(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetInventoryMaximum, pCog);
}

void J3DAPI sithCogFunctionThing_PathMovePause(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PathMovePause, pCog);
}

void J3DAPI sithCogFunctionThing_SetHeadLightIntensity(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetHeadLightIntensity, pCog);
}

void J3DAPI sithCogFunctionThing_GetHeadLightIntensity(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetHeadLightIntensity, pCog);
}

void J3DAPI sithCogFunctionThing_IsThingVisible(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsThingVisible, pCog);
}

void J3DAPI sithCogFunctionThing_PathMoveResume(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_PathMoveResume, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingCurLightMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingCurLightMode, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingCurLightMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingCurLightMode, pCog);
}

void J3DAPI sithCogFunctionThing_SetActorExtraSpeed(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetActorExtraSpeed, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingTemplate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingTemplate, pCog);
}

void J3DAPI sithCogFunctionThing_SetLifeleft(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetLifeleft, pCog);
}

void J3DAPI sithCogFunctionThing_GetLifeleft(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetLifeleft, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingThrust, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingThrust, pCog);
}

void J3DAPI sithCogFunctionThing_AmputateJoint(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AmputateJoint, pCog);
}

void J3DAPI sithCogFunctionThing_SetActorWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetActorWeapon, pCog);
}

void J3DAPI sithCogFunctionThing_GetActorWeapon(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetActorWeapon, pCog);
}

void J3DAPI sithCogFunctionThing_GetPhysicsFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetPhysicsFlags, pCog);
}

void J3DAPI sithCogFunctionThing_SetPhysicsFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetPhysicsFlags, pCog);
}

void J3DAPI sithCogFunctionThing_ClearPhysicsFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ClearPhysicsFlags, pCog);
}

void J3DAPI sithCogFunctionThing_ParseArg(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ParseArg, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingRotVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingRotVel, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingRotVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingRotVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetRotThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetRotThrust, pCog);
}

void J3DAPI sithCogFunctionThing_GetRotThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetRotThrust, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingLook(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingLook, pCog);
}

int J3DAPI sithCogFunctionThing_SetThingHeadLook(SithThing* pThing, const rdVector3* pLook)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingHeadLook, pThing, pLook);
}

void J3DAPI sithCogFunctionThing_SetThingHeadLookPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingHeadLookPos, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingHeadLookThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingHeadLookThing, pCog);
}

void J3DAPI sithCogFunctionThing_IsThingCrouching(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsThingCrouching, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingClassCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingClassCog, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingClassCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingClassCog, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingCaptureCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingCaptureCog, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingCaptureCog(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingCaptureCog, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingRespawn(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingRespawn, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingSignature(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingSignature, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingAttachFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingAttachFlags, pCog);
}

void J3DAPI sithCogFunctionThing_ClearThingAttachFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ClearThingAttachFlags, pCog);
}

void J3DAPI sithCogFunctionThing_GetParticleSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetParticleSize, pCog);
}

void J3DAPI sithCogFunctionThing_SetParticleSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetParticleSize, pCog);
}

void J3DAPI sithCogFunctionThing_GetParticleGrowthSpeed(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetParticleGrowthSpeed, pCog);
}

void J3DAPI sithCogFunctionThing_SetParticleGrowthSpeed(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetParticleGrowthSpeed, pCog);
}

void J3DAPI sithCogFunctionThing_GetParticleTimeoutRate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetParticleTimeoutRate, pCog);
}

void J3DAPI sithCogFunctionThing_SetParticleTimeoutRate(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetParticleTimeoutRate, pCog);
}

void J3DAPI sithCogFunctionThing_GetTypeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetTypeFlags, pCog);
}

void J3DAPI sithCogFunctionThing_SetTypeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetTypeFlags, pCog);
}

void J3DAPI sithCogFunctionThing_ClearTypeFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ClearTypeFlags, pCog);
}

void J3DAPI sithCogFunctionThing_TakeItem(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_TakeItem, pCog);
}

void J3DAPI sithCogFunctionThing_HasLOS(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_HasLOS, pCog);
}

void J3DAPI sithCogFunctionThing_GetFireOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetFireOffset, pCog);
}

void J3DAPI sithCogFunctionThing_SetFireOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetFireOffset, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingUserData(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingUserData, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingUserData(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingUserData, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingCollideSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingCollideSize, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingCollideSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingCollideSize, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMoveSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMoveSize, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMoveSize(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMoveSize, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMass(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMass, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMass(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMass, pCog);
}

void J3DAPI sithCogFunctionThing_SyncThingPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SyncThingPos, pCog);
}

void J3DAPI sithCogFunctionThing_SyncThingAttachment(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SyncThingAttachment, pCog);
}

void J3DAPI sithCogFunctionThing_SyncThingState(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SyncThingState, pCog);
}

void J3DAPI sithCogFunctionThing_GetMajorMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetMajorMode, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingPosEx(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingPosEx, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingGuid(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingGuid, pCog);
}

void J3DAPI sithCogFunctionThing_GetGuidThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetGuidThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMaxVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMaxVel, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxAngVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxAngVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMaxAngVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMaxAngVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetJointAngle(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetJointAngle, pCog);
}

void J3DAPI sithCogFunctionThing_GetJointAngle(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetJointAngle, pCog);
}

void J3DAPI sithCogFunctionThing_SetMaxHeadPitch(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetMaxHeadPitch, pCog);
}

void J3DAPI sithCogFunctionThing_SetMinHeadPitch(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetMinHeadPitch, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadPitch(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxHeadPitch, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMinHeadPitch(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMinHeadPitch, pCog);
}

void J3DAPI sithCogFunctionThing_SetMaxHeadYaw(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetMaxHeadYaw, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadYaw(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxHeadYaw, pCog);
}

void J3DAPI sithCogFunctionThing_InterpolatePYR(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_InterpolatePYR, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingLVecPYR(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingLVecPYR, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingLVec(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingLVec, pCog);
}

void J3DAPI sithCogFunctionThing_SetHeadPYR(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetHeadPYR, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingAirDrag(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingAirDrag, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingJointPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingJointPos, pCog);
}

void J3DAPI sithCogFunctionThing_IsThingModelName(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_IsThingModelName, pCog);
}

void J3DAPI sithCogFunctionThing_GetMeshByName(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetMeshByName, pCog);
}

void J3DAPI sithCogFunctionThing_GetNodeByName(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetNodeByName, pCog);
}

void J3DAPI sithCogFunctionThing_AttachThingToThingMesh(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_AttachThingToThingMesh, pCog);
}

void J3DAPI sithCogFunctionThing_DetachThingMesh(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_DetachThingMesh, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxRotVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxRotVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMaxRotVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMaxRotVel, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingMaxHeadVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingMaxHeadVel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingMaxHeadVel, pCog);
}

void J3DAPI sithCogFunctionThing_SetPuppetModeFPS(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetPuppetModeFPS, pCog);
}

void J3DAPI sithCogFunctionThing_ResetThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_ResetThing, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingInsertOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingInsertOffset, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingInsertOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingInsertOffset, pCog);
}

void J3DAPI sithCogFunctionThing_GetThingEyeOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_GetThingEyeOffset, pCog);
}

void J3DAPI sithCogFunctionThing_CheckFloorDistance(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CheckFloorDistance, pCog);
}

void J3DAPI sithCogFunctionThing_CheckPathToPoint(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_CheckPathToPoint, pCog);
}

void J3DAPI sithCogFunctionThing_MoveThing(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MoveThing, pCog);
}

void J3DAPI sithCogFunctionThing_MoveThingToPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MoveThingToPos, pCog);
}

void J3DAPI sithCogFunctionThing_SetThingStateChange(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_SetThingStateChange, pCog);
}

void J3DAPI sithCogFunctionThing_StartQuetzAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_StartQuetzAnim, pCog);
}

void J3DAPI sithCogFunctionThing_BoardVehicle(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_BoardVehicle, pCog);
}

void J3DAPI sithCogFunctionThing_FadeInTrack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_FadeInTrack, pCog);
}

void J3DAPI sithCogFunctionThing_MakeFairyDust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MakeFairyDust, pCog);
}

void J3DAPI sithCogFunctionThing_MakeFairyDustDeluxe(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionThing_MakeFairyDustDeluxe, pCog);
}
