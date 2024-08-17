#include "rdThing.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdThing_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdThing_New);
    // J3D_HOOKFUNC(rdThing_NewEntry);
    // J3D_HOOKFUNC(rdThing_Free);
    // J3D_HOOKFUNC(rdThing_FreeEntry);
    // J3D_HOOKFUNC(rdThing_SetModel3);
    // J3D_HOOKFUNC(rdThing_SetSprite3);
    // J3D_HOOKFUNC(rdThing_SetPolyline);
    // J3D_HOOKFUNC(rdThing_SetParticleCloud);
    // J3D_HOOKFUNC(rdThing_Draw);
    // J3D_HOOKFUNC(rdThing_AccumulateMatrices);
}

void rdThing_ResetGlobals(void)
{

}

rdThing* J3DAPI rdThing_New(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(rdThing_New, pThing);
}

void J3DAPI rdThing_NewEntry(rdThing* prdThing, SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(rdThing_NewEntry, prdThing, pThing);
}

void J3DAPI rdThing_Free(rdThing* pThing)
{
    J3D_TRAMPOLINE_CALL(rdThing_Free, pThing);
}

void J3DAPI rdThing_FreeEntry(rdThing* pThing)
{
    J3D_TRAMPOLINE_CALL(rdThing_FreeEntry, pThing);
}

int J3DAPI rdThing_SetModel3(rdThing* pThing, rdModel3* pModel3)
{
    return J3D_TRAMPOLINE_CALL(rdThing_SetModel3, pThing, pModel3);
}

int J3DAPI rdThing_SetSprite3(rdThing* pThing, rdSprite3* pSprite3)
{
    return J3D_TRAMPOLINE_CALL(rdThing_SetSprite3, pThing, pSprite3);
}

int J3DAPI rdThing_SetPolyline(rdThing* pThing, rdPolyline* pPolyline)
{
    return J3D_TRAMPOLINE_CALL(rdThing_SetPolyline, pThing, pPolyline);
}

int J3DAPI rdThing_SetParticleCloud(rdThing* pThing, rdParticle* pParticle)
{
    return J3D_TRAMPOLINE_CALL(rdThing_SetParticleCloud, pThing, pParticle);
}

int J3DAPI rdThing_Draw(rdThing* pThing, const rdMatrix34* pOrient)
{
    return J3D_TRAMPOLINE_CALL(rdThing_Draw, pThing, pOrient);
}

void J3DAPI rdThing_AccumulateMatrices(rdThing* prdThing, const rdModel3HNode* pNode, const rdMatrix34* pPlacement)
{
    J3D_TRAMPOLINE_CALL(rdThing_AccumulateMatrices, prdThing, pNode, pPlacement);
}
