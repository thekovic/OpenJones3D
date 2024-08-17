#include "rdWallpaper.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdWallpaper_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdWallpaper_New);
    // J3D_HOOKFUNC(rdWallpaper_Free);
    // J3D_HOOKFUNC(rdWallpaper_Draw);
    // J3D_HOOKFUNC(rdWallpaper_NewWallLine);
    // J3D_HOOKFUNC(rdWallpaper_FreeWallLine);
    // J3D_HOOKFUNC(rdWallpaper_DrawWallLine);
}

void rdWallpaper_ResetGlobals(void)
{

}

rdWallpaper* J3DAPI rdWallpaper_New(const char* pMatFilePath)
{
    return J3D_TRAMPOLINE_CALL(rdWallpaper_New, pMatFilePath);
}

void J3DAPI rdWallpaper_Free(rdWallpaper* pWallpaper)
{
    J3D_TRAMPOLINE_CALL(rdWallpaper_Free, pWallpaper);
}

void J3DAPI rdWallpaper_Draw(const rdWallpaper* pWallpaper)
{
    J3D_TRAMPOLINE_CALL(rdWallpaper_Draw, pWallpaper);
}

rdWallLine* J3DAPI rdWallpaper_NewWallLine(float startX, float startY, float endX, float endY, const rdVector4* pColor)
{
    return J3D_TRAMPOLINE_CALL(rdWallpaper_NewWallLine, startX, startY, endX, endY, pColor);
}

void J3DAPI rdWallpaper_FreeWallLine(rdWallLine* pWallLine)
{
    J3D_TRAMPOLINE_CALL(rdWallpaper_FreeWallLine, pWallLine);
}

void J3DAPI rdWallpaper_DrawWallLine(const rdWallLine* pLine, float progress)
{
    J3D_TRAMPOLINE_CALL(rdWallpaper_DrawWallLine, pLine, progress);
}
