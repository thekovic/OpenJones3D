#ifndef SITH_SITHSOUNDMIXER_H
#define SITH_SITHSOUNDMIXER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

// TODO: verify if function is not really be named stdSound_Startup
int sithSoundMixer_Startup(void);
void J3DAPI sithSoundMixer_Shutdown();
void J3DAPI sithSoundMixer_ClearAmbientSector();
tSoundChannelHandle J3DAPI sithSoundMixer_PlaySound(tSoundHandle hSnd, float volume, float pan, SoundPlayFlag playflags);
tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundPos(tSoundHandle hSnd, rdVector3* pos, SithSector* pSector, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags);
tSoundChannelHandle J3DAPI sithSoundMixer_PlaySoundThing(tSoundHandle hSnd, const SithThing* pThing, float volume, float minRadius, float maxRadius, SoundPlayFlag playflags);
void J3DAPI sithSoundMixer_StopSound(tSoundChannelHandle hChannel);
void sithSoundMixer_StopAll(void);
void J3DAPI sithSoundMixer_FadeVolume(tSoundChannelHandle hChannel, float volume, float secFadeTime);
void J3DAPI sithSoundMixer_FadePitch(tSoundChannelHandle hSndChannel, float pitch, float secFadeTime);
// handle is either track handle ot sound handle
void J3DAPI sithSoundMixer_SetPitchThing(SithThing* pThing, unsigned int handle, float a3);
// handle is either track handle or sound handle
void J3DAPI sithSoundMixer_SetVolumeThing(SithThing* pThing, tSoundChannelHandle hChannel, float volume);
void J3DAPI sithSoundMixer_FadeVolumeThing(SithThing* pThing, unsigned int handle, float startVolume, float endVolume);
// handle is either track handle or sound handle
unsigned int J3DAPI sithSoundMixer_IsThingFadingVol(SithThing* pThing, unsigned int handle);
void sithSoundMixer_Update(void);
int J3DAPI sithSoundMixer_GetThingInfo(int thingId, SoundThingInfo* pThingInfo);
void J3DAPI sithSoundMixer_CalcCameraRelativeSoundMix(const SoundSpatialInfo* pSpatialInfo, float* volume, float* pan, float* pitch);
void J3DAPI sithSoundMixer_StopAllSoundsThing(SithThing* pThing);
tSoundChannelHandle J3DAPI sithSoundMixer_GetChannelHandle(int guid);
// handle can be either track handle or sound handle
void J3DAPI sithSoundMixer_StopSoundThing(SithThing* pThing, unsigned int handle);
void J3DAPI sithSoundMixer_SetSectorAmbientSound(SithSector* pSector, tSoundHandle hSnd, float volume);
int J3DAPI sithSoundMixer_GameSave(tFileHandle fh);
signed int J3DAPI sithSoundMixer_GameRestore(tFileHandle fh);
int sithSoundMixer_GetNextChannelGUID(void);
tSoundChannelFlag J3DAPI sithSoundMixer_PlayFlagsToChannelFlags(SoundPlayFlag flags);
int J3DAPI sithSoundMixer_GetPlayPriority(SoundPlayFlag playflags);
int J3DAPI sithSoundMixer_GetThingID(int idx);
int J3DAPI sithSoundMixer_GetThingIndex(int thingID);

// Helper hooking functions
void sithSoundMixer_InstallHooks(void);
void sithSoundMixer_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSOUNDMIXER_H
