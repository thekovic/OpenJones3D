#ifndef RDROID_RDCANVAS_H
#define RDROID_RDCANVAS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

// Creates new canvas.
// left, top, right, bottom are canvas bounding rectangle in screen size
rdCanvas* J3DAPI rdCanvas_New(int flags, tVBuffer* pVBuffer, int left, int top, int right, int bottom);
int J3DAPI rdCanvas_NewEntry(rdCanvas* pCanvas, int flags, tVBuffer* pVBuffer, int left, int top, int right, int bottom);
void J3DAPI rdCanvas_Free(rdCanvas* pCanvas);

// Helper hooking functions
void rdCanvas_InstallHooks(void);
void rdCanvas_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDCANVAS_H
