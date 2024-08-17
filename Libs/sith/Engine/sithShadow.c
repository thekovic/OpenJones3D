#include "sithShadow.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithShadow_aShadowUVs J3D_DECL_FAR_ARRAYVAR(sithShadow_aShadowUVs, rdVector2(*)[4])
#define sithShadow_aTransformedVertices J3D_DECL_FAR_ARRAYVAR(sithShadow_aTransformedVertices, rdVector3(*)[4])
#define sithShadow_aVertices J3D_DECL_FAR_ARRAYVAR(sithShadow_aVertices, rdVector3(*)[4])

void sithShadow_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithShadow_RenderThingShadow);
    // J3D_HOOKFUNC(sithShadow_SearchForAttachDistance);
    // J3D_HOOKFUNC(sithShadow_DistanceThingToSurface);
    // J3D_HOOKFUNC(sithShadow_DrawShadow);
    // J3D_HOOKFUNC(sithShadow_DrawWalkShadow);
}

void sithShadow_ResetGlobals(void)
{
    rdVector2 sithShadow_aShadowUVs_tmp[4] = { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f } };
    memcpy(&sithShadow_aShadowUVs, &sithShadow_aShadowUVs_tmp, sizeof(sithShadow_aShadowUVs));
    
    memset(&sithShadow_aTransformedVertices, 0, sizeof(sithShadow_aTransformedVertices));
    memset(&sithShadow_aVertices, 0, sizeof(sithShadow_aVertices));
}

void J3DAPI sithShadow_RenderThingShadow(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithShadow_RenderThingShadow, pThing);
}

int J3DAPI sithShadow_SearchForAttachDistance(SithThing* pThing, float* distance, float* radius)
{
    return J3D_TRAMPOLINE_CALL(sithShadow_SearchForAttachDistance, pThing, distance, radius);
}

double J3DAPI sithShadow_DistanceThingToSurface(const SithThing* pThing, const rdVector3* normal, const rdFace* pFace)
{
    return J3D_TRAMPOLINE_CALL(sithShadow_DistanceThingToSurface, pThing, normal, pFace);
}

void J3DAPI sithShadow_DrawShadow(const rdMatrix34* orient, float size, float scale, int bCar)
{
    J3D_TRAMPOLINE_CALL(sithShadow_DrawShadow, orient, size, scale, bCar);
}

void J3DAPI sithShadow_DrawWalkShadow(float size, float scale, rdVector3* leg, rdVector3* rleg, rdVector3* lvec, rdVector3* rvec)
{
    J3D_TRAMPOLINE_CALL(sithShadow_DrawWalkShadow, size, scale, leg, rleg, lvec, rvec);
}
