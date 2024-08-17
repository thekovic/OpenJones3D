#include "Sound.h"
#include <j3dcore/j3dhook.h>
#include <sound/RTI/symbols.h>

#define Sound_cacheBlockSize J3D_DECL_FAR_VAR(Sound_cacheBlockSize, int)
#define Sound_maxVolume J3D_DECL_FAR_VAR(Sound_maxVolume, float)
#define Sound_defaultDistanceFactor J3D_DECL_FAR_VAR(Sound_defaultDistanceFactor, float)
#define Sound_pfGetThingInfoCallback J3D_DECL_FAR_VAR(Sound_pfGetThingInfoCallback, SoundGetThingInfoCallback)
#define Sound_aFades J3D_DECL_FAR_ARRAYVAR(Sound_aFades, SoundFade(*)[48])
#define Sound_nextHandle J3D_DECL_FAR_VAR(Sound_nextHandle, int)
#define Sound_loadBuffer J3D_DECL_FAR_ARRAYVAR(Sound_loadBuffer, uint8_t(*)[10000])
#define Sound_bNoSound3D J3D_DECL_FAR_VAR(Sound_bNoSound3D, int)
#define Sound_hwnd J3D_DECL_FAR_VAR(Sound_hwnd, HWND)
#define Sound_pDirectSound J3D_DECL_FAR_VAR(Sound_pDirectSound, LPDIRECTSOUND)
#define Sound_pfCalcListenerSoundMix J3D_DECL_FAR_VAR(Sound_pfCalcListenerSoundMix, SoundCalcListenerSoundMixFunc)
#define Sound_pausedRefCount J3D_DECL_FAR_VAR(Sound_pausedRefCount, int)
#define Sound_bNoLipSync J3D_DECL_FAR_VAR(Sound_bNoLipSync, int)
#define Sound_msecPauseStartTime J3D_DECL_FAR_VAR(Sound_msecPauseStartTime, unsigned int)
#define Sound_msecElapsed J3D_DECL_FAR_VAR(Sound_msecElapsed, unsigned int)
#define Sound_bGlobalFocusBuf J3D_DECL_FAR_VAR(Sound_bGlobalFocusBuf, int)
#define Sound_sndFilename J3D_DECL_FAR_ARRAYVAR(Sound_sndFilename, char(*)[256])
#define Sound_bNoSoundCompression J3D_DECL_FAR_VAR(Sound_bNoSoundCompression, int)
#define Sound_maxChannels J3D_DECL_FAR_VAR(Sound_maxChannels, int)
#define Sound_bLoadEnabled J3D_DECL_FAR_VAR(Sound_bLoadEnabled, int)
#define soundbank_apSoundCache J3D_DECL_FAR_ARRAYVAR(soundbank_apSoundCache, uint8_t*(*)[2])
#define soundbank_aUsedCacheSizes J3D_DECL_FAR_ARRAYVAR(soundbank_aUsedCacheSizes, int(*)[2])
#define soundbank_aCacheSizes J3D_DECL_FAR_ARRAYVAR(soundbank_aCacheSizes, int(*)[2])
#define soundbank_lastImportedBankNum J3D_DECL_FAR_VAR(soundbank_lastImportedBankNum, int)
#define soundbank_apSoundInfos J3D_DECL_FAR_ARRAYVAR(soundbank_apSoundInfos, SoundInfo*(*)[2])
#define soundbank_aNumSounds J3D_DECL_FAR_ARRAYVAR(soundbank_aNumSounds, int(*)[2])
#define soundbank_aSizeSounds J3D_DECL_FAR_ARRAYVAR(soundbank_aSizeSounds, int(*)[2])
#define Sound_apChannels J3D_DECL_FAR_VAR(Sound_apChannels, tSoundChannel*)
#define Sound_numChannels J3D_DECL_FAR_VAR(Sound_numChannels, int)
#define Sound_sizeChannels J3D_DECL_FAR_VAR(Sound_sizeChannels, int)
#define Sound_pMemfileBuf J3D_DECL_FAR_VAR(Sound_pMemfileBuf, void*)
#define Sound_memfileSize J3D_DECL_FAR_VAR(Sound_memfileSize, int)
#define Sound_memfilePos J3D_DECL_FAR_VAR(Sound_memfilePos, int)
#define Sound_pHS J3D_DECL_FAR_VAR(Sound_pHS, tHostServices*)
#define Sound_startupState J3D_DECL_FAR_VAR(Sound_startupState, int)
#define Sound_bReverseSound J3D_DECL_FAR_VAR(Sound_bReverseSound, int)
#define Sound_curUpdatePos J3D_DECL_FAR_VAR(Sound_curUpdatePos, rdVector3)

void Sound_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(Sound_Initialize);
    // J3D_HOOKFUNC(Sound_Uninitialize);
    // J3D_HOOKFUNC(Sound_Startup);
    // J3D_HOOKFUNC(Sound_Shutdown);
    // J3D_HOOKFUNC(Sound_Open);
    // J3D_HOOKFUNC(Sound_Close);
    // J3D_HOOKFUNC(Sound_Save);
    // J3D_HOOKFUNC(Sound_Restore);
    // J3D_HOOKFUNC(Sound_Pause);
    // J3D_HOOKFUNC(Sound_Resume);
    // J3D_HOOKFUNC(Sound_Set3DGlobals);
    // J3D_HOOKFUNC(Sound_Has3DHW);
    // J3D_HOOKFUNC(Sound_Set3DHWState);
    // J3D_HOOKFUNC(Sound_Get3DHWState);
    // J3D_HOOKFUNC(Sound_GetMemoryUsage);
    // J3D_HOOKFUNC(Sound_Load);
    // J3D_HOOKFUNC(Sound_LoadStatic);
    // J3D_HOOKFUNC(Sound_ResetBanks);
    // J3D_HOOKFUNC(Sound_EnableLoad);
    // J3D_HOOKFUNC(Sound_ExportStaticBank);
    // J3D_HOOKFUNC(Sound_ImportStaticBank);
    // J3D_HOOKFUNC(Sound_ExportNormalBank);
    // J3D_HOOKFUNC(Sound_ImportNormalBank);
    // J3D_HOOKFUNC(Sound_SkipSoundFileSection);
    // J3D_HOOKFUNC(Sound_GetSoundHandle);
    // J3D_HOOKFUNC(Sound_GetSoundIndex);
    // J3D_HOOKFUNC(Sound_GetChannelHandle);
    // J3D_HOOKFUNC(Sound_GetChannelGUID);
    // J3D_HOOKFUNC(Sound_GetSoundFilename);
    // J3D_HOOKFUNC(Sound_GetLengthMsec);
    // J3D_HOOKFUNC(Sound_SetMaxVolume);
    // J3D_HOOKFUNC(Sound_GetMaxVolume);
    // J3D_HOOKFUNC(Sound_Play);
    // J3D_HOOKFUNC(Sound_PlayPos);
    // J3D_HOOKFUNC(Sound_PlayThing);
    // J3D_HOOKFUNC(Sound_StopChannel);
    // J3D_HOOKFUNC(Sound_StopAllSounds);
    // J3D_HOOKFUNC(Sound_StopThing);
    // J3D_HOOKFUNC(Sound_SetVolume);
    // J3D_HOOKFUNC(Sound_FadeVolume);
    // J3D_HOOKFUNC(Sound_SetVolumeThing);
    // J3D_HOOKFUNC(Sound_FadeVolumeThing);
    // J3D_HOOKFUNC(Sound_IsThingFadingVol);
    // J3D_HOOKFUNC(Sound_SetChannelPitch);
    // J3D_HOOKFUNC(Sound_GetChannelPitch);
    // J3D_HOOKFUNC(Sound_FadePitch);
    // J3D_HOOKFUNC(Sound_SetPitchThing);
    // J3D_HOOKFUNC(Sound_GetChannelFlags);
    // J3D_HOOKFUNC(Sound_Update);
    // J3D_HOOKFUNC(Sound_GenerateLipSync);
    // J3D_HOOKFUNC(Sound_SetReverseSound);
    // J3D_HOOKFUNC(Sound_GetNextHandle);
    // J3D_HOOKFUNC(Sound_GetNextChannelHandle);
    // J3D_HOOKFUNC(Sound_GetFreeCache);
    // J3D_HOOKFUNC(Sound_IncreaseFreeCache);
    // J3D_HOOKFUNC(Sound_BankCacheWriteSoundFilePath);
    // J3D_HOOKFUNC(Sound_GetDeltaTime);
    // J3D_HOOKFUNC(Sound_soundbank_GetSoundInfo);
    // J3D_HOOKFUNC(Sound_GetChannel);
    // J3D_HOOKFUNC(Sound_GetChannelBySoundHandle);
    // J3D_HOOKFUNC(Sound_GetSoundBufferData);
    // J3D_HOOKFUNC(Sound_MemFileRead);
    // J3D_HOOKFUNC(Sound_MemFileWrite);
    // J3D_HOOKFUNC(Sound_MemFileReset);
    // J3D_HOOKFUNC(Sound_MemFileFree);
    // J3D_HOOKFUNC(Sound_StopAllNonStaticSounds);
    // J3D_HOOKFUNC(Sound_ExportBank);
    // J3D_HOOKFUNC(Sound_ImportBank);
    // J3D_HOOKFUNC(Sound_ReadFile);
}

void Sound_ResetGlobals(void)
{
    int Sound_cacheBlockSize_tmp = 2097152;
    memcpy(&Sound_cacheBlockSize, &Sound_cacheBlockSize_tmp, sizeof(Sound_cacheBlockSize));
    
    float Sound_maxVolume_tmp = 1.0f;
    memcpy(&Sound_maxVolume, &Sound_maxVolume_tmp, sizeof(Sound_maxVolume));
    
    float Sound_defaultDistanceFactor_tmp = 0.30000001f;
    memcpy(&Sound_defaultDistanceFactor, &Sound_defaultDistanceFactor_tmp, sizeof(Sound_defaultDistanceFactor));
    
    memset(&Sound_pfGetThingInfoCallback, 0, sizeof(Sound_pfGetThingInfoCallback));
    memset(&Sound_aFades, 0, sizeof(Sound_aFades));
    memset(&Sound_nextHandle, 0, sizeof(Sound_nextHandle));
    memset(&Sound_loadBuffer, 0, sizeof(Sound_loadBuffer));
    memset(&Sound_bNoSound3D, 0, sizeof(Sound_bNoSound3D));
    memset(&Sound_hwnd, 0, sizeof(Sound_hwnd));
    memset(&Sound_pDirectSound, 0, sizeof(Sound_pDirectSound));
    memset(&Sound_pfCalcListenerSoundMix, 0, sizeof(Sound_pfCalcListenerSoundMix));
    memset(&Sound_pausedRefCount, 0, sizeof(Sound_pausedRefCount));
    memset(&Sound_bNoLipSync, 0, sizeof(Sound_bNoLipSync));
    memset(&Sound_msecPauseStartTime, 0, sizeof(Sound_msecPauseStartTime));
    memset(&Sound_msecElapsed, 0, sizeof(Sound_msecElapsed));
    memset(&Sound_bGlobalFocusBuf, 0, sizeof(Sound_bGlobalFocusBuf));
    memset(&Sound_sndFilename, 0, sizeof(Sound_sndFilename));
    memset(&Sound_bNoSoundCompression, 0, sizeof(Sound_bNoSoundCompression));
    memset(&Sound_maxChannels, 0, sizeof(Sound_maxChannels));
    memset(&Sound_bLoadEnabled, 0, sizeof(Sound_bLoadEnabled));
    memset(&soundbank_apSoundCache, 0, sizeof(soundbank_apSoundCache));
    memset(&soundbank_aUsedCacheSizes, 0, sizeof(soundbank_aUsedCacheSizes));
    memset(&soundbank_aCacheSizes, 0, sizeof(soundbank_aCacheSizes));
    memset(&soundbank_lastImportedBankNum, 0, sizeof(soundbank_lastImportedBankNum));
    memset(&soundbank_apSoundInfos, 0, sizeof(soundbank_apSoundInfos));
    memset(&soundbank_aNumSounds, 0, sizeof(soundbank_aNumSounds));
    memset(&soundbank_aSizeSounds, 0, sizeof(soundbank_aSizeSounds));
    memset(&Sound_apChannels, 0, sizeof(Sound_apChannels));
    memset(&Sound_numChannels, 0, sizeof(Sound_numChannels));
    memset(&Sound_sizeChannels, 0, sizeof(Sound_sizeChannels));
    memset(&Sound_pMemfileBuf, 0, sizeof(Sound_pMemfileBuf));
    memset(&Sound_memfileSize, 0, sizeof(Sound_memfileSize));
    memset(&Sound_memfilePos, 0, sizeof(Sound_memfilePos));
    memset(&Sound_pHS, 0, sizeof(Sound_pHS));
    memset(&Sound_startupState, 0, sizeof(Sound_startupState));
    memset(&Sound_bReverseSound, 0, sizeof(Sound_bReverseSound));
    memset(&Sound_curUpdatePos, 0, sizeof(Sound_curUpdatePos));
}

int J3DAPI Sound_Initialize(tHostServices* pHS)
{
    return J3D_TRAMPOLINE_CALL(Sound_Initialize, pHS);
}

void J3DAPI Sound_Uninitialize()
{
    J3D_TRAMPOLINE_CALL(Sound_Uninitialize);
}

int J3DAPI Sound_Startup()
{
    return J3D_TRAMPOLINE_CALL(Sound_Startup);
}

void Sound_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(Sound_Shutdown);
}

int J3DAPI Sound_Open(unsigned int flags, int maxSoundChannels, SoundGetThingInfoCallback pfGetThingInfo, SoundCalcListenerSoundMixFunc pfCalcListenerSoundMix, HWND hwnd)
{
    return J3D_TRAMPOLINE_CALL(Sound_Open, flags, maxSoundChannels, pfGetThingInfo, pfCalcListenerSoundMix, hwnd);
}

void J3DAPI Sound_Close()
{
    J3D_TRAMPOLINE_CALL(Sound_Close);
}

int J3DAPI Sound_Save(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_Save, fh);
}

int J3DAPI Sound_Restore(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_Restore, fh);
}

void J3DAPI Sound_Pause()
{
    J3D_TRAMPOLINE_CALL(Sound_Pause);
}

void J3DAPI Sound_Resume()
{
    J3D_TRAMPOLINE_CALL(Sound_Resume);
}

void J3DAPI Sound_Set3DGlobals(float distanceFactor, float minDistance, float maxDistance, float folloverFactor, float dopplerFactor)
{
    J3D_TRAMPOLINE_CALL(Sound_Set3DGlobals, distanceFactor, minDistance, maxDistance, folloverFactor, dopplerFactor);
}

int J3DAPI Sound_Has3DHW()
{
    return J3D_TRAMPOLINE_CALL(Sound_Has3DHW);
}

void J3DAPI Sound_Set3DHWState(int bNo3DSound)
{
    J3D_TRAMPOLINE_CALL(Sound_Set3DHWState, bNo3DSound);
}

int J3DAPI Sound_Get3DHWState()
{
    return J3D_TRAMPOLINE_CALL(Sound_Get3DHWState);
}

unsigned int J3DAPI Sound_GetMemoryUsage()
{
    return J3D_TRAMPOLINE_CALL(Sound_GetMemoryUsage);
}

tSoundHandle J3DAPI Sound_Load(const char* filePath, int* sndIdx)
{
    return J3D_TRAMPOLINE_CALL(Sound_Load, filePath, sndIdx);
}

tSoundHandle J3DAPI Sound_LoadStatic(const char* pFilename, int* idx)
{
    return J3D_TRAMPOLINE_CALL(Sound_LoadStatic, pFilename, idx);
}

void J3DAPI Sound_ResetBanks(int bClearAll)
{
    J3D_TRAMPOLINE_CALL(Sound_ResetBanks, bClearAll);
}

int J3DAPI Sound_EnableLoad(int bEnable)
{
    return J3D_TRAMPOLINE_CALL(Sound_EnableLoad, bEnable);
}

size_t J3DAPI Sound_ExportStaticBank(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_ExportStaticBank, fh);
}

int J3DAPI Sound_ImportStaticBank(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_ImportStaticBank, fh);
}

size_t J3DAPI Sound_ExportNormalBank(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_ExportNormalBank, fh);
}

int J3DAPI Sound_ImportNormalBank(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_ImportNormalBank, fh);
}

int J3DAPI Sound_SkipSoundFileSection(tFileHandle fh)
{
    return J3D_TRAMPOLINE_CALL(Sound_SkipSoundFileSection, fh);
}

tSoundHandle J3DAPI Sound_GetSoundHandle(int idx)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetSoundHandle, idx);
}

int J3DAPI Sound_GetSoundIndex(tSoundHandle hSnd)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetSoundIndex, hSnd);
}

tSoundChannelHandle J3DAPI Sound_GetChannelHandle(int guid)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannelHandle, guid);
}

int J3DAPI Sound_GetChannelGUID(tSoundChannelHandle hSndChannel)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannelGUID, hSndChannel);
}

// handle can be either tSoundTrackHandle or tSoundHandle
const char* J3DAPI Sound_GetSoundFilename(unsigned int handle)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetSoundFilename, handle);
}

// handle can be either sound track handle or sound handle
unsigned int J3DAPI Sound_GetLengthMsec(unsigned int handle)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetLengthMsec, handle);
}

void J3DAPI Sound_SetMaxVolume(float maxVolume)
{
    J3D_TRAMPOLINE_CALL(Sound_SetMaxVolume, maxVolume);
}

float J3DAPI Sound_GetMaxVolume()
{
    return J3D_TRAMPOLINE_CALL(Sound_GetMaxVolume);
}

tSoundChannelHandle J3DAPI Sound_Play(tSoundHandle hSnd, float volume, float pan, int priority, tSoundChannelFlag flags, int guid)
{
    return J3D_TRAMPOLINE_CALL(Sound_Play, hSnd, volume, pan, priority, flags, guid);
}

tSoundChannelHandle J3DAPI Sound_PlayPos(tSoundHandle hSnd, float volume, int priority, tSoundChannelFlag channelflags, float x, float y, float z, int guid, float minRadius, float maxRadius, SoundEnvFlags envflags)
{
    return J3D_TRAMPOLINE_CALL(Sound_PlayPos, hSnd, volume, priority, channelflags, x, y, z, guid, minRadius, maxRadius, envflags);
}

tSoundChannelHandle J3DAPI Sound_PlayThing(tSoundHandle hSnd, float volume, int priority, tSoundChannelFlag flags, int thingID, int guid, float minRadius, float maxRadius)
{
    return J3D_TRAMPOLINE_CALL(Sound_PlayThing, hSnd, volume, priority, flags, thingID, guid, minRadius, maxRadius);
}

void J3DAPI Sound_StopChannel(tSoundChannelHandle hChannel)
{
    J3D_TRAMPOLINE_CALL(Sound_StopChannel, hChannel);
}

void J3DAPI Sound_StopAllSounds()
{
    J3D_TRAMPOLINE_CALL(Sound_StopAllSounds);
}

// handle can be either track handle or sound handle
void J3DAPI Sound_StopThing(int thingId, unsigned int handle)
{
    J3D_TRAMPOLINE_CALL(Sound_StopThing, thingId, handle);
}

void J3DAPI Sound_SetVolume(tSoundChannelHandle hChannel, float volume)
{
    J3D_TRAMPOLINE_CALL(Sound_SetVolume, hChannel, volume);
}

void J3DAPI Sound_FadeVolume(tSoundChannelHandle hChannel, float volume, float secFadeTime)
{
    J3D_TRAMPOLINE_CALL(Sound_FadeVolume, hChannel, volume, secFadeTime);
}

// handle is eather track handle or sound handle
void J3DAPI Sound_SetVolumeThing(int thingId, int handle, float volume)
{
    J3D_TRAMPOLINE_CALL(Sound_SetVolumeThing, thingId, handle, volume);
}

// handle is either track handle or sound handle
void J3DAPI Sound_FadeVolumeThing(int thingId, int handle, float startVolume, float endVolume)
{
    J3D_TRAMPOLINE_CALL(Sound_FadeVolumeThing, thingId, handle, startVolume, endVolume);
}

// handle is either track handle or sound handle
unsigned int J3DAPI Sound_IsThingFadingVol(int thingId, unsigned int handle)
{
    return J3D_TRAMPOLINE_CALL(Sound_IsThingFadingVol, thingId, handle);
}

void J3DAPI Sound_SetChannelPitch(tSoundChannelHandle hChannel, float pitch)
{
    J3D_TRAMPOLINE_CALL(Sound_SetChannelPitch, hChannel, pitch);
}

float J3DAPI Sound_GetChannelPitch(tSoundChannelHandle hChannel)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannelPitch, hChannel);
}

void J3DAPI Sound_FadePitch(tSoundChannelHandle hChannel, float pitch, float secFadeTime)
{
    J3D_TRAMPOLINE_CALL(Sound_FadePitch, hChannel, pitch, secFadeTime);
}

// handle is either track handle or sound handle
void J3DAPI Sound_SetPitchThing(int thingId, int handle, float pitch)
{
    J3D_TRAMPOLINE_CALL(Sound_SetPitchThing, thingId, handle, pitch);
}

tSoundChannelFlag J3DAPI Sound_GetChannelFlags(tSoundChannelHandle hChannel)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannelFlags, hChannel);
}

void J3DAPI Sound_Update(const rdVector3* pPos, const rdVector3* pVelocity, rdVector3* pTopOrient, rdVector3* pFrontOrient)
{
    J3D_TRAMPOLINE_CALL(Sound_Update, pPos, pVelocity, pTopOrient, pFrontOrient);
}

int J3DAPI Sound_GenerateLipSync(tSoundChannelHandle hChannel, int* pMouthPosX, int* pMouthPosY, int a4)
{
    return J3D_TRAMPOLINE_CALL(Sound_GenerateLipSync, hChannel, pMouthPosX, pMouthPosY, a4);
}

void J3DAPI Sound_SetReverseSound(int bReverse)
{
    J3D_TRAMPOLINE_CALL(Sound_SetReverseSound, bReverse);
}

tSoundHandle J3DAPI Sound_GetNextHandle()
{
    return J3D_TRAMPOLINE_CALL(Sound_GetNextHandle);
}

tSoundChannelHandle J3DAPI Sound_GetNextChannelHandle()
{
    return J3D_TRAMPOLINE_CALL(Sound_GetNextChannelHandle);
}

int J3DAPI Sound_GetFreeCache(int bankNum, int requiredSize)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetFreeCache, bankNum, requiredSize);
}

void J3DAPI Sound_IncreaseFreeCache(int bankNum, unsigned int nSize)
{
    J3D_TRAMPOLINE_CALL(Sound_IncreaseFreeCache, bankNum, nSize);
}

int J3DAPI Sound_BankCacheWriteSoundFilePath(int bankNum, const void* pName, unsigned int len)
{
    return J3D_TRAMPOLINE_CALL(Sound_BankCacheWriteSoundFilePath, bankNum, pName, len);
}

int J3DAPI Sound_GetDeltaTime()
{
    return J3D_TRAMPOLINE_CALL(Sound_GetDeltaTime);
}

SoundInfo* J3DAPI Sound_soundbank_GetSoundInfo(tSoundHandle hSnd)
{
    return J3D_TRAMPOLINE_CALL(Sound_soundbank_GetSoundInfo, hSnd);
}

tSoundChannel* J3DAPI Sound_GetChannel(tSoundChannelHandle hChannel)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannel, hChannel);
}

tSoundChannel* J3DAPI Sound_GetChannelBySoundHandle(tSoundHandle hSnd)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetChannelBySoundHandle, hSnd);
}

uint8_t* J3DAPI Sound_GetSoundBufferData(LPDIRECTSOUNDBUFFER pDSBuf, unsigned int* pDataSize, unsigned int* pbCompressed)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetSoundBufferData, pDSBuf, pDataSize, pbCompressed);
}

size_t J3DAPI Sound_MemFileRead(tFileHandle fh, void* pOutData, size_t nRead)
{
    return J3D_TRAMPOLINE_CALL(Sound_MemFileRead, fh, pOutData, nRead);
}

size_t J3DAPI Sound_MemFileWrite(tFileHandle fh, const void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(Sound_MemFileWrite, fh, pData, size);
}

tFileHandle J3DAPI Sound_MemFileReset()
{
    return J3D_TRAMPOLINE_CALL(Sound_MemFileReset);
}

void J3DAPI Sound_MemFileFree()
{
    J3D_TRAMPOLINE_CALL(Sound_MemFileFree);
}

void Sound_StopAllNonStaticSounds()
{
    J3D_TRAMPOLINE_CALL(Sound_StopAllNonStaticSounds);
}

size_t J3DAPI Sound_ExportBank(tFileHandle fh, int bankNum)
{
    return J3D_TRAMPOLINE_CALL(Sound_ExportBank, fh, bankNum);
}

int J3DAPI Sound_ImportBank(tFileHandle fh, int bankNum)
{
    return J3D_TRAMPOLINE_CALL(Sound_ImportBank, fh, bankNum);
}

int J3DAPI Sound_ReadFile(tFileHandle fh, void* pData, unsigned int size)
{
    return J3D_TRAMPOLINE_CALL(Sound_ReadFile, fh, pData, size);
}
