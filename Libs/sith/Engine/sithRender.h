#ifndef SITH_SITHRENDER_H
#define SITH_SITHRENDER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START
#define SITHRENDER_MAX_VISIBLE_SECTORS     4096 // Changed: Was 128
#define SITHRENDER_MAX_SECTORS_WITH_THINGS SITHRENDER_MAX_VISIBLE_SECTORS * 2 // Changed: Was 256

#define sithRender_g_fogDensity J3D_DECL_FAR_VAR(sithRender_g_fogDensity, float)
// extern float sithRender_g_fogDensity ;

#define sithRender_g_numDrawnThings J3D_DECL_FAR_VAR(sithRender_g_numDrawnThings, size_t)
// extern int sithRender_g_numDrawnThings;

#define sithRender_g_numArchPolys J3D_DECL_FAR_VAR(sithRender_g_numArchPolys, size_t)
// extern int sithRender_g_numArchPolys;

#define sithRender_g_numAlphaArchPolys J3D_DECL_FAR_VAR(sithRender_g_numAlphaArchPolys, size_t)
// extern int sithRender_g_numAlphaArchPolys;

#define sithRender_g_numThingPolys J3D_DECL_FAR_VAR(sithRender_g_numThingPolys, size_t)
// extern int sithRender_g_numThingPolys;

#define sithRender_g_numAlphaThingPoly J3D_DECL_FAR_VAR(sithRender_g_numAlphaThingPoly, size_t)
// extern int sithRender_g_numAlphaThingPoly;

#define sithRender_g_numVisibleAdjoins J3D_DECL_FAR_VAR(sithRender_g_numVisibleAdjoins, size_t)
// extern int sithRender_g_numVisibleAdjoins;

#define sithRender_g_numVisibleSectors J3D_DECL_FAR_VAR(sithRender_g_numVisibleSectors, size_t)
// extern int sithRender_g_numVisibleSectors;

int sithRender_Startup(void);
int J3DAPI sithRender_Open();
void J3DAPI sithRender_Close();
void sithRender_Shutdown(void);
void J3DAPI sithRender_SetRenderFlags(int flags);
int J3DAPI sithRender_GetRenderFlags();
void J3DAPI sithRender_SetLightingMode(rdLightMode mode);

void sithRender_RenderScene(void); // Added
void sithRender_Draw(void);
void sithRender_TogglePVS(void);// Added

void J3DAPI sithRender_BuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pFrustrum);
void J3DAPI sithRender_BuildVisibleSurface(SithSurface* pSurface);
void J3DAPI sithRender_BuildClipFrustrum(rdClipFrustum* pFrustrum, size_t numVertices, float orthLeft, float orthTop, float orthRight, float orthBottom);
void J3DAPI sithRender_PVSBuildVisibleSectorList(SithSector* pSector, rdClipFrustum* pClipFrustum);
void J3DAPI sithRender_PVSBuildVisibleSector(SithSector* pSector);
void J3DAPI sithRender_BuildVisibleSector(SithSector* pSector, const rdClipFrustum* pFrustrum);
void J3DAPI sithRender_RenderSectors();
void sithRender_BuildVisibleSectorsThingList(void);
void J3DAPI sithRender_BuildSectorThingList(SithSector* pSector, float curDistance, float extraDistance);
void sithRender_BuildDynamicLights(void);
void sithRender_RenderThings(void);
int J3DAPI sithRender_RenderThing(SithThing* pThing);
void sithRender_RenderAlphaAdjoins(void);
int sithRender_MakeScreenShot(void);

// Helper hooking functions
void sithRender_InstallHooks(void);
void sithRender_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHRENDER_H
