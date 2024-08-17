#include "sithSoundClass.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithSoundClass_aSoundModeNames J3D_DECL_FAR_ARRAYVAR(sithSoundClass_aSoundModeNames, char*(*)[141])
#define sithSoundClass_lastStartEntry J3D_DECL_FAR_VAR(sithSoundClass_lastStartEntry, int)
#define sithSoundClass_pHashTable J3D_DECL_FAR_VAR(sithSoundClass_pHashTable, tHashTable*)
#define sithSoundClass_pHashtblModes J3D_DECL_FAR_VAR(sithSoundClass_pHashtblModes, tHashTable*)

void sithSoundClass_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSoundClass_Startup);
    // J3D_HOOKFUNC(sithSoundClass_Shutdown);
    // J3D_HOOKFUNC(sithSoundClass_NDYReadSoundClassSection);
    // J3D_HOOKFUNC(sithSoundClass_CNDWriteSoundClassSection);
    // J3D_HOOKFUNC(sithSoundClass_CNDReadSoundClassSection);
    // J3D_HOOKFUNC(sithSoundClass_Load);
    // J3D_HOOKFUNC(sithSoundClass_LoadEntry);
    // J3D_HOOKFUNC(sithSoundClass_AllocSoundClasses);
    // J3D_HOOKFUNC(sithSoundClass_FreeWorldSoundClasses);
    // J3D_HOOKFUNC(sithSoundClass_PlayModeFirstEx);
    // J3D_HOOKFUNC(sithSoundClass_PlayModeFirst);
    // J3D_HOOKFUNC(sithSoundClass_PlayModeRandom);
    // J3D_HOOKFUNC(sithSoundClass_PlayVoiceModeRandom);
    // J3D_HOOKFUNC(sithSoundClass_PlayPlayerVoiceModeRandom);
    // J3D_HOOKFUNC(sithSoundClass_PlayMode);
    // J3D_HOOKFUNC(sithSoundClass_StopMode);
    // J3D_HOOKFUNC(sithSoundClass_SetModePitch);
    // J3D_HOOKFUNC(sithSoundClass_SetModeVolume);
    // J3D_HOOKFUNC(sithSoundClass_FadeModeVolume);
    // J3D_HOOKFUNC(sithSoundClass_IsModeFadingVol);
    // J3D_HOOKFUNC(sithSoundClass_PlayModeEntry);
    // J3D_HOOKFUNC(sithSoundClass_CacheFind);
    // J3D_HOOKFUNC(sithSoundClass_CacheAdd);
    // J3D_HOOKFUNC(sithSoundClass_CacheRemove);
}

void sithSoundClass_ResetGlobals(void)
{
    char *sithSoundClass_aSoundModeNames_tmp[141] = {
      "--reserved--",
      "create",
      "activate",
      "startmove",
      "stopmove",
      "moving",
      "lwalkhard",
      "rwalkhard",
      "lrunhard",
      "rrunhard",
      "lwalkmetal",
      "rwalkmetal",
      "lrunmetal",
      "rrunmetal",
      "lwalkwater",
      "rwalkwater",
      "lrunwater",
      "rrunwater",
      "lwalkpuddle",
      "rwalkpuddle",
      "lrunpuddle",
      "rrunpuddle",
      "lwalkearth",
      "rwalkearth",
      "lrunearth",
      "rrunearth",
      "lwalksnow",
      "rwalksnow",
      "lrunsnow",
      "rrunsnow",
      "lwalkwood",
      "rwalkwood",
      "lrunwood",
      "rrunwood",
      "lwalkhardecho",
      "rwalkhardecho",
      "lrunhardecho",
      "rrunhardecho",
      "lwalkwoodecho",
      "rwalkwoodecho",
      "lrunwoodecho",
      "rrunwoodecho",
      "lwalkearthecho",
      "rwalkearthecho",
      "lrunearthecho",
      "rrunearthecho",
      "lwalkaet",
      "rwalkaet",
      "lrunaet",
      "rrunaet",
      "enterwater",
      "enterwaterslow",
      "exitwater",
      "exitwaterslow",
      "lswimsurface",
      "rswimsurface",
      "treadsurface",
      "lswimunder",
      "rswimunder",
      "treadunder",
      "jump",
      "jumpmetal",
      "jumpwater",
      "jumpearth",
      "jumpsnow",
      "jumpwood",
      "jumphardecho",
      "jumpwoodecho",
      "jumpearthecho",
      "jumpaet",
      "landhard",
      "landmetal",
      "landwater",
      "landpuddle",
      "landearth",
      "landsnow",
      "landwood",
      "landhardecho",
      "landwoodecho",
      "landearthecho",
      "landaet",
      "landhurt",
      "hithard",
      "hitmetal",
      "hitearth",
      "deflected",
      "scrapehard",
      "scrapemetal",
      "scrapeearth",
      "hitdamaged",
      "falling",
      "corpsehit",
      "hurtimpact",
      "hurtenergy",
      "hurtfire",
      "hurtfists",
      "hurtmachete",
      "drowning",
      "death1",
      "death2",
      "deathunder",
      "drowned",
      "splattered",
      "pant",
      "breath",
      "gasp",
      "fire1",
      "fire2",
      "fire3",
      "fire4",
      "curious",
      "alert",
      "idle",
      "gloat",
      "fear",
      "boast",
      "slide1",
      "victory",
      "help",
      "flee",
      "search",
      "calm",
      "surprise",
      "reserved1",
      "reserved2",
      "reserved3",
      "reserved4",
      "reserved5",
      "reserved6",
      "reserved7",
      "reserved8",
      "stand2walk",
      "walk2stand",
      "climbhandleft",
      "climbhandright",
      "climbhoriz",
      "climbonto",
      "climbdownonto",
      "lswimaet",
      "rswimaet",
      "treadaet"
    };
    memcpy(&sithSoundClass_aSoundModeNames, &sithSoundClass_aSoundModeNames_tmp, sizeof(sithSoundClass_aSoundModeNames));
    
    int sithSoundClass_lastStartEntry_tmp = 1000;
    memcpy(&sithSoundClass_lastStartEntry, &sithSoundClass_lastStartEntry_tmp, sizeof(sithSoundClass_lastStartEntry));
    
    memset(&sithSoundClass_pHashTable, 0, sizeof(sithSoundClass_pHashTable));
    memset(&sithSoundClass_pHashtblModes, 0, sizeof(sithSoundClass_pHashtblModes));
}

int sithSoundClass_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_Startup);
}

void J3DAPI sithSoundClass_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_Shutdown);
}

int J3DAPI sithSoundClass_NDYReadSoundClassSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_NDYReadSoundClassSection, pWorld, bSkip);
}

int J3DAPI sithSoundClass_CNDWriteSoundClassSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_CNDWriteSoundClassSection, fh, pWorld);
}

int J3DAPI sithSoundClass_CNDReadSoundClassSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_CNDReadSoundClassSection, fh, pWorld);
}

SithSoundClass* J3DAPI sithSoundClass_Load(SithWorld* pWorld, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_Load, pWorld, pName);
}

int J3DAPI sithSoundClass_LoadEntry(SithWorld* pWorld, SithSoundClass* pClass, const char* pPath)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_LoadEntry, pWorld, pClass, pPath);
}

signed int J3DAPI sithSoundClass_AllocSoundClasses(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_AllocSoundClasses, pWorld, size);
}

void J3DAPI sithSoundClass_FreeWorldSoundClasses(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_FreeWorldSoundClasses, pWorld);
}

// Returns sound channel
//  handle
tSoundChannelHandle J3DAPI sithSoundClass_PlayModeFirstEx(SithThing* pThing, SithSoundClassMode mode, float volume)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayModeFirstEx, pThing, mode, volume);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayModeFirst(SithThing* pThing, SithSoundClassMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayModeFirst, pThing, mode);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayModeRandom(SithThing* pThing, SithSoundClassMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayModeRandom, pThing, mode);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayVoiceModeRandom(SithThing* pThing, SithSoundClassMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayVoiceModeRandom, pThing, mode);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayPlayerVoiceModeRandom(SithThing* pThing, SithSoundClassMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayPlayerVoiceModeRandom, pThing, mode);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayMode(SithThing* pThing, SithSoundClassMode mode, float a3)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayMode, pThing, mode, a3);
}

void J3DAPI sithSoundClass_StopMode(SithThing* pThing, SithSoundClassMode mode)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_StopMode, pThing, mode);
}

void J3DAPI sithSoundClass_SetModePitch(SithThing* pThing, SithSoundClassMode mode, float pitch)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_SetModePitch, pThing, mode, pitch);
}

void J3DAPI sithSoundClass_SetModeVolume(SithThing* pThing, SithSoundClassMode mode, float volume)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_SetModeVolume, pThing, mode, volume);
}

void J3DAPI sithSoundClass_FadeModeVolume(SithThing* pThing, SithSoundClassMode mode, float startVolume, float endVolume)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_FadeModeVolume, pThing, mode, startVolume, endVolume);
}

unsigned int J3DAPI sithSoundClass_IsModeFadingVol(SithThing* pThing, SithSoundClassMode mode)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_IsModeFadingVol, pThing, mode);
}

tSoundChannelHandle J3DAPI sithSoundClass_PlayModeEntry(SithThing* pThing, SithSoundClassMode mode, SithSoundClassEntry* pEntry, float volume)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_PlayModeEntry, pThing, mode, pEntry, volume);
}

SithSoundClass* J3DAPI sithSoundClass_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithSoundClass_CacheFind, pName);
}

void J3DAPI sithSoundClass_CacheAdd(SithSoundClass* pClass)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_CacheAdd, pClass);
}

void J3DAPI sithSoundClass_CacheRemove(const SithSoundClass* pClass)
{
    J3D_TRAMPOLINE_CALL(sithSoundClass_CacheRemove, pClass);
}
