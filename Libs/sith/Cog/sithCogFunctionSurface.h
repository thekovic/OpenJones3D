#ifndef SITH_SITHCOGFUNCTIONSURFACE_H
#define SITH_SITHCOGFUNCTIONSURFACE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithCogFunctionSurface_RegisterFunctions(SithCogSymbolTable* pTbl);
void J3DAPI sithCogFunctionSurface_GetAdjoinAlpha(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetAdjoinAlpha(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceAdjoin(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceSector(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetNumSurfaceVertices(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceVertexPos(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetHorizonSkyOffset(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetHorizonSkyOffset(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetCeilingSkyOffset(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetCeilingSkyOffset(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SlideHorizonSky(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SlideCeilingSky(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SurfaceLightAnim(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SlideWall(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetWallCel(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetWallCel(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceMaterial(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetSurfaceMaterial(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetSurfaceFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_ClearSurfaceFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetAdjoinFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_ClearAdjoinFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetAdjoinFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetFaceType(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_ClearFaceType(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetFaceType(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetFaceGeoMode(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetFaceGeoMode(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetFaceLightMode(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetFaceLightMode(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SetSurfaceLight(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceLight(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceCenter(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceCount(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_GetSurfaceNormal(SithCog* pCog);
void J3DAPI sithCogFunctionSurface_SyncSurface(SithCog* pCog);

// Helper hooking functions
void sithCogFunctionSurface_InstallHooks(void);
void sithCogFunctionSurface_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTIONSURFACE_H
