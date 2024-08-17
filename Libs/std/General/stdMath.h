#ifndef STD_STDMATH_H
#define STD_STDMATH_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

float J3DAPI stdMath_FlexPower(float base, int exponent);
float J3DAPI stdMath_NormalizeAngle(float angle);
float J3DAPI stdMath_NormalizeAngleAcute(float angle);
// Calculate sinus and cosinus of value x
void J3DAPI stdMath_SinCos(float angle, float* pSinOut, float* pCosOut);
float J3DAPI stdMath_Tan(float angle);
float J3DAPI stdMath_ArcSin1(float angle);
float J3DAPI stdMath_ArcSin3(float angle);
// Returns value of the arc tangent
// Name pulled from grim.
float J3DAPI stdMath_ArcTan4(float x, float y);
float J3DAPI stdMath_Dist2D1(float x, float y);
float J3DAPI stdMath_Dist3D1(float x, float y, float z);

// Helper hooking functions
void stdMath_InstallHooks(void);
void stdMath_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDMATH_H
