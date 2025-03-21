#ifndef RDROID_RDCACHE_H
#define RDROID_RDCACHE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define RDCACHE_MAXFACEVERTICES 64 // Max vertices per face
                                   // Note, some clipping functions, such as rdClip_FaceToPlane can handle at max 144 vertices. So be conservative when raising this number

#define RDCACHE_MAXVERTICES 32768 // Changed: Was 2048

    void J3DAPI rdCache_Startup();
void rdCache_AdvanceFrame(void);
int  rdCache_GetFrameNum(void);

rdCacheProcEntry* rdCache_GetProcEntry(void);
rdCacheProcEntry* rdCache_GetAlphaProcEntry(void);

void  rdCache_Flush(void);
void  rdCache_FlushAlpha(void);

void J3DAPI rdCache_AddProcFace(size_t numVerts);
void J3DAPI rdCache_AddAlphaProcFace(size_t numVertices);

void J3DAPI rdCache_SendFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys, rdCacheSortFunc pfSort);
void J3DAPI rdCache_SendWireframeFaceListToHardware(size_t numPolys, rdCacheProcEntry* aPolys);

void J3DAPI rdCache_AddToTextureCache(tSystemTexture* pTexture, StdColorFormatType format);

D3DTLVERTEX* rdCache_GetVertexPointer(int index); // Added

// Helper hooking functions
void rdCache_InstallHooks(void);
void rdCache_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDCACHE_H
