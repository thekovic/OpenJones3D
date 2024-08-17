#include "sithWhip.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithWhip_vecCameraOffsetWhipClimbAim J3D_DECL_FAR_VAR(sithWhip_vecCameraOffsetWhipClimbAim, rdVector3)
#define sithWhip_vecCameraLookOffsetWhipClimbAim J3D_DECL_FAR_VAR(sithWhip_vecCameraLookOffsetWhipClimbAim, rdVector3)
#define sithWhip_vecCameraOffsetWhipSwingAim J3D_DECL_FAR_VAR(sithWhip_vecCameraOffsetWhipSwingAim, rdVector3)
#define sithWhip_vecCameraLookOffsetWhipSwingAim J3D_DECL_FAR_VAR(sithWhip_vecCameraLookOffsetWhipSwingAim, rdVector3)
#define sithWhip_pWhipThing J3D_DECL_FAR_VAR(sithWhip_pWhipThing, SithThing*)
#define sithWhip_pWhipSwingThing J3D_DECL_FAR_VAR(sithWhip_pWhipSwingThing, SithThing*)
#define sithWhip_pWhipClimbThing J3D_DECL_FAR_VAR(sithWhip_pWhipClimbThing, SithThing*)
#define sithWhip_bClimbDismountFinish J3D_DECL_FAR_VAR(sithWhip_bClimbDismountFinish, int)
#define sithWhip_bFoundWhipClimbThing J3D_DECL_FAR_VAR(sithWhip_bFoundWhipClimbThing, int)

void sithWhip_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithWhip_UpdateWhipAim);
    // J3D_HOOKFUNC(sithWhip_StartWhipSwing);
    // J3D_HOOKFUNC(sithWhip_DeactivateWhip);
    // J3D_HOOKFUNC(sithWhip_StartWhipClimb);
    // J3D_HOOKFUNC(sithWhip_SetActorWhipClimbIdle);
    // J3D_HOOKFUNC(sithWhip_FinishWhipClimbDismount);
    // J3D_HOOKFUNC(sithWhip_WhipClimbDismount);
    // J3D_HOOKFUNC(sithWhip_ProcessWhipClimbMove);
    // J3D_HOOKFUNC(sithWhip_WhipFirePuppetCallback);
    // J3D_HOOKFUNC(sithWhip_WhipClimbPuppetCallback);
    // J3D_HOOKFUNC(sithWhip_ClimbDismountPuppetCallback);
    // J3D_HOOKFUNC(sithWhip_GetWhipSwingThing);
    // J3D_HOOKFUNC(sithWhip_GetWhipClimbThing);
    // J3D_HOOKFUNC(sithWhip_Reset);
    // J3D_HOOKFUNC(sithWhip_Save);
    // J3D_HOOKFUNC(sithWhip_Restore);
    // J3D_HOOKFUNC(sithWhip_SearchWhipSwingThing);
    // J3D_HOOKFUNC(sithWhip_SearchWhipClimbThing);
    // J3D_HOOKFUNC(sithWhip_CreatePlayerWhip);
    // J3D_HOOKFUNC(sithWhip_RemoveWhip);
}

void sithWhip_ResetGlobals(void)
{
    rdVector3 sithWhip_vecCameraOffsetWhipClimbAim_tmp = { { 0.0f }, { -0.1f }, { 0.02f } };
    memcpy(&sithWhip_vecCameraOffsetWhipClimbAim, &sithWhip_vecCameraOffsetWhipClimbAim_tmp, sizeof(sithWhip_vecCameraOffsetWhipClimbAim));
    
    rdVector3 sithWhip_vecCameraLookOffsetWhipClimbAim_tmp = { { 0.0f }, { 0.039999999f }, { 0.15000001f } };
    memcpy(&sithWhip_vecCameraLookOffsetWhipClimbAim, &sithWhip_vecCameraLookOffsetWhipClimbAim_tmp, sizeof(sithWhip_vecCameraLookOffsetWhipClimbAim));
    
    rdVector3 sithWhip_vecCameraOffsetWhipSwingAim_tmp = { { 0.0f }, { -0.2f }, { 0.035f } };
    memcpy(&sithWhip_vecCameraOffsetWhipSwingAim, &sithWhip_vecCameraOffsetWhipSwingAim_tmp, sizeof(sithWhip_vecCameraOffsetWhipSwingAim));
    
    rdVector3 sithWhip_vecCameraLookOffsetWhipSwingAim_tmp = { { 0.0f }, { 0.02f }, { 0.02f } };
    memcpy(&sithWhip_vecCameraLookOffsetWhipSwingAim, &sithWhip_vecCameraLookOffsetWhipSwingAim_tmp, sizeof(sithWhip_vecCameraLookOffsetWhipSwingAim));
    
    memset(&sithWhip_pWhipThing, 0, sizeof(sithWhip_pWhipThing));
    memset(&sithWhip_pWhipSwingThing, 0, sizeof(sithWhip_pWhipSwingThing));
    memset(&sithWhip_pWhipClimbThing, 0, sizeof(sithWhip_pWhipClimbThing));
    memset(&sithWhip_bClimbDismountFinish, 0, sizeof(sithWhip_bClimbDismountFinish));
    memset(&sithWhip_bFoundWhipClimbThing, 0, sizeof(sithWhip_bFoundWhipClimbThing));
}

void J3DAPI sithWhip_UpdateWhipAim(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_UpdateWhipAim, pThing);
}

signed int J3DAPI sithWhip_StartWhipSwing(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_StartWhipSwing, pThing);
}

void J3DAPI sithWhip_DeactivateWhip(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_DeactivateWhip, pThing);
}

int J3DAPI sithWhip_StartWhipClimb(SithThing* pThing, SithThing* pWhippedThing)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_StartWhipClimb, pThing, pWhippedThing);
}

void J3DAPI sithWhip_SetActorWhipClimbIdle(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_SetActorWhipClimbIdle, pThing);
}

void J3DAPI sithWhip_FinishWhipClimbDismount(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_FinishWhipClimbDismount, pThing);
}

void J3DAPI sithWhip_WhipClimbDismount(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_WhipClimbDismount, pThing);
}

void J3DAPI sithWhip_ProcessWhipClimbMove(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_ProcessWhipClimbMove, pThing);
}

void J3DAPI sithWhip_WhipFirePuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    J3D_TRAMPOLINE_CALL(sithWhip_WhipFirePuppetCallback, pThing, track, markerType);
}

void J3DAPI sithWhip_WhipClimbPuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    J3D_TRAMPOLINE_CALL(sithWhip_WhipClimbPuppetCallback, pThing, track, markerType);
}

void J3DAPI sithWhip_ClimbDismountPuppetCallback(SithThing* pThing, int track, rdKeyMarkerType mt)
{
    J3D_TRAMPOLINE_CALL(sithWhip_ClimbDismountPuppetCallback, pThing, track, mt);
}

SithThing* J3DAPI sithWhip_GetWhipSwingThing()
{
    return J3D_TRAMPOLINE_CALL(sithWhip_GetWhipSwingThing);
}

SithThing* J3DAPI sithWhip_GetWhipClimbThing()
{
    return J3D_TRAMPOLINE_CALL(sithWhip_GetWhipClimbThing);
}

void J3DAPI sithWhip_Reset()
{
    J3D_TRAMPOLINE_CALL(sithWhip_Reset);
}

int J3DAPI sithWhip_Save(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_Save, idTo, outstream);
}

int J3DAPI sithWhip_Restore(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_Restore, pMsg);
}

int J3DAPI sithWhip_SearchWhipSwingThing(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_SearchWhipSwingThing, pThing);
}

int J3DAPI sithWhip_SearchWhipClimbThing(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithWhip_SearchWhipClimbThing, pThing);
}

void J3DAPI sithWhip_CreatePlayerWhip(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithWhip_CreatePlayerWhip, pThing);
}

void J3DAPI sithWhip_RemoveWhip()
{
    J3D_TRAMPOLINE_CALL(sithWhip_RemoveWhip);
}
