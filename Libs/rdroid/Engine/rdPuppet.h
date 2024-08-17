#ifndef RDROID_RDPUPPET_H
#define RDROID_RDPUPPET_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <rdroid/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

rdPuppet* J3DAPI rdPuppet_New(rdThing* pThing);
void J3DAPI rdPuppet_NewEntry(rdPuppet* pPuppet, rdThing* pThing);
void J3DAPI rdPuppet_Free(rdPuppet* pPuppet);
int J3DAPI rdPuppet_AddTrack(rdPuppet* pPuppet, rdKeyframe* pKFTrack, int lowPriority, int highPriority);
void J3DAPI rdPuppet_RemoveTrack(rdPuppet* pPuppet, int32_t track);
int J3DAPI rdPuppet_SetStatus(rdPuppet* pPuppet, int32_t track, rdPuppetTrackStatus status);
void J3DAPI rdPuppet_SetCallback(rdPuppet* pPuppet, int32_t track, rdPuppetTrackCallback pfCallback);
int J3DAPI rdPuppet_PlayTrack(rdPuppet* pPuppet, int32_t track);
int J3DAPI rdPuppet_FadeInTrack(rdPuppet* pPuppet, int32_t track, float speed);
int J3DAPI rdPuppet_FadeOutTrack(rdPuppet* pPuppet, int32_t track, float speed);
void J3DAPI rdPuppet_SetTrackSpeed(rdPuppet* pPuppet, int32_t track, float fps);
void J3DAPI rdPuppet_AdvanceTrack(rdPuppet* pPuppet, int32_t track, float frames);
int J3DAPI rdPuppet_UpdateTracks(rdPuppet* pPuppet, float secDeltaTime);
void J3DAPI rdPuppet_ResetTrack(rdPuppet* pPuppet, int32_t track);
void J3DAPI rdPuppet_BuildJointMatrices(rdThing* prdThing, const rdMatrix34* pPlacement);

// Helper hooking functions
void rdPuppet_InstallHooks(void);
void rdPuppet_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // RDROID_RDPUPPET_H
