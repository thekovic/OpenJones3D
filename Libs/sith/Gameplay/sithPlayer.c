#include "sithPlayer.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithPlayer_awLocalPlayerName J3D_DECL_FAR_ARRAYVAR(sithPlayer_awLocalPlayerName, wchar_t(*)[64])

void sithPlayer_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithPlayer_Open);
    // J3D_HOOKFUNC(sithPlayer_Close);
    // J3D_HOOKFUNC(sithPlayer_GetLocalPlayerName);
    // J3D_HOOKFUNC(sithPlayer_PlacePlayers);
    // J3D_HOOKFUNC(sithPlayer_HidePlayer);
    // J3D_HOOKFUNC(sithPlayer_ShowPlayer);
    // J3D_HOOKFUNC(sithPlayer_SetLocalPlayer);
    // J3D_HOOKFUNC(sithPlayer_Reset);
    // J3D_HOOKFUNC(sithPlayer_Update);
    // J3D_HOOKFUNC(sithPlayer_NewPlayer);
    // J3D_HOOKFUNC(sithPlayer_GetPlayerNum);
    // J3D_HOOKFUNC(sithPlayer_PlayerKilledAction);
    // J3D_HOOKFUNC(sithPlayer_KillPlayer);
    // J3D_HOOKFUNC(sithPlayer_GetThingPlayerNum);
    // J3D_HOOKFUNC(sithPlayer_ToggleGuybrush);
    // J3D_HOOKFUNC(sithPlayer_IMPStartFiring);
    // J3D_HOOKFUNC(sithPlayer_IMPEndFiring);
}

void sithPlayer_ResetGlobals(void)
{
    int sithPlayer_g_bPlayerInPor_tmp = 1;
    memcpy(&sithPlayer_g_bPlayerInPor, &sithPlayer_g_bPlayerInPor_tmp, sizeof(sithPlayer_g_bPlayerInPor));
    
    int sithPlayer_g_impFireType_tmp = -1;
    memcpy(&sithPlayer_g_impFireType, &sithPlayer_g_impFireType_tmp, sizeof(sithPlayer_g_impFireType));
    
    memset(&sithPlayer_awLocalPlayerName, 0, sizeof(sithPlayer_awLocalPlayerName));
    memset(&sithPlayer_g_playerNum, 0, sizeof(sithPlayer_g_playerNum));
    memset(&sithPlayer_g_numPlayers, 0, sizeof(sithPlayer_g_numPlayers));
    memset(&sithPlayer_g_pLocalPlayerThing, 0, sizeof(sithPlayer_g_pLocalPlayerThing));
    memset(&sithPlayer_g_pLocalPlayer, 0, sizeof(sithPlayer_g_pLocalPlayer));
    memset(&sithPlayer_g_bPlayerInvulnerable, 0, sizeof(sithPlayer_g_bPlayerInvulnerable));
    memset(&sithPlayer_g_bInAetheriumSector, 0, sizeof(sithPlayer_g_bInAetheriumSector));
    memset(&sithPlayer_g_bGuybrush, 0, sizeof(sithPlayer_g_bGuybrush));
    memset(&sithPlayer_g_curLevelNum, 0, sizeof(sithPlayer_g_curLevelNum));
    memset(&sithPlayer_g_bBonusMapBought, 0, sizeof(sithPlayer_g_bBonusMapBought));
    memset(&sithPlayer_g_aPlayers, 0, sizeof(sithPlayer_g_aPlayers));
    memset(&sithPlayer_g_impState, 0, sizeof(sithPlayer_g_impState));
}

void J3DAPI sithPlayer_Open(const wchar_t* awName)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_Open, awName);
}

void sithPlayer_Close()
{
    J3D_TRAMPOLINE_CALL(sithPlayer_Close);
}

const wchar_t* J3DAPI sithPlayer_GetLocalPlayerName()
{
    return J3D_TRAMPOLINE_CALL(sithPlayer_GetLocalPlayerName);
}

void J3DAPI sithPlayer_PlacePlayers(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_PlacePlayers, pWorld);
}

void J3DAPI sithPlayer_HidePlayer(unsigned int playerNum)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_HidePlayer, playerNum);
}

int J3DAPI sithPlayer_ShowPlayer(size_t playerNum, DPID id)
{
    return J3D_TRAMPOLINE_CALL(sithPlayer_ShowPlayer, playerNum, id);
}

void J3DAPI sithPlayer_SetLocalPlayer(unsigned int playerNum)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_SetLocalPlayer, playerNum);
}

void J3DAPI sithPlayer_Reset(unsigned int playerNum)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_Reset, playerNum);
}

void J3DAPI sithPlayer_Update(SithPlayer* pPlayer, float secDetaTime)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_Update, pPlayer, secDetaTime);
}

void J3DAPI sithPlayer_NewPlayer(SithThing* pPlayer)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_NewPlayer, pPlayer);
}

int J3DAPI sithPlayer_GetPlayerNum(DPID playerId)
{
    return J3D_TRAMPOLINE_CALL(sithPlayer_GetPlayerNum, playerId);
}

void J3DAPI sithPlayer_PlayerKilledAction(SithThing* pPlayerThing, const SithThing* pSrcThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_PlayerKilledAction, pPlayerThing, pSrcThing);
}

void J3DAPI sithPlayer_KillPlayer(SithThing* pPlayerThing)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_KillPlayer, pPlayerThing);
}

int J3DAPI sithPlayer_GetThingPlayerNum(const SithThing* pThing)
{
    return J3D_TRAMPOLINE_CALL(sithPlayer_GetThingPlayerNum, pThing);
}

int J3DAPI sithPlayer_ToggleGuybrush()
{
    return J3D_TRAMPOLINE_CALL(sithPlayer_ToggleGuybrush);
}

void J3DAPI sithPlayer_IMPStartFiring(int fireType)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_IMPStartFiring, fireType);
}

void J3DAPI sithPlayer_IMPEndFiring(int fireType)
{
    J3D_TRAMPOLINE_CALL(sithPlayer_IMPEndFiring, fireType);
}
