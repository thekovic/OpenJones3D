#ifndef SOUND_DRIVER_H
#define SOUND_DRIVER_H
#include <j3dcore/j3d.h>
#include <sound/types.h>
#include <sound/RTI/addresses.h>

#include <dsound.h>

J3D_EXTERN_C_START

int J3DAPI SoundDriver_Open(int bNoSound3D, int bGlobalFocus, HWND hwnd, LPDIRECTSOUND pDirectSound, SoundCalcListenerSoundMixFunc pfCalcListenerSoundMix, SoundDriverGetSoundBufferDataFunc pfGetSoundBufferData, tPrintfFunc pfLogError);
void SoundDriver_Close(void);

void J3DAPI SoundDriver_SetMaxVolume(float volume);
LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_CreateAndPlay(size_t samplesPerSec, size_t nBitsPerSample, size_t numChannels, const uint8_t* pSoundData, size_t dataSize, tSoundChannelFlag* pFlags, LPDIRECTSOUNDBUFFER pSBuffer);
void J3DAPI SoundDriver_Release(LPDIRECTSOUNDBUFFER pDSBuf);
void J3DAPI SoundDriver_Play(LPDIRECTSOUNDBUFFER pDSBuf, int bLoop);
void J3DAPI SoundDriver_Stop(LPDIRECTSOUNDBUFFER pDSBuf);

void J3DAPI SoundDriver_SetVolume(LPDIRECTSOUNDBUFFER pDSBuf, float volume);
float J3DAPI SoundDriver_GetVolume(LPDIRECTSOUNDBUFFER pDSBuf);

void J3DAPI SoundDriver_SetPan(LPDIRECTSOUNDBUFFER pDSoundBuf, float pan);
float J3DAPI SoundDriver_GetPan(LPDIRECTSOUNDBUFFER pDSBuf); // Added: From debug

void J3DAPI SoundDriver_SetFrequency(LPDIRECTSOUNDBUFFER pDSBuf, float freq);
float J3DAPI SoundDriver_GetFrequency(LPDIRECTSOUNDBUFFER pDSBuf);

int J3DAPI SoundDriver_GetCurrentPosition(LPDIRECTSOUNDBUFFER pDSoundBuf);
tSoundChannelFlag J3DAPI SoundDriver_GetStatusAndCaps(LPDIRECTSOUNDBUFFER pDSBuffer);

void J3DAPI SoundDriver_SetListenerPosition(const rdVector3* pPos, const rdVector3* pVelocity, const rdVector3* pTopOrient, const rdVector3* pFrontOrient);
void SoundDriver_ListenerCommitDeferred(void);

void J3DAPI SoundDriver_SetPosAndVelocity(LPDIRECTSOUNDBUFFER pBuffer, float x, float y, float z, float velX, float velY, float velZ, float minDistance, float maxDistance);

int J3DAPI SoundDriver_Update3DSound(LPDIRECTSOUNDBUFFER* ppDSBuf, float x, float y, float z, float volume, float pitch, tSoundChannelFlag* pChannelFlags, float minRadius, float maxRadius, SoundEnvFlags envflags);

void J3DAPI SoundDriver_SetGlobals(float distanceFactor, float minDistance, float maxDistance, float rolloffFactor, float dopplerFactor);

int SoundDriver_Has3DHW(void);
int SoundDriver_Use3DCaps(void); // Added: From debug version
LPDIRECTSOUND SoundDriver_GetDSound(void);

LPDIRECTSOUND J3DAPI SoundDriver_CreateDirectSound(int bNoSound3D);
void J3DAPI SoundDriver_ReleaseDirectSound(LPDIRECTSOUND pDSound);

void SoundDriver_CreateListener(void);
void SoundDriver_ReleaseListener(void);

void J3DAPI SoundDriver_SetOuputFormat(LPDIRECTSOUND pDSound, uint32_t nSamplesPerSec, uint32_t nBitsPerSample, uint32_t numChannels);

LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_GetPrimaryDSBuffer(LPDIRECTSOUND pDSound);
void J3DAPI SoundDriver_ReleasePrimaryDSBuffer();

int J3DAPI SoundDriver_GetDecibelVolume(float volume);
int J3DAPI SoundDriver_GetIntPan(float pan);

float J3DAPI SoundDriver_GetVolumeFromDecibels(int dB);
float J3DAPI SoundDriver_GetPanFromTable(int pan); // Added From debug

uint32_t SoundDriver_GetTimeMsec(void);
void J3DAPI SoundDriver_Sleep(unsigned int dwMilliseconds);

// Helper hooking functions
void Driver_InstallHooks(void);
void Driver_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SOUND_DRIVER_H
