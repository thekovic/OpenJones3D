#ifndef SITH_SITHOVERLAYMAP_H
#define SITH_SITHOVERLAYMAP_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithOverlayMap_ConsoleCallback(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithOverlayMap_Open(SithOverlayMapConfig* pConfig);
void sithOverlayMap_Close(void);
int sithOverlayMap_IsMapVisible(void);
int sithOverlayMap_ToggleMap(void);
void J3DAPI sithOverlayMap_ZoomIn();
void J3DAPI sithOverlayMap_ZoomOut();
void sithOverlayMap_Draw(void);
void J3DAPI sithOverlayMap_SetShowHints(int bShow);
void J3DAPI sithOverlayMap_EnableMapRotation(int bEnable);
int J3DAPI sithOverlayMap_GetMapRotation();
int sithOverlayMap_GetShowHints(void);
int sithOverlayMap_UpdateHints(void);
int J3DAPI sithOverlayMap_SetHintSolved(SithThing* pThing);
int J3DAPI sithOverlayMap_SetHintUnsolved(SithThing* pThing);
void J3DAPI sithOverlayMap_GetNumSeenHints(int* pOutNumSeenHints, int* pOutNumHints);
void J3DAPI sithOverlayMap_RenderSectors(SithSector* pSector);
int J3DAPI sithOverlayMap_RenderSector(SithSector* pSector);
void J3DAPI sithOverlayMap_DrawPlayer();
void J3DAPI sithOverlayMap_DrawMark(const SithThing* pMark, const rdMaterial* pIcon, const rdVector2* aVertices, int bZLevelColor, int bBlink);
int J3DAPI sithOverlayMap_CanRenderSurface(SithSurface* pSurface, int vertIdx, int nextVertIdx);

// Helper hooking functions
void sithOverlayMap_InstallHooks(void);
void sithOverlayMap_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHOVERLAYMAP_H
