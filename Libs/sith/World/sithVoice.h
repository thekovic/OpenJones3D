#ifndef SITH_SITHVOICE_H
#define SITH_SITHVOICE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int sithVoice_Startup(void);
int J3DAPI sithVoice_Open();
void J3DAPI sithVoice_Shutdown();
void sithVoice_Close();
int J3DAPI sithVoice_RegisterCogFunctions(SithCogSymbolTable* pTbl);
int J3DAPI sithVoice_PlayThingVoice(SithThing* pThing, tSoundHandle hSnd, float volume);
void J3DAPI sithVoice_UpdateLipSync(SithThing* pThing);
void J3DAPI sithVoice_PlayVoice(SithCog* pCog);
void J3DAPI sithVoice_SetThingVoiceHeads(SithCog* pCog);
void J3DAPI sithVoice_SetVoiceHeadHeight(SithCog* pCog);
void J3DAPI sithVoice_SetThingVoiceColor(SithCog* pCog);
void J3DAPI sithVoice_SetVoiceParams(SithCog* pCog);
int J3DAPI sithVoice_GetShowText();
void J3DAPI sithVoice_ShowText(int bShow);
void J3DAPI sithVoice_sub_4435B0(int msecSoundLen, const char* pVoiceSoundFileName, const char* pVoiceSubtitles, VGradiantColor* pVoiceSubtitleColor);
void J3DAPI sithVoice_sub_443AF0();
void sithVoice_Draw(void);
int J3DAPI sithVoice_SyncVoiceState(DPID idTo, unsigned int outstream);
int J3DAPI sithVoice_ProcessVoiceState(const SithMessage* pMsg);
const rdFont* J3DAPI sithVoice_GetTextFont();

// Helper hooking functions
void sithVoice_InstallHooks(void);
void sithVoice_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHVOICE_H
