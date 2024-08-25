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
    J3D_HOOKFUNC(AudioLib_WVSMCompressBlock);
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
    memcpy((int16_t*)&AudioLib_aStepTable, &AudioLib_aStepTable_tmp, sizeof(AudioLib_aStepTable));

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
    memcpy((uint8_t*)&AudioLib_aStepBits, &AudioLib_aStepBits_tmp, sizeof(AudioLib_aStepBits));

    /* const int8_t *AudioLib_aIndexTableTable_tmp[8] = {
       NULL,
       NULL,
       &AudioLib_aIndex2Bit,
       &AudioLib_aIndex3Bit,
       &AudioLib_aIndex4Bit,
       &AudioLib_aIndex5Bit,
       &AudioLib_aIndex6Bit,
       &AudioLib_aIndex7Bit
     };
     memcpy((int8_t **)&AudioLib_aIndexTableTable, &AudioLib_aIndexTableTable_tmp, sizeof(AudioLib_aIndexTableTable));*/

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

//int J3DAPI AudioLib_WVSMCompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize, FILE* pFile)
//{
//    return J3D_TRAMPOLINE_CALL(AudioLib_WVSMCompressBlock, pOutBuffer, pInBuffer, blockSize, pFile);
//}

int J3DAPI AudioLib_WVSMUncompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize)
{
    return J3D_TRAMPOLINE_CALL(AudioLib_WVSMUncompressBlock, pOutBuffer, pInBuffer, blockSize);
}

int J3DAPI AudioLib_WVSMCompressBlock(uint8_t* pOutBuffer, const uint8_t* pInBuffer, int blockSize, FILE* pFile)
{
    const uint8_t* pInBuffer_1;
    int size_1;
    unsigned int sampleCount;
    int curLeftSamp;
    const uint8_t* v8;
    int i;
    int curRightSamp;
    int j;
    int kRight_1;
    int* pLeft;
    int kLeft;
    int* pRight;
    int rsavedBits;
    int lsavedBits_1;
    int numSlots;
    int* pRight_1;
    int* pLeft_1;
    int v21;
    int leftOffset;
    char kRight_2;
    int* v24;
    int v25;
    int* v26;
    int v27;
    const int16_t* pCurIn;
    uint8_t* pCurOut;
    int curLeftSample;
    const int16_t* pRightIn;
    int leftSampleOffseted;
    int leftSampeCompressed;
    int v34;
    uint8_t* v35;
    int curRightSampe;
    uint8_t* pRightOut;
    int rightSampleOffseted;
    int rightSampleCompressed;
    int v40;
    uint8_t* v41;
    int compressedSize;
    int kRight;
    int v44;
    unsigned int kLeft_1;
    int lsavedBits;
    int v47;
    int rightOffset;
    int leftBits[17];
    int rightBits[17];
    int blockSizea;

    pInBuffer_1 = pInBuffer;

    memset(leftBits, 0, sizeof(leftBits));

    size_1 = blockSize >> 1;
    blockSizea = size_1;

    memset(rightBits, 0, sizeof(rightBits));

    if (size_1 > 0)
    {
        int outOfBoundsLeft = 0;
        int outOfBoundsRight = 0;
        sampleCount = (unsigned int)(size_1 + 1) >> 1;

        // Note in debug version of Indy3D.exe the loop is the same only the loop range is different.
        // In debug version the loop range is defined as counter = 0; while(counter < size_1) {... counter += 2; }
        // This change still causes the rightBits or leftBits to be rad out of bounds, 
        // so the change must be somewhere else in order for the debug version to run normally
        do
        {
            curLeftSamp = *(int16_t*)pInBuffer_1;
            v8 = pInBuffer_1 + 2;
            if (curLeftSamp < 0)
            {
                curLeftSamp = -curLeftSamp;
            }

            for (i = 0; curLeftSamp; ++i) // [ADD] Fixed init i value (orig. i = 1) which caused out of bounds access
            {
                curLeftSamp >>= 1;
            }

            pInBuffer_1 = v8 + 2;

            if (i > 16) // [ADD] bound check fix
            {
                i = 16;
                outOfBoundsLeft++;
            }
            ++leftBits[i];

            curRightSamp = *((int16_t*)pInBuffer_1 - 1);
            if (curRightSamp < 0)
            {
                curRightSamp = -curRightSamp;
            }

            for (j = 0; curRightSamp; ++j) // [ADD] Fixed init j value (orig. j = 1)
            {
                curRightSamp >>= 1;
            }

            --sampleCount;

            if (j > 16) // [ADD] bound check fix
            {
                j = 16;
                outOfBoundsRight++;
            }
            ++rightBits[j];
        } while (sampleCount);

        if (outOfBoundsLeft || outOfBoundsRight)
        {
            // TODO: make separate log function var for audio lib
          /*  if (Sound_pHS) {
                Sound_pHS->logWarning("AudioLib_WVSMCompressBlock: %d left bits out of bounds, %d right bits out of bounds\n", outOfBoundsLeft, outOfBoundsRight);
            }*/
        }
    }

    kRight_1 = 8;

    pLeft = &leftBits[16];
    for (kLeft = 8; kLeft > 0; --kLeft)
    {
        if (*pLeft)
        {
            break;
        }

        --pLeft;
    }

    v44 = kLeft;

    pRight = &rightBits[16];
    do
    {
        if (*pRight)
        {
            break;
        }

        --kRight_1;
        --pRight;
    } while (kRight_1 > 0);

    rsavedBits = 0;
    lsavedBits_1 = 0;

    kRight = kRight_1;
    numSlots = 192;
    pRight_1 = &rightBits[kRight_1 + 8];
    pLeft_1 = &leftBits[kLeft + 8];
    do
    {
        if (kLeft <= 0)
        {
            if (kRight <= 0)
            {
                break;
            }

            v21 = 0;
        }

        else if (kRight <= 0)
        {
            v21 = 1;
        }
        else
        {
            v21 = *pLeft_1 < *pRight_1;
            kLeft = v44;
        }

        if (v21)
        {
            if (*pLeft_1 > numSlots)
            {
                break;
            }

            numSlots -= *pLeft_1;
            --kLeft;
            --pLeft_1;
            v44 = kLeft;
            ++lsavedBits_1;
        }
        else
        {
            if (*pRight_1 > numSlots)
            {
                break;
            }

            numSlots -= *pRight_1--;
            --kRight;
            ++rsavedBits;
        }
    } while (numSlots);

    lsavedBits = lsavedBits_1;
    if (kLeft)
    {
        leftOffset = 1 << (kLeft - 1);
        v47 = leftOffset;
    }
    else
    {
        v47 = 0;
        leftOffset = 0;
    }

    kRight_2 = kRight;
    if (kRight)
    {
        rightOffset = 1 << (kRight - 1);
    }
    else
    {
        rightOffset = 0;
    }

    if (pFile)
    {
        fprintf(pFile, "L = %4d:", kLeft);
        v24 = leftBits;
        v25 = 16;
        do
        {
            fprintf(pFile, "%4d,", *v24++);
            --v25;
        } while (v25);

        fprintf(pFile, "%4d\n", leftBits[16]);

        fprintf(pFile, "R = %4d:", kRight);
        v26 = rightBits;
        v27 = 16;
        do
        {
            fprintf(pFile, "%4d,", *v26++);
            --v27;
        } while (v27);

        fprintf(pFile, "%4d\n", rightBits[16]);

        fprintf(pFile, "%d escape slots used, %dL/%dR bits saved\n\n", 192 - numSlots, lsavedBits, rsavedBits);
        kLeft |= (v44 & 0xff);
        leftOffset = v47;
        kRight_2 = kRight;
    }

    pCurIn = (const int16_t*)pInBuffer;
    *pOutBuffer = 0;
    pOutBuffer[2] = kRight_2 + 16 * kLeft;      // assign sample expander kRight_2 | (kLeft << 4)
    pCurOut = pOutBuffer + 3;

    // compressing block
    if (blockSizea > 0)
    {
        kLeft_1 = (unsigned int)(blockSizea + 1) >> 1;// TODO: make new int var
        while (1)
        {
            curLeftSample = *pCurIn;
            pRightIn = pCurIn + 1;
            if (curLeftSample >= 0)
            {
                leftSampleOffseted = leftOffset + curLeftSample;
            }
            else
            {
                leftSampleOffseted = curLeftSample - leftOffset;
            }

            if (leftSampleOffseted < -32767)
            {
                leftSampleOffseted = -32767;
            }

            if (leftSampleOffseted > 32767)
            {
                leftSampleOffseted = 32767;
            }

            leftSampeCompressed = leftSampleOffseted >> kLeft;
            v34 = leftSampeCompressed << kLeft; // leftSampleOffseted could be used instead
            if (leftSampeCompressed > 127 || leftSampeCompressed < -127)
            {
                *pCurOut = 0x80;
                v35 = pCurOut + 1;
                *v35 = (v34 >> 8) & 0xff;
                pCurOut = v35 + 1;
                *pCurOut = v34;
            }
            else
            {
                *pCurOut = leftSampeCompressed;
            }

            curRightSampe = *pRightIn;
            pRightOut = pCurOut + 1;
            pCurIn = pRightIn + 1;
            if (curRightSampe >= 0)
            {
                rightSampleOffseted = rightOffset + curRightSampe;
            }
            else
            {
                rightSampleOffseted = curRightSampe - rightOffset;
            }

            if (rightSampleOffseted < -32767)
            {
                rightSampleOffseted = -32767;
            }

            if (rightSampleOffseted > 32767)
            {
                rightSampleOffseted = 32767;
            }

            rightSampleCompressed = rightSampleOffseted >> kRight;
            v40 = rightSampleCompressed << kRight;// rightSampleOffseted could be used instead
            if (rightSampleCompressed > 127 || rightSampleCompressed < -127)
            {
                *pRightOut = 0x80;
                v41 = pRightOut + 1;
                *v41 = (v40 >> 8) & 0xff;
                pRightOut = v41 + 1;
                *pRightOut = v40;
            }
            else
            {
                *pRightOut = rightSampleCompressed;
            }

            pCurOut = pRightOut + 1;
            if (!--kLeft_1)
            {
                break;
            }

            leftOffset = v47;
        }
    }

    compressedSize = pCurOut - pOutBuffer;

    // assign be compressed size to the begin of out block
    *pOutBuffer = (uint16_t)((uint16_t)pCurOut - (uint16_t)pOutBuffer - 2) >> 8;
    pOutBuffer[1] = (uint8_t)pCurOut - (uint8_t)pOutBuffer - 2;

    return compressedSize;
}