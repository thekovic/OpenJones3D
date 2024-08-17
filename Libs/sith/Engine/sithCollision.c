#include "sithCollision.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCollision_stackLevel J3D_DECL_FAR_VAR(sithCollision_stackLevel, int)
#define sithCollision_jeepDamage J3D_DECL_FAR_VAR(sithCollision_jeepDamage, float)
#define sithCollision_aNumSearchedSectors J3D_DECL_FAR_ARRAYVAR(sithCollision_aNumSearchedSectors, size_t(*)[4])
#define sithCollision_aCollideResults J3D_DECL_FAR_ARRAYVAR(sithCollision_aCollideResults, SithCollideResult(*)[15][15])
#define sithCollision_aThingSurfaceCollideResults J3D_DECL_FAR_ARRAYVAR(sithCollision_aThingSurfaceCollideResults, CollisionHandlerSurface(*)[15])
#define sithCollision_aCollisions J3D_DECL_FAR_ARRAYVAR(sithCollision_aCollisions, SithCollision(*)[4][512])
#define sithCollision_apSearchedSectors J3D_DECL_FAR_ARRAYVAR(sithCollision_apSearchedSectors, SithSector*(*)[4][256])
#define sithCollision_aNumStackCollisions J3D_DECL_FAR_ARRAYVAR(sithCollision_aNumStackCollisions, size_t(*)[4])
#define sithCollision_bCollideStartup J3D_DECL_FAR_VAR(sithCollision_bCollideStartup, int)
#define sithCollision_dword_17F1090 J3D_DECL_FAR_VAR(sithCollision_dword_17F1090, int)
#define sithCollision_vec17F10A0 J3D_DECL_FAR_VAR(sithCollision_vec17F10A0, rdVector3)

void sithCollision_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCollision_Startup);
    // J3D_HOOKFUNC(sithCollision_Shutdown);
    // J3D_HOOKFUNC(sithCollision_AddCollisionHandler);
    // J3D_HOOKFUNC(sithCollision_AddSurfaceCollisionHandler);
    // J3D_HOOKFUNC(sithCollision_PopStack);
    // J3D_HOOKFUNC(sithCollision_FindSectorInRadius);
    // J3D_HOOKFUNC(sithCollision_FindSectorAtThing);
    // J3D_HOOKFUNC(sithCollision_FindWaterSector);
    // J3D_HOOKFUNC(sithCollision_CanMoveToPos);
    // J3D_HOOKFUNC(sithCollision_HasLOS);
    // J3D_HOOKFUNC(sithCollision_RotateThing);
    // J3D_HOOKFUNC(sithCollision_sub_4A6EE0);
    // J3D_HOOKFUNC(sithCollision_MoveThing);
    // J3D_HOOKFUNC(sithCollision_SearchForCollisions);
    // J3D_HOOKFUNC(sithCollision_DecreaseStackLevel);
    // J3D_HOOKFUNC(sithCollision_SearchForThingCollisions);
    // J3D_HOOKFUNC(sithCollision_SearchForSurfaceCollisions);
    // J3D_HOOKFUNC(sithCollision_HandleThingHitSurface);
    // J3D_HOOKFUNC(sithCollision_ThingCollisionHandler);
    // J3D_HOOKFUNC(sithCollision_VehicleCollisionHandler);
    // J3D_HOOKFUNC(sithCollision_sub_4AA1A0);
    // J3D_HOOKFUNC(sithCollision_FindActivatedThing);
    // J3D_HOOKFUNC(sithCollision_PushThingCollision);
    // J3D_HOOKFUNC(sithCollision_PushSurfaceCollision);
    // J3D_HOOKFUNC(sithCollision_ParticleAndActorCollisionHandler);
    // J3D_HOOKFUNC(sithCollision_CheckDistance);
    // J3D_HOOKFUNC(sithCollision_sub_4AAF30);
}

void sithCollision_ResetGlobals(void)
{
    int sithCollision_stackLevel_tmp = -1;
    memcpy(&sithCollision_stackLevel, &sithCollision_stackLevel_tmp, sizeof(sithCollision_stackLevel));
    
    float sithCollision_jeepDamage_tmp = 1.0f;
    memcpy(&sithCollision_jeepDamage, &sithCollision_jeepDamage_tmp, sizeof(sithCollision_jeepDamage));
    
    memset(&sithCollision_aNumSearchedSectors, 0, sizeof(sithCollision_aNumSearchedSectors));
    memset(&sithCollision_aCollideResults, 0, sizeof(sithCollision_aCollideResults));
    memset(&sithCollision_aThingSurfaceCollideResults, 0, sizeof(sithCollision_aThingSurfaceCollideResults));
    memset(&sithCollision_aCollisions, 0, sizeof(sithCollision_aCollisions));
    memset(&sithCollision_apSearchedSectors, 0, sizeof(sithCollision_apSearchedSectors));
    memset(&sithCollision_aNumStackCollisions, 0, sizeof(sithCollision_aNumStackCollisions));
    memset(&sithCollision_bCollideStartup, 0, sizeof(sithCollision_bCollideStartup));
    memset(&sithCollision_dword_17F1090, 0, sizeof(sithCollision_dword_17F1090));
    memset(&sithCollision_vec17F10A0, 0, sizeof(sithCollision_vec17F10A0));
}

void sithCollision_Startup(void)
{
    J3D_TRAMPOLINE_CALL(sithCollision_Startup);
}

void sithCollision_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithCollision_Shutdown);
}

void J3DAPI sithCollision_AddCollisionHandler(SithThingType type1, SithThingType type2, CollisionHandlerThing pProcessFunc, int (J3DAPI* pUnknownFunc)(SithThing*, SithThing*))
{
    J3D_TRAMPOLINE_CALL(sithCollision_AddCollisionHandler, type1, type2, pProcessFunc, pUnknownFunc);
}

void J3DAPI sithCollision_AddSurfaceCollisionHandler(SithThingType type, CollisionHandlerSurface fpHandler)
{
    J3D_TRAMPOLINE_CALL(sithCollision_AddSurfaceCollisionHandler, type, fpHandler);
}

SithCollision* sithCollision_PopStack(void)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_PopStack);
}

SithSector* J3DAPI sithCollision_FindSectorInRadius(SithSector* pStartSector, const rdVector3* startPos, rdVector3* endPos, float radius)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_FindSectorInRadius, pStartSector, startPos, endPos, radius);
}

SithSector* J3DAPI sithCollision_FindSectorAtThing(SithThing* pThing, SithSector* pStartSector, const rdVector3* startPos, rdVector3* endPos, float radius)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_FindSectorAtThing, pThing, pStartSector, startPos, endPos, radius);
}

SithSector* J3DAPI sithCollision_FindWaterSector(SithSector* pStartSector, rdVector3* startPos, rdVector3* endPos, float radius)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_FindWaterSector, pStartSector, startPos, endPos, radius);
}

int J3DAPI sithCollision_CanMoveToPos(SithSector* pStartSector, const rdVector3* startPos, const rdVector3* endPos, float radius)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_CanMoveToPos, pStartSector, startPos, endPos, radius);
}

int J3DAPI sithCollision_HasLOS(const SithThing* pViewer, const SithThing* pTarget, int a3)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_HasLOS, pViewer, pTarget, a3);
}

void J3DAPI sithCollision_RotateThing(SithThing* pThing, const rdMatrix34* pOrient)
{
    J3D_TRAMPOLINE_CALL(sithCollision_RotateThing, pThing, pOrient);
}

void J3DAPI sithCollision_sub_4A6EE0(SithThing* pThing, rdMatrix34* pOrient)
{
    J3D_TRAMPOLINE_CALL(sithCollision_sub_4A6EE0, pThing, pOrient);
}

// Function returns distance the thing has travelled
float J3DAPI sithCollision_MoveThing(SithThing* pThing, const rdVector3* moveNorm, float moveDist, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_MoveThing, pThing, moveNorm, moveDist, flags);
}

float J3DAPI sithCollision_SearchForCollisions(SithSector* pStartSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_SearchForCollisions, pStartSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);
}

void sithCollision_DecreaseStackLevel(void)
{
    J3D_TRAMPOLINE_CALL(sithCollision_DecreaseStackLevel);
}

float J3DAPI sithCollision_SearchForThingCollisions(const SithSector* pSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_SearchForThingCollisions, pSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);
}

// flags:
// 0x100 - skip check for adjoin flag SITH_ADJOIN_MOVE
// 0x200 - skip check for adjoin flag SITH_ADJOIN_NO_PLAYER_MOVE
void J3DAPI sithCollision_SearchForSurfaceCollisions(const SithSector* pSector, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int flags)
{
    J3D_TRAMPOLINE_CALL(sithCollision_SearchForSurfaceCollisions, pSector, startPos, moveNorm, moveDist, radius, flags);
}

int J3DAPI sithCollision_HandleThingHitSurface(SithThing* pThing, SithSurface* pSurface, SithCollision* pCollision)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_HandleThingHitSurface, pThing, pSurface, pCollision);
}

// Note: Function handles collsions between 2 things.
// It returns True if there was collision otherwise False
int J3DAPI sithCollision_ThingCollisionHandler(SithThing* pSrcThing, SithThing* pThingCollided, SithCollision* pCollision, int bSecondThingIsSource)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_ThingCollisionHandler, pSrcThing, pThingCollided, pCollision, bSecondThingIsSource);
}

void J3DAPI sithCollision_VehicleCollisionHandler(SithThing* pThing, SithThing* pHitThing, rdVector3* pForce, rdVector3* pInpactForce, int* a5, const rdVector3* hitNormal, float impactSpeed, float hitImpactSpeed)
{
    J3D_TRAMPOLINE_CALL(sithCollision_VehicleCollisionHandler, pThing, pHitThing, pForce, pInpactForce, a5, hitNormal, impactSpeed, hitImpactSpeed);
}

int J3DAPI sithCollision_sub_4AA1A0(SithThing* pThing, const rdVector3* pHitNorm, float distance, int a4, const SithSurface* pHitSurf)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_sub_4AA1A0, pThing, pHitNorm, distance, a4, pHitSurf);
}

SithThing* J3DAPI sithCollision_FindActivatedThing(SithThing* pThing, int* pbFoundFloorItem)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_FindActivatedThing, pThing, pbFoundFloorItem);
}

void J3DAPI sithCollision_PushThingCollision(SithThing* pHitThing, float distance, SithCollisionType hitType, rdModel3Mesh* pHitMesh, rdFace* pHitFace, rdVector3* hitNorm)
{
    J3D_TRAMPOLINE_CALL(sithCollision_PushThingCollision, pHitThing, distance, hitType, pHitMesh, pHitFace, hitNorm);
}

void J3DAPI sithCollision_PushSurfaceCollision(SithSurface* pSurf, float distance, SithCollisionType hitType, rdVector3* pHitNorm)
{
    J3D_TRAMPOLINE_CALL(sithCollision_PushSurfaceCollision, pSurf, distance, hitType, pHitNorm);
}

int J3DAPI sithCollision_ParticleAndActorCollisionHandler(SithThing* pSrcThing, SithThing* pThingCollided, SithCollision* pCollision, int bSecondThingIsSource)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_ParticleAndActorCollisionHandler, pSrcThing, pThingCollided, pCollision, bSecondThingIsSource);
}

float J3DAPI sithCollision_CheckDistance(SithThing* pThing, const rdVector3* moveNorm)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_CheckDistance, pThing, moveNorm);
}

int J3DAPI sithCollision_sub_4AAF30(SithThing* pThing1, SithThing* pThing2)
{
    return J3D_TRAMPOLINE_CALL(sithCollision_sub_4AAF30, pThing1, pThing2);
}
