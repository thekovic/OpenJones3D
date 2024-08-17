#include "rdMath.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdMath_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdMath_DistancePointToPlane);
    // J3D_HOOKFUNC(rdMath_DeltaAngleNormalized);
}

void rdMath_ResetGlobals(void)
{

}

float J3DAPI rdMath_DistancePointToPlane(const rdVector3* point, const rdVector3* normal, const rdVector3* plane)
{
    return J3D_TRAMPOLINE_CALL(rdMath_DistancePointToPlane, point, normal, plane);
}

float J3DAPI rdMath_DeltaAngleNormalized(const rdVector3* pVectorX, const rdVector3* pVectorY, const rdVector3* pVectorZ)
{
    return J3D_TRAMPOLINE_CALL(rdMath_DeltaAngleNormalized, pVectorX, pVectorY, pVectorZ);
}
