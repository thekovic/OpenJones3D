#include "sithTemplate.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithTemplate_bMasterFileInitialized J3D_DECL_FAR_VAR(sithTemplate_bMasterFileInitialized, int)
#define sithTemplate_pMasterFile J3D_DECL_FAR_VAR(sithTemplate_pMasterFile, tHashTable*)

void sithTemplate_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithTemplate_Startup);
    // J3D_HOOKFUNC(sithTemplate_Shutdown);
    // J3D_HOOKFUNC(sithTemplate_AllocWorldTemplates);
    // J3D_HOOKFUNC(sithTemplate_GetTemplateByIndex);
    // J3D_HOOKFUNC(sithTemplate_GetTemplateIndex);
    // J3D_HOOKFUNC(sithTemplate_NDYReadTemplateSection);
    // J3D_HOOKFUNC(sithTemplate_CNDWriteTemplateSection);
    // J3D_HOOKFUNC(sithTemplate_CNDReadTemplateSection);
    // J3D_HOOKFUNC(sithTemplate_AddTemplate);
    // J3D_HOOKFUNC(sithTemplate_FreeWorldTemplates);
    // J3D_HOOKFUNC(sithTemplate_Parse);
    // J3D_HOOKFUNC(sithTemplate_CacheFind);
    // J3D_HOOKFUNC(sithTemplate_CacheAdd);
    // J3D_HOOKFUNC(sithTemplate_CacheRemove);
    // J3D_HOOKFUNC(sithTemplate_NDYReadTemplateList);
}

void sithTemplate_ResetGlobals(void)
{
    memset(&sithTemplate_g_pHashtable, 0, sizeof(sithTemplate_g_pHashtable));
    memset(&sithTemplate_bMasterFileInitialized, 0, sizeof(sithTemplate_bMasterFileInitialized));
    memset(&sithTemplate_pMasterFile, 0, sizeof(sithTemplate_pMasterFile));
}

int sithTemplate_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_Startup);
}

void J3DAPI sithTemplate_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithTemplate_Shutdown);
}

int J3DAPI sithTemplate_AllocWorldTemplates(SithWorld* pWorld, unsigned int size)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_AllocWorldTemplates, pWorld, size);
}

SithThing* J3DAPI sithTemplate_GetTemplateByIndex(int idx)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_GetTemplateByIndex, idx);
}

int J3DAPI sithTemplate_GetTemplateIndex(const SithThing* pTemplate)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_GetTemplateIndex, pTemplate);
}

int J3DAPI sithTemplate_NDYReadTemplateSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_NDYReadTemplateSection, pWorld, bSkip);
}

int J3DAPI sithTemplate_CNDWriteTemplateSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_CNDWriteTemplateSection, fh, pWorld);
}

int J3DAPI sithTemplate_CNDReadTemplateSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_CNDReadTemplateSection, fh, pWorld);
}

void J3DAPI sithTemplate_AddTemplate(SithThing* pTemplate)
{
    J3D_TRAMPOLINE_CALL(sithTemplate_AddTemplate, pTemplate);
}

void J3DAPI sithTemplate_FreeWorldTemplates(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithTemplate_FreeWorldTemplates, pWorld);
}

SithThing* J3DAPI sithTemplate_Parse(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_Parse, pWorld);
}

SithThing* J3DAPI sithTemplate_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_CacheFind, pName);
}

void J3DAPI sithTemplate_CacheAdd(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithTemplate_CacheAdd, pThing);
}

void J3DAPI sithTemplate_CacheRemove(const SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithTemplate_CacheRemove, pThing);
}

int J3DAPI sithTemplate_NDYReadTemplateList(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithTemplate_NDYReadTemplateList, pWorld);
}
