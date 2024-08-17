#ifndef SITH_SITHCOMMAND_H
#define SITH_SITHCOMMAND_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithCommand_Init();
int J3DAPI sithCommand_HandleDebugCommand(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_UrgonElsa(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_Fixme(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_AzerimSophia(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_Coords(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_PrintStatistics(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_PrintDynamicMem(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_MemDump(const SithConsoleCommand* pFunc, const char* pArg);
// 
// function goes through all charecters of encrypted text and xor each char with 34 (22h)
// 
// def decrypt_cheat_text(enc_cheat):
//      cheat = ""
//      for c in enc_cheat:
//          cheat += chr(ord(c) ^ 34)
//      return cheat
char* J3DAPI sithCommand_CipherText(const char* pText);

// Helper hooking functions
void sithCommand_InstallHooks(void);
void sithCommand_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOMMAND_H
