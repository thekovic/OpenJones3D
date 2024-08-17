#include "sithTime.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithTime_msecPauseStartTime J3D_DECL_FAR_VAR(sithTime_msecPauseStartTime, unsigned int)

void sithTime_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithTime_Advance);
    // J3D_HOOKFUNC(sithTime_Pause);
    // J3D_HOOKFUNC(sithTime_Resume);
    // J3D_HOOKFUNC(sithTime_Reset);
    // J3D_HOOKFUNC(sithTime_SetGameTime);
    // J3D_HOOKFUNC(sithTime_IsPaused);
}

void sithTime_ResetGlobals(void)
{
    memset(&sithTime_g_frameTimeFlex, 0, sizeof(sithTime_g_frameTimeFlex));
    memset(&sithTime_g_secFrameTime, 0, sizeof(sithTime_g_secFrameTime));
    memset(&sithTime_g_fps, 0, sizeof(sithTime_g_fps));
    memset(&sithTime_g_msecGameTime, 0, sizeof(sithTime_g_msecGameTime));
    memset(&sithTime_g_secGameTime, 0, sizeof(sithTime_g_secGameTime));
    memset(&sithTime_g_clockTime, 0, sizeof(sithTime_g_clockTime));
    memset(&sithTime_g_bPaused, 0, sizeof(sithTime_g_bPaused));
    memset(&sithTime_msecPauseStartTime, 0, sizeof(sithTime_msecPauseStartTime));
}

int sithTime_Advance(void)
{
    return J3D_TRAMPOLINE_CALL(sithTime_Advance);
}

void sithTime_Pause(void)
{
    J3D_TRAMPOLINE_CALL(sithTime_Pause);
}

void sithTime_Resume(void)
{
    J3D_TRAMPOLINE_CALL(sithTime_Resume);
}

void sithTime_Reset(void)
{
    J3D_TRAMPOLINE_CALL(sithTime_Reset);
}

void J3DAPI sithTime_SetGameTime(int msecTime)
{
    J3D_TRAMPOLINE_CALL(sithTime_SetGameTime, msecTime);
}

int J3DAPI sithTime_IsPaused()
{
    return J3D_TRAMPOLINE_CALL(sithTime_IsPaused);
}
