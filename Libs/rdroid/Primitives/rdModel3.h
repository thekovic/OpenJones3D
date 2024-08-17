#ifndef RDROID_RDMODEL3_H
#define RDROID_RDMODEL3_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define rdModel3_g_numGeoLights J3D_DECL_FAR_VAR(rdModel3_g_numGeoLights, int)
// extern int rdModel3_g_numGeoLights;

#define rdModel3_g_numMeshLights J3D_DECL_FAR_VAR(rdModel3_g_numMeshLights, int)
// extern int rdModel3_g_numMeshLights;

#define rdModel3_g_numDrawnFaces J3D_DECL_FAR_VAR(rdModel3_g_numDrawnFaces, int)
// extern int rdModel3_g_numDrawnFaces;

#define rdModel3_g_localCamera J3D_DECL_FAR_VAR(rdModel3_g_localCamera, rdVector3)
// extern rdVector3 rdModel3_g_localCamera;

#define rdModel3_g_numDrawnAlphaFaces J3D_DECL_FAR_VAR(rdModel3_g_numDrawnAlphaFaces, int)
// extern int rdModel3_g_numDrawnAlphaFaces;

#define rdModel3_g_apGeoLights J3D_DECL_FAR_ARRAYVAR(rdModel3_g_apGeoLights, rdLight*(*)[128])
// extern rdLight *rdModel3_g_apGeoLights[128];

#define rdModel3_g_aLocalLightPos J3D_DECL_FAR_ARRAYVAR(rdModel3_g_aLocalLightPos, rdVector3(*)[128])
// extern rdVector3 rdModel3_g_aLocalLightPos[128];

#define rdModel3_g_pCurMesh J3D_DECL_FAR_VAR(rdModel3_g_pCurMesh, const rdModel3Mesh*)
// extern const rdModel3Mesh *rdModel3_g_pCurMesh;

#define rdModel3_g_curLightingMode J3D_DECL_FAR_VAR(rdModel3_g_curLightingMode, rdLightMode)
// extern rdLightMode rdModel3_g_curLightingMode;

#define rdModel3_g_lightingMode J3D_DECL_FAR_VAR(rdModel3_g_lightingMode, rdLightMode)
// extern rdLightMode rdModel3_g_lightingMode;

rdModel3LoaderFunc J3DAPI rdModel3_RegisterLoader(rdModel3LoaderFunc pfFunc);
void J3DAPI rdModel3_NewEntry(rdModel3* pModel);
int J3DAPI rdModel3_LoadEntry(const char* pFilename, rdModel3* pModel3);
// Almost the same as _FreeEntry with additional code for freeing materials.
// 
// Note in GF there is call to pModel3Unloader if function pointer has pointer assigned. (Same way as rdMaterial_Free
void J3DAPI rdModel3_FreeEntry(rdModel3* pModel3);
// THIS is same function as _Free but missing before freeing apMaterials:
//  for ( i = 0; i < pModel3->numMaterials; ++i )
//  {
//      rdMaterial_Free(pModel3->apMaterials[i]);
//  }
//  
//  Verify if this leads to memory leak
void J3DAPI rdModel3_FreeEntryGeometryOnly(rdModel3* pModel);
void J3DAPI rdModel3_BuildExpandedRadius(const rdModel3* pModel, const rdModel3HNode* pNode, const rdMatrix34* orient);
int J3DAPI rdModel3_GetMeshMatrix(rdThing* pThing, const rdMatrix34* orient, unsigned int nodeNum, rdMatrix34* meshOrient);
int J3DAPI rdModel3_ReplaceMesh(rdModel3* pModel, unsigned int geosetNum, unsigned int meshNum, const rdModel3Mesh* pSrcMesh);
int J3DAPI rdModel3_SwapMesh(rdModel3* pModel1, unsigned int meshNum1, rdModel3* pModel2, int meshNum2);
void J3DAPI rdModel3_GetThingColor(const rdThing* pThing, rdVector4* pDestColor);
void J3DAPI rdModel3_SetModelColor(rdModel3* pModel, const rdVector4* pColor);
void J3DAPI rdModel3_SetThingColor(rdThing* prdThing, const rdVector4* pColor);
void J3DAPI rdModel3_SetNodeColor(const rdModel3* pModel, rdModel3GeoSet* pGeoSet, const rdModel3HNode* pNode, const rdVector4* pColor);
void J3DAPI rdModel3_SetNodeColorForNonAmputatedJoints(const rdThing* prdThing, rdModel3GeoSet* pGeoSet, const rdModel3HNode* pNode, const rdVector4* pColor);
int J3DAPI rdModel3_Draw(rdThing* pThing, const rdMatrix34* pPlacement);
void J3DAPI rdModel3_DrawHNode(const rdModel3GeoSet* prdGeo, const rdModel3HNode* pNode);
void J3DAPI rdModel3_DrawMesh(const rdModel3Mesh* pMesh, const rdMatrix34* pOrient);
void J3DAPI rdModel3_DrawFace(const rdFace* pFace, const rdVector3* aTransformedVertices, int bIsBackFace, const rdVector4* pMeshColor);
void J3DAPI rdModel3_EnableFogRendering(int bEnabled);

// Helper hooking functions
void rdModel3_InstallHooks(void);
void rdModel3_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDMODEL3_H
