#ifndef SITH_SITHMODEL_H
#define SITH_SITHMODEL_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithModel_g_pHashtable J3D_DECL_FAR_VAR(sithModel_g_pHashtable, tHashTable*)
// extern tHashTable *sithModel_g_pHashtable;

int sithModel_Startup(void);
void J3DAPI sithModel_Shutdown();
signed int J3DAPI sithModel_NDYReadModelSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithModel_CNDWriteModelSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithModel_CNDReadModelSection(tFileHandle fh, SithWorld* pWorld);
void J3DAPI sithModel_FreeWorldModels(SithWorld* pWorld);
unsigned int J3DAPI sithModel_GetModelMemUsage(const rdModel3* pModel);
int J3DAPI sithModel_AllocWorldModels(SithWorld* pWorld, int size);
rdModel3* J3DAPI sithModel_GetModelByIndex(uint16_t modelIdx);
// TODO: change return type to int
int16_t J3DAPI sithModel_GetModelIndex(const rdModel3* pModel);
rdModel3* J3DAPI sithModel_GetModel(const char* aName);
int J3DAPI sithModel_GetMeshIndex(const rdModel3* pModel, const char* pMeshName);
int J3DAPI sithModel_EnableHiPoly(int bEnabled);
void J3DAPI sithModel_CacheRemove(const rdModel3* pModel);
void J3DAPI sithModel_CacheAdd(rdModel3* pModel);
rdModel3* J3DAPI sithModel_CacheFind(const char* pName);

// Helper hooking functions
void sithModel_InstallHooks(void);
void sithModel_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHMODEL_H
