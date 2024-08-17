#include "rdPuppet.h"
#include <j3dcore/j3dhook.h>
#include <rdroid/RTI/symbols.h>


void rdPuppet_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(rdPuppet_New);
    // J3D_HOOKFUNC(rdPuppet_NewEntry);
    // J3D_HOOKFUNC(rdPuppet_Free);
    // J3D_HOOKFUNC(rdPuppet_AddTrack);
    // J3D_HOOKFUNC(rdPuppet_RemoveTrack);
    // J3D_HOOKFUNC(rdPuppet_SetStatus);
    // J3D_HOOKFUNC(rdPuppet_SetCallback);
    // J3D_HOOKFUNC(rdPuppet_PlayTrack);
    // J3D_HOOKFUNC(rdPuppet_FadeInTrack);
    // J3D_HOOKFUNC(rdPuppet_FadeOutTrack);
    // J3D_HOOKFUNC(rdPuppet_SetTrackSpeed);
    // J3D_HOOKFUNC(rdPuppet_AdvanceTrack);
    // J3D_HOOKFUNC(rdPuppet_UpdateTracks);
    // J3D_HOOKFUNC(rdPuppet_ResetTrack);
    // J3D_HOOKFUNC(rdPuppet_BuildJointMatrices);
}

void rdPuppet_ResetGlobals(void)
{

}

rdPuppet* J3DAPI rdPuppet_New(rdThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_New, pThing);
}

void J3DAPI rdPuppet_NewEntry(rdPuppet* pPuppet, rdThing* pThing)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_NewEntry, pPuppet, pThing);
}

void J3DAPI rdPuppet_Free(rdPuppet* pPuppet)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_Free, pPuppet);
}

int J3DAPI rdPuppet_AddTrack(rdPuppet* pPuppet, rdKeyframe* pKFTrack, int lowPriority, int highPriority)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_AddTrack, pPuppet, pKFTrack, lowPriority, highPriority);
}

void J3DAPI rdPuppet_RemoveTrack(rdPuppet* pPuppet, int32_t track)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_RemoveTrack, pPuppet, track);
}

int J3DAPI rdPuppet_SetStatus(rdPuppet* pPuppet, int32_t track, rdPuppetTrackStatus status)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_SetStatus, pPuppet, track, status);
}

void J3DAPI rdPuppet_SetCallback(rdPuppet* pPuppet, int32_t track, rdPuppetTrackCallback pfCallback)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_SetCallback, pPuppet, track, pfCallback);
}

int J3DAPI rdPuppet_PlayTrack(rdPuppet* pPuppet, int32_t track)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_PlayTrack, pPuppet, track);
}

int J3DAPI rdPuppet_FadeInTrack(rdPuppet* pPuppet, int32_t track, float speed)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_FadeInTrack, pPuppet, track, speed);
}

int J3DAPI rdPuppet_FadeOutTrack(rdPuppet* pPuppet, int32_t track, float speed)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_FadeOutTrack, pPuppet, track, speed);
}

void J3DAPI rdPuppet_SetTrackSpeed(rdPuppet* pPuppet, int32_t track, float fps)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_SetTrackSpeed, pPuppet, track, fps);
}

void J3DAPI rdPuppet_AdvanceTrack(rdPuppet* pPuppet, int32_t track, float frames)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_AdvanceTrack, pPuppet, track, frames);
}

int J3DAPI rdPuppet_UpdateTracks(rdPuppet* pPuppet, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(rdPuppet_UpdateTracks, pPuppet, secDeltaTime);
}

void J3DAPI rdPuppet_ResetTrack(rdPuppet* pPuppet, int32_t track)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_ResetTrack, pPuppet, track);
}

void J3DAPI rdPuppet_BuildJointMatrices(rdThing* prdThing, const rdMatrix34* pPlacement)
{
    J3D_TRAMPOLINE_CALL(rdPuppet_BuildJointMatrices, prdThing, pPlacement);
}
