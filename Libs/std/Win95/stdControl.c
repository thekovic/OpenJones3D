#include "stdControl.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdControl_aDIStatusTbl J3D_DECL_FAR_ARRAYVAR(stdControl_aDIStatusTbl, const DXStatus(*)[34])
#define stdControl_bReadMouse J3D_DECL_FAR_VAR(stdControl_bReadMouse, int)
#define stdControl_secFPS J3D_DECL_FAR_VAR(stdControl_secFPS, float)
#define stdControl_msecFPS J3D_DECL_FAR_VAR(stdControl_msecFPS, float)
#define stdControl_aJoystickDevices J3D_DECL_FAR_ARRAYVAR(stdControl_aJoystickDevices, StdControlJoystickDevice(*)[8])
#define stdControl_cursorDisplayCounter J3D_DECL_FAR_VAR(stdControl_cursorDisplayCounter, int)
#define stdControl_aKeyboardState J3D_DECL_FAR_ARRAYVAR(stdControl_aKeyboardState, uint8_t(*)[256])
#define stdControl_aAxisPos J3D_DECL_FAR_ARRAYVAR(stdControl_aAxisPos, int(*)[51])
#define stdControl_keyboard J3D_DECL_FAR_VAR(stdControl_keyboard, StdInputDevice)
#define stdControl_aKeyIdleTimes J3D_DECL_FAR_ARRAYVAR(stdControl_aKeyIdleTimes, int(*)[644])
#define stdControl_aKeyInfos J3D_DECL_FAR_ARRAYVAR(stdControl_aKeyInfos, int(*)[644])
#define stdControl_aAxes J3D_DECL_FAR_ARRAYVAR(stdControl_aAxes, StdControlAxis(*)[51])
#define stdControl_mouse J3D_DECL_FAR_VAR(stdControl_mouse, StdInputDevice)
#define stdControl_mousePos J3D_DECL_FAR_VAR(stdControl_mousePos, POINT)
#define stdControl_aKeyPressCounter J3D_DECL_FAR_ARRAYVAR(stdControl_aKeyPressCounter, int(*)[644])
#define stdControl_bStartup J3D_DECL_FAR_VAR(stdControl_bStartup, int)
#define stdControl_bOpen J3D_DECL_FAR_VAR(stdControl_bOpen, int)
#define stdControl_bControlsIdle J3D_DECL_FAR_VAR(stdControl_bControlsIdle, int)
#define stdControl_bControlsActive J3D_DECL_FAR_VAR(stdControl_bControlsActive, int)
#define stdControl_pDI J3D_DECL_FAR_VAR(stdControl_pDI, LPDIRECTINPUTA)
#define stdControl_bMouseSensitivityEnabled J3D_DECL_FAR_VAR(stdControl_bMouseSensitivityEnabled, int)
#define stdControl_bReadJoysticks J3D_DECL_FAR_VAR(stdControl_bReadJoysticks, int)
#define stdControl_numJoystickDevices J3D_DECL_FAR_VAR(stdControl_numJoystickDevices, int)
#define stdControl_curReadTime J3D_DECL_FAR_VAR(stdControl_curReadTime, unsigned int)
#define stdControl_lastReadTime J3D_DECL_FAR_VAR(stdControl_lastReadTime, unsigned int)
#define stdControl_readDeltaTime J3D_DECL_FAR_VAR(stdControl_readDeltaTime, unsigned int)

void stdControl_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdControl_Startup);
    // J3D_HOOKFUNC(stdControl_Shutdown);
    // J3D_HOOKFUNC(stdControl_Open);
    // J3D_HOOKFUNC(stdControl_Close);
    // J3D_HOOKFUNC(stdControl_Reset);
    // J3D_HOOKFUNC(stdControl_DisableReadJoysticks);
    // J3D_HOOKFUNC(stdControl_EnableAxis);
    // J3D_HOOKFUNC(stdControl_ReadControls);
    // J3D_HOOKFUNC(stdControl_ReadAxis);
    // J3D_HOOKFUNC(stdControl_ReadAxisRaw);
    // J3D_HOOKFUNC(stdControl_ReadKeyAsAxis);
    // J3D_HOOKFUNC(stdControl_ReadAxisAsKey);
    // J3D_HOOKFUNC(stdControl_ReadAxisAsKeyEx);
    // J3D_HOOKFUNC(stdControl_ReadKey);
    // J3D_HOOKFUNC(stdControl_ControlsActive);
    // J3D_HOOKFUNC(stdControl_SetActivation);
    // J3D_HOOKFUNC(stdControl_ToggleMouse);
    // J3D_HOOKFUNC(stdControl_EnableMouse);
    // J3D_HOOKFUNC(stdControl_ControlsIdle);
    // J3D_HOOKFUNC(stdControl_TestAxisFlag);
    // J3D_HOOKFUNC(stdControl_SetAxisFlags);
    // J3D_HOOKFUNC(stdControl_InitJoysticks);
    // J3D_HOOKFUNC(stdControl_InitKeyboard);
    // J3D_HOOKFUNC(stdControl_InitMouse);
    // J3D_HOOKFUNC(stdControl_EnableAxisRead);
    // J3D_HOOKFUNC(stdControl_ReadKeyboard);
    // J3D_HOOKFUNC(stdControl_ReadJoysticks);
    // J3D_HOOKFUNC(stdControl_ReadMouse);
    // J3D_HOOKFUNC(stdControl_RegisterAxis);
    // J3D_HOOKFUNC(stdControl_DIGetStatus);
    // J3D_HOOKFUNC(stdControl_EnumDevicesCallback);
    // J3D_HOOKFUNC(stdControl_ResetMousePos);
    // J3D_HOOKFUNC(stdControl_GetMaxJoystickButtons);
    // J3D_HOOKFUNC(stdControl_GetNumJoysticks);
    // J3D_HOOKFUNC(stdControl_EnableMouseSensitivity);
    // J3D_HOOKFUNC(stdControl_ShowMouseCursor);
    // J3D_HOOKFUNC(stdControl_IsGamePad);
}

void stdControl_ResetGlobals(void)
{
    const DXStatus stdControl_aDIStatusTbl_tmp[34] = {
      { 0, "DI_OK" },
      { 1, "DI_NOTATTACHED" },
      { 1, "DI_BUFFEROVERFLOW" },
      { 1, "DI_PROPNOEFFECT" },
      { 2, "DI_POLLEDDEVICE" },
      { -2147023746, "DIERR_OLDDIRECTINPUTVERSION" },
      { -2147023743, "DIERR_BETADIRECTINPUTVERSION" },
      { -2147024777, "DIERR_BADDRIVERVER" },
      { -2147221164, "DIERR_DEVICENOTREG" },
      { -2147024894, "DIERR_NOTFOUND" },
      { -2147024894, "DIERR_OBJECTNOTFOUND" },
      { -2147024809, "DIERR_INVALIDPARAM" },
      { -2147467262, "DIERR_NOINTERFACE" },
      { -2147467259, "DIERR_GENERIC" },
      { -2147024882, "DIERR_OUTOFMEMORY" },
      { -2147467263, "DIERR_UNSUPPORTED" },
      { -2147024875, "DIERR_NOTINITIALIZED" },
      { -2147023649, "DIERR_ALREADYINITIALIZED" },
      { -2147221232, "DIERR_NOAGGREGATION" },
      { -2147024891, "DIERR_OTHERAPPHASPRIO" },
      { -2147024866, "DIERR_INPUTLOST" },
      { -2147024726, "DIERR_ACQUIRED" },
      { -2147024884, "DIERR_NOTACQUIRED" },
      { -2147024891, "DIERR_READONLY" },
      { -2147024891, "DIERR_HANDLEEXISTS" },
      { -2147220992, "DIERR_INSUFFICIENTPRIVS" },
      { -2147220991, "DIERR_DEVICEFULL" },
      { -2147220990, "DIERR_MOREDATA" },
      { -2147220989, "DIERR_NOTDOWNLOADED" },
      { -2147220988, "DIERR_HASEFFECTS" },
      { -2147220987, "DIERR_NOTEXCLUSIVEACQUIRED" },
      { -2147220986, "DIERR_INCOMPLETEEFFECT" },
      { -2147220985, "DIERR_NOTBUFFERED" },
      { -2147220984, "DIERR_EFFECTPLAYING" }
    };
    memcpy((DXStatus *)&stdControl_aDIStatusTbl, &stdControl_aDIStatusTbl_tmp, sizeof(stdControl_aDIStatusTbl));
    
    int stdControl_bReadMouse_tmp = 1;
    memcpy(&stdControl_bReadMouse, &stdControl_bReadMouse_tmp, sizeof(stdControl_bReadMouse));
    
    float stdControl_secFPS_tmp = 1.0f;
    memcpy(&stdControl_secFPS, &stdControl_secFPS_tmp, sizeof(stdControl_secFPS));
    
    float stdControl_msecFPS_tmp = 1.0f;
    memcpy(&stdControl_msecFPS, &stdControl_msecFPS_tmp, sizeof(stdControl_msecFPS));
    
    memset(&stdControl_aJoystickDevices, 0, sizeof(stdControl_aJoystickDevices));
    memset(&stdControl_cursorDisplayCounter, 0, sizeof(stdControl_cursorDisplayCounter));
    memset(&stdControl_aKeyboardState, 0, sizeof(stdControl_aKeyboardState));
    memset(&stdControl_aAxisPos, 0, sizeof(stdControl_aAxisPos));
    memset(&stdControl_keyboard, 0, sizeof(stdControl_keyboard));
    memset(&stdControl_aKeyIdleTimes, 0, sizeof(stdControl_aKeyIdleTimes));
    memset(&stdControl_aKeyInfos, 0, sizeof(stdControl_aKeyInfos));
    memset(&stdControl_aAxes, 0, sizeof(stdControl_aAxes));
    memset(&stdControl_mouse, 0, sizeof(stdControl_mouse));
    memset(&stdControl_mousePos, 0, sizeof(stdControl_mousePos));
    memset(&stdControl_aKeyPressCounter, 0, sizeof(stdControl_aKeyPressCounter));
    memset(&stdControl_bStartup, 0, sizeof(stdControl_bStartup));
    memset(&stdControl_bOpen, 0, sizeof(stdControl_bOpen));
    memset(&stdControl_bControlsIdle, 0, sizeof(stdControl_bControlsIdle));
    memset(&stdControl_bControlsActive, 0, sizeof(stdControl_bControlsActive));
    memset(&stdControl_pDI, 0, sizeof(stdControl_pDI));
    memset(&stdControl_bMouseSensitivityEnabled, 0, sizeof(stdControl_bMouseSensitivityEnabled));
    memset(&stdControl_bReadJoysticks, 0, sizeof(stdControl_bReadJoysticks));
    memset(&stdControl_numJoystickDevices, 0, sizeof(stdControl_numJoystickDevices));
    memset(&stdControl_curReadTime, 0, sizeof(stdControl_curReadTime));
    memset(&stdControl_lastReadTime, 0, sizeof(stdControl_lastReadTime));
    memset(&stdControl_readDeltaTime, 0, sizeof(stdControl_readDeltaTime));
}

int J3DAPI stdControl_Startup(int bKeyboardForeground)
{
    return J3D_TRAMPOLINE_CALL(stdControl_Startup, bKeyboardForeground);
}

void stdControl_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_Shutdown);
}

int stdControl_Open(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_Open);
}

void stdControl_Close(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_Close);
}

void stdControl_Reset(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_Reset);
}

void stdControl_DisableReadJoysticks(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_DisableReadJoysticks);
}

int J3DAPI stdControl_EnableAxis(int axisID)
{
    return J3D_TRAMPOLINE_CALL(stdControl_EnableAxis, axisID);
}

void stdControl_ReadControls(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_ReadControls);
}

float J3DAPI stdControl_ReadAxis(int controlId)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadAxis, controlId);
}

int J3DAPI stdControl_ReadAxisRaw(int controlId)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadAxisRaw, controlId);
}

float J3DAPI stdControl_ReadKeyAsAxis(unsigned int keyId)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadKeyAsAxis, keyId);
}

int J3DAPI stdControl_ReadAxisAsKey(int controlId, int* pState)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadAxisAsKey, controlId, pState);
}

int J3DAPI stdControl_ReadAxisAsKeyEx(int controlId, int* pState, float lowValue)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadAxisAsKeyEx, controlId, pState, lowValue);
}

int J3DAPI stdControl_ReadKey(unsigned int keyNum, int* pNumPressed)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ReadKey, keyNum, pNumPressed);
}

int stdControl_ControlsActive(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ControlsActive);
}

// returns 0 if mouse control was succefully processed 
int J3DAPI stdControl_SetActivation(int bActive)
{
    return J3D_TRAMPOLINE_CALL(stdControl_SetActivation, bActive);
}

int stdControl_ToggleMouse(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ToggleMouse);
}

int J3DAPI stdControl_EnableMouse(int bEnable)
{
    return J3D_TRAMPOLINE_CALL(stdControl_EnableMouse, bEnable);
}

int stdControl_ControlsIdle(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_ControlsIdle);
}

int J3DAPI stdControl_TestAxisFlag(int axisID, StdControlAxisFlag flags)
{
    return J3D_TRAMPOLINE_CALL(stdControl_TestAxisFlag, axisID, flags);
}

void J3DAPI stdControl_SetAxisFlags(int axisID, StdControlAxisFlag flags)
{
    J3D_TRAMPOLINE_CALL(stdControl_SetAxisFlags, axisID, flags);
}

void J3DAPI stdControl_InitJoysticks()
{
    J3D_TRAMPOLINE_CALL(stdControl_InitJoysticks);
}

void J3DAPI stdControl_InitKeyboard(int bForeground)
{
    J3D_TRAMPOLINE_CALL(stdControl_InitKeyboard, bForeground);
}

void J3DAPI stdControl_InitMouse()
{
    J3D_TRAMPOLINE_CALL(stdControl_InitMouse);
}

void J3DAPI stdControl_EnableAxisRead(unsigned int axisID)
{
    J3D_TRAMPOLINE_CALL(stdControl_EnableAxisRead, axisID);
}

void stdControl_ReadKeyboard(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_ReadKeyboard);
}

void stdControl_ReadJoysticks(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_ReadJoysticks);
}

void J3DAPI stdControl_ReadMouse()
{
    J3D_TRAMPOLINE_CALL(stdControl_ReadMouse);
}

void J3DAPI stdControl_RegisterAxis(unsigned int axisID, int min, int max, float deadzoneScale)
{
    J3D_TRAMPOLINE_CALL(stdControl_RegisterAxis, axisID, min, max, deadzoneScale);
}

const char* J3DAPI stdControl_DIGetStatus(int HRESULT)
{
    return J3D_TRAMPOLINE_CALL(stdControl_DIGetStatus, HRESULT);
}

BOOL __stdcall stdControl_EnumDevicesCallback(LPCDIDEVICEINSTANCEA pdidInstance, LPVOID pContext)
{
    return J3D_TRAMPOLINE_CALL(stdControl_EnumDevicesCallback, pdidInstance, pContext);
}

void stdControl_ResetMousePos(void)
{
    J3D_TRAMPOLINE_CALL(stdControl_ResetMousePos);
}

int stdControl_GetMaxJoystickButtons(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_GetMaxJoystickButtons);
}

int stdControl_GetNumJoysticks(void)
{
    return J3D_TRAMPOLINE_CALL(stdControl_GetNumJoysticks);
}

void J3DAPI stdControl_EnableMouseSensitivity(int bEnable)
{
    J3D_TRAMPOLINE_CALL(stdControl_EnableMouseSensitivity, bEnable);
}

void J3DAPI stdControl_ShowMouseCursor(int bShow)
{
    J3D_TRAMPOLINE_CALL(stdControl_ShowMouseCursor, bShow);
}

unsigned int J3DAPI stdControl_IsGamePad(int joyNum)
{
    return J3D_TRAMPOLINE_CALL(stdControl_IsGamePad, joyNum);
}
