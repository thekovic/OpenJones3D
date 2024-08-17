#include "rdMatrix.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdMatrix_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdMatrix_Build34);
    // J3D_HOOKFUNC(rdMatrix_BuildFromLook34);
    // J3D_HOOKFUNC(rdMatrix_InvertOrtho34);
    // J3D_HOOKFUNC(rdMatrix_BuildRotate34);
    // J3D_HOOKFUNC(rdMatrix_BuildTranslate34);
    // J3D_HOOKFUNC(rdMatrix_BuildScale34);
    // J3D_HOOKFUNC(rdMatrix_BuildFromVectorAngle34);
    // J3D_HOOKFUNC(rdMatrix_LookAt);
    // J3D_HOOKFUNC(rdMatrix_ExtractAngles34);
    // J3D_HOOKFUNC(rdMatrix_Normalize34);
    // J3D_HOOKFUNC(rdMatrix_Copy34);
    // J3D_HOOKFUNC(rdMatrix_Multiply34);
    // J3D_HOOKFUNC(rdMatrix_PreMultiply34);
    // J3D_HOOKFUNC(rdMatrix_PostMultiply34);
    // J3D_HOOKFUNC(rdMatrix_PreRotate34);
    // J3D_HOOKFUNC(rdMatrix_PostRotate34);
    // J3D_HOOKFUNC(rdMatrix_PreTranslate34);
    // J3D_HOOKFUNC(rdMatrix_PostTranslate34);
    // J3D_HOOKFUNC(rdMatrix_PostScale34);
    // J3D_HOOKFUNC(rdMatrix_TransformVector34);
    // J3D_HOOKFUNC(rdMatrix_TransformVectorOrtho34);
    // J3D_HOOKFUNC(rdMatrix_TransformVector34Acc);
    // J3D_HOOKFUNC(rdMatrix_TransformPoint34);
    // J3D_HOOKFUNC(rdMatrix_TransformPoint34Acc);
    // J3D_HOOKFUNC(rdMatrix_TransformPointList34);
}

void rdMatrix_ResetGlobals(void)
{

}

void J3DAPI rdMatrix_Build34(rdMatrix34* mat, const rdVector3* pyr, const rdVector3* pos)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_Build34, mat, pyr, pos);
}

void J3DAPI rdMatrix_BuildFromLook34(rdMatrix34* mat, const rdVector3* look)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_BuildFromLook34, mat, look);
}

void J3DAPI rdMatrix_InvertOrtho34(rdMatrix34* dest, const rdMatrix34* src)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_InvertOrtho34, dest, src);
}

void J3DAPI rdMatrix_BuildRotate34(rdMatrix34* mat, const rdVector3* pyr)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_BuildRotate34, mat, pyr);
}

void J3DAPI rdMatrix_BuildTranslate34(rdMatrix34* mat, const rdVector3* vec)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_BuildTranslate34, mat, vec);
}

void J3DAPI rdMatrix_BuildScale34(rdMatrix34* mat, const rdVector3* scale)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_BuildScale34, mat, scale);
}

void J3DAPI rdMatrix_BuildFromVectorAngle34(rdMatrix34* mat, const rdVector3* vec, float angle)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_BuildFromVectorAngle34, mat, vec, angle);
}

void J3DAPI rdMatrix_LookAt(rdMatrix34* mat, const rdVector3* eyePos, const rdVector3* lookPos, float angle)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_LookAt, mat, eyePos, lookPos, angle);
}

void J3DAPI rdMatrix_ExtractAngles34(const rdMatrix34* mat, rdVector3* pyr)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_ExtractAngles34, mat, pyr);
}

void J3DAPI rdMatrix_Normalize34(rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_Normalize34, mat);
}

void J3DAPI rdMatrix_Copy34(rdMatrix34* dest, const rdMatrix34* src)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_Copy34, dest, src);
}

void J3DAPI rdMatrix_Multiply34(rdMatrix34* dest, const rdMatrix34* a, const rdMatrix34* b)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_Multiply34, dest, a, b);
}

void J3DAPI rdMatrix_PreMultiply34(rdMatrix34* a, const rdMatrix34* b)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PreMultiply34, a, b);
}

void J3DAPI rdMatrix_PostMultiply34(rdMatrix34* a, const rdMatrix34* b)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PostMultiply34, a, b);
}

void J3DAPI rdMatrix_PreRotate34(rdMatrix34* mat, const rdVector3* pyr)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PreRotate34, mat, pyr);
}

void J3DAPI rdMatrix_PostRotate34(rdMatrix34* mat, const rdVector3* vecPYR)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PostRotate34, mat, vecPYR);
}

void J3DAPI rdMatrix_PreTranslate34(rdMatrix34* mat, const rdVector3* vec)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PreTranslate34, mat, vec);
}

void J3DAPI rdMatrix_PostTranslate34(rdMatrix34* pMat, const rdVector3* pVec)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PostTranslate34, pMat, pVec);
}

void J3DAPI rdMatrix_PostScale34(rdMatrix34* mat, const rdVector3* vec)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_PostScale34, mat, vec);
}

void J3DAPI rdMatrix_TransformVector34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformVector34, dest, src, mat);
}

void J3DAPI rdMatrix_TransformVectorOrtho34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformVectorOrtho34, dest, src, mat);
}

void J3DAPI rdMatrix_TransformVector34Acc(rdVector3* dest, const rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformVector34Acc, dest, mat);
}

void J3DAPI rdMatrix_TransformPoint34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformPoint34, dest, src, mat);
}

void J3DAPI rdMatrix_TransformPoint34Acc(rdVector3* dest, const rdMatrix34* mat)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformPoint34Acc, dest, mat);
}

void J3DAPI rdMatrix_TransformPointList34(const rdMatrix34* mat, const rdVector3* aSrc, rdVector3* aDest, size_t size)
{
    J3D_TRAMPOLINE_CALL(rdMatrix_TransformPointList34, mat, aSrc, aDest, size);
}
