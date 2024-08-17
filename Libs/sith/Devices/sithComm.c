#include "sithComm.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithMessage_aTypeFuncs J3D_DECL_FAR_ARRAYVAR(sithMessage_aTypeFuncs, SithMessageProcessFunc(*)[65])
#define sithMessage_someMsg J3D_DECL_FAR_VAR(sithMessage_someMsg, SithMessage)
#define sithMessage_bSturtup J3D_DECL_FAR_VAR(sithMessage_bSturtup, int)
#define sithMessage_totalSentDataSize J3D_DECL_FAR_VAR(sithMessage_totalSentDataSize, size_t)
#define sithMessage_totalNetSent J3D_DECL_FAR_VAR(sithMessage_totalNetSent, size_t)
#define sithMessage_senderId J3D_DECL_FAR_VAR(sithMessage_senderId, DPID)
#define sithMessage_bStopProcessMessages J3D_DECL_FAR_VAR(sithMessage_bStopProcessMessages, int)

void sithComm_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithMessage_Startup);
    // J3D_HOOKFUNC(sithMessage_Shutdown);
    // J3D_HOOKFUNC(sithMessage_SendMessage);
    // J3D_HOOKFUNC(sithMessage_ProcessMessages);
    // J3D_HOOKFUNC(sithMessage_StopProcessMessages);
    // J3D_HOOKFUNC(sithMessage_GetSenderID);
    // J3D_HOOKFUNC(sithMessage_NetWrite);
    // J3D_HOOKFUNC(sithMessage_ReceiveMessage);
    // J3D_HOOKFUNC(sithMessage_CloseGame);
    // J3D_HOOKFUNC(sithMessage_CheckMembershipList);
    // J3D_HOOKFUNC(sithMessage_ProcessCheckMembershipList);
    // J3D_HOOKFUNC(sithMessage_RegisterFunction);
    // J3D_HOOKFUNC(sithMessage_Process);
    // J3D_HOOKFUNC(sithMessage_InitMessageHandlers);
    // J3D_HOOKFUNC(sithMessage_FileWrite);
}

void sithComm_ResetGlobals(void)
{
    memset(&sithMessage_aTypeFuncs, 0, sizeof(sithMessage_aTypeFuncs));
    memset(&sithMessage_someMsg, 0, sizeof(sithMessage_someMsg));
    memset(&sithMessage_g_localPlayerId, 0, sizeof(sithMessage_g_localPlayerId));
    memset(&sithMessage_g_outputstream, 0, sizeof(sithMessage_g_outputstream));
    memset(&sithMessage_g_inputstream, 0, sizeof(sithMessage_g_inputstream));
    memset(&sithMessage_bSturtup, 0, sizeof(sithMessage_bSturtup));
    memset(&sithMessage_totalSentDataSize, 0, sizeof(sithMessage_totalSentDataSize));
    memset(&sithMessage_totalNetSent, 0, sizeof(sithMessage_totalNetSent));
    memset(&sithMessage_senderId, 0, sizeof(sithMessage_senderId));
    memset(&sithMessage_bStopProcessMessages, 0, sizeof(sithMessage_bStopProcessMessages));
}

// NOTE: all sithMessage functions should be in sithComm module
void sithMessage_Startup(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_Startup);
}

void sithMessage_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_Shutdown);
}

int J3DAPI sithMessage_SendMessage(SithMessage* pMessage, DPID idTo, unsigned int outstream, unsigned int dwDPFlags)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_SendMessage, pMessage, idTo, outstream, dwDPFlags);
}

void sithMessage_ProcessMessages(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_ProcessMessages);
}

void sithMessage_StopProcessMessages(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_StopProcessMessages);
}

DPID sithMessage_GetSenderID(void)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_GetSenderID);
}

int J3DAPI sithMessage_NetWrite(const SithMessage* pMsg, DPID idTo, uint32_t dwDPFlags)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_NetWrite, pMsg, idTo, dwDPFlags);
}

int J3DAPI sithMessage_ReceiveMessage(SithMessage* pMsg, DPID* pSender)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_ReceiveMessage, pMsg, pSender);
}

void sithMessage_CloseGame(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_CloseGame);
}

void J3DAPI sithMessage_CheckMembershipList(DPID idTo)
{
    J3D_TRAMPOLINE_CALL(sithMessage_CheckMembershipList, idTo);
}

int J3DAPI sithMessage_ProcessCheckMembershipList(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_ProcessCheckMembershipList, pMsg);
}

void J3DAPI sithMessage_RegisterFunction(SithDSSType type, SithMessageProcessFunc pFunc)
{
    J3D_TRAMPOLINE_CALL(sithMessage_RegisterFunction, type, pFunc);
}

int J3DAPI sithMessage_Process(const SithMessage* pMessage)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_Process, pMessage);
}

void sithMessage_InitMessageHandlers(void)
{
    J3D_TRAMPOLINE_CALL(sithMessage_InitMessageHandlers);
}

int J3DAPI sithMessage_FileWrite(const SithMessage* pMessage)
{
    return J3D_TRAMPOLINE_CALL(sithMessage_FileWrite, pMessage);
}
