#ifndef STD_STDMATH_H
#define STD_STDMATH_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

#define _USE_MATH_DEFINES
#include <math.h>

J3D_EXTERN_C_START

// Clamp value between min and max
#define STDMATH_CLAMP(val, minv, maxv) (((val) < (minv)) ? (minv) : ((val) > (maxv)) ? (maxv) : (val))

// Convert radians to degrees
#define STDMATH_TODEGREES(rad)  ((rad) * (180.0 / M_PI))
#define STDMATH_TODEGREESF(rad) (float)STDMATH_TODEGREES(rad)

// Convert degrees to radians
#define STDMATH_RADIANS(deg)  ((deg) * (M_PI / 180.0))
#define STDMATH_RADIANSF(deg) (float)STDMATH_RADIANS(deg)

float J3DAPI stdMath_FlexPower(float base, int exponent);
inline float stdMath_ClipNearZero(float val); // Added

float J3DAPI stdMath_NormalizeAngle(float angle);
float J3DAPI stdMath_NormalizeAngleAcute(float angle);

// Calculate sinus and cousins of value angle
void J3DAPI stdMath_SinCos(float angle, float* pSinOut, float* pCosOut);
float J3DAPI stdMath_Tan(float angle);
float J3DAPI stdMath_ArcSin1(float angle);
float J3DAPI stdMath_ArcSin2(float value); // Added
float J3DAPI stdMath_ArcSin3(float angle);

// Returns value of the arc tangent
float J3DAPI stdMath_ArcTan4(float x, float y);
float J3DAPI stdMath_Dist2D1(float x, float y);
float J3DAPI stdMath_Dist3D1(float x, float y, float z);

inline float stdMath_ClipNearZero(float val)
{
    if ( fabsf(val) <= 0.00001f )
    {
        return 0.0f;
    }
    return val;
}

// Helper hooking functions
void stdMath_InstallHooks(void);
void stdMath_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDMATH_H
