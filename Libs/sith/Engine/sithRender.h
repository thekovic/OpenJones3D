#ifndef SITH_SITHRENDER_H
#define SITH_SITHRENDER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START
#define SITHRENDER_MAX_VISIBLE_SECTORS     4096 // Altered: Was 128
#define SITHRENDER_MAX_SECTORS_WITH_THINGS SITHRENDER_MAX_VISIBLE_SECTORS * 2 // Altered: Was 256


#define SITHRENDER_MAXTHINGCOLLECTDISTANCE_DEFAULT J3D_QOL_VALUE(16.0f, 8.0f)  // Max distance from each visible sector to collect things to be rendered. Altered: Changed to 16 (160m) form 8 (80m)
#define SITHRENDER_MAXLIGHTCOLLECTDISTANCE_DEFAULT J3D_QOL_VALUE(50.0f, 8.0f)  // Max distance from each visible sector to collect emitting lights. 
                                                                               // This is new configurable variable. Originally, light collecting distance was limited to things collecting distance (8.0f) and 
                                                                               // max number of collected things - SITHRENDER_MAX_SECTORS_WITH_THINGS
                                                                               // The new default distance - 500m was determined based on the light flickering issue in Babylon level (court yard)


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
void sithRender_Shutdown(void);

int sithRender_Open(void);
void sithRender_Close(void);

void J3DAPI sithRender_SetRenderFlags(int flags);
int sithRender_GetRenderFlags(void);

void J3DAPI sithRender_SetLightingMode(rdLightMode mode);
rdLightMode sithRender_GetLightingMode(void); // Added

float sithRender_GetMaxThingCollectDistance(void); // New
void J3DAPI sithRender_SetMaxThingCollectDistance(float distance); // New

float sithRender_GetMaxLightCollectDistance(void); // New
void J3DAPI sithRender_SetMaxLightCollectDistance(float distance); // New

//!< Renders sithWorld_g_pCurrentWorld from position of sithCamera_g_pCurCamera
void sithRender_RenderScene(void); // Added from debug

void sithRender_TogglePVS(void); // Added from debug

int sithRender_MakeScreenShot(void);

// Helper hooking functions
void sithRender_InstallHooks(void);
void sithRender_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHRENDER_H
