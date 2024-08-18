#ifndef SITH_SITHTHING_H
#define SITH_SITHTHING_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>

#include <std/types.h>
#include <std/General/stdConffile.h>

J3D_EXTERN_C_START

#define sithThing_g_numFreeThings J3D_DECL_FAR_VAR(sithThing_g_numFreeThings, size_t)
// extern size_t sithThing_g_numFreeThings;

int J3DAPI sithThing_Startup();
int J3DAPI sithThing_Shutdown();
int J3DAPI sithThing_Draw(SithThing* pThing);
int J3DAPI sithThing_AddSwapEntry(SithThing* pThing, int meshNum, rdModel3* pSrcModel, int meshNumSrc);
int J3DAPI sithThing_RemoveSwapEntry(SithThing* pThing, int refnum);
void J3DAPI sithThing_ResetSwapList(SithThing* pThing);
void J3DAPI sithThing_Update(float secDeltaTime, int msecDeltaTime);
void J3DAPI sithThing_UpdatePhysics(SithThing* pThing, float secDeltaTime);
void J3DAPI sithThing_Remove(SithThing* pThing);
SithThing* J3DAPI sithThing_GetThingParent(const SithThing* pThing);
SithThing* J3DAPI sithThing_GetThingByIndex(int idx);
int J3DAPI sithThing_GetThingIndex(const SithThing* pThing);
SithThing* J3DAPI sithThing_GetGuidThing(int guid);
void J3DAPI sithThing_DestroyThing(SithThing* pThing);
float J3DAPI sithThing_DamageThing(SithThing* pVictim, const SithThing* pPurpetrator, float damage, SithDamageType hitType);
float J3DAPI sithThing_ScaleCombatDamage(const SithThing* pThing, SithThing* pHitThing);
void J3DAPI sithThing_PlayCogDamageSound(SithThing* pThing, SithDamageType hitType);
int J3DAPI sithThing_AllocWorldThings(SithWorld* pWorld, int numThings);
void J3DAPI sithThing_FreeWorldThings(SithWorld* pWorld);
void J3DAPI sithThing_RemoveAllThings(SithWorld* pWorld);
void J3DAPI sithThing_ResetAllThings(SithWorld* pWorld);
void J3DAPI sithThing_LoadPostProcess(SithWorld* pWorld);
int J3DAPI sithThing_RemoveThing(SithWorld* pWorld, SithThing* pThing);
void J3DAPI sithThing_FreeThing(SithWorld* pWorld, SithThing* pThing);
void J3DAPI sithThing_Initialize(const SithWorld* pWorld, SithThing* pThing, int bFindFloor);
void J3DAPI sithThing_Reset(SithThing* pThing);
void J3DAPI sithThing_MoveToSector(SithThing* pThing, SithSector* pSector, int bNotify);
void J3DAPI sithThing_ExitSector(SithThing* pThing);
void J3DAPI sithThing_EnterWater(SithThing* pThing, int bNoSplash);
void J3DAPI sithThing_ExitWater(SithThing* pThing, int bNoSplash);
SithThing* J3DAPI sithThing_Create(SithThingType type);
void J3DAPI sithThing_SetPositionAndOrient(SithThing* pThing, const rdVector3* pos, const rdMatrix34* pOrient);
int J3DAPI sithThing_SetThingModel(SithThing* pThing, rdModel3* pModel);
void J3DAPI sithThing_SetThingBasedOn(SithThing* pThing, const SithThing* pTemplate);
SithThing* J3DAPI sithThing_CreateThingAtPos(const SithThing* pTemplate, const rdVector3* pos, const rdMatrix34* orient, SithSector* pSector, SithThing* pParent);
SithThing* J3DAPI sithThing_CreateThing(const SithThing* pTemplate, SithThing* pThing);
void J3DAPI sithThing_AttachThingToSurface(SithThing* pThing, SithSurface* pSurf, int bNoThingStateUpdate);
void J3DAPI sithThing_AttachThingToClimbSurface(SithThing* pThing, SithSurface* pSurf);
void J3DAPI sithThing_AttachThingToThingFace(SithThing* pThing, SithThing* pAttachThing, rdFace* pFace, const rdVector3* aVertices, int bNoThingStateUpdate);
void J3DAPI sithThing_AddThingToAttachedThings(SithThing* pThing, SithThing* pAttachThing);
void J3DAPI sithThing_AttachThingToThing(SithThing* pThing, SithThing* pAttachThing);
void J3DAPI sithThing_AttachThingToThingMesh(SithThing* pThing, SithThing* pAttachThing, int meshNum);
void J3DAPI sithThing_DetachThing(SithThing* pThing);
void J3DAPI sithThing_DetachAttachedThings(SithThing* pThing);
void J3DAPI sithThing_PurgeGarbageThings(SithWorld* pWorld);
int J3DAPI sithThing_NDYReadThingSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithThing_CNDWriteThingSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithThing_CNDReadThingSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithThing_CNDWriteThingList(tFileHandle fh, SithWorld* pWorld, unsigned int numThings, SithThing* aThings);
int J3DAPI sithThing_CNDReadThingList(tFileHandle fh, SithWorld* pWorld, unsigned int numThings, SithThing* aThings, void (J3DAPI* pfInitThingFunc)(SithThing*));
int J3DAPI sithThing_ParseArg(StdConffileArg* pArg, SithWorld* pWorld, SithThing* pThing);
int J3DAPI sithThing_ParseThingArg(StdConffileArg* pArg, SithWorld* pWorld, SithThing* pThing, int adjNum);
int J3DAPI sithThing_ParseType(const char* pType);
int J3DAPI sithThing_ValidateThingPointer(const SithWorld* pWorld, const SithThing* pThing);
void J3DAPI sithThing_SyncThing(SithThing* pThing, int syncFlags);
int J3DAPI sithThing_SyncThings();
int J3DAPI sithThing_CanSync(const SithThing* pThing);
int J3DAPI sithThing_GetThingMeshIndex(const SithThing* pThing, const char* meshName);
int J3DAPI sithThing_GetThingJointIndex(const SithThing* pThing, const char* pJointName);
int J3DAPI sithThing_FreeThingIndex(SithWorld* pWorld, size_t thingNum);
int J3DAPI sithThing_GetFreeThingIndex();
int J3DAPI sithThing_LoadEntry(SithWorld* pWorld);
int J3DAPI sithThing_CreateQuetzUserBlock(SithThing* pThing);
void J3DAPI sithThing_UpdateQuetzUserBlock(SithThing* pThing);

// Helper hooking functions
void sithThing_InstallHooks(void);
void sithThing_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHTHING_H
