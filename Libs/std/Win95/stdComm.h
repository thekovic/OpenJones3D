#ifndef STD_STDCOMM_H
#define STD_STDCOMM_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI stdComm_Send(DPID idFrom, DPID idTo, LPVOID lpData, uint32_t dwDataSize, uint32_t dwFlags);
int J3DAPI stdComm_Receive(DPID* pSender, void* pData, size_t* pLength);
void stdComm_CloseGame(void);
int J3DAPI stdComm_RejoinSession(DPID* pPlayerId, const wchar_t* pPlayerName);
int J3DAPI stdComm_GetSessionSettings(StdCommGame* pSettings);
int stdComm_IsGameActive(void);
int stdComm_IsGameHost(void);
int J3DAPI stdComm_UpdatePlayers(size_t gameNum);
DPID J3DAPI stdComm_CreatePlayer(const wchar_t* pPlayerName);
void J3DAPI stdComm_DestroyPlayer(DPID playerId);
size_t J3DAPI stdComm_GetNumPlayers();
int J3DAPI stdComm_VerifyPlayer(DPID id);
DPID J3DAPI stdComm_GetPlayerID(size_t playerNum);
BOOL __stdcall stdComm_EnumPlayersCallback(DPID playerId, uint32_t dwPlayerType, LPCDPNAME lpName, uint32_t dwFlags, LPVOID lpContext);
int J3DAPI stdComm_ProcessSystemMessage(LPDPMSG_GENERIC pMessage, DPID* pSender);
void J3DAPI stdComm_SessionToSettings(LPDPSESSIONDESC2 pSession, StdCommGame* pSettings);
const char* J3DAPI stdComm_DPGetStatus(HRESULT code);

// Helper hooking functions
void stdComm_InstallHooks(void);
void stdComm_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCOMM_H
