#ifndef SITH_SITHDSS_H
#define SITH_SITHDSS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

int J3DAPI sithDSS_SurfaceStatus(const SithSurface* pSurf, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSurfaceStatus(const SithMessage* pMsg);
int J3DAPI sithDSS_SectorStatus(const SithSector* pSector, DPID a2, unsigned int outstream);
int J3DAPI sithDSS_SyncSeenSectors(DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSyncSeenSecors(const SithMessage* pMsg);
int J3DAPI sithDSS_ProcessSectorStatus(const SithMessage* pMsg);
int J3DAPI sithDSS_SectorFlags(const SithSector* pSector, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSectorFlags(const SithMessage* pMsg);
int J3DAPI sithDSS_AIStatus(const SithAIControlBlock* pLocal, DPID idTo, signed int outstream);
int J3DAPI sithDSS_ProcessAIStatus(const SithMessage* pMsg);
int J3DAPI sithDSS_Inventory(const SithThing* pThing, unsigned int inventoryId, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessInventory(const SithMessage* pMsg);
int J3DAPI sithDSS_AnimStatus(const SithAnimationSlot* pAnim, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessAnimStatus(const SithMessage* pMsg);
int J3DAPI sithDSS_PuppetStatus(const SithThing* pThing, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessPuppetStatus(const SithMessage* pMsg);
int J3DAPI sithDSS_SyncTaskEvents(const SithEvent* pEvent, DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSyncTaskEvents(const SithMessage* pMsg);
int J3DAPI sithDSS_SyncCameras(DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSyncCameras(const SithMessage* pMsg);
int J3DAPI sithDSS_SyncWorldState(DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessSyncWorldState(const SithMessage* pMsg);
int J3DAPI sithDSS_SyncVehicleControlState(DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_ProcessVehicleControlsState(const SithMessage* pMsg);
int J3DAPI sithDSS_sub_4B3760(DPID idTo, unsigned int outstream);
int J3DAPI sithDSS_sub_4B3790(const SithMessage* pMsg);

// Helper hooking functions
void sithDSS_InstallHooks(void);
void sithDSS_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHDSS_H
