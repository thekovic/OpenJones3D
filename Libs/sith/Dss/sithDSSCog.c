#include "sithDSSCog.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithDSSCog_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithDSSCog_SendMessage);
    // J3D_HOOKFUNC(sithDSSCog_ProcessMessage);
    // J3D_HOOKFUNC(sithDSSCog_SyncCogState);
    // J3D_HOOKFUNC(sithDSSCog_ProcessCogState);
}

void sithDSSCog_ResetGlobals(void)
{

}

signed int J3DAPI sithDSSCog_SendMessage(const SithCog* pCog, SithCogMsgType msgType, SithCogSymbolRefType senderType, int senderIdx, SithCogSymbolRefType srcType, int srcIdx, int linkId, int param0, int param1, int param2, int param3, DPID idTo)
{
    return J3D_TRAMPOLINE_CALL(sithDSSCog_SendMessage, pCog, msgType, senderType, senderIdx, srcType, srcIdx, linkId, param0, param1, param2, param3, idTo);
}

int J3DAPI sithDSSCog_ProcessMessage(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSCog_ProcessMessage, pMsg);
}

signed int J3DAPI sithDSSCog_SyncCogState(const SithCog* pCog, DPID idTO, unsigned int outstream)
{
    return J3D_TRAMPOLINE_CALL(sithDSSCog_SyncCogState, pCog, idTO, outstream);
}

int J3DAPI sithDSSCog_ProcessCogState(const SithMessage* pMsg)
{
    return J3D_TRAMPOLINE_CALL(sithDSSCog_ProcessCogState, pMsg);
}
