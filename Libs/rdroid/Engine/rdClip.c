#include "rdClip.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdClip_pSourceTVert J3D_DECL_FAR_VAR(rdClip_pSourceTVert, rdVector2*)
#define rdClip_pDestTVert J3D_DECL_FAR_VAR(rdClip_pDestTVert, rdVector2*)
#define rdClip_pDestVertIntensity J3D_DECL_FAR_VAR(rdClip_pDestVertIntensity, rdVector4*)
#define rdClip_pDestVert J3D_DECL_FAR_VAR(rdClip_pDestVert, rdVector3*)
#define rdClip_aWorkTVerts J3D_DECL_FAR_ARRAYVAR(rdClip_aWorkTVerts, rdVector2(*)[80])
#define rdClip_pSourceVert J3D_DECL_FAR_VAR(rdClip_pSourceVert, rdVector3*)
#define rdClip_pSourceVertIntensity J3D_DECL_FAR_VAR(rdClip_pSourceVertIntensity, rdVector4*)
#define rdClip_aWorkVerts J3D_DECL_FAR_ARRAYVAR(rdClip_aWorkVerts, rdVector3(*)[80])
#define rdClip_aWorkVertIntensities J3D_DECL_FAR_ARRAYVAR(rdClip_aWorkVertIntensities, rdVector4(*)[80])
#define rdClip_aWorkFaceVerts J3D_DECL_FAR_ARRAYVAR(rdClip_aWorkFaceVerts, rdVector3(*)[144])

void rdClip_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdClip_Line2);
    // J3D_HOOKFUNC(rdClip_CalcOutcode2);
    // J3D_HOOKFUNC(rdClip_Line2Ex);
    // J3D_HOOKFUNC(rdClip_CalcOutcode2Ex);
    // J3D_HOOKFUNC(rdClip_ClipFacePVS);
    // J3D_HOOKFUNC(rdClip_Face3WPVS);
    // J3D_HOOKFUNC(rdClip_Face3W);
    // J3D_HOOKFUNC(rdClip_Face3WOrtho);
    // J3D_HOOKFUNC(rdClip_Face3S);
    // J3D_HOOKFUNC(rdClip_Face3SOrtho);
    // J3D_HOOKFUNC(rdClip_Face3GS);
    // J3D_HOOKFUNC(rdClip_Face3GSOrtho);
    // J3D_HOOKFUNC(rdClip_Face3GT);
    // J3D_HOOKFUNC(rdClip_Face3GTOrtho);
    // J3D_HOOKFUNC(rdClip_Face3T);
    // J3D_HOOKFUNC(rdClip_Face3TOrtho);
    // J3D_HOOKFUNC(rdClip_SphereInFrustrum);
    // J3D_HOOKFUNC(rdClip_QFace3W);
    // J3D_HOOKFUNC(rdClip_FaceToPlane);
    // J3D_HOOKFUNC(rdClip_VerticesToPlane);
}

void rdClip_ResetGlobals(void)
{
    memset(&rdClip_pSourceTVert, 0, sizeof(rdClip_pSourceTVert));
    memset(&rdClip_pDestTVert, 0, sizeof(rdClip_pDestTVert));
    memset(&rdClip_pDestVertIntensity, 0, sizeof(rdClip_pDestVertIntensity));
    memset(&rdClip_pDestVert, 0, sizeof(rdClip_pDestVert));
    memset(&rdClip_aWorkTVerts, 0, sizeof(rdClip_aWorkTVerts));
    memset(&rdClip_pSourceVert, 0, sizeof(rdClip_pSourceVert));
    memset(&rdClip_pSourceVertIntensity, 0, sizeof(rdClip_pSourceVertIntensity));
    memset(&rdClip_aWorkVerts, 0, sizeof(rdClip_aWorkVerts));
    memset(&rdClip_aWorkVertIntensities, 0, sizeof(rdClip_aWorkVertIntensities));
    memset(&rdClip_g_faceStatus, 0, sizeof(rdClip_g_faceStatus));
    memset(&rdClip_aWorkFaceVerts, 0, sizeof(rdClip_aWorkFaceVerts));
}

int J3DAPI rdClip_Line2(const rdCanvas* pCanvas, int* x1, int* y1, int* x2, int* y2)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Line2, pCanvas, x1, y1, x2, y2);
}

rdClipOutcode J3DAPI rdClip_CalcOutcode2(const rdCanvas* pCanvas, int x, int y)
{
    return J3D_TRAMPOLINE_CALL(rdClip_CalcOutcode2, pCanvas, x, y);
}

// overload of rdClip_Line2
int J3DAPI rdClip_Line2Ex(float* x1, float* y1, float* x2, float* y2)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Line2Ex, x1, y1, x2, y2);
}

// overload of rdClip_CalcOutcode2
int J3DAPI rdClip_CalcOutcode2Ex(float x, float y, float width, float height)
{
    return J3D_TRAMPOLINE_CALL(rdClip_CalcOutcode2Ex, x, y, width, height);
}

int J3DAPI rdClip_ClipFacePVS(rdClipFrustum* pFrustrum, const rdPrimit3* pSrc, rdPrimit3* pDest)
{
    return J3D_TRAMPOLINE_CALL(rdClip_ClipFacePVS, pFrustrum, pSrc, pDest);
}

int J3DAPI rdClip_Face3WPVS(rdClipFrustum* pFrustrum, rdVector3* aVertices, int numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3WPVS, pFrustrum, aVertices, numVertices);
}

int J3DAPI rdClip_Face3W(const rdClipFrustum* pFrustrum, rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3W, pFrustrum, aVertices, numVertices);
}

int J3DAPI rdClip_Face3WOrtho(const rdClipFrustum* pFrustrum, rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3WOrtho, pFrustrum, aVertices, numVertices);
}

int J3DAPI rdClip_Face3S(const rdClipFrustum* pFrustrum, rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3S, pFrustrum, aVertices, numVertices);
}

int J3DAPI rdClip_Face3SOrtho(const rdClipFrustum* pFrustum, rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3SOrtho, pFrustum, aVertices, numVertices);
}

int J3DAPI rdClip_Face3GS(const rdClipFrustum* pFrustrum, rdVector3* aVertices, rdVector4* aIntensities, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3GS, pFrustrum, aVertices, aIntensities, numVertices);
}

int J3DAPI rdClip_Face3GSOrtho(const rdClipFrustum* pFrustum, rdVector3* aVertices, rdVector4* aIntensities, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3GSOrtho, pFrustum, aVertices, aIntensities, numVertices);
}

int J3DAPI rdClip_Face3GT(const rdClipFrustum* pFrustrum, rdVector3* aVertices, rdVector2* aTexVertices, int numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3GT, pFrustrum, aVertices, aTexVertices, numVertices);
}

int J3DAPI rdClip_Face3GTOrtho(const rdClipFrustum* pFrustrum, rdVector3* aVertices, rdVector2* aTexVertices, int numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3GTOrtho, pFrustrum, aVertices, aTexVertices, numVertices);
}

int J3DAPI rdClip_Face3T(const rdClipFrustum* pFrustrum, rdVector3* aVertices, rdVector2* aTexVertices, rdVector4* aIntensities, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3T, pFrustrum, aVertices, aTexVertices, aIntensities, numVertices);
}

int J3DAPI rdClip_Face3TOrtho(const rdClipFrustum* pFrustum, rdVector3* aVertices, rdVector2* aTexVertices, rdVector4* aIntensities, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdClip_Face3TOrtho, pFrustum, aVertices, aTexVertices, aIntensities, numVertices);
}

// Checks if sphere is in frustum.
// pCenter should be in camera space.
// Returns RdFrustumCull:
//  0 - inside frustum
//  1 - intersects frustum
//  2 - outside frustum 
RdFrustumCull J3DAPI rdClip_SphereInFrustrum(const rdClipFrustum* pFrustum, const rdVector3* pCenter, float radius)
{
    return J3D_TRAMPOLINE_CALL(rdClip_SphereInFrustrum, pFrustum, pCenter, radius);
}

// Function clips vertices to clipfrustum and output them to pDst
// Function does quick clipiping by getting number of vertices in laying in frustum and than  only near plane clipping is performed
void J3DAPI rdClip_QFace3W(const rdClipFrustum* pFrustrum, const rdPrimit3* pSrc, rdPrimit3* pDst)
{
    J3D_TRAMPOLINE_CALL(rdClip_QFace3W, pFrustrum, pSrc, pDst);
}

// Function transforms face vertices to NDC screen space and assigns them to out pProcFace 
// 
// aVerts here should be transformed to camera space.
int J3DAPI rdClip_FaceToPlane(const rdClipFrustum* pFrustrum, rdCacheProcEntry* pProcFace, const rdFace* pFace, const rdVector3* aVerts, const rdVector2* aTexVerts, const rdVector4* aLightColors, const rdVector4* aVertColors)
{
    return J3D_TRAMPOLINE_CALL(rdClip_FaceToPlane, pFrustrum, pProcFace, pFace, aVerts, aTexVerts, aLightColors, aVertColors);
}

// Function transforms vertices to NDC screen space and assigns them to out pProcFace 
// 
// aVerts here should be transformed to camera space.
void J3DAPI rdClip_VerticesToPlane(rdCacheProcEntry* pProcFace, const rdVector3* aVerts, const rdVector2* aTexVerts, int numVerts)
{
    J3D_TRAMPOLINE_CALL(rdClip_VerticesToPlane, pProcFace, aVerts, aTexVerts, numVerts);
}
