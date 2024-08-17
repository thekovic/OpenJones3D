#include "sithCogFunctionSurface.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogFunctionSurface_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionSurface_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetAdjoinAlpha);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetAdjoinAlpha);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceAdjoin);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceSector);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetNumSurfaceVertices);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceVertexPos);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetHorizonSkyOffset);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetHorizonSkyOffset);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetCeilingSkyOffset);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetCeilingSkyOffset);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SlideHorizonSky);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SlideCeilingSky);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SurfaceLightAnim);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SlideWall);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetWallCel);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetWallCel);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceMaterial);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetSurfaceMaterial);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetSurfaceFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_ClearSurfaceFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetAdjoinFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_ClearAdjoinFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetAdjoinFlags);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetFaceType);
    // J3D_HOOKFUNC(sithCogFunctionSurface_ClearFaceType);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetFaceType);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetFaceGeoMode);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetFaceGeoMode);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetFaceLightMode);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetFaceLightMode);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SetSurfaceLight);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceLight);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceCenter);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceCount);
    // J3D_HOOKFUNC(sithCogFunctionSurface_GetSurfaceNormal);
    // J3D_HOOKFUNC(sithCogFunctionSurface_SyncSurface);
}

void sithCogFunctionSurface_ResetGlobals(void)
{

}

void J3DAPI sithCogFunctionSurface_RegisterFunctions(SithCogSymbolTable* pTbl)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_RegisterFunctions, pTbl);
}

void J3DAPI sithCogFunctionSurface_GetAdjoinAlpha(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetAdjoinAlpha, pCog);
}

void J3DAPI sithCogFunctionSurface_SetAdjoinAlpha(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetAdjoinAlpha, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceAdjoin(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceAdjoin, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceSector, pCog);
}

void J3DAPI sithCogFunctionSurface_GetNumSurfaceVertices(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetNumSurfaceVertices, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceVertexPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceVertexPos, pCog);
}

void J3DAPI sithCogFunctionSurface_SetHorizonSkyOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetHorizonSkyOffset, pCog);
}

void J3DAPI sithCogFunctionSurface_GetHorizonSkyOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetHorizonSkyOffset, pCog);
}

void J3DAPI sithCogFunctionSurface_SetCeilingSkyOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetCeilingSkyOffset, pCog);
}

void J3DAPI sithCogFunctionSurface_GetCeilingSkyOffset(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetCeilingSkyOffset, pCog);
}

void J3DAPI sithCogFunctionSurface_SlideHorizonSky(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SlideHorizonSky, pCog);
}

void J3DAPI sithCogFunctionSurface_SlideCeilingSky(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SlideCeilingSky, pCog);
}

void J3DAPI sithCogFunctionSurface_SurfaceLightAnim(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SurfaceLightAnim, pCog);
}

void J3DAPI sithCogFunctionSurface_SlideWall(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SlideWall, pCog);
}

void J3DAPI sithCogFunctionSurface_GetWallCel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetWallCel, pCog);
}

void J3DAPI sithCogFunctionSurface_SetWallCel(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetWallCel, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceMaterial(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceMaterial, pCog);
}

void J3DAPI sithCogFunctionSurface_SetSurfaceMaterial(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetSurfaceMaterial, pCog);
}

void J3DAPI sithCogFunctionSurface_SetSurfaceFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetSurfaceFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_ClearSurfaceFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_ClearSurfaceFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_SetAdjoinFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetAdjoinFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_ClearAdjoinFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_ClearAdjoinFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_GetAdjoinFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetAdjoinFlags, pCog);
}

void J3DAPI sithCogFunctionSurface_SetFaceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetFaceType, pCog);
}

void J3DAPI sithCogFunctionSurface_ClearFaceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_ClearFaceType, pCog);
}

void J3DAPI sithCogFunctionSurface_GetFaceType(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetFaceType, pCog);
}

void J3DAPI sithCogFunctionSurface_SetFaceGeoMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetFaceGeoMode, pCog);
}

void J3DAPI sithCogFunctionSurface_GetFaceGeoMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetFaceGeoMode, pCog);
}

void J3DAPI sithCogFunctionSurface_SetFaceLightMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetFaceLightMode, pCog);
}

void J3DAPI sithCogFunctionSurface_GetFaceLightMode(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetFaceLightMode, pCog);
}

void J3DAPI sithCogFunctionSurface_SetSurfaceLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SetSurfaceLight, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceLight, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceCenter(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceCenter, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceCount, pCog);
}

void J3DAPI sithCogFunctionSurface_GetSurfaceNormal(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_GetSurfaceNormal, pCog);
}

void J3DAPI sithCogFunctionSurface_SyncSurface(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSurface_SyncSurface, pCog);
}
