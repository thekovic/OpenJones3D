#ifndef STD_STDDISPLAY_H
#define STD_STDDISPLAY_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

#define stdDisplay_g_frontBuffer J3D_DECL_FAR_VAR(stdDisplay_g_frontBuffer, tVBuffer)
// extern tVBuffer stdDisplay_g_frontBuffer;

#define stdDisplay_g_backBuffer J3D_DECL_FAR_VAR(stdDisplay_g_backBuffer, tVBuffer)
// extern tVBuffer stdDisplay_g_backBuffer;

int stdDisplay_Startup(void);
void stdDisplay_Shutdown(void);
int J3DAPI stdDisplay_Open(size_t deviceNum);
void stdDisplay_Close(void);
int J3DAPI stdDisplay_SetMode(size_t modeNum, int bFullscreen, size_t numBackBuffers);
void stdDisplay_ClearMode(void);
size_t stdDisplay_GetNumDevices(void);
int J3DAPI stdDisplay_GetDevice(size_t deviceNum, StdDisplayDevice* pDest);
int J3DAPI stdDisplay_GetCurrentDevice(StdDisplayDevice* pDevice);
void J3DAPI stdDisplay_Refresh(int bReload);
tVBuffer* J3DAPI stdDisplay_VBufferNew(const tRasterInfo* pRasterInfo, int bUseVSurface, int bUseVideoMemory);
void J3DAPI stdDisplay_VBufferFree(tVBuffer* pVBuffer);
int J3DAPI stdDisplay_VBufferLock(tVBuffer* pVBuffer);
int J3DAPI stdDisplay_VBufferUnlock(tVBuffer* pVBuffer);
int J3DAPI stdDisplay_VBufferFill(tVBuffer* pVBuffer, uint32_t color, const StdRect* pRect);
tVBuffer* J3DAPI stdDisplay_VBufferConvertColorFormat(const ColorInfo* pDesiredColorFormat, tVBuffer* pSrc, int bColorKey, LPDDCOLORKEY pColorKey);
int J3DAPI stdDisplay_VideoModeCompare(const StdVideoMode* pMode1, const StdVideoMode* pMode2);
int J3DAPI stdDisplay_GetTextureMemory(size_t* pTotal, size_t* pFree);
int J3DAPI stdDisplay_GetTotalMemory(size_t* pTotal, size_t* pFree);
const char* J3DAPI stdDisplay_DDGetStatus(HRESULT status);
int J3DAPI stdDisplay_CreateZBuffer(LPDDPIXELFORMAT pPixelFormat, int bSystemMemory);
int J3DAPI stdDisplay_InitDirectDraw(HWND hwnd);
void J3DAPI stdDisplay_ReleaseDirectDraw();
BOOL __stdcall stdDisplay_DDEnumCallback(GUID* lpGUID, LPSTR szDriverName, LPSTR szDriverDescription, LPVOID lpContext);
HRESULT __stdcall stdDisplay_EnumVideoModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);
// Guessed, maybe this function does aspect ratio for different screen sizes
void J3DAPI stdDisplay_SetAspectRatio(StdVideoMode* pMode);
LPDIRECTDRAW4 stdDisplay_GetDirectDraw(void);
int J3DAPI stdDisplay_SetWindowMode(HWND hWnd, StdVideoMode* pDisplayMode);
// dwBackBufferCount - Specifies the number of back buffers associated with the surface
int J3DAPI stdDisplay_SetFullscreenMode(HWND hwnd, const StdVideoMode* pDisplayMode, unsigned int numBackBuffers);
void J3DAPI stdDisplay_ReleaseBuffers();
uint8_t* J3DAPI stdDisplay_LockSurface(tVSurface* pVSurf);
int J3DAPI stdDisplay_UnlockSurface(tVSurface* pSurf);
int stdDisplay_Update(void);
int J3DAPI stdDisplay_ColorFillSurface(tVSurface* pSurf, uint32_t color, const StdRect* pRect);
int J3DAPI stdDisplay_BackBufferFill(uint32_t color, const StdRect* lpRect);
int J3DAPI stdDisplay_SaveScreen(const char* pFilename);
void J3DAPI stdDisplay_SetDefaultResolution(uint32_t width, uint32_t height);
void J3DAPI stdDisplay_GetBackBufferSize(unsigned int* pWidth, unsigned int* pHeight);
size_t stdDisplay_GetNumVideoModes(void);
int J3DAPI stdDisplay_GetVideoMode(size_t modeNum, StdVideoMode* pDestMode);
int J3DAPI stdDisplay_GetCurrentVideoMode(StdVideoMode* pDisplayMode);
HDC J3DAPI stdDisplay_GetFrontBufferDC();
void J3DAPI stdDisplay_ReleaseFrontBufferDC(HDC hdc);
HDC J3DAPI stdDisplay_GetBackBufferDC();
void J3DAPI stdDisplay_ReleaseBackBufferDC(HDC hdc);
int stdDisplay_FlipToGDISurface(void);
int J3DAPI stdDisplay_CanRenderWindowed();
int J3DAPI stdDisplay_SetBufferClipper(int bFrontBuffer);
HRESULT J3DAPI stdDisplay_RemoveBufferClipper(int bFrontBuffer);
int J3DAPI stdDisplay_IsFullscreen();
int J3DAPI stdDisplay_LockBackBuffer(void** ppSurface, uint32_t* pWidth, uint32_t* pHeight, int32_t* pPitch);
void stdDisplay_UnlockBackBuffer(void);
unsigned int J3DAPI stdDisplay_EncodeRGB565(unsigned int pixel);

// Helper hooking functions
void stdDisplay_InstallHooks(void);
void stdDisplay_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDDISPLAY_H
