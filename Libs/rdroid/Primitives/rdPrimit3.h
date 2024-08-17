#ifndef RDROID_RDPRIMIT3_H
#define RDROID_RDPRIMIT3_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI rdPrimit3_DrawClippedCircle(const rdVector3* pPos, float radius, float step, uint32_t color, unsigned int flags);
void J3DAPI rdPrimit3_ClipFace(const rdClipFrustum* pFrustrum, rdGeometryMode geoMode, rdLightMode lightMode, const rdPrimit3* pSrc, rdPrimit3* pDest, const rdVector2* pTexVertOffset);

// Helper hooking functions
void rdPrimit3_InstallHooks(void);
void rdPrimit3_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDPRIMIT3_H
