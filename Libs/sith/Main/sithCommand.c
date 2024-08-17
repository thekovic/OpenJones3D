#include "sithCommand.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCommand_aBuf J3D_DECL_FAR_ARRAYVAR(sithCommand_aBuf, char(*)[256])

void sithCommand_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCommand_Init);
    // J3D_HOOKFUNC(sithCommand_HandleDebugCommand);
    // J3D_HOOKFUNC(sithCommand_UrgonElsa);
    // J3D_HOOKFUNC(sithCommand_Fixme);
    // J3D_HOOKFUNC(sithCommand_AzerimSophia);
    // J3D_HOOKFUNC(sithCommand_Coords);
    // J3D_HOOKFUNC(sithCommand_PrintStatistics);
    // J3D_HOOKFUNC(sithCommand_PrintDynamicMem);
    // J3D_HOOKFUNC(sithCommand_MemDump);
    // J3D_HOOKFUNC(sithCommand_CipherText);
}

void sithCommand_ResetGlobals(void)
{
    memset(&sithCommand_aBuf, 0, sizeof(sithCommand_aBuf));
}

void J3DAPI sithCommand_Init()
{
    J3D_TRAMPOLINE_CALL(sithCommand_Init);
}

int J3DAPI sithCommand_HandleDebugCommand(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_HandleDebugCommand, pFunc, pArg);
}

int J3DAPI sithCommand_UrgonElsa(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_UrgonElsa, pFunc, pArg);
}

int J3DAPI sithCommand_Fixme(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_Fixme, pFunc, pArg);
}

int J3DAPI sithCommand_AzerimSophia(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_AzerimSophia, pFunc, pArg);
}

int J3DAPI sithCommand_Coords(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_Coords, pFunc, pArg);
}

int J3DAPI sithCommand_PrintStatistics(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_PrintStatistics, pFunc, pArg);
}

int J3DAPI sithCommand_PrintDynamicMem(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_PrintDynamicMem, pFunc, pArg);
}

int J3DAPI sithCommand_MemDump(const SithConsoleCommand* pFunc, const char* pArg)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_MemDump, pFunc, pArg);
}

// 
// function goes through all charecters of encrypted text and xor each char with 34 (22h)
// 
// def decrypt_cheat_text(enc_cheat):
//      cheat = ""
//      for c in enc_cheat:
//          cheat += chr(ord(c) ^ 34)
//      return cheat
char* J3DAPI sithCommand_CipherText(const char* pText)
{
    return J3D_TRAMPOLINE_CALL(sithCommand_CipherText, pText);
}
