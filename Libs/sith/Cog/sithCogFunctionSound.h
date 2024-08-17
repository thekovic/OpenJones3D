#ifndef SITH_SITHCOGFUNCTIONSOUND_H
#define SITH_SITHCOGFUNCTIONSOUND_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunctionSound_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunctionSound_PlaySoundThing(SithCog* pCog);
void J3DAPI sithCogFunctionSound_StopSoundThing(SithCog* pCog);
void J3DAPI sithCogFunctionSound_StopAllSoundsThing(SithCog* pCog);
void J3DAPI sithCogFunctionSound_PlaySoundPos(SithCog* pCog);
void J3DAPI sithCogFunctionSound_PlaySoundLocal(SithCog* pCog);
void J3DAPI sithCogFunctionSound_PlaySoundGlobal(SithCog* pCog);
void J3DAPI sithCogFunctionSound_StopSound(SithCog* pCog);
void J3DAPI sithCogFunctionSound_LoadSound(SithCog* pCog);
void J3DAPI sithCogFunctionSound_PlaySoundClass(SithCog* pCog);
void J3DAPI sithCogFunctionSound_StopSoundClass(SithCog* pCog);
void J3DAPI sithCogFunctionSound_PlayVoiceMode(SithCog* pCog);
void J3DAPI sithCogFunctionSound_ChangeVolume(SithCog* pCog);
void J3DAPI sithCogFunctionSound_ChangePitch(SithCog* pCog);
void J3DAPI sithCogFunctionSound_SectorSound(SithCog* pCog);
void J3DAPI sithCogFunctionSound_GetSoundLen(SithCog* pCog);
void J3DAPI sithCogFunctionSound_WaitForSound(SithCog* pCog);

// Helper hooking functions
void sithCogFunctionSound_InstallHooks(void);
void sithCogFunctionSound_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTIONSOUND_H
