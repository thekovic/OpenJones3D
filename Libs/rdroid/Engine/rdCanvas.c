#include "rdCanvas.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdCanvas_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdCanvas_New);
    // J3D_HOOKFUNC(rdCanvas_NewEntry);
    // J3D_HOOKFUNC(rdCanvas_Free);
}

void rdCanvas_ResetGlobals(void)
{

}

// Creates new canvas.
// left, top, right, bottom are canvas bounding rectangle in screen size
rdCanvas* J3DAPI rdCanvas_New(int flags, tVBuffer* pVBuffer, int left, int top, int right, int bottom)
{
    return J3D_TRAMPOLINE_CALL(rdCanvas_New, flags, pVBuffer, left, top, right, bottom);
}

int J3DAPI rdCanvas_NewEntry(rdCanvas* pCanvas, int flags, tVBuffer* pVBuffer, int left, int top, int right, int bottom)
{
    return J3D_TRAMPOLINE_CALL(rdCanvas_NewEntry, pCanvas, flags, pVBuffer, left, top, right, bottom);
}

void J3DAPI rdCanvas_Free(rdCanvas* pCanvas)
{
    J3D_TRAMPOLINE_CALL(rdCanvas_Free, pCanvas);
}
