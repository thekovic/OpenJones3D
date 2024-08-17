#include "sithControl.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithControl_aFunctionNames J3D_DECL_FAR_ARRAYVAR(sithControl_aFunctionNames, char*(*)[59])
#define sithControl_numControlCallbacks J3D_DECL_FAR_VAR(sithControl_numControlCallbacks, int)
#define sithControl_aControlCallbacks J3D_DECL_FAR_ARRAYVAR(sithControl_aControlCallbacks, SithControlCallback(*)[32])
#define sithControl_aControlFlags J3D_DECL_FAR_ARRAYVAR(sithControl_aControlFlags, SithControlFunctionFlag(*)[58])
#define sithControl_aControlBindings J3D_DECL_FAR_ARRAYVAR(sithControl_aControlBindings, SithControlFunctionBinding(*)[58])
#define sithControl_msecIdleTime J3D_DECL_FAR_VAR(sithControl_msecIdleTime, unsigned int)
#define sithControl_bControlOpen J3D_DECL_FAR_VAR(sithControl_bControlOpen, int)

void sithControl_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithControl_Startup);
    // J3D_HOOKFUNC(sithControl_Shutdown);
    // J3D_HOOKFUNC(sithControl_Open);
    // J3D_HOOKFUNC(sithControl_Close);
    // J3D_HOOKFUNC(sithControl_RegisterAxisFunction);
    // J3D_HOOKFUNC(sithControl_RegisterKeyFunction);
    // J3D_HOOKFUNC(sithControl_BindControl);
    // J3D_HOOKFUNC(sithControl_BindAxis);
    // J3D_HOOKFUNC(sithControl_Unbind);
    // J3D_HOOKFUNC(sithControl_UnbindIndex);
    // J3D_HOOKFUNC(sithControl_RemoveAllControlBindings);
    // J3D_HOOKFUNC(sithControl_RegisterControlCallback);
    // J3D_HOOKFUNC(sithControl_Update);
    // J3D_HOOKFUNC(sithControl_GetKeyAsAxis);
    // J3D_HOOKFUNC(sithControl_GetAxis);
    // J3D_HOOKFUNC(sithControl_GetKey);
    // J3D_HOOKFUNC(sithControl_ReadControls);
    // J3D_HOOKFUNC(sithControl_UnbindJoystickAxes);
    // J3D_HOOKFUNC(sithControl_UnbindMouseAxes);
    // J3D_HOOKFUNC(sithControl_Reset);
    // J3D_HOOKFUNC(sithControl_RegisterKeyFunctions);
    // J3D_HOOKFUNC(sithControl_RegisterControlBindings);
    // J3D_HOOKFUNC(sithControl_GetNumJoystickDevices);
}

void sithControl_ResetGlobals(void)
{
    char *sithControl_aFunctionNames_tmp[59] = {
      "FORWARD",
      "BACK",
      "LEFT",
      "RIGHT",
      "TURNLEFT",
      "TURNRIGHT",
      "JUMP",
      "CRAWLTOGGLE",
      "ACT1",
      "FIRE1",
      "ACTIVATE",
      "ACT2",
      "ACT3",
      "NEXTWEAP",
      "PREVWEAP",
      "LIGHTERTOG",
      "LOOK",
      "STPLEFT",
      "STPRIGHT",
      "WEAPONTOG",
      "WSELECT0",
      "WSELECT1",
      "WSELECT2",
      "WSELECT3",
      "WSELECT4",
      "WSELECT5",
      "WSELECT6",
      "WSELECT7",
      "WSELECT8",
      "WSELECT9",
      "WSELECT10",
      "WSELECT11",
      "WSELECT12",
      "WSELECT13",
      "WSELECT14",
      "WSELECT15",
      "WSELECT16",
      "USEINV",
      "GAMESAVE",
      "DEBUG",
      "NEXTWEAPON",
      "PREVWEAPON",
      "MAP",
      "INCREASE",
      "DECREASE",
      "CAMERAMODE",
      "TALK",
      "SCREENSHOT",
      "CAMERAZOOMIN",
      "CAMERAZOOMOUT",
      "PITCH",
      "CENTER",
      "MLOOK",
      "MOUSETURN",
      "GAMMA",
      "RUNFWD",
      "HEALTH",
      "CHALK",
      "MAXFUNCTIONS"
    };
    memcpy(&sithControl_aFunctionNames, &sithControl_aFunctionNames_tmp, sizeof(sithControl_aFunctionNames));
    
    memset(&sithControl_numControlCallbacks, 0, sizeof(sithControl_numControlCallbacks));
    memset(&sithControl_aControlCallbacks, 0, sizeof(sithControl_aControlCallbacks));
    memset(&sithControl_aControlFlags, 0, sizeof(sithControl_aControlFlags));
    memset(&sithControl_aControlBindings, 0, sizeof(sithControl_aControlBindings));
    memset(&sithControl_msecIdleTime, 0, sizeof(sithControl_msecIdleTime));
    memset(&sithControl_g_bControlStartup, 0, sizeof(sithControl_g_bControlStartup));
    memset(&sithControl_bControlOpen, 0, sizeof(sithControl_bControlOpen));
}

int J3DAPI sithControl_Startup(int bKeyboardForeground)
{
    return J3D_TRAMPOLINE_CALL(sithControl_Startup, bKeyboardForeground);
}

void J3DAPI sithControl_Shutdown()
{
    J3D_TRAMPOLINE_CALL(sithControl_Shutdown);
}

int J3DAPI sithControl_Open()
{
    return J3D_TRAMPOLINE_CALL(sithControl_Open);
}

int J3DAPI sithControl_Close()
{
    return J3D_TRAMPOLINE_CALL(sithControl_Close);
}

void J3DAPI sithControl_RegisterAxisFunction(SithControlFunction functionId, SithControlFunctionFlag flag)
{
    J3D_TRAMPOLINE_CALL(sithControl_RegisterAxisFunction, functionId, flag);
}

void J3DAPI sithControl_RegisterKeyFunction(SithControlFunction functionId)
{
    J3D_TRAMPOLINE_CALL(sithControl_RegisterKeyFunction, functionId);
}

void J3DAPI sithControl_BindControl(SithControlFunction functionId, unsigned int controlId, SithControlBindFlag flags)
{
    J3D_TRAMPOLINE_CALL(sithControl_BindControl, functionId, controlId, flags);
}

SithControlBinding* J3DAPI sithControl_BindAxis(SithControlFunction functionId, int controlId, SithControlBindFlag flags)
{
    return J3D_TRAMPOLINE_CALL(sithControl_BindAxis, functionId, controlId, flags);
}

void J3DAPI sithControl_Unbind(SithControlFunction fctnID)
{
    J3D_TRAMPOLINE_CALL(sithControl_Unbind, fctnID);
}

void J3DAPI sithControl_UnbindIndex(int funcId, int bindIndex)
{
    J3D_TRAMPOLINE_CALL(sithControl_UnbindIndex, funcId, bindIndex);
}

void J3DAPI sithControl_RemoveAllControlBindings(SithControlBindFlag flags, int controlId)
{
    J3D_TRAMPOLINE_CALL(sithControl_RemoveAllControlBindings, flags, controlId);
}

int J3DAPI sithControl_RegisterControlCallback(SithControlCallback pfCallback)
{
    return J3D_TRAMPOLINE_CALL(sithControl_RegisterControlCallback, pfCallback);
}

void J3DAPI sithControl_Update(float secDeltaTime, int msecDeltaTime)
{
    J3D_TRAMPOLINE_CALL(sithControl_Update, secDeltaTime, msecDeltaTime);
}

float J3DAPI sithControl_GetKeyAsAxis(SithControlFunction asixId)
{
    return J3D_TRAMPOLINE_CALL(sithControl_GetKeyAsAxis, asixId);
}

float J3DAPI sithControl_GetAxis(SithControlFunction axisId)
{
    return J3D_TRAMPOLINE_CALL(sithControl_GetAxis, axisId);
}

int J3DAPI sithControl_GetKey(SithControlFunction keyId, int* pState)
{
    return J3D_TRAMPOLINE_CALL(sithControl_GetKey, keyId, pState);
}

void sithControl_ReadControls(void)
{
    J3D_TRAMPOLINE_CALL(sithControl_ReadControls);
}

void J3DAPI sithControl_UnbindJoystickAxes()
{
    J3D_TRAMPOLINE_CALL(sithControl_UnbindJoystickAxes);
}

int J3DAPI sithControl_UnbindMouseAxes()
{
    return J3D_TRAMPOLINE_CALL(sithControl_UnbindMouseAxes);
}

void J3DAPI sithControl_Reset()
{
    J3D_TRAMPOLINE_CALL(sithControl_Reset);
}

void J3DAPI sithControl_RegisterKeyFunctions()
{
    J3D_TRAMPOLINE_CALL(sithControl_RegisterKeyFunctions);
}

void J3DAPI sithControl_RegisterControlBindings()
{
    J3D_TRAMPOLINE_CALL(sithControl_RegisterControlBindings);
}

int J3DAPI sithControl_GetNumJoystickDevices()
{
    return J3D_TRAMPOLINE_CALL(sithControl_GetNumJoystickDevices);
}
