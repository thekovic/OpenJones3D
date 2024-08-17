#ifndef RDROID_RDMATH_H
#define RDROID_RDMATH_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

float J3DAPI rdMath_DistancePointToPlane(const rdVector3* point, const rdVector3* normal, const rdVector3* plane);
float J3DAPI rdMath_DeltaAngleNormalized(const rdVector3* pVectorX, const rdVector3* pVectorY, const rdVector3* pVectorZ);

// Helper hooking functions
void rdMath_InstallHooks(void);
void rdMath_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDMATH_H
