#include "sithCollision.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Math/rdMath.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>

#include <sith/Cog/sithCog.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Engine/sithCamera.h>
#include <sith/Engine/sithIntersect.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithActor.h>
#include <sith/World/sithItem.h>
#include <sith/World/sithSoundClass.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWeapon.h>
#include <sith/World/sithWorld.h>

#include <std/General/stdUtil.h>

#define SITHCOLLISION_STACKSIZE 4 

static int stackLevel = -1;
static float sithCollision_jeepDamage = 1.0f;

static SithCollideResult aCollideResults[SITH_THING_NUMTYPES][SITH_THING_NUMTYPES];
static CollisionHandlerSurface sithCollision_aThingSurfaceCollideResults[SITH_THING_NUMTYPES];

static size_t sithCollision_aNumSearchedSectors[SITHCOLLISION_STACKSIZE];
static SithSector* sithCollision_apSearchedSectors[SITHCOLLISION_STACKSIZE][256];

static size_t sithCollision_aNumStackCollisions[SITHCOLLISION_STACKSIZE];
static SithCollision sithCollision_aCollisions[SITHCOLLISION_STACKSIZE][512];

static int bCollideStartup;
static int sithCollision_dword_17F1090;
static rdVector3 sithCollision_vec17F10A0;

SithCollision* sithCollision_PopClosest(void);
void sithCollision_ResetCurStack(void);
float J3DAPI sithCollision_BuildCollisionList(SithSector* pSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags);
int J3DAPI sithCollision_CheckSectorSearched(const SithSector* pSector);
int J3DAPI sithCollision_AddSearchedSector(SithSector* pSector);
int J3DAPI sithCollision_sub_4DABF1(const SithThing* pThing, int searchFlags);
int J3DAPI sithCollision_sub_4DAC4B(const SithThing* pThing1, const SithThing* pThing2, int collflags);
int J3DAPI sithCollision_sub_4DAC4B(const SithThing* pThing1, const SithThing* pThing2, int collflags);
int J3DAPI sithCollision_sub_4DB3CA(SithThing* pThing1, SithThing* pThing2);
int J3DAPI sithCollision_sub_4DB49F(SithSurfaceAdjoinFlag adjflags, int colflags);

void sithCollision_InstallHooks(void)
{
    J3D_HOOKFUNC(sithCollision_Startup);
    J3D_HOOKFUNC(sithCollision_Shutdown);
    J3D_HOOKFUNC(sithCollision_AddCollisionHandler);
    J3D_HOOKFUNC(sithCollision_AddSurfaceCollisionHandler);
    J3D_HOOKFUNC(sithCollision_PopStack);
    J3D_HOOKFUNC(sithCollision_FindSectorInRadius);
    J3D_HOOKFUNC(sithCollision_FindSectorAtThing);
    J3D_HOOKFUNC(sithCollision_FindWaterSector);
    J3D_HOOKFUNC(sithCollision_CanMoveToPos);
    J3D_HOOKFUNC(sithCollision_HasLOS);
    J3D_HOOKFUNC(sithCollision_RotateThing);
    J3D_HOOKFUNC(sithCollision_sub_4A6EE0);
    J3D_HOOKFUNC(sithCollision_MoveThing);
    J3D_HOOKFUNC(sithCollision_SearchForCollisions);
    J3D_HOOKFUNC(sithCollision_DecreaseStackLevel);
    J3D_HOOKFUNC(sithCollision_SearchForThingCollisions);
    J3D_HOOKFUNC(sithCollision_SearchForSurfaceCollisions);
    J3D_HOOKFUNC(sithCollision_HandleThingHitSurface);
    J3D_HOOKFUNC(sithCollision_ThingCollisionHandler);
    J3D_HOOKFUNC(sithCollision_VehicleCollisionHandler);
    J3D_HOOKFUNC(sithCollision_sub_4AA1A0);
    J3D_HOOKFUNC(sithCollision_FindActivatedThing);
    J3D_HOOKFUNC(sithCollision_PushThingCollision);
    J3D_HOOKFUNC(sithCollision_PushSurfaceCollision);
    J3D_HOOKFUNC(sithCollision_ParticleAndActorCollisionHandler);
    J3D_HOOKFUNC(sithCollision_CheckDistance);
    J3D_HOOKFUNC(sithCollision_sub_4AAF30);
}

void sithCollision_ResetGlobals(void)
{

}

void sithCollision_Startup(void)
{
    if ( bCollideStartup )
    {
        SITHLOG_STATUS("Collide system already started.. chill.\n");
        return;
    }

    memset(aCollideResults, 0, sizeof(aCollideResults));
    memset(sithCollision_aThingSurfaceCollideResults, 0, sizeof(sithCollision_aThingSurfaceCollideResults));

    sithCollision_AddCollisionHandler(SITH_THING_ACTOR, SITH_THING_ACTOR, sithActor_ActorCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_ACTOR, SITH_THING_PLAYER, sithActor_ActorCollisionHandler, sithCollision_sub_4AAF30);

    sithCollision_AddCollisionHandler(SITH_THING_PLAYER, SITH_THING_PLAYER, sithCollision_ThingCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_PLAYER, SITH_THING_COG, sithCollision_ThingCollisionHandler, 0);

    sithCollision_AddCollisionHandler(SITH_THING_ACTOR, SITH_THING_COG, sithActor_ActorCollisionHandler, 0);

    sithCollision_AddCollisionHandler(SITH_THING_DEBRIS, SITH_THING_ACTOR, sithCollision_ParticleAndActorCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_DEBRIS, SITH_THING_PLAYER, sithCollision_ParticleAndActorCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_DEBRIS, SITH_THING_DEBRIS, sithCollision_ThingCollisionHandler, 0);

    sithCollision_AddCollisionHandler(SITH_THING_WEAPON, SITH_THING_ACTOR, sithWeapon_ThingCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_WEAPON, SITH_THING_PLAYER, sithWeapon_ThingCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_WEAPON, SITH_THING_DEBRIS, sithWeapon_ThingCollisionHandler, 0);
    sithCollision_AddCollisionHandler(SITH_THING_WEAPON, SITH_THING_COG, sithWeapon_ThingCollisionHandler, 0);

    sithCollision_AddCollisionHandler(SITH_THING_ITEM, SITH_THING_PLAYER, sithItem_PlayerCollisionHandler, 0);

    sithCollision_AddSurfaceCollisionHandler(SITH_THING_ACTOR, sithActor_SurfaceCollisionHandler);
    sithCollision_AddSurfaceCollisionHandler(SITH_THING_WEAPON, sithWeapon_SurfaceCollisionHandler);

    sithCollision_AddCollisionHandler(SITH_THING_COG, SITH_THING_COG, sithCollision_ThingCollisionHandler, 0);

    bCollideStartup = 1;
}

void sithCollision_Shutdown(void)
{
    if ( !bCollideStartup )
    {
        SITHLOG_ERROR("Collide system not started.\n");
        return;
    }

    bCollideStartup = 0;
}

void J3DAPI sithCollision_AddCollisionHandler(SithThingType type1, SithThingType type2, CollisionHandlerThing pProcessFunc, int (J3DAPI* pUnknownFunc)(SithThing*, SithThing*))
{
    SITH_ASSERTREL((type1 >= SITH_THING_FREE) && (type1 < SITH_THING_NUMTYPES));
    SITH_ASSERTREL((type2 >= SITH_THING_FREE) && (type2 < SITH_THING_NUMTYPES));
    SITH_ASSERTREL(pProcessFunc != ((void*)0));

    if ( aCollideResults[type1][type2].pProcessFunc || aCollideResults[type2][type1].pProcessFunc )
    {
        SITHLOG_STATUS("Warning- overriding previous collision handler for types %d and %d.\n", type1, type2);
    }

    aCollideResults[type1][type2].pProcessFunc = pProcessFunc;
    aCollideResults[type1][type2].pUnknownFunc = pUnknownFunc;
    aCollideResults[type1][type2].bDifferentTypHandler = 0;
    if ( type1 != type2 )
    {
        aCollideResults[type2][type1].pProcessFunc = pProcessFunc;
        aCollideResults[type2][type1].pUnknownFunc = pUnknownFunc;
        aCollideResults[type2][type1].bDifferentTypHandler = 1;
    }
}

void J3DAPI sithCollision_AddSurfaceCollisionHandler(SithThingType type, CollisionHandlerSurface fpHandler)
{
    SITH_ASSERTREL((type >= SITH_THING_FREE) && (type < SITH_THING_NUMTYPES));
    if ( sithCollision_aThingSurfaceCollideResults[type] )
    {
        SITHLOG_STATUS("Warning- overriding previous collision handler for type %d.\n", type);
    }

    sithCollision_aThingSurfaceCollideResults[type] = fpHandler;
}

SithSurface* J3DAPI sithCollision_sub_4D5E37(SithSector* pStartSector, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, SithCollisionType* hitType)
{
    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, moveNorm, moveDist, radius, 0x103);
    SithCollision* pCollision = sithCollision_PopStack();
    if ( pCollision )
    {
        SITH_ASSERTREL(pCollision->pSurfaceCollided != ((void*)0));
        *hitType = pCollision->type;
        sithCollision_DecreaseStackLevel();
        return pCollision->pSurfaceCollided;
    }

    sithCollision_DecreaseStackLevel();
    return NULL;
}

// Function searches for some camera collision
SithSurface* J3DAPI sithCollision_sub_4D57D8(const rdVector2* a1)
{
    rdCamera* pCamera = &sithCamera_g_pCurCamera->rdCamera;
    SITH_ASSERTREL(pCamera && pCamera->pCanvas);
    if ( !sithCamera_g_pCurCamera->pSector )
    {
        SITHLOG_STATUS("Unable to process query, don't have a valid camera sector right now.\n");
        return NULL;
    }

    rdVector3 dest;
    dest.x = a1->x;
    dest.z = -a1->y;
    dest.y = pCamera->focalLength;

    dest.x = dest.x - pCamera->pCanvas->center.x;
    dest.z = dest.z + pCamera->pCanvas->center.y;
    rdMatrix_TransformPoint34Acc(&dest, &sithCamera_g_pCurCamera->orient);

    rdVector3 moveNorm;
    moveNorm.x = dest.x - sithCamera_g_pCurCamera->orient.dvec.x;
    moveNorm.y = dest.y - sithCamera_g_pCurCamera->orient.dvec.y;
    moveNorm.z = dest.z - sithCamera_g_pCurCamera->orient.dvec.z;
    rdVector_Normalize3Acc(&moveNorm);

    SithCollisionType hitType;
    return sithCollision_sub_4D5E37(sithCamera_g_pCurCamera->pSector, &sithCamera_g_pCurCamera->orient.dvec, &moveNorm, 200.0f, 0.0f, &hitType);
}

SithCollision* sithCollision_PopStack(void)
{
    SithCollision* pCollision;

    SITH_ASSERTREL(stackLevel >= 0);
    SITH_ASSERTREL(stackLevel < SITHCOLLISION_STACKSIZE);
    pCollision = sithCollision_PopClosest();
    if ( pCollision )
    {
        pCollision->bEnumerated = 1;
    }
    else
    {
        sithCollision_ResetCurStack();
    }

    return pCollision;
}

SithSector* J3DAPI sithCollision_FindSectorInRadius(SithSector* pStartSector, const rdVector3* startPos, rdVector3* endPos, float radius)
{
    SithSector* pSector;
    float moveDist;
    SithCollision* pCollision;
    rdVector3 moveNorm;

    SITH_ASSERTREL(startPos && endPos && pStartSector);
    if ( sithIntersect_IsSphereInSector(sithWorld_g_pCurrentWorld, endPos, 0.0f, pStartSector) )
    {
        return pStartSector; // Shall returned sector be null here?
    }

    moveNorm.x = endPos->x - startPos->x;
    moveNorm.y = endPos->y - startPos->y;
    moveNorm.z = endPos->z - startPos->z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);

    pSector = pStartSector;
    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, &moveNorm, moveDist, radius, 1);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) == 0 )
        {
            endPos->x = pCollision->distance * moveNorm.x + startPos->x;
            endPos->y = pCollision->distance * moveNorm.y + startPos->y;
            endPos->z = pCollision->distance * moveNorm.z + startPos->z;
            break;
        }

        SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin != ((void*)0));
        pSector = pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector;
    }

    sithCollision_DecreaseStackLevel();
    return pSector;
}

SithSector* J3DAPI sithCollision_FindSectorAtThing(SithThing* pThing, SithSector* pStartSector, const rdVector3* startPos, rdVector3* endPos, float radius)
{
    SithSector* pSector;
    float moveDist;
    SithCollision* pCollision;
    rdVector3 moveNorm;

    SITH_ASSERTREL(startPos && endPos && pStartSector);
    moveNorm.x = endPos->x - startPos->x;
    moveNorm.y = endPos->y - startPos->y;
    moveNorm.z = endPos->z - startPos->z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);

    pSector = pStartSector;
    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, &moveNorm, moveDist, radius, 0);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) != 0
            && (pCollision->pSurfaceCollided->pAdjoin->flags & SITH_ADJOIN_NOPLAYERMOVE) == 0
            && (pCollision->pSurfaceCollided->pAdjoin->flags & SITH_ADJOIN_MOVE) != 0 )
        {
            SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin != ((void*)0));
            pSector = pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector;
        }
        else if ( (pCollision->type & SITHCOLLISION_THING) == 0 || pCollision->pThingCollided != pThing )
        {
            endPos->x = (pCollision->distance - 0.001f) * moveNorm.x + startPos->x;
            endPos->y = (pCollision->distance - 0.001f) * moveNorm.y + startPos->y;
            endPos->z = (pCollision->distance - 0.001f) * moveNorm.z + startPos->z;
            break;
        }
    }

    sithCollision_DecreaseStackLevel();
    return pSector;
}

SithSector* J3DAPI sithCollision_FindWaterSector(SithSector* pStartSector, rdVector3* startPos, rdVector3* endPos, float radius)
{
    SithSector* pSector;
    float moveDist;
    SithCollision* pCollision;
    rdVector3 moveNorm;

    SITH_ASSERTREL(startPos && endPos && pStartSector);
    if ( sithIntersect_IsSphereInSector(sithWorld_g_pCurrentWorld, endPos, 0.0f, pStartSector) )
    {
        return pStartSector;
    }

    moveNorm.x = endPos->x - startPos->x;
    moveNorm.y = endPos->y - startPos->y;
    moveNorm.z = endPos->z - startPos->z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);

    pSector = pStartSector;
    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, &moveNorm, moveDist, radius, 1);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & (SITHCOLLISION_WORLD | SITHCOLLISION_ADJOINTOUCH)) != 0
            && (pCollision->pSurfaceCollided->flags & SITH_SURFACE_WATER) != 0
            && (pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector->flags & SITH_SECTOR_UNDERWATER) != 0 )
        {
            endPos->x = pCollision->distance * moveNorm.x + startPos->x;
            endPos->y = pCollision->distance * moveNorm.y + startPos->y;
            endPos->z = pCollision->distance * moveNorm.z + startPos->z;
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) == 0 )// Note, here will return sector which might not be water sector for any collision it finds but adjoin collision
        {
            endPos->x = pCollision->distance * moveNorm.x + startPos->x;
            endPos->y = pCollision->distance * moveNorm.y + startPos->y;
            endPos->z = pCollision->distance * moveNorm.z + startPos->z;
            break;
        }

        SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin != ((void*)0));
        pSector = pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector;
    }

    sithCollision_DecreaseStackLevel();
    return pSector;
}

int J3DAPI sithCollision_sub_4D5EB3(SithSector* pStartSector, const rdVector3* startPos, const rdVector3* endPos, float radius)
{
    rdVector3 moveNorm;
    float moveDist;

    moveNorm.x = endPos->x - startPos->x;
    moveNorm.y = endPos->y - startPos->y;
    moveNorm.z = endPos->z - startPos->z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);
    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, &moveNorm, moveDist, radius, 0x12A);
    if ( sithCollision_PopStack() )
    {
        sithCollision_DecreaseStackLevel();
        return 0;
    }
    else
    {
        sithCollision_DecreaseStackLevel();
        return 1;
    }
}

int J3DAPI sithCollision_CanMoveToPos(SithSector* pStartSector, const rdVector3* startPos, const rdVector3* endPos, float radius)
{
    SithCollision* pCollision;
    int bCanMove;
    rdVector3 moveNorm;
    float moveDist;

    bCanMove = 1;
    moveNorm.x = endPos->x - startPos->x;
    moveNorm.y = endPos->y - startPos->y;
    moveNorm.z = endPos->z - startPos->z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);

    sithCollision_SearchForCollisions(pStartSector, NULL, startPos, &moveNorm, moveDist, radius, 0x4120);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) == 0 || (pCollision->pSurfaceCollided->pAdjoin->flags & SITH_ADJOIN_MOVE) == 0 )
        {
            bCanMove = 0;
            break;
        }
    }

    sithCollision_DecreaseStackLevel();
    return bCanMove;
}

int J3DAPI sithCollision_HasLOS(const SithThing* pViewer, const SithThing* pTarget, int a3)
{
    int v3;
    SithCollision* pCollision;
    int bLos;
    rdVector3 moveNorm;
    float moveDist;
    int searchFlags;

    bLos = 1;
    searchFlags = 0x6120;
    SITH_ASSERTREL(pViewer && pTarget);
    if ( a3 )
    {
        v3 = searchFlags;
        v3 = searchFlags & ~0x100;    // 0x100
        searchFlags = v3;
    }

    moveNorm.x = pTarget->pos.x - pViewer->pos.x;
    moveNorm.y = pTarget->pos.y - pViewer->pos.y;
    moveNorm.z = pTarget->pos.z - pViewer->pos.z;
    moveDist = rdVector_Normalize3Acc(&moveNorm);

    sithCollision_SearchForCollisions(pViewer->pInSector, NULL, &pViewer->pos, &moveNorm, moveDist, 0.0f, searchFlags);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
        {
            if ( pCollision->pThingCollided == pTarget )
            {
                bLos = 1;
                break;
            }

            if ( pCollision->pThingCollided != pViewer )
            {
                bLos = 0;
                break;
            }
        }

        else if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) == 0 || (pCollision->pSurfaceCollided->pAdjoin->flags & SITHCOLLISION_ADJOINCROSS) == 0 )
        {
            bLos = 0;
            break;
        }
    }

    sithCollision_DecreaseStackLevel();
    return bLos;
}

void J3DAPI sithCollision_RotateThing(SithThing* pThing, const rdMatrix34* pOrient)
{
    rdVector3 dir;
    float moveDist;
    SithThing* pAttachedThing;
    rdVector3 moveNorm;

    moveDist = 0.0f;
    rdMatrix_PreMultiply34(&pThing->orient, pOrient);

    for ( pAttachedThing = pThing->pAttachedThing; pAttachedThing; pAttachedThing = pAttachedThing->pNextAttachedThing )
    {
        dir.x = pAttachedThing->pos.x - pThing->pos.x;
        dir.y = pAttachedThing->pos.y - pThing->pos.y;
        dir.z = pAttachedThing->pos.z - pThing->pos.z;
        memcpy(&pAttachedThing->orient.dvec, &dir, sizeof(pAttachedThing->orient.dvec));
        sithCollision_RotateThing(pAttachedThing, pOrient);

        if ( (pAttachedThing->attach.flags & SITH_ATTACH_NOMOVE) == 0 )
        {
            moveNorm.x = pAttachedThing->orient.dvec.x - dir.x;
            moveNorm.y = pAttachedThing->orient.dvec.y - dir.y;
            moveNorm.z = pAttachedThing->orient.dvec.z - dir.z;
            if ( moveNorm.x != 0.0f || moveNorm.y != 0.0f || moveNorm.z != 0.0f )
            {
                moveDist = rdVector_Normalize3Acc(&moveNorm);
                sithCollision_MoveThing(pAttachedThing, &moveNorm, moveDist, 0);
            }
        }

        memset(&pAttachedThing->orient.dvec, 0, sizeof(pAttachedThing->orient.dvec));
    }
}

void J3DAPI sithCollision_sub_4A6EE0(SithThing* pThing, rdMatrix34* pOrient)
{
    SithPhysicsFlags flags;
    SithThing* pNextAttachedThing;
    rdMatrix34 mat;
    float moveDist;
    rdMatrix34 orient;
    SithThing* pAttachedThing;
    rdVector3 moveNorm;

    if ( pThing->pAttachedThing )
    {
        rdMatrix_Normalize34(pOrient);
        rdVector_Copy3(&pOrient->dvec, &pThing->pos);
        rdVector_Copy3(&pThing->orient.dvec, &pThing->pos);
        rdMatrix_InvertOrtho34(&orient, &pThing->orient);

        for ( pAttachedThing = pThing->pAttachedThing; pAttachedThing; pAttachedThing = pNextAttachedThing )
        {
            pNextAttachedThing = pAttachedThing->pNextAttachedThing;

            rdVector_Copy3(&pAttachedThing->orient.dvec, &pAttachedThing->pos);

            rdMatrix_Multiply34(&mat, &orient, &pAttachedThing->orient);
            rdMatrix_PostMultiply34(&mat, pOrient);

            /*moveNorm.x = mat.dvec.x - pAttachedThing->pos.x;
            moveNorm.y = mat.dvec.y - pAttachedThing->pos.y;
            moveNorm.z = mat.dvec.z - pAttachedThing->pos.z;*/
            rdVector_Sub3(&moveNorm, &mat.dvec, &pAttachedThing->pos);
            moveDist = rdVector_Normalize3Acc(&moveNorm);

            memset(&mat.dvec, 0, sizeof(mat.dvec));
            if ( moveDist != 0.0f )
            {
                sithCollision_MoveThing(pAttachedThing, &moveNorm, moveDist, 0x40);
            }

            sithCollision_sub_4A6EE0(pAttachedThing, &mat);
            if ( pAttachedThing->moveType == SITH_MT_PHYSICS )
            {
                flags = pAttachedThing->moveInfo.physics.flags;
                flags &= ~SITH_PF_ALIGNED;            // 0x100 - SITH_PF_ALIGNED
                pAttachedThing->moveInfo.physics.flags = flags;
            }
        }
    }

    else if ( (((uint8_t)sithMain_g_frameNumber + (uint8_t)pThing->idx) & 7) == 0 )// Visible ?
    {
        rdMatrix_Normalize34(pOrient);
    }

    memset(&pOrient->dvec, 0, sizeof(pOrient->dvec));
    rdMatrix_Copy34(&pThing->orient, pOrient);
}

float J3DAPI sithCollision_MoveThing(SithThing* pThing, const rdVector3* moveNorm, float moveDist, int flags)
{
    float damage;
    BOOL v11;
    SithThingMoveStatus moveStatus;
    float v17;
    float v18;
    float v19;
    rdVector3 curthPos;
    int bCollided;
    float v26;
    int moveToResult;
    float v30;
    rdVector3 v31;

    rdVector3 dest;
    rdVector3 prevAttPos;
    rdVector3 v40;
    float distMoved;
    SithMoveInfo* pMoveInfo;
    int v43;
    float v44;
    rdVector3 prevPos;
    float v46;
    SithThing* pAttached;
    unsigned int v49;
    float v50;

    v49 = 0;
    v46 = 0.0f;
    v44 = 0.0f;
    pMoveInfo = &pThing->moveInfo;
    SITH_ASSERTREL(bCollideStartup);
    SITH_ASSERTREL(sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing));

    if ( moveDist > 0.0f )
    {
        rdVector_Copy3(&dest, moveNorm);
        if ( pThing->collide.type == SITH_COLLIDE_NONE )
        {
            flags |= 5u;
        }

        if ( pThing->moveType == SITH_MT_PATH )
        {
            /*v2 = flags;
            (v2 & 0xFF) = flags | 4;
            flags = v2;*/
            flags |= 0x04;
        }

        if ( (flags & 0x01) == 0 )
        {
            /*v6 = flags;
            v6 = flags | 0x800;
            flags = v6;*/
            flags |= 0x800;
        }

        if ( pThing->type == SITH_THING_PLAYER )
        {
            /*v7 = flags;
            v7 = flags | 0x8000;
            flags = v7;*/
            flags |= 0x8000;
        }

        for ( pAttached = pThing->pAttachedThing; pAttached; pAttached = pAttached->pNextAttachedThing )
        {
            if ( (pAttached->attach.flags & SITH_ATTACH_NOMOVE) == 0 )
            {
                if ( pAttached->type == SITH_THING_PLAYER && pAttached->thingInfo.actorInfo.bForceMovePlay )
                {
                    rdVector_Copy3(&prevAttPos, &pAttached->pos);
                }

                distMoved = sithCollision_MoveThing(pAttached, moveNorm, moveDist, 0x40);
                if ( pAttached->type == SITH_THING_PLAYER )
                {
                    rdVector3 dAttPos;
                    rdVector_Sub3(&dAttPos, &prevAttPos, &pAttached->pos);
                    /* v32 = prevAttPos.x - pVictim->pos.x;
                     v33 = prevAttPos.y - pVictim->pos.y;
                     v34 = prevAttPos.z - pVictim->pos.z;*/
                    if ( pAttached->thingInfo.actorInfo.bForceMovePlay )
                    {
                        pAttached->forceMoveStartPos.x = pAttached->forceMoveStartPos.x + dAttPos.x;
                        pAttached->forceMoveStartPos.y = pAttached->forceMoveStartPos.y + dAttPos.y;
                        pAttached->forceMoveStartPos.z = pAttached->forceMoveStartPos.z + dAttPos.z;
                    }
                }

                if ( distMoved < moveDist )
                {
                    if ( (pAttached->attach.flags & SITH_ATTACH_THINGFACE) == 0
                        || ((rdMatrix_TransformVector34(&v31, &pAttached->attach.pFace->normal, &pThing->orient),
                            v30 = rdVector_Dot3(moveNorm, &v31),
                            v30 >= 0.0f)
                            ? (v18 = v30)
                            : (v18 = -v30),
                            v18 <= 0.0000099999997f ? (v17 = 0.0f) : (v17 = v30),
                            v17 > 0.0f) )
                    {
                        if ( (pThing->flags & SITH_TF_NOCRUSH) == 0 )
                        {
                            damage = (moveDist - distMoved) * 100.0f;
                            sithThing_DamageThing(pAttached, pThing, damage, SITH_DAMAGE_IMPACT);
                        }

                        moveDist = distMoved;
                    }
                }
            }
        }

        sithCollision_dword_17F1090 = 0;
        if ( pThing != sithPlayer_g_pLocalPlayerThing )
        {
            goto LABEL_61;
        }

        if ( (pMoveInfo->physics.flags & (SITH_PF_UNKNOWN_8000000 | SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) != 0 )
            // if ((pMoveInfo->physics.flags & 0xF000000) != 0)
        {
            goto LABEL_61;
        }

        moveStatus = pThing->moveStatus;
        if ( moveStatus <= SITHPLAYERMOVE_STILL || moveStatus > SITHPLAYERMOVE_UNKNOWN_5 )
        {
            goto LABEL_61;
        }

        if ( (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0 || (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 )
        {
            pThing->moveStatus = SITHPLAYERMOVE_SWIMIDLE;
            goto LABEL_61;
        }

        rdVector3 moveToPos;
        if ( pThing->attach.flags
            && ((memcpy(&prevPos, &pThing->pos, sizeof(prevPos)), pThing->moveStatus != SITHPLAYERMOVE_WALKING) && pThing->moveStatus != SITHPLAYERMOVE_RUNNING
                ? (moveToPos.x = (pThing->collide.movesize * 3.0f) * moveNorm->x + prevPos.x,
                    moveToPos.y = (pThing->collide.movesize * 3.0f) * moveNorm->y + prevPos.y,
                    moveToPos.z = (pThing->collide.movesize * 3.0f) * moveNorm->z + prevPos.z)
                : (moveToPos.x = pThing->collide.movesize * moveNorm->x + prevPos.x,
                    moveToPos.y = pThing->collide.movesize * moveNorm->y + prevPos.y,
                    moveToPos.z = pThing->collide.movesize * moveNorm->z + prevPos.z),
                (moveToResult = sithPlayerActions_CanMoveToPos(pThing, &moveToPos, &v43)) == 0 || moveToResult == 3) )
        {
            if ( pThing->moveStatus == SITHPLAYERMOVE_RUNNING )
            {
                if ( moveToResult == 3 )
                {
                    memset(&pMoveInfo->physics.deltaVelocity, 0, sizeof(pMoveInfo->physics.deltaVelocity));
                    sithPuppet_g_bPlayerLeapForward = 0;
                    return 0.0f;
                }
                else
                {
                    if ( sithPuppet_g_bPlayerLeapForward != 1 )
                    {
                        goto LABEL_61;
                    }

                    pThing->moveStatus = SITHPLAYERMOVE_LEAPFWD;
                    sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_LEAPLEFT, 0);
                    sithPuppet_g_bPlayerLeapForward = 0;
                    return moveDist;
                }
            }
            else
            {
                if ( pThing->moveStatus == SITHPLAYERMOVE_WALKING )
                {
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                }

                memset(&pMoveInfo->physics.deltaVelocity, 0, sizeof(pMoveInfo->physics.deltaVelocity));
                sithPuppet_g_bPlayerLeapForward = 0;
                sithPhysics_ResetThingMovement(pThing);
                return 0.0f;
            }
        }
        else
        {
        LABEL_61:
            SithSector* pPrevSector = NULL;
            while ( moveDist != 0.0f && v49 < 4 )
            {
                bCollided = 0;
                rdVector_Copy3(&prevPos, &pThing->pos);

                pPrevSector = pThing->pInSector;
                v50 = moveDist;

                rdVector_Copy3(&v40, &dest);


                float distance = 0.0f; // Added: Init to 0
                v26 = sithCollision_SearchForCollisions(pThing->pInSector, pThing, &pThing->pos, &dest, moveDist, pThing->collide.movesize, flags);
                while ( !bCollided )
                {
                    SithCollision* pCollision = sithCollision_PopStack();
                    if ( !pCollision )
                    {
                        break;
                    }

                    distance = pCollision->distance;
                    if ( distance != 0.0f )
                    {
                        pThing->pos.x = dest.x * distance + prevPos.x;
                        pThing->pos.y = dest.y * distance + prevPos.y;
                        pThing->pos.z = dest.z * distance + prevPos.z;
                    }

                    if ( distance >= moveDist )
                    {
                        memset(&pThing->moveDir, 0, sizeof(pThing->moveDir));
                    }
                    else
                    {
                        pThing->moveDir.x = (moveDist - distance) * dest.x;
                        pThing->moveDir.y = (moveDist - distance) * dest.y;
                        pThing->moveDir.z = (moveDist - distance) * dest.z;
                        if ( pThing->moveType == SITH_MT_PHYSICS
                            && (pThing->moveInfo.physics.flags & SITH_PF_SURFACEBOUNCE) != 0
                            && (pThing->moveInfo.physics.gravityForce.x != 0.0f
                                || pThing->moveInfo.physics.gravityForce.y != 0.0f
                                || pThing->moveInfo.physics.gravityForce.z != 0.0f) )
                        {
                            v44 = 1.0f - distance / moveDist;
                            pThing->moveInfo.physics.velocity.x = pThing->moveInfo.physics.gravityForce.x * -v44 + pThing->moveInfo.physics.velocity.x;
                            pThing->moveInfo.physics.velocity.y = pThing->moveInfo.physics.gravityForce.y * -v44 + pThing->moveInfo.physics.velocity.y;
                            pThing->moveInfo.physics.velocity.z = pThing->moveInfo.physics.gravityForce.z * -v44 + pThing->moveInfo.physics.velocity.z;
                        }
                    }

                    if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
                    {
                        SITH_ASSERTREL(pCollision->pSurfaceCollided == ((void*)0));
                        SITH_ASSERTREL(pCollision->pThingCollided != ((void*)0));

                        SithThingType type2 = pCollision->pThingCollided->type;
                        SithThingType type1 = pThing->type;
                        SITH_ASSERTREL(aCollideResults[type1][type2].pProcessFunc != ((void*)0));

                        if ( aCollideResults[type1][type2].bDifferentTypHandler )
                        {
                            bCollided = aCollideResults[type1][type2].pProcessFunc(pCollision->pThingCollided, pThing, pCollision, 1);
                        }
                        else
                        {
                            bCollided = aCollideResults[type1][type2].pProcessFunc(pThing, pCollision->pThingCollided, pCollision, 0);
                        }
                    }
                    else if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) != 0 )
                    {
                        SITH_ASSERTREL(pCollision->pSurfaceCollided != ((void*)0));
                        SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin != ((void*)0));
                        SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin->pMirrorAdjoin != ((void*)0));
                        SITH_ASSERTREL(pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector != ((void*)0));

                        rdVector_Copy3(&curthPos, &pThing->pos);
                        if ( (pCollision->pSurfaceCollided->flags & SITH_SURFACE_COGLINKED) != 0 )
                        {
                            sithCog_SurfaceSendMessage(pCollision->pSurfaceCollided, pThing, 8);
                        }

                        sithThing_SetSector(pThing, pCollision->pSurfaceCollided->pAdjoin->pAdjoinSector, 0);
                        bCollided = memcmp(&curthPos, &pThing->pos, sizeof(curthPos)) != 0;
                    }
                    else
                    {
                        SITH_ASSERTREL(pCollision->pThingCollided == ((void*)0));
                        SITH_ASSERTREL(pCollision->pSurfaceCollided != ((void*)0));

                        if ( sithCollision_aThingSurfaceCollideResults[pThing->type] )
                        {
                            bCollided = sithCollision_aThingSurfaceCollideResults[pThing->type](pThing, pCollision->pSurfaceCollided, pCollision);
                        }
                        else
                        {
                            bCollided = sithCollision_HandleThingHitSurface(pThing, pCollision->pSurfaceCollided, pCollision);
                        }
                    }

                    if ( v44 != 0.0f )
                    {
                        v19 = sithTime_g_frameTimeFlex * v44;
                        pThing->moveDir.x = pThing->moveInfo.physics.velocity.x * v19;
                        pThing->moveDir.y = pThing->moveInfo.physics.velocity.y * v19;
                        pThing->moveDir.z = pThing->moveInfo.physics.velocity.z * v19;
                        v44 = 0.0f;
                    }
                }

                sithCollision_DecreaseStackLevel();
                if ( bCollided )
                {
                    v46 = v46 + distance;
                    if ( pThing->moveDir.x == 0.0f && pThing->moveDir.y == 0.0f && pThing->moveDir.z == 0.0f )
                    {
                        moveDist = 0.0f;
                    }
                    else
                    {
                        moveDist = stdMath_ClipNearZero(rdVector_Normalize3(&dest, &pThing->moveDir));
                    }

                    ++v49;
                }
                else
                {
                    pThing->pos.x = dest.x * moveDist + prevPos.x;
                    pThing->pos.y = dest.y * moveDist + prevPos.y;
                    pThing->pos.z = dest.z * moveDist + prevPos.z;

                    memset(&pThing->moveDir, 0, sizeof(pThing->moveDir));
                    v46 = v46 + moveDist;
                    moveDist = 0.0f;
                }

                if ( (pThing->flags & SITH_TF_DESTROYED) != 0 )
                {
                    return v46;
                }
            }

            if ( v49 >= 4 && pThing->moveType == SITH_MT_PHYSICS )
            {
                sithPhysics_ResetThingMovement(pThing);
            }


            v46 = stdMath_ClipNearZero(fabsf(v46));

            if ( pThing->collide.type
                && pThing->moveType == SITH_MT_PHYSICS
                && (pThing->attach.flags & SITH_ATTACH_TAIL) == 0
                && (pThing->type != SITH_THING_PLAYER || pThing->thingInfo.actorInfo.bForceMovePlay != 1)
                && !sithIntersect_IsSphereInSector(sithWorld_g_pCurrentWorld, &pThing->pos, 0.0f, pThing->pInSector) )
            {
                if ( pThing->msecLifeLeft )
                {
                    SITHLOG_ERROR("Thing %s fell out of world, destroying.\n", pThing->aName);
                    sithThing_DestroyThing(pThing);
                }
                else if ( pThing->type == SITH_THING_PLAYER )
                {
                    SITHLOG_ERROR("Thing %s in wrong sector, pushed back to last good position.\n", pThing->aName);
                }

                rdVector_Copy3(&pThing->pos, &prevPos);
                rdVector_Copy3(&dest, &v40);
                sithThing_SetSector(pThing, pPrevSector, 0);
            }

            for ( pAttached = pThing->pAttachedThing; pAttached; pAttached = pAttached->pNextAttachedThing )
            {
                if ( (pAttached->attach.flags & SITH_ATTACH_NOMOVE) != 0 && (pAttached->attach.flags & SITH_ATTACH_TAIL) == 0 )
                {
                    rdMatrix_TransformVector34(&pAttached->pos, &pAttached->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing, &pThing->orient);
                    rdVector_Add3Acc(&pAttached->pos, &pThing->pos);
                    /*pAttached->pos.x = pAttached->pos.x + pThing->pos.x;
                    pAttached->pos.y = pAttached->pos.y + pThing->pos.y;
                    pAttached->pos.z = pAttached->pos.z + pThing->pos.z;*/

                    if ( pAttached->pInSector != pThing->pInSector )
                    {
                        sithThing_SetSector(pAttached, pThing->pInSector, 0);
                    }
                }
            }

            if ( pThing->moveType == SITH_MT_PHYSICS )
            {
                if ( v46 == 0.0f )
                {
                    return 0.0f;
                }
                else if ( (flags & 0x40) != 0 )
                {
                    return v46;
                }
                else
                {
                    switch ( pThing->moveStatus )
                    {
                        case SITHPLAYERMOVE_HANGING:
                        case SITHPLAYERMOVE_CLIMBIDLE:
                        case SITHPLAYERMOVE_WHIPSWINGING:
                        case SITHPLAYERMOVE_WHIPCLIMBIDLE:
                        case SITHPLAYERMOVE_JUMPFWD:
                        case SITHPLAYERMOVE_JUMPUP:
                        case SITHPLAYERMOVE_CLIMBING_UP:
                        case SITHPLAYERMOVE_CLIMBING_DOWN:
                        case SITHPLAYERMOVE_CLIMBING_LEFT:
                        case SITHPLAYERMOVE_CLIMBING_RIGHT:
                        case SITHPLAYERMOVE_PULLINGUP:
                        case SITHPLAYERMOVE_WHIP_CLIMB_START:
                        case SITHPLAYERMOVE_JEEP_STILL:
                        case SITHPLAYERMOVE_RAFT_STILL:
                        case SITHPLAYERMOVE_RAFT_PADDLE_FORWARD_LEFT:
                        case SITHPLAYERMOVE_RAFT_PADDLE_FORWARD_RIGHT:
                        case SITHPLAYERMOVE_RAFT_TURN_LEFT:
                        case SITHPLAYERMOVE_RAFT_TURN_RIGHT:
                        case SITHPLAYERMOVE_RAFT_PADDLE_BACK_LEFT:
                        case SITHPLAYERMOVE_RAFT_PADDLE_BACK_RIGHT:
                        case SITHPLAYERMOVE_RAFT_STARTPADDLE_LEFT:
                        case SITHPLAYERMOVE_RAFT_ENDPADDLE_LEFT:
                        case SITHPLAYERMOVE_RAFT_ENDPADDLE_RIGHT:
                        case SITHPLAYERMOVE_RAFT_STARTPADDLE_RIGHT:
                        case SITHPLAYERMOVE_RAFT_PADDLERIGHT_STARTPADDLE_LEFT:
                        case SITHPLAYERMOVE_RAFT_PADDLEL_LEFT_STARTPADDLE_RIGHT:
                        case SITHPLAYERMOVE_JEEP_BOARDING:
                        case SITHPLAYERMOVE_STAND_TO_CRAWL:
                        case SITHPLAYERMOVE_CRAWL_TO_STAND:
                        case SITHPLAYERMOVE_CLIMB_DOWN_TO_MOUNT:
                        case SITHPLAYERMOVE_CLIMB_TO_HANG:
                        case SITHPLAYERMOVE_RAFT_BOARDING:
                        case SITHPLAYERMOVE_RAFT_UNBOARDING_LEFT:
                        case SITHPLAYERMOVE_RAFT_UNBOARDING_RIGHT:
                        case SITHPLAYERMOVE_RAFT_UNBOARD_START:
                        case SITHPLAYERMOVE_UNKNOWN_82:
                        case SITHPLAYERMOVE_UNKNOWN_84:
                        case SITHPLAYERMOVE_JEEP_UNBOARDING:
                        case SITHPLAYERMOVE_JEWELFLYING:
                        case SITHPLAYERMOVE_JEWELFLYING_UNKN1:
                        case SITHPLAYERMOVE_JEWELFLYING_UNKN2:
                        case SITHPLAYERMOVE_LEAPFWD:
                            return v46;

                        default:
                            if ( (pThing->moveInfo.physics.flags & SITH_PF_RAFT) == 0
                                && (!pThing->pAttachedThing || (pThing->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) == 0)
                                && (pThing->attach.flags & SITH_ATTACH_TAIL) == 0 )
                            {
                                if ( pThing->attach.flags && (pThing->attach.flags & SITH_ATTACH_NOMOVE) == 0
                                    || (pThing->moveInfo.physics.flags & SITH_PF_FLOORSTICK) != 0
                                    && (pThing->moveInfo.physics.velocity.z < -2.0f ? (v11 = 0) : (v11 = pThing->moveInfo.physics.velocity.z <= 0.2f), v11) )
                                {
                                    sithPhysics_FindFloor(pThing, 0);
                                }
                            }

                            break;
                    }

                    return v46;
                }
            }
            else
            {
                return v46;
            }
        }
    }
    else
    {
        SITHLOG_ERROR("MoveThing called for %s with distance %f.\n", pThing->aName, moveDist);
        return 0.0f;
    }
}

float J3DAPI sithCollision_SearchForCollisions(SithSector* pStartSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags)
{
    SithSector* pCurSector;
    unsigned int secNum;
    SithSurfaceAdjoin* i;
    unsigned int numSectors;
    SithCollision* pCollision;
    SithSurfaceAdjoin* pAdjoin;
    unsigned int collNum;

    SITH_ASSERTREL((pStartSector) && (startPos) && (moveNorm));
    SITH_ASSERTREL((moveDist >= 0.0f) && (radius >= 0.0f));

    stackLevel++;
    SITH_ASSERTREL(stackLevel >= 0);
    SITH_ASSERTREL(stackLevel < SITHCOLLISION_STACKSIZE);

    sithCollision_ResetCurStack();
    moveDist = sithCollision_BuildCollisionList(pStartSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);

    collNum = 0;
    pCollision = sithCollision_aCollisions[stackLevel];
    while ( collNum < sithCollision_aNumStackCollisions[stackLevel] )
    {
        if ( pCollision->type == SITHCOLLISION_WORLD )
        {
            pAdjoin = pCollision->pSurfaceCollided->pAdjoin;
            SITH_ASSERTREL(pAdjoin);
            SITH_ASSERTREL(pAdjoin->pMirrorAdjoin != ((void*)0));
            SITH_ASSERTREL(pAdjoin->pAdjoinSector != ((void*)0));
            if ( (searchFlags & 0x400) != 0 || pCollision->distance <= moveDist )
            {
                moveDist = sithCollision_BuildCollisionList(pAdjoin->pAdjoinSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);
            }

            pCollision->bEnumerated = 1;
        }

        ++collNum;
        ++pCollision;
    }

    if ( moveDist == 0.0f || (searchFlags & 0x800) == 0 )
    {
        return moveDist;
    }

    numSectors = sithCollision_aNumSearchedSectors[stackLevel];
    secNum = 0;
    pCurSector = sithCollision_apSearchedSectors[stackLevel][0];
    while ( secNum < numSectors )
    {
        for ( i = pCurSector->pFirstAdjoin; i; i = i->pNextAdjoin )
        {
            if ( (i->flags & SITH_ADJOIN_MOVE) != 0
                && i->pAdjoinSector->pFirstThingInSector
                && !sithCollision_CheckSectorSearched(i->pAdjoinSector)
                && sithCollision_AddSearchedSector(i->pAdjoinSector) )
            {
                moveDist = sithCollision_SearchForThingCollisions(i->pAdjoinSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);
            }
        }

        pCurSector = sithCollision_apSearchedSectors[stackLevel][++secNum];
    }

    return moveDist;
}

void sithCollision_DecreaseStackLevel(void)
{
    SITH_ASSERTREL(stackLevel >= 0);
    SITH_ASSERTREL(stackLevel < SITHCOLLISION_STACKSIZE);
    --stackLevel;
}

float J3DAPI sithCollision_SearchForThingCollisions(const SithSector* pSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags)
{
    SithThing* pCurThing;
    float pHitDistance;
    rdFace* ppHitFace;
    rdModel3Mesh* ppHitMesh;
    SithCollisionType hitType;
    rdVector3 Src;

    ppHitMesh = 0;
    ppHitFace = 0;
    if ( sithWorld_g_pCurrentWorld )
    {
        SITH_ASSERTREL(sithSector_ValidateSectorPointer(sithWorld_g_pCurrentWorld, pSector));
        SITH_ASSERTREL(!pThing || sithThing_ValidateThingPointer(sithWorld_g_pCurrentWorld, pThing));
    }

    for ( pCurThing = pSector->pFirstThingInSector; pCurThing; pCurThing = pCurThing->pNextThingInSector )
    {
        if ( ((searchFlags & 8) == 0 || (pCurThing->flags & SITH_TF_MOUNTABLE) != 0)
            && ((searchFlags & 0x10) == 0 || (pCurThing->flags & SITH_TF_STANDON) != 0)
            && ((searchFlags & 0x4000) == 0
                || pCurThing->type != SITH_THING_PLAYER
                && pCurThing->type != SITH_THING_ACTOR
                && pCurThing->type != SITH_THING_WEAPON
                && pCurThing->type != SITH_THING_DEBRIS
                && (pCurThing->flags & (SITH_TF_INVISIBLE | SITH_TF_NOWEAPONCOLLIDE)) == 0)
            && sithCollision_sub_4DABF1(pCurThing, searchFlags)
            && (!pThing || sithCollision_sub_4DAC4B(pThing, pCurThing, searchFlags)) )
        {
            hitType = sithIntersect_CheckSphereThingIntersection(
                pThing,
                startPos,
                moveNorm,
                moveDist,
                radius,
                pCurThing,
                searchFlags,
                &pHitDistance,
                &ppHitMesh,
                &ppHitFace,
                &Src);
            if ( hitType )
            {
                sithCollision_PushThingCollision(pCurThing, pHitDistance, (SithCollisionType)(hitType | SITHCOLLISION_THING), ppHitMesh, ppHitFace, &Src);
                if ( pThing )
                {
                    if ( sithCollision_sub_4DB3CA(pThing, pCurThing) )
                    {
                        moveDist = pHitDistance;
                    }
                }
            }
        }
    }

    return moveDist;
}

void J3DAPI sithCollision_SearchForSurfaceCollisions(const SithSector* pSector, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int colflags)
{
    float pHitDist;
    SithSurfaceAdjoin* pAdjoin;
    SithSurface* pCurSurf;
    rdVector3 v9;
    unsigned int surfNum;
    rdVector3 hitNorm;
    SithCollisionType hitType;
    SithWorld* pWorld;
    float distance;

    pWorld = sithWorld_g_pCurrentWorld;
    SITH_ASSERTREL(sithSector_ValidateSectorPointer(sithWorld_g_pCurrentWorld, pSector));
    SITH_ASSERTREL(radius >= 0.0f);
    SITH_ASSERTREL(moveDist >= 0.0f);
    v9.x = moveNorm->x * moveDist + startPos->x;
    v9.y = moveNorm->y * moveDist + startPos->y;
    v9.z = moveNorm->z * moveDist + startPos->z;
    if ( (pSector->flags & SITH_SECTOR_HASCOLLIDEBOX) == 0
        || v9.z - radius <= pSector->collideBox.v0.z
        || v9.y - radius <= pSector->collideBox.v0.y
        || v9.x - radius <= pSector->collideBox.v0.x
        || v9.x + radius >= pSector->collideBox.v1.x
        || v9.y + radius >= pSector->collideBox.v1.y
        || v9.z + radius >= pSector->collideBox.v1.z )
    {
        surfNum = 0;
        pCurSurf = pSector->pFirstSurface;
        while ( surfNum < pSector->numSurfaces )
        {
            pAdjoin = pCurSurf->pAdjoin;
            if ( (pCurSurf->flags & SITH_SURFACE_COLLISION) != 0 || pAdjoin )
            {
                if ( pAdjoin && sithCollision_sub_4DB49F(pAdjoin->flags, colflags) )
                {
                    hitType = sithIntersect_CheckSphereFaceIntersection(
                        startPos,
                        moveNorm,
                        moveDist,
                        radius,
                        &pCurSurf->face,
                        pWorld->aVertices,
                        &pHitDist,
                        colflags);
                    if ( hitType )
                    {
                        if ( ((colflags & 4) == 0 || (colflags & 1) == 0) && !sithCollision_CheckSectorSearched(pAdjoin->pAdjoinSector) )
                        {
                            sithCollision_PushSurfaceCollision(pCurSurf, pHitDist, SITHCOLLISION_WORLD, 0);
                        }

                        if ( (colflags & 2) == 0
                            && sithIntersect_CheckSphereFaceIntersection(
                                startPos,
                                moveNorm,
                                moveDist,
                                0.0f,
                                &pCurSurf->face,
                                pWorld->aVertices,
                                &distance,
                                colflags) )
                        {
                            if ( (colflags & 4) != 0 && (colflags & 1) != 0 && !sithCollision_CheckSectorSearched(pAdjoin->pAdjoinSector) )
                            {
                                sithCollision_PushSurfaceCollision(pCurSurf, pHitDist, SITHCOLLISION_WORLD, 0);
                            }

                            sithCollision_PushSurfaceCollision(pCurSurf, distance, SITHCOLLISION_ADJOINTOUCH, 0);
                        }
                    }
                }

                else if ( (colflags & 4) == 0
                    && ((colflags & 0x10) == 0 || (pCurSurf->flags & SITH_SURFACE_ISFLOOR) != 0)
                    && (v9.x - pWorld->aVertices[*pCurSurf->face.aVertices].x) * pCurSurf->face.normal.x
                    + (v9.y - pWorld->aVertices[*pCurSurf->face.aVertices].y) * pCurSurf->face.normal.y
                    + (v9.z - pWorld->aVertices[*pCurSurf->face.aVertices].z) * pCurSurf->face.normal.z <= radius )
                {
                    hitType = sithIntersect_CheckSphereFaceIntersectionEx(
                        startPos,
                        moveNorm,
                        moveDist,
                        radius,
                        &pCurSurf->face,
                        pWorld->aVertices,
                        &pHitDist,
                        &hitNorm,
                        colflags);
                    if ( hitType )
                    {
                        if ( (colflags & 0x400) != 0 || rdVector_Dot3(moveNorm, &hitNorm) < 0.0f )
                        {
                            sithCollision_PushSurfaceCollision(pCurSurf, pHitDist, (SithCollisionType)(hitType | SITHCOLLISION_ADJOINCROSS), &hitNorm);
                        }
                    }
                }
            }

            ++surfNum;
            ++pCurSurf;
        }
    }
}

int J3DAPI sithCollision_HandleThingHitSurface(SithThing* pThing, SithSurface* pSurface, SithCollision* pCollision)
{
    SithMoveInfo* pMoveInfo;
    float impactSpeed;
    float absVelZ;
    float volume;

    volume = 1.0f;
    SITH_ASSERTREL(pThing != ((void*)0));
    SITH_ASSERTREL(pSurface != ((void*)0));
    if ( pThing->moveType != SITH_MT_PHYSICS )
    {
        return 0;
    }

    pMoveInfo = &pThing->moveInfo;

    impactSpeed = -(rdVector_Dot3(&pThing->moveInfo.physics.velocity, &pCollision->hitNorm));

    absVelZ = fabsf(pThing->moveInfo.physics.velocity.z);

    if ( !sithCollision_sub_4AA1A0(pThing, &pCollision->hitNorm, pCollision->distance, 0, pSurface) )
    {
        return 0;
    }

    if ( (pSurface->flags & SITH_SURFACE_COGLINKED) != 0 && (pThing->flags & SITH_TF_REMOTE) == 0 && pSurface->msecLastTouched + 500 <= sithTime_g_clockTime )
    {
        pSurface->msecLastTouched = sithTime_g_clockTime;
        sithCog_SurfaceSendMessage(pSurface, pThing, SITHCOG_MSG_TOUCHED);
    }

    if ( pThing->type == SITH_THING_PLAYER )
    {
        if ( (pThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
        {
            if ( pThing->moveInfo.physics.velocity.z >= -1.65f )
            {
                if ( pThing->moveStatus == SITHPLAYERMOVE_UNKNOWN_82 )
                {
                    sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_LAND, 0);
                    pThing->moveStatus = SITHPLAYERMOVE_JEEP_STILL;
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_LANDHARD);
                }
            }
            else
            {
            #ifdef J3D_DEBUG // Found in debug version
                if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_INVULNERABLE) != 0 )
                {
                    char aText[256];
                    STD_FORMAT(aText, "Falling Death Wall %f.", pThing->moveInfo.physics.velocity.z);
                    sithConsole_PrintString(aText);
                }
            #endif

                if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_INVULNERABLE) == 0 )
                {
                    pThing->moveStatus = SITHPLAYERMOVE_JEEP_IMPACT;
                    sithActor_KillActor(pThing, pThing, SITH_DAMAGE_IMPACT);
                }
            }
        }
        else if ( (pThing->moveStatus == SITHPLAYERMOVE_FALLING || !pThing->attach.flags) && absVelZ >= 1.45f )
        {
            if ( absVelZ < 1.65f )
            {
                if ( absVelZ < 1.55f )
                {
                    sithThing_DamageThing(pThing, pThing, 200.0f, SITH_DAMAGE_IMPACT);
                }
                else
                {
                    sithThing_DamageThing(pThing, pThing, 500.0f, SITH_DAMAGE_IMPACT);
                }
            }
            else if ( (pThing->type == SITH_THING_PLAYER || pThing->type == SITH_THING_ACTOR) && (pThing->thingInfo.actorInfo.flags & SITH_AF_INVULNERABLE) == 0 )
            {
                sithActor_KillActor(pThing, pThing, SITH_DAMAGE_IMPACT);
            }

            if ( pThing->pSoundClass )
            {
                sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_LANDHURT);
            }
        }
    }

    if ( impactSpeed <= 0.15000001f )
    {
        return 1;
    }

    if ( impactSpeed <= 1.0f )
    {
        volume = impactSpeed;
    }
    else
    {
        volume = 1.0f;
    }

    if ( (pSurface->flags & SITH_SURFACE_METAL) != 0 )
    {
        sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITMETAL, volume);
    }

    else if ( (pSurface->flags & SITH_SURFACE_EARTH) != 0 )
    {
        sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITEARTH, volume);
    }
    else
    {
        sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITHARD, volume);
    }

    return 1;
}

int J3DAPI sithCollision_ThingCollisionHandler(SithThing* pSrcThing, SithThing* pThingCollided, SithCollision* pCollision, int bSecondThingIsSource)
{
    float crushDamge;
    float v19;
    int a5;
    float hitImpact;
    float z;
    rdVector3 moveNorm;
    float moveDist;
    float hitMass;
    float mass;
    float hitImpactSpeed;
    float impactSpeed;
    SithThing* pHitThing;
    rdVector3 hitNorm;
    rdVector3 pImpactForce;
    float totalImpactSpeed;
    rdVector3 pForce;
    SithThing* pThing;

    if ( pSrcThing->type == SITH_THING_COG
        && pThingCollided->type == SITH_THING_COG
        && (pSrcThing->flags & SITH_TF_MOVABLE) == 0
        && (pThingCollided->flags & SITH_TF_MOVABLE) == 0 )
    {
        return 0;
    }

    rdVector_Copy3(&hitNorm, &pCollision->hitNorm);

    if ( bSecondThingIsSource )
    {
        pThing = pThingCollided;
        pHitThing = pSrcThing;
    }
    else
    {
        pThing = pSrcThing;
        pHitThing = pThingCollided;
    }

    if ( (pThing->flags & SITH_TF_COGLINKED) != 0 && (pThing->flags & SITH_TF_REMOTE) == 0 && pThing->type != SITH_THING_ITEM )
    {
        sithCog_ThingSendMessage(pThing, pHitThing, SITHCOG_MSG_TOUCHED);
    }

    if ( (pHitThing->flags & SITH_TF_COGLINKED) != 0 && (pThing->flags & SITH_TF_REMOTE) == 0 && pHitThing->type != SITH_THING_ITEM )
    {
        sithCog_ThingSendMessage(pHitThing, pThing, SITHCOG_MSG_TOUCHED);
    }

    if ( pThing->type == SITH_THING_PLAYER && pHitThing->type == SITH_THING_ITEM )
    {
        return 1;
    }

    // Handle jeep stop obj collision
    if ( (pHitThing->flags & SITH_TF_JEEPSTOP) != 0 )
    {
        // If colliding object is not player or player is not jeep player there is no collision and return
        if ( pThing->type != SITH_THING_PLAYER || (pThing->moveInfo.physics.flags & SITH_PF_JEEP) == 0 )
        {
            return 0;
        }

        float v31 = rdVector_Dot3(&pHitThing->orient.lvec, &pThing->moveInfo.physics.velocity);
        if ( v31 >= 0.0f )
        {
            return 0;
        }
    }

    if ( pThing->moveType == SITH_MT_PHYSICS && pThing->moveInfo.physics.mass != 0.0f )
    {
        if ( pHitThing->moveType == SITH_MT_PHYSICS && pHitThing->moveInfo.physics.mass != 0.0f )
        {
            a5 = 1;
            mass = pThing->moveInfo.physics.mass;

            impactSpeed = -rdVector_Dot3(&pThing->moveInfo.physics.velocity, &hitNorm);

            hitMass = pHitThing->moveInfo.physics.mass;

            hitImpactSpeed   = rdVector_Dot3(&pHitThing->moveInfo.physics.velocity, &hitNorm);
            totalImpactSpeed = stdMath_ClipNearZero(fabsf(impactSpeed + hitImpactSpeed));

            float totalMass = mass + hitMass;
            SITH_ASSERTREL(totalMass > 0.0f);
            if ( totalImpactSpeed <= 0.0f )
            {
                return 0;
            }
            else
            {
                if ( (pThing->moveInfo.physics.flags & SITH_PF_SURFACEBOUNCE) == 0 )
                {
                    totalImpactSpeed = totalImpactSpeed * 0.5f;
                }

                if ( (pHitThing->moveInfo.physics.flags & SITH_PF_SURFACEBOUNCE) == 0 )
                {
                    totalImpactSpeed = totalImpactSpeed * 0.5f;
                }

                pForce.x = hitNorm.x * totalImpactSpeed;
                pForce.y = hitNorm.y * totalImpactSpeed;
                pForce.z = hitNorm.z * totalImpactSpeed;

                pForce.x = mass * hitMass * 2.0f / (mass + hitMass) * pForce.x;
                pForce.y = mass * hitMass * 2.0f / (mass + hitMass) * pForce.y;
                pForce.z = mass * hitMass * 2.0f / (mass + hitMass) * pForce.z;

                pImpactForce.x = -pForce.x;
                pImpactForce.y = -pForce.y;
                pImpactForce.z = -pForce.z;

                if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_MINECAR)) != 0
                    || pHitThing->moveType == SITH_MT_PHYSICS && (pHitThing->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_MINECAR)) != 0 )
                {
                    sithCollision_VehicleCollisionHandler(pThing, pHitThing, &pForce, &pImpactForce, &a5, &hitNorm, impactSpeed, hitImpactSpeed);
                }

                else if ( pThing->pAttachedThing && (pThing->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0
                    || (pThing->attach.flags & SITH_ATTACH_TAIL) != 0 )
                {
                    float hitDot = fabsf(rdVector_Dot3(&pHitThing->orient.lvec, &hitNorm));
                    float thrust = rdVector_Len3(&pHitThing->moveInfo.physics.thrust);
                    totalImpactSpeed = thrust * sithTime_g_frameTimeFlex * hitDot;

                    totalImpactSpeed = impactSpeed + hitImpactSpeed + totalImpactSpeed;

                    pImpactForce.x = -(pHitThing->moveInfo.physics.mass * totalImpactSpeed) * hitNorm.x;
                    pImpactForce.y = -(pHitThing->moveInfo.physics.mass * totalImpactSpeed) * hitNorm.y;
                    pImpactForce.z = -(pHitThing->moveInfo.physics.mass * totalImpactSpeed) * hitNorm.z;

                    pImpactForce.x = pImpactForce.x * 1.2f;
                    pImpactForce.y = pImpactForce.y * 1.2f;
                    pImpactForce.z = pImpactForce.z * 1.2f;
                    memset(&pForce, 0, sizeof(pForce));

                    a5 = 0;
                }

                else if ( pHitThing->pAttachedThing && (pHitThing->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0
                    || (pHitThing->attach.flags & SITH_ATTACH_TAIL) != 0 )
                {
                    float hitDot = fabsf(rdVector_Dot3(&pThing->orient.lvec, &hitNorm));
                    float thrust = rdVector_Len3(&pThing->moveInfo.physics.thrust);
                    totalImpactSpeed = thrust * sithTime_g_frameTimeFlex * hitDot;

                    totalImpactSpeed = impactSpeed + hitImpactSpeed + totalImpactSpeed;

                    pForce.x = pThing->moveInfo.physics.mass * totalImpactSpeed * hitNorm.x;
                    pForce.y = pThing->moveInfo.physics.mass * totalImpactSpeed * hitNorm.y;
                    pForce.z = pThing->moveInfo.physics.mass * totalImpactSpeed * hitNorm.z;

                    pForce.x = pForce.x * 1.2f;
                    pForce.y = pForce.y * 1.2f;
                    pForce.z = pForce.z * 1.2f;
                    memset(&pImpactForce, 0, sizeof(pImpactForce));
                }

                sithPhysics_ApplyForce(pThing, &pForce);
                sithPhysics_ApplyForce(pHitThing, &pImpactForce);

                if ( a5 )
                {
                    return sithCollision_sub_4AA1A0(pThing, &hitNorm, pCollision->distance, 0, 0);
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            hitImpact = -(rdVector_Dot3(&pThing->moveInfo.physics.velocity, &hitNorm));
            z = pThing->moveInfo.physics.velocity.z;

            if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->moveInfo.physics.flags & SITH_PF_MINECAR) != 0 )
            {
                if ( pThing->controlType == SITH_CT_AI )
                {
                    sithCog_ThingSendMessage(pThing, 0, SITHCOG_MSG_BLOCKED);
                }

                sithPhysics_ResetThingMovement(pThing);
                return 1;
            }
            else if ( (pThing->pAttachedThing && (pThing->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0 || (pThing->attach.flags & SITH_ATTACH_TAIL) != 0)
                && _strcmpi(pHitThing->aName, "elevpltfrm") )
            {
                return 0;
            }
            else if ( !sithCollision_sub_4AA1A0(pThing, &hitNorm, pCollision->distance, 0, 0) )
            {
                return 0;
            }
            else
            {
                if ( hitImpact <= 0.15000001f && z >= -0.15000001f )
                {
                    return 1;
                }

                if ( fabsf(z) >= hitImpact )
                {
                    hitImpact = fabsf(z);
                }

                if ( pThing->type == SITH_THING_PLAYER
                    && (pThing->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) == 0
                    && !pSrcThing->attach.flags
                    && hitImpact >= 1.45f )
                {
                    if ( hitImpact < 1.65f )
                    {
                        if ( hitImpact < 1.55f )
                        {
                            sithThing_DamageThing(pSrcThing, pSrcThing, 200.0f, SITH_DAMAGE_IMPACT);
                        }
                        else
                        {
                            sithThing_DamageThing(pSrcThing, pSrcThing, 500.0f, SITH_DAMAGE_IMPACT);
                        }
                    }
                    else if ( (pSrcThing->thingInfo.actorInfo.flags & SITH_AF_INVULNERABLE) == 0 )
                    {
                        sithActor_KillActor(pSrcThing, pSrcThing, SITH_DAMAGE_IMPACT);
                    }

                    if ( pSrcThing->pSoundClass )
                    {
                        sithSoundClass_PlayModeRandom(pSrcThing, SITHSOUNDCLASS_LANDHURT);
                    }
                }

                if ( hitImpact <= 1.0f )
                {
                    v19 = hitImpact;
                }
                else
                {
                    v19 = 1.0f;
                }

                hitImpact = v19;
                if ( (pHitThing->flags & SITH_TF_METAL) != 0 )
                {
                    sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITMETAL, hitImpact);
                }
                else if ( (pHitThing->flags & SITH_TF_EARTH) != 0 )
                {
                    sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITEARTH, hitImpact);
                }
                else if ( (pHitThing->flags & SITH_TF_NOSOUND) == 0 )
                {
                    sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITHARD, hitImpact);
                }

                return 1;
            }
        }
    }
    else if ( pHitThing->moveType != SITH_MT_PHYSICS || pHitThing->moveInfo.physics.mass == 0.0f )
    {
        return 1;
    }
    else if ( pHitThing->moveType == SITH_MT_PHYSICS && (pHitThing->moveInfo.physics.flags & SITH_PF_MINECAR) != 0 )
    {
        sithPhysics_ResetThingMovement(pHitThing);
        return 0;
    }
    else if ( (pHitThing->pAttachedThing && (pHitThing->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0
        || (pHitThing->attach.flags & SITH_ATTACH_TAIL) != 0)
        && strcmpi(pThing->aName, "elevpltfrm") )
    {
        return 0;
    }
    else
    {
        float hitDot = stdMath_ClipNearZero(rdVector_Dot3(&pThing->moveDir, &hitNorm));
        if ( hitDot >= 0.0f )
        {
            return 0;
        }
        else
        {
            moveDist = -hitDot;
            moveNorm.x = -hitNorm.x;
            moveNorm.y = -hitNorm.y;
            moveNorm.z = -hitNorm.z;
            moveDist = moveDist * 1.0001f;
            float distMoved = sithCollision_MoveThing(pHitThing, &moveNorm, moveDist, 0);

            if ( distMoved >= moveDist )
            {
                return 1;
            }

            if ( (pThing->flags & SITH_TF_NOCRUSH) == 0 )
            {
                crushDamge = (moveDist - distMoved) * 100.0f;
                sithThing_DamageThing(pHitThing, pThing, crushDamge, SITH_DAMAGE_IMPACT);
            }

            memset(&pThing->moveDir, 0, sizeof(pThing->moveDir));
            return 1;
        }
    }
}

void J3DAPI sithCollision_VehicleCollisionHandler(SithThing* pThing, SithThing* pHitThing, rdVector3* pForce, rdVector3* pImpactForce, int* a5, const rdVector3* hitNormal, float impactSpeed, float hitImpactSpeed)
{
    if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->moveInfo.physics.flags & SITH_PF_MINECAR) != 0
        || (pHitThing->moveType != SITH_MT_PHYSICS || (pHitThing->moveInfo.physics.flags & SITH_PF_MINECAR) == 0)
        && pThing->moveType == SITH_MT_PHYSICS
        && (pThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
    {
        memset(pForce, 0, sizeof(rdVector3));

        *a5 = 0;
        if ( pHitThing->moveType == SITH_MT_PHYSICS && (pHitThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
        {
            float dot = rdVector_Dot3(&pHitThing->orient.lvec, hitNormal);
            if ( dot < 0.0f )
            {
                dot = -dot;
            }

            float totalImpactSpeed = rdVector_Len3(&pHitThing->moveInfo.physics.thrust) * sithTime_g_frameTimeFlex * dot;
            totalImpactSpeed = impactSpeed + hitImpactSpeed + totalImpactSpeed;

            pImpactForce->x = -(pHitThing->moveInfo.physics.mass * totalImpactSpeed) * hitNormal->x;
            pImpactForce->y = hitNormal->y * -(pHitThing->moveInfo.physics.mass * totalImpactSpeed);
            pImpactForce->z = hitNormal->z * -(pHitThing->moveInfo.physics.mass * totalImpactSpeed);

            pImpactForce->x = pImpactForce->x * 1.2f;
            pImpactForce->y = pImpactForce->y * 1.2f;
            pImpactForce->z = pImpactForce->z * 1.2f;

            sithSoundClass_PlayModeFirstEx(pThing, SITHSOUNDCLASS_HITMETAL, 1.0f);
        }
        else if ( pHitThing->type == SITH_THING_PLAYER )
        {
            float dheight = pHitThing->pos.z - pThing->pos.z;
            if ( dheight <= 0.15000001f )
            {
                rdVector3 hitDir;
                rdVector_Sub3(&hitDir, &pHitThing->pos, &pThing->pos);
                /*  hitDir.x = pHitThing->pos.x - pThing->pos.x;
                  hitDir.y = pHitThing->pos.y - pThing->pos.y;
                  hitDir.z = pHitThing->pos.z - pThing->pos.z;*/

                float theight = sithPhysics_GetThingHeight(pThing);
                hitDir.z = theight - sithPhysics_GetThingHeight(pHitThing) + hitDir.z;
                rdVector_Normalize3Acc(&hitDir);

                rdVector3 impactDir;
                rdVector_Normalize3(&impactDir, &pThing->moveInfo.physics.velocity);

                float hitDot = rdVector_Dot3(&impactDir, &hitDir);
                if ( hitDot >= 0.70700002f )
                {
                    float objSpeed = rdVector_Len3(&pThing->moveInfo.physics.velocity);
                    if ( objSpeed >= 0.40000001f )
                    {
                        if ( objSpeed < 0.0f )
                        {
                            objSpeed = 0.0f;
                        }
                        else if ( objSpeed > 1.2f )
                        {
                            objSpeed = 1.2f;
                        }

                        pImpactForce->z = objSpeed * 0.19f * pHitThing->moveInfo.physics.mass;
                        sithThing_DetachThing(pHitThing);

                        rdVector_Copy3(&pHitThing->orient.lvec, hitNormal);

                        pHitThing->orient.rvec.x = pHitThing->orient.lvec.y * pHitThing->orient.uvec.z - pHitThing->orient.lvec.z * pHitThing->orient.uvec.y;
                        pHitThing->orient.rvec.y = pHitThing->orient.lvec.z * pHitThing->orient.uvec.x - pHitThing->orient.lvec.x * pHitThing->orient.uvec.z;
                        pHitThing->orient.rvec.z = pHitThing->orient.lvec.x * pHitThing->orient.uvec.y - pHitThing->orient.lvec.y * pHitThing->orient.uvec.x;
                        rdMatrix_Normalize34(&pHitThing->orient);

                        float damage = pHitThing->thingInfo.actorInfo.maxHealth + 1.0f;
                        sithThing_DamageThing(pHitThing, pThing, damage, SITH_DAMAGE_VEHICLE);
                        sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_HITHARD);

                        if ( pImpactForce->z < 0.0f )
                        {
                            pImpactForce->z = 0.0f;
                        }

                        pImpactForce->x = pImpactForce->x * 4.0f;
                        pImpactForce->y = pImpactForce->y * 4.0f;
                        pImpactForce->z = pImpactForce->z * 4.0f;
                    }
                }
            }
        }
        else if ( pHitThing->moveStatus == SITHPLAYERMOVE_RUNOVER )
        {
            memset(pImpactForce, 0, sizeof(rdVector3));
        }
        else if ( pHitThing->type == SITH_THING_ACTOR )
        {
            if ( pHitThing->moveInfo.physics.mass > 75.0f
                && ((rdVector_Len3(pImpactForce) / pHitThing->moveInfo.physics.mass) < 0.105f) )
            {
                sithThing_DamageThing(pHitThing, pThing, sithCollision_jeepDamage, SITH_DAMAGE_VEHICLE);
            }
            else
            {
                float objSpeed = rdVector_Len3(&pThing->moveInfo.physics.velocity);
                if ( objSpeed < 0.0f )
                {
                    objSpeed = 0.0f;
                }
                else if ( objSpeed > 1.2f )
                {
                    objSpeed = 1.2f;
                }

                pImpactForce->z = objSpeed * 0.19f * pHitThing->moveInfo.physics.mass;
                sithThing_DetachThing(pHitThing);

                rdVector_Copy3(&pHitThing->orient.lvec, hitNormal);

                pHitThing->orient.rvec.x = pHitThing->orient.lvec.y * pHitThing->orient.uvec.z - pHitThing->orient.lvec.z * pHitThing->orient.uvec.y;
                pHitThing->orient.rvec.y = pHitThing->orient.lvec.z * pHitThing->orient.uvec.x - pHitThing->orient.lvec.x * pHitThing->orient.uvec.z;
                pHitThing->orient.rvec.z = pHitThing->orient.lvec.x * pHitThing->orient.uvec.y - pHitThing->orient.lvec.y * pHitThing->orient.uvec.x;
                rdMatrix_Normalize34(&pHitThing->orient);

                float damage = pHitThing->thingInfo.actorInfo.maxHealth + 1.0f;
                sithThing_DamageThing(pHitThing, pThing, damage, SITH_DAMAGE_VEHICLE);

                if ( (pThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
                {
                    sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_LWALKSNOW);
                }

                sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_HITHARD);
            }

            if ( pImpactForce->z < 0.0f )
            {
                pImpactForce->z = 0.0f;
            }

            pImpactForce->x = pImpactForce->x * 4.0f;
            pImpactForce->y = pImpactForce->y * 4.0f;
            pImpactForce->z = pImpactForce->z * 4.0f;
        }
    }
    else
    {
        memset(pImpactForce, 0, sizeof(rdVector3));
        if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
        {
            rdVector3 impactDir;
            impactDir.x = pThing->pos.x - pHitThing->pos.x;
            impactDir.y = pThing->pos.y - pHitThing->pos.y;
            impactDir.z = pThing->pos.z - pHitThing->pos.z - 0.14f;
            rdVector_Normalize3Acc(&impactDir);

            float dot = rdVector_Dot3(&pThing->orient.lvec, &impactDir);
            if ( dot < 0.0f )
            {
                dot = -dot;
            }

            float totalImpactSpeed = (float)((double)rdVector_Len3(&pThing->moveInfo.physics.thrust) * sithTime_g_frameTimeFlex * dot);
            totalImpactSpeed = impactSpeed + hitImpactSpeed + totalImpactSpeed;

            pForce->x = pThing->moveInfo.physics.mass * totalImpactSpeed * impactDir.x;
            pForce->y = pThing->moveInfo.physics.mass * totalImpactSpeed * impactDir.y;
            pForce->z = pThing->moveInfo.physics.mass * totalImpactSpeed * impactDir.z;

            pForce->x = pForce->x * 1.2f;
            pForce->y = pForce->y * 1.2f;
            pForce->z = pForce->z * 1.2f;
            sithSoundClass_PlayModeFirstEx(pHitThing, SITHSOUNDCLASS_HITMETAL, 1.0f);
        }
        else if ( pThing->type == SITH_THING_PLAYER )
        {
            float dheight = pThing->pos.z - pHitThing->pos.z;
            if ( dheight <= 0.15000001f )
            {
                rdVector3 impactDir;
                impactDir.x = pThing->pos.x - pHitThing->pos.x;
                impactDir.y = pThing->pos.y - pHitThing->pos.y;
                impactDir.z = pThing->pos.z - pHitThing->pos.z;

                float theight = sithPhysics_GetThingHeight(pHitThing);
                impactDir.z = theight - sithPhysics_GetThingHeight(pThing) + impactDir.z;
                rdVector_Normalize3Acc(&impactDir);

                rdVector3 hitDir;
                rdVector_Normalize3(&hitDir, &pHitThing->moveInfo.physics.velocity);
                float hitDot = rdVector_Dot3(&hitDir, &impactDir);
                if ( hitDot >= 0.70700002f )
                {
                    float objSpeed = rdVector_Len3(&pHitThing->moveInfo.physics.velocity);
                    if ( objSpeed >= 0.40000001f )
                    {
                        if ( objSpeed < 0.0f )
                        {
                            objSpeed = 0.0f;
                        }
                        else if ( objSpeed > 1.2f )
                        {
                            objSpeed = 1.2f;
                        }

                        pForce->z = objSpeed * 0.19f * pThing->moveInfo.physics.mass;
                        sithThing_DetachThing(pThing);

                        pThing->orient.lvec.x = -hitNormal->x;
                        pThing->orient.lvec.y = -hitNormal->y;
                        pThing->orient.lvec.z = -hitNormal->z;

                        pThing->orient.rvec.x = pThing->orient.lvec.y * pThing->orient.uvec.z - pThing->orient.lvec.z * pThing->orient.uvec.y;
                        pThing->orient.rvec.y = pThing->orient.lvec.z * pThing->orient.uvec.x - pThing->orient.lvec.x * pThing->orient.uvec.z;
                        pThing->orient.rvec.z = pThing->orient.lvec.x * pThing->orient.uvec.y - pThing->orient.lvec.y * pThing->orient.uvec.x;
                        rdMatrix_Normalize34(&pThing->orient);

                        float damage = pThing->thingInfo.actorInfo.maxHealth + 1.0f;
                        sithThing_DamageThing(pThing, pHitThing, damage, SITH_DAMAGE_VEHICLE);

                        sithSoundClass_PlayModeRandom(pHitThing, SITHSOUNDCLASS_HITHARD);

                        if ( pForce->z < 0.0f )
                        {
                            pForce->z = 0.0f;
                        }

                        pForce->x = pForce->x * 4.0f;
                        pForce->y = pForce->y * 4.0f;
                        pForce->z = pForce->z * 4.0f;
                    }
                }
            }
        }
        else if ( pThing->moveStatus == SITHPLAYERMOVE_RUNOVER )
        {
            memset(pForce, 0, sizeof(rdVector3));
        }
        else if ( pThing->type == SITH_THING_ACTOR )
        {
            if ( pThing->moveInfo.physics.mass > 75.0f
                && ((rdVector_Len3(pForce) / pThing->moveInfo.physics.mass) < 0.105f) )
            {
                sithThing_DamageThing(pThing, pHitThing, sithCollision_jeepDamage, SITH_DAMAGE_VEHICLE);
            }
            else
            {
                float objSpeed = rdVector_Len3(&pHitThing->moveInfo.physics.velocity);
                if ( objSpeed < 0.0f )
                {
                    objSpeed = 0.0f;
                }
                else if ( objSpeed > 1.2f )
                {
                    objSpeed = 1.2f;
                }

                pForce->z = objSpeed * 0.19f * pThing->moveInfo.physics.mass;
                sithThing_DetachThing(pThing);

                pThing->orient.lvec.x = -hitNormal->x;
                pThing->orient.lvec.y = -hitNormal->y;
                pThing->orient.lvec.z = -hitNormal->z;

                pThing->orient.rvec.x = pThing->orient.lvec.y * pThing->orient.uvec.z - pThing->orient.lvec.z * pThing->orient.uvec.y;
                pThing->orient.rvec.y = pThing->orient.lvec.z * pThing->orient.uvec.x - pThing->orient.lvec.x * pThing->orient.uvec.z;
                pThing->orient.rvec.z = pThing->orient.lvec.x * pThing->orient.uvec.y - pThing->orient.lvec.y * pThing->orient.uvec.x;
                rdMatrix_Normalize34(&pThing->orient);

                float damage = pThing->thingInfo.actorInfo.maxHealth + 1.0f;
                sithThing_DamageThing(pThing, pHitThing, damage, SITH_DAMAGE_VEHICLE);

                if ( (pHitThing->moveInfo.physics.flags & SITH_PF_JEEP) != 0 )
                {
                    sithSoundClass_PlayModeFirst(pHitThing, SITHSOUNDCLASS_LWALKSNOW);
                }

                sithSoundClass_PlayModeRandom(pHitThing, SITHSOUNDCLASS_HITHARD);
            }

            if ( pForce->z < 0.0f )
            {
                pForce->z = 0.0f;
            }

            pForce->x = pForce->x * 4.0f;
            pForce->y = pForce->y * 4.0f;
            pForce->z = pForce->z * 4.0f;
        }
    }
}

int J3DAPI sithCollision_sub_4AA1A0(SithThing* pThing, const rdVector3* pHitNorm, float colDistance, int a4, const SithSurface* pHitSurf)
{
    J3D_UNUSED(a4);
    float impactDot;
    float scaledImpact;
    SithMoveInfo* pMoveInfo;
    float v36;
    float impactScale;
    float hitDot;

    SITH_ASSERTREL(pThing);
    if ( pThing->moveType != SITH_MT_PHYSICS )
    {
        return 0;
    }

    pMoveInfo = &pThing->moveInfo;
    hitDot = -rdVector_Dot3(&pThing->moveDir, pHitNorm);
    hitDot = stdMath_ClipNearZero(hitDot);
    if ( hitDot <= 0.0f )
    {
        return 0;
    }

    if ( (pMoveInfo->physics.flags & SITH_PF_SURFACEBOUNCE) != 0 )
    {
        impactScale = 1.9f;
    }
    else
    {
        impactScale = 1.0001f;
    }

    if ( colDistance == 0.0f && sithCollision_dword_17F1090 )
    {
        hitDot = -rdVector_Dot3(&pThing->moveDir, pHitNorm);
        if ( hitDot <= 0.0f )
        {
            return 0;
        }

        pThing->moveDir.x = pHitNorm->x * hitDot + pThing->moveDir.x;
        pThing->moveDir.y = pHitNorm->y * hitDot + pThing->moveDir.y;
        pThing->moveDir.z = pHitNorm->z * hitDot + pThing->moveDir.z;
        impactDot = -(rdVector_Dot3(&pMoveInfo->physics.velocity, pHitNorm));

        if ( (pMoveInfo->physics.flags & SITH_PF_RAFT) != 0 && pHitSurf && (pHitSurf->flags & SITH_SURFACE_WATER) != 0 )
        {
            float impact = rdMath_DistancePointToPlane(&pMoveInfo->physics.velocity, pHitNorm, &rdroid_g_zeroVector3);
            /*    impact = (pMoveInfo->physics.velocity.x - 0.0f) * pHitNorm->x
                + (pMoveInfo->physics.velocity.y - 0.0f) * pHitNorm->y
                + (pMoveInfo->physics.velocity.z - 0.0f) * pHitNorm->z;*/

            float zHitDot = rdVector_Dot3(pHitNorm, &rdroid_g_zVector3);// rdroid_g_zVector3 dot pHitNormal
            impact /= zHitDot;

            // Note: rdroid_g_zVector3 * -zImpact + pMoveInfo->physics.velocity
            rdVector3 zImpactVel;
            zImpactVel.x = -impact * 0.0f + pMoveInfo->physics.velocity.x;
            zImpactVel.y = -impact * 0.0f + pMoveInfo->physics.velocity.y;
            zImpactVel.z = -impact * 1.0f + pMoveInfo->physics.velocity.z;
            rdVector_Normalize3Acc(&zImpactVel);

            // Note: Speed can be calculated only once
            double speed  = rdVector_Len3(&pMoveInfo->physics.velocity);
            zImpactVel.x = (float)(speed * zImpactVel.x);
            zImpactVel.y = (float)(speed * zImpactVel.y);
            zImpactVel.z = (float)(speed * zImpactVel.z);

            rdVector_Copy3(&pMoveInfo->physics.velocity, &zImpactVel);
        }
        else
        {
            pMoveInfo->physics.velocity.x = pHitNorm->x * impactDot + pMoveInfo->physics.velocity.x;
            pMoveInfo->physics.velocity.y = pHitNorm->y * impactDot + pMoveInfo->physics.velocity.y;
            pMoveInfo->physics.velocity.z = pHitNorm->z * impactDot + pMoveInfo->physics.velocity.z;
        }

        v36 = -rdVector_Dot3(pHitNorm, &sithCollision_vec17F10A0);
        sithCollision_vec17F10A0.x = pHitNorm->x * v36 + sithCollision_vec17F10A0.x;
        sithCollision_vec17F10A0.y = pHitNorm->y * v36 + sithCollision_vec17F10A0.y;
        sithCollision_vec17F10A0.z = pHitNorm->z * v36 + sithCollision_vec17F10A0.z;
        rdVector_Normalize3Acc(&sithCollision_vec17F10A0);

        impactDot = -(rdVector_Dot3(&pMoveInfo->physics.velocity, &sithCollision_vec17F10A0));

        pMoveInfo->physics.velocity.x = sithCollision_vec17F10A0.x * impactDot + pMoveInfo->physics.velocity.x;
        pMoveInfo->physics.velocity.y = sithCollision_vec17F10A0.y * impactDot + pMoveInfo->physics.velocity.y;
        pMoveInfo->physics.velocity.z = sithCollision_vec17F10A0.z * impactDot + pMoveInfo->physics.velocity.z;

        hitDot = -rdVector_Dot3(&pThing->moveDir, &sithCollision_vec17F10A0);
        if ( hitDot <= 0.0f )
        {
            return 1;
        }

        pThing->moveDir.x = sithCollision_vec17F10A0.x * hitDot + pThing->moveDir.x;
        pThing->moveDir.y = sithCollision_vec17F10A0.y * hitDot + pThing->moveDir.y;
        pThing->moveDir.z = sithCollision_vec17F10A0.z * hitDot + pThing->moveDir.z;
    }

    rdVector_Copy3(&sithCollision_vec17F10A0, pHitNorm);
    sithCollision_dword_17F1090 = 1;

    impactDot = -rdVector_Dot3(&pMoveInfo->physics.velocity, pHitNorm);
    if ( impactDot > 0.0f )
    {
        if ( (pMoveInfo->physics.flags & SITH_PF_RAFT) != 0 && pHitSurf && (pHitSurf->flags & SITH_SURFACE_WATER) != 0 )
        {
            float impact = rdMath_DistancePointToPlane(&pMoveInfo->physics.velocity, pHitNorm, &rdroid_g_zeroVector3);
            /*   v28 = (pMoveInfo->physics.velocity.x - 0.0f) * pHitNorm->x
                   + (pMoveInfo->physics.velocity.y - 0.0f) * pHitNorm->y
                   + (pMoveInfo->physics.velocity.z - 0.0f) * pHitNorm->z;*/

            float zHitDot = rdVector_Dot3(pHitNorm, &rdroid_g_zVector3);
            impact /= zHitDot;

            // Note,  rdVector_Scale3(&rdroid_g_zVector3, -impact) + pMoveInfo->physics.velocity
            rdVector3 newVel;
            newVel.x = -impact * 0.0f + pMoveInfo->physics.velocity.x;
            newVel.y = -impact * 0.0f + pMoveInfo->physics.velocity.y;
            newVel.z = -impact * 1.0f + pMoveInfo->physics.velocity.z;
            rdVector_Normalize3Acc(&newVel);

            double speed = rdVector_Len3(&pMoveInfo->physics.velocity);
            newVel.x = (float)(speed * newVel.x);
            newVel.y = (float)(speed * newVel.y);
            newVel.z = (float)(speed * newVel.z);
            rdVector_Copy3(&pMoveInfo->physics.velocity, &newVel);
        }
        else
        {
            scaledImpact = impactDot * impactScale;
            pMoveInfo->physics.velocity.x = pHitNorm->x * scaledImpact + pMoveInfo->physics.velocity.x;
            pMoveInfo->physics.velocity.y = pHitNorm->y * scaledImpact + pMoveInfo->physics.velocity.y;
            pMoveInfo->physics.velocity.z = pHitNorm->z * scaledImpact + pMoveInfo->physics.velocity.z;
        }
    }

    scaledImpact = hitDot * impactScale;
    pThing->moveDir.x = pHitNorm->x * scaledImpact + pThing->moveDir.x;
    pThing->moveDir.y = pHitNorm->y * scaledImpact + pThing->moveDir.y;
    pThing->moveDir.z = pHitNorm->z * scaledImpact + pThing->moveDir.z;
    return 1;
}

void J3DAPI sithCollision_sub_4DA7DB(SithThing* pThing, float a2)
{
    double v2 = a2 - 1.51f;
    double damage = v2 * v2 * 45.0f;
    if ( damage > 1.0f )
    {
        sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_HITDAMAGED);
        sithThing_DamageThing(pThing, pThing, (float)damage, SITH_DAMAGE_CRUSH);
    }
}

SithThing* J3DAPI sithCollision_FindActivatedThing(SithThing* pThing, int* pbFoundFloorItem)
{
    rdVector3 moveNorm;
    SithThing* pThingCollided;
    SithSector* pSector;
    float radius;
    float moveDist;
    SithCollision* pCollision;
    rdVector3 startPos;
    int curWeaponID;
    int searchFlags;

    searchFlags = 0x04;
    curWeaponID = pThing->thingInfo.actorInfo.curWeaponID;
    moveDist = 0.079999998f;
    if ( curWeaponID && curWeaponID != SITHWEAPON_ZIPPO )
    {
        return 0;
    }

    SITH_ASSERTREL(pThing);
    radius = 0.025f;
    if ( !pThing->pInSector )
    {
        return 0;
    }

    rdVector_Copy3(&moveNorm, &pThing->orient.lvec);
    rdVector_Copy3(&startPos, &pThing->pos);
    startPos.z = startPos.z + radius;

    pSector = sithCollision_FindSectorInRadius(pThing->pInSector, &pThing->pos, &startPos, 0.0f);
    if ( !pSector )
    {
        return 0;
    }

    sithCollision_SearchForCollisions(pSector, NULL, &startPos, &moveNorm, moveDist, radius, searchFlags);
    pCollision = sithCollision_PopStack();
    if ( pCollision )
    {
        while ( pCollision )
        {
            if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
            {
                SITH_ASSERTREL(pCollision->pSurfaceCollided == ((void*)0));
                SITH_ASSERTREL(pCollision->pThingCollided != ((void*)0));
                pThingCollided = pCollision->pThingCollided;
                if ( pThingCollided->type == SITH_THING_ITEM )
                {
                    sithCollision_DecreaseStackLevel();
                    *pbFoundFloorItem = 0;
                    return pThingCollided;
                }
            }

            pCollision = sithCollision_PopStack();
        }
    }

    sithCollision_DecreaseStackLevel();
    moveNorm.x = 0.0f;
    moveNorm.y = 0.0f;
    moveNorm.z = -1.0f;

    startPos.x = pThing->orient.lvec.x * 0.025f + pThing->pos.x;
    startPos.y = pThing->orient.lvec.y * 0.025f + pThing->pos.y;
    startPos.z = pThing->orient.lvec.z * 0.025f + pThing->pos.z;
    pSector = sithCollision_FindSectorInRadius(pThing->pInSector, &pThing->pos, &startPos, 0.0f);
    if ( !pSector )
    {
        return 0;
    }

    sithCollision_SearchForCollisions(pSector, NULL, &startPos, &moveNorm, moveDist, radius, searchFlags);
    pCollision = sithCollision_PopStack();
    if ( pCollision )
    {
        while ( pCollision )
        {
            if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
            {
                SITH_ASSERTREL(pCollision->pSurfaceCollided == ((void*)0));
                SITH_ASSERTREL(pCollision->pThingCollided != ((void*)0));
                pThingCollided = pCollision->pThingCollided;
                if ( pThingCollided->type == SITH_THING_ITEM )
                {
                    sithCollision_DecreaseStackLevel();
                    *pbFoundFloorItem = 1;
                    return pThingCollided;
                }
            }

            pCollision = sithCollision_PopStack();
        }
    }

    sithCollision_DecreaseStackLevel();
    return 0;
}

float J3DAPI sithCollision_BuildCollisionList(SithSector* pSector, SithThing* pThing, const rdVector3* startPos, const rdVector3* moveNorm, float moveDist, float radius, int searchFlags)
{
    if ( sithCollision_CheckSectorSearched(pSector) || !sithCollision_AddSearchedSector(pSector) )
    {
        return moveDist;
    }

    float v8 = moveDist;
    if ( (searchFlags & 1) == 0 )
    {
        v8 = sithCollision_SearchForThingCollisions(pSector, pThing, startPos, moveNorm, moveDist, radius, searchFlags);
    }

    if ( (searchFlags & 0x8000) != 0 )
    {
        sithCollision_SearchForSurfaceCollisions(pSector, startPos, moveNorm, moveDist, radius, searchFlags);
    }
    else
    {
        sithCollision_SearchForSurfaceCollisions(pSector, startPos, moveNorm, v8, radius, searchFlags);
    }

    return v8;
}

int J3DAPI sithCollision_sub_4DABF1(const SithThing* pThing, int searchFlags)
{
    if ( pThing->collide.type == SITH_COLLIDE_NONE || (pThing->flags & (SITH_TF_DISABLED | SITH_TF_DESTROYED)) != 0 )
    {
        return 0;
    }

    return (searchFlags & 0x2000) == 0 || pThing->type == SITH_THING_COG || !strcmp(pThing->aName, "killtruk");
}

int J3DAPI sithCollision_sub_4DAC4B(const SithThing* pThing1, const SithThing* pThing2, int collflags)
{
    if ( pThing1 == pThing2 || !aCollideResults[pThing1->type][pThing2->type].pProcessFunc )
    {
        return 0;
    }

    if ( (pThing1->flags & SITH_TF_DYING) != 0 || (pThing2->flags & SITH_TF_DYING) != 0 )
    {
        return 0;
    }

    if ( pThing1->type == SITH_THING_WEAPON
        && (pThing1->thingInfo.weaponInfo.flags & SITH_WF_NOSHOOTERDAMAGE) != 0
        && (pThing1->pParent && pThing2->pParent && pThing1->pParent == pThing2->pParent && pThing1->parentSignature == pThing2->parentSignature
            || pThing1->pParent == pThing2 && pThing1->parentSignature == pThing2->signature) )
    {
        return 0;
    }

    if ( pThing2->type == SITH_THING_WEAPON
        && (pThing2->thingInfo.weaponInfo.flags & SITH_WF_NOSHOOTERDAMAGE) != 0
        && (pThing2->pParent && pThing1->pParent && pThing2->pParent == pThing1->pParent && pThing2->parentSignature == pThing1->parentSignature
            || pThing2->pParent == pThing1 && pThing2->parentSignature == pThing1->signature) )
    {
        return 0;
    }

    if ( (pThing1->attach.flags & (SITH_ATTACH_THING | SITH_ATTACH_THINGFACE)) != 0 && pThing1->attach.attachedToStructure.pThingAttached == pThing2 )
    {
        if ( (pThing1->attach.flags & SITH_ATTACH_NOMOVE) != 0 || (collflags & 0x40) != 0 )
        {
            return 0;
        }

        if ( pThing1->type == SITH_THING_ACTOR && (pThing1->thingInfo.actorInfo.flags & SITH_AF_UNKNOWN_20000000) != 0 )
        {
            return 0;
        }
    }

    if ( (pThing2->attach.flags & (SITH_ATTACH_THING | SITH_ATTACH_THINGFACE)) == 0 || pThing2->attach.attachedToStructure.pThingAttached != pThing1 )
    {
        goto LABEL_42;
    }

    if ( (pThing2->attach.flags & SITH_ATTACH_NOMOVE) != 0 || (collflags & 0x40) != 0 )
    {
        return 0;
    }

    if ( pThing2->type == SITH_THING_ACTOR && (pThing2->thingInfo.actorInfo.flags & SITH_AF_UNKNOWN_20000000) != 0 )
    {
        return 0;
    }

LABEL_42:
    if ( (pThing1->attach.flags & SITH_ATTACH_TAIL) != 0 && (pThing2->attach.flags & SITH_ATTACH_TAIL) != 0 )
    {
        return 0;
    }

    if ( (pThing1->pAttachedThing && (pThing1->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0 || (pThing1->attach.flags & SITH_ATTACH_TAIL) != 0)
        && pThing2->controlType == SITH_CT_AI )
    {
        return 0;
    }

    if ( (pThing2->pAttachedThing && (pThing2->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0 || (pThing2->attach.flags & SITH_ATTACH_TAIL) != 0)
        && pThing1->controlType == SITH_CT_AI )
    {
        return 0;
    }

    if ( (pThing1->pAttachedThing && (pThing1->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0 || (pThing1->attach.flags & SITH_ATTACH_TAIL) != 0)
        && pThing2->type == SITH_THING_PLAYER
        && (pThing2->moveStatus == SITHPLAYERMOVE_JEWELFLYING || pThing2->moveStatus == SITHPLAYERMOVE_JEWELFLYING_UNKN1) )
    {
        return 0;
    }

    if ( (pThing2->pAttachedThing && (pThing2->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) != 0 || (pThing2->attach.flags & SITH_ATTACH_TAIL) != 0)
        && pThing1->type == SITH_THING_PLAYER
        && (pThing1->moveStatus == SITHPLAYERMOVE_JEWELFLYING || pThing1->moveStatus == SITHPLAYERMOVE_JEWELFLYING_UNKN1) )
    {
        return 0;
    }

    if ( pThing1->moveType == SITH_MT_PHYSICS
        && (pThing1->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_MINECAR)) != 0
        && pThing2->moveStatus == SITHPLAYERMOVE_RUNOVER )
    {
        return 0;
    }

    return pThing2->moveType != SITH_MT_PHYSICS
        || (pThing2->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_MINECAR)) == 0
        || pThing1->moveStatus != SITHPLAYERMOVE_RUNOVER;
}

void sithCollision_ResetCurStack(void)
{
    sithCollision_aNumStackCollisions[stackLevel] = 0;
    sithCollision_aNumSearchedSectors[stackLevel] = 0;
}

int J3DAPI sithCollision_AddSearchedSector(SithSector* pSector)
{
    if ( sithCollision_aNumSearchedSectors[stackLevel] == STD_ARRAYLEN(sithCollision_apSearchedSectors[stackLevel]) )
    {
        SITHLOG_ERROR("Tried to search too many sectors in collision system.\n");
        return 0;
    }

    sithCollision_apSearchedSectors[stackLevel][sithCollision_aNumSearchedSectors[stackLevel]++] = pSector;
    return 1;
}

int J3DAPI sithCollision_CheckSectorSearched(const SithSector* pSector)
{
    unsigned int i;

    for ( i = 0; i < sithCollision_aNumSearchedSectors[stackLevel]; ++i )
    {
        if ( sithCollision_apSearchedSectors[stackLevel][i] == pSector )
        {
            return 1;
        }
    }

    return 0;
}

void J3DAPI sithCollision_PushThingCollision(SithThing* pHitThing, float distance, SithCollisionType hitType, rdModel3Mesh* pHitMesh, rdFace* pHitFace, rdVector3* hitNorm)
{
    SITH_ASSERTREL(((hitType) & (SITHCOLLISION_THING)));
    SITH_ASSERTREL(hitNorm);
    if ( sithCollision_aNumStackCollisions[stackLevel] == STD_ARRAYLEN(sithCollision_aCollisions[stackLevel]) )
    {
        SITHLOG_ERROR("Found too many collisions in collision system.\n");
        return;
    }

    SithCollision* pCollision = &sithCollision_aCollisions[stackLevel][sithCollision_aNumStackCollisions[stackLevel]++];
    pCollision->pSurfaceCollided = NULL;
    pCollision->bEnumerated      = 0;
    pCollision->type             = hitType;
    pCollision->distance         = distance;
    pCollision->pThingCollided   = pHitThing;
    pCollision->pMeshCollided    = pHitMesh;
    pCollision->pFaceCollided    = pHitFace;

    rdVector_Copy3(&pCollision->hitNorm, hitNorm);
}

void J3DAPI sithCollision_PushSurfaceCollision(SithSurface* pSurf, float distance, SithCollisionType hitType, rdVector3* pHitNorm)
{
    SithCollision* pCollision;

    SITH_ASSERTREL(((hitType) & (SITHCOLLISION_WORLD | SITHCOLLISION_ADJOINTOUCH | SITHCOLLISION_ADJOINCROSS)));
    if ( sithCollision_aNumStackCollisions[stackLevel] == STD_ARRAYLEN(sithCollision_aCollisions[stackLevel]) )
    {
        SITHLOG_ERROR("Found too many collisions in collision system.\n");
        return;
    }

    pCollision = &sithCollision_aCollisions[stackLevel][sithCollision_aNumStackCollisions[stackLevel]++];
    pCollision->pThingCollided = NULL;
    pCollision->bEnumerated = 0;
    pCollision->type = hitType;
    pCollision->distance = distance;
    pCollision->pSurfaceCollided = pSurf;
    if ( pHitNorm )
    {
        rdVector_Copy3(&pCollision->hitNorm, pHitNorm);
    }
}

SithCollision* sithCollision_PopClosest(void)
{
    SithCollision* pCollision;
    float distance;
    unsigned int collNum;
    SithCollision* pClosest;

    pClosest = 0;
    distance = 3.4028235e38f;
    collNum = 0;
    pCollision = sithCollision_aCollisions[stackLevel];

    while ( collNum < sithCollision_aNumStackCollisions[stackLevel] )
    {
        if ( !pCollision->bEnumerated )
        {
            if ( pCollision->distance >= distance )
            {
                if ( pCollision->distance == distance )
                {
                    SITH_ASSERTREL(pClosest != ((void*)0));
                    if ( (pClosest->type & (SITHCOLLISION_FACEVERTEX | SITHCOLLISION_FACEEDGE)) != 0 && (pCollision->type & SITHCOLLISION_FACE) != 0 )
                    {
                        pClosest = pCollision;
                    }
                }
            }
            else
            {
                pClosest = pCollision;
                distance = pCollision->distance;
            }
        }

        ++pCollision;
        ++collNum;
    }

    return pClosest;
}

int J3DAPI sithCollision_sub_4DB3CA(SithThing* pThing1, SithThing* pThing2)
{
    if ( (pThing2->flags & SITH_TF_JEEPSTOP) != 0 )
    {
        return pThing1->type == SITH_THING_PLAYER
            && (pThing1->moveInfo.physics.flags & SITH_PF_JEEP) != 0
            && rdVector_Dot3(&pThing2->orient.lvec, &pThing1->moveInfo.physics.velocity) < 0.0f;
    }

    if ( aCollideResults[pThing1->type][pThing2->type].pUnknownFunc )
    {
        return aCollideResults[pThing1->type][pThing2->type].pUnknownFunc(pThing1, pThing2);
    }

    return 1;
}

int J3DAPI sithCollision_sub_4DB49F(SithSurfaceAdjoinFlag adjflags, int colflags)
{
    if ( (colflags & 4) != 0 )
    {
        return 1;
    }

    if ( (colflags & 0x1100) != 0 && (adjflags & SITH_ADJOIN_VISIBLE) == 0 )
    {
        return 0;
    }

    if ( (colflags & 0x200) != 0 && (colflags & 0x100) == 0 && (adjflags & SITH_ADJOIN_NOPLAYERMOVE) != 0 )
    {
        return 0;
    }

    return (colflags & 0x100) != 0 || (adjflags & SITH_ADJOIN_MOVE) != 0;
}

int J3DAPI sithCollision_ParticleAndActorCollisionHandler(SithThing* pSrcThing, SithThing* pThingCollided, SithCollision* pCollision, int bSecondThingIsSource)
{
    float damage;
    float mass;


    mass = pSrcThing->moveInfo.physics.mass;
    if ( bSecondThingIsSource )
    {
        return sithCollision_ThingCollisionHandler(pSrcThing, pThingCollided, pCollision, bSecondThingIsSource);
    }

    float dirDot = 0.0f; // Added: Init to 0
    if ( pSrcThing->moveType == SITH_MT_PHYSICS )
    {
        dirDot = -(rdVector_Dot3(&pSrcThing->moveInfo.physics.velocity, &pCollision->hitNorm));
    }

    if ( !sithCollision_ThingCollisionHandler(pSrcThing, pThingCollided, pCollision, 0) )
    {
        return 0;
    }

    if ( dirDot <= 0.25f )
    {
        return 1;
    }

    damage = mass * 0.30000001f * dirDot;
    sithThing_DamageThing(pThingCollided, pSrcThing, damage, SITH_DAMAGE_IMPACT);
    return 1;
}

float J3DAPI sithCollision_CheckDistance(SithThing* pThing, const rdVector3* moveNorm)
{
    SithThing* pHitThing;
    rdVector3 dir;
    SithSurface* pSurfaceCollided;
    float moveDist;
    SithCollision* pCollision;
    float distance;
    int searchFlags;

    moveDist = 10.0f;
    searchFlags = 528;
    distance = 10.0f;
    sithCollision_SearchForCollisions(pThing->pInSector, pThing, &pThing->pos, moveNorm, 10.0f, pThing->collide.movesize, 528);
    while ( 1 )
    {
        pCollision = sithCollision_PopStack();
        if ( !pCollision )
        {
            break;
        }

        if ( (pCollision->type & SITHCOLLISION_ADJOINCROSS) != 0 )
        {
            SITH_ASSERTREL(pCollision->pThingCollided == ((void*)0));
            SITH_ASSERTREL(pCollision->pSurfaceCollided != ((void*)0));
            pSurfaceCollided = pCollision->pSurfaceCollided;
            if ( (pSurfaceCollided->flags & SITH_SURFACE_ISFLOOR) != 0 && pCollision->distance < distance )
            {
                distance = pCollision->distance;
            }
        }
        else if ( (pCollision->type & SITHCOLLISION_THING) != 0 )
        {
            pHitThing = pCollision->pThingCollided;
            SITH_ASSERTREL(pHitThing);
            if ( pHitThing != pThing )
            {
                if ( !pCollision->pFaceCollided || !pCollision->pMeshCollided )
                {
                    SITHLOG_ERROR("Hit standon object but not enough collide info to attach.\n");
                    sithCollision_DecreaseStackLevel();
                    return 100.0f;
                }

                rdMatrix_TransformVector34(&dir, &pCollision->pFaceCollided->normal, &pCollision->pThingCollided->orient);
                if ( rdVector_Dot3(&dir, &rdroid_g_zVector3) >= 0.60000002f && pCollision->distance < distance )
                {
                    distance = pCollision->distance;
                }
            }
        }
    }

    sithCollision_DecreaseStackLevel();
    return distance;
}

int J3DAPI sithCollision_sub_4AAF30(SithThing* pThing1, SithThing* pThing2)
{
    if ( pThing1->type == SITH_THING_PLAYER && (pThing1->moveInfo.physics.flags & (SITH_PF_JEEP | SITH_PF_MINECAR)) != 0 && pThing2->type == SITH_THING_ACTOR )
    {
        return 0;
    }

    return (!pThing1->pAttachedThing || (pThing1->pAttachedThing->attach.flags & SITH_ATTACH_TAIL) == 0) && (pThing1->attach.flags & SITH_ATTACH_TAIL) == 0
        || pThing2->type != SITH_THING_PLAYER;
}
