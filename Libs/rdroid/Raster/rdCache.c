#include "rdCache.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdCache_aProcFaces J3D_DECL_FAR_ARRAYVAR(rdCache_aProcFaces, rdCacheProcEntry(*)[128])
#define rdCache_aVertIntensities J3D_DECL_FAR_ARRAYVAR(rdCache_aVertIntensities, rdVector4(*)[8192])
#define rdCache_aAlphaProcFaces J3D_DECL_FAR_ARRAYVAR(rdCache_aAlphaProcFaces, rdCacheProcEntry(*)[2048])
#define rdCache_numProcFaces J3D_DECL_FAR_VAR(rdCache_numProcFaces, size_t)
#define rdCache_aVertices J3D_DECL_FAR_ARRAYVAR(rdCache_aVertices, D3DTLVERTEX(*)[131072])
#define rdCache_aAlphaVertIntensities J3D_DECL_FAR_ARRAYVAR(rdCache_aAlphaVertIntensities, rdVector4(*)[131072])
#define rdCache_aAlphaVertices J3D_DECL_FAR_ARRAYVAR(rdCache_aAlphaVertices, D3DTLVERTEX(*)[131072])
#define rdCache_pCurCacheVertex J3D_DECL_FAR_VAR(rdCache_pCurCacheVertex, LPD3DTLVERTEX)
#define rdCache_totalVerts J3D_DECL_FAR_VAR(rdCache_totalVerts, size_t)
#define rdCache_numAlphaProcFaces J3D_DECL_FAR_VAR(rdCache_numAlphaProcFaces, size_t)
#define rdCache_pCurInVert J3D_DECL_FAR_VAR(rdCache_pCurInVert, LPD3DTLVERTEX)
#define rdCache_aVertIndices J3D_DECL_FAR_ARRAYVAR(rdCache_aVertIndices, uint16_t(*)[393216])
#define rdCache_aHWVertices J3D_DECL_FAR_ARRAYVAR(rdCache_aHWVertices, D3DTLVERTEX(*)[131072])
#define rdCache_drawnFaces J3D_DECL_FAR_VAR(rdCache_drawnFaces, size_t)
#define rdCache_frameNum J3D_DECL_FAR_VAR(rdCache_frameNum, int)
#define rdCache_numUsedVertices J3D_DECL_FAR_VAR(rdCache_numUsedVertices, size_t)
#define rdCache_numUsedAlphaVertices J3D_DECL_FAR_VAR(rdCache_numUsedAlphaVertices, size_t)

void rdCache_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdCache_Startup);
    // J3D_HOOKFUNC(rdCache_AdvanceFrame);
    // J3D_HOOKFUNC(rdCache_GetFrameNum);
    // J3D_HOOKFUNC(rdCache_GetProcEntry);
    // J3D_HOOKFUNC(rdCache_GetAlphaProcEntry);
    // J3D_HOOKFUNC(rdCache_Flush);
    // J3D_HOOKFUNC(rdCache_FlushAlpha);
    // J3D_HOOKFUNC(rdCache_AddProcFace);
    // J3D_HOOKFUNC(rdCache_AddAlphaProcFace);
    // J3D_HOOKFUNC(rdCache_SendFaceListToHardware);
    // J3D_HOOKFUNC(rdCache_SendWireframeFaceListToHardware);
    // J3D_HOOKFUNC(rdCache_AddToTextureCache);
    // J3D_HOOKFUNC(rdCache_ProcFaceDistanceCompare);
    // J3D_HOOKFUNC(rdCache_ProcFaceCompare);
}

void rdCache_ResetGlobals(void)
{
    memset(&rdCache_aProcFaces, 0, sizeof(rdCache_aProcFaces));
    memset(&rdCache_aVertIntensities, 0, sizeof(rdCache_aVertIntensities));
    memset(&rdCache_aAlphaProcFaces, 0, sizeof(rdCache_aAlphaProcFaces));
    memset(&rdCache_numProcFaces, 0, sizeof(rdCache_numProcFaces));
    memset(&rdCache_aVertices, 0, sizeof(rdCache_aVertices));
    memset(&rdCache_aAlphaVertIntensities, 0, sizeof(rdCache_aAlphaVertIntensities));
    memset(&rdCache_aAlphaVertices, 0, sizeof(rdCache_aAlphaVertices));
    memset(&rdCache_pCurCacheVertex, 0, sizeof(rdCache_pCurCacheVertex));
    memset(&rdCache_totalVerts, 0, sizeof(rdCache_totalVerts));
    memset(&rdCache_numAlphaProcFaces, 0, sizeof(rdCache_numAlphaProcFaces));
    memset(&rdCache_pCurInVert, 0, sizeof(rdCache_pCurInVert));
    memset(&rdCache_aVertIndices, 0, sizeof(rdCache_aVertIndices));
    memset(&rdCache_aHWVertices, 0, sizeof(rdCache_aHWVertices));
    memset(&rdCache_drawnFaces, 0, sizeof(rdCache_drawnFaces));
    memset(&rdCache_frameNum, 0, sizeof(rdCache_frameNum));
    memset(&rdCache_numUsedVertices, 0, sizeof(rdCache_numUsedVertices));
    memset(&rdCache_numUsedAlphaVertices, 0, sizeof(rdCache_numUsedAlphaVertices));
}

void J3DAPI rdCache_Startup()
{
    J3D_TRAMPOLINE_CALL(rdCache_Startup);
}

void rdCache_AdvanceFrame(void)
{
    J3D_TRAMPOLINE_CALL(rdCache_AdvanceFrame);
}

int J3DAPI rdCache_GetFrameNum()
{
    return J3D_TRAMPOLINE_CALL(rdCache_GetFrameNum);
}

rdCacheProcEntry* rdCache_GetProcEntry(void)
{
    return J3D_TRAMPOLINE_CALL(rdCache_GetProcEntry);
}

rdCacheProcEntry* rdCache_GetAlphaProcEntry(void)
{
    return J3D_TRAMPOLINE_CALL(rdCache_GetAlphaProcEntry);
}

void rdCache_Flush(void)
{
    J3D_TRAMPOLINE_CALL(rdCache_Flush);
}

void rdCache_FlushAlpha(void)
{
    J3D_TRAMPOLINE_CALL(rdCache_FlushAlpha);
}

void J3DAPI rdCache_AddProcFace(size_t numVerts)
{
    J3D_TRAMPOLINE_CALL(rdCache_AddProcFace, numVerts);
}

void J3DAPI rdCache_AddAlphaProcFace(size_t numVertices)
{
    J3D_TRAMPOLINE_CALL(rdCache_AddAlphaProcFace, numVertices);
}

void J3DAPI rdCache_SendFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys, rdCacheSortFunc pfSort)
{
    J3D_TRAMPOLINE_CALL(rdCache_SendFaceListToHardware, numPolys, aPolys, pfSort);
}

void J3DAPI rdCache_SendWireframeFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys)
{
    J3D_TRAMPOLINE_CALL(rdCache_SendWireframeFaceListToHardware, numPolys, aPolys);
}

void J3DAPI rdCache_AddToTextureCache(tSystemTexture* pTexture, StdColorFormatType format)
{
    J3D_TRAMPOLINE_CALL(rdCache_AddToTextureCache, pTexture, format);
}

int J3DAPI rdCache_ProcFaceDistanceCompare(const rdCacheProcEntry* pEntry1, const rdCacheProcEntry* pEntry2)
{
    return J3D_TRAMPOLINE_CALL(rdCache_ProcFaceDistanceCompare, pEntry1, pEntry2);
}

int J3DAPI rdCache_ProcFaceCompare(const rdCacheProcEntry* pEntry1, const rdCacheProcEntry* pEntry2)
{
    return J3D_TRAMPOLINE_CALL(rdCache_ProcFaceCompare, pEntry1, pEntry2);
}
