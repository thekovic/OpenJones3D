#include "sithThing.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

// Just static regression test
static_assert(SITHTHING_TYPEMASK(SITH_THING_PLAYER) == 0x400, "SITHTHING_TYPEMASK(SITH_THING_PLAYER) == 0x400");
static_assert(SITHTHING_TYPEMASK(SITH_THING_ACTOR, SITH_THING_PLAYER) == 0x404, "SITHTHING_TYPEMASK(SITH_THING_ACTOR, SITH_THING_PLAYER) == 0x404");
static_assert(SITHTHING_TYPEMASK(SITH_THING_ACTOR, SITH_THING_PLAYER, SITH_THING_WEAPON) == 0x40C, "SITHTHING_TYPEMASK(SITH_THING_ACTOR, SITH_THING_PLAYER, SITH_THING_WEAPON) == 0x40C");

#define sithThing_aStrThingTypes J3D_DECL_FAR_ARRAYVAR(sithThing_aStrThingTypes, const char*(*)[15])
#define sithThing_aStrThingArgs J3D_DECL_FAR_ARRAYVAR(sithThing_aStrThingArgs, const char*(*)[77])
#define sithThing_curSignature J3D_DECL_FAR_VAR(sithThing_curSignature, unsigned int)
#define sithThing_guidEntropy J3D_DECL_FAR_VAR(sithThing_guidEntropy, uint16_t)
#define sithThing_aWeaponCoefficients J3D_DECL_FAR_ARRAYVAR(sithThing_aWeaponCoefficients, float(*)[10])
#define sithThing_jeepHitMinVelocityZ J3D_DECL_FAR_VAR(sithThing_jeepHitMinVelocityZ, float)
#define sithThing_apUnsyncedThings J3D_DECL_FAR_ARRAYVAR(sithThing_apUnsyncedThings, SithThing*(*)[16])
#define sithThing_pParseHashtbl J3D_DECL_FAR_VAR(sithThing_pParseHashtbl, tHashTable*)
#define sithThing_prevQuetzAttachInfo J3D_DECL_FAR_VAR(sithThing_prevQuetzAttachInfo, SithQuetzAttachInfo*)
#define sithThing_aFreeThingIdxs J3D_DECL_FAR_ARRAYVAR(sithThing_aFreeThingIdxs, int(*)[2304])
#define sithThing_curQuetzAttachInfo J3D_DECL_FAR_VAR(sithThing_curQuetzAttachInfo, SithQuetzAttachInfo*)
#define sithThing_aSyncFlags J3D_DECL_FAR_ARRAYVAR(sithThing_aSyncFlags, int(*)[16])
#define sithThing_numUnsyncedThings J3D_DECL_FAR_VAR(sithThing_numUnsyncedThings, int)
#define sithThing_bThingStartup J3D_DECL_FAR_VAR(sithThing_bThingStartup, int)
#define sithThing_pfUnknownFunc J3D_DECL_FAR_VAR(sithThing_pfUnknownFunc, SithThingUnknownFunc)
#define sithThing_dword_5612B8 J3D_DECL_FAR_VAR(sithThing_dword_5612B8, int)

void sithThing_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithThing_Startup);
    // J3D_HOOKFUNC(sithThing_Shutdown);
    // J3D_HOOKFUNC(sithThing_Draw);
    // J3D_HOOKFUNC(sithThing_AddSwapEntry);
    // J3D_HOOKFUNC(sithThing_RemoveSwapEntry);
    // J3D_HOOKFUNC(sithThing_ResetSwapList);
    // J3D_HOOKFUNC(sithThing_Update);
    // J3D_HOOKFUNC(sithThing_UpdatePhysics);
    // J3D_HOOKFUNC(sithThing_Remove);
    // J3D_HOOKFUNC(sithThing_GetThingParent);
    // J3D_HOOKFUNC(sithThing_GetThingByIndex);
    // J3D_HOOKFUNC(sithThing_GetThingIndex);
    // J3D_HOOKFUNC(sithThing_GetGuidThing);
    // J3D_HOOKFUNC(sithThing_DestroyThing);
    // J3D_HOOKFUNC(sithThing_DamageThing);
    // J3D_HOOKFUNC(sithThing_ScaleCombatDamage);
    // J3D_HOOKFUNC(sithThing_PlayCogDamageSound);
    // J3D_HOOKFUNC(sithThing_AllocWorldThings);
    // J3D_HOOKFUNC(sithThing_FreeWorldThings);
    // J3D_HOOKFUNC(sithThing_RemoveAllThings);
    // J3D_HOOKFUNC(sithThing_ResetAllThings);
    // J3D_HOOKFUNC(sithThing_LoadPostProcess);
    // J3D_HOOKFUNC(sithThing_RemoveThing);
    // J3D_HOOKFUNC(sithThing_FreeThing);
    // J3D_HOOKFUNC(sithThing_Initialize);
    // J3D_HOOKFUNC(sithThing_Reset);
    // J3D_HOOKFUNC(sithThing_MoveToSector);
    // J3D_HOOKFUNC(sithThing_ExitSector);
    // J3D_HOOKFUNC(sithThing_EnterWater);
    // J3D_HOOKFUNC(sithThing_ExitWater);
    // J3D_HOOKFUNC(sithThing_Create);
    // J3D_HOOKFUNC(sithThing_SetPositionAndOrient);
    // J3D_HOOKFUNC(sithThing_SetThingModel);
    // J3D_HOOKFUNC(sithThing_SetThingBasedOn);
    // J3D_HOOKFUNC(sithThing_CreateThingAtPos);
    // J3D_HOOKFUNC(sithThing_CreateThing);
    // J3D_HOOKFUNC(sithThing_AttachThingToSurface);
    // J3D_HOOKFUNC(sithThing_AttachThingToClimbSurface);
    // J3D_HOOKFUNC(sithThing_AttachThingToThingFace);
    // J3D_HOOKFUNC(sithThing_AddThingToAttachedThings);
    // J3D_HOOKFUNC(sithThing_AttachThingToThing);
    // J3D_HOOKFUNC(sithThing_AttachThingToThingMesh);
    // J3D_HOOKFUNC(sithThing_DetachThing);
    // J3D_HOOKFUNC(sithThing_DetachAttachedThings);
    // J3D_HOOKFUNC(sithThing_PurgeGarbageThings);
    // J3D_HOOKFUNC(sithThing_NDYReadThingSection);
    // J3D_HOOKFUNC(sithThing_CNDWriteThingSection);
    // J3D_HOOKFUNC(sithThing_CNDReadThingSection);
    // J3D_HOOKFUNC(sithThing_CNDWriteThingList);
    // J3D_HOOKFUNC(sithThing_CNDReadThingList);
    // J3D_HOOKFUNC(sithThing_ParseArg);
    // J3D_HOOKFUNC(sithThing_ParseThingArg);
    // J3D_HOOKFUNC(sithThing_ParseType);
    // J3D_HOOKFUNC(sithThing_ValidateThingPointer);
    // J3D_HOOKFUNC(sithThing_SyncThing);
    // J3D_HOOKFUNC(sithThing_SyncThings);
    // J3D_HOOKFUNC(sithThing_CanSync);
    // J3D_HOOKFUNC(sithThing_GetThingMeshIndex);
    // J3D_HOOKFUNC(sithThing_GetThingJointIndex);
    // J3D_HOOKFUNC(sithThing_FreeThingIndex);
    // J3D_HOOKFUNC(sithThing_GetFreeThingIndex);
    // J3D_HOOKFUNC(sithThing_LoadEntry);
    // J3D_HOOKFUNC(sithThing_CreateQuetzUserBlock);
    // J3D_HOOKFUNC(sithThing_UpdateQuetzUserBlock);
}

void sithThing_ResetGlobals(void)
{
    const char* sithThing_aStrThingTypes_tmp[15] = {
      "free",
      "camera",
      "actor",
      "weapon",
      "debris",
      "item",
      "explosion",
      "cog",
      "ghost",
      "corpse",
      "player",
      "particle",
      "hint",
      "sprite",
      "polyline"
    };
    memcpy((char**)&sithThing_aStrThingTypes, &sithThing_aStrThingTypes_tmp, sizeof(sithThing_aStrThingTypes));

    const char* sithThing_aStrThingArgs_tmp[77] = {
      "--invalid--",
      "type",
      "collide",
      "move",
      "size",
      "thingflags",
      "timer",
      "light",
      "attach",
      "soundclass",
      "model3d",
      "sprite",
      "surfdrag",
      "airdrag",
      "staticdrag",
      "mass",
      "height",
      "physflags",
      "maxrotvel",
      "maxvel",
      "vel",
      "angvel",
      "typeflags",
      "health",
      "maxthrust",
      "maxrotthrust",
      "maxheadvel",
      "maxheadyaw",
      "jumpspeed",
      "weapon",
      "damage",
      "mindamage",
      "damageclass",
      "explode",
      "frame",
      "numframes",
      "puppet",
      "blasttime",
      "babytime",
      "force",
      "maxlight",
      "range",
      "flashrgb",
      "expandtime",
      "fadetime",
      "aiclass",
      "cog",
      "respawn",
      "material",
      "rate",
      "count",
      "elementsize",
      "particle",
      "maxhealth",
      "movesize",
      "orientspeed",
      "buoyancy",
      "eyeoffset",
      "minheadpitch",
      "maxheadpitch",
      "fireoffset",
      "lightoffset",
      "lightintensity",
      "debris",
      "creatething",
      "minsize",
      "pitchrange",
      "yawrange",
      "orient",
      "userval",
      "spritething",
      "spritestart",
      "spriteend",
      "collheight",
      "collwidth",
      "voicecolor",
      "perflevel"
    };
    memcpy((char**)&sithThing_aStrThingArgs, &sithThing_aStrThingArgs_tmp, sizeof(sithThing_aStrThingArgs));

    unsigned int sithThing_curSignature_tmp = 1u;
    memcpy(&sithThing_curSignature, &sithThing_curSignature_tmp, sizeof(sithThing_curSignature));

    uint16_t sithThing_guidEntropy_tmp = 1u;
    memcpy(&sithThing_guidEntropy, &sithThing_guidEntropy_tmp, sizeof(sithThing_guidEntropy));

    float sithThing_aWeaponCoefficients_tmp[10] = {
      0.0f,
      0.0f,
      0.0f,
      0.025f,
      0.050000001f,
      0.059999999f,
      0.059999999f,
      0.0f,
      0.0099999998f,
      0.0f
    };
    memcpy(&sithThing_aWeaponCoefficients, &sithThing_aWeaponCoefficients_tmp, sizeof(sithThing_aWeaponCoefficients));

    float sithThing_jeepHitMinVelocityZ_tmp = -1.65f;
    memcpy(&sithThing_jeepHitMinVelocityZ, &sithThing_jeepHitMinVelocityZ_tmp, sizeof(sithThing_jeepHitMinVelocityZ));

    memset(&sithThing_apUnsyncedThings, 0, sizeof(sithThing_apUnsyncedThings));
    memset(&sithThing_pParseHashtbl, 0, sizeof(sithThing_pParseHashtbl));
    memset(&sithThing_prevQuetzAttachInfo, 0, sizeof(sithThing_prevQuetzAttachInfo));
    memset(&sithThing_aFreeThingIdxs, 0, sizeof(sithThing_aFreeThingIdxs));
    memset(&sithThing_curQuetzAttachInfo, 0, sizeof(sithThing_curQuetzAttachInfo));
    memset(&sithThing_aSyncFlags, 0, sizeof(sithThing_aSyncFlags));
    memset(&sithThing_g_numFreeThings, 0, sizeof(sithThing_g_numFreeThings));
    memset(&sithThing_numUnsyncedThings, 0, sizeof(sithThing_numUnsyncedThings));
    memset(&sithThing_bThingStartup, 0, sizeof(sithThing_bThingStartup));
    memset(&sithThing_pfUnknownFunc, 0, sizeof(sithThing_pfUnknownFunc));
    memset(&sithThing_dword_5612B8, 0, sizeof(sithThing_dword_5612B8));
}

int J3DAPI sithThing_Startup()
{
    return J3D_TRAMPOLINE_CALL(sithThing_Startup);
}

int J3DAPI sithThing_Shutdown()
{
    return J3D_TRAMPOLINE_CALL(sithThing_Shutdown);
}

int J3DAPI sithThing_Draw(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_Draw, pThing);
}

int J3DAPI sithThing_AddSwapEntry(SithThing* pThing, int meshNum, rdModel3* pSrcModel, int meshNumSrc)
{
    return J3D_TRAMPOLINE_CALL(sithThing_AddSwapEntry, pThing, meshNum, pSrcModel, meshNumSrc);
}

int J3DAPI sithThing_RemoveSwapEntry(SithThing* pThing, int refnum)
{
    return J3D_TRAMPOLINE_CALL(sithThing_RemoveSwapEntry, pThing, refnum);
}

void J3DAPI sithThing_ResetSwapList(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_ResetSwapList, pThing);
}

void J3DAPI sithThing_Update(float secDeltaTime, int msecDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithThing_Update, secDeltaTime, msecDeltaTime);
}

void J3DAPI sithThing_UpdatePhysics(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithThing_UpdatePhysics, pThing, secDeltaTime);
}

void J3DAPI sithThing_Remove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_Remove, pThing);
}

SithThing* J3DAPI sithThing_GetThingParent(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetThingParent, pThing);
}

SithThing* J3DAPI sithThing_GetThingByIndex(int idx)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetThingByIndex, idx);
}

int J3DAPI sithThing_GetThingIndex(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetThingIndex, pThing);
}

SithThing* J3DAPI sithThing_GetGuidThing(int guid)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetGuidThing, guid);
}

void J3DAPI sithThing_DestroyThing(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_DestroyThing, pThing);
}

float J3DAPI sithThing_DamageThing(SithThing* pVictim, const SithThing* pPurpetrator, float damage, SithDamageType hitType)
{
    return J3D_TRAMPOLINE_CALL(sithThing_DamageThing, pVictim, pPurpetrator, damage, hitType);
}

float J3DAPI sithThing_ScaleCombatDamage(const SithThing* pThing, SithThing* pHitThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_ScaleCombatDamage, pThing, pHitThing);
}

void J3DAPI sithThing_PlayCogDamageSound(SithThing* pThing, SithDamageType hitType)
{
    J3D_TRAMPOLINE_CALL(sithThing_PlayCogDamageSound, pThing, hitType);
}

int J3DAPI sithThing_AllocWorldThings(SithWorld* pWorld, int numThings)
{
    return J3D_TRAMPOLINE_CALL(sithThing_AllocWorldThings, pWorld, numThings);
}

void J3DAPI sithThing_FreeWorldThings(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithThing_FreeWorldThings, pWorld);
}

void J3DAPI sithThing_RemoveAllThings(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithThing_RemoveAllThings, pWorld);
}

void J3DAPI sithThing_ResetAllThings(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithThing_ResetAllThings, pWorld);
}

void J3DAPI sithThing_LoadPostProcess(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithThing_LoadPostProcess, pWorld);
}

int J3DAPI sithThing_RemoveThing(SithWorld* pWorld, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_RemoveThing, pWorld, pThing);
}

void J3DAPI sithThing_FreeThing(SithWorld* pWorld, SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_FreeThing, pWorld, pThing);
}

void J3DAPI sithThing_Initialize(const SithWorld* pWorld, SithThing* pThing, int bFindFloor)
{
    J3D_TRAMPOLINE_CALL(sithThing_Initialize, pWorld, pThing, bFindFloor);
}

void J3DAPI sithThing_Reset(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_Reset, pThing);
}

void J3DAPI sithThing_MoveToSector(SithThing* pThing, SithSector* pSector, int bNotify)
{
    J3D_TRAMPOLINE_CALL(sithThing_MoveToSector, pThing, pSector, bNotify);
}

void J3DAPI sithThing_ExitSector(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_ExitSector, pThing);
}

void J3DAPI sithThing_EnterWater(SithThing* pThing, int bNoSplash)
{
    J3D_TRAMPOLINE_CALL(sithThing_EnterWater, pThing, bNoSplash);
}

void J3DAPI sithThing_ExitWater(SithThing* pThing, int bNoSplash)
{
    J3D_TRAMPOLINE_CALL(sithThing_ExitWater, pThing, bNoSplash);
}

SithThing* J3DAPI sithThing_Create(SithThingType type)
{
    return J3D_TRAMPOLINE_CALL(sithThing_Create, type);
}

void J3DAPI sithThing_SetPositionAndOrient(SithThing* pThing, const rdVector3* pos, const rdMatrix34* pOrient)
{
    J3D_TRAMPOLINE_CALL(sithThing_SetPositionAndOrient, pThing, pos, pOrient);
}

int J3DAPI sithThing_SetThingModel(SithThing* pThing, rdModel3* pModel)
{
    return J3D_TRAMPOLINE_CALL(sithThing_SetThingModel, pThing, pModel);
}

void J3DAPI sithThing_SetThingBasedOn(SithThing* pThing, const SithThing* pTemplate)
{
    J3D_TRAMPOLINE_CALL(sithThing_SetThingBasedOn, pThing, pTemplate);
}

SithThing* J3DAPI sithThing_CreateThingAtPos(const SithThing* pTemplate, const rdVector3* pos, const rdMatrix34* orient, SithSector* pSector, SithThing* pParent)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CreateThingAtPos, pTemplate, pos, orient, pSector, pParent);
}

SithThing* J3DAPI sithThing_CreateThing(const SithThing* pTemplate, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CreateThing, pTemplate, pThing);
}

void J3DAPI sithThing_AttachThingToSurface(SithThing* pThing, SithSurface* pSurf, int bNoThingStateUpdate)
{
    J3D_TRAMPOLINE_CALL(sithThing_AttachThingToSurface, pThing, pSurf, bNoThingStateUpdate);
}

void J3DAPI sithThing_AttachThingToClimbSurface(SithThing* pThing, SithSurface* pSurf)
{
    J3D_TRAMPOLINE_CALL(sithThing_AttachThingToClimbSurface, pThing, pSurf);
}

void J3DAPI sithThing_AttachThingToThingFace(SithThing* pThing, SithThing* pAttachThing, rdFace* pFace, const rdVector3* aVertices, int bNoThingStateUpdate)
{
    J3D_TRAMPOLINE_CALL(sithThing_AttachThingToThingFace, pThing, pAttachThing, pFace, aVertices, bNoThingStateUpdate);
}

void J3DAPI sithThing_AddThingToAttachedThings(SithThing* pThing, SithThing* pAttachThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_AddThingToAttachedThings, pThing, pAttachThing);
}

void J3DAPI sithThing_AttachThingToThing(SithThing* pThing, SithThing* pAttachThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_AttachThingToThing, pThing, pAttachThing);
}

void J3DAPI sithThing_AttachThingToThingMesh(SithThing* pThing, SithThing* pAttachThing, int meshNum)
{
    J3D_TRAMPOLINE_CALL(sithThing_AttachThingToThingMesh, pThing, pAttachThing, meshNum);
}

void J3DAPI sithThing_DetachThing(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_DetachThing, pThing);
}

void J3DAPI sithThing_DetachAttachedThings(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_DetachAttachedThings, pThing);
}

void J3DAPI sithThing_PurgeGarbageThings(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithThing_PurgeGarbageThings, pWorld);
}

int J3DAPI sithThing_NDYReadThingSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithThing_NDYReadThingSection, pWorld, bSkip);
}

int J3DAPI sithThing_CNDWriteThingSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CNDWriteThingSection, fh, pWorld);
}

int J3DAPI sithThing_CNDReadThingSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CNDReadThingSection, fh, pWorld);
}

int J3DAPI sithThing_CNDWriteThingList(tFileHandle fh, SithWorld* pWorld, unsigned int numThings, SithThing* aThings)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CNDWriteThingList, fh, pWorld, numThings, aThings);
}

int J3DAPI sithThing_CNDReadThingList(tFileHandle fh, SithWorld* pWorld, unsigned int numThings, SithThing* aThings, void (J3DAPI* pfInitThingFunc)(SithThing*))
{
    return J3D_TRAMPOLINE_CALL(sithThing_CNDReadThingList, fh, pWorld, numThings, aThings, pfInitThingFunc);
}

int J3DAPI sithThing_ParseArg(StdConffileArg* pArg, SithWorld* pWorld, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_ParseArg, pArg, pWorld, pThing);
}

int J3DAPI sithThing_ParseThingArg(StdConffileArg* pArg, SithWorld* pWorld, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithThing_ParseThingArg, pArg, pWorld, pThing, adjNum);
}

int J3DAPI sithThing_ParseType(const char* pType)
{
    return J3D_TRAMPOLINE_CALL(sithThing_ParseType, pType);
}

int J3DAPI sithThing_ValidateThingPointer(const SithWorld* pWorld, const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_ValidateThingPointer, pWorld, pThing);
}

void J3DAPI sithThing_SyncThing(SithThing* pThing, int syncFlags)
{
    J3D_TRAMPOLINE_CALL(sithThing_SyncThing, pThing, syncFlags);
}

int J3DAPI sithThing_SyncThings()
{
    return J3D_TRAMPOLINE_CALL(sithThing_SyncThings);
}

int J3DAPI sithThing_CanSync(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CanSync, pThing);
}

int J3DAPI sithThing_GetThingMeshIndex(const SithThing* pThing, const char* meshName)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetThingMeshIndex, pThing, meshName);
}

int J3DAPI sithThing_GetThingJointIndex(const SithThing* pThing, const char* pJointName)
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetThingJointIndex, pThing, pJointName);
}

int J3DAPI sithThing_FreeThingIndex(SithWorld* pWorld, size_t thingNum)
{
    return J3D_TRAMPOLINE_CALL(sithThing_FreeThingIndex, pWorld, thingNum);
}

int J3DAPI sithThing_GetFreeThingIndex()
{
    return J3D_TRAMPOLINE_CALL(sithThing_GetFreeThingIndex);
}

int J3DAPI sithThing_LoadEntry(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithThing_LoadEntry, pWorld);
}

int J3DAPI sithThing_CreateQuetzUserBlock(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithThing_CreateQuetzUserBlock, pThing);
}

void J3DAPI sithThing_UpdateQuetzUserBlock(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithThing_UpdateQuetzUserBlock, pThing);
}
