#ifndef SITH_SITHSECTOR_H
#define SITH_SITHSECTOR_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithSector_NDYReadSectorSection(SithWorld* pWorld, int bSkip);
int J3DAPI sithSector_CNDWriteSectorSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSector_CNDReadSectorSection(tFileHandle fh, SithWorld* pWorld);
int J3DAPI sithSector_ValidateSectorPointer(const SithWorld* pWorld, const SithSector* pSector);
int J3DAPI sithSector_AllocWorldSectors(SithWorld* pWorld, int numSectors);
void J3DAPI sithSector_ResetAllSectors(SithWorld* pWorld);
void J3DAPI sithSector_FreeWorldSectors(SithWorld* pWorld);
SithSector* J3DAPI sithSector_FindSectorAtPos(const SithWorld* pWorld, const rdVector3* pos);
void J3DAPI sithSector_HideSectorAdjoins(SithSector* pSector);
void J3DAPI sithSector_ShowSectorAdjoins(SithSector* pSector);
void J3DAPI sithSector_SetSectorFlags(SithSector* pSector, SithSectorFlag flags);
void J3DAPI sithSector_ClearSectorFlags(SithSector* pSector, SithSectorFlag flags);
int J3DAPI sithSector_GetSectorThingCount(const SithSector* pSector);
int J3DAPI sithSector_GetSectorPlayerCount(const SithSector* pSector);
unsigned int J3DAPI sithSector_SyncSector(SithSector* pSector, int flags);
int J3DAPI sithSector_SyncSectors();
SithSector* J3DAPI sithSector_GetSectorEx(const SithWorld* pWorld, int idx);
int J3DAPI sithSector_GetSectorIndexEx(const SithWorld* pWorld, const SithSector* pSector);
int J3DAPI sithSector_GetSectorIndex(const SithSector* pSector);

// Helper hooking functions
void sithSector_InstallHooks(void);
void sithSector_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHSECTOR_H
