#ifndef SITH_SITHCOGFUNCTIONSECTOR_H
#define SITH_SITHCOGFUNCTIONSECTOR_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithCogFunctionSector_RegisterFunctions(SithCogSymbolTable* pTable);
void J3DAPI sithCogFunctionSector_GetSectorTint(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorTint(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorLight(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorLight(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorAdjoins(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorSurfflags(SithCog* pCog);
void J3DAPI sithCogFunctionSector_ClearSectorSurfflags(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorColormap(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorColormap(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorThrust(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorThrust(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SetSectorFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSector_ClearSectorFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorFlags(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorThingCount(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorPlayerCount(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorCount(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorCenter(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetNumSectorVertices(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetNumSectorSurfaces(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorVertexPos(SithCog* pCog);
void J3DAPI sithCogFunctionSector_GetSectorSurfaceRef(SithCog* pCog);
void J3DAPI sithCogFunctionSector_SyncSector(SithCog* pCog);
void J3DAPI sithCogFunctionSector_FindSectorAtPos(SithCog* pCog);

// Helper hooking functions
void sithCogFunctionSector_InstallHooks(void);
void sithCogFunctionSector_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGFUNCTIONSECTOR_H
