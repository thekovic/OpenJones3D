#ifndef RDROID_RDCACHE_H
#define RDROID_RDCACHE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI rdCache_Startup();
void rdCache_AdvanceFrame(void);
int J3DAPI rdCache_GetFrameNum();
rdCacheProcEntry* rdCache_GetProcEntry(void);
rdCacheProcEntry* rdCache_GetAlphaProcEntry(void);
void rdCache_Flush(void);
void rdCache_FlushAlpha(void);
void J3DAPI rdCache_AddProcFace(size_t numVerts);
void J3DAPI rdCache_AddAlphaProcFace(size_t numVertices);
void J3DAPI rdCache_SendFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys, rdCacheSortFunc pfSort);
void J3DAPI rdCache_SendWireframeFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys);
void J3DAPI rdCache_AddToTextureCache(tSystemTexture* pTexture, StdColorFormatType format);
int J3DAPI rdCache_ProcFaceDistanceCompare(const rdCacheProcEntry* pEntry1, const rdCacheProcEntry* pEntry2);
int J3DAPI rdCache_ProcFaceCompare(const rdCacheProcEntry* pEntry1, const rdCacheProcEntry* pEntry2);

// Helper hooking functions
void rdCache_InstallHooks(void);
void rdCache_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDCACHE_H
