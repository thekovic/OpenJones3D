#include "sithSurface.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithSurface_apUnsyncedSurfaces J3D_DECL_FAR_ARRAYVAR(sithSurface_apUnsyncedSurfaces, SithSurface*(*)[32])
#define sithSurface_numUnsyncedSurfaces J3D_DECL_FAR_VAR(sithSurface_numUnsyncedSurfaces, int)

void sithSurface_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSurface_HideSectorAdjoin);
    // J3D_HOOKFUNC(sithSurface_ShowSectorAdjoin);
    // J3D_HOOKFUNC(sithSurface_AllocWorldSurfaces);
    // J3D_HOOKFUNC(sithSurface_FreeWorldSurfaces);
    // J3D_HOOKFUNC(sithSurface_CNDWriteAdjoinSection);
    // J3D_HOOKFUNC(sithSurface_CNDReadAdjoinSection);
    // J3D_HOOKFUNC(sithSurface_AllocWorldAdjoins);
    // J3D_HOOKFUNC(sithSurface_CNDWriteSurfaceSection);
    // J3D_HOOKFUNC(sithSurface_CNDReadSurfaceSection);
    // J3D_HOOKFUNC(sithSurface_NDYReadSurfaceList);
    // J3D_HOOKFUNC(sithSurface_ValidateSurfacePointer);
    // J3D_HOOKFUNC(sithSurface_ValidateWorldSurfaces);
    // J3D_HOOKFUNC(sithSurface_HandleThingImpact);
    // J3D_HOOKFUNC(sithSurface_PlaySurfaceHitSound);
    // J3D_HOOKFUNC(sithSurface_GetCenterPoint);
    // J3D_HOOKFUNC(sithSurface_SyncSurface);
    // J3D_HOOKFUNC(sithSurface_SyncSurfaces);
    // J3D_HOOKFUNC(sithSurface_GetSurfaceEx);
    // J3D_HOOKFUNC(sithSurface_GetSurfaceIndex);
    // J3D_HOOKFUNC(sithSurface_GetSurfaceIndexEx);
}

void sithSurface_ResetGlobals(void)
{
    memset(&sithSurface_apUnsyncedSurfaces, 0, sizeof(sithSurface_apUnsyncedSurfaces));
    memset(&sithSurface_numUnsyncedSurfaces, 0, sizeof(sithSurface_numUnsyncedSurfaces));
}

char J3DAPI sithSurface_HideSectorAdjoin(SithSurfaceAdjoin* pAdjoin)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_HideSectorAdjoin, pAdjoin);
}

char J3DAPI sithSurface_ShowSectorAdjoin(SithSurfaceAdjoin* pAdjoin)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_ShowSectorAdjoin, pAdjoin);
}

int J3DAPI sithSurface_AllocWorldSurfaces(SithWorld* pWorld, int numSurfaces)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_AllocWorldSurfaces, pWorld, numSurfaces);
}

void J3DAPI sithSurface_FreeWorldSurfaces(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSurface_FreeWorldSurfaces, pWorld);
}

int J3DAPI sithSurface_CNDWriteAdjoinSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_CNDWriteAdjoinSection, fh, pWorld);
}

int J3DAPI sithSurface_CNDReadAdjoinSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_CNDReadAdjoinSection, fh, pWorld);
}

int J3DAPI sithSurface_AllocWorldAdjoins(SithWorld* pWorld, int numAdjoins)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_AllocWorldAdjoins, pWorld, numAdjoins);
}

int J3DAPI sithSurface_CNDWriteSurfaceSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_CNDWriteSurfaceSection, fh, pWorld);
}

int J3DAPI sithSurface_CNDReadSurfaceSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_CNDReadSurfaceSection, fh, pWorld);
}

signed int J3DAPI sithSurface_NDYReadSurfaceList(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_NDYReadSurfaceList, pWorld);
}

int J3DAPI sithSurface_ValidateSurfacePointer(const SithSurface* pSurf)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_ValidateSurfacePointer, pSurf);
}

int J3DAPI sithSurface_ValidateWorldSurfaces(const SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_ValidateWorldSurfaces, pWorld);
}

void J3DAPI sithSurface_HandleThingImpact(SithSurface* pSurf, SithThing* pThing, float damage, int damageType)
{
    J3D_TRAMPOLINE_CALL(sithSurface_HandleThingImpact, pSurf, pThing, damage, damageType);
}

void J3DAPI sithSurface_PlaySurfaceHitSound(const SithSurface* pSurf, SithThing* pThing, int damageType)
{
    J3D_TRAMPOLINE_CALL(sithSurface_PlaySurfaceHitSound, pSurf, pThing, damageType);
}

int J3DAPI sithSurface_GetCenterPoint(const SithSurface* pSurface, rdVector3* centerpoint)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_GetCenterPoint, pSurface, centerpoint);
}

int J3DAPI sithSurface_SyncSurface(SithSurface* pSurface)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_SyncSurface, pSurface);
}

void J3DAPI sithSurface_SyncSurfaces()
{
    J3D_TRAMPOLINE_CALL(sithSurface_SyncSurfaces);
}

SithSurface* J3DAPI sithSurface_GetSurfaceEx(const SithWorld* pWorld, int surfIdx)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_GetSurfaceEx, pWorld, surfIdx);
}

int J3DAPI sithSurface_GetSurfaceIndex(const SithSurface* pSurf)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_GetSurfaceIndex, pSurf);
}

int J3DAPI sithSurface_GetSurfaceIndexEx(const SithWorld* pWorld, const SithSurface* pSurface)
{
    return J3D_TRAMPOLINE_CALL(sithSurface_GetSurfaceIndexEx, pWorld, pSurface);
}
