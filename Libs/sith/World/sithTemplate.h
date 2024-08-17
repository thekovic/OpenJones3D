#ifndef SITH_SITHTEMPLATE_H
#define SITH_SITHTEMPLATE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithTemplate_g_pHashtable J3D_DECL_FAR_VAR(sithTemplate_g_pHashtable, tHashTable*)
// extern tHashTable *sithTemplate_g_pHashtable;

int sithTemplate_Startup(void);
void J3DAPI sithTemplate_Shutdown();
int J3DAPI sithTemplate_AllocWorldTemplates(SithWorld* pWorld, unsigned int size);
SithThing* J3DAPI sithTemplate_GetTemplateByIndex(int idx);
int J3DAPI sithTemplate_GetTemplateIndex(const SithThing* pTemplate);
int J3DAPI sithTemplate_NDYReadTemplateSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithTemplate_CNDWriteTemplateSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithTemplate_CNDReadTemplateSection(tFileHandle fh, SithWorld* pWorld);
void J3DAPI sithTemplate_AddTemplate(SithThing* pTemplate);
void J3DAPI sithTemplate_FreeWorldTemplates(SithWorld* pWorld);
SithThing* J3DAPI sithTemplate_Parse(SithWorld* pWorld);
SithThing* J3DAPI sithTemplate_CacheFind(const char* pName);
void J3DAPI sithTemplate_CacheAdd(SithThing* pThing);
void J3DAPI sithTemplate_CacheRemove(const SithThing* pThing);
int J3DAPI sithTemplate_NDYReadTemplateList(SithWorld* pWorld);

// Helper hooking functions
void sithTemplate_InstallHooks(void);
void sithTemplate_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHTEMPLATE_H
