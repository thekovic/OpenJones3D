#ifndef SITH_SITHAICLASS_H
#define SITH_SITHAICLASS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithAIClass_g_pHashtable J3D_DECL_FAR_VAR(sithAIClass_g_pHashtable, tHashTable*)
// extern tHashTable *sithAIClass_g_pHashtable;

int sithAIClass_Startup(void);
void J3DAPI sithAIClass_Shutdown();
int J3DAPI sithAIClass_NDYReadAIClassSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithAIClass_CNDWriteAIClassSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithAIClass_CNDReadAIClassSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithAIClass_AllocWorldAIClasses(SithWorld* pWorld, int numClasses);
void J3DAPI sithAIClass_FreeWorldAIClasses(SithWorld* pWorld);
SithAIClass* J3DAPI sithAIClass_Load(SithWorld* pWorld, const char* pName);
int J3DAPI sithAIClass_LoadEntry(const char* pPath, SithAIClass* pClass);
SithAIClass* J3DAPI sithAIClass_CacheFind(const char* pName);
void J3DAPI sithAIClass_CacheAdd(SithAIClass* pClass);
int J3DAPI sithAIClass_CacheRemove(const SithAIClass* pClass);

// Helper hooking functions
void sithAIClass_InstallHooks(void);
void sithAIClass_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHAICLASS_H
