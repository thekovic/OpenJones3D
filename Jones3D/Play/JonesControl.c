#include "JonesControl.h"
#include <j3dcore/j3dhook.h>

#include <Jones3D/Display/JonesConfig.h>
#include <Jones3D/Display/JonesConsole.h>
#include <Jones3D/Main/JonesMain.h>
#include <Jones3D/RTI/symbols.h>

#include <sith/Devices/sithControl.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/World/sithWeapon.h>

#include <std/Win95/stdControl.h>
#include <w32util/wuRegistry.h>

#define JonesControl_bStartup J3D_DECL_FAR_VAR(JonesControl_bStartup, int)

void JonesControl_InstallHooks(void)
{
    J3D_HOOKFUNC(JonesControl_Startup);
    J3D_HOOKFUNC(JonesControl_Shutdown);
    J3D_HOOKFUNC(JonesControl_ProcessControls);
    J3D_HOOKFUNC(JonesControl_EnableJoystickAxes);
}

void JonesControl_ResetGlobals(void)
{

}

int JonesControl_Startup(void)
{
    int bMouseControl;
    JonesDisplaySettings* pSettings;
    int functionId;
    int bJoystickControl;

    bMouseControl = wuRegistry_GetIntEx("Mouse Control", 0);
    pSettings = JonesMain_GetDisplaySettings();

    if ( JonesControl_bStartup )
    {
        return 1;
    }

    if ( sithControl_Startup(0) )
    {
        return 1;
    }

    sithControl_Reset();
    jonesConfig_g_controlOptions = 4;
    sithControl_RegisterControlBindings();

    sithControl_GetNumJoystickDevices();        // ???

    if ( !pSettings->windowMode || bMouseControl )
    {
        stdControl_EnableMouse(1);
    }

    sithControl_RegisterControlCallback(sithPlayerControls_Process);
    sithControl_RegisterControlCallback(sithWeapon_ProcessWeaponControls);
    sithControl_RegisterControlCallback(JonesControl_ProcessControls);

    for ( functionId = 0; functionId < 58; ++functionId ) // This might be joystick controls? TODO: make macro or use existing
    {
        sithControl_RegisterAxisFunction((SithControlFunction)functionId, SITHCONTROLFUNCTION_KEY);
    }

    bJoystickControl = wuRegistry_GetIntEx("Joystick Control", 0);
    if ( bJoystickControl == 1 && stdControl_GetNumJoysticks() )
    {
        JonesControl_EnableJoystickAxes();
        sithControl_UnbindJoystickAxes();
    }

    wuRegistry_SaveIntEx("Joystick Control", bJoystickControl);

    if ( (sithMain_g_sith_mode.debugModeFlags & SITHDEBUG_INEDITOR) == 0 && (!pSettings->windowMode || bMouseControl) )
    {
        sithControl_UnbindMouseAxes();
    }

    JonesControl_bStartup = 1;

    return 0;
}

void JonesControl_Shutdown(void)
{
    sithControl_Shutdown();
    JonesControl_bStartup = 0;
}

int J3DAPI JonesControl_ProcessControls(SithThing* pPlayer, float secDeltaTime)
{
    J3D_UNUSED(secDeltaTime);

    if ( (pPlayer->thingInfo.actorInfo.flags & SITH_AF_CONTROLSDISABLED) != 0 || JonesConsole_g_bVisible )
    {
        return 0;
    }

    sithControl_GetKey(SITHCONTROL_TALK, (int*)&pPlayer);// F10 pressed, TODO: make new var for pPlayer
    if ( pPlayer )
    {
        JonesConsole_ShowConsole();
    }

    return 0;
}

void JonesControl_EnableJoystickAxes(void)
{
    int joystickCount = stdControl_GetNumJoysticks();
    if ( joystickCount > 0 )
    {
        int axisId = 2;
        do
        {
            stdControl_EnableAxis(axisId - 2);
            stdControl_EnableAxis(axisId - 1);
            stdControl_EnableAxis(axisId);
            stdControl_EnableAxis(axisId + 3);
            axisId += 6;
            --joystickCount;
        } while ( joystickCount );
    }
}
