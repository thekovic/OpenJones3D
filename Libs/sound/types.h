#ifndef SOUND_TYPES_H
#define SOUND_TYPES_H
#include <stdint.h>
#include <Mmreg.h>
#include <dsound.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>

J3D_EXTERN_C_START

typedef enum eSoundPlayFlag
{
    SOUNDPLAY_LOOP                 = 0x1,
    SOUNDPLAY_REMOVE_AFTER_FADEOUT = 0x2,
    SOUNDPLAY_AMBIENT              = 0x4,
    SOUNDPLAY_USE_DOPPLAR_FX       = 0x8,
    SOUNDPLAY_FADEIN               = 0x10,
    SOUNDPLAY_FADEOUT              = 0x20,
    SOUNDPLAY_ABSOLUTE_POS         = 0x40,
    SOUNDPLAY_THING_POS            = 0x80,
    SOUNDPLAY_HIGH_PRIORITY        = 0x100,
    SOUNDPLAY_HIGHEST_PRIORITY     = 0x200,
    SOUNDPLAY_PLAYONCE             = 0x400,
    SOUNDPLAY_PLAYTHIGNONCE        = 0x800,
} SoundPlayFlag;

typedef enum eSoundChannelFlag J3D_ENUM_TYPE(uint32_t)
{
    SOUND_CHANNEL_PLAYING          = 0x1,
    SOUND_CHANNEL_LOOP             = 0x2,
    SOUND_CHANNEL_HWMIXING         = 0x4,
    SOUND_CHANNEL_GLOBALFOCUS      = 0x8,
    SOUND_CHANNEL_VOLUMEFADE       = 0x10,
    SOUND_CHANNEL_PITCHFADE        = 0x20,
    SOUND_CHANNEL_PLAYONCE         = 0x100,
    SOUND_CHANNEL_PLAYTHINGONCE    = 0x200,
    SOUND_CHANNEL_PAUSED           = 0x20000,
    SOUND_CHANNEL_3DSOUND          = 0x40000,
    SOUND_CHANNEL_THING            = 0x80000,
    SOUND_CHANNEL_COMPRESSED       = 0x100000,
    SOUND_CHANNEL_FAR              = 0x200000,
    SOUND_CHANNEL_SWMIXING         = 0x400000,
    SOUND_CHANNEL_UNKNOWN_800000   = 0x800000,
    SOUND_CHANNEL_RESTART          = 0x1000000,
    SOUND_CHANNEL_UNKNOWN_2000000  = 0x2000000,
    SOUND_CHANNEL_USE3DCAPS        = 0x4000000,
    SOUND_CHANNEL_UNKNOWN_8000000  = 0x8000000,
    SOUND_CHANNEL_UNKNOWN_10000000 = 0x10000000,
} tSoundChannelFlag;

typedef enum eSoundEnvFlags
{
  SOUND_ENV_UNDERWATER = 0x1,
} SoundEnvFlags;

typedef unsigned int tSoundChannelHandle;
typedef unsigned int tSoundHandle;

typedef struct sSoundThingInfo SoundThingInfo;
typedef struct sSoundSpatialInfo SoundSpatialInfo;

typedef int (J3DAPI *SoundGetThingInfoCallback)(int thingID, SoundThingInfo *pInfo);
typedef void (J3DAPI *SoundCalcListenerSoundMixFunc)(const SoundSpatialInfo *, float *volume, float *pan, float *pitch);
typedef uint8_t *(J3DAPI *SoundDriverGetSoundBufferDataFunc)(LPDIRECTSOUNDBUFFER pDSBuf, unsigned int *pSoundDataSize, unsigned int *pbCompressed);


typedef struct sSoundInfo
{
    tSoundHandle hSnd;
    unsigned int bankNum;
    unsigned int filePathOffset;
    unsigned int nameOffset;
    unsigned int dataOffset;
    uint8_t *pLipSyncData;
    unsigned int sampleRate;
    unsigned int sempleBitSize;
    unsigned int numChannels;
    unsigned int dataSize;
    unsigned int bCompressed;
    unsigned int idx;
} SoundInfo;

typedef struct sSoundChannel
{
    tSoundChannelHandle handle;
    int priority;
    tSoundHandle hSnd;
    int thingId;
    LPDIRECTSOUNDBUFFER pDSoundBuffer;
    rdVector3 playPos;
    float volume;
    float pitch;
    float sampleRate;
    tSoundChannelFlag flags;
    SoundEnvFlags envflags;
    int guid;
    float minRadius;
    float maxRadius;
} tSoundChannel;

typedef struct sSoundFade
{
    tSoundChannelHandle hChannel;
    int bPitch;
    float startValue;
    float endValue;
    unsigned int msecStartTime;
    unsigned int msecEndTime;
} SoundFade;

struct sSoundThingInfo
{
    rdVector3 pos;
    rdVector3 velocity;
    SoundEnvFlags envflags;
};

typedef struct sAudioCompressorState
{
    uint8_t unknown0;
    uint8_t unknown1;
    int16_t unknown2;
    int16_t unknown3;
    int16_t unknown4;
} tAudioCompressorState;

struct sSoundSpatialInfo
{
  rdVector3 pos;
  int unknown1;
  int unknown2;
  int unknown3;
  float minRadius;
  float maxRadius;
  float volume;
  float pitch;
  SoundEnvFlags flags;
};


J3D_EXTERN_C_END
#endif //SOUND_TYPES_H
