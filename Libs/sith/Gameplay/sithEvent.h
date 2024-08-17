#ifndef SITH_SITHEVENT_H
#define SITH_SITHEVENT_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithEvent_g_pFirstQueuedEvent J3D_DECL_FAR_VAR(sithEvent_g_pFirstQueuedEvent, SithEvent*)
// extern SithEvent *sithEvent_g_pFirstQueuedEvent;

int sithEvent_Startup(void);
void J3DAPI sithEvent_Shutdown();
int J3DAPI sithEvent_Open();
void J3DAPI sithEvent_Close();
void sithEvent_Reset(void);
int J3DAPI sithEvent_CreateEvent(unsigned int taskId, SithEventParams* params, int when);
int J3DAPI sithEvent_FreeEvent(SithEvent* pEvent);
int J3DAPI sithEvent_AddTask(unsigned int taskId, SithEventProcess pfProcess, int frequency, SithEventTaskMode startMode);
void J3DAPI sithEvent_ProcessEvents();
void J3DAPI sithEvent_ResetFreeBufferTable();
SithEvent* J3DAPI sithEvent_Create();
void J3DAPI sithEvent_AddEvent(SithEvent* pEvent);

// Helper hooking functions
void sithEvent_InstallHooks(void);
void sithEvent_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHEVENT_H
