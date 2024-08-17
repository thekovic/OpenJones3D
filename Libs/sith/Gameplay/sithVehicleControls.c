#include "sithVehicleControls.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithVehicleControls_curMineCarState J3D_DECL_FAR_VAR(sithVehicleControls_curMineCarState, SithMineCarControlState)
#define sithVehicleControls_curRaftState J3D_DECL_FAR_VAR(sithVehicleControls_curRaftState, SithRaftControlState)
#define sithVehicleControls_jeepSurfDrag J3D_DECL_FAR_VAR(sithVehicleControls_jeepSurfDrag, const float)
#define sithVehicleControls_jeepStaticDrag J3D_DECL_FAR_VAR(sithVehicleControls_jeepStaticDrag, const float)
#define sithVehicleControls_jeepMaxVelocity J3D_DECL_FAR_VAR(sithVehicleControls_jeepMaxVelocity, const float)
#define sithVehicleControls_jeepHeight J3D_DECL_FAR_VAR(sithVehicleControls_jeepHeight, const float)
#define sithVehicleControls_jeepMoveSize J3D_DECL_FAR_VAR(sithVehicleControls_jeepMoveSize, const float)
#define sithVehicleControls_jeepWheelRadius J3D_DECL_FAR_VAR(sithVehicleControls_jeepWheelRadius, float)
#define sithVehicleControls_raftRotThrust J3D_DECL_FAR_VAR(sithVehicleControls_raftRotThrust, float)
#define sithVehicleControls_dword_53B188 J3D_DECL_FAR_VAR(sithVehicleControls_dword_53B188, int)
#define sithVehicleControls_flt_586294 J3D_DECL_FAR_VAR(sithVehicleControls_flt_586294, float)
#define sithVehicleControls_bJeepStartMoveSndFxPlayed J3D_DECL_FAR_VAR(sithVehicleControls_bJeepStartMoveSndFxPlayed, int)
#define sithVehicleControls_raftStaticDrag J3D_DECL_FAR_VAR(sithVehicleControls_raftStaticDrag, float)
#define sithVehicleControls_raftRotSpeed J3D_DECL_FAR_VAR(sithVehicleControls_raftRotSpeed, float)

void sithVehicleControls_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithVehicleControls_GetMineCarControlState);
    // J3D_HOOKFUNC(sithVehicleControls_SetMineCarControlState);
    // J3D_HOOKFUNC(sithVehicleControls_GetRaftControlState);
    // J3D_HOOKFUNC(sithVehicleControls_SetRaftControlState);
    // J3D_HOOKFUNC(sithVehicleControls_PuppetCallback);
    // J3D_HOOKFUNC(sithVehicleControls_ProcessMineCarPlayerMove);
    // J3D_HOOKFUNC(sithVehicleControls_ProcessJeepPlayerMove);
    // J3D_HOOKFUNC(sithVehicleControls_PlayPuppetMode);
    // J3D_HOOKFUNC(sithVehicleControls_ProcessRaftPlayerMove);
    // J3D_HOOKFUNC(sithVehicleControls_FindRaftExitSurfacePos);
    // J3D_HOOKFUNC(sithVehicleControls_sub_4A5AE0);
    // J3D_HOOKFUNC(sithVehicleControls_FadeJeepMoveSounds);
    // J3D_HOOKFUNC(sithVehicleControls_CanMoveInDirection);
    // J3D_HOOKFUNC(sithVehicleControls_ExitRaft);
    // J3D_HOOKFUNC(sithVehicleControls_UpdateRaftPaddleSoundFx);
    // J3D_HOOKFUNC(sithVehicleControls_SendMessageUser0);
    // J3D_HOOKFUNC(sithVehicleControls_SendMessageUser1);
}

void sithVehicleControls_ResetGlobals(void)
{
    SithMineCarControlState sithVehicleControls_curMineCarState_tmp = { 0.0f, 0, 0.0f, -1, 0, 0, -1, 0u, 0.0f, 0.0f, 0 };
    memcpy(&sithVehicleControls_curMineCarState, &sithVehicleControls_curMineCarState_tmp, sizeof(sithVehicleControls_curMineCarState));
    
    SithRaftControlState sithVehicleControls_curRaftState_tmp = {
      SITHPLAYERMOVE_RAFT_STILL,
      SITHPUPPETSUBMODE_STAND,
      { { 0.0f }, { 0.0f }, { 0.0f } },
      { { 0.0f }, { 0.0f }, { 0.0f } },
      0.0f,
      0.0f,
      0,
      0.0f,
      0.0f
    };
    memcpy(&sithVehicleControls_curRaftState, &sithVehicleControls_curRaftState_tmp, sizeof(sithVehicleControls_curRaftState));
    
    const float sithVehicleControls_jeepSurfDrag_tmp = 2.0f;
    memcpy((float *)&sithVehicleControls_jeepSurfDrag, &sithVehicleControls_jeepSurfDrag_tmp, sizeof(sithVehicleControls_jeepSurfDrag));
    
    const float sithVehicleControls_jeepStaticDrag_tmp = 0.02f;
    memcpy((float *)&sithVehicleControls_jeepStaticDrag, &sithVehicleControls_jeepStaticDrag_tmp, sizeof(sithVehicleControls_jeepStaticDrag));
    
    const float sithVehicleControls_jeepMaxVelocity_tmp = 1.0f;
    memcpy((float *)&sithVehicleControls_jeepMaxVelocity, &sithVehicleControls_jeepMaxVelocity_tmp, sizeof(sithVehicleControls_jeepMaxVelocity));
    
    const float sithVehicleControls_jeepHeight_tmp = 0.18000001f;
    memcpy((float *)&sithVehicleControls_jeepHeight, &sithVehicleControls_jeepHeight_tmp, sizeof(sithVehicleControls_jeepHeight));
    
    const float sithVehicleControls_jeepMoveSize_tmp = 0.16500001f;
    memcpy((float *)&sithVehicleControls_jeepMoveSize, &sithVehicleControls_jeepMoveSize_tmp, sizeof(sithVehicleControls_jeepMoveSize));
    
    float sithVehicleControls_jeepWheelRadius_tmp = 0.037500001f;
    memcpy(&sithVehicleControls_jeepWheelRadius, &sithVehicleControls_jeepWheelRadius_tmp, sizeof(sithVehicleControls_jeepWheelRadius));
    
    float sithVehicleControls_raftRotThrust_tmp = 60.0f;
    memcpy(&sithVehicleControls_raftRotThrust, &sithVehicleControls_raftRotThrust_tmp, sizeof(sithVehicleControls_raftRotThrust));
    
    int sithVehicleControls_dword_53B188_tmp = -1;
    memcpy(&sithVehicleControls_dword_53B188, &sithVehicleControls_dword_53B188_tmp, sizeof(sithVehicleControls_dword_53B188));
    
    memset(&sithVehicleControls_flt_586294, 0, sizeof(sithVehicleControls_flt_586294));
    memset(&sithVehicleControls_g_bJeepForceStopped, 0, sizeof(sithVehicleControls_g_bJeepForceStopped));
    memset(&sithVehicleControls_g_bJeepAccMoveSndFxPlayed, 0, sizeof(sithVehicleControls_g_bJeepAccMoveSndFxPlayed));
    memset(&sithVehicleControls_bJeepStartMoveSndFxPlayed, 0, sizeof(sithVehicleControls_bJeepStartMoveSndFxPlayed));
    memset(&sithVehicleControls_raftStaticDrag, 0, sizeof(sithVehicleControls_raftStaticDrag));
    memset(&sithVehicleControls_raftRotSpeed, 0, sizeof(sithVehicleControls_raftRotSpeed));
}

SithMineCarControlState* J3DAPI sithVehicleControls_GetMineCarControlState()
{
    return J3D_TRAMPOLINE_CALL(sithVehicleControls_GetMineCarControlState);
}

void J3DAPI sithVehicleControls_SetMineCarControlState(SithMineCarControlState* pState)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_SetMineCarControlState, pState);
}

SithRaftControlState* J3DAPI sithVehicleControls_GetRaftControlState()
{
    return J3D_TRAMPOLINE_CALL(sithVehicleControls_GetRaftControlState);
}

void J3DAPI sithVehicleControls_SetRaftControlState(SithRaftControlState* pState)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_SetRaftControlState, pState);
}

void J3DAPI sithVehicleControls_PuppetCallback(SithThing* pThing, int track, rdKeyMarkerType markerType)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_PuppetCallback, pThing, track, markerType);
}

void J3DAPI sithVehicleControls_ProcessMineCarPlayerMove(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_ProcessMineCarPlayerMove, pThing, secDeltaTime);
}

void J3DAPI sithVehicleControls_ProcessJeepPlayerMove(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_ProcessJeepPlayerMove, pThing, secDeltaTime);
}

void J3DAPI sithVehicleControls_PlayPuppetMode(SithThing* pThing, SithPuppetSubMode submode)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_PlayPuppetMode, pThing, submode);
}

void J3DAPI sithVehicleControls_ProcessRaftPlayerMove(SithThing* pThing, float secDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_ProcessRaftPlayerMove, pThing, secDeltaTime);
}

int J3DAPI sithVehicleControls_FindRaftExitSurfacePos(SithThing* pThing, float moveDist, rdVector3* pOutPos, rdVector3* pOutPYR)
{
    return J3D_TRAMPOLINE_CALL(sithVehicleControls_FindRaftExitSurfacePos, pThing, moveDist, pOutPos, pOutPYR);
}

void J3DAPI sithVehicleControls_sub_4A5AE0(SithThing* pThing, void* a2, float moveDist)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_sub_4A5AE0, pThing, a2, moveDist);
}

void J3DAPI sithVehicleControls_FadeJeepMoveSounds(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_FadeJeepMoveSounds, pThing);
}

int J3DAPI sithVehicleControls_CanMoveInDirection(SithThing* pThing, rdVector3* pDir)
{
    return J3D_TRAMPOLINE_CALL(sithVehicleControls_CanMoveInDirection, pThing, pDir);
}

void J3DAPI sithVehicleControls_ExitRaft(SithThing* pRaftPlayer)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_ExitRaft, pRaftPlayer);
}

void J3DAPI sithVehicleControls_UpdateRaftPaddleSoundFx(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_UpdateRaftPaddleSoundFx, pThing);
}

int J3DAPI sithVehicleControls_SendMessageUser0(SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithVehicleControls_SendMessageUser0, pThing);
}

void J3DAPI sithVehicleControls_SendMessageUser1(SithThing* pThing)
{
    J3D_TRAMPOLINE_CALL(sithVehicleControls_SendMessageUser1, pThing);
}
