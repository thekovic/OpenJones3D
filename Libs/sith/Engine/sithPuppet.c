#include "sithPuppet.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithPuppet_aStrSubModes J3D_DECL_FAR_ARRAYVAR(sithPuppet_aStrSubModes, const char*(*)[84])
#define sithPuppet_pHashtblSubmodes J3D_DECL_FAR_VAR(sithPuppet_pHashtblSubmodes, tHashTable*)

void sithPuppet_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPuppet_Startup);
    // J3D_HOOKFUNC(sithPuppet_Shutdown);
    // J3D_HOOKFUNC(sithPuppet_New);
    // J3D_HOOKFUNC(sithPuppet_Free);
    // J3D_HOOKFUNC(sithPuppet_RemoveAllTracks);
    // J3D_HOOKFUNC(sithPuppet_UpdatePuppet);
    // J3D_HOOKFUNC(sithPuppet_PlayFidgetMode);
    // J3D_HOOKFUNC(sithPuppet_StopFridgetTrack);
    // J3D_HOOKFUNC(sithPuppet_IsModeOnTrack);
    // J3D_HOOKFUNC(sithPuppet_IsAnyModeOnTrack);
    // J3D_HOOKFUNC(sithPuppet_FindActiveTrack);
    // J3D_HOOKFUNC(sithPuppet_UpdateThingMoveTracks);
    // J3D_HOOKFUNC(sithPuppet_UpdateThingMove);
    // J3D_HOOKFUNC(sithPuppet_SetSubMode);
    // J3D_HOOKFUNC(sithPuppet_SetMoveMode);
    // J3D_HOOKFUNC(sithPuppet_SetArmedMode);
    // J3D_HOOKFUNC(sithPuppet_PlayMode);
    // J3D_HOOKFUNC(sithPuppet_PlayForceMoveMode);
    // J3D_HOOKFUNC(sithPuppet_PlayKey);
    // J3D_HOOKFUNC(sithPuppet_GetTrackNumForGUID);
    // J3D_HOOKFUNC(sithPuppet_StopKey);
    // J3D_HOOKFUNC(sithPuppet_StopForceMove);
    // J3D_HOOKFUNC(sithPuppet_DefaultCallback);
    // J3D_HOOKFUNC(sithPuppet_NDYReadPuppetSection);
    // J3D_HOOKFUNC(sithPuppet_CNDWritePuppetSection);
    // J3D_HOOKFUNC(sithPuppet_CNDReadPuppetSection);
    // J3D_HOOKFUNC(sithPuppet_LoadPuppetClass);
    // J3D_HOOKFUNC(sithPuppet_LoadPuppetClassEntry);
    // J3D_HOOKFUNC(sithPuppet_AllocWorldPuppets);
    // J3D_HOOKFUNC(sithPuppet_FreeWorldPuppets);
    // J3D_HOOKFUNC(sithPuppet_CNDWriteKeyframeSection);
    // J3D_HOOKFUNC(sithPuppet_CNDReadKeyframeSection);
    // J3D_HOOKFUNC(sithPuppet_GetKeyframeByIndex);
    // J3D_HOOKFUNC(sithPuppet_LoadKeyframe);
    // J3D_HOOKFUNC(sithPuppet_AllocWorldKeyframes);
    // J3D_HOOKFUNC(sithPuppet_FreeWorldKeyframes);
    // J3D_HOOKFUNC(sithPuppet_ClassCacheAdd);
    // J3D_HOOKFUNC(sithPuppet_ClassCacheRemove);
    // J3D_HOOKFUNC(sithPuppet_GetdKeyframe);
    // J3D_HOOKFUNC(sithPuppet_KeyCacheFind);
    // J3D_HOOKFUNC(sithPuppet_KeyCacheAdd);
    // J3D_HOOKFUNC(sithPuppet_KeyCacheRemove);
    // J3D_HOOKFUNC(sithPuppet_StopMode);
    // J3D_HOOKFUNC(sithPuppet_SynchMode);
    // J3D_HOOKFUNC(sithPuppet_ClearMode);
    // J3D_HOOKFUNC(sithPuppet_FreeTrackNum);
    // J3D_HOOKFUNC(sithPuppet_NewTrack);
    // J3D_HOOKFUNC(sithPuppet_AddTrack);
    // J3D_HOOKFUNC(sithPuppet_RemoveTrack);
    // J3D_HOOKFUNC(sithPuppet_RemoveTrackImpl);
    // J3D_HOOKFUNC(sithPuppet_RemoveTrackNum);
    // J3D_HOOKFUNC(sithPuppet_GetModeTrack);
    // J3D_HOOKFUNC(sithPuppet_GetModeTrackImpl);
    // J3D_HOOKFUNC(sithPuppet_FreeEntry);
}

void sithPuppet_ResetGlobals(void)
{
    const char *sithPuppet_aStrSubModes_tmp[84] = {
      "--RESERVED--",
      "stand",
      "walk",
      "run",
      "walkback",
      "hopback",
      "hopleft",
      "hopright",
      "strafeleft",
      "straferight",
      "turnleft",
      "turnright",
      "slidedownfwd",
      "slidedownback",
      "leap",
      "jumpready",
      "jumpup",
      "jumpfwd",
      "rising",
      "fall",
      "death",
      "death2",
      "fidget",
      "fidget2",
      "pickup",
      "pushpullready",
      "pushitem",
      "pullitem",
      "mountledge",
      "grabledge",
      "hangledge",
      "hangshimleft",
      "hangshimright",
      "mountwall",
      "climbwallidle",
      "climbwallup",
      "climbwalldown",
      "climbwallleft",
      "climbwallright",
      "climbpullingup",
      "whipclimbmount",
      "whipclimbidle",
      "whipclimbup",
      "whipclimbdown",
      "whipclimbleft",
      "whipclimbright",
      "whipclimbdismount",
      "whipswingmount",
      "whipswing",
      "mountfromwater",
      "divefromsurface",
      "mount1mstep",
      "mount2mledge",
      "jumprollback",
      "jumprollfwd",
      "land",
      "hitheadl",
      "hitheadr",
      "hitsidel",
      "hitsider",
      "activate",
      "activatehigh",
      "drawweapon",
      "aimweapon",
      "holsterweapon",
      "fire",
      "fire2",
      "fire3",
      "fire4",
      "stand2walk",
      "walk2stand",
      "stand2crawl",
      "crawl2stand",
      "walk2attack",
      "victory",
      "hit",
      "hit2",
      "grabarms",
      "reserved",
      "climbtoclimb",
      "climbtohang",
      "leapleft",
      "leapright",
      "fallforward"
    };
    memcpy((char **)&sithPuppet_aStrSubModes, &sithPuppet_aStrSubModes_tmp, sizeof(sithPuppet_aStrSubModes));
    
    memset(&sithPuppet_g_pClassHashtable, 0, sizeof(sithPuppet_g_pClassHashtable));
    memset(&sithPuppet_g_pKeyHashtable, 0, sizeof(sithPuppet_g_pKeyHashtable));
    memset(&sithPuppet_pHashtblSubmodes, 0, sizeof(sithPuppet_pHashtblSubmodes));
    memset(&sithPuppet_g_bPlayerLeapForward, 0, sizeof(sithPuppet_g_bPlayerLeapForward));
}

int sithPuppet_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_Startup);
}

void J3DAPI sithPuppet_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithPuppet_Shutdown);
}

void J3DAPI sithPuppet_New(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_New, pThing);
}

void J3DAPI sithPuppet_Free(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_Free, pThing);
}

void J3DAPI sithPuppet_RemoveAllTracks(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_RemoveAllTracks, pThing);
}

void J3DAPI sithPuppet_UpdatePuppet(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_UpdatePuppet, pThing, secDeltaTime);
}

void J3DAPI sithPuppet_PlayFidgetMode(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_PlayFidgetMode, pThing);
}

void J3DAPI sithPuppet_StopFridgetTrack(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_StopFridgetTrack, pThing);
}

int J3DAPI sithPuppet_IsModeOnTrack(const SithThing* pThing, SithPuppetSubMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_IsModeOnTrack, pThing, mode);
}

int J3DAPI sithPuppet_IsAnyModeOnTrack(const SithThing* pThing, SithPuppetSubMode firstMode, SithPuppetSubMode lastMode)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_IsAnyModeOnTrack, pThing, firstMode, lastMode);
}

SithPuppetTrack* J3DAPI sithPuppet_FindActiveTrack(const SithThing* pThing, const rdKeyframe* pKfTrack)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_FindActiveTrack, pThing, pKfTrack);
}

void J3DAPI sithPuppet_UpdateThingMoveTracks(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_UpdateThingMoveTracks, pThing, secDeltaTime);
}

double J3DAPI sithPuppet_UpdateThingMove(SithThing* pThing, rdPuppetTrackCallback pAxis)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_UpdateThingMove, pThing, pAxis);
}

int J3DAPI sithPuppet_SetSubMode(SithThing* pThing, SithPuppetSubMode newSubMode, rdPuppetTrackCallback pfCallback)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_SetSubMode, pThing, newSubMode, pfCallback);
}

void J3DAPI sithPuppet_SetMoveMode(SithThing* pThing, SithPuppetMoveMode newMode)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_SetMoveMode, pThing, newMode);
}

void J3DAPI sithPuppet_SetArmedMode(SithThing* pThing, unsigned int newMode)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_SetArmedMode, pThing, newMode);
}

// On success trackIdx is returned, 
// -99 is returned when submode already plays 
// and -1 is returned on error e.g. submode doesn't contain animation keyframe 
int J3DAPI sithPuppet_PlayMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_PlayMode, pThing, submode, pfCallback);
}

int J3DAPI sithPuppet_PlayForceMoveMode(SithThing* pThing, SithPuppetSubMode submode, rdPuppetTrackCallback pfCallback)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_PlayForceMoveMode, pThing, submode, pfCallback);
}

int J3DAPI sithPuppet_PlayKey(rdPuppet* pPuppet, rdKeyframe* pTrack, int lowPriority, int highPriority, rdKeyframeFlags flags, rdPuppetTrackCallback pfCallback)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_PlayKey, pPuppet, pTrack, lowPriority, highPriority, flags, pfCallback);
}

unsigned int J3DAPI sithPuppet_GetTrackNumForGUID(const SithThing* pThing, int guid)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_GetTrackNumForGUID, pThing, guid);
}

int J3DAPI sithPuppet_StopKey(rdPuppet* pPuppet, int track, float fadeTime)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_StopKey, pPuppet, track, fadeTime);
}

void J3DAPI sithPuppet_StopForceMove(SithThing* pThing, int bStopTracks)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_StopForceMove, pThing, bStopTracks);
}

void J3DAPI sithPuppet_DefaultCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_DefaultCallback, pThing, track, markerType);
}

int J3DAPI sithPuppet_NDYReadPuppetSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_NDYReadPuppetSection, pWorld, bSkip);
}

int J3DAPI sithPuppet_CNDWritePuppetSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_CNDWritePuppetSection, fh, pWorld);
}

int J3DAPI sithPuppet_CNDReadPuppetSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_CNDReadPuppetSection, fh, pWorld);
}

SithPuppetClass* J3DAPI sithPuppet_LoadPuppetClass(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_LoadPuppetClass, pFilename);
}

int J3DAPI sithPuppet_LoadPuppetClassEntry(SithPuppetClass* pClass, const char* pPath)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_LoadPuppetClassEntry, pClass, pPath);
}

int J3DAPI sithPuppet_AllocWorldPuppets(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_AllocWorldPuppets, pWorld, size);
}

void J3DAPI sithPuppet_FreeWorldPuppets(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_FreeWorldPuppets, pWorld);
}

int J3DAPI sithPuppet_CNDWriteKeyframeSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_CNDWriteKeyframeSection, fh, pWorld);
}

int J3DAPI sithPuppet_CNDReadKeyframeSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_CNDReadKeyframeSection, fh, pWorld);
}

rdKeyframe* J3DAPI sithPuppet_GetKeyframeByIndex(int index)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_GetKeyframeByIndex, index);
}

rdKeyframe* J3DAPI sithPuppet_LoadKeyframe(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_LoadKeyframe, pName);
}

int J3DAPI sithPuppet_AllocWorldKeyframes(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_AllocWorldKeyframes, pWorld, size);
}

void J3DAPI sithPuppet_FreeWorldKeyframes(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_FreeWorldKeyframes, pWorld);
}

int J3DAPI sithPuppet_ClassCacheAdd(const SithPuppetClass* pClass)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_ClassCacheAdd, pClass);
}

int J3DAPI sithPuppet_ClassCacheRemove(const SithPuppetClass* pClass)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_ClassCacheRemove, pClass);
}

rdKeyframe* J3DAPI sithPuppet_GetdKeyframe(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_GetdKeyframe, pName);
}

rdKeyframe* J3DAPI sithPuppet_KeyCacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_KeyCacheFind, pName);
}

void J3DAPI sithPuppet_KeyCacheAdd(rdKeyframe* pKeyframe)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_KeyCacheAdd, pKeyframe);
}

void J3DAPI sithPuppet_KeyCacheRemove(rdKeyframe* pKeyframe)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_KeyCacheRemove, pKeyframe);
}

int J3DAPI sithPuppet_StopMode(SithThing* pThing, SithPuppetSubMode submode, float fadeOutTime)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_StopMode, pThing, submode, fadeOutTime);
}

signed int J3DAPI sithPuppet_SynchMode(SithThing* pThing, SithPuppetSubMode oldMode, SithPuppetSubMode newMode, float a4, int bReverse)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_SynchMode, pThing, oldMode, newMode, a4, bReverse);
}

void J3DAPI sithPuppet_ClearMode(SithThing* pThing, SithPuppetSubMode mode)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_ClearMode, pThing, mode);
}

SithPuppetTrack* J3DAPI sithPuppet_FreeTrackNum(SithThing* pThing, int trackNum)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_FreeTrackNum, pThing, trackNum);
}

int J3DAPI sithPuppet_NewTrack(SithThing* pThing, SithPuppetClassSubmode* pSubmode, int trackNum, SithPuppetSubMode submode)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_NewTrack, pThing, pSubmode, trackNum, submode);
}

void J3DAPI sithPuppet_AddTrack(SithThing* pThing, SithPuppetTrack* pNewTrack)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_AddTrack, pThing, pNewTrack);
}

void J3DAPI sithPuppet_RemoveTrack(SithThing* pThing, SithPuppetTrack* pTrack)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_RemoveTrack, pThing, pTrack);
}

void J3DAPI sithPuppet_RemoveTrackImpl(SithThing* pThing, SithPuppetTrack* pTrack)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_RemoveTrackImpl, pThing, pTrack);
}

void J3DAPI sithPuppet_RemoveTrackNum(SithThing* pThing, int trackNum)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_RemoveTrackNum, pThing, trackNum);
}

SithPuppetTrack* J3DAPI sithPuppet_GetModeTrack(const SithThing* pThing, SithPuppetSubMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_GetModeTrack, pThing, mode);
}

SithPuppetTrack* J3DAPI sithPuppet_GetModeTrackImpl(const SithThing* pThing, SithPuppetSubMode submode)
{
    return J3D_TRAMPOLINE_CALL(sithPuppet_GetModeTrackImpl, pThing, submode);
}

void J3DAPI sithPuppet_FreeEntry(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithPuppet_FreeEntry, pThing);
}
