#include "sithVoice.h"
#include <j3dcore/j3dhook.h>

#include <sith/Cog/sithCog.h>
#include <sith/Cog/sithCogExec.h>
#include <sith/Devices/sithComm.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/Dss/sithDSS.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Main/sithString.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithThing.h>

#include <rdroid/Engine/rdCamera.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Primitives/rdFont.h>

#include <sound/Sound.h>

#include <std/General/stdMemory.h>
#include <std/General/stdPlatform.h>
#include <std/General/stdUtil.h>
#include <std/Win95/stdDisplay.h>

#include <w32util/wuRegistry.h>

#define SITHVOICE_MSEC_EXTRA_SUBTITLE_SHOW_DURATION  1000
#define SITHVOICE_MAX_LINES_PER_DRAW                 3    // number of lines to draw

#define SITHVOICE_TEXT_PADDING_X 24.0f
#define SITHVOICE_REF_WIDTH     (RD_REF_WIDTH * RD_REF_WIDTH)
static_assert(SITHVOICE_REF_WIDTH == 409600.0f, "SITHVOICE_REF_WIDTH == 409600.f");

#define SITHVOICE_TEXT_PADDING_Y 12.0f
#define SITHVOICE_REF_HEIGHT     (RD_REF_HEIGHT * RD_REF_HEIGHT)
static_assert(SITHVOICE_REF_HEIGHT == 230400.0f, "SITHVOICE_REF_WIDTH == 409600.f");

#define SITHVOICE_FONTFILENAME "mat\\jonesCalisto MT20.gcf"

static bool sithVoice_bStartup = false; // Added: Init to 0
static bool sithVoice_bOpen    = false; // Added: Init to 0

static bool sithVoice_bShowText;
static bool sithVoice_bThingHasSwapHead;

static int sithVoice_dword_52B9A8  = 50; // this is some offset when calculating head pos from lypsync data

static int sithVoice_curHeadHeight;
static int sithVoice_lastHeadHeight = -1;
static size_t sithVoice_sameHeadHightCounter;

static float sithVoice_secHeadSwapInterval = 0.1f;
static uint8_t sithVoice_aVoiceHeadHeights[4][4];
static float sithVoice_secNextHeadSwapTime;

static size_t sithVoice_curSubtitleInfoNum;
static size_t sithVoice_numSubtitleInfos;
static SithVoiceSubtitleInfo sithVoice_aSubtitleInfos[25];

static rdFont* sithVoice_pTextFont;

void J3DAPI sithVoice_PlayVoice(SithCog* pCog);
void J3DAPI sithVoice_SetThingVoiceHeads(SithCog* pCog);
void J3DAPI sithVoice_SetVoiceHeadHeight(SithCog* pCog);
void J3DAPI sithVoice_SetThingVoiceColor(SithCog* pCog);
void J3DAPI sithVoice_SetVoiceParams(SithCog* pCog);

void J3DAPI sithVoice_AddSubtitle(unsigned int msecSoundLen, const char* pVoiceSoundFileName, const char* pVoiceSubtitles, VGradiantColor* pVoiceSubtitleColor);
void sithVoice_PurgeDrawnSubtitles(void);

void sithVoice_InstallHooks(void)
{
    J3D_HOOKFUNC(sithVoice_Startup);
    J3D_HOOKFUNC(sithVoice_Open);
    J3D_HOOKFUNC(sithVoice_Shutdown);
    J3D_HOOKFUNC(sithVoice_Close);
    J3D_HOOKFUNC(sithVoice_RegisterCogFunctions);
    J3D_HOOKFUNC(sithVoice_PlayThingVoice);
    J3D_HOOKFUNC(sithVoice_UpdateLipSync);
    J3D_HOOKFUNC(sithVoice_PlayVoice);
    J3D_HOOKFUNC(sithVoice_SetThingVoiceHeads);
    J3D_HOOKFUNC(sithVoice_SetVoiceHeadHeight);
    J3D_HOOKFUNC(sithVoice_SetThingVoiceColor);
    J3D_HOOKFUNC(sithVoice_SetVoiceParams);
    J3D_HOOKFUNC(sithVoice_GetShowText);
    J3D_HOOKFUNC(sithVoice_ShowText);
    J3D_HOOKFUNC(sithVoice_AddSubtitle);
    J3D_HOOKFUNC(sithVoice_PurgeDrawnSubtitles);
    J3D_HOOKFUNC(sithVoice_Draw);
    J3D_HOOKFUNC(sithVoice_SyncVoiceState);
    J3D_HOOKFUNC(sithVoice_ProcessVoiceState);
    J3D_HOOKFUNC(sithVoice_GetTextFont);
}

void sithVoice_ResetGlobals(void)
{
}

int sithVoice_Startup(void)
{
    // Added:
    if ( sithVoice_bStartup )
    {
        // TODO: Maybe add log
        return 0;
    }

    sithVoice_pTextFont = NULL;
    sithVoice_bShowText = wuRegistry_GetIntEx("Show Text", 0) == 1;
    sithVoice_bStartup  = true;
    return 1;
}

void sithVoice_Shutdown(void)
{
    // Added:
    if ( !sithVoice_bStartup )
    {
        // TODO: Maybe add log
        return;
    }

    sithVoice_Close(); // Added: Make sure the system was closed which will also release any allocated resources (prevent memory leak)
    sithVoice_pTextFont = NULL;
    sithVoice_bStartup  = false;
}

int sithVoice_Open(void)
{
    // Added:
    if ( sithVoice_bOpen )
    {
        // TODO: Maybe add log
        return 0;
    }

    sithVoice_pTextFont = rdFont_Load(SITHVOICE_FONTFILENAME);
    if ( !sithVoice_pTextFont )
    {
        sithVoice_Close();
        sithVoice_bOpen = false;
        return 0;
    }

    memset(sithVoice_aSubtitleInfos, 0, sizeof(sithVoice_aSubtitleInfos));
    sithVoice_curSubtitleInfoNum = 0;
    sithVoice_numSubtitleInfos   = 0;

    sithVoice_bThingHasSwapHead = false; // Added: Init to false
    sithVoice_bOpen = true;
    return 1;
}

void sithVoice_Close(void)
{
    // Added:
    if ( !sithVoice_bOpen )
    {
        // TODO: Maybe add log
        return;
    }

    if ( sithVoice_pTextFont )
    {
        rdFont_Free(sithVoice_pTextFont);
        sithVoice_pTextFont = NULL;
    }

    memset(sithVoice_aSubtitleInfos, 0, sizeof(sithVoice_aSubtitleInfos));
    sithVoice_curSubtitleInfoNum = 0;
    sithVoice_numSubtitleInfos   = 0;
    sithVoice_bOpen = false;
}

int J3DAPI sithVoice_RegisterCogFunctions(SithCogSymbolTable* pTable)
{
    return sithCog_RegisterFunction(pTable, sithVoice_PlayVoice, "playvoice")
        || sithCog_RegisterFunction(pTable, sithVoice_SetThingVoiceHeads, "setthingvoiceheads")
        || sithCog_RegisterFunction(pTable, sithVoice_SetThingVoiceColor, "setthingvoicecolor")
        || sithCog_RegisterFunction(pTable, sithVoice_SetVoiceParams, "setvoiceparams")
        || sithCog_RegisterFunction(pTable, sithVoice_SetVoiceHeadHeight, "setvoiceheadheight");
}

int J3DAPI sithVoice_PlayThingVoice(SithThing* pThing, tSoundHandle hSnd, float volume)
{
    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));

    SithActorVoiceInfo* pVoiceInfo = &pThing->thingInfo.actorInfo.voiceInfo;
    int hSndChannel = pVoiceInfo->hSndChannel;
    if ( hSndChannel )
    {
        sithSoundMixer_StopSound(hSndChannel);
    }

    pVoiceInfo->voiceHeadInfo.headSwapRefNum = -1;
    sithVoice_secNextHeadSwapTime = 0.0f;

    if ( pThing->pSwapList )
    {
        for ( SithThingSwapEntry* pSwapEntry = pThing->pSwapList; pSwapEntry; pSwapEntry = pSwapEntry->pNextEntry )
        {
            if ( strncmp(pSwapEntry->pSrcModel->aName, "head", 4u) == 0 )
            {
                sithVoice_bThingHasSwapHead = true;
                break;
            }
        }
    }

    // Set voice line subtitle text
    const char* pFilename = Sound_GetSoundFilename(hSnd);
    if ( pFilename )
    {
        char aFilename[64];
        STD_STRCPY(aFilename, pFilename);
        stdUtil_ToUpper(aFilename);
        // _strupr(aFilename);

        wchar_t* pwVoiceLine = sithString_GetString(aFilename);
        if ( pwVoiceLine )
        {
            char* pVoiceLine = stdUtil_ToAString(pwVoiceLine);
            if ( pVoiceLine )
            {
                unsigned int sndLength = Sound_GetLengthMsec(hSnd);
                sithVoice_AddSubtitle(sndLength, aFilename, pVoiceLine, &pVoiceInfo->voiceColor);
                stdMemory_Free(pVoiceLine);
            }
        }
    }

    // Reset head swap stuff as the lip sync works per single speaker only
    sithVoice_lastHeadHeight       = -1;
    sithVoice_sameHeadHightCounter = 0;

    // Play thing voice line
    pVoiceInfo->hSndChannel = sithSoundMixer_PlaySound(hSnd, volume, 0.0f, SOUNDPLAY_PLAYONCE | SOUNDPLAY_THING_POS);;
    return pVoiceInfo->hSndChannel == 0;
}

void J3DAPI sithVoice_UpdateLipSync(SithThing* pThing)
{
    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));

    SithActorVoiceInfo* pVoiceInfo = &pThing->thingInfo.actorInfo.voiceInfo;
    if ( pVoiceInfo->hSndChannel )
    {
        if ( (pThing->flags & (SITH_TF_DYING | SITH_TF_DESTROYED)) != 0 )
        {
            Sound_StopChannel(pVoiceInfo->hSndChannel);
        }

        uint8_t mouthPosX, mouthPosY;
        int bSyncData = Sound_GenerateLipSync(pVoiceInfo->hSndChannel, &mouthPosX, &mouthPosY, sithVoice_dword_52B9A8);
        if ( bSyncData )
        {
            if ( sithVoice_secNextHeadSwapTime < (double)sithTime_g_secGameTime )
            {
                sithVoice_curHeadHeight = sithVoice_aVoiceHeadHeights[mouthPosY / 32][mouthPosX / 32];// >> 5 = / 32
                if ( sithVoice_curHeadHeight == sithVoice_lastHeadHeight )
                {
                    if ( ++sithVoice_sameHeadHightCounter >= 2 )
                    {
                        switch ( sithVoice_curHeadHeight )
                        {
                            case 1:
                                sithVoice_curHeadHeight = 3;
                                break;

                            case 2:
                                sithVoice_curHeadHeight = 0;
                                break;

                            case 3:
                                sithVoice_curHeadHeight = 1;
                                break;

                            default:
                                break;
                        }

                        sithVoice_sameHeadHightCounter = 0;
                    }
                }
                else
                {
                    sithVoice_sameHeadHightCounter = 0;
                }

                sithVoice_lastHeadHeight = sithVoice_curHeadHeight;
                if ( pVoiceInfo->voiceHeadInfo.apSoundHeadModels[sithVoice_curHeadHeight] )
                {
                    int refNum = sithThing_AddSwapEntry(pThing, pVoiceInfo->voiceHeadInfo.headMeshNum, pVoiceInfo->voiceHeadInfo.apSoundHeadModels[sithVoice_curHeadHeight], 0);
                    pVoiceInfo->voiceHeadInfo.headSwapRefNum = refNum;
                }
                else if ( pVoiceInfo->voiceHeadInfo.headSwapRefNum != -1 )
                {
                    sithThing_RemoveSwapEntry(pThing, pVoiceInfo->voiceHeadInfo.headSwapRefNum);
                    pVoiceInfo->voiceHeadInfo.headSwapRefNum = -1;
                }

                sithVoice_secNextHeadSwapTime = sithTime_g_secGameTime + sithVoice_secHeadSwapInterval;
            }
        }
        else
        {
            if ( pVoiceInfo->voiceHeadInfo.headSwapRefNum != -1 )
            {
                if ( sithVoice_bThingHasSwapHead && pVoiceInfo->voiceHeadInfo.apSoundHeadModels[0] ) // TODO: Note that sithVoice_bThingHasSwapHead might be set for other thing than the one passed to this function
                {
                    sithVoice_bThingHasSwapHead = false;
                    sithThing_AddSwapEntry(pThing, pVoiceInfo->voiceHeadInfo.headMeshNum, pVoiceInfo->voiceHeadInfo.apSoundHeadModels[0], 0);
                }
                else
                {
                    sithThing_RemoveSwapEntry(pThing, pVoiceInfo->voiceHeadInfo.headSwapRefNum);
                }

                pVoiceInfo->voiceHeadInfo.headSwapRefNum = -1;
            }

            pVoiceInfo->hSndChannel = 0;
            sithVoice_secNextHeadSwapTime = 0.0f;
        }
    }
}

void J3DAPI sithVoice_PlayVoice(SithCog* pCog)
{
    int  bWait        = sithCogExec_PopInt(pCog);
    float volume      = sithCogExec_PopFlex(pCog);
    tSoundHandle hSnd = sithCogExec_PopSound(pCog);
    SithThing* pThing = sithCogExec_PopThing(pCog);

    if ( !pThing || !hSnd )
    {
        SITHLOG_ERROR("Cog %s: Bad params passed to PlayVoice().\n", pCog->aName);
        sithCogExec_PushInt(pCog, -1);
        return; // Fixed: Added missing return
    }

    SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));
    SITH_ASSERTREL(pThing->renderData.data.pModel3 != ((void*)0));

    int guid = -1; // Fixed: Init to -1;
    if ( strcmpi(pThing->renderData.data.pModel3->aName, "aet_gy.3do") == 0 )
    {
        tSoundChannelHandle hChannel = sithSoundMixer_PlaySound(hSnd, 1.0f, 0.0f, SOUNDPLAY_PLAYTHIGNONCE | SOUNDPLAY_THING_POS);
        if ( hChannel )
        {
            guid = Sound_GetChannelGUID(hChannel);
        }
    }
    else
    {
        if ( !sithVoice_PlayThingVoice(pThing, hSnd, volume) )
        {
            if ( pThing->thingInfo.actorInfo.voiceInfo.hSndChannel )
            {
                guid = Sound_GetChannelGUID(pThing->thingInfo.actorInfo.voiceInfo.hSndChannel);
            }
        }
    }

    if ( guid == -1 )
    {
        sithCogExec_PushInt(pCog, -1);
        return;
    }

    if ( bWait )
    {
        pCog->status = SITHCOG_STATUS_WAITING_SOUND_TO_STOP;
        pCog->statusParams[0] = guid;
    }

    sithCogExec_PushInt(pCog, guid);
}


void J3DAPI sithVoice_SetThingVoiceHeads(SithCog* pCog)
{
    const char* aModelNames[4];
    for ( int i = 3; i >= 0; --i )
    {
        aModelNames[i] = sithCogExec_PopString(pCog); // Head Model Names
    }

    const char* pMeshName = sithCogExec_PopString(pCog); // thing model head mesh name
    SithThing* pThing = sithCogExec_PopThing(pCog);
    if ( pThing )
    {
        SITH_ASSERTREL((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR));
        for ( size_t i = 0; i < 4; ++i )
        {
            pThing->thingInfo.actorInfo.voiceInfo.voiceHeadInfo.apSoundHeadModels[i] = sithModel_GetModel(aModelNames[i]);
        }

        pThing->thingInfo.actorInfo.voiceInfo.voiceHeadInfo.headMeshNum = sithThing_GetThingMeshIndex(pThing, pMeshName);
    }
}

void J3DAPI sithVoice_SetVoiceHeadHeight(SithCog* pCog)
{
    size_t aHeights[4];
    for ( int i = 3; i >= 0; --i )
    {
        aHeights[i] = sithCogExec_PopInt(pCog);
        if ( aHeights[i] > 3 )
        {
            aHeights[i] = 3;
        }
    }

    size_t idx = sithCogExec_PopInt(pCog);
    if ( idx > 3 )
    {
        idx = 3;
    }

    for ( size_t i = 0; i < 4; ++i )
    {
        sithVoice_aVoiceHeadHeights[idx][i] = (uint8_t)aHeights[i]; // It should be ok to cast since it's clamped to 3
    }
}

void J3DAPI sithVoice_SetThingVoiceColor(SithCog* pCog)
{
    rdVector3 aColors[4];
    for ( int i = 3; i >= 0; --i )
    {
        sithCogExec_PopVector(pCog, &aColors[i]);
    }

    SithThing* pThing = sithCogExec_PopThing(pCog);
    SITH_ASSERTREL(pThing && ((pThing->type == SITH_THING_PLAYER) || (pThing->type == SITH_THING_ACTOR)));

    SithActorVoiceInfo* pVoiceInfo = &pThing->thingInfo.actorInfo.voiceInfo;
    for ( size_t i = 0; i < 4; ++i )
    {
        rdVector_Set4(&pVoiceInfo->voiceColor.top + i, aColors[i].red, aColors[i].green, aColors[i].blue, 1.0f);
    }
}

void J3DAPI sithVoice_SetVoiceParams(SithCog* pCog)
{
    sithVoice_dword_52B9A8 = sithCogExec_PopInt(pCog);
    sithVoice_secHeadSwapInterval = sithCogExec_PopFlex(pCog);
}

int sithVoice_GetShowText(void)
{
    // TODO: refactor function to return bool
    return (int)sithVoice_bShowText;
}

void J3DAPI sithVoice_ShowText(int bShow)
{
    // TODO: refactor tfunction to accept bool
    sithVoice_bShowText = bShow != 0;
}

void J3DAPI sithVoice_AddSubtitle(unsigned int msecSoundLen, const char* pSoundFilename, const char* pSubtitleText, VGradiantColor* pSubtitleColor)
{
    const char* pCurLine = pSubtitleText;

    if ( pSubtitleText && pSoundFilename && sithVoice_bShowText )
    {
        if ( (int)sithVoice_numSubtitleInfos > 0 && strcmp(pSoundFilename, sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos - 1].aSoundFileName) == 0 )
        {
            size_t numSubtitles = sithVoice_numSubtitleInfos;

            char aCurVoiceLine[256] = { 0 };
            char aVoiceLines[256]   = { 0 };

            unsigned int curTime = stdPlatform_GetTimeMsec();
            while ( strcmp(pSoundFilename, sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos - 1].aSoundFileName) == 0
                 && (int)sithVoice_numSubtitleInfos > 0
                 && curTime < sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos - 1].msecEndTime )
            {
                if ( strlen(aCurVoiceLine) == 0 )
                {
                    STD_STRCPY(aCurVoiceLine, sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos - 1].aSubtitleText);
                }

                STD_STRCAT(aVoiceLines, aCurVoiceLine);
                memset(aCurVoiceLine, 0, sizeof(aCurVoiceLine));

                --sithVoice_numSubtitleInfos;
            }

            if ( strcmp(aVoiceLines, pSubtitleText) == 0 )
            {
                unsigned int msecStartTime = stdPlatform_GetTimeMsec();
                while ( sithVoice_numSubtitleInfos < numSubtitles )
                {
                    unsigned int msecDuration  = sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime
                        - sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecStartTime;

                    sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecStartTime   = msecStartTime;
                    sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime     = msecDuration + msecStartTime;
                    sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecShowEndTime = sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime + SITHVOICE_MSEC_EXTRA_SUBTITLE_SHOW_DURATION;
                    ++sithVoice_numSubtitleInfos;
                }

                return;
            }

            sithVoice_numSubtitleInfos = numSubtitles;
        }

        size_t numProcessedLines = 0; // TODO: Kind of useless var
        unsigned int msecEndTime = 0;
        size_t numLines          = 0; // Fixed: Init to 0

        // Changed: Moved the calculation of textWidthScalar outside while loop
        uint32_t width, height;
        stdDisplay_GetBackBufferSize(&width, &height);

        float fontWidth = 1.0f - (float)((double)width * SITHVOICE_TEXT_PADDING_X / SITHVOICE_REF_WIDTH);
        float textWidthScalar = 2.0f * fontWidth - 1.0f;

        while ( pCurLine )
        {
            unsigned int msecStartTime = msecEndTime;
            if ( pCurLine == pSubtitleText )
            {
                rdFont_GetTextWidth(pSubtitleText, sithVoice_pTextFont); // TODO: ??

                numLines  = 0;

                const char* pText = pCurLine;
                while ( pText )
                {
                    const char* pInText = pText;
                    pText = rdFont_GetWrapLine(pInText, sithVoice_pTextFont, textWidthScalar);
                    ++numLines;

                    // Fixed: Fixed infinitive loop bay adding check for case where text contain word which is too long to fit onto the screen.
                    //        In this case pInText is returned which leads to infinitive loop.
                    if ( pText == pInText ) {
                        pText = NULL;
                    }
                }

                msecStartTime = stdPlatform_GetTimeMsec();
            }

            msecEndTime = msecStartTime + (msecSoundLen / numLines);

            ++numProcessedLines;

            const char* pLineEnd  = rdFont_GetWrapLine(pCurLine, sithVoice_pTextFont, textWidthScalar);
            if ( pLineEnd == pCurLine ) { // Fixed: If line contains long word at the end and cannot fit onto the screen the function returns pCurLine, in this case pLineEnd should be NULL.
                pLineEnd = NULL;
            }

            if ( sithVoice_numSubtitleInfos >= STD_ARRAYLEN(sithVoice_aSubtitleInfos) ) // Fixed: Make sure the sithVoice_numSubtitleInfos is not greater than STD_ARRAYLEN(sithVoice_aSubtitleInfos)
            {
                sithVoice_PurgeDrawnSubtitles(); // resets to STD_ARRAYLEN(sithVoice_aSubtitleInfos) - sithVoice_curSubtitleInfoNum
            }

            if ( pLineEnd )
            {
                STD_STRNCPY(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aSubtitleText, pCurLine, pLineEnd - pCurLine); // Fixed: By using STD_STNRCPY ensures null termination
                pCurLine = pLineEnd;
            }
            else
            {
                rdFont_GetTextWidth(pCurLine, sithVoice_pTextFont); // TODO: ??

                STD_STRCPY(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aSubtitleText, pCurLine); // Fixed: By using STD_STRCPY ensures null termination
                pCurLine = NULL;
            }

            sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecStartTime   = msecStartTime;
            sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime     = msecEndTime;
            sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecShowEndTime = sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime + SITHVOICE_MSEC_EXTRA_SUBTITLE_SHOW_DURATION;

            STD_STRCPY(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aSoundFileName, pSoundFilename); // Fixed: By using STD_STRCPY ensures null termination

            if ( pSubtitleColor->top.red == -1.0f )
            {
                rdVector_Set4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[0], 1.0f, 0.0f, 0.0f, 1.0f);
                rdVector_Set4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[1], 1.0f, 0.0f, 0.0f, 1.0f);
                rdVector_Set4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[2], 1.0f, 1.0f, 0.0f, 1.0f);
                rdVector_Set4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[3], 1.0f, 1.0f, 0.0f, 1.0f);
            }
            else
            {
                for ( size_t i = 0; i < 4; ++i )
                {
                    rdVector_Copy4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[i], &pSubtitleColor->top + i);
                }
            }

            ++sithVoice_numSubtitleInfos;
        }
    }
}

void sithVoice_PurgeDrawnSubtitles(void)
{
    memset(sithVoice_aSubtitleInfos, 0, sizeof(SithVoiceSubtitleInfo) * sithVoice_curSubtitleInfoNum);
    sithVoice_numSubtitleInfos = 0;

    for ( size_t i = sithVoice_curSubtitleInfoNum; i < STD_ARRAYLEN(sithVoice_aSubtitleInfos); ++i )
    {
        sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecStartTime   = sithVoice_aSubtitleInfos[i].msecStartTime;
        sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecEndTime     = sithVoice_aSubtitleInfos[i].msecEndTime;
        sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].msecShowEndTime = sithVoice_aSubtitleInfos[i].msecShowEndTime;

        STD_STRCPY(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aSubtitleText, sithVoice_aSubtitleInfos[i].aSubtitleText); // Fixed: By using STD_STRCPY it ensures null termination
        STD_STRCPY(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aSoundFileName, sithVoice_aSubtitleInfos[i].aSoundFileName); // Fixed: By using STD_STRCPY it ensures null termination

        for ( size_t j = 0; j < STD_ARRAYLEN(sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors); ++j )
        {
            rdVector_Copy4(&sithVoice_aSubtitleInfos[sithVoice_numSubtitleInfos].aTextColors[j], &sithVoice_aSubtitleInfos[i].aTextColors[j]);
        }

        ++sithVoice_numSubtitleInfos;
    }

    memset(&sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum], 0, sizeof(SithVoiceSubtitleInfo) * (STD_ARRAYLEN(sithVoice_aSubtitleInfos) - sithVoice_curSubtitleInfoNum));
    sithVoice_curSubtitleInfoNum = 0;
}

void sithVoice_Draw(void)
{
    if ( !sithVoice_bShowText )
    {
        return;
    }

    unsigned int curTime = stdPlatform_GetTimeMsec();

    bool bDraw = true;

    // Skip lines that expired
    while ( (strlen(sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum].aSubtitleText) > 0)
         && (curTime > sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum].msecShowEndTime) )
    {
        ++sithVoice_curSubtitleInfoNum;
        if ( sithVoice_curSubtitleInfoNum >= STD_ARRAYLEN(sithVoice_aSubtitleInfos) )
        {
            sithVoice_curSubtitleInfoNum = STD_ARRAYLEN(sithVoice_aSubtitleInfos) - 1;
            bDraw = false;
            break;
        }
    }



    if ( bDraw && strlen(sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum].aSubtitleText) > 0 )
    {
        uint32_t width, height;
        stdDisplay_GetBackBufferSize(&width, &height);

        float x = (float)((double)width * SITHVOICE_TEXT_PADDING_X / SITHVOICE_REF_WIDTH);
        float y = (float)((double)height * SITHVOICE_TEXT_PADDING_Y / SITHVOICE_REF_HEIGHT);
        float lineHeight = (float)((double)sithVoice_pTextFont->lineSpacing / RD_REF_HEIGHT);

        if ( curTime >= sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum].msecEndTime
          && strlen(sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum + 1].aSubtitleText) > 0 )
        {
            y = y - (float)((double)(curTime - sithVoice_aSubtitleInfos[sithVoice_curSubtitleInfoNum].msecEndTime) * lineHeight) / 1000.0f;
        }

        // Print up
        for ( size_t lineCount = 0; lineCount < SITHVOICE_MAX_LINES_PER_DRAW; lineCount++ )
        {
            SithVoiceSubtitleInfo* pSubInfo = &sithVoice_aSubtitleInfos[lineCount + sithVoice_curSubtitleInfoNum];
            if ( strlen(pSubInfo->aSubtitleText) == 0 || curTime <= sithVoice_aSubtitleInfos[lineCount + sithVoice_curSubtitleInfoNum].msecStartTime )
            {
                break;
            }

            rdFont_SetFontColor(sithVoice_aSubtitleInfos[lineCount + sithVoice_curSubtitleInfoNum].aTextColors);
            rdFont_DrawTextLine(pSubInfo->aSubtitleText, x, y, rdCamera_g_pCurCamera->pFrustum->nearPlane, sithVoice_pTextFont, RDFONT_ALIGNLEFT);

            y = y + lineHeight;
        }
    }
}

int J3DAPI sithVoice_SyncVoiceState(DPID idTo, unsigned int outstream)
{
    SITHDSS_STARTOUT(SITHDSS_VOICESTATE);
    SITHDSS_PUSHINT8(sithVoice_bShowText);

    //sithMulti_g_message.data[0] = sithVoice_bShowText;
   // uint8_t* pCurOut = &sithMulti_g_message.data[1];

    static_assert(STD_ARRAYLEN(sithVoice_aVoiceHeadHeights) == 4, "");
    static_assert(STD_ARRAYLEN(sithVoice_aVoiceHeadHeights[0]) == 4, "");
    for ( size_t i = 0; i < STD_ARRAYLEN(sithVoice_aVoiceHeadHeights); ++i )
    {
        for ( size_t j = 0; j < STD_ARRAYLEN(sithVoice_aVoiceHeadHeights[i]); ++j )
        {
            SITHDSS_PUSHINT8(sithVoice_aVoiceHeadHeights[i][j]);
            //pCurOut = sithVoice_aVoiceHeadHeights[i][j];
            //pCurOut = (float*)((char*)pCurOut + 1);
        }
    }

    SITHDSS_PUSHFLOAT(sithVoice_secHeadSwapInterval);
    //*(float*)pCurOut = sithVoice_secHeadSwapInterval;
    // pCurOut += 4;

    SITHDSS_PUSHINT32(sithVoice_dword_52B9A8);
    //*(uint32_t*)pCurOut = sithVoice_dword_52B9A8;

    SITHDSS_ENDOUT;
    //sithMulti_g_message.type = SITHDSS_VOICESTATE;
    //sithMulti_g_message.length = (char*)(pCurOut + 1) - (char*)sithMulti_g_message.data;

    return sithMessage_SendMessage(&sithMulti_g_message, idTo, outstream, 1u);
}

int J3DAPI sithVoice_ProcessVoiceState(const SithMessage* pMsg)
{
    SITH_ASSERTREL(pMsg);

    SITHDSS_STARTIN(pMsg);

    sithVoice_bShowText = SITHDSS_POPUINT8();
    //sithVoice_bShowText = pMsg->data[0];

    //pCurIn = &pMsg->data[1];
    for ( size_t i = 0; i < 4; ++i )
    {
        for ( size_t j = 0; j < 4; ++j )
        {
            sithVoice_aVoiceHeadHeights[i][j] = SITHDSS_POPUINT8();
            //sithVoice_aVoiceHeadHeights[i][j] = *pCurIn++;
        }
    }

    sithVoice_secHeadSwapInterval = SITHDSS_POPFLOAT();
    //sithVoice_secHeadSwapInterval = *(float*)pCurIn;

    sithVoice_dword_52B9A8 = SITHDSS_POPUINT32();
    //sithVoice_dword_52B9A8 = *((uint32_t*)pCurIn + 1);

    SITHDSS_ENDIN;
    return 1;
}

const rdFont* sithVoice_GetTextFont(void)
{
    return sithVoice_pTextFont;
}
