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

static bool JonesControl_bStartup = false; // Added: Init to false

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
    int bMouseControl = wuRegistry_GetIntEx("Mouse Control", 0);
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();

    if ( JonesControl_bStartup )
    {
        return 1;
    }

    if ( sithControl_Startup(0) )
    {
        return 1;
    }

    // Note, instead of manually initializing the sithControl_DefaultInit could be called 
    // and unbind mouse controller afterwards
    sithControl_Reset();
    sithControl_g_controlOptions = 0x04;
    sithControl_RegisterKeyboardBindings();
    sithControl_RegisterJoystickBindings();
    // Note, sithControl_RegisterMouseBindings() is not called probably because jonesconfig would unbind it anyway

    if ( !pSettings->bWindowMode || bMouseControl )
    {
        stdControl_EnableMouse(1);
    }

    sithControl_RegisterControlCallback(sithPlayerControls_Process);
    sithControl_RegisterControlCallback(sithWeapon_ProcessWeaponControls);
    sithControl_RegisterControlCallback(JonesControl_ProcessControls);

    for ( size_t functionId = 0; functionId < SITHCONTROL_MAXFUNCTIONS; ++functionId )
    {
        sithControl_RegisterAxisFunction((SithControlFunction)functionId, SITHCONTROLFUNCTION_KEY);
    }

    int bJoystickControl = wuRegistry_GetIntEx("Joystick Control", 0);
    if ( bJoystickControl == 1 && stdControl_GetNumJoysticks() )
    {
        JonesControl_EnableJoystickAxes();
        sithControl_UnbindJoystickAxes();
    }

    wuRegistry_SaveIntEx("Joystick Control", bJoystickControl);

    if ( (sithMain_g_sith_mode.debugModeFlags & SITHDEBUG_INEDITOR) == 0 && (!pSettings->bWindowMode || bMouseControl) )
    {
        sithControl_UnbindMouseAxes();
    }

    JonesControl_bStartup = true;
    return 0;
}

void JonesControl_Shutdown(void)
{
    sithControl_Shutdown();
    JonesControl_bStartup = false;
}

int J3DAPI JonesControl_ProcessControls(SithThing* pPlayer, float secDeltaTime)
{
    J3D_UNUSED(secDeltaTime);

    if ( (pPlayer->thingInfo.actorInfo.flags & SITH_AF_CONTROLSDISABLED) != 0 || JonesConsole_g_bVisible )
    {
        return 0;
    }

    int numPressed = 0;
    sithControl_GetKey(SITHCONTROL_TALK, &numPressed); // F10 pressed
    if ( numPressed )
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
