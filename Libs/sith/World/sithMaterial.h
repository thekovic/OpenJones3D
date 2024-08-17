#ifndef SITH_SITHMATERIAL_H
#define SITH_SITHMATERIAL_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithMaterial_g_pHashtable J3D_DECL_FAR_VAR(sithMaterial_g_pHashtable, tHashTable*)
// extern tHashTable *sithMaterial_g_pHashtable;

int sithMaterial_Startup(void);
void J3DAPI sithMaterial_Shutdown();
void J3DAPI sithMaterial_FreeWorldMaterials(SithWorld* pWorld);
int J3DAPI sithMaterial_CNDWriteMaterialSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithMaterial_CNDReadMaterialSection(tFileHandle fh, SithWorld* pWorld);
rdMaterial* J3DAPI sithMaterial_Load(const char* pName);
rdMaterial* J3DAPI sithMaterial_GetMaterialByIndex(int idx);
int J3DAPI sithMaterial_AllocWorldMaterials(SithWorld* pWorld, int numMaterials);
rdMaterial* J3DAPI sithMaterial_CacheFind(const char* pName);
void J3DAPI sithMaterial_CacheAdd(rdMaterial* pMat);
int J3DAPI sithMaterial_CacheRemove(const rdMaterial* pMat);

// Helper hooking functions
void sithMaterial_InstallHooks(void);
void sithMaterial_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHMATERIAL_H
