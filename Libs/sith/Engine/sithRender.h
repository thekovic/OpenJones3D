#ifndef SITH_SITHRENDER_H
#define SITH_SITHRENDER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithRender_g_numDrawnThings J3D_DECL_FAR_VAR(sithRender_g_numDrawnThings, int)
// extern int sithRender_g_numDrawnThings;

#define sithRender_g_numArchPolys J3D_DECL_FAR_VAR(sithRender_g_numArchPolys, int)
// extern int sithRender_g_numArchPolys;

#define sithRender_g_numAlphaArchPolys J3D_DECL_FAR_VAR(sithRender_g_numAlphaArchPolys, int)
// extern int sithRender_g_numAlphaArchPolys;

#define sithRender_g_numThingPolys J3D_DECL_FAR_VAR(sithRender_g_numThingPolys, int)
// extern int sithRender_g_numThingPolys;

#define sithRender_g_numAlphaThingPoly J3D_DECL_FAR_VAR(sithRender_g_numAlphaThingPoly, int)
// extern int sithRender_g_numAlphaThingPoly;

#define sithRender_g_numVisibleAdjoins J3D_DECL_FAR_VAR(sithRender_g_numVisibleAdjoins, int)
// extern int sithRender_g_numVisibleAdjoins;

#define sithRender_g_lightMode J3D_DECL_FAR_VAR(sithRender_g_lightMode, rdLightMode)
// extern rdLightMode sithRender_g_lightMode;

#define sithRender_g_numVisibleSectors J3D_DECL_FAR_VAR(sithRender_g_numVisibleSectors, int)
// extern int sithRender_g_numVisibleSectors;

int sithRender_Startup(void);
int J3DAPI sithRender_Open();
void J3DAPI sithRender_Close();
void sithRender_Shutdown(void);
void J3DAPI sithRender_SetRenderFlags(int flags);
int J3DAPI sithRender_GetRenderFlags();
void J3DAPI sithRender_SetLightingMode(rdLightMode mode);
void sithRender_Draw(void);
void J3DAPI sithRender_BuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pFrustrum);
void J3DAPI sithRender_BuildVisibleSurface(SithSurface* pSurface);
void J3DAPI sithRender_BuildClipFrustrum(rdClipFrustum* pFrustrum, int numVertices, float orthLeft, float orthTop, float orthRight, float orthBottom);
void J3DAPI sithRender_PVSBuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pClipFrustum);
void J3DAPI sithRender_PVSBuildVisibleSector(SithSector* pSector);
void J3DAPI sithRender_BuildVisibleSector(SithSector* pSector, const rdClipFrustum* pFrustrum);
void J3DAPI sithRender_RenderSectors();
void sithRender_BuildVisibleSectorsThingList(void);
void J3DAPI sithRender_BuildSectorThingList(SithSector* pSector, float a2, float distance);
void sithRender_BuildDynamicLights(void);
void sithRender_RenderThings(void);
int J3DAPI sithRender_RenderThing(SithThing* pThing);
void sithRender_RenderAlphaAdjoins(void);
int sithRender_MakeScreenShot(void);
int J3DAPI sithRenderSky_Open(float horizonDistance, float ceilingSkyHeight);
void sithRenderSky_Update(void);
// Function transforms horizon sky surface vertices to NDC screen space
// 
// aVerts should be transformed to clip space.
void J3DAPI sithRenderSky_HorizonFaceToPlane(rdCacheProcEntry* pPoly, const rdFace* pFace, rdVector3* aVerts, int numVerts);
// Function transforms ceiling sky vertices to NDC screen space
// 
// aVerts here should be transformed to camera space.
// 
// aTransformedVerts should be projected to clip space. (amera->pfProject)
void J3DAPI sithRenderSky_CeilingFaceToPlane(rdCacheProcEntry* pPoly, const rdFace* pFace, const rdVector3* aVerts, const rdVector3* aTransformedVerts, unsigned int numVerts);

// Helper hooking functions
void sithRender_InstallHooks(void);
void sithRender_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHRENDER_H
