#include "rdMaterial.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdMaterial_pfMaterialLoader J3D_DECL_FAR_VAR(rdMaterial_pfMaterialLoader, rdMaterialLoaderFunc)
#define rdMaterial_pfMaterialUnloader J3D_DECL_FAR_VAR(rdMaterial_pfMaterialUnloader, rdMaterialUnloaderFunc)

void rdMaterial_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdMaterial_RegisterLoader);
    // J3D_HOOKFUNC(rdMaterial_Load);
    // J3D_HOOKFUNC(rdMaterial_LoadEntry);
    // J3D_HOOKFUNC(rdMaterial_Free);
    // J3D_HOOKFUNC(rdMaterial_FreeEntry);
    // J3D_HOOKFUNC(rdMaterial_GetMaterialMemUsage);
    // J3D_HOOKFUNC(rdMaterial_GetMipSize);
}

void rdMaterial_ResetGlobals(void)
{
    memset(&rdMaterial_pfMaterialLoader, 0, sizeof(rdMaterial_pfMaterialLoader));
    memset(&rdMaterial_pfMaterialUnloader, 0, sizeof(rdMaterial_pfMaterialUnloader));
}

rdMaterialLoaderFunc J3DAPI rdMaterial_RegisterLoader(rdMaterialLoaderFunc pFunc)
{
    return J3D_TRAMPOLINE_CALL(rdMaterial_RegisterLoader, pFunc);
}

rdMaterial* J3DAPI rdMaterial_Load(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(rdMaterial_Load, pFilename);
}

int J3DAPI rdMaterial_LoadEntry(const char* pFilename, rdMaterial* pMat)
{
    return J3D_TRAMPOLINE_CALL(rdMaterial_LoadEntry, pFilename, pMat);
}

void J3DAPI rdMaterial_Free(rdMaterial* pMaterial)
{
    J3D_TRAMPOLINE_CALL(rdMaterial_Free, pMaterial);
}

void J3DAPI rdMaterial_FreeEntry(rdMaterial* pMaterial)
{
    J3D_TRAMPOLINE_CALL(rdMaterial_FreeEntry, pMaterial);
}

size_t J3DAPI rdMaterial_GetMaterialMemUsage(const rdMaterial* pMaterial)
{
    return J3D_TRAMPOLINE_CALL(rdMaterial_GetMaterialMemUsage, pMaterial);
}

size_t J3DAPI rdMaterial_GetMipSize(int width, int height, int mipLevels)
{
    return J3D_TRAMPOLINE_CALL(rdMaterial_GetMipSize, width, height, mipLevels);
}
