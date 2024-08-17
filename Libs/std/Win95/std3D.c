#include "std3D.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define std3D_cfRGB565 J3D_DECL_FAR_VAR(std3D_cfRGB565, const ColorInfo)
#define std3D_cfRGB5551 J3D_DECL_FAR_VAR(std3D_cfRGB5551, const ColorInfo)
#define std3D_cfRGB4444 J3D_DECL_FAR_VAR(std3D_cfRGB4444, const ColorInfo)
#define std3D_aD3DStatusTbl J3D_DECL_FAR_ARRAYVAR(std3D_aD3DStatusTbl, const DXStatus(*)[186])
#define std3D_mipmapFilter J3D_DECL_FAR_VAR(std3D_mipmapFilter, Std3DMipmapFilterType)
#define std3D_bRenderFog J3D_DECL_FAR_VAR(std3D_bRenderFog, int)
#define std3D_frameCount J3D_DECL_FAR_VAR(std3D_frameCount, size_t)
#define std3D_curDevice J3D_DECL_FAR_VAR(std3D_curDevice, int)
#define std3D_RGBATextureFormat J3D_DECL_FAR_VAR(std3D_RGBATextureFormat, size_t)
#define std3D_zDepth J3D_DECL_FAR_VAR(std3D_zDepth, float)
#define std3D_RGBTextureFormat J3D_DECL_FAR_VAR(std3D_RGBTextureFormat, size_t)
#define std3D_RGBAKeyTextureFormat J3D_DECL_FAR_VAR(std3D_RGBAKeyTextureFormat, size_t)
#define std3D_fogStartDepth J3D_DECL_FAR_VAR(std3D_fogStartDepth, float)
#define std3D_numDevices J3D_DECL_FAR_VAR(std3D_numDevices, size_t)
#define std3D_aTextureFormats J3D_DECL_FAR_ARRAYVAR(std3D_aTextureFormats, StdTextureFormat(*)[8])
#define std3D_fogDepthFactor J3D_DECL_FAR_VAR(std3D_fogDepthFactor, float)
#define std3D_aDevices J3D_DECL_FAR_ARRAYVAR(std3D_aDevices, Device3D(*)[4])
#define std3D_renderState J3D_DECL_FAR_VAR(std3D_renderState, Std3DRenderState)
#define std3D_activeRect J3D_DECL_FAR_VAR(std3D_activeRect, D3DRECT)
#define std3D_fogEndDepth J3D_DECL_FAR_VAR(std3D_fogEndDepth, float)
#define std3D_pCurDevice J3D_DECL_FAR_VAR(std3D_pCurDevice, Device3D*)
#define std3D_numTextureFormats J3D_DECL_FAR_VAR(std3D_numTextureFormats, size_t)
#define std3D_bHasRGBTextureFormat J3D_DECL_FAR_VAR(std3D_bHasRGBTextureFormat, int)
#define std3D_bFogTable J3D_DECL_FAR_VAR(std3D_bFogTable, int)
#define std3D_pD3DTex J3D_DECL_FAR_VAR(std3D_pD3DTex, LPDIRECT3DTEXTURE2)
#define std3D_bFindAllD3Devices J3D_DECL_FAR_VAR(std3D_bFindAllD3Devices, int)
#define std3D_numCachedTextures J3D_DECL_FAR_VAR(std3D_numCachedTextures, size_t)
#define std3D_pFirstTexCache J3D_DECL_FAR_VAR(std3D_pFirstTexCache, tSystemTexture*)
#define std3D_pLastTexCache J3D_DECL_FAR_VAR(std3D_pLastTexCache, tSystemTexture*)
#define std3D_lpDD J3D_DECL_FAR_VAR(std3D_lpDD, LPDIRECTDRAW4)
#define std3D_pDDPalette J3D_DECL_FAR_VAR(std3D_pDDPalette, LPDIRECTDRAWPALETTE)
#define std3D_pDirect3D J3D_DECL_FAR_VAR(std3D_pDirect3D, LPDIRECT3D3)
#define std3D_pD3Device J3D_DECL_FAR_VAR(std3D_pD3Device, LPDIRECT3DDEVICE3)
#define std3D_lpD3DViewPort J3D_DECL_FAR_VAR(std3D_lpD3DViewPort, LPDIRECT3DVIEWPORT3)
#define std3D_bStartup J3D_DECL_FAR_VAR(std3D_bStartup, int)
#define std3D_bOpen J3D_DECL_FAR_VAR(std3D_bOpen, int)

void std3D_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(std3D_Startup);
    // J3D_HOOKFUNC(std3D_Shutdown);
    // J3D_HOOKFUNC(std3D_GetNumDevices);
    // J3D_HOOKFUNC(std3D_GetAllDevices);
    // J3D_HOOKFUNC(std3D_Open);
    // J3D_HOOKFUNC(std3D_Close);
    // J3D_HOOKFUNC(std3D_GetTextureFormat);
    // J3D_HOOKFUNC(std3D_GetColorFormat);
    // J3D_HOOKFUNC(std3D_GetNumTextureFormats);
    // J3D_HOOKFUNC(std3D_StartScene);
    // J3D_HOOKFUNC(std3D_EndScene);
    // J3D_HOOKFUNC(std3D_DrawRenderList);
    // J3D_HOOKFUNC(std3D_SetWireframeRenderState);
    // J3D_HOOKFUNC(std3D_DrawLineStrip);
    // J3D_HOOKFUNC(std3D_DrawPointList);
    // J3D_HOOKFUNC(std3D_SetRenderState);
    // J3D_HOOKFUNC(std3D_AllocSystemTexture);
    // J3D_HOOKFUNC(std3D_GetValidDimensions);
    // J3D_HOOKFUNC(std3D_ClearSystemTexture);
    // J3D_HOOKFUNC(std3D_AddToTextureCache);
    // J3D_HOOKFUNC(std3D_GetMipMapCount);
    // J3D_HOOKFUNC(std3D_ResetTextureCache);
    // J3D_HOOKFUNC(std3D_UpdateFrameCount);
    // J3D_HOOKFUNC(std3D_FindClosestFormat);
    // J3D_HOOKFUNC(std3D_InitRenderState);
    // J3D_HOOKFUNC(std3D_SetMipmapFilter);
    // J3D_HOOKFUNC(std3D_SetProjection);
    // J3D_HOOKFUNC(std3D_EnableFog);
    // J3D_HOOKFUNC(std3D_SetFog);
    // J3D_HOOKFUNC(std3D_ClearZBuffer);
    // J3D_HOOKFUNC(std3D_CreateViewport);
    // J3D_HOOKFUNC(std3D_GetZBufferFormat);
    // J3D_HOOKFUNC(std3D_EnumZBufferFormatsCallback);
    // J3D_HOOKFUNC(std3D_D3DEnumDevicesCallback);
    // J3D_HOOKFUNC(std3D_EnumTextureFormatsCallback);
    // J3D_HOOKFUNC(std3D_AddTextureToCacheList);
    // J3D_HOOKFUNC(std3D_RemoveTextureFromCacheList);
    // J3D_HOOKFUNC(std3D_PurgeTextureCache);
    // J3D_HOOKFUNC(std3D_D3DGetStatus);
    // J3D_HOOKFUNC(std3D_BuildDisplayEnvironment);
    // J3D_HOOKFUNC(std3D_FreeDisplayEnvironment);
    // J3D_HOOKFUNC(std3D_SetFindAllDevices);
}

void std3D_ResetGlobals(void)
{
    const ColorInfo std3D_cfRGB565_tmp = { STDCOLOR_RGB, 16, 5, 6, 5, 11, 5, 0, 3, 2, 3, 0, 0, 0 };
    memcpy((ColorInfo *)&std3D_cfRGB565, &std3D_cfRGB565_tmp, sizeof(std3D_cfRGB565));
    
    const ColorInfo std3D_cfRGB5551_tmp = { STDCOLOR_RGBA, 16, 5, 5, 5, 11, 6, 1, 3, 3, 3, 1, 0, 7 };
    memcpy((ColorInfo *)&std3D_cfRGB5551, &std3D_cfRGB5551_tmp, sizeof(std3D_cfRGB5551));
    
    const ColorInfo std3D_cfRGB4444_tmp = { STDCOLOR_RGBA, 16, 4, 4, 4, 12, 8, 4, 4, 4, 4, 4, 0, 4 };
    memcpy((ColorInfo *)&std3D_cfRGB4444, &std3D_cfRGB4444_tmp, sizeof(std3D_cfRGB4444));
    
    const DXStatus std3D_aD3DStatusTbl_tmp[186] = {
      { 0, "D3D_OK" },
      { -2005531972, "D3DERR_BADMAJORVERSION" },
      { -2005531971, "D3DERR_BADMINORVERSION" },
      { -2005531967, "D3DERR_INVALID_DEVICE" },
      { -2005531966, "D3DERR_INITFAILED" },
      { -2005531965, "D3DERR_DEVICEAGGREGATED" },
      { -2005531962, "D3DERR_EXECUTE_CREATE_FAILED" },
      { -2005531961, "D3DERR_EXECUTE_DESTROY_FAILED" },
      { -2005531960, "D3DERR_EXECUTE_LOCK_FAILED" },
      { -2005531959, "D3DERR_EXECUTE_UNLOCK_FAILED" },
      { -2005531958, "D3DERR_EXECUTE_LOCKED" },
      { -2005531957, "D3DERR_EXECUTE_NOT_LOCKED" },
      { -2005531956, "D3DERR_EXECUTE_FAILED" },
      { -2005531955, "D3DERR_EXECUTE_CLIPPED_FAILED" },
      { -2005531952, "D3DERR_TEXTURE_NO_SUPPORT" },
      { -2005531951, "D3DERR_TEXTURE_CREATE_FAILED" },
      { -2005531950, "D3DERR_TEXTURE_DESTROY_FAILED" },
      { -2005531949, "D3DERR_TEXTURE_LOCK_FAILED" },
      { -2005531948, "D3DERR_TEXTURE_UNLOCK_FAILED" },
      { -2005531947, "D3DERR_TEXTURE_LOAD_FAILED" },
      { -2005531946, "D3DERR_TEXTURE_SWAP_FAILED" },
      { -2005531945, "D3DERR_TEXTURE_LOCKED" },
      { -2005531944, "D3DERR_TEXTURE_NOT_LOCKED" },
      { -2005531943, "D3DERR_TEXTURE_GETSURF_FAILED" },
      { -2005531942, "D3DERR_MATRIX_CREATE_FAILED" },
      { -2005531941, "D3DERR_MATRIX_DESTROY_FAILED" },
      { -2005531940, "D3DERR_MATRIX_SETDATA_FAILED" },
      { -2005531939, "D3DERR_MATRIX_GETDATA_FAILED" },
      { -2005531938, "D3DERR_SETVIEWPORTDATA_FAILED" },
      { -2005531937, "D3DERR_INVALIDCURRENTVIEWPORT" },
      { -2005531936, "D3DERR_INVALIDPRIMITIVETYPE" },
      { -2005531935, "D3DERR_INVALIDVERTEXTYPE" },
      { -2005531934, "D3DERR_TEXTURE_BADSIZE" },
      { -2005531933, "D3DERR_INVALIDRAMPTEXTURE" },
      { -2005531932, "D3DERR_MATERIAL_CREATE_FAILED" },
      { -2005531931, "D3DERR_MATERIAL_DESTROY_FAILED" },
      { -2005531930, "D3DERR_MATERIAL_SETDATA_FAILED" },
      { -2005531929, "D3DERR_MATERIAL_GETDATA_FAILED" },
      { -2005531928, "D3DERR_INVALIDPALETTE" },
      { -2005531927, "D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY" },
      { -2005531926, "D3DERR_ZBUFF_NEEDS_VIDEOMEMORY" },
      { -2005531925, "D3DERR_SURFACENOTINVIDMEM" },
      { -2005531922, "D3DERR_LIGHT_SET_FAILED" },
      { -2005531921, "D3DERR_LIGHTHASVIEWPORT" },
      { -2005531920, "D3DERR_LIGHTNOTINTHISVIEWPORT" },
      { -2005531912, "D3DERR_SCENE_IN_SCENE" },
      { -2005531911, "D3DERR_SCENE_NOT_IN_SCENE" },
      { -2005531910, "D3DERR_SCENE_BEGIN_FAILED" },
      { -2005531909, "D3DERR_SCENE_END_FAILED" },
      { -2005531902, "D3DERR_INBEGIN" },
      { -2005531901, "D3DERR_NOTINBEGIN" },
      { -2005531900, "D3DERR_NOVIEWPORTS" },
      { -2005531899, "D3DERR_VIEWPORTDATANOTSET" },
      { -2005531898, "D3DERR_VIEWPORTHASNODEVICE" },
      { -2005531897, "D3DERR_NOCURRENTVIEWPORT" },
      { -2005530624, "D3DERR_INVALIDVERTEXFORMAT" },
      { -2005530622, "D3DERR_COLORKEYATTACHED" },
      { -2005530612, "D3DERR_VERTEXBUFFEROPTIMIZED" },
      { -2005530611, "D3DERR_VBUF_CREATE_FAILED" },
      { -2005530610, "D3DERR_VERTEXBUFFERLOCKED" },
      { -2005530602, "D3DERR_ZBUFFER_NOTPRESENT" },
      { -2005530601, "D3DERR_STENCILBUFFER_NOTPRESENT" },
      { -2005530600, "D3DERR_WRONGTEXTUREFORMAT" },
      { -2005530599, "D3DERR_UNSUPPORTEDCOLOROPERATION" },
      { -2005530598, "D3DERR_UNSUPPORTEDCOLORARG" },
      { -2005530597, "D3DERR_UNSUPPORTEDALPHAOPERATION" },
      { -2005530596, "D3DERR_UNSUPPORTEDALPHAARG" },
      { -2005530595, "D3DERR_TOOMANYOPERATIONS" },
      { -2005530594, "D3DERR_CONFLICTINGTEXTUREFILTER" },
      { -2005530593, "D3DERR_UNSUPPORTEDFACTORVALUE" },
      { -2005530591, "D3DERR_CONFLICTINGRENDERSTATE" },
      { -2005530590, "D3DERR_UNSUPPORTEDTEXTUREFILTER" },
      { -2005530589, "D3DERR_TOOMANYPRIMITIVES" },
      { -2005530588, "D3DERR_INVALIDMATRIX" },
      { -2005530587, "D3DERR_TOOMANYVERTICES" },
      { -2005530586, "D3DERR_CONFLICTINGTEXTUREPALETTE" },
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
    memcpy((DXStatus *)&std3D_aD3DStatusTbl, &std3D_aD3DStatusTbl_tmp, sizeof(std3D_aD3DStatusTbl));
    
    float std3D_g_fogDensity_tmp = 1.0f;
    memcpy(&std3D_g_fogDensity, &std3D_g_fogDensity_tmp, sizeof(std3D_g_fogDensity));
    
    Std3DMipmapFilterType std3D_mipmapFilter_tmp = -1;
    memcpy(&std3D_mipmapFilter, &std3D_mipmapFilter_tmp, sizeof(std3D_mipmapFilter));
    
    int std3D_bRenderFog_tmp = 1;
    memcpy(&std3D_bRenderFog, &std3D_bRenderFog_tmp, sizeof(std3D_bRenderFog));
    
    size_t std3D_frameCount_tmp = 1u;
    memcpy(&std3D_frameCount, &std3D_frameCount_tmp, sizeof(std3D_frameCount));
    
    memset(&std3D_curDevice, 0, sizeof(std3D_curDevice));
    memset(&std3D_RGBATextureFormat, 0, sizeof(std3D_RGBATextureFormat));
    memset(&std3D_zDepth, 0, sizeof(std3D_zDepth));
    memset(&std3D_RGBTextureFormat, 0, sizeof(std3D_RGBTextureFormat));
    memset(&std3D_RGBAKeyTextureFormat, 0, sizeof(std3D_RGBAKeyTextureFormat));
    memset(&std3D_fogStartDepth, 0, sizeof(std3D_fogStartDepth));
    memset(&std3D_numDevices, 0, sizeof(std3D_numDevices));
    memset(&std3D_aTextureFormats, 0, sizeof(std3D_aTextureFormats));
    memset(&std3D_fogDepthFactor, 0, sizeof(std3D_fogDepthFactor));
    memset(&std3D_aDevices, 0, sizeof(std3D_aDevices));
    memset(&std3D_renderState, 0, sizeof(std3D_renderState));
    memset(&std3D_activeRect, 0, sizeof(std3D_activeRect));
    memset(&std3D_fogEndDepth, 0, sizeof(std3D_fogEndDepth));
    memset(&std3D_pCurDevice, 0, sizeof(std3D_pCurDevice));
    memset(&std3D_numTextureFormats, 0, sizeof(std3D_numTextureFormats));
    memset(&std3D_bHasRGBTextureFormat, 0, sizeof(std3D_bHasRGBTextureFormat));
    memset(&std3D_bFogTable, 0, sizeof(std3D_bFogTable));
    memset(&std3D_g_maxVertices, 0, sizeof(std3D_g_maxVertices));
    memset(&std3D_pD3DTex, 0, sizeof(std3D_pD3DTex));
    memset(&std3D_bFindAllD3Devices, 0, sizeof(std3D_bFindAllD3Devices));
    memset(&std3D_numCachedTextures, 0, sizeof(std3D_numCachedTextures));
    memset(&std3D_pFirstTexCache, 0, sizeof(std3D_pFirstTexCache));
    memset(&std3D_pLastTexCache, 0, sizeof(std3D_pLastTexCache));
    memset(&std3D_lpDD, 0, sizeof(std3D_lpDD));
    memset(&std3D_pDDPalette, 0, sizeof(std3D_pDDPalette));
    memset(&std3D_pDirect3D, 0, sizeof(std3D_pDirect3D));
    memset(&std3D_pD3Device, 0, sizeof(std3D_pD3Device));
    memset(&std3D_lpD3DViewPort, 0, sizeof(std3D_lpD3DViewPort));
    memset(&std3D_bStartup, 0, sizeof(std3D_bStartup));
    memset(&std3D_bOpen, 0, sizeof(std3D_bOpen));
}

int std3D_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_Startup);
}

void std3D_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(std3D_Shutdown);
}

size_t std3D_GetNumDevices(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_GetNumDevices);
}

const Device3D* std3D_GetAllDevices(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_GetAllDevices);
}

int J3DAPI std3D_Open(size_t deviceNum)
{
    return J3D_TRAMPOLINE_CALL(std3D_Open, deviceNum);
}

void J3DAPI std3D_Close()
{
    J3D_TRAMPOLINE_CALL(std3D_Close);
}

void J3DAPI std3D_GetTextureFormat(StdColorFormatType type, ColorInfo* pDest, int* pbColorKeySet, LPDDCOLORKEY* ppColorKey)
{
    J3D_TRAMPOLINE_CALL(std3D_GetTextureFormat, type, pDest, pbColorKeySet, ppColorKey);
}

// Returns color mode:
// 0 - RGB565
// 1 - RGB5551
// 2 - RGB4444
StdColorFormatType J3DAPI std3D_GetColorFormat(const ColorInfo* pCi)
{
    return J3D_TRAMPOLINE_CALL(std3D_GetColorFormat, pCi);
}

size_t std3D_GetNumTextureFormats(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_GetNumTextureFormats);
}

int std3D_StartScene(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_StartScene);
}

void std3D_EndScene(void)
{
    J3D_TRAMPOLINE_CALL(std3D_EndScene);
}

void J3DAPI std3D_DrawRenderList(LPDIRECT3DTEXTURE2 pTex, Std3DRenderState rdflags, LPD3DTLVERTEX aVerts, size_t numVerts, LPWORD aIndices, size_t numIndices)
{
    J3D_TRAMPOLINE_CALL(std3D_DrawRenderList, pTex, rdflags, aVerts, numVerts, aIndices, numIndices);
}

void std3D_SetWireframeRenderState(void)
{
    J3D_TRAMPOLINE_CALL(std3D_SetWireframeRenderState);
}

void J3DAPI std3D_DrawLineStrip(LPD3DTLVERTEX aVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(std3D_DrawLineStrip, aVerts, numVerts);
}

void J3DAPI std3D_DrawPointList(LPD3DTLVERTEX aVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(std3D_DrawPointList, aVerts, numVerts);
}

void J3DAPI std3D_SetRenderState(Std3DRenderState rdflags)
{
    J3D_TRAMPOLINE_CALL(std3D_SetRenderState, rdflags);
}

void J3DAPI std3D_AllocSystemTexture(tSystemTexture* pTexture, tVBuffer** apVBuffers, unsigned int numMipLevels, StdColorFormatType formatType)
{
    J3D_TRAMPOLINE_CALL(std3D_AllocSystemTexture, pTexture, apVBuffers, numMipLevels, formatType);
}

void J3DAPI std3D_GetValidDimensions(unsigned int width, unsigned int height, unsigned int* pOutWidth, unsigned int* pOutHeight)
{
    J3D_TRAMPOLINE_CALL(std3D_GetValidDimensions, width, height, pOutWidth, pOutHeight);
}

void J3DAPI std3D_ClearSystemTexture(tSystemTexture* pTex)
{
    J3D_TRAMPOLINE_CALL(std3D_ClearSystemTexture, pTex);
}

void J3DAPI std3D_AddToTextureCache(tSystemTexture* pCacheTexture, StdColorFormatType format)
{
    J3D_TRAMPOLINE_CALL(std3D_AddToTextureCache, pCacheTexture, format);
}

size_t J3DAPI std3D_GetMipMapCount(const tSystemTexture* pTexture)
{
    return J3D_TRAMPOLINE_CALL(std3D_GetMipMapCount, pTexture);
}

void std3D_ResetTextureCache(void)
{
    J3D_TRAMPOLINE_CALL(std3D_ResetTextureCache);
}

void J3DAPI std3D_UpdateFrameCount(tSystemTexture* pTexture)
{
    J3D_TRAMPOLINE_CALL(std3D_UpdateFrameCount, pTexture);
}

size_t J3DAPI std3D_FindClosestFormat(const ColorInfo* pCI)
{
    return J3D_TRAMPOLINE_CALL(std3D_FindClosestFormat, pCI);
}

int std3D_InitRenderState(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_InitRenderState);
}

// On success 0 is returned
int J3DAPI std3D_SetMipmapFilter(Std3DMipmapFilterType filter)
{
    return J3D_TRAMPOLINE_CALL(std3D_SetMipmapFilter, filter);
}

int J3DAPI std3D_SetProjection(float fov, float nearPlane, float farPlane)
{
    return J3D_TRAMPOLINE_CALL(std3D_SetProjection, fov, nearPlane, farPlane);
}

void J3DAPI std3D_EnableFog(int bEnabled, float density)
{
    J3D_TRAMPOLINE_CALL(std3D_EnableFog, bEnabled, density);
}

void J3DAPI std3D_SetFog(float red, float green, float blue, float startDepth, float endDepth)
{
    J3D_TRAMPOLINE_CALL(std3D_SetFog, red, green, blue, startDepth, endDepth);
}

void std3D_ClearZBuffer(void)
{
    J3D_TRAMPOLINE_CALL(std3D_ClearZBuffer);
}

int std3D_CreateViewport(void)
{
    return J3D_TRAMPOLINE_CALL(std3D_CreateViewport);
}

void J3DAPI std3D_GetZBufferFormat(DDPIXELFORMAT* pPixelFormat)
{
    J3D_TRAMPOLINE_CALL(std3D_GetZBufferFormat, pPixelFormat);
}

HRESULT __stdcall std3D_EnumZBufferFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, DDPIXELFORMAT* lpContext)
{
    return J3D_TRAMPOLINE_CALL(std3D_EnumZBufferFormatsCallback, lpDDPixFmt, lpContext);
}

HRESULT __stdcall std3D_D3DEnumDevicesCallback(GUID* lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHalDDesc, LPD3DDEVICEDESC lpD3DHelDDesc, LPVOID a6)
{
    return J3D_TRAMPOLINE_CALL(std3D_D3DEnumDevicesCallback, lpGuid, lpDeviceDescription, lpDeviceName, lpD3DHalDDesc, lpD3DHelDDesc, a6);
}

HRESULT __stdcall std3D_EnumTextureFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext)
{
    return J3D_TRAMPOLINE_CALL(std3D_EnumTextureFormatsCallback, lpDDPixFmt, lpContext);
}

void J3DAPI std3D_AddTextureToCacheList(tSystemTexture* pTexture)
{
    J3D_TRAMPOLINE_CALL(std3D_AddTextureToCacheList, pTexture);
}

void J3DAPI std3D_RemoveTextureFromCacheList(tSystemTexture* pCacheTexture)
{
    J3D_TRAMPOLINE_CALL(std3D_RemoveTextureFromCacheList, pCacheTexture);
}

int J3DAPI std3D_PurgeTextureCache(size_t size)
{
    return J3D_TRAMPOLINE_CALL(std3D_PurgeTextureCache, size);
}

const char* J3DAPI std3D_D3DGetStatus(HRESULT res)
{
    return J3D_TRAMPOLINE_CALL(std3D_D3DGetStatus, res);
}

StdDisplayEnvironment* J3DAPI std3D_BuildDisplayEnvironment()
{
    return J3D_TRAMPOLINE_CALL(std3D_BuildDisplayEnvironment);
}

void J3DAPI std3D_FreeDisplayEnvironment(StdDisplayEnvironment* pEnv)
{
    J3D_TRAMPOLINE_CALL(std3D_FreeDisplayEnvironment, pEnv);
}

void J3DAPI std3D_SetFindAllDevices(int bFindAll)
{
    J3D_TRAMPOLINE_CALL(std3D_SetFindAllDevices, bFindAll);
}
