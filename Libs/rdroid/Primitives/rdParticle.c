#include "rdParticle.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdParticle_aFaceTexVerts J3D_DECL_FAR_ARRAYVAR(rdParticle_aFaceTexVerts, rdVector2(*)[4])
#define rdParticle_aFaceVerts J3D_DECL_FAR_ARRAYVAR(rdParticle_aFaceVerts, rdVector3(*)[4])
#define rdParticle_aTransformedVertices J3D_DECL_FAR_ARRAYVAR(rdParticle_aTransformedVertices, rdVector3(*)[256])

void rdParticle_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdParticle_New);
    // J3D_HOOKFUNC(rdParticle_NewEntry);
    // J3D_HOOKFUNC(rdParticle_Duplicate);
    // J3D_HOOKFUNC(rdParticle_Free);
    // J3D_HOOKFUNC(rdParticle_FreeEntry);
    // J3D_HOOKFUNC(rdParticle_LoadEntry);
    // J3D_HOOKFUNC(rdParticle_Draw);
}

void rdParticle_ResetGlobals(void)
{
    rdVector2 rdParticle_aFaceTexVerts_tmp[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    memcpy(&rdParticle_aFaceTexVerts, &rdParticle_aFaceTexVerts_tmp, sizeof(rdParticle_aFaceTexVerts));
    
    memset(&rdParticle_aFaceVerts, 0, sizeof(rdParticle_aFaceVerts));
    memset(&rdParticle_aTransformedVertices, 0, sizeof(rdParticle_aTransformedVertices));
}

rdParticle* J3DAPI rdParticle_New(unsigned int num, float size, rdMaterial* pMat, rdLightMode lightMode)
{
    return J3D_TRAMPOLINE_CALL(rdParticle_New, num, size, pMat, lightMode);
}

int J3DAPI rdParticle_NewEntry(rdParticle* pParticle, unsigned int num, float size, rdMaterial* pMaterial, rdLightMode lightMode)
{
    return J3D_TRAMPOLINE_CALL(rdParticle_NewEntry, pParticle, num, size, pMaterial, lightMode);
}

rdParticle* J3DAPI rdParticle_Duplicate(const rdParticle* pOriginal)
{
    return J3D_TRAMPOLINE_CALL(rdParticle_Duplicate, pOriginal);
}

void J3DAPI rdParticle_Free(rdParticle* pParticle)
{
    J3D_TRAMPOLINE_CALL(rdParticle_Free, pParticle);
}

void J3DAPI rdParticle_FreeEntry(rdParticle* pParticle)
{
    J3D_TRAMPOLINE_CALL(rdParticle_FreeEntry, pParticle);
}

int J3DAPI rdParticle_LoadEntry(const char* pFilename, rdParticle* pParticle)
{
    return J3D_TRAMPOLINE_CALL(rdParticle_LoadEntry, pFilename, pParticle);
}

int J3DAPI rdParticle_Draw(const rdThing* pParticle, const rdMatrix34* pOrient)
{
    return J3D_TRAMPOLINE_CALL(rdParticle_Draw, pParticle, pOrient);
}
