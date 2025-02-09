#ifndef STD_STDCONTROL_H
#define STD_STDCONTROL_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

#include <stdbool.h>

J3D_EXTERN_C_START

// Mouse axis control ids
#define STDCONTROL_AID_MOUSE_X    STDCONTROL_MAX_JOYSTICK_AXES // 48
#define STDCONTROL_AID_MOUSE_Y    STDCONTROL_AID_MOUSE_X + 1
#define STDCONTROL_AID_MOUSE_Z    STDCONTROL_AID_MOUSE_X + 2

// Axis aid flags
#define STDCONTROL_AID_LOW_SENSITIVITY 0x20000000
#define STDCONTROL_AID_POSITIVE_AXIS   0x80000000
#define STDCONTROL_AID_NEGATIVE_AXIS   0xC0000000

#define STDCONTROL_GETAID(axis) (axis & ~(STDCONTROL_AID_POSITIVE_AXIS | STDCONTROL_AID_NEGATIVE_AXIS | STDCONTROL_AID_LOW_SENSITIVITY))

// Button key ids
#define STDCONTROL_KID_MOUSE_LBUTTON   (STDCONTROL_JOYSTICK_FIRSTKID + STDCONTROL_JOYSTICK_TOTALKIDS ) // 640
#define STDCONTROL_KID_MOUSE_RBUTTON   STDCONTROL_KID_MOUSE_LBUTTON + 1
#define STDCONTROL_KID_MOUSE_MBUTTON   STDCONTROL_KID_MOUSE_LBUTTON + 2
#define STDCONTROL_KID_MOUSE_XBUTTON   STDCONTROL_KID_MOUSE_LBUTTON + 3

// Joystick 
#define STDCONTROL_JOYSTICK_FIRSTKID    STDCONTROL_MAX_KEYBOARD_BUTTONS
#define STDCONTROL_JOYSTICK_FIRTPOVKID  STDCONTROL_JOYSTICK_FIRSTKID + STDCONTROL_NUM_JOYSTICK_BUTTONS
#define STDCONTROL_JOYSTICK_TOTALKIDS   (STDCONTROL_MAX_JOYSTICK_DEVICES * STDCONTROL_TOTAL_JOYSTICK_BUTTONS)

#define STDCONTROL_JOYSTICK_GETBUTTON(joyNum, btnNum)            ((STDCONTROL_TOTAL_JOYSTICK_BUTTONS) * joyNum + btnNum + STDCONTROL_JOYSTICK_FIRSTKID)
#define STDCONTROL_JOYSTICK_GETPOVBUTTON(joyNum, povNum, btnNum) ((STDCONTROL_TOTAL_JOYSTICK_BUTTONS) * joyNum + (povNum * STDCONTROL_MAX_JOYSTICK_POVCONTROLERS) + (STDCONTROL_JOYSTICK_FIRTPOVKID + btnNum))

#define STDCONTROL_JOYSTICK_NUMPOSAXES  3u // number of positional axes
#define STDCONTROL_JOYSTICK_NUMROTAXES  3u // number of rotation axes
#define STDCONTROL_JOYSTICK_TOTALAXES   (STDCONTROL_JOYSTICK_NUMPOSAXES + STDCONTROL_JOYSTICK_NUMROTAXES) // 6

// Joystick positional & rotation axis indices
#define STDCONTROL_JOYSTICK_AXIS_X  0u
#define STDCONTROL_JOYSTICK_AXIS_Y  1u
#define STDCONTROL_JOYSTICK_AXIS_Z  2u
#define STDCONTROL_JOYSTICK_AXIS_RX 3u
#define STDCONTROL_JOYSTICK_AXIS_RY 4u
#define STDCONTROL_JOYSTICK_AXIS_RZ 5u

#define STDCONTROL_GET_JOYSTICK_AXIS(joyNum, axisIdx) (STDCONTROL_JOYSTICK_TOTALAXES * joyNum + axisIdx)
#define STDCONTROL_GET_JOYSTICK_AXIS_X(joyNum)        STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_X)
#define STDCONTROL_GET_JOYSTICK_AXIS_Y(joyNum)        STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_Y)
#define STDCONTROL_GET_JOYSTICK_AXIS_Z(joyNum)        STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_Z)
#define STDCONTROL_GET_JOYSTICK_AXIS_RX(joyNum)       STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_RX)
#define STDCONTROL_GET_JOYSTICK_AXIS_RY(joyNum)       STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_RY)
#define STDCONTROL_GET_JOYSTICK_AXIS_RZ(joyNum)       STDCONTROL_GET_JOYSTICK_AXIS(joyNum, STDCONTROL_JOYSTICK_AXIS_RZ)

#define STDCONTROL_MAX_JOYSTICK_DEVICES       8u
#define STDCONTROL_MAX_JOYSTICK_POVCONTROLERS 4u  // max number of point-of-view controllers e.g.: Hat switch
#define STDCONTROL_MAX_JOYSTICK_AXES         (STDCONTROL_MAX_JOYSTICK_DEVICES * STDCONTROL_JOYSTICK_TOTALAXES) // 48, total number of axes from all devices

// Miscellaneous constants
#define STDCONTROL_MAX_AXES                  (STDCONTROL_MAX_JOYSTICK_AXES + 3) // 51; 3 - mouse axes 
#define STDCONTROL_MAX_KEYBOARD_BUTTONS       256u // aka max keyboard kids
#define STDCONTROL_MAX_MOUSE_BUTTONS          4u
#define STDCONTROL_NUM_JOYSTICK_BUTTONS       32u // number of joy buttons per device
#define STDCONTROL_NUM_JOYSTICK_POVBUTTONS    4u  // number of buttons per point-of-view controller
#define STDCONTROL_TOTAL_JOYSTICK_BUTTONS    (STDCONTROL_NUM_JOYSTICK_BUTTONS + (STDCONTROL_NUM_JOYSTICK_POVBUTTONS * STDCONTROL_MAX_JOYSTICK_POVCONTROLERS))// max number of joy buttons + POV buttons  per device
#define STDCONTROL_MAX_KEYID                  STDCONTROL_MAX_KEYBOARD_BUTTONS + STDCONTROL_JOYSTICK_TOTALKIDS + STDCONTROL_MAX_MOUSE_BUTTONS // 644

// Helper macros to test if specific keyid or aid is either button or axis of specific device

#define STDCONTROL_ISKEYBOARDBUTTON(kid) (kid < STDCONTROL_MAX_KEYBOARD_BUTTONS)

#define STDCONTROL_ISMOUSEAXIS(aid) (STDCONTROL_GETAID(aid) >= STDCONTROL_AID_MOUSE_X && STDCONTROL_GETAID(aid) <= STDCONTROL_AID_MOUSE_Z )
#define STDCONTROL_ISMOUSEBUTTON(kid) (kid >= STDCONTROL_KID_MOUSE_LBUTTON && kid <= STDCONTROL_KID_MOUSE_XBUTTON)

#define STDCONTROL_ISJOYSTICKAXIS(aid) (STDCONTROL_GETAID(aid) < STDCONTROL_AID_MOUSE_X)
#define STDCONTROL_ISJOYSTICKBUTTON(kid) (STDCONTROL_GETAID(kid) >= STDCONTROL_JOYSTICK_FIRSTKID) && (STDCONTROL_GETAID(kid) < STDCONTROL_KID_MOUSE_LBUTTON)

// In-place reg. tests
static_assert(STDCONTROL_JOYSTICK_FIRSTKID == 256, "STDCONTROL_JOYSTICK_FIRSTKID == 256");
static_assert(STDCONTROL_JOYSTICK_TOTALKIDS == 384, "STDCONTROL_JOYSTICK_TOTALKIDS == 384");
static_assert(STDCONTROL_KID_MOUSE_LBUTTON == 640, "STDCONTROL_AID_MOUSE_LBUTTON == 640");
static_assert(STDCONTROL_KID_MOUSE_XBUTTON == 643, "STDCONTROL_KID_MOUSE_XBUTTON == 643");
static_assert(STDCONTROL_TOTAL_JOYSTICK_BUTTONS == 48, "STDCONTROL_TOTAL_JOYSTICK_BUTTONS == 48");
static_assert(STDCONTROL_MAX_KEYID == 644, "STDCONTROL_MAX_KEYID == 644");
static_assert(STDCONTROL_MAX_JOYSTICK_AXES == 48, "STDCONTROL_MAX_JOYSTICK_AXES == 48");
static_assert(STDCONTROL_MAX_AXES == 51, "STDCONTROL_MAX_AXES == 51");
static_assert(STDCONTROL_AID_MOUSE_X == 48, "STDCONTROL_AID_MOUSE_X == 48");
static_assert(STDCONTROL_JOYSTICK_GETBUTTON(0, 0) == 256, "STDCONTROL_JOYSTICK_GETBUTTON(0, 0) == 256");
static_assert(STDCONTROL_JOYSTICK_GETBUTTON(0, 1) == 257, "STDCONTROL_JOYSTICK_GETBUTTON(0, 0) == 257");
static_assert(STDCONTROL_JOYSTICK_GETBUTTON(0, 1) == 257, "STDCONTROL_JOYSTICK_GETBUTTON(0, 0) == 257");
static_assert(STDCONTROL_JOYSTICK_GETBUTTON(1, 0) == 304, "STDCONTROL_JOYSTICK_GETBUTTON(1, 0) == 304");
static_assert(STDCONTROL_JOYSTICK_GETBUTTON(1, 1) == 305, "STDCONTROL_JOYSTICK_GETBUTTON(1, 1) == 305");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 0, 0) == 288, "STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 0, 0) == 288");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 0, 1) == 289, "STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 0, 0) == 288");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 1, 0) == 292, "STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 1, 0) == 292");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 1, 1) == 293, "STDCONTROL_JOYSTICK_GETPOVBUTTON(0, 1, 1) == 293");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 0, 0) == 336, "STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 0, 0) == 336");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 0, 1) == 337, "STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 0, 1) == 337");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 1, 0) == 340, "STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 1, 0) == 340");
static_assert(STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 1, 1) == 341, "STDCONTROL_JOYSTICK_GETPOVBUTTON(1, 1, 1) == 341");


int J3DAPI stdControl_Startup(int bKeyboardForeground);
bool stdControl_HasStarted(void);
void stdControl_Shutdown(void);

int stdControl_Open(void);
bool stdControl_IsOpen(void);
void stdControl_Close(void);
void stdControl_Reset(void);

void stdControl_DisableReadJoysticks(void);
int J3DAPI stdControl_EnableAxis(int axisID);

void stdControl_ReadControls(void);
void stdControl_FinishRead(void); // Added

float J3DAPI stdControl_ReadAxis(size_t axis);
int J3DAPI stdControl_ReadAxisRaw(size_t axis);
float J3DAPI stdControl_ReadKeyAsAxis(size_t keyId);

/**
 * @brief Emulates a key press from a joystick/gamepad axis.
 *
 * Returns non-zero if the axis is "pressed". If pbPressed is not NULL,
 * it is set to non-zero if the axis was just pressed - always true if non-zero value is returned.
 *
 * @param axis - The axis index.
 * @param pbPressed - Pointer to an int for the "just pressed" state.
 * @return A non-zero value if the key is currently pressed down; zero otherwise.
 */
int J3DAPI stdControl_ReadAxisAsKey(size_t axis, int* pbPressed);

/**
 * @brief Emulates a key press from a joystick/gamepad axis with a threshold.
 *
 * Returns non-zero if the axis value exceeds the specified threshold. If pbPressed is not NULL,
 * it is set to non-zero if the axis was just pressed - always true if non-zero value is returned.
 *
 * @param axis - The axis index.
 * @param pbPressed - Pointer to an int for the "just pressed" state.
 * @param lowValue - The threshold value for detecting a press.
 * @return A non-zero value if the key is currently pressed down; zero otherwise.
 */
int J3DAPI stdControl_ReadAxisAsKeyEx(size_t axis, int* pbPressed, float lowValue);

/**
 * @brief Reads the current and just pressed state of a specified key.
 *
 * Returns non-zero if the key is currently pressed. If pbPressed is not NULL,
 * it is set to non-zero if the key was just pressed.
 *
 * @param keyNum - The key identifier.
 * @param pbPressed - Pointer to an int for the "just pressed" state.
 *
 * @return A non-zero value if the key is currently pressed down; zero otherwise.
 */
int J3DAPI stdControl_ReadKey(size_t keyNum, int* pbPressed);

int stdControl_ControlsActive(void);
int J3DAPI stdControl_SetActivation(int bActive); // returns 0 if mouse control was successfully processed 

int stdControl_ToggleMouse(void);
int J3DAPI stdControl_EnableMouse(int bEnable);
bool stdControl_IsMouseEnabled(void); // Added

void J3DAPI stdControl_RegisterMouseAxesXY(float xrange, float yrange); // Added
void stdControl_ResetMousePos(void);
int stdControl_MouseSensitivityEnabled(void); // Added: From debug version
void J3DAPI stdControl_EnableMouseSensitivity(int bEnable);
void J3DAPI stdControl_SetMouseSensitivity(float xSensitivity, float ySensitivity); // Added
void J3DAPI stdControl_ShowMouseCursor(int bShow);

int stdControl_ControlsIdle(void);

int J3DAPI stdControl_TestAxisFlag(size_t axis, StdControlAxisFlag flags);
void J3DAPI stdControl_SetAxisFlags(size_t axis, StdControlAxisFlag flags);

void J3DAPI stdControl_RegisterAxis(size_t aid, int min, int max, float deadzoneScale);
size_t stdControl_GetMaxJoystickButtons(void);
size_t stdControl_GetNumJoysticks(void);
const char* J3DAPI stdControl_GetJoysticDescription(int joyNum); // Added: From debug version

int J3DAPI stdControl_IsGamePad(int joyNum);

// Helper hooking functions
void stdControl_InstallHooks(void);
void stdControl_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDCONTROL_H
