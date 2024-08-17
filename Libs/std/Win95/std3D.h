#ifndef STD_STD3D_H
#define STD_STD3D_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

#define std3D_g_fogDensity J3D_DECL_FAR_VAR(std3D_g_fogDensity, float)
// extern float std3D_g_fogDensity ;

#define std3D_g_maxVertices J3D_DECL_FAR_VAR(std3D_g_maxVertices, size_t)
// extern size_t std3D_g_maxVertices;

int std3D_Startup(void);
void std3D_Shutdown(void);
size_t std3D_GetNumDevices(void);
const Device3D* std3D_GetAllDevices(void);
int J3DAPI std3D_Open(size_t deviceNum);
void J3DAPI std3D_Close();
void J3DAPI std3D_GetTextureFormat(StdColorFormatType type, ColorInfo* pDest, int* pbColorKeySet, LPDDCOLORKEY* ppColorKey);
// Returns color mode:
// 0 - RGB565
// 1 - RGB5551
// 2 - RGB4444
StdColorFormatType J3DAPI std3D_GetColorFormat(const ColorInfo* pCi);
size_t std3D_GetNumTextureFormats(void);
int std3D_StartScene(void);
void std3D_EndScene(void);
void J3DAPI std3D_DrawRenderList(LPDIRECT3DTEXTURE2 pTex, Std3DRenderState rdflags, LPD3DTLVERTEX aVerts, size_t numVerts, LPWORD aIndices, size_t numIndices);
void std3D_SetWireframeRenderState(void);
void J3DAPI std3D_DrawLineStrip(LPD3DTLVERTEX aVerts, size_t numVerts);
void J3DAPI std3D_DrawPointList(LPD3DTLVERTEX aVerts, size_t numVerts);
void J3DAPI std3D_SetRenderState(Std3DRenderState rdflags);
void J3DAPI std3D_AllocSystemTexture(tSystemTexture* pTexture, tVBuffer** apVBuffers, unsigned int numMipLevels, StdColorFormatType formatType);
void J3DAPI std3D_GetValidDimensions(unsigned int width, unsigned int height, unsigned int* pOutWidth, unsigned int* pOutHeight);
void J3DAPI std3D_ClearSystemTexture(tSystemTexture* pTex);
void J3DAPI std3D_AddToTextureCache(tSystemTexture* pCacheTexture, StdColorFormatType format);
size_t J3DAPI std3D_GetMipMapCount(const tSystemTexture* pTexture);
void std3D_ResetTextureCache(void);
void J3DAPI std3D_UpdateFrameCount(tSystemTexture* pTexture);
size_t J3DAPI std3D_FindClosestFormat(const ColorInfo* pCI);
int std3D_InitRenderState(void);
// On success 0 is returned
int J3DAPI std3D_SetMipmapFilter(Std3DMipmapFilterType filter);
int J3DAPI std3D_SetProjection(float fov, float nearPlane, float farPlane);
void J3DAPI std3D_EnableFog(int bEnabled, float density);
void J3DAPI std3D_SetFog(float red, float green, float blue, float startDepth, float endDepth);
void std3D_ClearZBuffer(void);
int std3D_CreateViewport(void);
void J3DAPI std3D_GetZBufferFormat(DDPIXELFORMAT* pPixelFormat);
HRESULT __stdcall std3D_EnumZBufferFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, DDPIXELFORMAT* lpContext);
HRESULT __stdcall std3D_D3DEnumDevicesCallback(GUID* lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHalDDesc, LPD3DDEVICEDESC lpD3DHelDDesc, LPVOID a6);
HRESULT __stdcall std3D_EnumTextureFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);
void J3DAPI std3D_AddTextureToCacheList(tSystemTexture* pTexture);
void J3DAPI std3D_RemoveTextureFromCacheList(tSystemTexture* pCacheTexture);
int J3DAPI std3D_PurgeTextureCache(size_t size);
const char* J3DAPI std3D_D3DGetStatus(HRESULT res);
StdDisplayEnvironment* J3DAPI std3D_BuildDisplayEnvironment();
void J3DAPI std3D_FreeDisplayEnvironment(StdDisplayEnvironment* pEnv);
void J3DAPI std3D_SetFindAllDevices(int bFindAll);

// Helper hooking functions
void std3D_InstallHooks(void);
void std3D_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STD3D_H
