#ifndef SITH_SITHCOMM_H
#define SITH_SITHCOMM_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithMessage_g_localPlayerId J3D_DECL_FAR_VAR(sithMessage_g_localPlayerId, DPID)
// extern DPID sithMessage_g_localPlayerId;

#define sithMessage_g_outputstream J3D_DECL_FAR_VAR(sithMessage_g_outputstream, int)
// extern int sithMessage_g_outputstream;

#define sithMessage_g_inputstream J3D_DECL_FAR_VAR(sithMessage_g_inputstream, int)
// extern int sithMessage_g_inputstream;

// NOTE: all sithMessage functions should be in sithComm module
void sithMessage_Startup(void);
void sithMessage_Shutdown(void);
int J3DAPI sithMessage_SendMessage(SithMessage* pMessage, DPID idTo, unsigned int outstream, unsigned int dwDPFlags);
void sithMessage_ProcessMessages(void);
void sithMessage_StopProcessMessages(void);
DPID sithMessage_GetSenderID(void);
int J3DAPI sithMessage_NetWrite(const SithMessage* pMsg, DPID idTo, uint32_t dwDPFlags);
int J3DAPI sithMessage_ReceiveMessage(SithMessage* pMsg, DPID* pSender);
void sithMessage_CloseGame(void);
void J3DAPI sithMessage_CheckMembershipList(DPID idTo);
int J3DAPI sithMessage_ProcessCheckMembershipList(const SithMessage* pMsg);
void J3DAPI sithMessage_RegisterFunction(SithDSSType type, SithMessageProcessFunc pFunc);
int J3DAPI sithMessage_Process(const SithMessage* pMessage);
void sithMessage_InitMessageHandlers(void);
int J3DAPI sithMessage_FileWrite(const SithMessage* pMessage);

// Helper hooking functions
void sithComm_InstallHooks(void);
void sithComm_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOMM_H
