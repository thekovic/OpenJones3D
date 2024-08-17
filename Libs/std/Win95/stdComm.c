#include "stdComm.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdComm_aDPStatusTbl J3D_DECL_FAR_ARRAYVAR(stdComm_aDPStatusTbl, const DXStatus(*)[60])
#define stdComm_aPlayerInfos J3D_DECL_FAR_ARRAYVAR(stdComm_aPlayerInfos, StdCommPlayerInfo(*)[24])
#define stdComm_numPlayers J3D_DECL_FAR_VAR(stdComm_numPlayers, size_t)
#define stdComm_pDirectPlay J3D_DECL_FAR_VAR(stdComm_pDirectPlay, LPDIRECTPLAY4)
#define stdComm_bGameHost J3D_DECL_FAR_VAR(stdComm_bGameHost, int)
#define stdComm_aGames J3D_DECL_FAR_ARRAYVAR(stdComm_aGames, StdCommGame(*)[32])
#define stdComm_bGameActive J3D_DECL_FAR_VAR(stdComm_bGameActive, int)
#define stdComm_numGames J3D_DECL_FAR_VAR(stdComm_numGames, size_t)

void stdComm_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdComm_Send);
    // J3D_HOOKFUNC(stdComm_Receive);
    // J3D_HOOKFUNC(stdComm_CloseGame);
    // J3D_HOOKFUNC(stdComm_RejoinSession);
    // J3D_HOOKFUNC(stdComm_GetSessionSettings);
    // J3D_HOOKFUNC(stdComm_IsGameActive);
    // J3D_HOOKFUNC(stdComm_IsGameHost);
    // J3D_HOOKFUNC(stdComm_UpdatePlayers);
    // J3D_HOOKFUNC(stdComm_CreatePlayer);
    // J3D_HOOKFUNC(stdComm_DestroyPlayer);
    // J3D_HOOKFUNC(stdComm_GetNumPlayers);
    // J3D_HOOKFUNC(stdComm_VerifyPlayer);
    // J3D_HOOKFUNC(stdComm_GetPlayerID);
    // J3D_HOOKFUNC(stdComm_EnumPlayersCallback);
    // J3D_HOOKFUNC(stdComm_ProcessSystemMessage);
    // J3D_HOOKFUNC(stdComm_SessionToSettings);
    // J3D_HOOKFUNC(stdComm_DPGetStatus);
}

void stdComm_ResetGlobals(void)
{
    const DXStatus stdComm_aDPStatusTbl_tmp[60] = {
      { 0, "DP_OK" },
      { -2005467131, "DPERR_ALREADYINITIALIZED" },
      { -2005467126, "DPERR_ACCESSDENIED" },
      { -2005467116, "DPERR_ACTIVEPLAYERS" },
      { -2005467106, "DPERR_BUFFERTOOSMALL" },
      { -2005467096, "DPERR_CANTADDPLAYER" },
      { -2005467086, "DPERR_CANTCREATEGROUP" },
      { -2005467076, "DPERR_CANTCREATEPLAYER" },
      { -2005467066, "DPERR_CANTCREATESESSION" },
      { -2005467056, "DPERR_CAPSNOTAVAILABLEYET" },
      { -2005467046, "DPERR_EXCEPTION" },
      { -2147467259, "DPERR_GENERIC" },
      { -2005467016, "DPERR_INVALIDFLAGS" },
      { -2005467006, "DPERR_INVALIDOBJECT" },
      { -2147024809, "DPERR_INVALIDPARAM" },
      { -2147024809, "DPERR_INVALIDPARAMS" },
      { -2005466986, "DPERR_INVALIDPLAYER" },
      { -2005466981, "DPERR_INVALIDGROUP" },
      { -2005466976, "DPERR_NOCAPS" },
      { -2005466966, "DPERR_NOCONNECTION" },
      { -2147024882, "DPERR_NOMEMORY" },
      { -2147024882, "DPERR_OUTOFMEMORY" },
      { -2005466946, "DPERR_NOMESSAGES" },
      { -2005466936, "DPERR_NONAMESERVERFOUND" },
      { -2005466926, "DPERR_NOPLAYERS" },
      { -2005466916, "DPERR_NOSESSIONS" },
      { -2147483638, "DPERR_PENDING" },
      { -2005466906, "DPERR_SENDTOOBIG" },
      { -2005466896, "DPERR_TIMEOUT" },
      { -2005466886, "DPERR_UNAVAILABLE" },
      { -2147467263, "DPERR_UNSUPPORTED" },
      { -2005466866, "DPERR_BUSY" },
      { -2005466856, "DPERR_USERCANCEL" },
      { -2147467262, "DPERR_NOINTERFACE" },
      { -2005466846, "DPERR_CANNOTCREATESERVER" },
      { -2005466836, "DPERR_PLAYERLOST" },
      { -2005466826, "DPERR_SESSIONLOST" },
      { -2005466816, "DPERR_UNINITIALIZED" },
      { -2005466806, "DPERR_NONEWPLAYERS" },
      { -2005466796, "DPERR_INVALIDPASSWORD" },
      { -2005466786, "DPERR_CONNECTING" },
      { -2005466136, "DPERR_BUFFERTOOLARGE" },
      { -2005466126, "DPERR_CANTCREATEPROCESS" },
      { -2005466116, "DPERR_APPNOTSTARTED" },
      { -2005466106, "DPERR_INVALIDINTERFACE" },
      { -2005466096, "DPERR_NOSERVICEPROVIDER" },
      { -2005466086, "DPERR_UNKNOWNAPPLICATION" },
      { -2005466066, "DPERR_NOTLOBBIED" },
      { -2005466056, "DPERR_SERVICEPROVIDERLOADED" },
      { -2005466046, "DPERR_ALREADYREGISTERED" },
      { -2005466036, "DPERR_NOTREGISTERED" },
      { -2005465136, "DPERR_AUTHENTICATIONFAILED" },
      { -2005465126, "DPERR_CANTLOADSSPI" },
      { -2005465116, "DPERR_ENCRYPTIONFAILED" },
      { -2005465106, "DPERR_SIGNFAILED" },
      { -2005465096, "DPERR_CANTLOADSECURITYPACKAGE" },
      { -2005465086, "DPERR_ENCRYPTIONNOTSUPPORTED" },
      { -2005465076, "DPERR_CANTLOADCAPI" },
      { -2005465066, "DPERR_NOTLOGGEDIN" },
      { -2005465056, "DPERR_LOGONDENIED" }
    };
    memcpy((DXStatus *)&stdComm_aDPStatusTbl, &stdComm_aDPStatusTbl_tmp, sizeof(stdComm_aDPStatusTbl));
    
    memset(&stdComm_aPlayerInfos, 0, sizeof(stdComm_aPlayerInfos));
    memset(&stdComm_numPlayers, 0, sizeof(stdComm_numPlayers));
    memset(&stdComm_pDirectPlay, 0, sizeof(stdComm_pDirectPlay));
    memset(&stdComm_bGameHost, 0, sizeof(stdComm_bGameHost));
    memset(&stdComm_aGames, 0, sizeof(stdComm_aGames));
    memset(&stdComm_bGameActive, 0, sizeof(stdComm_bGameActive));
    memset(&stdComm_numGames, 0, sizeof(stdComm_numGames));
}

int J3DAPI stdComm_Send(DPID idFrom, DPID idTo, LPVOID lpData, uint32_t dwDataSize, uint32_t dwFlags)
{
    return J3D_TRAMPOLINE_CALL(stdComm_Send, idFrom, idTo, lpData, dwDataSize, dwFlags);
}

int J3DAPI stdComm_Receive(DPID* pSender, void* pData, size_t* pLength)
{
    return J3D_TRAMPOLINE_CALL(stdComm_Receive, pSender, pData, pLength);
}

void stdComm_CloseGame(void)
{
    J3D_TRAMPOLINE_CALL(stdComm_CloseGame);
}

int J3DAPI stdComm_RejoinSession(DPID* pPlayerId, const wchar_t* pPlayerName)
{
    return J3D_TRAMPOLINE_CALL(stdComm_RejoinSession, pPlayerId, pPlayerName);
}

int J3DAPI stdComm_GetSessionSettings(StdCommGame* pSettings)
{
    return J3D_TRAMPOLINE_CALL(stdComm_GetSessionSettings, pSettings);
}

int stdComm_IsGameActive(void)
{
    return J3D_TRAMPOLINE_CALL(stdComm_IsGameActive);
}

int stdComm_IsGameHost(void)
{
    return J3D_TRAMPOLINE_CALL(stdComm_IsGameHost);
}

int J3DAPI stdComm_UpdatePlayers(size_t gameNum)
{
    return J3D_TRAMPOLINE_CALL(stdComm_UpdatePlayers, gameNum);
}

DPID J3DAPI stdComm_CreatePlayer(const wchar_t* pPlayerName)
{
    return J3D_TRAMPOLINE_CALL(stdComm_CreatePlayer, pPlayerName);
}

void J3DAPI stdComm_DestroyPlayer(DPID playerId)
{
    J3D_TRAMPOLINE_CALL(stdComm_DestroyPlayer, playerId);
}

size_t J3DAPI stdComm_GetNumPlayers()
{
    return J3D_TRAMPOLINE_CALL(stdComm_GetNumPlayers);
}

int J3DAPI stdComm_VerifyPlayer(DPID id)
{
    return J3D_TRAMPOLINE_CALL(stdComm_VerifyPlayer, id);
}

DPID J3DAPI stdComm_GetPlayerID(size_t playerNum)
{
    return J3D_TRAMPOLINE_CALL(stdComm_GetPlayerID, playerNum);
}

BOOL __stdcall stdComm_EnumPlayersCallback(DPID playerId, uint32_t dwPlayerType, LPCDPNAME lpName, uint32_t dwFlags, LPVOID lpContext)
{
    return J3D_TRAMPOLINE_CALL(stdComm_EnumPlayersCallback, playerId, dwPlayerType, lpName, dwFlags, lpContext);
}

int J3DAPI stdComm_ProcessSystemMessage(LPDPMSG_GENERIC pMessage, DPID* pSender)
{
    return J3D_TRAMPOLINE_CALL(stdComm_ProcessSystemMessage, pMessage, pSender);
}

void J3DAPI stdComm_SessionToSettings(LPDPSESSIONDESC2 pSession, StdCommGame* pSettings)
{
    J3D_TRAMPOLINE_CALL(stdComm_SessionToSettings, pSession, pSettings);
}

const char* J3DAPI stdComm_DPGetStatus(HRESULT code)
{
    return J3D_TRAMPOLINE_CALL(stdComm_DPGetStatus, code);
}
