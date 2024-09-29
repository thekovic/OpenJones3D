#include "rdMatrix.h"
#include "rdVector.h"

#include <j3dcore/j3dhook.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/RTI/symbols.h>

#include <math.h>

void rdVector_InstallHooks(void)
{
    J3D_HOOKFUNC(rdVector_Set3);
    J3D_HOOKFUNC(rdVector_Set4);
    J3D_HOOKFUNC(rdVector_Neg3);
    J3D_HOOKFUNC(rdVector_Add3Acc);
    J3D_HOOKFUNC(rdVector_Dot3);
    J3D_HOOKFUNC(rdVector_Len3);
    J3D_HOOKFUNC(rdVector_Normalize3);
    J3D_HOOKFUNC(rdVector_Normalize2Acc);
    J3D_HOOKFUNC(rdVector_Normalize3Acc);
    J3D_HOOKFUNC(rdVector_Normalize3QuickAcc);
    J3D_HOOKFUNC(rdVector_InvScale3);
    J3D_HOOKFUNC(rdVector_Rotate3);
    J3D_HOOKFUNC(rdVector_Rotate3Acc);
}

void rdVector_ResetGlobals(void)
{
    static const rdVector3 rdroid_g_zeroVector3_tmp = { { 0.0f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector3*)&rdroid_g_zeroVector3, &rdroid_g_zeroVector3_tmp, sizeof(rdroid_g_zeroVector3));

    static const rdVector3 rdroid_g_xVector3_tmp = { { 1.0f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector3*)&rdroid_g_xVector3, &rdroid_g_xVector3_tmp, sizeof(rdroid_g_xVector3));

    static const rdVector3 rdroid_g_yVector3_tmp = { { 0.0f }, { 1.0f }, { 0.0f } };
    memcpy((rdVector3*)&rdroid_g_yVector3, &rdroid_g_yVector3_tmp, sizeof(rdroid_g_yVector3));

    static const rdVector3 rdroid_g_zVector3_tmp = { { 0.0f }, { 0.0f }, { 1.0f } };
    memcpy((rdVector3*)&rdroid_g_zVector3, &rdroid_g_zVector3_tmp, sizeof(rdroid_g_zVector3));
}

float J3DAPI rdVector_Normalize2(rdVector2* dest, const rdVector2* src)
{
    RD_ASSERTREL(dest != src);
    float len = sqrtf(src->x * src->x + src->y * src->y);
    if ( len == 0.0f )
    {
        dest->x = src->x;
        dest->y = src->y;
    }
    else
    {
        dest->x = src->x / len;
        dest->y = src->y / len;
    }

    return len;
}

float J3DAPI rdVector_Normalize3(rdVector3* dest, const rdVector3* src)
{
    RD_ASSERTREL(dest != src);
    float len = sqrtf(src->x * src->x + src->y * src->y + src->z * src->z);
    if ( len == 0.0f )
    {
        dest->x = src->x;
        dest->y = src->y;
        dest->z = src->z;
    }
    else
    {
        dest->x = src->x / len;
        dest->y = src->y / len;
        dest->z = src->z / len;
    }

    return len;
}

float J3DAPI rdVector_Normalize4(rdVector4* dest, const rdVector4* src)
{
    RD_ASSERTREL(dest != src);
    float len = sqrtf(src->x * src->x + src->y * src->y + src->z * src->z + src->w * src->w);
    if ( len == 0.0f )
    {
        dest->x = src->x;
        dest->y = src->y;
        dest->z = src->z;
        dest->w = src->w;
    }
    else
    {
        dest->x = src->x / len;
        dest->y = src->y / len;
        dest->z = src->z / len;
        dest->w = src->w / len;
    }

    return len;
}


float J3DAPI rdVector_Normalize2Acc(rdVector2* vec)
{
    float magnitude = sqrtf(vec->y * vec->y + vec->x * vec->x);
    if ( magnitude == 0.0f )
    {
        return magnitude;
    }

    vec->x = vec->x / magnitude;
    vec->y = vec->y / magnitude;
    return magnitude;
}

float J3DAPI rdVector_Normalize3Acc(rdVector3* vec)
{
    float len = sqrtf(vec->y * vec->y + vec->z * vec->z + vec->x * vec->x);
    if ( len == 0.0f ) {
        return len;
    }

    float invLen = 1.0f / len;
    vec->x = vec->x * invLen;
    vec->y = vec->y * invLen;
    vec->z = vec->z * invLen;
    return len;
}

float J3DAPI rdVector_Normalize3QuickAcc(rdVector3* src)
{
    float z;
    float y;
    float x;
    float min;
    float v6;
    float v7;
    float max;
    float med;

    if ( src->x >= 0.0f )
    {
        x = src->x;
    }
    else
    {
        x = -src->x;
    }

    max = x;
    if ( src->y >= 0.0f )
    {
        y = src->y;
    }
    else
    {
        y = -src->y;
    }

    med = y;
    if ( src->z >= 0.0f )
    {
        z = src->z;
    }
    else
    {
        z = -src->z;
    }

    min = z;
    if ( z <= y )
    {
        if ( x < y )
        {
            med = x;
            max = y;
            if ( z > x )
            {
                min = x;
                med = z;
            }
        }
    }
    else if ( z <= x )
    {
        min = y;
        med = z;
    }
    else
    {
        min = x;
        max = z;
        if ( y < x )
        {
            min = y;
            med = x;
        }
    }

    RD_ASSERTREL((min <= med) && (med <= max));
    v6 = 0.34375f * med + 0.25f * min + max;
    v7 = 1.0f / v6;
    src->x = src->x * v7;
    src->y = src->y * v7;
    src->z = src->z * v7;
    return v6;
}

float J3DAPI rdVector_Normalize4Acc(rdVector4* vec)
{
    float len = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z + vec->w * vec->w);
    if ( len == 0.0f ) {
        return len;
    }

    float invLen = 1.0f / len;
    vec->x = vec->x * invLen;
    vec->y = vec->y * invLen;
    vec->z = vec->z * invLen;
    vec->w = vec->w * invLen;
    return len;
}

void J3DAPI rdVector_Rotate3(rdVector3* vec, const rdVector3* pivot, const rdVector3* pyr)
{
    rdMatrix34 mat;
    rdMatrix_BuildRotate34(&mat, pyr);
    rdMatrix_TransformVector34(vec, pivot, &mat);
}

void J3DAPI rdVector_Rotate3Acc(rdVector3* vec, const rdVector3* pyr)
{
    rdMatrix34 mat;
    rdMatrix_BuildRotate34(&mat, pyr);
    rdMatrix_TransformVector34Acc(vec, &mat);
}

