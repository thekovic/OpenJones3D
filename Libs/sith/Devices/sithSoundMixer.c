#include "sithSoundMixer.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Math/rdVector.h>

#include <sith/Engine/sithCamera.h>
#include <sith/RTI/symbols.h>

#include <sound/Sound.h>

#define sithSoundMixer_channelGUIDSeed J3D_DECL_FAR_VAR(sithSoundMixer_channelGUIDSeed, uint16_t)
#define sithSoundMixer_bStartup J3D_DECL_FAR_VAR(sithSoundMixer_bStartup, int)
#define sithSoundMixer_pCurSector J3D_DECL_FAR_VAR(sithSoundMixer_pCurSector, SithSector*)
#define sithSoundMixer_hCurAmbientChannel J3D_DECL_FAR_VAR(sithSoundMixer_hCurAmbientChannel, tSoundChannelHandle)

void sithSoundMixer_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSoundMixer_Startup);
    // J3D_HOOKFUNC(sithSoundMixer_Shutdown);
    // J3D_HOOKFUNC(sithSoundMixer_ClearAmbientSector);
    // J3D_HOOKFUNC(sithSoundMixer_PlaySound);
    // J3D_HOOKFUNC(sithSoundMixer_PlaySoundPos);
    // J3D_HOOKFUNC(sithSoundMixer_PlaySoundThing);
    // J3D_HOOKFUNC(sithSoundMixer_StopSound);
    // J3D_HOOKFUNC(sithSoundMixer_StopAll);
    // J3D_HOOKFUNC(sithSoundMixer_FadeVolume);
    // J3D_HOOKFUNC(sithSoundMixer_FadePitch);
    // J3D_HOOKFUNC(sithSoundMixer_SetPitchThing);
    // J3D_HOOKFUNC(sithSoundMixer_SetVolumeThing);
    // J3D_HOOKFUNC(sithSoundMixer_FadeVolumeThing);
    // J3D_HOOKFUNC(sithSoundMixer_IsThingFadingVol);
    J3D_HOOKFUNC(sithSoundMixer_Update);
    // J3D_HOOKFUNC(sithSoundMixer_GetThingInfo);
    // J3D_HOOKFUNC(sithSoundMixer_CalcCameraRelativeSoundMix);
    // J3D_HOOKFUNC(sithSoundMixer_StopAllSoundsThing);
    // J3D_HOOKFUNC(sithSoundMixer_GetChannelHandle);
    // J3D_HOOKFUNC(sithSoundMixer_StopSoundThing);
    // J3D_HOOKFUNC(sithSoundMixer_SetSectorAmbientSound);
    // J3D_HOOKFUNC(sithSoundMixer_GameSave);
    // J3D_HOOKFUNC(sithSoundMixer_GameRestore);
    // J3D_HOOKFUNC(sithSoundMixer_GetNextChannelGUID);
    // J3D_HOOKFUNC(sithSoundMixer_PlayFlagsToChannelFlags);
    // J3D_HOOKFUNC(sithSoundMixer_GetPlayPriority);
    // J3D_HOOKFUNC(sithSoundMixer_GetThingID);
    // J3D_HOOKFUNC(sithSoundMixer_GetThingIndex);
}

void sithSoundMixer_ResetGlobals(void)
{
    uint16_t sithSoundMixer_channelGUIDSeed_tmp = 1u;
    memcpy(&sithSoundMixer_channelGUIDSeed, &sithSoundMixer_channelGUIDSeed_tmp, sizeof(sithSoundMixer_channelGUIDSeed));

    memset(&sithSoundMixer_bStartup, 0, sizeof(sithSoundMixer_bStartup));
    memset(&sithSoundMixer_pCurSector, 0, sizeof(sithSoundMixer_pCurSector));
    memset(&sithSoundMixer_hCurAmbientChannel, 0, sizeof(sithSoundMixer_hCurAmbientChannel));
}

// TODO: verify if function is not really be named stdSound_Startup
int sithSoundMixer_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_Startup);
}

void J3DAPI sithSoundMixer_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_Shutdown);
}

void J3DAPI sithSoundMixer_ClearAmbientSector()
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_ClearAmbientSector);
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySound(tSoundHandle hSnd, float volume, float pan, SoundPlayFlag playflags)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_PlaySound, hSnd, volume, pan, playflags);
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundPos(tSoundHandle hSnd, rdVector3* pos, SithSector* pSector, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_PlaySoundPos, hSnd, pos, pSector, volume, minRadius, maxRadius, playflags);
}

tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundThing(tSoundHandle hSnd, const SithThing* pThing, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_PlaySoundThing, hSnd, pThing, volume, minRadius, maxRadius, playflags);
}

void J3DAPI sithSoundMixer_StopSound(tSoundChannelHandle hChannel)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_StopSound, hChannel);
}

void sithSoundMixer_StopAll(void)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_StopAll);
}

void J3DAPI sithSoundMixer_FadeVolume(tSoundChannelHandle hChannel, float volume, float secFadeTime)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_FadeVolume, hChannel, volume, secFadeTime);
}

void J3DAPI sithSoundMixer_FadePitch(tSoundChannelHandle hSndChannel, float pitch, float secFadeTime)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_FadePitch, hSndChannel, pitch, secFadeTime);
}

// handle is either track handle ot sound handle
void J3DAPI sithSoundMixer_SetPitchThing(SithThing* pThing, unsigned int handle, float a3)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_SetPitchThing, pThing, handle, a3);
}

// handle is either track handle or sound handle
void J3DAPI sithSoundMixer_SetVolumeThing(SithThing* pThing, tSoundChannelHandle hChannel, float volume)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_SetVolumeThing, pThing, hChannel, volume);
}

void J3DAPI sithSoundMixer_FadeVolumeThing(SithThing* pThing, unsigned int handle, float startVolume, float endVolume)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_FadeVolumeThing, pThing, handle, startVolume, endVolume);
}

// handle is either track handle or sound handle
unsigned int J3DAPI sithSoundMixer_IsThingFadingVol(SithThing* pThing, unsigned int handle)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_IsThingFadingVol, pThing, handle);
}

//void sithSoundMixer_Update(void)
//{
//    J3D_TRAMPOLINE_CALL(sithSoundMixer_Update);
//}

int J3DAPI sithSoundMixer_GetThingInfo(int thingId, SoundThingInfo* pThingInfo)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetThingInfo, thingId, pThingInfo);
}

void J3DAPI sithSoundMixer_CalcCameraRelativeSoundMix(const SoundSpatialInfo* pSpatialInfo, float* volume, float* pan, float* pitch)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_CalcCameraRelativeSoundMix, pSpatialInfo, volume, pan, pitch);
}

void J3DAPI sithSoundMixer_StopAllSoundsThing(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_StopAllSoundsThing, pThing);
}

tSoundChannelHandle J3DAPI sithSoundMixer_GetChannelHandle(int guid)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetChannelHandle, guid);
}

// handle can be either track handle or sound handle
void J3DAPI sithSoundMixer_StopSoundThing(SithThing* pThing, unsigned int handle)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_StopSoundThing, pThing, handle);
}

void J3DAPI sithSoundMixer_SetSectorAmbientSound(SithSector* pSector, tSoundHandle hSnd, float volume)
{
    J3D_TRAMPOLINE_CALL(sithSoundMixer_SetSectorAmbientSound, pSector, hSnd, volume);
}

int J3DAPI sithSoundMixer_GameSave(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GameSave, fh);
}

signed int J3DAPI sithSoundMixer_GameRestore(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GameRestore, fh);
}

int sithSoundMixer_GetNextChannelGUID(void)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetNextChannelGUID);
}

tSoundChannelFlag J3DAPI sithSoundMixer_PlayFlagsToChannelFlags(SoundPlayFlag flags)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_PlayFlagsToChannelFlags, flags);
}

int J3DAPI sithSoundMixer_GetPlayPriority(SoundPlayFlag playflags)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetPlayPriority, playflags);
}

int J3DAPI sithSoundMixer_GetThingID(int idx)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetThingID, idx);
}

int J3DAPI sithSoundMixer_GetThingIndex(int thingID)
{
    return J3D_TRAMPOLINE_CALL(sithSoundMixer_GetThingIndex, thingID);
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
        float sndVolPrev = 0.0f;
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
    Sound_Update(&sithCamera_g_pCurCamera->lookPos, 0, &sithCamera_g_pCurCamera->orient.uvec, &fwdDir);
}
