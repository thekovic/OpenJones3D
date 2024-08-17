#ifndef RDROID_RDKEYFRAME_H
#define RDROID_RDKEYFRAME_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

rdKeyframeLoadFunc J3DAPI rdKeyframe_RegisterLoader(rdKeyframeLoadFunc pFunc);
void J3DAPI rdKeyframe_NewEntry(rdKeyframe* pKeyframe);
int J3DAPI rdKeyframe_LoadEntry(const char* pFilename, rdKeyframe* pKeyframe);
void J3DAPI rdKeyframe_FreeEntry(rdKeyframe* pKeyfreame);

// Helper hooking functions
void rdKeyframe_InstallHooks(void);
void rdKeyframe_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDKEYFRAME_H
