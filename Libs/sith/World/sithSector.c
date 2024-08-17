#include "sithSector.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithSector_aModifiedSectors J3D_DECL_FAR_ARRAYVAR(sithSector_aModifiedSectors, SithSector*(*)[16])
#define sithSector_aSyncFlags J3D_DECL_FAR_ARRAYVAR(sithSector_aSyncFlags, int(*)[16])
#define sithSector_numModifiedSectors J3D_DECL_FAR_VAR(sithSector_numModifiedSectors, int)

void sithSector_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSector_NDYReadSectorSection);
    // J3D_HOOKFUNC(sithSector_CNDWriteSectorSection);
    // J3D_HOOKFUNC(sithSector_CNDReadSectorSection);
    // J3D_HOOKFUNC(sithSector_ValidateSectorPointer);
    // J3D_HOOKFUNC(sithSector_AllocWorldSectors);
    // J3D_HOOKFUNC(sithSector_ResetAllSectors);
    // J3D_HOOKFUNC(sithSector_FreeWorldSectors);
    // J3D_HOOKFUNC(sithSector_FindSectorAtPos);
    // J3D_HOOKFUNC(sithSector_HideSectorAdjoins);
    // J3D_HOOKFUNC(sithSector_ShowSectorAdjoins);
    // J3D_HOOKFUNC(sithSector_SetSectorFlags);
    // J3D_HOOKFUNC(sithSector_ClearSectorFlags);
    // J3D_HOOKFUNC(sithSector_GetSectorThingCount);
    // J3D_HOOKFUNC(sithSector_GetSectorPlayerCount);
    // J3D_HOOKFUNC(sithSector_SyncSector);
    // J3D_HOOKFUNC(sithSector_SyncSectors);
    // J3D_HOOKFUNC(sithSector_GetSectorEx);
    // J3D_HOOKFUNC(sithSector_GetSectorIndexEx);
    // J3D_HOOKFUNC(sithSector_GetSectorIndex);
}

void sithSector_ResetGlobals(void)
{
    memset(&sithSector_aModifiedSectors, 0, sizeof(sithSector_aModifiedSectors));
    memset(&sithSector_aSyncFlags, 0, sizeof(sithSector_aSyncFlags));
    memset(&sithSector_numModifiedSectors, 0, sizeof(sithSector_numModifiedSectors));
}

int J3DAPI sithSector_NDYReadSectorSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithSector_NDYReadSectorSection, pWorld, bSkip);
}

int J3DAPI sithSector_CNDWriteSectorSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSector_CNDWriteSectorSection, fh, pWorld);
}

int J3DAPI sithSector_CNDReadSectorSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSector_CNDReadSectorSection, fh, pWorld);
}

int J3DAPI sithSector_ValidateSectorPointer(const SithWorld* pWorld, const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithSector_ValidateSectorPointer, pWorld, pSector);
}

int J3DAPI sithSector_AllocWorldSectors(SithWorld* pWorld, int numSectors)
{
    return J3D_TRAMPOLINE_CALL(sithSector_AllocWorldSectors, pWorld, numSectors);
}

void J3DAPI sithSector_ResetAllSectors(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSector_ResetAllSectors, pWorld);
}

void J3DAPI sithSector_FreeWorldSectors(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSector_FreeWorldSectors, pWorld);
}

SithSector* J3DAPI sithSector_FindSectorAtPos(const SithWorld* pWorld, const rdVector3* pos)
{
    return J3D_TRAMPOLINE_CALL(sithSector_FindSectorAtPos, pWorld, pos);
}

void J3DAPI sithSector_HideSectorAdjoins(SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithSector_HideSectorAdjoins, pSector);
}

void J3DAPI sithSector_ShowSectorAdjoins(SithSector* pSector)
{
    J3D_TRAMPOLINE_CALL(sithSector_ShowSectorAdjoins, pSector);
}

void J3DAPI sithSector_SetSectorFlags(SithSector* pSector, SithSectorFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithSector_SetSectorFlags, pSector, flags);
}

void J3DAPI sithSector_ClearSectorFlags(SithSector* pSector, SithSectorFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithSector_ClearSectorFlags, pSector, flags);
}

int J3DAPI sithSector_GetSectorThingCount(const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithSector_GetSectorThingCount, pSector);
}

int J3DAPI sithSector_GetSectorPlayerCount(const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithSector_GetSectorPlayerCount, pSector);
}

unsigned int J3DAPI sithSector_SyncSector(SithSector* pSector, int flags)
{
    return J3D_TRAMPOLINE_CALL(sithSector_SyncSector, pSector, flags);
}

int J3DAPI sithSector_SyncSectors()
{
    return J3D_TRAMPOLINE_CALL(sithSector_SyncSectors);
}

SithSector* J3DAPI sithSector_GetSectorEx(const SithWorld* pWorld, int idx)
{
    return J3D_TRAMPOLINE_CALL(sithSector_GetSectorEx, pWorld, idx);
}

int J3DAPI sithSector_GetSectorIndexEx(const SithWorld* pWorld, const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithSector_GetSectorIndexEx, pWorld, pSector);
}

int J3DAPI sithSector_GetSectorIndex(const SithSector* pSector)
{
    return J3D_TRAMPOLINE_CALL(sithSector_GetSectorIndex, pSector);
}
