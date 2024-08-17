#include "sithAIUtil.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithAIUtil_thingsInViewFovY J3D_DECL_FAR_VAR(sithAIUtil_thingsInViewFovY, float)
#define sithAIUtil_numVisitedSectors J3D_DECL_FAR_VAR(sithAIUtil_numVisitedSectors, size_t)
#define sithAIUtil_activeWpntLayer J3D_DECL_FAR_VAR(sithAIUtil_activeWpntLayer, SithAIWaypointLayerFlag)
#define sithAIUtil_numThingsInView J3D_DECL_FAR_VAR(sithAIUtil_numThingsInView, size_t)
#define sithAIUtil_vec_585490 J3D_DECL_FAR_VAR(sithAIUtil_vec_585490, rdVector3)
#define sithAIUtil_pMkPointCurLocal J3D_DECL_FAR_VAR(sithAIUtil_pMkPointCurLocal, SithAIControlBlock*)
#define sithAIUtil_mkPointCurPYR J3D_DECL_FAR_VAR(sithAIUtil_mkPointCurPYR, rdVector3)
#define sithAIUtil_thingsInViewFovX J3D_DECL_FAR_VAR(sithAIUtil_thingsInViewFovX, float)
#define sithAIUtil_aWpntOwners J3D_DECL_FAR_ARRAYVAR(sithAIUtil_aWpntOwners, SithAIWaypointOwner(*)[10])
#define sithAIUtil_aThingsInView J3D_DECL_FAR_VAR(sithAIUtil_aThingsInView, SithThing**)
#define sithAIUtil_aWpntDistances J3D_DECL_FAR_ARRAYVAR(sithAIUtil_aWpntDistances, SithAIWaypointDistance(*)[60])
#define sithAIUtil_sizeThingsInView J3D_DECL_FAR_VAR(sithAIUtil_sizeThingsInView, int)
#define sithAIUtil_vec_585718 J3D_DECL_FAR_VAR(sithAIUtil_vec_585718, rdVector3)
#define sithAIUtil_maxDistanceToThingsInView J3D_DECL_FAR_VAR(sithAIUtil_maxDistanceToThingsInView, float)
#define sithAIUtil_thingInViewTypeMask J3D_DECL_FAR_VAR(sithAIUtil_thingInViewTypeMask, int)
#define sithAIUtil_aAIWpnts J3D_DECL_FAR_ARRAYVAR(sithAIUtil_aAIWpnts, SithAIWaypoint(*)[60])
#define sithAIUtil_secLastUpdate J3D_DECL_FAR_VAR(sithAIUtil_secLastUpdate, float)
#define sithAIUtil_mkPoinCurFlags J3D_DECL_FAR_VAR(sithAIUtil_mkPoinCurFlags, int)

void sithAIUtil_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAIUtil_sub_49B2E0);
    // J3D_HOOKFUNC(sithAIUtil_sub_49B640);
    // J3D_HOOKFUNC(sithAIUtil_GetDistanceToTarget);
    // J3D_HOOKFUNC(sithAIUtil_GetDistanceToTargetPos);
    // J3D_HOOKFUNC(sithAIUtil_AIFire);
    // J3D_HOOKFUNC(sithAIUtil_AIPauseMove);
    // J3D_HOOKFUNC(sithAIUtil_AIResetWaypoints);
    // J3D_HOOKFUNC(sithAIUtil_SyncWpnts);
    // J3D_HOOKFUNC(sithAIUtil_ProcessSyncWpnts);
    // J3D_HOOKFUNC(sithAIUtil_AISetWpnt);
    // J3D_HOOKFUNC(sithAIUtil_AIGetWpntThing);
    // J3D_HOOKFUNC(sithAIUtil_AISetWpntRank);
    // J3D_HOOKFUNC(sithAIUtil_AISetWpntFlags);
    // J3D_HOOKFUNC(sithAIUtil_AIClearWpntFlags);
    // J3D_HOOKFUNC(sithAIUtil_AISetActiveWpntLayer);
    // J3D_HOOKFUNC(sithAIUtil_AIConnectWpnts);
    // J3D_HOOKFUNC(sithAIUtil_AIMoveToNextWpnt);
    // J3D_HOOKFUNC(sithAIUtil_AITraverseWpnts);
    // J3D_HOOKFUNC(sithAIUtil_AIAdvanceToNextWpnt);
    // J3D_HOOKFUNC(sithAIUtil_sub_49CC60);
    // J3D_HOOKFUNC(sithAIUtil_sub_49D170);
    // J3D_HOOKFUNC(sithAIUtil_AIFindNearestWpnt);
    // J3D_HOOKFUNC(sithAIUtil_sub_49D640);
    // J3D_HOOKFUNC(sithAIUtil_sub_49D750);
    // J3D_HOOKFUNC(sithAIUtil_CreateAIWaypoint);
    // J3D_HOOKFUNC(sithAIUtil_ClearAIWaypoint);
    // J3D_HOOKFUNC(sithAIUtil_GetAIWaypointNum);
    // J3D_HOOKFUNC(sithAIUtil_CompareAIWpntDistances);
    // J3D_HOOKFUNC(sithAIUtil_RenderAIWaypoints);
    // J3D_HOOKFUNC(sithAIUtil_CheckPathToPoint);
    // J3D_HOOKFUNC(sithAIUtil_sub_49DC90);
    // J3D_HOOKFUNC(sithAIUtil_sub_49DD20);
    // J3D_HOOKFUNC(sithAIUtil_MakeRandPoint);
    // J3D_HOOKFUNC(sithAIUtil_RetryMakeRandPoint);
    // J3D_HOOKFUNC(sithAIUtil_CheckPathToPos);
    // J3D_HOOKFUNC(sithAIUtil_sub_49EE50);
    // J3D_HOOKFUNC(sithAIUtil_sub_49F010);
    // J3D_HOOKFUNC(sithAIUtil_MakePathPos);
    // J3D_HOOKFUNC(sithAIUtil_sub_49F1F0);
    // J3D_HOOKFUNC(sithAIUtil_AIPlaySoundMode);
    // J3D_HOOKFUNC(sithAIUtil_AISetMode);
    // J3D_HOOKFUNC(sithAIUtil_AIClearMode);
    // J3D_HOOKFUNC(sithAIUtil_SetWeaponFireFlags);
    // J3D_HOOKFUNC(sithAIUtil_AIGetMovePos);
    // J3D_HOOKFUNC(sithAIUtil_GetXYHeadingVector);
    // J3D_HOOKFUNC(sithAIUtil_GetXYZHeadingVector);
    // J3D_HOOKFUNC(sithAIUtil_CanAttackTarget);
    // J3D_HOOKFUNC(sithAIUtil_IsThingMoving);
    // J3D_HOOKFUNC(sithAIUtil_ApplyForce);
    // J3D_HOOKFUNC(sithAIUtil_RandomRotate);
    // J3D_HOOKFUNC(sithAIUtil_GetThingsInView);
    // J3D_HOOKFUNC(sithAIUtil_GetNextThingsInView);
    // J3D_HOOKFUNC(sithAIUtil_CanSeeTarget);
}

void sithAIUtil_ResetGlobals(void)
{
    memset(&sithAIUtil_thingsInViewFovY, 0, sizeof(sithAIUtil_thingsInViewFovY));
    memset(&sithAIUtil_numVisitedSectors, 0, sizeof(sithAIUtil_numVisitedSectors));
    memset(&sithAIUtil_g_bRenderAIWpnts, 0, sizeof(sithAIUtil_g_bRenderAIWpnts));
    memset(&sithAIUtil_activeWpntLayer, 0, sizeof(sithAIUtil_activeWpntLayer));
    memset(&sithAIUtil_numThingsInView, 0, sizeof(sithAIUtil_numThingsInView));
    memset(&sithAIUtil_vec_585490, 0, sizeof(sithAIUtil_vec_585490));
    memset(&sithAIUtil_pMkPointCurLocal, 0, sizeof(sithAIUtil_pMkPointCurLocal));
    memset(&sithAIUtil_mkPointCurPYR, 0, sizeof(sithAIUtil_mkPointCurPYR));
    memset(&sithAIUtil_thingsInViewFovX, 0, sizeof(sithAIUtil_thingsInViewFovX));
    memset(&sithAIUtil_aWpntOwners, 0, sizeof(sithAIUtil_aWpntOwners));
    memset(&sithAIUtil_aThingsInView, 0, sizeof(sithAIUtil_aThingsInView));
    memset(&sithAIUtil_aWpntDistances, 0, sizeof(sithAIUtil_aWpntDistances));
    memset(&sithAIUtil_sizeThingsInView, 0, sizeof(sithAIUtil_sizeThingsInView));
    memset(&sithAIUtil_vec_585718, 0, sizeof(sithAIUtil_vec_585718));
    memset(&sithAIUtil_maxDistanceToThingsInView, 0, sizeof(sithAIUtil_maxDistanceToThingsInView));
    memset(&sithAIUtil_thingInViewTypeMask, 0, sizeof(sithAIUtil_thingInViewTypeMask));
    memset(&sithAIUtil_aAIWpnts, 0, sizeof(sithAIUtil_aAIWpnts));
    memset(&sithAIUtil_secLastUpdate, 0, sizeof(sithAIUtil_secLastUpdate));
    memset(&sithAIUtil_mkPoinCurFlags, 0, sizeof(sithAIUtil_mkPoinCurFlags));
}

void J3DAPI sithAIUtil_sub_49B2E0(SithAIControlBlock* pLocal, SithAIUtilFireFlags flags)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49B2E0, pLocal, flags);
}

void J3DAPI sithAIUtil_sub_49B640(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49B640, pLocal);
}

// returns target sight state:
// 0 - target in sight
// 1 - target too far away (dist > sightDistance)
// 2 - target out of FOV view
// 3 - target not in sight
int J3DAPI sithAIUtil_GetDistanceToTarget(SithThing* pViewer, rdVector3* startPos, const SithThing* pTarget, float fov, float sightDistance, float collisionSize, rdVector3* toTarget, float* pDist)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetDistanceToTarget, pViewer, startPos, pTarget, fov, sightDistance, collisionSize, toTarget, pDist);
}

int J3DAPI sithAIUtil_GetDistanceToTargetPos(SithThing* pViewer, rdVector3* startPos, rdVector3* endPos, float fov, float sightDistance, float collisionSize, rdVector3* toTarget, float* pDist)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetDistanceToTargetPos, pViewer, startPos, endPos, fov, sightDistance, collisionSize, toTarget, pDist);
}

int J3DAPI sithAIUtil_AIFire(SithAIControlBlock* pLocal, float minDist, float maxDist, float fireDot, float aimError, int weaponNum, SithAIUtilFireFlags flags, int burstCount)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIFire, pLocal, minDist, maxDist, fireDot, aimError, weaponNum, flags, burstCount);
}

void J3DAPI sithAIUtil_AIPauseMove(SithAIControlBlock* pLocal, int msecPause)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIPauseMove, pLocal, msecPause);
}

void sithAIUtil_AIResetWaypoints(void)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIResetWaypoints);
}

int J3DAPI sithAIUtil_SyncWpnts(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_SyncWpnts, idTo, outstream);
}

int J3DAPI sithAIUtil_ProcessSyncWpnts(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_ProcessSyncWpnts, pMsg);
}

void J3DAPI sithAIUtil_AISetWpnt(SithThing* pGhost, unsigned int wpntIdx)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AISetWpnt, pGhost, wpntIdx);
}

SithThing* J3DAPI sithAIUtil_AIGetWpntThing(int wpntIdx)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIGetWpntThing, wpntIdx);
}

void J3DAPI sithAIUtil_AISetWpntRank(unsigned int wpntIdx, unsigned int rank)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AISetWpntRank, wpntIdx, rank);
}

void J3DAPI sithAIUtil_AISetWpntFlags(unsigned int wpntIdx, SithAIWaypointLayerFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AISetWpntFlags, wpntIdx, flags);
}

void J3DAPI sithAIUtil_AIClearWpntFlags(unsigned int tIdx, SithAIWaypointLayerFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIClearWpntFlags, tIdx, flags);
}

void J3DAPI sithAIUtil_AISetActiveWpntLayer(SithAIWaypointLayerFlag layer)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AISetActiveWpntLayer, layer);
}

void J3DAPI sithAIUtil_AIConnectWpnts(unsigned int wpntIdx1, unsigned int wpntIdx2, int bConnectWpnt1To2)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIConnectWpnts, wpntIdx1, wpntIdx2, bConnectWpnt1To2);
}

int J3DAPI sithAIUtil_AIMoveToNextWpnt(SithAIControlBlock* pLocal, float moveSpeed, float degTurn, int mode)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIMoveToNextWpnt, pLocal, moveSpeed, degTurn, mode);
}

void J3DAPI sithAIUtil_AITraverseWpnts(SithAIControlBlock* pLocal, int wpntIdx, float moveSpeed, float degTurn, int mode)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AITraverseWpnts, pLocal, wpntIdx, moveSpeed, degTurn, mode);
}

int J3DAPI sithAIUtil_AIAdvanceToNextWpnt(SithAIControlBlock* pLocal, int bNotify)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIAdvanceToNextWpnt, pLocal, bNotify);
}

int J3DAPI sithAIUtil_sub_49CC60(SithAIControlBlock* pLocal, unsigned int numLinks, int* aWypointLinks, int linkNum, int wpntOwnerNum)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49CC60, pLocal, numLinks, aWypointLinks, linkNum, wpntOwnerNum);
}

void J3DAPI sithAIUtil_sub_49D170(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49D170, pLocal);
}

int J3DAPI sithAIUtil_AIFindNearestWpnt(SithThing* pThing, int a2)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIFindNearestWpnt, pThing, a2);
}

void J3DAPI sithAIUtil_sub_49D640()
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49D640);
}

void J3DAPI sithAIUtil_sub_49D750(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49D750, pThing);
}

int J3DAPI sithAIUtil_CreateAIWaypoint(SithAIControlBlock* pLocal, float degTurn)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CreateAIWaypoint, pLocal, degTurn);
}

void J3DAPI sithAIUtil_ClearAIWaypoint(SithAIControlBlock* pLocal)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_ClearAIWaypoint, pLocal);
}

int J3DAPI sithAIUtil_GetAIWaypointNum(SithAIControlBlock* pLocal)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetAIWaypointNum, pLocal);
}

int J3DAPI sithAIUtil_CompareAIWpntDistances(const SithAIWaypointDistance* pDist1, const SithAIWaypointDistance* pDist2)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CompareAIWpntDistances, pDist1, pDist2);
}

void sithAIUtil_RenderAIWaypoints(void)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_RenderAIWaypoints);
}

int J3DAPI sithAIUtil_CheckPathToPoint(SithThing* pViewer, const rdVector3* pTarget, float radius, float* pDistance, rdVector3* pHitNorm, int bDetectThings, int bSkipFloor)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CheckPathToPoint, pViewer, pTarget, radius, pDistance, pHitNorm, bDetectThings, bSkipFloor);
}

int J3DAPI sithAIUtil_sub_49DC90(const SithAIControlBlock* pLocal, rdVector3* endPos, int* pbNoCollision)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49DC90, pLocal, endPos, pbNoCollision);
}

int J3DAPI sithAIUtil_sub_49DD20(const SithAIControlBlock* pLocal, const rdVector3* startPos, SithSector* pStartSector, int* pbNoCollision)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49DD20, pLocal, startPos, pStartSector, pbNoCollision);
}

int J3DAPI sithAIUtil_MakeRandPoint(SithAIControlBlock* pLocal, rdVector3* pPos, int flags, float angle, float* pDownCos, rdVector3* pDir, rdVector3* pDestPoint)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_MakeRandPoint, pLocal, pPos, flags, angle, pDownCos, pDir, pDestPoint);
}

int J3DAPI sithAIUtil_RetryMakeRandPoint(SithAIControlBlock* pLocal, rdVector3* pPos, float a3, rdVector3* pDirection, rdVector3* pDestPoint)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_RetryMakeRandPoint, pLocal, pPos, a3, pDirection, pDestPoint);
}

int J3DAPI sithAIUtil_CheckPathToPos(SithAIControlBlock* pLocal, SithSector* pStartSector, rdVector3* startPos, int flags, float minMoveDist, float moveDist, float radius, rdVector3* pDirection, rdVector3* a9)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CheckPathToPos, pLocal, pStartSector, startPos, flags, minMoveDist, moveDist, radius, pDirection, a9);
}

int J3DAPI sithAIUtil_sub_49EE50(SithAIControlBlock* pLocal, rdVector3* pPos, float angle, float maxAngle, float deltaAngle, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49EE50, pLocal, pPos, angle, maxAngle, deltaAngle, flags);
}

int J3DAPI sithAIUtil_sub_49F010(SithAIControlBlock* pLocal, rdVector3* pPos, float minDist, float moveDist, int bSomeBool, int maxRetries, rdVector3* pDestPos)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49F010, pLocal, pPos, minDist, moveDist, bSomeBool, maxRetries, pDestPos);
}

int J3DAPI sithAIUtil_MakePathPos(SithAIControlBlock* pLocal, rdVector3* pPos, float minDist, float moveDist, float angle, int flags, rdVector3* pDirection, rdVector3* pDestPos)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_MakePathPos, pLocal, pPos, minDist, moveDist, angle, flags, pDirection, pDestPos);
}

int J3DAPI sithAIUtil_sub_49F1F0(const SithAIControlBlock* pLocal, const rdVector3* pPos)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_sub_49F1F0, pLocal, pPos);
}

void J3DAPI sithAIUtil_AIPlaySoundMode(SithAIControlBlock* pLocal, SithSoundClassMode mode)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIPlaySoundMode, pLocal, mode);
}

void J3DAPI sithAIUtil_AISetMode(SithAIControlBlock* pLocal, SithAIMode mode)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AISetMode, pLocal, mode);
}

void J3DAPI sithAIUtil_AIClearMode(SithAIControlBlock* pLocal, SithAIMode mode)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_AIClearMode, pLocal, mode);
}

void J3DAPI sithAIUtil_SetWeaponFireFlags(int weaponNum, SithAIUtilFireFlags* pFlags)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_SetWeaponFireFlags, weaponNum, pFlags);
}

int J3DAPI sithAIUtil_AIGetMovePos(const SithAIControlBlock* pLocal, int flags, rdVector3* pDestPos)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_AIGetMovePos, pLocal, flags, pDestPos);
}

signed int J3DAPI sithAIUtil_GetXYHeadingVector(const SithThing* pThing, rdVector3* pDest)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetXYHeadingVector, pThing, pDest);
}

signed int J3DAPI sithAIUtil_GetXYZHeadingVector(const SithThing* pThing, rdVector3* pDest)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetXYZHeadingVector, pThing, pDest);
}

int J3DAPI sithAIUtil_CanAttackTarget(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CanAttackTarget, pThing);
}

int J3DAPI sithAIUtil_IsThingMoving(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_IsThingMoving, pThing);
}

void J3DAPI sithAIUtil_ApplyForce(SithAIControlBlock* pLocal, const rdVector3* pDirection, float force)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_ApplyForce, pLocal, pDirection, force);
}

void J3DAPI sithAIUtil_RandomRotate(rdVector3* pOutPYR, float scalar)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_RandomRotate, pOutPYR, scalar);
}

size_t J3DAPI sithAIUtil_GetThingsInView(const SithSector* pStartSector, const rdMatrix34* orient, float fovX, float fovY, int sizeResult, SithThing** pResult, int thingTypeMask, float maxDistance)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_GetThingsInView, pStartSector, orient, fovX, fovY, sizeResult, pResult, thingTypeMask, maxDistance);
}

void J3DAPI sithAIUtil_GetNextThingsInView(const SithSector* pSector, const rdMatrix34* pOrient, float distance)
{
    J3D_TRAMPOLINE_CALL(sithAIUtil_GetNextThingsInView, pSector, pOrient, distance);
}

int J3DAPI sithAIUtil_CanSeeTarget(const SithAIControlBlock* pLocal, SithThing* pTarget, float distance)
{
    return J3D_TRAMPOLINE_CALL(sithAIUtil_CanSeeTarget, pLocal, pTarget, distance);
}
