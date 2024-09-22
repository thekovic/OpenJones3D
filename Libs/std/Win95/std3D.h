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
void J3DAPI std3D_SetFindAllDevices(int bFindAll);

int J3DAPI std3D_Open(size_t deviceNum);
void J3DAPI std3D_Close();

void J3DAPI std3D_GetTextureFormat(StdColorFormatType type, ColorInfo* pDest, int* pbColorKeySet, LPDDCOLORKEY* ppColorKey);
StdColorFormatType J3DAPI std3D_GetColorFormat(const ColorInfo* pCi);
size_t std3D_GetNumTextureFormats(void);

int std3D_StartScene(void);
void std3D_EndScene(void);

void J3DAPI std3D_DrawRenderList(LPDIRECT3DTEXTURE2 pTex, Std3DRenderState rdflags, LPD3DTLVERTEX aVerts, size_t numVerts, LPWORD aIndices, size_t numIndices);
void J3DAPI std3D_DrawLineStrip(LPD3DTLVERTEX aVerts, size_t numVerts);
void J3DAPI std3D_DrawPointList(LPD3DTLVERTEX aVerts, size_t numVerts);
void J3DAPI std3D_SetRenderState(Std3DRenderState rdflags);
void std3D_SetWireframeRenderState(void);

void J3DAPI std3D_AllocSystemTexture(tSystemTexture* pTexture, tVBuffer** apVBuffers, size_t numMipLevels, StdColorFormatType formatType);
void J3DAPI std3D_GetValidDimensions(uint32_t width, uint32_t height, uint32_t* pOutWidth, uint32_t* pOutHeight);
void J3DAPI std3D_ClearSystemTexture(tSystemTexture* pTex);

void J3DAPI std3D_AddToTextureCache(tSystemTexture* pCacheTexture, StdColorFormatType format);
void std3D_ResetTextureCache(void);

size_t J3DAPI std3D_GetMipMapCount(const tSystemTexture* pTexture);
void J3DAPI std3D_UpdateFrameCount(tSystemTexture* pTexture);
size_t J3DAPI std3D_FindClosestFormat(const ColorInfo* pMatch);

// On success 0 is returned
int J3DAPI std3D_SetMipmapFilter(Std3DMipmapFilterType mode);
int J3DAPI std3D_SetProjection(float fov, float nearPlane, float farPlane);
void J3DAPI std3D_EnableFog(int bEnabled, float density);
void J3DAPI std3D_SetFog(float red, float green, float blue, float startDepth, float endDepth);
void std3D_ClearZBuffer(void);

StdDisplayEnvironment* J3DAPI std3D_BuildDisplayEnvironment();
void J3DAPI std3D_FreeDisplayEnvironment(StdDisplayEnvironment* pEnv);

// Helper hooking functions
void std3D_InstallHooks(void);
void std3D_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STD3D_H
