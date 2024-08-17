#include "sithItem.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithItem_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithItem_PlayerCollisionHandler);
    // J3D_HOOKFUNC(sithItem_Initialize);
    // J3D_HOOKFUNC(sithItem_SetItemTaken);
    // J3D_HOOKFUNC(sithItem_Remove);
    // J3D_HOOKFUNC(sithItem_ParseArg);
}

void sithItem_ResetGlobals(void)
{

}

int J3DAPI sithItem_PlayerCollisionHandler(SithThing* pItem, SithThing* pPlayer, SithCollision* pCollision, int a5)
{
    return J3D_TRAMPOLINE_CALL(sithItem_PlayerCollisionHandler, pItem, pPlayer, pCollision, a5);
}

void J3DAPI sithItem_Initialize(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithItem_Initialize, pThing);
}

void J3DAPI sithItem_SetItemTaken(SithThing* pItem, const SithThing* pSrcThing, int bNoMultiSync)
{
    J3D_TRAMPOLINE_CALL(sithItem_SetItemTaken, pItem, pSrcThing, bNoMultiSync);
}

void J3DAPI sithItem_Remove(SithThing* pItem)
{
    J3D_TRAMPOLINE_CALL(sithItem_Remove, pItem);
}

int J3DAPI sithItem_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum)
{
    return J3D_TRAMPOLINE_CALL(sithItem_ParseArg, pArg, pThing, adjNum);
}
