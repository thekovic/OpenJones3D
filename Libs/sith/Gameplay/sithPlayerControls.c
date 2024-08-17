#include "sithPlayerControls.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithPlayerControls_vecDebugCamDir J3D_DECL_FAR_VAR(sithPlayerControls_vecDebugCamDir, rdVector3)
#define sithPlayerControls_cameraDistance J3D_DECL_FAR_VAR(sithPlayerControls_cameraDistance, float)
#define sithPlayerControls_bActionActivated J3D_DECL_FAR_VAR(sithPlayerControls_bActionActivated, int)
#define sithPlayerControls_pCollidedThing J3D_DECL_FAR_VAR(sithPlayerControls_pCollidedThing, SithThing*)
#define sithPlayerControls_curJumpDirection J3D_DECL_FAR_VAR(sithPlayerControls_curJumpDirection, int)
#define sithPlayerControls_pCurActivatedThing J3D_DECL_FAR_VAR(sithPlayerControls_pCurActivatedThing, SithThing*)
#define sithPlayerControls_bJumpActivated J3D_DECL_FAR_VAR(sithPlayerControls_bJumpActivated, int)
#define sithPlayerControls_bLookMode J3D_DECL_FAR_VAR(sithPlayerControls_bLookMode, int)
#define sithPlayerControls_bHealthActivated J3D_DECL_FAR_VAR(sithPlayerControls_bHealthActivated, int)
#define sithPlayerControls_pVehicleBoardedThing J3D_DECL_FAR_VAR(sithPlayerControls_pVehicleBoardedThing, SithThing*)
#define sithPlayerControls_pTargetThing J3D_DECL_FAR_VAR(sithPlayerControls_pTargetThing, SithThing*)
#define sithPlayerControls_dword_55EE00 J3D_DECL_FAR_VAR(sithPlayerControls_dword_55EE00, int)
#define sithPlayerControls_curMoveStatus J3D_DECL_FAR_VAR(sithPlayerControls_curMoveStatus, int)
#define sithPlayerControls_bTurnRightActivated J3D_DECL_FAR_VAR(sithPlayerControls_bTurnRightActivated, int)
#define sithPlayerControls_bTurnLeftActivated J3D_DECL_FAR_VAR(sithPlayerControls_bTurnLeftActivated, int)
#define sithPlayerControls_secSwimmingTime J3D_DECL_FAR_VAR(sithPlayerControls_secSwimmingTime, float)
#define sithPlayerControls_secCommentWait J3D_DECL_FAR_VAR(sithPlayerControls_secCommentWait, float)

void sithPlayerControls_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPlayerControls_PuppetCallback);
    // J3D_HOOKFUNC(sithPlayerControls_Process);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessPlayerDebugControls);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessLookControls);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessGeneralMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessClimbMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessJewelFlyMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessFlyAndUnderwaterMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessGeneralControls);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessEditorDebugControls);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessDeadPlayer);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessJumpForwardMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessSwimMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessHangMove);
    // J3D_HOOKFUNC(sithPlayerControls_ProcessWeaponAim);
    // J3D_HOOKFUNC(sithPlayerControls_CanAimAtPos);
    // J3D_HOOKFUNC(sithPlayerControls_GetPushPullMoveNorm);
    // J3D_HOOKFUNC(sithPlayerControls_CheckWaterLedge);
    // J3D_HOOKFUNC(sithPlayerControls_SearchForCollisions);
    // J3D_HOOKFUNC(sithPlayerControls_SearchForClimbSurface);
    // J3D_HOOKFUNC(sithPlayerControls_TryBoardVehicle);
    // J3D_HOOKFUNC(sithPlayerControls_ExitVehicle);
    // J3D_HOOKFUNC(sithPlayerControls_RotateAimJoints);
    // J3D_HOOKFUNC(sithPlayerControls_CenterActorOrientation);
    // J3D_HOOKFUNC(sithPlayerControls_GetTargetThing);
    // J3D_HOOKFUNC(sithPlayerControls_GetVehicleBoardedThing);
    // J3D_HOOKFUNC(sithPlayerControls_SetVehicleBoardedThing);
    // J3D_HOOKFUNC(sithPlayerControls_CanStrafeMove);
}

void sithPlayerControls_ResetGlobals(void)
{
    rdVector3 sithPlayerControls_vecDebugCamDir_tmp = { { 0.0f }, { -1.0f }, { 0.0f } };
    memcpy(&sithPlayerControls_vecDebugCamDir, &sithPlayerControls_vecDebugCamDir_tmp, sizeof(sithPlayerControls_vecDebugCamDir));
    
    float sithPlayerControls_cameraDistance_tmp = 0.2f;
    memcpy(&sithPlayerControls_cameraDistance, &sithPlayerControls_cameraDistance_tmp, sizeof(sithPlayerControls_cameraDistance));
    
    memset(&sithPlayerControls_bActionActivated, 0, sizeof(sithPlayerControls_bActionActivated));
    memset(&sithPlayerControls_g_bCutsceneMode, 0, sizeof(sithPlayerControls_g_bCutsceneMode));
    memset(&sithPlayerControls_pCollidedThing, 0, sizeof(sithPlayerControls_pCollidedThing));
    memset(&sithPlayerControls_curJumpDirection, 0, sizeof(sithPlayerControls_curJumpDirection));
    memset(&sithPlayerControls_pCurActivatedThing, 0, sizeof(sithPlayerControls_pCurActivatedThing));
    memset(&sithPlayerControls_bJumpActivated, 0, sizeof(sithPlayerControls_bJumpActivated));
    memset(&sithPlayerControls_bLookMode, 0, sizeof(sithPlayerControls_bLookMode));
    memset(&sithPlayerControls_bHealthActivated, 0, sizeof(sithPlayerControls_bHealthActivated));
    memset(&sithPlayerControls_pVehicleBoardedThing, 0, sizeof(sithPlayerControls_pVehicleBoardedThing));
    memset(&sithPlayerControls_pTargetThing, 0, sizeof(sithPlayerControls_pTargetThing));
    memset(&sithPlayerControls_dword_55EE00, 0, sizeof(sithPlayerControls_dword_55EE00));
    memset(&sithPlayerControls_curMoveStatus, 0, sizeof(sithPlayerControls_curMoveStatus));
    memset(&sithPlayerControls_bTurnRightActivated, 0, sizeof(sithPlayerControls_bTurnRightActivated));
    memset(&sithPlayerControls_bTurnLeftActivated, 0, sizeof(sithPlayerControls_bTurnLeftActivated));
    memset(&sithPlayerControls_secSwimmingTime, 0, sizeof(sithPlayerControls_secSwimmingTime));
    memset(&sithPlayerControls_secCommentWait, 0, sizeof(sithPlayerControls_secCommentWait));
}

void J3DAPI sithPlayerControls_PuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_PuppetCallback, pThing, track, markerType);
}

int J3DAPI sithPlayerControls_Process(SithThing* pPlayerThing, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_Process, pPlayerThing, secDeltaTime);
}

int J3DAPI sithPlayerControls_ProcessPlayerDebugControls(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessPlayerDebugControls, pThing);
}

void J3DAPI sithPlayerControls_ProcessLookControls(SithThing* pThing, float a2)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessLookControls, pThing, a2);
}

void J3DAPI sithPlayerControls_ProcessGeneralMove(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessGeneralMove, pThing, secDeltaTime);
}

void J3DAPI sithPlayerControls_ProcessClimbMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessClimbMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessJewelFlyMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessJewelFlyMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessFlyAndUnderwaterMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessFlyAndUnderwaterMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessGeneralControls(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessGeneralControls, pThing);
}

int J3DAPI sithPlayerControls_ProcessEditorDebugControls(SithThing* pThing, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessEditorDebugControls, pThing, secDeltaTime);
}

int J3DAPI sithPlayerControls_ProcessDeadPlayer(SithThing* pThing, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessDeadPlayer, pThing, secDeltaTime);
}

void J3DAPI sithPlayerControls_ProcessJumpForwardMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessJumpForwardMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessSwimMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessSwimMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessHangMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessHangMove, pThing);
}

void J3DAPI sithPlayerControls_ProcessWeaponAim(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ProcessWeaponAim, pThing, secDeltaTime);
}

int J3DAPI sithPlayerControls_CanAimAtPos(SithThing* pThing, const rdVector3* pStartPost, const rdVector3* pAimPos, float cos1, float cos2, float cos3, float maxDist)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_CanAimAtPos, pThing, pStartPost, pAimPos, cos1, cos2, cos3, maxDist);
}

int J3DAPI sithPlayerControls_GetPushPullMoveNorm(rdVector3* moveNorm, const rdVector3* pLVect, float angle)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_GetPushPullMoveNorm, moveNorm, pLVect, angle);
}

int J3DAPI sithPlayerControls_CheckWaterLedge(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_CheckWaterLedge, pThing);
}

int J3DAPI sithPlayerControls_SearchForCollisions(SithThing* pThing, rdVector3* moveNorm, SithSurface** ppHitSurf, SithThing** ppHitThing, rdModel3** ppHitModel, rdFace** ppHitFace, rdModel3Mesh** ppHitMesh, int someType)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_SearchForCollisions, pThing, moveNorm, ppHitSurf, ppHitThing, ppHitModel, ppHitFace, ppHitMesh, someType);
}

SithSurface* J3DAPI sithPlayerControls_SearchForClimbSurface(SithThing* pThing, const rdVector3* moveNorm, int climbDir, int* pbHitNonClimbSurface)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_SearchForClimbSurface, pThing, moveNorm, climbDir, pbHitNonClimbSurface);
}

int J3DAPI sithPlayerControls_TryBoardVehicle(SithThing* pThing, int bBoard)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_TryBoardVehicle, pThing, bBoard);
}

void J3DAPI sithPlayerControls_ExitVehicle(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_ExitVehicle, pThing);
}

void J3DAPI sithPlayerControls_RotateAimJoints(SithThing* pThing, float pitch, float yaw)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_RotateAimJoints, pThing, pitch, yaw);
}

void J3DAPI sithPlayerControls_CenterActorOrientation(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_CenterActorOrientation, pThing);
}

SithThing* sithPlayerControls_GetTargetThing(void)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_GetTargetThing);
}

SithThing* J3DAPI sithPlayerControls_GetVehicleBoardedThing()
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_GetVehicleBoardedThing);
}

void J3DAPI sithPlayerControls_SetVehicleBoardedThing(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerControls_SetVehicleBoardedThing, pThing);
}

signed int J3DAPI sithPlayerControls_CanStrafeMove(SithThing* pThing, int bMoveRight)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerControls_CanStrafeMove, pThing, bMoveRight);
}
