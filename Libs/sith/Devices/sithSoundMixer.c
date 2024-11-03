#include "sithSoundMixer.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Math/rdVector.h>

#include <sith/Engine/sithCamera.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithThing.h>

#include <sound/Sound.h>

#include <std/General/stdMath.h>
#include <std/General/stdMemory.h>
#include <std/Win95/stdComm.h>

static bool sithSoundMixer_bStartup = false; // Added: Init. to false
static uint16_t sithSoundMixer_channelGUIDSeed = 0; // Added: Init to 0

static SithSector* sithSoundMixer_pCurSector = NULL; // Added: Init to null
tSoundChannelHandle sithSoundMixer_hCurAmbientChannel;

int sithSoundMixer_GetNextChannelGUID(void);
tSoundChannelFlag J3DAPI sithSoundMixer_PlayFlagsToChannelFlags(SoundPlayFlag flags);
int J3DAPI sithSoundMixer_GetPlayPriority(SoundPlayFlag playflags);
int J3DAPI sithSoundMixer_GetThingID(int idx);
int J3DAPI sithSoundMixer_GetThingIndex(int thingID);

void sithSoundMixer_InstallHooks(void)
{
    J3D_HOOKFUNC(sithSoundMixer_Startup);
    J3D_HOOKFUNC(sithSoundMixer_Shutdown);
    J3D_HOOKFUNC(sithSoundMixer_ClearAmbientSector);
    J3D_HOOKFUNC(sithSoundMixer_PlaySound);
    J3D_HOOKFUNC(sithSoundMixer_PlaySoundPos);
    J3D_HOOKFUNC(sithSoundMixer_PlaySoundThing);
    J3D_HOOKFUNC(sithSoundMixer_StopSound);
    J3D_HOOKFUNC(sithSoundMixer_StopAll);
    J3D_HOOKFUNC(sithSoundMixer_FadeVolume);
    J3D_HOOKFUNC(sithSoundMixer_FadePitch);
    J3D_HOOKFUNC(sithSoundMixer_SetPitchThing);
    J3D_HOOKFUNC(sithSoundMixer_SetVolumeThing);
    J3D_HOOKFUNC(sithSoundMixer_FadeVolumeThing);
    J3D_HOOKFUNC(sithSoundMixer_IsThingFadingVol);
    J3D_HOOKFUNC(sithSoundMixer_Update);
    J3D_HOOKFUNC(sithSoundMixer_GetThingInfo);
    J3D_HOOKFUNC(sithSoundMixer_CalcCameraRelativeSoundMix);
    J3D_HOOKFUNC(sithSoundMixer_StopAllSoundsThing);
    J3D_HOOKFUNC(sithSoundMixer_GetChannelHandle);
    J3D_HOOKFUNC(sithSoundMixer_StopSoundThing);
    J3D_HOOKFUNC(sithSoundMixer_SetSectorAmbientSound);
    J3D_HOOKFUNC(sithSoundMixer_GameSave);
    J3D_HOOKFUNC(sithSoundMixer_GameRestore);
    J3D_HOOKFUNC(sithSoundMixer_GetNextChannelGUID);
    J3D_HOOKFUNC(sithSoundMixer_PlayFlagsToChannelFlags);
    J3D_HOOKFUNC(sithSoundMixer_GetPlayPriority);
    J3D_HOOKFUNC(sithSoundMixer_GetThingID);
    J3D_HOOKFUNC(sithSoundMixer_GetThingIndex);
}

void sithSoundMixer_ResetGlobals(void)
{
}

int sithSoundMixer_Startup(void)
{
    if ( sithSoundMixer_bStartup )
    {
        SITHLOG_ERROR("Multiple open in soundmix.\n");
        return 1;
    }

    sithSoundMixer_ClearAmbientSector();
    sithSoundMixer_bStartup = true;
    return 0;
}

void sithSoundMixer_Shutdown(void)
{
    if ( sithSoundMixer_bStartup )
    {
        sithSoundMixer_StopAll();
        sithSoundMixer_ClearAmbientSector();
        sithSoundMixer_bStartup = false;
    }
}

void sithSoundMixer_ClearAmbientSector(void)
{
    sithSoundMixer_pCurSector = NULL;
    sithSoundMixer_hCurAmbientChannel = 0;
}

void sithSoundMixer_Pause(void)
{
    if ( !stdComm_IsGameActive() ) {
        Sound_Pause();
    }
}

void sithSoundMixer_Resume(void)
{
    if ( !stdComm_IsGameActive() ) {
        Sound_Resume();
    }
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySound(tSoundHandle hSnd, float volume, float pan, SoundPlayFlag playflags)
{
    if ( !sithSoundMixer_bStartup ) {
        return 0;
    }

    int guid                = sithSoundMixer_GetNextChannelGUID();
    tSoundChannelFlag flags = sithSoundMixer_PlayFlagsToChannelFlags(playflags);
    int priority            = sithSoundMixer_GetPlayPriority(playflags);
    return Sound_Play(hSnd, volume, pan, priority, flags, guid);
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundPos(tSoundHandle hSnd, rdVector3* pos, SithSector* pSector, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags)
{
    if ( !sithSoundMixer_bStartup ) {
        return 0;
    }

    if ( !sithCamera_g_pCurCamera ) {
        return 0;
    }

    if ( (playflags & SOUNDPLAY_LOOP) == 0 )
    {
        rdVector3 dvec;
        rdVector_Sub3(&dvec, pos, &sithCamera_g_pCurCamera->lookPos);
        if ( rdVector_Normalize3QuickAcc(&dvec) > maxRadius ) {
            return 0;
        }
    }

    SoundEnvFlags envflags = 0;
    if ( pSector && (pSector->flags & SITH_SECTOR_UNDERWATER) != 0 ) {
        envflags |= SOUND_ENV_UNDERWATER;
    }

    int guid                = sithSoundMixer_GetNextChannelGUID();
    tSoundChannelFlag flags = sithSoundMixer_PlayFlagsToChannelFlags(playflags);
    int priority            = sithSoundMixer_GetPlayPriority(playflags);
    return Sound_PlayPos(hSnd, volume, priority, flags, pos->x, pos->y, pos->z, guid, minRadius, maxRadius, envflags);
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundThing(tSoundHandle hSnd, const SithThing* pThing, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags)
{
    SITH_ASSERTREL(pThing);
    if ( !sithSoundMixer_bStartup ) {
        return 0;
    }

    if ( !sithCamera_g_pCurCamera ) {
        return 0;
    }

    if ( (playflags & SOUNDPLAY_LOOP) == 0 )
    {
        rdVector3 dvec;
        rdVector_Sub3(&dvec, &pThing->pos, &sithCamera_g_pCurCamera->lookPos);
        if ( rdVector_Normalize3QuickAcc(&dvec) > maxRadius ) {
            return 0;
        }
    }

    int guid                = sithSoundMixer_GetNextChannelGUID();
    int thingID             = sithSoundMixer_GetThingID(pThing->idx);
    tSoundChannelFlag flags = sithSoundMixer_PlayFlagsToChannelFlags(playflags);
    int priority            = sithSoundMixer_GetPlayPriority(playflags);
    return Sound_PlayThing(hSnd, volume, priority, flags, thingID, guid, minRadius, maxRadius);
}

void J3DAPI sithSoundMixer_StopSound(tSoundChannelHandle hChannel)
{
    Sound_StopChannel(hChannel);
}

void sithSoundMixer_StopAll(void)
{
    Sound_StopAllSounds();
    sithSoundMixer_ClearAmbientSector();
}

void J3DAPI sithSoundMixer_FadeVolume(tSoundChannelHandle hChannel, float volume, float secFadeTime)
{
    Sound_FadeVolume(hChannel, volume, secFadeTime);
}

void J3DAPI sithSoundMixer_SetVolume(tSoundChannelHandle hChannel, float volume)
{
    Sound_SetVolume(hChannel, volume);
}

void J3DAPI sithSoundMixer_FadePitch(tSoundChannelHandle hSndChannel, float pitch, float secFadeTime)
{
    Sound_FadePitch(hSndChannel, pitch, secFadeTime);
}

void J3DAPI sithSoundMixer_SetPitch(tSoundChannelHandle hChannel, float pitch)
{
    Sound_SetPitch(hChannel, pitch);
}

void J3DAPI sithSoundMixer_SetPitchThing(const SithThing* pThing, unsigned int handle, float pitch)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    Sound_SetPitchThing(thingID, handle, pitch);
}

void J3DAPI sithSoundMixer_SetVolumeThing(const SithThing* pThing, unsigned int handle, float volume)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    Sound_SetVolumeThing(thingID, handle, volume);
}

void J3DAPI sithSoundMixer_FadeVolumeThing(const SithThing* pThing, unsigned int handle, float startVolume, float endVolume)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    Sound_FadeVolumeThing(thingID, handle, startVolume, endVolume);
}

int J3DAPI sithSoundMixer_IsThingFadingVol(const SithThing* pThing, unsigned int handle)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    return Sound_IsThingFadingVol(thingID, handle);
}

int J3DAPI sithSoundMixer_IsThingFadingPitch(SithThing* pThing, int handle)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    return Sound_IsThingFadingPitch(thingID, handle);
}

void sithSoundMixer_Update(void)
{
    if ( !sithCamera_g_pCurCamera || !sithCamera_g_pCurCamera->pSector )
    {
        Sound_Update(NULL, NULL, NULL, NULL);
        return;
    }

    if ( sithCamera_g_pCurCamera->pSector != sithSoundMixer_pCurSector )
    {
        tSoundHandle hSndPrev = 0;
        float sndVolPrev      = 0.0f;
        if ( sithSoundMixer_pCurSector )
        {
            hSndPrev = sithSoundMixer_pCurSector->hAmbientSound;
            sndVolPrev = sithSoundMixer_pCurSector->ambientSoundVolume;
        }

        sithSoundMixer_pCurSector = sithCamera_g_pCurCamera->pSector;
        tSoundHandle hSnd = sithSoundMixer_pCurSector->hAmbientSound;
        float sndVol = sithSoundMixer_pCurSector->ambientSoundVolume;
        if ( sithSoundMixer_pCurSector->ambientSoundVolume == 0.0f )
        {
            hSnd = 0;
        }

        if ( hSnd == hSndPrev )
        {
            if ( sndVol != sndVolPrev )
            {
                sithSoundMixer_FadeVolume(sithSoundMixer_hCurAmbientChannel, sndVol, 0.5f);
            }
        }
        else
        {
            if ( sithSoundMixer_hCurAmbientChannel )
            {
                sithSoundMixer_FadeVolume(sithSoundMixer_hCurAmbientChannel, 0.0f, 0.5f);
                sithSoundMixer_hCurAmbientChannel = 0;
            }

            if ( hSnd )
            {
                sithSoundMixer_hCurAmbientChannel = sithSoundMixer_PlaySound(hSnd, 0.0f, 0.0f, SOUNDPLAY_LOOP);
                if ( sithSoundMixer_hCurAmbientChannel )
                {
                    sithSoundMixer_FadeVolume(sithSoundMixer_hCurAmbientChannel, sndVol, 0.5f);
                }
            }
        }
    }

    rdVector3 fwdDir;
    rdVector_Neg3(&fwdDir, &sithCamera_g_pCurCamera->orient.lvec);
    Sound_Update(&sithCamera_g_pCurCamera->lookPos, NULL, &sithCamera_g_pCurCamera->orient.uvec, &fwdDir);
}

int J3DAPI sithSoundMixer_GetThingInfo(int thingId, SoundThingInfo* pThingInfo)
{
    int thidx = sithSoundMixer_GetThingIndex(thingId);
    SithThing* pThing = sithThing_GetThingByIndex(thidx);
    if ( !pThing )
    {
        return 0;
    }

    rdVector_Copy3(&pThingInfo->pos, &pThing->pos);
    if ( pThing->moveType == SITH_MT_PHYSICS )
    {
        rdVector_Copy3(&pThingInfo->velocity, &pThing->moveInfo.physics.velocity);
    }
    else
    {
        rdVector_Set3(&pThingInfo->velocity, 0.0f, 0.0f, 0.0f);
    }

    SoundEnvFlags envflags = pThingInfo->envflags;
    if ( (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) != 0 )
    {
        envflags |= SOUND_ENV_UNDERWATER;
    }
    else
    {
        envflags &= ~SOUND_ENV_UNDERWATER;
    }

    pThingInfo->envflags = envflags;
    return 1;
}

void J3DAPI sithSoundMixer_CalcCameraRelativeSoundMix(const SoundSpatialInfo* pSpatialInfo, float* volume, float* pan, float* pitch)
{
    float vol = pSpatialInfo->volume;
    SoundEnvFlags flags = pSpatialInfo->flags;

    if ( sithCamera_g_pCurCamera )
    {
        rdVector3 pos, dir;
        rdVector_Set3(&pos, pSpatialInfo->pos.x, pSpatialInfo->pos.y, pSpatialInfo->pos.z);
        rdVector_Sub3(&dir, &pos, &sithCamera_g_pCurCamera->lookPos);
        float dist = rdVector_Normalize3QuickAcc(&dir);

        float dot = rdVector_Dot3(&sithCamera_g_pCurCamera->orient.lvec, &dir);
        if ( dot < 0.0f )
        {
            vol = (1.0f - -dot * 0.3f) * vol;
        }

        if ( pan )
        {
            *pan = rdVector_Dot3(&sithCamera_g_pCurCamera->orient.rvec, &dir);
        }

        if ( dist < pSpatialInfo->maxRadius && sithCamera_g_pCurCamera->pSector )
        {
            if ( (flags & SOUND_ENV_UNDERWATER) == 0 || (sithCamera_g_pCurCamera->pSector->flags & SITH_SECTOR_UNDERWATER) != 0 )
            {
                if ( (flags & SOUND_ENV_UNDERWATER) == 0 && (sithCamera_g_pCurCamera->pSector->flags & SITH_SECTOR_UNDERWATER) != 0 )
                {
                    dist = dist * 1.5f;
                }
            }
            else
            {
                dist = dist * 1.5f;
            }
        }

        if ( volume )
        {
            float minDist = dist - pSpatialInfo->minRadius;
            if ( minDist <= 0.0f )
            {
                vol = pSpatialInfo->volume;
            }
            else
            {
                float dminmax = 0.0f;
                if ( pSpatialInfo->minRadius != pSpatialInfo->maxRadius )
                {
                    dminmax = 1.0f / (pSpatialInfo->maxRadius - pSpatialInfo->minRadius);
                }

                float volLev = STDMATH_CLAMP(minDist * dminmax, 0.0f, 1.0f);
                vol = (1.0f - volLev) * vol;
            }

            *volume = vol;
        }

        if ( pitch )
        {
            *pitch = 1.0f;
        }
    }
}

void J3DAPI sithSoundMixer_StopAllSoundsThing(const SithThing* pThing)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    Sound_StopThing(thingID, 0);
}

tSoundChannelHandle J3DAPI sithSoundMixer_GetChannelHandle(int guid)
{
    if ( guid ) {
        return Sound_GetChannelHandle(guid);
    }

    return 0;
}

void J3DAPI sithSoundMixer_StopSoundThing(const SithThing* pThing, unsigned int handle)
{
    int thingID = sithSoundMixer_GetThingID(pThing->idx);
    Sound_StopThing(thingID, handle);
}

void J3DAPI sithSoundMixer_SetSectorAmbientSound(SithSector* pSector, tSoundHandle hSnd, float volume)
{
    SITH_ASSERTREL(pSector);

    pSector->hAmbientSound      = hSnd;
    pSector->ambientSoundVolume = volume;
    if ( sithSoundMixer_pCurSector == pSector )
    {
        sithSoundMixer_pCurSector = NULL;
    }
}

int J3DAPI sithSoundMixer_GameSave(tFileHandle fh)
{
    static_assert(sizeof(sithSoundMixer_hCurAmbientChannel) == 4, "sizeof(sithSoundMixer_hCurAmbientChannel) == 4");
    return sith_g_pHS->pFileWrite(fh, &sithSoundMixer_hCurAmbientChannel, sizeof(sithSoundMixer_hCurAmbientChannel)) != sizeof(sithSoundMixer_hCurAmbientChannel)
        || Sound_Save(fh) == 0;
}

int J3DAPI sithSoundMixer_GameRestore(tFileHandle fh)
{
    sithSoundMixer_StopAll();

    tSoundChannelHandle hAmbChannel;
    if ( sith_g_pHS->pFileRead(fh, &hAmbChannel, sizeof(sithSoundMixer_hCurAmbientChannel)) != sizeof(sithSoundMixer_hCurAmbientChannel) )
    {
        return 1;
    }

    sithSoundMixer_ClearAmbientSector();

    if ( !Sound_Restore(fh) )
    {
        return 1;
    }

    Sound_StopChannel(hAmbChannel); // TODO: Why hAmbChannel is not set to sithSoundMixer_hCurAmbientChannel?
    return 0;
}

int sithSoundMixer_GetNextChannelGUID(void)
{
    if ( !sithSoundMixer_channelGUIDSeed ) {
        sithSoundMixer_channelGUIDSeed = 1;
    }

    return sithSoundMixer_channelGUIDSeed++ | ((sithPlayer_g_playerNum + 1) << 16);
}

tSoundChannelFlag J3DAPI sithSoundMixer_PlayFlagsToChannelFlags(SoundPlayFlag flags)
{
    tSoundChannelFlag chflags = (flags & SOUNDPLAY_LOOP) != 0 ? SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING : SOUND_CHANNEL_PLAYING;
    if ( (flags & SOUNDPLAY_PLAYONCE) != 0 ) {
        chflags |= SOUND_CHANNEL_PLAYONCE;
    }

    if ( (flags & SOUNDPLAY_PLAYTHIGNONCE) != 0 ) {
        chflags |= SOUND_CHANNEL_PLAYTHINGONCE;
    }

    return chflags;
}

int J3DAPI sithSoundMixer_GetPlayPriority(SoundPlayFlag playflags)
{
    switch ( playflags & (SOUNDPLAY_HIGHEST_PRIORITY | SOUNDPLAY_HIGH_PRIORITY) )
    {
        case SOUNDPLAY_HIGH_PRIORITY:
            return 500;

        case SOUNDPLAY_HIGHEST_PRIORITY:
            return 1000;

        case SOUNDPLAY_HIGHEST_PRIORITY | SOUNDPLAY_HIGH_PRIORITY:
            return 2000;
    }

    return 0;
}

int J3DAPI sithSoundMixer_GetThingID(int idx)
{
    return idx + 1;
}

int J3DAPI sithSoundMixer_GetThingIndex(int thingID)
{
    return thingID - 1;
}
