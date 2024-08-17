#include "AudioLib.h"
#include <j3dcore/j3dhook.h>
#include <sound/RTI/symbols.h>

#define AudioLib_aStepTable J3D_DECL_FAR_ARRAYVAR(AudioLib_aStepTable, const int16_t(*)[89])
#define AudioLib_aStepBits J3D_DECL_FAR_ARRAYVAR(AudioLib_aStepBits, const uint8_t(*)[89])
#define AudioLib_aIndexTableTable J3D_DECL_FAR_ARRAYVAR(AudioLib_aIndexTableTable, const int8_t*(*)[8])
#define AudioLib_aDeltaTable J3D_DECL_FAR_ARRAYVAR(AudioLib_aDeltaTable, int16_t(*)[64])
#define AudioLib_word_14E4928 J3D_DECL_FAR_ARRAYVAR(AudioLib_word_14E4928, int16_t(*)[5632])
#define AudioLib_bDeltaTableInitialized J3D_DECL_FAR_VAR(AudioLib_bDeltaTableInitialized, int)

void AudioLib_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(AudioLib_ParseWaveFileHeader);
    // J3D_HOOKFUNC(AudioLib_Compress);
    // J3D_HOOKFUNC(AudioLib_ResetCompressor);
    // J3D_HOOKFUNC(AudioLib_Uncompress);
    // J3D_HOOKFUNC(AudioLib_GetMouthPosition);
    // J3D_HOOKFUNC(AudioLib_GenerateLipSynchBlock);
    // J3D_HOOKFUNC(AudioLib_CompressBlock);
    // J3D_HOOKFUNC(AudioLib_UncompressBlock);
    // J3D_HOOKFUNC(AudioLib_WVSMCompressBlock);
    // J3D_HOOKFUNC(AudioLib_WVSMUncompressBlock);
}

void AudioLib_ResetGlobals(void)
{
    const int16_t AudioLib_aStepTable_tmp[89] = {
      7,
      8,
      9,
      10,
      11,
      12,
      13,
      14,
      16,
      17,
      19,
      21,
      23,
      25,
      28,
      31,
      34,
      37,
      41,
      45,
      50,
      55,
      60,
      66,
      73,
      80,
      88,
      97,
      107,
      118,
      130,
      143,
      157,
      173,
      190,
      209,
      230,
      253,
      279,
      307,
      337,
      371,
      408,
      449,
      494,
      544,
      598,
      658,
      724,
      796,
      876,
      963,
      1060,
      1166,
      1282,
      1411,
      1552,
      1707,
      1878,
      2066,
      2272,
      2499,
      2749,
      3024,
      3327,
      3660,
      4026,
      4428,
      4871,
      5358,
      5894,
      6484,
      7132,
      7845,
      8630,
      9493,
      10442,
      11487,
      12635,
      13899,
      15289,
      16818,
      18500,
      20350,
      22385,
      24623,
      27086,
      29794,
      32767
    };
    memcpy((int16_t *)&AudioLib_aStepTable, &AudioLib_aStepTable_tmp, sizeof(AudioLib_aStepTable));
    
    const uint8_t AudioLib_aStepBits_tmp[89] = {
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      4u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      5u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      6u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u,
      7u
    };
    memcpy((uint8_t *)&AudioLib_aStepBits, &AudioLib_aStepBits_tmp, sizeof(AudioLib_aStepBits));
    
    const int8_t *AudioLib_aIndexTableTable_tmp[8] = {
      NULL,
      NULL,
      &AudioLib_aIndex2Bit,
      &AudioLib_aIndex3Bit,
      &AudioLib_aIndex4Bit,
      &AudioLib_aIndex5Bit,
      &AudioLib_aIndex6Bit,
      &AudioLib_aIndex7Bit
    };
    memcpy((int8_t **)&AudioLib_aIndexTableTable, &AudioLib_aIndexTableTable_tmp, sizeof(AudioLib_aIndexTableTable));
    
    memset(&AudioLib_aDeltaTable, 0, sizeof(AudioLib_aDeltaTable));
    memset(&AudioLib_word_14E4928, 0, sizeof(AudioLib_word_14E4928));
    memset(&AudioLib_bDeltaTableInitialized, 0, sizeof(AudioLib_bDeltaTableInitialized));
}

// Returns pointer to snd data
uint8_t* J3DAPI AudioLib_ParseWaveFileHeader(const uint8_t* pData, int* pType, unsigned int* pSampleRate, unsigned int* pBitsPerSample, unsigned int* pNumChannels, int* a6, unsigned int* pSoundDataSize, const uint8_t** ppHeaderEnd, unsigned int* pDataOffset)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_ParseWaveFileHeader, pData, pType, pSampleRate, pBitsPerSample, pNumChannels, a6, pSoundDataSize, ppHeaderEnd, pDataOffset);
}

int J3DAPI AudioLib_Compress(tAudioCompressorState* pCompressorState, uint8_t* pOutBuffer, const uint8_t* pInBuffer, int size, unsigned int numChannels)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_Compress, pCompressorState, pOutBuffer, pInBuffer, size, numChannels);
}

void J3DAPI AudioLib_ResetCompressor(tAudioCompressorState* pState)
{
    J3D_TRAMPOLINE_CALL(AudioLib_ResetCompressor, pState);
}

void J3DAPI AudioLib_Uncompress(tAudioCompressorState* pCompressorState, uint8_t* pOutSndData, const uint8_t* pCompressedData, unsigned int size)
{
    J3D_TRAMPOLINE_CALL(AudioLib_Uncompress, pCompressorState, pOutSndData, pCompressedData, size);
}

int J3DAPI AudioLib_GetMouthPosition(uint8_t* pData, int a2, int* pMouthPosX, int* pMouthPosY)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_GetMouthPosition, pData, a2, pMouthPosX, pMouthPosY);
}

int J3DAPI AudioLib_GenerateLipSynchBlock(uint8_t* pOutData, const uint8_t* pSndData, unsigned int a3, char a4, char a5, int sampleRate, int bitsPerSample, int numChannels, int a9, int sndDataSize)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_GenerateLipSynchBlock, pOutData, pSndData, a3, a4, a5, sampleRate, bitsPerSample, numChannels, a9, sndDataSize);
}

// ADPCM compression
int J3DAPI AudioLib_CompressBlock(tAudioCompressorState* pCompressorState, uint8_t* pOutBuffer, int16_t* a3, int a4, unsigned int numChannels, int a6, int bStateInitialized)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_CompressBlock, pCompressorState, pOutBuffer, a3, a4, numChannels, a6, bStateInitialized);
}

// ADPCM decompress
void J3DAPI AudioLib_UncompressBlock(tAudioCompressorState* pCompressorState, uint8_t* pOutData, const uint8_t* pInData, int size, unsigned int numChannels, int bStateInited)
{
    J3D_TRAMPOLINE_CALL(AudioLib_UncompressBlock, pCompressorState, pOutData, pInData, size, numChannels, bStateInited);
}

int J3DAPI AudioLib_WVSMCompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize, FILE* pFile)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_WVSMCompressBlock, pOutBuffer, pInBuffer, blockSize, pFile);
}

int J3DAPI AudioLib_WVSMUncompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_WVSMUncompressBlock, pOutBuffer, pInBuffer, blockSize);
}
