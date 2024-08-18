#include "sithDSSThing.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


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
    // J3D_HOOKFUNC(sithDSSThing_Attachment);
    // J3D_HOOKFUNC(sithDSSThing_ProcessAttachment);
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

int J3DAPI sithDSSThing_UpdateState(const SithThing* pThing, DPID toID, unsigned int sendFlags)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_UpdateState, pThing, toID, sendFlags);
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

int J3DAPI sithDSSThing_Attachment(const SithThing* pThing, DPID idTo, unsigned int outstream, unsigned int sendFlags)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_Attachment, pThing, idTo, outstream, sendFlags);
}

int J3DAPI sithDSSThing_ProcessAttachment(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSThing_ProcessAttachment, pMsg);
}

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
