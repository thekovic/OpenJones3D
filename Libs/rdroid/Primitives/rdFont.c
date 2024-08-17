#include "rdFont.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdFont_lightingMode J3D_DECL_FAR_VAR(rdFont_lightingMode, rdLightMode)
#define rdFont_aFontColors J3D_DECL_FAR_ARRAYVAR(rdFont_aFontColors, rdVector4(*)[4])
#define rdFont_bStartup J3D_DECL_FAR_VAR(rdFont_bStartup, int)
#define rdFont_bOpen J3D_DECL_FAR_VAR(rdFont_bOpen, int)
#define rdFont_bFontColorSet J3D_DECL_FAR_VAR(rdFont_bFontColorSet, int)

void rdFont_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdFont_Load);
    // J3D_HOOKFUNC(rdFont_LoadEntry);
    // J3D_HOOKFUNC(rdFont_LoadMaterial);
    // J3D_HOOKFUNC(rdFont_Free);
    // J3D_HOOKFUNC(rdFont_SetFontColor);
    // J3D_HOOKFUNC(rdFont_GetTextEnd);
    // J3D_HOOKFUNC(rdFont_GetTextWidth);
    // J3D_HOOKFUNC(rdFont_DrawText);
    // J3D_HOOKFUNC(rdFont_DrawChar);
    // J3D_HOOKFUNC(rdFont_DrawText2);
    // J3D_HOOKFUNC(rdFont_Startup);
    // J3D_HOOKFUNC(rdFont_Shutdown);
    // J3D_HOOKFUNC(rdFont_Open);
    // J3D_HOOKFUNC(rdFont_Close);
}

void rdFont_ResetGlobals(void)
{
    memset(&rdFont_lightingMode, 0, sizeof(rdFont_lightingMode));
    memset(&rdFont_aFontColors, 0, sizeof(rdFont_aFontColors));
    memset(&rdFont_bStartup, 0, sizeof(rdFont_bStartup));
    memset(&rdFont_bOpen, 0, sizeof(rdFont_bOpen));
    memset(&rdFont_bFontColorSet, 0, sizeof(rdFont_bFontColorSet));
}

rdFont* J3DAPI rdFont_Load(char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(rdFont_Load, pFilename);
}

int J3DAPI rdFont_LoadEntry(const char* pFilename, rdFont* pFont)
{
    return J3D_TRAMPOLINE_CALL(rdFont_LoadEntry, pFilename, pFont);
}

int J3DAPI rdFont_LoadMaterial(const char* pFilename, rdFont* pFont)
{
    return J3D_TRAMPOLINE_CALL(rdFont_LoadMaterial, pFilename, pFont);
}

void J3DAPI rdFont_Free(rdFont* pFont)
{
    J3D_TRAMPOLINE_CALL(rdFont_Free, pFont);
}

void J3DAPI rdFont_SetFontColor(rdVector4* apColor)
{
    J3D_TRAMPOLINE_CALL(rdFont_SetFontColor, apColor);
}

const char* J3DAPI rdFont_GetTextEnd(const char* pText, rdFont* pFont, float maxTextWidthScalar)
{
    return J3D_TRAMPOLINE_CALL(rdFont_GetTextEnd, pText, pFont, maxTextWidthScalar);
}

int J3DAPI rdFont_GetTextWidth(const char* pText, rdFont* pFont)
{
    return J3D_TRAMPOLINE_CALL(rdFont_GetTextWidth, pText, pFont);
}

// local variable allocation has failed, the output may be wrong!
void J3DAPI rdFont_DrawText(const char* pText, float x, float y, float z, const rdFont* pFont, int flags)
{
    J3D_TRAMPOLINE_CALL(rdFont_DrawText, pText, x, y, z, pFont, flags);
}

void J3DAPI rdFont_DrawChar(uint8_t chr, float x, float y, float z, const rdFont* pFont)
{
    J3D_TRAMPOLINE_CALL(rdFont_DrawChar, chr, x, y, z, pFont);
}

void J3DAPI rdFont_DrawText2(const char* pText, float x, float y, float z, const rdFont* pFont, int flags)
{
    J3D_TRAMPOLINE_CALL(rdFont_DrawText2, pText, x, y, z, pFont, flags);
}

void J3DAPI rdFont_Startup()
{
    J3D_TRAMPOLINE_CALL(rdFont_Startup);
}

void rdFont_Shutdown()
{
    J3D_TRAMPOLINE_CALL(rdFont_Shutdown);
}

int J3DAPI rdFont_Open()
{
    return J3D_TRAMPOLINE_CALL(rdFont_Open);
}

void J3DAPI rdFont_Close()
{
    J3D_TRAMPOLINE_CALL(rdFont_Close);
}
