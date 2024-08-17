#include "sithMaterial.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithMaterial_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithMaterial_Startup);
    // J3D_HOOKFUNC(sithMaterial_Shutdown);
    // J3D_HOOKFUNC(sithMaterial_FreeWorldMaterials);
    // J3D_HOOKFUNC(sithMaterial_CNDWriteMaterialSection);
    // J3D_HOOKFUNC(sithMaterial_CNDReadMaterialSection);
    // J3D_HOOKFUNC(sithMaterial_Load);
    // J3D_HOOKFUNC(sithMaterial_GetMaterialByIndex);
    // J3D_HOOKFUNC(sithMaterial_AllocWorldMaterials);
    // J3D_HOOKFUNC(sithMaterial_CacheFind);
    // J3D_HOOKFUNC(sithMaterial_CacheAdd);
    // J3D_HOOKFUNC(sithMaterial_CacheRemove);
}

void sithMaterial_ResetGlobals(void)
{
    memset(&sithMaterial_g_pHashtable, 0, sizeof(sithMaterial_g_pHashtable));
}

int sithMaterial_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_Startup);
}

void J3DAPI sithMaterial_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithMaterial_Shutdown);
}

void J3DAPI sithMaterial_FreeWorldMaterials(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithMaterial_FreeWorldMaterials, pWorld);
}

int J3DAPI sithMaterial_CNDWriteMaterialSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_CNDWriteMaterialSection, fh, pWorld);
}

int J3DAPI sithMaterial_CNDReadMaterialSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_CNDReadMaterialSection, fh, pWorld);
}

rdMaterial* J3DAPI sithMaterial_Load(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_Load, pName);
}

rdMaterial* J3DAPI sithMaterial_GetMaterialByIndex(int idx)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_GetMaterialByIndex, idx);
}

int J3DAPI sithMaterial_AllocWorldMaterials(SithWorld* pWorld, int numMaterials)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_AllocWorldMaterials, pWorld, numMaterials);
}

rdMaterial* J3DAPI sithMaterial_CacheFind(const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_CacheFind, pName);
}

void J3DAPI sithMaterial_CacheAdd(rdMaterial* pMat)
{
    J3D_TRAMPOLINE_CALL(sithMaterial_CacheAdd, pMat);
}

int J3DAPI sithMaterial_CacheRemove(const rdMaterial* pMat)
{
    return J3D_TRAMPOLINE_CALL(sithMaterial_CacheRemove, pMat);
}
