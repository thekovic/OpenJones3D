#include "JonesDialog.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesDialog_bWindowResized J3D_DECL_FAR_VAR(JonesDialog_bWindowResized, int)
#define JonesDialog_cursorPointIdx J3D_DECL_FAR_VAR(JonesDialog_cursorPointIdx, int)
#define JonesDialog_mousePos J3D_DECL_FAR_VAR(JonesDialog_mousePos, POINT)
#define JonesDialog_pfGetDrawBufferDC J3D_DECL_FAR_VAR(JonesDialog_pfGetDrawBufferDC, JonesDialogGetDrawBufferDCFunc)
#define JonesDialog_szErrorBuffer J3D_DECL_FAR_ARRAYVAR(JonesDialog_szErrorBuffer, CHAR(*)[256])
#define JonesDialog_GDIDIBSectionInfoOffScreen J3D_DECL_FAR_VAR(JonesDialog_GDIDIBSectionInfoOffScreen, GDIDIBSectionInfo)
#define JonesDialog_pfReleaseDC J3D_DECL_FAR_VAR(JonesDialog_pfReleaseDC, JonesDialogReleaseDCFunc)
#define JonesDialog_windowRect J3D_DECL_FAR_VAR(JonesDialog_windowRect, RECT)
#define JonesDialog_windowPos J3D_DECL_FAR_ARRAYVAR(JonesDialog_windowPos, RECT(*)[2])
#define JonesDialog_stru_553210 J3D_DECL_FAR_VAR(JonesDialog_stru_553210, RECT)
#define JonesDialog_cursorInfo J3D_DECL_FAR_VAR(JonesDialog_cursorInfo, JonesDialogCursorInfo)
#define JonesDialog_GDIDIBSectionInfo J3D_DECL_FAR_VAR(JonesDialog_GDIDIBSectionInfo, GDIDIBSectionInfo)
#define JonesDialog_stru_5532D0 J3D_DECL_FAR_VAR(JonesDialog_stru_5532D0, RECT)
#define JonesDialog_pfFlipPage J3D_DECL_FAR_VAR(JonesDialog_pfFlipPage, JonesDialogFlipPageFunc)
#define JonesDialog_dword_5532E4 J3D_DECL_FAR_VAR(JonesDialog_dword_5532E4, int)
#define JonesDialog_bCursorTrackingInited J3D_DECL_FAR_VAR(JonesDialog_bCursorTrackingInited, int)
#define JonesDialog_dword_5532EC J3D_DECL_FAR_VAR(JonesDialog_dword_5532EC, int)

void JonesDialog_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesDialog_InitCursorTracking);
    // J3D_HOOKFUNC(JonesDialog_TrackCursor);
    // J3D_HOOKFUNC(JonesDialog_ResetCursorTracking);
    // J3D_HOOKFUNC(JonesDialog_CopyRectToDrawBuffer);
    // J3D_HOOKFUNC(JonesDialog_RestoreBackground);
    // J3D_HOOKFUNC(JonesDialog_ShowDialog);
    // J3D_HOOKFUNC(JonesDialog_SetGameState);
    // J3D_HOOKFUNC(JonesDialog_ResetGameState);
    // J3D_HOOKFUNC(JonesDialog_DummyFlipGDI);
    // J3D_HOOKFUNC(JonesDialog_FullscreenDlgProc);
    // J3D_HOOKFUNC(JonesDialog_SubclassDialogWindowProc);
    // J3D_HOOKFUNC(JonesDialog_HandleWM_ERASEBKGND);
    // J3D_HOOKFUNC(JonesDialog_HandleWM_PAINT);
    // J3D_HOOKFUNC(JonesDialog_HandleWM_NCPAINT);
    // J3D_HOOKFUNC(JonesDialog_AllocScreenDBISection);
    // J3D_HOOKFUNC(JonesDialog_AllocOffScreenGDISection);
    // J3D_HOOKFUNC(JonesDialog_FreeScreenDIBSection);
    // J3D_HOOKFUNC(JonesDialog_AllocOffScreenDIBSection);
    // J3D_HOOKFUNC(JonesDialog_FreeOffScreenDIBSection);
    // J3D_HOOKFUNC(JonesDialog_ShowFileSelectDialog);
    // J3D_HOOKFUNC(JonesDialog_SubclassFileDialogProc);
}

void JonesDialog_ResetGlobals(void)
{
    int JonesDialog_bWindowResized_tmp = 1;
    memcpy(&JonesDialog_bWindowResized, &JonesDialog_bWindowResized_tmp, sizeof(JonesDialog_bWindowResized));
    
    int JonesDialog_cursorPointIdx_tmp = 1;
    memcpy(&JonesDialog_cursorPointIdx, &JonesDialog_cursorPointIdx_tmp, sizeof(JonesDialog_cursorPointIdx));
    
    memset(&JonesDialog_mousePos, 0, sizeof(JonesDialog_mousePos));
    memset(&JonesDialog_pfGetDrawBufferDC, 0, sizeof(JonesDialog_pfGetDrawBufferDC));
    memset(&JonesDialog_szErrorBuffer, 0, sizeof(JonesDialog_szErrorBuffer));
    memset(&JonesDialog_GDIDIBSectionInfoOffScreen, 0, sizeof(JonesDialog_GDIDIBSectionInfoOffScreen));
    memset(&JonesDialog_pfReleaseDC, 0, sizeof(JonesDialog_pfReleaseDC));
    memset(&JonesDialog_windowRect, 0, sizeof(JonesDialog_windowRect));
    memset(&JonesDialog_windowPos, 0, sizeof(JonesDialog_windowPos));
    memset(&JonesDialog_stru_553210, 0, sizeof(JonesDialog_stru_553210));
    memset(&JonesDialog_cursorInfo, 0, sizeof(JonesDialog_cursorInfo));
    memset(&JonesDialog_GDIDIBSectionInfo, 0, sizeof(JonesDialog_GDIDIBSectionInfo));
    memset(&JonesDialog_stru_5532D0, 0, sizeof(JonesDialog_stru_5532D0));
    memset(&JonesDialog_pfFlipPage, 0, sizeof(JonesDialog_pfFlipPage));
    memset(&JonesDialog_dword_5532E4, 0, sizeof(JonesDialog_dword_5532E4));
    memset(&JonesDialog_bCursorTrackingInited, 0, sizeof(JonesDialog_bCursorTrackingInited));
    memset(&JonesDialog_dword_5532EC, 0, sizeof(JonesDialog_dword_5532EC));
}

int J3DAPI JonesDialog_InitCursorTracking(int* pAlreadyInited)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_InitCursorTracking, pAlreadyInited);
}

int J3DAPI JonesDialog_TrackCursor(int bReDraw)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_TrackCursor, bReDraw);
}

int J3DAPI JonesDialog_ResetCursorTracking()
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_ResetCursorTracking);
}

int J3DAPI JonesDialog_CopyRectToDrawBuffer(GDIDIBSectionInfo* pInfo, const PPOINT lpSourceOrigin, LPRECT pDstRect)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_CopyRectToDrawBuffer, pInfo, lpSourceOrigin, pDstRect);
}

int J3DAPI JonesDialog_RestoreBackground(HDC hdc, HWND hwnd, LPPOINT a3, LPRECT a4)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_RestoreBackground, hdc, hwnd, a3, a4);
}

int J3DAPI JonesDialog_ShowDialog(LPCSTR lpTemplateName, HWND hWnd, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_ShowDialog, lpTemplateName, hWnd, lpDialogFunc, dwInitParam);
}

void J3DAPI JonesDialog_SetGameState(JonesDialogGameState* pState, int bWindowModeSupported)
{
    J3D_TRAMPOLINE_CALL(JonesDialog_SetGameState, pState, bWindowModeSupported);
}

void J3DAPI JonesDialog_ResetGameState(JonesDialogGameState* pState, int bWindowModeSupported)
{
    J3D_TRAMPOLINE_CALL(JonesDialog_ResetGameState, pState, bWindowModeSupported);
}

int J3DAPI JonesDialog_DummyFlipGDI()
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_DummyFlipGDI);
}

INT_PTR __stdcall JonesDialog_FullscreenDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_FullscreenDlgProc, hwnd, uMsg, wParam, lParam);
}

LRESULT __stdcall JonesDialog_SubclassDialogWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_SubclassDialogWindowProc, hwnd, uMsg, wParam, lParam);
}

void J3DAPI JonesDialog_HandleWM_ERASEBKGND(HWND hwnd, WPARAM wParam, int bIconEraseBkgnd, JonesDialogData* pData)
{
    J3D_TRAMPOLINE_CALL(JonesDialog_HandleWM_ERASEBKGND, hwnd, wParam, bIconEraseBkgnd, pData);
}

void J3DAPI JonesDialog_HandleWM_PAINT(HWND hWnd, JonesDialogData* lpData)
{
    J3D_TRAMPOLINE_CALL(JonesDialog_HandleWM_PAINT, hWnd, lpData);
}

void J3DAPI JonesDialog_HandleWM_NCPAINT(HWND hwnd, WPARAM wParam, JonesDialogData* lpData)
{
    J3D_TRAMPOLINE_CALL(JonesDialog_HandleWM_NCPAINT, hwnd, wParam, lpData);
}

int J3DAPI JonesDialog_AllocScreenDBISection(int* pbSkippedAllocation)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_AllocScreenDBISection, pbSkippedAllocation);
}

int J3DAPI JonesDialog_AllocOffScreenGDISection(GDIDIBSectionInfo* pInfo, HDC hdc, int b24bpp, int* pBSkipedAllocation)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_AllocOffScreenGDISection, pInfo, hdc, b24bpp, pBSkipedAllocation);
}

void J3DAPI JonesDialog_FreeScreenDIBSection()
{
    J3D_TRAMPOLINE_CALL(JonesDialog_FreeScreenDIBSection);
}

int J3DAPI JonesDialog_AllocOffScreenDIBSection(int* pBSkipedAllocation)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_AllocOffScreenDIBSection, pBSkipedAllocation);
}

int J3DAPI JonesDialog_FreeOffScreenDIBSection()
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_FreeOffScreenDIBSection);
}

BOOL J3DAPI JonesDialog_ShowFileSelectDialog(LPOPENFILENAMEA pofn, int bOpen)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_ShowFileSelectDialog, pofn, bOpen);
}

UINT_PTR __stdcall JonesDialog_SubclassFileDialogProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(JonesDialog_SubclassFileDialogProc, hDlg, Msg, wParam, lParam);
}
