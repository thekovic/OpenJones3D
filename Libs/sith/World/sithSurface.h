#ifndef SITH_SITHSURFACE_H
#define SITH_SITHSURFACE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

char J3DAPI sithSurface_HideSectorAdjoin(SithSurfaceAdjoin* pAdjoin);
char J3DAPI sithSurface_ShowSectorAdjoin(SithSurfaceAdjoin* pAdjoin);
int J3DAPI sithSurface_AllocWorldSurfaces(SithWorld* pWorld, int numSurfaces);
void J3DAPI sithSurface_FreeWorldSurfaces(SithWorld* pWorld);
int J3DAPI sithSurface_CNDWriteAdjoinSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_CNDReadAdjoinSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_AllocWorldAdjoins(SithWorld* pWorld, int numAdjoins);
int J3DAPI sithSurface_CNDWriteSurfaceSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSurface_CNDReadSurfaceSection(tFileHandle fh, SithWorld* pWorld);
signed int J3DAPI sithSurface_NDYReadSurfaceList(SithWorld* pWorld);
int J3DAPI sithSurface_ValidateSurfacePointer(const SithSurface* pSurf);
int J3DAPI sithSurface_ValidateWorldSurfaces(const SithWorld* pWorld);
void J3DAPI sithSurface_HandleThingImpact(SithSurface* pSurf, SithThing* pThing, float damage, int damageType);
void J3DAPI sithSurface_PlaySurfaceHitSound(const SithSurface* pSurf, SithThing* pThing, int damageType);
int J3DAPI sithSurface_GetCenterPoint(const SithSurface* pSurface, rdVector3* centerpoint);
int J3DAPI sithSurface_SyncSurface(SithSurface* pSurface);
void J3DAPI sithSurface_SyncSurfaces();
SithSurface* J3DAPI sithSurface_GetSurfaceEx(const SithWorld* pWorld, int surfIdx);
int J3DAPI sithSurface_GetSurfaceIndex(const SithSurface* pSurf);
int J3DAPI sithSurface_GetSurfaceIndexEx(const SithWorld* pWorld, const SithSurface* pSurface);

// Helper hooking functions
void sithSurface_InstallHooks(void);
void sithSurface_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSURFACE_H
