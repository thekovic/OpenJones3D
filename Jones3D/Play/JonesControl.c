#include "JonesControl.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesControl_bStartup J3D_DECL_FAR_VAR(JonesControl_bStartup, int)

void JonesControl_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesControl_Startup);
    // J3D_HOOKFUNC(JonesControl_Shutdown);
    // J3D_HOOKFUNC(JonesControl_ProcessControls);
    // J3D_HOOKFUNC(JonesControl_EnableJoystickAxes);
}

void JonesControl_ResetGlobals(void)
{
    memset(&JonesControl_bStartup, 0, sizeof(JonesControl_bStartup));
}

int JonesControl_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(JonesControl_Startup);
}

void JonesControl_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesControl_Shutdown);
}

int J3DAPI JonesControl_ProcessControls(SithThing* pPlayer, float secDeltaTime)
{
    return J3D_TRAMPOLINE_CALL(JonesControl_ProcessControls, pPlayer, secDeltaTime);
}

void JonesControl_EnableJoystickAxes(void)
{
    J3D_TRAMPOLINE_CALL(JonesControl_EnableJoystickAxes);
}
