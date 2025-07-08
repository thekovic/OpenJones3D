#include "sithPuppet.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdKeyframe.h>
#include <rdroid/Engine/rdPuppet.h>
#include <rdroid/Engine/rdThing.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>

#include <sith/AI/sithAIMove.h>
#include <sith/AI/sithAIUtil.h>
#include <sith/Cog/sithCog.h>
#include <sith/Devices/sithControl.h>
#include <sith/Engine/sithCamera.h>
#include <sith/Engine/sithCollision.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Gameplay/sithFX.h>
#include <sith/Gameplay/sithInventory.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Gameplay/sithWhip.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithSoundClass.h>
#include <sith/World/sithWorld.h>

#include <std/General/stdConffile.h>
#include <std/General/stdHashtbl.h>
#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sCndKeyframeMarker
{
    float frame;
    rdKeyMarkerType type;
} CndKeyframeMarker;
static_assert(sizeof(CndKeyframeMarker) == 8, "sizeof(CndKeyframeMarker) == 8");

typedef struct sCndKeyframeInfo
{
    char name[64];
    int flags;
    int type;
    uint32_t numFrames;
    float fps;
    uint32_t numMarkers;
    uint32_t numJoints;
    uint32_t numNodes;
} CndKeyframeInfo;
static_assert(sizeof(CndKeyframeInfo) == 92, "sizeof(CndKeyframeInfo) == 92");

typedef struct sCndKeyframeNode
{
    char meshName[64];
    uint32_t nodeNum;
    uint32_t numEntries;
} CndKeyframeNode;
static_assert(sizeof(CndKeyframeNode) == 72, "sizeof(CndKeyframeNode) == 72");

static tHashTable* sithPuppet_pHashtblSubmodes;
static tHashTable* sithPuppet_pClassHashtable;
static tHashTable* sithPuppet_pKeyHashtable;

static const char* sithPuppet_aStrSubModes[SITH_PUPPET_NUMSUBMODES] =
{
    "--RESERVED--",
    "stand",
    "walk",
    "run",
    "walkback",
    "hopback",
    "hopleft",
    "hopright",
    "strafeleft",
    "straferight",
    "turnleft",
    "turnright",
    "slidedownfwd",
    "slidedownback",
    "leap",
    "jumpready",
    "jumpup",
    "jumpfwd",
    "rising",
    "fall",
    "death",
    "death2",
    "fidget",
    "fidget2",
    "pickup",
    "pushpullready",
    "pushitem",
    "pullitem",
    "mountledge",
    "grabledge",
    "hangledge",
    "hangshimleft",
    "hangshimright",
    "mountwall",
    "climbwallidle",
    "climbwallup",
    "climbwalldown",
    "climbwallleft",
    "climbwallright",
    "climbpullingup",
    "whipclimbmount",
    "whipclimbidle",
    "whipclimbup",
    "whipclimbdown",
    "whipclimbleft",
    "whipclimbright",
    "whipclimbdismount",
    "whipswingmount",
    "whipswing",
    "mountfromwater",
    "divefromsurface",
    "mount1mstep",
    "mount2mledge",
    "jumprollback",
    "jumprollfwd",
    "land",
    "hitheadl",
    "hitheadr",
    "hitsidel",
    "hitsider",
    "activate",
    "activatehigh",
    "drawweapon",
    "aimweapon",
    "holsterweapon",
    "fire",
    "fire2",
    "fire3",
    "fire4",
    "stand2walk",
    "walk2stand",
    "stand2crawl",
    "crawl2stand",
    "walk2attack",
    "victory",
    "hit",
    "hit2",
    "grabarms",
    "reserved",
    "climbtoclimb",
    "climbtohang",
    "leapleft",
    "leapright",
    "fallforward"
};

SithPuppetClass* J3DAPI sithPuppet_ClassCacheFind(const char* pName);
int J3DAPI sithPuppet_ClassCacheAdd(const SithPuppetClass* pClass);
int J3DAPI sithPuppet_ClassCacheRemove(const SithPuppetClass* pClass);

rdKeyframe* J3DAPI sithPuppet_KeyCacheFind(const char* pName);
void J3DAPI sithPuppet_KeyCacheAdd(rdKeyframe* pKeyframe);
void J3DAPI sithPuppet_KeyCacheRemove(rdKeyframe* pKeyframe);

float J3DAPI sithPuppet_GetThingLocalVelocityAxis(SithThing* pThing, size_t* pAxis, float* pVelX, float* pVelY, float* pVelZ); // Added: From debug version

SithPuppetTrack* J3DAPI sithPuppet_GetModeTrackImpl(const SithThing* pThing, SithPuppetSubMode submode);

void sithPuppet_InstallHooks(void)
{
    J3D_HOOKFUNC(sithPuppet_Startup);
    J3D_HOOKFUNC(sithPuppet_Shutdown);
    J3D_HOOKFUNC(sithPuppet_New);
    J3D_HOOKFUNC(sithPuppet_Free);
    J3D_HOOKFUNC(sithPuppet_RemoveAllTracks);
    J3D_HOOKFUNC(sithPuppet_UpdatePuppet);
    J3D_HOOKFUNC(sithPuppet_PlayFidgetMode);
    J3D_HOOKFUNC(sithPuppet_StopFridgetTrack);
    J3D_HOOKFUNC(sithPuppet_IsModeOnTrack);
    J3D_HOOKFUNC(sithPuppet_IsAnyModeOnTrack);
    J3D_HOOKFUNC(sithPuppet_FindActiveTrack);
    J3D_HOOKFUNC(sithPuppet_UpdateThingMoveTracks);
    J3D_HOOKFUNC(sithPuppet_UpdateThingMove);
    J3D_HOOKFUNC(sithPuppet_SetSubMode);
    J3D_HOOKFUNC(sithPuppet_SetMoveMode);
    J3D_HOOKFUNC(sithPuppet_SetArmedMode);
    J3D_HOOKFUNC(sithPuppet_PlayMode);
    J3D_HOOKFUNC(sithPuppet_PlayForceMoveMode);
    J3D_HOOKFUNC(sithPuppet_PlayKey);
    J3D_HOOKFUNC(sithPuppet_GetTrackNumForGUID);
    J3D_HOOKFUNC(sithPuppet_StopKey);
    J3D_HOOKFUNC(sithPuppet_StopForceMove);
    J3D_HOOKFUNC(sithPuppet_DefaultCallback);
    J3D_HOOKFUNC(sithPuppet_ReadStaticPuppetsListText);
    J3D_HOOKFUNC(sithPuppet_WriteStaticPuppetsListBinary);
    J3D_HOOKFUNC(sithPuppet_ReadStaticPuppetsListBinary);
    J3D_HOOKFUNC(sithPuppet_LoadPuppetClass);
    J3D_HOOKFUNC(sithPuppet_LoadPuppetClassEntry);
    J3D_HOOKFUNC(sithPuppet_AllocWorldPuppets);
    J3D_HOOKFUNC(sithPuppet_FreeWorldPuppets);
    J3D_HOOKFUNC(sithPuppet_ReadStaticKeyframesListText);
    J3D_HOOKFUNC(sithPuppet_WriteStaticKeyframesListBinary);
    J3D_HOOKFUNC(sithPuppet_ReadStaticKeyframesListBinary);
    J3D_HOOKFUNC(sithPuppet_GetKeyframeByIndex);
    J3D_HOOKFUNC(sithPuppet_LoadKeyframe);
    J3D_HOOKFUNC(sithPuppet_AllocWorldKeyframes);
    J3D_HOOKFUNC(sithPuppet_FreeWorldKeyframes);
    J3D_HOOKFUNC(sithPuppet_ClassCacheFind);
    J3D_HOOKFUNC(sithPuppet_ClassCacheAdd);
    J3D_HOOKFUNC(sithPuppet_ClassCacheRemove);
    J3D_HOOKFUNC(sithPuppet_GetKeyframe);
    J3D_HOOKFUNC(sithPuppet_KeyCacheFind);
    J3D_HOOKFUNC(sithPuppet_KeyCacheAdd);
    J3D_HOOKFUNC(sithPuppet_KeyCacheRemove);
    J3D_HOOKFUNC(sithPuppet_StopMode);
    J3D_HOOKFUNC(sithPuppet_SynchMode);
    J3D_HOOKFUNC(sithPuppet_ClearMode);
    J3D_HOOKFUNC(sithPuppet_RemoveTrackByIndex);
    J3D_HOOKFUNC(sithPuppet_NewTrack);
    J3D_HOOKFUNC(sithPuppet_AddTrack);
    J3D_HOOKFUNC(sithPuppet_RemoveTrack);
    J3D_HOOKFUNC(sithPuppet_FreeTrack);
    J3D_HOOKFUNC(sithPuppet_FreeTrackByIndex);
    J3D_HOOKFUNC(sithPuppet_GetModeTrack);
    J3D_HOOKFUNC(sithPuppet_GetModeTrackImpl);
    J3D_HOOKFUNC(sithPuppet_ClearTrackList);
}

void sithPuppet_ResetGlobals(void)
{
    memset(&sithPuppet_g_bPlayerLeapForward, 0, sizeof(sithPuppet_g_bPlayerLeapForward));
}

int sithPuppet_Startup(void)
{
    sithPuppet_pClassHashtable = stdHashtbl_New(64u);
    sithPuppet_pKeyHashtable   = stdHashtbl_New(512u);

    if ( !sithPuppet_pClassHashtable || !sithPuppet_pKeyHashtable )
    {
        SITHLOG_ERROR("Could not allocate memory of puppets.\n");
        return 1;
    }

    sithPuppet_pHashtblSubmodes = stdHashtbl_New(168u);
    for ( size_t modeNum = 1; modeNum < STD_ARRAYLEN(sithPuppet_aStrSubModes); ++modeNum )
    {
        stdHashtbl_Add(sithPuppet_pHashtblSubmodes, sithPuppet_aStrSubModes[modeNum], (void*)modeNum);
    }

    return 0;
}

void sithPuppet_Shutdown(void)
{
    if ( sithPuppet_pClassHashtable )
    {
        stdHashtbl_Free(sithPuppet_pClassHashtable);
        sithPuppet_pClassHashtable = NULL;
    }

    if ( sithPuppet_pKeyHashtable )
    {
        stdHashtbl_Free(sithPuppet_pKeyHashtable);
        sithPuppet_pKeyHashtable = NULL;
    }

    if ( sithPuppet_pHashtblSubmodes )
    {
        stdHashtbl_Free(sithPuppet_pHashtblSubmodes);
        sithPuppet_pHashtblSubmodes = NULL;
    }
}

void J3DAPI sithPuppet_New(SithThing* pThing)
{
    SITH_ASSERTREL(pThing && pThing->renderData.pPuppet);

    pThing->pPuppetState = (SithPuppetState*)STDMALLOC(sizeof(SithPuppetState));
    if ( !pThing->pPuppetState )
    {
        pThing->pPuppetClass = NULL;
        return; // Fixed: Added return to prevent writting to and accessing null pointer
    }

    memset(pThing->pPuppetState, 0, sizeof(SithPuppetState));

    if ( pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0
        || (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 && pThing->type == SITH_THING_PLAYER )
    {
        pThing->pPuppetState->moveMode = SITHPUPPET_MOVEMODE_SWIM;
        pThing->pPuppetState->pFirstTrack = NULL;
    }
    else
    {
        pThing->pPuppetState->moveMode = SITHPUPPET_MOVEMODE_NORMAL;
        pThing->pPuppetState->pFirstTrack = NULL;
    }
}

void J3DAPI sithPuppet_Free(SithThing* pThing)
{
    if ( pThing->pPuppetState )
    {
        if ( pThing->pPuppetState->pFirstTrack )
        {
            SithPuppetTrack* pNextTrack;
            for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pNextTrack )
            {
                pNextTrack = pTrack->pNextTrack;
                stdMemory_Free(pTrack);
            }
        }

        stdMemory_Free(pThing->pPuppetState);
        pThing->pPuppetState = NULL;
    }
}

void J3DAPI sithPuppet_RemoveAllTracks(SithThing* pThing)
{
    SITH_ASSERTREL(pThing && pThing->renderData.pPuppet);

    SithPuppetTrack* pNextTrack;
    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pNextTrack )
    {
        if ( pTrack == STDMEMORY_FREEDPTR )
        {
            SITHLOG_ERROR("Pup track list is messed up, pointer to freed memory!\n");
            break;
        }

        if ( pTrack->trackNum == (int)STDMEMORY_FREEDPTR )
        {
            SITHLOG_ERROR("Pup track list is messed up, pointer to freed memory!\n");
            break;
        }

        pNextTrack = pTrack->pNextTrack;

        rdPuppet_RemoveTrack(pThing->renderData.pPuppet, pTrack->trackNum);
        if ( pTrack->pNextTrack != STDMEMORY_FREEDPTR )
        {
            stdMemory_Free(pTrack);
        }
    }

    pThing->pPuppetState->pFirstTrack = NULL;

    for ( size_t track = 0; track < RDPUPPET_MAX_TRACKS; ++track )
    {
        if ( pThing->renderData.pPuppet->aTracks[track].status )
        {
            rdPuppet_RemoveTrack(pThing->renderData.pPuppet, track);
        }
    }
}

void J3DAPI sithPuppet_UpdatePuppet(SithThing* pThing, float secDeltaTime)
{
    SITH_ASSERTREL(pThing != NULL);

    if ( pThing->pPuppetClass
        && pThing->pPuppetState
        && pThing->renderData.pPuppet
        && (sithMain_g_sith_mode.debugModeFlags & SITHDEBUG_PUPPETSYSTEM_DISABLED) == 0 )
    {
        if ( pThing->moveType == SITH_MT_PHYSICS && (pThing->flags & (SITH_TF_DISABLED | SITH_TF_DYING | SITH_TF_DESTROYED)) == 0 )
        {
            sithPuppet_UpdateThingMoveTracks(pThing, secDeltaTime);
            sithPuppet_PlayFidgetMode(pThing);
        }

        SithPuppetTrack* pNextTrack;
        for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pNextTrack )
        {
            if ( pTrack->pNextTrack == STDMEMORY_FREEDPTR )
            {
                pTrack->pNextTrack = NULL;
            }

            pNextTrack = pTrack->pNextTrack;

            if ( !pThing->renderData.pPuppet->aTracks[pTrack->trackNum].pKFTrack )
            {
                SITHLOG_ERROR("Removed submode %d from pup list, no KFTrack!\n", pTrack->submode);
                sithPuppet_FreeTrack(pThing, pTrack);
            }

            else if ( (pThing->renderData.pPuppet->aTracks[pTrack->trackNum].status & RDPUPPET_TRACK_PLAYING) == 0 )
            {
                SITHLOG_ERROR("Removed submode %d from pup list, not playing!\n", pTrack->submode);
                sithPuppet_FreeTrack(pThing, pTrack);
            }
        }

        int majorMode     = pThing->pPuppetState->majorMode;
        size_t numUpdated = rdPuppet_UpdateTracks(pThing->renderData.pPuppet, secDeltaTime);
        if ( pThing->pPuppetState->majorMode != majorMode )
        {
            numUpdated = rdPuppet_UpdateTracks(pThing->renderData.pPuppet, secDeltaTime);
        }

        if ( numUpdated && pThing->moveType == SITH_MT_PATH )
        {
            pThing->orient.dvec = rdroid_g_zeroVector3;

            pThing->renderData.bSkipBuildingJoints = 0;
            rdPuppet_BuildJointMatrices(&pThing->renderData, &pThing->orient);
            pThing->renderData.bSkipBuildingJoints = 1;

            rdVector3 moveNorm;
            rdVector_Add3(&moveNorm, &pThing->renderData.paJointMatrices->dvec, &pThing->moveInfo.pathMovement.curOrient.dvec);
            rdVector_Sub3Acc(&moveNorm, &pThing->pos);

            if ( moveNorm.x != 0.0f || moveNorm.y != 0.0f || moveNorm.z != 0.0f )
            {
                float moveDist = rdVector_Normalize3Acc(&moveNorm);
                sithCollision_MoveThing(pThing, &moveNorm, moveDist, 0);
            }

            rdVector_Sub3(&moveNorm, &pThing->pos, &pThing->renderData.paJointMatrices->dvec);
            for ( size_t i = 0; i < pThing->renderData.data.pModel3->numHNodes; ++i )
            {
                rdVector_Add3Acc(&pThing->renderData.paJointMatrices[i].dvec, &moveNorm);
            }
        }

        if ( pThing->thingInfo.actorInfo.bForceMovePlay == 1 )
        {
            bool bSkipUpdatingJoints = false;
            pThing->orient.dvec = rdroid_g_zeroVector3;

            pThing->renderData.bSkipBuildingJoints = 0;
            rdPuppet_BuildJointMatrices(&pThing->renderData, &pThing->orient);
            pThing->renderData.bSkipBuildingJoints = 1;

            rdVector3 moveNorm;
            rdVector_Add3(&moveNorm, &pThing->renderData.paJointMatrices->dvec, &pThing->forceMoveStartPos);
            rdVector_Sub3Acc(&moveNorm, &pThing->pos);

            float distMoved = 0.0f;
            float moveDist = 0.0f;

            if ( moveNorm.x != 0.0f || moveNorm.y != 0.0f || moveNorm.z != 0.0f )
            {
                rdVector_Copy3(&pThing->moveInfo.physics.velocity, &moveNorm);
                moveDist = rdVector_Normalize3Acc(&moveNorm);
                distMoved = sithCollision_MoveThing(pThing, &moveNorm, moveDist, 0xA00);
            }

            if ( moveDist * 0.25f > distMoved && pThing->type == SITH_THING_PLAYER )
            {
                switch ( pThing->moveStatus )
                {
                    case SITHPLAYERMOVE_STILL:
                    case SITHPLAYERMOVE_CRAWL_STILL:
                    case SITHPLAYERMOVE_UNKNOWN_4:
                    case SITHPLAYERMOVE_UNKNOWN_5:
                    case SITHPLAYERMOVE_HANGING:
                    case SITHPLAYERMOVE_CLIMBIDLE:
                    case SITHPLAYERMOVE_WHIPSWINGING:
                    case SITHPLAYERMOVE_SWIMIDLE:
                    case SITHPLAYERMOVE_CLIMBING_UP:
                    case SITHPLAYERMOVE_CLIMBING_DOWN:
                    case SITHPLAYERMOVE_CLIMBING_LEFT:
                    case SITHPLAYERMOVE_CLIMBING_RIGHT:
                    case SITHPLAYERMOVE_PULLINGUP:
                    case SITHPLAYERMOVE_PULLINGUP_1M:
                    case SITHPLAYERMOVE_WHIP_CLIMB_START:
                    case SITHPLAYERMOVE_STAND_TO_CRAWL:
                    case SITHPLAYERMOVE_CRAWL_TO_STAND:
                    case SITHPLAYERMOVE_CLIMB_DOWN_TO_MOUNT:
                    case SITHPLAYERMOVE_CLIMB_TO_HANG:
                        break;

                    default:
                        sithPuppet_StopForceMove(pThing, 1);
                        bSkipUpdatingJoints = true;
                        break;
                }
            }

            if ( !bSkipUpdatingJoints )
            {
                rdVector_Sub3(&moveNorm, &pThing->pos, &pThing->renderData.paJointMatrices->dvec);
                for ( size_t i = 0; i < pThing->renderData.data.pModel3->numHNodes; ++i )
                {
                    rdVector_Add3Acc(&pThing->renderData.paJointMatrices[i].dvec, &moveNorm);
                }
            }
        }
    }
}

void J3DAPI sithPuppet_PlayFidgetMode(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->pPuppetState);

    if ( (pThing->type != SITH_THING_PLAYER || !pThing->thingInfo.actorInfo.curWeaponID)
        && (pThing->controlType != SITH_CT_AI || !pThing->controlInfo.aiControl.pLocal || (pThing->controlInfo.aiControl.pLocal->mode & SITHAI_MODE_BLOCK) == 0) )
    {
        for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pTrack->pNextTrack )
        {
            if ( pTrack == STDMEMORY_FREEDPTR || pTrack->submode == SITHPUPPETSUBMODE_FIDGET || pTrack->submode == SITHPUPPETSUBMODE_FIDGET2 )
            {
                return;
            }
        }

        if ( pThing->pPuppetState->submode == SITHPUPPETSUBMODE_STAND
            && (double)pThing->pPuppetState->msecLastFidgetStillMoveTime + 30000.0f < (double)sithTime_g_msecGameTime )
        {
            float rnd = SITH_RANDF();
            if ( rnd < 0.30000001f )
            {
                sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_FIDGET, NULL);
                pThing->pPuppetState->msecLastFidgetStillMoveTime = sithTime_g_msecGameTime;
            }
            else
            {
                if ( rnd < 0.60000002f )
                {
                    sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_FIDGET2, NULL);
                }
            }
        }
    }
}

void J3DAPI sithPuppet_StopFridgetTrack(SithThing* pThing)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->pPuppetState);

    pThing->pPuppetState->msecLastFidgetStillMoveTime = sithTime_g_msecGameTime;

    if ( pThing->controlType != SITH_CT_AI || !pThing->controlInfo.aiControl.pLocal || (pThing->controlInfo.aiControl.pLocal->mode & SITHAI_MODE_BLOCK) == 0 )
    {
        for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )
        {
            if ( pTrack->submode == SITHPUPPETSUBMODE_FIDGET || pTrack->submode == SITHPUPPETSUBMODE_FIDGET2 )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.0f);
                return;
            }
        }
    }
}

int J3DAPI sithPuppet_IsModeOnTrack(const SithThing* pThing, SithPuppetSubMode mode)
{
    SITH_ASSERTREL(pThing);

    if ( !pThing->pPuppetClass || mode < 0 || mode >= SITH_PUPPET_NUMSUBMODES ) // Added: Check for < 0
    {
        return 0;
    }

    if ( !pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][mode].pKeyframe )
    {
        return 0;
    }

    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )
    {
        if ( pTrack->submode == mode )
        {
            return 1;
        }
    }

    return 0;
}

int J3DAPI sithPuppet_IsAnyModeOnTrack(const SithThing* pThing, SithPuppetSubMode firstMode, SithPuppetSubMode lastMode)
{
    SITH_ASSERTREL(pThing);

    SithPuppetSubMode startMode = firstMode;
    if ( firstMode >= lastMode )
    {
        startMode = lastMode;
    }

    SithPuppetSubMode endMode = firstMode;
    if ( firstMode <= lastMode )
    {
        endMode = lastMode;
    }

    for ( SithPuppetSubMode mode = startMode; mode <= endMode; ++mode )
    {
        rdKeyframe* pKeyframe = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][mode].pKeyframe;
        if ( pKeyframe )
        {
            for ( size_t i = 0; i < RDPUPPET_MAX_TRACKS; ++i )
            {
                if ( pThing->renderData.pPuppet->aTracks[i].pKFTrack == pKeyframe )
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

SithPuppetTrack* J3DAPI sithPuppet_FindActiveTrack(const SithThing* pThing, const rdKeyframe* pKfTrack)
{
    SITH_ASSERTREL(pThing);

    if ( !pKfTrack )
    {
        SITHLOG_ERROR("FindActiveTrack(): NULL track to search for THING '%s' passed.\n", pThing->aName);
        return NULL;
    }

    if ( !pThing->pPuppetState )
    {
        return NULL;
    }

    SithPuppetTrack* pTrack = NULL;
    for ( pTrack = pThing->pPuppetState->pFirstTrack; ; pTrack = pTrack->pNextTrack )
    {
        if ( !pTrack || pTrack == STDMEMORY_FREEDPTR )
        {
            return NULL;
        }

        if ( pTrack->pSubmode->pKeyframe == pKfTrack )
        {
            break;
        }
    }

    if ( (pThing->renderData.pPuppet->aTracks[pTrack->trackNum].status & RDPUPPET_TRACK_PLAYING) == 0 )
    {
        return NULL;
    }

    if ( (pThing->renderData.pPuppet->aTracks[pTrack->trackNum].status & RDPUPPET_TRACK_FADEOUT) != 0 )
    {
        return NULL;
    }

    return pTrack;
}

void J3DAPI sithPuppet_UpdateThingMoveTracks(SithThing* pThing, float secDeltaTime)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->renderData.pPuppet);
    SITH_ASSERTREL(pThing->moveType == SITH_MT_PHYSICS);

    float moveSpeed;
    if ( pThing->controlType == SITH_CT_AI
        && pThing->controlInfo.aiControl.pLocal
        && (pThing->moveInfo.physics.flags & (SITH_PF_UNKNOWN_8000000 | SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) == 0
        && ((pThing->thingInfo.actorInfo.flags & SITH_AF_NOSLOPEMOVE) == 0 || (pThing->thingInfo.actorInfo.flags & SITH_AF_HUMAN) == 0) )
    {
        moveSpeed = sithAIMove_UpdateAIMove(pThing->controlInfo.aiControl.pLocal) * secDeltaTime;
    }
    else
    {
        moveSpeed = sithPuppet_UpdateThingMove(pThing, NULL) * secDeltaTime;
    }

    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )
    {
        if ( (pTrack->pSubmode->flags & RDKEYFRAME_PUPPET_CONTROLLED) != 0 )
        {
            if ( pTrack->submode == SITHPUPPETSUBMODE_RUN )
            {
                float numFrames = fabsf(moveSpeed) * 90.0f;
                rdPuppet_AdvanceTrack(pThing->renderData.pPuppet, pTrack->trackNum, numFrames);
            }
            else
            {
                if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_FASTMOVE15) != 0 )
                {
                    float numFrames = fabsf(moveSpeed) * 500.0f;
                    rdPuppet_AdvanceTrack(pThing->renderData.pPuppet, pTrack->trackNum, numFrames);
                }

                else if ( (pThing->thingInfo.actorInfo.flags & SITH_AF_FASTMOVE10) != 0 )
                {
                    float numFrames = fabsf(moveSpeed) * 300.0f;
                    rdPuppet_AdvanceTrack(pThing->renderData.pPuppet, pTrack->trackNum, numFrames);
                }
                else
                {
                    float numFrames = fabsf(moveSpeed) * 180.0f;
                    rdPuppet_AdvanceTrack(pThing->renderData.pPuppet, pTrack->trackNum, numFrames);
                }
            }
        }
    }
}

float J3DAPI sithPuppet_UpdateThingMove(SithThing* pThing, rdPuppetTrackCallback pCallback)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->pPuppetClass);
    SITH_ASSERTREL(pThing->renderData.pPuppet);

    //int v10 = 0x3E4CCCCD; // This is leftover from debug version

    size_t axis;
    float velX, velY, velZ;
    float moveSpeed = sithPuppet_GetThingLocalVelocityAxis(pThing, &axis, &velX, &velY, &velZ);

    if ( (pThing->type == SITH_THING_PLAYER && pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0
        || (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0)
        && !pThing->thingInfo.actorInfo.bForceMovePlay
        && pThing->moveStatus != SITHPLAYERMOVE_ACTIVATING )
    {
        pThing->moveStatus = SITHPLAYERMOVE_SWIMIDLE;
    }

    if ( pThing->thingInfo.actorInfo.bForceMovePlay == 1 )
    {
        return moveSpeed;
    }

    if ( pThing->thingInfo.actorInfo.bControlsDisabled )
    {
        return moveSpeed;
    }

    SithPuppetSubMode submode = pThing->pPuppetState->submode;
    if ( pThing->type == SITH_THING_ACTOR && pThing->controlInfo.aiControl.pLocal && !sithAIMove_AIGetMoveState(pThing->controlInfo.aiControl.pLocal) )
    {
        sithAIMove_GetAIMoveModes(pThing, moveSpeed, axis, &pThing->moveStatus, &submode);
    }

    switch ( pThing->moveStatus )
    {
        case SITHPLAYERMOVE_STILL:
        {
            if ( axis <= 1 ) // left or forward
            {
                if ( moveSpeed < 0.0f )
                {
                    submode = SITHPUPPETSUBMODE_WALKBACK;
                    pThing->moveStatus = SITHPLAYERMOVE_WALKING;
                }

                else if ( moveSpeed <= 0.000099999997f )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_WALK;
                    pThing->moveStatus = SITHPLAYERMOVE_WALKING;
                }
            }
            else if ( axis == 2 ) // up
            {
                if ( moveSpeed >= 0.0f || (pThing->moveInfo.physics.flags & SITH_PF_FLY) != 0 )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                }
                else
                {
                    if ( pThing->moveInfo.physics.velocity.x == 0.0f && pThing->moveInfo.physics.velocity.y == 0.0f )
                    {
                        submode = SITHPUPPETSUBMODE_FALL;
                    }
                    else
                    {
                        submode = SITHPUPPETSUBMODE_FALLFORWARD;
                    }

                    pThing->moveStatus = SITHPLAYERMOVE_FALLING;
                }
            }
            else // 99 not moving
            {
                moveSpeed = pThing->moveInfo.physics.angularVelocity.y * 0.00019999999f; // TODO: Verify if  it's ok setting yaw speed to move speed here
                if ( moveSpeed < -0.01f )
                {
                    submode = SITHPUPPETSUBMODE_TURNRIGHT;
                }
                else if ( moveSpeed <= 0.01f )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_TURNLEFT;
                }
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_WALKING:
        {
            if ( axis == 0 ) // left
            {
                if ( moveSpeed != 0.0f )
                {
                    submode = SITHPUPPETSUBMODE_WALK;
                }
            }
            else if ( axis == 1 ) // forward
            {
                if ( moveSpeed < 0.0f )
                {
                    submode = SITHPUPPETSUBMODE_WALKBACK;
                }
                else if ( moveSpeed <= 0.000099999997f )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_WALK;
                }
            }
            else // up or not moving
            {
                submode = SITHPUPPETSUBMODE_STAND;
                pThing->moveStatus = SITHPLAYERMOVE_STILL;
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_RUNNING:
        {
            if ( axis == 0 ) // left
            {
                if ( moveSpeed == 0.0f )
                {
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                    submode = SITHPUPPETSUBMODE_STAND;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_RUN;
                }
            }
            else if ( axis == 1 ) // forward
            {
                if ( moveSpeed == 0.0f )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_RUN;
                }
            }
            else if ( moveSpeed < 0.0f && (pThing->moveInfo.physics.flags & SITH_PF_FLY) == 0 )
            {
                if ( pThing->moveInfo.physics.velocity.x == 0.0f && pThing->moveInfo.physics.velocity.y == 0.0f )
                {
                    submode = SITHPUPPETSUBMODE_FALL;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_FALLFORWARD;
                }

                pThing->moveStatus = SITHPLAYERMOVE_FALLING;
            }
            else
            {
                submode = SITHPUPPETSUBMODE_STAND;
                pThing->moveStatus = SITHPLAYERMOVE_STILL;
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_CRAWL_STILL:
        {
            if ( !pThing->thingInfo.actorInfo.bForceMovePlay )
            {
                if ( axis == 1 ) // forward
                {
                    if ( moveSpeed < 0.0f )
                    {
                        submode = SITHPUPPETSUBMODE_WALKBACK;
                    }

                    else if ( moveSpeed > 0.000099999997f )
                    {
                        submode = SITHPUPPETSUBMODE_WALK;
                    }
                }
                else  // left or up or not moving
                {
                    float yawSpeed = pThing->moveInfo.physics.angularVelocity.y * 0.00019999999f;
                    if ( yawSpeed < -0.01f ) // rotate right
                    {
                        submode = SITHPUPPETSUBMODE_TURNRIGHT;
                    }
                    else if ( yawSpeed <= 0.01f ) // still
                    {
                        submode = SITHPUPPETSUBMODE_STAND;
                    }
                    else
                    {
                        submode = SITHPUPPETSUBMODE_TURNLEFT;
                    }
                }
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_UNKNOWN_4:
        case SITHPLAYERMOVE_UNKNOWN_5:
        case SITHPLAYERMOVE_PUSHING:
        case SITHPLAYERMOVE_PULLING:
        case SITHPLAYERMOVE_WHIPSWINGING:
        case SITHPLAYERMOVE_JUMPFWD:
        case SITHPLAYERMOVE_JUMPUP:
        case SITHPLAYERMOVE_JUMP_READY:
        case SITHPLAYERMOVE_PUSHPULL_READY:
        case SITHPLAYERMOVE_MOUNTING_WALL:
        case SITHPLAYERMOVE_CLIMBING_UP:
        case SITHPLAYERMOVE_CLIMBING_DOWN:
        case SITHPLAYERMOVE_CLIMBING_LEFT:
        case SITHPLAYERMOVE_CLIMBING_RIGHT:
        case SITHPLAYERMOVE_PULLINGUP:
        case SITHPLAYERMOVE_PULLINGUP_1M:
        case SITHPLAYERMOVE_MINECAR_IDLE:
        case SITHPLAYERMOVE_MINECAR_BOARDING:
        case SITHPLAYERMOVE_MINECAR_UNBOARDING_LEFT:
        case SITHPLAYERMOVE_MINECAR_UNBOARDING_RIGHT:
        case SITHPLAYERMOVE_MINECAR_DUCKING:
        case SITHPLAYERMOVE_MINECAR_DUCKED:
        case SITHPLAYERMOVE_MINECAR_GETTING_UP:
        case SITHPLAYERMOVE_JEEP_BOARDING:
        case SITHPLAYERMOVE_ROLLING_LEFT:
        case SITHPLAYERMOVE_ROLLING_RIGHT:
        case SITHPLAYERMOVE_STRAFING_LEFT:
        case SITHPLAYERMOVE_STRAFING_RIGHT:
        case SITHPLAYERMOVE_JUMPBACK:
        case SITHPLAYERMOVE_STAND_TO_CRAWL:
        case SITHPLAYERMOVE_CRAWL_TO_STAND:
        case SITHPLAYERMOVE_JUMPROLLBACK:
        case SITHPLAYERMOVE_JUMPROLLFWD:
        case SITHPLAYERMOVE_CLIMB_DOWN_TO_MOUNT:
        case SITHPLAYERMOVE_CLIMB_TO_HANG:
        case SITHPLAYERMOVE_JUMPLEFT:
        case SITHPLAYERMOVE_JUMPRIGHT:
        case SITHPLAYERMOVE_LEAPFWD:
        case SITHPLAYERMOVE_TURNING_LEFT_90_DEGREES:
        case SITHPLAYERMOVE_TURNING_RIGHT_90_DEGREES:
        {
            return moveSpeed;
        }
        case SITHPLAYERMOVE_HANGING:
        {
            submode = SITHPUPPETSUBMODE_HANGLEDGE;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_CLIMBIDLE:
        {
            submode = SITHPUPPETSUBMODE_CLIMBWALLIDLE;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_WHIPCLIMBIDLE:
        case SITHPLAYERMOVE_WHIP_CLIMB_START:
        {
            submode = SITHPUPPETSUBMODE_WHIPCLIMBIDLE;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_SWIMIDLE:
        {
            bool bFloating = false;
            if ( (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 || (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) == 0 ) {
                bFloating = true;
            }

            bool bSwimming = false;
            if ( pThing->pInSector
                && ((pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0 || bFloating)
                && pThing->pPuppetState->moveMode != SITHPUPPET_MOVEMODE_SWIM )
            {
                sithPuppet_SetMoveMode(pThing, SITHPUPPET_MOVEMODE_SWIM);
                bSwimming = true;
            }

            if ( axis == 1 ) // left
            {
                if ( moveSpeed < -0.04f ) // rotate/move right
                {
                    submode = SITHPUPPETSUBMODE_WALKBACK;
                    if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_WALKBACK
                        || SITH_ISFRAMECYCLE(pThing->idx, 8) && SITH_RAND() < 0.40000001f) // On every 8th frame and at random
                        && !bFloating )
                    {
                        // Create ripples in water
                        sithFX_CreateWaterRipple(pThing);
                    }
                }
                else if ( moveSpeed <= 0.04f ) // still
                {
                    if ( (pThing->flags & SITH_TF_SUBMERGED) != 0 && (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) == 0 || bFloating )
                    {
                        submode = SITHPUPPETSUBMODE_RISING;
                        if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_RISING
                            || SITH_ISFRAMECYCLE(pThing->idx, 4) && SITH_RAND() < 0.30000001f) // On every 4th frame and at random
                            && !bFloating )
                        {
                            // Create ripples in water
                            sithFX_CreateBubble(pThing);
                        }
                    }
                    else
                    {
                        submode = SITHPUPPETSUBMODE_STAND;
                        if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_STAND
                            || SITH_ISFRAMECYCLE(pThing->idx, 8) && SITH_RAND() < 0.30000001f) // On every 8th frame and at random
                            && !bFloating )
                        {
                            sithFX_CreateWaterRipple(pThing);
                        }
                    }
                }
                else if ( (pThing->flags & SITH_TF_SUBMERGED) != 0 && (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) == 0 || bFloating )
                {
                    // Here is turning/moving left

                    submode = SITHPUPPETSUBMODE_RUN;
                    if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_RUN
                        || SITH_ISFRAMECYCLE(pThing->idx, 4) && SITH_RAND() < 0.30000001f) // On every 4th frame and at random
                        && !bFloating )
                    {
                        // Create breath bubbles
                        sithFX_CreateBubble(pThing);
                    }
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_WALK;
                    if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_WALK
                        || SITH_ISFRAMECYCLE(pThing->idx, 8) && SITH_RAND() < 0.30000001f) // On every 8th frame and at random
                        && !bFloating )
                    {
                        // Create ripples in water
                        sithFX_CreateWaterRipple(pThing);
                    }
                }
            }
            else if ( (pThing->flags & SITH_TF_SUBMERGED) != 0 && (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) == 0 || bFloating )
            {
                 // axis forward or up or not moving

                submode = SITHPUPPETSUBMODE_RISING;
                if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_RISING
                    || SITH_ISFRAMECYCLE(pThing->idx, 8) && SITH_RAND() < 0.30000001f) // On every 8th frame and at random
                    && !bFloating )
                {
                    sithFX_CreateBubble(pThing);
                }
            }
            else
            {
                // On water surface here

                submode = SITHPUPPETSUBMODE_STAND;
                if ( (pThing->pPuppetState->submode != SITHPUPPETSUBMODE_STAND
                    || SITH_ISFRAMECYCLE(pThing->idx, 8) && SITH_RAND() < 0.30000001f) // on every 8th frame and at random
                    && !bFloating )
                {
                    // Create ripples in water
                    sithFX_CreateWaterRipple(pThing);
                }
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_FALLING:
        {
            if ( pThing->moveInfo.physics.velocity.x == 0.0f && pThing->moveInfo.physics.velocity.y == 0.0f )
            {
                submode = SITHPUPPETSUBMODE_FALL;
            }
            else
            {
                submode = SITHPUPPETSUBMODE_FALLFORWARD;
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_LAND:
        {
            submode = SITHPUPPETSUBMODE_STAND;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_JEEP_STILL:
        {
            float yawSpeed = pThing->moveInfo.physics.angularVelocity.y * 0.00019999999f;
            if ( moveSpeed <= 0.001f && (moveSpeed >= -0.001f || sithControl_GetKey(SITHCONTROL_BACK, 0)) )
            {
                if ( moveSpeed < -0.001f )
                {
                    submode = SITHPUPPETSUBMODE_WALKBACK;
                    if ( sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_WALKBACK) )
                    {
                        if ( yawSpeed >= -0.001f )
                        {
                            if ( yawSpeed <= 0.001f )
                            {
                                sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADL, 0.1f);
                                sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADR, 0.1f);
                            }
                            else
                            {
                                sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_HITHEADR, pCallback);
                            }
                        }
                        else
                        {
                            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_HITHEADL, pCallback);
                        }
                    }
                }
                else
                {
                    if ( sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_WALKBACK) )
                    {
                        sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_WALKBACK, 0.1f);
                        sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADL, 0.01f);
                        sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADR, 0.01f);

                        submode = SITHPUPPETSUBMODE_LEAP;
                        sithPuppet_SetSubMode(pThing, submode, pCallback);
                        return moveSpeed;
                    }

                    if ( sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_LEAP) )
                    {
                        return moveSpeed;
                    }

                    if ( pThing->pPuppetState->pFirstTrack )
                    {
                        return moveSpeed;
                    }

                    submode = SITHPUPPETSUBMODE_STAND;
                }
            }
            else
            {
                if ( sithPuppet_IsModeOnTrack(pThing, SITHPUPPETSUBMODE_WALKBACK) )
                {
                    sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_WALKBACK, 0.1f);
                    sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADL, 0.01f);
                    sithPuppet_StopMode(pThing, SITHPUPPETSUBMODE_HITHEADR, 0.01f);

                    submode = SITHPUPPETSUBMODE_LEAP;
                    sithPuppet_SetSubMode(pThing, submode, pCallback);
                    return moveSpeed;
                }

                if ( yawSpeed < -0.001f )
                {
                    submode = SITHPUPPETSUBMODE_TURNRIGHT;
                }

                else if ( yawSpeed <= 0.001f )
                {
                    submode = SITHPUPPETSUBMODE_STAND;
                }
                else
                {
                    submode = SITHPUPPETSUBMODE_TURNLEFT;
                }
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
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
        case SITHPLAYERMOVE_UNKNOWN_45:
        case SITHPLAYERMOVE_UNKNOWN_46:
        case SITHPLAYERMOVE_SLIDING:
        case SITHPLAYERMOVE_RAFT_BOARDING:
        case SITHPLAYERMOVE_RAFT_UNBOARDING_LEFT:
        case SITHPLAYERMOVE_RAFT_UNBOARDING_RIGHT:
        {
            pThing->pPuppetState->submode = SITHPUPPETSUBMODE_STAND;
            return moveSpeed;
        }
        case SITHPLAYERMOVE_ACTIVATING:
        {
            return moveSpeed;
        }
        case SITHPLAYERMOVE_SLIDEDOWNFORWARD:
        {
            submode = SITHPUPPETSUBMODE_SLIDEDOWNFWD;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_UNKNOWN_63:
        {
            SithPuppetTrack* pTrack = sithPuppet_GetModeTrackImpl(pThing, SITHPUPPETSUBMODE_JUMPREADY);
            if ( pTrack )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.0f);
                sithPuppet_FreeTrack(pThing, pTrack);
            }

            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_TURNING_LEFT:
        {
            submode = SITHPUPPETSUBMODE_TURNLEFT;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_TURNING_RIGHT:
        {
            submode = SITHPUPPETSUBMODE_TURNRIGHT;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        case SITHPLAYERMOVE_WALK2STAND:
        case SITHPLAYERMOVE_STAND2WALK:
        {
            return moveSpeed;
        }
        case SITHPLAYERMOVE_JEWELFLYING:
        {
            return moveSpeed;
        }
        case SITHPLAYERMOVE_SLIDEDOWNBACK:
        {
            submode = SITHPUPPETSUBMODE_SLIDEDOWNBACK;
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
        default:
        {
            sithPuppet_SetSubMode(pThing, submode, pCallback);
            return moveSpeed;
        }
    }
}

int J3DAPI sithPuppet_SetSubMode(SithThing* pThing, SithPuppetSubMode newSubMode, rdPuppetTrackCallback pfCallback)
{
    SITH_ASSERTREL(newSubMode < SITH_PUPPET_NUMSUBMODES);
    if ( !pThing->pPuppetClass || !pThing->pPuppetState )
    {
        return -1;
    }

    bool bTrackPlaying = false;
    bool bFadeTrack = false;

    int trackNum = -1;
    SithPuppetTrack* pNextTrack;
    for ( SithPuppetTrack* pCurTrack = pThing->pPuppetState->pFirstTrack; pCurTrack && pCurTrack != STDMEMORY_FREEDPTR; pCurTrack = pNextTrack )
    {
        bool bTrackFadding = false;
        pNextTrack = pCurTrack->pNextTrack;

        if ( pCurTrack->submode == newSubMode )
        {
            if ( (pThing->renderData.pPuppet->aTracks[pCurTrack->trackNum].status & RDPUPPET_TRACK_FADEOUT) != 0 )
            {
                bTrackFadding = true;
            }
            else
            {
                bTrackPlaying = true;
                trackNum = pCurTrack->trackNum;
            }
        }

        if ( !bTrackPlaying
            && (pCurTrack->submode < (unsigned int)SITHPUPPETSUBMODE_JUMPROLLFWD || pCurTrack->submode >(unsigned int)SITHPUPPETSUBMODE_GRABARMS) )
        {
            bFadeTrack = true;
            if ( bTrackFadding )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pCurTrack->trackNum, 0.0f);
                continue;
            }

            if ( pThing->controlType == SITH_CT_AI && (pThing->controlInfo.aiControl.pLocal->submode & SITHAI_SUBMODE_QUICKMODEFADE) != 0 )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pCurTrack->trackNum, 0.0049999999f);
            }
            else if ( pThing->controlType == SITH_CT_AI && (pThing->controlInfo.aiControl.pLocal->submode & SITHAI_SUBMODE_SLOWMODEFADE) != 0 )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pCurTrack->trackNum, 0.25f);
            }
            else
            {
                if ( pThing->moveStatus == SITHPLAYERMOVE_CRAWL_STILL )
                {
                    sithPuppet_StopKey(pThing->renderData.pPuppet, pCurTrack->trackNum, 0.0f);
                    continue;
                }

                sithPuppet_StopKey(pThing->renderData.pPuppet, pCurTrack->trackNum, 0.07f);
            }
        }
    }

    pThing->pPuppetState->submode = newSubMode;
    if ( bTrackPlaying )
    {
        return trackNum;
    }

    trackNum = sithPuppet_PlayMode(pThing, newSubMode, pfCallback);
    if ( !bFadeTrack )
    {
        return trackNum;
    }

    if ( trackNum != -1
        && trackNum != SITHPUPPET_PLAYERROR_ALREADYPLAYING
        && pThing->controlType == SITH_CT_AI
        && (pThing->controlInfo.aiControl.pLocal->submode & SITHAI_SUBMODE_SLOWMODEFADE) != 0 )
    {
        rdPuppet_FadeInTrack(pThing->renderData.pPuppet, trackNum, 0.25f);
    }

    return trackNum;
}

void J3DAPI sithPuppet_SetMoveMode(SithThing* pThing, SithPuppetMoveMode newMode)
{
    SITH_ASSERTREL(newMode < SITH_PUPPET_NUMMOVEMODES);

    if ( pThing->pPuppetClass && pThing->pPuppetState )
    {
        pThing->pPuppetState->majorMode = pThing->pPuppetState->armedMode + SITH_PUPPET_NUMARMEDMODES * newMode;
        pThing->pPuppetState->moveMode  = newMode;

        SithPuppetTrack* pNextTrack;
        for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pNextTrack )
        {
            pNextTrack = pTrack->pNextTrack;
            sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.0f);
        }

        sithPuppet_ClearTrackList(pThing);
        pThing->thingInfo.actorInfo.bControlsDisabled = 0;
    }
}

void J3DAPI sithPuppet_SetArmedMode(SithThing* pThing, unsigned int newMode)
{
    SITH_ASSERTREL(newMode < SITH_PUPPET_NUMARMEDMODES);
    if ( pThing->pPuppetClass )
    {
        pThing->pPuppetState->armedMode = newMode;
        pThing->pPuppetState->majorMode = newMode + SITH_PUPPET_NUMARMEDMODES * pThing->pPuppetState->moveMode;
    }
}

int J3DAPI sithPuppet_PlayMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback)
{
    SITH_ASSERTREL(pThing);
    if ( !pThing->pPuppetClass || submode < 0 || submode >= SITH_PUPPET_NUMSUBMODES ) // Added: Check submode < 0
    {
        SITHLOG_ERROR("PlayMode(): Invalid data for THING '%s' submode %d.\n", pThing->aName, submode);
        return -1;
    }

    SithPuppetClassSubmode* pSubmode = &pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][submode];
    if ( !pSubmode->pKeyframe )
    {
        return -1;
    }

    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )
    {
        if ( pTrack->submode == submode )
        {
            return SITHPUPPET_PLAYERROR_ALREADYPLAYING; // already playing
        }
    }

    if ( submode != SITHPUPPETSUBMODE_FIDGET && submode != SITHPUPPETSUBMODE_FIDGET2 )
    {
        sithPuppet_StopFridgetTrack(pThing);
    }

    int trackNum = sithPuppet_PlayKey(pThing->renderData.pPuppet, pSubmode->pKeyframe, pSubmode->lowPriority, pSubmode->highPriority, pSubmode->flags, pfCallback);
    if ( trackNum < 0 )
    {
        SITHLOG_DEBUG("PlayMode(): Attempt to add track for THING '%s' submode '%s' failed.\n", pThing->aName, sithPuppet_aStrSubModes[submode]);
        return -1;
    }

    SithPuppetTrack* pNewTrack = (SithPuppetTrack*)STDMALLOC(sizeof(SithPuppetTrack));
    SITH_ASSERTREL(pNewTrack);

    pNewTrack->pSubmode   = pSubmode;
    pNewTrack->trackNum   = trackNum;
    pNewTrack->submode    = submode;
    pNewTrack->pNextTrack = NULL;
    sithPuppet_AddTrack(pThing, pNewTrack);

    return trackNum;
}

int J3DAPI sithPuppet_PlayForceMoveMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback)
{
    SITH_ASSERTREL(pThing);
    if ( submode < 0 || pThing->pPuppetClass == NULL || submode > SITH_PUPPET_NUMSUBMODES )
    {
        return -1;
    }

    SithPuppetClassSubmode* pSubmode = &pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][submode];
    if ( !pSubmode->pKeyframe )
    {
        SITHLOG_ERROR("No valid track for force-move anim.\n");
        return -1;
    }

    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )// TODO: Dont compare against the 0xDDDDDD address
    {
        if ( pTrack->submode == submode )
        {
            return SITHPUPPET_PLAYERROR_ALREADYPLAYING; // already playing
        }
    }

    sithPuppet_StopFridgetTrack(pThing);

    int trackNum = sithPuppet_PlayKey(pThing->renderData.pPuppet, pSubmode->pKeyframe, pSubmode->lowPriority, pSubmode->highPriority, pSubmode->flags, pfCallback);
    if ( trackNum < 0 )
    {
        SITHLOG_ERROR("No valid track for force-move anim.\n");
        return -1;
    }

    pThing->thingInfo.actorInfo.bForceMovePlay = 1;
    SithPuppetTrack* pNewTrack = (SithPuppetTrack*)STDMALLOC(sizeof(SithPuppetTrack));
    SITH_ASSERTREL(pNewTrack);

    pNewTrack->pSubmode   = pSubmode;
    pNewTrack->trackNum   = trackNum;
    pNewTrack->submode    = submode;
    pNewTrack->pNextTrack = NULL;
    sithPuppet_AddTrack(pThing, pNewTrack);

    return trackNum;
}

int J3DAPI sithPuppet_PlayKey(rdPuppet* pPuppet, rdKeyframe* pTrack, int lowPriority, int highPriority, rdKeyframeFlags flags, rdPuppetTrackCallback pfCallback)
{
    SITH_ASSERTREL(pPuppet && pTrack);

    bool bAddTrack = true;
    int track;
    if ( (flags & RDKEYFRAME_RESTART_ACTIVE) != 0 )
    {
        for ( track = 0; track < RDPUPPET_MAX_TRACKS; ++track )
        {
            if ( pPuppet->aTracks[track].pKFTrack == pTrack )
            {
                rdPuppet_ResetTrack(pPuppet, track);
                bAddTrack = false;
                break;
            }
        }
    }

    if ( bAddTrack && (track = rdPuppet_AddTrack(pPuppet, pTrack, lowPriority, highPriority), track < 0) )
    {
        SITHLOG_ERROR("Could not get free track to play in.\n");
        return -1;
    }

    if ( pfCallback )
    {
        rdPuppet_SetCallback(pPuppet, track, pfCallback);
    }
    else
    {
        rdPuppet_SetCallback(pPuppet, track, sithPuppet_DefaultCallback);
    }

    if ( (flags & RDKEYFRAME_NOLOOP) != 0 )
    {
        rdPuppet_SetStatus(pPuppet, track, RDPUPPET_TRACK_NOLOOP);
    }
    else if ( (flags & RDKEYFRAME_FADEOUT_NOLOOP) != 0 )
    {
        rdPuppet_SetStatus(pPuppet, track, RDPUPPET_TRACK_FADEOUT_NOLOOP);
    }

    else if ( (flags & RDKEYFRAME_PAUSE_ON_LAST_FRAME) != 0 )
    {
        rdPuppet_SetStatus(pPuppet, track, RDPUPPET_TRACK_PAUSE_ON_LAST_FRAME);
    }

    if ( (flags & RDKEYFRAME_PUPPET_CONTROLLED) != 0 )
    {
        rdPuppet_SetTrackSpeed(pPuppet, track, 0.0f);
    }

    if ( (flags & RDKEYFRAME_DISABLE_FADEIN) != 0 )
    {
        rdPuppet_PlayTrack(pPuppet, track);
    }
    else
    {
        rdPuppet_FadeInTrack(pPuppet, track, 0.07f);
    }

    pPuppet->aTracks[track].guid = (uint16_t)(track + 1) | ((sithPlayer_g_playerNum + 1) << 16);
    return track;
}

int J3DAPI sithPuppet_GetTrackNumForGUID(const SithThing* pThing, uint32_t guid)
{
    SITH_ASSERTREL(pThing);
    SITH_ASSERTREL(pThing->renderData.pPuppet);

    for ( size_t i = 0; i < RDPUPPET_MAX_TRACKS; ++i )
    {
        if ( pThing->renderData.pPuppet->aTracks[i].guid == guid )
        {
            return (int)i;
        }
    }

    return -1;
}

int J3DAPI sithPuppet_StopKey(rdPuppet* pPuppet, int track, float fadeTime)
{
    SITH_ASSERTREL(pPuppet);
    if ( track < 0 || track > RDPUPPET_MAX_TRACKS ) // Added: Check from < 0
    {
        return 0;
    }

    if ( !pPuppet->aTracks[track].pKFTrack )
    {
        return 0;
    }

    if ( fadeTime <= 0.0f )
    {
        rdPuppet_RemoveTrack(pPuppet, track);
    }
    else
    {
        rdPuppet_FadeOutTrack(pPuppet, track, fadeTime);
    }

    return 1;
}

void J3DAPI sithPuppet_SwapSubMode(SithThing* pThing, SithPuppetSubMode newMode, SithPuppetSubMode oldMode)
{
    SITH_ASSERTREL(pThing);

    bool bStopTrack = false;
    if ( pThing->renderData.pPuppet && pThing->pPuppetClass )
    {
        SITH_ASSERTREL(pThing->renderData.pPuppet);
        SithPuppetClassSubmode* pMode = &pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][newMode];
        if ( !pMode || pMode->pKeyframe != pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][oldMode].pKeyframe )
        {
            sithPuppet_StopFridgetTrack(pThing);

            SithPuppetTrack* pTrack;
            for ( pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )// TODO: Dont compare against the 0xDDDDDD address
            {
                if ( pTrack->submode == oldMode )
                {
                    bStopTrack = 1;
                    break;
                }
            }

            if ( bStopTrack )
            {
                sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.07f);
            }

            if ( pMode->pKeyframe )// TODO: should be probably if ( pMode )
            {
                sithPuppet_PlayMode(pThing, newMode, sithPuppet_DefaultCallback);
            }
        }
    }
}

void J3DAPI sithPuppet_StopForceMove(SithThing* pThing, int bStopTracks)
{
    SITH_ASSERTREL(pThing);

    pThing->thingInfo.actorInfo.bForceMovePlay = 0;

    if ( pThing->type != SITH_THING_PLAYER )
    {
        sithPhysics_ResetThingMovement(pThing);
        sithPhysics_FindFloor(pThing, 1);

        pThing->renderData.bSkipBuildingJoints = 0;
        rdVector_Copy3(&pThing->orient.dvec, &pThing->pos);
        rdPuppet_BuildJointMatrices(&pThing->renderData, &pThing->orient);
        pThing->orient.dvec = rdroid_g_zeroVector3;

        pThing->moveStatus = SITHPLAYERMOVE_STILL;
        return;
    }

    // Thing is player

    if ( bStopTracks )
    {
        bool bStopTrack = false;
        SithPuppetTrack* pTrack;
        for ( pTrack = pThing->pPuppetState->pFirstTrack; pTrack && pTrack != STDMEMORY_FREEDPTR; pTrack = pTrack->pNextTrack )// TODO: Dont compare against the 0xDDDDDD address
        {
            if ( pTrack->pSubmode && (pTrack->pSubmode->flags & RDKEYFRAME_FORCEMOVE) != 0 )
            {
                bStopTrack = true;
                break;
            }
        }

        if ( bStopTrack )
        {
            sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.0f);
        }
    }

    pThing->renderData.bSkipBuildingJoints = 0;
    rdVector_Copy3(&pThing->orient.dvec, &pThing->pos);
    rdPuppet_BuildJointMatrices(&pThing->renderData, &pThing->orient);
    pThing->orient.dvec = rdroid_g_zeroVector3;

    switch ( pThing->moveStatus )
    {
        case SITHPLAYERMOVE_CRAWL_STILL:
            return;

        case SITHPLAYERMOVE_HANGING:
        {
            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_HANGLEDGE, NULL);
            sithPhysics_ResetThingMovement(pThing);
            pThing->collide.movesize = 0.04f;
            break;
        }
        case SITHPLAYERMOVE_CLIMBIDLE:
        case SITHPLAYERMOVE_CLIMBING_UP:
        case SITHPLAYERMOVE_CLIMBING_DOWN:
        case SITHPLAYERMOVE_CLIMBING_LEFT:
        case SITHPLAYERMOVE_CLIMBING_RIGHT:
        {
            pThing->moveStatus = SITHPLAYERMOVE_CLIMBIDLE;
            pThing->collide.movesize = 0.04f;
            if ( pThing->attach.attachedToStructure.pThingAttached )
            {
                sithPlayerActions_MoveToClimbSector(pThing, pThing->attach.attachedToStructure.pSurfaceAttached);
            }

            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_CLIMBWALLIDLE, NULL);
            break;
        }
        case SITHPLAYERMOVE_WHIPSWINGING:
        {
            if ( (pThing->flags & SITH_TF_DESTROYED) == 0 && (pThing->flags & SITH_TF_DYING) == 0 )
            {
                pThing->moveStatus = SITHPLAYERMOVE_STILL;
            }

            sithPhysics_ResetThingMovement(pThing);
            sithPhysics_FindFloor(pThing, 1);
            break;
        }
        case SITHPLAYERMOVE_WHIPCLIMBIDLE:
        {
            sithWhip_FinishWhipClimbDismount(pThing);
            break;
        }
        case SITHPLAYERMOVE_SWIMIDLE:
        {
            sithPhysics_ResetThingMovement(pThing);
            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_RISING, NULL);
            for ( size_t i = 0; i < 8; ++i ) // TODO: make constant
            {
                sithFX_CreateBubble(pThing);
            }
            break;
        }
        case SITHPLAYERMOVE_JUMPUP:
        {
            pThing->collide.movesize = 0.04f;
            sithPhysics_ResetThingMovement(pThing);
            if ( (pThing->flags & SITH_TF_DESTROYED) == 0 && (pThing->flags & SITH_TF_DYING) == 0 )
            {
                pThing->moveStatus = SITHPLAYERMOVE_FALLING;
            }

            int trackNum = sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_FALL, NULL);
            break;
        }
        case SITHPLAYERMOVE_PULLINGUP:
        {
            pThing->collide.movesize = 0.04f;
            pThing->collide.type = SITH_COLLIDE_SPHERE;
            sithPhysics_ResetThingMovement(pThing);

            if ( (pThing->flags & SITH_TF_DESTROYED) == 0 && (pThing->flags & SITH_TF_DYING) == 0 )
            {
                pThing->moveStatus = SITHPLAYERMOVE_STILL;
            }

            pThing->moveInfo.physics.flags &= ~SITH_PF_ONWATERSURFACE;
            sithPuppet_SetMoveMode(pThing, SITHPUPPET_MOVEMODE_NORMAL);
            sithPhysics_FindFloor(pThing, 1);
            sithInventory_SetSwimmingInventory(pThing, 1);
            break;
        }
        case SITHPLAYERMOVE_PULLINGUP_1M:
        {
            pThing->moveStatus = SITHPLAYERMOVE_STILL;
            sithPhysics_ResetThingMovement(pThing);

            pThing->collide.movesize = 0.04f;
            sithPhysics_FindFloor(pThing, 1);
            sithInventory_SetSwimmingInventory(pThing, 1);
            break;
        }
        case SITHPLAYERMOVE_WHIP_CLIMB_START:
        {
            sithWhip_SetActorWhipClimbIdle(pThing);
            break;
        }
        case SITHPLAYERMOVE_STRAFING_LEFT:
        case SITHPLAYERMOVE_STRAFING_RIGHT:
        case SITHPLAYERMOVE_JUMPBACK:
        {
            pThing->collide.movesize = 0.04f;
            sithPhysics_FindFloor(pThing, 0);

            pThing->moveStatus = SITHPLAYERMOVE_FALLING;
            if ( pThing->attach.flags )
            {
                pThing->moveStatus = SITHPLAYERMOVE_STILL;
                sithPhysics_ResetThingMovement(pThing);
            }

            break;
        }
        case SITHPLAYERMOVE_STAND_TO_CRAWL:
        {
            pThing->moveStatus = SITHPLAYERMOVE_CRAWL_STILL;
            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_STAND, NULL);
            break;
        }
        case SITHPLAYERMOVE_CRAWL_TO_STAND:
        {
            pThing->moveInfo.physics.flags &= ~SITH_PF_ALIGNSURFACE;
            pThing->moveInfo.physics.flags |= SITH_PF_ALIGNUP;
            pThing->moveInfo.physics.height = 0.090000004f;

            sithPhysics_FindFloor(pThing, 1);
            sithPuppet_SetMoveMode(pThing, SITHPUPPET_MOVEMODE_NORMAL);
            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_STAND, NULL);
            pThing->moveStatus = SITHPLAYERMOVE_STILL;
            break;
        }
        case SITHPLAYERMOVE_CLIMB_DOWN_TO_MOUNT:
        {
            pThing->collide.movesize = 0.04f;
            sithPhysics_ResetThingMovement(pThing);
            sithPlayerActions_ClimbDownToIdle(pThing);
            break;
        }
        case SITHPLAYERMOVE_CLIMB_TO_HANG:
        {
            sithPhysics_ResetThingMovement(pThing);

            pThing->collide.movesize = 0.01f;
            sithPhysics_ResetThingMovement(pThing);

            bool bSomeBool = false;

            rdVector3 moveNorm;
            rdVector_Neg3(&moveNorm, &rdroid_g_zVector3);

            sithCollision_SearchForCollisions(pThing->pInSector, pThing, &pThing->pos, &moveNorm, 0.07f, pThing->collide.movesize, 0xA00);
            while ( 1 )
            {
                SithCollision* pCollision = sithCollision_PopStack();
                if ( !pCollision )
                {
                    break;
                }
                if ( (pCollision->type & SITHCOLLISION_WORLD) != 0 )
                {
                    if ( (pCollision->pSurfaceCollided->flags & SITH_SURFACE_LAVA) == 0 )
                    {
                        bSomeBool = true;
                        break;
                    }
                }
                else if ( (pCollision->type & SITHCOLLISION_ADJOINTOUCH) != 0 )
                {
                    if ( (pCollision->pSurfaceCollided->pAdjoin->flags & SITH_ADJOIN_NOPLAYERMOVE) != 0
                        && (pCollision->pSurfaceCollided->flags & SITH_SURFACE_LAVA) == 0 )
                    {
                        bSomeBool = true;
                        break;
                    }
                }
                else if ( (pCollision->type & SITHCOLLISION_THING) != 0 && (pCollision->pThingCollided->flags & SITH_TF_STANDON) != 0 )
                {
                    bSomeBool = true;
                    break;
                }
            }

            sithCollision_DecreaseStackLevel();

            SithSurface* pHitSurf  = NULL;
            rdModel3Mesh* pHitMesh = NULL;
            SithThing* pHitThing   = NULL;
            rdFace* pHitFace       = NULL;

            pThing->collide.movesize = 0.04f; // restore default move size

            float distance = sithPlayerActions_SearchForCollision(pThing, &pThing->orient.lvec, &pHitSurf, &pHitFace, &pHitMesh, &pHitThing);
            if ( distance < 0.0f )
            {
                pThing->moveStatus = SITHPLAYERMOVE_FALLING;
                sithInventory_SetSwimmingInventory(pThing, 1);
            }
            else
            {
                sithPlayerActions_ActorGrabLedge(pThing, distance, pHitSurf, pHitFace, pHitMesh, pHitThing);
            }

            break;
        }
        default:
        {
            pThing->moveStatus = SITHPLAYERMOVE_STILL;
            pThing->collide.movesize = 0.04f;
            sithPhysics_ResetThingMovement(pThing);

            sithPlayerControls_g_bCutsceneMode = 0;
            if ( !pThing->attach.flags )
            {
                sithPhysics_FindFloor(pThing, 1);
            }

            break;
        }
    }
}

void J3DAPI sithPuppet_DefaultCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    switch ( markerType )
    {
        case (rdKeyMarkerType)0: // Finish playing
        {
            if ( pThing->thingInfo.actorInfo.bForceMovePlay == 1 )
            {
                for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pTrack->pNextTrack )
                {
                    if ( pTrack->trackNum == track )
                    {
                        if ( (pTrack->pSubmode->flags & RDKEYFRAME_FORCEMOVE) != 0 )
                        {
                            sithPuppet_StopForceMove(pThing, /*bStopTracks=*/0);
                        }

                        break;
                    }
                }

                if ( pThing->controlType == SITH_CT_AI && pThing->controlInfo.aiControl.pLocal )
                {
                    sithAIMove_SetGoalReached(pThing->controlInfo.aiControl.pLocal);
                }
            }

            switch ( pThing->moveStatus )
            {
                case SITHPLAYERMOVE_JUMPFWD:
                case SITHPLAYERMOVE_JUMPBACK:
                case SITHPLAYERMOVE_LEAPFWD:
                {
                    SithPuppetTrack* pTrack = sithPuppet_GetModeTrackImpl(pThing, SITHPUPPETSUBMODE_RUN);
                    if ( !pTrack || pTrack->trackNum != track )
                    {
                        if ( pThing->moveStatus == SITHPLAYERMOVE_JUMPBACK && (pThing->thingInfo.actorInfo.flags & SITH_AF_CONTROLSDISABLED) != 0 )
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_STILL;
                            pThing->collide.movesize = 0.04f;
                        }
                        else
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_FALLING;
                            pThing->collide.movesize = 0.04f;
                            sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_FALLFORWARD, NULL);
                        }
                    }

                    break;
                }
                case SITHPLAYERMOVE_PUSHPULL_READY:
                {
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                    break;
                }
                case SITHPLAYERMOVE_JUMPROLLBACK:
                    sithCamera_RestoreExtCamera();
                    // Fall through
                case SITHPLAYERMOVE_SLIDEDOWNFORWARD:
                case SITHPLAYERMOVE_SLIDEDOWNBACK:
                {
                    if ( (pThing == sithPlayer_g_pLocalPlayerThing || (pThing->thingInfo.actorInfo.flags & SITH_AF_NOSLOPEMOVE) != 0)
                        && (pThing->moveInfo.physics.flags & (SITH_PF_UNKNOWN_8000000 | SITH_PF_JEEP | SITH_PF_RAFT | SITH_PF_MINECAR)) == 0 )
                    {
                        pThing->thingInfo.actorInfo.bControlsDisabled = 0;

                        if ( pThing->pInSector && ((pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0
                            || (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0) ) // Fixed: Corrected operator precedence in aetherium/underwater sector check to prevent potential null pointer dereference of pThing->pInSector.
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_SWIMIDLE;
                            if ( pThing->pPuppetState->moveMode != SITHPUPPET_MOVEMODE_SWIM )
                            {
                                sithPuppet_SetMoveMode(pThing, SITHPUPPET_MOVEMODE_SWIM);
                            }
                        }
                        else if ( pThing->attach.flags != 0 )
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_STILL;
                        }
                        else
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_FALLING;
                        }
                    }

                #ifdef J3D_QOL_IMPROVEMENTS
                    // Movement must not be reset if the player is falling
                    // as it will cause the falling velocity to be reset 
                    // making it possible to fall from high places without taking damage
                    if ( pThing->moveStatus != SITHPLAYERMOVE_FALLING ) {
                        sithPhysics_ResetThingMovement(pThing);
                    }
                #else
                    sithPhysics_ResetThingMovement(pThing); // Altered: Moved to after above player check
                #endif

                    break;
                }
                case SITHPLAYERMOVE_JUMPROLLFWD:
                case SITHPLAYERMOVE_JUMPLEFT:
                case SITHPLAYERMOVE_JUMPRIGHT:
                {
                    pThing->moveStatus = SITHPLAYERMOVE_STILL;
                    break;
                }
                default:
                    break;
            }

            sithPuppet_FreeTrackByIndex(pThing, track);
            break;
        }
        case RDKEYMARKER_LEFTFOOT:
        case RDKEYMARKER_RIGHTFOOT:
        case RDKEYMARKER_RUNLEFTFOOT:
        case RDKEYMARKER_RUNRIGHTFOOT:
        {
            if ( pThing->renderData.pPuppet->aTracks[track].playSpeed >= 0.5f
                && (pThing->flags & SITH_TF_DYING) == 0
                && pThing->type != SITH_THING_CORPSE
                && pThing->attach.flags
                && pThing->pSoundClass )
            {
                if ( pThing->moveStatus == SITHPLAYERMOVE_SLIDEDOWNFORWARD || pThing->moveStatus == SITHPLAYERMOVE_SLIDEDOWNBACK )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_SLIDE1);
                }
                else
                {
                    SithSoundClassMode sndmode = 0;
                    int sndModeOffset = markerType - 1;
                    if ( (unsigned int)(markerType - 1) > 1 )
                    {
                        sndModeOffset = markerType - 6;
                    }

                    if ( (pThing->attach.flags & SITH_ATTACH_THINGFACE) != 0 )
                    {
                        SithThing* pThingAttached = pThing->attach.attachedToStructure.pThingAttached;
                        if ( (pThingAttached->flags & SITH_TF_METAL) != 0 )
                        {
                            sndmode = SITHSOUNDCLASS_CREATE;
                        }
                        else if ( (pThingAttached->flags & SITH_TF_EARTH) != 0 )
                        {
                            sndmode = SITHSOUNDCLASS_STOPMOVE;
                        }
                        else if ( (pThingAttached->flags & SITH_TF_SNOW) != 0 )
                        {
                            sndmode = SITHSOUNDCLASS_MOVING;
                        }
                        else if ( (pThingAttached->flags & SITH_TF_WOOD) != 0 )
                        {
                            sndmode = SITHSOUNDCLASS_LWALKHARD;
                        }
                    }
                    else if ( (pThing->attach.flags & SITH_ATTACH_SURFACE) != 0 )
                    {
                        SithSurface* pSurfaceAttached = pThing->attach.attachedToStructure.pSurfaceAttached;
                        if ( (pSurfaceAttached->flags & (SITH_SURFACE_WOODECHO | SITH_SURFACE_ECHO | SITH_SURFACE_WOOD | SITH_SURFACE_SNOW | SITH_SURFACE_WEB | SITH_SURFACE_EARTH | SITH_SURFACE_SHALLOWWATER | SITH_SURFACE_WATER | SITH_SURFACE_METAL | SITH_SURFACE_AETHERIUM | SITH_SURFACE_EARTHECHO)) != 0 )
                        {
                            if ( (pSurfaceAttached->flags & SITH_SURFACE_METAL) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_CREATE;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_WATER) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_ACTIVATE;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_SHALLOWWATER) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_STARTMOVE;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_EARTH) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_STOPMOVE;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_SNOW) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_MOVING;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_WOOD) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_LWALKHARD;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_ECHO) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_RWALKHARD;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_WOODECHO) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_LRUNHARD;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_EARTHECHO) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_RRUNHARD;
                            }
                            else if ( (pSurfaceAttached->flags & SITH_SURFACE_AETHERIUM) != 0 )
                            {
                                sndmode = SITHSOUNDCLASS_LWALKMETAL;
                            }
                            else
                            {
                                sndmode = 0;
                            }
                        }
                    }

                    sithSoundClass_PlayModeRandom(pThing, (SithSoundClassMode)(sndModeOffset + 4 * sndmode + 6));

                    if ( sndmode == SITHSOUNDCLASS_ACTIVATE || sndmode == SITHSOUNDCLASS_STARTMOVE )
                    {
                        sithFX_CreateWaterRipple(pThing);
                    }

                    if ( pThing == sithPlayer_g_pLocalPlayerThing
                        && (markerType == RDKEYMARKER_RUNLEFTFOOT || markerType == RDKEYMARKER_RUNRIGHTFOOT)
                        && sithPuppet_g_bPlayerLeapForward == 1
                        && pThing->attach.flags )
                    {
                        if ( pThing->moveStatus == SITHPLAYERMOVE_LEAPFWD )
                        {
                            sithPuppet_g_bPlayerLeapForward = 0;
                        }
                        else
                        {
                            pThing->moveStatus = SITHPLAYERMOVE_LEAPFWD;
                            if ( markerType == RDKEYMARKER_RUNLEFTFOOT )
                            {
                                sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_LEAPLEFT, NULL);
                            }
                            else
                            {
                                sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_LEAPRIGHT, NULL);
                            }

                            sithPuppet_g_bPlayerLeapForward = 0;
                        }
                    }
                }
            }

            break;
        }
        case RDKEYMARKER_ATTACK:
        {
            if ( pThing->controlType == SITH_CT_AI && pThing->controlInfo.aiControl.pLocal )
            {
                SithInventoryType* pInvType = sithInventory_GetType(pThing->thingInfo.actorInfo.curWeaponID);
                if ( pInvType->pCog )
                {
                    sithCog_SendMessageEx(pInvType->pCog, SITHCOG_MSG_FIRE, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, -1, 0, 0, 0);
                }
                else
                {
                    SithAIControlBlock* pLocal = pThing->controlInfo.aiControl.pLocal;
                    sithAIUtil_AIFire(pLocal, pLocal->minFireDist, pLocal->maxFireDist, pLocal->fireDot, pLocal->aimError, pLocal->fireWeaponNum, pLocal->fireFlags, 1);
                }
            }
            else if ( pThing->controlType == SITH_CT_PLAYER )
            {
                SithInventoryType* pCog = sithInventory_GetType(pThing->thingInfo.actorInfo.curWeaponID);
                if ( pCog->pCog )
                {
                    sithCog_SendMessageEx(pCog->pCog, SITHCOG_MSG_FIRE, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, pThing->idx, 0, -1, 0, 0, 0);
                }
            }

            break;
        }
        case RDKEYMARKER_SWING:
        {
            pThing->unknownFlags |= 2u;
            break;
        }
        case RDKEYMARKER_SWINGFINISH:
        {
            pThing->unknownFlags &= ~2u;
            break;
        }
        case RDKEYMARKER_SWIMLEFT:
        {
            if ( pThing->renderData.pPuppet->aTracks[track].playSpeed >= 0.5f && pThing->pSoundClass )
            {
                if ( pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_LSWIMAET);
                }

                else if ( (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_LSWIMSURFACE);
                }
                else
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_LSWIMUNDER);
                }
            }

            break;
        }
        case RDKEYMARKER_TREAD:
        {
            if ( pThing->renderData.pPuppet->aTracks[track].playSpeed >= 0.5f && pThing->pSoundClass )
            {
                if ( pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_TREADAET);
                }

                else if ( (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_TREADSURFACE);
                }
                else
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_TREADUNDER);
                }
            }

            break;
        }
        case RDKEYMARKER_DIED:
        {
            if ( pThing->renderData.pPuppet->aTracks[track].playSpeed >= 0.5f && (pThing == sithPlayer_g_pLocalPlayerThing || pThing->attach.flags) )
            {
                sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_CORPSEHIT);
            }
            break;
        }
        case RDKEYMARKER_JUMP:
        {
            switch ( pThing->moveStatus )
            {
                case SITHPLAYERMOVE_JUMPFWD:
                {
                    sithPlayerActions_JumpForward(pThing);
                    break;
                }
                case SITHPLAYERMOVE_JUMPBACK:
                {
                    sithPlayerActions_HopBack(pThing);
                    break;
                }
                case SITHPLAYERMOVE_JUMPROLLBACK:
                {
                    sithPlayerActions_JumpRollBack(pThing);
                    break;
                }
                case SITHPLAYERMOVE_JUMPROLLFWD:
                {
                    sithPlayerActions_JumpRollForward(pThing);
                    break;
                }
                case SITHPLAYERMOVE_JUMPLEFT:
                {
                    sithPlayerActions_JumpLeft(pThing);
                    break;
                }
                case SITHPLAYERMOVE_JUMPRIGHT:
                {
                    sithPlayerActions_JumpRight(pThing);
                    break;
                }
                case SITHPLAYERMOVE_LEAPFWD:
                {
                    pThing->moveStatus = SITHPLAYERMOVE_LEAPFWD;
                    if ( pThing->attach.flags )
                    {
                        sithPlayerActions_LeapForward(pThing);
                    }
                    break;
                }
                default:
                {
                    if ( pThing->controlType == SITH_CT_AI )
                    {
                        pThing->controlInfo.aiControl.pLocal->mode |= SITHAI_MODE_MOVING;
                    }
                } break;
            }

            break;
        }
        case RDKEYMARKER_JUMPUP:
        {
            if ( pThing->attach.flags )
            {
                sithPlayerActions_Jump(pThing, 2.0f, 0);
                if ( pThing->controlType == SITH_CT_AI )
                {
                    pThing->controlInfo.aiControl.pLocal->mode |= SITHAI_MODE_MOVING;
                }
            }

            break;
        }
        case RDKEYMARKER_SWIMRIGHT:
        {
            if ( pThing->renderData.pPuppet->aTracks[track].playSpeed >= 0.5f && pThing->pSoundClass )
            {
                if ( pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_RSWIMAET);
                }

                else if ( (pThing->moveInfo.physics.flags & SITH_PF_ONWATERSURFACE) != 0 )
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_RSWIMSURFACE);
                }
                else
                {
                    sithSoundClass_PlayModeRandom(pThing, SITHSOUNDCLASS_RSWIMUNDER);
                }
            }

            break;
        }
        case RDKEYMARKER_ACTIVATE:
        case RDKEYMARKER_PLACERIGHTARM:
        case RDKEYMARKER_PLACERIGHTARMREST:
        case RDKEYMARKER_REACHRIGHTARM:
        case RDKEYMARKER_REACHRIGHTARMREST:
        case RDKEYMARKER_PICKUP:
        case RDKEYMARKER_DROP:
        case RDKEYMARKER_MOVE:
        case RDKEYMARKER_INVENTORYPULL:
        case RDKEYMARKER_INVENTORYPUT:
        case RDKEYMARKER_ATTACKFINISH:
        case RDKEYMARKER_TURNOFF:
        {
            if ( (pThing->moveStatus == SITHPLAYERMOVE_PUSHING || pThing->moveStatus == SITHPLAYERMOVE_PULLING) && markerType == RDKEYMARKER_MOVE )
            {
                SithSurface* pSurfaceAttached = pThing->attach.attachedToStructure.pSurfaceAttached;
                if ( pSurfaceAttached )
                {
                    int sndMode = 0; // Added: Initialize to 0
                    if ( (pSurfaceAttached->flags & (SITH_SURFACE_WOODECHO | SITH_SURFACE_ECHO | SITH_SURFACE_WOOD | SITH_SURFACE_SNOW | SITH_SURFACE_WEB | SITH_SURFACE_EARTH | SITH_SURFACE_SHALLOWWATER | SITH_SURFACE_WATER | SITH_SURFACE_METAL | SITH_SURFACE_AETHERIUM | SITH_SURFACE_EARTHECHO)) != 0 )
                    {
                        if ( (pSurfaceAttached->flags & SITH_SURFACE_METAL) != 0 )
                        {
                            sndMode = 1;
                        }
                        else if ( (pSurfaceAttached->flags & SITH_SURFACE_EARTH) != 0 )
                        {
                            sndMode = 4;
                        }
                        else if ( (pSurfaceAttached->flags & SITH_SURFACE_SNOW) != 0 )
                        {
                            sndMode = 5;
                        }
                        else if ( (pSurfaceAttached->flags & SITH_SURFACE_WOOD) != 0 )
                        {
                            sndMode = 6;
                        }
                        else
                        {
                            sndMode = 0;
                        }
                    }

                    if ( !sndMode )
                    {
                        sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_SCRAPEHARD);
                    }
                    else if ( sndMode == 1 )
                    {
                        sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_SCRAPEMETAL);
                    }
                    else
                    {
                        sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_SCRAPEEARTH);
                    }
                }
            }
            else
            {
                sithCog_ThingSendMessageEx(pThing, NULL, SITHCOG_MSG_CALLBACK, track, markerType, 0, 0);
            }

            break;
        }
        case RDKEYMARKER_CRAWL:
        {
            if ( pThing->moveStatus == SITHPLAYERMOVE_STAND_TO_CRAWL )
            {
                pThing->moveInfo.physics.height = 0.045000002f;
                pThing->moveInfo.physics.flags |= SITH_PF_ALIGNSURFACE;
                pThing->moveInfo.physics.flags &= ~SITH_PF_ALIGNUP;
                sithPlayerActions_Crawl(pThing);
            }

            break;
        }
        case RDKEYMARKER_RUNJUMPLAND:
        {
            if ( pThing->moveType == SITH_MT_PHYSICS )
            {
                if ( pThing->moveStatus == SITHPLAYERMOVE_CRAWL_STILL )
                {
                    pThing->forceMoveStartPos.z = pThing->forceMoveStartPos.z + 0.04f;
                }
                else
                {
                    rdVector3 moveNorm;
                    rdVector_Neg3(&moveNorm, &rdroid_g_zVector3);

                    if ( sithCollision_CheckDistance(pThing, &moveNorm) > 0.14f )
                    {
                        sithPuppet_StopForceMove(pThing, 1);

                        if ( pThing->moveStatus != SITHPLAYERMOVE_JUMPBACK && pThing->moveStatus != SITHPLAYERMOVE_FALLING )
                        {
                            pThing->moveInfo.physics.thrust = rdroid_g_zeroVector3;
                            pThing->moveInfo.physics.velocity.x = pThing->moveInfo.physics.velocity.x * 80.0f;
                            pThing->moveInfo.physics.velocity.y = pThing->moveInfo.physics.velocity.y * 80.0f;
                        }

                        pThing->moveStatus = SITHPLAYERMOVE_FALLING;
                        sithPuppet_PlayMode(pThing, SITHPUPPETSUBMODE_FALL, NULL);
                    }
                }
            }

            break;
        }
        case RDKEYMARKER_LEFTHAND:
        {
            sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_CLIMBHANDLEFT);
            break;
        }
        case RDKEYMARKER_RIGHTHAND:
        {
            sithSoundClass_PlayModeFirst(pThing, SITHSOUNDCLASS_CLIMBHANDRIGHT);
            break;
        }
        default:
            return;
    }
}

int J3DAPI sithPuppet_WriteStaticPuppetsListText(const SithWorld* pWorld)
{
    if ( stdConffile_WriteLine("###### Animation Classes #######\n")
        || stdConffile_WriteLine("Section: ANIMCLASS\n\n")
        || stdConffile_Printf("World puppets %d\n", pWorld->numPuppetClasses) )
    {
        return 1;
    }

    for ( size_t i = 0; i < pWorld->numPuppetClasses; ++i )
    {
        if ( stdConffile_Printf("%d:\t%s\n", i, pWorld->aPuppetClasses[i].aName) )
        {
            return 1;
        }
    }

    return stdConffile_WriteLine("end\n") || stdConffile_WriteLine("################################\n\n\n");
}

int J3DAPI sithPuppet_ReadStaticPuppetsListText(SithWorld* pWorld, int bSkip)
{
    SITH_ASSERTREL(pWorld);

    if ( bSkip )
    {
        return 1;
    }

    stdConffile_ReadArgs();
    if ( !streq(stdConffile_g_entry.aArgs[0].argValue, "world") || !streq(stdConffile_g_entry.aArgs[1].argValue, "puppets") )
    {
        return 1;
    }

    size_t numPuppets = atoi(stdConffile_g_entry.aArgs[2].argValue);
    if ( !numPuppets )
    {
        return 0;
    }

    if ( sithPuppet_AllocWorldPuppets(pWorld, numPuppets) )
    {
        return 1;
    }

    while ( stdConffile_ReadArgs() && !streq(stdConffile_g_entry.aArgs[0].argValue, "end") )
    {
        if ( !sithPuppet_LoadPuppetClass(stdConffile_g_entry.aArgs[1].argValue) )
        {
            SITHLOG_ERROR("Load failed for puppet %s.\n", stdConffile_g_entry.aArgs[1].argValue);
        }
    }

    return 0;
}

int J3DAPI sithPuppet_WriteStaticPuppetsListBinary(tFileHandle fh, const SithWorld* pWorld)
{
    for ( size_t i = 0; i < pWorld->numPuppetClasses; ++i )
    {
        static_assert(STD_ARRAYLEN(pWorld->aPuppetClasses[i].aName) == 64, "STD_ARRAYLEN(pWorld->aPuppetClasses[i].aName) == 64");
        if ( sith_g_pHS->pFileWrite(fh, &pWorld->aPuppetClasses[i].aName, STD_ARRAYLEN(pWorld->aPuppetClasses[i].aName)) != STD_ARRAYLEN(pWorld->aPuppetClasses[i].aName) )
        {
            return 1;
        }
    }

    return 0;
}

int J3DAPI sithPuppet_ReadStaticPuppetsListBinary(tFileHandle fh, SithWorld* pWorld)
{
    char (*aFilenames)[64] = NULL;
    size_t numPuppetClasses = pWorld->numPuppetClasses;
    const size_t sizeNames = numPuppetClasses * 64;

    if ( sithPuppet_AllocWorldPuppets(pWorld, numPuppetClasses)
        || (aFilenames = (char (*)[64])STDMALLOC(sizeNames)) == 0
        || sith_g_pHS->pFileRead(fh, aFilenames, sizeNames) != sizeNames )
    {
        if ( aFilenames )
        {
            stdMemory_Free(aFilenames);
        }

        return 1;
    }
    else
    {
        const char (*pName)[64] = aFilenames;
        for ( size_t i = 0; i < numPuppetClasses; ++i )
        {
            if ( !sithPuppet_LoadPuppetClass(*pName) )
            {
                if ( aFilenames )
                {
                    stdMemory_Free(aFilenames);
                }

                return 1;
            }

            ++pName;
        }

        stdMemory_Free(aFilenames);
        return 0;
    }
}

SithPuppetClass* J3DAPI sithPuppet_LoadPuppetClass(const char* pFilename)
{
    SithWorld* pWorld = sithWorld_g_pLastLoadedWorld;
    SITH_ASSERTREL(pWorld);

    SITH_ASSERTREL(pFilename);
    SithPuppetClass* pClass = sithPuppet_ClassCacheFind(pFilename);
    if ( pClass )
    {
        return pClass;
    }

    if ( pWorld->numPuppetClasses == pWorld->sizePuppetClasses )
    {
        SITHLOG_ERROR("Too many puppet classes loaded, line %d.\n", stdConffile_GetLineNumber());
        return NULL;
    }

    pClass = &pWorld->aPuppetClasses[pWorld->numPuppetClasses];
    memset(pClass, 0, sizeof(SithPuppetClass));

    STD_STRCPY(pClass->aName, pFilename);

    char aPath[128];
    STD_FORMAT(aPath, "%s%c%s", "misc\\pup", '\\', pFilename);
    if ( sithPuppet_LoadPuppetClassEntry(pClass, aPath) )
    {
        SITHLOG_ERROR("Failed to load anim class %s.\n", aPath);
        return NULL;
    }

    ++pWorld->numPuppetClasses;
    sithPuppet_ClassCacheAdd(pClass);
    return pClass;
}

int J3DAPI sithPuppet_LoadPuppetClassEntry(SithPuppetClass* pClass, const char* pPath)
{
    SITH_ASSERTREL(pPath);
    SITH_ASSERTREL(pClass);

    if ( !stdConffile_Open(pPath) )
    {
        return 1;
    }

    for ( size_t i = 0; i < STD_ARRAYLEN(pClass->aJoints); ++i )
    {
        pClass->aJoints[i] = -1;
    }

    int modeNum = 0;
    size_t animNum = -1; // Added: Init to -1
    while ( stdConffile_ReadArgs() )
    {
        if ( !stdConffile_g_entry.numArgs )
        {
            SITHLOG_ERROR("Bad line encountered line %d.\n", stdConffile_GetLineNumber());
        }
        else if ( streq(stdConffile_g_entry.aArgs[0].argName, "mode") )
        {
            modeNum = atoi(stdConffile_g_entry.aArgs[0].argValue);
            SITH_ASSERTREL((modeNum >= 0) && (modeNum < (SITH_PUPPET_NUMARMEDMODES * SITH_PUPPET_NUMMOVEMODES)));

            if ( stdConffile_g_entry.numArgs > 1u && !strcmp(stdConffile_g_entry.aArgs[1].argName, "basedon") )
            {
                int basedOn = atoi(stdConffile_g_entry.aArgs[1].argValue);
                SITH_ASSERTREL((basedOn >= 0) && (basedOn < (SITH_PUPPET_NUMARMEDMODES * SITH_PUPPET_NUMMOVEMODES)));

                memcpy(pClass->aModes[modeNum], pClass->aModes[basedOn], sizeof(pClass->aModes[modeNum]));
            }
        }
        else if ( streq(stdConffile_g_entry.aArgs[0].argValue, "joints") )
        {
            while ( stdConffile_ReadArgs() && stdConffile_g_entry.numArgs && !streq(stdConffile_g_entry.aArgs[0].argName, "end") )
            {
                size_t jointNum = atoi(stdConffile_g_entry.aArgs[0].argName);
                int jointId     = atoi(stdConffile_g_entry.aArgs[0].argValue);
                if ( jointNum >= STD_ARRAYLEN(pClass->aJoints) )
                {
                    SITHLOG_ERROR("Joint id %d out of range, line %d, file %s.\n", jointNum, stdConffile_GetLineNumber(), stdConffile_GetFilename());
                }
                else
                {
                    pClass->aJoints[jointNum] = jointId;
                }
            }
        }
        else if ( stdConffile_g_entry.numArgs <= 1u
            || (animNum = (size_t)stdHashtbl_Find(sithPuppet_pHashtblSubmodes, stdConffile_g_entry.aArgs[0].argValue)) == 0 )
        {
            SITHLOG_ERROR("File %s, unrecognized command %s on line %d.\n", pPath, stdConffile_g_entry.aArgs[0].argValue, stdConffile_GetLineNumber());
        }
        else
        {
            SITH_ASSERTREL(animNum < SITH_PUPPET_NUMSUBMODES);

            rdKeyframeFlags flags = 0;
            if ( stdConffile_g_entry.numArgs > 2u )
            {
                sscanf_s(stdConffile_g_entry.aArgs[2].argValue, "%x", &flags);
            }

            int lo = 0;
            if ( stdConffile_g_entry.numArgs > 3u )
            {
                lo = atoi(stdConffile_g_entry.aArgs[3].argValue);
            }

            int hi = lo;
            if ( stdConffile_g_entry.numArgs > 4u )
            {
                hi = atoi(stdConffile_g_entry.aArgs[4].argValue);
            }

            rdKeyframe* pKeyframe = NULL;
            if ( !streq(stdConffile_g_entry.aArgs[1].argValue, "none") )
            {
                pKeyframe = sithPuppet_LoadKeyframe(stdConffile_g_entry.aArgs[1].argValue);
            }

            pClass->aModes[modeNum][animNum].pKeyframe    = pKeyframe;
            pClass->aModes[modeNum][animNum].flags        = flags;
            pClass->aModes[modeNum][animNum].lowPriority  = lo;
            pClass->aModes[modeNum][animNum].highPriority = hi;
        }
    }

    stdConffile_Close();
    return 0;
}

int J3DAPI sithPuppet_AllocWorldPuppets(SithWorld* pWorld, size_t size)
{
    SITH_ASSERTREL(pWorld != NULL);
    if ( size && (pWorld->aPuppetClasses = (SithPuppetClass*)STDMALLOC(sizeof(SithPuppetClass) * size)) == NULL )
    {
        SITHLOG_ERROR("No memory to allocate %d anim classes.\n", size);
        return 1;
    }

    pWorld->sizePuppetClasses = size;
    pWorld->numPuppetClasses  = 0;
    memset(pWorld->aPuppetClasses, 0, sizeof(SithPuppetClass) * pWorld->sizePuppetClasses);
    return 0;
}

void J3DAPI sithPuppet_FreeWorldPuppets(SithWorld* pWorld)
{
    SITH_ASSERTREL(pWorld != NULL);
    if ( !pWorld->sizePuppetClasses )
    {
        SITH_ASSERTREL(pWorld->aPuppetClasses == NULL);
        return;
    }

    SITH_ASSERTREL(pWorld->aPuppetClasses != NULL);
    for ( size_t i = 0; i < pWorld->numPuppetClasses; ++i )
    {
        sithPuppet_ClassCacheRemove(&pWorld->aPuppetClasses[i]);
    }

    stdMemory_Free(pWorld->aPuppetClasses);
    pWorld->aPuppetClasses    = NULL;
    pWorld->numPuppetClasses  = 0;
    pWorld->sizePuppetClasses = 0;
}

int J3DAPI sithPuppet_WriteStaticKeyframesListText(const SithWorld* pWorld)
{
    if ( stdConffile_WriteLine("##### Keyframe information #####\n")
        || stdConffile_WriteLine("Section: KEYFRAMES\n\n")
        || stdConffile_Printf("World keyframes %d\n", pWorld->numKeyframes + 32) ) // 32 - extra buffer
    {
        return 1;
    }

    for ( size_t i = 0; i < pWorld->numKeyframes; ++i )
    {
        if ( stdConffile_Printf("%d:\t%s\n", i, pWorld->aKeyframes[i].aName) )
        {
            return 1;
        }
    }

    return stdConffile_WriteLine("end\n") || stdConffile_WriteLine("################################\n\n\n");
}

int J3DAPI sithPuppet_ReadStaticKeyframesListText(SithWorld* pWorld, int bSkip)
{
    if ( bSkip )
    {
        return 1;
    }

    SITH_ASSERTREL(pWorld != NULL);
    SITH_ASSERTREL(pWorld->aKeyframes == NULL);
    SITH_ASSERTREL(pWorld->numKeyframes == 0);
    SITH_ASSERTREL(pWorld->sizeKeyframes == 0);

    stdConffile_ReadArgs();

    if ( !streq(stdConffile_g_entry.aArgs[0].argValue, "world") || !streq(stdConffile_g_entry.aArgs[1].argValue, "keyframes") )
    {
        SITHLOG_ERROR("Parse error reading keyframe list line %d.\n", stdConffile_GetLineNumber());
        return 1;
    }

    size_t numKeyframes = atoi(stdConffile_g_entry.aArgs[2].argValue);
    if ( !numKeyframes )
    {
        SITHLOG_STATUS("Keyframes section not needed if numKeyframes == 0.\n");
        return 0;
    }

    if ( sithPuppet_AllocWorldKeyframes(pWorld, numKeyframes) )
    {
        SITHLOG_ERROR("Memory error while reading keyframes, line %d.\n", stdConffile_GetLineNumber());
        return 1;
    }

    float progress = 80.0f;
    const float progressDelta = 15.0f / (float)numKeyframes;
    while ( stdConffile_ReadArgs() && !streq(stdConffile_g_entry.aArgs[0].argValue, "end") )
    {
        if ( !sithPuppet_LoadKeyframe(stdConffile_g_entry.aArgs[1].argValue) )
        {
            SITHLOG_ERROR("Parse error while reading keyframes, line %d.\n", stdConffile_GetLineNumber());
            return 1;
        }

        progress += progressDelta;
        if ( progress >= 95.0f )
        {
            progress = 95.0f;
        }

        sithWorld_UpdateLoadProgress(progress);
    }

    SITHLOG_STATUS("Keyframes read.  Keyframe array space %d, used %d.\n", pWorld->sizeKeyframes, pWorld->numKeyframes);
    SITH_ASSERTREL(pWorld->numKeyframes <= pWorld->sizeKeyframes);
    return 0;
}

int J3DAPI sithPuppet_WriteStaticKeyframesListBinary(tFileHandle fh, const SithWorld* pWorld)
{
    int bError = 1;
    CndKeyframeMarker* aMarkers   = NULL;
    CndKeyframeNode* aNodes       = NULL;
    rdKeyframeNodeEntry* aEntries = NULL;

    size_t sizeInfos = sizeof(CndKeyframeInfo) * pWorld->numKeyframes;
    CndKeyframeInfo* aKeyInfos = (CndKeyframeInfo*)STDMALLOC(sizeInfos);
    if ( aKeyInfos )
    {
        memset(aKeyInfos, 0, sizeInfos);

        uint32_t aSizes[3] = { 0 }; // Note, must be 32 bit

        // Pre-calculate all sizes
        for ( size_t i = 0; i < pWorld->numKeyframes; ++i )
        {
            aSizes[0] += pWorld->aKeyframes[i].numMarkers;
            for ( size_t j = 0; j < pWorld->aKeyframes[i].numJoints; ++j )
            {
                if ( pWorld->aKeyframes[i].aNodes[j].numEntries )
                {
                    ++aSizes[1];
                }

                aSizes[2] += pWorld->aKeyframes[i].aNodes[j].numEntries;
            }
        }

        size_t sizeMarkers = sizeof(CndKeyframeMarker) * aSizes[0];
        aMarkers = (CndKeyframeMarker*)STDMALLOC(sizeof(CndKeyframeMarker) * aSizes[0]);
        if ( aMarkers )
        {
            memset(aMarkers, 0, sizeMarkers);

            size_t sizeNodes = sizeof(CndKeyframeNode) * aSizes[1];
            aNodes = (CndKeyframeNode*)STDMALLOC(sizeof(CndKeyframeNode) * aSizes[1]);
            if ( aNodes )
            {
                memset(aNodes, 0, sizeNodes);

                size_t sizeEntries = sizeof(rdKeyframeNodeEntry) * aSizes[2];
                aEntries = (rdKeyframeNodeEntry*)STDMALLOC(sizeof(rdKeyframeNodeEntry) * aSizes[2]);
                if ( aEntries )
                {
                    memset(aEntries, 0, sizeEntries);

                    CndKeyframeInfo* pCurInfo      = aKeyInfos;
                    CndKeyframeMarker* pCurMarker  = aMarkers;
                    CndKeyframeNode* pCurNode      = aNodes;
                    rdKeyframeNodeEntry* pCurEntry = aEntries;

                    for ( size_t i = 0; i < pWorld->numKeyframes; ++i )
                    {
                        rdKeyframe* pKey = &pWorld->aKeyframes[i];

                        STD_STRCPY(pCurInfo->name, pKey->aName);
                        pCurInfo->flags      = pKey->flags;
                        pCurInfo->type       = pKey->type;
                        pCurInfo->numFrames  = pKey->numFrames;
                        pCurInfo->fps        = pKey->fps;
                        pCurInfo->numMarkers = pKey->numMarkers;
                        pCurInfo->numJoints  = pKey->numJoints;
                        pCurInfo->numNodes   = 0;

                        for ( size_t j = 0; j < pKey->numJoints; ++j )
                        {
                            if ( pKey->aNodes[j].numEntries )
                            {
                                ++pCurInfo->numNodes;
                                pCurNode->nodeNum = j;
                                pCurNode->numEntries = pKey->aNodes[j].numEntries;

                                STD_STRCPY(pCurNode->meshName, pKey->aNodes[j].aMeshName);
                                memcpy(pCurEntry, pKey->aNodes[j].aEntries, sizeof(rdKeyframeNodeEntry) * pCurNode->numEntries);

                                pCurEntry += pCurNode->numEntries;
                                ++pCurNode;
                            }
                        }

                        for ( size_t j = 0; j < pKey->numMarkers; ++j )
                        {
                            pCurMarker->frame = pKey->aMarkerFrames[j];
                            pCurMarker->type  = pKey->aMarkerTypes[j];
                            ++pCurMarker;
                        }

                        ++pCurInfo;
                    }

                    bError = 0; // TODO: this should probably be but in the most inner if scope
                    if ( sith_g_pHS->pFileWrite(fh, aSizes, sizeof(aSizes)) == sizeof(aSizes) && sith_g_pHS->pFileWrite(fh, aKeyInfos, sizeInfos) == sizeInfos )
                    {
                        size_t nWritten = sith_g_pHS->pFileWrite(fh, aMarkers, sizeMarkers);
                        if ( nWritten == sizeMarkers )
                        {
                            nWritten = sith_g_pHS->pFileWrite(fh, aNodes, sizeNodes);
                            if ( nWritten == sizeNodes )
                            {
                                sith_g_pHS->pFileWrite(fh, aEntries, sizeEntries);
                            }
                        }
                    }
                }
            }
        }
    }

    if ( aKeyInfos )
    {
        stdMemory_Free(aKeyInfos);
    }

    if ( aMarkers )
    {
        stdMemory_Free(aMarkers);
    }

    if ( aNodes )
    {
        stdMemory_Free(aNodes);
    }

    if ( aEntries )
    {
        stdMemory_Free(aEntries);
    }

    return bError;
}

int J3DAPI sithPuppet_ReadStaticKeyframesListBinary(tFileHandle fh, SithWorld* pWorld)
{
    int bError = 1;
    CndKeyframeInfo* aInfos       = NULL;
    CndKeyframeMarker* aMarkers   = NULL;
    CndKeyframeNode* aNodes       = NULL;
    rdKeyframeNodeEntry* aEntries = NULL;

    size_t numKeyframes = pWorld->numKeyframes;
    if ( !sithPuppet_AllocWorldKeyframes(pWorld, numKeyframes) )
    {
        size_t sizeInfos = sizeof(CndKeyframeInfo) * numKeyframes;
        aInfos = (CndKeyframeInfo*)STDMALLOC(sizeof(CndKeyframeInfo) * numKeyframes);
        if ( aInfos )
        {
            memset(aInfos, 0, sizeInfos);

            uint32_t aSizes[3]; // Note must be 32 bit int
            static_assert(sizeof(aSizes) == 12, "sizeof(aSizes) == 12");
            if ( sith_g_pHS->pFileRead(fh, aSizes, sizeof(aSizes)) == sizeof(aSizes) )
            {
                size_t sizeMarkers = sizeof(CndKeyframeMarker) * aSizes[0];
                aMarkers = (CndKeyframeMarker*)STDMALLOC(sizeof(CndKeyframeMarker) * aSizes[0]);
                if ( aMarkers )
                {
                    memset(aMarkers, 0, sizeMarkers);

                    size_t sizeNodes = sizeof(CndKeyframeNode) * aSizes[1];
                    aNodes = (CndKeyframeNode*)STDMALLOC(sizeof(CndKeyframeNode) * aSizes[1]);
                    if ( aNodes )
                    {
                        memset(aNodes, 0, sizeNodes);

                        size_t sizeEntries = sizeof(rdKeyframeNodeEntry) * aSizes[2];
                        aEntries = (rdKeyframeNodeEntry*)STDMALLOC(sizeof(rdKeyframeNodeEntry) * aSizes[2]);
                        if ( aEntries )
                        {
                            memset(aEntries, 0, sizeEntries);

                            // Read all keyframes data and assign to world keyframes
                            if ( sith_g_pHS->pFileRead(fh, aInfos, sizeInfos) == sizeInfos
                                && sith_g_pHS->pFileRead(fh, aMarkers, sizeMarkers) == sizeMarkers
                                && sith_g_pHS->pFileRead(fh, aNodes, sizeNodes) == sizeNodes
                                && sith_g_pHS->pFileRead(fh, aEntries, sizeEntries) == sizeEntries )
                            {
                                CndKeyframeInfo* pCurInfo      = aInfos;
                                CndKeyframeMarker* pCurMarker  = aMarkers;
                                CndKeyframeNode* pCurNode      = aNodes;
                                rdKeyframeNodeEntry* pCurEntry = aEntries;

                                for ( size_t i = 0; i < numKeyframes; ++i )
                                {
                                    if ( sithPuppet_KeyCacheFind(pCurInfo->name) )
                                    {
                                        pCurMarker += pCurInfo->numMarkers;
                                        for ( size_t j = 0; j < pCurInfo->numNodes; ++j )
                                        {
                                            pCurEntry += pCurNode->numEntries;
                                            ++pCurNode;
                                        }

                                        ++pCurInfo;
                                    }
                                    else
                                    {
                                        rdKeyframe* pKeyframe = &pWorld->aKeyframes[pWorld->numKeyframes];

                                        STD_STRCPY(pKeyframe->aName, pCurInfo->name);
                                        pKeyframe->flags      = pCurInfo->flags;
                                        pKeyframe->type       = pCurInfo->type;
                                        pKeyframe->numFrames  = pCurInfo->numFrames;
                                        pKeyframe->fps        = pCurInfo->fps;
                                        pKeyframe->numMarkers = pCurInfo->numMarkers;
                                        pKeyframe->numJoints  = pCurInfo->numJoints;

                                        for ( size_t j = 0; j < pCurInfo->numMarkers; ++j )
                                        {
                                            pKeyframe->aMarkerFrames[j] = pCurMarker->frame;
                                            pKeyframe->aMarkerTypes[j] = pCurMarker->type;
                                            ++pCurMarker;
                                        }

                                        pKeyframe->idx = pWorld->numKeyframes;
                                        if ( (pWorld->state & SITH_WORLD_STATE_STATIC) != 0 )
                                        {
                                            pKeyframe->idx = SITHWORLD_STATICINDEX(pKeyframe->idx);
                                        }

                                        size_t aKeyNodes = sizeof(rdKeyframeNode) * pCurInfo->numJoints;
                                        pKeyframe->aNodes = (rdKeyframeNode*)STDMALLOC(aKeyNodes);
                                        if ( !pKeyframe->aNodes )
                                        {
                                            goto error;
                                        }

                                        memset(pKeyframe->aNodes, 0, aKeyNodes);

                                        for ( size_t j = 0; j < pCurInfo->numNodes; ++j )
                                        {

                                            rdKeyframeNode* pNode = &pKeyframe->aNodes[pCurNode->nodeNum];
                                            pNode->nodeNum    = pCurNode->nodeNum;
                                            pNode->numEntries = pCurNode->numEntries;
                                            STD_STRCPY(pNode->aMeshName, pCurNode->meshName);

                                            rdKeyframeNodeEntry* aKeyEntries = (rdKeyframeNodeEntry*)STDMALLOC(sizeof(rdKeyframeNodeEntry) * pNode->numEntries);
                                            pNode->aEntries = aKeyEntries;
                                            if ( !pNode->aEntries )
                                            {
                                                goto error;
                                            }

                                            memcpy(pNode->aEntries, pCurEntry, sizeof(rdKeyframeNodeEntry) * pNode->numEntries);
                                            pCurEntry += pCurNode->numEntries;
                                            ++pCurNode;
                                        }

                                        sithPuppet_KeyCacheAdd(pKeyframe);
                                        ++pCurInfo;
                                        ++pWorld->numKeyframes;
                                    }
                                }

                                bError = 0;
                            }
                        }
                    }
                }
            }
        }
    }

error:
    if ( aInfos )
    {
        stdMemory_Free(aInfos);
    }

    if ( aMarkers )
    {
        stdMemory_Free(aMarkers);
    }

    if ( aNodes )
    {
        stdMemory_Free(aNodes);
    }

    if ( aEntries )
    {
        stdMemory_Free(aEntries);
    }

    return bError;
}

rdKeyframe* J3DAPI sithPuppet_GetKeyframeByIndex(int index)
{
    SithWorld* pWorld = sithWorld_g_pCurrentWorld;
    if ( SITHWORLD_IS_STATICINDEX(index) )
    {
        pWorld = sithWorld_g_pStaticWorld;
        index = SITHWORLD_FROM_STATICINDEX(index);
    }

    if ( index >= 0 && index < (signed int)pWorld->numKeyframes )
    {
        return &pWorld->aKeyframes[index];
    }

    return NULL;
}

rdKeyframe* J3DAPI sithPuppet_LoadKeyframe(const char* pName)
{
    SithWorld* pWorld = sithWorld_g_pLastLoadedWorld;
    SITH_ASSERTREL(pWorld != NULL);

    SITH_ASSERTREL(pName != NULL);
    SITH_ASSERTREL(strlen(pName) < 128);

    if ( !pWorld->aKeyframes )
    {
        SITHLOG_ERROR("No space to load keyframe '%s'.\n", pName);
        return NULL;
    }

    char aPath[128];
    STD_FORMAT(aPath, "%s%c%s", "3do\\key", '\\', pName);
    rdKeyframe* pKey = sithPuppet_KeyCacheFind(pName);
    if ( pKey )
    {
        return pKey;
    }

    SITH_ASSERTREL(pWorld->numKeyframes <= pWorld->sizeKeyframes);
    if ( pWorld->numKeyframes >= pWorld->sizeKeyframes )
    {
        SITHLOG_ERROR("No space to load new keyframe '%s'.\n", pName);
        return NULL;
    }

    pKey = &pWorld->aKeyframes[pWorld->numKeyframes];
    if ( !rdKeyframe_LoadEntry(aPath, pKey) )
    {
        SITHLOG_ERROR("Failed to load keyframe '%s'.\n", aPath);
        return NULL;
    }

    pKey->idx = pWorld->numKeyframes;
    if ( (pWorld->state & SITH_WORLD_STATE_STATIC) != 0 )
    {
        pKey->idx = SITHWORLD_STATICINDEX(pKey->idx);
    }

    sithPuppet_KeyCacheAdd(pKey);
    ++pWorld->numKeyframes;
    return pKey;
}

int J3DAPI sithPuppet_AllocWorldKeyframes(SithWorld* pWorld, size_t size)
{
    SITH_ASSERTREL(pWorld != NULL);

    pWorld->aKeyframes = (rdKeyframe*)STDMALLOC(sizeof(rdKeyframe) * size);
    if ( !pWorld->aKeyframes )
    {
        SITHLOG_ERROR("No memory to allocate %d keyframe buffers.\n", size);
        return 1;
    }

    pWorld->sizeKeyframes = size;
    pWorld->numKeyframes  = 0;
    memset(pWorld->aKeyframes, 0, sizeof(rdKeyframe) * pWorld->sizeKeyframes);
    return 0;
}

void J3DAPI sithPuppet_FreeWorldKeyframes(SithWorld* pWorld)
{
    SITH_ASSERTREL(pWorld != NULL);
    if ( !pWorld->sizeKeyframes )
    {
        SITH_ASSERTREL(pWorld->aKeyframes == NULL);
        return;
    }

    SITH_ASSERTREL(pWorld->aKeyframes != NULL);
    for ( size_t i = 0; i < pWorld->numKeyframes; ++i )
    {
        sithPuppet_KeyCacheRemove(&pWorld->aKeyframes[i]);
        rdKeyframe_FreeEntry(&pWorld->aKeyframes[i]);
    }

    stdMemory_Free(pWorld->aKeyframes);
    pWorld->aKeyframes    = NULL;
    pWorld->numKeyframes  = 0;
    pWorld->sizeKeyframes = 0;
}

SithPuppetClass* J3DAPI sithPuppet_ClassCacheFind(const char* pName)
{
    SITH_ASSERTREL(pName != NULL);
    SITH_ASSERTREL(sithPuppet_pClassHashtable != NULL);
    return (SithPuppetClass*)stdHashtbl_Find(sithPuppet_pClassHashtable, pName);
}

int J3DAPI sithPuppet_ClassCacheAdd(const SithPuppetClass* pClass)
{
    SITH_ASSERTREL(pClass != NULL);
    SITH_ASSERTREL(strlen(pClass->aName) > 0);
    SITH_ASSERTREL(sithPuppet_pClassHashtable != NULL);
    return stdHashtbl_Add(sithPuppet_pClassHashtable, pClass->aName, (void*)pClass);
}

int J3DAPI sithPuppet_ClassCacheRemove(const SithPuppetClass* pClass)
{
    SITH_ASSERTREL(pClass != NULL);
    SITH_ASSERTREL(strlen(pClass->aName) > 0);
    SITH_ASSERTREL(sithPuppet_pClassHashtable != NULL);
    return stdHashtbl_Remove(sithPuppet_pClassHashtable, pClass->aName);
}

rdKeyframe* J3DAPI sithPuppet_GetKeyframe(const char* pName)
{
    return sithPuppet_KeyCacheFind(pName);
}

rdKeyframe* J3DAPI sithPuppet_KeyCacheFind(const char* pName)
{
    SITH_ASSERTREL(pName != NULL);
    SITH_ASSERTREL(sithPuppet_pKeyHashtable != NULL);
    return (rdKeyframe*)stdHashtbl_Find(sithPuppet_pKeyHashtable, pName);
}

void J3DAPI sithPuppet_KeyCacheAdd(rdKeyframe* pKeyframe)
{
    SITH_ASSERTREL(pKeyframe != NULL);
    SITH_ASSERTREL(strlen(pKeyframe->aName) > 0);
    SITH_ASSERTREL(sithPuppet_pKeyHashtable != NULL);
    stdHashtbl_Add(sithPuppet_pKeyHashtable, pKeyframe->aName, pKeyframe);
}

void J3DAPI sithPuppet_KeyCacheRemove(rdKeyframe* pKeyframe)
{
    SITH_ASSERTREL(pKeyframe != NULL);
    SITH_ASSERTREL(strlen(pKeyframe->aName) > 0);
    SITH_ASSERTREL(sithPuppet_pKeyHashtable != NULL);
    stdHashtbl_Remove(sithPuppet_pKeyHashtable, pKeyframe->aName);
}

float J3DAPI sithPuppet_GetThingLocalVelocityAxis(SithThing* pThing, size_t* pAxis, float* pVelX, float* pVelY, float* pVelZ)
{
    SITH_ASSERTREL(pAxis);
    SITH_ASSERTREL(pThing);

    if ( !pThing->pInSector )
    {
        *pVelX = 0.0f;
        *pVelY = 0.0f;
        *pVelZ = 0.0f;
        return 0.0f;
    }

    SithPhysicsInfo* pPhysics = (SithPhysicsInfo*)&pThing->moveInfo; // Changed: Moved here from the top of the function
    if ( pPhysics->velocity.x == 0.0f && pPhysics->velocity.y == 0.0f && pPhysics->velocity.z == 0.0f )
    {
        *pVelX = 0.0f;
        *pVelY = 0.0f;
        *pVelZ = 0.0f;
        *pAxis = 99;
        return 0.0f;
    }

    // Transform velocity to local velocity of thing object
    rdVector3 velocity;
    rdMatrix_TransformVectorOrtho34(&velocity, &pPhysics->velocity, &pThing->orient);

    if ( !pThing->attach.flags
        && (pPhysics->flags & SITH_PF_FLY) == 0
        && (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) == 0
        && (pThing->pInSector->flags & SITH_SECTOR_AETHERIUM) == 0 )
    {
        // Falling
        *pAxis = 2;  // Up
        *pVelX = velocity.x;
        *pVelY = velocity.y;
        *pVelZ = pPhysics->velocity.z;
        return pPhysics->velocity.z;
    }
    else
    {
        // Attached to floor or flying or swimming

        float y = fabsf(velocity.y);
        float x = fabsf(velocity.x);
        if ( y <= (double)x )
        {
            *pAxis = 0; // Left
            *pVelX = velocity.x;
            *pVelY = velocity.y;
            *pVelZ = pPhysics->velocity.z;
            return velocity.x;
        }
        else
        {
            *pAxis = 1; // Forward
            *pVelX = velocity.x;
            *pVelY = velocity.y;
            *pVelZ = pPhysics->velocity.z;
            return velocity.y;
        }
    }
}

int J3DAPI sithPuppet_StopMode(SithThing* pThing, SithPuppetSubMode submode, float fadeOutTime)
{
    SITH_ASSERTREL(pThing && pThing->pPuppetState && pThing->renderData.pPuppet);

    if ( !pThing->pPuppetClass || (size_t)submode >= SITH_PUPPET_NUMSUBMODES ) // Fixed: cast submode to unsigned to catch negative OOB
    {
        return 1;
    }

    rdKeyframe* pKeyframe = pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][submode].pKeyframe;
    if ( !pKeyframe )
    {
        return 1;
    }

    for ( size_t track = 0; track < RDPUPPET_MAX_TRACKS; ++track )
    {
        if ( pThing->renderData.pPuppet->aTracks[track].pKFTrack == pKeyframe )
        {
            sithPuppet_StopKey(pThing->renderData.pPuppet, track, fadeOutTime);
        }
    }

    return 0;
}

int J3DAPI sithPuppet_SynchMode(SithThing* pThing, SithPuppetSubMode oldMode, SithPuppetSubMode newMode, float a4, int bReverse)
{
    J3D_UNUSED(a4);
    SITH_ASSERTREL(pThing);

    if ( oldMode < SITHPUPPETSUBMODE_STAND || oldMode > SITHPUPPETSUBMODE_FALLFORWARD )
    {
        SITHLOG_ERROR("SynchMode(): Old mode (%d) out of range.\n", oldMode);
        return -1;
    }

    if ( newMode < SITHPUPPETSUBMODE_STAND || newMode > SITHPUPPETSUBMODE_FALLFORWARD )
    {
        SITHLOG_ERROR("SynchMode(): New mode (%d) out of range.\n", newMode);
        return -1;
    }

    if ( !pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][oldMode].pKeyframe
        || !pThing->pPuppetClass->aModes[pThing->pPuppetState->majorMode][newMode].pKeyframe )
    {
        SITHLOG_ERROR("SynchMode(): THING '%s' doesn't possess mode '%s' or '%s'.\n", pThing->aName, sithPuppet_aStrSubModes[oldMode], sithPuppet_aStrSubModes[newMode]);
        return -1;
    }

    SithPuppetTrack* pTrack = sithPuppet_GetModeTrackImpl(pThing, oldMode);
    if ( !pTrack )
    {
        SITHLOG_ERROR("SynchMode(): Old Mode '%s' not playing for THING '%s'.\n", sithPuppet_aStrSubModes[oldMode], pThing->aName);
        return -1;
    }

    int trackNum = pTrack->trackNum;
    int newTrackNum = sithPuppet_PlayMode(pThing, newMode, 0);
    if ( newTrackNum == -1 )
    {
        SITHLOG_ERROR("SynchMode(): Failed to play new mode '%s' for THING '%s'.\n", sithPuppet_aStrSubModes[newMode], pThing->aName);
        return -1;
    }

    if ( newTrackNum == SITHPUPPET_PLAYERROR_ALREADYPLAYING ) // already playing
    {
        return -1;
    }

    rdPuppet* pPuppet = pThing->renderData.pPuppet;
    if ( (pPuppet->aTracks[trackNum].status & RDPUPPET_TRACK_PAUSED) != 0 )
    {
        return -1;
    }

    float progress = pPuppet->aTracks[trackNum].curFrame / (float)pPuppet->aTracks[trackNum].pKFTrack->numFrames;

    float frame = bReverse
        ? (float)pPuppet->aTracks[newTrackNum].pKFTrack->numFrames * (1.0f - progress)
        : (float)pPuppet->aTracks[newTrackNum].pKFTrack->numFrames * progress;

    pPuppet->aTracks[newTrackNum].curFrame  = frame;
    pPuppet->aTracks[newTrackNum].prevFrame = frame;

    if ( newMode < SITHPUPPETSUBMODE_JUMPROLLFWD || newMode > SITHPUPPETSUBMODE_GRABARMS )
    {
        pThing->pPuppetState->submode = newMode;
    }

    sithPuppet_StopKey(pPuppet, trackNum, 0.0f);
    return newTrackNum;
}

void J3DAPI sithPuppet_ClearMode(SithThing* pThing, SithPuppetSubMode mode)
{
    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pTrack->pNextTrack )
    {
        if ( pTrack->submode == mode )
        {
            sithPuppet_StopKey(pThing->renderData.pPuppet, pTrack->trackNum, 0.0f);
            sithPuppet_FreeTrack(pThing, pTrack);
            return;
        }
    }
}

void J3DAPI sithPuppet_RemoveTrackByIndex(SithThing* pThing, int trackNum)
{
    for ( SithPuppetTrack* pTrack = pThing->pPuppetState->pFirstTrack; pTrack; pTrack = pTrack->pNextTrack )
    {
        if ( pTrack->trackNum == trackNum )
        {
            sithPuppet_FreeTrack(pThing, pTrack);
            return;
        }
    }
}

int J3DAPI sithPuppet_NewTrack(SithThing* pThing, SithPuppetClassSubmode* pSubmode, int trackNum, SithPuppetSubMode submode)
{
    SithPuppetTrack* pNewTrack = (SithPuppetTrack*)STDMALLOC(sizeof(SithPuppetTrack));
    if ( !pNewTrack )
    {
        return 1;
    }

    pNewTrack->pSubmode   = pSubmode;
    pNewTrack->trackNum   = trackNum;
    pNewTrack->submode    = submode;
    pNewTrack->pNextTrack = NULL;
    sithPuppet_AddTrack(pThing, pNewTrack);
    return 0;
}

void J3DAPI sithPuppet_AddTrack(SithThing* pThing, SithPuppetTrack* pNewTrack)
{
    SITH_ASSERTREL(pNewTrack);

    SithPuppetTrack* pCurTrack = pThing->pPuppetState->pFirstTrack;
    if ( pCurTrack )
    {
        size_t count = 1; // ?? 
        while ( pCurTrack->pNextTrack )
        {
            pCurTrack = pCurTrack->pNextTrack;
            ++count;
        }

        pCurTrack->pNextTrack = pNewTrack;
    }
    else
    {
        pThing->pPuppetState->pFirstTrack = pNewTrack;
    }
}

void J3DAPI sithPuppet_RemoveTrack(SithThing* pThing, SithPuppetTrack* pTrack)
{
    // Note, could actually be sithPuppet_FreeTrack;
    sithPuppet_FreeTrack(pThing, pTrack);
}

void J3DAPI sithPuppet_FreeTrack(SithThing* pThing, SithPuppetTrack* pTrack)
{
    // Note, could be defined in sithPuppet_RemoveTrack
    SithPuppetTrack* pFirstTrack = pThing->pPuppetState->pFirstTrack;
    if ( pFirstTrack )
    {
        if ( pFirstTrack == pTrack )
        {
            pThing->pPuppetState->pFirstTrack = pFirstTrack->pNextTrack;
            stdMemory_Free(pFirstTrack);
        }
        else
        {
            SithPuppetTrack* pPrevTrack = pThing->pPuppetState->pFirstTrack;
            for ( SithPuppetTrack* pCurTrack = pFirstTrack->pNextTrack; pCurTrack; pCurTrack = pCurTrack->pNextTrack )
            {
                if ( pCurTrack == pTrack )
                {
                    SithPuppetTrack* pNextTrack = pCurTrack->pNextTrack;
                    stdMemory_Free(pCurTrack);
                    pPrevTrack->pNextTrack = pNextTrack;
                    return;
                }

                pPrevTrack = pCurTrack;
            }
        }
    }
}

void J3DAPI sithPuppet_FreeTrackByIndex(SithThing* pThing, int trackNum)
{
    SithPuppetTrack* pFirstTrack = pThing->pPuppetState->pFirstTrack;
    if ( pFirstTrack && pFirstTrack != STDMEMORY_FREEDPTR )
    {
        if ( pFirstTrack->trackNum == trackNum )
        {
            pThing->pPuppetState->pFirstTrack = pFirstTrack->pNextTrack;
            stdMemory_Free(pFirstTrack);
        }
        else
        {
            SithPuppetTrack* pPrevTrack = pThing->pPuppetState->pFirstTrack;
            for ( SithPuppetTrack* pCurTrack = pFirstTrack->pNextTrack; pCurTrack && pCurTrack != STDMEMORY_FREEDPTR; pCurTrack = pCurTrack->pNextTrack )
            {
                if ( pCurTrack->trackNum == trackNum )
                {
                    SithPuppetTrack* pNextTrack = pCurTrack->pNextTrack;
                    stdMemory_Free(pCurTrack);
                    pPrevTrack->pNextTrack = pNextTrack;
                    return;
                }

                pPrevTrack = pCurTrack;
            }
        }
    }
}

SithPuppetTrack* J3DAPI sithPuppet_GetModeTrack(const SithThing* pThing, SithPuppetSubMode mode)
{
    return sithPuppet_GetModeTrackImpl(pThing, mode);
}

SithPuppetTrack* J3DAPI sithPuppet_GetModeTrackImpl(const SithThing* pThing, SithPuppetSubMode submode)
{
    SithPuppetTrack* pCurTrack = pThing->pPuppetState->pFirstTrack;
    while ( pCurTrack )
    {
        if ( pCurTrack->submode == submode )
        {
            return pCurTrack;
        }

        pCurTrack = pCurTrack->pNextTrack;
        if ( pCurTrack == STDMEMORY_FREEDPTR )
        {
            pCurTrack = NULL;
        }
    }

    return NULL;
}

void J3DAPI sithPuppet_ClearTrackList(SithThing* pThing)
{
    SithPuppetTrack* pNextTrack;
    for ( SithPuppetTrack* pCurTrack = pThing->pPuppetState->pFirstTrack; pCurTrack; pCurTrack = pNextTrack )
    {
        pNextTrack = pCurTrack->pNextTrack;
        stdMemory_Free(pCurTrack);
    }

    pThing->pPuppetState->pFirstTrack = NULL;
}