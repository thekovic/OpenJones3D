#include "sithPVS.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithPVS_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPVS_NDYReadPVSSection);
    // J3D_HOOKFUNC(sithPVS_CNDWritePVSSection);
    // J3D_HOOKFUNC(sithPVS_CNDReadPVSSection);
    // J3D_HOOKFUNC(sithPVS_SetTable);
}

void sithPVS_ResetGlobals(void)
{

}

int J3DAPI sithPVS_NDYReadPVSSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithPVS_NDYReadPVSSection, pWorld, bSkip);
}

int J3DAPI sithPVS_CNDWritePVSSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPVS_CNDWritePVSSection, fh, pWorld);
}

int J3DAPI sithPVS_CNDReadPVSSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithPVS_CNDReadPVSSection, fh, pWorld);
}

void J3DAPI sithPVS_SetTable(uint8_t* paAdjoinTable, uint8_t* aElements, int size)
{
    J3D_TRAMPOLINE_CALL(sithPVS_SetTable, paAdjoinTable, aElements, size);
}
