#ifndef STD_STDCONTROL_H
#define STD_STDCONTROL_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI stdControl_Startup(int bKeyboardForeground);
void stdControl_Shutdown(void);
int stdControl_Open(void);
void stdControl_Close(void);
void stdControl_Reset(void);
void stdControl_DisableReadJoysticks(void);
int J3DAPI stdControl_EnableAxis(int axisID);
void stdControl_ReadControls(void);
float J3DAPI stdControl_ReadAxis(int controlId);
int J3DAPI stdControl_ReadAxisRaw(int controlId);
float J3DAPI stdControl_ReadKeyAsAxis(unsigned int keyId);
int J3DAPI stdControl_ReadAxisAsKey(int controlId, int* pState);
int J3DAPI stdControl_ReadAxisAsKeyEx(int controlId, int* pState, float lowValue);
int J3DAPI stdControl_ReadKey(unsigned int keyNum, int* pNumPressed);
int stdControl_ControlsActive(void);
// returns 0 if mouse control was succefully processed 
int J3DAPI stdControl_SetActivation(int bActive);
int stdControl_ToggleMouse(void);
int J3DAPI stdControl_EnableMouse(int bEnable);
int stdControl_ControlsIdle(void);
int J3DAPI stdControl_TestAxisFlag(int axisID, StdControlAxisFlag flags);
void J3DAPI stdControl_SetAxisFlags(int axisID, StdControlAxisFlag flags);
void J3DAPI stdControl_InitJoysticks();
void J3DAPI stdControl_InitKeyboard(int bForeground);
void J3DAPI stdControl_InitMouse();
void J3DAPI stdControl_EnableAxisRead(unsigned int axisID);
void stdControl_ReadKeyboard(void);
void stdControl_ReadJoysticks(void);
void J3DAPI stdControl_ReadMouse();
void J3DAPI stdControl_RegisterAxis(unsigned int axisID, int min, int max, float deadzoneScale);
const char* J3DAPI stdControl_DIGetStatus(int HRESULT);
BOOL __stdcall stdControl_EnumDevicesCallback(LPCDIDEVICEINSTANCEA pdidInstance, LPVOID pContext);
void stdControl_ResetMousePos(void);
int stdControl_GetMaxJoystickButtons(void);
int stdControl_GetNumJoysticks(void);
void J3DAPI stdControl_EnableMouseSensitivity(int bEnable);
void J3DAPI stdControl_ShowMouseCursor(int bShow);
unsigned int J3DAPI stdControl_IsGamePad(int joyNum);

// Helper hooking functions
void stdControl_InstallHooks(void);
void stdControl_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCONTROL_H
