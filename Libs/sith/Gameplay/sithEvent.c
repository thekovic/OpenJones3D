#include "sithEvent.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithEvent_aEventBuffer J3D_DECL_FAR_ARRAYVAR(sithEvent_aEventBuffer, SithEvent(*)[256])
#define sithEvent_aFreeEventBufferIdxs J3D_DECL_FAR_ARRAYVAR(sithEvent_aFreeEventBufferIdxs, int(*)[256])
#define sithEvent_aTasks J3D_DECL_FAR_ARRAYVAR(sithEvent_aTasks, SithEventTask(*)[5])
#define sithEvent_numFreeEventBuffers J3D_DECL_FAR_VAR(sithEvent_numFreeEventBuffers, int)
#define sithEvent_bEventStartup J3D_DECL_FAR_VAR(sithEvent_bEventStartup, int)
#define sithEvent_bOpen J3D_DECL_FAR_VAR(sithEvent_bOpen, int)

void sithEvent_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithEvent_Startup);
    // J3D_HOOKFUNC(sithEvent_Shutdown);
    // J3D_HOOKFUNC(sithEvent_Open);
    // J3D_HOOKFUNC(sithEvent_Close);
    // J3D_HOOKFUNC(sithEvent_Reset);
    // J3D_HOOKFUNC(sithEvent_CreateEvent);
    // J3D_HOOKFUNC(sithEvent_FreeEvent);
    // J3D_HOOKFUNC(sithEvent_AddTask);
    // J3D_HOOKFUNC(sithEvent_ProcessEvents);
    // J3D_HOOKFUNC(sithEvent_ResetFreeBufferTable);
    // J3D_HOOKFUNC(sithEvent_Create);
    // J3D_HOOKFUNC(sithEvent_AddEvent);
}

void sithEvent_ResetGlobals(void)
{
    memset(&sithEvent_aEventBuffer, 0, sizeof(sithEvent_aEventBuffer));
    memset(&sithEvent_aFreeEventBufferIdxs, 0, sizeof(sithEvent_aFreeEventBufferIdxs));
    memset(&sithEvent_aTasks, 0, sizeof(sithEvent_aTasks));
    memset(&sithEvent_numFreeEventBuffers, 0, sizeof(sithEvent_numFreeEventBuffers));
    memset(&sithEvent_g_pFirstQueuedEvent, 0, sizeof(sithEvent_g_pFirstQueuedEvent));
    memset(&sithEvent_bEventStartup, 0, sizeof(sithEvent_bEventStartup));
    memset(&sithEvent_bOpen, 0, sizeof(sithEvent_bOpen));
}

int sithEvent_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(sithEvent_Startup);
}

void J3DAPI sithEvent_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithEvent_Shutdown);
}

int J3DAPI sithEvent_Open()
{
    return J3D_TRAMPOLINE_CALL(sithEvent_Open);
}

void J3DAPI sithEvent_Close()
{
    J3D_TRAMPOLINE_CALL(sithEvent_Close);
}

void sithEvent_Reset(void)
{
    J3D_TRAMPOLINE_CALL(sithEvent_Reset);
}

int J3DAPI sithEvent_CreateEvent(unsigned int taskId, SithEventParams* params, int when)
{
    return J3D_TRAMPOLINE_CALL(sithEvent_CreateEvent, taskId, params, when);
}

int J3DAPI sithEvent_FreeEvent(SithEvent* pEvent)
{
    return J3D_TRAMPOLINE_CALL(sithEvent_FreeEvent, pEvent);
}

int J3DAPI sithEvent_AddTask(unsigned int taskId, SithEventProcess pfProcess, int frequency, SithEventTaskMode startMode)
{
    return J3D_TRAMPOLINE_CALL(sithEvent_AddTask, taskId, pfProcess, frequency, startMode);
}

void J3DAPI sithEvent_ProcessEvents()
{
    J3D_TRAMPOLINE_CALL(sithEvent_ProcessEvents);
}

void J3DAPI sithEvent_ResetFreeBufferTable()
{
    J3D_TRAMPOLINE_CALL(sithEvent_ResetFreeBufferTable);
}

SithEvent* J3DAPI sithEvent_Create()
{
    return J3D_TRAMPOLINE_CALL(sithEvent_Create);
}

void J3DAPI sithEvent_AddEvent(SithEvent* pEvent)
{
    J3D_TRAMPOLINE_CALL(sithEvent_AddEvent, pEvent);
}
