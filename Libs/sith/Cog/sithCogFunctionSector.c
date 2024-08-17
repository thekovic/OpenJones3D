#include "sithCogFunctionSector.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogFunctionSector_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogFunctionSector_RegisterFunctions);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorTint);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorTint);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorLight);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorLight);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorAdjoins);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorSurfflags);
    // J3D_HOOKFUNC(sithCogFunctionSector_ClearSectorSurfflags);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorColormap);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorColormap);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorThrust);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorThrust);
    // J3D_HOOKFUNC(sithCogFunctionSector_SetSectorFlags);
    // J3D_HOOKFUNC(sithCogFunctionSector_ClearSectorFlags);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorFlags);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorThingCount);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorPlayerCount);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorCount);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorCenter);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetNumSectorVertices);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetNumSectorSurfaces);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorVertexPos);
    // J3D_HOOKFUNC(sithCogFunctionSector_GetSectorSurfaceRef);
    // J3D_HOOKFUNC(sithCogFunctionSector_SyncSector);
    // J3D_HOOKFUNC(sithCogFunctionSector_FindSectorAtPos);
}

void sithCogFunctionSector_ResetGlobals(void)
{

}

int J3DAPI sithCogFunctionSector_RegisterFunctions(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogFunctionSector_RegisterFunctions, pTable);
}

void J3DAPI sithCogFunctionSector_GetSectorTint(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorTint, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorTint(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorTint, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorLight, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorLight(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorLight, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorAdjoins(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorAdjoins, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorSurfflags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorSurfflags, pCog);
}

void J3DAPI sithCogFunctionSector_ClearSectorSurfflags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_ClearSectorSurfflags, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorColormap(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorColormap, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorColormap(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorColormap, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorThrust, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorThrust(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorThrust, pCog);
}

void J3DAPI sithCogFunctionSector_SetSectorFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SetSectorFlags, pCog);
}

void J3DAPI sithCogFunctionSector_ClearSectorFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_ClearSectorFlags, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorFlags(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorFlags, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorThingCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorThingCount, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorPlayerCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorPlayerCount, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorCount(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorCount, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorCenter(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorCenter, pCog);
}

void J3DAPI sithCogFunctionSector_GetNumSectorVertices(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetNumSectorVertices, pCog);
}

void J3DAPI sithCogFunctionSector_GetNumSectorSurfaces(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetNumSectorSurfaces, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorVertexPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorVertexPos, pCog);
}

void J3DAPI sithCogFunctionSector_GetSectorSurfaceRef(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_GetSectorSurfaceRef, pCog);
}

void J3DAPI sithCogFunctionSector_SyncSector(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_SyncSector, pCog);
}

void J3DAPI sithCogFunctionSector_FindSectorAtPos(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogFunctionSector_FindSectorAtPos, pCog);
}
