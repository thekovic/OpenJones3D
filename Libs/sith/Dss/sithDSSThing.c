#include "sithDSSThing.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Math/rdVector.h>

#include <sith/Devices/sithComm.h>
#include <sith/Dss/sithDSS.h>
#include <sith/Dss/sithMulti.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithSurface.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWorld.h>


void sithDSSThing_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithDSSThing_Pos);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPos);
    // J3D_HOOKFUNC(sithDSSThing_MovePos);
    // J3D_HOOKFUNC(sithDSSThing_ProcessMovePos);
    // J3D_HOOKFUNC(sithDSSThing_UpdateState);
    // J3D_HOOKFUNC(sithDSSThing_ProcessStateUpdate);
    // J3D_HOOKFUNC(sithDSSThing_PlaySound);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPlaySound);
    // J3D_HOOKFUNC(sithDSSThing_PlaySoundMode);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPlaySoundMode);
    // J3D_HOOKFUNC(sithDSSThing_PlayKey);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPlayKey);
    // J3D_HOOKFUNC(sithDSSThing_PlayKeyMode);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPlayKeyMode);
    // J3D_HOOKFUNC(sithDSSThing_SetModel);
    // J3D_HOOKFUNC(sithDSSThing_ProcessSetModel);
    // J3D_HOOKFUNC(sithDSSThing_StopKey);
    // J3D_HOOKFUNC(sithDSSThing_ProcessStopKey);
    // J3D_HOOKFUNC(sithDSSThing_StopSound);
    // J3D_HOOKFUNC(sithDSSThing_ProcessStopSound);
    // J3D_HOOKFUNC(sithDSSThing_Fire);
    // J3D_HOOKFUNC(sithDSSThing_ProcessFire);
    // J3D_HOOKFUNC(sithDSSThing_Death);
    // J3D_HOOKFUNC(sithDSSThing_ProcessDeath);
    // J3D_HOOKFUNC(sithDSSThing_DamageThing);
    // J3D_HOOKFUNC(sithDSSThing_ProcessDamage);
    // J3D_HOOKFUNC(sithDSSThing_FullDescription);
    // J3D_HOOKFUNC(sithDSSThing_ProcessFullDescription);
    // J3D_HOOKFUNC(sithDSSThing_PathMove);
    // J3D_HOOKFUNC(sithDSSThing_ProcessPathMove);
    J3D_HOOKFUNC(sithDSSThing_Attachment);
    J3D_HOOKFUNC(sithDSSThing_ProcessAttachment);
    // J3D_HOOKFUNC(sithDSSThing_Take);
    // J3D_HOOKFUNC(sithDSSThing_ProcessTake);
    // J3D_HOOKFUNC(sithDSSThing_CreateThing);
    // J3D_HOOKFUNC(sithDSSThing_ProcessCreateThing);
    // J3D_HOOKFUNC(sithDSSThing_DestroyThing);
    // J3D_HOOKFUNC(sithDSSThing_ProcessDestroyThing);
    // J3D_HOOKFUNC(sithDSSThing_MoveToPos);
}

void sithDSSThing_ResetGlobals(void)
{

}

int J3DAPI sithDSSThing_Pos(const SithThing* pThing, DPID toID, unsigned int dpFlags)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_Pos, pThing, toID, dpFlags);
}

int J3DAPI sithDSSThing_ProcessPos(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPos, pMsg);
}

int J3DAPI sithDSSThing_MovePos(const SithThing* pThing, DPID idTo, unsigned int sendFlags)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_MovePos, pThing, idTo, sendFlags);
}

int J3DAPI sithDSSThing_ProcessMovePos(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessMovePos, pMsg);
}

int J3DAPI sithDSSThing_UpdateState(const SithThing* pThing, DPID toID, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_UpdateState, pThing, toID, outstream);
}

int J3DAPI sithDSSThing_ProcessStateUpdate(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessStateUpdate, pMsg);
}

int J3DAPI sithDSSThing_PlaySound(const SithThing* pThing, const rdVector3* pPos, tSoundHandle hSnd, float volume, float pan, SoundPlayFlag playflags, int guid, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_PlaySound, pThing, pPos, hSnd, volume, pan, playflags, guid, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessPlaySound(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPlaySound, pMsg);
}

int J3DAPI sithDSSThing_PlaySoundMode(const SithThing* pThing, int16_t mode, int channel, float a4)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_PlaySoundMode, pThing, mode, channel, a4);
}

int J3DAPI sithDSSThing_ProcessPlaySoundMode(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPlaySoundMode, pMsg);
}

int J3DAPI sithDSSThing_PlayKey(const SithThing* pThing, const rdKeyframe* pKey, rdKeyframeFlags flags, int16_t lo, unsigned int trackGUID, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_PlayKey, pThing, pKey, flags, lo, trackGUID, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessPlayKey(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPlayKey, pMsg);
}

int J3DAPI sithDSSThing_PlayKeyMode(const SithThing* pThing, SithPuppetSubMode mode, unsigned int trackGUID, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_PlayKeyMode, pThing, mode, trackGUID, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessPlayKeyMode(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPlayKeyMode, pMsg);
}

int J3DAPI sithDSSThing_SetModel(const SithThing* pThing, DPID idTo)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_SetModel, pThing, idTo);
}

int J3DAPI sithDSSThing_ProcessSetModel(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessSetModel, pMsg);
}

int J3DAPI sithDSSThing_StopKey(const SithThing* pThing, int trackGUID, float fadeTime, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_StopKey, pThing, trackGUID, fadeTime, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessStopKey(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessStopKey, pMsg);
}

int J3DAPI sithDSSThing_StopSound(tSoundChannelHandle hChannel, float secFadeTime, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_StopSound, hChannel, secFadeTime, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessStopSound(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessStopSound, pMsg);
}

int J3DAPI sithDSSThing_Fire(const SithThing* pShooter, const SithThing* pProjectileTemplate, const rdVector3* fireDir, const rdVector3* firePos, tSoundHandle hFireSnd, uint16_t puppetSubmode, float extra, int16_t projectileFlags, float sedRapidFireTime, int projectileGUID, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_Fire, pShooter, pProjectileTemplate, fireDir, firePos, hFireSnd, puppetSubmode, extra, projectileFlags, sedRapidFireTime, projectileGUID, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessFire(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessFire, pMsg);
}

int J3DAPI sithDSSThing_Death(const SithThing* pThing, const SithThing* pKiller, char bKillPlayer, DPID to, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_Death, pThing, pKiller, bKillPlayer, to, outstream);
}

int J3DAPI sithDSSThing_ProcessDeath(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessDeath, pMsg);
}

int J3DAPI sithDSSThing_DamageThing(const SithThing* pVictim, const SithThing* pPurpetrator, float damage, SithDamageType hitType, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_DamageThing, pVictim, pPurpetrator, damage, hitType, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessDamage(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessDamage, pMsg);
}

int J3DAPI sithDSSThing_FullDescription(const SithThing* pThing, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_FullDescription, pThing, idTo, outstream);
}

int J3DAPI sithDSSThing_ProcessFullDescription(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessFullDescription, pMsg);
}

int J3DAPI sithDSSThing_PathMove(const SithThing* pThing, int16_t frame, float speed, int moveType, DPID idTO, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_PathMove, pThing, frame, speed, moveType, idTO, outstream);
}

int J3DAPI sithDSSThing_ProcessPathMove(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessPathMove, pMsg);
}

//int J3DAPI sithDSSThing_Attachment(const SithThing* pThing, DPID idTo, unsigned int outstream, unsigned int sendFlags)
//{
//    return J3D_TRAMPOLINE_CALL(sithDSSThing_Attachment, pThing, idTo, outstream, sendFlags);
//}
//
//int J3DAPI sithDSSThing_ProcessAttachment(const SithMessage* pMsg)
//{
//    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessAttachment, pMsg);
//}

int J3DAPI sithDSSThing_Take(const SithThing* pItem, const SithThing* pThing, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_Take, pItem, pThing, outstream);
}

int J3DAPI sithDSSThing_ProcessTake(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessTake, pMsg);
}

int J3DAPI sithDSSThing_CreateThing(const SithThing* pTemplate, const SithThing* pNewThing, const SithThing* pMarker, const SithSector* pSector, const rdVector3* pos, const rdVector3* pyr, unsigned int outstream, unsigned int sendFlags)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_CreateThing, pTemplate, pNewThing, pMarker, pSector, pos, pyr, outstream, sendFlags);
}

int J3DAPI sithDSSThing_ProcessCreateThing(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessCreateThing, pMsg);
}

int J3DAPI sithDSSThing_DestroyThing(int guid, DPID idTo)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_DestroyThing, guid, idTo);
}

int J3DAPI sithDSSThing_ProcessDestroyThing(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessDestroyThing, pMsg);
}

void J3DAPI sithDSSThing_MoveToPos(SithThing* pThing, const rdVector3* pPos, SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithDSSThing_MoveToPos, pThing, pPos, pSector);
}

int J3DAPI sithDSSThing_Attachment(const SithThing* pThing, DPID idTo, unsigned int outstream, unsigned int sendFlags)
{
    SITHDSS_STARTOUT(SITHDSS_ATTACHMENT);
    SITHDSS_PUSHINT32(pThing->guid);
    SITHDSS_PUSHUINT16(pThing->attach.flags);

    /**(uint32_t*)sithMulti_g_message.data = pThing->guid;
    *(uint16_t*)&sithMulti_g_message.data[4] = pThing->attach.flags;*/
    //uint8_t* pCurOut = &sithMulti_g_message.data[6];

    if ( (pThing->attach.flags & SITH_ATTACH_SURFACE) != 0 || (pThing->attach.flags & SITH_ATTACH_CLIMBSURFACE) != 0 )
    {
        SITHDSS_PUSHINT16(sithSurface_GetSurfaceIndex(pThing->attach.attachedToStructure.pSurfaceAttached));
        //*(uint16_t*)pCurOut = sithSurface_GetSurfaceIndex(pThing->attach.attachedToStructure.pSurfaceAttached);
        //pCurOut = &sithMulti_g_message.data[8];
    }
    else if ( (pThing->attach.flags & (SITH_ATTACH_THING | SITH_ATTACH_THINGFACE)) != 0 )
    {
        SITHDSS_PUSHINT32(pThing->attach.attachedToStructure.pThingAttached->guid);
       /**(uint32_t*)pCurOut = pThing->attach.attachedToStructure.pThingAttached->guid;
       pCurOut = &sithMulti_g_message.data[10];*/

        if ( (pThing->attach.flags & SITH_ATTACH_THINGFACE) != 0 )
        {
            SithThing* pThingAttached = pThing->attach.attachedToStructure.pThingAttached;
            if ( pThingAttached && pThingAttached->renderData.data.pModel3 )
            {
                // Note: This is buggy as the attached pFace can be from any of the model's mesh and not from the first one.
                const rdModel3Mesh* pMesh = pThing->attach.attachedToStructure.pThingAttached->renderData.data.pModel3->aGeos[0].aMeshes;
                int16_t faceIdx = pThing->attach.pFace - pMesh->aFaces;

                // Fixed: Added
                if ( faceIdx >= 0 && faceIdx < pMesh->numFaces ) {
                    SITHDSS_PUSHINT16(faceIdx);
                }
                else
                {
                    // TODO: This is quick fix, a better solution would be to pack mesh index and face index in int16.
                    //       Note, the vanilla engine doesn't handle -1 index on load and can crash the game.
                    //       But we don't care as it could crash anyway since the index is invalid.
                    SITHDSS_PUSHINT16(-1);
                }

                /**(uint16_t*)pCurOut = pThing->attach.pFace - pThing->attach.attachedToStructure.pThingAttached->renderData.data.pModel3->aGeos[0].aMeshes->aFaces;
                pCurOut = &sithMulti_g_message.data[12];*/
            }
            else
            {
                SITHDSS_PUSHINT16(-1);
                /**(uint16_t*)pCurOut = -1;
                pCurOut = &sithMulti_g_message.data[12];*/
            }
        }
        else
        {
            SITHDSS_PUSHVEC3(&pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing);
            /*memcpy(pCurOut, &pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing, 12u);
            pCurOut = &sithMulti_g_message.data[22];*/
        }
    }

    else if ( (pThing->attach.flags & SITH_ATTACH_THINGCLIMBWHIP) != 0 )
    {
        SITHDSS_PUSHFLOAT(pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing.z);
        /**(float*)pCurOut = pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing.z;
        pCurOut = &sithMulti_g_message.data[10];*/
    }

    /*sithMulti_g_message.type = SITHDSS_ATTACHMENT;
    sithMulti_g_message.length = pCurOut - sithMulti_g_message.data;*/
    SITHDSS_ENDOUT;
    return sithMessage_SendMessage(&sithMulti_g_message, idTo, outstream, sendFlags);
}

int J3DAPI sithDSSThing_ProcessAttachment(const SithMessage* pMsg)
{
    SITH_ASSERTREL(pMsg);
    SITHDSS_STARTIN(pMsg);

    //guid = *(uint32_t*)pMsg->data;
    int guid = SITHDSS_POPINT32();
    SithThing* pThing = sithThing_GetGuidThing(guid);
    if ( !pThing )
    {
        SITHLOG_ERROR("sithDSSThing_ProcessAttachment: Cannot find GUID for thing index %d.\n", guid);
        return 0;
    }

    //attachflags = *(uint16_t*)&pMsg->data[4];
    SithAttachFlag attachflags = SITHDSS_POPUINT16();

    // uint8_t* pCurIn = &pMsg->data[6];
    if ( (attachflags & (SITH_ATTACH_CLIMBSURFACE | SITH_ATTACH_SURFACE)) != 0 )
    {
        //surfIdx = *(uint16_t*)pCurIn;
        int surfIdx = SITHDSS_POPINT16();
        SithSurface* pSurf = sithSurface_GetSurfaceEx(sithWorld_g_pCurrentWorld, surfIdx);
        if ( !pSurf )
        {
            SITHLOG_ERROR("sithDSSThing_ProcessAttachment: Invalid surface index %d.\n", surfIdx);
            SITHDSS_ENDIN;
            return 0;
        }

        pThing->attach.flags = attachflags;
        pThing->attach.pFace = &pSurf->face;
        pThing->attach.attachedToStructure.pSurfaceAttached = pSurf;
        rdVector_Copy3(&pThing->attach.attachedFaceFirstVert, &sithWorld_g_pCurrentWorld->aVertices[*pSurf->face.aVertices]);
    }
    else if ( (attachflags & (SITH_ATTACH_THING | SITH_ATTACH_THINGFACE)) != 0 )
    {
        /*guidAttach = *(uint32_t*)pCurIn;
        pCurIn = &pMsg->data[10];*/

        int guidAttach = SITHDSS_POPINT32();
        SithThing* pThingAttached = sithThing_GetGuidThing(guidAttach);
        if ( !pThingAttached )
        {
            SITHLOG_ERROR("sithDSSThing_ProcessAttachment: Cannot find GUID for thing index %d.\n", guidAttach);
            SITHDSS_ENDIN;
            return 0;
        }

        pThing->attach.attachedToStructure.pThingAttached = pThingAttached;
        pThing->attach.flags = attachflags;
        sithThing_AddThingToAttachedThings(pThing, pThingAttached);

        if ( (attachflags & SITH_ATTACH_THINGFACE) != 0 )
        {
            int faceIdx = SITHDSS_POPINT16();

            // Fixed: Add null check and index bound check
            if ( pThingAttached->renderData.data.pModel3 && faceIdx >= 0 && faceIdx < pThingAttached->renderData.data.pModel3->aGeos[0].aMeshes->numFaces )
            {
                rdFace* pFaceAttached = &pThingAttached->renderData.data.pModel3->aGeos[0].aMeshes->aFaces[faceIdx];
                rdVector_Copy3(&pThing->attach.attachedFaceFirstVert, &pThingAttached->renderData.data.pModel3->aGeos[0].aMeshes->apVertices[*pFaceAttached->aVertices]);
                pThing->attach.pFace = pFaceAttached;
            }
            else // Added
            {
                pThing->attach.flags &= ~SITH_ATTACH_THINGFACE;
                if ( pThing->attach.flags == 0 ) {
                    pThing->attach.flags |= SITH_ATTACH_THING;
                }
            }
        }
        else
        {
            SITHDSS_POPVEC3(&pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing);
            //rdVector_Copy3(&pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing, pCurIn, sizeof(pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing));
        }
    }
    else if ( (attachflags & SITH_ATTACH_THINGCLIMBWHIP) != 0 )
    {
        pThing->attach.flags = attachflags;
        pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing.z = SITHDSS_POPFLOAT();
        //pThing->attach.vecUnknownMaybeLocalPositionOnTheAttachedThing.z = *(float*)pCurIn;
    }
    else if ( pThing->attach.flags )
    {
        sithThing_DetachThing(pThing);
    }

    SITHDSS_ENDIN;
    return 1;
}
