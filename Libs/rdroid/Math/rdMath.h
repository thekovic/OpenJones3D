#ifndef RDROID_RDMATH_H
#define RDROID_RDMATH_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>

#include <std/General/stdMath.h>
#include <std/types.h>

#include <stdbool.h>
#include <math.h>

J3D_EXTERN_C_START

void J3DAPI rdMath_CalcSurfaceNormal(rdVector3* pDestNormal, const rdVector3* pVert1, const rdVector3* pVert2, const rdVector3* pVert3); // Added

void J3DAPI rdMath_ClipVector3(rdVector3* vect, float minVal); // Added (renamed from rdMathClampVector)
void J3DAPI rdMath_ClampVector3(rdVector3* vect, float minVal, float maxVal); // Added 
void J3DAPI rdMath_ClampVector4(rdVector4* vect, float minVal, float maxVal); // Added 

float J3DAPI rdMath_DistancePointToPlane(const rdVector3* pPoint, const rdVector3* pPlaneNormal, const rdVector3* pPointOnPlane);
float J3DAPI rdMath_DeltaAngleNormalizedAbs(const rdVector3* pVectorX, const rdVector3* pVectorY); // Added
float J3DAPI rdMath_DeltaAngleNormalized(const rdVector3* pVectorX, const rdVector3* pVectorY, const rdVector3* pVectorZ);
bool J3DAPI rdMath_PointsCollinear(const rdVector3* p1, const rdVector3* p2, const rdVector3* p3); // Added

inline void J3DAPI rdMath_ClipVector3(rdVector3* vect, float minVal)
{
    vect->x = (fabsf(vect->x) >= minVal) ? vect->x : 0.0f;
    vect->y = (fabsf(vect->y) >= minVal) ? vect->y : 0.0f;
    vect->z = (fabsf(vect->z) >= minVal) ? vect->z : 0.0f;
}

inline void J3DAPI rdMath_ClampVector3(rdVector3* vect, float minVal, float maxVal)
{
    vect->x = STDMATH_CLAMP(vect->x, minVal, maxVal);
    vect->y = STDMATH_CLAMP(vect->y, minVal, maxVal);
    vect->z = STDMATH_CLAMP(vect->z, minVal, maxVal);
}

inline void J3DAPI rdMath_ClampVector4(rdVector4* vect, float minVal, float maxVal)
{
    vect->x = STDMATH_CLAMP(vect->x, minVal, maxVal);
    vect->y = STDMATH_CLAMP(vect->y, minVal, maxVal);
    vect->z = STDMATH_CLAMP(vect->z, minVal, maxVal);
    vect->w = STDMATH_CLAMP(vect->w, minVal, maxVal);
}

// Helper hooking functions
void rdMath_InstallHooks(void);
void rdMath_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDMATH_H
