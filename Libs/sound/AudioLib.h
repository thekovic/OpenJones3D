#ifndef SOUND_AUDIOLIB_H
#define SOUND_AUDIOLIB_H
#include <j3dcore/j3d.h>
#include <sound/types.h>
#include <sound/RTI/addresses.h>

J3D_EXTERN_C_START

// Returns pointer to snd data
uint8_t* J3DAPI AudioLib_ParseWaveFileHeader(const uint8_t* pData, int* pType, unsigned int* pSampleRate, unsigned int* pBitsPerSample, unsigned int* pNumChannels, int* a6, unsigned int* pSoundDataSize, const uint8_t** ppHeaderEnd, unsigned int* pDataOffset);
int J3DAPI AudioLib_Compress(tAudioCompressorState* pCompressorState, uint8_t* pOutBuffer, const uint8_t* pInBuffer, int size, unsigned int numChannels);
void J3DAPI AudioLib_ResetCompressor(tAudioCompressorState* pState);
void J3DAPI AudioLib_Uncompress(tAudioCompressorState* pCompressorState, uint8_t* pOutSndData, const uint8_t* pCompressedData, unsigned int size);
int J3DAPI AudioLib_GetMouthPosition(uint8_t* pData, int a2, int* pMouthPosX, int* pMouthPosY);
int J3DAPI AudioLib_GenerateLipSynchBlock(uint8_t* pOutData, const uint8_t* pSndData, unsigned int a3, char a4, char a5, int sampleRate, int bitsPerSample, int numChannels, int a9, int sndDataSize);
// ADPCM compression
int J3DAPI AudioLib_CompressBlock(tAudioCompressorState* pCompressorState, uint8_t* pOutBuffer, int16_t* a3, int a4, unsigned int numChannels, int a6, int bStateInitialized);
// ADPCM decompress
void J3DAPI AudioLib_UncompressBlock(tAudioCompressorState* pCompressorState, uint8_t* pOutData, const uint8_t* pInData, int size, unsigned int numChannels, int bStateInited);
int J3DAPI AudioLib_WVSMCompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize, FILE* pFile);
int J3DAPI AudioLib_WVSMUncompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize);

// Helper hooking functions
void AudioLib_InstallHooks(void);
void AudioLib_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SOUND_AUDIOLIB_H
