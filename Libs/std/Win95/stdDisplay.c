#include "stdDisplay.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdDisplay_aDDStatusTbl J3D_DECL_FAR_ARRAYVAR(stdDisplay_aDDStatusTbl, const DXStatus(*)[111])
#define stdDisplay_coopLevelFlags J3D_DECL_FAR_VAR(stdDisplay_coopLevelFlags, int)
#define stdDisplay_hFont J3D_DECL_FAR_VAR(stdDisplay_hFont, HFONT)
#define stdDisplay_curDevice J3D_DECL_FAR_VAR(stdDisplay_curDevice, size_t)
#define stdDisplay_primaryVideoMode J3D_DECL_FAR_VAR(stdDisplay_primaryVideoMode, StdVideoMode)
#define stdDisplay_dword_5D73D8 J3D_DECL_FAR_VAR(stdDisplay_dword_5D73D8, int)
#define stdDisplay_dword_5D73DC J3D_DECL_FAR_VAR(stdDisplay_dword_5D73DC, int)
#define stdDisplay_backbufWidth J3D_DECL_FAR_VAR(stdDisplay_backbufWidth, int)
#define stdDisplay_backbufHeight J3D_DECL_FAR_VAR(stdDisplay_backbufHeight, int)
#define stdDisplay_zBuffer J3D_DECL_FAR_VAR(stdDisplay_zBuffer, tVSurface)
#define stdDisplay_aVideoModes J3D_DECL_FAR_ARRAYVAR(stdDisplay_aVideoModes, StdVideoMode(*)[64])
#define stdDisplay_aDisplayDevices J3D_DECL_FAR_ARRAYVAR(stdDisplay_aDisplayDevices, StdDisplayDevice(*)[16])
#define stdDisplay_bStartup J3D_DECL_FAR_VAR(stdDisplay_bStartup, int)
#define stdDisplay_bOpen J3D_DECL_FAR_VAR(stdDisplay_bOpen, int)
#define stdDisplay_bModeSet J3D_DECL_FAR_VAR(stdDisplay_bModeSet, int)
#define stdDisplay_numDevices J3D_DECL_FAR_VAR(stdDisplay_numDevices, size_t)
#define stdDisplay_pCurDevice J3D_DECL_FAR_VAR(stdDisplay_pCurDevice, StdDisplayDevice*)
#define stdDisplay_numVideoModes J3D_DECL_FAR_VAR(stdDisplay_numVideoModes, size_t)
#define stdDisplay_pCurVideoMode J3D_DECL_FAR_VAR(stdDisplay_pCurVideoMode, StdVideoMode*)
#define stdDisplay_lpDD J3D_DECL_FAR_VAR(stdDisplay_lpDD, LPDIRECTDRAW4)
#define stdDisplay_bFullscreen J3D_DECL_FAR_VAR(stdDisplay_bFullscreen, int)

void stdDisplay_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdDisplay_Startup);
    // J3D_HOOKFUNC(stdDisplay_Shutdown);
    // J3D_HOOKFUNC(stdDisplay_Open);
    // J3D_HOOKFUNC(stdDisplay_Close);
    // J3D_HOOKFUNC(stdDisplay_SetMode);
    // J3D_HOOKFUNC(stdDisplay_ClearMode);
    // J3D_HOOKFUNC(stdDisplay_GetNumDevices);
    // J3D_HOOKFUNC(stdDisplay_GetDevice);
    // J3D_HOOKFUNC(stdDisplay_GetCurrentDevice);
    // J3D_HOOKFUNC(stdDisplay_Refresh);
    // J3D_HOOKFUNC(stdDisplay_VBufferNew);
    // J3D_HOOKFUNC(stdDisplay_VBufferFree);
    // J3D_HOOKFUNC(stdDisplay_VBufferLock);
    // J3D_HOOKFUNC(stdDisplay_VBufferUnlock);
    // J3D_HOOKFUNC(stdDisplay_VBufferFill);
    // J3D_HOOKFUNC(stdDisplay_VBufferConvertColorFormat);
    // J3D_HOOKFUNC(stdDisplay_VideoModeCompare);
    // J3D_HOOKFUNC(stdDisplay_GetTextureMemory);
    // J3D_HOOKFUNC(stdDisplay_GetTotalMemory);
    // J3D_HOOKFUNC(stdDisplay_DDGetStatus);
    // J3D_HOOKFUNC(stdDisplay_CreateZBuffer);
    // J3D_HOOKFUNC(stdDisplay_InitDirectDraw);
    // J3D_HOOKFUNC(stdDisplay_ReleaseDirectDraw);
    // J3D_HOOKFUNC(stdDisplay_DDEnumCallback);
    // J3D_HOOKFUNC(stdDisplay_EnumVideoModesCallback);
    // J3D_HOOKFUNC(stdDisplay_SetAspectRatio);
    // J3D_HOOKFUNC(stdDisplay_GetDirectDraw);
    // J3D_HOOKFUNC(stdDisplay_SetWindowMode);
    // J3D_HOOKFUNC(stdDisplay_SetFullscreenMode);
    // J3D_HOOKFUNC(stdDisplay_ReleaseBuffers);
    // J3D_HOOKFUNC(stdDisplay_LockSurface);
    // J3D_HOOKFUNC(stdDisplay_UnlockSurface);
    // J3D_HOOKFUNC(stdDisplay_Update);
    // J3D_HOOKFUNC(stdDisplay_ColorFillSurface);
    // J3D_HOOKFUNC(stdDisplay_BackBufferFill);
    // J3D_HOOKFUNC(stdDisplay_SaveScreen);
    // J3D_HOOKFUNC(stdDisplay_SetDefaultResolution);
    // J3D_HOOKFUNC(stdDisplay_GetBackBufferSize);
    // J3D_HOOKFUNC(stdDisplay_GetNumVideoModes);
    // J3D_HOOKFUNC(stdDisplay_GetVideoMode);
    // J3D_HOOKFUNC(stdDisplay_GetCurrentVideoMode);
    // J3D_HOOKFUNC(stdDisplay_GetFrontBufferDC);
    // J3D_HOOKFUNC(stdDisplay_ReleaseFrontBufferDC);
    // J3D_HOOKFUNC(stdDisplay_GetBackBufferDC);
    // J3D_HOOKFUNC(stdDisplay_ReleaseBackBufferDC);
    // J3D_HOOKFUNC(stdDisplay_FlipToGDISurface);
    // J3D_HOOKFUNC(stdDisplay_CanRenderWindowed);
    // J3D_HOOKFUNC(stdDisplay_SetBufferClipper);
    // J3D_HOOKFUNC(stdDisplay_RemoveBufferClipper);
    // J3D_HOOKFUNC(stdDisplay_IsFullscreen);
    // J3D_HOOKFUNC(stdDisplay_LockBackBuffer);
    // J3D_HOOKFUNC(stdDisplay_UnlockBackBuffer);
    // J3D_HOOKFUNC(stdDisplay_EncodeRGB565);
}

void stdDisplay_ResetGlobals(void)
{
    const DXStatus stdDisplay_aDDStatusTbl_tmp[111] = {
      { 0, "DD_OK" },
      { -2005532667, "DDERR_ALREADYINITIALIZED" },
      { -2005532662, "DDERR_CANNOTATTACHSURFACE" },
      { -2005532652, "DDERR_CANNOTDETACHSURFACE" },
      { -2005532632, "DDERR_CURRENTLYNOTAVAIL" },
      { -2005532617, "DDERR_EXCEPTION" },
      { -2147467259, "DDERR_GENERIC" },
      { -2005532582, "DDERR_HEIGHTALIGN" },
      { -2005532577, "DDERR_INCOMPATIBLEPRIMARY" },
      { -2005532572, "DDERR_INVALIDCAPS" },
      { -2005532562, "DDERR_INVALIDCLIPLIST" },
      { -2005532552, "DDERR_INVALIDMODE" },
      { -2005532542, "DDERR_INVALIDOBJECT" },
      { -2147024809, "DDERR_INVALIDPARAMS" },
      { -2005532527, "DDERR_INVALIDPIXELFORMAT" },
      { -2005532522, "DDERR_INVALIDRECT" },
      { -2005532512, "DDERR_LOCKEDSURFACES" },
      { -2005532502, "DDERR_NO3D" },
      { -2005532492, "DDERR_NOALPHAHW" },
      { -2005532467, "DDERR_NOCLIPLIST" },
      { -2005532462, "DDERR_NOCOLORCONVHW" },
      { -2005532460, "DDERR_NOCOOPERATIVELEVELSET" },
      { -2005532457, "DDERR_NOCOLORKEY" },
      { -2005532452, "DDERR_NOCOLORKEYHW" },
      { -2005532450, "DDERR_NODIRECTDRAWSUPPORT" },
      { -2005532447, "DDERR_NOEXCLUSIVEMODE" },
      { -2005532442, "DDERR_NOFLIPHW" },
      { -2005532432, "DDERR_NOGDI" },
      { -2005532422, "DDERR_NOMIRRORHW" },
      { -2005532417, "DDERR_NOTFOUND" },
      { -2005532412, "DDERR_NOOVERLAYHW" },
      { -2005532402, "DDERR_OVERLAPPINGRECTS" },
      { -2005532392, "DDERR_NORASTEROPHW" },
      { -2005532382, "DDERR_NOROTATIONHW" },
      { -2005532362, "DDERR_NOSTRETCHHW" },
      { -2005532356, "DDERR_NOT4BITCOLOR" },
      { -2005532355, "DDERR_NOT4BITCOLORINDEX" },
      { -2005532352, "DDERR_NOT8BITCOLOR" },
      { -2005532342, "DDERR_NOTEXTUREHW" },
      { -2005532337, "DDERR_NOVSYNCHW" },
      { -2005532332, "DDERR_NOZBUFFERHW" },
      { -2005532322, "DDERR_NOZOVERLAYHW" },
      { -2005532312, "DDERR_OUTOFCAPS" },
      { -2147024882, "DDERR_OUTOFMEMORY" },
      { -2005532292, "DDERR_OUTOFVIDEOMEMORY" },
      { -2005532290, "DDERR_OVERLAYCANTCLIP" },
      { -2005532288, "DDERR_OVERLAYCOLORKEYONLYONEACTIVE" },
      { -2005532285, "DDERR_PALETTEBUSY" },
      { -2005532272, "DDERR_COLORKEYNOTSET" },
      { -2005532262, "DDERR_SURFACEALREADYATTACHED" },
      { -2005532252, "DDERR_SURFACEALREADYDEPENDENT" },
      { -2005532242, "DDERR_SURFACEBUSY" },
      { -2005532237, "DDERR_CANTLOCKSURFACE" },
      { -2005532232, "DDERR_SURFACEISOBSCURED" },
      { -2005532222, "DDERR_SURFACELOST" },
      { -2005532212, "DDERR_SURFACENOTATTACHED" },
      { -2005532202, "DDERR_TOOBIGHEIGHT" },
      { -2005532192, "DDERR_TOOBIGSIZE" },
      { -2005532182, "DDERR_TOOBIGWIDTH" },
      { -2147467263, "DDERR_UNSUPPORTED" },
      { -2005532162, "DDERR_UNSUPPORTEDFORMAT" },
      { -2005532152, "DDERR_UNSUPPORTEDMASK" },
      { -2005532151, "DDERR_INVALIDSTREAM" },
      { -2005532135, "DDERR_VERTICALBLANKINPROGRESS" },
      { -2005532132, "DDERR_WASSTILLDRAWING" },
      { -2005532112, "DDERR_XALIGN" },
      { -2005532111, "DDERR_INVALIDDIRECTDRAWGUID" },
      { -2005532110, "DDERR_DIRECTDRAWALREADYCREATED" },
      { -2005532109, "DDERR_NODIRECTDRAWHW" },
      { -2005532108, "DDERR_PRIMARYSURFACEALREADYEXISTS" },
      { -2005532107, "DDERR_NOEMULATION" },
      { -2005532106, "DDERR_REGIONTOOSMALL" },
      { -2005532105, "DDERR_CLIPPERISUSINGHWND" },
      { -2005532104, "DDERR_NOCLIPPERATTACHED" },
      { -2005532103, "DDERR_NOHWND" },
      { -2005532102, "DDERR_HWNDSUBCLASSED" },
      { -2005532101, "DDERR_HWNDALREADYSET" },
      { -2005532100, "DDERR_NOPALETTEATTACHED" },
      { -2005532099, "DDERR_NOPALETTEHW" },
      { -2005532098, "DDERR_BLTFASTCANTCLIP" },
      { -2005532097, "DDERR_NOBLTHW" },
      { -2005532096, "DDERR_NODDROPSHW" },
      { -2005532095, "DDERR_OVERLAYNOTVISIBLE" },
      { -2005532094, "DDERR_NOOVERLAYDEST" },
      { -2005532093, "DDERR_INVALIDPOSITION" },
      { -2005532092, "DDERR_NOTAOVERLAYSURFACE" },
      { -2005532091, "DDERR_EXCLUSIVEMODEALREADYSET" },
      { -2005532090, "DDERR_NOTFLIPPABLE" },
      { -2005532089, "DDERR_CANTDUPLICATE" },
      { -2005532088, "DDERR_NOTLOCKED" },
      { -2005532087, "DDERR_CANTCREATEDC" },
      { -2005532086, "DDERR_NODC" },
      { -2005532085, "DDERR_WRONGMODE" },
      { -2005532084, "DDERR_IMPLICITLYCREATED" },
      { -2005532083, "DDERR_NOTPALETTIZED" },
      { -2005532082, "DDERR_UNSUPPORTEDMODE" },
      { -2005532081, "DDERR_NOMIPMAPHW" },
      { -2005532080, "DDERR_INVALIDSURFACETYPE" },
      { -2005532072, "DDERR_NOOPTIMIZEHW" },
      { -2005532071, "DDERR_NOTLOADED" },
      { -2005532070, "DDERR_NOFOCUSWINDOW" },
      { -2005532052, "DDERR_DCALREADYCREATED" },
      { -2005532042, "DDERR_NONONLOCALVIDMEM" },
      { -2005532032, "DDERR_CANTPAGELOCK" },
      { -2005532012, "DDERR_CANTPAGEUNLOCK" },
      { -2005531992, "DDERR_NOTPAGELOCKED" },
      { -2005531982, "DDERR_MOREDATA" },
      { -2005531981, "DDERR_EXPIRED" },
      { -2005531977, "DDERR_VIDEONOTACTIVE" },
      { -2005531973, "DDERR_DEVICEDOESNTOWNSURFACE" },
      { -2147221008, "DDERR_NOTINITIALIZED" }
    };
    memcpy((DXStatus *)&stdDisplay_aDDStatusTbl, &stdDisplay_aDDStatusTbl_tmp, sizeof(stdDisplay_aDDStatusTbl));
    
    int stdDisplay_coopLevelFlags_tmp = 8;
    memcpy(&stdDisplay_coopLevelFlags, &stdDisplay_coopLevelFlags_tmp, sizeof(stdDisplay_coopLevelFlags));
    
    memset(&stdDisplay_hFont, 0, sizeof(stdDisplay_hFont));
    memset(&stdDisplay_g_frontBuffer, 0, sizeof(stdDisplay_g_frontBuffer));
    memset(&stdDisplay_curDevice, 0, sizeof(stdDisplay_curDevice));
    memset(&stdDisplay_primaryVideoMode, 0, sizeof(stdDisplay_primaryVideoMode));
    memset(&stdDisplay_dword_5D73D8, 0, sizeof(stdDisplay_dword_5D73D8));
    memset(&stdDisplay_dword_5D73DC, 0, sizeof(stdDisplay_dword_5D73DC));
    memset(&stdDisplay_backbufWidth, 0, sizeof(stdDisplay_backbufWidth));
    memset(&stdDisplay_backbufHeight, 0, sizeof(stdDisplay_backbufHeight));
    memset(&stdDisplay_zBuffer, 0, sizeof(stdDisplay_zBuffer));
    memset(&stdDisplay_aVideoModes, 0, sizeof(stdDisplay_aVideoModes));
    memset(&stdDisplay_aDisplayDevices, 0, sizeof(stdDisplay_aDisplayDevices));
    memset(&stdDisplay_bStartup, 0, sizeof(stdDisplay_bStartup));
    memset(&stdDisplay_bOpen, 0, sizeof(stdDisplay_bOpen));
    memset(&stdDisplay_bModeSet, 0, sizeof(stdDisplay_bModeSet));
    memset(&stdDisplay_numDevices, 0, sizeof(stdDisplay_numDevices));
    memset(&stdDisplay_pCurDevice, 0, sizeof(stdDisplay_pCurDevice));
    memset(&stdDisplay_numVideoModes, 0, sizeof(stdDisplay_numVideoModes));
    memset(&stdDisplay_pCurVideoMode, 0, sizeof(stdDisplay_pCurVideoMode));
    memset(&stdDisplay_lpDD, 0, sizeof(stdDisplay_lpDD));
    memset(&stdDisplay_bFullscreen, 0, sizeof(stdDisplay_bFullscreen));
    memset(&stdDisplay_g_backBuffer, 0, sizeof(stdDisplay_g_backBuffer));
}

int stdDisplay_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_Startup);
}

void stdDisplay_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_Shutdown);
}

int J3DAPI stdDisplay_Open(size_t deviceNum)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_Open, deviceNum);
}

void stdDisplay_Close(void)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_Close);
}

int J3DAPI stdDisplay_SetMode(size_t modeNum, int bFullscreen, size_t numBackBuffers)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_SetMode, modeNum, bFullscreen, numBackBuffers);
}

void stdDisplay_ClearMode(void)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_ClearMode);
}

size_t stdDisplay_GetNumDevices(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetNumDevices);
}

int J3DAPI stdDisplay_GetDevice(size_t deviceNum, StdDisplayDevice* pDest)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetDevice, deviceNum, pDest);
}

int J3DAPI stdDisplay_GetCurrentDevice(StdDisplayDevice* pDevice)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetCurrentDevice, pDevice);
}

void J3DAPI stdDisplay_Refresh(int bReload)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_Refresh, bReload);
}

tVBuffer* J3DAPI stdDisplay_VBufferNew(const tRasterInfo* pRasterInfo, int bUseVSurface, int bUseVideoMemory)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VBufferNew, pRasterInfo, bUseVSurface, bUseVideoMemory);
}

void J3DAPI stdDisplay_VBufferFree(tVBuffer* pVBuffer)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_VBufferFree, pVBuffer);
}

int J3DAPI stdDisplay_VBufferLock(tVBuffer* pVBuffer)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VBufferLock, pVBuffer);
}

int J3DAPI stdDisplay_VBufferUnlock(tVBuffer* pVBuffer)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VBufferUnlock, pVBuffer);
}

int J3DAPI stdDisplay_VBufferFill(tVBuffer* pVBuffer, uint32_t color, const StdRect* pRect)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VBufferFill, pVBuffer, color, pRect);
}

tVBuffer* J3DAPI stdDisplay_VBufferConvertColorFormat(const ColorInfo* pDesiredColorFormat, tVBuffer* pSrc, int bColorKey, LPDDCOLORKEY pColorKey)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VBufferConvertColorFormat, pDesiredColorFormat, pSrc, bColorKey, pColorKey);
}

int J3DAPI stdDisplay_VideoModeCompare(const StdVideoMode* pMode1, const StdVideoMode* pMode2)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_VideoModeCompare, pMode1, pMode2);
}

int J3DAPI stdDisplay_GetTextureMemory(size_t* pTotal, size_t* pFree)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetTextureMemory, pTotal, pFree);
}

int J3DAPI stdDisplay_GetTotalMemory(size_t* pTotal, size_t* pFree)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetTotalMemory, pTotal, pFree);
}

const char* J3DAPI stdDisplay_DDGetStatus(HRESULT status)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_DDGetStatus, status);
}

int J3DAPI stdDisplay_CreateZBuffer(LPDDPIXELFORMAT pPixelFormat, int bSystemMemory)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_CreateZBuffer, pPixelFormat, bSystemMemory);
}

int J3DAPI stdDisplay_InitDirectDraw(HWND hwnd)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_InitDirectDraw, hwnd);
}

void J3DAPI stdDisplay_ReleaseDirectDraw()
{
    J3D_TRAMPOLINE_CALL(stdDisplay_ReleaseDirectDraw);
}

BOOL __stdcall stdDisplay_DDEnumCallback(GUID* lpGUID, LPSTR szDriverName, LPSTR szDriverDescription, LPVOID lpContext)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_DDEnumCallback, lpGUID, szDriverName, szDriverDescription, lpContext);
}

HRESULT __stdcall stdDisplay_EnumVideoModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_EnumVideoModesCallback, lpDDSurfaceDesc, lpContext);
}

// Guessed, maybe this function does aspect ratio for different screen sizes
void J3DAPI stdDisplay_SetAspectRatio(StdVideoMode* pMode)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_SetAspectRatio, pMode);
}

LPDIRECTDRAW4 stdDisplay_GetDirectDraw(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetDirectDraw);
}

int J3DAPI stdDisplay_SetWindowMode(HWND hWnd, StdVideoMode* pDisplayMode)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_SetWindowMode, hWnd, pDisplayMode);
}

// dwBackBufferCount - Specifies the number of back buffers associated with the surface
int J3DAPI stdDisplay_SetFullscreenMode(HWND hwnd, const StdVideoMode* pDisplayMode, unsigned int numBackBuffers)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_SetFullscreenMode, hwnd, pDisplayMode, numBackBuffers);
}

void J3DAPI stdDisplay_ReleaseBuffers()
{
    J3D_TRAMPOLINE_CALL(stdDisplay_ReleaseBuffers);
}

uint8_t* J3DAPI stdDisplay_LockSurface(tVSurface* pVSurf)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_LockSurface, pVSurf);
}

int J3DAPI stdDisplay_UnlockSurface(tVSurface* pSurf)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_UnlockSurface, pSurf);
}

int stdDisplay_Update(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_Update);
}

int J3DAPI stdDisplay_ColorFillSurface(tVSurface* pSurf, uint32_t color, const StdRect* pRect)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_ColorFillSurface, pSurf, color, pRect);
}

int J3DAPI stdDisplay_BackBufferFill(uint32_t color, const StdRect* lpRect)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_BackBufferFill, color, lpRect);
}

int J3DAPI stdDisplay_SaveScreen(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_SaveScreen, pFilename);
}

void J3DAPI stdDisplay_SetDefaultResolution(uint32_t width, uint32_t height)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_SetDefaultResolution, width, height);
}

void J3DAPI stdDisplay_GetBackBufferSize(unsigned int* pWidth, unsigned int* pHeight)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_GetBackBufferSize, pWidth, pHeight);
}

size_t stdDisplay_GetNumVideoModes(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetNumVideoModes);
}

int J3DAPI stdDisplay_GetVideoMode(size_t modeNum, StdVideoMode* pDestMode)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetVideoMode, modeNum, pDestMode);
}

int J3DAPI stdDisplay_GetCurrentVideoMode(StdVideoMode* pDisplayMode)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetCurrentVideoMode, pDisplayMode);
}

HDC J3DAPI stdDisplay_GetFrontBufferDC()
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetFrontBufferDC);
}

void J3DAPI stdDisplay_ReleaseFrontBufferDC(HDC hdc)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_ReleaseFrontBufferDC, hdc);
}

HDC J3DAPI stdDisplay_GetBackBufferDC()
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_GetBackBufferDC);
}

void J3DAPI stdDisplay_ReleaseBackBufferDC(HDC hdc)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_ReleaseBackBufferDC, hdc);
}

int stdDisplay_FlipToGDISurface(void)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_FlipToGDISurface);
}

int J3DAPI stdDisplay_CanRenderWindowed()
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_CanRenderWindowed);
}

int J3DAPI stdDisplay_SetBufferClipper(int bFrontBuffer)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_SetBufferClipper, bFrontBuffer);
}

HRESULT J3DAPI stdDisplay_RemoveBufferClipper(int bFrontBuffer)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_RemoveBufferClipper, bFrontBuffer);
}

int J3DAPI stdDisplay_IsFullscreen()
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_IsFullscreen);
}

int J3DAPI stdDisplay_LockBackBuffer(void** ppSurface, uint32_t* pWidth, uint32_t* pHeight, int32_t* pPitch)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_LockBackBuffer, ppSurface, pWidth, pHeight, pPitch);
}

void stdDisplay_UnlockBackBuffer(void)
{
    J3D_TRAMPOLINE_CALL(stdDisplay_UnlockBackBuffer);
}

unsigned int J3DAPI stdDisplay_EncodeRGB565(unsigned int pixel)
{
    return J3D_TRAMPOLINE_CALL(stdDisplay_EncodeRGB565, pixel);
}
