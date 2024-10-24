#ifndef SOUND_SOUND_H
#define SOUND_SOUND_H
#include <j3dcore/j3d.h>
#include <sound/types.h>
#include <sound/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI Sound_Initialize(tHostServices* pHS);
void J3DAPI Sound_Uninitialize();
int J3DAPI Sound_Startup();
void Sound_Shutdown(void);
int J3DAPI Sound_Open(unsigned int flags, int maxSoundChannels, SoundGetThingInfoCallback pfGetThingInfo, SoundCalcListenerSoundMixFunc pfCalcListenerSoundMix, HWND hwnd);
void J3DAPI Sound_Close();
int J3DAPI Sound_Save(tFileHandle fh);
int J3DAPI Sound_Restore(tFileHandle fh);
void J3DAPI Sound_Pause();
void J3DAPI Sound_Resume();
void J3DAPI Sound_Set3DGlobals(float distanceFactor, float minDistance, float maxDistance, float folloverFactor, float dopplerFactor);
int J3DAPI Sound_Has3DHW();
void J3DAPI Sound_Set3DHWState(int bNo3DSound);
int J3DAPI Sound_Get3DHWState();
unsigned int J3DAPI Sound_GetMemoryUsage();
tSoundHandle J3DAPI Sound_Load(const char* filePath, int* sndIdx);
tSoundHandle J3DAPI Sound_LoadStatic(const char* pFilename, int* idx);
void J3DAPI Sound_ResetBanks(int bClearAll);
int J3DAPI Sound_EnableLoad(int bEnable);
size_t J3DAPI Sound_ExportStaticBank(tFileHandle fh);
int J3DAPI Sound_ImportStaticBank(tFileHandle fh);
size_t J3DAPI Sound_ExportNormalBank(tFileHandle fh);
int J3DAPI Sound_ImportNormalBank(tFileHandle fh);
int J3DAPI Sound_SkipSoundFileSection(tFileHandle fh);
tSoundHandle J3DAPI Sound_GetSoundHandle(int idx);
int J3DAPI Sound_GetSoundIndex(tSoundHandle hSnd);
tSoundChannelHandle J3DAPI Sound_GetChannelHandle(int guid);
int J3DAPI Sound_GetChannelGUID(tSoundChannelHandle hSndChannel);
// handle can be either tSoundTrackHandle or tSoundHandle
const char* J3DAPI Sound_GetSoundFilename(unsigned int handle);
// handle can be either sound track handle or sound handle
unsigned int J3DAPI Sound_GetLengthMsec(unsigned int handle);
void J3DAPI Sound_SetMaxVolume(float maxVolume);
float J3DAPI Sound_GetMaxVolume();
tSoundChannelHandle J3DAPI Sound_Play(tSoundHandle hSnd, float volume, float pan, int priority, tSoundChannelFlag flags, int guid);
tSoundChannelHandle J3DAPI Sound_PlayPos(tSoundHandle hSnd, float volume, int priority, tSoundChannelFlag channelflags, float x, float y, float z, int guid, float minRadius, float maxRadius, SoundEnvFlags envflags);
tSoundChannelHandle J3DAPI Sound_PlayThing(tSoundHandle hSnd, float volume, int priority, tSoundChannelFlag flags, int thingID, int guid, float minRadius, float maxRadius);
void J3DAPI Sound_StopChannel(tSoundChannelHandle hChannel);
void J3DAPI Sound_StopAllSounds();
// handle can be either track handle or sound handle
void J3DAPI Sound_StopThing(int thingId, unsigned int handle);
void J3DAPI Sound_SetVolume(tSoundChannelHandle hChannel, float volume);
void J3DAPI Sound_FadeVolume(tSoundChannelHandle hChannel, float volume, float secFadeTime);
// handle is eather track handle or sound handle
void J3DAPI Sound_SetVolumeThing(int thingId, int handle, float volume);
// handle is either track handle or sound handle
void J3DAPI Sound_FadeVolumeThing(int thingId, int handle, float startVolume, float endVolume);
// handle is either track handle or sound handle
unsigned int J3DAPI Sound_IsThingFadingVol(int thingId, unsigned int handle);
void J3DAPI Sound_SetPitch(tSoundChannelHandle hChannel, float pitch);
float J3DAPI Sound_GetPitch(tSoundChannelHandle hChannel);
void J3DAPI Sound_FadePitch(tSoundChannelHandle hChannel, float pitch, float secFadeTime);

void J3DAPI Sound_SetPitchThing(int thingId, int handle, float pitch); // handle is either track handle or sound handle
int J3DAPI Sound_IsThingFadingPitch(int thingId, unsigned int handle); // Added // handle is either track handle or sound handle

tSoundChannelFlag J3DAPI Sound_GetChannelFlags(tSoundChannelHandle hChannel);
void J3DAPI Sound_Update(const rdVector3* pPos, const rdVector3* pVelocity, const rdVector3* pTopOrient, const rdVector3* pFrontOrient);
int J3DAPI Sound_GenerateLipSync(tSoundChannelHandle hChannel, int* pMouthPosX, int* pMouthPosY, int a4);
void J3DAPI Sound_SetReverseSound(int bReverse);
tSoundHandle J3DAPI Sound_GetNextHandle();
tSoundChannelHandle J3DAPI Sound_GetNextChannelHandle();
int J3DAPI Sound_GetFreeCache(int bankNum, int requiredSize);
void J3DAPI Sound_IncreaseFreeCache(int bankNum, unsigned int nSize);
int J3DAPI Sound_BankCacheWriteSoundFilePath(int bankNum, const void* pName, unsigned int len);
int J3DAPI Sound_GetDeltaTime();
SoundInfo* J3DAPI Sound_soundbank_GetSoundInfo(tSoundHandle hSnd);
tSoundChannel* J3DAPI Sound_GetChannel(tSoundChannelHandle hChannel);
tSoundChannel* J3DAPI Sound_GetChannelBySoundHandle(tSoundHandle hSnd);
uint8_t* J3DAPI Sound_GetSoundBufferData(LPDIRECTSOUNDBUFFER pDSBuf, unsigned int* pDataSize, unsigned int* pbCompressed);
size_t J3DAPI Sound_MemFileRead(tFileHandle fh, void* pOutData, size_t nRead);
size_t J3DAPI Sound_MemFileWrite(tFileHandle fh, const void* pData, size_t size);
tFileHandle J3DAPI Sound_MemFileReset();
void J3DAPI Sound_MemFileFree();
void Sound_StopAllNonStaticSounds();
size_t J3DAPI Sound_ExportBank(tFileHandle fh, int bankNum);
int J3DAPI Sound_ImportBank(tFileHandle fh, int bankNum);
int J3DAPI Sound_ReadFile(tFileHandle fh, void* pData, unsigned int size);

// Helper hooking functions
void Sound_InstallHooks(void);
void Sound_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SOUND_SOUND_H
