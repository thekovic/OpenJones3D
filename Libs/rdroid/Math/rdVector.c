#include "rdVector.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdVector_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdVector_Set3);
    // J3D_HOOKFUNC(rdVector_Set4);
    // J3D_HOOKFUNC(rdVector_Neg3);
    // J3D_HOOKFUNC(rdVector_Add3Acc);
    // J3D_HOOKFUNC(rdVector_Dot3);
    // J3D_HOOKFUNC(rdVector_Len3);
    // J3D_HOOKFUNC(rdVector_Normalize3);
    // J3D_HOOKFUNC(rdVector_Normalize2Acc);
    // J3D_HOOKFUNC(rdVector_Normalize3Acc);
    // J3D_HOOKFUNC(rdVector_Normalize3QuickAcc);
    // J3D_HOOKFUNC(rdVector_InvScale3);
    // J3D_HOOKFUNC(rdVector_Rotate3);
    // J3D_HOOKFUNC(rdVector_Rotate3Acc);
}

void rdVector_ResetGlobals(void)
{

}

void J3DAPI rdVector_Set3(rdVector3* dest, float x, float y, float z)
{
    J3D_TRAMPOLINE_CALL(rdVector_Set3, dest, x, y, z);
}

void J3DAPI rdVector_Set4(rdVector4* dest, float x, float y, float z, float w)
{
    J3D_TRAMPOLINE_CALL(rdVector_Set4, dest, x, y, z, w);
}

void J3DAPI rdVector_Neg3(rdVector3* dest, const rdVector3* src)
{
    J3D_TRAMPOLINE_CALL(rdVector_Neg3, dest, src);
}

void J3DAPI rdVector_Add3Acc(rdVector3* a, const rdVector3* b)
{
    J3D_TRAMPOLINE_CALL(rdVector_Add3Acc, a, b);
}

float J3DAPI rdVector_Dot3(const rdVector3* a, const rdVector3* b)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Dot3, a, b);
}

float J3DAPI rdVector_Len3(const rdVector3* vec)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Len3, vec);
}

float J3DAPI rdVector_Normalize3(rdVector3* dest, const rdVector3* src)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Normalize3, dest, src);
}

float J3DAPI rdVector_Normalize2Acc(rdVector2* vec)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Normalize2Acc, vec);
}

float J3DAPI rdVector_Normalize3Acc(rdVector3* vec)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Normalize3Acc, vec);
}

float J3DAPI rdVector_Normalize3QuickAcc(rdVector3* src)
{
    return J3D_TRAMPOLINE_CALL(rdVector_Normalize3QuickAcc, src);
}

void J3DAPI rdVector_InvScale3(rdVector3* dest, const rdVector3* src, float scalar)
{
    J3D_TRAMPOLINE_CALL(rdVector_InvScale3, dest, src, scalar);
}

void J3DAPI rdVector_Rotate3(rdVector3* vec, const rdVector3* pivot, const rdVector3* pyr)
{
    J3D_TRAMPOLINE_CALL(rdVector_Rotate3, vec, pivot, pyr);
}

void J3DAPI rdVector_Rotate3Acc(rdVector3* vec, const rdVector3* pyr)
{
    J3D_TRAMPOLINE_CALL(rdVector_Rotate3Acc, vec, pyr);
}
