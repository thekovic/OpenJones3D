#ifndef SITH_SITHCONTROL_H
#define SITH_SITHCONTROL_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithControl_g_bControlStartup J3D_DECL_FAR_VAR(sithControl_g_bControlStartup, int)
// extern int sithControl_g_bControlStartup;

int J3DAPI sithControl_Startup(int bKeyboardForeground);
void J3DAPI sithControl_Shutdown();
int J3DAPI sithControl_Open();
int J3DAPI sithControl_Close();
void J3DAPI sithControl_RegisterAxisFunction(SithControlFunction functionId, SithControlFunctionFlag flag);
void J3DAPI sithControl_RegisterKeyFunction(SithControlFunction functionId);
void J3DAPI sithControl_BindControl(SithControlFunction functionId, unsigned int controlId, SithControlBindFlag flags);
SithControlBinding* J3DAPI sithControl_BindAxis(SithControlFunction functionId, int controlId, SithControlBindFlag flags);
void J3DAPI sithControl_Unbind(SithControlFunction fctnID);
void J3DAPI sithControl_UnbindIndex(int funcId, int bindIndex);
void J3DAPI sithControl_RemoveAllControlBindings(SithControlBindFlag flags, int controlId);
int J3DAPI sithControl_RegisterControlCallback(SithControlCallback pfCallback);
void J3DAPI sithControl_Update(float secDeltaTime, int msecDeltaTime);
float J3DAPI sithControl_GetKeyAsAxis(SithControlFunction asixId);
float J3DAPI sithControl_GetAxis(SithControlFunction axisId);
int J3DAPI sithControl_GetKey(SithControlFunction keyId, int* pState);
void sithControl_ReadControls(void);
void J3DAPI sithControl_UnbindJoystickAxes();
int J3DAPI sithControl_UnbindMouseAxes();
void J3DAPI sithControl_Reset();
void J3DAPI sithControl_RegisterKeyFunctions();
void J3DAPI sithControl_RegisterControlBindings();
int J3DAPI sithControl_GetNumJoystickDevices();

// Helper hooking functions
void sithControl_InstallHooks(void);
void sithControl_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCONTROL_H
