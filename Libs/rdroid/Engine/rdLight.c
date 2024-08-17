#include "rdLight.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdLight_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdLight_NewEntry);
    // J3D_HOOKFUNC(rdLight_CalcVertexIntensities);
    // J3D_HOOKFUNC(rdLight_CalcFaceIntensity);
    // J3D_HOOKFUNC(rdLight_GetIntensity);
}

void rdLight_ResetGlobals(void)
{

}

int J3DAPI rdLight_NewEntry(rdLight* pLight)
{
    return J3D_TRAMPOLINE_CALL(rdLight_NewEntry, pLight);
}

void J3DAPI rdLight_CalcVertexIntensities(const rdLight** apLights, const rdVector3* aLightPos, size_t numLights, const rdVector3* aVertexNormal, const rdVector3* aVertices, const rdVector4* aVertexColors, rdVector4* aLightColors, size_t numVertices)
{
    J3D_TRAMPOLINE_CALL(rdLight_CalcVertexIntensities, apLights, aLightPos, numLights, aVertexNormal, aVertices, aVertexColors, aLightColors, numVertices);
}

void J3DAPI rdLight_CalcFaceIntensity(const rdLight** apLights, const rdVector3* apLightPos, size_t numLights, const rdFace* pFace, const rdVector3* pNormal, const rdVector3* apVertices, float attenuation, rdVector4* pOutLightColor)
{
    J3D_TRAMPOLINE_CALL(rdLight_CalcFaceIntensity, apLights, apLightPos, numLights, pFace, pNormal, apVertices, attenuation, pOutLightColor);
}

float J3DAPI rdLight_GetIntensity(const rdVector4* pLight)
{
    return J3D_TRAMPOLINE_CALL(rdLight_GetIntensity, pLight);
}
