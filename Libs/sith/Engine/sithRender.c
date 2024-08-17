#include "sithRender.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithRender_bPVSClipEnabled J3D_DECL_FAR_VAR(sithRender_bPVSClipEnabled, int)
#define sithRenderSky_ceilingSkyNormal J3D_DECL_FAR_VAR(sithRenderSky_ceilingSkyNormal, rdVector3)
#define sithRender_aVisibleSectors J3D_DECL_FAR_ARRAYVAR(sithRender_aVisibleSectors, SithSector*(*)[128])
#define sithRender_aClipVertices J3D_DECL_FAR_ARRAYVAR(sithRender_aClipVertices, rdVector3(*)[80])
#define sithRender_dword_564D90 J3D_DECL_FAR_VAR(sithRender_dword_564D90, int)
#define sithRender_aFaceVerts J3D_DECL_FAR_VAR(sithRender_aFaceVerts, rdPrimit3)
#define sithRender_aVisibleAdjoins J3D_DECL_FAR_ARRAYVAR(sithRender_aVisibleAdjoins, SithSurfaceAdjoin*(*)[128])
#define sithRender_dword_564FBC J3D_DECL_FAR_VAR(sithRender_dword_564FBC, int)
#define sithRender_renderflags J3D_DECL_FAR_VAR(sithRender_renderflags, int)
#define sithRender_numSectorPointLights J3D_DECL_FAR_VAR(sithRender_numSectorPointLights, int)
#define sithRender_numSpritesToDraw J3D_DECL_FAR_VAR(sithRender_numSpritesToDraw, int)
#define sithRender_numAlphaAdjoins J3D_DECL_FAR_VAR(sithRender_numAlphaAdjoins, int)
#define sithRender_aTransformedClipVertices J3D_DECL_FAR_ARRAYVAR(sithRender_aTransformedClipVertices, rdVector3(*)[80])
#define sithRender_numThingSectors J3D_DECL_FAR_VAR(sithRender_numThingSectors, int)
#define sithRender_aView J3D_DECL_FAR_VAR(sithRender_aView, rdPrimit3)
#define sithRender_aSectorPointLights J3D_DECL_FAR_ARRAYVAR(sithRender_aSectorPointLights, rdLight(*)[64])
#define sithRender_aThingLights J3D_DECL_FAR_ARRAYVAR(sithRender_aThingLights, rdLight(*)[64])
#define sithRender_aThingSectors J3D_DECL_FAR_ARRAYVAR(sithRender_aThingSectors, SithSector*(*)[256])
#define sithRender_numSecorFrustrums J3D_DECL_FAR_VAR(sithRender_numSecorFrustrums, int)
#define sithRender_aSectorFrustrums J3D_DECL_FAR_ARRAYVAR(sithRender_aSectorFrustrums, rdClipFrustum(*)[128])
#define sithRender_curSectorIdx J3D_DECL_FAR_VAR(sithRender_curSectorIdx, int)
#define sithRender_aAlphaAdjoins J3D_DECL_FAR_ARRAYVAR(sithRender_aAlphaAdjoins, SithSurface*(*)[64])
#define sithRender_aSurfaceTransformedVertices J3D_DECL_FAR_ARRAYVAR(sithRender_aSurfaceTransformedVertices, rdVector3(*)[80])
#define sithRender_numThingLights J3D_DECL_FAR_VAR(sithRender_numThingLights, int)
#define sithRender_numRenderedSectors J3D_DECL_FAR_VAR(sithRender_numRenderedSectors, int)
#define sithRender_numVisibleThingSectors J3D_DECL_FAR_VAR(sithRender_numVisibleThingSectors, int)
#define sithRender_bResetCameraAspect J3D_DECL_FAR_VAR(sithRender_bResetCameraAspect, int)
#define sithRender_pfUnknownFunc J3D_DECL_FAR_VAR(sithRender_pfUnknownFunc, SithRenderUnknownFunc)
#define sithRender_aAdjoinTable J3D_DECL_FAR_VAR(sithRender_aAdjoinTable, uint8_t*)
#define sithRenderSky_lookYaw J3D_DECL_FAR_VAR(sithRenderSky_lookYaw, float)
#define sithRenderSky_horizonPixelsPerRev J3D_DECL_FAR_VAR(sithRenderSky_horizonPixelsPerRev, float)
#define sithRenderSky_horizonScale J3D_DECL_FAR_VAR(sithRenderSky_horizonScale, float)
#define sithRenderSky_lookPitch J3D_DECL_FAR_VAR(sithRenderSky_lookPitch, float)
#define sithRenderSky_lookRollCos J3D_DECL_FAR_VAR(sithRenderSky_lookRollCos, float)
#define sithRenderSky_ceilingSkyMaxZ J3D_DECL_FAR_VAR(sithRenderSky_ceilingSkyMaxZ, rdVector3)
#define sithRenderSky_ceilingSkyHeight J3D_DECL_FAR_VAR(sithRenderSky_ceilingSkyHeight, float)
#define sithRenderSky_ceilingSkyMinZ J3D_DECL_FAR_VAR(sithRenderSky_ceilingSkyMinZ, rdVector3)
#define sithRenderSky_horizonSkyDistance J3D_DECL_FAR_VAR(sithRenderSky_horizonSkyDistance, float)
#define sithRenderSky_lookRollSin J3D_DECL_FAR_VAR(sithRenderSky_lookRollSin, float)

void sithRender_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithRender_Startup);
    // J3D_HOOKFUNC(sithRender_Open);
    // J3D_HOOKFUNC(sithRender_Close);
    // J3D_HOOKFUNC(sithRender_Shutdown);
    // J3D_HOOKFUNC(sithRender_SetRenderFlags);
    // J3D_HOOKFUNC(sithRender_GetRenderFlags);
    // J3D_HOOKFUNC(sithRender_SetLightingMode);
    // J3D_HOOKFUNC(sithRender_Draw);
    // J3D_HOOKFUNC(sithRender_BuildVisibleSectorList);
    // J3D_HOOKFUNC(sithRender_BuildVisibleSurface);
    // J3D_HOOKFUNC(sithRender_BuildClipFrustrum);
    // J3D_HOOKFUNC(sithRender_PVSBuildVisibleSectorList);
    // J3D_HOOKFUNC(sithRender_PVSBuildVisibleSector);
    // J3D_HOOKFUNC(sithRender_BuildVisibleSector);
    // J3D_HOOKFUNC(sithRender_RenderSectors);
    // J3D_HOOKFUNC(sithRender_BuildVisibleSectorsThingList);
    // J3D_HOOKFUNC(sithRender_BuildSectorThingList);
    // J3D_HOOKFUNC(sithRender_BuildDynamicLights);
    // J3D_HOOKFUNC(sithRender_RenderThings);
    // J3D_HOOKFUNC(sithRender_RenderThing);
    // J3D_HOOKFUNC(sithRender_RenderAlphaAdjoins);
    // J3D_HOOKFUNC(sithRender_MakeScreenShot);
    // J3D_HOOKFUNC(sithRenderSky_Open);
    // J3D_HOOKFUNC(sithRenderSky_Update);
    // J3D_HOOKFUNC(sithRenderSky_HorizonFaceToPlane);
    // J3D_HOOKFUNC(sithRenderSky_CeilingFaceToPlane);
}

void sithRender_ResetGlobals(void)
{
    int sithRender_bPVSClipEnabled_tmp = 1;
    memcpy(&sithRender_bPVSClipEnabled, &sithRender_bPVSClipEnabled_tmp, sizeof(sithRender_bPVSClipEnabled));
    
    rdVector3 sithRenderSky_ceilingSkyNormal_tmp = { { 0.0f }, { 0.0f }, { -1.0f } };
    memcpy(&sithRenderSky_ceilingSkyNormal, &sithRenderSky_ceilingSkyNormal_tmp, sizeof(sithRenderSky_ceilingSkyNormal));
    
    memset(&sithRender_aVisibleSectors, 0, sizeof(sithRender_aVisibleSectors));
    memset(&sithRender_aClipVertices, 0, sizeof(sithRender_aClipVertices));
    memset(&sithRender_dword_564D90, 0, sizeof(sithRender_dword_564D90));
    memset(&sithRender_aFaceVerts, 0, sizeof(sithRender_aFaceVerts));
    memset(&sithRender_aVisibleAdjoins, 0, sizeof(sithRender_aVisibleAdjoins));
    memset(&sithRender_dword_564FBC, 0, sizeof(sithRender_dword_564FBC));
    memset(&sithRender_renderflags, 0, sizeof(sithRender_renderflags));
    memset(&sithRender_numSectorPointLights, 0, sizeof(sithRender_numSectorPointLights));
    memset(&sithRender_numSpritesToDraw, 0, sizeof(sithRender_numSpritesToDraw));
    memset(&sithRender_numAlphaAdjoins, 0, sizeof(sithRender_numAlphaAdjoins));
    memset(&sithRender_aTransformedClipVertices, 0, sizeof(sithRender_aTransformedClipVertices));
    memset(&sithRender_numThingSectors, 0, sizeof(sithRender_numThingSectors));
    memset(&sithRender_aView, 0, sizeof(sithRender_aView));
    memset(&sithRender_aSectorPointLights, 0, sizeof(sithRender_aSectorPointLights));
    memset(&sithRender_aThingLights, 0, sizeof(sithRender_aThingLights));
    memset(&sithRender_aThingSectors, 0, sizeof(sithRender_aThingSectors));
    memset(&sithRender_numSecorFrustrums, 0, sizeof(sithRender_numSecorFrustrums));
    memset(&sithRender_aSectorFrustrums, 0, sizeof(sithRender_aSectorFrustrums));
    memset(&sithRender_curSectorIdx, 0, sizeof(sithRender_curSectorIdx));
    memset(&sithRender_aAlphaAdjoins, 0, sizeof(sithRender_aAlphaAdjoins));
    memset(&sithRender_aSurfaceTransformedVertices, 0, sizeof(sithRender_aSurfaceTransformedVertices));
    memset(&sithRender_numThingLights, 0, sizeof(sithRender_numThingLights));
    memset(&sithRender_numRenderedSectors, 0, sizeof(sithRender_numRenderedSectors));
    memset(&sithRender_g_numDrawnThings, 0, sizeof(sithRender_g_numDrawnThings));
    memset(&sithRender_g_numArchPolys, 0, sizeof(sithRender_g_numArchPolys));
    memset(&sithRender_g_numAlphaArchPolys, 0, sizeof(sithRender_g_numAlphaArchPolys));
    memset(&sithRender_g_numThingPolys, 0, sizeof(sithRender_g_numThingPolys));
    memset(&sithRender_g_numAlphaThingPoly, 0, sizeof(sithRender_g_numAlphaThingPoly));
    memset(&sithRender_g_numVisibleAdjoins, 0, sizeof(sithRender_g_numVisibleAdjoins));
    memset(&sithRender_numVisibleThingSectors, 0, sizeof(sithRender_numVisibleThingSectors));
    memset(&sithRender_bResetCameraAspect, 0, sizeof(sithRender_bResetCameraAspect));
    memset(&sithRender_pfUnknownFunc, 0, sizeof(sithRender_pfUnknownFunc));
    memset(&sithRender_aAdjoinTable, 0, sizeof(sithRender_aAdjoinTable));
    memset(&sithRenderSky_lookYaw, 0, sizeof(sithRenderSky_lookYaw));
    memset(&sithRenderSky_horizonPixelsPerRev, 0, sizeof(sithRenderSky_horizonPixelsPerRev));
    memset(&sithRenderSky_horizonScale, 0, sizeof(sithRenderSky_horizonScale));
    memset(&sithRenderSky_lookPitch, 0, sizeof(sithRenderSky_lookPitch));
    memset(&sithRenderSky_lookRollCos, 0, sizeof(sithRenderSky_lookRollCos));
    memset(&sithRenderSky_ceilingSkyMaxZ, 0, sizeof(sithRenderSky_ceilingSkyMaxZ));
    memset(&sithRenderSky_ceilingSkyHeight, 0, sizeof(sithRenderSky_ceilingSkyHeight));
    memset(&sithRenderSky_ceilingSkyMinZ, 0, sizeof(sithRenderSky_ceilingSkyMinZ));
    memset(&sithRenderSky_horizonSkyDistance, 0, sizeof(sithRenderSky_horizonSkyDistance));
    memset(&sithRenderSky_lookRollSin, 0, sizeof(sithRenderSky_lookRollSin));
    memset(&sithRender_g_lightMode, 0, sizeof(sithRender_g_lightMode));
    memset(&sithRender_g_numVisibleSectors, 0, sizeof(sithRender_g_numVisibleSectors));
}

int sithRender_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithRender_Startup);
}

int J3DAPI sithRender_Open()
{
    return J3D_TRAMPOLINE_CALL(sithRender_Open);
}

void J3DAPI sithRender_Close()
{
    J3D_TRAMPOLINE_CALL(sithRender_Close);
}

void sithRender_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_Shutdown);
}

void J3DAPI sithRender_SetRenderFlags(int flags)
{
    J3D_TRAMPOLINE_CALL(sithRender_SetRenderFlags, flags);
}

int J3DAPI sithRender_GetRenderFlags()
{
    return J3D_TRAMPOLINE_CALL(sithRender_GetRenderFlags);
}

void J3DAPI sithRender_SetLightingMode(rdLightMode mode)
{
    J3D_TRAMPOLINE_CALL(sithRender_SetLightingMode, mode);
}

void sithRender_Draw(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_Draw);
}

void J3DAPI sithRender_BuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pFrustrum)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildVisibleSectorList, pSector, pFrustrum);
}

void J3DAPI sithRender_BuildVisibleSurface(SithSurface* pSurface)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildVisibleSurface, pSurface);
}

void J3DAPI sithRender_BuildClipFrustrum(rdClipFrustum* pFrustrum, int numVertices, float orthLeft, float orthTop, float orthRight, float orthBottom)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildClipFrustrum, pFrustrum, numVertices, orthLeft, orthTop, orthRight, orthBottom);
}

void J3DAPI sithRender_PVSBuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pClipFrustum)
{
    J3D_TRAMPOLINE_CALL(sithRender_PVSBuildVisibleSectorList, pSector, pClipFrustum);
}

void J3DAPI sithRender_PVSBuildVisibleSector(SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithRender_PVSBuildVisibleSector, pSector);
}

void J3DAPI sithRender_BuildVisibleSector(SithSector* pSector, const rdClipFrustum* pFrustrum)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildVisibleSector, pSector, pFrustrum);
}

void J3DAPI sithRender_RenderSectors()
{
    J3D_TRAMPOLINE_CALL(sithRender_RenderSectors);
}

void sithRender_BuildVisibleSectorsThingList(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildVisibleSectorsThingList);
}

void J3DAPI sithRender_BuildSectorThingList(SithSector* pSector, float a2, float distance)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildSectorThingList, pSector, a2, distance);
}

void sithRender_BuildDynamicLights(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_BuildDynamicLights);
}

void sithRender_RenderThings(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_RenderThings);
}

int J3DAPI sithRender_RenderThing(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithRender_RenderThing, pThing);
}

void sithRender_RenderAlphaAdjoins(void)
{
    J3D_TRAMPOLINE_CALL(sithRender_RenderAlphaAdjoins);
}

int sithRender_MakeScreenShot(void)
{
    return J3D_TRAMPOLINE_CALL(sithRender_MakeScreenShot);
}

int J3DAPI sithRenderSky_Open(float horizonDistance, float ceilingSkyHeight)
{
    return J3D_TRAMPOLINE_CALL(sithRenderSky_Open, horizonDistance, ceilingSkyHeight);
}

void sithRenderSky_Update(void)
{
    J3D_TRAMPOLINE_CALL(sithRenderSky_Update);
}

// Function transforms horizon sky surface vertices to NDC screen space
// 
// aVerts should be transformed to clip space.
void J3DAPI sithRenderSky_HorizonFaceToPlane(rdCacheProcEntry* pPoly, const rdFace* pFace, rdVector3* aVerts, int numVerts)
{
    J3D_TRAMPOLINE_CALL(sithRenderSky_HorizonFaceToPlane, pPoly, pFace, aVerts, numVerts);
}

// Function transforms ceiling sky vertices to NDC screen space
// 
// aVerts here should be transformed to camera space.
// 
// aTransformedVerts should be projected to clip space. (amera->pfProject)
void J3DAPI sithRenderSky_CeilingFaceToPlane(rdCacheProcEntry* pPoly, const rdFace* pFace, const rdVector3* aVerts, const rdVector3* aTransformedVerts, unsigned int numVerts)
{
    J3D_TRAMPOLINE_CALL(sithRenderSky_CeilingFaceToPlane, pPoly, pFace, aVerts, aTransformedVerts, numVerts);
}
