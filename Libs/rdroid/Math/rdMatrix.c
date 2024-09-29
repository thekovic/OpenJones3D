#include "rdMatrix.h"
#include "rdVector.h"

#include <j3dcore/j3dhook.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/RTI/symbols.h>

#include <std/General/stdMath.h>


void rdMatrix_InstallHooks(void)
{
    J3D_HOOKFUNC(rdMatrix_Build34);
    J3D_HOOKFUNC(rdMatrix_BuildFromLook34);
    J3D_HOOKFUNC(rdMatrix_InvertOrtho34);
    J3D_HOOKFUNC(rdMatrix_BuildRotate34);
    J3D_HOOKFUNC(rdMatrix_BuildTranslate34);
    J3D_HOOKFUNC(rdMatrix_BuildScale34);
    J3D_HOOKFUNC(rdMatrix_BuildFromVectorAngle34);
    J3D_HOOKFUNC(rdMatrix_LookAt);
    J3D_HOOKFUNC(rdMatrix_ExtractAngles34);
    J3D_HOOKFUNC(rdMatrix_Normalize34);
    J3D_HOOKFUNC(rdMatrix_Copy34);
    J3D_HOOKFUNC(rdMatrix_Multiply34);
    J3D_HOOKFUNC(rdMatrix_PreMultiply34);
    J3D_HOOKFUNC(rdMatrix_PostMultiply34);
    J3D_HOOKFUNC(rdMatrix_PreRotate34);
    J3D_HOOKFUNC(rdMatrix_PostRotate34);
    J3D_HOOKFUNC(rdMatrix_PreTranslate34);
    J3D_HOOKFUNC(rdMatrix_PostTranslate34);
    J3D_HOOKFUNC(rdMatrix_PostScale34);
    J3D_HOOKFUNC(rdMatrix_TransformVector34);
    J3D_HOOKFUNC(rdMatrix_TransformVectorOrtho34);
    J3D_HOOKFUNC(rdMatrix_TransformVector34Acc);
    J3D_HOOKFUNC(rdMatrix_TransformPoint34);
    J3D_HOOKFUNC(rdMatrix_TransformPoint34Acc);
    J3D_HOOKFUNC(rdMatrix_TransformPointList34);
}

void rdMatrix_ResetGlobals(void)
{
    static const rdMatrix34 rdroid_g_identMatrix34_tmp = {
      { { 1.0f }, { 0.0f }, { 0.0f } },
      { { 0.0f }, { 1.0f }, { 0.0f } },
      { { 0.0f }, { 0.0f }, { 1.0f } },
      { { 0.0f }, { 0.0f }, { 0.0f } }
    };
    memcpy((rdMatrix34*)&rdroid_g_identMatrix34, &rdroid_g_identMatrix34_tmp, sizeof(rdroid_g_identMatrix34));
}

void J3DAPI rdMatrix_Build34(rdMatrix34* res, const rdVector3* pyr, const rdVector3* pos)
{
    float yCos;
    float zSin;
    float xSin;
    float zCos;
    float xCos;
    float ySin;

    stdMath_SinCos(pyr->x, &xSin, &xCos);
    stdMath_SinCos(pyr->y, &ySin, &yCos);
    stdMath_SinCos(pyr->z, &zSin, &zCos);

    float yzCos = yCos * zCos;
    float yzSin = ySin * zSin;
    float v7 = yCos * zSin;
    float v8 = ySin * zCos;

    res->rvec.x = -yzSin * xSin + yzCos;
    res->rvec.y = v7 * xSin + v8;
    res->rvec.z = -zSin * xCos;

    res->lvec.x = -ySin * xCos;
    res->lvec.y = yCos * xCos;
    res->lvec.z = xSin;

    res->uvec.x = v8 * xSin + v7;
    res->uvec.y = -xSin * yzCos + yzSin;
    res->uvec.z = zCos * xCos;

    memcpy(&res->dvec, pos, sizeof(res->dvec));
}

void J3DAPI rdMatrix_BuildFromLook34(rdMatrix34* mat, const rdVector3* look)
{
    RD_ASSERTREL(mat && look);
    memcpy(&mat->lvec, look, sizeof(mat->lvec));

    //mat->rvec.x = mat->lvec.y * 1.0f - mat->lvec.z * 0.0f;
    //mat->rvec.y = mat->lvec.z * 0.0f - mat->lvec.x * 1.0f;
    //mat->rvec.z = mat->lvec.x * 0.0f - mat->lvec.y * 0.0f;

    rdVector_Cross3(&mat->rvec, &mat->lvec, &rdroid_g_zVector3);
    if ( rdVector_Normalize3Acc(&mat->rvec) == 0.0f )
    {
        /*mat->uvec.x = mat->lvec.z * 0.0f - mat->lvec.y * 0.0f;
        mat->uvec.y = mat->lvec.x * 0.0f - mat->lvec.z * 1.0f;
        mat->uvec.z = mat->lvec.y * 1.0f - mat->lvec.x * 0.0f;*/

        rdVector_Cross3(&mat->uvec, &mat->lvec, &rdroid_g_xVector3);
        rdVector_Normalize3Acc(&mat->uvec);

        /*mat->rvec.x = mat->lvec.y * mat->uvec.z - mat->lvec.z * mat->uvec.y;
        mat->rvec.y = mat->lvec.z * mat->uvec.x - mat->lvec.x * mat->uvec.z;
        mat->rvec.z = mat->lvec.x * mat->uvec.y - mat->lvec.y * mat->uvec.x;*/
        rdVector_Cross3(&mat->rvec, &mat->lvec, &mat->uvec);
    }
    else
    {
        /*mat->uvec.x = mat->rvec.y * mat->lvec.z - mat->rvec.z * mat->lvec.y;
        mat->uvec.y = mat->rvec.z * mat->lvec.x - mat->lvec.z * mat->rvec.x;
        mat->uvec.z = mat->lvec.y * mat->rvec.x - mat->rvec.y * mat->lvec.x;*/
        rdVector_Cross3(&mat->uvec, &mat->rvec, &mat->lvec);
    }
}

void J3DAPI rdMatrix_InvertOrtho34(rdMatrix34* dest, const rdMatrix34* src)
{
    float z;
    float y;
    float x;

    dest->rvec.x = src->rvec.x;
    dest->rvec.y = src->lvec.x;
    dest->rvec.z = src->uvec.x;

    dest->lvec.x = src->rvec.y;
    dest->lvec.z = src->uvec.y;
    dest->lvec.y = src->lvec.y;

    dest->uvec.x = src->rvec.z;
    dest->uvec.y = src->lvec.z;
    dest->uvec.z = src->uvec.z;

    x = src->dvec.x;
    y = src->dvec.y;
    z = src->dvec.z;
    dest->dvec.x = -(x * src->rvec.x + src->rvec.y * y + src->rvec.z * z);
    dest->dvec.y = -(src->lvec.x * x + src->lvec.y * y + src->lvec.z * z);
    dest->dvec.z = -(src->uvec.x * x + src->uvec.y * y + src->uvec.z * z);
}

void J3DAPI rdMatrix_BuildRotate34(rdMatrix34* mat, const rdVector3* pyr)
{
    float yCos;
    float zSin;
    float xSin;
    float yzSin;
    float v6;
    float v7;
    float yzCos;
    float zCos;
    float xCos;
    float ySin;

    stdMath_SinCos(pyr->x, &xSin, &xCos);
    stdMath_SinCos(pyr->y, &ySin, &yCos);
    stdMath_SinCos(pyr->z, &zSin, &zCos);

    yzCos = yCos * zCos;
    yzSin = ySin * zSin;
    v6 = yCos * zSin;
    v7 = ySin * zCos;

    mat->rvec.x = -yzSin * xSin + yzCos;
    mat->rvec.y = v6 * xSin + v7;
    mat->rvec.z = -zSin * xCos;

    mat->lvec.x = -ySin * xCos;
    mat->lvec.y = yCos * xCos;
    mat->lvec.z = xSin;

    mat->uvec.x = v7 * xSin + v6;
    mat->uvec.y = -xSin * yzCos + yzSin;
    mat->uvec.z = zCos * xCos;

    memset(&mat->dvec, 0, sizeof(mat->dvec));
}

void J3DAPI rdMatrix_BuildTranslate34(rdMatrix34* mat, const rdVector3* vec)
{
    memcpy(mat, &rdroid_g_identMatrix34, sizeof(rdMatrix34));
    memcpy(&mat->dvec, vec, sizeof(mat->dvec));
}

void J3DAPI rdMatrix_BuildScale34(rdMatrix34* mat, const rdVector3* scale)
{
    mat->rvec.x = scale->x;
    mat->rvec.y = 0.0f;
    mat->rvec.z = 0.0f;

    mat->lvec.x = 0.0f;
    mat->lvec.y = scale->y;
    mat->lvec.z = 0.0f;

    mat->uvec.x = 0.0f;
    mat->uvec.y = 0.0f;
    mat->uvec.z = scale->z;

    memset(&mat->dvec, 0, sizeof(mat->dvec));
}

// TODO: test throughly rdMatrix_BuildFromVectorAngle34 function before removing this function
void J3DAPI rdMatrix_BuildFromVectorAngle34_old(rdMatrix34* mat, const rdVector3* vec, float angle)
{
    float v3;
    float v4;
    float v5;
    float v6;
    float v7;
    float v8;
    float v9;
    float v10;
    float v11;
    float v12;
    float zy;
    float angCos;
    float zx;
    float angSin;
    float v17;
    float v18;
    float yx;

    stdMath_SinCos(angle, &angSin, &angCos);
    if ( vec->z < 1.0f )
    {
        if ( vec->z > -1.0f )
        {
            v17 = 1.0f - angCos; // 2*sin(angle/2)^2

            yx = vec->y * vec->x;
            zy = vec->z * vec->y;
            zx = vec->z * vec->x;

            v7 = angSin * vec->x;
            v6 = vec->y * angSin;
            v4 = vec->z * angSin;
            v11 = vec->x * vec->x;
            v5 = vec->y * vec->y;
            v18 = 1.0f - v11 - v5;
            v12 = 1.0f - v18;
            v9 = angCos * v11;
            v3 = angCos * v5;
            v10 = v17 * zx;
            v8 = v17 * zy;
            mat->rvec.x = (v9 * v18 + v3) / v12 + v11;
            mat->lvec.y = (v3 * v18 + v9) / v12 + v5;
            mat->uvec.z = v18 + v9 + v3;
            mat->rvec.y = v17 * yx + v4;
            mat->lvec.x = v17 * yx - v4;
            mat->rvec.z = v10 - v6;
            mat->lvec.z = v8 + v7;
            mat->uvec.x = v10 + v6;
            mat->uvec.y = v8 - v7;
        }
        else
        {
            mat->rvec.x = angCos;
            mat->rvec.y = -angSin;
            mat->rvec.z = 0.0f;

            mat->lvec.x = angSin;
            mat->lvec.y = angCos;
            mat->lvec.z = 0.0f;

            mat->uvec.x = 0.0f;
            mat->uvec.y = 0.0f;
            mat->uvec.z = 1.0f;
        }
    }
    else
    {
        mat->rvec.x = angCos;
        mat->rvec.y = angSin;
        mat->rvec.z = 0.0f;

        mat->lvec.x = -angSin;
        mat->lvec.y = angCos;
        mat->lvec.z = 0.0f;

        mat->uvec.x = 0.0f;
        mat->uvec.y = 0.0f;
        mat->uvec.z = 1.0f;
    }

    mat->dvec.x = 0.0f;
    mat->dvec.y = 0.0f;
    mat->dvec.z = 0.0f;
}

void J3DAPI rdMatrix_BuildFromVectorAngle34(rdMatrix34* mat, const rdVector3* vec, float angle)
{
    float sinAngle, cosAngle;
    stdMath_SinCos(angle, &sinAngle, &cosAngle);

    if ( vec->z < 1.0f && vec->z > -1.0f )
    {
        float oneMinusCos = 1.0f - cosAngle; // 2*sin(angle/2)^2
        float xx = vec->x * vec->x;
        float yy = vec->y * vec->y;
        float zz = 1.0f - xx - yy;
        float xy = vec->x * vec->y;
        float xz = vec->x * vec->z;
        float yz = vec->y * vec->z;
        float xs = vec->x * sinAngle;
        float ys = vec->y * sinAngle;
        float zs = vec->z * sinAngle;
        float invZZ = 1.0f / (1.0f - zz);

        mat->rvec.x = (cosAngle * xx * zz + cosAngle * yy) * invZZ + xx;
        mat->lvec.y = (cosAngle * yy * zz + cosAngle * xx) * invZZ + yy;
        mat->uvec.z = zz + cosAngle * xx + cosAngle * yy;

        mat->rvec.y = oneMinusCos * xy + zs;
        mat->lvec.x = oneMinusCos * xy - zs;
        mat->rvec.z = oneMinusCos * xz - ys;
        mat->lvec.z = oneMinusCos * yz + xs;
        mat->uvec.x = oneMinusCos * xz + ys;
        mat->uvec.y = oneMinusCos * yz - xs;
    }
    else if ( vec->z <= -1.0f )
    {
        mat->rvec = (rdVector3){ cosAngle, -sinAngle, 0.0f };
        mat->lvec = (rdVector3){ sinAngle, cosAngle, 0.0f };
        mat->uvec = rdroid_g_zVector3;// (rdVector3) { 0.0f, 0.0f, 1.0f };
    }
    else // vec->z >= 1.0f
    {
        mat->rvec = (rdVector3){ cosAngle, sinAngle, 0.0f };
        mat->lvec = (rdVector3){ -sinAngle, cosAngle, 0.0f };
        mat->uvec = rdroid_g_zVector3; // (rdVector3) { 0.0f, 0.0f, 1.0f };
    }

    mat->dvec = rdroid_g_zeroVector3;//(rdVector3){ 0.0f, 0.0f, 0.0f };
}

void J3DAPI rdMatrix_LookAt(rdMatrix34* mat, const rdVector3* eyePos, const rdVector3* lookPos, float angle)
{
    /*mat->lvec.x = lookPos->x - eyePos->x;
    mat->lvec.y = lookPos->y - eyePos->y;
    mat->lvec.z = lookPos->z - eyePos->z;*/
    rdVector_Sub3(&mat->lvec, lookPos, eyePos);
    rdVector_Normalize3Acc(&mat->lvec);

    rdMatrix34 tmat = { 0 }; // Added: init to zero
    rdMatrix_BuildFromVectorAngle34(&tmat, &mat->lvec, angle);

    rdVector3 dir = { 0 }; // Added: init to zero
    double dot = fabs(rdVector_Dot3(&mat->lvec, &rdroid_g_zVector3));
    if ( dot <= 0.999 )
    {
        rdMatrix_TransformVector34(&dir, &rdroid_g_zVector3, &tmat);
    }
    else
    {
        rdVector3 fwdVector = rdroid_g_yVector3;
        if ( mat->lvec.z > 0.0f )
        {
            rdVector_Neg3Acc(&fwdVector);
        }
        rdMatrix_TransformVector34(&dir, &fwdVector, &tmat);
    }

    /* mat->rvec.x = mat->lvec.y * dir.z - mat->lvec.z * dir.y;
     mat->rvec.y = mat->lvec.z * dir.x - mat->lvec.x * dir.z;
     mat->rvec.z = mat->lvec.x * dir.y - mat->lvec.y * dir.x;*/
    rdVector_Cross3(&mat->rvec, &mat->lvec, &dir);
    rdVector_Normalize3Acc(&mat->rvec);

    /* mat->uvec.x = mat->rvec.y * mat->lvec.z - mat->rvec.z * mat->lvec.y;
     mat->uvec.y = mat->rvec.z * mat->lvec.x - mat->rvec.x * mat->lvec.z;
     mat->uvec.z = mat->rvec.x * mat->lvec.y - mat->rvec.y * mat->lvec.x;*/
    rdVector_Cross3(&mat->uvec, &mat->rvec, &mat->lvec);
    rdVector_Normalize3Acc(&mat->uvec);

    mat->dvec = *eyePos;
    //memcpy(&mat->dvec, eyePos, sizeof(mat->dvec));
}

void J3DAPI rdMatrix_ExtractAngles34_old(const rdMatrix34* mat, rdVector3* pyr)
{
    double v2;
    double v3;
    double v4;
    float v5;
    float v6;
    float v7;
    float v8;
    float v9;
    float v10;
    float v11;
    float v12;
    float v13;
    float v14;
    float v15;
    rdVector3 v16;
    float v17;
    float v18;
    float v19;
    float v20;
    float v21;

    rdVector_Copy3(&v16, &mat->lvec);
    v9 = -mat->rvec.x;
    v10 = -mat->rvec.y;
    v11 = -mat->rvec.z;

    v5 = v16.x * v16.x + v16.y * v16.y + 0.0f * 0.0f;
    v2 = sqrtf(v5);
    v15 = v2;
    if ( v2 >= 0.001f )
    {
        v7 = v16.y / v15;
        v18 = 90.0f - stdMath_ArcSin3(v7);
        if ( v16.x > 0.0f )
        {
            v18 = -v18;
        }

        pyr->y = v18;
    }
    else
    {
        v6 = -v9;
        v17 = 90.0f - stdMath_ArcSin3(v6);
        if ( v10 > 0.0f && v16.z > 0.0f || v10 < 0.0f && v16.z < 0.0f )
        {
            v17 = -v17;
        }

        pyr->z = v17;
        pyr->y = 0.0f;
    }

    if ( v15 >= 0.001f )
    {
        v3 = (v16.x * v16.x + v16.y * v16.y + 0.0f * v16.z) / v15;
        if ( v3 < 1.0f )
        {
            v12 = v3;
            v19 = 90.0f - stdMath_ArcSin3(v12);
            pyr->x = v19;
        }
        else
        {
            pyr->x = 0.0f;
        }
    }
    else
    {
        pyr->x = 90.0f;
    }

    if ( v16.z < 0.0f )
    {
        pyr->x = -pyr->x;
    }

    v21 = -v16.y;
    v8 = v21 * v21 + v16.x * v16.x + 0.0f * 0.0f;
    v14 = sqrtf(v8);
    if ( v15 >= 0.001f )
    {
        v4 = (v21 * v9 + v16.x * v10 + 0.0f * v11) / v14;
        v13 = v4;
        if ( v4 < 1.0f )
        {
            if ( v13 > -1.0f )
            {
                v20 = 90.0f - stdMath_ArcSin3(v13);
                pyr->z = v20;
            }
            else
            {
                pyr->z = 180.0f;
            }
        }
        else
        {
            pyr->z = 0.0f;
        }

        if ( v11 < 0.0f )
        {
            pyr->z = -pyr->z;
        }
    }
}

void J3DAPI rdMatrix_ExtractAngles34(const rdMatrix34* mat, rdVector3* pyr)
{
    float negRightX = -mat->rvec.x;
    float negRightY = -mat->rvec.y;
    float negRightZ = -mat->rvec.z;

    rdVector3 vecFwd;
    rdVector_Copy3(&vecFwd, &mat->lvec);
    float fwdLenXY = sqrtf(vecFwd.x * vecFwd.x + vecFwd.y * vecFwd.y);

    // Calculate Yaw (Y)
    if ( fwdLenXY >= 0.001f )
    {
        float sinYaw = vecFwd.y / fwdLenXY;
        pyr->yaw = 90.0f - stdMath_ArcSin3(sinYaw);
        if ( vecFwd.x > 0.0f ) {
            pyr->yaw = -pyr->yaw;
        }
    }
    else
    {
        float sinYaw = -negRightX;
        pyr->yaw  = 0.0f;
        pyr->roll = 90.0f - stdMath_ArcSin3(sinYaw);
        if ( (negRightY > 0.0f && vecFwd.z > 0.0f) || (negRightY < 0.0f && vecFwd.z < 0.0f) ) {
            pyr->roll = -pyr->roll;
        }
    }

    // Calculate Pitch (X)
    pyr->pitch = 90.0f;
    if ( fwdLenXY >= 0.001f )
    {
        float sinPitch = (vecFwd.x * vecFwd.x + vecFwd.y * vecFwd.y) / fwdLenXY;
        if ( sinPitch < 1.0f ) {
            pyr->pitch = 90.0f - stdMath_ArcSin3(sinPitch);
        }
        else {
            pyr->pitch = 0.0f;
        }
    }

    if ( vecFwd.z < 0.0f ) {
        pyr->pitch = -pyr->pitch;
    }

    // Calculate Roll (Z)
    float negUpY = -vecFwd.y;
    float upXYLen = sqrtf(negUpY * negUpY + vecFwd.x * vecFwd.x);

    if ( fwdLenXY >= 0.001f )
    {
        pyr->roll = 0.0f;
        float sinRoll = (negUpY * negRightX + vecFwd.x * negRightY) / upXYLen;
        if ( sinRoll < 1.0f )
        {
            if ( sinRoll > -1.0f ) {
                pyr->roll= 90.0f - stdMath_ArcSin3(sinRoll);
            }
            else {
                pyr->roll = 180.0f;
            }
        }

        if ( negRightZ < 0.0f ) {
            pyr->roll = -pyr->roll;
        }
    }

    // TEST scope
    // TODO: Remove
    #ifdef J3D_DEBUG
    rdVector3 pyr2;
    rdMatrix_ExtractAngles34_old(mat, &pyr2);
    if ( ((pyr2.x != pyr->x) && (!isnan(pyr2.x) || !isnan(pyr->x)))
      || ((pyr2.y != pyr->y) && (!isnan(pyr2.y) || !isnan(pyr->y)))
      || ((pyr2.z != pyr->z) && (!isnan(pyr2.z) || !isnan(pyr->z)))
        )
    {
        RDLOG_ERROR("PYR p=%.f y%.f r=%.f op=%.f oy=%.f or=%.f\n", pyr2.x, pyr2.y, pyr2.z, pyr->x, pyr->y, pyr->z);
        //RDLOG_FATAL("pyr2.x == pyr->x && pyr2.y == pyr->y && pyr2.z == pyr->z");
    }
    #endif
    // TEST scope remove 
}

void J3DAPI rdMatrix_Normalize34(rdMatrix34* mat)
{
    mat->uvec.x = mat->rvec.y * mat->lvec.z - mat->rvec.z * mat->lvec.y;
    mat->uvec.y = mat->rvec.z * mat->lvec.x - mat->lvec.z * mat->rvec.x;
    mat->uvec.z = mat->rvec.x * mat->lvec.y - mat->rvec.y * mat->lvec.x;
    rdVector_Normalize3Acc(&mat->lvec);

    rdVector_Normalize3Acc(&mat->uvec);

    mat->rvec.x = mat->lvec.y * mat->uvec.z - mat->lvec.z * mat->uvec.y;
    mat->rvec.y = mat->lvec.z * mat->uvec.x - mat->lvec.x * mat->uvec.z;
    mat->rvec.z = mat->lvec.x * mat->uvec.y - mat->lvec.y * mat->uvec.x;
}

void __cdecl rdMatrix_Multiply34(rdMatrix34* dest, const rdMatrix34* a, const rdMatrix34* b)
{
    RD_ASSERTREL(((dest != a) && (dest != b)));

    dest->rvec.x = a->rvec.x * b->rvec.x + a->lvec.x * b->rvec.y + a->uvec.x * b->rvec.z;
    dest->rvec.y = a->rvec.y * b->rvec.x + a->lvec.y * b->rvec.y + a->uvec.y * b->rvec.z;
    dest->rvec.z = a->rvec.z * b->rvec.x + a->lvec.z * b->rvec.y + a->uvec.z * b->rvec.z;

    dest->lvec.x = b->lvec.x * a->rvec.x + a->lvec.x * b->lvec.y + a->uvec.x * b->lvec.z;
    dest->lvec.y = a->rvec.y * b->lvec.x + a->lvec.y * b->lvec.y + a->uvec.y * b->lvec.z;
    dest->lvec.z = a->rvec.z * b->lvec.x + a->lvec.z * b->lvec.y + a->uvec.z * b->lvec.z;

    dest->uvec.x = b->uvec.x * a->rvec.x + a->lvec.x * b->uvec.y + a->uvec.x * b->uvec.z;
    dest->uvec.y = a->rvec.y * b->uvec.x + a->lvec.y * b->uvec.y + a->uvec.y * b->uvec.z;
    dest->uvec.z = a->rvec.z * b->uvec.x + a->lvec.z * b->uvec.y + a->uvec.z * b->uvec.z;

    dest->dvec.x = b->dvec.x * a->rvec.x + a->lvec.x * b->dvec.y + a->uvec.x * b->dvec.z + a->dvec.x;
    dest->dvec.y = a->rvec.y * b->dvec.x + a->lvec.y * b->dvec.y + a->uvec.y * b->dvec.z + a->dvec.y;
    dest->dvec.z = a->rvec.z * b->dvec.x + a->lvec.z * b->dvec.y + a->uvec.z * b->dvec.z + a->dvec.z;
}

void J3DAPI rdMatrix_PreMultiply34(rdMatrix34* a, const rdMatrix34* b)
{
    rdMatrix34 acpy = { 0 };
    memcpy(&acpy, a, sizeof(acpy));
    a->rvec.x = acpy.rvec.x * b->rvec.x + b->rvec.y * acpy.lvec.x + b->rvec.z * acpy.uvec.x;
    a->rvec.y = acpy.rvec.y * b->rvec.x + b->rvec.y * acpy.lvec.y + b->rvec.z * acpy.uvec.y;
    a->rvec.z = acpy.rvec.z * b->rvec.x + b->rvec.y * acpy.lvec.z + b->rvec.z * acpy.uvec.z;

    a->lvec.x = b->lvec.x * acpy.rvec.x + b->lvec.y * acpy.lvec.x + b->lvec.z * acpy.uvec.x;
    a->lvec.y = b->lvec.x * acpy.rvec.y + b->lvec.y * acpy.lvec.y + b->lvec.z * acpy.uvec.y;
    a->lvec.z = b->lvec.x * acpy.rvec.z + b->lvec.y * acpy.lvec.z + b->lvec.z * acpy.uvec.z;

    a->uvec.x = b->uvec.x * acpy.rvec.x + b->uvec.y * acpy.lvec.x + b->uvec.z * acpy.uvec.x;
    a->uvec.y = b->uvec.x * acpy.rvec.y + b->uvec.y * acpy.lvec.y + b->uvec.z * acpy.uvec.y;
    a->uvec.z = b->uvec.x * acpy.rvec.z + b->uvec.y * acpy.lvec.z + b->uvec.z * acpy.uvec.z;

    a->dvec.x = b->dvec.x * acpy.rvec.x + b->dvec.y * acpy.lvec.x + b->dvec.z * acpy.uvec.x + acpy.dvec.x;
    a->dvec.y = b->dvec.x * acpy.rvec.y + b->dvec.y * acpy.lvec.y + b->dvec.z * acpy.uvec.y + acpy.dvec.y;
    a->dvec.z = b->dvec.x * acpy.rvec.z + b->dvec.y * acpy.lvec.z + b->dvec.z * acpy.uvec.z + acpy.dvec.z;
}

void J3DAPI rdMatrix_PostMultiply34(rdMatrix34* a, const rdMatrix34* b)
{
    rdMatrix34 acpy;
    memcpy(&acpy, a, sizeof(acpy));

    a->rvec.x = b->rvec.x * acpy.rvec.x + b->lvec.x * acpy.rvec.y + b->uvec.x * acpy.rvec.z;
    a->rvec.y = b->rvec.y * acpy.rvec.x + b->lvec.y * acpy.rvec.y + b->uvec.y * acpy.rvec.z;
    a->rvec.z = b->rvec.z * acpy.rvec.x + b->lvec.z * acpy.rvec.y + b->uvec.z * acpy.rvec.z;

    a->lvec.x = b->rvec.x * acpy.lvec.x + b->lvec.x * acpy.lvec.y + b->uvec.x * acpy.lvec.z;
    a->lvec.y = b->rvec.y * acpy.lvec.x + b->lvec.y * acpy.lvec.y + b->uvec.y * acpy.lvec.z;
    a->lvec.z = b->rvec.z * acpy.lvec.x + b->lvec.z * acpy.lvec.y + b->uvec.z * acpy.lvec.z;

    a->uvec.x = b->rvec.x * acpy.uvec.x + b->lvec.x * acpy.uvec.y + b->uvec.x * acpy.uvec.z;
    a->uvec.y = b->rvec.y * acpy.uvec.x + b->lvec.y * acpy.uvec.y + b->uvec.y * acpy.uvec.z;
    a->uvec.z = b->rvec.z * acpy.uvec.x + b->lvec.z * acpy.uvec.y + b->uvec.z * acpy.uvec.z;

    a->dvec.x = b->rvec.x * acpy.dvec.x + b->lvec.x * acpy.dvec.y + b->uvec.x * acpy.dvec.z + b->dvec.x;
    a->dvec.y = b->rvec.y * acpy.dvec.x + b->lvec.y * acpy.dvec.y + b->uvec.y * acpy.dvec.z + b->dvec.y;
    a->dvec.z = b->rvec.z * acpy.dvec.x + b->lvec.z * acpy.dvec.y + b->uvec.z * acpy.dvec.z + b->dvec.z;
}

void J3DAPI rdMatrix_PreRotate34(rdMatrix34* mat, const rdVector3* pyr)
{
    rdMatrix34 rotMat;
    rdMatrix_BuildRotate34(&rotMat, pyr);
    rdMatrix_PreMultiply34(mat, &rotMat);
}

void J3DAPI rdMatrix_PostRotate34(rdMatrix34* mat, const rdVector3* vecPYR)
{
    rdMatrix34 rotMat;
    rdMatrix_BuildRotate34(&rotMat, vecPYR);
    rdMatrix_PostMultiply34(mat, &rotMat);
}

void J3DAPI rdMatrix_PreTranslate34(rdMatrix34* mat, const rdVector3* vec)
{
    rdMatrix34 tmat;
    rdMatrix_BuildTranslate34(&tmat, vec);
    rdMatrix_PreMultiply34(mat, &tmat);
}

void J3DAPI rdMatrix_PostTranslate34(rdMatrix34* pMat, const rdVector3* pVec)
{
    rdVector_Add3Acc(&pMat->dvec, pVec);
}

void J3DAPI rdMatrix_PreScale34(rdMatrix34* mat, const rdVector3* vec)
{
    rdMatrix34 smat;
    rdMatrix_BuildScale34(&smat, vec);
    rdMatrix_PreMultiply34(mat, &smat);
}

void J3DAPI rdMatrix_PostScale34(rdMatrix34* mat, const rdVector3* vec)
{
    rdMatrix34 smat;
    rdMatrix_BuildScale34(&smat, vec);
    rdMatrix_PostMultiply34(mat, &smat);
}

void J3DAPI rdMatrix_TransformVector34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    RD_ASSERTREL(dest != src);
    dest->x = mat->rvec.x * src->x + mat->lvec.x * src->y + mat->uvec.x * src->z;
    dest->y = mat->rvec.y * src->x + mat->lvec.y * src->y + mat->uvec.y * src->z;
    dest->z = mat->rvec.z * src->x + mat->lvec.z * src->y + mat->uvec.z * src->z;
}

void J3DAPI rdMatrix_TransformVectorOrtho34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    RD_ASSERTREL(dest != src);
    dest->x = rdVector_Dot3(&mat->rvec, src);
    dest->y = rdVector_Dot3(&mat->lvec, src);
    dest->z = rdVector_Dot3(&mat->uvec, src);
}

void J3DAPI rdMatrix_TransformVector34Acc(rdVector3* dest, const rdMatrix34* mat)
{
    rdVector3 vec;
    vec.x = mat->rvec.x * dest->x + mat->lvec.x * dest->y + mat->uvec.x * dest->z;
    vec.y = mat->rvec.y * dest->x + mat->lvec.y * dest->y + mat->uvec.y * dest->z;
    vec.z = mat->rvec.z * dest->x + mat->lvec.z * dest->y + mat->uvec.z * dest->z;
    memcpy(dest, &vec, sizeof(rdVector3));
}

void J3DAPI rdMatrix_TransformPoint34(rdVector3* dest, const rdVector3* src, const rdMatrix34* mat)
{
    RD_ASSERTREL(dest != src);
    dest->x = mat->rvec.x * src->x + mat->lvec.x * src->y + mat->uvec.x * src->z + mat->dvec.x;
    dest->y = mat->rvec.y * src->x + mat->lvec.y * src->y + mat->uvec.y * src->z + mat->dvec.y;
    dest->z = mat->rvec.z * src->x + mat->lvec.z * src->y + mat->uvec.z * src->z + mat->dvec.z;
}

void J3DAPI rdMatrix_TransformPoint34Acc(rdVector3* dest, const rdMatrix34* mat)
{
    rdVector3 point = *dest;
    rdMatrix_TransformPoint34(dest, &point, mat);
    /*point.x = mat->rvec.x * dest->x + mat->lvec.x * dest->y + mat->uvec.x * dest->z + mat->dvec.x;
    point.y = mat->rvec.y * dest->x + mat->lvec.y * dest->y + mat->uvec.y * dest->z + mat->dvec.y;
    point.z = mat->rvec.z * dest->x + mat->lvec.z * dest->y + mat->uvec.z * dest->z + mat->dvec.z;*/
    //memcpy(dest, &point, sizeof(rdVector3));
}

void J3DAPI rdMatrix_TransformPointList34(const rdMatrix34* mat, const rdVector3* aSrc, rdVector3* aDest, size_t size)
{
    while ( size-- )
    {
        rdMatrix_TransformPoint34(aDest, aSrc, mat);
        ++aSrc;
        ++aDest;
    }
}