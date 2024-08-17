#ifndef SITH_SITHPARTICLE_H
#define SITH_SITHPARTICLE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithParticle_g_pHashtable J3D_DECL_FAR_VAR(sithParticle_g_pHashtable, tHashTable*)
// extern tHashTable *sithParticle_g_pHashtable;

int sithParticle_Startup(void);
void J3DAPI sithParticle_Shutdown();
rdParticle* J3DAPI sithParticle_Load(SithWorld* pWorld, const char* pName);
int J3DAPI sithParticle_AllocWorldParticles(SithWorld* pWorld, int size);
int J3DAPI sithParticle_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum);
void J3DAPI sithParticle_Update(SithThing* pThing, float secDeltaTime);
void J3DAPI sithParticle_Initalize(SithThing* pThing);
void J3DAPI sithParticle_Remove(SithThing* pThing);
void J3DAPI sithParticle_Free(SithThing* pThing);
void J3DAPI sithParticle_FreeWorldParticles(SithWorld* pWorld);
rdParticle* J3DAPI sithParticle_CacheFind(const char* pName);
tLinkListNode* J3DAPI sithParticle_CacheAdd(rdParticle* pParticle);
signed int J3DAPI sithParticle_CacheRemove(const rdParticle* pParticle);

// Helper hooking functions
void sithParticle_InstallHooks(void);
void sithParticle_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPARTICLE_H
