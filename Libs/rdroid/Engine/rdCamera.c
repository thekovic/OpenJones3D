#include "rdCamera.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdCamera_dword_5E10E8 J3D_DECL_FAR_VAR(rdCamera_dword_5E10E8, int)

void rdCamera_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdCamera_New);
    // J3D_HOOKFUNC(rdCamera_NewEntry);
    // J3D_HOOKFUNC(rdCamera_Free);
    // J3D_HOOKFUNC(rdCamera_FreeEntry);
    // J3D_HOOKFUNC(rdCamera_SetCanvas);
    // J3D_HOOKFUNC(rdCamera_SetCurrent);
    // J3D_HOOKFUNC(rdCamera_SetFOV);
    // J3D_HOOKFUNC(rdCamera_SetProjectType);
    // J3D_HOOKFUNC(rdCamera_SetAspectRatio);
    // J3D_HOOKFUNC(rdCamera_BuildFOV);
    // J3D_HOOKFUNC(rdCamera_BuildClipFrustrum);
    // J3D_HOOKFUNC(rdCamera_SetFrustrum);
    // J3D_HOOKFUNC(rdCamera_Update);
    // J3D_HOOKFUNC(rdCamera_OrthoProject);
    // J3D_HOOKFUNC(rdCamera_OrthoProjectLst);
    // J3D_HOOKFUNC(rdCamera_OrthoProjectSquare);
    // J3D_HOOKFUNC(rdCamera_OrthoProjectSquareLst);
    // J3D_HOOKFUNC(rdCamera_PerspProject);
    // J3D_HOOKFUNC(rdCamera_PerspProjectLst);
    // J3D_HOOKFUNC(rdCamera_PerspProjectSquare);
    // J3D_HOOKFUNC(rdCamera_PerspProjectSquareLst);
    // J3D_HOOKFUNC(rdCamera_SetAmbientLight);
    // J3D_HOOKFUNC(rdCamera_SetAttenuation);
    // J3D_HOOKFUNC(rdCamera_AddLight);
    // J3D_HOOKFUNC(rdCamera_ClearLights);
    // J3D_HOOKFUNC(rdCamera_sub_4C60B0);
}

void rdCamera_ResetGlobals(void)
{
    memset(&rdCamera_g_camPYR, 0, sizeof(rdCamera_g_camPYR));
    memset(&rdCamera_g_pCurCamera, 0, sizeof(rdCamera_g_pCurCamera));
    memset(&rdCamera_dword_5E10E8, 0, sizeof(rdCamera_dword_5E10E8));
    memset(&rdCamera_g_camMatrix, 0, sizeof(rdCamera_g_camMatrix));
}

rdCamera* J3DAPI rdCamera_New(float fov, int bFarClip, float nearPlane, float farPlane, float aspectRatio)
{
    return J3D_TRAMPOLINE_CALL(rdCamera_New, fov, bFarClip, nearPlane, farPlane, aspectRatio);
}

int J3DAPI rdCamera_NewEntry(rdCamera* pCamera, float fov, int bClipFar, float nearPlane, float farPlane, float aspectRatio)
{
    return J3D_TRAMPOLINE_CALL(rdCamera_NewEntry, pCamera, fov, bClipFar, nearPlane, farPlane, aspectRatio);
}

void J3DAPI rdCamera_Free(rdCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(rdCamera_Free, pCamera);
}

void J3DAPI rdCamera_FreeEntry(rdCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(rdCamera_FreeEntry, pCamera);
}

void J3DAPI rdCamera_SetCanvas(rdCamera* pCamera, rdCanvas* pCanvas)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetCanvas, pCamera, pCanvas);
}

void J3DAPI rdCamera_SetCurrent(rdCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetCurrent, pCamera);
}

void J3DAPI rdCamera_SetFOV(rdCamera* pCamera, float fov)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetFOV, pCamera, fov);
}

void J3DAPI rdCamera_SetProjectType(rdCamera* pCamera, rdCameraProjType type)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetProjectType, pCamera, type);
}

void J3DAPI rdCamera_SetAspectRatio(rdCamera* pCamera, float ratio)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetAspectRatio, pCamera, ratio);
}

void J3DAPI rdCamera_BuildFOV(rdCamera* pCamera)
{
    J3D_TRAMPOLINE_CALL(rdCamera_BuildFOV, pCamera);
}

void J3DAPI rdCamera_BuildClipFrustrum(rdCamera* pCamera, rdClipFrustum* pFrustum, float width, float height)
{
    J3D_TRAMPOLINE_CALL(rdCamera_BuildClipFrustrum, pCamera, pFrustum, width, height);
}

int J3DAPI rdCamera_SetFrustrum(rdCamera* pCamera, rdClipFrustum* pFrustrum, int left, int top, int right, int bottom)
{
    return J3D_TRAMPOLINE_CALL(rdCamera_SetFrustrum, pCamera, pFrustrum, left, top, right, bottom);
}

void J3DAPI rdCamera_Update(const rdMatrix34* orient)
{
    J3D_TRAMPOLINE_CALL(rdCamera_Update, orient);
}

// Function does ortho projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_OrthoProject(rdVector3* pDestVertex, const rdVector3* pSrcVertex)
{
    J3D_TRAMPOLINE_CALL(rdCamera_OrthoProject, pDestVertex, pSrcVertex);
}

// Function does ortho projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_OrthoProjectLst(rdVector3* pDestVerts, const rdVector3* pSrcVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(rdCamera_OrthoProjectLst, pDestVerts, pSrcVerts, numVerts);
}

// Function does ortho projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_OrthoProjectSquare(rdVector3* pDestVertex, const rdVector3* pSrcVertex)
{
    J3D_TRAMPOLINE_CALL(rdCamera_OrthoProjectSquare, pDestVertex, pSrcVertex);
}

// Function does ortho projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_OrthoProjectSquareLst(rdVector3* pDestVerts, const rdVector3* pSrcVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(rdCamera_OrthoProjectSquareLst, pDestVerts, pSrcVerts, numVerts);
}

// Function does perspective projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_PerspProject(rdVector3* pDestVertex, const rdVector3* pSrcVertex)
{
    J3D_TRAMPOLINE_CALL(rdCamera_PerspProject, pDestVertex, pSrcVertex);
}

// Function does perspective projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_PerspProjectLst(rdVector3* pDestVerts, const rdVector3* pSrcVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(rdCamera_PerspProjectLst, pDestVerts, pSrcVerts, numVerts);
}

// Function does perspective projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_PerspProjectSquare(rdVector3* pDestVertex, const rdVector3* pSrcVertex)
{
    J3D_TRAMPOLINE_CALL(rdCamera_PerspProjectSquare, pDestVertex, pSrcVertex);
}

// Function does perspective projection from view space (camera space ) to intermediante projection space. (2D projection in intermediante space between camera space and clip space) 
void J3DAPI rdCamera_PerspProjectSquareLst(rdVector3* pDestVerts, const rdVector3* pSrcVerts, size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(rdCamera_PerspProjectSquareLst, pDestVerts, pSrcVerts, numVerts);
}

void J3DAPI rdCamera_SetAmbientLight(rdCamera* pCamera, const rdVector4* pLight)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetAmbientLight, pCamera, pLight);
}

void J3DAPI rdCamera_SetAttenuation(rdCamera* pCamera, float min, float max)
{
    J3D_TRAMPOLINE_CALL(rdCamera_SetAttenuation, pCamera, min, max);
}

int J3DAPI rdCamera_AddLight(rdCamera* pCamera, rdLight* pLight, const rdVector3* pPos)
{
    return J3D_TRAMPOLINE_CALL(rdCamera_AddLight, pCamera, pLight, pPos);
}

int J3DAPI rdCamera_ClearLights(rdCamera* pCamera)
{
    return J3D_TRAMPOLINE_CALL(rdCamera_ClearLights, pCamera);
}

void J3DAPI rdCamera_sub_4C60B0(int bEnable)
{
    J3D_TRAMPOLINE_CALL(rdCamera_sub_4C60B0, bEnable);
}
