#include "rdPrimit3.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdPrimit3_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdPrimit3_DrawClippedCircle);
    // J3D_HOOKFUNC(rdPrimit3_ClipFace);
}

void rdPrimit3_ResetGlobals(void)
{

}

void J3DAPI rdPrimit3_DrawClippedCircle(const rdVector3* pPos, float radius, float step, uint32_t color, unsigned int flags)
{
    J3D_TRAMPOLINE_CALL(rdPrimit3_DrawClippedCircle, pPos, radius, step, color, flags);
}

void J3DAPI rdPrimit3_ClipFace(const rdClipFrustum* pFrustrum, rdGeometryMode geoMode, rdLightMode lightMode, const rdPrimit3* pSrc, rdPrimit3* pDest, const rdVector2* pTexVertOffset)
{
    J3D_TRAMPOLINE_CALL(rdPrimit3_ClipFace, pFrustrum, geoMode, lightMode, pSrc, pDest, pTexVertOffset);
}
