#include "sithVoice.h"
#include <j3dcore/j3dhook.h>

#include <sith/Cog/sithCogExec.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/RTI/symbols.h>

#include <sound/Sound.h>

#define sithVoice_secHeadSwapInterval J3D_DECL_FAR_VAR(sithVoice_secHeadSwapInterval, float)
#define sithVoice_dword_52B9A8 J3D_DECL_FAR_VAR(sithVoice_dword_52B9A8, int)
#define sithVoice_curHeadHeight J3D_DECL_FAR_VAR(sithVoice_curHeadHeight, int)
#define sithVoice_nextSubtitleNum J3D_DECL_FAR_VAR(sithVoice_nextSubtitleNum, int)
#define sithVoice_aVoiceHeadHeights J3D_DECL_FAR_ARRAYVAR(sithVoice_aVoiceHeadHeights, uint8_t(*)[4][4])
#define sithVoice_dword_5647A0 J3D_DECL_FAR_VAR(sithVoice_dword_5647A0, int)
#define sithVoice_secNextHeadSwapTime J3D_DECL_FAR_VAR(sithVoice_secNextHeadSwapTime, float)
#define sithVoice_pTextFont J3D_DECL_FAR_VAR(sithVoice_pTextFont, rdFont*)
#define sithVoice_dword_5647AC J3D_DECL_FAR_VAR(sithVoice_dword_5647AC, int)
#define sithVoice_bOpen J3D_DECL_FAR_VAR(sithVoice_bOpen, int)
#define sithVoice_bStartup J3D_DECL_FAR_VAR(sithVoice_bStartup, int)
#define sithVoice_bShowText J3D_DECL_FAR_VAR(sithVoice_bShowText, int)
#define sithVoice_bThingHasSwapHeadRdModel J3D_DECL_FAR_VAR(sithVoice_bThingHasSwapHeadRdModel, int)
#define sithVoice_headHeight J3D_DECL_FAR_VAR(sithVoice_headHeight, int)
#define sithVoice_aSubtitleInfos J3D_DECL_FAR_ARRAYVAR(sithVoice_aSubtitleInfos, SithVoiceSubtitleInfo(*)[25])

void sithVoice_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithVoice_Startup);
    // J3D_HOOKFUNC(sithVoice_Open);
    // J3D_HOOKFUNC(sithVoice_Shutdown);
    // J3D_HOOKFUNC(sithVoice_Close);
    // J3D_HOOKFUNC(sithVoice_RegisterCogFunctions);
    // J3D_HOOKFUNC(sithVoice_PlayThingVoice);
    // J3D_HOOKFUNC(sithVoice_UpdateLipSync);
    J3D_HOOKFUNC(sithVoice_PlayVoice);
    // J3D_HOOKFUNC(sithVoice_SetThingVoiceHeads);
    // J3D_HOOKFUNC(sithVoice_SetVoiceHeadHeight);
    // J3D_HOOKFUNC(sithVoice_SetThingVoiceColor);
    // J3D_HOOKFUNC(sithVoice_SetVoiceParams);
    // J3D_HOOKFUNC(sithVoice_GetShowText);
    // J3D_HOOKFUNC(sithVoice_ShowText);
    // J3D_HOOKFUNC(sithVoice_sub_4435B0);
    // J3D_HOOKFUNC(sithVoice_sub_443AF0);
    // J3D_HOOKFUNC(sithVoice_Draw);
    // J3D_HOOKFUNC(sithVoice_SyncVoiceState);
    // J3D_HOOKFUNC(sithVoice_ProcessVoiceState);
    // J3D_HOOKFUNC(sithVoice_GetTextFont);
}

void sithVoice_ResetGlobals(void)
{
    float sithVoice_secHeadSwapInterval_tmp = 0.1f;
    memcpy(&sithVoice_secHeadSwapInterval, &sithVoice_secHeadSwapInterval_tmp, sizeof(sithVoice_secHeadSwapInterval));

    int sithVoice_dword_52B9A8_tmp = 50;
    memcpy(&sithVoice_dword_52B9A8, &sithVoice_dword_52B9A8_tmp, sizeof(sithVoice_dword_52B9A8));

    int sithVoice_curHeadHeight_tmp = -1;
    memcpy(&sithVoice_curHeadHeight, &sithVoice_curHeadHeight_tmp, sizeof(sithVoice_curHeadHeight));

    memset(&sithVoice_nextSubtitleNum, 0, sizeof(sithVoice_nextSubtitleNum));
    memset(&sithVoice_aVoiceHeadHeights, 0, sizeof(sithVoice_aVoiceHeadHeights));
    memset(&sithVoice_dword_5647A0, 0, sizeof(sithVoice_dword_5647A0));
    memset(&sithVoice_secNextHeadSwapTime, 0, sizeof(sithVoice_secNextHeadSwapTime));
    memset(&sithVoice_pTextFont, 0, sizeof(sithVoice_pTextFont));
    memset(&sithVoice_dword_5647AC, 0, sizeof(sithVoice_dword_5647AC));
    memset(&sithVoice_bOpen, 0, sizeof(sithVoice_bOpen));
    memset(&sithVoice_bStartup, 0, sizeof(sithVoice_bStartup));
    memset(&sithVoice_bShowText, 0, sizeof(sithVoice_bShowText));
    memset(&sithVoice_bThingHasSwapHeadRdModel, 0, sizeof(sithVoice_bThingHasSwapHeadRdModel));
    memset(&sithVoice_headHeight, 0, sizeof(sithVoice_headHeight));
    memset(&sithVoice_aSubtitleInfos, 0, sizeof(sithVoice_aSubtitleInfos));
}

int sithVoice_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithVoice_Startup);
}

int J3DAPI sithVoice_Open()
{
    return J3D_TRAMPOLINE_CALL(sithVoice_Open);
}

void J3DAPI sithVoice_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithVoice_Shutdown);
}

void sithVoice_Close()
{
    J3D_TRAMPOLINE_CALL(sithVoice_Close);
}

int J3DAPI sithVoice_RegisterCogFunctions(SithCogSymbolTable* pTbl)
{
    return J3D_TRAMPOLINE_CALL(sithVoice_RegisterCogFunctions, pTbl);
}

int J3DAPI sithVoice_PlayThingVoice(SithThing* pThing, tSoundHandle hSnd, float volume)
{
    return J3D_TRAMPOLINE_CALL(sithVoice_PlayThingVoice, pThing, hSnd, volume);
}

void J3DAPI sithVoice_UpdateLipSync(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithVoice_UpdateLipSync, pThing);
}

//void J3DAPI sithVoice_PlayVoice(SithCog* pCog)
//{
//    J3D_TRAMPOLINE_CALL(sithVoice_PlayVoice, pCog);
//}

void J3DAPI sithVoice_SetThingVoiceHeads(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithVoice_SetThingVoiceHeads, pCog);
}

void J3DAPI sithVoice_SetVoiceHeadHeight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithVoice_SetVoiceHeadHeight, pCog);
}

void J3DAPI sithVoice_SetThingVoiceColor(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithVoice_SetThingVoiceColor, pCog);
}

void J3DAPI sithVoice_SetVoiceParams(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithVoice_SetVoiceParams, pCog);
}

int J3DAPI sithVoice_GetShowText()
{
    return J3D_TRAMPOLINE_CALL(sithVoice_GetShowText);
}

void J3DAPI sithVoice_ShowText(int bShow)
{
    J3D_TRAMPOLINE_CALL(sithVoice_ShowText, bShow);
}

void J3DAPI sithVoice_sub_4435B0(int msecSoundLen, const char* pVoiceSoundFileName, const char* pVoiceSubtitles, VGradiantColor* pVoiceSubtitleColor)
{
    J3D_TRAMPOLINE_CALL(sithVoice_sub_4435B0, msecSoundLen, pVoiceSoundFileName, pVoiceSubtitles, pVoiceSubtitleColor);
}

void J3DAPI sithVoice_sub_443AF0()
{
    J3D_TRAMPOLINE_CALL(sithVoice_sub_443AF0);
}

void sithVoice_Draw(void)
{
    J3D_TRAMPOLINE_CALL(sithVoice_Draw);
}

int J3DAPI sithVoice_SyncVoiceState(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithVoice_SyncVoiceState, idTo, outstream);
}

int J3DAPI sithVoice_ProcessVoiceState(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithVoice_ProcessVoiceState, pMsg);
}

const rdFont* J3DAPI sithVoice_GetTextFont()
{
    return J3D_TRAMPOLINE_CALL(sithVoice_GetTextFont);
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
    if ( strcmpi(pThing->renderData.data.pModel3->aName, "aet_gy.3do") != 0 )
    {
        if ( !sithVoice_PlayThingVoice(pThing, hSnd, volume) )
        {
            if ( pThing->thingInfo.actorInfo.voiceInfo.hSndChannel )
            {
                guid = Sound_GetChannelGUID(pThing->thingInfo.actorInfo.voiceInfo.hSndChannel);
            }
        }
    }
    else
    {
        tSoundChannelHandle hChannel = sithSoundMixer_PlaySound(hSnd, 1.0f, 0.0f, SOUNDPLAY_PLAYTHIGNONCE | SOUNDPLAY_THING_POS);
        if ( hChannel )
        {
            guid = Sound_GetChannelGUID(hChannel);
        }
    }

    if ( guid == -1 )
    {
        sithCogExec_PushInt(pCog, -1);
    }
    else
    {
        if ( bWait )
        {
            pCog->status = SITHCOG_STATUS_WAITING_SOUND_TO_STOP;
            pCog->statusParams[0] = guid;
        }

        sithCogExec_PushInt(pCog, guid);
    }
}
