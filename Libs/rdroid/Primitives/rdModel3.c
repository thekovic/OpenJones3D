#include "rdModel3.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>

#define rdModel3_pfDrawFace J3D_DECL_FAR_VAR(rdModel3_pfDrawFace, rdModel3DrawFaceFunc)
#define rdModel3_aView J3D_DECL_FAR_ARRAYVAR(rdModel3_aView, rdVector3(*)[1024])
#define rdModel3_pCurThing J3D_DECL_FAR_VAR(rdModel3_pCurThing, const rdThing*)
#define rdModel3_bDrawMeshBounds J3D_DECL_FAR_VAR(rdModel3_bDrawMeshBounds, int)
#define rdModel3_pModel3Loader J3D_DECL_FAR_VAR(rdModel3_pModel3Loader, rdModel3LoaderFunc)
#define rdModel3_bCalcRadius J3D_DECL_FAR_VAR(rdModel3_bCalcRadius, int)
#define rdModel3_maxGeoRadius J3D_DECL_FAR_VAR(rdModel3_maxGeoRadius, float)
#define rdModel3_extraFaceFlags J3D_DECL_FAR_VAR(rdModel3_extraFaceFlags, rdFaceFlags)
#define rdModel3_apMeshLights J3D_DECL_FAR_ARRAYVAR(rdModel3_apMeshLights, rdLight*(*)[128])

void rdModel3_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdModel3_RegisterLoader);
    // J3D_HOOKFUNC(rdModel3_NewEntry);
    // J3D_HOOKFUNC(rdModel3_LoadEntry);
    // J3D_HOOKFUNC(rdModel3_FreeEntry);
    // J3D_HOOKFUNC(rdModel3_FreeEntryGeometryOnly);
    // J3D_HOOKFUNC(rdModel3_BuildExpandedRadius);
    // J3D_HOOKFUNC(rdModel3_GetMeshMatrix);
    // J3D_HOOKFUNC(rdModel3_ReplaceMesh);
    // J3D_HOOKFUNC(rdModel3_SwapMesh);
    // J3D_HOOKFUNC(rdModel3_GetThingColor);
    // J3D_HOOKFUNC(rdModel3_SetModelColor);
    // J3D_HOOKFUNC(rdModel3_SetThingColor);
    // J3D_HOOKFUNC(rdModel3_SetNodeColor);
    // J3D_HOOKFUNC(rdModel3_SetNodeColorForNonAmputatedJoints);
    // J3D_HOOKFUNC(rdModel3_Draw);
    // J3D_HOOKFUNC(rdModel3_DrawHNode);
    // J3D_HOOKFUNC(rdModel3_DrawMesh);
    // J3D_HOOKFUNC(rdModel3_DrawFace);
    // J3D_HOOKFUNC(rdModel3_EnableFogRendering);
}

void rdModel3_ResetGlobals(void)
{
    rdModel3DrawFaceFunc rdModel3_pfDrawFace_tmp = &rdModel3_DrawFace;
    memcpy(&rdModel3_pfDrawFace, &rdModel3_pfDrawFace_tmp, sizeof(rdModel3_pfDrawFace));
    
    memset(&rdModel3_aView, 0, sizeof(rdModel3_aView));
    memset((rdThing* *)&rdModel3_pCurThing, 0, sizeof(rdModel3_pCurThing));
    memset(&rdModel3_bDrawMeshBounds, 0, sizeof(rdModel3_bDrawMeshBounds));
    memset(&rdModel3_pModel3Loader, 0, sizeof(rdModel3_pModel3Loader));
    memset(&rdModel3_g_numGeoLights, 0, sizeof(rdModel3_g_numGeoLights));
    memset(&rdModel3_g_numMeshLights, 0, sizeof(rdModel3_g_numMeshLights));
    memset(&rdModel3_bCalcRadius, 0, sizeof(rdModel3_bCalcRadius));
    memset(&rdModel3_maxGeoRadius, 0, sizeof(rdModel3_maxGeoRadius));
    memset(&rdModel3_extraFaceFlags, 0, sizeof(rdModel3_extraFaceFlags));
    memset(&rdModel3_g_numDrawnFaces, 0, sizeof(rdModel3_g_numDrawnFaces));
    memset(&rdModel3_g_localCamera, 0, sizeof(rdModel3_g_localCamera));
    memset(&rdModel3_g_numDrawnAlphaFaces, 0, sizeof(rdModel3_g_numDrawnAlphaFaces));
    memset(&rdModel3_g_apGeoLights, 0, sizeof(rdModel3_g_apGeoLights));
    memset(&rdModel3_g_aLocalLightPos, 0, sizeof(rdModel3_g_aLocalLightPos));
    memset((rdModel3Mesh* *)&rdModel3_g_pCurMesh, 0, sizeof(rdModel3_g_pCurMesh));
    memset(&rdModel3_g_curLightingMode, 0, sizeof(rdModel3_g_curLightingMode));
    memset(&rdModel3_apMeshLights, 0, sizeof(rdModel3_apMeshLights));
    memset(&rdModel3_g_lightingMode, 0, sizeof(rdModel3_g_lightingMode));
}

rdModel3LoaderFunc J3DAPI rdModel3_RegisterLoader(rdModel3LoaderFunc pfFunc)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_RegisterLoader, pfFunc);
}

void J3DAPI rdModel3_NewEntry(rdModel3* pModel)
{
    J3D_TRAMPOLINE_CALL(rdModel3_NewEntry, pModel);
}

int J3DAPI rdModel3_LoadEntry(const char* pFilename, rdModel3* pModel3)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_LoadEntry, pFilename, pModel3);
}

// Almost the same as _FreeEntry with additional code for freeing materials.
// 
// Note in GF there is call to pModel3Unloader if function pointer has pointer assigned. (Same way as rdMaterial_Free
void J3DAPI rdModel3_FreeEntry(rdModel3* pModel3)
{
    J3D_TRAMPOLINE_CALL(rdModel3_FreeEntry, pModel3);
}

// THIS is same function as _Free but missing before freeing apMaterials:
//  for ( i = 0; i < pModel3->numMaterials; ++i )
//  {
//      rdMaterial_Free(pModel3->apMaterials[i]);
//  }
//  
//  Verify if this leads to memory leak
void J3DAPI rdModel3_FreeEntryGeometryOnly(rdModel3* pModel)
{
    J3D_TRAMPOLINE_CALL(rdModel3_FreeEntryGeometryOnly, pModel);
}

void J3DAPI rdModel3_BuildExpandedRadius(const rdModel3* pModel, const rdModel3HNode* pNode, const rdMatrix34* orient)
{
    J3D_TRAMPOLINE_CALL(rdModel3_BuildExpandedRadius, pModel, pNode, orient);
}

int J3DAPI rdModel3_GetMeshMatrix(rdThing* pThing, const rdMatrix34* orient, unsigned int nodeNum, rdMatrix34* meshOrient)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_GetMeshMatrix, pThing, orient, nodeNum, meshOrient);
}

int J3DAPI rdModel3_ReplaceMesh(rdModel3* pModel, unsigned int geosetNum, unsigned int meshNum, const rdModel3Mesh* pSrcMesh)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_ReplaceMesh, pModel, geosetNum, meshNum, pSrcMesh);
}

int J3DAPI rdModel3_SwapMesh(rdModel3* pModel1, unsigned int meshNum1, rdModel3* pModel2, int meshNum2)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_SwapMesh, pModel1, meshNum1, pModel2, meshNum2);
}

void J3DAPI rdModel3_GetThingColor(const rdThing* pThing, rdVector4* pDestColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_GetThingColor, pThing, pDestColor);
}

void J3DAPI rdModel3_SetModelColor(rdModel3* pModel, const rdVector4* pColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_SetModelColor, pModel, pColor);
}

void J3DAPI rdModel3_SetThingColor(rdThing* prdThing, const rdVector4* pColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_SetThingColor, prdThing, pColor);
}

void J3DAPI rdModel3_SetNodeColor(const rdModel3* pModel, rdModel3GeoSet* pGeoSet, const rdModel3HNode* pNode, const rdVector4* pColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_SetNodeColor, pModel, pGeoSet, pNode, pColor);
}

void J3DAPI rdModel3_SetNodeColorForNonAmputatedJoints(const rdThing* prdThing, rdModel3GeoSet* pGeoSet, const rdModel3HNode* pNode, const rdVector4* pColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_SetNodeColorForNonAmputatedJoints, prdThing, pGeoSet, pNode, pColor);
}

int J3DAPI rdModel3_Draw(rdThing* pThing, const rdMatrix34* pPlacement)
{
    return J3D_TRAMPOLINE_CALL(rdModel3_Draw, pThing, pPlacement);
}

void J3DAPI rdModel3_DrawHNode(const rdModel3GeoSet* prdGeo, const rdModel3HNode* pNode)
{
    J3D_TRAMPOLINE_CALL(rdModel3_DrawHNode, prdGeo, pNode);
}

void J3DAPI rdModel3_DrawMesh(const rdModel3Mesh* pMesh, const rdMatrix34* pOrient)
{
    J3D_TRAMPOLINE_CALL(rdModel3_DrawMesh, pMesh, pOrient);
}

void J3DAPI rdModel3_DrawFace(const rdFace* pFace, const rdVector3* aTransformedVertices, int bIsBackFace, const rdVector4* pMeshColor)
{
    J3D_TRAMPOLINE_CALL(rdModel3_DrawFace, pFace, aTransformedVertices, bIsBackFace, pMeshColor);
}

void J3DAPI rdModel3_EnableFogRendering(int bEnabled)
{
    J3D_TRAMPOLINE_CALL(rdModel3_EnableFogRendering, bEnabled);
}
