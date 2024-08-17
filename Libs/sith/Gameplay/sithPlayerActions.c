#include "sithPlayerActions.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithPlayerActions_climbPupTrackNum J3D_DECL_FAR_VAR(sithPlayerActions_climbPupTrackNum, int)
#define sithPlayerActions_msecCurActivateTime J3D_DECL_FAR_VAR(sithPlayerActions_msecCurActivateTime, unsigned int)

void sithPlayerActions_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPlayerActions_Activate);
    // J3D_HOOKFUNC(sithPlayerActions_Jump);
    // J3D_HOOKFUNC(sithPlayerActions_MoveToPlayerPosition);
    // J3D_HOOKFUNC(sithPlayerActions_PushItem);
    // J3D_HOOKFUNC(sithPlayerActions_PullItem);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbPullUp);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbMove);
    // J3D_HOOKFUNC(sithPlayerActions_UnmountWall);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbOn1m);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbOn2m);
    // J3D_HOOKFUNC(sithPlayerActions_LeapForward);
    // J3D_HOOKFUNC(sithPlayerActions_JumpForward);
    // J3D_HOOKFUNC(sithPlayerActions_JumpLeft);
    // J3D_HOOKFUNC(sithPlayerActions_JumpRight);
    // J3D_HOOKFUNC(sithPlayerActions_JumpRollBack);
    // J3D_HOOKFUNC(sithPlayerActions_JumpRollForward);
    // J3D_HOOKFUNC(sithPlayerActions_StrafeLeft);
    // J3D_HOOKFUNC(sithPlayerActions_StrafeRight);
    // J3D_HOOKFUNC(sithPlayerActions_HopBack);
    // J3D_HOOKFUNC(sithPlayerActions_Stand2Crawl);
    // J3D_HOOKFUNC(sithPlayerActions_Crawl2Stand);
    // J3D_HOOKFUNC(sithPlayerActions_JumpStart);
    // J3D_HOOKFUNC(sithPlayerActions_HasActiveWeapon);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbToClimb);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbToHang);
    // J3D_HOOKFUNC(sithPlayerActions_CanMoveToPos);
    // J3D_HOOKFUNC(sithPlayerActions_SearchForCollision);
    // J3D_HOOKFUNC(sithPlayerActions_CanClimbOn1m);
    // J3D_HOOKFUNC(sithPlayerActions_CanClimbOn2m);
    // J3D_HOOKFUNC(sithPlayerActions_SearchClimbSurface);
    // J3D_HOOKFUNC(sithPlayerActions_ActorGrabLedge);
    // J3D_HOOKFUNC(sithPlayerActions_ClimbDownToIdle);
    // J3D_HOOKFUNC(sithPlayerActions_CanPullUp);
    // J3D_HOOKFUNC(sithPlayerActions_GetFaceTopZ);
    // J3D_HOOKFUNC(sithPlayerActions_StartInvisibility);
    // J3D_HOOKFUNC(sithPlayerActions_EndInvisibility);
    // J3D_HOOKFUNC(sithPlayerActions_IsInvisible);
    // J3D_HOOKFUNC(sithPlayerActions_StartJewelFlying);
    // J3D_HOOKFUNC(sithPlayerActions_EnableJewelFlying);
    // J3D_HOOKFUNC(sithPlayerActions_DisableJewelFlying);
    // J3D_HOOKFUNC(sithPlayerActions_MoveToClimbSector);
    // J3D_HOOKFUNC(sithPlayerActions_Crawl);
}

void sithPlayerActions_ResetGlobals(void)
{
    int sithPlayerActions_g_jewelFlyingPuppetTrackNum_tmp = -1;
    memcpy(&sithPlayerActions_g_jewelFlyingPuppetTrackNum, &sithPlayerActions_g_jewelFlyingPuppetTrackNum_tmp, sizeof(sithPlayerActions_g_jewelFlyingPuppetTrackNum));
    
    memset(&sithPlayerActions_climbPupTrackNum, 0, sizeof(sithPlayerActions_climbPupTrackNum));
    memset(&sithPlayerActions_g_pCurCollidedSurface, 0, sizeof(sithPlayerActions_g_pCurCollidedSurface));
    memset(&sithPlayerActions_g_pCurCollidedModelFace, 0, sizeof(sithPlayerActions_g_pCurCollidedModelFace));
    memset(&sithPlayerActions_g_pCurCollidedModel, 0, sizeof(sithPlayerActions_g_pCurCollidedModel));
    memset(&sithPlayerActions_g_pPlasma, 0, sizeof(sithPlayerActions_g_pPlasma));
    memset(&sithPlayerActions_g_bJewelFlying, 0, sizeof(sithPlayerActions_g_bJewelFlying));
    memset(&sithPlayerActions_g_bPlayerInvisible, 0, sizeof(sithPlayerActions_g_bPlayerInvisible));
    memset(&sithPlayerActions_msecCurActivateTime, 0, sizeof(sithPlayerActions_msecCurActivateTime));
    memset(&sithPlayerActions_g_pChalkWriteSurf, 0, sizeof(sithPlayerActions_g_pChalkWriteSurf));
    memset(&sithPlayerActions_g_posChalkMarkWrite, 0, sizeof(sithPlayerActions_g_posChalkMarkWrite));
    memset(&sithPlayerActions_g_pChalkWriteSector, 0, sizeof(sithPlayerActions_g_pChalkWriteSector));
}

int J3DAPI sithPlayerActions_Activate(SithThing* pPlayer)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_Activate, pPlayer);
}

void J3DAPI sithPlayerActions_Jump(SithThing* pThing, float a2, int jumpDirection)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_Jump, pThing, a2, jumpDirection);
}

void J3DAPI sithPlayerActions_MoveToPlayerPosition(SithThing* pThing, unsigned int playerNum)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_MoveToPlayerPosition, pThing, playerNum);
}

void J3DAPI sithPlayerActions_PushItem(SithThing* pThing, SithThing* pItem, rdVector3* pDirection)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_PushItem, pThing, pItem, pDirection);
}

void J3DAPI sithPlayerActions_PullItem(SithThing* pThing, SithThing* pItem, rdVector3* pDirection)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_PullItem, pThing, pItem, pDirection);
}

SithInventoryItem* J3DAPI sithPlayerActions_ClimbPullUp(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbPullUp, pThing);
}

void J3DAPI sithPlayerActions_ClimbMove(SithThing* pThing, SithSurface* pSurf, int direction)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbMove, pThing, pSurf, direction);
}

void J3DAPI sithPlayerActions_UnmountWall(SithThing* pThing, int trackNum)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_UnmountWall, pThing, trackNum);
}

void J3DAPI sithPlayerActions_ClimbOn1m(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbOn1m, pThing);
}

void J3DAPI sithPlayerActions_ClimbOn2m(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbOn2m, pThing);
}

void J3DAPI sithPlayerActions_LeapForward(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_LeapForward, pThing);
}

void J3DAPI sithPlayerActions_JumpForward(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpForward, pThing);
}

void J3DAPI sithPlayerActions_JumpLeft(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpLeft, pThing);
}

void J3DAPI sithPlayerActions_JumpRight(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpRight, pThing);
}

void J3DAPI sithPlayerActions_JumpRollBack(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpRollBack, pThing);
}

void J3DAPI sithPlayerActions_JumpRollForward(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpRollForward, pThing);
}

void J3DAPI sithPlayerActions_StrafeLeft(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_StrafeLeft, pThing);
}

void J3DAPI sithPlayerActions_StrafeRight(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_StrafeRight, pThing);
}

void J3DAPI sithPlayerActions_HopBack(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_HopBack, pThing);
}

void J3DAPI sithPlayerActions_Stand2Crawl(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_Stand2Crawl, pThing);
}

void J3DAPI sithPlayerActions_Crawl2Stand(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_Crawl2Stand, pThing);
}

int J3DAPI sithPlayerActions_JumpStart(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_JumpStart, pThing);
}

int J3DAPI sithPlayerActions_HasActiveWeapon(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_HasActiveWeapon, pThing);
}

void J3DAPI sithPlayerActions_ClimbToClimb(SithThing* pThing, int bLedge)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbToClimb, pThing, bLedge);
}

void J3DAPI sithPlayerActions_ClimbToHang(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbToHang, pThing);
}

int J3DAPI sithPlayerActions_CanMoveToPos(SithThing* pThing, rdVector3* pPos, int* a3)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_CanMoveToPos, pThing, pPos, a3);
}

double J3DAPI sithPlayerActions_SearchForCollision(SithThing* pThing, const rdVector3* pPYR, SithSurface** pHitSurf, rdFace** pHitFace, rdModel3Mesh** pHitMesh, SithThing** pHitThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_SearchForCollision, pThing, pPYR, pHitSurf, pHitFace, pHitMesh, pHitThing);
}

int J3DAPI sithPlayerActions_CanClimbOn1m(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_CanClimbOn1m, pThing);
}

int J3DAPI sithPlayerActions_CanClimbOn2m(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_CanClimbOn2m, pThing);
}

int J3DAPI sithPlayerActions_SearchClimbSurface(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_SearchClimbSurface, pThing);
}

int J3DAPI sithPlayerActions_ActorGrabLedge(SithThing* pThing, float distance, SithSurface* pHitSurf, rdFace* pHitFace, const rdModel3Mesh* pHitMesh, SithThing* pHitThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_ActorGrabLedge, pThing, distance, pHitSurf, pHitFace, pHitMesh, pHitThing);
}

int J3DAPI sithPlayerActions_ClimbDownToIdle(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_ClimbDownToIdle, pThing);
}

int J3DAPI sithPlayerActions_CanPullUp(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_CanPullUp, pThing);
}

float J3DAPI sithPlayerActions_GetFaceTopZ(const SithThing* pThing, const rdFace* pFace, const rdModel3Mesh* pMesh)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_GetFaceTopZ, pThing, pFace, pMesh);
}

void J3DAPI sithPlayerActions_StartInvisibility()
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_StartInvisibility);
}

void J3DAPI sithPlayerActions_EndInvisibility()
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_EndInvisibility);
}

int J3DAPI sithPlayerActions_IsInvisible()
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_IsInvisible);
}

int J3DAPI sithPlayerActions_StartJewelFlying()
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_StartJewelFlying);
}

int J3DAPI sithPlayerActions_EnableJewelFlying(SithThing* pPlasma)
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_EnableJewelFlying, pPlasma);
}

SithThing* J3DAPI sithPlayerActions_DisableJewelFlying()
{
    return J3D_TRAMPOLINE_CALL(sithPlayerActions_DisableJewelFlying);
}

void J3DAPI sithPlayerActions_MoveToClimbSector(SithThing* pThing, SithSurface* pSurface)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_MoveToClimbSector, pThing, pSurface);
}

void J3DAPI sithPlayerActions_Crawl(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayerActions_Crawl, pThing);
}
