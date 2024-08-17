#include "rdPrimit2.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdPrimit2_aD3DVertices J3D_DECL_FAR_ARRAYVAR(rdPrimit2_aD3DVertices, D3DTLVERTEX(*)[2])

void rdPrimit2_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdPrimit2_DrawClippedLine);
    // J3D_HOOKFUNC(rdPrimit2_Reset);
    // J3D_HOOKFUNC(rdPrimit2_DrawClippedLine2);
    // J3D_HOOKFUNC(rdPrimit2_DrawClippedCircle);
    // J3D_HOOKFUNC(rdPrimit2_DrawClippedCircle2);
}

void rdPrimit2_ResetGlobals(void)
{
    memset(&rdPrimit2_aD3DVertices, 0, sizeof(rdPrimit2_aD3DVertices));
}

int J3DAPI rdPrimit2_DrawClippedLine(rdCanvas* pCanvas, int x1, int y1, int x2, int y2, int16_t color, unsigned int flags)
{
    return J3D_TRAMPOLINE_CALL(rdPrimit2_DrawClippedLine, pCanvas, x1, y1, x2, y2, color, flags);
}

void rdPrimit2_Reset(void)
{
    J3D_TRAMPOLINE_CALL(rdPrimit2_Reset);
}

int J3DAPI rdPrimit2_DrawClippedLine2(float x1, float y1, float x2, float y2, uint32_t color)
{
    return J3D_TRAMPOLINE_CALL(rdPrimit2_DrawClippedLine2, x1, y1, x2, y2, color);
}

void J3DAPI rdPrimit2_DrawClippedCircle(rdCanvas* pCanvas, int x, int y, float radius, float step, int16_t color, unsigned int flags)
{
    J3D_TRAMPOLINE_CALL(rdPrimit2_DrawClippedCircle, pCanvas, x, y, radius, step, color, flags);
}

void J3DAPI rdPrimit2_DrawClippedCircle2(float centerX, float centerY, float radius, float degrees, uint32_t color)
{
    J3D_TRAMPOLINE_CALL(rdPrimit2_DrawClippedCircle2, centerX, centerY, radius, degrees, color);
}
