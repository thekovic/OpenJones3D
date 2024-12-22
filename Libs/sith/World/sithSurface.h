#ifndef SITH_SITHSURFACE_H
#define SITH_SITHSURFACE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithSurface_HideSectorAdjoin(SithSurfaceAdjoin* pAdjoin);
void J3DAPI sithSurface_ShowSectorAdjoin(SithSurfaceAdjoin* pAdjoin);

int J3DAPI sithSurface_AllocWorldSurfaces(SithWorld* pWorld, size_t numSurfaces);
void J3DAPI sithSurface_FreeWorldSurfaces(SithWorld* pWorld);

int J3DAPI sithSurface_AllocWorldAdjoins(SithWorld* pWorld, size_t numAdjoins);

int J3DAPI sithSurface_WriteAdjoinsBinary(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_LoadAdjoinsBinary(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_WriteAdjoinsText(const SithWorld* pWorld); // Added

int J3DAPI sithSurface_WriteSurfacesBinary(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_LoadSurfacesBinary(tFileHandle fh, SithWorld* pWorld);

int J3DAPI sithSurface_WriteSurfacesText(const SithWorld* pWorld); // Added
int J3DAPI sithSurface_LoadSurfacesText(SithWorld* pWorld);

int J3DAPI sithSurface_ValidateSurfacePointer(const SithSurface* pSurf);
int J3DAPI sithSurface_ValidateWorldSurfaces(const SithWorld* pWorld);
int J3DAPI sithSurface_GetCenterPoint(const SithSurface* pSurface, rdVector3* centerpoint);

void J3DAPI sithSurface_HandleThingImpact(SithSurface* pSurf, SithThing* pThing, float damage, int damageType);
void J3DAPI sithSurface_PlaySurfaceHitSound(const SithSurface* pSurf, SithThing* pThing, int damageType);

void J3DAPI sithSurface_SyncSurface(SithSurface* pSurface);
void sithSurface_SyncSurfaces(void);

SithSurface* J3DAPI sithSurface_GetSurfaceEx(const SithWorld* pWorld, int surfIdx);
int J3DAPI sithSurface_GetSurfaceIndex(const SithSurface* pSurf);
int J3DAPI sithSurface_GetSurfaceIndexEx(const SithWorld* pWorld, const SithSurface* pSurface);

// Helper hooking functions
void sithSurface_InstallHooks(void);
void sithSurface_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSURFACE_H
