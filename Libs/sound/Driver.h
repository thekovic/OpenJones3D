#ifndef SOUND_DRIVER_H
#define SOUND_DRIVER_H
#include <j3dcore/j3d.h>
#include <sound/types.h>
#include <sound/RTI/addresses.h>

J3D_EXTERN_C_START

#define SoundDriver_g_bHas3DHW J3D_DECL_FAR_VAR(SoundDriver_g_bHas3DHW, int)
// extern int SoundDriver_g_bHas3DHW;

int J3DAPI SoundDriver_Open(int bNoSound3D, int bGlobalFocus, HWND hwnd, LPDIRECTSOUND pDirectSound, SoundCalcListenerSoundMixFunc pfCalcListenerSoundMix, SoundDriverGetSoundBufferDataFunc pfGetSoundBufferData, tPrintfFunc pfLogError);
void J3DAPI SoundDriver_Close();
void J3DAPI SoundDriver_SetMaxVolume(float volume);
LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_CreateAndPlay(int samplesPerSec, int nBitsPerSample, unsigned int numChannels, const uint8_t* pSoundData, int dataSize, tSoundChannelFlag* pFlags, uint8_t* pAudioPtr1);
void J3DAPI SoundDriver_Release(LPDIRECTSOUNDBUFFER pDSBuf);
void J3DAPI SoundDriver_Play(struct IDirectSoundBuffer* pDSBuf, int bLoop);
void J3DAPI SoundDriver_Stop(LPDIRECTSOUNDBUFFER pDSBuf);
void J3DAPI SoundDriver_SetVolume(LPDIRECTSOUNDBUFFER pDSBuf, float volume);
float J3DAPI SoundDriver_GetVolume(LPDIRECTSOUNDBUFFER pDSBuf);
void J3DAPI SoundDriver_SetPan(LPDIRECTSOUNDBUFFER pDSoundBuf, float pan);
void J3DAPI SoundDriver_SetFrequency(LPDIRECTSOUNDBUFFER pDSBuf, float freq);
float J3DAPI SoundDriver_GetFrequency(LPDIRECTSOUNDBUFFER pDSBuf);
int J3DAPI SoundDriver_GetCurrentPosition(LPDIRECTSOUNDBUFFER pDSoundBuf);
unsigned int J3DAPI SoundDriver_GetStatusAndCaps(LPDIRECTSOUNDBUFFER pDSBuffer);
void J3DAPI SoundDriver_SetListenerPosition(const rdVector3* pPos, const rdVector3* pVelocity, const rdVector3* pTopOrient, const rdVector3* pFrontOrient);
void J3DAPI SoundDriver_ListenerCommitDeferred();
void J3DAPI SoundDriver_SetPosAndVelocity(LPDIRECTSOUND3DBUFFER pBuffer, float x, float y, float z, float velX, float velY, float velZ, float minDistance, float maxDistance);
int J3DAPI SoundDriver_Update(LPDIRECTSOUNDBUFFER* ppDSBuf, float x, float y, float z, float volume, float pitch, tSoundChannelFlag* pChannelFlags, float minRadius, float maxRadius, SoundEnvFlags envflags);
void J3DAPI SoundDriver_SetGlobals(float distanceFactor, float minDistance, float maxDistance, float rolloffFactor, float dopplerFactor);
int J3DAPI SoundDriver_Use3DCaps();
LPDIRECTSOUND J3DAPI SoundDriver_GetDSound();
LPDIRECTSOUND J3DAPI SoundDriver_CreateDirectSound(int bNoSound3D);
void J3DAPI SoundDriver_ReleaseDirectSound(LPDIRECTSOUND pDSound);
void J3DAPI SoundDriver_CreateListener();
void J3DAPI SoundDriver_ReleaseListener();
void J3DAPI SoundDriver_SetOuputFormat(LPDIRECTSOUND pDSound, uint32_t nSamplesPerSec, unsigned int nBitsPerSample, int numChannels);
LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_GetPrimaryDSBuffer(LPDIRECTSOUND pDSound);
void J3DAPI SoundDriver_ReleasePrimaryDSBuffer();
int J3DAPI SoundDriver_GetDecibelVolume(float volume);
LONG J3DAPI SoundDriver_GetIntPan(float pan);
float J3DAPI SoundDriver_GetVolumeFromDecibels(int dB);
void J3DAPI SoundDriver_InitPanTable();
HRESULT J3DAPI SoundDriver_DSCheckStatus(HRESULT code, int codeLine);
void J3DAPI SoundDriver_CalcListeneSoundMix(float x, float y, float z, float volume, float pitch, float* newVolume, float* pan, float* newPitch, float minRadius, float maxRadius, SoundEnvFlags envflags);
double J3DAPI SoundDriver_CalcDistToListener(float x1, float y1, float z1, float x2, float y2, float z2);
void J3DAPI SoundDriver_RestoreSoundBufferData(LPDIRECTSOUNDBUFFER pDSBuf);
void J3DAPI SoundDriver_Sleep(unsigned int dwMilliseconds);

// Helper hooking functions
void Driver_InstallHooks(void);
void Driver_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SOUND_DRIVER_H
