#include "Sound.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Math/rdVector.h>
#include <rdroid/Math/rdMatrix.h>

#include "Driver.h"
#include <sound/RTI/symbols.h>

#include <std/General/stdUtil.h>

#define SOUND_OPEN 3u

static const uint32_t Sound_serMagic        = 0x12345678u;
static const uint32_t Sound_serSoundListEnd = 0u;

static char Sound_sndFilename[256] = { 0 };


#define Sound_cacheBlockSize J3D_DECL_FAR_VAR(Sound_cacheBlockSize, int)
#define Sound_maxVolume J3D_DECL_FAR_VAR(Sound_maxVolume, float)
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
//#define Sound_sndFilename J3D_DECL_FAR_ARRAYVAR(Sound_sndFilename, char(*)[256])
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
#define Sound_numChannels J3D_DECL_FAR_VAR(Sound_numChannels, size_t)
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
    J3D_HOOKFUNC(Sound_Save);
    J3D_HOOKFUNC(Sound_Restore);
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
    // J3D_HOOKFUNC(Sound_SetPitch);
    // J3D_HOOKFUNC(Sound_GetPitch);
    // J3D_HOOKFUNC(Sound_FadePitch);
    // J3D_HOOKFUNC(Sound_SetPitchThing);
    // J3D_HOOKFUNC(Sound_GetChannelFlags);
    J3D_HOOKFUNC(Sound_Update);
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
    //memset(&Sound_sndFilename, 0, sizeof(Sound_sndFilename));
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

//int J3DAPI Sound_Save(tFileHandle fh)
//{
//    return J3D_TRAMPOLINE_CALL(Sound_Save, fh);
//}
//
//int J3DAPI Sound_Restore(tFileHandle fh)
//{
//    return J3D_TRAMPOLINE_CALL(Sound_Restore, fh);
//}

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

tSoundHandle J3DAPI Sound_Load(const char* filePath, uint32_t* sndIdx)
{
    return J3D_TRAMPOLINE_CALL(Sound_Load, filePath, sndIdx);
}

tSoundHandle J3DAPI Sound_LoadStatic(const char* pFilename, uint32_t* idx)
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

void J3DAPI Sound_SetPitch(tSoundChannelHandle hChannel, float pitch)
{
    J3D_TRAMPOLINE_CALL(Sound_SetPitch, hChannel, pitch);
}

float J3DAPI Sound_GetPitch(tSoundChannelHandle hChannel)
{
    return J3D_TRAMPOLINE_CALL(Sound_GetPitch, hChannel);
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

//void J3DAPI Sound_Update(const rdVector3* pPos, const rdVector3* pVelocity, rdVector3* pTopOrient, rdVector3* pFrontOrient)
//{
//    J3D_TRAMPOLINE_CALL(Sound_Update, pPos, pVelocity, pTopOrient, pFrontOrient);
//}

int J3DAPI Sound_GenerateLipSync(tSoundChannelHandle hChannel, uint8_t* pMouthPosX, uint8_t* pMouthPosY, int a4)
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



int J3DAPI Sound_Save(tFileHandle fh)
{
    if ( Sound_startupState < 1 )
    {
        Sound_pHS->pErrorPrint("Sound_Save: module is not initialized.\n");
        return 0;
    }

    // section marker (header magic)
    if ( Sound_pHS->pFileWrite(fh, &Sound_serMagic, sizeof(Sound_serMagic)) != sizeof(Sound_serMagic) )
    {
        static_assert(sizeof(Sound_serMagic) == 4, "sizeof(Sound_sermagic) == 4");
        return 0;
    }

    if ( Sound_pHS->pFileWrite(fh, &Sound_pausedRefCount, sizeof(Sound_pausedRefCount)) != sizeof(Sound_pausedRefCount) )
    {
        static_assert(sizeof(Sound_pausedRefCount) == 4, "sizeof(Sound_pausedRefCount) == 4");
        return 0;
    }

    const uint32_t curDetlatTime = Sound_GetDeltaTime();
    if ( Sound_pHS->pFileWrite(fh, &curDetlatTime, sizeof(curDetlatTime)) != sizeof(curDetlatTime) )
    {
        static_assert(sizeof(curDetlatTime) == 4, "sizeof(curDetlatTime) == 4");
        return 0;
    }

    const uint32_t curDetlatPauseTime = SoundDriver_GetTimeMsec() - Sound_msecPauseStartTime;
    if ( Sound_pHS->pFileWrite(fh, &curDetlatPauseTime, sizeof(curDetlatPauseTime)) != sizeof(curDetlatPauseTime) )
    {
        static_assert(sizeof(curDetlatPauseTime) == 4, "sizeof(curDetlatPauseTime) == 4");
        return 0;
    }

    int channelNum = Sound_numChannels;
    tSoundChannel* pCurChannel = &Sound_apChannels[Sound_numChannels];

    while ( 1 )
    {
        --pCurChannel;
        if ( !channelNum-- )
        {
            break;
        }

        if ( pCurChannel->handle
            && ((pCurChannel->flags & (SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING)) == (SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING)
                || (pCurChannel->flags & SOUND_CHANNEL_FAR) != 0)
            && (pCurChannel->flags & SOUND_CHANNEL_3DSOUND) != 0 )
        {
            SoundInfo* pSndInfo = Sound_soundbank_GetSoundInfo(pCurChannel->hSnd);
            if ( pSndInfo )
            {
                uint8_t* aSndCache = soundbank_apSoundCache[pSndInfo->bankNum];

                // TODO: Make sure name max len should be less or equal than STD_ARRAYLEN(Sound_sndFilename)
                const uint32_t nameLen = strlen((const char*)&aSndCache[pSndInfo->filePathOffset]) + 1;
                if ( Sound_pHS->pFileWrite(fh, &nameLen, sizeof(nameLen)) != sizeof(nameLen) )
                {
                    static_assert(sizeof(nameLen) == 4, "sizeof(nameLen) == 4");
                    return 0;
                }

                // Write filename
                if ( Sound_pHS->pFileWrite(fh, &aSndCache[pSndInfo->filePathOffset], nameLen) != nameLen )
                {
                    return 0;
                }

                // Read sound bank num
                const uint32_t bankNum = pSndInfo->bankNum;
                if ( Sound_pHS->pFileWrite(fh, &bankNum, sizeof(bankNum)) != sizeof(bankNum) )
                {
                    static_assert(sizeof(bankNum) == 4, "sizeof(bankNum) == 4");
                    return 0;
                }

                // Read sound index
                const uint32_t sndIdx = pSndInfo->idx;
                if ( Sound_pHS->pFileWrite(fh, &sndIdx, sizeof(sndIdx)) != sizeof(sndIdx) )
                {
                    static_assert(sizeof(sndIdx) == 4, "sizeof(sndIdx) == 4");
                    return 0;
                }

                const uint32_t hSnd = pSndInfo->hSnd;
                if ( Sound_pHS->pFileWrite(fh, &hSnd, sizeof(hSnd)) != sizeof(hSnd) )
                {
                    static_assert(sizeof(hSnd) == 4, "sizeof(hSnd) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->handle, sizeof(pCurChannel->handle)) != sizeof(pCurChannel->handle) )
                {
                    static_assert(sizeof(pCurChannel->handle) == 4, "sizeof(pCurChannel->handle) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->priority, sizeof(pCurChannel->priority)) != sizeof(pCurChannel->priority) )
                {
                    static_assert(sizeof(pCurChannel->priority) == 4, "sizeof(pCurChannel->handle) == 4");

                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->thingId, sizeof(pCurChannel->thingId)) != sizeof(pCurChannel->thingId) )
                {
                    static_assert(sizeof(pCurChannel->thingId) == 4, "sizeof(pCurChannel->thingId) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->playPos.x, sizeof(pCurChannel->playPos.x)) != sizeof(pCurChannel->playPos.x) )
                {
                    static_assert(sizeof(pCurChannel->playPos.x) == 4, "sizeof(pCurChannel->playPos.x) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->playPos.y, sizeof(pCurChannel->playPos.y)) != sizeof(pCurChannel->playPos.y) )
                {
                    static_assert(sizeof(pCurChannel->playPos.y) == 4, "sizeof(pCurChannel->playPos.y) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->playPos.z, sizeof(pCurChannel->playPos.z)) != sizeof(pCurChannel->playPos.z) )
                {
                    static_assert(sizeof(pCurChannel->playPos.z) == 4, "sizeof(pCurChannel->playPos.z) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->volume, sizeof(pCurChannel->volume)) != sizeof(pCurChannel->volume) )
                {
                    static_assert(sizeof(pCurChannel->volume) == 4, "sizeof(pCurChannel->volume) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->pitch, sizeof(pCurChannel->pitch)) != sizeof(pCurChannel->pitch) )
                {
                    static_assert(sizeof(pCurChannel->pitch) == 4, "sizeof(pCurChannel->pitch) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->sampleRate, sizeof(pCurChannel->sampleRate)) != sizeof(pCurChannel->sampleRate) )
                {
                    static_assert(sizeof(pCurChannel->sampleRate) == 4, "sizeof(pCurChannel->sampleRate) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->flags, sizeof(pCurChannel->flags)) != sizeof(pCurChannel->flags) )
                {
                    static_assert(sizeof(pCurChannel->flags) == 4, "sizeof(pCurChannel->flags) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->guid, sizeof(pCurChannel->guid)) != sizeof(pCurChannel->guid) )
                {
                    static_assert(sizeof(pCurChannel->guid) == 4, "sizeof(pCurChannel->guid) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->minRadius, sizeof(pCurChannel->minRadius)) != sizeof(pCurChannel->minRadius) )
                {
                    static_assert(sizeof(pCurChannel->minRadius) == 4, "sizeof(pCurChannel->minRadius) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->maxRadius, sizeof(pCurChannel->maxRadius)) != sizeof(pCurChannel->maxRadius) )
                {
                    static_assert(sizeof(pCurChannel->maxRadius) == 4, "sizeof(pCurChannel->maxRadius) == 4");
                    return 0;
                }

                if ( Sound_pHS->pFileWrite(fh, &pCurChannel->envflags, sizeof(pCurChannel->envflags)) != sizeof(pCurChannel->envflags) )
                {
                    static_assert(sizeof(pCurChannel->envflags) == 4, "sizeof(pCurChannel->envflags) == 4");
                    return 0;
                }
            }
        }
    }

    // Marks end of list
    if ( Sound_pHS->pFileWrite(fh, &Sound_serSoundListEnd, sizeof(Sound_serSoundListEnd)) != sizeof(Sound_serSoundListEnd) )
    {
        static_assert(sizeof(Sound_serSoundListEnd) == 4, "sizeof(Sound_serSoundListEnd) == 4");
        return 0;
    }

    static_assert(sizeof(Sound_aFades) == 1152, "sizeof(Sound_aFades) == 1152");
    return Sound_pHS->pFileWrite(fh, &Sound_nextHandle, sizeof(uint32_t)) == sizeof(uint32_t)
        && Sound_pHS->pFileWrite(fh, Sound_aFades, sizeof(Sound_aFades)) == sizeof(Sound_aFades);// sizeof(SoundFade) * 48
}


int J3DAPI Sound_Restore(tFileHandle fh)
{
    if ( Sound_startupState != SOUND_OPEN )
    {
        // Sound module is not opened, read out sound list anyway so the file read offset is moved to the end of sound section
        Sound_pHS->pErrorPrint("Sound_Restore: module is not open.\n");
    }

    uint32_t magic;
    if ( Sound_pHS->pFileRead(fh, &magic, sizeof(magic)) != sizeof(magic) )
    {
        return 0;
    }

    if ( magic != Sound_serMagic )
    {
        // We're not at the ser sound position roll back position for sizeof(magic)
        Sound_pHS->pFileSeek(fh, -(int)sizeof(magic), 1);
        return 0;
    }

    // Set initial listener position
    if ( Sound_startupState == SOUND_OPEN )
    {
        rdVector3 listnerPos;
        listnerPos.x = 100000.0f;
        listnerPos.y = 100000.0f;
        listnerPos.z = 100000.0f;
        Sound_StopAllSounds();
        Sound_Update(&listnerPos, NULL, NULL, NULL);
    }

    if ( Sound_pHS->pFileRead(fh, &Sound_pausedRefCount, sizeof(uint32_t)) != sizeof(uint32_t) )
    {
        return 0;
    }

    Sound_pausedRefCount = 0; // ???

    uint32_t pauseDeltaTime;
    if ( Sound_pHS->pFileRead(fh, &pauseDeltaTime, sizeof(pauseDeltaTime)) != sizeof(pauseDeltaTime) )
    {
        return 0;
    }

    Sound_msecElapsed = SoundDriver_GetTimeMsec() - pauseDeltaTime;

    if ( Sound_pHS->pFileRead(fh, &Sound_msecPauseStartTime, sizeof(uint32_t)) != sizeof(uint32_t) )
    {
        return 0;
    }

    Sound_msecPauseStartTime += SoundDriver_GetTimeMsec();

    // Read sound file name length
    uint32_t filenameLen;
    if ( Sound_pHS->pFileRead(fh, &filenameLen, sizeof(filenameLen)) != sizeof(filenameLen) )
    {
        return 0;
    }

    while ( filenameLen != Sound_serSoundListEnd )
    {
        if ( filenameLen <= STD_ARRAYLEN(Sound_sndFilename) )
        {
            // Read filename
            if ( Sound_pHS->pFileRead(fh, Sound_sndFilename, filenameLen) != filenameLen )
            {
                return 0;
            }

            uint32_t bankNum;
            if ( Sound_pHS->pFileRead(fh, &bankNum, sizeof(bankNum)) != sizeof(bankNum) )
            {
                return 0;
            }

            // Read sound index
            uint32_t sndIdx;
            if ( Sound_pHS->pFileRead(fh, &sndIdx, sizeof(sndIdx)) != sizeof(sndIdx) )
            {
                return 0;
            }

            // Read sound handle
            if ( Sound_pHS->pFileRead(fh, &Sound_nextHandle, sizeof(uint32_t)) != sizeof(uint32_t) )
            {
                return 0;
            }

            tSoundHandle hSnd = 0;
            if ( Sound_startupState == SOUND_OPEN )
            {
                if ( bankNum ) // 1 - normal, 0 - static
                {
                    hSnd = Sound_Load(Sound_sndFilename, &sndIdx);
                }
                else
                {
                    hSnd = Sound_LoadStatic(Sound_sndFilename, &sndIdx);
                }
            }

            // Read channel handle
            if ( Sound_pHS->pFileRead(fh, &Sound_nextHandle, sizeof(uint32_t)) != sizeof(uint32_t) )
            {
                return 0;
            }

            int32_t priority;
            if ( Sound_pHS->pFileRead(fh, &priority, sizeof(priority)) != sizeof(priority) )
            {
                return 0;
            }

            int32_t thingId;
            if ( Sound_pHS->pFileRead(fh, &thingId, sizeof(thingId)) != sizeof(thingId) )
            {
                return 0;
            }

            float posX;
            if ( Sound_pHS->pFileRead(fh, &posX, sizeof(posX)) != sizeof(posX) )
            {
                return 0;
            }

            float posY;
            if ( Sound_pHS->pFileRead(fh, &posY, sizeof(posY)) != sizeof(posY) )
            {
                return 0;
            }

            float posZ;
            if ( Sound_pHS->pFileRead(fh, &posZ, sizeof(posY)) != sizeof(posY) )
            {
                return 0;
            }

            float volume;
            if ( Sound_pHS->pFileRead(fh, &volume, sizeof(volume)) != sizeof(volume) )
            {
                return 0;
            }

            float pitch;
            if ( Sound_pHS->pFileRead(fh, &pitch, sizeof(pitch)) != sizeof(pitch) )
            {
                return 0;
            }

            float sampleRate;
            if ( Sound_pHS->pFileRead(fh, &sampleRate, sizeof(sampleRate)) != sizeof(sampleRate) )
            {
                return 0;
            }

            tSoundChannelFlag chflags;
            if ( Sound_pHS->pFileRead(fh, &chflags, sizeof(int32_t)) != sizeof(int32_t) )
            {
                return 0;
            }

            int32_t guid;
            if ( Sound_pHS->pFileRead(fh, &guid, sizeof(guid)) != sizeof(guid) )
            {
                return 0;
            }

            float minRadius;
            if ( Sound_pHS->pFileRead(fh, &minRadius, sizeof(minRadius)) != sizeof(minRadius) )
            {
                return 0;
            }

            float maxRadius;
            if ( Sound_pHS->pFileRead(fh, &maxRadius, sizeof(maxRadius)) != sizeof(maxRadius) )
            {
                return 0;
            }

            SoundEnvFlags envflags;
            if ( Sound_pHS->pFileRead(fh, &envflags, sizeof(int32_t)) != sizeof(int32_t) )
            {
                return 0;
            }

            if ( Sound_startupState == SOUND_OPEN )
            {
                // Fixed: Mark far sound as loop play sound
                if ( (chflags & SOUND_CHANNEL_FAR) != 0 ) {
                    chflags |= (SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING);
                }

                if ( (chflags & (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND)) == (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND) )
                {
                    tSoundChannelHandle hChannel = Sound_PlayPos(hSnd, volume, priority, chflags, posX, posY, posZ, guid, minRadius, maxRadius, envflags);
                    tSoundChannel* pChannel = Sound_GetChannel(hChannel);
                    if ( pChannel )
                    {
                        pChannel->thingId = thingId;
                        pChannel->flags |= SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND;
                    }
                }
                else if ( (chflags & SOUND_CHANNEL_3DSOUND) != 0 )
                {
                    chflags |= SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING;
                    Sound_PlayPos(hSnd, volume, priority, chflags, posX, posY, posZ, guid, minRadius, maxRadius, envflags);
                }
            }
        }

        // Read next sound filename
        if ( Sound_pHS->pFileRead(fh, &filenameLen, sizeof(filenameLen)) != sizeof(filenameLen) )
        {
            return 0;
        }
    }

    // Read next handle and fades. 
    // Note, what's the point to read fades to system in case system is not opened? 
    return Sound_pHS->pFileRead(fh, &Sound_nextHandle, sizeof(uint32_t)) == sizeof(uint32_t) && Sound_pHS->pFileRead(fh, Sound_aFades, sizeof(Sound_aFades)) == sizeof(Sound_aFades);
}


bool J3DAPI Sound_IsThingFadingPitch(int thingId, unsigned int handle)
{
    if ( (int)handle >= 1234 && (int)handle < 1112345 && (handle & 1) != 0 )
    {
        return (Sound_GetChannelFlags(handle) & SOUND_CHANNEL_PITCHFADE) != 0;
    }

    if ( handle && ((int)handle < 1234 || (int)handle >= 1112345 || (handle & 1) != 0) )
    {
        Sound_pHS->pErrorPrint("Sound_IsThingFadingPitch: Don't know what 'sound' is: %p\n", handle);
        return false;
    }

    size_t count = Sound_numChannels;
    tSoundChannel* pCurChannel = &Sound_apChannels[Sound_numChannels];
    while ( 1 )
    {
        --pCurChannel;
        if ( !count-- )
        {
            break;
        }

        if ( pCurChannel->handle
            && (pCurChannel->flags & (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND)) != 0
            && pCurChannel->thingId == thingId
            && (!handle || pCurChannel->hSnd == handle)
            && (pCurChannel->flags & SOUND_CHANNEL_PITCHFADE) != 0 )
        {
            return true;
        }
    }

    return false;
}

static void Sound_UpdateFades(void) // Added
{
    for ( size_t i = 0; i < STD_ARRAYLEN(Sound_aFades); i++ )
    {
        SoundFade* pFade = &Sound_aFades[i];
        if ( Sound_aFades[i].hChannel )
        {
            int dtime = Sound_GetDeltaTime();
            tSoundChannel* pChannel = Sound_GetChannel(pFade->hChannel);
            if ( !pChannel )
            {
                pFade->hChannel = 0;
                continue;
            }

            if ( dtime < (int)pFade->msecEndTime )
            {
                double newValue = (pFade->endValue - pFade->startValue)
                    * (double)(dtime - pFade->msecStartTime)
                    / (double)(pFade->msecEndTime - pFade->msecStartTime)
                    + pFade->startValue;

                if ( newValue != 0.0 )
                {
                    if ( pFade->bPitch )
                    {
                        Sound_SetPitch(pFade->hChannel, (float)newValue);
                    }
                    else
                    {
                        Sound_SetVolume(pFade->hChannel, (float)newValue);
                    }

                    if ( (float)newValue == pFade->endValue )
                    {
                        pFade->hChannel = 0;
                    }
                }
            }
            else
            {
                if ( pFade->bPitch )
                {
                    Sound_SetPitch(pFade->hChannel, pFade->endValue);
                    pChannel->flags &= ~SOUND_CHANNEL_PITCHFADE;
                }
                else if ( pFade->endValue == 0.0f )
                {
                    Sound_StopChannel(pFade->hChannel);
                }
                else
                {
                    Sound_SetVolume(pFade->hChannel, pFade->endValue);
                    pChannel->flags &= ~SOUND_CHANNEL_VOLUMEFADE;
                }

                pFade->hChannel = 0;
            }
        }
    }
}

void J3DAPI Sound_Update(const rdVector3* pPos, const rdVector3* pVelocity, const rdVector3* pTopOrient, const rdVector3* pFrontOrient)
{
    // Was changed to function call
    Sound_UpdateFades();

    // Fixed: Fixed negating orient by not modifying the original pointer var
    rdVector3 topOrient;
    if ( pTopOrient && !Sound_bReverseSound )
    {
        rdVector_Neg3(&topOrient, pTopOrient);
        pTopOrient = &topOrient;
    }

    // Fixed: Fixed negating orient by not modifying the original pointer var
    rdVector3 frontOrient;
    if ( pFrontOrient && !Sound_bReverseSound )
    {
        rdVector_Neg3(&frontOrient, pFrontOrient);
        pFrontOrient = &frontOrient;
    }

    if ( pPos )
    {
        Sound_curUpdatePos = *pPos;
    }

    SoundDriver_SetListenerPosition(pPos, pVelocity, pTopOrient, pFrontOrient);

    int count = Sound_numChannels;
    tSoundChannel* pCurChannel = &Sound_apChannels[Sound_numChannels];

    while ( 1 )
    {
        --pCurChannel;
        if ( !count-- )
        {
            break;
        }

        if ( pCurChannel->handle && (pCurChannel->flags & SOUND_CHANNEL_3DSOUND) != 0 )
        {
            SoundThingInfo thngSndInfo;
            if ( (pCurChannel->flags & (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND)) != 0
                && Sound_pfGetThingInfoCallback
                && Sound_pfGetThingInfoCallback(pCurChannel->thingId, &thngSndInfo) )
            {
                pCurChannel->playPos  = thngSndInfo.pos;
                pCurChannel->envflags = thngSndInfo.envflags;

                SoundDriver_SetPosAndVelocity(
                    pCurChannel->pDSoundBuffer,
                    thngSndInfo.pos.x,
                    thngSndInfo.pos.y,
                    thngSndInfo.pos.z,
                    thngSndInfo.velocity.x,
                    thngSndInfo.velocity.y,
                    thngSndInfo.velocity.z,
                    pCurChannel->minRadius,
                    pCurChannel->maxRadius
                );
            }

            if ( !SoundDriver_Update3DSound(
                &pCurChannel->pDSoundBuffer,
                pCurChannel->playPos.x,
                pCurChannel->playPos.y,
                pCurChannel->playPos.z,
                pCurChannel->volume,
                pCurChannel->pitch,
                &pCurChannel->flags,
                pCurChannel->minRadius,
                pCurChannel->maxRadius,
                pCurChannel->envflags) )
            {
                Sound_StopChannel(pCurChannel->handle); // Fixed: Fixed bug to use correct channel handle; OG used count var
            }
            else if ( (pCurChannel->flags & SOUND_CHANNEL_RESTART) != 0 )
            {
                pCurChannel->flags |= SOUND_CHANNEL_LOOP | SOUND_CHANNEL_PLAYING;
                pCurChannel->flags &= ~SOUND_CHANNEL_FAR;

                if ( (pCurChannel->flags & (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND)) == (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND) )
                {
                    tSoundChannel channel = *pCurChannel;
                    pCurChannel->handle  = 0;
                    pCurChannel->hSnd    = 0;
                    pCurChannel->thingId = 0;
                    if ( pCurChannel->pDSoundBuffer )
                    {
                        SoundDriver_Release(pCurChannel->pDSoundBuffer);
                        pCurChannel->pDSoundBuffer = NULL;
                    }

                    tSoundChannelHandle hChannel = Sound_PlayThing(channel.hSnd, channel.volume, channel.priority, channel.flags, channel.thingId, channel.guid, channel.minRadius, channel.maxRadius);
                    if ( !hChannel )
                    {
                        Sound_pHS->pErrorPrint("Sound_Update: Error restarting distant sound.\n");
                    }
                    else
                    {
                        for ( size_t i = Sound_numChannels; i-- > 0; )
                        {
                            tSoundChannel* pChannel = &Sound_apChannels[i];
                            if ( pChannel->handle == hChannel )
                            {
                                pChannel->flags &= ~SOUND_CHANNEL_RESTART;
                                pChannel->handle = channel.handle;
                                break; // Should continue the while loop
                            }
                        }
                    }
                }
                else
                {
                    tSoundChannel channel = *pCurChannel;
                    pCurChannel->handle = 0;
                    if ( pCurChannel->pDSoundBuffer )
                    {
                        SoundDriver_Release(pCurChannel->pDSoundBuffer);
                        pCurChannel->pDSoundBuffer = NULL;
                    }

                    tSoundChannelHandle hChannel = Sound_PlayPos(
                        channel.hSnd,
                        channel.volume,
                        channel.priority,
                        channel.flags,
                        channel.playPos.x,
                        channel.playPos.y,
                        channel.playPos.z,
                        channel.guid,
                        channel.minRadius,
                        channel.maxRadius,
                        channel.envflags
                    );

                    if ( !hChannel )
                    {
                        Sound_pHS->pErrorPrint("Sound_Update: Error restarting distant sound.\n");
                    }
                    else
                    {
                        for ( size_t i = Sound_numChannels; i-- > 0; )
                        {
                            tSoundChannel* pChannel = &Sound_apChannels[i];
                            if ( pChannel->handle == hChannel )
                            {
                                pChannel->flags &= ~SOUND_CHANNEL_RESTART;
                                pChannel->handle = channel.handle;
                                break; // Should continue the while loop
                            }
                        }
                    }
                }
            }
        }
    }

    SoundDriver_ListenerCommitDeferred();

    // Remove channels that have finished playing
    if ( Sound_apChannels )
    {
        for ( size_t i = 0; i < Sound_numChannels; ++i )
        {
            pCurChannel = &Sound_apChannels[i];
            if ( pCurChannel->handle
                && (SoundDriver_GetStatusAndCaps(pCurChannel->pDSoundBuffer) & SOUND_CHANNEL_PLAYING) == 0
                && (pCurChannel->flags & SOUND_CHANNEL_PAUSED) == 0
                && (pCurChannel->flags & SOUND_CHANNEL_FAR) == 0 )
            {
                SoundDriver_Release(pCurChannel->pDSoundBuffer);
                pCurChannel->pDSoundBuffer = NULL;
                pCurChannel->handle        = 0;
                pCurChannel->hSnd          = 0;
                pCurChannel->thingId       = 0;
            }
        }
    }
}

size_t J3DAPI Sound_GetAllInstanceInfo(SoundInstanceInfo* pCurInstance, size_t sizeInstances)
{
    size_t numSounds   = 0;
    size_t numChannels = Sound_numChannels;
    tSoundChannel* pCurChannel = &Sound_apChannels[Sound_numChannels];
    while ( 1 )
    {
        --pCurChannel;
        if ( !numChannels-- )
        {
            break;
        }

        if ( pCurChannel->handle )
        {

            if ( numSounds >= sizeInstances )
            {
                Sound_pHS->pErrorPrint("Sound_GetAllInstanceInfo: Return value not big enough!\n");
                return sizeInstances;
            }

            SoundInfo* pSndInfo = Sound_soundbank_GetSoundInfo(pCurChannel->hSnd);
            if ( pSndInfo )
            {
                pCurInstance->pName = (const char*)&soundbank_apSoundCache[pSndInfo->bankNum][pSndInfo->nameOffset];
            }
            else
            {
                Sound_pHS->pErrorPrint("Sound_GetAllInstanceInfo: Unknown sound data for playing sound.\n");
                pCurInstance->pName = ">ERR:Unknown<";
            }

            pCurInstance->handle  = pCurChannel->handle;
            pCurInstance->thingId = pCurChannel->thingId;
            pCurInstance->flags   = pCurChannel->flags;
            ++pCurInstance;
            ++numSounds;
        }
    }

    return numSounds;
}

void Sound_SoundDump(void)
{
    SoundInstanceInfo aInfos[64];
    size_t numSounds = Sound_GetAllInstanceInfo(aInfos, STD_ARRAYLEN(aInfos));

    char aText[256];
    STD_FORMAT(aText, "Sound Dump of %d sounds\n", numSounds);
    Sound_pHS->pStatusPrint(aText);

    for ( size_t i = 0; i < numSounds; ++i )
    {
        char aPlayingText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_PLAYING) != 0 )
        {
            STD_FORMAT(aPlayingText, "Playing,");
        }
        else
        {
            STD_FORMAT(aPlayingText, "NotPlay,");
        }

        char aPusedText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_PAUSED) != 0 )
        {
            STD_FORMAT(aPusedText, "Paused,");
        }
        else
        {
            STD_FORMAT(aPusedText, "Not Paused,");
        }

        char aDistanceText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_FAR) != 0 )
        {
            STD_FORMAT(aDistanceText, "Far,");
        }
        else
        {
            STD_FORMAT(aDistanceText, "   ,");
        }

        char aLoopingText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_LOOP) != 0 )
        {
            STD_FORMAT(aLoopingText, "Looping,");
        }
        else
        {
            STD_FORMAT(aLoopingText, "       ,");
        }

        char aSpacialText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_3DSOUND) != 0 )
        {
            STD_FORMAT(aSpacialText, "3D,");
        }
        else
        {
            STD_FORMAT(aSpacialText, "2D,");
        }

        char aThingText[32];
        if ( (aInfos[i].flags & (SOUND_CHANNEL_THING | SOUND_CHANNEL_3DSOUND)) != 0 )
        {
            STD_FORMAT(aThingText, "Thing,");
        }
        else
        {
            STD_FORMAT(aThingText, "     ,");
        }

        char aVoldFadeText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_VOLUMEFADE) != 0 )
        {
            STD_FORMAT(aVoldFadeText, "volFade,");
        }
        else
        {
            STD_FORMAT(aVoldFadeText, "       ,");
        }

        char aPitchText[32];
        if ( (aInfos[i].flags & SOUND_CHANNEL_PITCHFADE) != 0 )
        {
            STD_FORMAT(aPitchText, "pitchFade,");
        }
        else
        {
            STD_FORMAT(aPitchText, "         ,");
        }

        STD_FORMAT(aText, "%s %d\n \t%s %s %s %s %s %s %s %s", aInfos[i].pName, aInfos[i].handle, aPlayingText, aDistanceText, aLoopingText, aSpacialText, aThingText, aVoldFadeText, aPitchText, aPusedText);
        Sound_pHS->pStatusPrint("%s\n", aText);
    }

    Sound_pHS->pStatusPrint("\n");
}