#ifndef SITH_SITHAI_H
#define SITH_SITHAI_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>

#include <std/types.h>
#include <std/General/stdConffile.h>

J3D_EXTERN_C_START

#define sithAI_g_bOpen J3D_DECL_FAR_VAR(sithAI_g_bOpen, int)
// extern int sithAI_g_bOpen;

#define sithAI_g_aControlBlocks J3D_DECL_FAR_ARRAYVAR(sithAI_g_aControlBlocks, SithAIControlBlock(*)[256])
// extern SithAIControlBlock sithAI_g_aControlBlocks[256];

#define sithAI_g_lastUsedAIIndex J3D_DECL_FAR_VAR(sithAI_g_lastUsedAIIndex, int)
// extern int sithAI_g_lastUsedAIIndex;

int sithAI_Startup(void);
void J3DAPI sithAI_Shutdown();
void J3DAPI sithAI_Open();
void J3DAPI sithAI_Close();
void J3DAPI sithAI_Create(SithThing* pThing);
void J3DAPI sithAI_Free(SithThing* pThing);
int J3DAPI sithAI_Process();
void J3DAPI sithAI_ProcessAIState(SithAIControlBlock* pLocal);
unsigned int J3DAPI sithAI_InstinctUpdate(SithAIControlBlock* pLocal);
signed int J3DAPI sithAI_ForceInstinctUpdate(SithAIControlBlock* pLocal, const char* pInstinctName, int bSendModeChangeEvent);
void J3DAPI sithAI_EmitEvent(SithAIControlBlock* pLocal, SithAIEventType event, void* pObject);
int J3DAPI sithAI_ProcessBlockedEvent(SithAIControlBlock* pLocal, SithAIEventType aievent);
int J3DAPI sithAI_ProcessUnhandledEvent(SithAIControlBlock* pLocal, SithAIEventType event, void* pObject);
int J3DAPI sithAI_ProcessUnhandledWpntEvent(SithAIControlBlock* pLocal, SithAIEventType event);
void J3DAPI sithAI_Stop(SithThing* pThing);
void sithAI_StopAllAttackingAIs();
int J3DAPI sithAI_RegisterInstinct(char* pName, SithAIInstinctFunc pfInstinct, SithAIMode updateModes, SithAIMode updateBlockModes, SithAIEventType triggerEvents);
SithAIRegisteredInstinct* J3DAPI sithAI_FindInstinct(const char* pInstinctName);
int J3DAPI sithAI_GetInstinctIndex(const SithAIControlBlock* pLocal, const SithAIRegisteredInstinct* pRegInstinct);
BOOL J3DAPI sithAI_HasInstinct(const SithAIControlBlock* pLocal, const char* pName);
signed int J3DAPI sithAI_EnableInstinct(SithAIControlBlock* pLocal, const char* pInstinctName, int bEnable);
signed int J3DAPI sithAI_ParseArg(StdConffileArg* pArg, SithThing* pThing, int adjNum);
signed int J3DAPI sithAI_AllocAIFrames(SithAIControlBlock* pLocal, int sizeFrames);
int J3DAPI sithAI_CreateInstinctRegistry(unsigned int maxInstincts);
int J3DAPI sithAI_FreeAI(unsigned int aiNum);
int J3DAPI sithAI_CreateAI();
void J3DAPI sithAI_FreeAllAIs();

int J3DAPI sithAI_AIList(const SithConsoleCommand* pFunc, const char* pArg); //Added: From debug version
int J3DAPI sithAI_AIStatus(const SithConsoleCommand* pFunc, const char* pArg); //Added: From debug version

// Helper hooking functions
void sithAI_InstallHooks(void);
void sithAI_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHAI_H
