#ifndef SITH_SITHSOUNDCLASS_H
#define SITH_SITHSOUNDCLASS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int sithSoundClass_Startup(void);
void J3DAPI sithSoundClass_Shutdown();
int J3DAPI sithSoundClass_NDYReadSoundClassSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithSoundClass_CNDWriteSoundClassSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSoundClass_CNDReadSoundClassSection(tFileHandle fh, SithWorld* pWorld);
SithSoundClass* J3DAPI sithSoundClass_Load(SithWorld* pWorld, const char* pName);
int J3DAPI sithSoundClass_LoadEntry(SithWorld* pWorld, SithSoundClass* pClass, const char* pPath);
signed int J3DAPI sithSoundClass_AllocSoundClasses(SithWorld* pWorld, int size);
void J3DAPI sithSoundClass_FreeWorldSoundClasses(SithWorld* pWorld);
// Returns sound channel
//  handle
tSoundChannelHandle J3DAPI sithSoundClass_PlayModeFirstEx(SithThing* pThing, SithSoundClassMode mode, float volume);
tSoundChannelHandle J3DAPI sithSoundClass_PlayModeFirst(SithThing* pThing, SithSoundClassMode mode);
tSoundChannelHandle J3DAPI sithSoundClass_PlayModeRandom(SithThing* pThing, SithSoundClassMode mode);
tSoundChannelHandle J3DAPI sithSoundClass_PlayVoiceModeRandom(SithThing* pThing, SithSoundClassMode mode);
tSoundChannelHandle J3DAPI sithSoundClass_PlayPlayerVoiceModeRandom(SithThing* pThing, SithSoundClassMode mode);
tSoundChannelHandle J3DAPI sithSoundClass_PlayMode(SithThing* pThing, SithSoundClassMode mode, float a3);
void J3DAPI sithSoundClass_StopMode(SithThing* pThing, SithSoundClassMode mode);
void J3DAPI sithSoundClass_SetModePitch(SithThing* pThing, SithSoundClassMode mode, float pitch);
void J3DAPI sithSoundClass_SetModeVolume(SithThing* pThing, SithSoundClassMode mode, float volume);
void J3DAPI sithSoundClass_FadeModeVolume(SithThing* pThing, SithSoundClassMode mode, float startVolume, float endVolume);
unsigned int J3DAPI sithSoundClass_IsModeFadingVol(SithThing* pThing, SithSoundClassMode mode);
tSoundChannelHandle J3DAPI sithSoundClass_PlayModeEntry(SithThing* pThing, SithSoundClassMode mode, SithSoundClassEntry* pEntry, float volume);
SithSoundClass* J3DAPI sithSoundClass_CacheFind(const char* pName);
void J3DAPI sithSoundClass_CacheAdd(SithSoundClass* pClass);
void J3DAPI sithSoundClass_CacheRemove(const SithSoundClass* pClass);

// Helper hooking functions
void sithSoundClass_InstallHooks(void);
void sithSoundClass_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSOUNDCLASS_H
