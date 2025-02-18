#include "sithMulti.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#include <sith/Devices/sithComm.h>
#include <sith/Dss/sithDSS.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithTime.h>

#define sithMulti_tickRate J3D_DECL_FAR_VAR(sithMulti_tickRate, size_t)
#define sithMulti_numUpdatedSurfaces J3D_DECL_FAR_VAR(sithMulti_numUpdatedSurfaces, int)
#define sithMulti_lastUpdateIdx J3D_DECL_FAR_VAR(sithMulti_lastUpdateIdx, int)
#define sithMulti_playerWelcomeState J3D_DECL_FAR_VAR(sithMulti_playerWelcomeState, int)
#define sithMulti_numUpdatedSectors J3D_DECL_FAR_VAR(sithMulti_numUpdatedSectors, int)
#define sithMulti_aRemovedStaticThings J3D_DECL_FAR_ARRAYVAR(sithMulti_aRemovedStaticThings, int(*)[256])
#define sithMulti_curWelcomePlayerNum J3D_DECL_FAR_VAR(sithMulti_curWelcomePlayerNum, unsigned int)
#define sithMulti_numUpdatedThings J3D_DECL_FAR_VAR(sithMulti_numUpdatedThings, int)
#define sithMulti_quitGameState J3D_DECL_FAR_VAR(sithMulti_quitGameState, int)
#define sithMulti_checksum J3D_DECL_FAR_VAR(sithMulti_checksum, int)
#define sithMulti_bWelcomingPlayer J3D_DECL_FAR_VAR(sithMulti_bWelcomingPlayer, int)
#define sithMulti_newPlayerId J3D_DECL_FAR_VAR(sithMulti_newPlayerId, DPID)
#define sithMulti_bSyncScores J3D_DECL_FAR_VAR(sithMulti_bSyncScores, int)
#define sithMulti_pfNewPlayerJoinedCallback J3D_DECL_FAR_VAR(sithMulti_pfNewPlayerJoinedCallback, SithMultiNewPlayerJoinedCallback)
#define sithMulti_msecPingStartTime J3D_DECL_FAR_VAR(sithMulti_msecPingStartTime, unsigned int)
#define sithMulti_msecQuitGameTime J3D_DECL_FAR_VAR(sithMulti_msecQuitGameTime, unsigned int)
#define sithMulti_numRemovedStaticThings J3D_DECL_FAR_VAR(sithMulti_numRemovedStaticThings, int)
#define sithMulti_msecLastSyncScoreTime J3D_DECL_FAR_VAR(sithMulti_msecLastSyncScoreTime, unsigned int)
#define sithMulti_msecWelcomeUpdateInterval J3D_DECL_FAR_VAR(sithMulti_msecWelcomeUpdateInterval, unsigned int)
#define sithMulti_dword_17F10EC J3D_DECL_FAR_VAR(sithMulti_dword_17F10EC, int)

void sithMulti_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithMulti_CloseGame);
    // J3D_HOOKFUNC(sithMulti_CheckPlayers);
    // J3D_HOOKFUNC(sithMulti_ProcessPlayerLost);
    // J3D_HOOKFUNC(sithMulti_RemovePlayer);
    // J3D_HOOKFUNC(sithMulti_SendWelcome);
    // J3D_HOOKFUNC(sithMulti_ProcessWelcome);
    // J3D_HOOKFUNC(sithMulti_ProcessPlayerJoin);
    // J3D_HOOKFUNC(sithMulti_SyncPlayers);
    // J3D_HOOKFUNC(sithMulti_ProcessSyncPlayers);
    // J3D_HOOKFUNC(sithMulti_ProcessJoinRequest);
    // J3D_HOOKFUNC(sithMulti_FinishJoining);
    // J3D_HOOKFUNC(sithMulti_ProcessChat);
    // J3D_HOOKFUNC(sithMulti_ProcessPing);
    // J3D_HOOKFUNC(sithMulti_ProcessPong);
    // J3D_HOOKFUNC(sithMulti_QuitPlayer);
    // J3D_HOOKFUNC(sithMulti_ProcessQuit);
    // J3D_HOOKFUNC(sithMulti_Update);
    // J3D_HOOKFUNC(sithMulti_SyncScores);
    J3D_HOOKFUNC(sithMulti_GetPlayerIndexByID);
    // J3D_HOOKFUNC(sithMulti_ProcessKilledPlayer);
    // J3D_HOOKFUNC(sithMulti_QuitGame);
    // J3D_HOOKFUNC(sithMulti_Respawn);
    // J3D_HOOKFUNC(sithMulti_RemoveStaticThing);
    // J3D_HOOKFUNC(sithMulti_UpdateSurfaces);
    // J3D_HOOKFUNC(sithMulti_UpdateSectors);
    // J3D_HOOKFUNC(sithMulti_UpdateThings);
    // J3D_HOOKFUNC(sithMulti_UpdateRemovals);
    // J3D_HOOKFUNC(sithMulti_StartWelcomingPlayer);
    // J3D_HOOKFUNC(sithMulti_StopWelcomingPlayer);
}

void sithMulti_ResetGlobals(void)
{
    int sithMulti_tickRate_tmp = 70;
    memcpy(&sithMulti_tickRate, &sithMulti_tickRate_tmp, sizeof(sithMulti_tickRate));

    memset(&sithMulti_numUpdatedSurfaces, 0, sizeof(sithMulti_numUpdatedSurfaces));
    memset(&sithMulti_lastUpdateIdx, 0, sizeof(sithMulti_lastUpdateIdx));
    memset(&sithMulti_playerWelcomeState, 0, sizeof(sithMulti_playerWelcomeState));
    memset(&sithMulti_numUpdatedSectors, 0, sizeof(sithMulti_numUpdatedSectors));
    memset(&sithMulti_aRemovedStaticThings, 0, sizeof(sithMulti_aRemovedStaticThings));
    memset(&sithMulti_curWelcomePlayerNum, 0, sizeof(sithMulti_curWelcomePlayerNum));
    memset(&sithMulti_numUpdatedThings, 0, sizeof(sithMulti_numUpdatedThings));
    memset(&sithMulti_quitGameState, 0, sizeof(sithMulti_quitGameState));
    memset(&sithMulti_checksum, 0, sizeof(sithMulti_checksum));
    memset(&sithMulti_bWelcomingPlayer, 0, sizeof(sithMulti_bWelcomingPlayer));
    memset(&sithMulti_newPlayerId, 0, sizeof(sithMulti_newPlayerId));
    memset(&sithMulti_bSyncScores, 0, sizeof(sithMulti_bSyncScores));
    memset(&sithMulti_pfNewPlayerJoinedCallback, 0, sizeof(sithMulti_pfNewPlayerJoinedCallback));
    memset(&sithMulti_msecPingStartTime, 0, sizeof(sithMulti_msecPingStartTime));
    memset(&sithMulti_msecQuitGameTime, 0, sizeof(sithMulti_msecQuitGameTime));
    memset(&sithMulti_numRemovedStaticThings, 0, sizeof(sithMulti_numRemovedStaticThings));
    memset(&sithMulti_msecLastSyncScoreTime, 0, sizeof(sithMulti_msecLastSyncScoreTime));
    memset(&sithMulti_msecWelcomeUpdateInterval, 0, sizeof(sithMulti_msecWelcomeUpdateInterval));
    memset(&sithMulti_g_serverId, 0, sizeof(sithMulti_g_serverId));
    memset(&sithMulti_dword_17F10EC, 0, sizeof(sithMulti_dword_17F10EC));
    memset(&sithMulti_g_message, 0, sizeof(sithMulti_g_message));
}

void sithMulti_CloseGame()
{
    J3D_TRAMPOLINE_CALL(sithMulti_CloseGame);
}

int J3DAPI sithMulti_CheckPlayers(int msecTime, SithEventParams* pParam)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_CheckPlayers, msecTime, pParam);
}

void J3DAPI sithMulti_ProcessPlayerLost(DPID idPlayer)
{
    J3D_TRAMPOLINE_CALL(sithMulti_ProcessPlayerLost, idPlayer);
}

void J3DAPI sithMulti_RemovePlayer(unsigned int playerNum)
{
    J3D_TRAMPOLINE_CALL(sithMulti_RemovePlayer, playerNum);
}

signed int J3DAPI sithMulti_SendWelcome(DPID idPlayer, int playerNum, DPID idTo)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_SendWelcome, idPlayer, playerNum, idTo);
}

int J3DAPI sithMulti_ProcessWelcome(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessWelcome, pMsg);
}

int J3DAPI sithMulti_ProcessPlayerJoin(int playerNum)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessPlayerJoin, playerNum);
}

void J3DAPI sithMulti_SyncPlayers(DPID idTo, uint32_t dpFlags)
{
    J3D_TRAMPOLINE_CALL(sithMulti_SyncPlayers, idTo, dpFlags);
}

signed int J3DAPI sithMulti_ProcessSyncPlayers(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessSyncPlayers, pMsg);
}

int J3DAPI sithMulti_ProcessJoinRequest(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessJoinRequest, pMsg);
}

signed int J3DAPI sithMulti_FinishJoining(SithMultiJoinStatus code, float arg4, int playerId)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_FinishJoining, code, arg4, playerId);
}

int J3DAPI sithMulti_ProcessChat(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessChat, pMsg);
}

int J3DAPI sithMulti_ProcessPing(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessPing, pMsg);
}

int J3DAPI sithMulti_ProcessPong(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessPong, pMsg);
}

int J3DAPI sithMulti_QuitPlayer(DPID id)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_QuitPlayer, id);
}

int J3DAPI sithMulti_ProcessQuit(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_ProcessQuit, pMsg);
}

void J3DAPI sithMulti_Update(int msecDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithMulti_Update, msecDeltaTime);
}

void J3DAPI sithMulti_SyncScores()
{
    J3D_TRAMPOLINE_CALL(sithMulti_SyncScores);
}

//int J3DAPI sithMulti_GetPlayerIndexByID(DPID idPlayer)
//{
//    return J3D_TRAMPOLINE_CALL(sithMulti_GetPlayerIndexByID, idPlayer);
//}

void J3DAPI sithMulti_ProcessKilledPlayer(const SithPlayer* pPlayer, const SithThing* pPlayerThing, const SithThing* pKiller)
{
    J3D_TRAMPOLINE_CALL(sithMulti_ProcessKilledPlayer, pPlayer, pPlayerThing, pKiller);
}

int J3DAPI sithMulti_QuitGame(unsigned int msecTime, int state)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_QuitGame, msecTime, state);
}

size_t J3DAPI sithMulti_Respawn(SithThing* pPlayer)
{
    return J3D_TRAMPOLINE_CALL(sithMulti_Respawn, pPlayer);
}

void J3DAPI sithMulti_RemoveStaticThing(int guid)
{
    J3D_TRAMPOLINE_CALL(sithMulti_RemoveStaticThing, guid);
}

void J3DAPI sithMulti_UpdateSurfaces()
{
    J3D_TRAMPOLINE_CALL(sithMulti_UpdateSurfaces);
}

void J3DAPI sithMulti_UpdateSectors()
{
    J3D_TRAMPOLINE_CALL(sithMulti_UpdateSectors);
}

void J3DAPI sithMulti_UpdateThings()
{
    J3D_TRAMPOLINE_CALL(sithMulti_UpdateThings);
}

void J3DAPI sithMulti_UpdateRemovals()
{
    J3D_TRAMPOLINE_CALL(sithMulti_UpdateRemovals);
}

void J3DAPI sithMulti_StartWelcomingPlayer(DPID playerId)
{
    J3D_TRAMPOLINE_CALL(sithMulti_StartWelcomingPlayer, playerId);
}

void J3DAPI sithMulti_StopWelcomingPlayer(int bError)
{
    J3D_TRAMPOLINE_CALL(sithMulti_StopWelcomingPlayer, bError);
}

void sithMulti_OpenGame(void)
{
    // TODO: Add implementation
    SITH_ASSERT(0);
}

size_t J3DAPI sithMulti_GetTickRate(void)
{
    return sithMulti_tickRate;
}

void J3DAPI sithMulti_SetTickRate(size_t tickRate)
{
    sithMulti_tickRate = tickRate;
}

int J3DAPI sithMulti_Ping(DPID idTo)
{
    sithMulti_msecPingStartTime = sithTime_g_msecGameTime;

    SITHDSS_STARTOUT(SITHDSS_PING);
    SITHDSS_PUSHUINT32(sithTime_g_msecGameTime);
    SITHDSS_ENDOUT;
    return sithMessage_SendMessage(&sithMulti_g_message, idTo, 1u, 0);
}

int J3DAPI sithMulti_GetPlayerIndexByID(int playerID)
{
    for ( size_t i = 0; i < sithPlayer_g_numPlayers; ++i )
    {
        if ( playerID == sithPlayer_g_aPlayers[i].playerNetId )
        {
            return i;
        }
    }

    return -1;
}