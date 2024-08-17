#ifndef SITH_SITHAIAWARENESS_H
#define SITH_SITHAIAWARENESS_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithAIAwareness_g_aSectors J3D_DECL_FAR_VAR(sithAIAwareness_g_aSectors, SithAIAwarenessSector*)
// extern SithAIAwarenessSector *sithAIAwareness_g_aSectors;

void sithAIAwareness_Close();
int J3DAPI sithAIAwareness_CreateTransmittingEvent(SithSector* pSector, const rdVector3* pos, int type, float transmittingLevel, SithThing* pThing);
void J3DAPI sithAIAwareness_ProcessEvents();
int J3DAPI sithAIAwareness_Update(int msecTime, SithEventParams* pParams);
int J3DAPI sithAIAwareness_sub_4B0BE0(SithAIAwarenessSector* pAISector, int type, SithThing* pThing);
void J3DAPI sithAIAwareness_ProcessEvent(const SithAIAwarenessEvent* pEvent, const SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float levelAtTransmittingPos, const SithSurfaceAdjoin* pTargetAdjoin, SithThing* pThing);
float J3DAPI sithAIAwareness_CheckAdjoinDistance(const SithSurfaceAdjoin* pAdjoin, const rdVector3* startPos, rdVector3* pHitPos, float moveDistance);
signed int J3DAPI sithAIAwareness_CreateEvent(SithSector* pSector, const rdVector3* pos, int type, float levelAtTransmittingPos, SithThing* pThing);

// Helper hooking functions
void sithAIAwareness_InstallHooks(void);
void sithAIAwareness_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHAIAWARENESS_H
