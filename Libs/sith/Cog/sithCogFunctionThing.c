#define _CRT_SECURE_NO_WARNINGS
#include "sithCogFunctionThing.h"
#include <j3dcore/j3dhook.h>

#include <sith/AI/sithAIMove.h>
#include <sith/AI/sithAIUtil.h>
#include <sith/Cog/sithCog.h>
#include <sith/Cog/sithCogExec.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Dss/sithDSSThing.h>
#include <sith/Engine/sithAnimate.h>
#include <sith/Engine/sithCamera.h>
#include <sith/Engine/sithCollision.h>
#include <sith/Engine/sithPathMove.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Gameplay/sithFX.h>
#include <sith/Gameplay/sithInventory.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithWorld.h>

#include <rdroid/Engine/rdPuppet.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Primitives/rdModel3.h>

#include <std/General/stdMath.h>
#include <std/Win95/stdComm.h>

void sithCogFunctionThing_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    J3D_HOOKFUNC(sithCogFunctionThing_RegisterFunctions);
    J3D_HOOKFUNC(sithCogFunctionThing_IsGhostVisible);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingAlpha);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingAlpha);
    J3D_HOOKFUNC(sithCogFunctionThing_CreatePolylineThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetMoveStatus);
    J3D_HOOKFUNC(sithCogFunctionThing_CopyOrient);
    J3D_HOOKFUNC(sithCogFunctionThing_CopyOrientAndPos);
    J3D_HOOKFUNC(sithCogFunctionThing_CreateLaser);
    J3D_HOOKFUNC(sithCogFunctionThing_CreateLightning);
    J3D_HOOKFUNC(sithCogFunctionThing_AnimateSpriteSize);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingType);
    J3D_HOOKFUNC(sithCogFunctionThing_PlayForceMoveMode);
    J3D_HOOKFUNC(sithCogFunctionThing_SetMoveMode);
    J3D_HOOKFUNC(sithCogFunctionThing_CreateThing);
    J3D_HOOKFUNC(sithCogFunctionThing_CreateThingAtPos);
    J3D_HOOKFUNC(sithCogFunctionThing_DamageThing);
    J3D_HOOKFUNC(sithCogFunctionThing_HealThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetHealth);
    J3D_HOOKFUNC(sithCogFunctionThing_GetMaxHealth);
    J3D_HOOKFUNC(sithCogFunctionThing_SetHealth);
    J3D_HOOKFUNC(sithCogFunctionThing_DestroyThing);
    J3D_HOOKFUNC(sithCogFunctionThing_JumpToFrame);
    J3D_HOOKFUNC(sithCogFunctionThing_MoveToFrame);
    J3D_HOOKFUNC(sithCogFunctionThing_SkipToFrame);
    J3D_HOOKFUNC(sithCogFunctionThing_RotatePivot);
    J3D_HOOKFUNC(sithCogFunctionThing_Rotate);
    J3D_HOOKFUNC(sithCogFunctionThing_RotateToPYR);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingLight);
    J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamOffsetToThing);
    J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamLookOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_SetExtCamLookOffsetToThing);
    J3D_HOOKFUNC(sithCogFunctionThing_MakeCamera2LikeCamera1);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraPosition);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraLookInterp);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraPosInterp);
    J3D_HOOKFUNC(sithCogFunctionThing_GetCameraFOV);
    J3D_HOOKFUNC(sithCogFunctionThing_GetCameraPosition);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraInterpSpeed);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraFOV);
    J3D_HOOKFUNC(sithCogFunctionThing_ResetCameraFOV);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCameraFadeThing);
    J3D_HOOKFUNC(sithCogFunctionThing_ThingLight);
    J3D_HOOKFUNC(sithCogFunctionThing_ThingLightAnim);
    J3D_HOOKFUNC(sithCogFunctionThing_ThingFadeAnim);
    J3D_HOOKFUNC(sithCogFunctionThing_WaitForStop);
    J3D_HOOKFUNC(sithCogFunctionThing_WaitForAnimStop);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingSector);
    J3D_HOOKFUNC(sithCogFunctionThing_GetCurFrame);
    J3D_HOOKFUNC(sithCogFunctionThing_GetGoalFrame);
    J3D_HOOKFUNC(sithCogFunctionThing_StopThing);
    J3D_HOOKFUNC(sithCogFunctionThing_IsThingMoving);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingPulse);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingTimer);
    J3D_HOOKFUNC(sithCogFunctionThing_CaptureThing);
    J3D_HOOKFUNC(sithCogFunctionThing_ReleaseThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingParent);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingPos);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingPos);
    J3D_HOOKFUNC(sithCogFunctionThing_GetInventory);
    J3D_HOOKFUNC(sithCogFunctionThing_SetInventory);
    J3D_HOOKFUNC(sithCogFunctionThing_ChangeInventory);
    J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryCog);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingVelocity);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingVel);
    J3D_HOOKFUNC(sithCogFunctionThing_ApplyForce);
    J3D_HOOKFUNC(sithCogFunctionThing_AddThingVel);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingLVec);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingUVec);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingRVec);
    J3D_HOOKFUNC(sithCogFunctionThing_GetActorHeadPYR);
    J3D_HOOKFUNC(sithCogFunctionThing_DetachThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingAttachFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToSurf);
    J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThing);
    J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThingEx);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingAttachedThing);
    J3D_HOOKFUNC(sithCogFunctionThing_WaitMode);
    J3D_HOOKFUNC(sithCogFunctionThing_PlayMode);
    J3D_HOOKFUNC(sithCogFunctionThing_StopMode);
    J3D_HOOKFUNC(sithCogFunctionThing_SynchMode);
    J3D_HOOKFUNC(sithCogFunctionThing_IsModePlaying);
    J3D_HOOKFUNC(sithCogFunctionThing_PauseMode);
    J3D_HOOKFUNC(sithCogFunctionThing_ResumeMode);
    J3D_HOOKFUNC(sithCogFunctionThing_TrackToMode);
    J3D_HOOKFUNC(sithCogFunctionThing_PlayKey);
    J3D_HOOKFUNC(sithCogFunctionThing_PlayKeyEx);
    J3D_HOOKFUNC(sithCogFunctionThing_PauseKey);
    J3D_HOOKFUNC(sithCogFunctionThing_ResumeKey);
    J3D_HOOKFUNC(sithCogFunctionThing_StopKey);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMesh);
    J3D_HOOKFUNC(sithCogFunctionThing_RestoreThingMesh);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingModel);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingModel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetArmedMode);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_ClearThingFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_TeleportThing);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingType);
    J3D_HOOKFUNC(sithCogFunctionThing_GetCollideType);
    J3D_HOOKFUNC(sithCogFunctionThing_SetCollideType);
    J3D_HOOKFUNC(sithCogFunctionThing_FirstThingInSector);
    J3D_HOOKFUNC(sithCogFunctionThing_NextThingInSector);
    J3D_HOOKFUNC(sithCogFunctionThing_PrevThingInSector);
    J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryMinimum);
    J3D_HOOKFUNC(sithCogFunctionThing_GetInventoryMaximum);
    J3D_HOOKFUNC(sithCogFunctionThing_PathMovePause);
    J3D_HOOKFUNC(sithCogFunctionThing_SetHeadLightIntensity);
    J3D_HOOKFUNC(sithCogFunctionThing_GetHeadLightIntensity);
    J3D_HOOKFUNC(sithCogFunctionThing_IsThingVisible);
    J3D_HOOKFUNC(sithCogFunctionThing_PathMoveResume);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingCurLightMode);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingCurLightMode);
    J3D_HOOKFUNC(sithCogFunctionThing_SetActorExtraSpeed);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingTemplate);
    J3D_HOOKFUNC(sithCogFunctionThing_SetLifeleft);
    J3D_HOOKFUNC(sithCogFunctionThing_GetLifeleft);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingThrust);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingThrust);
    J3D_HOOKFUNC(sithCogFunctionThing_AmputateJoint);
    J3D_HOOKFUNC(sithCogFunctionThing_SetActorWeapon);
    J3D_HOOKFUNC(sithCogFunctionThing_GetActorWeapon);
    J3D_HOOKFUNC(sithCogFunctionThing_GetPhysicsFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_SetPhysicsFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_ClearPhysicsFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_ParseArg);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingRotVel);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingRotVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetRotThrust);
    J3D_HOOKFUNC(sithCogFunctionThing_GetRotThrust);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingLook);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLook);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLookPos);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingHeadLookThing);
    J3D_HOOKFUNC(sithCogFunctionThing_IsThingCrouching);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingClassCog);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingClassCog);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingCaptureCog);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingCaptureCog);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingRespawn);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingSignature);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingAttachFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_ClearThingAttachFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_GetParticleSize);
    J3D_HOOKFUNC(sithCogFunctionThing_SetParticleSize);
    J3D_HOOKFUNC(sithCogFunctionThing_GetParticleGrowthSpeed);
    J3D_HOOKFUNC(sithCogFunctionThing_SetParticleGrowthSpeed);
    J3D_HOOKFUNC(sithCogFunctionThing_GetParticleTimeoutRate);
    J3D_HOOKFUNC(sithCogFunctionThing_SetParticleTimeoutRate);
    J3D_HOOKFUNC(sithCogFunctionThing_GetTypeFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_SetTypeFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_ClearTypeFlags);
    J3D_HOOKFUNC(sithCogFunctionThing_TakeItem);
    J3D_HOOKFUNC(sithCogFunctionThing_HasLOS);
    J3D_HOOKFUNC(sithCogFunctionThing_GetFireOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_SetFireOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingUserData);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingUserData);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingCollideSize);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingCollideSize);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMoveSize);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMoveSize);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMass);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMass);
    J3D_HOOKFUNC(sithCogFunctionThing_SyncThingPos);
    J3D_HOOKFUNC(sithCogFunctionThing_SyncThingAttachment);
    J3D_HOOKFUNC(sithCogFunctionThing_SyncThingState);
    J3D_HOOKFUNC(sithCogFunctionThing_GetMajorMode);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingPosEx);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingGuid);
    J3D_HOOKFUNC(sithCogFunctionThing_GetGuidThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxVel);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxAngVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxAngVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetJointAngle);
    J3D_HOOKFUNC(sithCogFunctionThing_GetJointAngle);
    J3D_HOOKFUNC(sithCogFunctionThing_SetMaxHeadPitch);
    J3D_HOOKFUNC(sithCogFunctionThing_SetMinHeadPitch);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadPitch);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMinHeadPitch);
    J3D_HOOKFUNC(sithCogFunctionThing_SetMaxHeadYaw);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadYaw);
    J3D_HOOKFUNC(sithCogFunctionThing_InterpolatePYR);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingLVecPYR);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingLVec);
    J3D_HOOKFUNC(sithCogFunctionThing_SetHeadPYR);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingAirDrag);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingJointPos);
    J3D_HOOKFUNC(sithCogFunctionThing_IsThingModelName);
    J3D_HOOKFUNC(sithCogFunctionThing_GetMeshByName);
    J3D_HOOKFUNC(sithCogFunctionThing_GetNodeByName);
    J3D_HOOKFUNC(sithCogFunctionThing_AttachThingToThingMesh);
    J3D_HOOKFUNC(sithCogFunctionThing_DetachThingMesh);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxRotVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxRotVel);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingMaxHeadVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingMaxHeadVel);
    J3D_HOOKFUNC(sithCogFunctionThing_SetPuppetModeFPS);
    J3D_HOOKFUNC(sithCogFunctionThing_ResetThing);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingInsertOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingInsertOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_GetThingEyeOffset);
    J3D_HOOKFUNC(sithCogFunctionThing_CheckFloorDistance);
    J3D_HOOKFUNC(sithCogFunctionThing_CheckPathToPoint);
    J3D_HOOKFUNC(sithCogFunctionThing_MoveThing);
    J3D_HOOKFUNC(sithCogFunctionThing_MoveThingToPos);
    J3D_HOOKFUNC(sithCogFunctionThing_SetThingStateChange);
    J3D_HOOKFUNC(sithCogFunctionThing_StartQuetzAnim);
    J3D_HOOKFUNC(sithCogFunctionThing_BoardVehicle);
    J3D_HOOKFUNC(sithCogFunctionThing_FadeInTrack);
    J3D_HOOKFUNC(sithCogFunctionThing_MakeFairyDust);
    J3D_HOOKFUNC(sithCogFunctionThing_MakeFairyDustDeluxe);
}

void sithCogFunctionThing_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionThing_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return sithCog_RegisterFunction(pTable, sithCogFunctionThing_WaitForStop, "waitforstop")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_WaitForAnimStop, "waitforanimstop")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_StopThing, "stopthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_DestroyThing, "destroything")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetHealth, "getthinghealth")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetMaxHealth, "getthingmaxhealth")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetHealth, "gethealth")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_HealThing, "healthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingLight, "getthinglight")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ThingLight, "setthinglight")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ThingLight, "thinglight")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ThingLightAnim, "thinglightanim")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ThingFadeAnim, "thingfadeanim")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CreateThing, "creatething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CreateThingAtPos, "createthingatpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CaptureThing, "capturething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ReleaseThing, "releasething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingVel, "setthingvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AddThingVel, "addthingvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ApplyForce, "applyforce")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_DetachThing, "detachthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingAttachFlags, "getattachflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingAttachFlags, "getthingattachflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AttachThingToSurf, "attachthingtosurf")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AttachThingToThing, "attachthingtothing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetArmedMode, "setarmedmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingFlags, "setthingflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearThingFlags, "clearthingflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_TeleportThing, "teleportthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingType, "setthingtype")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCollideType, "setcollidetype")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetHeadLightIntensity, "setheadlightintensity")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingCurLightMode, "getthingcurlightmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingCurLightMode, "setthingcurlightmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetActorExtraSpeed, "setactorextraspeed")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingPosEx, "setthingposex")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMaxVel, "setthingmaxvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMaxAngVel, "setthingmaxangvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetJointAngle, "setthingjointangle")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetMaxHeadPitch, "setthingmaxheadpitch")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetMinHeadPitch, "setthingminheadpitch")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxHeadPitch, "getthingmaxheadpitch")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMinHeadPitch, "getthingminheadpitch")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetMaxHeadYaw, "setthingmaxheadyaw")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxHeadYaw, "getthingmaxheadyaw")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingLVec, "setthinglvecpyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetHeadPYR, "setactorheadpyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingAirDrag, "setthingairdrag")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMaxRotVel, "setthingmaxrotvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMaxHeadVel, "setthingmaxheadvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ResetThing, "resetthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MoveThing, "movething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MoveThingToPos, "movethingtopos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingType, "getthingtype")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingMoving, "isthingmoving")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingMoving, "ismoving")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetCurFrame, "getcurframe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetGoalFrame, "getgoalframe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingParent, "getthingparent")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingSector, "getthingsector")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingPos, "getthingpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingPos, "setthingpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingVelocity, "getthingvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingUVec, "getthinguvec")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingLVec, "getthinglvec")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingRVec, "getthingrvec")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingFlags, "getthingflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetCollideType, "getcollidetype")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetHeadLightIntensity, "getheadlightintensity")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingVisible, "isthingvisible")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingGuid, "getthingguid")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetGuidThing, "getguidthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxVel, "getthingmaxvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxAngVel, "getthingmaxangvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetJointAngle, "getthingjointangle")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_InterpolatePYR, "interpolatepyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingLVecPYR, "getthinglvecpyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetActorHeadPYR, "getactorheadpyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingJointPos, "getthingjointpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingModelName, "isthingmodelname")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxRotVel, "getthingmaxrotvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMaxHeadVel, "getthingmaxheadvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CopyOrient, "copyorient")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CopyOrientAndPos, "copyorientandpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingInsertOffset, "getthinginsertoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingInsertOffset, "setthinginsertoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingEyeOffset, "getthingeyeoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingPulse, "setthingpulse")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingTimer, "setthingtimer")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetInventory, "getinv")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetInventory, "setinv")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ChangeInventory, "changeinv")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetInventoryCog, "getinvcog")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetInventoryMinimum, "getinvmin")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetInventoryMaximum, "getinvmax")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PlayKey, "playkey")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PlayKeyEx, "playkeyex")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_StopKey, "stopkey")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PauseKey, "pausekey")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ResumeKey, "resumekey")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingModel, "setthingmodel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingModel, "getthingmodel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PlayMode, "playmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_StopMode, "stopmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SynchMode, "synchmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsModePlaying, "ismodeplaying")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PauseMode, "pausemode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ResumeMode, "resumemode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_TrackToMode, "tracktomode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_WaitMode, "waitmode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetMajorMode, "getmajormode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_FirstThingInSector, "firstthinginsector")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_NextThingInSector, "nextthinginsector")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PrevThingInSector, "prevthinginsector")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MoveToFrame, "movetoframe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SkipToFrame, "skiptoframe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_JumpToFrame, "jumptoframe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PathMovePause, "pathmovepause")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PathMoveResume, "pathmoveresume")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_Rotate, "rotate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_RotatePivot, "rotatepivot")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_RotateToPYR, "rotatetopyr")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingTemplate, "getthingtemplate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_DamageThing, "damagething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetLifeleft, "setlifeleft")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetLifeleft, "getlifeleft")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingThrust, "setthingthrust")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingThrust, "getthingthrust")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetHealth, "setthinghealth")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetHealth, "sethealth")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AmputateJoint, "amputatejoint")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetActorWeapon, "setactorweapon")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetActorWeapon, "getactorweapon")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetPhysicsFlags, "getphysicsflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetPhysicsFlags, "setphysicsflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearPhysicsFlags, "clearphysicsflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ParseArg, "parsearg")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingRotVel, "getthingrotvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingRotVel, "setthingrotvel")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetRotThrust, "getthingrotthrust")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetRotThrust, "setthingrotthrust")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingLook, "setthinglook")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingHeadLookPos, "setthingheadlookpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingHeadLookThing, "setthingheadlookthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingCrouching, "isthingcrouching")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsThingCrouching, "iscrouching")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingClassCog, "getthingclasscog")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingClassCog, "setthingclasscog")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingCaptureCog, "getthingcapturecog")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingCaptureCog, "setthingcapturecog")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingRespawn, "getthingrespawn")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingSignature, "getthingsignature")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingAttachFlags, "setthingattachflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearThingAttachFlags, "clearthingattachflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetParticleSize, "getparticlesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetParticleSize, "setparticlesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetParticleGrowthSpeed, "getparticlegrowthspeed")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetParticleGrowthSpeed, "setparticlegrowthspeed")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetParticleTimeoutRate, "getparticletimeoutrate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetParticleTimeoutRate, "setparticletimeoutrate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "gettypeflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "settypeflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "cleartypeflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "getactorflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "setactorflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "clearactorflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "getweaponflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "setweaponflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "clearweaponflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "getexplosionflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "setexplosionflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "clearexplosionflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "getitemflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "setitemflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "clearitemflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetTypeFlags, "getparticleflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetTypeFlags, "setparticleflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ClearTypeFlags, "clearparticleflags")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_TakeItem, "takeitem")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_HasLOS, "haslos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetFireOffset, "getthingfireoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetFireOffset, "setthingfireoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingUserData, "getthinguserdata")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingUserData, "setthinguserdata")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingCollideSize, "getthingcollidesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingCollideSize, "setthingcollidesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMoveSize, "getthingmovesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMoveSize, "setthingmovesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingMass, "getthingmass")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMass, "setthingmass")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SyncThingPos, "syncthingpos")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SyncThingAttachment, "syncthingattachment")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SyncThingState, "syncthingstate")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AttachThingToThingEx, "attachthingtothingex")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingAttachedThing, "getthingattachedthing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetMeshByName, "getmeshbyname")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetNodeByName, "getnodebyname")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AttachThingToThingMesh, "attachthingtothingmesh")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_DetachThingMesh, "detachthingmesh")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingMesh, "setthingmesh")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_RestoreThingMesh, "restorethingmesh")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetThingAlpha, "getthingalpha")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingAlpha, "setthingalpha")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetCameraFOV, "getcamerafov")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraFOV, "setcamerafov")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_ResetCameraFOV, "resetcamerafov")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraLookInterp, "setcameralookinterp")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraPosInterp, "setcameraposinterp")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraInterpSpeed, "setcamerainterpspeed")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraPosition, "setcameraposition")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_AnimateSpriteSize, "animatespritesize")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetCameraPosition, "getcameraposition")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetCameraFadeThing, "setcamerafadething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetExtCamOffset, "setextcamoffset")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetExtCamOffsetToThing, "setextcamoffsettothing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetExtCamLookOffsetToThing, "setextcamlookoffsettothing")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetExtCamLookOffset, "setextcamlookoffset")
        || sithCog_RegisterFunction(pTable, sithCamera_RestoreExtCamera, "restoreextcam") // RestoreExtCam didn't exist, debug exe calls this function instead
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_PlayForceMoveMode, "playforcemovemode")
     // || sithCog_RegisterFunction(pTable, (SithCogFunctionType)stdPlatform_UnlockHandle, "isthingautoaiming") // TODO: ??
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_GetMoveStatus, "getmovestatus")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CreateLaser, "createlaser")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CreateLightning, "createlightning")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MakeFairyDust, "makefairydust")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MakeFairyDustDeluxe, "makefairydustdeluxe")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetPuppetModeFPS, "setpuppetmodefps")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetMoveMode, "setmovemode")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CheckFloorDistance, "checkfloordistance")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CheckPathToPoint, "checkpathtopoint")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_SetThingStateChange, "setthingstatechange")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_CreatePolylineThing, "createpolylinething")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_StartQuetzAnim, "startquetzanim")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_BoardVehicle, "boardvehicle")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_FadeInTrack, "fadeintrack")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_IsGhostVisible, "isghostvisible")
        || sithCog_RegisterFunction(pTable, sithCogFunctionThing_MakeCamera2LikeCamera1, "makecamera2likecamera1");
}

void J3DAPI sithCogFunctionThing_IsGhostVisible(SithCog* pCog)
{
    float angle            = sithCogExec_PopFlex(pCog);
    SithThing* pGhostThing = sithCogExec_PopThing(pCog);
    SithThing* pThing      = sithCogExec_PopThing(pCog);
    if ( !pGhostThing || !pThing )
    {
        STDLOG_ERROR("Cog %s: Invalid thing ref in IsGhostVisible()!\n", pCog->aName);
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( angle < 1.0 || angle > 90.0 )
    {
        STDLOG_ERROR("Cog %s: Invalid range angle in IsGhostVisible()!\n", pCog->aName);
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    float retSin, retCos;
    stdMath_SinCos(angle, &retSin, &retCos);

    rdVector3 dir;
    rdVector_Sub3(&dir, &pGhostThing->pos, &pThing->pos);
    rdVector_Normalize3Acc(&dir);

    if ( rdVector_Dot3(&pThing->orient.lvec, &dir) < retCos )
    {
        sithCogExec_PushInt(pCog, 0);
    }
    else
    {
        sithCogExec_PushInt(pCog, 1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingAlpha(SithCog* pCog)
{
    SithThing* pThing;
    rdVector4* pLightColor;
    float green;
    float blue;
    float alpha;

    alpha = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( alpha < 0.0 )
        {
            alpha = 0.0;
        }

        else if ( alpha > 1.0 )
        {
            alpha = 1.0;
        }

        if ( pThing->type == SITH_THING_POLYLINE )
        {
            pLightColor = &pThing->renderData.data.pPolyline->face.extraLight;
            green = pThing->renderData.data.pPolyline->face.extraLight.green;
            blue = pThing->renderData.data.pPolyline->face.extraLight.blue;
            pLightColor->red = pLightColor->red;
            pLightColor->green = green;
            pLightColor->blue = blue;
            pLightColor->alpha = alpha;
        }

        pThing->alpha = alpha;
        sithCogExec_PushFlex(pCog, alpha);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing ref in SetThingAlpha()!\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_GetThingAlpha(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Invalid thing ref in SetThingAlpha()!\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }

    sithCogExec_PushFlex(pCog, pThing->alpha);
}

void J3DAPI sithCogFunctionThing_CreatePolylineThing(SithCog* pCog)
{
    int bValidVec;
    SithThing* pDestThing;
    SithThing* pSrcThing;
    SithThing* pPolyline;
    float tipRadius;
    float baseRadius;
    rdMaterial* pMaterial;
    rdVector3 endPos;
    float duration;

    duration = sithCogExec_PopFlex(pCog);
    tipRadius = sithCogExec_PopFlex(pCog);
    baseRadius = sithCogExec_PopFlex(pCog);
    pMaterial = sithCogExec_PopMaterial(pCog);
    bValidVec = sithCogExec_PopVector(pCog, &endPos);
    pDestThing = sithCogExec_TryPopThing(pCog);
    pSrcThing = sithCogExec_PopThing(pCog);

    if ( bValidVec )
    {
        if ( pSrcThing )
        {
            pPolyline = sithFX_CreatePolylineThing(
                pSrcThing,
                pDestThing,
                &endPos,
                pMaterial,
                baseRadius,
                tipRadius,
                duration);
            if ( pPolyline )
            {
                sithCogExec_PushInt(pCog, pPolyline->idx);
                return;
            }

            STDLOG_ERROR("Cog %s: Unable to create poly line from thing %s to thing %s CreatePolyLineThing!\n",
                pCog->aName,
                pSrcThing->aName,
                pDestThing->aName);             // BUG: pDestThing could be null
        }
        else
        {
            STDLOG_ERROR("Cog %s: Invalid source thing in CreatePolyLineThing!\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid vector in CreatePolyLineThing!\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_GetMoveStatus(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->moveStatus);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing ref if GetMoveStatus()!\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_CopyOrient(SithCog* pCog)
{
    SithThing* pDestThing;
    SithThing* pSrcThing;

    pDestThing = sithCogExec_PopThing(pCog);
    if ( pDestThing )
    {
        pSrcThing = sithCogExec_PopThing(pCog);
        if ( pSrcThing )
        {
            memcpy(&pDestThing->orient, &pSrcThing->orient, sizeof(pDestThing->orient));
        }
        else
        {
            STDLOG_ERROR("Cog %s: Invalid source thing in CopyOrient!\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid destination thing in CopyOrient!\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_CopyOrientAndPos(SithCog* pCog)
{
    SithThing* pDstThing;
    SithThing* pSrcThing;

    pDstThing = sithCogExec_PopThing(pCog);
    pSrcThing = sithCogExec_PopThing(pCog);
    if ( pDstThing )
    {
        if ( pSrcThing )
        {
            if ( pSrcThing->pInSector )
            {
                memcpy(&pDstThing->orient, &pSrcThing->orient, 0x3Cu);// TODO: memcopy position seperately, 0x3C = sizeof(matrix) + sizeof(rdVector3)

                sithThing_ExitSector(pDstThing);
                sithThing_EnterSector(pDstThing, pSrcThing->pInSector, 1, 1);
            }
            else
            {
                STDLOG_ERROR("Cog %s: Source thing %s isn't in any sector in CopyOrient!\n",
                    pCog->aName,
                    pSrcThing->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Invalid source thing in CopyOrientAndPos!\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid destination thing in CopyOrientAndPos!\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_CreateLaser(SithCog* pCog)
{
    int bError;
    SithThing* pSrcThing;
    SithThing* pLaser;
    float tipRadius;
    float baseRadius;
    rdVector3 endPos;
    rdVector3 offset;
    float duration;

    bError = 0;
    duration = sithCogExec_PopFlex(pCog);
    tipRadius = sithCogExec_PopFlex(pCog);
    baseRadius = sithCogExec_PopFlex(pCog);
    if ( !sithCogExec_PopVector(pCog, &endPos) )
    {
        STDLOG_ERROR("Cog %s: Invalid end pos vector in CreateLaser!\n",
            pCog->aName);
    }

    if ( !sithCogExec_PopVector(pCog, &offset) )
    {
        STDLOG_ERROR("Cog %s: Invalid offset vector in CreateLaser!\n",
            pCog->aName);
        bError = 1;
    }

    pSrcThing = sithCogExec_PopThing(pCog);
    if ( !pSrcThing )
    {
        STDLOG_ERROR("Cog %s: Invalid source thing in CreateLaser!\n",
            pCog->aName);
        bError = 1;
    }

    if ( bError != 1 )
    {
        pLaser = sithFX_CreateLaserThing(pSrcThing, &offset, &endPos, baseRadius, tipRadius, duration);
        if ( pLaser )
        {
            sithCogExec_PushInt(pCog, pLaser->idx);
            return;
        }

        STDLOG_ERROR("Cog %s: Unable to create laser from thing %s in CreateLaser!\n",
            pCog->aName,
            pSrcThing->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_CreateLightning(SithCog* pCog)
{
    int bError;
    SithThing* pSourceThing;
    SithThing* pLightning;
    float tipRadius;
    float baseRadius;
    rdVector3 endPos;
    rdVector3 offset;
    float duration;

    bError = 0;
    duration = sithCogExec_PopFlex(pCog);
    tipRadius = sithCogExec_PopFlex(pCog);
    baseRadius = sithCogExec_PopFlex(pCog);
    if ( !sithCogExec_PopVector(pCog, &endPos) )
    {
        STDLOG_ERROR("Cog %s: Invalid end pos vector in CreateLightning!\n",
            pCog->aName);
        bError = 1;
    }

    if ( !sithCogExec_PopVector(pCog, &offset) )
    {
        STDLOG_ERROR("Cog %s: Invalid offset vector in CreateLightning!\n",
            pCog->aName);
        bError = 1;
    }

    pSourceThing = sithCogExec_PopThing(pCog);
    if ( !pSourceThing )
    {
        STDLOG_ERROR("Cog %s: Invalid source thing in CreateLightning!\n",
            pCog->aName);
        bError = 1;
    }

    if ( bError != 1 )
    {
        pLightning = sithFX_CreateLightningThing(pSourceThing, &offset, &endPos, baseRadius, tipRadius, duration);
        if ( pLightning )
        {
            sithCogExec_PushInt(pCog, pLightning->idx);
            return;
        }

        STDLOG_ERROR("Cog %s: Unable to create lightning from thing %s in CreateLightning!\n",
            pCog->aName,
            pSourceThing->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_AnimateSpriteSize(SithCog* pCog)
{
    int bVecEnd;
    int bVecStart;
    SithThing* pSprite;
    SithAnimationSlot* pAnim;
    rdVector3 vecEnd;
    rdVector3 vecStart;
    float deltaTime;

    deltaTime = sithCogExec_PopFlex(pCog);
    bVecEnd = sithCogExec_PopVector(pCog, &vecEnd);
    bVecStart = sithCogExec_PopVector(pCog, &vecStart);
    pSprite = sithCogExec_PopThing(pCog);
    if ( !bVecStart )
    {
        STDLOG_ERROR("Cog %s: Invalid start vector in AnimateSpriteSize!\n",
            pCog->aName);

    error_exit:
        STDLOG_ERROR("Cog %s: Unable to create animation for AnimateSpriteSize().\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( !bVecEnd )
    {
        STDLOG_ERROR("Cog %s: Invalid end vector in AnimateSpriteSize!\n",
            pCog->aName);
        goto error_exit;
    }

    if ( !pSprite )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in AnimateSpriteSize!\n",
            pCog->aName);
        goto error_exit;
    }

    pAnim = sithAnimate_StartSpriteSizeAnim(pSprite, &vecStart, &vecEnd, deltaTime);
    if ( !pAnim )
    {
        goto error_exit;
    }

    sithCogExec_PushInt(pCog, pAnim->animID);
}

void J3DAPI sithCogFunctionThing_GetThingType(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->type);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PlayForceMoveMode(SithCog* pCog)
{
    int bPlaying;
    SithThing* pThing;
    rdVector3* pThingPos;
    rdVector3* pForceMoveStartPos;
    SithPuppetSubMode origmode;
    float z;
    float origZPos;
    int trackNum;
    SithPuppetSubMode submode;

    bPlaying = 0;
    submode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThingPos = &pThing->pos;
        pForceMoveStartPos = &pThing->forceMoveStartPos;
        pThing->forceMoveStartPos.x = pThing->pos.x;
        pThing->forceMoveStartPos.y = pThing->pos.y;
        pThing->forceMoveStartPos.z = pThing->pos.z;
        origmode = submode;
        if ( submode - 5 > (unsigned int)SITHPUPPETSUBMODE_MOUNTFROMWATER )
        {
        push_error_code:
            sithCogExec_PushInt(pCog, -1);
        }
        else
        {
            switch ( submode )
            {
                case SITHPUPPETSUBMODE_HOPBACK:
                    sithPlayerActions_HopBack(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_HOPLEFT:
                    sithPlayerActions_JumpLeft(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_HOPRIGHT:
                    sithPlayerActions_JumpRight(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_STRAFELEFT:
                case SITHPUPPETSUBMODE_STRAFERIGHT:
                case SITHPUPPETSUBMODE_TURNLEFT:
                case SITHPUPPETSUBMODE_TURNRIGHT:
                case SITHPUPPETSUBMODE_SLIDEDOWNFWD:
                case SITHPUPPETSUBMODE_SLIDEDOWNBACK:
                case SITHPUPPETSUBMODE_JUMPREADY:
                case SITHPUPPETSUBMODE_RISING:
                case SITHPUPPETSUBMODE_FALL:
                case SITHPUPPETSUBMODE_DEATH:
                case SITHPUPPETSUBMODE_DEATH2:
                case SITHPUPPETSUBMODE_FIDGET:
                case SITHPUPPETSUBMODE_FIDGET2:
                case SITHPUPPETSUBMODE_PICKUP:
                case SITHPUPPETSUBMODE_MOUNTLEDGE:
                case SITHPUPPETSUBMODE_GRABLEDGE:
                case SITHPUPPETSUBMODE_HANGLEDGE:
                case SITHPUPPETSUBMODE_MOUNTWALL:
                case SITHPUPPETSUBMODE_CLIMBWALLIDLE:
                case SITHPUPPETSUBMODE_WHIPCLIMBMOUNT:
                case SITHPUPPETSUBMODE_WHIPCLIMBIDLE:
                case SITHPUPPETSUBMODE_WHIPCLIMBUP:
                case SITHPUPPETSUBMODE_WHIPCLIMBDOWN:
                case SITHPUPPETSUBMODE_WHIPCLIMBLEFT:
                case SITHPUPPETSUBMODE_WHIPCLIMBRIGHT:
                case SITHPUPPETSUBMODE_WHIPCLIMBDISMOUNT:
                case SITHPUPPETSUBMODE_WHIPSWINGMOUNT:
                    goto push_error_code;

                case SITHPUPPETSUBMODE_LEAP:
                    pForceMoveStartPos->x = pThingPos->x;
                    z = pThing->pos.z;
                    pThing->forceMoveStartPos.y = pThing->pos.y;
                    pThing->moveStatus = SITHPLAYERMOVE_JUMPFWD;
                    pThing->forceMoveStartPos.z = z;
                    sithThing_DetachThing(pThing);
                    submode = sithPuppet_PlayForceMoveMode(pThing, SITHPUPPETSUBMODE_LEAP, 0);// TODO: set new var for submode to tracknum
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_JUMPUP:
                    sithPlayerActions_Jump(pThing, 0.60000002, 0);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_JUMPFWD:
                    sithPlayerActions_Jump(pThing, 0.76999998, 1);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_PUSHPULLREADY:
                case SITHPUPPETSUBMODE_WHIPSWING:
                    if ( pThing->type == SITH_THING_PLAYER )
                    {
                        goto push_error_code;
                    }

                    pForceMoveStartPos->x = pThingPos->x;
                    origZPos = pThing->pos.z;
                    pThing->forceMoveStartPos.y = pThing->pos.y;
                    pThing->forceMoveStartPos.z = origZPos;
                    break;

                case SITHPUPPETSUBMODE_PUSHITEM:
                    pThing->moveStatus = SITHPLAYERMOVE_PUSHING;
                    break;

                case SITHPUPPETSUBMODE_PULLITEM:
                    pThing->moveStatus = SITHPLAYERMOVE_PULLING;
                    break;

                case SITHPUPPETSUBMODE_HANGSHIMLEFT:
                case SITHPUPPETSUBMODE_HANGSHIMRIGHT:
                    pThing->moveStatus = SITHPLAYERMOVE_HANGING;
                    break;

                case SITHPUPPETSUBMODE_CLIMBWALLUP:
                case SITHPUPPETSUBMODE_CLIMBWALLDOWN:
                case SITHPUPPETSUBMODE_CLIMBWALLLEFT:
                case SITHPUPPETSUBMODE_CLIMBWALLRIGHT:
                    pThing->moveStatus = SITHPLAYERMOVE_CLIMBIDLE;
                    break;

                case SITHPUPPETSUBMODE_CLIMBPULLINGUP:
                case SITHPUPPETSUBMODE_MOUNTFROMWATER:
                    pThing->moveStatus = SITHPLAYERMOVE_PULLINGUP;
                    break;

                case SITHPUPPETSUBMODE_DIVEFROMSURFACE:
                    pThing->moveStatus = SITHPLAYERMOVE_SWIMIDLE;
                    break;

                case SITHPUPPETSUBMODE_MOUNT1MSTEP:
                    sithPlayerActions_ClimbOn1m(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_MOUNT2MLEDGE:
                    sithPlayerActions_ClimbOn2m(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_JUMPROLLBACK:
                    sithPlayerActions_JumpRollBack(pThing);
                    bPlaying = 1;
                    break;

                case SITHPUPPETSUBMODE_JUMPROLLFWD:
                    sithPlayerActions_JumpRollForward(pThing);
                    bPlaying = 1;
                    break;
            }

            if ( bPlaying )
            {
                sithCogExec_PushInt(pCog, submode);
            }
            else
            {
                trackNum = sithPuppet_PlayForceMoveMode(pThing, origmode, 0);
                sithCogExec_PushInt(pCog, trackNum);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Bad thing in PlayForceMoveMode()\n", pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetMoveMode(SithCog* pCog)
{
    int newMode;
    SithThing* pThing;

    newMode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( (unsigned int)newMode <= 107 )     // ?? shouldnt be less than SITH_PUPPET_NUMMOVEMODES which is 3 => newMode > -1 && newMode <  SITH_PUPPET_NUMMOVEMODES
        {
            sithPuppet_SetMoveMode(pThing, (SithPuppetMoveMode)newMode);
            sithCogExec_PushInt(pCog, 0);
            return;
        }

        STDLOG_ERROR("Bad move mode for thing %s in SetMoveMode()\n",
            pThing->aName);
    }
    else
    {
        STDLOG_ERROR("Bad thing in SetMoveMode()\n");
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_CreateThing(SithCog* pCog)
{
    SithThing* pRefThing;
    SithThing* pTemplate;
    SithThing* pNewThing;
    SithCogMsgType execMsgType;
    int idx;

    pRefThing = sithCogExec_PopThing(pCog);
    pTemplate = sithCogExec_PopTemplate(pCog);
    if ( !pRefThing )
    {
        STDLOG_ERROR("Cog %s: Bad thing reference in CreateThing.\n",
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( pRefThing->type == SITH_THING_FREE )
    {
        STDLOG_ERROR("Cog %s: Thing %s has been deleted from the world in CreateThing.\n",
            pCog->aName,
            pRefThing->aName);
        goto error_return;
    }

    if ( !pRefThing->pInSector )
    {
        STDLOG_ERROR("Cog %s: Thing %s is not in any sector in CreateThing.\n",
            pCog->aName,
            pRefThing->aName);
        goto error_return;
    }

    if ( !pTemplate )
    {
        STDLOG_ERROR("Cog %s: Bad template reference in CreateThing.\n",
            pCog->aName);
        goto error_return;
    }

    pNewThing = sithThing_CreateThing(pTemplate, pRefThing);
    if ( !pNewThing )
    {
        STDLOG_ERROR("Cog %s: CreateThing failed.\n",
            pCog->aName);
        goto error_return;
    }

    if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
    {
        execMsgType = pCog->execMsgType;
        if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
        {
            sithDSSThing_CreateThing(pTemplate, pNewThing, pRefThing, 0, 0, 0, 0xFFu, DPSEND_GUARANTEED);// make encrypted
        }
    }

    idx = pNewThing->idx;
    pNewThing->moveStatus = SITHPLAYERMOVE_STILL;
    sithCogExec_PushInt(pCog, idx);
}

void J3DAPI sithCogFunctionThing_CreateThingAtPos(SithCog* pCog)
{
    int bPyrVec;
    int bPosVec;
    SithThing* pTemplate;
    int rdType;
    SithThing* pNewThing;
    SithCogMsgType execMsgType;
    rdVector3 offset;
    rdVector3 pos;
    rdVector3 pyr;
    rdMatrix34 orient;
    SithSector* pSector;

    bPyrVec = sithCogExec_PopVector(pCog, &pyr);
    bPosVec = sithCogExec_PopVector(pCog, &pos);
    pSector = sithCogExec_PopSector(pCog);
    pTemplate = sithCogExec_PopTemplate(pCog);
    if ( !bPyrVec || !bPosVec )
    {
        STDLOG_ERROR("Cog %s: Bad vector in CreateThingAtPos.\n",
            pCog->aName);
        goto error_return;
    }

    if ( !pTemplate )
    {
        STDLOG_ERROR("Cog %s: Bad template in CreateThingAtPos.\n",
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( !pSector )
    {
        STDLOG_ERROR("Cog %s: Bad sector in CreateThingAtPos.\n",
            pCog->aName);
        goto error_return;
    }

    rdType = pTemplate->renderData.type - 1;    // ??
    if ( rdType )
    {
        if ( rdType == RD_THING_LIGHT )
        {
            *(rdVector3*)&offset.x = *(rdVector3*)&pTemplate->renderData.data.pSprite3->offset.x;// TODO: memcpy
        }
        else
        {
            memset(&offset, 0, sizeof(offset));
        }
    }
    else
    {
        *(rdVector3*)&offset.x = *(rdVector3*)&pTemplate->renderData.data.pModel3->insertOffset.x;// TODO: memcpy
    }

    rdMatrix_BuildRotate34(&orient, &pyr);
    rdMatrix_TransformVector34Acc(&offset, &orient);
    pos.x = pos.x + offset.x;
    pos.y = pos.y + offset.y;
    pos.z = pos.z + offset.z;

    pNewThing = sithThing_CreateThingAtPos(pTemplate, &pos, &orient, pSector, 0);
    if ( !pNewThing )
    {
        STDLOG_ERROR("Cog %s: Unable to create thing in CreateThingAtPos.\n",
            pCog->aName);
        goto error_return;
    }

    if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
    {
        execMsgType = pCog->execMsgType;
        if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
        {
            sithDSSThing_CreateThing(pTemplate, pNewThing, 0, pSector, &pos, &pyr, 0xFFu, DPSEND_GUARANTEED);
        }
    }

    sithCogExec_PushInt(pCog, pNewThing->idx);
}

void J3DAPI sithCogFunctionThing_DamageThing(SithCog* pCog)
{
    SithThing* pPerpetrator;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    SithDamageType damageclass;
    float damage;
    float newDamage;

    pPerpetrator = sithCogExec_PopThing(pCog);
    damageclass = sithCogExec_PopInt(pCog);
    damage = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( damage > 0.0 && pThing )
    {
        if ( !pPerpetrator )
        {
            pPerpetrator = pThing;
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                if ( stdComm_IsGameHost() )
                {
                    sithDSSThing_DamageThing(pThing, pPerpetrator, damage, damageclass, SITHMESSAGE_SENDTOALL, 1u);
                }
            }
        }

        newDamage = sithThing_DamageThing(pThing, pPerpetrator, damage, damageclass);
        sithCogExec_PushFlex(pCog, newDamage);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_HealThing(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    float health;

    health = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( health > 0.0 )
    {
        if ( pThing )
        {
            type = pThing->type;
            if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
            {
                pThing->thingInfo.actorInfo.health = health + pThing->thingInfo.actorInfo.health;
                if ( pThing->thingInfo.actorInfo.health > pThing->thingInfo.actorInfo.maxHealth )
                {
                    pThing->thingInfo.actorInfo.health = pThing->thingInfo.actorInfo.maxHealth;
                }
            }
        }
    }
}

void J3DAPI sithCogFunctionThing_GetHealth(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.health);
            return;
        }

        STDLOG_ERROR("Cog %s: Thing %s is not an actor or player in GetHealth.\n",
            pCog->aName,
            pThing->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetHealth.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_GetMaxHealth(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHealth);
            return;
        }

        STDLOG_ERROR("Cog %s: Thing %s is not an actor or player in GetMaxHealth.\n",
            pCog->aName,
            pThing->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetMaxHealth.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_SetHealth(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    float health;

    health = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
        {
            pThing->thingInfo.actorInfo.health = health;
        }
    }
}

void J3DAPI sithCogFunctionThing_DestroyThing(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_DestroyThing(pThing->guid, SITHMESSAGE_SENDTOALL);
            }
        }

        sithThing_DestroyThing(pThing);
    }
}

void J3DAPI sithCogFunctionThing_JumpToFrame(SithCog* pCog)
{
    SithSector* pSector;
    unsigned int frame;
    SithThing* pThing;
    SithSector* pInSector;

    pSector = sithCogExec_PopSector(pCog);
    frame = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pSector && pThing->moveType == SITH_MT_PATH && frame < pThing->moveInfo.pathMovement.numFrames )
    {
        pInSector = pThing->pInSector;
        if ( pInSector && pSector != pInSector )
        {
            sithThing_ExitSector(pThing);
        }

        if ( pThing->attach.flags )
        {
            sithThing_DetachThing(pThing);
        }

        rdMatrix_BuildRotate34(&pThing->orient, &pThing->moveInfo.pathMovement.aFrames[frame].pyr);
        pThing->pos = *(rdVector3*)&pThing->moveInfo.pathMovement.aFrames[frame].pos.x;
        if ( !pThing->pInSector )
        {
            sithThing_EnterSector(pThing, pSector, 1, 0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal params in JumpToFrame.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_MoveToFrame(SithCog* pCog)
{
    unsigned int frame;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    float speed;

    speed = sithCogExec_PopFlex(pCog) * 0.1;
    frame = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PATH )
        {
            if ( pThing->moveInfo.pathMovement.numFrames > frame )
            {
                if ( speed == 0.0 )
                {
                    STDLOG_ERROR("Cog %s: Bad movement speed set for movetoframe.  Set=0.5\n",
                        pCog->aName);

                    speed = 0.5;
                }

                sithPathMove_MoveToFrame(pThing, frame, speed);

                if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
                {
                    execMsgType = pCog->execMsgType;
                    if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                    {
                        sithDSSThing_PathMove(pThing, frame, speed, 0, SITHMESSAGE_SENDTOALL, 0xFFu);
                    }
                }
            }
            else
            {
                STDLOG_ERROR("Cog %s: Thing %s, moveFrame (%d) > path's frames (%d)\n",
                    pCog->aName,
                    pThing->aName,
                    frame,
                    pThing->moveInfo.pathMovement.numFrames);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s is not a path move thing in MoveToFrame\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Thing pointer is NULL in MoveToFrame\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SkipToFrame(SithCog* pCog)
{
    unsigned int frame;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    float speed;

    speed = sithCogExec_PopFlex(pCog) * 0.1;
    frame = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PATH && pThing->moveInfo.pathMovement.numFrames > frame )
    {
        if ( speed == 0.0 )
        {
            STDLOG_ERROR("Cog %s: Bad movement speed set for movetoframe.  Set=0.5\n",
                pCog->aName);

            speed = 0.5;
        }

        sithPathMove_SkipToFrame(pThing, frame, speed);

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_PathMove(pThing, frame, speed, 1, SITHMESSAGE_SENDTOALL, 0xFFu);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal params in MoveToFrame call from COG.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_RotatePivot(SithCog* pCog)
{
    unsigned int frame;
    SithThing* pThing;
    SithPathFrame* pFrame;
    float rotTime;
    rdVector3 rot;
    float v7;

    v7 = sithCogExec_PopFlex(pCog);
    frame = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( v7 == 0.0 )
    {
        v7 = 1.0;
    }

    if ( pThing && pThing->moveType == SITH_MT_PATH && pThing->moveInfo.pathMovement.numFrames > frame )
    {
        pFrame = &pThing->moveInfo.pathMovement.aFrames[frame];
        if ( v7 <= 0.0 )
        {
            rot.x = -pFrame->pyr.x;
            rot.y = -pFrame->pyr.y;
            rot.z = -pFrame->pyr.z;
            rotTime = -v7;
            sithPathMove_RotatePivot(pThing, &pFrame->pos, &rot, rotTime);
        }
        else
        {
            sithPathMove_RotatePivot(pThing, &pFrame->pos, &pFrame->pyr, v7);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal parameters in Rotate call from COG.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_Rotate(SithCog* pCog)
{
    unsigned int axis;
    SithThing* pThing;
    rdModel3* pModel3;
    float rotTime;
    rdVector3 offset;
    rdVector3 pyrRot;
    float degrees;

    rotTime = sithCogExec_PopFlex(pCog);
    axis = sithCogExec_PopInt(pCog);
    degrees = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Invalid thing in Rotate.\n",
            pCog->aName);
        return;
    }

    if ( pThing->moveType != SITH_MT_PATH )
    {
        STDLOG_ERROR("Cog %s: Thing %s is not a pathmove object in Rotate.\n",
            pCog->aName,
            pThing->aName);
        return;
    }

    if ( axis >= 3 )
    {
        STDLOG_ERROR("Cog %s: Thing %s invalid rotation axis %d in Rotate.\n",
            pCog->aName,
            pThing->aName,
            axis);
        return;
    }

    if ( degrees != 0.0 )
    {
        if ( rotTime == 0.0 )
        {
            STDLOG_ERROR("Cog %s: Thing %s given rotation time of 0 in Rotate.\n",
                pCog->aName,
                pThing->aName);
            return;
        }

        pModel3 = pThing->renderData.data.pModel3;
        if ( pModel3 )
        {
            offset = pModel3->insertOffset;
        }
        else
        {
            memset(&offset, 0, sizeof(offset));
        }

        rdMatrix_TransformVector34Acc(&offset, &pThing->orient);

        offset.x = pThing->pos.x - offset.x;
        offset.y = pThing->pos.y - offset.y;
        offset.z = pThing->pos.z - offset.z;

        if ( axis )
        {
            pyrRot.x = 0.0;
            if ( axis == 2 )
            {
                pyrRot.z = -degrees;
                pyrRot.y = 0.0;

            rotate_pivot:
                sithPathMove_RotatePivot(pThing, &offset, &pyrRot, rotTime);
                return;
            }

            pyrRot.y = -degrees;
        }
        else
        {
            pyrRot.x = -degrees;
            pyrRot.y = 0.0;
        }

        pyrRot.z = 0.0;
        goto rotate_pivot;
    }

    STDLOG_ERROR("NOTE: Cog %s: Thing %s being rotated 0 degrees in Rotate.\n",
        pCog->aName,
        pThing->aName);
}

void J3DAPI sithCogFunctionThing_RotateToPYR(SithCog* pCog)
{
    int bPyr;
    SithThing* pThing;
    rdVector3 pyr;
    float time;

    time = sithCogExec_PopFlex(pCog);
    bPyr = sithCogExec_PopVector(pCog, &pyr);
    pThing = sithCogExec_PopThing(pCog);

    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PATH )
        {
            if ( bPyr )
            {
                if ( time > 0.0 )
                {
                    sithPathMove_RotateToPYR(pThing, &pyr, time);
                }
                else
                {
                    STDLOG_ERROR("Cog %s: Time must be greater than zero for thing %s in RotateToPYR call from COG.\n",
                        pCog->aName,
                        pThing->aName);
                }
            }
            else
            {
                STDLOG_ERROR("Cog %s: Invalid vector applied to thing %s in RotateToPYR call from COG.\n",
                    pCog->aName,
                    pThing->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s is not a pathmove object in RotateToPYR.\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing in RotateToPYR.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingLight(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3 color;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        color = *(rdVector3*)&pThing->light.color;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal call to GetThingLight().\n",
            pCog->aName);

        color.blue = -1.0;
        color.green = -1.0;
        color.red = -1.0;
    }

    sithCogExec_PushVector(pCog, &color);
}

void J3DAPI sithCogFunctionThing_SetExtCamOffset(SithCog* pCog)
{
    rdVector3 vec;

    sithCogExec_PopVector(pCog, &vec);
    sithCamera_SetExtCameraOffset(&vec);
}

void J3DAPI sithCogFunctionThing_SetExtCamOffsetToThing(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3 pyrOrient;
    rdVector3 offset;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        offset.x = pThing->pos.x - sithPlayer_g_pLocalPlayerThing->pos.x;
        offset.y = pThing->pos.y - sithPlayer_g_pLocalPlayerThing->pos.y;
        offset.z = pThing->pos.z - sithPlayer_g_pLocalPlayerThing->pos.z;
        rdMatrix_ExtractAngles34(&sithPlayer_g_pLocalPlayerThing->orient, &pyrOrient);

        pyrOrient.x = 0.0;
        pyrOrient.y = -pyrOrient.y;
        pyrOrient.z = 0.0;
        rdVector_Rotate3Acc(&offset, &pyrOrient);
        sithCamera_SetExtCameraOffset(&offset);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad THING in SetExtCamOffsetToThing() call.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetExtCamLookOffset(SithCog* pCog)
{
    rdVector3 vec;

    sithCogExec_PopVector(pCog, &vec);
    sithCamera_SetExtCameraLookOffset(&vec);
}

void J3DAPI sithCogFunctionThing_SetExtCamLookOffsetToThing(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3 pyrRot;
    rdVector3 offset;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        offset.x = pThing->pos.x - sithPlayer_g_pLocalPlayerThing->pos.x;
        offset.y = pThing->pos.y - sithPlayer_g_pLocalPlayerThing->pos.y;
        offset.z = pThing->pos.z - sithPlayer_g_pLocalPlayerThing->pos.z;

        rdMatrix_ExtractAngles34(&sithPlayer_g_pLocalPlayerThing->orient, &pyrRot);

        pyrRot.x = 0.0;
        pyrRot.y = -pyrRot.y;
        pyrRot.z = 0.0;
        rdVector_Rotate3Acc(&offset, &pyrRot);
        sithCamera_SetExtCameraLookOffset(&offset);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad THING in SetExtCamLookOffsetToThing() call.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_MakeCamera2LikeCamera1(SithCog* pCog)
{
    SithThing* pCam1Look;
    SithThing* pCam1Pos;
    SithSector* pPosSector;
    SithSector* pLookSector;
    SithSector* pThing1Sec;
    SithSector* pThing2Sec;
    rdVector3 pos;
    rdVector3 look;

    pCam1Look = sithCogExec_PopThing(pCog);
    pCam1Pos = sithCogExec_PopThing(pCog);
    if ( !sithPlayer_g_pLocalPlayerThing || !sithPlayer_g_pLocalPlayerThing->pInSector )
    {
        STDLOG_ERROR("Cog %s: no local player or player not in valid sector!\n",
            pCog->aName);
        goto error_return;
    }

    if ( !pCam1Look || !pCam1Pos )
    {
        STDLOG_ERROR("Cog &s: Bad THING in MakeCamera2LikeCamera1() call.\n");
        goto error_return;
    }

    pos.x = sithCamera_g_camSpot.x;
    pos.y = sithCamera_g_camSpot.y;
    pos.z = sithCamera_g_camSpot.z;

    look.x = sithCamera_g_camLookSpot.x;
    look.y = sithCamera_g_camLookSpot.y;
    look.z = sithCamera_g_camLookSpot.z;

    pPosSector = sithCollision_FindSectorInRadius(
        sithPlayer_g_pLocalPlayerThing->pInSector,
        &sithPlayer_g_pLocalPlayerThing->pos,
        &pos,
        0.0);
    if ( !pPosSector )
    {
        STDLOG_ERROR("Cog &s: pos thing %s endpoint not in valid sector in MakeCamera2LikeCamera1() call.\n",// TODO: format bug Cog &s -> Cog %s
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, 0);
        return;
    }

    pLookSector = sithCollision_FindSectorInRadius(
        sithPlayer_g_pLocalPlayerThing->pInSector,
        &sithPlayer_g_pLocalPlayerThing->pos,
        &look,
        0.0);
    if ( !pLookSector )
    {
        STDLOG_ERROR("Cog &s: look thing %s endpoint not in valid sector in MakeCamera2LikeCamera1() call.\n",// TODO: format bug Cog &s -> Cog %s
            pCog->aName);
        goto error_return;
    }

    pCam1Pos->pos = pos;
    pCam1Look->pos = look;
    pThing1Sec = pCam1Pos->pInSector;
    if ( pPosSector != pThing1Sec )
    {
        if ( pThing1Sec )
        {
            sithThing_ExitSector(pCam1Pos);
        }

        sithThing_EnterSector(pCam1Pos, pPosSector, 1, 1);
    }

    pThing2Sec = pCam1Look->pInSector;
    if ( pLookSector != pThing2Sec )
    {
        if ( pThing2Sec )
        {
            sithThing_ExitSector(pCam1Look);
        }

        sithThing_EnterSector(pCam1Look, pLookSector, 1, 1);
    }

    sithCogExec_PushInt(pCog, 1);
}

void J3DAPI sithCogFunctionThing_SetCameraPosition(SithCog* pCog)
{
    unsigned int camNum;
    rdVector3 vec;

    sithCogExec_PopVector(pCog, &vec);
    camNum = sithCogExec_PopInt(pCog);
    if ( camNum <= 6 )
    {
        sithCamera_SetCameraPosition(&sithCamera_g_aCameras[camNum], &vec);
    }
}

void J3DAPI sithCogFunctionThing_SetCameraLookInterp(SithCog* pCog)
{
    int bEnable;
    unsigned int camNum;
    int bLookInterp;
    SithCamera* pCamera;

    bEnable = sithCogExec_PopInt(pCog);         // enable pan & tilt to lock on 2nd target
    camNum = sithCogExec_PopInt(pCog);
    if ( camNum > 6 )
    {
        STDLOG_ERROR("Cog %s: Invalid camera in SetCameraLookInterp().\n",
            pCog->aName);
    }
    else
    {
        bLookInterp = sithCamera_g_aCameras[camNum].bLookInterp;
        pCamera = &sithCamera_g_aCameras[camNum];
        if ( bEnable != bLookInterp )
        {
            pCamera->lookInterpState = -1;
        }

        pCamera->bLookInterp = bEnable;
    }
}

// Function enables/disables dolly mode for specified camera.
// 
// Dolly mode: when camera primary focus is changed the camera will interpolate move to the new focused thing instead of teleporte to it.
void J3DAPI sithCogFunctionThing_SetCameraPosInterp(SithCog* pCog)
{
    int bDollyMode;
    unsigned int camNum;
    int bPosInterp;
    SithCamera* pCamera;

    bDollyMode = sithCogExec_PopInt(pCog);
    camNum = sithCogExec_PopInt(pCog);
    if ( camNum > 6 )
    {
        STDLOG_ERROR("Cog %s: Invalid camera in SetCameraPosInterp().\n",
            pCog->aName);
    }
    else
    {
        bPosInterp = sithCamera_g_aCameras[camNum].bPosInterp;
        pCamera = &sithCamera_g_aCameras[camNum];
        if ( bDollyMode != bPosInterp )
        {
            pCamera->posInterpState = -1;
        }

        pCamera->bPosInterp = bDollyMode;
    }
}

void J3DAPI sithCogFunctionThing_GetCameraFOV(SithCog* pCog)
{
    sithCogExec_PushFlex(pCog, sithCamera_g_pCurCamera->fov);
}

void J3DAPI sithCogFunctionThing_GetCameraPosition(SithCog* pCog)
{
    unsigned int camNum;
    rdVector3 pos;

    camNum = sithCogExec_PopInt(pCog);
    if ( camNum > 6 )
    {
        STDLOG_ERROR("Cog %s: Invalid camera number %d in GetCameraPosition().\n",
            pCog->aName,
            camNum);

        memset(&pos, 0, sizeof(pos));
    }
    else
    {
        sithCamera_GetCameraPosition(&sithCamera_g_aCameras[camNum], &pos);
    }

    sithCogExec_PushVector(pCog, &pos);
}

void J3DAPI sithCogFunctionThing_SetCameraInterpSpeed(SithCog* pCog)
{
    unsigned int camNum;
    float speed;

    speed = sithCogExec_PopFlex(pCog);
    camNum = sithCogExec_PopInt(pCog);
    if ( camNum > 6 )
    {
        STDLOG_ERROR("Cog %s: Invalid camera in SetCameraInterpSpeed().\n",
            pCog->aName);
    }
    else
    {
        sithCamera_g_aCameras[camNum].interpSpeed = speed;
    }
}

void J3DAPI sithCogFunctionThing_SetCameraFOV(SithCog* pCog)
{
    int bInterp;
    SithCamera* pCamera;
    float fov;
    float timeDelta;

    timeDelta = sithCogExec_PopFlex(pCog);
    bInterp = sithCogExec_PopInt(pCog);
    fov = sithCogExec_PopFlex(pCog);
    pCamera = sithCamera_g_pCurCamera;
    if ( bInterp )
    {
        if ( timeDelta > 0.0 )
        {
            sithAnimate_CameraZoom(sithCamera_g_pCurCamera, fov, timeDelta);
            return;
        }

        STDLOG_ERROR("Cog %s: Invalid interp time in SetCameraFOV().\n",
            pCog->aName);
    }

    sithCamera_SetCameraFOV(pCamera, fov);
}

void J3DAPI sithCogFunctionThing_ResetCameraFOV(SithCog* pCog)
{
    int bInterp;
    SithCamera* pCamera;
    float time;

    time = sithCogExec_PopFlex(pCog);
    bInterp = sithCogExec_PopInt(pCog);
    pCamera = sithCamera_g_pCurCamera;
    if ( bInterp )
    {
        if ( time > 0.0 )
        {
            sithAnimate_CameraZoom(sithCamera_g_pCurCamera, 90.0, time);
            return;
        }

        STDLOG_ERROR("Cog %s: Invalid interp time in ResetCameraFOV().\n",
            pCog->aName);
    }

    sithCamera_SetCameraFOV(pCamera, 90.0);
}

void J3DAPI sithCogFunctionThing_SetCameraFadeThing(SithCog* pCog)
{
    SithThing* pSecondaryFocusThing;
    unsigned int camNum;
    SithCamera* pCamera;
    int bLookInterp;
    SithSector* pSector;
    int bBackside;
    rdVector3 pyr;
    SithThing* pPrimaryFocusThing;

    bBackside = sithCogExec_PopInt(pCog);       // Flip fadeplate to backside (i.e: frontside black & backside white color)
    pPrimaryFocusThing = sithCogExec_PopThing(pCog);
    pSecondaryFocusThing = sithCogExec_PopThing(pCog);
    camNum = sithCogExec_PopInt(pCog);
    if ( !pSecondaryFocusThing )
    {
        STDLOG_ERROR("Cog %s: Bad fade thing in SetCameraFadeThing() call.\n",
            pCog->aName);
    }

    else if ( camNum > 6 )
    {
        STDLOG_ERROR("Cog %s: Bad camera number in SetCameraFadeThing() call.\n",
            pCog->aName);
    }
    else
    {
        pCamera = &sithCamera_g_aCameras[camNum];
        if ( sithCamera_g_aCameras[camNum].bPosInterp )
        {
            pCamera->posInterpState = -1;
        }

        bLookInterp = pCamera->bLookInterp;
        pCamera->bPosInterp = 0;
        if ( bLookInterp )
        {
            pCamera->lookInterpState = -1;
        }

        pCamera->bLookInterp = 0;
        sithCamera_SetCameraPosition(pCamera, &sithCamera_g_aCameras[1].lookPos);// EXT camera
        sithCamera_SetCameraFOV(pCamera, sithCamera_g_aCameras[1].fov);

        memcpy(&pCamera->orient, &sithCamera_g_aCameras[1].orient, sizeof(pCamera->orient));
        memcpy(&pSecondaryFocusThing->orient, &pCamera->orient, sizeof(pSecondaryFocusThing->orient));

        pSecondaryFocusThing->pos.x = pSecondaryFocusThing->orient.lvec.x * 0.02 + sithCamera_g_aCameras[1].lookPos.x;

        pSecondaryFocusThing->pos.y = pSecondaryFocusThing->orient.lvec.y * 0.02 + sithCamera_g_aCameras[1].lookPos.y;

        pSecondaryFocusThing->pos.z = pSecondaryFocusThing->orient.lvec.z * 0.02 + sithCamera_g_aCameras[1].lookPos.z;

        pSector = sithCollision_FindSectorInRadius(
            sithCamera_g_aCameras[1].pSector,
            &sithCamera_g_aCameras[1].lookPos,
            &pSecondaryFocusThing->pos,
            0.0);

        sithThing_SetSector(pSecondaryFocusThing, pSector, 0);

        memcpy(&pPrimaryFocusThing->orient, &pSecondaryFocusThing->orient, sizeof(pPrimaryFocusThing->orient));

        pPrimaryFocusThing->pos = sithCamera_g_aCameras[1].lookPos;

        sithThing_SetSector(pPrimaryFocusThing, sithCamera_g_aCameras[1].pSector, 0);
        if ( !bBackside )
        {
            pyr.pitch = 0.0;
            pyr.yaw = 180.0;
            pyr.roll = 0.0;
            rdMatrix_PreRotate34(&pSecondaryFocusThing->orient, &pyr);
        }

        sithCamera_SetCameraFocus(pCamera, pPrimaryFocusThing, pSecondaryFocusThing);
    }
}

void J3DAPI sithCogFunctionThing_ThingLight(SithCog* pCog)
{
    int bVect;
    SithThing* pThing;
    float timeDelta;
    rdVector4 color;
    float maxRadius;

    timeDelta = sithCogExec_PopFlex(pCog);
    maxRadius = sithCogExec_PopFlex(pCog);
    bVect = sithCogExec_PopVector(pCog, (rdVector3*)&color);
    pThing = sithCogExec_PopThing(pCog);
    if ( bVect && pThing )
    {
        if ( timeDelta == 0.0 )
        {
            // TODO: BUG: Missing initialization of light.color.alpha which creates render flickering bug
            pThing->light.color.red = color.red;
            pThing->light.color.green = color.green;
            pThing->light.color.blue = color.blue;

            pThing->light.minRadius = maxRadius;
            pThing->light.maxRadius = maxRadius * 1.1;

            if ( color.red > 0.0 || color.green > 0.0 || color.blue > 0.0 )
            {
                pThing->flags |= SITH_TF_EMITLIGHT; // Is this right instead of LOBYTE macro?
            }
        }
        else
        {
            color.alpha = maxRadius;
            sithAnimate_StartThingLightAnim(pThing, &color, timeDelta, (SithAnimateFlags)0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal call to ThingLight().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ThingLightAnim(SithCog* pCog)
{
    int bEndColor;
    int bColor;
    SithThing* pThing;
    SithAnimationSlot* started;
    float timeDelta;
    float speed;
    float endRadius;
    rdVector3 startColor;
    rdVector4 endColor;
    float startRadius;

    speed = sithCogExec_PopFlex(pCog);
    endRadius = sithCogExec_PopFlex(pCog);
    bEndColor = sithCogExec_PopVector(pCog, (rdVector3*)&endColor);
    startRadius = sithCogExec_PopFlex(pCog);
    bColor = sithCogExec_PopVector(pCog, &startColor);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && bEndColor && bColor && speed > 0.0 )
    {
        endColor.alpha = endRadius;

        pThing->light.color.red = startColor.red;
        pThing->light.color.green = startColor.green;
        pThing->light.color.blue = startColor.blue;

        timeDelta = speed * 0.5;
        pThing->light.color.alpha = startRadius;
        pThing->light.minRadius = startRadius;
        pThing->light.maxRadius = startRadius * 1.1;
        started = sithAnimate_StartThingLightAnim(pThing, &endColor, timeDelta, SITHANIMATE_LOOP);
        if ( started )
        {
            sithCogExec_PushInt(pCog, started->animID);
            return;
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad parameters to ThingLightAnim.\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_ThingFadeAnim(SithCog* pCog)
{
    int bLoop;
    SithThing* pThing;
    rdVector4* pPolyExtraColor;
    SithAnimationSlot* pAnim;
    float startAlpha;
    float endAlpha;
    rdVector4 startColor;
    rdVector4 endColor;
    float timeDelta;

    endColor.red = 1.0;
    endColor.green = 1.0;
    endColor.blue = 1.0;
    endColor.alpha = 1.0;

    startColor.red = 1.0;
    startColor.green = 1.0;
    startColor.blue = 1.0;
    startColor.alpha = 1.0;

    bLoop = sithCogExec_PopInt(pCog);
    timeDelta = sithCogExec_PopFlex(pCog);
    endAlpha = sithCogExec_PopFlex(pCog);
    startAlpha = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( pThing && timeDelta > 0.0 )
    {
        if ( pThing->type == SITH_THING_POLYLINE )
        {
            *(rdVector4*)&startColor.red = *(rdVector4*)&pThing->renderData.data.pPolyline->face.extraLight.red;// TODO: memcpy

            pPolyExtraColor = &pThing->renderData.data.pPolyline->face.extraLight;
            endColor.red = pPolyExtraColor->red;
            endColor.green = pPolyExtraColor->y;
            endColor.blue = pPolyExtraColor->z;
            startColor.alpha = startAlpha;
        }
        else
        {
            startColor.alpha = startAlpha;
            rdModel3_SetThingColor(&pThing->renderData, &startColor);
        }

        endColor.alpha = endAlpha;
        if ( bLoop )
        {
            timeDelta = timeDelta * 0.5;
            pAnim = sithAnimate_StartThingColorAnim(pThing, &startColor, &endColor, timeDelta, SITHANIMATE_LOOP);
        }
        else
        {
            pAnim = sithAnimate_StartThingColorAnim(pThing, &startColor, &endColor, timeDelta, (SithAnimateFlags)0);
        }

        if ( pAnim )
        {
            sithCogExec_PushInt(pCog, pAnim->animID);
            return;
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad parameters to sithCogFunctionThing_FadeThingAnim.\n",
            pCog->aName);
    }

    STDLOG_ERROR("Cog %s: Unable to create animation for sithCogFunctionThing_FadeThingAnim().\n",
        pCog->aName);

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_WaitForStop(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PATH )
        {
            if ( (pThing->moveInfo.pathMovement.mode & 3) != 0 )// 3- SITH_PATHMOVE_MOVING
            {
                pCog->status = 3;               // SITHCOG_STATUS_WAITING_THING_TO_STOP
                pCog->statusParams[0] = pThing->idx;
                if ( (pCog->flags & SITHCOG_DEBUG) != 0 )
                {
                    sprintf(std_g_genBuffer, "Cog %s: Waiting for stop on object %d.\n", pCog->aName, pThing->idx);
                    sithConsole_PrintString(std_g_genBuffer);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: thing %s is not a path move thing in WaitForStop call.\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal thingref in WaitForStop call.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_WaitForAnimStop(SithCog* pCog)
{
    int animID;
    char flags;

    animID = sithCogExec_PopInt(pCog);
    if ( sithAnimate_GetAnim(animID) )
    {
        flags = pCog->flags;
        pCog->status = SITHCOG_STATUS_WAITING_ANIMATION_TO_STOP;
        pCog->statusParams[0] = animID;
        if ( (flags & SITHCOG_DEBUG) != 0 )
        {
            sprintf(std_g_genBuffer, "Cog %s: Waiting for anim %d to stop.\n", pCog->aName, animID);
            sithConsole_PrintString(std_g_genBuffer);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Anim ID %d is not a valid ID in WaitForAnimStop call.\n",
            pCog->aName,
            animID);
    }
}

void J3DAPI sithCogFunctionThing_GetThingSector(SithCog* pCog)
{
    SithThing* pThing;
    const SithSector* pSector;
    int sectorIdx;

    if ( !pCog )
    {
        // sith_g_pHS->pAssert("pCog", "C:\\Jones3D\\Libs\\sith\\Cog\\sithCogFunctionThing.c", 2913);

        SITH_ASSERTREL(pCog);
    }

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pSector = pThing->pInSector) != 0 )
    {
        sectorIdx = sithSector_GetSectorIndex(pSector);
        sithCogExec_PushInt(pCog, sectorIdx);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing ref in GetThingSector().\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetCurFrame(SithCog* pCog)
{
    SithThing* pThing;

    if ( !pCog )
    {
        // sith_g_pHS->pAssert("pCog", "C:\\Jones3D\\Libs\\sith\\Cog\\sithCogFunctionThing.c", 2946);

        SITH_ASSERTREL(pCog);
    }

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PATH )
        {
            sithCogExec_PushInt(pCog, pThing->moveInfo.pathMovement.currentFrame);
            return;
        }

        STDLOG_ERROR("Cog %s: Thing %s is not a path move type thing.\n",
            pCog->aName,
            pThing->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thingRef in GetCurFrame.\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, 0);
}

void J3DAPI sithCogFunctionThing_GetGoalFrame(SithCog* pCog)
{
    SithThing* pThing;

    if ( !pCog )
    {
        // sith_g_pHS->pAssert("pCog", "C:\\Jones3D\\Libs\\sith\\Cog\\sithCogFunctionThing.c", 2983);

        SITH_ASSERTREL(pCog);
    }

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PATH )
    {
        sithCogExec_PushInt(pCog, pThing->moveInfo.pathMovement.goalFrame);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thingRef in GetGoalFrame.\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_StopThing(SithCog* pCog)
{
    SithThing* pThing;
    int moveType;
    SithCogMsgType execMsgType;
    SithAIControlBlock* pLocal;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        moveType = pThing->moveType - 1;
        if ( moveType )
        {
            if ( moveType == 1 )                // Path move
            {
                sithPathMove_Finish(pThing);
                if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )// 0x200
                {
                    execMsgType = pCog->execMsgType;
                    if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                    {
                        sithDSSThing_PathMove(pThing, 0, 0.0, 2, SITHMESSAGE_SENDTOALL, 0xFFu);// 2 - finish moving
                    }
                }
            }
        }
        else
        {
            sithPhysics_ResetThingMovement(pThing);
            if ( pThing->controlType == SITH_CT_AI )
            {
                pLocal = pThing->controlInfo.aiControl.pLocal;
                if ( pLocal )
                {
                    sithAIMove_AIStop(pLocal);
                }
            }
        }
    }
}

void J3DAPI sithCogFunctionThing_IsThingMoving(SithCog* pCog)
{
    SithThing* pThing;
    SithAIControlBlock* pLocal;
    SithThingMoveType moveType;
    int moveState;

    if ( !pCog )
    {
        // sith_g_pHS->pAssert("pCog", "C:\\Jones3D\\Libs\\sith\\Cog\\sithCogFunctionThing.c", 3070);

        SITH_ASSERTREL(pCog);
    }

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type )
    {
        if ( pThing->controlType == SITH_CT_AI && (pLocal = pThing->controlInfo.aiControl.pLocal) != 0 )
        {
            sithCogExec_PushInt(pCog, pLocal->mode & (SITHAI_MODE_TURNING | SITHAI_MODE_MOVING));
        }
        else
        {
            moveType = pThing->moveType;
            if ( moveType == SITH_MT_PHYSICS )
            {
                moveState = pThing->moveInfo.physics.velocity.x != 0.0
                    || pThing->moveInfo.physics.velocity.y != 0.0
                    || pThing->moveInfo.physics.velocity.z != 0.0;

                if ( pThing->moveInfo.physics.angularVelocity.pitch != 0.0
                    || pThing->moveInfo.physics.angularVelocity.yaw != 0.0
                    || pThing->moveInfo.physics.angularVelocity.roll != 0.0 )
                {
                    sithCogExec_PushInt(pCog, moveState | 1);
                }
                else
                {
                    sithCogExec_PushInt(pCog, moveState);
                }
            }

            else if ( moveType == SITH_MT_PATH )
            {
                sithCogExec_PushInt(
                    pCog,
                    pThing->moveInfo.pathMovement.mode & (SITH_PATHMOVE_ROTATE | SITH_PATHMOVE_MOVE));
            }
            else
            {
                STDLOG_ERROR("Cog %s: Unknown movement type for thingRef, assuming not moving.\n",
                    pCog->aName);
                sithCogExec_PushInt(pCog, 0);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad parameters in IsMoving()\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingPulse(SithCog* pCog)
{
    SithThing* pThing;
    SithThingFlag flags;
    __int64 msecPulse;
    float secPulse;

    secPulse = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        flags = pThing->flags;
        if ( secPulse == 0.0 )
        {
            pThing->msecNextPulseTime = 0;
            pThing->flags = flags & ~SITH_TF_PULSESET;
            pThing->msecPulseInterval = 0;
        }
        else
        {
            pThing->flags = flags | SITH_TF_PULSESET;
            msecPulse = (__int64)(secPulse * 1000.0);
            pThing->msecPulseInterval = msecPulse;
            pThing->msecNextPulseTime = msecPulse + sithTime_g_msecGameTime;
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal parameters to SetThingPulse.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingTimer(SithCog* pCog)
{
    SithThing* pThing;
    SithThingFlag flags;
    float secTimer;

    secTimer = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( secTimer == 0.0 )
        {
            flags = pThing->flags;
            pThing->msecTimerTime = 0;
            pThing->flags = flags & ~SITH_TF_TIMERSET;
        }
        else
        {
            pThing->flags |= SITH_TF_TIMERSET;
            pThing->msecTimerTime = sithTime_g_msecGameTime + (__int64)(secTimer * 1000.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal parameters to SetThingTimer.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_CaptureThing(SithCog* pCog)
{
    SithThing* pThing;
    SithThingFlag flags;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        flags = pThing->flags;
        pThing->pCaptureCog = pCog;
        // BYTE1(flags) |= 4u;                     // 0x400 - cog linked
        // Fix: Modify the flags variable directly instead of using BYTE1
        flags |= SITH_TF_COGLINKED;  // Set the "cog linked" flag (bit 10)
        pThing->flags = flags;
    }
}

void J3DAPI sithCogFunctionThing_ReleaseThing(SithCog* pCog)
{
    SithThing* pThing;
    SithCog* pThingCog;
    SithThingFlag flags;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThingCog = pThing->pCog;
        pThing->pCaptureCog = 0;
        if ( !pThingCog && !sithCog_IsThingLinked(pThing) )
        {
            flags = pThing->flags;
            // BYTE1(flags) = ((unsigned __int16)pThing->flags >> 8) & ~4;// 0x400 - SITH_TF_COGLINKED
            // Fix: Modify the flags variable directly instead of using BYTE1
            flags &= ~SITH_TF_COGLINKED; // Clear bit 10 (0x400 - SITH_TF_COGLINKED)
            pThing->flags = flags;
        }
    }
}

void J3DAPI sithCogFunctionThing_GetThingParent(SithCog* pCog)
{
    SithThing* pThing;
    SithThing* pParent;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pParent = sithThing_GetThingParent(pThing)) != 0 )
    {
        sithCogExec_PushInt(pCog, pParent->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetThingPos(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushVector(pCog, &pThing->pos);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetThingPos(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 newPos;

    sithCogExec_PopVector(pCog, &newPos);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->pos.x = newPos.x;
        pThing->pos.y = newPos.y;
        pThing->pos.z = newPos.z;

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Pos(pThing, SITHMESSAGE_SENDTOALL, DPSEND_GUARANTEED);// TODO: make separate global var for dpflags and do secure connection
            }
        }

        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_GetInventory(SithCog* pCog)
{
    unsigned int typeId;
    SithThing* pThing;
    float val;

    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.actorInfo.pPlayer )
    {
        if ( typeId < 200 )
        {
            val = sithInventory_GetInventory(pThing, typeId);
            sithCogExec_PushFlex(pCog, val);
            return;
        }

        STDLOG_ERROR("Cog %s: Called GetInventory for illegal type %d.\n",
            pCog->aName,
            typeId);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Called GetInventory for illegal thing.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, 0.0);
}

void J3DAPI sithCogFunctionThing_SetInventory(SithCog* pCog)
{
    unsigned int typeId;
    SithThing* pThing;
    float amount;

    amount = sithCogExec_PopFlex(pCog);
    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.actorInfo.pPlayer )
    {
        if ( typeId < 200 )
        {
            sithInventory_SetInventory(pThing, typeId, amount);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Called SetInventory for illegal type %d.\n",
                pCog->aName,
                typeId);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Called SetInventory for illegal thing.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ChangeInventory(SithCog* pCog)
{
    unsigned int typeId;
    SithThing* pThing;
    float newAmount;
    float amount;

    amount = sithCogExec_PopFlex(pCog);
    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.actorInfo.pPlayer )
    {
        if ( typeId < 200 )
        {
            newAmount = sithInventory_ChangeInventory(pThing, typeId, amount);
            sithCogExec_PushFlex(pCog, newAmount);
            return;
        }

        STDLOG_ERROR("Cog %s: Called ChangeInventory for illegal type %d.\n",
            pCog->aName,
            typeId);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Called ChangeInventory for illegal thing.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, 0.0);
}

void J3DAPI sithCogFunctionThing_GetInventoryCog(SithCog* pCog)
{
    unsigned int typeId;
    SithThing* pThing;
    SithInventoryType* pInventory;
    SithCog* pInvCog;

    typeId = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.actorInfo.pPlayer )
    {
        pInventory = sithInventory_GetInventoryType(pThing, typeId);
        if ( typeId < 200 && pInventory )
        {
            pInvCog = pInventory->pCog;
            if ( pInvCog )
            {
                sithCogExec_PushInt(pCog, pInvCog->idx);
                return;
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Called GetInventoryCog for illegal type %d.\n",
                pCog->aName,
                typeId);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Called GetInventoryCog for illegal thing.\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_GetThingVelocity(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3 vec;

    vec.x = rdroid_g_zeroVector3.x;
    vec.y = rdroid_g_zeroVector3.y;
    vec.z = rdroid_g_zeroVector3.z;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            vec = pThing->moveInfo.physics.velocity;
        }

        else if ( pThing->moveType == SITH_MT_PATH )
        {
            vec.x = pThing->moveInfo.pathMovement.vecDeltaPos.x * pThing->moveInfo.pathMovement.moveVel;
            vec.y = pThing->moveInfo.pathMovement.vecDeltaPos.y * pThing->moveInfo.pathMovement.moveVel;
            vec.z = pThing->moveInfo.pathMovement.vecDeltaPos.z * pThing->moveInfo.pathMovement.moveVel;
        }

        sithCogExec_PushVector(pCog, &vec);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetThingVel(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vel;

    sithCogExec_PopVector(pCog, &vel);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            pThing->moveInfo.physics.velocity.x = vel.red;
            pThing->moveInfo.physics.velocity.y = vel.green;
            pThing->moveInfo.physics.velocity.z = vel.blue;

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 1);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Cannot set velocity on a movepath thing.",
                pCog->aName);
        }
    }
}

void J3DAPI sithCogFunctionThing_ApplyForce(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vec;

    sithCogExec_PopVector(pCog, &vec);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            sithPhysics_ApplyForce(pThing, &vec);
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 1);
                }
            }
        }
    }
}

void J3DAPI sithCogFunctionThing_AddThingVel(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vel;

    sithCogExec_PopVector(pCog, &vel);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            pThing->moveInfo.physics.velocity.x = vel.x + pThing->moveInfo.physics.velocity.x;
            pThing->moveInfo.physics.velocity.y = vel.y + pThing->moveInfo.physics.velocity.y;
            pThing->moveInfo.physics.velocity.z = vel.z + pThing->moveInfo.physics.velocity.z;

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 1);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Cannot add velocity on a non-physics thing.",
                pCog->aName);
        }
    }
}

void J3DAPI sithCogFunctionThing_GetThingLVec(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushVector(pCog, &pThing->orient.lvec);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_GetThingUVec(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushVector(pCog, &pThing->orient.uvec);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_GetThingRVec(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushVector(pCog, &pThing->orient.rvec);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_GetActorHeadPYR(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && ((type = pThing->type, type == SITH_THING_ACTOR) || type == SITH_THING_PLAYER) )
    {
        sithCogExec_PushVector(pCog, &pThing->thingInfo.actorInfo.headPYR);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_DetachThing(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithThing_DetachThing(pThing);
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
            }
        }
    }
}

void J3DAPI sithCogFunctionThing_GetThingAttachFlags(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->attach.flags);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_AttachThingToSurf(SithCog* pCog)
{
    SithSurface* pSurf;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    pSurf = sithCogExec_PopSurface(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pSurf )
        {
            sithThing_AttachThingToSurface(pThing, pSurf, 1);
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad sector in AttachThingToSurf().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in AttachThingToSurf().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_AttachThingToThing(SithCog* pCog)
{
    SithThing* pAttachThing;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    pAttachThing = sithCogExec_PopThing(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pAttachThing )
        {
            sithThing_AttachThingToThing(pThing, pAttachThing);
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad attach thing in AttachThingToThing().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in AttachThingToThing().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_AttachThingToThingEx(SithCog* pCog)
{
    int attflags;
    SithThing* pAttachThing;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    attflags = sithCogExec_PopInt(pCog);
    pAttachThing = sithCogExec_PopThing(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pAttachThing )
        {
            sithThing_AttachThingToThing(pThing, pAttachThing);
            pThing->attach.flags |= attflags;

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Invalid attach thing in AttachThingToThingEx.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing in AttachThingToThingEx.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingAttachedThing(SithCog* pCog)
{
    int thingNum;
    int attype;
    SithThing* pThing;
    SithThing* pAttachedThing;

    thingNum = -1;
    attype = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Invalid THING in GetThingAttachedThing().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    pAttachedThing = pThing->pAttachedThing;
    if ( attype == -1 )
    {
        thingNum = sithThing_GetThingIndex(pAttachedThing);
        sithCogExec_PushInt(pCog, thingNum);
        return;
    }

    if ( pAttachedThing )
    {
        while ( pAttachedThing->type != attype )
        {
            pAttachedThing = pAttachedThing->pNextAttachedThing;
            if ( !pAttachedThing )
            {
                sithCogExec_PushInt(pCog, -1);
                return;
            }
        }

        thingNum = sithThing_GetThingIndex(pAttachedThing);
    }

    sithCogExec_PushInt(pCog, thingNum);
}

void J3DAPI sithCogFunctionThing_WaitMode(SithCog* pCog)
{
    SithPuppetSubMode mode;
    SithThing* pThing;
    SithPuppetTrack* pTrack;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pTrack = sithPuppet_GetModeTrack(pThing, mode);
        if ( pTrack )
        {
            pCog->status = SITHCOG_STATUS_WAITING_KEYFRAME_TO_STOP;
            pCog->statusParams[0] = pThing->renderData.pPuppet->aTracks[pTrack->trackNum].guid;
            pCog->statusParams[1] = pThing->idx;
            sithCogExec_PushInt(pCog, 1);
        }
        else
        {
            sithCogExec_PushInt(pCog, 0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing in WaitMode().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PlayMode(SithCog* pCog)
{
    SithPuppetSubMode mode;
    SithThing* pThing;
    int trackNum;
    SithCogMsgType execMsgType;
    int bWait;

    bWait = sithCogExec_PopInt(pCog);
    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        trackNum = sithPuppet_PlayMode(pThing, mode, 0);
        if ( trackNum == -1 )
        {
            STDLOG_ERROR("Cog %s: No space to add keyframe mode %d to thing %s in PlayMode().\n",
                pCog->aName,
                mode,
                pThing->aName);

            sithCogExec_PushInt(pCog, -1);
        }
        else
        {
            sithCogExec_PushInt(pCog, trackNum);

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN && trackNum >= 0 )
                {
                    sithDSSThing_PlayKeyMode(
                        pThing,
                        mode,
                        pThing->renderData.pPuppet->aTracks[trackNum].guid,
                        SITHMESSAGE_SENDTOALL,
                        0xFFu);
                }
            }

            if ( bWait )
            {
                if ( trackNum >= 0 )
                {
                    pCog->status = SITHCOG_STATUS_WAITING_KEYFRAME_TO_STOP;
                    pCog->statusParams[0] = pThing->renderData.pPuppet->aTracks[trackNum].guid;
                    pCog->statusParams[1] = pThing->idx;
                }
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in PlayMode().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_StopMode(SithCog* pCog)
{
    SithPuppetSubMode mode;
    SithThing* pThing;
    float fadeTime;

    fadeTime = sithCogExec_PopFlex(pCog);
    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithPuppet_StopMode(pThing, mode, fadeTime);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in StopMode().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SynchMode(SithCog* pCog)
{
    int bReverse;
    SithPuppetSubMode newMode;
    SithPuppetSubMode oldMode;
    SithThing* pThing;
    float v1;

    bReverse = sithCogExec_PopInt(pCog);
    v1 = sithCogExec_PopFlex(pCog);
    newMode = sithCogExec_PopInt(pCog);
    oldMode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( pThing )
    {
        if ( sithPuppet_SynchMode(pThing, oldMode, newMode, v1, bReverse) < 0 )
        {
            STDLOG_ERROR("Cog %s: SynchMode() - Unable to sync mode %d to mode %d.\n",
                pCog->aName,
                oldMode,
                newMode);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SynchMode().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_IsModePlaying(SithCog* pCog)
{
    int mode;
    SithThing* pThing;
    rdKeyframe* pKeyframe;
    rdPuppet* pPuppet;
    int trackNum;
    rdPuppetTrack* pTrack;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        // TODO: bug, missing bound check for mode
        pKeyframe = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][mode].pKeyframe;
        if ( !pKeyframe )
        {
            sithCogExec_PushInt(pCog, 0);
            return;
        }

        pPuppet = pThing->renderData.pPuppet;
        trackNum = 0;
        pTrack = pPuppet->aTracks[trackNum].pKFTrack;
        do
        {
            if ( pTrack == pKeyframe )
            {
                break;
            }

            ++trackNum;
        } while ( trackNum < RDPUPPET_MAX_TRACKS );

        if ( trackNum == RDPUPPET_MAX_TRACKS )
        {
            sithCogExec_PushInt(pCog, 0);
        }
        else if ( (pPuppet->aTracks[trackNum].status & RDPUPPET_TRACK_PAUSED) != 0 )
        {
            sithCogExec_PushInt(pCog, 2);
        }
        else
        {
            sithCogExec_PushInt(pCog, 1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in IsModePlaying().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PauseMode(SithCog* pCog)
{
    int mode;
    SithThing* pThing;
    rdKeyframe* pKeyframe;
    rdPuppet* pPuppet;
    int trackNum;
    rdPuppetTrack* pTrack;
    rdPuppetTrackStatus status;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pKeyframe = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][mode].pKeyframe;
        if ( !pKeyframe )
        {
            sithCogExec_PushInt(pCog, 0);
            return;
        }

        pPuppet = pThing->renderData.pPuppet;
        trackNum = 0;
        pTrack = pPuppet->aTracks[trackNum].pKFTrack;
        do
        {
            if ( pTrack == pKeyframe )
            {
                break;
            }

            ++trackNum;
        } while ( trackNum < RDPUPPET_MAX_TRACKS );

        if ( trackNum == RDPUPPET_MAX_TRACKS )
        {
            sithCogExec_PushInt(pCog, 0);
        }
        else
        {
            pTrack = &pPuppet->aTracks[trackNum];
            status = pTrack->status;
            if ( (pTrack->status & RDPUPPET_TRACK_PAUSED) != 0 )
            {
                sithCogExec_PushInt(pCog, 2);
            }
            else
            {
                status |= RDPUPPET_TRACK_PAUSED;
                pTrack->status = status;
                sithCogExec_PushInt(pCog, 1);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in PauseMode().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_ResumeMode(SithCog* pCog)
{
    int mode;
    SithThing* pThing;
    rdKeyframe* pKeyframe;
    rdPuppet* pPuppet;
    int trackNum;
    rdPuppetTrack* pTrack;
    rdPuppetTrackStatus status;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pKeyframe = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][mode].pKeyframe;
        if ( !pKeyframe )
        {
            sithCogExec_PushInt(pCog, 0);
            return;
        }

        pPuppet = pThing->renderData.pPuppet;
        trackNum = 0;
        pTrack = pPuppet->aTracks[trackNum].pKFTrack;
        do
        {
            if ( pTrack == pKeyframe )
            {
                break;
            }

            ++trackNum;
        } while ( trackNum < RDPUPPET_MAX_TRACKS );

        if ( trackNum == RDPUPPET_MAX_TRACKS )
        {
            sithCogExec_PushInt(pCog, 0);
        }
        else
        {
            pTrack = &pPuppet->aTracks[trackNum];
            status = pTrack->status;
            if ( (pTrack->status & RDPUPPET_TRACK_PAUSED) != 0 )
            {
                status &= ~RDPUPPET_TRACK_PAUSED;
                pTrack->status = status;
                sithCogExec_PushInt(pCog, 1);
            }
            else
            {
                sithCogExec_PushInt(pCog, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in ResumeMode().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_TrackToMode(SithCog* pCog)
{
    unsigned int trackNum;
    SithThing* pThing;
    rdKeyframe* pKFTrack;
    int mode;
    SithPuppetClassSubmode* pSubmode;

    trackNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( trackNum > 7 )
        {
            sithCogExec_PushInt(pCog, -1);
            return;
        }

        pKFTrack = pThing->renderData.pPuppet->aTracks[trackNum].pKFTrack;
        if ( !pKFTrack )
        {
            sithCogExec_PushInt(pCog, -1);
            return;
        }

        mode = 0;
        pSubmode = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode];
        do
        {
            if ( pSubmode->pKeyframe == pKFTrack )
            {
                break;
            }

            ++mode;
            ++pSubmode;
        } while ( mode < 84 );

        if ( mode != SITH_PUPPET_NUMSUBMODES )
        {
            sithCogExec_PushInt(pCog, mode);
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in TrackToMode().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PlayKey(SithCog* pCog)
{
    int lowPriority;
    rdKeyframe* pKfTrack;
    SithThing* pThing;
    rdPuppet* pPuppet;
    int trackNum;
    SithCogMsgType execMsgType;
    int bWait;
    rdKeyframeFlags kfflags;

    bWait = sithCogExec_PopInt(pCog);
    kfflags = sithCogExec_PopInt(pCog);
    lowPriority = sithCogExec_PopInt(pCog);
    pKfTrack = sithCogExec_PopKeyframe(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: No thing to play keyframe anim on in PlayKey().\n",
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    pPuppet = pThing->renderData.pPuppet;
    if ( !pPuppet )
    {
        STDLOG_ERROR("Cog %s: tried to play keyframe anim %s on thing %s - no puppet in PlayKey().\n",
            pCog->aName,
            pKfTrack,
            pThing->aName);
        goto error_return;
    }

    if ( !pKfTrack )
    {
        STDLOG_ERROR("Cog %s: Bad keyframe reference in PlayKey().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    trackNum = sithPuppet_PlayKey(pPuppet, pKfTrack, lowPriority, lowPriority + 2, kfflags, 0);
    if ( trackNum < 0 )
    {
        STDLOG_ERROR("Cog %s: No space to add keyframe %s to thing %s.\n",
            pCog->aName,
            pKfTrack,
            pThing->aName);
        goto error_return;
    }

    sithCogExec_PushInt(pCog, trackNum);
    if ( pThing->moveType == SITH_MT_PATH )
    {
        if ( pThing->moveInfo.pathMovement.mode )
        {
            sithPathMove_Finish(pThing);
        }

        pThing->moveInfo.pathMovement.curOrient.dvec.x = pThing->pos.x;
        pThing->moveInfo.pathMovement.curOrient.dvec.y = pThing->pos.y;
        pThing->moveInfo.pathMovement.curOrient.dvec.z = pThing->pos.z;
    }

    if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
    {
        execMsgType = pCog->execMsgType;
        if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
        {
            sithDSSThing_PlayKey(
                pThing,
                pKfTrack,
                kfflags,
                lowPriority,
                pThing->renderData.pPuppet->aTracks[trackNum].guid,
                SITHMESSAGE_SENDTOALL,
                0xFFu);
        }
    }

    if ( bWait )
    {
        pCog->status = SITHCOG_STATUS_WAITING_KEYFRAME_TO_STOP;
        pCog->statusParams[0] = pThing->renderData.pPuppet->aTracks[trackNum].guid;
        pCog->statusParams[1] = pThing->idx;
    }
}

void J3DAPI sithCogFunctionThing_PlayKeyEx(SithCog* pCog)
{
    rdKeyframeFlags kfflags;
    rdKeyframe* pKfTrack;
    SithThing* pThing;
    int trackNum;
    int lowPriority;
    int bWait;
    int highPriority;

    bWait = sithCogExec_PopInt(pCog);
    kfflags = sithCogExec_PopInt(pCog);
    highPriority = sithCogExec_PopInt(pCog);
    lowPriority = sithCogExec_PopInt(pCog);
    pKfTrack = sithCogExec_PopKeyframe(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pKfTrack )
        {
            trackNum = sithPuppet_PlayKey(pThing->renderData.pPuppet, pKfTrack, lowPriority, highPriority, kfflags, 0);
            if ( trackNum >= 0 )
            {
                sithCogExec_PushInt(pCog, trackNum);

                if ( pThing->moveType == SITH_MT_PATH )
                {
                    if ( pThing->moveInfo.pathMovement.mode )
                    {
                        sithPathMove_Finish(pThing);
                    }

                    pThing->moveInfo.pathMovement.curOrient.dvec.x = pThing->pos.x;
                    pThing->moveInfo.pathMovement.curOrient.dvec.y = pThing->pos.y;
                    pThing->moveInfo.pathMovement.curOrient.dvec.z = pThing->pos.z;
                }

                if ( bWait )
                {
                    pCog->status = SITHCOG_STATUS_WAITING_KEYFRAME_TO_STOP;
                    pCog->statusParams[0] = pThing->renderData.pPuppet->aTracks[trackNum].guid;
                    pCog->statusParams[1] = pThing->idx;
                }
            }
            else
            {
                STDLOG_ERROR("Cog %s: No space to add keyframe %s to thing %s in PLayKeyEx().\n",
                    pCog->aName,
                    pKfTrack->aName,
                    pThing->aName);

                sithCogExec_PushInt(pCog, trackNum);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad keyframe reference in PlayKeyEx().\n",
                pCog->aName);

            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing to play keyframe anim on in PlayKeyEx().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PauseKey(SithCog* pCog)
{
    unsigned int trackNum;
    SithThing* pThing;
    rdPuppetTrack* pTrack;

    trackNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->pPuppetClass )
        {
            if ( trackNum < RDPUPPET_MAX_TRACKS )
            {
                pTrack = &pThing->renderData.pPuppet->aTracks[trackNum];
                if ( pTrack->status )
                {
                    pTrack->status |= RDPUPPET_TRACK_PAUSED;
                    sithCogExec_PushInt(pCog, 1);
                    return;
                }

                STDLOG_ERROR("Cog %s: Track number %d does not exist for thing %s in PauseKey().\n",
                    pCog->aName,
                    trackNum,
                    pThing->aName);
            }
            else
            {
                STDLOG_ERROR("Cog %s: Invalid track number %d for thing %s in PauseKey().\n",
                    pCog->aName,
                    trackNum,
                    pThing->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s has no puppet in PauseKey().\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in PauseKey().\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_ResumeKey(SithCog* pCog)
{
    unsigned int trackNum;
    SithThing* pThing;
    rdPuppetTrack* pTrack;

    trackNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->pPuppetClass )
        {
            if ( trackNum < RDPUPPET_MAX_TRACKS )
            {
                pTrack = &pThing->renderData.pPuppet->aTracks[trackNum];
                if ( pTrack->status )
                {
                    pTrack->status &= ~RDPUPPET_TRACK_PAUSED;
                    sithCogExec_PushInt(pCog, 1);
                    return;
                }

                STDLOG_ERROR("Cog %s: Track number %d does not exist for thing %s in ResumeKey().\n",
                    pCog->aName,
                    trackNum,
                    pThing->aName);
            }
            else
            {
                STDLOG_ERROR("Cog %s: Invalid track number %d for thing %s in ResumeKey().\n",
                    pCog->aName,
                    trackNum,
                    pThing->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s has no puppet in ResumeKey().\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in ResumeKey().\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_StopKey(SithCog* pCog)
{
    unsigned int trackNum;
    SithThing* pThing;
    rdPuppet* pPuppet;
    int trackGUID;
    SithCogMsgType execMsgType;
    float fadeTime;

    fadeTime = sithCogExec_PopFlex(pCog);
    trackNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);

    if ( pThing )
    {
        pPuppet = pThing->renderData.pPuppet;
        if ( pPuppet )
        {
            if ( trackNum >= RDPUPPET_MAX_TRACKS )
            {
                STDLOG_ERROR("Cog %s: can't stop track %d, out of range.\n",
                    pCog->aName,
                    trackNum);
            }

            else if ( fadeTime >= 0.0 )
            {
                trackGUID = pPuppet->aTracks[trackNum].guid;
                if ( sithPuppet_StopKey(pPuppet, trackNum, fadeTime) )
                {
                    if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
                    {
                        execMsgType = pCog->execMsgType;
                        if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                        {
                            sithDSSThing_StopKey(pThing, trackGUID, fadeTime, SITHMESSAGE_SENDTOALL, 0xFFu);
                        }
                    }
                }
            }
            else
            {
                STDLOG_ERROR("Cog %s: fadeTime %g, is illegal.\n",
                    pCog->aName,
                    fadeTime);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: cannot stop puppet track %d, not puppet.\n",
                pCog->aName,
                trackNum);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing to stop keyframe anim on.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingMesh(SithCog* pCog)
{
    int meshNumSrc;
    rdModel3* pModel;
    SithThing* pThing;
    int refNum;
    SithCogMsgType execMsgType;
    int meshNum;

    meshNumSrc = sithCogExec_PopInt(pCog);
    pModel = sithCogExec_PopModel3(pCog);
    meshNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pModel )
        {
            refNum = sithThing_AddSwapEntry(pThing, meshNum, pModel, meshNumSrc);
            sithCogExec_PushInt(pCog, refNum);
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 2);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad model in SetThingMesh.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingMesh.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_RestoreThingMesh(SithCog* pCog)
{
    int refnum;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    refnum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( refnum == -99 )
        {
            sithThing_ResetSwapList(pThing);
        }
        else
        {
            sithThing_RemoveSwapEntry(pThing, refnum);
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in RestoreThingMesh.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingModel(SithCog* pCog)
{
    rdModel3* pModel;
    SithThing* pThing;
    rdModel3* pThingModel;
    int num;
    SithCogMsgType execMsgType;

    pModel = sithCogExec_PopModel3(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: SetThingModel - No thing to set.\n",
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( !pModel )
    {
        STDLOG_ERROR("Cog %s: SetThingModel - No model to set.\n",
            pCog->aName);
        goto error_return;
    }

    pThingModel = pThing->renderData.data.pModel3;
    if ( pThingModel )
    {
        num = pThingModel->num;
    }
    else
    {
        STDLOG_ERROR("Cog %s: SetThingModel - Thing had no model (warning).\n",
            pCog->aName);

        num = -1;
    }

    if ( !sithThing_SetThingModel(pThing, pModel) )
    {
        STDLOG_ERROR("Cog %s: SetThingModel - Failed to set model.\n",
            pCog->aName);
        goto error_return;
    }

    sithCogExec_PushInt(pCog, num);

    if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
    {
        execMsgType = pCog->execMsgType;
        if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
        {
            sithDSSThing_SetModel(pThing, SITHMESSAGE_SENDTOALL);
        }
    }
}

void J3DAPI sithCogFunctionThing_GetThingModel(SithCog* pCog)
{
    SithThing* pThing;
    rdModel3* pModel;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: GetThingModel - No thing to set.",
            pCog->aName);

    error_return:
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( pThing->renderData.type != RD_THING_MODEL3 )
    {
        STDLOG_ERROR("Cog %s: GetThingModel - Thing is not model.",
            pCog->aName);
        goto error_return;
    }

    pModel = pThing->renderData.data.pModel3;
    if ( !pModel )
    {
        STDLOG_ERROR("Cog %s: GetThingModel - No model on thing.",
            pCog->aName);
        goto error_return;
    }

    sithCogExec_PushInt(pCog, pModel->num);
}

void J3DAPI sithCogFunctionThing_SetArmedMode(SithCog* pCog)
{
    unsigned int armedMode;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    armedMode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( armedMode < SITH_PUPPET_NUMARMEDMODES )
        {
            sithPuppet_SetArmedMode(pThing, armedMode);

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithDSSThing_UpdateState(pThing, SITHMESSAGE_SENDTOALL, 0xFFu);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Trying to set invalid armed mode '%d' on thing '%s'.\n",
                pCog->aName,
                armedMode,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Trying to set armed mode on illegal thing.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingFlags(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->flags);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingFlags(SithCog* pCog)
{
    int flags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    flags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && flags )
    {
        pThing->flags |= flags;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot set thing flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ClearThingFlags(SithCog* pCog)
{
    int flags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    flags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && flags )
    {
        pThing->flags &= ~flags;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot clear thing flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_TeleportThing(SithCog* pCog)
{
    SithThing* pSrcThing;
    SithThing* pDestThing;
    SithCogMsgType execMsgType;

    pSrcThing = sithCogExec_PopThing(pCog);
    pDestThing = sithCogExec_PopThing(pCog);
    if ( !pDestThing || !pSrcThing )
    {
        STDLOG_ERROR("Cog %s:Illegal params in TeleportThing.\n",
            pCog->aName);
    }
    else
    {
        if ( pDestThing->attach.flags )
        {
            sithThing_DetachThing(pDestThing);
        }

        memcpy(&pDestThing->orient, &pSrcThing->orient, 0x3Cu);// TODO: do separate orient and pos copy

        sithThing_SetSector(pDestThing, pSrcThing->pInSector, 0);

        if ( pDestThing->moveType == SITH_MT_PHYSICS && (pDestThing->moveInfo.physics.flags & SITH_PF_FLOORSTICK) != 0 )
        {
            sithPhysics_FindFloor(pDestThing, 1);
        }

        if ( pDestThing == sithPlayer_g_pLocalPlayerThing )
        {
            sithCamera_Update(sithCamera_g_pCurCamera);
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Pos(pDestThing, SITHMESSAGE_SENDTOALL, DPSEND_GUARANTEED);// TODO: make separate global var for dpflags and do secure connection
            }
        }
    }
}

void J3DAPI sithCogFunctionThing_SetThingType(SithCog* pCog)
{
    unsigned int type;
    SithThing* pThing;

    type = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( type <= SITH_THING_POLYLINE )
        {
            pThing->type = type;
        }
    }
}

void J3DAPI sithCogFunctionThing_GetCollideType(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->collide.type);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetCollideType(SithCog* pCog)
{
    SithCollideType type;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    type = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (unsigned int)type < 4 )
    {
        pThing->collide.type = type;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot set thing collide type.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_FirstThingInSector(SithCog* pCog)
{
    SithSector* pThing;
    SithThing* pFirstThing;

    pThing = sithCogExec_PopSector(pCog);
    if ( pThing )
    {
        pFirstThing = pThing->pFirstThingInSector;
        if ( pFirstThing )
        {
            sithCogExec_PushInt(pCog, pFirstThing->idx);
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot get first thing in sector.  Invalid sector.\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
        sithCogExec_PushInt(pCog, -1);          // ??? BUG?
    }
}

void J3DAPI sithCogFunctionThing_NextThingInSector(SithCog* pCog)
{
    SithThing* pThing;
    SithThing* pNextThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pNextThing = pThing->pNextThingInSector;
        if ( pNextThing )
        {
            sithCogExec_PushInt(pCog, pNextThing->idx);
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing passed to NextThingInSector.\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_PrevThingInSector(SithCog* pCog)
{
    SithThing* pThing;
    SithThing* pPrevThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pPrevThing = pThing->pPrevThingInSector;
        if ( pPrevThing )
        {
            sithCogExec_PushInt(pCog, pPrevThing->idx);
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing passed to PrevThingInSector()\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetInventoryMinimum(SithCog* pCog)
{
    int bin;
    SithThing* pThing;
    float pCoga;

    bin = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.itemInfo.aBackpackItems[14].typeId )
    {
        pCoga = sithInventory_GetInventoryMinimum(pThing, bin);
        sithCogExec_PushFlex(pCog, pCoga);
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing passed to GetInventoryMinimum.\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_GetInventoryMaximum(SithCog* pCog)
{
    int bin;
    SithThing* pThing;
    float maxval;

    bin = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_PLAYER && pThing->thingInfo.itemInfo.aBackpackItems[14].typeId )
    {
        maxval = sithInventory_GetInventoryMaximum(pThing, bin);
        sithCogExec_PushFlex(pCog, maxval);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing passed to GetInventoryMaximum.\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_PathMovePause(SithCog* pCog)
{
    int bPaused;
    SithThing* pThing;

    bPaused = 0;
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PATH )
    {
        if ( !sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing) )
        {
            SITH_ASSERTREL(sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing));
        }

        bPaused = sithPathMove_PathMovePause(pThing);
    }

    if ( bPaused == 1 )
    {
        sithCogExec_PushInt(pCog, pThing->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetHeadLightIntensity(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    rdVector3 color;

    sithCogExec_PopVector(pCog, &color);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && ((type = pThing->type, type == SITH_THING_ACTOR) || type == SITH_THING_PLAYER) )
    {
        pThing->thingInfo.actorInfo.headLightIntensity.red = color.x;
        pThing->thingInfo.actorInfo.headLightIntensity.green = color.y;
        pThing->thingInfo.actorInfo.headLightIntensity.blue = color.z;
        pThing->thingInfo.actorInfo.headLightIntensity.alpha = 0.0;
        sithCogExec_PushVector(pCog, &color);
    }
    else
    {
        color.blue = -1.0;
        color.green = -1.0;
        color.red = -1.0;
        sithCogExec_PushVector(pCog, &color);
    }
}

void J3DAPI sithCogFunctionThing_GetHeadLightIntensity(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    rdVector3 color;

    sithCogExec_PopVector(pCog, &color);        // TODO: ???? probably bug
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && ((type = pThing->type, type == SITH_THING_ACTOR) || type == SITH_THING_PLAYER) )
    {
        //*(rdVector3*)&color.red = *(rdVector3*)&pThing->thingInfo.actorInfo.headLightIntensity.red;// TODO: memcpy or rdVector_Copy3
        color = *(rdVector3*)&pThing->thingInfo.actorInfo.headLightIntensity;
        sithCogExec_PushVector(pCog, &color);
    }
    else
    {
        color.blue = -1.0;
        color.green = -1.0;
        color.red = -1.0;
        sithCogExec_PushVector(pCog, &color);
    }
}

void J3DAPI sithCogFunctionThing_IsThingVisible(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->renderFrame + 1 >= (unsigned int)sithMain_g_frameNumber);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad parameters in IsThingVisible()\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_PathMoveResume(SithCog* pCog)
{
    int res;
    SithThing* pThing;

    res = 0;
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PATH )
    {
        if ( !sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing) )
        {
            SITH_ASSERTREL(sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing));
        }

        res = sithPathMove_PathMoveResume(pThing);
    }

    if ( res == 1 )
    {
        sithCogExec_PushInt(pCog, pThing->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingCurLightMode(SithCog* pCog)
{
    int mode;
    SithThing* pThing;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->renderData.lightMode = mode;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingCurLightMode().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingCurLightMode(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->renderData.lightMode);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingCurLightMode().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetActorExtraSpeed(SithCog* pCog)
{
    SithThing* pThing;
    float speed;

    speed = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->thingInfo.actorInfo.extraSpeed = speed;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetActorExtraSpeed().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingTemplate(SithCog* pCog)
{
    SithThing* pThing;
    const SithThing* pTemplate;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingTemplate().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    pTemplate = pThing->pTemplate;
    if ( !pTemplate )
    {
        STDLOG_ERROR("Cog %s: No template for thing in GetThingTemplate().\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    sithCogExec_PushInt(pCog, pTemplate->idx);
}

void J3DAPI sithCogFunctionThing_SetLifeleft(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    float secLeft;

    secLeft = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( secLeft >= 0.0 )
        {
            pThing->msecLifeLeft = (__int64)(secLeft * 1000.0);
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 2);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Seconds must be positive for SetLifeleft().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetLifeleft().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetLifeleft(SithCog* pCog)
{
    SithThing* pThing;
    float secLeft;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        secLeft = (double)pThing->msecLifeLeft * 0.001;
        sithCogExec_PushFlex(pCog, secLeft);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetLifeleft().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingThrust(SithCog* pCog)
{
    int bValidThrust;
    SithThing* pThing;
    rdVector3* pThrust;
    rdVector3 thrust;

    bValidThrust = sithCogExec_PopVector(pCog, &thrust);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        if ( bValidThrust )
        {
            pThrust = &pThing->moveInfo.physics.thrust;
            sithCogExec_PushVector(pCog, pThrust);
            pThrust->x = thrust.x;
            pThrust->y = thrust.y;
            pThrust->z = thrust.z;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad vector in SetThingThrust().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing or no physics in SetThingThrust().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingThrust(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        sithCogExec_PushVector(pCog, &pThing->moveInfo.physics.thrust);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing or no physics in GetThingThrust().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_AmputateJoint(SithCog* pCog)
{
    unsigned int joint;
    SithThing* pThing;

    joint = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( !pThing->renderData.data.pModel3 )
        {
            SITH_ASSERTREL(pThing->renderData.data.pModel3 != ((void*)0));
        }

        if ( joint > pThing->renderData.data.pModel3->numHNodes )
        {
            STDLOG_ERROR("Cog %s: Bad joint passed to AmputateJoint().\n",
                pCog->aName);
        }
        else
        {
            pThing->renderData.paJointAmputationFlags[joint] = 1;
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in AmputateJoint().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetActorWeapon(SithCog* pCog)
{
    SithThing* pWeapon;
    SithThing* pActor;
    SithThingType type;

    pWeapon = sithCogExec_PopTemplate(pCog);
    pActor = sithCogExec_PopThing(pCog);
    if ( pActor && ((type = pActor->type, type == SITH_THING_ACTOR) || type == SITH_THING_PLAYER) )
    {
        pActor->thingInfo.actorInfo.pWeaponTemplate = pWeapon;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing or weapon in SetActorWeapon().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetActorWeapon(SithCog* pCog)
{
    SithThing* pActor;
    SithThingType type;
    SithThing* pWeaponTemplate;

    pActor = sithCogExec_PopThing(pCog);
    if ( pActor && ((type = pActor->type, type == SITH_THING_ACTOR) || type == SITH_THING_PLAYER) )
    {
        pWeaponTemplate = pActor->thingInfo.actorInfo.pWeaponTemplate;
        if ( pWeaponTemplate )
        {
            sithCogExec_PushInt(pCog, pWeaponTemplate->idx);
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing or weapon in GetActorWeapon().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetPhysicsFlags(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        sithCogExec_PushInt(pCog, pThing->moveInfo.physics.flags);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetPhysicsFlags(SithCog* pCog)
{
    int physflags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    physflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && physflags && pThing->moveType == SITH_MT_PHYSICS )
    {
        pThing->moveInfo.physics.flags |= physflags;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot set Physics flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ClearPhysicsFlags(SithCog* pCog)
{
    int physflags;
    SithThing* pThing;

    physflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && physflags && pThing->moveType == SITH_MT_PHYSICS )
    {
        pThing->moveInfo.physics.flags &= ~physflags;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot clear Physics flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ParseArg(SithCog* pCog)
{
    const char* pArgs;
    SithThing* pThing;
    unsigned int argNum;
    StdConffileArg* pArg;

    pArgs = sithCogExec_PopString(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pArgs
        && pThing
        && (strncpy(std_g_genBuffer, pArgs, 2047u),
            std_g_genBuffer[2047] = 0,
            !stdConffile_ReadArgsFromStr(std_g_genBuffer)) )
    {
        argNum = 0;
        if ( stdConffile_g_entry.numArgs )
        {
            pArg = stdConffile_g_entry.aArgs;
            do
            {
                if ( sithThing_ParseArg(pArg, sithWorld_g_pCurrentWorld, pThing) )
                {
                    STDLOG_ERROR("Cog %s: Argument %s=%s parse failed.\n",
                        pCog->aName,
                        pArg->argName,
                        pArg->argValue);
                }

                ++argNum;
                ++pArg;
            } while ( argNum < stdConffile_g_entry.numArgs );
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad arguments to ParseArg verb.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingRotVel(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vel;

    sithCogExec_PopVector(pCog, &vel);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        pThing->moveInfo.physics.angularVelocity.x = vel.red;
        pThing->moveInfo.physics.angularVelocity.y = vel.green;
        pThing->moveInfo.physics.angularVelocity.z = vel.blue;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 1);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing, or non-physics thing in SetRotVel.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingRotVel(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        sithCogExec_PushVector(pCog, &pThing->moveInfo.pathMovement.vecDeltaPos);// TODO: set union memeber to angularVelocity
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing, or non-physics thing in SetRotVel.\n",
            pCog->aName);
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetRotThrust(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vec;

    sithCogExec_PopVector(pCog, &vec);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        pThing->moveInfo.physics.rotThrust.x = vec.red;
        pThing->moveInfo.physics.rotThrust.y = vec.green;
        pThing->moveInfo.physics.rotThrust.z = vec.blue;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 1);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing, or non-physics thing in SetRotThrust.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetRotThrust(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        sithCogExec_PushVector(pCog, &pThing->moveInfo.physics.rotThrust);
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing, or non-physics thing in SetRotThrust.\n",
            pCog->aName);

        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetThingLook(SithCog* pCog)
{
    int bValidVec;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 look;

    bValidVec = sithCogExec_PopVector(pCog, &look);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && bValidVec == 1 )
    {
        rdVector_Normalize3Acc(&look);
        rdMatrix_BuildFromLook34(&pThing->orient, &look);
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 1);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Could not set thing orientation from look vector for SetThingLook().\n",
            pCog->aName);
    }
}

int J3DAPI sithCogFunctionThing_SetThingHeadLook(SithThing* pThing, const rdVector3* pLook)
{
    int result;
    SithThingType type;
    double v5;
    double v6;
    double v7;
    double yaw;
    float dot;
    rdVector3 dir;
    float pitch;

    if ( !pThing )
    {
        return 0;
    }

    result = (int)pLook;
    if ( !pLook )
    {
        return result;
    }

    type = pThing->type;
    if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
    {
        if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_CANROTATEHEAD) != 0 )
        {
            v5 = pLook->y - pThing->pos.y;
            v6 = pLook->z - pThing->pos.z;
            dir.x = pLook->x - pThing->pos.x;
            dir.y = v5;
            dir.z = v6;
            rdVector_Normalize3Acc(&dir);

            v7 = stdMath_ArcSin3(dir.z);
            pitch = v7;
            if ( v7 < pThing->thingInfo.actorInfo.minHeadPitch )
            {
                pitch = pThing->thingInfo.actorInfo.minHeadPitch;
            }

            else if ( pitch > (double)pThing->thingInfo.actorInfo.maxHeadPitch )
            {
                pitch = pThing->thingInfo.actorInfo.maxHeadPitch;
            }

            dir.z = 0.0;
            rdVector_Normalize3Acc(&dir);
            dot = rdVector_Dot3(&pThing->orient.lvec, &dir);
            yaw = 90.0 - stdMath_ArcSin3(dot);

            if ( rdVector_Dot3(&pThing->orient.rvec, &dir) > 0 )
            {
                yaw = -yaw;
            }

            if ( yaw < -35.0 )
            {
                yaw = -35.0;
            }

            else if ( yaw > 35.0 )
            {
                yaw = 35.0;
            }

            if ( pitch != pThing->thingInfo.actorInfo.headPYR.pitch || yaw != pThing->thingInfo.actorInfo.headPYR.yaw )
            {
                pThing->thingInfo.actorInfo.headPYR.yaw = yaw;
                pThing->thingInfo.actorInfo.headPYR.pitch = pitch;
                sithActor_SetHeadPYR(pThing, &pThing->thingInfo.actorInfo.headPYR);

                return 1;
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: illegal attempt to set thing %s head orientation: thing is not an actor.\n",
                pThing->aName,
                0);
            return 0;
        }
    }
    else
    {
        return 0;
    }

    return result;
}

void J3DAPI sithCogFunctionThing_SetThingHeadLookPos(SithCog* pCog)
{
    int bValidVec;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 look;

    bValidVec = sithCogExec_PopVector(pCog, &look);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( bValidVec == 1 )
        {
            if ( !sithCogFunctionThing_SetThingHeadLook(pThing, &look) )
            {
                STDLOG_ERROR("Cog %s: illegal attempt to set thing %s head orientation SetThingHeadLook().\n",
                    pCog->aName,
                    pThing->aName);
            }

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 1);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad look vector passed for thing %s in SetThingHeadLook().\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing reference passed to SetThingHeadLook().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingHeadLookThing(SithCog* pCog)
{
    SithThing* pLookThing;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    pLookThing = sithCogExec_PopThing(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pLookThing )
        {
            if ( !sithCogFunctionThing_SetThingHeadLook(pThing, &pLookThing->pos) )
            {
                STDLOG_ERROR("Cog %s: illegal attempt to set thing %s head orientation SetThingHeadLook().\n",
                    pCog->aName,
                    pThing->aName);
            }

            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 1);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad look vector passed for thing %s in SetThingHeadLook().\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing reference passed to SetThingHeadLook().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_IsThingCrouching(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || pThing->moveType != SITH_MT_PHYSICS )
    {
        sithCogExec_PushInt(pCog, -1);
    }

    if ( (pThing->moveInfo.physics.flags & SITH_PF_CROUCHING) != 0 )
    {
        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_GetThingClassCog(SithCog* pCog)
{
    SithThing* pThing;
    SithCog* pThingCog;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pThingCog = pThing->pCog) != 0 )
    {
        sithCogExec_PushInt(pCog, pThingCog->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingClassCog(SithCog* pCog)
{
    SithCog* pThingCog;
    SithThing* pThing;

    pThingCog = sithCogExec_PopCog(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: No thing, in SetThingClassCog.\n",
            pCog->aName);
    }

    else if ( !pThingCog )
    {
        STDLOG_ERROR("Cog %s: No cog, in SetThingClassCog.\n",
            pCog->aName);
    }
    else
    {
        pThing->pCog = pThingCog;
    }
}

void J3DAPI sithCogFunctionThing_GetThingCaptureCog(SithCog* pCog)
{
    SithThing* pThing;
    SithCog* pCaptureCog;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pCaptureCog = pThing->pCaptureCog) != 0 )
    {
        sithCogExec_PushInt(pCog, pCaptureCog->idx);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingCaptureCog(SithCog* pCog)
{
    SithCog* pCaptureCog;
    SithThing* pThing;

    pCaptureCog = sithCogExec_PopCog(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pCaptureCog )
        {
            pThing->pCaptureCog = pCaptureCog;
        }
        else
        {
            STDLOG_ERROR("Cog %s: No cog, in SetThingCaptureCog.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing, in SetThingCaptureCog.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingRespawn(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->type == SITH_THING_ITEM )
    {
        sithCogExec_PushFlex(pCog, pThing->thingInfo.itemInfo.secRespawnInterval);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Illegal thing, in GetThingRespawn.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingSignature(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->signature);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetThingAttachFlags(SithCog* pCog)
{
    int attflags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    attflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && attflags )
    {
        pThing->attach.flags |= attflags;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot set thing attach flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ClearThingAttachFlags(SithCog* pCog)
{
    int attflags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    attflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && attflags )
    {
        pThing->attach.flags &= ~attflags;
        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 1u);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Cannot clear thing attach flags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetParticleSize(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.particleInfo.size);
            return;
        }

        STDLOG_ERROR("Cog %s: Cannot get thing Particle size for non particle things.\n",
            pCog->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetParticleSize.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_SetParticleSize(SithCog* pCog)
{
    SithThing* pThing;
    float size;

    size = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            pThing->thingInfo.particleInfo.size = size;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Cannot set thing particle size for non particle things.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetParticleSize.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetParticleGrowthSpeed(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.particleInfo.growthSpeed);
            return;
        }

        STDLOG_ERROR("Cog %s: Cannot get thing particle GrowthSpeed for non particle things.\n",
            pCog->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetParticleGrowthSpeed.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_SetParticleGrowthSpeed(SithCog* pCog)
{
    SithThing* pThing;
    float speed;

    speed = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            pThing->thingInfo.particleInfo.growthSpeed = speed;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Cannot set thing particle GrowthSpeed for non particle things.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetParticleGrowthSpeed.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetParticleTimeoutRate(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.particleInfo.timeoutRate);
            return;
        }

        STDLOG_ERROR("Cog %s: Cannot get thing particle TimeoutRate for non particle things.\n",
            pCog->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetParticleTimeoutRate.\n",
            pCog->aName);
    }

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_SetParticleTimeoutRate(SithCog* pCog)
{
    SithThing* pThing;
    float timeoutRate;

    timeoutRate = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PARTICLE )
        {
            pThing->thingInfo.particleInfo.timeoutRate = timeoutRate;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Cannot set thing particle TimeoutRate for non particle things.\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetParticleTimeoutRate.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetTypeFlags(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        switch ( pThing->type )
        {
            case SITH_THING_ACTOR:
            case SITH_THING_WEAPON:
            case SITH_THING_ITEM:
            case SITH_THING_EXPLOSION:
            case SITH_THING_PLAYER:
            case SITH_THING_PARTICLE:
                sithCogExec_PushInt(pCog, pThing->thingInfo.actorInfo.flags);
                break;

            default:
                STDLOG_ERROR("Cog %s: Cannot get thing type flags for this type of thing.\n",
                    pCog->aName);
                sithCogExec_PushInt(pCog, -1);
                break;
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetTypeFlags.\n",
            pCog->aName);

        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_SetTypeFlags(SithCog* pCog)
{
    int typeflags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    typeflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && typeflags )
    {
        switch ( pThing->type )
        {
            case SITH_THING_ACTOR:
            case SITH_THING_WEAPON:
            case SITH_THING_ITEM:
            case SITH_THING_EXPLOSION:
            case SITH_THING_PLAYER:
            case SITH_THING_PARTICLE:
                pThing->thingInfo.actorInfo.flags |= typeflags;
                break;

            default:
                STDLOG_ERROR("Cog %s: Cannot set thing type flags for this type of thing.\n",
                    pCog->aName);
                break;
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetTypeFlags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_ClearTypeFlags(SithCog* pCog)
{
    int typeflags;
    SithThing* pThing;
    SithCogMsgType execMsgType;

    typeflags = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && typeflags )
    {
        switch ( pThing->type )
        {
            case SITH_THING_ACTOR:
            case SITH_THING_WEAPON:
            case SITH_THING_ITEM:
            case SITH_THING_EXPLOSION:
            case SITH_THING_PLAYER:
            case SITH_THING_PARTICLE:
                pThing->thingInfo.actorInfo.flags &= ~typeflags;
                break;

            default:
                STDLOG_ERROR("Cog %s: Cannot clear thing type flags for this type of thing.\n",
                    pCog->aName);
                break;
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 2);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in ClearTypeFlags.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_TakeItem(SithCog* pCog)
{
    SithThing* pThing;
    SithThing* pItem;

    pThing = sithCogExec_PopThing(pCog);
    pItem = sithCogExec_PopThing(pCog);
    if ( pItem && pThing && pItem->type == SITH_THING_ITEM )
    {
        sithItem_SetItemTaken(pItem, pThing, 0);
    }
}

void J3DAPI sithCogFunctionThing_HasLOS(SithCog* pCog)
{
    SithThing* pTarget;
    SithThing* pViewer;

    pTarget = sithCogExec_PopThing(pCog);
    pViewer = sithCogExec_PopThing(pCog);
    if ( pViewer && pTarget )
    {
        if ( sithCollision_HasLOS(pViewer, pTarget, 0) )
        {
            sithCogExec_PushInt(pCog, 1);
        }
        else
        {
            sithCogExec_PushInt(pCog, 0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in HasLOS.\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetFireOffset(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushVector(pCog, &pThing->thingInfo.actorInfo.fireOffset);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetFireOffset.\n",
            pCog->aName);
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetFireOffset(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3* pFireOffset;
    rdVector3 offset;

    sithCogExec_PopVector(pCog, &offset);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pFireOffset = &pThing->thingInfo.actorInfo.fireOffset;
        pFireOffset->x = offset.x;
        pFireOffset->y = offset.y;
        pFireOffset->z = offset.z;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetFireOffset.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingUserData(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->userval);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingUserData.\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingUserData(SithCog* pCog)
{
    SithThing* pThing;
    float userval;

    userval = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->userval = userval;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingUserData.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingCollideSize(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->collide.size);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingCollideSize.\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingCollideSize(SithCog* pCog)
{
    SithThing* pThing;
    float size;

    size = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->collide.size = size;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingCollideSize.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMoveSize(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->collide.movesize);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingMoveSize.\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingMoveSize(SithCog* pCog)
{
    SithThing* pThing;
    float movesize;

    movesize = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pThing->collide.movesize = movesize;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingMoveSize.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMass(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            sithCogExec_PushFlex(pCog, pThing->moveInfo.physics.mass);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in GetThingMass.\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, 0.0);
        }
    }
}

void J3DAPI sithCogFunctionThing_SetThingMass(SithCog* pCog)
{
    SithThing* pThing;
    SithCogMsgType execMsgType;
    float mass;

    mass = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            pThing->moveInfo.physics.mass = mass;
            if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
            {
                execMsgType = pCog->execMsgType;
                if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
                {
                    sithThing_SyncThing(pThing, 2);
                }
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in SetThingMass.\n",
                pCog->aName);
        }
    }
}

void J3DAPI sithCogFunctionThing_SyncThingPos(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithThing_SyncThing(pThing, 1);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SyncThingPos().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SyncThingAttachment(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithDSSThing_Attachment(pThing, SITHMESSAGE_SENDTOALL, 0xFFu, 0);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SyncThingAttachment().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SyncThingState(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithThing_SyncThing(pThing, 2);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SyncThingState().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetMajorMode(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->pPuppetClass && pThing->renderData.pPuppet )
        {
            sithCogExec_PushInt(pCog, pThing->pPuppetState->majorMode);
            return;
        }

        STDLOG_ERROR("Cog %s: No puppet on thing %s for GetMajorMode().\n",
            pCog->aName,
            pThing->aName);
    }
    else
    {
        STDLOG_ERROR("Cog %s: No thing in GetMajorMode().\n",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, -1);
}

void J3DAPI sithCogFunctionThing_SetThingPosEx(SithCog* pCog)
{
    SithSector* pSector;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 vecPos;

    pSector = sithCogExec_PopSector(pCog);
    sithCogExec_PopVector(pCog, &vecPos);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pSector )
    {
        pSector = sithSector_FindSectorAtPos(sithWorld_g_pCurrentWorld, &vecPos);
    }

    if ( pThing )
    {
        pThing->pos.x = vecPos.x;
        pThing->pos.y = vecPos.y;
        pThing->pos.z = vecPos.z;
        sithThing_SetSector(pThing, pSector, 0);

        if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->moveInfo.physics.flags & SITH_PF_FLOORSTICK) != 0 )
        {
            sithPhysics_FindFloor(pThing, 1);
        }

        if ( pThing == sithPlayer_g_pLocalPlayerThing )
        {
            sithCamera_Update(sithCamera_g_pCurCamera);
        }

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithDSSThing_Pos(pThing, SITHMESSAGE_SENDTOALL, DPSEND_GUARANTEED);// TODO: make separate global var for dpflags and do secure connection
            }
        }

        sithCogExec_PushInt(pCog, 1);
    }
    else
    {
        sithCogExec_PushInt(pCog, 0);
    }
}

void J3DAPI sithCogFunctionThing_GetThingGuid(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushInt(pCog, pThing->guid);
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetGuidThing(SithCog* pCog)
{
    int guid;
    SithThing* pThing;

    guid = sithCogExec_PopInt(pCog);
    pThing = sithThing_GetGuidThing(guid);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Invalid GUID in GetGuidThing.\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        sithCogExec_PushInt(pCog, pThing->idx);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxVel(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            sithCogExec_PushFlex(pCog, pThing->moveInfo.pathMovement.curOrient.dvec.y);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in GetThingMaxVel.\n",
                pCog->aName);

            sithCogExec_PushFlex(pCog, 0.0);
        }
    }
}

void J3DAPI sithCogFunctionThing_SetThingMaxVel(SithCog* pCog)
{
    SithThing* pThing;
    float maxSpeed;

    maxSpeed = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            pThing->moveInfo.physics.maxVelocity = maxSpeed;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in SetThingMaxVel.\n",
                pCog->aName);
        }
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxAngVel(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            sithCogExec_PushFlex(pCog, pThing->moveInfo.physics.maxRotationVelocity);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in GetThingMaxAngVel.\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, 0.0);
        }
    }
}

void J3DAPI sithCogFunctionThing_SetThingMaxAngVel(SithCog* pCog)
{
    SithThing* pThing;
    float maxRotSpeed;

    maxRotSpeed = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS )
        {
            pThing->moveInfo.physics.maxRotationVelocity = maxRotSpeed;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Non physics thing in SetThingMaxAngVel.\n",
                pCog->aName);
        }
    }
}

void J3DAPI sithCogFunctionThing_SetJointAngle(SithCog* pCog)
{
    int jointNum;
    SithThing* pThing;
    SithThingType type;
    SithPuppetClass* pPuppet;
    rdVector3* apTweakedAngles;
    int nodeNum;
    float angle;

    angle = sithCogExec_PopFlex(pCog);
    jointNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type != SITH_THING_ACTOR && type != SITH_THING_PLAYER && type != SITH_THING_CORPSE )
        {
            SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_ACTOR) || (pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_CORPSE)));
        }

        pPuppet = pThing->pPuppetClass;
        if ( pPuppet )
        {
            if ( pThing->renderData.type == RD_THING_MODEL3 )
            {
                apTweakedAngles = pThing->renderData.apTweakedAngles;
                if ( apTweakedAngles )
                {
                    nodeNum = pPuppet->aJoints[jointNum];
                    if ( nodeNum >= 0 && nodeNum <= (signed int)(pThing->renderData.data.pModel3->numHNodes - 1) )
                    {
                        apTweakedAngles[nodeNum].pitch = angle;
                    }
                }
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetJointAngle.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetJointAngle(SithCog* pCog)
{
    int jointNum;
    SithThing* pThing;
    SithThingType type;
    SithPuppetClass* pPuppetClass;
    rdVector3* apTweakedAngles;
    int nodeNum;
    float val;

    val = -1.0;
    jointNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type != SITH_THING_ACTOR && type != SITH_THING_PLAYER && type != SITH_THING_CORPSE )
        {
            SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_ACTOR) || (pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_CORPSE)));
        }

        pPuppetClass = pThing->pPuppetClass;
        if ( pPuppetClass )
        {
            if ( pThing->renderData.type == RD_THING_MODEL3 )
            {
                apTweakedAngles = pThing->renderData.apTweakedAngles;
                if ( apTweakedAngles )
                {
                    nodeNum = pPuppetClass->aJoints[jointNum];
                    if ( nodeNum >= 0 && nodeNum <= (signed int)(pThing->renderData.data.pModel3->numHNodes - 1) )
                    {
                        val = apTweakedAngles[nodeNum].pitch;
                    }
                }
            }
        }

        sithCogExec_PushFlex(pCog, val);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetJointAngle.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetMaxHeadPitch(SithCog* pCog)
{
    SithThing* pThing;
    float maxPitch;

    maxPitch = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHeadPitch);
        pThing->thingInfo.actorInfo.maxHeadPitch = maxPitch;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetMaxHeadPitch.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetMinHeadPitch(SithCog* pCog)
{
    SithThing* pThing;
    float minPitch;

    minPitch = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.minHeadPitch);
        pThing->thingInfo.actorInfo.minHeadPitch = minPitch;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetMinHeadPitch.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadPitch(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHeadPitch);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in GetThingMaxHeadPitch().\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, -1.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in GetThingMaxHeadPitch().\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMinHeadPitch(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.minHeadPitch);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in GetThingMinHeadPitch().\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, -1.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in GetThingMinHeadPitch().\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetMaxHeadYaw(SithCog* pCog)
{
    SithThing* pThing;
    float maxYaw;

    maxYaw = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHeadYaw);
        pThing->thingInfo.actorInfo.maxHeadYaw = maxYaw;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetMaxHeadYaw.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadYaw(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHeadYaw);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in GetThingMaxHeadYaw().\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, -1.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in GetThingMaxHeadYaw().\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_InterpolatePYR(SithCog* pCog)
{
    float angle;
    rdVector3 look;
    rdVector3 axisX;
    rdVector3 pyr1;
    rdVector3 axisY;
    rdVector3 axisZ;
    rdVector3 pyr2;
    rdMatrix34 orient;

    angle = sithCogExec_PopFlex(pCog);
    sithCogExec_PopVector(pCog, &axisZ);
    sithCogExec_PopVector(pCog, &axisY);
    sithCogExec_PopVector(pCog, &axisX);

    look.x = axisY.x - axisX.x;
    look.y = axisY.y - axisX.y;
    look.z = axisY.z - axisX.z;
    rdVector_Normalize3Acc(&look);
    rdMatrix_BuildFromLook34(&orient, &look);
    rdMatrix_ExtractAngles34(&orient, &pyr1);

    look.x = axisZ.x - axisX.x;
    look.y = axisZ.y - axisX.y;
    look.z = axisZ.z - axisX.z;
    rdVector_Normalize3Acc(&look);
    rdMatrix_BuildFromLook34(&orient, &look);
    rdMatrix_ExtractAngles34(&orient, &pyr2);

    look.x = (pyr2.x - pyr1.x) * angle + pyr1.x;
    look.y = (pyr2.y - pyr1.y) * angle + pyr1.y;
    look.z = (pyr2.z - pyr1.z) * angle + pyr1.z;
    sithCogExec_PushVector(pCog, &look);
}

void J3DAPI sithCogFunctionThing_GetThingLVecPYR(SithCog* pCog)
{
    SithThing* pThing;
    rdVector3 pyr;
    rdMatrix34 orient;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        memcpy(&orient, &pThing->orient, sizeof(orient));
        rdMatrix_ExtractAngles34(&orient, &pyr);
        sithCogExec_PushVector(pCog, &pyr);
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
    }
}

void J3DAPI sithCogFunctionThing_SetThingLVec(SithCog* pCog)
{
    int bVec;
    SithThing* pThing;
    SithCogMsgType execMsgType;
    rdVector3 lvec;
    rdMatrix34 orient;

    bVec = sithCogExec_PopVector(pCog, &lvec);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && bVec == 1 )
    {
        rdMatrix_BuildRotate34(&orient, &lvec);
        rdVector_Normalize3Acc(&orient.lvec);
        rdMatrix_BuildFromLook34(&pThing->orient, &orient.lvec);

        if ( (pCog->flags & SITHCOG_NOSYNC) == 0 )
        {
            execMsgType = pCog->execMsgType;
            if ( execMsgType != SITHCOG_MSG_STARTUP && execMsgType != SITHCOG_MSG_SHUTDOWN )
            {
                sithThing_SyncThing(pThing, 1);
            }
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Could not set thing orientation from look vector for SetThingLVec().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetHeadPYR(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    double v4;
    rdVector3 pyr;

    sithCogExec_PopVector(pCog, &pyr);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_ACTOR || type == SITH_THING_PLAYER )
        {
            if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_CANROTATEHEAD) != 0 )
            {
                if ( pyr.pitch < (double)pThing->thingInfo.actorInfo.minHeadPitch )
                {
                    pyr.pitch = pThing->thingInfo.actorInfo.minHeadPitch;
                }

                else if ( pyr.pitch > (double)pThing->thingInfo.actorInfo.maxHeadPitch )
                {
                    pyr.pitch = pThing->thingInfo.actorInfo.maxHeadPitch;
                }

                v4 = -pThing->thingInfo.actorInfo.maxHeadYaw;
                if ( pyr.yaw < v4 )
                {
                    pyr.yaw = v4;
                }

                else if ( pyr.yaw > (double)pThing->thingInfo.actorInfo.maxHeadYaw )
                {
                    pyr.yaw = pThing->thingInfo.actorInfo.maxHeadYaw;
                }

                sithActor_SetHeadPYR(pThing, &pyr);
            }
            else
            {
                STDLOG_ERROR("Cog %s: Thing %s cannot change head orientation in SetHeadPYR.\n",
                    pCog->aName,
                    pThing->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s is not an actor or player in SetHeadPYR.\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetHeadPYR.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingAirDrag(SithCog* pCog)
{
    SithThing* pThing;
    float drag;

    drag = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->moveType == SITH_MT_PHYSICS )
    {
        pThing->moveInfo.physics.airDrag = drag;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingAirDrag.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingJointPos(SithCog* pCog)
{
    unsigned int jointNum;
    SithThing* pThing;

    jointNum = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->renderData.pPuppet )
    {
        if ( jointNum < pThing->renderData.data.pModel3->numHNodes )
        {
            sithCogExec_PushVector(pCog, &pThing->renderData.paJointMatrices[jointNum].dvec);
        }
        else
        {
            sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
            STDLOG_ERROR("Cog %s: Invalid joint number in GetThingJointPos.\n",
                pCog->aName);
        }
    }
    else
    {
        sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
        STDLOG_ERROR("Cog %s: Bad thing in GetThingJointPos.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_IsThingModelName(SithCog* pCog)
{
    const char* pModelName;
    SithThing* pThing;
    const char* pName;

    pModelName = sithCogExec_PopString(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pName = pThing->renderData.data.pModel3->aName) != 0 )
    {
        if ( pModelName )
        {
            if ( !_strcmpi(pName, pModelName) )
            {
                sithCogExec_PushInt(pCog, 1);
                return;
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad args in IsThingModelName().",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad Thing in IsThingModelName().",
            pCog->aName);
    }

    sithCogExec_PushInt(pCog, 0);
}

void J3DAPI sithCogFunctionThing_GetMeshByName(SithCog* pCog)
{
    const char* pMeshName;
    SithThing* pThing;
    int meshNum;

    pMeshName = sithCogExec_PopString(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        meshNum = sithThing_GetThingMeshIndex(pThing, pMeshName);
        sithCogExec_PushInt(pCog, meshNum);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad Thing in GetMeshByName().",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_GetNodeByName(SithCog* pCog)
{
    const char* pNodeName;
    SithThing* pThing;
    int nodeNum;

    pNodeName = sithCogExec_PopString(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        nodeNum = sithThing_GetThingJointIndex(pThing, pNodeName);
        sithCogExec_PushInt(pCog, nodeNum);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad Thing in GetNodeByName().",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_AttachThingToThingMesh(SithCog* pCog)
{
    int meshNum;
    SithThing* pTemplate;
    SithThing* pAttachThing;
    SithThing* pThing;

    meshNum = sithCogExec_PopInt(pCog);
    pTemplate = sithCogExec_PopTemplate(pCog);
    pAttachThing = sithCogExec_PopThing(pCog);
    if ( pAttachThing && pAttachThing->renderData.pPuppet && pAttachThing->renderData.data.pModel3 )
    {
        if ( pTemplate )
        {
            if ( meshNum >= 0 )
            {
                pThing = sithThing_CreateThingAtPos(
                    pTemplate,
                    &pAttachThing->pos,
                    &pAttachThing->orient,
                    pAttachThing->pInSector,
                    0);
                if ( pThing )
                {
                    if ( pThing->type == SITH_THING_EXPLOSION )
                    {
                        pThing->pParent = pAttachThing;
                    }

                    sithThing_AttachThingToThingMesh(pThing, pAttachThing, meshNum);
                    sithCogExec_PushInt(pCog, pThing->idx);
                }
                else
                {
                    sithCogExec_PushInt(pCog, -1);
                    STDLOG_ERROR("Cog %s: Unable to create attached thing in AttachThingToThingMesh().\n",
                        pCog->aName);
                }
            }
            else
            {
                sithCogExec_PushInt(pCog, -1);
                STDLOG_ERROR("Cog %s: Bad mesh number in AttachThingToThingMesh().\n",
                    pCog->aName);
            }
        }
        else
        {
            sithCogExec_PushInt(pCog, -1);
            STDLOG_ERROR("Cog %s: Bad template in AttachThingToThingMesh().\n",
                pCog->aName);
        }
    }
    else
    {
        sithCogExec_PushInt(pCog, -1);
        STDLOG_ERROR("Cog %s: Bad thing in AttachThingToThingMesh().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_DetachThingMesh(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Cog %s: Bad thing reference in DetachThingMesh().\n",
            pCog->aName);
    }
    else
    {
        sithThing_DestroyThing(pThing);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxRotVel(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxRotVelocity);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in GetThingMaxRotVel().\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, -1.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in GetThingMaxRotVel().\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingMaxRotVel(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    float vel;

    vel = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            pThing->thingInfo.actorInfo.maxRotVelocity = vel;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in SetThingMaxRotVel().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in SetThingMaxRotVel().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingMaxHeadVel(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushFlex(pCog, pThing->thingInfo.actorInfo.maxHeadVelocity);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in GetThingMaxHeadVel().\n",
                pCog->aName);
            sithCogExec_PushFlex(pCog, -1.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in GetThingMaxHeadVel().\n",
            pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_SetThingMaxHeadVel(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;
    float vel;

    vel = sithCogExec_PopFlex(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            pThing->thingInfo.actorInfo.maxHeadVelocity = vel;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad thing type in SetThingMaxHeadVel().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Ain't no thing in SetThingMaxHeadVel().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetPuppetModeFPS(SithCog* pCog)
{
    unsigned int submode;
    unsigned int majorMode;
    SithThing* pThing;
    SithPuppetClass* pPuppetClass;
    int v7;
    rdKeyframe* pKfTrack;
    float fps;

    fps = sithCogExec_PopFlex(pCog);
    submode = sithCogExec_PopInt(pCog);
    majorMode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing || (pPuppetClass = pThing->pPuppetClass) == 0 )
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetPuppetModeFPS().\n", pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
        return;
    }

    if ( majorMode >= SITH_PUPPET_NUMARMEDMODES * SITH_PUPPET_NUMMOVEMODES )
    {
        STDLOG_ERROR("Cog %s: Bad major mode number in SetPuppetModeFPS().\n", pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
        return;
    }

    if ( submode >= SITH_PUPPET_NUMSUBMODES )
    {
        STDLOG_ERROR("Cog %s: Bad mode number in SetPuppetModeFPS().\n", pCog->aName);
        sithCogExec_PushFlex(pCog, -1.0);
        return;
    }

    pKfTrack = pPuppetClass->aModes[majorMode][submode].pKeyframe;
    if ( pKfTrack )
    {
        sithCogExec_PushFlex(pCog, pKfTrack->fps);
        pKfTrack->fps = fps;
        return;
    }

    STDLOG_ERROR("Cog %s: THING %s doesn't possess Submode %d for SetPuppetModeFPS().\n",
        pCog->aName,
        pThing->aName,
        submode);

    sithCogExec_PushFlex(pCog, -1.0);
}

void J3DAPI sithCogFunctionThing_ResetThing(SithCog* pCog)
{
    SithThing* pThing;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && pThing->renderData.pPuppet )
    {
        sithPhysics_ResetThingMovement(pThing);
        sithPuppet_RemoveAllTracks(pThing);
        pThing->moveStatus = SITHPLAYERMOVE_STILL;
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in ResetThing().\n", pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingInsertOffset(SithCog* pCog)
{
    SithThing* pThing;
    rdModel3* pModel3;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        pModel3 = pThing->renderData.data.pModel3;
        if ( pModel3 )
        {
            sithCogExec_PushVector(pCog, &pModel3->insertOffset);
        }
        else
        {
            STDLOG_ERROR("Cog %s: No thing model in GetThingInsertOffset().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in GetThingInsertOffset().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingInsertOffset(SithCog* pCog)
{
    int bVec;
    SithThing* pThing;
    rdModel3* pModel3;
    rdVector3* pOffset;
    rdVector3 offset;

    bVec = sithCogExec_PopVector(pCog, &offset);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( bVec )
        {
            pModel3 = pThing->renderData.data.pModel3;
            if ( pModel3 )
            {
                pOffset = &pModel3->insertOffset;
                pOffset->x = offset.x;
                pOffset->y = offset.y;
                pOffset->z = offset.z;
                sithCogExec_PushVector(pCog, &pThing->renderData.data.pModel3->insertOffset);
            }
            else
            {
                STDLOG_ERROR("Cog %s: No thing model in SetThingInsertOffset().\n",
                    pCog->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad vector in SetThingInsertOffset().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingInsertOffset().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_GetThingEyeOffset(SithCog* pCog)
{
    SithThing* pThing;
    SithThingType type;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        type = pThing->type;
        if ( type == SITH_THING_PLAYER || type == SITH_THING_ACTOR )
        {
            sithCogExec_PushVector(pCog, &pThing->thingInfo.actorInfo.eyeOffset);
        }
        else
        {
            sithCogExec_PushVector(pCog, &rdroid_g_zeroVector3);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Invalid thing in GetThingEyeOffset().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_CheckFloorDistance(SithCog* pCog)
{
    SithThing* pThing;
    float distance;
    rdVector3 moveNorm;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        // rdVector_Neg3(moveNorm, rdroid_g_zVector3)
        moveNorm.x = 0.0;
        moveNorm.y = 0.0;
        moveNorm.z = -1.0;
        distance = sithCollision_CheckDistance(pThing, &moveNorm);
        sithCogExec_PushFlex(pCog, distance);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in CheckFloorDistance().\n",
            pCog->aName);

        sithCogExec_PushFlex(pCog, -1.0);
    }
}

void J3DAPI sithCogFunctionThing_CheckPathToPoint(SithCog* pCog)
{
    SithCog* pCog_1;
    int bSkipFloor;
    int bDetectThings;
    int bVec;
    SithThing* pViewer;
    rdVector3 vecTarget;
    rdVector3 pHitNorm;

    pCog_1 = pCog;
    bSkipFloor = sithCogExec_PopInt(pCog) == 1;
    bDetectThings = sithCogExec_PopInt(pCog_1) == 1;
    bVec = sithCogExec_PopVector(pCog_1, &vecTarget);
    pViewer = sithCogExec_PopThing(pCog_1);
    if ( pViewer )
    {
        if ( bVec )
        {
            sithAIUtil_CheckPathToPoint(
                pViewer,
                &vecTarget,
                pViewer->collide.movesize,
                (float*)&pCog,
                &pHitNorm,
                bDetectThings,
                bSkipFloor);                    // TODO: make sep distance var for arg 4
            sithCogExec_PushFlex(pCog_1, *(float*)&pCog);
        }
        else
        {
            sithCogExec_PushFlex(pCog_1, 0.0);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad THING in CheckPathToPoint() call.\n",
            pCog_1->aName);
        sithCogExec_PushFlex(pCog_1, 0.0);
    }
}

void J3DAPI sithCogFunctionThing_MoveThing(SithCog* pCog)
{
    int bVec;
    SithThing* pThing;
    SithAnimationSlot* pAnim;
    float timeDelta;
    rdVector3 vecDirection;
    float moveDist;

    timeDelta = sithCogExec_PopFlex(pCog);
    moveDist = sithCogExec_PopFlex(pCog);
    bVec = sithCogExec_PopVector(pCog, &vecDirection);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( bVec )
        {
            if ( moveDist > 0.0 )
            {

                if ( timeDelta > 0.0 )
                {
                    pAnim = sithAnimate_StartThingMove(pThing, &vecDirection, moveDist, timeDelta);
                    if ( pAnim )
                    {
                        sithCogExec_PushInt(pCog, pAnim->animID);
                    }
                    else
                    {
                        sithCogExec_PushInt(pCog, -1);
                    }
                }
                else
                {
                    sithCollision_MoveThing(pThing, &vecDirection, moveDist, 0);
                    sithCogExec_PushInt(pCog, -1);
                }
            }
            else
            {
                STDLOG_ERROR("Cog %s: Bad move distance in MoveThing().\n",
                    pCog->aName);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad vector in MoveThing().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in MoveThing().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_MoveThingToPos(SithCog* pCog)
{
    int bVec;
    SithThing* pThing;
    SithAnimationSlot* pAnim;
    rdVector3 startPos;
    rdVector3 pos;
    float time;
    float distance;

    time = sithCogExec_PopFlex(pCog);
    bVec = sithCogExec_PopVector(pCog, &pos);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( bVec )
        {
            if ( time > 0.0 )
            {
                pAnim = sithAnimate_StartThingMoveToPos(pThing, &pos, time);
                if ( pAnim )
                {
                    sithCogExec_PushInt(pCog, pAnim->animID);
                }
                else
                {
                    sithCogExec_PushInt(pCog, -1);
                }
            }
            else
            {
                startPos.x = pos.x - pThing->pos.x;
                startPos.y = pos.y - pThing->pos.y;
                startPos.z = pos.z - pThing->pos.z;
                distance = rdVector_Normalize3Acc(&startPos);
                sithCollision_MoveThing(pThing, &startPos, distance, 0);
                sithCogExec_PushInt(pCog, -1);
            }
        }
        else
        {
            STDLOG_ERROR("Cog %s: Bad vector in MoveThingToPos().\n",
                pCog->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in MoveThingToPos().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_SetThingStateChange(SithCog* pCog)
{
    int armModeState;
    int state;
    SithThing* pThing;

    armModeState = sithCogExec_PopInt(pCog);
    state = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_ACTOR || pThing->type == SITH_THING_PLAYER )
        {
            pThing->aiArmedModeState = armModeState;
            pThing->aiState = state;
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s is not an actor or player in SetThingStateChange.\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in SetThingStateChange.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_StartQuetzAnim(SithCog* pCog)
{
    unsigned int mode;
    SithThing* pThing;

    mode = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( !pThing )
    {
        STDLOG_ERROR("Bad thing in StartQuetzAnim()\n");

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( mode > 6 )
    {
        STDLOG_ERROR("Bad mode for thing %s in StartQuetzAnim()\n",
            pThing->aName);

        sithCogExec_PushInt(pCog, -1);
        return;
    }

    switch ( mode )
    {
        case 2u:
            sithAIMove_sub_49AB80(pThing->controlInfo.aiControl.pLocal);
            break;

        case 3u:
            sithAIMove_sub_49AC50(pThing->controlInfo.aiControl.pLocal);
            break;

        case 4u:
            sithAIMove_sub_49B1B0(pThing->controlInfo.aiControl.pLocal);
            break;

        case 5u:
            sithAIMove_sub_49AF80(pThing->controlInfo.aiControl.pLocal);
            break;

        default:
            return;
    }
}

void J3DAPI sithCogFunctionThing_BoardVehicle(SithCog* pCog)
{
    SithThing* pThing;
    int bBoarded;

    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        if ( pThing->type == SITH_THING_PLAYER )
        {
            bBoarded = sithPlayerControls_TryBoardVehicle(pThing, 1);
            sithCogExec_PushInt(pCog, bBoarded);
        }
        else
        {
            STDLOG_ERROR("Cog %s: Thing %s is not player in Board Vehicle.\n",
                pCog->aName,
                pThing->aName);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in Board Vehicle.\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_FadeInTrack(SithCog* pCog)
{
    int track;
    SithThing* pThing;
    int bSuccess;
    float speed;

    speed = sithCogExec_PopFlex(pCog);
    track = sithCogExec_PopInt(pCog);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        bSuccess = rdPuppet_FadeInTrack(pThing->renderData.pPuppet, track, speed);
        sithCogExec_PushInt(pCog, bSuccess);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad thing in FadeInMode().\n",
            pCog->aName);
        sithCogExec_PushInt(pCog, -1);
    }
}

void J3DAPI sithCogFunctionThing_MakeFairyDust(SithCog* pCog)
{
    int bPos;
    SithThing* pThing;
    SithSector* pInSector;
    rdVector3 pos;

    bPos = sithCogExec_PopVector(pCog, &pos);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && (pInSector = pThing->pInSector) != 0 && bPos )
    {
        sithFX_CreateFairyDust(&pos, pInSector);
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad args in MakeFairyDust().\n",
            pCog->aName);
    }
}

void J3DAPI sithCogFunctionThing_MakeFairyDustDeluxe(SithCog* pCog)
{
    int bPos;
    SithThing* pThing;
    rdVector3 pos;

    bPos = sithCogExec_PopVector(pCog, &pos);
    pThing = sithCogExec_PopThing(pCog);
    if ( pThing && bPos )
    {
        if ( pos.x == 0.0 && pos.y == 0.0 && pos.z == 0.0 )
        {
            sithFX_DestroyFairyDustDeluxe(pThing);
        }
        else
        {
            sithFX_CreateFairyDustDelux(pThing, &pos);
        }
    }
    else
    {
        STDLOG_ERROR("Cog %s: Bad args in MakeFairyDustDeluxe().\n",
            pCog->aName);
    }
}
