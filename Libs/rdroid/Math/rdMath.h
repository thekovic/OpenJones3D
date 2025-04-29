#ifndef RDROID_RDMATH_H
#define RDROID_RDMATH_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>

#include <std/General/stdMath.h>
#include <std/types.h>

#include <stdbool.h>
#include <math.h>

#include "rdVector.h"

J3D_EXTERN_C_START

void J3DAPI rdMath_CalcSurfaceNormal(rdVector3* pDestNormal, const rdVector3* pVert1, const rdVector3* pVert2, const rdVector3* pVert3); // Added

void J3DAPI rdMath_ClipVector3(rdVector3* out, const rdVector3* vect, float minVal); // Added
void J3DAPI rdMath_ClipVector3Acc(rdVector3* vect, float minVal); // Added (renamed from rdMathClampVector)

void J3DAPI rdMath_ClampVector3(rdVector3* out, const rdVector3* vect, float minVal, float maxVal); // Added
void J3DAPI rdMath_ClampVector3Acc(rdVector3* vect, float minVal, float maxVal); // Added

void J3DAPI rdMath_ClampVector4Acc(rdVector4* vect, float minVal, float maxVal); // Added

float J3DAPI rdMath_DistancePointToPlane(const rdVector3* pPoint, const rdVector3* pPlaneNormal, const rdVector3* pPointOnPlane);
float J3DAPI rdMath_DeltaAngleNormalizedAbs(const rdVector3* pVectorX, const rdVector3* pVectorY); // Added
float J3DAPI rdMath_DeltaAngleNormalized(const rdVector3* pVectorX, const rdVector3* pVectorY, const rdVector3* pVectorZ);
bool J3DAPI rdMath_PointsCollinear(const rdVector3* p1, const rdVector3* p2, const rdVector3* p3); // Added

inline void J3DAPI rdMath_ClipVector3(rdVector3* out, const rdVector3* vect, float minVal)
{
    out->x = (fabsf(vect->x) >= minVal) ? vect->x : 0.0f;
    out->y = (fabsf(vect->y) >= minVal) ? vect->y : 0.0f;
    out->z = (fabsf(vect->z) >= minVal) ? vect->z : 0.0f;
}

inline void J3DAPI rdMath_ClipVector3Acc(rdVector3* vect, float minVal)
{
    rdMath_ClipVector3(vect, vect, minVal);
}

inline void J3DAPI rdMath_ClampVector3(rdVector3* out, const rdVector3* vect, float minVal, float maxVal)
{
    out->x = STDMATH_CLAMP(vect->x, minVal, maxVal);
    out->y = STDMATH_CLAMP(vect->y, minVal, maxVal);
    out->z = STDMATH_CLAMP(vect->z, minVal, maxVal);
}

inline void J3DAPI rdMath_ClampVector3Acc(rdVector3* vect, float minVal, float maxVal)
{
    rdMath_ClampVector3(vect, vect, minVal, maxVal);
}

inline void J3DAPI rdMath_ClampVector4(rdVector4* out, const rdVector4* vect, float minVal, float maxVal)
{
    out->x = STDMATH_CLAMP(vect->x, minVal, maxVal);
    out->y = STDMATH_CLAMP(vect->y, minVal, maxVal);
    out->z = STDMATH_CLAMP(vect->z, minVal, maxVal);
    out->w = STDMATH_CLAMP(vect->w, minVal, maxVal);
}

inline void J3DAPI rdMath_ClampVector4Acc(rdVector4* vect, float minVal, float maxVal)
{
    rdMath_ClampVector4(vect, vect, minVal, maxVal);
}

inline float J3DAPI rdMath_DistancePointToPlane(const rdVector3* pPoint, const rdVector3* pPlaneNormal, const rdVector3* pPointOnPlane)
{
    return (pPoint->x - pPointOnPlane->x) * pPlaneNormal->x
        + (pPoint->y - pPointOnPlane->y) * pPlaneNormal->y
        + (pPoint->z - pPointOnPlane->z) * pPlaneNormal->z;
}

inline float J3DAPI rdMath_DeltaAngleNormalizedAbs(const rdVector3* pVectorX, const rdVector3* pVectorY)
{
    float dot  = rdVector_Dot3(pVectorX, pVectorY);
    if ( dot == 1.0 ) {
        return 0.0f;
    }

    return 90.0f - stdMath_ArcSin1(dot);
}

// Helper hooking functions
void rdMath_InstallHooks(void);
void rdMath_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDMATH_H
