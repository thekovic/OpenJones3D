#ifndef WKERNEL_WKERNEL_H
#define WKERNEL_WKERNEL_H
#include <j3dcore/j3d.h>
#include <wkernel/types.h>
#include <wkernel/RTI/addresses.h>

J3D_EXTERN_C_START

int J3DAPI wkernel_Main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd, LPCSTR lpWindowName);
HRESULT wkernel_PeekProcessEvents(void);
HRESULT wkernel_ProcessEvents(void);
void J3DAPI wkernel_SetWindowStyle(LONG dwNewLong);
BOOL J3DAPI wkernel_SetWindowSize(int width, int height);
void J3DAPI wkernel_SetWindowProc(WKERNELPROC pfProc);
int J3DAPI wkernel_CreateWindow(HINSTANCE hInstance, int nShowCmd, LPCSTR lpWindowName);
LRESULT __stdcall wkernel_MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

// Helper hooking functions
void wkernel_InstallHooks(void);
void wkernel_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // WKERNEL_WKERNEL_H
