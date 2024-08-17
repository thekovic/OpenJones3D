#ifndef SITH_SITHPUPPET_H
#define SITH_SITHPUPPET_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithPuppet_g_pClassHashtable J3D_DECL_FAR_VAR(sithPuppet_g_pClassHashtable, tHashTable*)
// extern tHashTable *sithPuppet_g_pClassHashtable;

#define sithPuppet_g_pKeyHashtable J3D_DECL_FAR_VAR(sithPuppet_g_pKeyHashtable, tHashTable*)
// extern tHashTable *sithPuppet_g_pKeyHashtable;

#define sithPuppet_g_bPlayerLeapForward J3D_DECL_FAR_VAR(sithPuppet_g_bPlayerLeapForward, int)
// extern int sithPuppet_g_bPlayerLeapForward;

int sithPuppet_Startup(void);
void J3DAPI sithPuppet_Shutdown();
void J3DAPI sithPuppet_New(SithThing* pThing);
void J3DAPI sithPuppet_Free(SithThing* pThing);
void J3DAPI sithPuppet_RemoveAllTracks(SithThing* pThing);
void J3DAPI sithPuppet_UpdatePuppet(SithThing* pThing, float secDeltaTime);
void J3DAPI sithPuppet_PlayFidgetMode(SithThing* pThing);
void J3DAPI sithPuppet_StopFridgetTrack(SithThing* pThing);
int J3DAPI sithPuppet_IsModeOnTrack(const SithThing* pThing, SithPuppetSubMode mode);
int J3DAPI sithPuppet_IsAnyModeOnTrack(const SithThing* pThing, SithPuppetSubMode firstMode, SithPuppetSubMode lastMode);
SithPuppetTrack* J3DAPI sithPuppet_FindActiveTrack(const SithThing* pThing, const rdKeyframe* pKfTrack);
void J3DAPI sithPuppet_UpdateThingMoveTracks(SithThing* pThing, float secDeltaTime);
double J3DAPI sithPuppet_UpdateThingMove(SithThing* pThing, rdPuppetTrackCallback pAxis);
int J3DAPI sithPuppet_SetSubMode(SithThing* pThing, SithPuppetSubMode newSubMode, rdPuppetTrackCallback pfCallback);
void J3DAPI sithPuppet_SetMoveMode(SithThing* pThing, SithPuppetMoveMode newMode);
void J3DAPI sithPuppet_SetArmedMode(SithThing* pThing, unsigned int newMode);
// On success trackIdx is returned, 
// -99 is returned when submode already plays 
// and -1 is returned on error e.g. submode doesn't contain animation keyframe 
int J3DAPI sithPuppet_PlayMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback);
int J3DAPI sithPuppet_PlayForceMoveMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback);
int J3DAPI sithPuppet_PlayKey(rdPuppet* pPuppet, rdKeyframe* pTrack, int lowPriority, int highPriority, rdKeyframeFlags flags, rdPuppetTrackCallback pfCallback);
unsigned int J3DAPI sithPuppet_GetTrackNumForGUID(const SithThing* pThing, int guid);
int J3DAPI sithPuppet_StopKey(rdPuppet* pPuppet, int track, float fadeTime);
void J3DAPI sithPuppet_StopForceMove(SithThing* pThing, int bStopTracks);
void J3DAPI sithPuppet_DefaultCallback(SithThing* pThing, int track, rdKeyMarkerType markerType);
int J3DAPI sithPuppet_NDYReadPuppetSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithPuppet_CNDWritePuppetSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithPuppet_CNDReadPuppetSection(tFileHandle fh, SithWorld* pWorld);
SithPuppetClass* J3DAPI sithPuppet_LoadPuppetClass(const char* pFilename);
int J3DAPI sithPuppet_LoadPuppetClassEntry(SithPuppetClass* pClass, const char* pPath);
int J3DAPI sithPuppet_AllocWorldPuppets(SithWorld* pWorld, int size);
void J3DAPI sithPuppet_FreeWorldPuppets(SithWorld* pWorld);
int J3DAPI sithPuppet_CNDWriteKeyframeSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithPuppet_CNDReadKeyframeSection(tFileHandle fh, SithWorld* pWorld);
rdKeyframe* J3DAPI sithPuppet_GetKeyframeByIndex(int index);
rdKeyframe* J3DAPI sithPuppet_LoadKeyframe(const char* pName);
int J3DAPI sithPuppet_AllocWorldKeyframes(SithWorld* pWorld, int size);
void J3DAPI sithPuppet_FreeWorldKeyframes(SithWorld* pWorld);
int J3DAPI sithPuppet_ClassCacheAdd(const SithPuppetClass* pClass);
int J3DAPI sithPuppet_ClassCacheRemove(const SithPuppetClass* pClass);
rdKeyframe* J3DAPI sithPuppet_GetdKeyframe(const char* pName);
rdKeyframe* J3DAPI sithPuppet_KeyCacheFind(const char* pName);
void J3DAPI sithPuppet_KeyCacheAdd(rdKeyframe* pKeyframe);
void J3DAPI sithPuppet_KeyCacheRemove(rdKeyframe* pKeyframe);
int J3DAPI sithPuppet_StopMode(SithThing* pThing, SithPuppetSubMode submode, float fadeOutTime);
signed int J3DAPI sithPuppet_SynchMode(SithThing* pThing, SithPuppetSubMode oldMode, SithPuppetSubMode newMode, float a4, int bReverse);
void J3DAPI sithPuppet_ClearMode(SithThing* pThing, SithPuppetSubMode mode);
SithPuppetTrack* J3DAPI sithPuppet_FreeTrackNum(SithThing* pThing, int trackNum);
int J3DAPI sithPuppet_NewTrack(SithThing* pThing, SithPuppetClassSubmode* pSubmode, int trackNum, SithPuppetSubMode submode);
void J3DAPI sithPuppet_AddTrack(SithThing* pThing, SithPuppetTrack* pNewTrack);
void J3DAPI sithPuppet_RemoveTrack(SithThing* pThing, SithPuppetTrack* pTrack);
void J3DAPI sithPuppet_RemoveTrackImpl(SithThing* pThing, SithPuppetTrack* pTrack);
void J3DAPI sithPuppet_RemoveTrackNum(SithThing* pThing, int trackNum);
SithPuppetTrack* J3DAPI sithPuppet_GetModeTrack(const SithThing* pThing, SithPuppetSubMode mode);
SithPuppetTrack* J3DAPI sithPuppet_GetModeTrackImpl(const SithThing* pThing, SithPuppetSubMode submode);
void J3DAPI sithPuppet_FreeEntry(SithThing* pThing);

// Helper hooking functions
void sithPuppet_InstallHooks(void);
void sithPuppet_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPUPPET_H
