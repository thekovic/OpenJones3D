#include "sithModel.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithModel_bHiPoly J3D_DECL_FAR_VAR(sithModel_bHiPoly, int)

void sithModel_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithModel_Startup);
    // J3D_HOOKFUNC(sithModel_Shutdown);
    // J3D_HOOKFUNC(sithModel_NDYReadModelSection);
    // J3D_HOOKFUNC(sithModel_CNDWriteModelSection);
    // J3D_HOOKFUNC(sithModel_CNDReadModelSection);
    // J3D_HOOKFUNC(sithModel_FreeWorldModels);
    // J3D_HOOKFUNC(sithModel_Load);
    // J3D_HOOKFUNC(sithModel_GetModelMemUsage);
    // J3D_HOOKFUNC(sithModel_AllocWorldModels);
    // J3D_HOOKFUNC(sithModel_GetModelByIndex);
    // J3D_HOOKFUNC(sithModel_GetModelIndex);
    // J3D_HOOKFUNC(sithModel_GetModel);
    // J3D_HOOKFUNC(sithModel_GetMeshIndex);
    // J3D_HOOKFUNC(sithModel_EnableHiPoly);
    // J3D_HOOKFUNC(sithModel_CacheRemove);
    // J3D_HOOKFUNC(sithModel_CacheAdd);
    // J3D_HOOKFUNC(sithModel_CacheFind);
}

void sithModel_ResetGlobals(void)
{
    memset(&sithModel_g_pHashtable, 0, sizeof(sithModel_g_pHashtable));
    memset(&sithModel_bHiPoly, 0, sizeof(sithModel_bHiPoly));
}

int sithModel_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithModel_Startup);
}

void J3DAPI sithModel_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithModel_Shutdown);
}

signed int J3DAPI sithModel_NDYReadModelSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithModel_NDYReadModelSection, pWorld, bSkip);
}

int J3DAPI sithModel_CNDWriteModelSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithModel_CNDWriteModelSection, fh, pWorld);
}

int J3DAPI sithModel_CNDReadModelSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithModel_CNDReadModelSection, fh, pWorld);
}

void J3DAPI sithModel_FreeWorldModels(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithModel_FreeWorldModels, pWorld);
}

rdModel3* J3DAPI sithModel_Load(const char* pName, int bOnErrorSkipDefault)
{
    return  J3D_TRAMPOLINE_CALL(sithModel_Load, pName, bOnErrorSkipDefault);
}

unsigned int J3DAPI sithModel_GetModelMemUsage(const rdModel3* pModel)
{
    return J3D_TRAMPOLINE_CALL(sithModel_GetModelMemUsage, pModel);
}

int J3DAPI sithModel_AllocWorldModels(SithWorld* pWorld, int size)
{
    return J3D_TRAMPOLINE_CALL(sithModel_AllocWorldModels, pWorld, size);
}

rdModel3* J3DAPI sithModel_GetModelByIndex(uint16_t modelIdx)
{
    return J3D_TRAMPOLINE_CALL(sithModel_GetModelByIndex, modelIdx);
}

// TODO: change return type to int
int16_t J3DAPI sithModel_GetModelIndex(const rdModel3* pModel)
{
    return J3D_TRAMPOLINE_CALL(sithModel_GetModelIndex, pModel);
}

rdModel3* J3DAPI sithModel_GetModel(const char* aName)
{
    return J3D_TRAMPOLINE_CALL(sithModel_GetModel, aName);
}

int J3DAPI sithModel_GetMeshIndex(const rdModel3* pModel, const char* pMeshName)
{
    return J3D_TRAMPOLINE_CALL(sithModel_GetMeshIndex, pModel, pMeshName);
}

int J3DAPI sithModel_EnableHiPoly(int bEnabled)
{
    return J3D_TRAMPOLINE_CALL(sithModel_EnableHiPoly, bEnabled);
}

void J3DAPI sithModel_CacheRemove(const rdModel3* pModel)
{
    J3D_TRAMPOLINE_CALL(sithModel_CacheRemove, pModel);
}

void J3DAPI sithModel_CacheAdd(rdModel3* pModel)
{
    J3D_TRAMPOLINE_CALL(sithModel_CacheAdd, pModel);
}

rdModel3* J3DAPI sithModel_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithModel_CacheFind, pName);
}
