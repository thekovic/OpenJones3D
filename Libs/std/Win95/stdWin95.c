#include "stdWin95.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdWin95_guid J3D_DECL_FAR_VAR(stdWin95_guid, GUID)
#define stdWin95_hwnd J3D_DECL_FAR_VAR(stdWin95_hwnd, HWND)
#define stdWin95_hInstance J3D_DECL_FAR_VAR(stdWin95_hInstance, HINSTANCE)

void stdWin95_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdWin95_SetWindow);
    // J3D_HOOKFUNC(stdWin95_GetWindow);
    // J3D_HOOKFUNC(stdWin95_SetInstance);
    // J3D_HOOKFUNC(stdWin95_GetInstance);
    // J3D_HOOKFUNC(stdWin95_SetGuid);
}

void stdWin95_ResetGlobals(void)
{
    memset(&stdWin95_guid, 0, sizeof(stdWin95_guid));
    memset(&stdWin95_hwnd, 0, sizeof(stdWin95_hwnd));
    memset(&stdWin95_hInstance, 0, sizeof(stdWin95_hInstance));
}

void J3DAPI stdWin95_SetWindow(HWND hwnd)
{
    J3D_TRAMPOLINE_CALL(stdWin95_SetWindow, hwnd);
}

HWND J3DAPI stdWin95_GetWindow()
{
    return J3D_TRAMPOLINE_CALL(stdWin95_GetWindow);
}

void J3DAPI stdWin95_SetInstance(HINSTANCE hinstance)
{
    J3D_TRAMPOLINE_CALL(stdWin95_SetInstance, hinstance);
}

HINSTANCE stdWin95_GetInstance(void)
{
    return J3D_TRAMPOLINE_CALL(stdWin95_GetInstance);
}

void J3DAPI stdWin95_SetGuid(const GUID* pGuid)
{
    J3D_TRAMPOLINE_CALL(stdWin95_SetGuid, pGuid);
}
