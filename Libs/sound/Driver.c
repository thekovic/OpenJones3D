#include "Driver.h"
#include <j3dcore/j3dhook.h>
#include <sound/RTI/symbols.h>

#define SoundDriver_aDBTable J3D_DECL_FAR_ARRAYVAR(SoundDriver_aDBTable, const int(*)[256])
#define SoundDriver_aDStatusTbl J3D_DECL_FAR_ARRAYVAR(SoundDriver_aDStatusTbl, const DXStatus(*)[16])
#define SoundDriver_maxVolume J3D_DECL_FAR_VAR(SoundDriver_maxVolume, float)
#define SoundDriver_minDistance J3D_DECL_FAR_VAR(SoundDriver_minDistance, float)
#define SoundDriver_maxDistance J3D_DECL_FAR_VAR(SoundDriver_maxDistance, float)
#define SoundDriver_defaultRolloffFactor J3D_DECL_FAR_VAR(SoundDriver_defaultRolloffFactor, float)
#define SoundDriver_defaultDopplerFactor J3D_DECL_FAR_VAR(SoundDriver_defaultDopplerFactor, float)
#define SoundDriver_pfLogError J3D_DECL_FAR_VAR(SoundDriver_pfLogError, tPrintfFunc)
#define SoundDriver_aPanTable J3D_DECL_FAR_ARRAYVAR(SoundDriver_aPanTable, int(*)[256])
#define SoundDriver_frontOrientATan J3D_DECL_FAR_VAR(SoundDriver_frontOrientATan, float)
#define SoundDriver_bNoDSound3D J3D_DECL_FAR_VAR(SoundDriver_bNoDSound3D, int)
#define SoundDriver_bUseGlobalFocusBuf J3D_DECL_FAR_VAR(SoundDriver_bUseGlobalFocusBuf, int)
#define SoundDriver_hwnd J3D_DECL_FAR_VAR(SoundDriver_hwnd, HWND)
#define SoundDriver_bDSoundNotCreated J3D_DECL_FAR_VAR(SoundDriver_bDSoundNotCreated, int)
#define SoundDriver_pfCalcListenerSoundMix J3D_DECL_FAR_VAR(SoundDriver_pfCalcListenerSoundMix, SoundCalcListenerSoundMixFunc)
#define SoundDriver_pfGetSoundBufferData J3D_DECL_FAR_VAR(SoundDriver_pfGetSoundBufferData, SoundDriverGetSoundBufferDataFunc)
#define SoundDriver_pDirectSound J3D_DECL_FAR_VAR(SoundDriver_pDirectSound, LPDIRECTSOUND)
#define SoundDriver_pDSBuffer J3D_DECL_FAR_VAR(SoundDriver_pDSBuffer, LPDIRECTSOUNDBUFFER)
#define SoundDriver_pDS3DListener J3D_DECL_FAR_VAR(SoundDriver_pDS3DListener, LPDIRECTSOUND3DLISTENER)
#define SoundDriver_curListenerPos J3D_DECL_FAR_VAR(SoundDriver_curListenerPos, rdVector3)
#define SoundDriver_bUse3DCaps J3D_DECL_FAR_VAR(SoundDriver_bUse3DCaps, int)

void Driver_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(SoundDriver_Open);
    // J3D_HOOKFUNC(SoundDriver_Close);
    // J3D_HOOKFUNC(SoundDriver_SetMaxVolume);
    // J3D_HOOKFUNC(SoundDriver_CreateAndPlay);
    // J3D_HOOKFUNC(SoundDriver_Release);
    // J3D_HOOKFUNC(SoundDriver_Play);
    // J3D_HOOKFUNC(SoundDriver_Stop);
    // J3D_HOOKFUNC(SoundDriver_SetVolume);
    // J3D_HOOKFUNC(SoundDriver_GetVolume);
    // J3D_HOOKFUNC(SoundDriver_SetPan);
    // J3D_HOOKFUNC(SoundDriver_SetFrequency);
    // J3D_HOOKFUNC(SoundDriver_GetFrequency);
    // J3D_HOOKFUNC(SoundDriver_GetCurrentPosition);
    // J3D_HOOKFUNC(SoundDriver_GetStatusAndCaps);
    // J3D_HOOKFUNC(SoundDriver_SetListenerPosition);
    // J3D_HOOKFUNC(SoundDriver_ListenerCommitDeferred);
    // J3D_HOOKFUNC(SoundDriver_SetPosAndVelocity);
    // J3D_HOOKFUNC(SoundDriver_Update);
    // J3D_HOOKFUNC(SoundDriver_SetGlobals);
    // J3D_HOOKFUNC(SoundDriver_Use3DCaps);
    // J3D_HOOKFUNC(SoundDriver_GetDSound);
    // J3D_HOOKFUNC(SoundDriver_CreateDirectSound);
    // J3D_HOOKFUNC(SoundDriver_ReleaseDirectSound);
    // J3D_HOOKFUNC(SoundDriver_CreateListener);
    // J3D_HOOKFUNC(SoundDriver_ReleaseListener);
    // J3D_HOOKFUNC(SoundDriver_SetOuputFormat);
    // J3D_HOOKFUNC(SoundDriver_GetPrimaryDSBuffer);
    // J3D_HOOKFUNC(SoundDriver_ReleasePrimaryDSBuffer);
    // J3D_HOOKFUNC(SoundDriver_GetDecibelVolume);
    // J3D_HOOKFUNC(SoundDriver_GetIntPan);
    // J3D_HOOKFUNC(SoundDriver_GetVolumeFromDecibels);
    // J3D_HOOKFUNC(SoundDriver_InitPanTable);
    // J3D_HOOKFUNC(SoundDriver_DSCheckStatus);
    // J3D_HOOKFUNC(SoundDriver_CalcListeneSoundMix);
    // J3D_HOOKFUNC(SoundDriver_CalcDistToListener);
    // J3D_HOOKFUNC(SoundDriver_RestoreSoundBufferData);
    // J3D_HOOKFUNC(SoundDriver_Sleep);
}

void Driver_ResetGlobals(void)
{
    const int SoundDriver_aDBTable_tmp[256] = {
      -9640,
      -4810,
      -4210,
      -3850,
      -3600,
      -3410,
      -3250,
      -3120,
      -3000,
      -2900,
      -2810,
      -2730,
      -2650,
      -2580,
      -2520,
      -2460,
      -2400,
      -2350,
      -2300,
      -2250,
      -2210,
      -2160,
      -2120,
      -2080,
      -2050,
      -2010,
      -1980,
      -1950,
      -1910,
      -1880,
      -1850,
      -1830,
      -1800,
      -1770,
      -1750,
      -1720,
      -1700,
      -1670,
      -1650,
      -1630,
      -1600,
      -1580,
      -1560,
      -1540,
      -1520,
      -1500,
      -1480,
      -1460,
      -1450,
      -1430,
      -1410,
      -1390,
      -1380,
      -1360,
      -1340,
      -1330,
      -1310,
      -1300,
      -1280,
      -1270,
      -1250,
      -1240,
      -1220,
      -1210,
      -1200,
      -1180,
      -1170,
      -1160,
      -1140,
      -1130,
      -1120,
      -1110,
      -1090,
      -1080,
      -1070,
      -1060,
      -1050,
      -1040,
      -1020,
      -1010,
      -1000,
      -990,
      -980,
      -970,
      -960,
      -950,
      -940,
      -930,
      -920,
      -910,
      -900,
      -890,
      -880,
      -870,
      -860,
      -850,
      -840,
      -830,
      -830,
      -820,
      -810,
      -800,
      -790,
      -780,
      -770,
      -770,
      -760,
      -750,
      -740,
      -730,
      -730,
      -720,
      -710,
      -700,
      -690,
      -690,
      -680,
      -670,
      -660,
      -660,
      -650,
      -640,
      -640,
      -630,
      -620,
      -610,
      -610,
      -600,
      -590,
      -590,
      -580,
      -570,
      -570,
      -560,
      -550,
      -550,
      -540,
      -530,
      -530,
      -520,
      -520,
      -510,
      -500,
      -500,
      -490,
      -490,
      -480,
      -470,
      -470,
      -460,
      -460,
      -450,
      -440,
      -440,
      -430,
      -430,
      -420,
      -420,
      -410,
      -410,
      -400,
      -390,
      -390,
      -380,
      -380,
      -370,
      -370,
      -360,
      -360,
      -350,
      -350,
      -340,
      -340,
      -330,
      -330,
      -320,
      -320,
      -310,
      -310,
      -300,
      -300,
      -290,
      -290,
      -280,
      -280,
      -270,
      -270,
      -260,
      -260,
      -260,
      -250,
      -250,
      -240,
      -240,
      -230,
      -230,
      -220,
      -220,
      -210,
      -210,
      -210,
      -200,
      -200,
      -190,
      -190,
      -180,
      -180,
      -180,
      -170,
      -170,
      -160,
      -160,
      -160,
      -150,
      -150,
      -140,
      -140,
      -140,
      -130,
      -130,
      -120,
      -120,
      -120,
      -110,
      -110,
      -100,
      -100,
      -100,
      -90,
      -90,
      -80,
      -80,
      -80,
      -70,
      -70,
      -70,
      -60,
      -60,
      -50,
      -50,
      -50,
      -40,
      -40,
      -40,
      -30,
      -30,
      -30,
      -20,
      -20,
      -20,
      -10,
      -10,
      -10,
      -10,
      -10,
      -10
    };
    memcpy((int*)&SoundDriver_aDBTable, &SoundDriver_aDBTable_tmp, sizeof(SoundDriver_aDBTable));

    const DXStatus SoundDriver_aDStatusTbl_tmp[16] = {
      { -2005401590, "DSERR_ALLOCATED" },
      { -2005401470, "DSERR_ALREADYINITIALIZED" },
      { -2005401500, "DSERR_BADFORMAT" },
      { -2005401450, "DSERR_BUFFERLOST" },
      { -2005401570, "DSERR_CONTROLUNAVAIL" },
      { -2147467259, "DSERR_GENERIC" },
      { -2005401550, "DSERR_INVALIDCALL" },
      { -2147024809, "DSERR_INVALIDPARAM" },
      { -2147221232, "DSERR_NOAGGREGATION" },
      { -2005401480, "DSERR_NODRIVER" },
      { -2005401440, "DSERR_OTHERAPPHASPRIO" },
      { -2147024882, "DSERR_OUTOFMEMORY" },
      { -2005401530, "DSERR_PRIOLEVELNEEDED" },
      { -2005401430, "DSERR_UNINITIALIZED" },
      { -2147467263, "DSERR_UNSUPPORTED" },
      { 0, "Unknown error code." }
    };
    memcpy((DXStatus*)&SoundDriver_aDStatusTbl, &SoundDriver_aDStatusTbl_tmp, sizeof(SoundDriver_aDStatusTbl));

    float SoundDriver_maxVolume_tmp = 1.0f;
    memcpy(&SoundDriver_maxVolume, &SoundDriver_maxVolume_tmp, sizeof(SoundDriver_maxVolume));

    float SoundDriver_minDistance_tmp = 15.0f;
    memcpy(&SoundDriver_minDistance, &SoundDriver_minDistance_tmp, sizeof(SoundDriver_minDistance));

    float SoundDriver_maxDistance_tmp = 10000.0f;
    memcpy(&SoundDriver_maxDistance, &SoundDriver_maxDistance_tmp, sizeof(SoundDriver_maxDistance));

    float SoundDriver_defaultRolloffFactor_tmp = 1.0f;
    memcpy(&SoundDriver_defaultRolloffFactor, &SoundDriver_defaultRolloffFactor_tmp, sizeof(SoundDriver_defaultRolloffFactor));

    float SoundDriver_defaultDopplerFactor_tmp = 1.0f;
    memcpy(&SoundDriver_defaultDopplerFactor, &SoundDriver_defaultDopplerFactor_tmp, sizeof(SoundDriver_defaultDopplerFactor));

    memset(&SoundDriver_pfLogError, 0, sizeof(SoundDriver_pfLogError));
    memset(&SoundDriver_aPanTable, 0, sizeof(SoundDriver_aPanTable));
    memset(&SoundDriver_frontOrientATan, 0, sizeof(SoundDriver_frontOrientATan));
    memset(&SoundDriver_bNoDSound3D, 0, sizeof(SoundDriver_bNoDSound3D));
    memset(&SoundDriver_bUseGlobalFocusBuf, 0, sizeof(SoundDriver_bUseGlobalFocusBuf));
    memset(&SoundDriver_hwnd, 0, sizeof(SoundDriver_hwnd));
    memset(&SoundDriver_bDSoundNotCreated, 0, sizeof(SoundDriver_bDSoundNotCreated));
    memset(&SoundDriver_pfCalcListenerSoundMix, 0, sizeof(SoundDriver_pfCalcListenerSoundMix));
    memset(&SoundDriver_pfGetSoundBufferData, 0, sizeof(SoundDriver_pfGetSoundBufferData));
    memset(&SoundDriver_pDirectSound, 0, sizeof(SoundDriver_pDirectSound));
    memset(&SoundDriver_pDSBuffer, 0, sizeof(SoundDriver_pDSBuffer));
    memset(&SoundDriver_pDS3DListener, 0, sizeof(SoundDriver_pDS3DListener));
    memset(&SoundDriver_curListenerPos, 0, sizeof(SoundDriver_curListenerPos));
    memset(&SoundDriver_bUse3DCaps, 0, sizeof(SoundDriver_bUse3DCaps));
    memset(&SoundDriver_g_bHas3DHW, 0, sizeof(SoundDriver_g_bHas3DHW));
}

int J3DAPI SoundDriver_Open(int bNoSound3D, int bGlobalFocus, HWND hwnd, LPDIRECTSOUND pDirectSound, SoundCalcListenerSoundMixFunc pfCalcListenerSoundMix, SoundDriverGetSoundBufferDataFunc pfGetSoundBufferData, tPrintfFunc pfLogError)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_Open, bNoSound3D, bGlobalFocus, hwnd, pDirectSound, pfCalcListenerSoundMix, pfGetSoundBufferData, pfLogError);
}

void J3DAPI SoundDriver_Close()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_Close);
}

void J3DAPI SoundDriver_SetMaxVolume(float volume)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetMaxVolume, volume);
}

LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_CreateAndPlay(int samplesPerSec, int nBitsPerSample, unsigned int numChannels, const uint8_t* pSoundData, int dataSize, tSoundChannelFlag* pFlags, uint8_t* pAudioPtr1)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_CreateAndPlay, samplesPerSec, nBitsPerSample, numChannels, pSoundData, dataSize, pFlags, pAudioPtr1);
}

void J3DAPI SoundDriver_Release(LPDIRECTSOUNDBUFFER pDSBuf)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_Release, pDSBuf);
}

void J3DAPI SoundDriver_Play(struct IDirectSoundBuffer* pDSBuf, int bLoop)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_Play, pDSBuf, bLoop);
}

void J3DAPI SoundDriver_Stop(LPDIRECTSOUNDBUFFER pDSBuf)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_Stop, pDSBuf);
}

void J3DAPI SoundDriver_SetVolume(LPDIRECTSOUNDBUFFER pDSBuf, float volume)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetVolume, pDSBuf, volume);
}

float J3DAPI SoundDriver_GetVolume(LPDIRECTSOUNDBUFFER pDSBuf)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetVolume, pDSBuf);
}

void J3DAPI SoundDriver_SetPan(LPDIRECTSOUNDBUFFER pDSoundBuf, float pan)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetPan, pDSoundBuf, pan);
}

void J3DAPI SoundDriver_SetFrequency(LPDIRECTSOUNDBUFFER pDSBuf, float freq)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetFrequency, pDSBuf, freq);
}

float J3DAPI SoundDriver_GetFrequency(LPDIRECTSOUNDBUFFER pDSBuf)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetFrequency, pDSBuf);
}

int J3DAPI SoundDriver_GetCurrentPosition(LPDIRECTSOUNDBUFFER pDSoundBuf)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetCurrentPosition, pDSoundBuf);
}

unsigned int J3DAPI SoundDriver_GetStatusAndCaps(LPDIRECTSOUNDBUFFER pDSBuffer)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetStatusAndCaps, pDSBuffer);
}

void J3DAPI SoundDriver_SetListenerPosition(const rdVector3* pPos, const rdVector3* pVelocity, const rdVector3* pTopOrient, const rdVector3* pFrontOrient)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetListenerPosition, pPos, pVelocity, pTopOrient, pFrontOrient);
}

void J3DAPI SoundDriver_ListenerCommitDeferred()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_ListenerCommitDeferred);
}

void J3DAPI SoundDriver_SetPosAndVelocity(LPDIRECTSOUNDBUFFER pBuffer, float x, float y, float z, float velX, float velY, float velZ, float minDistance, float maxDistance)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetPosAndVelocity, pBuffer, x, y, z, velX, velY, velZ, minDistance, maxDistance);
}

int J3DAPI SoundDriver_Update(LPDIRECTSOUNDBUFFER* ppDSBuf, float x, float y, float z, float volume, float pitch, tSoundChannelFlag* pChannelFlags, float minRadius, float maxRadius, SoundEnvFlags envflags)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_Update, ppDSBuf, x, y, z, volume, pitch, pChannelFlags, minRadius, maxRadius, envflags);
}

void J3DAPI SoundDriver_SetGlobals(float distanceFactor, float minDistance, float maxDistance, float rolloffFactor, float dopplerFactor)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetGlobals, distanceFactor, minDistance, maxDistance, rolloffFactor, dopplerFactor);
}

int J3DAPI SoundDriver_Use3DCaps()
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_Use3DCaps);
}

LPDIRECTSOUND J3DAPI SoundDriver_GetDSound()
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetDSound);
}

LPDIRECTSOUND J3DAPI SoundDriver_CreateDirectSound(int bNoSound3D)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_CreateDirectSound, bNoSound3D);
}

void J3DAPI SoundDriver_ReleaseDirectSound(LPDIRECTSOUND pDSound)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_ReleaseDirectSound, pDSound);
}

void J3DAPI SoundDriver_CreateListener()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_CreateListener);
}

void J3DAPI SoundDriver_ReleaseListener()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_ReleaseListener);
}

void J3DAPI SoundDriver_SetOuputFormat(LPDIRECTSOUND pDSound, uint32_t nSamplesPerSec, unsigned int nBitsPerSample, int numChannels)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_SetOuputFormat, pDSound, nSamplesPerSec, nBitsPerSample, numChannels);
}

LPDIRECTSOUNDBUFFER J3DAPI SoundDriver_GetPrimaryDSBuffer(LPDIRECTSOUND pDSound)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetPrimaryDSBuffer, pDSound);
}

void J3DAPI SoundDriver_ReleasePrimaryDSBuffer()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_ReleasePrimaryDSBuffer);
}

int J3DAPI SoundDriver_GetDecibelVolume(float volume)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetDecibelVolume, volume);
}

LONG J3DAPI SoundDriver_GetIntPan(float pan)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetIntPan, pan);
}

float J3DAPI SoundDriver_GetVolumeFromDecibels(int dB)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_GetVolumeFromDecibels, dB);
}

void J3DAPI SoundDriver_InitPanTable()
{
    J3D_TRAMPOLINE_CALL(SoundDriver_InitPanTable);
}

HRESULT J3DAPI SoundDriver_DSCheckStatus(HRESULT code, int codeLine)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_DSCheckStatus, code, codeLine);
}

void J3DAPI SoundDriver_CalcListeneSoundMix(float x, float y, float z, float volume, float pitch, float* newVolume, float* pan, float* newPitch, float minRadius, float maxRadius, SoundEnvFlags envflags)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_CalcListeneSoundMix, x, y, z, volume, pitch, newVolume, pan, newPitch, minRadius, maxRadius, envflags);
}

double J3DAPI SoundDriver_CalcDistToListener(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return J3D_TRAMPOLINE_CALL(SoundDriver_CalcDistToListener, x1, y1, z1, x2, y2, z2);
}

void J3DAPI SoundDriver_RestoreSoundBufferData(LPDIRECTSOUNDBUFFER pDSBuf)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_RestoreSoundBufferData, pDSBuf);
}

void J3DAPI SoundDriver_Sleep(unsigned int dwMilliseconds)
{
    J3D_TRAMPOLINE_CALL(SoundDriver_Sleep, dwMilliseconds);
}
