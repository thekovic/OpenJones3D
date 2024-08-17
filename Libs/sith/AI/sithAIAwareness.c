#include "sithAIAwareness.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithAIAwareness_aEvents J3D_DECL_FAR_ARRAYVAR(sithAIAwareness_aEvents, SithAIAwarenessEvent(*)[32])
#define sithAIAwareness_numEvents J3D_DECL_FAR_VAR(sithAIAwareness_numEvents, int)
#define sithAIAwareness_bOpened J3D_DECL_FAR_VAR(sithAIAwareness_bOpened, int)
#define sithAIAwareness_curProcessID J3D_DECL_FAR_VAR(sithAIAwareness_curProcessID, int)

void sithAIAwareness_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithAIAwareness_Close);
    // J3D_HOOKFUNC(sithAIAwareness_CreateTransmittingEvent);
    // J3D_HOOKFUNC(sithAIAwareness_ProcessEvents);
    // J3D_HOOKFUNC(sithAIAwareness_Update);
    // J3D_HOOKFUNC(sithAIAwareness_sub_4B0BE0);
    // J3D_HOOKFUNC(sithAIAwareness_ProcessEvent);
    // J3D_HOOKFUNC(sithAIAwareness_CheckAdjoinDistance);
    // J3D_HOOKFUNC(sithAIAwareness_CreateEvent);
}

void sithAIAwareness_ResetGlobals(void)
{
    memset(&sithAIAwareness_aEvents, 0, sizeof(sithAIAwareness_aEvents));
    memset(&sithAIAwareness_g_aSectors, 0, sizeof(sithAIAwareness_g_aSectors));
    memset(&sithAIAwareness_numEvents, 0, sizeof(sithAIAwareness_numEvents));
    memset(&sithAIAwareness_bOpened, 0, sizeof(sithAIAwareness_bOpened));
    memset(&sithAIAwareness_curProcessID, 0, sizeof(sithAIAwareness_curProcessID));
}

void sithAIAwareness_Close()
{
    J3D_TRAMPOLINE_CALL(sithAIAwareness_Close);
}

int J3DAPI sithAIAwareness_CreateTransmittingEvent(SithSector* pSector, const rdVector3* pos, int type, float transmittingLevel, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIAwareness_CreateTransmittingEvent, pSector, pos, type, transmittingLevel, pThing);
}

void J3DAPI sithAIAwareness_ProcessEvents()
{
    J3D_TRAMPOLINE_CALL(sithAIAwareness_ProcessEvents);
}

int J3DAPI sithAIAwareness_Update(int msecTime, SithEventParams* pParams)
{
    return J3D_TRAMPOLINE_CALL(sithAIAwareness_Update, msecTime, pParams);
}

int J3DAPI sithAIAwareness_sub_4B0BE0(SithAIAwarenessSector* pAISector, int type, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIAwareness_sub_4B0BE0, pAISector, type, pThing);
}

void J3DAPI sithAIAwareness_ProcessEvent(const SithAIAwarenessEvent* pEvent, const SithSector* pSector, const rdVector3* startPos, rdVector3* endPos, float levelAtTransmittingPos, const SithSurfaceAdjoin* pTargetAdjoin, SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithAIAwareness_ProcessEvent, pEvent, pSector, startPos, endPos, levelAtTransmittingPos, pTargetAdjoin, pThing);
}

float J3DAPI sithAIAwareness_CheckAdjoinDistance(const SithSurfaceAdjoin* pAdjoin, const rdVector3* startPos, rdVector3* pHitPos, float moveDistance)
{
    return J3D_TRAMPOLINE_CALL(sithAIAwareness_CheckAdjoinDistance, pAdjoin, startPos, pHitPos, moveDistance);
}

signed int J3DAPI sithAIAwareness_CreateEvent(SithSector* pSector, const rdVector3* pos, int type, float levelAtTransmittingPos, SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithAIAwareness_CreateEvent, pSector, pos, type, levelAtTransmittingPos, pThing);
}
