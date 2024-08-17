#include "rdQClip.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdQClip_pDestVert J3D_DECL_FAR_VAR(rdQClip_pDestVert, rdVector3*)
#define rdQClip_pSourceVert J3D_DECL_FAR_VAR(rdQClip_pSourceVert, rdVector3*)
#define rdQClip_aWorkVerts J3D_DECL_FAR_ARRAYVAR(rdQClip_aWorkVerts, rdVector3(*)[80])

void rdQClip_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdQClip_VerticesInFrustrum);
    // J3D_HOOKFUNC(rdQClip_Face3W);
}

void rdQClip_ResetGlobals(void)
{
    memset(&rdQClip_pDestVert, 0, sizeof(rdQClip_pDestVert));
    memset(&rdQClip_pSourceVert, 0, sizeof(rdQClip_pSourceVert));
    memset(&rdQClip_aWorkVerts, 0, sizeof(rdQClip_aWorkVerts));
}

size_t J3DAPI rdQClip_VerticesInFrustrum(const rdClipFrustum* pFrustrum, const rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdQClip_VerticesInFrustrum, pFrustrum, aVertices, numVertices);
}

// Function clips face vertices (max RDQCLIP_MAXWORKVERTS) based on their Y coord (aka forward) and clip frustum nearPlane
int J3DAPI rdQClip_Face3W(const rdClipFrustum* pFrustrum, rdVector3* aVertices, size_t numVertices)
{
    return J3D_TRAMPOLINE_CALL(rdQClip_Face3W, pFrustrum, aVertices, numVertices);
}
