#ifndef JONES3D_JONESCONFIG_H
#define JONES3D_JONESCONFIG_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>

#include <std/General/stdConffile.h>
#include <std/types.h>

J3D_EXTERN_C_START

int jonesConfig_Startup(void);
int J3DAPI jonesConfig_InitKeySetsPath();
int J3DAPI jonesConfig_InitKeyActions();
void jonesConfig_Shutdown(void);
void J3DAPI jonesConfig_ControlToString(unsigned int controlId, char* pDest);
int J3DAPI jonesConfig_ShowMessageDialog(HWND hWnd, const char* pTitle, const char* pText, int iconID);
BOOL CALLBACK jonesConfig_MessageDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM a4);
void J3DAPI jonesConfig_sub_4025F0(HWND hWnd, uint16_t* a2);
int J3DAPI jonesConfig_sub_402670(HWND hDlg, int a2, uint16_t* dwNewLong);
int J3DAPI jonesConfig_SetTextControl(HWND hDlg, HWND hWnd, const char* aText);
BOOL J3DAPI jonesConfig_sub_402A90(HWND hDlg, int nResult);
JonesControlsScheme* J3DAPI jonesConfig_NewControlScheme();
int J3DAPI jonesConfig_LoadConstrolsScheme(const char* pFilePath, JonesControlsScheme* pConfig);
int J3DAPI jonesConfig_GetEntryIndex(int* argNum, StdConffileEntry* pEntry, int a3, const char** apStringList, int size);
int J3DAPI jonesConfig_GetValueIndex(char* pValue, const char** apStringList, int size);
int J3DAPI jonesConfig_GetControllerKeySchemeIndex(int* pArgNum, StdConffileEntry* pEntry);
int J3DAPI jonesConfig_SetDefaultControlScheme(JonesControlsScheme* pScheme, int num);
void J3DAPI jonesConfig_BindControls(JonesControlsScheme* pConfig);
void J3DAPI jonesConfig_BindJoystickControl(SithControlFunction functionId, int controlId);
HFONT J3DAPI jonesConfig_InitDialog(HWND hWnd, HFONT hFont, int dlgID);
HFONT J3DAPI jonesConfig_CreateDialogFont(HWND hWnd, int bWindowMode, int dlgResNum, float* pFontScale);
void J3DAPI jonesConfig_ResetDialogFont(HWND hWndParent, HFONT hFont);
BOOL CALLBACK jonesConfig_ResetWindowFontCallback(HWND hWnd, LPARAM lparam);
BOOL CALLBACK jonesConfig_SetPositionAndTextCallback(HWND hwnd, LPARAM lparam);
void J3DAPI jonesConfig_SetWindowFontAndPosition(HWND hwnd, JonesDialogFontInfo* pFontInfo);
void J3DAPI jonesConfig_GetWindowScreenRect(HWND hWnd, LPRECT lpRect);
void J3DAPI jonesConfig_SetDialogTitleAndPosition(HWND hWnd, JonesDialogFontInfo* pDlgFontInfo);
int J3DAPI jonesConfig_GetSaveGameFilePath(HWND hWnd, char* pOutFilePath);
UINT_PTR CALLBACK jonesConfig_SaveGameDialogHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_SaveGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA lpOfn);
LRESULT CALLBACK jonesConfig_SaveGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_ShowOverwriteSaveGameDlg(HWND hWnd, const char* aFilePath);
int J3DAPI jonesConfig_ShowExitGameDialog(HWND hWnd, char* pSaveGameFilePath);
INT_PTR CALLBACK jonesConfig_ExitGameDlgProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
INT_PTR CALLBACK jonesConfig_SaveGameMsgBoxProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_GameSaveSetData(HWND hDlg, int a2, GameSaveMsgBoxData* pData);
void J3DAPI jonesConfig_MsgBoxDlg_HandleWM_COMMAND(HWND hWnd, int nResult);
int J3DAPI jonesConfig_GetLoadGameFilePath(HWND hWnd, char* pDestNdsPath);
void* J3DAPI jonesConfig_sub_405F60(HWND hWnd);
UINT_PTR CALLBACK jonesConfig_LoadGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_ShowLoadGameWarningMsgBox(HWND hWnd);
BOOL J3DAPI jonesConfig_LoadGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA pofn);
LRESULT CALLBACK jonesConfig_LoadGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int J3DAPI jonesConfig_ShowGamePlayOptions(HWND hWnd);
INT_PTR CALLBACK jonesConfig_GamePlayOptionsProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
void J3DAPI jonesConfig_HandleWM_HSCROLL(HWND hDlg, HWND hWnd, uint16_t sbValue);
int J3DAPI jonesConfig_GamePlayOptionsInitDlg(HWND hDlg);
void J3DAPI jonesConfig_GamePlayOptions_HandleWM_COMMAND(HWND hDlg, uint16_t controlID);

void J3DAPI jonesConfig_EnableMouseControl(int bEnable);
void J3DAPI jonesConfig_FreeControlScheme(JonesControlsScheme* pConfig);
void J3DAPI jonesConfig_FreeControlConfigEntry(JonesControlsConfig* pConfig);
int J3DAPI jonesConfig_ShowControlOptions(HWND hWnd);
int J3DAPI jonesConfig_CopyControlConfig(JonesControlsConfig* pSrc, JonesControlsConfig* pDst);
JonesControlsScheme* J3DAPI jonesConfig_CopyControlSchemes(JonesControlsScheme* aSchemes, int start, int sizeScheme);
int J3DAPI jonesConfig_InitControlsConfig();
int J3DAPI jonesConfig_LoadControlsSchemesFromSystem(JonesControlsConfig* pConfig);
int J3DAPI jonesConfig_SetDefaultControlSchemes(JonesControlsConfig* pConfig);
INT_PTR __stdcall jonesConfig_ControlOptionsProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_InitControlOptionsDlg(HWND hDlg, int a2, JonesControlsConfig* pConfig);
void J3DAPI jonesConfig_ControlOptions_HandleWM_COMMAND(HWND hWnd, int ctrlID, int a3, int16_t a4);
int J3DAPI jonesConfig_WriteScheme(JonesControlsScheme* pScheme);
int J3DAPI jonesConfig_sub_407F60(HWND hDlg);
LRESULT J3DAPI jonesConfig_sub_408000(HWND hDlg, int a2);
void J3DAPI jonesConfig_sub_408260(HWND hDlg, JonesControlsConfig* a2);
JonesControlsScheme* J3DAPI jonesConfig_sub_408400(JonesControlsConfig* pConfig);
void J3DAPI jonesConfig_CreateNewSchemeAction(HWND hDlg, JonesControlsConfig* pConfig);
int J3DAPI jonesConfig_ShowCreateControlSchemeDialog(HWND hWnd, char* pDstSchemeName);
INT_PTR __stdcall jonesConfig_CreateControlSchemeProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_InitCreateControlScheme(HWND hDlg, int a2, char* pSchemeName);
void J3DAPI jonesConfig_CreateControlScheme_Handle_WM_COMMAND(HWND hWnd, int16_t nResult);
int J3DAPI jonesConfig_ShowEditControlShemeDialog(HWND hWnd, void* dwInitParam);
INT_PTR __stdcall jonesConfig_EditControlSchemProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_InitEditControlSchemeDlg(HWND hDlg, int a2, void* dwNewLong);
LRESULT J3DAPI jonesConfig_sub_408ED0(HWND hWnd, char* pKey);
const char** J3DAPI jonesConfig_sub_408FC0(HWND hWnd, int a2, JonesControlsScheme* a3);
char J3DAPI jonesConfig_sub_409200(HWND hWnd, int nResult);
LPARAM J3DAPI jonesConfig_sub_409530(HWND hWnd, HWND a2, int a3, int a4);
int J3DAPI jonesConfig_sub_4096F0(int a1, HWND hWnd, int a3, HWND* a4, uint32_t* a5);
char J3DAPI jonesConfig_sub_4097D0(HWND a1, HWND hWnd, int a3, int a4);
LPARAM J3DAPI jonesConfig_sub_409BC0(int a1, HWND hWnd, int a3, int a4);
int J3DAPI jonesConfig_AssignKeyAction(HWND hWnd, uint32_t* dwInitParam);
int J3DAPI jonesConfig_sub_409F70(int a1, int a2, int* a3, int a4, int* a5);
INT_PTR __stdcall jonesConfig_AssignKeyDlgProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_sub_40A1A0(HWND hDlg, int a2, uint32_t* dwNewLong);
void J3DAPI jonesConfig_AssignControlKey(HWND hWnd);
int J3DAPI jonesConfig_sub_40A500(int a1);
void J3DAPI jonesConfig_AssignKeyDlg_HandleWM_COMMAND(HWND hWnd, int a2);
int J3DAPI jonesConfig_ShowReassignKeyMsgBox(HWND hWnd, LPARAM dwInitParam);
INT_PTR __stdcall jonesConfig_ReassignKeyDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_SetReassignKeyDialogText(HWND hDlg, int a2, void* dwNewLong);
int J3DAPI jonesConfig_sub_40AA10(HWND hWnd, int nResult);
int J3DAPI jonesConfig_ShowDisplaySettingsDialog(HWND hWnd, StdDisplayEnvironment* pDisplayEnv, JonesDisplaySettings* pDSettings);
INT_PTR __stdcall jonesConfig_DisplaySettingsDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_sub_40AE90(HWND hDlg, int a2, int* dwNewLong);
int J3DAPI jonesConfig_sub_40B530(const char* a1, const char* a2, int a3);
int J3DAPI jonesConfig_sub_40B5A0(HWND hWnd, int nResult, int a3, int a4);
uint32_t J3DAPI jonesConfig_ShowAdvanceDisplaySettings(HWND hWnd, LPARAM dwInitParam);
INT_PTR __stdcall jonesConfig_AdvanceDisplaySettingsDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_sub_40BC40(int a1, int a2, int a3);
int J3DAPI jonesConfig_sub_40BCD0(HWND hDlg, int a2, uint32_t* dwNewLong);
int J3DAPI jonesConfig_sub_40C090(HWND hWnd, int nResult, int a3, int a4);
int J3DAPI jonesConfig_ShowSoundSettingsDialog(HWND hWnd, float* dwInitParam);
INT_PTR __stdcall jonesConfig_SoundSettingsDialogProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_sub_40C650(HWND hDlg, int a2, LONG dwNewLong);
int J3DAPI jonesConfig_SoundSettings_HandleWM_COMMAND(HWND hWnd, int nResult);
int J3DAPI jonesConfig_ShowGameOverDialog(HWND hWnd, char* pRestoreFilename, tSoundHandle hSndGameOVerMus, tSoundChannelHandle* pSndChnlMus);
INT_PTR __stdcall jonesConfig_GameOverDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void J3DAPI jonesConfig_LoadGameGetLastSavedGamePath(char* pPath, unsigned int size);
int J3DAPI jonesConfig_GameOverDialogInit(HWND hDlg, int a2, GameOverDialogData* pData);
void J3DAPI jonesConfig_GameOverDialog_HandleWM_COMMAND(HWND hWnd, uint16_t wParam);
int J3DAPI jonesConfig_ShowStatisticsDialog(HWND hWnd, SithGameStatistics* pStatistics);
INT_PTR __stdcall jonesConfig_StatisticsDialogProc(HWND hwnd, UINT uMsg, WPARAM wPAram, LPARAM lParam);
int J3DAPI jonesConfig_sub_40D100(int a1, HWND hWnd, int a3, int a4);
void J3DAPI jonesConfig_UpdateCurrentLevelNum();
int J3DAPI jonesConfig_DrawImageOnDialogItem(HWND hDlg, HDC hdcWnd, HDC hdcCtrl, int nIDDlgItem, HBITMAP hImage, HBITMAP hMask);
int J3DAPI jonesConfig_SetStatisticsDialogForLevel(HWND hDlg, int levelNum, int* a3);
void J3DAPI jonesConfig_DrawStatisticDialogIQPoints(HWND hwnd, JonesDialogImageInfo** ppImageInfo, int dlgID, int iqpoints);
int J3DAPI jonesConfig_InitStatisticDialog(HWND hDlg, int a2, int* pData);
void J3DAPI jonesConfig_StatisticProc_HandleWM_COMMAND(HWND hWnd, int16_t wParam);
int J3DAPI jonesConfig_ShowLevelCompletedDialog(HWND hWnd, int* pBalance, int* apItemsState, int a4, int elapsedTime, int qiPoints, int numFoundTrasures, int foundTrasureValue, int totalTreasureValue);
int __stdcall jonesConfig_LevelCompletedDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_InitLevelCompletedDialog(HWND hDlg, int wParam, tLevelCompletedDialogState* pState);
void J3DAPI jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND(HWND hWnd, int wParam);
int J3DAPI jonesConfig_ShowStoreDialog(HWND hWnd, int* pBalance, int* pItemsState, int a4);
int __stdcall jonesConfig_StoreDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int J3DAPI jonesConfig_StoreHandleDragEvent(HWND hwnd, HWND hDlgCtrl);
void J3DAPI jonesConfig_StoreDialog_HandleWM_MBUTTONUP(HWND hWnd);
BOOL J3DAPI jonesConfig_StoreDialog_HandleWM_MOUSEFIRST(HWND hWnd);
int J3DAPI jonesConfig_InitStoreDialog(HWND hDlg, int a2, tStoreCartState* pCart);
int J3DAPI jonesConfig_StoreInitItemIcons(HWND hWnd, tStoreCartState* pCart);
LRESULT J3DAPI jonesConfig_StoreSetListColumns(HWND hList, const char* pColumnName);
void J3DAPI jonesConfig_StoreInitItemList(HWND hWnd, int* apItemsState, int listID);
void J3DAPI jonesConfig_UpdateBalances(HWND hDlg, tStoreCartState* pCart);
void J3DAPI jonesConfig_AddStoreCartItem(HWND hDlg, tStoreCartState* pCart);
void J3DAPI jonesConfig_RemoveStoreCartItem(HWND hDlg, tStoreCartState* pCart);
void J3DAPI jonesConfig_StoreDialog_HandleWM_COMMAND(HWND hWnd, WPARAM wParam);
void J3DAPI jonesConfig_ClearStoreCart(HWND hDlg, tStoreCartState* pCart);
int J3DAPI jonesConfig_ShowPurchaseMessageBox(HWND hWnd, tStoreCartState* dwInitParam);
INT_PTR __stdcall jonesConfig_PurchaseMessageBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_InitPurchaseMessageBox(HWND hDlg, int a2, tStoreCartState* pCart);
int J3DAPI jonesConfig_ShowDialogInsertCD(HWND hWnd, LPARAM dwInitParam);
INT_PTR CALLBACK jonesConfig_DialogInsertCDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int J3DAPI jonesConfig_InitDialogInsertCD(HWND hDlg, int a2, int cdNum);
int J3DAPI jonesConfig_InsertCD_HandleWM_COMMAND(HWND hWnd, int nResult);

// Helper hooking functions
void jonesConfig_InstallHooks(void);
void jonesConfig_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESCONFIG_H
