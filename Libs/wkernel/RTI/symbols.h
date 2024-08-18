#ifndef WKERNEL_RTI_SYMBOLS_H
#define WKERNEL_RTI_SYMBOLS_H
#include <j3dcore/j3d.h>
#include <wkernel/types.h>

#define wkernel_Run_TYPE int (J3DAPI*)(HINSTANCE, HINSTANCE, LPSTR, int, LPCSTR)
#define wkernel_PeekProcessEvents_TYPE int (*)(void)
#define wkernel_ProcessEvents_TYPE int (*)(void)
#define wkernel_SetWindowStyle_TYPE void (J3DAPI*)(LONG)
#define wkernel_SetWindowSize_TYPE BOOL (J3DAPI*)(int, int)
#define wkernel_SetWindowProc_TYPE void (J3DAPI*)(WKERNELPROC)
#define wkernel_CreateWindow_TYPE int (J3DAPI*)(HINSTANCE, int, LPCSTR)
#define wkernel_MainWndProc_TYPE LRESULT (CALLBACK*)(HWND, UINT, WPARAM, LPARAM)

#endif // WKERNEL_RTI_SYMBOLS_H
