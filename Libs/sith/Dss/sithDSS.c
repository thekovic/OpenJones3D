#include "sithDSS.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/Gameplay/sithVehicleControls.h>
#include <sith/Gameplay/sithWhip.h>
#include <sith/AI/sithAIMove.h>

#define sithDSS_aPuppetCallbacks J3D_DECL_FAR_ARRAYVAR(sithDSS_aPuppetCallbacks, rdPuppetTrackCallback(*)[7])

void sithDSS_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithDSS_SurfaceStatus);
    // J3D_HOOKFUNC(sithDSS_ProcessSurfaceStatus);
    // J3D_HOOKFUNC(sithDSS_SectorStatus);
    // J3D_HOOKFUNC(sithDSS_SyncSeenSectors);
    // J3D_HOOKFUNC(sithDSS_ProcessSyncSeenSecors);
    // J3D_HOOKFUNC(sithDSS_ProcessSectorStatus);
    // J3D_HOOKFUNC(sithDSS_SectorFlags);
    // J3D_HOOKFUNC(sithDSS_ProcessSectorFlags);
    // J3D_HOOKFUNC(sithDSS_AIStatus);
    // J3D_HOOKFUNC(sithDSS_ProcessAIStatus);
    // J3D_HOOKFUNC(sithDSS_Inventory);
    // J3D_HOOKFUNC(sithDSS_ProcessInventory);
    // J3D_HOOKFUNC(sithDSS_AnimStatus);
    // J3D_HOOKFUNC(sithDSS_ProcessAnimStatus);
    // J3D_HOOKFUNC(sithDSS_PuppetStatus);
    // J3D_HOOKFUNC(sithDSS_ProcessPuppetStatus);
    // J3D_HOOKFUNC(sithDSS_SyncTaskEvents);
    // J3D_HOOKFUNC(sithDSS_ProcessSyncTaskEvents);
    // J3D_HOOKFUNC(sithDSS_SyncCameras);
    // J3D_HOOKFUNC(sithDSS_ProcessSyncCameras);
    // J3D_HOOKFUNC(sithDSS_SyncWorldState);
    // J3D_HOOKFUNC(sithDSS_ProcessSyncWorldState);
    // J3D_HOOKFUNC(sithDSS_SyncVehicleControlState);
    // J3D_HOOKFUNC(sithDSS_ProcessVehicleControlsState);
    // J3D_HOOKFUNC(sithDSS_sub_4B3760);
    // J3D_HOOKFUNC(sithDSS_sub_4B3790);
}

void sithDSS_ResetGlobals(void)
{
    rdPuppetTrackCallback sithDSS_aPuppetCallbacks_tmp[7] = {
      &sithPuppet_DefaultCallback,
      &sithPlayerControls_PuppetCallback,
      &sithVehicleControls_PuppetCallback,
      &sithAIMove_PuppetCallback,
      &sithWhip_WhipClimbPuppetCallback,
      &sithWhip_ClimbDismountPuppetCallback,
      &sithWhip_WhipFirePuppetCallback
    };
    memcpy(&sithDSS_aPuppetCallbacks, &sithDSS_aPuppetCallbacks_tmp, sizeof(sithDSS_aPuppetCallbacks));
    
}

int J3DAPI sithDSS_SurfaceStatus(const SithSurface* pSurf, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SurfaceStatus, pSurf, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSurfaceStatus(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSurfaceStatus, pMsg);
}

int J3DAPI sithDSS_SectorStatus(const SithSector* pSector, DPID a2, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SectorStatus, pSector, a2, outstream);
}

int J3DAPI sithDSS_SyncSeenSectors(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SyncSeenSectors, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSyncSeenSecors(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSyncSeenSecors, pMsg);
}

int J3DAPI sithDSS_ProcessSectorStatus(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSectorStatus, pMsg);
}

int J3DAPI sithDSS_SectorFlags(const SithSector* pSector, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SectorFlags, pSector, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSectorFlags(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSectorFlags, pMsg);
}

int J3DAPI sithDSS_AIStatus(const SithAIControlBlock* pLocal, DPID idTo, signed int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_AIStatus, pLocal, idTo, outstream);
}

int J3DAPI sithDSS_ProcessAIStatus(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessAIStatus, pMsg);
}

int J3DAPI sithDSS_Inventory(const SithThing* pThing, unsigned int inventoryId, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_Inventory, pThing, inventoryId, idTo, outstream);
}

int J3DAPI sithDSS_ProcessInventory(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessInventory, pMsg);
}

int J3DAPI sithDSS_AnimStatus(const SithAnimationSlot* pAnim, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_AnimStatus, pAnim, idTo, outstream);
}

int J3DAPI sithDSS_ProcessAnimStatus(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessAnimStatus, pMsg);
}

int J3DAPI sithDSS_PuppetStatus(const SithThing* pThing, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_PuppetStatus, pThing, idTo, outstream);
}

int J3DAPI sithDSS_ProcessPuppetStatus(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessPuppetStatus, pMsg);
}

int J3DAPI sithDSS_SyncTaskEvents(const SithEvent* pEvent, DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SyncTaskEvents, pEvent, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSyncTaskEvents(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSyncTaskEvents, pMsg);
}

int J3DAPI sithDSS_SyncCameras(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SyncCameras, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSyncCameras(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSyncCameras, pMsg);
}

int J3DAPI sithDSS_SyncWorldState(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SyncWorldState, idTo, outstream);
}

int J3DAPI sithDSS_ProcessSyncWorldState(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessSyncWorldState, pMsg);
}

int J3DAPI sithDSS_SyncVehicleControlState(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_SyncVehicleControlState, idTo, outstream);
}

int J3DAPI sithDSS_ProcessVehicleControlsState(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_ProcessVehicleControlsState, pMsg);
}

int J3DAPI sithDSS_sub_4B3760(DPID idTo, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_sub_4B3760, idTo, outstream);
}

int J3DAPI sithDSS_sub_4B3790(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSS_sub_4B3790, pMsg);
}
