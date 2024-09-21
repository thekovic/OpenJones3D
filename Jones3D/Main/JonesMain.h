#ifndef JONES3D_JONESMAIN_H
#define JONES3D_JONESMAIN_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define JonesMain_g_aErrorBuffer J3D_DECL_FAR_ARRAYVAR(JonesMain_g_aErrorBuffer, char(*)[1024])
// extern char JonesMain_g_aErrorBuffer[1024] ;

#define JonesMain_g_mainMutex J3D_DECL_FAR_VAR(JonesMain_g_mainMutex, HANDLE)
// extern HANDLE JonesMain_g_mainMutex;

int J3DAPI JonesMain_Startup(const char* lpCmdLine);
void JonesMain_Shutdown(void);

int JonesMain_Open(void);
int JonesMain_Close(void);
int JonesMain_IsOpen(void);

int J3DAPI JonesMain_GameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void J3DAPI JonesMain_HandleWMGetMinMaxInfo(HWND hwnd, LPMINMAXINFO pMinMaxInfo);
void J3DAPI JonesMain_HandleWMPaint(HWND hWnd);
int J3DAPI JonesMain_HandleWMTimer(HWND hWnd);
void J3DAPI JonesMain_HandleWMKeydown(HWND hWnd, WPARAM vk, int a3, unsigned int lParam, int exkeyflags);
void JonesMain_PrintQuickSave(void);
int J3DAPI JonesMain_HandleWMActivateApp(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT J3DAPI JonesMain_HandleWMActivate(HWND hWnd, int wParam, LPARAM lParamLo, int lParamHi);
void J3DAPI JonesMain_OnAppActivate(HWND hWnd, int bActivated);
void J3DAPI JonesMain_HandleWMChar(HWND hwnd, char chr);
void J3DAPI JonesMain_HandleWMSysCommand(HWND hWnd, WPARAM wParam);
void J3DAPI JonesMain_HandleWMPowerBroadcast(HWND hWnd, WPARAM wParam);

void J3DAPI JonesMain_PauseGame();
void J3DAPI JonesMain_ResumeGame();
int J3DAPI JonesMain_IsGamePaused();

int JonesMain_Process(void);
int JonesMain_ProcessWindowEvents(void);
int JonesMain_ProcessGame(void);
void JonesMain_ProcessMenu(void);

void J3DAPI JonesMain_PrintFramerate();
int J3DAPI JonesMain_TogglePrintFramerate();


int J3DAPI JonesMain_EnsureFile(const char* pFilename);

int J3DAPI JonesMain_Restore(const char* pNdsFilePath);
int JonesMain_ProcessGamesaveState(void);

void JonesMain_UpdateLevelNum(void);
void JonesMain_NextLevel(void); // Added
int JonesMain_ProcessEndLevel(void);
void JonesMain_SetBonusLevel(void);
void JonesMain_ShowEndCredits(void);
int JonesMain_Credits(void);


StdDisplayEnvironment* JonesMain_GetDisplayEnvironment(void);
JonesDisplaySettings* JonesMain_GetDisplaySettings(void);
int J3DAPI JonesMain_CloseWindow();
int JonesMain_FilePrintf(const char* pFormat, ...);
int JonesMain_Printf(const char* pFormat, ...);
void JonesMain_RefreshDisplayDevice(void);
int J3DAPI JonesMain_PlayIntro();
int J3DAPI JonesMain_IntroWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void J3DAPI JonesMain_HandleWMLButtonUp();
void J3DAPI JonesMain_IntroHandleKeydown(HWND hwnd, int wParam);
signed int J3DAPI JonesMain_IntroMovieBll565(void* a1);
signed int J3DAPI JonesMain_IntroMovieBlt555(void* a1);
int J3DAPI JonesMain_IntroMovieBlt32(void* a1);
J3DNORETURN void J3DAPI JonesMain_Assert(const char* pErrorText, const char* pSrcFile, int line);
void J3DAPI JonesMain_BindInventoryControlKeys(const int* a1, int numKeys);
void J3DAPI JonesMain_ResetHUD();
int J3DAPI JonesMain_SaveHUD(DPID idTo, unsigned int outstream);
int J3DAPI JonesMain_RestoreHUD(const SithMessage* pMsg);
int J3DAPI JonesMain_GetCurrentLevelNum();
void J3DAPI JonesMain_LogErrorToFile(const char* pErrorText);
void J3DAPI JonesMain_LoadSettings(StdDisplayEnvironment* pDisplayEnv, JonesState* pConfig);
int J3DAPI JonesMain_ShowDevDialog(HWND hWnd, JonesState* pConfig);
LRESULT __stdcall JonesMain_DevDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI JonesMain_InitDevDialog(HWND hDlg, WPARAM wParam, JonesState* pConfig);
void J3DAPI JonesMain_DevDialogHandleCommand(HWND hWnd, int controlId, LPARAM lParam, int hiWParam);
void J3DAPI JonesMain_DevDialogInitDisplayDevices(HWND hDlg, JonesState* pConfig);
void J3DAPI JonesMain_DevDialogUpdateRadioButtons(HWND hDlg, JonesState* pState);
int J3DAPI JonesMain_FindClosestVideoMode(const StdDisplayEnvironment* pList, StdVideoMode* pVideoMOde, size_t deviceNum);
int J3DAPI JonesMain_CurDisplaySupportsBPP(JonesDisplaySettings* pSettings, int bpp);

// Helper hooking functions
void JonesMain_InstallHooks(void);
void JonesMain_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESMAIN_H
