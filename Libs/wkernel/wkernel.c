#include "wkernel.h"
#include <j3dcore/j3dhook.h>
#include <wkernel/RTI/symbols.h>

#define wkernel_guid J3D_DECL_FAR_VAR(wkernel_guid, const GUID)
#define wkernel_hwnd J3D_DECL_FAR_VAR(wkernel_hwnd, HWND)
#define wkernel_nShowCmd J3D_DECL_FAR_VAR(wkernel_nShowCmd, int)
#define wkernel_msg_1 J3D_DECL_FAR_VAR(wkernel_msg_1, MSG)
#define wkernel_msg_2 J3D_DECL_FAR_VAR(wkernel_msg_2, MSG)
#define wkernel_pfWndProc J3D_DECL_FAR_VAR(wkernel_pfWndProc, WKERNELPROC)
#define wkernel_wndBorderWidth J3D_DECL_FAR_VAR(wkernel_wndBorderWidth, int)
#define wkernel_wndMenuBarHeight J3D_DECL_FAR_VAR(wkernel_wndMenuBarHeight, int)

void wkernel_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(wkernel_Main);
    // J3D_HOOKFUNC(wkernel_PeekProcessEvents);
    // J3D_HOOKFUNC(wkernel_ProcessEvents);
    // J3D_HOOKFUNC(wkernel_SetWindowStyle);
    // J3D_HOOKFUNC(wkernel_SetWindowSize);
    // J3D_HOOKFUNC(wkernel_SetWindowProc);
    // J3D_HOOKFUNC(wkernel_CreateWindow);
    // J3D_HOOKFUNC(wkernel_MainWndProc);
}

void wkernel_ResetGlobals(void)
{
    const GUID wkernel_guid_tmp = { 2194558368u, 40127u, 4561u, { 144u, 133u, 0u, 96u, 151u, 118u, 234u, 2u } };
    memcpy((GUID *)&wkernel_guid, &wkernel_guid_tmp, sizeof(wkernel_guid));
    
    memset(&wkernel_hwnd, 0, sizeof(wkernel_hwnd));
    memset(&wkernel_nShowCmd, 0, sizeof(wkernel_nShowCmd));
    memset(&wkernel_msg_1, 0, sizeof(wkernel_msg_1));
    memset(&wkernel_msg_2, 0, sizeof(wkernel_msg_2));
    memset(&wkernel_pfWndProc, 0, sizeof(wkernel_pfWndProc));
    memset(&wkernel_wndBorderWidth, 0, sizeof(wkernel_wndBorderWidth));
    memset(&wkernel_wndMenuBarHeight, 0, sizeof(wkernel_wndMenuBarHeight));
}

int J3DAPI wkernel_Main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, LPCSTR lpWindowName)
{
    return J3D_TRAMPOLINE_CALL(wkernel_Main, hinstance, hPrevInstance, lpCmdLine, nShowCmd, lpWindowName);
}

HRESULT wkernel_PeekProcessEvents(void)
{
    return J3D_TRAMPOLINE_CALL(wkernel_PeekProcessEvents);
}

HRESULT wkernel_ProcessEvents(void)
{
    return J3D_TRAMPOLINE_CALL(wkernel_ProcessEvents);
}

void J3DAPI wkernel_SetWindowStyle(LONG dwNewLong)
{
    J3D_TRAMPOLINE_CALL(wkernel_SetWindowStyle, dwNewLong);
}

BOOL J3DAPI wkernel_SetWindowSize(int width, int height)
{
    return J3D_TRAMPOLINE_CALL(wkernel_SetWindowSize, width, height);
}

void J3DAPI wkernel_SetWindowProc(WKERNELPROC pfProc)
{
    J3D_TRAMPOLINE_CALL(wkernel_SetWindowProc, pfProc);
}

int J3DAPI wkernel_CreateWindow(HINSTANCE hInstance, int nShowCmd, LPCSTR lpWindowName)
{
    return J3D_TRAMPOLINE_CALL(wkernel_CreateWindow, hInstance, nShowCmd, lpWindowName);
}

LRESULT __stdcall wkernel_MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(wkernel_MainWndProc, hWnd, Msg, wParam, lParam);
}
