#ifndef SITH_SITHWHIP_H
#define SITH_SITHWHIP_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithWhip_UpdateWhipAim(SithThing* pThing);
signed int J3DAPI sithWhip_StartWhipSwing(SithThing* pThing);
void J3DAPI sithWhip_DeactivateWhip(SithThing* pThing);
int J3DAPI sithWhip_StartWhipClimb(SithThing* pThing, SithThing* pWhippedThing);
void J3DAPI sithWhip_SetActorWhipClimbIdle(SithThing* pThing);
void J3DAPI sithWhip_FinishWhipClimbDismount(SithThing* pThing);
void J3DAPI sithWhip_WhipClimbDismount(SithThing* pThing);
void J3DAPI sithWhip_ProcessWhipClimbMove(SithThing* pThing);
void J3DAPI sithWhip_WhipFirePuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType);
void J3DAPI sithWhip_WhipClimbPuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType);
void J3DAPI sithWhip_ClimbDismountPuppetCallback(SithThing* pThing, int track, rdKeyMarkerType mt);
SithThing* J3DAPI sithWhip_GetWhipSwingThing();
SithThing* J3DAPI sithWhip_GetWhipClimbThing();
void J3DAPI sithWhip_Reset();
int J3DAPI sithWhip_Save(DPID idTo, unsigned int outstream);
int J3DAPI sithWhip_Restore(const SithMessage* pMsg);
int J3DAPI sithWhip_SearchWhipSwingThing(SithThing* pThing);
int J3DAPI sithWhip_SearchWhipClimbThing(SithThing* pThing);
void J3DAPI sithWhip_CreatePlayerWhip(SithThing* pThing);
void J3DAPI sithWhip_RemoveWhip();

// Helper hooking functions
void sithWhip_InstallHooks(void);
void sithWhip_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHWHIP_H
