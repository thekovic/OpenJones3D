#define _CRT_SECURE_NO_WARNINGS
#include "jonesConfig.h"
#include <j3dcore/j3dhook.h>

#include <Jones3D/Display/JonesHud.h>
#include <Jones3D/Display/JonesHudConstants.h>
#include <Jones3D/Gui/JonesDialog.h>
#include <Jones3D/Main/JonesFile.h>
#include <Jones3D/Main/JonesLevel.h>
#include <Jones3D/Main/JonesMain.h>
#include <Jones3D/Main/jonesString.h>
#include <Jones3D/Play/JonesControl.h>
#include <Jones3D/Play/jonesInventory.h>
#include <Jones3D/RTI/symbols.h>

#include <rdroid/Main/rdroid.h>
#include <rdroid/Raster/rdCache.h>

#include <sith/Devices/sithControl.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/DSS/sithGamesave.h>
#include <sith/Engine/sithRender.h>
#include <sith/Gameplay/sithOverlayMap.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithVoice.h>
#include <sith/World/sithWorld.h>

#include <std/General/std.h>
#include <std/General/stdFnames.h>
#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>
#include <std/Win95/stdControl.h>
#include <std/Win95/stdDisplay.h>
#include <std/Win95/stdWin95.h>

#include <sound/Sound.h>

#include <w32util/wuRegistry.h>

#include <math.h>

#define JONESCONFIG_NOFONTSCALEMASK 1119
#define JONESCONFIG_NOFONTSCALE(dlgID) MAKELONG(dlgID, JONESCONFIG_NOFONTSCALEMASK)
#define JONES_CONTROL_ACTION_COUNT 37
#define SHIWORD(x) ((int16_t)((uint32_t)(x) >> 16))
#define BYTE1(x) (((x) >> 8) & 0xFF)

typedef struct sLoadGameDialogData
{
    HDC hdcThumbnail;
    char aFilePath[128];
    HBITMAP hThumbnail;
    int pfThubnailProc;
    int bFolderSel;
    int unknown36;
    int unknown37;
} LoadGameDialogData;

typedef struct sSaveGameDialogData
{
    HDC hdcThumbnail;
    char aFilePath[128];
    HBITMAP hThumbnail;
    int pfThumbnailProc;
    int bFolderSel;
} SaveGameDialogData;

typedef struct sJonesDialogFontScaleMetrics
{
    int dialogID;
    int refWidth;
    int refHeight;
} JonesDialogSize;
static_assert(sizeof(JonesDialogSize) == 12, "sizeof(JonesDialogSize) == 12");

static const JonesDialogSize jonesConfig_aDialogSizes[21] = {
   { 164, 368, 232 },
   { 112, 260, 252 },
   { 111, 408, 218 },
   { 116, 297, 95 },
   { 115, 549, 367 },
   { 117, 309, 103 },
   { 120, 282, 152 },
   { 114, 238, 285 },
   { 148, 440, 393 },
   { 113, 351, 206 },
   { 211, 266, 103 },
   { 163, 282, 90 },
   { 214, 282, 90 },
   { 121, 282, 90 },
   { 150, 249, 100 },
   { 233, 344, 180 },
   { 190, 538, 297 },
   { 212, 280, 74 },
   { 159, 583, 330 }, // Changed: height to 330 from 250
   { 154, 579, 332 }, // Changed: height to 332 from 252
   { 167, 279, 75 }
};

// jonesConfig_DrawStatisticDialogIQPoints
static const StdRect jonesConfig_aNumberGlyphMetrics[10] =
{
  { 11, 2, 44, 45 },
  { 49, 2, 69, 45 },
  { 78, 2, 106, 45 },
  { 110, 2, 138, 45 },
  { 11, 76, 44, 120 },
  { 45, 76, 75, 120 },
  { 77, 76, 107, 120 },
  { 11, 150, 45, 194 },
  { 45, 150, 75, 194 },
  { 76, 150, 107, 194 }
};

// Game save dialog
static HFONT jonesConfig_hFontSaveGameDlg = NULL;

// Game load dialog
static HFONT jonesConfig_hFontLoadGameDlg = NULL;

// Game play options dialog
static HFONT jonesConfig_hFontGamePlayOptionsDlg = NULL;

// Exit game dialog
static HFONT jonesConfig_hFontExitDlg = NULL;

// Chapter completed dialog
static int jonesConfig_prevLevelNum = -1;
static HFONT jonesConfig_hFontLevelCopletedDialog;

// Store dialog
static HFONT jonesConfig_hFontStoreDialog;
static HFONT jonesConfig_hFontPurchaseMessageBox;

// CD dialog
static HFONT jonesConfig_hFontDialogInsertCD;

//#define jonesConfig_aNumberGlyphMetrics J3D_DECL_FAR_ARRAYVAR(jonesConfig_aNumberGlyphMetrics, StdRect(*)[10])
#define jonesConfig_apDialogIconFiles J3D_DECL_FAR_ARRAYVAR(jonesConfig_apDialogIconFiles, char*(*)[6])
#define jonesConfig_aLevelNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aLevelNames, const char*(*)[17])
#define jonesConfig_JONES_STR_SUMMERY J3D_DECL_FAR_VAR(jonesConfig_JONES_STR_SUMMERY, const char*)
#define jonesConfig_aJonesControlActionNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aJonesControlActionNames, const char*(*)[37])
#define jonesConfig_aJonesCapControlActionNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aJonesCapControlActionNames, const char*(*)[37])
#define jonesConfig_aDfltKeySets J3D_DECL_FAR_ARRAYVAR(jonesConfig_aDfltKeySets, int*(*)[3])
#define jonesConfig_aDfltKeySetNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aDfltKeySetNames, const char*(*)[3])
#define jonesConfig_aControlKeyStrings J3D_DECL_FAR_ARRAYVAR(jonesConfig_aControlKeyStrings, const char*(*)[223])
// #define jonesConfig_aDialogSizes J3D_DECL_FAR_ARRAYVAR(jonesConfig_aDialogSizes, JonesDialogSize(*)[21])
#define jonesConfig_dword_511954 J3D_DECL_FAR_VAR(jonesConfig_dword_511954, int)
#define jonesConfig_dword_511958 J3D_DECL_FAR_VAR(jonesConfig_dword_511958, int)
#define jonesConfig_perfLevel J3D_DECL_FAR_VAR(jonesConfig_perfLevel, int)
//#define jonesConfig_prevLevelNum J3D_DECL_FAR_VAR(jonesConfig_prevLevelNum, int)
#define jonesConfig_dword_5510B8 J3D_DECL_FAR_VAR(jonesConfig_dword_5510B8, int)
#define jonesConfig_dword_5510BC J3D_DECL_FAR_VAR(jonesConfig_dword_5510BC, int)
#define jonesConfig_dword_5510C0 J3D_DECL_FAR_VAR(jonesConfig_dword_5510C0, int)
#define jonesConfig_dword_5510C4 J3D_DECL_FAR_VAR(jonesConfig_dword_5510C4, int)
#define jonesConfig_curControlConfig J3D_DECL_FAR_VAR(jonesConfig_curControlConfig, JonesControlsConfig)
#define jonesConfig_dword_5510E0 J3D_DECL_FAR_VAR(jonesConfig_dword_5510E0, int)
#define jonesConfig_aGlyphMetrics J3D_DECL_FAR_ARRAYVAR(jonesConfig_aGlyphMetrics, ABC(*)[256])
#define jonesConfig_textMetric J3D_DECL_FAR_VAR(jonesConfig_textMetric, TEXTMETRICA)
#define jonesConfig_dword_551D20 J3D_DECL_FAR_VAR(jonesConfig_dword_551D20, unsigned int)
#define jonesConfig_apDialogIcons J3D_DECL_FAR_ARRAYVAR(jonesConfig_apDialogIcons, HBITMAP(*)[6])
#define jonesConfig_pKeySetsDirPath J3D_DECL_FAR_ARRAYVAR(jonesConfig_pKeySetsDirPath, char(*)[128])
#define jonesConfig_bDefaultRun J3D_DECL_FAR_VAR(jonesConfig_bDefaultRun, UINT)
#define jonesConfig_curLevelNum J3D_DECL_FAR_VAR(jonesConfig_curLevelNum, int)
#define jonesConfig_bStartup J3D_DECL_FAR_VAR(jonesConfig_bStartup, int)
#define jonesConfig_dword_551DCC J3D_DECL_FAR_VAR(jonesConfig_dword_551DCC, int)
#define jonesConfig_hdo_551DD0 J3D_DECL_FAR_VAR(jonesConfig_hdo_551DD0, HGDIOBJ)
//#define jonesConfig_hFontSaveGameDlg J3D_DECL_FAR_VAR(jonesConfig_hFontSaveGameDlg, HFONT)
//#define jonesConfig_hFontExitDlg J3D_DECL_FAR_VAR(jonesConfig_hFontExitDlg, HFONT)
#define jonesConfig_hFontGameSaveMsgBox J3D_DECL_FAR_VAR(jonesConfig_hFontGameSaveMsgBox, HFONT)
//#define jonesConfig_hFontLoadGameDlg J3D_DECL_FAR_VAR(jonesConfig_hFontLoadGameDlg, HFONT)
//#define jonesConfig_hFontGamePlayOptionsDlg J3D_DECL_FAR_VAR(jonesConfig_hFontGamePlayOptionsDlg, HFONT)
#define jonesConfig_hFontControlOptions J3D_DECL_FAR_VAR(jonesConfig_hFontControlOptions, HFONT)
#define jonesConfig_dword_551DEC J3D_DECL_FAR_VAR(jonesConfig_dword_551DEC, void*)
#define jonesConfig_hFontCreateControlSchemeDlg J3D_DECL_FAR_VAR(jonesConfig_hFontCreateControlSchemeDlg, HFONT)
#define jonesConfig_hFontEditControlShceme J3D_DECL_FAR_VAR(jonesConfig_hFontEditControlShceme, HFONT)
#define jonesConfig_hFontAssignKeyDlg J3D_DECL_FAR_VAR(jonesConfig_hFontAssignKeyDlg, HFONT)
#define jonesConfig_bControlsActive J3D_DECL_FAR_VAR(jonesConfig_bControlsActive, int)
#define jonesConfig_hFontReassignKeyDlg J3D_DECL_FAR_VAR(jonesConfig_hFontReassignKeyDlg, HFONT)
#define jonesConfig_hFontDisplaySettingsDlg J3D_DECL_FAR_VAR(jonesConfig_hFontDisplaySettingsDlg, HFONT)
#define jonesConfig_hFontAdvanceDisplaySettingsDialog J3D_DECL_FAR_VAR(jonesConfig_hFontAdvanceDisplaySettingsDialog, HFONT)
#define jonesConfig_hFontSoundSettings J3D_DECL_FAR_VAR(jonesConfig_hFontSoundSettings, HFONT)
#define jonesConfig_hSndChannel J3D_DECL_FAR_VAR(jonesConfig_hSndChannel, tSoundChannelHandle)
#define jonesConfig_dword_551E14 J3D_DECL_FAR_VAR(jonesConfig_dword_551E14, int)
#define jonesConfig_hFontGameOverDialog J3D_DECL_FAR_VAR(jonesConfig_hFontGameOverDialog, HFONT)
#define jonesConfig_dword_551E1C J3D_DECL_FAR_VAR(jonesConfig_dword_551E1C, HGDIOBJ)
//#define jonesConfig_hFontLevelCopletedDialog J3D_DECL_FAR_VAR(jonesConfig_hFontLevelCopletedDialog, HFONT)
//#define jonesConfig_hFontStoreDialog J3D_DECL_FAR_VAR(jonesConfig_hFontStoreDialog, HFONT)
//#define jonesConfig_hFontPurchaseMessageBox J3D_DECL_FAR_VAR(jonesConfig_hFontPurchaseMessageBox, HFONT)
//#define jonesConfig_hFontDialogInsertCD J3D_DECL_FAR_VAR(jonesConfig_hFontDialogInsertCD, HFONT)

void J3DAPI jonesConfig_MsgBoxDlg_HandleWM_COMMAND(HWND hWnd, int nResult);

void jonesConfig_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    J3D_HOOKFUNC(jonesConfig_Startup);
    J3D_HOOKFUNC(jonesConfig_InitKeySetsPath);
    J3D_HOOKFUNC(jonesConfig_InitKeyActions);
    J3D_HOOKFUNC(jonesConfig_Shutdown);
    J3D_HOOKFUNC(jonesConfig_ControlToString);
    J3D_HOOKFUNC(jonesConfig_ShowMessageDialog);
    J3D_HOOKFUNC(jonesConfig_MessageDialogProc);
    J3D_HOOKFUNC(jonesConfig_sub_4025F0);
    J3D_HOOKFUNC(jonesConfig_sub_402670);
    J3D_HOOKFUNC(jonesConfig_SetTextControl);
    J3D_HOOKFUNC(jonesConfig_sub_402A90);
    J3D_HOOKFUNC(jonesConfig_NewControlScheme);
    J3D_HOOKFUNC(jonesConfig_LoadConstrolsScheme);
    J3D_HOOKFUNC(jonesConfig_GetEntryIndex);
    J3D_HOOKFUNC(jonesConfig_GetValueIndex);
    J3D_HOOKFUNC(jonesConfig_GetControllerKeySchemeIndex);
    J3D_HOOKFUNC(jonesConfig_SetDefaultControlScheme);
    J3D_HOOKFUNC(jonesConfig_BindControls);
    J3D_HOOKFUNC(jonesConfig_BindJoystickControl);
    J3D_HOOKFUNC(jonesConfig_InitDialog);
    J3D_HOOKFUNC(jonesConfig_CreateDialogFont);
    J3D_HOOKFUNC(jonesConfig_ResetDialogFont);
    J3D_HOOKFUNC(jonesConfig_ResetWindowFontCallback);
    J3D_HOOKFUNC(jonesConfig_SetPositionAndTextCallback);
    J3D_HOOKFUNC(jonesConfig_SetWindowFontAndPosition);
    J3D_HOOKFUNC(jonesConfig_GetWindowScreenRect);
    J3D_HOOKFUNC(jonesConfig_SetDialogTitleAndPosition);
    J3D_HOOKFUNC(jonesConfig_GetSaveGameFilePath);
    J3D_HOOKFUNC(jonesConfig_SaveGameDialogHookProc);
    J3D_HOOKFUNC(jonesConfig_SaveGameDialogInit);
    J3D_HOOKFUNC(jonesConfig_SaveGameThumbnailPaintProc);
    J3D_HOOKFUNC(jonesConfig_ShowOverwriteSaveGameDlg);
    J3D_HOOKFUNC(jonesConfig_ShowExitGameDialog);
    J3D_HOOKFUNC(jonesConfig_ExitGameDlgProc);
    J3D_HOOKFUNC(jonesConfig_SaveGameMsgBoxProc);
    J3D_HOOKFUNC(jonesConfig_GameSaveSetData);
    J3D_HOOKFUNC(jonesConfig_MsgBoxDlg_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_GetLoadGameFilePath);
    J3D_HOOKFUNC(jonesConfig_sub_405F60);
    J3D_HOOKFUNC(jonesConfig_LoadGameDialogHookProc);
    J3D_HOOKFUNC(jonesConfig_ShowLoadGameWarningMsgBox);
    J3D_HOOKFUNC(jonesConfig_LoadGameDialogInit);
    J3D_HOOKFUNC(jonesConfig_LoadGameThumbnailPaintProc);
    J3D_HOOKFUNC(jonesConfig_ShowGamePlayOptions);
    J3D_HOOKFUNC(jonesConfig_GamePlayOptionsProc);
    J3D_HOOKFUNC(jonesConfig_HandleWM_HSCROLL);
    J3D_HOOKFUNC(jonesConfig_GamePlayOptionsInitDlg);
    J3D_HOOKFUNC(jonesConfig_GamePlayOptions_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_EnableMouseControl);
    J3D_HOOKFUNC(jonesConfig_FreeControlScheme);
    J3D_HOOKFUNC(jonesConfig_FreeControlConfigEntry);
    J3D_HOOKFUNC(jonesConfig_ShowControlOptions);
    J3D_HOOKFUNC(jonesConfig_CopyControlConfig);
    J3D_HOOKFUNC(jonesConfig_CopyControlSchemes);
    J3D_HOOKFUNC(jonesConfig_InitControlsConfig);
    J3D_HOOKFUNC(jonesConfig_LoadControlsSchemesFromSystem);
    J3D_HOOKFUNC(jonesConfig_SetDefaultControlSchemes);
    J3D_HOOKFUNC(jonesConfig_ControlOptionsProc);
    J3D_HOOKFUNC(jonesConfig_InitControlOptionsDlg);
    J3D_HOOKFUNC(jonesConfig_ControlOptions_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_WriteScheme);
    J3D_HOOKFUNC(jonesConfig_sub_407F60);
    J3D_HOOKFUNC(jonesConfig_sub_408000);
    J3D_HOOKFUNC(jonesConfig_sub_408260);
    J3D_HOOKFUNC(jonesConfig_sub_408400);
    J3D_HOOKFUNC(jonesConfig_CreateNewSchemeAction);
    J3D_HOOKFUNC(jonesConfig_ShowCreateControlSchemeDialog);
    J3D_HOOKFUNC(jonesConfig_CreateControlSchemeProc);
    J3D_HOOKFUNC(jonesConfig_InitCreateControlScheme);
    J3D_HOOKFUNC(jonesConfig_CreateControlScheme_Handle_WM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowEditControlShemeDialog);
    J3D_HOOKFUNC(jonesConfig_EditControlSchemProc);
    J3D_HOOKFUNC(jonesConfig_InitEditControlSchemeDlg);
    J3D_HOOKFUNC(jonesConfig_sub_408ED0);
    J3D_HOOKFUNC(jonesConfig_sub_408FC0);
    J3D_HOOKFUNC(jonesConfig_sub_409200);
    J3D_HOOKFUNC(jonesConfig_sub_409530);
    J3D_HOOKFUNC(jonesConfig_sub_4096F0);
    J3D_HOOKFUNC(jonesConfig_sub_4097D0);
    J3D_HOOKFUNC(jonesConfig_sub_409BC0);
    J3D_HOOKFUNC(jonesConfig_AssignKeyAction);
    J3D_HOOKFUNC(jonesConfig_sub_409F70);
    J3D_HOOKFUNC(jonesConfig_AssignKeyDlgProc);
    J3D_HOOKFUNC(jonesConfig_sub_40A1A0);
    J3D_HOOKFUNC(jonesConfig_AssignControlKey);
    J3D_HOOKFUNC(jonesConfig_sub_40A500);
    J3D_HOOKFUNC(jonesConfig_AssignKeyDlg_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowReassignKeyMsgBox);
    J3D_HOOKFUNC(jonesConfig_ReassignKeyDialogProc);
    J3D_HOOKFUNC(jonesConfig_SetReassignKeyDialogText);
    J3D_HOOKFUNC(jonesConfig_sub_40AA10);
    J3D_HOOKFUNC(jonesConfig_ShowDisplaySettingsDialog);
    J3D_HOOKFUNC(jonesConfig_DisplaySettingsDialogProc);
    J3D_HOOKFUNC(jonesConfig_sub_40AE90);
    J3D_HOOKFUNC(jonesConfig_sub_40B530);
    J3D_HOOKFUNC(jonesConfig_sub_40B5A0);
    J3D_HOOKFUNC(jonesConfig_ShowAdvanceDisplaySettings);
    J3D_HOOKFUNC(jonesConfig_AdvanceDisplaySettingsDialog);
    J3D_HOOKFUNC(jonesConfig_sub_40BC40);
    J3D_HOOKFUNC(jonesConfig_sub_40BCD0);
    J3D_HOOKFUNC(jonesConfig_sub_40C090);
    J3D_HOOKFUNC(jonesConfig_ShowSoundSettingsDialog);
    J3D_HOOKFUNC(jonesConfig_SoundSettingsDialogProc);
    J3D_HOOKFUNC(jonesConfig_sub_40C650);
    J3D_HOOKFUNC(jonesConfig_SoundSettings_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowGameOverDialog);
    J3D_HOOKFUNC(jonesConfig_GameOverDialogProc);
    J3D_HOOKFUNC(jonesConfig_LoadGameGetLastSavedGamePath);
    J3D_HOOKFUNC(jonesConfig_GameOverDialogInit);
    J3D_HOOKFUNC(jonesConfig_GameOverDialog_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowStatisticsDialog);
    J3D_HOOKFUNC(jonesConfig_StatisticsDialogProc);
    J3D_HOOKFUNC(jonesConfig_sub_40D100);
    J3D_HOOKFUNC(jonesConfig_UpdateCurrentLevelNum);
    J3D_HOOKFUNC(jonesConfig_DrawImageOnDialogItem);
    J3D_HOOKFUNC(jonesConfig_SetStatisticsDialogForLevel);
    J3D_HOOKFUNC(jonesConfig_DrawStatisticDialogIQPoints);
    J3D_HOOKFUNC(jonesConfig_InitStatisticDialog);
    J3D_HOOKFUNC(jonesConfig_StatisticProc_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowLevelCompletedDialog);
    J3D_HOOKFUNC(jonesConfig_LevelCompletedDialogProc);
    J3D_HOOKFUNC(jonesConfig_InitLevelCompletedDialog);
    J3D_HOOKFUNC(jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ShowStoreDialog);
    J3D_HOOKFUNC(jonesConfig_StoreDialogProc);
    J3D_HOOKFUNC(jonesConfig_StoreHandleDragEvent);
    J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_MBUTTONUP);
    J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_MOUSEFIRST);
    J3D_HOOKFUNC(jonesConfig_InitStoreDialog);
    J3D_HOOKFUNC(jonesConfig_StoreInitItemIcons);
    J3D_HOOKFUNC(jonesConfig_StoreSetListColumns);
    J3D_HOOKFUNC(jonesConfig_StoreInitItemList);
    J3D_HOOKFUNC(jonesConfig_UpdateBalances);
    J3D_HOOKFUNC(jonesConfig_AddStoreCartItem);
    J3D_HOOKFUNC(jonesConfig_RemoveStoreCartItem);
    J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_ClearStoreCart);
    J3D_HOOKFUNC(jonesConfig_ShowPurchaseMessageBox);
    J3D_HOOKFUNC(jonesConfig_PurchaseMessageBoxProc);
    J3D_HOOKFUNC(jonesConfig_InitPurchaseMessageBox);
    J3D_HOOKFUNC(jonesConfig_ShowDialogInsertCD);
    J3D_HOOKFUNC(jonesConfig_DialogInsertCDProc);
    J3D_HOOKFUNC(jonesConfig_InitDialogInsertCD);
    J3D_HOOKFUNC(jonesConfig_InsertCD_HandleWM_COMMAND);
}

void jonesConfig_ResetGlobals(void)
{
    /*StdRect jonesConfig_aNumberGlyphMetrics_tmp[10] = {
      { 11, 2, 44, 45 },
      { 49, 2, 69, 45 },
      { 78, 2, 106, 45 },
      { 110, 2, 138, 45 },
      { 11, 76, 44, 120 },
      { 45, 76, 75, 120 },
      { 77, 76, 107, 120 },
      { 11, 150, 45, 194 },
      { 45, 150, 75, 194 },
      { 76, 150, 107, 194 }
    };
    memcpy(&jonesConfig_aNumberGlyphMetrics, &jonesConfig_aNumberGlyphMetrics_tmp, sizeof(jonesConfig_aNumberGlyphMetrics));*/

    char* jonesConfig_apDialogIconFiles_tmp[6] = {
      "iq.bmp",
      "iqMask.bmp",
      "iqOverlay.bmp",
      "numbers.bmp",
      "exit.bmp",
      "exitmask.bmp"
    };
    memcpy(&jonesConfig_apDialogIconFiles, &jonesConfig_apDialogIconFiles_tmp, sizeof(jonesConfig_apDialogIconFiles));

    const char* jonesConfig_aLevelNames_tmp[17] = {
      "JONES_STR_CYN",
      "JONES_STR_BAB",
      "JONES_STR_RIV",
      "JONES_STR_SHS",
      "JONES_STR_LAG",
      "JONES_STR_VOL",
      "JONES_STR_TEM",
      "JONES_STR_JEP",
      "JONES_STR_TEO",
      "JONES_STR_OLV",
      "JONES_STR_SEA",
      "JONES_STR_PYR",
      "JONES_STR_SOL",
      "JONES_STR_NUB",
      "JONES_STR_INF",
      "JONES_STR_AET",
      "JONES_STR_PRU"
    };
    memcpy((char**)&jonesConfig_aLevelNames, &jonesConfig_aLevelNames_tmp, sizeof(jonesConfig_aLevelNames));

    const char* jonesConfig_JONES_STR_SUMMERY_tmp = "JONES_STR_SUMMARY";
    memcpy((char**)&jonesConfig_JONES_STR_SUMMERY, &jonesConfig_JONES_STR_SUMMERY_tmp, sizeof(jonesConfig_JONES_STR_SUMMERY));

    const char* jonesConfig_aJonesControlActionNames_tmp[37] = {
      "JONES_STR_WLKFWD",
      "JONES_STR_WLKBK",
      "JONES_STR_TRNLFT",
      "JONES_STR_TRNRGHT",
      "JONES_STR_STPLFT",
      "JONES_STR_STPRGHT",
      "JONES_STR_CRAWL",
      "JONES_STR_RUN",
      "JONES_STR_ROLL",
      "JONES_STR_JUMP",
      "JONES_STR_LOOK",
      "JONES_STR_ACT",
      "JONES_STR_TGLWEAP",
      "JONES_STR_PREVWEAP",
      "JONES_STR_NEXTWEAP",
      "JONES_STR_TGLLGHT",
      "JONES_STR_FISTS",
      "JONES_STR_WHIP",
      "JONES_STR_MAUSER",
      "JONES_STR_PPSH41",
      "JONES_STR_PISTOL",
      "JONES_STR_SIMONOV",
      "JONES_STR_TOKEREV",
      "JONES_STR_TOZ34",
      "JONES_STR_BAZOOKA",
      "JONES_STR_MACHETE",
      "JONES_STR_SATCHEL",
      "JONES_STR_GRENADE",
      "JONES_STR_MAP",
      "JONES_STR_INTERFACE",
      "JONES_STR_HEALTH",
      "JONES_STR_IMP1",
      "JONES_STR_IMP2",
      "JONES_STR_IMP3",
      "JONES_STR_IMP4",
      "JONES_STR_IMP5",
      "JONES_STR_CHALK"
    };
    memcpy((char**)&jonesConfig_aJonesControlActionNames, &jonesConfig_aJonesControlActionNames_tmp, sizeof(jonesConfig_aJonesControlActionNames));

    const char* jonesConfig_aJonesCapControlActionNames_tmp[37] = {
      "JONES_STR_CAPS_WLKFWD",
      "JONES_STR_CAPS_WLKBK",
      "JONES_STR_CAPS_TRNLFT",
      "JONES_STR_CAPS_TRNRGHT",
      "JONES_STR_CAPS_STPLFT",
      "JONES_STR_CAPS_STPRGHT",
      "JONES_STR_CAPS_CRAWL",
      "JONES_STR_CAPS_RUN",
      "JONES_STR_CAPS_ROLL",
      "JONES_STR_CAPS_JUMP",
      "JONES_STR_CAPS_LOOK",
      "JONES_STR_CAPS_ACT",
      "JONES_STR_CAPS_TGLWEAP",
      "JONES_STR_CAPS_PREVWEAP",
      "JONES_STR_CAPS_NEXTWEAP",
      "JONES_STR_CAPS_TGLLGHT",
      "JONES_STR_CAPS_FISTS",
      "JONES_STR_CAPS_WHIP",
      "JONES_STR_CAPS_MAUSER",
      "JONES_STR_CAPS_PPSH41",
      "JONES_STR_CAPS_PISTOL",
      "JONES_STR_CAPS_SIMONOV",
      "JONES_STR_CAPS_TOKEREV",
      "JONES_STR_CAPS_TOZ34",
      "JONES_STR_CAPS_BAZOOKA",
      "JONES_STR_CAPS_MACHETE",
      "JONES_STR_CAPS_SATCHEL",
      "JONES_STR_CAPS_GRENADE",
      "JONES_STR_CAPS_MAP",
      "JONES_STR_CAPS_INTERFACE",
      "JONES_STR_CAPS_HEALTH",
      "JONES_STR_CAPS_IMP1",
      "JONES_STR_CAPS_IMP2",
      "JONES_STR_CAPS_IMP3",
      "JONES_STR_CAPS_IMP4",
      "JONES_STR_CAPS_IMP5",
      "JONES_STR_CAPS_CHALK"
    };
    memcpy((char**)&jonesConfig_aJonesCapControlActionNames, &jonesConfig_aJonesCapControlActionNames_tmp, sizeof(jonesConfig_aJonesCapControlActionNames));

    // TODO: define keysets and uncomment
    /*int *jonesConfig_aDfltKeySets_tmp[3] = {
      &jonesConfig_aDfltKeyboardSets,
      &jonesConfig_aDflt2a4b,
      &jonesConfig_aDflt2a8b
    };
    memcpy(&jonesConfig_aDfltKeySets, &jonesConfig_aDfltKeySets_tmp, sizeof(jonesConfig_aDfltKeySets));*/

    const char* jonesConfig_aDfltKeySetNames_tmp[3] = { "JONES_STR_DFLTKEY", "JONES_STR_DFLT2A4B", "JONES_STR_DFLT2A8B" };
    memcpy((char**)&jonesConfig_aDfltKeySetNames, &jonesConfig_aDfltKeySetNames_tmp, sizeof(jonesConfig_aDfltKeySetNames));

    const char* jonesConfig_aControlKeyStrings_tmp[223] = {
      NULL,
      "JONES_STR_ESCAPE",
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9",
      "0",
      "JONES_STR_MINUS",
      "JONES_STR_EQUAL",
      "JONES_STR_BACK",
      "JONES_STR_TAB",
      "Q",
      "W",
      "E",
      "R",
      "T",
      "posY",
      "U",
      "I",
      "O",
      "P",
      "JONES_STR_LEFT_BRCKT",
      "JONES_STR_RIGHT_BRCKT",
      "JONES_STR_ENTER",
      "JONES_STR_LEFT_CTRL",
      "A",
      "S",
      "D",
      "F",
      "G",
      "H",
      "J",
      "K",
      "L",
      ";",
      "'",
      "`",
      "JONES_STR_LEFT_SHIFT",
      "\\",
      "Z",
      "X",
      "C",
      "V",
      "B",
      "N",
      "M",
      "JONES_STR_COMMA",
      ".",
      "/",
      "JONES_STR_RIGHT_SHIFT",
      "JONES_STR_NUMPAD_MULT",
      "JONES_STR_LEFT_ALT",
      "JONES_STR_SPACE",
      "JONES_STR_CAPS",
      "JONES_STR_F1",
      "JONES_STR_F2",
      "JONES_STR_F3",
      "JONES_STR_F4",
      "JONES_STR_F5",
      "JONES_STR_F6",
      "JONES_STR_F7",
      "JONES_STR_F8",
      "JONES_STR_F9",
      "JONES_STR_F10",
      "JONES_STR_NUMLOCK",
      "JONES_STR_SCROLL",
      "JONES_STR_NUMPAD_7",
      "JONES_STR_NUMPAD_8",
      "JONES_STR_NUMPAD_9",
      "JONES_STR_NUMPAD_MINUS",
      "JONES_STR_NUMPAD_4",
      "JONES_STR_NUMPAD_5",
      "JONES_STR_NUMPAD_6",
      "JONES_STR_NUMPAD_PLUS",
      "JONES_STR_NUMPAD_1",
      "JONES_STR_NUMPAD_2",
      "JONES_STR_NUMPAD_3",
      "JONES_STR_NUMPAD_0",
      "JONES_STR_NUMPAD_DOT",
      NULL,
      NULL,
      NULL,
      "JONES_STR_F11",
      "JONES_STR_F12",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_F13",
      "JONES_STR_F14",
      "JONES_STR_F15",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_NUMPAD_EQL",
      NULL,
      NULL,
      NULL,
      "@",
      ":",
      "__",
      NULL,
      "STOP",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_NUMPAD_ENTER",
      "JONES_STR_RIGHT_CTRL",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_NUMPAD_COMMA",
      NULL,
      "JONES_STR_NUMPAD_DIV",
      NULL,
      "JONES_STR_SYSRQ",
      "JONES_STR_RIGHT_ALT",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_HOME",
      "JONES_STR_UPARRW",
      "JONES_STR_PAGEUP",
      NULL,
      "JONES_STR_LEFTARRW",
      NULL,
      "JONES_STR_RGHTARRW",
      NULL,
      "JONES_STR_END",
      "JONES_STR_DNARRW",
      "JONES_STR_PGDN",
      "JONES_STR_INSERT",
      "JONES_STR_DELETE",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_LEFT_WND",
      "JONES_STR_RIGHT_WND",
      "JONES_STR_APPS",
      NULL
    };
    memcpy((char**)&jonesConfig_aControlKeyStrings, &jonesConfig_aControlKeyStrings_tmp, sizeof(jonesConfig_aControlKeyStrings));

    /*   JonesDialogSize jonesConfig_aFontScaleFactors_tmp[21] = {
         { 164, 368, 232 },
         { 112, 260, 224 },
         { 111, 408, 218 },
         { 116, 297, 95 },
         { 115, 549, 367 },
         { 117, 309, 103 },
         { 120, 282, 152 },
         { 114, 238, 285 },
         { 148, 440, 393 },
         { 113, 351, 206 },
         { 211, 266, 103 },
         { 163, 282, 90 },
         { 214, 282, 90 },
         { 121, 282, 90 },
         { 150, 249, 100 },
         { 233, 344, 180 },
         { 190, 538, 297 },
         { 212, 280, 74 },
         { 159, 583, 250 },
         { 154, 579, 252 },
         { 167, 279, 75 }
       };
       memcpy(&jonesConfig_aDialogSizes, &jonesConfig_aFontScaleFactors_tmp, sizeof(jonesConfig_aDialogSizes));*/

    int jonesConfig_dword_511954_tmp = 1;
    memcpy(&jonesConfig_dword_511954, &jonesConfig_dword_511954_tmp, sizeof(jonesConfig_dword_511954));

    int jonesConfig_dword_511958_tmp = 1;
    memcpy(&jonesConfig_dword_511958, &jonesConfig_dword_511958_tmp, sizeof(jonesConfig_dword_511958));

    int jonesConfig_perfLevel_tmp = 4;
    memcpy(&jonesConfig_perfLevel, &jonesConfig_perfLevel_tmp, sizeof(jonesConfig_perfLevel));

    /*int jonesConfig_prevLevelNum_tmp = -1;
    memcpy(&jonesConfig_prevLevelNum, &jonesConfig_prevLevelNum_tmp, sizeof(jonesConfig_prevLevelNum));*/


    jonesConfig_dword_5510B8 = 0;
    jonesConfig_dword_5510BC = 0;
    jonesConfig_dword_5510C0 = 0;
    jonesConfig_dword_5510C4 = 0;
    JonesControlsConfig jonesConfig_curControlConfig_tmp = { NULL, 0, 0, 0, 0, NULL };
    memcpy(&jonesConfig_curControlConfig, &jonesConfig_curControlConfig_tmp, sizeof(jonesConfig_curControlConfig));

    jonesConfig_dword_5510E0 = 0;
    ABC jonesConfig_aGlyphMetrics_tmp[256] = {
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0, 0u, 0 },
      { 0,  }
    };
    memcpy(&jonesConfig_aGlyphMetrics, &jonesConfig_aGlyphMetrics_tmp, sizeof(jonesConfig_aGlyphMetrics));

    memset(&jonesConfig_textMetric, 0, sizeof(jonesConfig_textMetric));
    memset(&jonesConfig_dword_551D20, 0, sizeof(jonesConfig_dword_551D20));
    memset(&jonesConfig_apDialogIcons, 0, sizeof(jonesConfig_apDialogIcons));
    memset(&jonesConfig_pKeySetsDirPath, 0, sizeof(jonesConfig_pKeySetsDirPath));
    memset(&jonesConfig_bDefaultRun, 0, sizeof(jonesConfig_bDefaultRun));
    memset(&jonesConfig_curLevelNum, 0, sizeof(jonesConfig_curLevelNum));
    memset(&jonesConfig_bStartup, 0, sizeof(jonesConfig_bStartup));
    memset(&jonesConfig_dword_551DCC, 0, sizeof(jonesConfig_dword_551DCC));
    memset(&jonesConfig_hdo_551DD0, 0, sizeof(jonesConfig_hdo_551DD0));
   // memset(&jonesConfig_hFontSaveGameDlg, 0, sizeof(jonesConfig_hFontSaveGameDlg));
    //memset(&jonesConfig_hFontExitDlg, 0, sizeof(jonesConfig_hFontExitDlg));
    memset(&jonesConfig_hFontGameSaveMsgBox, 0, sizeof(jonesConfig_hFontGameSaveMsgBox));
    memset(&jonesConfig_hFontLoadGameDlg, 0, sizeof(jonesConfig_hFontLoadGameDlg));
    //memset(&jonesConfig_hFontGamePlayOptionsDlg, 0, sizeof(jonesConfig_hFontGamePlayOptionsDlg));
    memset(&jonesConfig_hFontControlOptions, 0, sizeof(jonesConfig_hFontControlOptions));
    memset(&jonesConfig_dword_551DEC, 0, sizeof(jonesConfig_dword_551DEC));
    memset(&jonesConfig_hFontCreateControlSchemeDlg, 0, sizeof(jonesConfig_hFontCreateControlSchemeDlg));
    memset(&jonesConfig_hFontEditControlShceme, 0, sizeof(jonesConfig_hFontEditControlShceme));
    memset(&jonesConfig_hFontAssignKeyDlg, 0, sizeof(jonesConfig_hFontAssignKeyDlg));
    memset(&jonesConfig_bControlsActive, 0, sizeof(jonesConfig_bControlsActive));
    memset(&jonesConfig_hFontReassignKeyDlg, 0, sizeof(jonesConfig_hFontReassignKeyDlg));
    memset(&jonesConfig_hFontDisplaySettingsDlg, 0, sizeof(jonesConfig_hFontDisplaySettingsDlg));
    memset(&jonesConfig_hFontAdvanceDisplaySettingsDialog, 0, sizeof(jonesConfig_hFontAdvanceDisplaySettingsDialog));
    memset(&jonesConfig_hFontSoundSettings, 0, sizeof(jonesConfig_hFontSoundSettings));
    memset(&jonesConfig_hSndChannel, 0, sizeof(jonesConfig_hSndChannel));
    memset(&jonesConfig_dword_551E14, 0, sizeof(jonesConfig_dword_551E14));
    memset(&jonesConfig_hFontGameOverDialog, 0, sizeof(jonesConfig_hFontGameOverDialog));
    memset(&jonesConfig_dword_551E1C, 0, sizeof(jonesConfig_dword_551E1C));
    /*memset(&jonesConfig_hFontLevelCopletedDialog, 0, sizeof(jonesConfig_hFontLevelCopletedDialog));
    memset(&jonesConfig_hFontStoreDialog, 0, sizeof(jonesConfig_hFontStoreDialog));
    memset(&jonesConfig_hFontPurchaseMessageBox, 0, sizeof(jonesConfig_hFontPurchaseMessageBox));
    memset(&jonesConfig_hFontDialogInsertCD, 0, sizeof(jonesConfig_hFontDialogInsertCD));*/

}

int jonesConfig_Startup(void)
{
    int result; // eax
    int idx; // esi
    HBITMAP hBmp; // eax
    int options; // eax
    JonesControlsScheme* pConfig; // eax
    JonesControlsScheme* pConfig_1; // esi
    HBITMAP* v6; // edi
    char szIconFilePath[128]; // [esp+Ch] [ebp-80h] BYREF

    if ( jonesConfig_bStartup )
    {
        return 1;
    }

    idx = 0;
    while ( 1 )
    {
        stdFnames_MakePath(szIconFilePath, 128, "misc", jonesConfig_apDialogIconFiles[idx]);
        hBmp = stdBmp_Load(szIconFilePath);
        jonesConfig_apDialogIcons[idx] = hBmp;
        if ( !hBmp )
        {
            break;
        }

        if ( ++idx >= 6 )
        {
            result = jonesConfig_InitKeySetsPath();
            if ( !result )
            {
                return result;
            }

            result = jonesConfig_InitKeyActions();
            if ( !result )
            {
                return result;
            }

            memset(jonesConfig_aGlyphMetrics, 0, sizeof(jonesConfig_aGlyphMetrics));
            memset(&jonesConfig_textMetric, 0, sizeof(jonesConfig_textMetric));

            jonesConfig_dword_551DCC = 0;

            jonesConfig_bDefaultRun = wuRegistry_GetIntEx("Default Run", 0);
            options = sithControl_g_controlOptions;
            if ( jonesConfig_bDefaultRun )
            {
                options = (options & 0xFF00) | ((sithControl_g_controlOptions | 2) & 0xFF);
            }
            else
            {
                options = (options & 0xFF00) | (sithControl_g_controlOptions & ~2 & 0xFF);
            }

            sithControl_g_controlOptions = options;
            jonesConfig_curLevelNum = 0;
            pConfig = jonesConfig_NewControlScheme();
            pConfig_1 = pConfig;
            if ( pConfig )
            {
                jonesConfig_BindControls(pConfig);
                jonesConfig_FreeControlScheme(pConfig_1);
            }

            result = 1;
            jonesConfig_bStartup = 1;
            return result;
        }
    }

    if ( idx > 0 )
    {
        v6 = jonesConfig_apDialogIcons;
        do
        {
            DeleteObject(*v6++);
            --idx;
        } while ( idx );
    }

    STDLOG_ERROR("Couldn't load bitmap %s.\n", szIconFilePath);
    return 0;
}

int J3DAPI jonesConfig_InitKeySetsPath()
{
    wchar_t* pwKeySets; // eax
    wchar_t* v1; // ebx
    char* pKeySets; // esi
    unsigned int len; // kr04_4
    char v5; // [esp+Bh] [ebp-81h]
    char aInstallPath[128]; // [esp+Ch] [ebp-80h] BYREF

    pwKeySets = sithString_GetString("SITHSTRING_KEYSETS");
    v1 = pwKeySets;
    if ( !pwKeySets )
    {
        return 0;
    }


    pKeySets = stdUtil_ToAString(pwKeySets);
    memset(aInstallPath, 0, sizeof(aInstallPath));
    wuRegistry_GetStr("Install Path", aInstallPath, 0x80u, std_g_aEmptyString);
    if ( pKeySets )
    {
        len = strlen(aInstallPath) + 1;
        if ( len == 1 )
        {
            sprintf(jonesConfig_pKeySetsDirPath, "..\\\\%s", pKeySets);
            stdMemory_Free(pKeySets);
            return 1;
        }
        else
        {
            if ( *(&v5 + len - 1) == '\\' )     // TODO: fix => if ( aInstallPath[len - 1] == '\\' )
            {
                sprintf(jonesConfig_pKeySetsDirPath, "%s%s", aInstallPath, pKeySets);
            }
            else
            {
                sprintf(jonesConfig_pKeySetsDirPath, "%s\\%s", aInstallPath, pKeySets);
            }

            stdMemory_Free(pKeySets);
            return 1;
        }
    }
    else
    {
        STDLOG_ERROR("Couldn't find string %s in lookup table.\n", pwKeySets);                               // TODO: [BUG] zero passd to %s; should probably be pwKeySets
        stdMemory_Free(v1);
        return 0;
    }
}

int J3DAPI jonesConfig_InitKeyActions()
{
    const char** pJSAction; // ebx
    const char* pActionName; // eax
    char* v2; // eax
    int v3; // esi
    unsigned int v4; // kr0C_4
    signed int controlId; // ebx
    int v6; // esi
    char* i; // eax
    int v8; // esi
    unsigned int v9; // kr10_4
    int result; // eax
    int v11; // [esp+0h] [ebp-30Ch] BYREF
    char aControlStr[256]; // [esp+Ch] [ebp-300h] BYREF
    char aActionName[512]; // [esp+10Ch] [ebp-200h] BYREF

    jonesConfig_dword_5510E0 = 0;
    jonesConfig_dword_5510C4 = 0;
    pJSAction = jonesConfig_aJonesCapControlActionNames;

    // Change to for loop
    for ( int i = 0; i < JONES_CONTROL_ACTION_COUNT; i++ )
    {
        pActionName = jonesString_GetString(*pJSAction);
        if ( !pActionName )
        {
            return 0;
        }

        strcpy(aActionName, pActionName);

        v2 = aActionName;
        v3 = 0;
        if ( &v11 != (int*)0xFFFFFEF4 )
        {
            do
            {
                v2 = strchr(v2, ' ');
                if ( v2 )
                {
                    ++v2;
                }

                ++v3;
            } while ( v2 );
        }

        if ( v3 > jonesConfig_dword_5510E0 )
        {
            jonesConfig_dword_5510E0 = v3;
        }

        v4 = strlen(aActionName) + 1;
        if ( (int)(v4 - 1) > jonesConfig_dword_5510C4 )
        {
            jonesConfig_dword_5510C4 = v4 - 1;
        }

        ++pJSAction;
    }

    for ( controlId = 0; controlId < 656; ++controlId )
    {
        memset(aControlStr, 0, sizeof(aControlStr));
        switch ( controlId )
        {
            case 644:
                jonesConfig_ControlToString(0x8000u, aControlStr);
                break;

            case 645:
                jonesConfig_ControlToString(0x8002u, aControlStr);
                break;

            case 646:
                jonesConfig_ControlToString(0x8003u, aControlStr);
                break;

            case 647:
                jonesConfig_ControlToString(0x8001u, aControlStr);
                break;

            case 648:
                jonesConfig_ControlToString(0x8006u, aControlStr);
                break;

            case 649:
                jonesConfig_ControlToString(0x8007u, aControlStr);
                break;

            case 650:
                jonesConfig_ControlToString(0x8004u, aControlStr);
                break;

            case 651:
                jonesConfig_ControlToString(0x8005u, aControlStr);
                break;

            default:
                jonesConfig_ControlToString(controlId, aControlStr);
                break;
        }

        v6 = 0;
        for ( i = aControlStr; i; ++v6 )
        {
            i = strchr(i, ' ');
            if ( i )
            {
                ++i;
            }
        }


        if ( v6 > jonesConfig_dword_5510BC )
        {
            jonesConfig_dword_5510BC = v6;
        }

        v8 = jonesConfig_dword_5510B8;
        v9 = strlen(aControlStr) + 1;
        if ( (int)(v9 - 1) > jonesConfig_dword_5510B8 )
        {
            v8 = v9 - 1;
            jonesConfig_dword_5510B8 = v9 - 1;
        }
    }

    jonesConfig_dword_551D20 = jonesConfig_dword_5510C4 - jonesConfig_dword_5510C4 % 5 + 5;
    result = 1;
    jonesConfig_dword_5510C0 = v8 - v8 % 5 + 5;
    return result;
}

void jonesConfig_Shutdown(void)
{
    HBITMAP* hdi; // esi

    jonesConfig_FreeControlConfigEntry(&jonesConfig_curControlConfig);
    hdi = jonesConfig_apDialogIcons;
    do
    {
        DeleteObject(*hdi);
        *hdi++ = 0;
    } while ( (int)hdi < (int)&jonesConfig_apDialogIcons[2] );// TODO: Fix range loop to not compare against the address

    if ( jonesConfig_pKeySetsDirPath )
    {
        memset(jonesConfig_pKeySetsDirPath, 0, sizeof(jonesConfig_pKeySetsDirPath));
    }
}

void J3DAPI jonesConfig_ControlToString(unsigned int controlId, char* pDest)
{
    const char* pJonesString; // edx
    const char* pControlStr; // edi

    pJonesString = 0;
    if ( !pDest )
    {
        return;
    }

    memset(pDest, 0, 256u);

    if ( controlId <= 0x8000 )
    {
        if ( controlId == 0x8000 )
        {
            pJonesString = "JONES_STR_JOYUP";
        }
        else
        {
            switch ( controlId )
            {
                case 1u:
                    pJonesString = "JONES_STR_ESCAPE";
                    break;

                case 2u:
                    *(WORD*)pDest = *(WORD*)"1";
                    break;

                case 3u:
                    *(WORD*)pDest = *(WORD*)"2";
                    break;

                case 4u:
                    *(WORD*)pDest = *(WORD*)"3";
                    break;

                case 5u:
                    *(WORD*)pDest = *(WORD*)"4";
                    break;

                case 6u:
                    *(WORD*)pDest = *(WORD*)"5";
                    break;

                case 7u:
                    *(WORD*)pDest = *(WORD*)"6";
                    break;

                case 8u:
                    *(WORD*)pDest = *(WORD*)"7";
                    break;

                case 9u:
                    *(WORD*)pDest = *(WORD*)"8";
                    break;

                case 10u:
                    *(WORD*)pDest = *(WORD*)"9";
                    break;

                case 11u:
                    *(WORD*)pDest = *(WORD*)"0";
                    break;

                case 12u:
                    pJonesString = "JONES_STR_MINUS";
                    break;

                case 13u:
                    pJonesString = "JONES_STR_EQUAL";
                    break;

                case 14u:
                    pJonesString = "JONES_STR_BACK";
                    break;

                case 15u:
                    pJonesString = "JONES_STR_TAB";
                    break;

                case 16u:
                    *(WORD*)pDest = *(WORD*)"Q";
                    break;

                case 17u:
                    *(WORD*)pDest = *(WORD*)"W";
                    break;

                case 18u:
                    *(WORD*)pDest = *(WORD*)"E";
                    break;

                case 19u:
                    *(WORD*)pDest = *(WORD*)"R";
                    break;

                case 20u:
                    *(WORD*)pDest = *(WORD*)"T";
                    break;

                case 21u:
                    *(WORD*)pDest = *(WORD*)"Y";
                    break;

                case 22u:
                    *(WORD*)pDest = *(WORD*)"U";
                    break;

                case 23u:
                    *(WORD*)pDest = *(WORD*)"I";
                    break;

                case 24u:
                    *(WORD*)pDest = *(WORD*)"O";
                    break;

                case 25u:
                    *(WORD*)pDest = *(WORD*)"P";
                    break;

                case 26u:
                    pJonesString = "JONES_STR_LEFT_BRCKT";
                    break;

                case 27u:
                    pJonesString = "JONES_STR_RIGHT_BRCKT";
                    break;

                case 28u:
                    pJonesString = "JONES_STR_ENTER";
                    break;

                case 29u:
                    pJonesString = "JONES_STR_LEFT_CTRL";
                    break;

                case 30u:
                    *(WORD*)pDest = *(WORD*)"A";
                    break;

                case 31u:
                    *(WORD*)pDest = *(WORD*)"S";
                    break;

                case 32u:
                    *(WORD*)pDest = *(WORD*)"D";
                    break;

                case 33u:
                    *(WORD*)pDest = *(WORD*)"F";
                    break;

                case 34u:
                    *(WORD*)pDest = *(WORD*)"G";
                    break;

                case 35u:
                    *(WORD*)pDest = *(WORD*)"H";
                    break;

                case 36u:
                    *(WORD*)pDest = *(WORD*)"J";
                    break;

                case 37u:
                    *(WORD*)pDest = *(WORD*)"K";
                    break;

                case 38u:
                    *(WORD*)pDest = *(WORD*)"L";
                    break;

                case 39u:
                    *(WORD*)pDest = *(WORD*)";";
                    break;

                case 40u:
                    *(WORD*)pDest = *(WORD*)"'";
                    break;

                case 41u:
                    *(WORD*)pDest = *(WORD*)"`";
                    break;

                case 42u:
                    pJonesString = "JONES_STR_LEFT_SHIFT";
                    break;

                case 43u:
                    *(WORD*)pDest = *(WORD*)"\\";
                    break;

                case 44u:
                    *(WORD*)pDest = *(WORD*)"Z";
                    break;

                case 45u:
                    *(WORD*)pDest = *(WORD*)"X";
                    break;

                case 46u:
                    *(WORD*)pDest = *(WORD*)"C";
                    break;

                case 47u:
                    *(WORD*)pDest = *(WORD*)"V";
                    break;

                case 48u:
                    *(WORD*)pDest = *(WORD*)"B";
                    break;

                case 49u:
                    *(WORD*)pDest = *(WORD*)"N";
                    break;

                case 50u:
                    *(WORD*)pDest = *(WORD*)"M";
                    break;

                case 51u:
                    pJonesString = "JONES_STR_COMMA";
                    break;

                case 52u:
                    *(WORD*)pDest = *(WORD*)".";
                    break;

                case 53u:
                    *(WORD*)pDest = *(WORD*)"/";
                    break;

                case 54u:
                    pJonesString = "JONES_STR_RIGHT_SHIFT";
                    break;

                case 55u:
                    pJonesString = "JONES_STR_NUMPAD_MULT";
                    break;

                case 56u:
                    pJonesString = "JONES_STR_LEFT_ALT";
                    break;

                case 57u:
                    pJonesString = "JONES_STR_SPACE";
                    break;

                case 58u:
                    pJonesString = "JONES_STR_CAPS";
                    break;

                case 59u:
                    pJonesString = "JONES_STR_F1";
                    break;

                case 60u:
                    pJonesString = "JONES_STR_F2";
                    break;

                case 61u:
                    pJonesString = "JONES_STR_F3";
                    break;

                case 62u:
                    pJonesString = "JONES_STR_F4";
                    break;

                case 63u:
                    pJonesString = "JONES_STR_F5";
                    break;

                case 64u:
                    pJonesString = "JONES_STR_F6";
                    break;

                case 65u:
                    pJonesString = "JONES_STR_F7";
                    break;

                case 66u:
                    pJonesString = "JONES_STR_F8";
                    break;

                case 67u:
                    pJonesString = "JONES_STR_F9";
                    break;

                case 68u:
                    pJonesString = "JONES_STR_F10";
                    break;

                case 69u:
                    pJonesString = "JONES_STR_NUMLOCK";
                    break;

                case 71u:
                    pJonesString = "JONES_STR_NUMPAD_7";
                    break;

                case 72u:
                    pJonesString = "JONES_STR_NUMPAD_8";
                    break;

                case 73u:
                    pJonesString = "JONES_STR_NUMPAD_9";
                    break;

                case 74u:
                    pJonesString = "JONES_STR_NUMPAD_MINUS";
                    break;

                case 75u:
                    pJonesString = "JONES_STR_NUMPAD_4";
                    break;

                case 76u:
                    pJonesString = "JONES_STR_NUMPAD_5";
                    break;

                case 77u:
                    pJonesString = "JONES_STR_NUMPAD_6";
                    break;

                case 78u:
                    pJonesString = "JONES_STR_NUMPAD_PLUS";
                    break;

                case 79u:
                    pJonesString = "JONES_STR_NUMPAD_1";
                    break;

                case 80u:
                    pJonesString = "JONES_STR_NUMPAD_2";
                    break;

                case 81u:
                    pJonesString = "JONES_STR_NUMPAD_3";
                    break;

                case 82u:
                    pJonesString = "JONES_STR_NUMPAD_0";
                    break;

                case 83u:
                    pJonesString = "JONES_STR_NUMPAD_DOT";
                    break;

                case 87u:
                    pJonesString = "JONES_STR_F11";
                    break;

                case 88u:
                    pJonesString = "JONES_STR_F12";
                    break;

                case 100u:
                    pJonesString = "JONES_STR_F13";
                    break;

                case 101u:
                    pJonesString = "JONES_STR_F14";
                    break;

                case 102u:
                    pJonesString = "JONES_STR_F15";
                    break;

                case 141u:
                    pJonesString = "JONES_STR_NUMPAD_EQL";
                    break;

                case 156u:
                    pJonesString = "JONES_STR_NUMPAD_ENTER";
                    break;

                case 157u:
                    pJonesString = "JONES_STR_RIGHT_CTRL";
                    break;

                case 179u:
                    pJonesString = "JONES_STR_NUMPAD_COMMA";
                    break;

                case 181u:
                    pJonesString = "JONES_STR_NUMPAD_DIV";
                    break;

                case 184u:
                    pJonesString = "JONES_STR_RIGHT_ALT";
                    break;

                case 199u:
                    pJonesString = "JONES_STR_HOME";
                    break;

                case 200u:
                    pJonesString = "JONES_STR_UPARRW";
                    break;

                case 201u:
                    pJonesString = "JONES_STR_PAGEUP";
                    break;

                case 203u:
                    pJonesString = "JONES_STR_LEFTARRW";
                    break;

                case 205u:
                    pJonesString = "JONES_STR_RGHTARRW";
                    break;

                case 207u:
                    pJonesString = "JONES_STR_END";
                    break;

                case 208u:
                    pJonesString = "JONES_STR_DNARRW";
                    break;

                case 209u:
                    pJonesString = "JONES_STR_PGDN";
                    break;

                case 210u:
                    pJonesString = "JONES_STR_INSERT";
                    break;

                case 211u:
                    pJonesString = "JONES_STR_DELETE";
                    break;

                case 219u:
                    pJonesString = "JONES_STR_LEFT_WND";
                    break;

                case 220u:
                    pJonesString = "JONES_STR_RIGHT_WND";
                    break;

                default:
                    goto LABEL_117;
            }
        }

        goto LABEL_133;
    }

    switch ( controlId )
    {
        case 0x8001u:
            pJonesString = "JONES_STR_JOYRIGHT";
            goto LABEL_133;

        case 0x8002u:
            pJonesString = "JONES_STR_JOYDOWN";
            goto LABEL_133;

        case 0x8003u:
            pJonesString = "JONES_STR_JOYLEFT";
            goto LABEL_133;

        case 0x8004u:
            pJonesString = "JONES_STR_JOYTWISTL";
            goto LABEL_133;

        case 0x8005u:
            pJonesString = "JONES_STR_JOYTWISTR";
            goto LABEL_133;

        default:
        LABEL_117:
            if ( controlId < 288 )
            {
                goto LABEL_130;
            }

            if ( controlId > 639 || (controlId & 3) != 0 )
            {
                if ( controlId <= 639 && (controlId & 3) == 2 )
                {
                    pJonesString = "JONES_STR_HATRIGHT";
                }

                else if ( controlId <= 639 && (controlId & 3) == 3 )
                {
                    pJonesString = "JONES_STR_HATDOWN";
                }
                else
                {
                    if ( controlId > 639 || (controlId & 3) != 1 )
                    {
                    LABEL_130:
                        if ( controlId >= 256 && controlId <= 639 )
                        {
                            pJonesString = "JONES_STR_JOYSTICK";
                        }

                        goto LABEL_133;
                    }

                    pJonesString = "JONES_STR_HATUP";
                }
            }
            else
            {
                pJonesString = "JONES_STR_HATLEFT";
            }

        LABEL_133:
            if ( !pJonesString )
            {
                return;
            }

            pControlStr = jonesString_GetString(pJonesString);
            if ( !pControlStr )
            {
                return;
            }

            if ( controlId < 256 || controlId > 287 )
            {
                if ( controlId >= 288
                    && (controlId <= 639 && (controlId & 3) == 0
                        || controlId <= 639 && (controlId & 3) == 1
                        || controlId <= 639 && (controlId & 3) == 2
                        || controlId <= 639 && (controlId & 3) == 3) )
                {
                    sprintf(pDest, pControlStr, ((((controlId - 256) % 48) >> 2) & 7) + 1);
                }
                else
                {
                    strcpy(pDest, pControlStr);
                }
            }
            else
            {
                sprintf(pDest, pControlStr, (controlId - 256) % 48 + 1);
            }

            return;
    }
}

int J3DAPI jonesConfig_ShowMessageDialog(HWND hWnd, const char* pTitle, const char* pText, int iconID)
{
    char dwInitParam[520]; // [esp+Ch] [ebp-208h] BYREF

    GetWindowLongA(hWnd, GWL_HINSTANCE);
    memset(dwInitParam, 0, sizeof(dwInitParam));
    *(DWORD*)dwInitParam = iconID;
    strcpy(&dwInitParam[260], pText);
    strcpy(&dwInitParam[4], pTitle);
    return JonesDialog_ShowDialog((LPCSTR)121, hWnd, jonesConfig_MessageDialogProc, (LPARAM)dwInitParam);
}

BOOL CALLBACK jonesConfig_MessageDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM a4)
{
    LONG WindowLongA; // ebx
    HWND hDlgItem; // esi
    void* v7; // ebp
    int v8; // [esp+10h] [ebp-4h]

    if ( uMsg == WM_DESTROY )
    {
        WindowLongA = GetWindowLongA(hwnd, 8);
        hDlgItem = GetDlgItem(hwnd, 1201);
        jonesConfig_ResetDialogFont(hwnd, (HFONT)jonesConfig_hdo_551DD0);
        if ( !WindowLongA || !hDlgItem )
        {
            return 1;
        }

        v7 = (void*)SendMessageA(hDlgItem, STM_GETICON, 0, 0);
        SendMessageA(hDlgItem, STM_SETICON, *(DWORD*)(WindowLongA + 516), 0);
        DeleteObject(v7);
        return 1;
    }

    else if ( uMsg == WM_INITDIALOG )
    {
        SetWindowTextA(hwnd, (LPCSTR)(a4 + 4));
        jonesConfig_sub_4025F0(hwnd, (unsigned __int16*)a4);
        jonesConfig_hdo_551DD0 = jonesConfig_InitDialog(hwnd, 0, 121);
        v8 = jonesConfig_sub_402670(hwnd, wParam, (unsigned __int16*)a4);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return v8;
    }
    else
    {
        if ( uMsg == WM_COMMAND )
        {
            jonesConfig_sub_402A90(hwnd, (unsigned __int16)wParam);
        }

        return 0;
    }
}

void J3DAPI jonesConfig_sub_4025F0(HWND hWnd, uint16_t* a2)
{
    HINSTANCE hInstance; // eax
    HANDLE hImage; // ebx
    HWND DlgItem; // eax
    HWND v5; // esi
    HWND hWnda; // [esp+10h] [ebp+4h]

    hInstance = (HINSTANCE)GetWindowLongA(hWnd, GWL_HINSTANCE);
    if ( a2 )
    {
        hImage = LoadImageA(hInstance, (LPCSTR)*a2, IMAGE_ICON, 64, 64, 0);
        DlgItem = GetDlgItem(hWnd, 1201);
        v5 = DlgItem;
        if ( DlgItem )
        {
            if ( hImage )
            {
                hWnda = (HWND)SendMessageA(DlgItem, STM_GETICON, 0, 0);
                SendMessageA(v5, STM_SETICON, (WPARAM)hImage, 0);
                *((DWORD*)a2 + 129) = hWnda;
            }
        }
    }
}

int J3DAPI jonesConfig_sub_402670(HWND hDlg, int a2, uint16_t* dwNewLong)
{
    HWND DlgItem; // ebx

    DlgItem = GetDlgItem(hDlg, 1075);
    GetDC(DlgItem);
    if ( !dwNewLong )
    {
        return 0;
    }

    jonesConfig_sub_4025F0(hDlg, dwNewLong);
    jonesConfig_SetTextControl(hDlg, DlgItem, (const char*)dwNewLong + 260);
    SetWindowLongA(hDlg, DWL_USER, (LONG)dwNewLong);
    return 1;
}

int J3DAPI jonesConfig_SetTextControl(HWND hDlg, HWND hWnd, const char* aText)
{
    HDC hdc; // esi
    HFONT hFont; // eax
    const char* v5; // ebx
    const char* v6; // esi
    char* v7; // ebx
    int v8; // ebp
    unsigned int v9; // kr0C_4
    signed int v10; // edi
    bool v11; // zf
    int i; // edx
    int v13; // edx
    int v14; // esi
    int v15; // ebp
    int v16; // edi
    int v17; // ebx
    HWND v18; // ebx
    int v20; // [esp+0h] [ebp-174h]
    int v21; // [esp+18h] [ebp-15Ch]
    int SystemMetrics; // [esp+18h] [ebp-15Ch]
    int v23; // [esp+1Ch] [ebp-158h]
    int v24; // [esp+1Ch] [ebp-158h]
    int v25; // [esp+20h] [ebp-154h]
    int v26; // [esp+20h] [ebp-154h]
    HWND DlgItem; // [esp+24h] [ebp-150h]
    struct tagRECT Rect; // [esp+28h] [ebp-14Ch] BYREF
    struct tagRECT v29; // [esp+38h] [ebp-13Ch] BYREF
    struct tagRECT v30; // [esp+48h] [ebp-12Ch] BYREF
    int X; // [esp+58h] [ebp-11Ch]
    int Y; // [esp+5Ch] [ebp-118h]
    HWND v33; // [esp+60h] [ebp-114h]
    struct tagRECT v34; // [esp+64h] [ebp-110h] BYREF
    char v35[256]; // [esp+74h] [ebp-100h] BYREF

    hdc = GetDC(hWnd);
    hFont = (HFONT)SendMessageA(hWnd, WM_GETFONT, 0, 0);
    SelectObject(hdc, hFont);

    if ( !jonesConfig_dword_551DCC )
    {
        memset(jonesConfig_aGlyphMetrics, 0, sizeof(jonesConfig_aGlyphMetrics));
        memset(&jonesConfig_textMetric, 0, sizeof(jonesConfig_textMetric));
        GetTextMetricsA(hdc, &jonesConfig_textMetric);
        GetCharABCWidthsA(
            hdc,
            jonesConfig_textMetric.tmFirstChar,
            jonesConfig_textMetric.tmLastChar,
            jonesConfig_aGlyphMetrics);
        jonesConfig_dword_551DCC = 1;
    }

    v21 = 0;
    GetWindowRect(hDlg, &Rect);

    X = Rect.left;
    Y = Rect.top;
    GetWindowRect(hWnd, &Rect);
    v5 = aText;
    v25 = Rect.right - Rect.left;
    do
    {
        v6 = v5;
        v7 = strchr(v5, '\n');
        memset(v35, 0, sizeof(v35));
        if ( v7 )
        {
            strncpy(v35, v6, v7 - v6);
        }
        else
        {
            strcpy(v35, v6);
        }

        v8 = 0;
        v9 = strlen(v35) + 1;
        v10 = 0;
        v11 = v9 == 1;
        v23 = 0;
        if ( (int)(v9 - 1) > 0 )
        {
            for ( i = jonesConfig_textMetric.tmFirstChar; ; i = jonesConfig_textMetric.tmFirstChar )
            {
                v13 = (unsigned __int8)v35[v10++] - i;
                v8 += abs(jonesConfig_aGlyphMetrics[v13].abcA)
                    + abs(jonesConfig_aGlyphMetrics[v13].abcB)
                    + abs(jonesConfig_aGlyphMetrics[v13].abcC);
                if ( v10 >= (int)(v9 - 1) )
                {
                    break;
                }
            }

            v23 = v8;
            v11 = v9 == 1;
        }

        if ( v11 && v7 )
        {
            ++v21;
        }
        else
        {
            v21 += (__int64)ceil((double)v23 / (double)v25);
        }

        if ( !v7 )
        {
            break;
        }

        v5 = v7 + 1;
        if ( !strlen(v5) )
        {
            v5 = 0;
        }
    } while ( v5 );

    v14 = Rect.top + v21 * (jonesConfig_textMetric.tmHeight + jonesConfig_textMetric.tmExternalLeading) - Rect.bottom;
    if ( v14 > 0 )
    {
        DlgItem = GetDlgItem(hDlg, 1);
        v33 = GetDlgItem(hDlg, 2);

        SystemMetrics = GetSystemMetrics(4);
        v15 = 2 * GetSystemMetrics(8);

        GetWindowRect(DlgItem, &v29);
        v29.top += v14;

        GetWindowRect(hDlg, &v30);

        v26 = v29.left - v30.left;
        v29.bottom += v14;
        v24 = Rect.left - v30.left;
        Rect.bottom += v14;
        v30.bottom += v14;
        v16 = v29.top - v30.top - SystemMetrics - v15;
        v17 = Rect.top - v30.top - SystemMetrics - v15;

        MoveWindow(hDlg, X, Y, v30.right - v30.left, v30.bottom - v30.top, 1);
        MoveWindow(DlgItem, v26, v16, v29.right - v29.left, v29.bottom - v29.top, 1);
        MoveWindow(hWnd, v24, v17, Rect.right - Rect.left, Rect.bottom - Rect.top, 1);

        v18 = v33;
        if ( v33 )
        {
            GetWindowRect(v33, &v34);
            v34.bottom += v14;
            v20 = v34.bottom - (v14 + v34.top);
            v34.top += v14;
            MoveWindow(v18, v34.left - v30.left, v34.top - v30.top - SystemMetrics - v15, v34.right - v34.left, v20, 1);
        }
    }

    SetWindowTextA(hWnd, aText);
    return ShowWindow(hDlg, 1);
}

BOOL J3DAPI jonesConfig_sub_402A90(HWND hDlg, int nResult)
{
    BOOL result; // eax

    result = nResult;
    if ( nResult > 0 && nResult <= 2 )
    {
        return EndDialog(hDlg, nResult);
    }

    return result;
}

JonesControlsScheme* J3DAPI jonesConfig_NewControlScheme()
{
    JonesControlsScheme* pConfig; // esi
    int keysetNum; // ebx
    const char** pKeySetJS; // ebp
    const char* pName; // eax
    int MaxJoystickButtons; // eax
    int v6; // eax
    int v7; // ebp
    const char* String; // eax
    const char* v9; // ebx
    JonesControlsScheme* pConfig_1; // [esp+10h] [ebp-18Ch]
    LPSTR pFilePart; // [esp+18h] [ebp-184h] BYREF
    CHAR aConfigFilename[128]; // [esp+1Ch] [ebp-180h] BYREF
    CHAR aBuffer[128]; // [esp+9Ch] [ebp-100h] BYREF
    char aKFGPath[128]; // [esp+11Ch] [ebp-80h] BYREF

    memset(aConfigFilename, 0, sizeof(aConfigFilename));
    pConfig = (JonesControlsScheme*)STDMALLOC(sizeof(JonesControlsScheme));
    pConfig_1 = pConfig;
    if ( !pConfig )
    {
        return 0;
    }

    memset(aBuffer, 0, sizeof(aBuffer));
    memset(pConfig, 0, sizeof(JonesControlsScheme));

    wuRegistry_GetStr("Configuration", aConfigFilename, 128u, std_g_aEmptyString);
    if ( strlen(aConfigFilename) )
    {
        memset(aKFGPath, 0, sizeof(aKFGPath));
        sprintf(aKFGPath, "%s\\%s%s", jonesConfig_pKeySetsDirPath, aConfigFilename, ".kfg");

        memset(aBuffer, 0, sizeof(aBuffer));
        SearchPathA(jonesConfig_pKeySetsDirPath, aConfigFilename, ".kfg", 128u, aBuffer, &pFilePart);

        if ( strlen(aBuffer) && jonesConfig_LoadConstrolsScheme(aKFGPath, pConfig) )
        {
            return pConfig;
        }

        keysetNum = 0;
        while ( keysetNum < 3 )  // Replace pointer comparison with simple counter check
        {
            pName = jonesString_GetString(jonesConfig_aDfltKeySetNames[keysetNum]);
            if ( !pName )
            {
                goto LABEL_17;
            }
            strcpy(pConfig->aName, pName);
            if ( !strcmp(aConfigFilename, pName) )
            {
                if ( !strlen(aBuffer) )
                {
                    pConfig = pConfig_1;
                    if ( jonesConfig_SetDefaultControlScheme(pConfig_1, keysetNum) )
                    {
                        return pConfig;
                    }
                }
            }
            else
            {
                ++keysetNum;
            }
        }
        wuRegistry_SaveStr("Configuration", std_g_aEmptyString);
        goto LABEL_16;
    }

    if ( strlen(aConfigFilename) && strlen(aBuffer) )
    {
        return pConfig;
    }

    MaxJoystickButtons = stdControl_GetMaxJoystickButtons();
    if ( MaxJoystickButtons == 4 )
    {
        v7 = 1;
    }
    else
    {
        v6 = -(MaxJoystickButtons != 8);
        v6 &= ~1;
        v7 = v6 + 2;
    }

    String = jonesString_GetString(jonesConfig_aDfltKeySetNames[v7]);
    v9 = String;
    if ( String )
    {
        strcpy(pConfig->aName, String);
        if ( jonesConfig_SetDefaultControlScheme(pConfig, v7) )
        {
            wuRegistry_SaveStr("Configuration", v9);
            return pConfig;
        }

    LABEL_16:
        pConfig = pConfig_1;
    }

LABEL_17:
    jonesConfig_FreeControlScheme(pConfig);
    return 0;
}

int J3DAPI jonesConfig_LoadConstrolsScheme(const char* pFilePath, JonesControlsScheme* pConfig)
{
    JonesControlsScheme* pConfig_1; // ebp
    int v3; // ebx
    int actionIdx; // eax
    int v5; // eax
    int* pKeyAction; // esi
    int bController; // edi
    int bKeyboard; // ebp
    int keyIdx; // eax
    int controllerKey; // eax
    int v11; // ecx
    int v12; // edx
    const char* pFaultyActionName; // eax
    const char* String; // eax
    HWND Window; // eax
    int (*pAction)[9]; // eax
    int argNum; // [esp+10h] [ebp-510h] BYREF
    int v19; // [esp+14h] [ebp-50Ch]
    int actionCount; // [esp+18h] [ebp-508h]
    int actionIdx_1; // [esp+1Ch] [ebp-504h]
    char aErrorStr[256]; // [esp+20h] [ebp-500h] BYREF
    char aErrorActionName[512]; // [esp+120h] [ebp-400h] BYREF
    char aErrorFormat[512]; // [esp+320h] [ebp-200h] BYREF


    // Function loads kfg file to pConfig

    if ( !stdConffile_Open(pFilePath) )
    {
        return 0;
    }

    pConfig_1 = pConfig;
    if ( !pConfig )
    {
        return 0;
    }

    if ( !pFilePath )
    {
        return 0;
    }

    memset(pConfig->aName, 0, sizeof(pConfig->aName));
    strncpy(pConfig->aName, pFilePath, strlen(pFilePath) - 4);// -4 removes .kfg extension
    v3 = 0;

    stdConffile_ReadArgs();                     // skip first comment line
    stdConffile_ReadArgs();

    if ( stdConffile_g_entry.numArgs && !_strnicmp(stdConffile_g_entry.aArgs[0].argName, "1", 128u) )// 1 mark shceme is enabled
    {
        stdConffile_ReadArgs();                 // Skip header line

        actionCount = 0;
        while ( 1 )
        {
            argNum = 0;
            if ( !stdConffile_ReadArgs() )
            {
                break;
            }

            actionIdx = jonesConfig_GetEntryIndex(
                &argNum,
                &stdConffile_g_entry,
                jonesConfig_dword_5510E0,
                jonesConfig_aJonesControlActionNames,
                37);
            actionIdx_1 = actionIdx;
            if ( actionIdx == -1 )
            {
                break;
            }

            // TODO: Fix offsets
            v5 = 9 * actionIdx;                 // 9 is size of JonesControlSchemeEntry in ints
            v3 = 1;
            pKeyAction = pConfig_1->aActions[v5 / 9u];// TODO: maybe pKeyAction is a struct like JonesControlSchemeAction
            *pKeyAction = 0;
            if ( (JonesControlsScheme*)((char*)pConfig_1 + 4 * v5) != (JonesControlsScheme*)-4 )// TODO: Fix this if statement to if( pEntry != 0
            {
                while ( 1 )
                {
                    if ( argNum >= stdConffile_g_entry.numArgs )
                    {
                        pConfig_1 = pConfig;
                        goto LABEL_18;
                    }

                    bController = 0;
                    bKeyboard = 0;
                    v19 = argNum;
                    keyIdx = jonesConfig_GetEntryIndex(
                        &argNum,
                        &stdConffile_g_entry,
                        jonesConfig_dword_5510BC,
                        jonesConfig_aControlKeyStrings,
                        223);

                    pKeyAction[v3] = keyIdx;

                    if ( keyIdx != -1 )
                    {
                        bKeyboard = 1;          // eventually flag 0x100
                    }
                    else
                    {
                        // We couldn't find control key num, try searching by control mouse button num, gamepad & joystick button num
                        argNum = v19;
                        controllerKey = jonesConfig_GetControllerKeySchemeIndex(&argNum, &stdConffile_g_entry);
                        pKeyAction[v3] = controllerKey;
                        if ( controllerKey == -1 )
                        {
                            goto LABEL_30;
                        }

                        bController = 1;        // eventually flag 0x10000
                        ++argNum;
                    }

                    v11 = *pKeyAction;
                    v12 = *pKeyAction & 0xFF0000;
                    v19 = v3 + 1;
                    *pKeyAction = (bController + bKeyboard + (unsigned __int8)v11) | ((bKeyboard << 8) + (v11 & 0xFF00)) | (v12 + (bController << 16));
                    if ( (unsigned __int8)((bController + bKeyboard + v11) | v12) > 8u )
                    {
                        break;
                    }

                    v3 = v19;
                }


                // We've exceeded the number of key mappings
                pFaultyActionName = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[actionIdx_1]);
                if ( pFaultyActionName )
                {
                    strcpy(aErrorActionName, pFaultyActionName);
                }
                else
                {
                    memset(aErrorActionName, 0, sizeof(aErrorActionName));
                }

                String = jonesString_GetString("JONES_STR_EXCEED");
                if ( String )
                {
                    strcpy(aErrorFormat, String);
                }
                else
                {
                    memset(aErrorFormat, 0, sizeof(aErrorFormat));
                }

                memset(aErrorStr, 0, sizeof(aErrorStr));
                if ( aErrorFormat[0] && aErrorActionName[0] )
                {
                    sprintf(aErrorStr, aErrorFormat, aErrorActionName);
                    Window = stdWin95_GetWindow();
                    jonesConfig_ShowMessageDialog(Window, "JONES_STR_CTRL_OPTS", aErrorStr, 145);
                }

                v3 = v19;
                break;
            }

        LABEL_18:
            if ( ++actionCount >= 37 )          // max 37, TODO: make sizeof(JonesConfig.aEntries) / sizeof(JonesConfig.aEntries[0]), or make a macro
            {
                stdConffile_Close();
                return 1;
            }
        }
    }

LABEL_30:
    memset(pConfig->aName, 0, sizeof(pConfig->aName));
    if ( v3 > 0 )
    {
        pAction = pConfig->aActions;
        do
        {
            if ( pAction )
            {
                (*pAction)[0] = 0;
                (*pAction)[1] = 0;
                (*pAction)[2] &= 0xFF00;
            }

            ++pAction;
            --v3;
        } while ( v3 );
    }

    stdConffile_Close();
    return 0;
}

int J3DAPI jonesConfig_GetEntryIndex(int* argNum, StdConffileEntry* pEntry, int a3, const char** apStringList, int size)
{
    int result; // eax
    char aValue[256]; // [esp+4h] [ebp-100h] BYREF

    strncpy(aValue, pEntry->aArgs[*argNum].argName, 256u);
    result = jonesConfig_GetValueIndex(aValue, apStringList, size);
    ++*argNum;
    return result;
}

int J3DAPI jonesConfig_GetValueIndex(char* pValue, const char** apStringList, int size)
{
    char* pVal; // ebp
    const char* pStr; // eax
    const char* pStr_1; // esi
    int entryNum; // [esp+10h] [ebp-4h]

    entryNum = 0;
    if ( size == 223 )                          // if the list is list of keys, TODO: kill this nonsense and make case insensitive comparison
    {
        pVal = strupr(pValue);
    }
    else
    {
        pVal = pValue;
    }

    if ( size > 0 )
    {
        while ( 1 )
        {
            if ( *apStringList )
            {
                pStr = jonesString_GetString(*apStringList);
                pStr_1 = pStr;
                if ( pStr )
                {
                    if ( !_strnicmp(pVal, pStr, strlen(pStr)) && strlen(pStr_1) == strlen(pVal) )
                    {
                        return entryNum;
                    }
                }

                else if ( !_strnicmp(pVal, *apStringList, strlen(pVal)) && strlen(pVal) == strlen(*apStringList) )
                {
                    return entryNum;
                }
            }

            ++apStringList;
            if ( ++entryNum >= size )
            {
                return -1;
            }
        }
    }

    return -1;
}

int J3DAPI jonesConfig_GetControllerKeySchemeIndex(int* pArgNum, StdConffileEntry* pEntry)
{

    const char* pStrButton; // eax
    int* argNum; // ebx
    char* pBtnNumStr; // eax
    StdConffileArg* v5; // edx
    signed int v6; // ebx
    char* v7; // eax
    const char* String; // eax
    const char* v9; // eax
    const char* v10; // eax
    const char* v11; // eax
    int v12; // eax
    const char* v13; // eax
    const char* v14; // eax
    const char* v15; // eax
    const char* v16; // eax
    const char* v17; // eax
    const char* v18; // eax
    int result; // eax
    int ctrlBtnNum; // [esp+10h] [ebp-D04h]
    char v21[256]; // [esp+14h] [ebp-D00h] BYREF
    char Dest[512]; // [esp+114h] [ebp-C00h] BYREF
    char v23[512]; // [esp+314h] [ebp-A00h] BYREF
    char v24[512]; // [esp+514h] [ebp-800h] BYREF
    char v25[512]; // [esp+714h] [ebp-600h] BYREF
    char v26[512]; // [esp+914h] [ebp-400h] BYREF
    char v27[512]; // [esp+B14h] [ebp-200h] BYREF

    // First check if key name is 'BUTTON x' where x is it's number. and set the button number
    ctrlBtnNum = -1;
    pStrButton = jonesString_GetString("JONES_STR_CAPS_BUTTON");
    if ( pStrButton )
    {
        argNum = pArgNum;
        if ( !_strnicmp(pEntry->aArgs[*pArgNum].argName, pStrButton, strlen(pStrButton)) )
        {
            pBtnNumStr = strpbrk(pEntry->aArgs[*pArgNum].argName, "0123456789");
            if ( pBtnNumStr )
            {
                ctrlBtnNum = atoi(pBtnNumStr) + 255;
            }
        }
    }
    else
    {
        argNum = pArgNum;
    }

    if ( ctrlBtnNum == -1 )
    {
        memset(Dest, 0, 0x100u);
        memset(v21, 0, sizeof(v21));
        v5 = &pEntry->aArgs[*argNum];
        strcpy(v21, v5->argName);
        v6 = strcspn(v5->argName, "0123456789");
        v21[v6] = 0;
        if ( v6 > 0 )
        {
            v6 = atoi(&pEntry->aArgs[*pArgNum].argName[v6]) - 1;
        }

        v7 = strchr(pEntry->aArgs[*pArgNum].argName, ' ');
        if ( v7 )
        {
            sprintf(Dest, "%s%%i %s", v21, v7 + 1);
        }

        String = jonesString_GetString("JONES_STR_HATUP");
        if ( String )
        {
            strcpy(v23, String);
        }
        else
        {
            memset(v23, 0, sizeof(v23));
        }

        v9 = jonesString_GetString("JONES_STR_HATDOWN");
        if ( v9 )
        {
            strcpy(v26, v9);
        }
        else
        {
            memset(v26, 0, sizeof(v26));
        }

        v10 = jonesString_GetString("JONES_STR_HATLEFT");
        if ( v10 )
        {
            strcpy(v24, v10);
        }
        else
        {
            memset(v24, 0, sizeof(v24));
        }

        v11 = jonesString_GetString("JONES_STR_HATRIGHT");
        if ( v11 )
        {
            strcpy(v25, v11);
        }
        else
        {
            memset(v25, 0, sizeof(v25));
        }

        if ( !v23[0] || !v26[0] || !v24[0] || !v25[0] || !strlen(Dest) )
        {
            goto LABEL_37;
        }

        if ( !_strnicmp(Dest, v23, strlen(v23)) )
        {
            v12 = 4 * v6 + 289;
        }

        else if ( !_strnicmp(Dest, v26, strlen(v26)) )
        {
            v12 = 4 * v6 + 291;
        }

        else if ( !_strnicmp(Dest, v24, strlen(v24)) )
        {
            v12 = 4 * v6 + 288;
        }
        else
        {
            if ( _strnicmp(Dest, v25, strlen(v25)) )
            {
            LABEL_37:
                argNum = pArgNum;
                goto LABEL_38;
            }

            v12 = 4 * v6 + 290;
        }

        ctrlBtnNum = v12;
        goto LABEL_37;
    }

LABEL_38:
    if ( ctrlBtnNum == -1 )
    {
        v13 = jonesString_GetString("JONES_STR_JOYTWISTL");
        if ( v13 )
        {
            strcpy(Dest, v13);
        }
        else
        {
            memset(Dest, 0, sizeof(Dest));
        }

        v14 = jonesString_GetString("JONES_STR_JOYTWISTR");
        if ( v14 )
        {
            strcpy(v27, v14);
        }
        else
        {
            memset(v27, 0, sizeof(v27));
        }

        memset(v21, 0, sizeof(v21));
        sprintf(v21, "%s", pEntry->aArgs[*argNum].argName);
        if ( !_strnicmp(v21, Dest, strlen(Dest)) )
        {
            ctrlBtnNum = 32772;
        }

        else if ( !_strnicmp(v21, v27, strlen(v27)) )
        {
            ctrlBtnNum = 0x8005;
        }

        if ( ctrlBtnNum == -1 )
        {
            v15 = jonesString_GetString("JONES_STR_JOYUP");
            if ( v15 )
            {
                strcpy(v23, v15);
            }
            else
            {
                memset(v23, 0, sizeof(v23));
            }

            v16 = jonesString_GetString("JONES_STR_JOYDOWN");
            if ( v16 )
            {
                strcpy(v26, v16);
            }
            else
            {
                memset(v26, 0, sizeof(v26));
            }

            v17 = jonesString_GetString("JONES_STR_JOYLEFT");
            if ( v17 )
            {
                strcpy(v24, v17);
            }
            else
            {
                memset(v24, 0, sizeof(v24));
            }

            v18 = jonesString_GetString("JONES_STR_JOYRIGHT");
            if ( v18 )
            {
                strcpy(v25, v18);
            }
            else
            {
                memset(v25, 0, sizeof(v25));
            }

            if ( !_strnicmp(pEntry->aArgs[*argNum].argName, v23, strlen(v23)) )
            {
                ctrlBtnNum = 0x8000;
            }

            else if ( !_strnicmp(pEntry->aArgs[*argNum].argName, v26, strlen(v26)) )
            {
                ctrlBtnNum = 0x8002;
            }

            else if ( !_strnicmp(pEntry->aArgs[*argNum].argName, v24, strlen(v24)) )
            {
                ctrlBtnNum = 0x8003;
            }

            else if ( !_strnicmp(pEntry->aArgs[*argNum].argName, v25, strlen(v25)) )
            {
                ctrlBtnNum = 0x8001;
            }
        }
    }

    result = ctrlBtnNum;
    if ( ctrlBtnNum > -1 )
    {
        ++*argNum;
    }

    return result;

}

int J3DAPI jonesConfig_SetDefaultControlScheme(JonesControlsScheme* pScheme, int num)
{
    const char* pName; // eax
    int v3; // edx
    int (*aActions)[9]; // ecx
    int* v5; // eax
    int i; // esi
    unsigned int v7; // eax
    int v8; // edi
    int v9; // eax

    pName = jonesString_GetString(jonesConfig_aDfltKeySetNames[num]);
    if ( !pName )
    {
        return 0;
    }

    strcpy(pScheme->aName, pName);

    v3 = 0;
    aActions = pScheme->aActions;
    do
    {
        (*aActions)[0] = 0;
        v5 = jonesConfig_aDfltKeySets[num];
        for ( i = 1; i <= v5[v3]; v5 = jonesConfig_aDfltKeySets[num] )
        {
            v7 = *(DWORD*)(v5[v3 + 1] + 4 * i - 4);
            (*aActions)[i] = v7;
            if ( (v7 < 256 || v7 > 639) && (v7 < 32768 || v7 > 32775) )
            {
                v8 = ((unsigned __int8)(*aActions)[0] + 1) | (((*aActions)[0] & 0xFF00) + 256);
                v9 = (*aActions)[0] & 0xFF0000;
            }
            else
            {
                v8 = (((*aActions)[0] & 0xFF0000) + 0x10000) | (*aActions)[0] & 0xFF00;
                v9 = (unsigned __int8)(*aActions)[0] + 1;
            }

            ++i;
            (*aActions)[0] = v9 | v8;
        }

        v3 += 2;
        ++aActions;
    } while ( v3 < 74 );

    return 1;
}

void J3DAPI jonesConfig_BindControls(JonesControlsScheme* pConfig)
{
    SithControlFunction i; // esi
    SithControlFunction functionId; // esi
    int v3; // ebx
    int v4; // edx
    unsigned int controlId; // eax
    int v6; // edi
    char* v7; // ebp
    unsigned int* v8; // ebx
    int v9; // ecx
    int v10; // edi
    char* v11; // ebx
    unsigned int* v12; // ebp
    int j; // [esp+10h] [ebp-14h]
    int bJoystickControl; // [esp+14h] [ebp-10h]
    int v15; // [esp+18h] [ebp-Ch]
    int* v16; // [esp+1Ch] [ebp-8h]
    int v17; // [esp+1Ch] [ebp-8h]
    int bMouseControl; // [esp+20h] [ebp-4h]

    bMouseControl = wuRegistry_GetIntEx("Mouse Control", 0);
    bJoystickControl = wuRegistry_GetIntEx("Joystick Control", 0);
    if ( pConfig )
    {
        JonesMain_BindToggleMenuControlKeys(&pConfig->aActions[29][1], (unsigned __int8)pConfig->aActions[29][0]);// pConfig->aActions[29][0] & 0xFF
        JonesHud_BindActivateControlKeys(&pConfig->aActions[11][1], (unsigned __int8)pConfig->aActions[11][0]);// pConfig->aActions[11][0] & 0xFF

        for ( i = SITHCONTROL_WSELECT0; i <= SITHCONTROL_WSELECT16; ++i )
        {
            sithControl_UnbindFunction(i);
        }

        for ( j = 0; j < 37; ++j )
        {
            functionId = -1;
            if ( j == 11 || j == 2 || j == 3 )
            {
                v9 = 1;
                v17 = 1;
                if ( j <= 3 )
                {
                    v15 = 2;
                }
                else
                {
                    v15 = 3;
                }

                do
                {
                    if ( j == 2 )
                    {
                        if ( v9 == 1 )
                        {
                            functionId = SITHCONTROL_LEFT;
                        }

                        else if ( v9 == 2 )
                        {
                            functionId = SITHCONTROL_TURNLEFT;
                        }
                    }

                    else if ( j == 3 )
                    {
                        if ( v9 == 1 )
                        {
                            functionId = SITHCONTROL_RIGHT;
                        }

                        else if ( v9 == 2 )
                        {
                            functionId = SITHCONTROL_TURNRIGHT;
                        }
                    }
                    else
                    {
                        switch ( v9 )
                        {
                            case 1:
                                functionId = SITHCONTROL_ACT2;
                                break;

                            case 2:
                                functionId = SITHCONTROL_FIRE1;
                                break;

                            case 3:
                                functionId = SITHCONTROL_ACTIVATE;
                                break;
                        }
                    }

                    if ( functionId != -1 )
                    {
                        sithControl_UnbindFunction(functionId);
                        v10 = 1;
                        v11 = (char*)pConfig + 36 * j;
                        if ( (unsigned __int8)*((DWORD*)v11 + 1) )
                        {
                            v12 = (unsigned int*)(v11 + 8);
                            do
                            {
                                if ( *v12 < 256 )// keyboard
                                {
                                    sithControl_BindControl(functionId, *v12, (SithControlBindFlag)0);
                                }

                                else if ( bJoystickControl )
                                {
                                    jonesConfig_BindJoystickControl(functionId, *v12);
                                }

                                ++v10;
                                ++v12;
                            } while ( v10 <= (unsigned __int8)*((DWORD*)v11 + 1) );
                        }
                    }

                    v9 = ++v17;
                } while ( v17 <= v15 );
            }

            else if ( j < 16 || j == 28 || j == 29 )
            {
                switch ( j )
                {
                    case 0:
                        functionId = SITHCONTROL_FORWARD;
                        break;

                    case 1:
                        functionId = SITHCONTROL_BACK;
                        break;

                    case 4:
                        functionId = SITHCONTROL_STPLEFT;
                        break;

                    case 5:
                        functionId = SITHCONTROL_STPRIGHT;
                        break;

                    case 6:
                        functionId = SITHCONTROL_CRAWLTOGGLE;
                        break;

                    case 7:
                        functionId = SITHCONTROL_ACT1;
                        break;

                    case 8:
                        functionId = SITHCONTROL_ACT3;
                        break;

                    case 9:
                        functionId = SITHCONTROL_JUMP;
                        break;

                    case 10:
                        functionId = SITHCONTROL_LOOK;
                        break;

                    case 12:
                        functionId = SITHCONTROL_WEAPONTOGGLE;
                        break;

                    case 13:
                        functionId = SITHCONTROL_PREVWEAPON;
                        break;

                    case 14:
                        functionId = SITHCONTROL_NEXTWEAPON;
                        break;

                    case 15:
                        functionId = SITHCONTROL_LIGHTERTOGGLE;
                        break;

                    case 28:
                        functionId = SITHCONTROL_MAP;
                        break;

                    default:
                        break;
                }

                if ( functionId != -1 )
                {
                    sithControl_UnbindFunction(functionId);
                    if ( functionId == SITHCONTROL_FORWARD )
                    {
                        sithControl_UnbindFunction(SITHCONTROL_RUNFWD);
                    }

                    v6 = 1;
                    v7 = (char*)pConfig + 36 * j;
                    if ( (unsigned __int8)*((DWORD*)v7 + 1) )
                    {
                        v8 = (unsigned int*)(v7 + 8);
                        do
                        {
                            if ( *v8 < 256 )    // keyboard
                            {
                                sithControl_BindControl(functionId, *v8, (SithControlBindFlag)0);
                            }

                            else if ( bJoystickControl )
                            {
                                jonesConfig_BindJoystickControl(functionId, *v8);
                            }

                            ++v6;
                            ++v8;
                        } while ( v6 <= (unsigned __int8)*((DWORD*)v7 + 1) );
                    }
                }
            }
            else
            {
                v16 = pConfig->aActions[j];
                if ( (unsigned __int8)*v16 )
                {
                    v3 = 1;
                    if ( (unsigned __int8)*v16 )
                    {
                        do
                        {
                            switch ( j )
                            {
                                case 16:
                                    functionId = SITHCONTROL_WSELECT0;
                                    break;

                                case 17:
                                    functionId = SITHCONTROL_WSELECT1;
                                    break;

                                case 18:
                                    functionId = SITHCONTROL_WSELECT4;
                                    break;

                                case 19:
                                    functionId = SITHCONTROL_WSELECT7;
                                    break;

                                case 20:
                                    functionId = SITHCONTROL_WSELECT2;
                                    break;

                                case 21:
                                    functionId = SITHCONTROL_WSELECT5;
                                    break;

                                case 22:
                                    functionId = SITHCONTROL_WSELECT3;
                                    break;

                                case 23:
                                    functionId = SITHCONTROL_WSELECT8;
                                    break;

                                case 24:
                                    functionId = SITHCONTROL_WSELECT9;
                                    break;

                                case 25:
                                    functionId = SITHCONTROL_WSELECT6;
                                    break;

                                case 26:
                                    functionId = SITHCONTROL_WSELECT11;
                                    break;

                                case 27:
                                    functionId = SITHCONTROL_WSELECT10;
                                    break;

                                case 30:
                                    functionId = SITHCONTROL_HEALTH;
                                    break;

                                case 31:
                                    functionId = SITHCONTROL_WSELECT12;
                                    break;

                                case 32:
                                    functionId = SITHCONTROL_WSELECT13;
                                    break;

                                case 33:
                                    functionId = SITHCONTROL_WSELECT14;
                                    break;

                                case 34:
                                    functionId = SITHCONTROL_WSELECT15;
                                    break;

                                case 35:
                                    functionId = SITHCONTROL_WSELECT16;
                                    break;

                                case 36:
                                    functionId = SITHCONTROL_CHALK;
                                    break;

                                default:
                                    break;
                            }

                            if ( functionId != -1 )
                            {
                                v4 = v3 + 8 * j;
                                controlId = pConfig->aActions[0][v4 + j];
                                if ( controlId < 256 )// keyboard, up to 256
                                {
                                    // controlId is DIK num here
                                    sithControl_BindControl(functionId, controlId, (SithControlBindFlag)0);
                                }

                                else if ( bJoystickControl )
                                {
                                    jonesConfig_BindJoystickControl(functionId, pConfig->aActions[0][v4 + j]);
                                }
                            }

                            ++v3;
                        } while ( v3 <= (unsigned __int8)*v16 );
                    }
                }
            }
        }

        jonesConfig_EnableMouseControl(bMouseControl);
        if ( !bJoystickControl )
        {
            sithControl_UnbindJoystickAxes();
        }
    }
}

void J3DAPI jonesConfig_BindJoystickControl(SithControlFunction functionId, int controlId)
{
    int numJoysticks; // ecx
    int v3; // edi
    SithControlFunction v4; // esi
    unsigned int v5; // esi
    int v6; // edi
    int v7; // ebp
    SithControlFunction v8; // ebx
    int numJoysticks_1; // [esp+10h] [ebp-4h]

    numJoysticks = stdControl_GetNumJoysticks();
    numJoysticks_1 = numJoysticks;
    switch ( controlId )
    {
        case 32768:
            v3 = 1;
            v4 = STDCONTROL_AID_NEGATIVE_AXIS;
            break;

        case 32769:
            v3 = 0;
            v4 = STDCONTROL_AID_POSITIVE_AXIS;
            break;

        case 32770:
            v3 = 1;
            v4 = STDCONTROL_AID_POSITIVE_AXIS;
            break;

        case 32771:
            v3 = 0;
            v4 = STDCONTROL_AID_NEGATIVE_AXIS;
            break;

        case 32772:
            v3 = 5;
            v4 = STDCONTROL_AID_NEGATIVE_AXIS;
            break;

        case 32773:
            v3 = 5;
            v4 = STDCONTROL_AID_POSITIVE_AXIS;
            break;

        case 32774:
            v3 = 2;
            v4 = STDCONTROL_AID_NEGATIVE_AXIS;
            break;

        case 32775:
            v3 = 2;
            v4 = STDCONTROL_AID_POSITIVE_AXIS;
            break;

        default:
            v4 = functionId;
            v3 = -1;
            break;
    }

    if ( v3 == -1 )
    {
        if ( numJoysticks > 0 )
        {
            v5 = (controlId - 256) % 0x30u + 256;
            v6 = numJoysticks;
            do
            {
                sithControl_BindControl(functionId, v5, (SithControlBindFlag)0);
                v5 += 48;
                --v6;
            } while ( v6 );
        }
    }
    else
    {
        v7 = 0;
        if ( numJoysticks > 0 )
        {
            v8 = functionId;
            do
            {
                sithControl_BindAxis(v8, v3 | v4, (SithControlBindFlag)0);
                if ( v8 == SITHCONTROL_FORWARD && !stdControl_IsGamePad(v7) )
                {
                    v4 |= STDCONTROL_AID_LOW_SENSITIVITY;
                    v8 = SITHCONTROL_RUNFWD;
                    sithControl_BindAxis(SITHCONTROL_RUNFWD, v3 | v4, (SithControlBindFlag)0);
                }

                ++v7;
                v3 += 6;
            } while ( v7 < numJoysticks_1 );
        }
    }
}

//HFONT J3DAPI jonesConfig_InitDialog(HWND hWnd, HFONT hFont, int dlgID)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InitDialog, hWnd, hFont, dlgID);
//}

//HFONT J3DAPI jonesConfig_CreateDialogFont(HWND hWnd, int bWindowMode, int dlgResNum, float* pFontScale)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_CreateDialogFont, hWnd, bWindowMode, dlgResNum, pFontScale);
//}
//
//void J3DAPI jonesConfig_ResetDialogFont(HWND hWndParent, HFONT hFont)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_ResetDialogFont, hWndParent, hFont);
//}
//
//int __stdcall jonesConfig_SetWindowFontCallback(HWND hWnd, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_SetWindowFontCallback, hWnd, lparam);
//}
//
//BOOL __stdcall jonesConfig_SetPositionAndTextCallback(HWND hwnd, JonesDialogFontInfo* lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_SetPositionAndTextCallback, hwnd, lparam);
//}
//
//void J3DAPI jonesConfig_SetWindowFontAndPosition(HWND hwnd, JonesDialogFontInfo* pFontInfo)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_SetWindowFontAndPosition, hwnd, pFontInfo);
//}
//
//void J3DAPI jonesConfig_GetWindowScreenRect(HWND hWnd, LPRECT lpRect)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_GetWindowScreenRect, hWnd, lpRect);
//}
//
//void J3DAPI jonesConfig_SetDialogTitleAndPosition(HWND hWnd, JonesDialogFontInfo* pDlgFontInfo)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_SetDialogTitleAndPosition, hWnd, pDlgFontInfo);
//}

//int J3DAPI jonesConfig_GetSaveGameFilePath(HWND hWnd, char* pOutFilePath)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_GetSaveGameFilePath, hWnd, pOutFilePath);
//}

//UINT_PTR CALLBACK jonesConfig_SaveGameDialogHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameDialogHookProc, hDlg, msg, wParam, lParam);
//}
//
//int J3DAPI jonesConfig_SaveGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA lpOfn)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameDialogInit, hDlg, a2, lpOfn);
//}

//LRESULT CALLBACK jonesConfig_SaveGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameThumbnailPaintProc, hWnd, uMsg, wParam, lParam);
//}

int J3DAPI jonesConfig_ShowOverwriteSaveGameDlg(HWND hWnd, const char* aFilePath)
{
    GameSaveMsgBoxData data; // [esp+0h] [ebp-8h] BYREF

    data.dialogID = 214;
    data.pNdsFilePath = aFilePath;
    return JonesDialog_ShowDialog((LPCSTR)214, hWnd, jonesConfig_SaveGameMsgBoxProc, (LPARAM)&data);
}

//int J3DAPI jonesConfig_ShowExitGameDialog(HWND hWnd, char* pSaveGameFilePath)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowExitGameDialog, hWnd, pSaveGameFilePath);
//}
//
//INT_PTR CALLBACK jonesConfig_ExitGameDlgProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ExitGameDlgProc, hWnd, uMsg, wparam, lparam);
//}

INT_PTR CALLBACK jonesConfig_SaveGameMsgBoxProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    int bSuccess; // edi

    if ( umsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontGameSaveMsgBox);
        return 1;
    }

    else if ( umsg == WM_INITDIALOG )
    {
        jonesConfig_hFontGameSaveMsgBox = jonesConfig_InitDialog(hWnd, 0, *(DWORD*)lParam);// (GameSaveMsgBoxData *)lparam->dialogID
        bSuccess = jonesConfig_GameSaveSetData(hWnd, wParam, (GameSaveMsgBoxData*)lParam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return bSuccess;
    }
    else
    {
        if ( umsg == WM_COMMAND )
        {
            jonesConfig_MsgBoxDlg_HandleWM_COMMAND(hWnd, (unsigned __int16)wParam);
        }

        return 0;
    }
}

int J3DAPI jonesConfig_GameSaveSetData(HWND hDlg, int a2, GameSaveMsgBoxData* pData)
{
    const char* pNdsFilePath; // ebx
    const char* pOverwriteText; // edx
    const char* pProgressText; // eax MAPDST
    HWND hMsgTextCntrl; // eax MAPDST
    char aText[256]; // [esp+4h] [ebp-100h] BYREF

    if ( !pData )
    {
        return 0;
    }

    if ( pData->dialogID == 163 )               // if  load game message box
    {
        pProgressText = jonesString_GetString("JONES_STR_PROGRESS1");
        if ( pProgressText )
        {
            hMsgTextCntrl = GetDlgItem(hDlg, 1126);
            jonesConfig_SetTextControl(hDlg, hMsgTextCntrl, pProgressText);
        }
    }

    else if ( pData->dialogID == 214 )          // if save game overwrite message box
    {
        pNdsFilePath = pData->pNdsFilePath;
        pOverwriteText = jonesString_GetString("JONES_STR_OVERWRITE");
        if ( pOverwriteText )
        {
            memset(aText, 0, sizeof(aText));
            sprintf(aText, pOverwriteText, pNdsFilePath + 4);
            hMsgTextCntrl = GetDlgItem(hDlg, 1197);
            jonesConfig_SetTextControl(hDlg, hMsgTextCntrl, aText);
        }
    }

    SetWindowLongA(hDlg, DWL_USER, (LONG)pData);
    return 1;
}

void J3DAPI jonesConfig_MsgBoxDlg_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    GameSaveMsgBoxData* pData; // eax

    pData = (GameSaveMsgBoxData*)GetWindowLongA(hWnd, DWL_USER);
    if ( nResult > 0 )
    {
        if ( nResult <= 2 )
        {
            goto LABEL_7;
        }

        if ( nResult != 1187 )
        {
            return;
        }

        if ( pData->dialogID == 211 && jonesConfig_GetSaveGameFilePath(hWnd, (char*)pData->pNdsFilePath) != 1 )// in exit dialoge save game button was clicked
        {
            EndDialog(hWnd, 2);
        }
        else
        {
        LABEL_7:
            EndDialog(hWnd, nResult);
        }
    }
}

//int J3DAPI jonesConfig_GetLoadGameFilePath(HWND hWnd, char* pDestNdsPath)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_GetLoadGameFilePath, hWnd, pDestNdsPath);
//}

void* J3DAPI jonesConfig_sub_405F60(HWND hWnd)
{
    return (void*)GetWindowLongA(hWnd, DWL_USER);
}

//UINT_PTR __stdcall jonesConfig_LoadGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameDialogHookProc, hDlg, uMsg, wParam, lparam);
//}

int J3DAPI jonesConfig_ShowLoadGameWarningMsgBox(HWND hWnd)
{
    GameSaveMsgBoxData data; // [esp+0h] [ebp-8h] BYREF

    data.pNdsFilePath = 0;
    data.dialogID = 163;
    return JonesDialog_ShowDialog((LPCSTR)163, hWnd, jonesConfig_SaveGameMsgBoxProc, (LPARAM)&data);
}

//int J3DAPI jonesConfig_LoadGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA pofn)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameDialogInit, hDlg, a2, pofn);
//}

//LRESULT CALLBACK jonesConfig_LoadGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameThumbnailPaintProc, hWnd, uMsg, wParam, lParam);
//}

//int J3DAPI jonesConfig_ShowGamePlayOptions(HWND hWnd)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowGamePlayOptions, hWnd);
//}
//
//INT_PTR CALLBACK jonesConfig_GamePlayOptionsProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptionsProc, hWnd, msg, wparam, lparam);
//}
//
//LRESULT J3DAPI jonesConfig_HandleWM_HSCROLL(HWND hDlg, HWND hWnd, int a3)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_HandleWM_HSCROLL, hDlg, hWnd, a3);
//}
//
//int J3DAPI jonesConfig_GamePlayOptionsInitDlg(HWND hDlg)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptionsInitDlg, hDlg);
//}
//
//int J3DAPI jonesConfig_GamePlayOptions_HandleWM_COMMAND(HWND hDlg, int nResult)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptions_HandleWM_COMMAND, hDlg, nResult);
//}

//void J3DAPI jonesConfig_EnableMouseControl(int bEnable)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_EnableMouseControl, bEnable);
//}

void J3DAPI jonesConfig_FreeControlScheme(JonesControlsScheme* pConfig)
{
    int v1; // ecx
    JonesControlAction* pEntry; // eax

    v1 = 37;
    pEntry = (JonesControlAction*)pConfig->aActions;
    do
    {
        if ( pEntry )
        {
            pEntry->unknown0 = 0;
            pEntry->aUnknown1[0] = 0;
            pEntry->aUnknown1[1] &= ~0xFF; // Clears the low byte
        }

        ++pEntry;
        --v1;
    } while ( v1 );

    stdMemory_Free(pConfig);
}

void J3DAPI jonesConfig_FreeControlConfigEntry(JonesControlsConfig* pConfig)
{
    int v1; // ebp
    int v2; // edi
    JonesControlsScheme* v3; // eax
    int (*aActions)[9]; // eax
    int v5; // ecx

    v1 = 0;
    if ( pConfig->numSchemes > 0 )
    {
        v2 = 0;
        do
        {
            v3 = &pConfig->aSchemes[v2];
            if ( v3 )
            {
                aActions = v3->aActions;
                v5 = 37;
                do
                {
                    if ( aActions )
                    {
                        (*aActions)[0] = 0;
                        (*aActions)[1] = 0;
                        (*aActions)[2] &= ~0xFF;
                    }

                    ++aActions;
                    --v5;
                } while ( v5 );
            }

            ++v1;
            ++v2;
        } while ( v1 < pConfig->numSchemes );
    }

    if ( pConfig->unknown2 )
    {
        stdMemory_Free((void*)pConfig->unknown2);
        pConfig->unknown2 = 0;
    }

    if ( pConfig->aSchemes )
    {
        stdMemory_Free(pConfig->aSchemes);
        pConfig->aSchemes = 0;
    }
}

int J3DAPI jonesConfig_ShowControlOptions(HWND hWnd)
{
    int v1; // esi
    int bEnableControl; // eax
    JonesControlsConfig data; // [esp+8h] [ebp-18h] BYREF

    if ( !jonesConfig_InitControlsConfig() )
    {
        return 2;
    }

    memset(&data, 0, sizeof(data));
    if ( !jonesConfig_CopyControlConfig(&jonesConfig_curControlConfig, &data) )
    {
        return 2;
    }

    GetWindowLongA(hWnd, GWL_HINSTANCE);        // ???
    v1 = JonesDialog_ShowDialog((LPCSTR)111, hWnd, jonesConfig_ControlOptionsProc, (LPARAM)&data);
    if ( v1 == 1 )
    {
        wuRegistry_SaveStr("Configuration", data.aSchemes[data.selectedShemeIdx].aName);
        jonesConfig_BindControls(&data.aSchemes[data.selectedShemeIdx]);

        jonesConfig_FreeControlConfigEntry(&data);
        jonesConfig_FreeControlConfigEntry(&jonesConfig_curControlConfig);
        jonesConfig_curControlConfig.numSchemes = 0;
        bEnableControl = wuRegistry_GetIntEx("Mouse Control", 0);
        jonesConfig_EnableMouseControl(bEnableControl);
        return 1;
    }
    else
    {
        jonesConfig_FreeControlConfigEntry(&data);
        return v1;
    }
}

int J3DAPI jonesConfig_CopyControlConfig(JonesControlsConfig* pSrc, JonesControlsConfig* pDst)
{
    int result; // eax
    JonesControlsConfig* pDst_1; // ebx
    JonesControlsScheme* aCpySchemes; // edi
    int v5; // esi
    JonesControlsScheme* aSchemes; // eax

    if ( !pSrc )
    {
        return 0;
    }

    pDst_1 = pDst;
    if ( !pDst )
    {
        result = (int)STDMALLOC(0x18u);
        if ( (pDst_1 = (JonesControlsConfig*)result) == 0 )
        {
            return result;
        }
    }

    pDst_1->numSchemes = pSrc->numSchemes;
    pDst_1->selectedShemeIdx = pSrc->selectedShemeIdx;

    aCpySchemes = jonesConfig_CopyControlSchemes(pSrc->aSchemes, 0, pSrc->numSchemes);
    if ( aCpySchemes || !pSrc->aSchemes )
    {
        if ( pDst_1->aSchemes )
        {
            jonesConfig_FreeControlConfigEntry(pDst_1);
            pDst_1->aSchemes = 0;
        }

        pDst_1->aSchemes = aCpySchemes;
        v5 = 10 - pSrc->numSchemes % 10;
        if ( v5 <= 0 || v5 >= 10 )
        {
            return 1;
        }

        aSchemes = (JonesControlsScheme*)STDREALLOC(
            aCpySchemes,
            sizeof(JonesControlsScheme) * (v5 + pSrc->numSchemes));
        pDst_1->aSchemes = aSchemes;
        memset(&aSchemes[pSrc->numSchemes], 0, 4 * ((sizeof(JonesControlsScheme) * v5) >> 2));
        return 1;
    }
    else
    {
        return 0;
    }

    return result;
}

JonesControlsScheme* J3DAPI jonesConfig_CopyControlSchemes(JonesControlsScheme* aSchemes, int start, int sizeScheme)
{
    JonesControlsScheme* aDstSchemes; // ebp
    int v4; // ecx
    int v5; // ebx
    JonesControlsScheme* pScheme; // edx
    JonesControlAction* pSrcAction; // eax
    JonesControlAction* pDstAction; // edi
    int* p_unknown0; // edx
    int v10; // esi
    int* v11; // ecx
    bool v12; // zf
    int v14; // [esp+10h] [ebp-8h]
    JonesControlsScheme* v15; // [esp+14h] [ebp-4h]
    int aSchemesa; // [esp+1Ch] [ebp+4h]
    JonesControlsScheme* starta; // [esp+20h] [ebp+8h]
    int sizeSchemea; // [esp+24h] [ebp+Ch]

    aDstSchemes = (JonesControlsScheme*)STDMALLOC(1464 * sizeScheme);
    v15 = aDstSchemes;
    if ( !aDstSchemes || !aSchemes )
    {
        return 0;
    }

    memset(aDstSchemes, 0, 1464 * sizeScheme);
    v4 = sizeScheme + start;
    if ( start >= sizeScheme + start )
    {
        return aDstSchemes;
    }

    v5 = 1464 * start;
    sizeSchemea = 1464 * start;
    pScheme = (JonesControlsScheme*)aSchemes[start].aActions;// TODO: Fix offsets
    v14 = v4 - start;
    starta = pScheme;
    do
    {
        aSchemesa = 37;
        strcpy(&aDstSchemes->aName[sizeSchemea - v5], CONTAINING_RECORD(pScheme, JonesControlsScheme, aActions)->aName);// TODO: Fix offsets
        pSrcAction = (JonesControlAction*)pScheme;// TODO: Fix offsets to ->aActions
        pDstAction = (JonesControlAction*)((char*)aDstSchemes->aActions + sizeSchemea - v5);// TODO: Fix idex
        do
        {
            p_unknown0 = &pDstAction->unknown0;
            v10 = 0;
            pDstAction->unknown0 = 0;
            pDstAction->aUnknown1[0] = 0;
            pDstAction->aUnknown1[1] &= ~0xFF;
            v11 = &pSrcAction->unknown0;
            do
            {
                ++v10;
                *p_unknown0++ = *v11++;
            } while ( v10 <= (unsigned __int8)pSrcAction->unknown0 );

            aDstSchemes = v15;
            ++pSrcAction;
            ++pDstAction;
            --aSchemesa;
        } while ( aSchemesa );

        sizeSchemea += 1464;
        pScheme = starta + 1;
        v12 = v14 == 1;
        ++starta;
        --v14;
    } while ( !v12 );

    return aDstSchemes;
}

int J3DAPI jonesConfig_InitControlsConfig()
{
    JonesControlsConfig config; // [esp+4h] [ebp-18h] BYREF

    memset(&config, 0, sizeof(config));
    config.selectedShemeIdx = -1;
    if ( jonesConfig_SetDefaultControlSchemes(&config) && jonesConfig_LoadControlsSchemesFromSystem(&config) )
    {
        if ( jonesConfig_CopyControlConfig(&config, &jonesConfig_curControlConfig) )
        {
            jonesConfig_FreeControlConfigEntry(&config);
            return 1;
        }
        else
        {
            jonesConfig_FreeControlConfigEntry(&jonesConfig_curControlConfig);
            jonesConfig_FreeControlConfigEntry(&config);
            return 0;
        }
    }
    else
    {
        jonesConfig_FreeControlConfigEntry(&config);
        return 0;
    }
}

int J3DAPI jonesConfig_LoadControlsSchemesFromSystem(JonesControlsConfig* pConfig)
{
    HANDLE hFile; // ebx
    JonesControlsScheme* aSchemes; // edx
    CHAR Buffer[128]; // [esp+10h] [ebp-1C0h] BYREF
    WIN32_FIND_DATAA FindFileData; // [esp+90h] [ebp-140h] BYREF

    memset(Buffer, 0, sizeof(Buffer));
    GetCurrentDirectoryA(128u, Buffer);
    if ( !SetCurrentDirectoryA(jonesConfig_pKeySetsDirPath) )
    {
        return 1;
    }

    hFile = FindFirstFileA("*.kfg", &FindFileData);
    if ( hFile == (HANDLE)INVALID_HANDLE_VALUE )
    {
    LABEL_10:
        SetCurrentDirectoryA(Buffer);
        return 1;
    }

    while ( 1 )
    {
        if ( !(pConfig->numSchemes % 10) )
        {
            pConfig->aSchemes = (JonesControlsScheme*)STDREALLOC(
                pConfig->aSchemes,
                sizeof(JonesControlsScheme) * (pConfig->numSchemes + 10));
        }

        aSchemes = pConfig->aSchemes;
        if ( !aSchemes )
        {
            break;
        }

        if ( jonesConfig_LoadConstrolsScheme(FindFileData.cFileName, &aSchemes[pConfig->numSchemes]) )
        {
            ++pConfig->numSchemes;
        }

        if ( !FindNextFileA(hFile, &FindFileData) )
        {
            FindClose(hFile);
            goto LABEL_10;
        }
    }

    SetCurrentDirectoryA(Buffer);
    return 0;
}

int J3DAPI jonesConfig_SetDefaultControlSchemes(JonesControlsConfig* pConfig)
{
    int cfgNum; // edi
    JonesControlsScheme* aSchemes; // edx
    JonesControlsScheme* pScheme; // eax

    cfgNum = 0;
    while ( 1 )
    {
        if ( !(pConfig->numSchemes % 10) )
        {
            pConfig->aSchemes = (JonesControlsScheme*)STDREALLOC(
                pConfig->aSchemes,
                sizeof(JonesControlsScheme) * (pConfig->numSchemes + 10));
        }

        aSchemes = pConfig->aSchemes;
        if ( !aSchemes )
        {
            break;
        }

        pScheme = &aSchemes[pConfig->numSchemes];
        if ( !pScheme || !jonesConfig_SetDefaultControlScheme(pScheme, cfgNum) )
        {
            break;
        }

        ++cfgNum;
        ++pConfig->numSchemes;
        if ( cfgNum >= 3 )
        {
            return 1;
        }
    }

    return 0;
}

INT_PTR __stdcall jonesConfig_ControlOptionsProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    int res; // edi

    if ( umsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hwnd, jonesConfig_hFontControlOptions);
        return 1;
    }

    else if ( umsg == WM_INITDIALOG )
    {
        jonesConfig_hFontControlOptions = jonesConfig_InitDialog(hwnd, 0, 111);
        res = jonesConfig_InitControlOptionsDlg(hwnd, wparam, (JonesControlsConfig*)lparam);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return res;
    }
    else
    {
        if ( umsg == WM_COMMAND )
        {
            jonesConfig_ControlOptions_HandleWM_COMMAND(hwnd, (unsigned __int16)wparam, lparam, SHIWORD(wparam));
        }

        return 0;
    }
}

int J3DAPI jonesConfig_InitControlOptionsDlg(HWND hDlg, int a2, JonesControlsConfig* pConfig)
{
    int MaxJoystickButtons; // eax
    const char* pSelectedName; // eax
    HWND v5; // ebp
    HWND(__stdcall * pfGetDlgItem)(HWND, int); // edi
    HWND lbControlCfgList; // esi
    HWND lbControlCfgList_2; // eax
    int v9; // ebp
    const char* pConfigName; // ebp
    bool bLoop; // cc
    const char* String; // esi
    HWND btnDelScheme; // eax
    HWND btnEditSheme; // eax
    HWND v15; // esi
    int Int; // eax
    HWND v17; // edi
    int v18; // eax
    int i; // [esp+10h] [ebp-A8h]
    int schemeNum; // [esp+14h] [ebp-A4h]
    HWND lbControlCfgList_1; // [esp+18h] [ebp-A0h]
    HDC hdcList; // [esp+1Ch] [ebp-9Ch]
    SIZE textSize; // [esp+20h] [ebp-98h] BYREF
    RECT rectList; // [esp+28h] [ebp-90h] BYREF
    char aSelectedConfigName[128]; // [esp+38h] [ebp-80h] BYREF

    if ( pConfig->selectedShemeIdx == -1 )
    {
        memset(aSelectedConfigName, 0, sizeof(aSelectedConfigName));
        wuRegistry_GetStr("Configuration", aSelectedConfigName, 128u, std_g_aEmptyString);
        if ( !strlen(aSelectedConfigName) )
        {
            MaxJoystickButtons = stdControl_GetMaxJoystickButtons();
            if ( MaxJoystickButtons == 4 )
            {
                pSelectedName = jonesString_GetString(jonesConfig_aDfltKeySetNames[1]);
            }
            else
            {
                pSelectedName = MaxJoystickButtons == 8
                    ? jonesString_GetString(jonesConfig_aDfltKeySetNames[2])
                    : jonesString_GetString(jonesConfig_aDfltKeySetNames[0]);
            }

            if ( pSelectedName )
            {
                strcpy(aSelectedConfigName, pSelectedName);
            }
        }
    }

    v5 = hDlg;
    pfGetDlgItem = GetDlgItem;
    pConfig->selectedShemeIdx = 0;
    lbControlCfgList = GetDlgItem(hDlg, 1047);
    lbControlCfgList_1 = lbControlCfgList;

    lbControlCfgList_2 = GetDlgItem(hDlg, 1047);// ?? why another call for the same control
    hdcList = GetDC(lbControlCfgList_2);

    schemeNum = 0;
    if ( pConfig->numSchemes > 0 )
    {
        v9 = 0;
        for ( i = 0; ; v9 = i )
        {
            SendMessageA(lbControlCfgList, LB_ADDSTRING, 0, (LPARAM)&pConfig->aSchemes->aName[v9]);
            *(int*)((char*)&pConfig->aSchemes->unknown0 + v9) = 0;
            pConfigName = &pConfig->aSchemes->aName[v9];
            if ( !strcmp(aSelectedConfigName, pConfigName) )
            {
                pConfig->selectedShemeIdx = schemeNum;
            }

            GetTextExtentPointA(hdcList, pConfigName, strlen(pConfigName), &textSize);
            if ( textSize.cx > (int)pConfig->unknown0 )
            {
                pConfig->unknown0 = (void*)textSize.cx;
            }

            bLoop = ++schemeNum < pConfig->numSchemes;
            i += 1464;
            if ( !bLoop )
            {
                break;
            }

            lbControlCfgList = lbControlCfgList_1;
        }

        v5 = hDlg;
        lbControlCfgList = lbControlCfgList_1;
        pfGetDlgItem = GetDlgItem;
    }

    GetClientRect(lbControlCfgList, &rectList);
    if ( rectList.right - rectList.left < (int)pConfig->unknown0 )
    {
        SendMessageA(lbControlCfgList, LB_SETHORIZONTALEXTENT, (WPARAM)pConfig->unknown0, 0);
    }

    SendMessageA(lbControlCfgList, LB_SETCURSEL, pConfig->selectedShemeIdx, 0);
    if ( pConfig->selectedShemeIdx < 3 )
    {
        String = jonesString_GetString("JONES_STR_VIEW_SCHEME");
        btnDelScheme = pfGetDlgItem(v5, 1022);  // delete scheme
        EnableWindow(btnDelScheme, 0);
        if ( String )
        {
            btnEditSheme = pfGetDlgItem(v5, 1028);
            SetWindowTextA(btnEditSheme, String);
        }
    }

    v15 = pfGetDlgItem(v5, 1053);
    Int = wuRegistry_GetIntEx("Mouse Control", 0);
    SendMessageA(v15, 0xF1u, Int, 0);
    v17 = pfGetDlgItem(v5, 1054);
    if ( stdControl_GetNumJoysticks() )
    {
        v18 = wuRegistry_GetIntEx("Joystick Control", 0);
        SendMessageA(v17, 0xF1u, v18, 0);
    }
    else
    {
        EnableWindow(v17, 0);
    }

    SetWindowLongA(v5, 8, (LONG)pConfig);
    return 1;
}

void J3DAPI jonesConfig_ControlOptions_HandleWM_COMMAND(HWND hWnd, int ctrlID, int a3, int16_t a4)
{
    JonesControlsConfig* pConfig_1; // eax
    int v6; // ebx
    JonesControlsConfig* pConfig; // esi
    HWND cbMouse; // eax
    HWND cbJoystick; // eax
    int v10; // ebx
    int v11; // ebp
    void* unknown2; // eax
    int schemeNum; // ebx
    const char* pErrorStr; // eax
    const char* String; // eax
    JonesControlsScheme* pScheme; // esi
    HWND DlgItem; // eax
    LRESULT v18; // ebx
    int bJoystickEnabled; // [esp+10h] [ebp-4h]
    int hWnda; // [esp+18h] [ebp+4h]
    int a4a; // [esp+24h] [ebp+10h]

    pConfig_1 = (JonesControlsConfig*)GetWindowLongA(hWnd, DWL_USER);
    v6 = ctrlID;
    pConfig = pConfig_1;
    if ( ctrlID > 1022 )
    {
        switch ( ctrlID )
        {
            case 1028:
                goto LABEL_38;                  // edit scheme

            case 1029:                          // new config scheme
                jonesConfig_CreateNewSchemeAction(hWnd, pConfig_1);
                return;

            case 1047:
                DlgItem = GetDlgItem(hWnd, 1047);
                v18 = SendMessageA(DlgItem, 0x188u, 0, 0);
                jonesConfig_sub_407F60(hWnd);
                pConfig->selectedShemeIdx = v18;
                if ( a4 == 2 )
                {
                LABEL_38:
                    jonesConfig_sub_408260(hWnd, pConfig);
                }

                break;
        }
    }
    else
    {
        switch ( ctrlID )
        {
            case 1022:                          // delete config scheme
                jonesConfig_sub_408000(hWnd, (int)pConfig_1);
                return;

            case 1:                             // ok btn clicked
                cbMouse = GetDlgItem(hWnd, 1053);
                a4a = SendMessageA(cbMouse, BM_GETCHECK, 0, 0);

                cbJoystick = GetDlgItem(hWnd, 1054);
                bJoystickEnabled = SendMessageA(cbJoystick, BM_GETCHECK, 0, 0);

                v10 = 0;
                if ( pConfig->unknown1 > 0 )
                {
                    v11 = 0;
                    do
                    {
                        remove((LPCSTR)(v11 + pConfig->unknown2));
                        ++v10;
                        v11 += 128;
                    } while ( v10 < pConfig->unknown1 );
                }

                unknown2 = (void*)pConfig->unknown2;
                pConfig->unknown1 = 0;
                if ( unknown2 )
                {
                    stdMemory_Free(unknown2);
                    pConfig->unknown2 = 0;
                }

                if ( jonesConfig_CopyControlConfig(pConfig, &jonesConfig_curControlConfig) )
                {
                    hWnda = 3;
                    if ( pConfig->numSchemes > 3 )
                    {
                        schemeNum = 3;
                        do
                        {
                            if ( pConfig->aSchemes[schemeNum].unknown0 == 1
                                && !jonesConfig_WriteScheme(&pConfig->aSchemes[schemeNum]) )
                            {
                                pErrorStr = jonesString_GetString("JONES_STR_NO_MEM_SCHEME");
                                if ( pErrorStr )
                                {
                                    jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", pErrorStr, 145);
                                    InvalidateRect(hWnd, 0, 1);
                                }
                            }

                            ++schemeNum;
                            ++hWnda;
                        } while ( hWnda < pConfig->numSchemes );
                    }
                }
                else
                {
                    String = jonesString_GetString("JONES_STR_NO_MEM_SCHEME");
                    if ( String )
                    {
                        jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", String, 145);
                        InvalidateRect(hWnd, 0, 1);
                    }

                    ctrlID = 2;
                }

                wuRegistry_SaveIntEx("Mouse Control", a4a);
                wuRegistry_SaveIntEx("Joystick Control", bJoystickEnabled);

                if ( bJoystickEnabled )
                {
                    pScheme = jonesConfig_NewControlScheme();
                    if ( pScheme )
                    {
                        JonesControl_EnableJoystickAxes();
                        jonesConfig_BindControls(pScheme);
                        jonesConfig_FreeControlScheme(pScheme);
                    }
                }
                else
                {
                    sithControl_UnbindJoystickAxes();
                }

                v6 = ctrlID;
                break;

            case 2:                             // cacnel btn clicked
                break;

            default:
                return;
        }

        if ( jonesConfig_dword_551DEC )
        {
            stdMemory_Free(jonesConfig_dword_551DEC);
            jonesConfig_dword_551DEC = 0;
        }

        EndDialog(hWnd, v6);
    }
}

int J3DAPI jonesConfig_WriteScheme(JonesControlsScheme* pScheme)
{
    size_t v1; // eax
    void* v2; // ebx
    unsigned int v3; // ecx
    char* v4; // esi
    FILE* pFile; // ebp
    const char* String; // eax
    const char* v7; // eax
    unsigned int v8; // eax
    unsigned int v9; // esi
    const char* v10; // eax
    const char** v11; // eax
    int (*aActions)[9]; // esi
    const char* v13; // eax
    unsigned int v14; // eax
    unsigned int v15; // edx
    int (*v16)[9]; // esi
    unsigned int v17; // eax
    unsigned int v18; // edx
    bool v19; // cc
    char* Format; // [esp+10h] [ebp-320h]
    unsigned int* v22; // [esp+14h] [ebp-31Ch]
    int (*v23)[9]; // [esp+18h] [ebp-318h]
    const char** v24; // [esp+1Ch] [ebp-314h]
    int v25; // [esp+20h] [ebp-310h]
    struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+24h] [ebp-30Ch] BYREF
    CHAR aCurDir[128]; // [esp+30h] [ebp-300h] BYREF
    char v28[256]; // [esp+B0h] [ebp-280h] BYREF
    char aKfgPath[128]; // [esp+1B0h] [ebp-180h] BYREF
    char pDest[256]; // [esp+230h] [ebp-100h] BYREF

    if ( !SetCurrentDirectoryA(jonesConfig_pKeySetsDirPath) )
    {
        SecurityAttributes.lpSecurityDescriptor = 0;
        SecurityAttributes.nLength = 12;
        SecurityAttributes.bInheritHandle = 1;
        CreateDirectoryA(jonesConfig_pKeySetsDirPath, &SecurityAttributes);

        memset(aCurDir, 0, sizeof(aCurDir));
        GetCurrentDirectoryA(128u, aCurDir);

        SetCurrentDirectoryA(jonesConfig_pKeySetsDirPath);
    }

    v1 = jonesConfig_dword_551D20;
    if ( (int)jonesConfig_dword_551D20 <= jonesConfig_dword_5510C0 )
    {
        v1 = jonesConfig_dword_5510C0;
    }

    v2 = STDMALLOC(v1);
    if ( !v2 )
    {
        return 0;
    }

    v3 = jonesConfig_dword_5510C0;
    if ( (int)jonesConfig_dword_551D20 > jonesConfig_dword_5510C0 )
    {
        v3 = jonesConfig_dword_551D20;
    }

    memset(v2, 0x20u, v3);

    v4 = (char*)STDMALLOC(jonesConfig_dword_5510C4 + jonesConfig_dword_5510B8);
    Format = v4;
    if ( v4 )
    {
        memset(v4, 0, jonesConfig_dword_5510B8 + jonesConfig_dword_5510C4);
        memset(aKfgPath, 0, sizeof(aKfgPath));
        sprintf(aKfgPath, "%s%s", pScheme->aName, ".kfg");

        pFile = fopen(aKfgPath, "wt+");
        if ( pFile )
        {
            String = jonesString_GetString("JONES_STR_HEADING");
            if ( String )
            {
                fprintf(pFile, String);
                fprintf(pFile, "\n");
                sprintf((char*)&SecurityAttributes, "%s\n\n", "1");
                fprintf(pFile, (const char*)&SecurityAttributes);
                memset(v4, 0, jonesConfig_dword_5510C4 + jonesConfig_dword_5510B8);
                v7 = jonesString_GetString("JONES_STR_ACTIONS");
                if ( v7 )
                {
                    strcpy(v4, v7);
                    v8 = jonesConfig_dword_551D20;
                    v9 = jonesConfig_dword_551D20 - strlen(v4);
                    if ( (int)jonesConfig_dword_551D20 <= jonesConfig_dword_5510C0 )
                    {
                        v8 = jonesConfig_dword_5510C0;
                    }

                    memset(v2, 0, v8);
                    memset(v2, 0x20u, v9);
                    strcat(Format, (const char*)v2);
                    v10 = jonesString_GetString("JONES_STR_KEYS");
                    if ( v10 )
                    {
                        strcat(Format, v10);
                        fprintf(pFile, Format);
                        fprintf(pFile, "\n\n");
                        v11 = jonesConfig_aJonesControlActionNames;
                        v24 = jonesConfig_aJonesControlActionNames;
                        aActions = pScheme->aActions;
                        v23 = pScheme->aActions;
                        while ( 1 )
                        {
                            v13 = jonesString_GetString(*v11);
                            if ( !aActions || !v13 )
                            {
                                break;
                            }

                            memset(v28, 0, sizeof(v28));
                            _snprintf(v28, 256u, "\"%s\"", v13);
                            fprintf(pFile, v28);

                            v14 = jonesConfig_dword_551D20;
                            v15 = jonesConfig_dword_551D20 - strlen(v28);
                            if ( (int)jonesConfig_dword_551D20 <= jonesConfig_dword_5510C0 )
                            {
                                v14 = jonesConfig_dword_5510C0;
                            }

                            memset(v2, 0, v14);
                            memset(v2, 0x20u, v15);
                            fprintf(pFile, (const char*)v2);
                            v16 = v23;
                            v25 = 1;
                            if ( (unsigned __int8)(*v23)[0] )
                            {
                                v22 = (unsigned int*)&(*v23)[1];
                                do
                                {
                                    memset(pDest, 0, sizeof(pDest));
                                    jonesConfig_ControlToString(*v22, pDest);
                                    _snprintf(v28, 0x100u, "\"%s\"", pDest);
                                    fprintf(pFile, v28);
                                    v17 = jonesConfig_dword_5510C0;
                                    v18 = jonesConfig_dword_5510C0 - strlen(pDest);
                                    if ( (int)jonesConfig_dword_551D20 > jonesConfig_dword_5510C0 )
                                    {
                                        v17 = jonesConfig_dword_551D20;
                                    }

                                    memset(v2, 0, v17);
                                    memset(v2, 0x20u, v18);
                                    fprintf(pFile, (const char*)v2);
                                    v16 = v23;
                                    ++v22;
                                    ++v25;
                                } while ( v25 <= (unsigned __int8)(*v23)[0] );
                            }

                            fprintf(pFile, "\n");
                            v11 = v24 + 1;
                            aActions = v16 + 1;
                            v19 = (v24 + 1 - jonesConfig_aJonesControlActionNames) < JONES_CONTROL_ACTION_COUNT;
                            v23 = aActions;
                            ++v24;
                            if ( !v19 )
                            {
                                fclose(pFile);
                                SetCurrentDirectoryA(aCurDir);
                                stdMemory_Free(v2);
                                stdMemory_Free(Format);
                                return 1;
                            }
                        }
                    }

                    v4 = Format;
                }
            }

            fclose(pFile);
            SetCurrentDirectoryA(aCurDir);
            stdMemory_Free(v2);
            stdMemory_Free(v4);
        }
        else
        {
            SetCurrentDirectoryA(aCurDir);
            stdMemory_Free(v4);
            stdMemory_Free(v2);
        }
    }
    else
    {
        stdMemory_Free(v2);
    }

    return 0;

}

int J3DAPI jonesConfig_sub_407F60(HWND hDlg)
{
    HWND DlgItem; // eax
    LRESULT v2; // ebx
    HWND v3; // ebp
    const char* v4; // eax
    HWND v5; // eax
    const char* String; // eax
    HWND v8; // eax

    DlgItem = GetDlgItem(hDlg, 1047);
    v2 = SendMessageA(DlgItem, 0x188u, 0, 0);
    v3 = GetDlgItem(hDlg, 1028);
    if ( v2 >= 3 )
    {
        String = jonesString_GetString("JONES_STR_EDIT_SCHEME");
        if ( String )
        {
            SetWindowTextA(v3, String);
        }

        v8 = GetDlgItem(hDlg, 1022);
        return EnableWindow(v8, 1);
    }
    else
    {
        v4 = jonesString_GetString("JONES_STR_VIEW_SCHEME");
        if ( v4 )
        {
            SetWindowTextA(v3, v4);
        }

        v5 = GetDlgItem(hDlg, 1022);
        return EnableWindow(v5, 0);
    }
}

LRESULT J3DAPI jonesConfig_sub_408000(HWND hDlg, int a2)
{
    WPARAM v2; // esi
    LRESULT result; // eax
    int v4; // edx
    const char* i; // edi
    int v6; // eax
    int v7; // edx
    int v8; // edx
    int v9; // esi
    int v10; // eax
    int v11; // edx
    HWND DlgItem; // eax
    WPARAM v13; // [esp-8h] [ebp-124h]
    int v14; // [esp+10h] [ebp-10Ch]
    int v15; // [esp+14h] [ebp-108h]
    HWND hWnd; // [esp+18h] [ebp-104h]
    char lParam[128]; // [esp+1Ch] [ebp-100h] BYREF
    char Dest[128]; // [esp+9Ch] [ebp-80h] BYREF

    v14 = 0;
    hWnd = GetDlgItem(hDlg, 1047);
    v2 = SendMessageA(hWnd, 0x188u, 0, 0);
    memset(lParam, 0, sizeof(lParam));
    SendMessageA(hWnd, 0x189u, v2, (LPARAM)lParam);
    result = SendMessageA(hWnd, 0x182u, v2, 0);
    v4 = *(DWORD*)(a2 + 12);
    if ( v4 <= 0 )
    {
        return result;
    }

    for ( i = (const char*)(*(DWORD*)(a2 + 20) + 1336); strcmp(i, lParam); i += 1464 )
    {
        result = ++v14;
        if ( v14 >= v4 )
        {
            return result;
        }
    }

    if ( !(*(DWORD*)(a2 + 4) % 10) )
    {
        *(DWORD*)(a2 + 8) = STDREALLOC(
            *(void**)(a2 + 8),
            (*(DWORD*)(a2 + 4) + 10) << 7);
    }

    if ( *(DWORD*)(1464 * v14 + *(DWORD*)(a2 + 20)) != 1 )
    {
        memset(Dest, 0, sizeof(Dest));
        sprintf(Dest, "%s\\%s%s", jonesConfig_pKeySetsDirPath, lParam, ".kfg");
        strcpy((char*)(((*(DWORD*)(a2 + 4))++ << 7) + *(DWORD*)(a2 + 8)), Dest);
    }

    v6 = 0;
    do
    {
        v7 = v6 + 1464 * v14;
        v6 += 36;
        v8 = v7 + *(DWORD*)(a2 + 20) + 4;
        *(DWORD*)v8 = 0;
        *(DWORD*)(v8 + 4) = 0;
        *(BYTE*)(v8 + 8) = 0;
    } while ( v6 < 1332 );

    v9 = v14;
    v10 = *(DWORD*)(a2 + 12);
    v15 = v14;
    if ( v14 < v10 )
    {
        v11 = 1464 * v14;
        do
        {
            if ( v9 == v10 - 1 )
            {
                memset((void*)(*(DWORD*)(a2 + 20) + v11), 0, 0x5B8u);
            }
            else
            {
                memcpy((void*)(v11 + *(DWORD*)(a2 + 20)), (const void*)(v11 + *(DWORD*)(a2 + 20) + 1464), 0x5B8u);
                v9 = v15;
            }

            v10 = *(DWORD*)(a2 + 12);
            ++v9;
            v11 += 1464;
            v15 = v9;
        } while ( v9 < v10 );

        v9 = v14;
    }

    result = *(DWORD*)(a2 + 16);
    if ( v9 == result )
    {
        v13 = result - 1 < 0 ? 0 : result - 1;
        *(DWORD*)(a2 + 16) = v13;
        result = SendMessageA(hWnd, 0x186u, v13, 0);
        if ( *(int*)(a2 + 16) < 3 )
        {
            DlgItem = GetDlgItem(hDlg, 1022);
            result = EnableWindow(DlgItem, 0);
        }
    }

    -- * (DWORD*)(a2 + 12);
    return result;
}

void J3DAPI jonesConfig_sub_408260(HWND hDlg, JonesControlsConfig* a2)
{
    HWND DlgItem; // esi
    WPARAM v3; // edx
    int v4; // ebp
    char* aName; // edx
    JonesControlsScheme* aSchemes; // eax
    int v7; // eax
    int v8; // ecx
    int v9; // edx
    int v10; // ebx
    void* a1[5]; // [esp+10h] [ebp-94h] BYREF
    char lParam[128]; // [esp+24h] [ebp-80h] BYREF

    DlgItem = GetDlgItem(hDlg, 1047);
    v3 = SendMessageA(DlgItem, 0x188u, 0, 0);
    memset(lParam, 0, sizeof(lParam));
    v4 = 0;
    SendMessageA(DlgItem, 0x189u, v3, (LPARAM)lParam);
    if ( a2->numSchemes > 0 )
    {
        aName = a2->aSchemes->aName;
        while ( strcmp(aName, lParam) )
        {
            ++v4;
            aName += 1464;
            if ( v4 >= a2->numSchemes )
            {
                goto LABEL_7;
            }
        }

        aSchemes = a2->aSchemes;
        a1[2] = 0;
        a1[3] = 0;
        a1[0] = jonesConfig_CopyControlSchemes(aSchemes, v4, 1);
        a1[1] = (void*)v4;
        a1[4] = jonesConfig_sub_408400(a2);
    }

LABEL_7:
    if ( v4 != a2->numSchemes )
    {
        if ( jonesConfig_ShowEditControlShemeDialog(hDlg, a1) == 1 )
        {
            InvalidateRect(hDlg, 0, 1);
            a2->aSchemes[v4].unknown0 = *(DWORD*)a1[0];
            if ( a2->aSchemes[v4].unknown0 )
            {
                v7 = 4;
                v8 = 1464 * v4 + 4;
                do
                {
                    v9 = 9;
                    do
                    {
                        v8 += 4;
                        v10 = *(DWORD*)((char*)a1[0] + v7);
                        v7 += 4;
                        *(DWORD*)((char*)a2->aSchemes + v8 - 4) = v10;
                        --v9;
                    } while ( v9 );
                } while ( v7 < 1336 );
            }

            stdMemory_Free(a1[0]);
        }
        else
        {
            jonesConfig_FreeControlScheme((JonesControlsScheme*)a1[0]);
        }
    }
}

JonesControlsScheme* J3DAPI jonesConfig_sub_408400(JonesControlsConfig* pConfig)
{
    int numButtons; // eax
    const char* String; // eax
    int v3; // edi
    JonesControlsScheme* i; // ebp
    JonesControlsScheme* pConfiga; // [esp+14h] [ebp+4h]

    numButtons = stdControl_GetMaxJoystickButtons();
    if ( numButtons == 4 )
    {
        String = jonesString_GetString(jonesConfig_aDfltKeySetNames[1]);
    }

    else if ( numButtons == 8 )
    {
        String = jonesString_GetString(jonesConfig_aDfltKeySetNames[2]);
    }
    else
    {
        String = jonesString_GetString(jonesConfig_aDfltKeySetNames[0]);
    }

    if ( !String )
    {
        return 0;
    }

    v3 = 0;
    pConfiga = pConfig->aSchemes;
    for ( i = (JonesControlsScheme*)pConfiga->aName; strcmp((const char*)i, String); ++i )
    {
        if ( ++v3 >= 3 )
        {
            return 0;
        }
    }

    return &pConfiga[v3];
}

void J3DAPI jonesConfig_CreateNewSchemeAction(HWND hDlg, JonesControlsConfig* pConfig)
{
    JonesControlsScheme* v2; // edx
    const char* v3; // eax
    int numSchemes; // edx
    int selectedIdx; // ebp
    const char* aName; // edx
    int v7; // eax
    int v8; // ebp
    int v9; // eax
    int v10; // esi
    int v11; // edx
    HWND v12; // esi
    HDC hdc; // edx
    int v14; // eax
    int v15; // ecx
    int v16; // edx
    int v17; // edi
    const char* String; // eax
    int v19; // [esp+10h] [ebp-B8h]
    int v20; // [esp+14h] [ebp-B4h]
    int a1[6]; // [esp+18h] [ebp-B0h] BYREF
    RECT Rect; // [esp+34h] [ebp-94h] BYREF
    char aSchemeName[128]; // [esp+44h] [ebp-84h] BYREF
    HWND DlgItem; // [esp+C4h] [ebp-4h]
    JonesControlsScheme* pBytes; // [esp+D4h] [ebp+Ch]

    memset(aSchemeName, 0, sizeof(aSchemeName));
    DlgItem = GetDlgItem(hDlg, 1047);
    if ( jonesConfig_ShowCreateControlSchemeDialog(hDlg, aSchemeName) == 1 )
    {
        InvalidateRect(hDlg, 0, 1);
        v2 = jonesConfig_CopyControlSchemes(pConfig->aSchemes, 0, 1);
        pBytes = v2;
        if ( v2 )
        {
            strcpy(v2->aName, aSchemeName);
            a1[0] = (int)v2;
            numSchemes = pConfig->numSchemes;
            a1[2] = 0;
            a1[1] = numSchemes;
            a1[3] = 0;
            a1[4] = (int)jonesConfig_sub_408400(pConfig);
            if ( jonesConfig_ShowEditControlShemeDialog(hDlg, a1) == 1 )
            {
                InvalidateRect(hDlg, 0, 1);
                selectedIdx = 3;
                v20 = 3;
                if ( pConfig->numSchemes > 3 )
                {
                    aName = pConfig->aSchemes[3].aName;// TODO: fix offsets
                    do
                    {
                        if ( strcmp(aSchemeName, aName) < 0 )
                        {
                            break;
                        }

                        ++selectedIdx;
                        aName += 1464;
                    } while ( selectedIdx < pConfig->numSchemes );

                    v20 = selectedIdx;
                }

                if ( !(pConfig->numSchemes % 10) )
                {
                    pConfig->aSchemes = (JonesControlsScheme*)STDREALLOC(
                        pConfig->aSchemes,
                        1464 * (pConfig->numSchemes + 10));
                }

                if ( pConfig->aSchemes )
                {
                    v7 = pConfig->numSchemes - 1;
                    if ( v7 >= selectedIdx )
                    {
                        v8 = v7;
                        v19 = pConfig->numSchemes - v20;
                        do
                        {
                            strcpy(pConfig->aSchemes[v8 + 1].aName, pConfig->aSchemes[v8].aName);
                            v9 = v8 * 1464 + 1468;
                            v10 = 37;
                            do
                            {
                                v11 = 9;
                                do
                                {
                                    v9 += 4;
                                    --v11;
                                    *(DWORD*)((char*)pConfig->aSchemes + v9 - 4) = *(DWORD*)((char*)&pConfig->aSchemes[-1]
                                        + v9
                                        - 4);
                                } while ( v11 );

                                --v10;
                            } while ( v10 );

                            --v8;
                            --v19;
                        } while ( v19 );

                        selectedIdx = v20;
                    }

                    v12 = GetDlgItem(hDlg, 1047);
                    SendMessageA(v12, LB_INSERTSTRING, selectedIdx, (LPARAM)aSchemeName);
                    SendMessageA(v12, LB_SETCURSEL, selectedIdx, 0);
                    pConfig->selectedShemeIdx = selectedIdx;

                    hdc = GetDC(v12);
                    GetTextExtentPointA(hdc, aSchemeName, strlen(aSchemeName), (LPSIZE)&a1[5]);// TODO: make new var for 4th param
                    if ( a1[5] > (int)pConfig->unknown0 )
                    {
                        pConfig->unknown0 = (void*)a1[5];
                        GetClientRect(v12, &Rect);
                        if ( Rect.right - Rect.left < a1[5] )
                        {
                            SendMessageA(v12, LB_SETHORIZONTALEXTENT, a1[5], 0);
                        }
                    }

                    pConfig->aSchemes[selectedIdx].unknown0 = *(DWORD*)a1[0];
                    strcpy(pConfig->aSchemes[selectedIdx].aName, (const char*)(a1[0] + 1336));
                    v14 = 4;
                    v15 = 1464 * selectedIdx + 4;
                    do
                    {
                        v16 = 9;
                        do
                        {
                            v15 += 4;
                            v17 = *(DWORD*)(a1[0] + v14);
                            v14 += 4;
                            *(DWORD*)((char*)pConfig->aSchemes + v15 - 4) = v17;
                            --v16;
                        } while ( v16 );
                    } while ( v14 < 1336 );

                    stdMemory_Free((void*)a1[0]);
                    ++pConfig->numSchemes;
                }
                else
                {
                    String = jonesString_GetString("JONES_STR_NO_MEM_SCHEME");
                    if ( String )
                    {
                        jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_CTRL_OPTS", String, 145);
                        InvalidateRect(hDlg, 0, 1);
                    }
                }
            }
            else
            {
                stdMemory_Free(pBytes);
            }
        }
        else
        {
            v3 = jonesString_GetString("JONES_STR_NO_MEM_SCHEME");
            if ( v3 )
            {
                jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_CTRL_OPTS", v3, 145);
                InvalidateRect(hDlg, 0, 1);
            }
        }
    }
}

int J3DAPI jonesConfig_ShowCreateControlSchemeDialog(HWND hWnd, char* pDstSchemeName)
{
    GetWindowLongA(hWnd, GWL_HINSTANCE);
    return JonesDialog_ShowDialog((LPCSTR)116, hWnd, jonesConfig_CreateControlSchemeProc, (LPARAM)pDstSchemeName);
}

INT_PTR __stdcall jonesConfig_CreateControlSchemeProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int ControlScheme; // edi

    if ( msg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontCreateControlSchemeDlg);
        return 1;
    }

    else if ( msg == WM_INITDIALOG )
    {
        jonesConfig_hFontCreateControlSchemeDlg = jonesConfig_InitDialog(hWnd, 0, 116);
        ControlScheme = jonesConfig_InitCreateControlScheme(hWnd, wparam, (char*)lparam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return ControlScheme;
    }
    else
    {
        if ( msg == WM_COMMAND )
        {
            jonesConfig_CreateControlScheme_Handle_WM_COMMAND(hWnd, wparam);
        }

        return 0;
    }
}

int J3DAPI jonesConfig_InitCreateControlScheme(HWND hDlg, int a2, char* pSchemeName)
{
    HWND ebSchemeName; // esi

    ebSchemeName = GetDlgItem(hDlg, 1052);
    SetFocus(ebSchemeName);
    SendMessageA(ebSchemeName, EM_SETLIMITTEXT, 60u, 0);
    SetWindowLongA(hDlg, DWL_USER, (LONG)pSchemeName);
    return 0;
}

void J3DAPI jonesConfig_CreateControlScheme_Handle_WM_COMMAND(HWND hWnd, int16_t nResult)
{
    HWND v2; // esi
    char* pControlSchemeName; // ebx
    HWND ebSchemeName; // ebp
    const char* v5; // edx
    WPARAM v6; // ebp
    LRESULT v7; // eax
    const char* v8; // eax
    const char* String; // eax
    signed int v10; // [esp+10h] [ebp-208h]
    HWND v11; // [esp+14h] [ebp-204h]
    CHAR aName[128]; // [esp+18h] [ebp-200h] BYREF
    char lParam[128]; // [esp+98h] [ebp-180h] BYREF
    char Dest[256]; // [esp+118h] [ebp-100h] BYREF

    v2 = hWnd;
    pControlSchemeName = (char*)GetWindowLongA(hWnd, DWL_USER);
    if ( nResult != 1 )
    {
        if ( nResult != 2 )
        {
            return;
        }

        goto LABEL_15;
    }

    ebSchemeName = GetDlgItem(hWnd, 1052);
    memset(aName, 0, sizeof(aName));
    v11 = ebSchemeName;
    GetWindowTextA(ebSchemeName, aName, 128);
    if ( strlen(aName) == strcspn(aName, "/:\\\"?<>*|+") )
    {
        v6 = 0;
        memset(lParam, 0, sizeof(lParam));
        v7 = SendMessageA(*((HWND*)pControlSchemeName + 32), LB_GETCOUNT, 0, 0);
        v10 = v7;
        if ( v7 <= 0 )
        {
        LABEL_13:
            if ( v6 == v7 )
            {
                GetWindowTextA(v11, pControlSchemeName, 128);
            }

        LABEL_15:
            EndDialog(v2, nResult);
            return;
        }

        while ( 1 )
        {
            SendMessageA(*((HWND*)pControlSchemeName + 32), 0x189u, v6, (LPARAM)lParam);
            if ( !strcmp(aName, lParam) )
            {
                break;
            }

            if ( !strlen(aName) )
            {
                String = jonesString_GetString("JONES_STR_NO_SCHEME");
                if ( !String )
                {
                    return;
                }

                jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", String, 145);
                InvalidateRect(hWnd, 0, 1);
                return;
            }

            v7 = v10;
            if ( (int)++v6 >= v10 )
            {
                v2 = hWnd;
                goto LABEL_13;
            }
        }

        v8 = jonesString_GetString("JONES_STR_DUP_SCHEME");
        if ( v8 )
        {
            jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", v8, 145);
            InvalidateRect(hWnd, 0, 1);
        }

        SetWindowTextA(v11, std_g_aEmptyString);
    }
    else
    {
        v5 = jonesString_GetString("JONES_STR_INVALIDFILE");
        if ( v5 )
        {
            memset(Dest, 0, sizeof(Dest));
            sprintf(Dest, v5, aName);
            jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", Dest, 145);
            InvalidateRect(hWnd, 0, 1);
        }

        SetWindowTextA(ebSchemeName, std_g_aEmptyString);
    }
}

int J3DAPI jonesConfig_ShowEditControlShemeDialog(HWND hWnd, void* dwInitParam)
{
    GetWindowLongA(hWnd, GWL_HINSTANCE);
    return JonesDialog_ShowDialog((LPCSTR)115, hWnd, jonesConfig_EditControlSchemProc, (LPARAM)dwInitParam);
}

INT_PTR __stdcall jonesConfig_EditControlSchemProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int inited; // ebx
    LONG WindowLongA; // esi
    int v7; // eax

    inited = 1;
    if ( msg <= WM_NOTIFY )
    {
        if ( msg != WM_NOTIFY )
        {
            if ( msg != WM_DESTROY )
            {
                return 0;
            }

            jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontEditControlShceme);
            return 1;
        }

        WindowLongA = GetWindowLongA(hWnd, 8);
        if ( *(DWORD*)(lparam + 8) != -2 )
        {
            return inited;
        }

        v7 = *(DWORD*)(lparam + 4);
        if ( v7 == 1005 )
        {
            *(DWORD*)(WindowLongA + 8) = GetDlgItem(hWnd, 1005);
            *(DWORD*)(WindowLongA + 12) = 1005;
            return 1;
        }

        if ( v7 != 1006 )
        {
            return inited;
        }

        *(DWORD*)(WindowLongA + 8) = GetDlgItem(hWnd, 1006);
        *(DWORD*)(WindowLongA + 12) = 1006;
        return 1;
    }

    if ( msg == WM_INITDIALOG )
    {
        jonesConfig_hFontEditControlShceme = jonesConfig_InitDialog(hWnd, 0, 115);
        inited = jonesConfig_InitEditControlSchemeDlg(hWnd, wparam, (void*)lparam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return inited;
    }

    if ( msg != WM_COMMAND )
    {
        return 0;
    }

    jonesConfig_sub_409200(hWnd, (unsigned __int16)wparam);
    return 0;
}

int J3DAPI jonesConfig_InitEditControlSchemeDlg(HWND hDlg, int a2, void* dwNewLong)
{
    HWND DlgItem; // edi
    HWND v4; // ebp
    const char* String; // eax
    HWND v6; // eax
    HWND v7; // eax
    HWND v8; // eax
    HWND v9; // eax
    HWND v10; // eax
    HWND v11; // eax
    char Dest[256]; // [esp+10h] [ebp-100h] BYREF

    DlgItem = GetDlgItem(hDlg, 1005);
    v4 = GetDlgItem(hDlg, 1006);
    jonesConfig_sub_408ED0(DlgItem, "JONES_STR_MAPKEY");
    jonesConfig_sub_408FC0(DlgItem, 1005, *(JonesControlsScheme**)dwNewLong);
    jonesConfig_sub_408ED0(v4, "JONES_STR_MAPBUTTON");
    jonesConfig_sub_408FC0(v4, 1006, *(JonesControlsScheme**)dwNewLong);
    memset(Dest, 0, sizeof(Dest));
    String = jonesString_GetString("JONES_STR_SETTINGS");
    if ( String )
    {
        sprintf(Dest, String, *(DWORD*)dwNewLong + 1336);
        v6 = GetDlgItem(hDlg, 1049);
        SetWindowTextA(v6, Dest);
    }

    if ( *((int*)dwNewLong + 1) < 3 )
    {
        v7 = GetDlgItem(hDlg, 1056);
        EnableWindow(v7, 0);

        v8 = GetDlgItem(hDlg, 1046);
        EnableWindow(v8, 0);

        v9 = GetDlgItem(hDlg, 1038);
        EnableWindow(v9, 0);

        v10 = GetDlgItem(hDlg, 1);
        EnableWindow(v10, 0);

        v11 = GetDlgItem(hDlg, 1099);
        EnableWindow(v11, 0);
    }

    SetWindowLongA(hDlg, 8, (LONG)dwNewLong);
    return 1;
}

LRESULT J3DAPI jonesConfig_sub_408ED0(HWND hWnd, char* pKey)
{
    HWND v2; // ebx
    int v3; // esi
    double v4; // st7
    int width; // [esp+Ch] [ebp-34h] BYREF
    struct tagRECT Rect; // [esp+10h] [ebp-30h] BYREF
    LPARAM lParam[2]; // [esp+20h] [ebp-20h] BYREF
    int v9; // [esp+28h] [ebp-18h]
    const char* String; // [esp+2Ch] [ebp-14h]
    int v11; // [esp+30h] [ebp-10h]
    int v12; // [esp+34h] [ebp-Ch]

    v2 = hWnd;
    GetClientRect(hWnd, &Rect);
    v3 = Rect.right - Rect.left - GetSystemMetrics(2);
    lParam[0] = 15;
    v11 = 256;
    lParam[1] = 0;
    stdDisplay_GetBackBufferSize((unsigned int*)&width, (unsigned int*)&hWnd);// TODO: make new var for last param
    v4 = (double)(int)hWnd * 0.002083333333333333;
    if ( v4 > 1.0 )
    {
        v4 = 1.0;
    }

    String = jonesString_GetString("JONES_STR_FCTN");
    v9 = v3 - (__int64)(v4 * 105.0);
    v12 = 0;
    SendMessageA(v2, LVM_INSERTCOLUMNA, 0, (LPARAM)lParam);
    if ( pKey )
    {
        String = jonesString_GetString(pKey);
    }

    v12 = 1;
    v9 = (__int64)(v4 * 105.0);
    return SendMessageA(v2, LVM_INSERTCOLUMNA, 1u, (LPARAM)lParam);
}

const char** J3DAPI jonesConfig_sub_408FC0(HWND hWnd, int a2, JonesControlsScheme* a3)
{
    const char** result; // eax
    int (*aActions)[9]; // edi
    WPARAM v5; // ebx
    signed int v6; // esi
    int v7; // eax
    LPARAM v8; // [esp+10h] [ebp-194h]
    signed int* v9; // [esp+14h] [ebp-190h]
    int v10; // [esp+18h] [ebp-18Ch]
    int (*v11)[9]; // [esp+1Ch] [ebp-188h]
    const char** pActionName; // [esp+20h] [ebp-184h]
    int v13; // [esp+24h] [ebp-180h]
    CHAR* String; // [esp+28h] [ebp-17Ch]
    LVITEM item; // [esp+2Ch] [ebp-178h] BYREF
    LPARAM v16[10]; // [esp+54h] [ebp-150h] BYREF
    LPARAM v17[10]; // [esp+7Ch] [ebp-128h] BYREF
    char pDest[256]; // [esp+A4h] [ebp-100h] BYREF

    result = jonesConfig_aJonesControlActionNames;
    aActions = a3->aActions;
    item.mask = 13;
    item.cchTextMax = 256;
    item.state = 0;
    item.stateMask = 0;
    v5 = 0;
    v8 = 0;
    pActionName = jonesConfig_aJonesControlActionNames;
    v11 = a3->aActions;
    // Rewrite as for loop
    for ( int i = 0; i < JONES_CONTROL_ACTION_COUNT; i++ )
    {
        v10 = 0;
        String = (CHAR*)jonesString_GetString(*result);
        v13 = 1;
        if ( (unsigned __int8)(*aActions)[0] )
        {
            v9 = &(*aActions)[1];
            do
            {
                v6 = *v9;
                v7 = a2;
                item.iItem = v5;
                item.iSubItem = 0;
                item.pszText = String;
                if ( a2 == 1005 && (v6 < 256 || v6 > 639) && (v6 < 0x8000 || v6 > 0x8007)
                    || a2 == 1006 && (v6 >= 256 && v6 <= 639 || v6 >= 0x8000 && v6 <= 0x8007) )
                {
                    if ( a2 == 1006 )
                    {
                        ++v10;
                    }

                    item.lParam = v8 | (v6 << 16);
                    SendMessageA(hWnd, LVM_INSERTITEMA, 0, (LPARAM)&item);
                    memset(pDest, 0, sizeof(pDest));
                    jonesConfig_ControlToString(v6, pDest);

                    v17[2] = 1;
                    v17[5] = (LPARAM)pDest;
                    SendMessageA(hWnd, LVM_SETITEMTEXTA, v5, (LPARAM)v17);
                    v7 = a2;
                    aActions = v11;
                    ++v5;
                }

                ++v9;
                ++v13;
            } while ( v13 <= (unsigned __int8)(*aActions)[0] );
        }
        else
        {
            v7 = a2;
        }

        if ( !v10 && v7 == 1006 )
        {
            item.lParam = v8;
            SendMessageA(hWnd, LVM_INSERTITEMA, 0, (LPARAM)&item);
            memset(pDest, 0, sizeof(pDest));
            v16[2] = 1;
            v16[5] = (LPARAM)pDest;
            SendMessageA(hWnd, LVM_SETITEMTEXTA, v5, (LPARAM)v16);
            aActions = v11;
            ++v5;
        }

        v11 = ++aActions;
        ++v8;
        result = ++pActionName;
    }

    return result;
}

char J3DAPI jonesConfig_sub_409200(HWND hWnd, int nResult)
{
    HWND v2; // esi
    LONG pData; // eax
    int v4; // ecx
    LONG v5; // ebp
    const char** v6; // ebx
    const char* String; // eax
    int i; // edi
    int v9; // eax
    int v10; // edx
    DWORD* v11; // ecx
    char* v12; // esi
    HWND v14; // [esp+10h] [ebp-408h]
    HWND DlgItem; // [esp+10h] [ebp-408h]
    HWND v16; // [esp+14h] [ebp-404h]
    char v17[512]; // [esp+18h] [ebp-400h] BYREF
    char Dest[512]; // [esp+218h] [ebp-200h] BYREF

    v2 = hWnd;
    pData = GetWindowLongA(hWnd, DWL_USER);
    v4 = nResult;
    v5 = pData;
    if ( nResult > 1038 )
    {
        pData = (pData & ~0xFF) | ((nResult - 22) & 0xFF);
        if ( nResult == 1046 )
        {
            if ( *(int*)(v5 + 4) >= 3 )
            {
                char temp = jonesConfig_sub_4097D0(hWnd, *(HWND*)(v5 + 8), *(DWORD*)(v5 + 12), *(DWORD*)v5);
                pData = (pData & ~0xFF) | ((int)temp & 0xFF);
            }
        }
        else
        {
            pData = (pData & ~0xFF) | ((nResult - 32) & 0xFF);
            if ( nResult == 1056 )
            {
                if ( *(int*)(v5 + 4) >= 3 )
                {
                    LPARAM temp = jonesConfig_sub_409530(hWnd, *(HWND*)(v5 + 8), *(DWORD*)(v5 + 12), *(DWORD*)v5);
                    pData = (pData & ~0xFF) | (temp & 0xFF);
                }
            }
            else
            {
                pData = (pData & ~0xFF) | ((nResult - 75) & 0xFF);
                if ( nResult == 1099 )
                {
                    DlgItem = GetDlgItem(hWnd, 1005);
                    v16 = GetDlgItem(hWnd, 1006);
                    for ( i = 0; i < 1332; i += 36 )
                    {
                        v9 = *(DWORD*)v5 + i + 4;
                        v10 = 0;
                        v11 = (DWORD*)(i + *(DWORD*)(v5 + 16) + 4);
                        *(DWORD*)v9 = 0;
                        *(DWORD*)(v9 + 4) = 0;
                        *(BYTE*)(v9 + 8) = 0;
                        v12 = (char*)v11 - v9;
                        do
                        {
                            ++v10;
                            *(DWORD*)v9 = *(DWORD*)&v12[v9];
                            v9 += 4;
                        } while ( v10 <= (unsigned __int8)*v11 );
                    }

                    SendMessageA(DlgItem, 0x1009u, 0, 0);
                    SendMessageA(v16, 0x1009u, 0, 0);
                    jonesConfig_sub_408FC0(DlgItem, 1005, *(JonesControlsScheme**)v5);
                    pData = (pData & ~0xFF) | ((unsigned __int8)jonesConfig_sub_408FC0(v16, 1006, *(JonesControlsScheme**)v5) & 0xFF);
                }
            }
        }
    }

    else if ( nResult == 1038 )
    {
        if ( *(int*)(pData + 4) >= 3 )
        {
            LPARAM temp = jonesConfig_sub_409BC0(
                (int)hWnd,
                *(HWND*)(pData + 8),
                *(DWORD*)(pData + 12),
                *(DWORD*)pData);

            pData = (pData & ~0xFF) | (temp & 0xFF);
        }
    }
    else
    {
        if ( nResult != 1 )
        {
            pData = (pData & ~0xFF) | ((nResult - 2) & 0xFF);

            if ( nResult != 2 )
            {
                return pData;
            }

            goto LABEL_15;
        }

        v14 = 0;
        memset(v17, 0, sizeof(v17));
        v6 = jonesConfig_aJonesCapControlActionNames;

        // Rewrote as for loop
        for ( int i = 0; i < JONES_CONTROL_ACTION_COUNT; i++ )
        {
            if ( !*((BYTE*)v14 + *(DWORD*)v5 + 4)
                && ((int)v6 < (int)&jonesConfig_aJonesCapControlActionNames[16]
                    || (int)v6 > (int)&jonesConfig_aJonesCapControlActionNames[24]) )
            {
                strcat(v17, jonesString_GetString(*v6));
                strcat(v17, "\n");
                v2 = hWnd;
            }

            ++v6;
            v14 += 9;
        }

        if ( !strlen(v17) )
        {
            **(DWORD**)v5 = 1;
            v4 = 1;

        LABEL_15:
            pData = (pData & ~0xFF) | (EndDialog(v2, v4) & 0xFF);
            return pData;
        }

        memset(Dest, 0, sizeof(Dest));
        String = jonesString_GetString("JONES_STR_NO_MAPNG");
        sprintf(Dest, "%s\n", String);
        strcat(Dest, v17);
        jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", Dest, 145);
        pData = (pData & ~0xFF) | (InvalidateRect(hWnd, 0, 1) & 0xFF);
    }

    return pData;
}

LPARAM J3DAPI jonesConfig_sub_409530(HWND hWnd, HWND a2, int a3, int a4)
{
    LPARAM result; // eax
    LPARAM* v5; // esi
    int v6; // ecx
    HWND v7; // [esp+Ch] [ebp-16Ch] BYREF
    LPARAM v8; // [esp+10h] [ebp-168h] BYREF
    LPARAM v9[10]; // [esp+14h] [ebp-164h] BYREF
    LPARAM lParam[10]; // [esp+3Ch] [ebp-13Ch] BYREF
    DWORD dwInitParam[69]; // [esp+64h] [ebp-114h] BYREF

    memset(dwInitParam, 0, sizeof(dwInitParam));
    dwInitParam[1] = a4;
    dwInitParam[0] = jonesConfig_sub_4096F0((int)hWnd, a2, a4, &v7, &v8);
    dwInitParam[67] = a3;
    if ( dwInitParam[0] >= 0 )
    {
        result = jonesConfig_AssignKeyAction(hWnd, dwInitParam);
        if ( result == 1 )
        {
            v5 = (LPARAM*)(a4 + 36 * dwInitParam[0] + 4);
            result = InvalidateRect(hWnd, 0, 1);
            if ( v5 )
            {
                v7 = (HWND)SendMessageA(a2, 0x100Cu, 0xFFFFFFFF, 2);
                lParam[2] = 1;
                lParam[5] = (LPARAM)&dwInitParam[2];
                SendMessageA(a2, 0x102Eu, (WPARAM)v7, (LPARAM)lParam);
                v9[0] = 4;
                v9[1] = (LPARAM)v7;
                v9[2] = 0;
                v9[8] = dwInitParam[0] | (dwInitParam[66] << 16);
                SendMessageA(a2, 0x1006u, 0, (LPARAM)v9);
                result = v8;
                v5[v8 + 1] = dwInitParam[66];
                if ( dwInitParam[67] != 1005 || (result = *v5, BYTE1(*v5)) )
                {
                    if ( dwInitParam[67] == 1006 )
                    {
                        result = *v5;
                        if ( (*v5 & 0xFF0000) == 0 )
                        {
                            result = (unsigned __int8)*v5 + 1;
                            *v5 = result | *v5 & 0xFF00 | 0x10000;
                        }
                    }
                }
                else
                {
                    result = (unsigned __int8)*v5 + 1;
                    v6 = result | *v5 & 0xFF0000;
                    //BYTE1(v6) = BYTE1(result) | 1;
                    v6 = (v6 & ~(0xFF << 8)) | ((((result >> 8) & 0xFF) | 1) << 8);
                    *v5 = v6;
                }
            }
        }
    }
    else
    {
        result = (LPARAM)jonesString_GetString("JONES_STR_NOKEYACTION");
        if ( result )
        {
            jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", (const char*)result, 145);
            return InvalidateRect(hWnd, 0, 1);
        }
    }

    return result;
}

int J3DAPI jonesConfig_sub_4096F0(int a1, HWND hWnd, int a3, HWND* a4, uint32_t* a5)
{
    unsigned int i; // [esp+0h] [ebp-40h]
    HWND v7; // [esp+4h] [ebp-3Ch]
    int v8; // [esp+8h] [ebp-38h]
    int v9; // [esp+Ch] [ebp-34h]
    unsigned int v10; // [esp+10h] [ebp-30h]
    LPARAM lParam[8]; // [esp+14h] [ebp-2Ch] BYREF
    int v12 = 0; // [esp+34h] [ebp-Ch]
    DWORD* v13; // [esp+3Ch] [ebp-4h]

    if ( !hWnd || !a1 || !a3 )
    {
        return -1;
    }

    v7 = (HWND)SendMessageA(hWnd, 0x100Cu, 0xFFFFFFFF, 2);
    if ( (int)v7 < 0 )
    {
        return -1;
    }

    lParam[0] = 4;
    lParam[1] = (LPARAM)v7;
    lParam[2] = 0;
    SendMessageA(hWnd, 0x1005u, 0, (LPARAM)lParam);
    v8 = (unsigned __int16)0; // v12 uninitialized, TODO: FIX?
    v10 = (0 & 0xFFFF0000) >> 16; // Set v12 to 0 because uninitialized, TODO: FIX?
    v9 = 0;
    v13 = (DWORD*)(a3 + 36 * (unsigned __int16)v12 + 4);
    for ( i = 1; i <= (unsigned __int8)*v13 && v13[i] != v10; ++i )
    {
        ++v9;
    }

    if ( v10 && (unsigned __int8)*v13 && i > (unsigned __int8)*v13 )
    {
        return -1;
    }

    if ( a4 )
    {
        *a4 = v7;
    }

    if ( a5 )
    {
        *a5 = v9;
    }

    return v8;
}

char J3DAPI jonesConfig_sub_4097D0(HWND a1, HWND hWnd, int a3, int a4)
{
    const char* String; // eax
    int v5; // ebx
    const char* v6; // eax
    const char* v7; // eax
    int v8; // eax
    LRESULT v9; // ebp
    int i; // eax
    const char* v11; // eax
    int v12; // eax
    int v13; // edx
    int v14; // edx
    LPARAM lParam; // [esp+10h] [ebp-664h] BYREF
    WPARAM wParam; // [esp+14h] [ebp-660h]
    int v18; // [esp+18h] [ebp-65Ch]
    int v19; // [esp+1Ch] [ebp-658h]
    int v20; // [esp+20h] [ebp-654h]
    const char* v21; // [esp+24h] [ebp-650h]
    int v22; // [esp+28h] [ebp-64Ch]
    int v23; // [esp+30h] [ebp-644h]
    LPARAM v24[10]; // [esp+38h] [ebp-63Ch] BYREF
    DWORD dwInitParam[69]; // [esp+60h] [ebp-614h] BYREF
    char Dest[256]; // [esp+174h] [ebp-500h] BYREF
    char v27[512]; // [esp+274h] [ebp-400h] BYREF
    char Format[512]; // [esp+474h] [ebp-200h] BYREF

    memset(dwInitParam, 0, sizeof(dwInitParam));

    lParam = 4;
    v18 = 0;
    wParam = SendMessageA(hWnd, LVM_GETNEXTITEM, 0xFFFFFFFF, 2);
    if ( (wParam & 0x80000000) != 0 )
    {
        String = jonesString_GetString("JONES_STR_NOKEYACTION");
        if ( !String )
        {
            return (char)String;
        }

        jonesConfig_ShowMessageDialog(a1, "JONES_STR_CTRL_OPTS", String, 145);

        //LOBYTE(String) = InvalidateRect(a1, 0, 1);
        //return (char)String;

        // Can't set low byte of const char*
        // Low byte is essentially first char of String
        // Return cast to char directly, hopefully correct?
        return (char)InvalidateRect(a1, 0, 1);
    }

    SendMessageA(hWnd, LVM_GETITEMA, 0, (LPARAM)&lParam);
    dwInitParam[0] = (unsigned __int16)0; // v23 uninitialized, TODO: FIX?
    dwInitParam[1] = a4;
    dwInitParam[67] = a3;
    String = (const char*)jonesConfig_AssignKeyAction(a1, dwInitParam);
    if ( String != (const char*)1 )
    {
        return (char)String;
    }

    v5 = a4 + 36 * dwInitParam[0] + 4;
    InvalidateRect(a1, 0, 1);
    if ( !v5 )
    {
        String = jonesString_GetString("JONES_STR_NO_MEM_ASGNMNT");
        if ( !String )
        {
            return (char)String;
        }

        jonesConfig_ShowMessageDialog(a1, "JONES_STR_CTRL_OPTS", String, 145);

    LABEL_31:
        //LOBYTE(String) = InvalidateRect(a1, 0, 1);
        //return (char)String;
        return (char)InvalidateRect(a1, 0, 1);
    }

    if ( *(BYTE*)v5 == 8 )
    {
        memset(Dest, 0, sizeof(Dest));
        v6 = jonesString_GetString("JONES_STR_EXCEED");
        if ( v6 )
        {
            strcpy(Format, v6);
        }
        else
        {
            memset(Format, 0, sizeof(Format));
        }

        v7 = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[dwInitParam[0]]);
        if ( v7 )
        {
            strcpy(v27, v7);
        }
        else
        {
            memset(v27, 0, sizeof(v27));
        }

        //LOBYTE(String) = Format[0];
        if ( Format[0] )
        {
            //LOBYTE(String) = v27[0];
            if ( v27[0] )
            {
                sprintf(Dest, Format, v27);
                jonesConfig_ShowMessageDialog(a1, "JONES_STR_CTRL_OPTS", Dest, 145);
                goto LABEL_31;
            }
        }
    }
    else
    {
        if ( a3 == 1005 )
        {
            v8 = *(unsigned __int8*)(v5 + 1);
        }
        else
        {
            v8 = *(unsigned __int8*)(v5 + 2);
        }

        if ( v8 <= 0 )
        {
            lParam = 4;
            v23 = dwInitParam[0] | (dwInitParam[66] << 16);
            SendMessageA(hWnd, LVM_SETITEMA, 0, (LPARAM)&lParam);
        }
        else
        {
            v9 = SendMessageA(hWnd, LVM_GETITEMCOUNT, 0, 0);
            for ( i = dwInitParam[0]; dwInitParam[0] == (unsigned __int16)0; i = dwInitParam[0] ) // set v23 to 0 because uninitialized, TODO: FIX?
            {
                if ( (int)wParam >= v9 )
                {
                    break;
                }

                ++wParam;
                SendMessageA(hWnd, LVM_GETITEMA, 0, (LPARAM)&lParam);
            }

            v11 = jonesString_GetString(jonesConfig_aJonesControlActionNames[i]);
            if ( v11 )
            {
                v21 = v11;
                lParam = 13;
                v19 = 0;
                v20 = 0;
                v22 = 256;
                v23 = dwInitParam[0] | (dwInitParam[66] << 16);
                SendMessageA(hWnd, LVM_INSERTITEMA, 0, (LPARAM)&lParam);
            }
        }

        v24[4] = 3;
        v24[3] = 3;
        SendMessageA(hWnd, LVM_SETITEMSTATE, wParam, (LPARAM)v24);
        v24[2] = 1;
        v24[5] = (LPARAM)&dwInitParam[2];
        SendMessageA(hWnd, LVM_SETITEMTEXTA, wParam, (LPARAM)v24);
        *(DWORD*)(v5 + 4 * (unsigned __int8)*(DWORD*)v5 + 4) = dwInitParam[66];
        v12 = *(DWORD*)v5;
        if ( a3 == 1005 )
        {
            v13 = (unsigned __int8)v12 + 1;
            String = (const char*)(v12 & 0xFF0000);
            *(DWORD*)v5 = (unsigned int)String | v13 | ((*(DWORD*)v5 & 0xFF00) + 256);
        }
        else
        {
            v14 = (v12 & 0xFF0000) + 0x10000;
            String = (const char*)((unsigned __int8)*(DWORD*)v5 + 1);
            *(DWORD*)v5 = (unsigned int)String | v14 | *(DWORD*)v5 & 0xFF00;
        }
    }

    return (char)String;
}

LPARAM J3DAPI jonesConfig_sub_409BC0(int a1, HWND hWnd, int a3, int a4)
{
    int v4; // ebx
    HWND v5; // ebp
    LPARAM result; // eax
    LPARAM v7; // edi
    int* v8; // esi
    int v9; // ecx
    DWORD* v10; // eax
    int v11; // eax
    int v12; // edx
    int v13; // edx
    LPARAM v14[10]; // [esp+10h] [ebp-50h] BYREF
    LPARAM lParam[10]; // [esp+38h] [ebp-28h] BYREF

    v4 = a4;
    v5 = hWnd;
    result = jonesConfig_sub_4096F0(a1, hWnd, a4, &hWnd, &a1);
    v7 = result;
    if ( result < 0 )
    {
        return result;
    }

    if ( a3 == 1005 )
    {
        v8 = (int*)(v4 + 36 * result + 4);
        result = *(unsigned __int8*)(v4 + 36 * result + 5);
    }
    else
    {
        result = *(unsigned __int8*)(v4 + 36 * result + 6);
        v8 = (int*)(v4 + 36 * v7 + 4);
    }

    if ( !result )
    {
        return result;
    }

    if ( result <= 1 )
    {
        lParam[2] = 1;
        lParam[5] = (LPARAM)std_g_aEmptyString;
        SendMessageA(v5, 0x102Eu, (WPARAM)hWnd, (LPARAM)lParam);
        v14[0] = 4;
        v14[1] = (LPARAM)hWnd;
        v14[2] = 0;
        v14[8] = v7;
        SendMessageA(v5, 0x1006u, 0, (LPARAM)v14);
        v4 = a4;
    }
    else
    {
        SendMessageA(v5, 0x1008u, (WPARAM)hWnd, 0);
    }

    v9 = a1 + 1;
    if ( a1 + 1 < (unsigned __int8)*v8 )
    {
        v10 = (DWORD*)(v4 + 4 * (v9 + 8 * v7 + v7) + 4);
        do
        {
            ++v9;
            *v10 = v10[1];
            ++v10;
        } while ( v9 < (unsigned __int8)*v8 );
    }

    v11 = *v8;
    if ( a3 == 1005 )
    {
        v12 = (unsigned __int8)v11 - 1;
        result = v11 & 0xFF0000;
        *v8 = result | v12 | ((*v8 & 0xFF00) - 256);
    }
    else
    {
        v13 = (v11 & 0xFF0000) - 0x10000;
        result = (unsigned __int8)*v8 - 1;
        *v8 = result | v13 | *v8 & 0xFF00;
    }

    return result;
}

int J3DAPI jonesConfig_AssignKeyAction(HWND hWnd, uint32_t* dwInitParam)
{
    int v2; // esi
    int v3; // edi
    int result; // eax
    const char* String; // eax
    const char* v6; // eax
    unsigned int controlId; // edx
    int v8; // [esp+10h] [ebp-620h]
    int v9; // [esp+14h] [ebp-61Ch] BYREF
    int v10; // [esp+18h] [ebp-618h] BYREF
    LPARAM v11[5]; // [esp+1Ch] [ebp-614h] BYREF
    char aStr[256]; // [esp+30h] [ebp-600h] BYREF
    char aControlStr[256]; // [esp+130h] [ebp-500h] BYREF
    char v14[512]; // [esp+230h] [ebp-400h] BYREF
    char v15[512]; // [esp+430h] [ebp-200h] BYREF

    v8 = 1;
    GetWindowLongA(hWnd, GWL_HINSTANCE);
    memset(dwInitParam + 2, 0, 256u);
    dwInitParam[66] = 0;
    v2 = JonesDialog_ShowDialog((LPCSTR)117, hWnd, jonesConfig_AssignKeyDlgProc, (LPARAM)dwInitParam);
    if ( v2 == 2 )
    {
        return v2;
    }

    while ( 1 )
    {
        v3 = jonesConfig_sub_409F70(dwInitParam[1], dwInitParam[66], &v9, dwInitParam[67], &v10);
        if ( v9 == *dwInitParam )
        {
            break;
        }

        if ( v3 > -1 )
        {
            v11[3] = v9;
            v11[0] = (LPARAM)dwInitParam;
            v11[1] = v3;
            v11[2] = v10;
            v11[4] = (LPARAM)hWnd;
            v8 = jonesConfig_ShowReassignKeyMsgBox(hWnd, (LPARAM)v11);
        }

        if ( v2 != 1 || v3 <= -1 || v8 == 1 )
        {
            return v2;
        }

        memset(dwInitParam + 2, 0, 0x100u);
        dwInitParam[66] = 0;
        result = JonesDialog_ShowDialog((LPCSTR)117, hWnd, jonesConfig_AssignKeyDlgProc, (LPARAM)dwInitParam);
        v2 = result;
        if ( result == 2 )
        {
            return result;
        }
    }

    String = jonesString_GetString("JONES_STR_SAMEMAP");
    if ( String )
    {
        strcpy(v15, String);
    }
    else
    {
        memset(v15, 0, sizeof(v15));
    }

    v6 = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[*dwInitParam]);
    if ( v6 )
    {
        strcpy(v14, v6);
    }
    else
    {
        memset(v14, 0, sizeof(v14));
    }

    if ( !v15[0] || !v14[0] )
    {
        return 2;
    }

    controlId = dwInitParam[66];
    memset(aStr, 0, sizeof(aStr));
    memset(aControlStr, 0, sizeof(aControlStr));
    jonesConfig_ControlToString(controlId, aControlStr);
    sprintf(aStr, "\"%s\" %s %s.", aControlStr, v15, v14);
    jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", aStr, 145);
    return 2;
}

int J3DAPI jonesConfig_sub_409F70(int a1, int a2, int* a3, int a4, int* a5)
{
    DWORD* i; // ebp
    int v6; // ebx
    unsigned int v7; // esi
    int offset; // edi
    unsigned int* v9; // ecx
    unsigned int v10; // eax
    unsigned int v11; // eax
    int idx; // [esp+10h] [ebp-8h]
    int function; // [esp+14h] [ebp-4h]

    idx = -1;
    function = 0;
    for ( i = (DWORD*)(a1 + 4); ; i += 9 )
    {
        v6 = *i;
        v7 = 1;
        offset = 0;
        if ( (unsigned __int8)*i )
        {
            break;
        }

    LABEL_17:
        if ( !BYTE1(v6) && a4 == 1005 || (v6 & 0xFF0000) == 0 && a4 == 1006 )
        {
            ++idx;
        }

        if ( ++function >= 37 )
        {
            return -1;
        }
    }

    v9 = i + 1;
    while ( 1 )
    {
        if ( a4 == 1006 && ((v10 = *v9, *v9 >= 0x100) && v10 <= 0x27F || v10 >= 0x8000 && v10 <= 0x8007)
            || a4 == 1005 && ((v11 = *v9, *v9 < 0x100) || v11 > 0x27F) && (v11 < 0x8000 || v11 > 0x8007) )
        {
            ++idx;
        }

        if ( a2 == *v9 )
        {
            break;
        }

        ++offset;
        ++v7;
        ++v9;
        if ( v7 > (unsigned __int8)*i )
        {
            goto LABEL_17;
        }
    }

    *a3 = function;
    *a5 = offset;
    STDLOG_STATUS("index: %i function: %i offset: %i\n", idx, function, offset);
    return idx;
}

INT_PTR __stdcall jonesConfig_AssignKeyDlgProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int v5; // esi
    LONG pData; // eax

    if ( msg <= WM_INITDIALOG )
    {
        if ( msg == WM_INITDIALOG )
        {
            jonesConfig_hFontAssignKeyDlg = jonesConfig_InitDialog(hWnd, 0, 117);
            v5 = jonesConfig_sub_40A1A0(hWnd, wparam, (DWORD*)lparam);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return v5;
        }

        if ( msg != WM_DESTROY )
        {
            return 0;
        }

        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontAssignKeyDlg);
        return 1;
    }

    if ( msg == WM_COMMAND )
    {
        jonesConfig_AssignKeyDlg_HandleWM_COMMAND(hWnd, (unsigned __int16)wparam);
        return 0;
    }
    else
    {
        if ( msg != WM_TIMER )
        {
            return 0;
        }

        pData = GetWindowLongA(hWnd, DWL_USER);
        if ( !pData || *(DWORD*)(pData + 272) )
        {
            return 1;
        }

        jonesConfig_AssignControlKey(hWnd);
        return 0;
    }
}

int J3DAPI jonesConfig_sub_40A1A0(HWND hDlg, int a2, uint32_t* dwNewLong)
{
    const char* String; // eax
    HWND DlgItem; // eax
    const char* v5; // eax
    HWND v6; // eax
    const CHAR* v8; // [esp-4h] [ebp-14h]
    const CHAR* v9; // [esp-4h] [ebp-14h]

    if ( dwNewLong[67] == 1006 )
    {
        String = jonesString_GetString("JONES_STR_NEXTBUTTON");
        if ( String )
        {
            v8 = String;
            DlgItem = GetDlgItem(hDlg, 1054);
            SetWindowTextA(DlgItem, v8);
        }
    }

    v5 = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[*dwNewLong]);
    if ( v5 )
    {
        v9 = v5;
        v6 = GetDlgItem(hDlg, 1055);
        SetWindowTextA(v6, v9);
    }

    SetTimer(hDlg, 1u, 0x64u, 0);
    SetWindowLongA(hDlg, 8, (LONG)dwNewLong);
    return 1;
}

void J3DAPI jonesConfig_AssignControlKey(HWND hWnd)
{
    int pSomeControleStruct; // esi
    int bJoystickControl; // ebx
    unsigned int controlId; // ebx
    int v4; // eax
    const char* String; // eax
    void* v6; // edi
    const char* v7; // eax
    const char* v8; // eax
    int numKeyPressed; // [esp+10h] [ebp-104h] BYREF
    char Dest[256]; // [esp+14h] [ebp-100h] BYREF

    pSomeControleStruct = GetWindowLongA(hWnd, DWL_USER);// TODO: Reconstruct struct
    bJoystickControl = wuRegistry_GetIntEx("Joystick Control", 0);

    jonesConfig_bControlsActive = stdControl_ControlsActive();
    stdControl_SetActivation(1);
    stdControl_ReadControls();

    if ( bJoystickControl
        && *(DWORD*)(pSomeControleStruct + 268) == 1006
        && jonesConfig_sub_40A500(pSomeControleStruct) )
    {
        stdControl_SetActivation(jonesConfig_bControlsActive);

    LABEL_29:
        KillTimer(hWnd, 1u);
        EndDialog(hWnd, 1);
        return;
    }

    controlId = 0;
    while ( !stdControl_ReadKey(controlId, &numKeyPressed) )
    {
        if ( ++controlId >= 644 )
        {
            return;
        }
    }

    v4 = *(DWORD*)(pSomeControleStruct + 268);
    if ( v4 == 1005 && controlId >= 256 && controlId <= 639 )
    {
        String = jonesString_GetString("JONES_STR_KEYONLY");
        goto LABEL_18;
    }

    if ( v4 == 1006 && (controlId < 256 || controlId > 639) )
    {
        String = jonesString_GetString("JONES_STR_BUTTONONLY");

    LABEL_18:
        if ( !String )
        {
            return;
        }

        *(DWORD*)(pSomeControleStruct + 272) = 1;
        jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", String, 145);
        *(DWORD*)(pSomeControleStruct + 272) = 0;
        InvalidateRect(hWnd, 0, 1);
        return;
    }

    v6 = (void*)(pSomeControleStruct + 8);
    jonesConfig_ControlToString(controlId, (char*)(pSomeControleStruct + 8));
    *(DWORD*)(pSomeControleStruct + 264) = controlId;
    switch ( controlId )
    {
        case DIK_ESCAPE:
        case DIK_MINUS:
        case DIK_EQUALS:
        case DIK_F4:
            v7 = jonesString_GetString("JONES_STR_NO_MAP");
            if ( !v7 )
            {
                goto LABEL_27;
            }

            sprintf(Dest, v7, pSomeControleStruct + 8);
            *(DWORD*)(pSomeControleStruct + 272) = 1;
            jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", Dest, 145);
            *(DWORD*)(pSomeControleStruct + 272) = 0;
            memset(v6, 0, 256u);
            break;

        case DIK_1:
        case DIK_2:
        case DIK_3:
        case DIK_4:
        case DIK_5:
        case DIK_6:
        case DIK_7:
        case DIK_8:
        case DIK_9:
        case DIK_0:
            if ( *(int*)pSomeControleStruct >= 16 && *(int*)pSomeControleStruct <= 27 )
            {
                goto LABEL_28;
            }

            v8 = jonesString_GetString("JONES_STR_NO_KEYMAP_NUM");
            if ( v8 )
            {
                sprintf(Dest, v8, pSomeControleStruct + 8);
                *(DWORD*)(pSomeControleStruct + 272) = 1;
                jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_CTRL_OPTS", Dest, 145);
                *(DWORD*)(pSomeControleStruct + 272) = 0;
                InvalidateRect(hWnd, 0, 1);
            }

        LABEL_27:
            memset(v6, 0, 0x100u);
            break;

        default:
        LABEL_28:
            stdControl_SetActivation(jonesConfig_bControlsActive);
            goto LABEL_29;
    }
}

int J3DAPI jonesConfig_sub_40A500(int a1)
{
    int NumJoysticks; // eax
    int v2; // ebp
    int i; // edi
    int v5; // [esp+10h] [ebp-Ch]
    char v6[4]; // [esp+14h] [ebp-8h] BYREF
    int v7; // [esp+18h] [ebp-4h]

    NumJoysticks = stdControl_GetNumJoysticks();
    v2 = 0;
    v7 = NumJoysticks;
    if ( !NumJoysticks )
    {
        return 0;
    }

    v5 = 0;
    if ( NumJoysticks <= 0 )
    {
        return 0;
    }

    while ( 2 )
    {
        for ( i = 0; i <= 5; ++i )
        {
            if ( stdControl_ReadAxisAsKey((i + v2) | 0x80000000, (int*)v6) )
            {
                if ( i )
                {
                    if ( i == 1 )
                    {
                        *(DWORD*)(a1 + 264) = 32770;
                    }

                    else if ( i == 5 )
                    {
                        *(DWORD*)(a1 + 264) = 32773;
                    }
                }
                else
                {
                    *(DWORD*)(a1 + 264) = 32769;
                }

                if ( *(DWORD*)(a1 + 264) )
                {
                    goto LABEL_24;
                }
            }

            else if ( stdControl_ReadAxisAsKey((i + v2) | 0xC0000000, (int*)v6) )
            {
                if ( i )
                {
                    if ( i == 1 )
                    {
                        *(DWORD*)(a1 + 264) = 0x8000;
                    }

                    else if ( i == 5 )
                    {
                        *(DWORD*)(a1 + 264) = 32772;
                    }
                }
                else
                {
                    *(DWORD*)(a1 + 264) = 32771;
                }

                if ( *(DWORD*)(a1 + 264) )
                {
                LABEL_24:
                    jonesConfig_ControlToString(*(DWORD*)(a1 + 264), (char*)(a1 + 8));
                    return 1;
                }
            }
        }

        v2 += 6;
        if ( ++v5 < v7 )
        {
            continue;
        }

        return 0;
    }
}

void J3DAPI jonesConfig_AssignKeyDlg_HandleWM_COMMAND(HWND hWnd, int a2)
{
    if ( a2 == 2 )
    {
        KillTimer(hWnd, 1u);
        EndDialog(hWnd, 2);
    }
}

int J3DAPI jonesConfig_ShowReassignKeyMsgBox(HWND hWnd, LPARAM dwInitParam)
{
    GetWindowLongA(hWnd, GWL_HINSTANCE);        // ??
    return JonesDialog_ShowDialog((LPCSTR)120, hWnd, jonesConfig_ReassignKeyDialogProc, dwInitParam);
}

INT_PTR __stdcall jonesConfig_ReassignKeyDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int v5; // edi

    if ( uMsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontReassignKeyDlg);
        return 1;
    }

    else if ( uMsg == WM_INITDIALOG )
    {
        jonesConfig_hFontReassignKeyDlg = jonesConfig_InitDialog(hWnd, 0, 120);
        v5 = jonesConfig_SetReassignKeyDialogText(hWnd, wParam, (void*)lParam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return v5;
    }
    else
    {
        if ( uMsg == WM_COMMAND )
        {
            jonesConfig_sub_40AA10(hWnd, (unsigned __int16)wParam);
        }

        return 0;
    }
}

int J3DAPI jonesConfig_SetReassignKeyDialogText(HWND hDlg, int a2, void* dwNewLong)
{
    DWORD* v3; // ebx
    const char* pTitle; // esi
    HWND DlgItem; // edi
    const char* pMapFromStr; // eax
    const char* pToControlName; // eax
    HWND hwndControl; // esi
    const char* v9; // eax
    const char* v10; // eax
    HWND v11; // esi
    CHAR aBuffer[256]; // [esp+10h] [ebp-700h] BYREF
    char aControlText[256]; // [esp+110h] [ebp-600h] BYREF
    char aCaptionFormat[512]; // [esp+210h] [ebp-500h] BYREF
    char aControlName[512]; // [esp+410h] [ebp-300h] BYREF
    CHAR String[256]; // [esp+610h] [ebp-100h] BYREF

    v3 = *(DWORD**)dwNewLong;
    memset(aControlText, 0, sizeof(aControlText));
    memset(aBuffer, 0, sizeof(aBuffer));
    jonesConfig_ControlToString(v3[66], aBuffer);

    sprintf(aControlText, "\"%s\" ", aBuffer);
    pTitle = jonesString_GetString("JONES_STR_NEWMAP");
    if ( pTitle )
    {
        DlgItem = GetDlgItem(hDlg, 1066);
        sprintf(String, pTitle, aControlText);
        SetWindowTextA(DlgItem, String);
    }

    memset(aControlText, 0, sizeof(aControlText));

    pMapFromStr = jonesString_GetString("JONES_STR_FROM");
    if ( pMapFromStr )
    {
        strcpy(aCaptionFormat, pMapFromStr);
    }
    else
    {
        memset(aCaptionFormat, 0, sizeof(aCaptionFormat));
    }

    pToControlName = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[*((DWORD*)dwNewLong + 3)]);
    if ( pToControlName )
    {
        strcpy(aControlName, pToControlName);
    }
    else
    {
        memset(aControlName, 0, sizeof(aControlName));
    }

    if ( aCaptionFormat[0] && aControlName[0] )
    {
        hwndControl = GetDlgItem(hDlg, 1073);
        sprintf(aControlText, aCaptionFormat, aControlName);
        SetWindowTextA(hwndControl, aControlText);
    }

    memset(aBuffer, 0, sizeof(aBuffer));
    v9 = jonesString_GetString("JONES_STR_TO");
    if ( v9 )
    {
        strcpy(aCaptionFormat, v9);
    }
    else
    {
        memset(aCaptionFormat, 0, sizeof(aCaptionFormat));
    }

    v10 = jonesString_GetString(jonesConfig_aJonesCapControlActionNames[*v3]);
    if ( v10 )
    {
        strcpy(aControlName, v10);
    }
    else
    {
        memset(aControlName, 0, sizeof(aControlName));
    }

    if ( aCaptionFormat[0] && aControlName[0] )
    {
        v11 = GetDlgItem(hDlg, 1072);
        sprintf(aBuffer, aCaptionFormat, aControlName);
        SetWindowTextA(v11, aBuffer);
    }

    SetWindowLongA(hDlg, 8, (LONG)dwNewLong);
    return 1;
}

int J3DAPI jonesConfig_sub_40AA10(HWND hWnd, int nResult)
{
    LONG WindowLongA; // edi
    int result; // eax
    int v4; // esi
    HWND DlgItem; // ebp
    LPARAM v6; // eax
    int v7; // edx
    LPARAM v8; // ecx
    int v9; // eax
    int i; // ecx
    int v11; // eax
    int v12; // eax
    int v13; // edi
    int* v14; // ecx
    int v15; // edx
    int v16; // eax
    WPARAM v17; // [esp-8h] [ebp-68h]
    LPARAM lParam[10]; // [esp+10h] [ebp-50h] BYREF
    LPARAM v19[10]; // [esp+38h] [ebp-28h] BYREF

    WindowLongA = GetWindowLongA(hWnd, 8);
    result = *(DWORD*)WindowLongA;
    v4 = *(DWORD*)(*(DWORD*)WindowLongA + 4);
    if ( nResult == 1 )
    {
        DlgItem = GetDlgItem(*(HWND*)(WindowLongA + 16), *(DWORD*)(result + 268));
        v6 = *(DWORD*)(WindowLongA + 12);
        if ( *(DWORD*)(*(DWORD*)WindowLongA + 268) == 1005 )
        {
            v7 = *(unsigned __int8*)(v4 + 36 * v6 + 5);
        }
        else
        {
            v7 = *(unsigned __int8*)(v4 + 36 * v6 + 6);
        }

        if ( v7 <= 1 )
        {
            if ( v7 == 1 )
            {
                v8 = *(DWORD*)(WindowLongA + 4);
                lParam[0] = 4;
                lParam[1] = v8;
                lParam[2] = 0;
                lParam[8] = v6;
                SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
                v17 = *(DWORD*)(WindowLongA + 4);
                v19[2] = 1;
                v19[5] = (LPARAM)std_g_aEmptyString;
                SendMessageA(DlgItem, 0x102Eu, v17, (LPARAM)v19);
            }
        }
        else
        {
            SendMessageA(DlgItem, 0x1008u, *(DWORD*)(WindowLongA + 4), 0);
        }

        v9 = *(DWORD*)(WindowLongA + 12);
        for ( i = *(DWORD*)(WindowLongA + 8) + 1;
            i < (unsigned __int8)*(DWORD*)(v4 + 36 * v9 + 4);
            v9 = *(DWORD*)(WindowLongA + 12) )
        {
            v11 = i + 8 * v9 + v9;
            ++i;
            *(DWORD*)(v4 + 4 * v11 + 4) = *(DWORD*)(v4 + 4 * v11 + 8);
        }

        v12 = *(DWORD*)WindowLongA;
        v13 = *(DWORD*)(WindowLongA + 12);
        v14 = (int*)(v4 + 36 * v13 + 4);
        if ( *(DWORD*)(v12 + 268) == 1005 )
        {
            v15 = ((unsigned __int8)*(DWORD*)(v4 + 36 * v13 + 4) - 1) | ((*(DWORD*)(v4 + 36 * v13 + 4) & 0xFF00)
                - 256);
            v16 = *(DWORD*)(v4 + 36 * v13 + 4) & 0xFF0000;
        }
        else
        {
            v15 = ((*v14 & 0xFF0000) - 0x10000) | *v14 & 0xFF00;
            v16 = (unsigned __int8)*v14 - 1;
        }

        *v14 = v16 | v15;
        return EndDialog(hWnd, nResult);
    }

    if ( nResult == 2 )
    {
        return EndDialog(hWnd, nResult);
    }

    return result;
}

int J3DAPI jonesConfig_ShowDisplaySettingsDialog(HWND hWnd, StdDisplayEnvironment* pDisplayEnv, JonesDisplaySettings* pDSettings)
{
    int Int; // eax
    int windowMode; // edx
    int v6; // ebp
    int displayDeviceNum; // ecx
    int height; // eax
    int videoModeNum; // edx
    rdGeometryMode geoMode; // eax
    Std3DMipmapFilterType filter; // ecx
    int width; // edx
    int bBuffering; // ecx
    int bFog; // edx
    rdLightMode lightMode; // ecx
    int bClearBackBuffer; // edx
    int v17; // edi
    int v18; // eax
    int result; // eax
    int v20; // eax
    int v21; // ecx
    int v22; // edx
    int v23; // eax
    Std3DMipmapFilterType v24; // ecx
    int v25; // edx
    int v26; // eax
    int v27; // ecx
    int v28; // edx
    rdGeometryMode v29; // eax
    rdLightMode v30; // ecx
    int v31; // edx
    LPARAM dwInitParam[2]; // [esp+10h] [ebp-50h] BYREF
    void* a1; // [esp+18h] [ebp-48h]
    void* pBytes; // [esp+1Ch] [ebp-44h]
    int v35; // [esp+20h] [ebp-40h]
    int v36; // [esp+24h] [ebp-3Ch]
    int v37; // [esp+28h] [ebp-38h]
    int bDualMonitor; // [esp+2Ch] [ebp-34h]
    int v39; // [esp+30h] [ebp-30h]
    int v40; // [esp+34h] [ebp-2Ch]
    int device3DNum; // [esp+38h] [ebp-28h]
    Std3DMipmapFilterType v42; // [esp+3Ch] [ebp-24h]
    int v43; // [esp+40h] [ebp-20h]
    int v44; // [esp+44h] [ebp-1Ch]
    int v45; // [esp+48h] [ebp-18h]
    int v46; // [esp+4Ch] [ebp-14h]
    rdGeometryMode v47; // [esp+50h] [ebp-10h]
    rdLightMode v48; // [esp+54h] [ebp-Ch]
    int v49; // [esp+58h] [ebp-8h]
    float hWnda; // [esp+64h] [ebp+4h]

    GetWindowLongA(hWnd, -6);
    dwInitParam[0] = (LPARAM)pDSettings;
    dwInitParam[1] = (LPARAM)pDisplayEnv;
    a1 = 0;
    pBytes = 0;
    v35 = 0;
    v36 = 0;
    hWnda = sithRender_g_fogDensity;
    Int = wuRegistry_GetInt("Performance Level", 4);
    windowMode = pDSettings->bWindowMode;
    v6 = Int;
    displayDeviceNum = pDSettings->displayDeviceNum;
    bDualMonitor = pDSettings->bDualMonitor;
    device3DNum = pDSettings->device3DNum;
    height = pDSettings->height;
    v37 = windowMode;
    videoModeNum = pDSettings->videoModeNum;
    v44 = height;
    geoMode = pDSettings->geoMode;
    v39 = displayDeviceNum;
    filter = pDSettings->filter;
    v40 = videoModeNum;
    width = pDSettings->width;
    v47 = geoMode;
    v42 = filter;
    bBuffering = pDSettings->bBuffering;
    v43 = width;
    bFog = pDSettings->bFog;
    v45 = bBuffering;
    lightMode = pDSettings->lightMode;
    v46 = bFog;
    bClearBackBuffer = pDSettings->bClearBackBuffer;
    v48 = lightMode;
    v49 = bClearBackBuffer;

    v17 = JonesDialog_ShowDialog((LPCSTR)114, hWnd, jonesConfig_DisplaySettingsDialogProc, (LPARAM)dwInitParam);
    if ( a1 )
    {
        stdMemory_Free(a1);
    }

    if ( pBytes )
    {
        stdMemory_Free(pBytes);
    }

    if ( v17 == 1 )
    {
        v18 = wuRegistry_GetIntEx("Mouse Control", 0);
        jonesConfig_EnableMouseControl(v18);
        return 1;
    }
    else
    {
        sithRender_g_fogDensity = hWnda;
        wuRegistry_SaveInt("Performance Level", v6);
        v20 = bDualMonitor;
        v21 = v39;
        pDSettings->bWindowMode = v37;
        v22 = v40;
        pDSettings->bDualMonitor = v20;
        v23 = device3DNum;
        pDSettings->displayDeviceNum = v21;
        v24 = v42;
        pDSettings->videoModeNum = v22;
        v25 = v43;
        pDSettings->device3DNum = v23;
        v26 = v44;
        pDSettings->filter = v24;
        v27 = v45;
        pDSettings->width = v25;
        v28 = v46;
        pDSettings->height = v26;
        v29 = v47;
        pDSettings->bBuffering = v27;
        v30 = v48;
        pDSettings->bFog = v28;
        v31 = v49;
        pDSettings->geoMode = v29;
        result = v17;
        pDSettings->lightMode = v30;
        pDSettings->bClearBackBuffer = v31;
    }

    return result;
}

INT_PTR __stdcall jonesConfig_DisplaySettingsDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int v5; // esi
    LONG WindowLongA; // ebx
    HWND DlgItem; // eax
    LRESULT v8; // edi
    HWND v9; // eax

    if ( uMsg <= WM_INITDIALOG )
    {
        if ( uMsg == WM_INITDIALOG )
        {
            jonesConfig_hFontDisplaySettingsDlg = jonesConfig_InitDialog(hWnd, 0, 114);
            v5 = jonesConfig_sub_40AE90(hWnd, wParam, (int*)lParam);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return v5;
        }

        if ( uMsg != 2 )
        {
            return 0;
        }

        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontDisplaySettingsDlg);
        return 1;
    }

    if ( uMsg == WM_COMMAND )
    {
        jonesConfig_sub_40B5A0(hWnd, (unsigned __int16)wParam, lParam, HIWORD(wParam));
        return 0;
    }
    else
    {
        if ( uMsg != WM_HSCROLL )
        {
            return 0;
        }

        if ( !jonesConfig_dword_511954 )
        {
            return 1;
        }

        WindowLongA = GetWindowLongA(hWnd, 8);
        jonesConfig_HandleWM_HSCROLL(hWnd, (HWND)lParam, (unsigned __int16)wParam);
        DlgItem = GetDlgItem(hWnd, 1050);
        v8 = SendMessageA(DlgItem, 0x400u, 0, 0);
        v9 = GetDlgItem(hWnd, 1097);
        SetWindowTextA(v9, (LPCSTR)(*(DWORD*)(WindowLongA + 8) + 280 * v8));
        return 1;
    }
}

int J3DAPI jonesConfig_sub_40AE90(HWND hDlg, int a2, int* dwNewLong)
{
    int v3; // ebp
    int v4; // esi
    void* v5; // edi
    int v6; // edi
    const char* v7; // edx
    DWORD* v8; // eax
    int v9; // eax
    int v10; // ebp
    int v11; // eax
    const char* v12; // eax
    BYTE* v13; // eax
    int v14; // edi
    WPARAM v15; // esi
    DWORD* v16; // eax
    void* v17; // eax
    unsigned int v18; // esi
    HWND v19; // eax
    char* v20; // edi
    unsigned int v21; // edx
    char* v22; // edi
    char v23; // cl
    int v24; // edx
    unsigned int v25; // eax
    int v26; // ebp
    HWND v27; // edi
    HWND v28; // edi
    int v30; // [esp+10h] [ebp-284h]
    int v31; // [esp+10h] [ebp-284h]
    HWND hWnd; // [esp+14h] [ebp-280h]
    int hWnda; // [esp+14h] [ebp-280h]
    int lParam; // [esp+18h] [ebp-27Ch]
    HWND DlgItem; // [esp+1Ch] [ebp-278h]
    int v36; // [esp+20h] [ebp-274h]
    int v37; // [esp+24h] [ebp-270h]
    int v38; // [esp+28h] [ebp-26Ch]
    int v39; // [esp+2Ch] [ebp-268h]
    int v40; // [esp+30h] [ebp-264h]
    unsigned int v41; // [esp+30h] [ebp-264h]
    int v42; // [esp+34h] [ebp-260h]
    int v43; // [esp+38h] [ebp-25Ch]
    int v44; // [esp+3Ch] [ebp-258h]
    WPARAM v45; // [esp+40h] [ebp-254h]
    int v46[20]; // [esp+44h] [ebp-250h] BYREF
    char Dest[256]; // [esp+94h] [ebp-200h] BYREF
    CHAR String[256]; // [esp+194h] [ebp-100h] BYREF

    v3 = *dwNewLong;
    v4 = dwNewLong[1];
    v42 = *dwNewLong;
    v43 = v4;
    lParam = -1;
    hWnd = GetDlgItem(hDlg, 1);
    DlgItem = GetDlgItem(hDlg, 1094);
    SendMessageA(DlgItem, 0x14Bu, 0, 0);
    if ( dwNewLong[2] )
    {
        stdMemory_Free((void*)dwNewLong[2]);
        dwNewLong[2] = 0;
        dwNewLong[5] = 0;
    }

    v5 = STDMALLOC(280 * *(DWORD*)(688 * *(DWORD*)(v3 + 8) + *(DWORD*)(v4 + 4) + 672));
    dwNewLong[2] = (int)v5;
    if ( !v5 )
    {
        return 0;
    }

    memset(v5, 0, 280 * *(DWORD*)(688 * *(DWORD*)(v3 + 8) + *(DWORD*)(v4 + 4) + 672));
    if ( dwNewLong[3] )
    {
        stdMemory_Free((void*)dwNewLong[3]);
        dwNewLong[3] = 0;
        dwNewLong[4] = 0;
    }

    v6 = *(DWORD*)(v4 + 4) + 688 * *(DWORD*)(v3 + 8);
    v37 = v6;
    if ( *(DWORD*)(v6 + 256) )
    {
        EnableWindow(hWnd, 1);
        EnableWindow(DlgItem, 1);
    }
    else
    {
        EnableWindow(hWnd, 0);
        EnableWindow(DlgItem, 0);
    }

    memcpy(v46, (const void*)(*(DWORD*)(v6 + 676) + 80 * *(DWORD*)(v3 + 12)), sizeof(v46));
    hWnda = 0;
    v30 = 0;
    if ( *(DWORD*)(688 * *(DWORD*)(v3 + 8) + *(DWORD*)(v4 + 4) + 672) )
    {
        v36 = 0;
        while ( 1 )
        {
            v7 = jonesString_GetString("JONES_STR_BYPIXELS");
            memset(Dest, 0, sizeof(Dest));
            if ( v7 )
            {
                sprintf(
                    Dest,
                    v7,
                    *(DWORD*)(*(DWORD*)(v37 + 676) + v36 + 4),
                    *(DWORD*)(*(DWORD*)(v37 + 676) + v36 + 8));
            }

            v8 = (DWORD*)(*(DWORD*)(v37 + 676) + v36);
            if ( *v8 != 1065353216 || v8[1] < 0x200u || v8[2] < 0x180u || !jonesConfig_sub_40BC40(v37, v3, v8[7]) )
            {
                goto LABEL_37;
            }

            v9 = jonesConfig_sub_40B530((const char*)dwNewLong[2], Dest, dwNewLong[5]);
            v10 = v9;
            if ( v9 != -1 )
            {
                break;
            }

        LABEL_36:
            v3 = v42;

        LABEL_37:
            v36 += 80;
            if ( (unsigned int)++v30 >= *(DWORD*)(688 * *(DWORD*)(v3 + 8) + *(DWORD*)(v43 + 4) + 672) )
            {
                goto LABEL_38;
            }
        }

        if ( v9 == dwNewLong[5] )
        {
            strcpy((char*)(dwNewLong[2] + 280 * v9), Dest);
            ++dwNewLong[5];
        }

        v11 = *(DWORD*)(*(DWORD*)(v37 + 676) + v36 + 28);
        switch ( v11 )
        {
            case 16:
                v38 = 2;
                v39 = 4;
                v12 = jonesString_GetString("JONES_STR_16BBP");
                if ( !v12 )
                {
                    goto LABEL_29;
                }

                break;

            case 24:
                v38 = 3;
                v39 = 8;
                v12 = jonesString_GetString("JONES_STR_24BBP");
                if ( !v12 )
                {
                    goto LABEL_29;
                }

                break;

            case 32:
                v38 = 4;
                v39 = 16;
                v12 = jonesString_GetString("JONES_STR_32BBP");
                if ( !v12 )
                {
                    goto LABEL_29;
                }

                break;

            default:
                goto LABEL_29;
        }

        sprintf(Dest, v12);

    LABEL_29:
        v13 = (BYTE*)(dwNewLong[2] + 280 * v10 + 256);
        *v13 |= v39;
        *(DWORD*)(dwNewLong[2] + 4 * (v38 + 70 * v10) + 260) = v30;
        if ( SendMessageA(DlgItem, 0x14Cu, 0, (LPARAM)Dest) == -1 )
        {
            v14 = v38 | (v39 << 16);
            v44 = v14;
            v15 = SendMessageA(DlgItem, 0x143u, 0, (LPARAM)Dest);
            v45 = v15;
            SendMessageA(DlgItem, 0x151u, v15, v14);
        }
        else
        {
            v15 = v45;
            v14 = v44;
        }

        v16 = (DWORD*)(*(DWORD*)(v37 + 676) + v36);
        if ( v16[1] == v46[1] && v16[2] == v46[2] && v16[7] == v46[7] )
        {
            lParam = v10;
            v40 = v14;
            SendMessageA(DlgItem, 0x14Eu, v15, 0);
            hWnda = 1;
        }

        goto LABEL_36;
    }

LABEL_38:
    v17 = STDMALLOC(4 * dwNewLong[5]);
    dwNewLong[3] = (int)v17;
    if ( !v17 )
    {
        return 0;
    }

    if ( hWnda )
    {
        v18 = v40;
    }
    else
    {
        lParam = 0;
        v18 = *(unsigned __int8*)(dwNewLong[2] + 256) << 16;
    }

    v19 = GetDlgItem(hDlg, 1097);
    GetWindowTextA(v19, String, 256);
    v20 = (char*)dwNewLong[3];
    v21 = 4 * dwNewLong[5];
    memset(v20, 0, 4 * (v21 >> 2));
    v22 = &v20[4 * (v21 >> 2)];
    v23 = v21;
    v24 = 0;
    memset(v22, 0, v23 & 3);
    if ( dwNewLong[5] > 0 )
    {
        v31 = 0;
        v25 = HIWORD(v18);
        v41 = HIWORD(v18);
        do
        {
            v26 = dwNewLong[2] + v31;
            if ( (*(BYTE*)(v26 + 256) & (unsigned __int8)v25) != 0 )
            {
                if ( strlen(String) && !strcmp(String, (const char*)(dwNewLong[2] + v31)) )
                {
                    lParam = dwNewLong[4];
                }

                else if ( lParam == v24 )
                {
                    lParam = dwNewLong[4];
                }

                *(DWORD*)(dwNewLong[3] + 4 * dwNewLong[4]++) = v26;
                v25 = (v25 & 0xFFFFFF00) | (v41 & 0xFF);
            }

            ++v24;
            v31 += 280;
        } while ( v24 < dwNewLong[5] );
    }

    v27 = GetDlgItem(hDlg, 1050);
    SendMessageA(v27, 0x406u, 1u, (unsigned __int16)(*((WORD*)dwNewLong + 8) - 1) << 16);
    SendMessageA(v27, 0x405u, 1u, lParam);
    SendMessageA(v27, 0x414u, 1u, 0);
    v28 = GetDlgItem(hDlg, 1097);
    SetWindowTextA(v28, *(LPCSTR*)(dwNewLong[3] + 4 * lParam));
    SendMessageA(v28, 0x415u, 0, 1);
    if ( !hWnda )
    {
        SendMessageA(DlgItem, 0x14Eu, 0, 0);
    }

    SetWindowLongA(hDlg, 8, (LONG)dwNewLong);
    return 1;
}

int J3DAPI jonesConfig_sub_40B530(const char* a1, const char* a2, int a3)
{
    int i; // ebp

    if ( !a2 )
    {
        return -1;
    }

    for ( i = 0; i < a3; a1 += 280 )
    {
        if ( !strcmp(a1, a2) )
        {
            break;
        }

        ++i;
    }

    return i;
}

int J3DAPI jonesConfig_sub_40B5A0(HWND hWnd, int nResult, int a3, int a4)
{
    LONG WindowLongA; // ebp
    int result; // eax
    DWORD* v6; // esi
    int v7; // edi
    HWND v8; // eax
    WPARAM v9; // eax
    int v10; // ecx
    int v11; // edx
    HWND v12; // esi
    WPARAM v13; // edi
    const char* v14; // esi
    HWND v15; // ebx
    char* v16; // edi
    unsigned int v17; // edx
    char* v18; // edi
    char v19; // cl
    int v20; // edx
    int v21; // eax
    int v22; // esi
    HWND v23; // esi
    void(__stdcall * v24)(HWND, UINT, WPARAM, LPARAM); // ebx
    WPARAM v25; // eax
    unsigned int v26; // esi
    int v27; // eax
    int v28; // edx
    unsigned int v29; // eax
    int v30; // esi
    float v31; // [esp+0h] [ebp-128h]
    LPARAM lParamb; // [esp+14h] [ebp-114h]
    LRESULT lParam; // [esp+14h] [ebp-114h]
    LPARAM lParama; // [esp+14h] [ebp-114h]
    HWND DlgItem; // [esp+18h] [ebp-110h]
    HWND v36; // [esp+18h] [ebp-110h]
    HWND v37; // [esp+18h] [ebp-110h]
    HWND v38; // [esp+1Ch] [ebp-10Ch]
    HWND v39; // [esp+1Ch] [ebp-10Ch]
    HWND v40; // [esp+20h] [ebp-108h]
    HWND v41; // [esp+20h] [ebp-108h]
    LPARAM v42; // [esp+24h] [ebp-104h]
    char Dest[256]; // [esp+28h] [ebp-100h] BYREF

    WindowLongA = GetWindowLongA(hWnd, 8);
    result = nResult;
    v6 = *(DWORD**)WindowLongA;
    v7 = *(DWORD*)(WindowLongA + 4);
    if ( nResult <= 1093 )
    {
        switch ( nResult )
        {
            case 1093:
                jonesConfig_ShowAdvanceDisplaySettings(hWnd, WindowLongA);
                return InvalidateRect(hWnd, 0, 1);

            case 1:
                DlgItem = GetDlgItem(hWnd, 1094);
                v8 = GetDlgItem(hWnd, 1050);
                lParamb = SendMessageA(v8, 0x400u, 0, 0);
                v9 = SendMessageA(DlgItem, 0x147u, 0, 0);
                v10 = *(DWORD*)(*(DWORD*)(*(DWORD*)(WindowLongA + 12) + 4 * lParamb)
                    + 4 * (unsigned __int16)SendMessageA(DlgItem, 0x150u, v9, 0)
                    + 260);
                v11 = v6[2];
                v6[3] = v10;
                v6[6] = *(DWORD*)(*(DWORD*)(*(DWORD*)(v7 + 4) + 688 * v11 + 676) + 80 * v10 + 4);
                v6[7] = *(DWORD*)(*(DWORD*)(*(DWORD*)(v7 + 4) + 688 * v11 + 676) + 80 * v6[3] + 8);
                wuRegistry_SaveStr("Display", (const char*)(*(DWORD*)(v7 + 4) + 688 * v11 + 128));
                wuRegistry_SaveStr(
                    "3D Device",
                    (const char*)(*(DWORD*)(688 * v6[2] + *(DWORD*)(v7 + 4) + 684) + 872 * v6[4] + 180));

                wuRegistry_SaveInt("Width", v6[6]);
                wuRegistry_SaveInt("Height", v6[7]);
                wuRegistry_SaveInt(
                    "BPP",
                    *(DWORD*)(*(DWORD*)(688 * v6[2] + *(DWORD*)(v7 + 4) + 676) + 80 * v6[3] + 28));

                v31 = sithRender_g_fogDensity * 0.0099999998;
                wuRegistry_SaveFloat("Fog Density", v31);

                wuRegistry_SaveIntEx("Buffering", v6[8]);
                wuRegistry_SaveIntEx("Fog", v6[9]);
                std3D_EnableFog(v6[9], sithRender_g_fogDensity);

                if ( sithWorld_g_pCurrentWorld )
                {
                    sithWorld_g_pCurrentWorld->state |= SITH_WORLD_STATE_UPDATE_FOG;
                }

                wuRegistry_SaveInt("Filter", v6[5]);
                result = 1;
                break;

            case 2:
                break;

            default:
                return result;
        }

        return EndDialog(hWnd, result);
    }

    result = nResult - 1094;
    if ( nResult == 1094 )
    {
        if ( a4 == 1 )
        {
            v23 = GetDlgItem(hWnd, 1094);
            v39 = GetDlgItem(hWnd, 1050);
            v24 = (void(__stdcall*)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
            v37 = GetDlgItem(hWnd, 1097);
            v25 = SendMessageA(v23, 0x147u, 0, 0);
            v26 = SendMessageA(v23, 0x150u, v25, 0);
            memset(Dest, 0, sizeof(Dest));
            memset(*(void**)(WindowLongA + 12), 0, 4 * *(DWORD*)(WindowLongA + 16));
            GetWindowTextA(v37, Dest, 256);
            v27 = *(DWORD*)(WindowLongA + 20);
            v28 = 0;
            *(DWORD*)(WindowLongA + 16) = 0;
            lParama = 0;
            if ( v27 > 0 )
            {
                v29 = HIWORD(v26);
                v41 = (HWND)HIWORD(v26);
                do
                {
                    v30 = *(DWORD*)(WindowLongA + 8) + v28;
                    if ( (*(BYTE*)(v30 + 256) & (unsigned __int8)v29) != 0 )
                    {
                        if ( !strcmp(Dest, (const char*)(*(DWORD*)(WindowLongA + 8) + v28)) )
                        {
                            v42 = *(DWORD*)(WindowLongA + 16);
                        }

                        *(DWORD*)(*(DWORD*)(WindowLongA + 12) + 4 * (*(DWORD*)(WindowLongA + 16))++) = v30;
                        v29 = (v29 & 0xFFFFFF00) | ((BYTE)v41 & 0xFF);
                    }

                    v28 += 280;
                    ++lParama;
                } while ( lParama < *(DWORD*)(WindowLongA + 20) );

                v24 = (void(__stdcall*)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
            }

            v24(v39, 0x406u, 1u, (unsigned __int16)(*(WORD*)(WindowLongA + 16) - 1) << 16);
            v24(v39, 0x405u, 1u, v42);          // TODO: check v42 is initialized
            v24(v39, 0x414u, 1u, 0);
            return SetWindowTextA(v37, *(LPCSTR*)(*(DWORD*)(WindowLongA + 12) + 4 * v42));
        }
    }
    else
    {
        result = nResult - 1099;
        if ( nResult == 1099 )
        {
            v12 = GetDlgItem(hWnd, 1094);
            v13 = 0;
            lParam = SendMessageA(v12, 0x146u, 0, 0);
            if ( lParam > 0 )
            {
                while ( (unsigned int)SendMessageA(v12, 0x150u, v13, 0) >> 16 != 4 )
                {
                    if ( (int)++v13 >= lParam )
                    {
                        goto LABEL_18;
                    }
                }

                SendMessageA(v12, 0x14Eu, v13, 0);
            }

        LABEL_18:
            CheckDlgButton(hWnd, 1095, 0);
            result = (int)jonesString_GetString("JONES_STR_BYPIXELS");
            v14 = (const char*)result;
            if ( result )
            {
                v40 = GetDlgItem(hWnd, 1050);
                v15 = GetDlgItem(hWnd, 1097);
                memset(Dest, 0, sizeof(Dest));
                v38 = v15;
                sprintf(Dest, v14, 640, 480);
                SetWindowTextA(v15, Dest);
                v16 = *(char**)(WindowLongA + 12);
                v17 = 4 * *(DWORD*)(WindowLongA + 16);
                memset(v16, 0, 4 * (v17 >> 2));
                v18 = &v16[4 * (v17 >> 2)];
                v19 = v17;
                v20 = 0;
                v36 = 0;
                memset(v18, 0, v19 & 3);
                v21 = *(DWORD*)(WindowLongA + 20);
                *(DWORD*)(WindowLongA + 16) = 0;
                if ( v21 > 0 )
                {
                    do
                    {
                        v22 = *(DWORD*)(WindowLongA + 8) + v20;
                        if ( (*(BYTE*)(v22 + 256) & 4) != 0 )
                        {
                            if ( !strcmp(Dest, (const char*)(*(DWORD*)(WindowLongA + 8) + v20)) )
                            {
                                lParam = *(DWORD*)(WindowLongA + 16);
                            }

                            *(DWORD*)(*(DWORD*)(WindowLongA + 12) + 4 * (*(DWORD*)(WindowLongA + 16))++) = v22;
                        }

                        v20 += 280;
                        v36 = (HWND)((char*)v36 + 1);
                    } while ( (int)v36 < *(DWORD*)(WindowLongA + 20) );

                    v15 = v38;
                }

                SendMessageA(v40, 0x406u, 1u, (unsigned __int16)(*(WORD*)(WindowLongA + 16) - 1) << 16);
                SendMessageA(v40, 0x405u, 1u, lParam);
                SendMessageA(v40, 0x414u, 1u, 0);
                return SetWindowTextA(v15, *(LPCSTR*)(*(DWORD*)(WindowLongA + 12) + 4 * lParam));
            }
        }
    }

    return result;
}

uint32_t J3DAPI jonesConfig_ShowAdvanceDisplaySettings(HWND hWnd, LPARAM dwInitParam)
{
    return JonesDialog_ShowDialog((LPCSTR)148, hWnd, jonesConfig_AdvanceDisplaySettingsDialog, dwInitParam);
}

INT_PTR __stdcall jonesConfig_AdvanceDisplaySettingsDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int v5; // edi

    if ( uMsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontAdvanceDisplaySettingsDialog);
        return 1;
    }

    else if ( uMsg == WM_INITDIALOG )
    {
        jonesConfig_hFontAdvanceDisplaySettingsDialog = jonesConfig_InitDialog(hWnd, 0, 148);
        v5 = jonesConfig_sub_40BCD0(hWnd, wParam, (DWORD*)lParam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return v5;
    }
    else
    {
        if ( uMsg == WM_COMMAND )
        {
            jonesConfig_sub_40C090(hWnd, (unsigned __int16)wParam, lParam, HIWORD(wParam));
        }

        return 0;
    }
}

int J3DAPI jonesConfig_sub_40BC40(int a1, int a2, int a3)
{
    if ( !a1 )
    {
        return 0;
    }

    switch ( a3 )
    {
        case 16:
            return *(DWORD*)(*(DWORD*)(a1 + 684) + 872 * *(DWORD*)(a2 + 16) + 472) & 0x400;

        case 24:
            return *(DWORD*)(*(DWORD*)(a1 + 684) + 872 * *(DWORD*)(a2 + 16) + 472) & 0x200;

        case 32:
            return *(DWORD*)(*(DWORD*)(a1 + 684) + 872 * *(DWORD*)(a2 + 16) + 472) & 0x100;
    }

    return 0;
}

int J3DAPI jonesConfig_sub_40BCD0(HWND hDlg, int a2, uint32_t* dwNewLong)
{
    unsigned int* v3; // edi
    unsigned int v4; // ebx
    HWND DlgItem; // ebp
    int v6; // eax
    WPARAM v7; // edi
    HWND v8; // ebp
    DWORD* v9; // edi
    DWORD* v10; // ebx
    WPARAM v11; // ebx
    int v12; // eax
    LPARAM v13; // edi
    HWND v14; // ebx
    void(__stdcall * v15)(HWND, int, int, int); // ebp
    int v16; // eax
    int v17; // eax
    int Int; // eax
    int v19; // eax
    HWND v20; // edi
    LPARAM lParam; // [esp+10h] [ebp-214h]
    LPARAM lParama; // [esp+10h] [ebp-214h]
    unsigned int* v24; // [esp+14h] [ebp-210h]
    int v25; // [esp+14h] [ebp-210h]
    DWORD* v26; // [esp+18h] [ebp-20Ch]
    DWORD* v27; // [esp+1Ch] [ebp-208h]
    int v28; // [esp+20h] [ebp-204h]
    char Dest[256]; // [esp+24h] [ebp-200h] BYREF
    CHAR String[256]; // [esp+124h] [ebp-100h] BYREF

    v3 = (unsigned int*)dwNewLong[1];
    v26 = (DWORD*)*dwNewLong;
    v24 = v3;
    v4 = 0;
    DlgItem = GetDlgItem(hDlg, 1084);
    SendMessageA(DlgItem, 0x14Bu, 0, 0);
    if ( *v3 )
    {
        lParam = 0;
        do
        {
            memset(Dest, 0, sizeof(Dest));
            v6 = lParam + v24[1];
            if ( *(DWORD*)(v6 + 256) == 1 )
            {
                sprintf(Dest, "%s", (const char*)(v6 + 128));
                v7 = SendMessageA(DlgItem, 0x143u, 0, (LPARAM)Dest);
                SendMessageA(DlgItem, 0x151u, v7, v4);
                if ( v4 == v26[2] )
                {
                    SendMessageA(DlgItem, 0x14Eu, v7, 0);
                }
            }

            ++v4;
            lParam += 688;
        } while ( v4 < *v24 );
    }

    v8 = GetDlgItem(hDlg, 1085);
    memset(String, 0, sizeof(String));
    GetWindowTextA(v8, String, 256);
    SendMessageA(v8, 0x14Bu, 0, 0);
    v9 = v26;
    v10 = (DWORD*)(688 * v26[2] + v24[1]);
    v27 = v10;
    if ( v10[64] )
    {
        EnableWindow(v8, 1);
        v28 = 0;
        lParama = 0;
        if ( v10[170] )
        {
            v25 = 0;
            while ( 1 )
            {
                memset(Dest, 0, sizeof(Dest));
                sprintf(Dest, "%s", (const char*)(v25 + v10[171] + 180));
                v11 = SendMessageA(v8, 0x143u, 0, (LPARAM)Dest);
                SendMessageA(v8, 0x151u, v11, lParama);
                v12 = strcmp(String, Dest);
                v13 = lParama;
                if ( !v12 || v26[4] == lParama )
                {
                    SendMessageA(v8, 0x14Eu, v11, 0);
                    v28 = 1;
                    v26[4] = lParama;
                }

                ++lParama;
                v25 += 872;
                if ( (unsigned int)(v13 + 1) >= v27[170] )
                {
                    break;
                }

                v10 = v27;
            }

            v9 = v26;
        }

        if ( !v28 )
        {
            SendMessageA(v8, 0x14Eu, 0, 0);
            v9[4] = 0;
        }
    }
    else
    {
        EnableWindow(v8, 0);
    }

    if ( v9[8] )
    {
        v14 = hDlg;
        v15 = (void(__stdcall*)(HWND, int, int, int))CheckRadioButton;
        CheckRadioButton(hDlg, 1091, 1092, 1092);
    }
    else
    {
        v15 = (void(__stdcall*)(HWND, int, int, int))CheckRadioButton;
        CheckRadioButton(hDlg, 1091, 1092, 1091);
        v14 = hDlg;
    }

    v16 = v9[5];
    if ( v16 )
    {
        v17 = v16 - 1;
        if ( v17 )
        {
            if ( v17 == 1 )
            {
                v15(v14, 1088, 1090, 1090);
            }
        }
        else
        {
            v15(v14, 1088, 1090, 1089);
        }
    }
    else
    {
        v15(v14, 1088, 1090, 1088);
    }

    Int = wuRegistry_GetInt("Performance Level", 4);
    if ( Int )
    {
        v19 = Int - 2;
        if ( v19 )
        {
            if ( v19 == 2 )
            {
                v15(v14, 1093, 1095, 1095);
            }
        }
        else
        {
            v15(v14, 1093, 1095, 1094);
        }
    }
    else
    {
        v15(v14, 1093, 1095, 1093);
    }

    CheckDlgButton(v14, 1051, v9[9]);
    v20 = GetDlgItem(v14, 1216);
    SendMessageA(v20, 0x406u, 1u, (LPARAM)rdCache_GetVertexPointer(4792));
    SendMessageA(v20, 0x414u, 5u, 0);
    SendMessageA(v20, 0x405u, 1u, (__int64)sithRender_g_fogDensity);
    SendMessageA(v20, 0x415u, 0, 5);
    SetWindowLongA(v14, 8, (LONG)dwNewLong);
    return 1;
}

int J3DAPI jonesConfig_sub_40C090(HWND hWnd, int nResult, int a3, int a4)
{
    int* WindowLongA; // ebx
    int result; // eax
    int v6; // edi
    HWND v7; // eax
    HWND v8; // eax
    double v9; // st7
    const char* String; // eax
    HWND v11; // ebp
    WPARAM v12; // eax
    HWND v13; // eax
    HWND DlgItem; // ebp
    WPARAM v15; // eax
    HWND nResulta; // [esp+18h] [ebp+8h]
    HWND nResultb; // [esp+18h] [ebp+8h]

    WindowLongA = (int*)GetWindowLongA(hWnd, 8);
    result = nResult;
    v6 = *WindowLongA;
    if ( nResult > 1084 )
    {
        result = nResult - 1085;
        switch ( nResult )
        {
            case 1085:
                if ( a4 == 1 )
                {
                    DlgItem = GetDlgItem(hWnd, 1084);
                    nResultb = GetParent(hWnd);
                    v15 = SendMessageA(DlgItem, 0x147u, 0, 0);
                    *(DWORD*)(v6 + 16) = SendMessageA(DlgItem, 0x150u, v15, 0);
                    jonesConfig_sub_40BCD0(hWnd, 0, WindowLongA);
                    result = jonesConfig_sub_40AE90(nResultb, 0, WindowLongA);
                }

                break;

            case 1088:
                result = CheckRadioButton(hWnd, 1088, 1090, 1088);
                jonesConfig_dword_511958 = 0;
                break;

            case 1089:
                result = CheckRadioButton(hWnd, 1088, 1090, 1089);
                jonesConfig_dword_511958 = 1;
                break;

            case 1090:
                result = CheckRadioButton(hWnd, 1088, 1090, 1090);
                jonesConfig_dword_511958 = 2;
                break;

            case 1091:
                result = CheckRadioButton(hWnd, 1091, 1092, 1091);
                *(DWORD*)(v6 + 32) = 0;
                break;

            case 1092:
                result = CheckRadioButton(hWnd, 1091, 1092, 1092);
                *(DWORD*)(v6 + 32) = 1;
                break;

            case 1093:
                result = CheckRadioButton(hWnd, 1093, 1095, 1093);
                jonesConfig_perfLevel = 0;
                break;

            case 1094:
                result = CheckRadioButton(hWnd, 1093, 1095, 1094);
                jonesConfig_perfLevel = 2;
                break;

            case 1095:
                result = CheckRadioButton(hWnd, 1093, 1095, 1095);
                jonesConfig_perfLevel = 4;
                break;

            case 1099:
                CheckDlgButton(hWnd, 1051, 1u);
                *(DWORD*)(v6 + 36) = 1;
                sithRender_g_fogDensity = 100.0;
                v13 = GetDlgItem(hWnd, 1216);
                SendMessageA(v13, 0x405u, 1u, 100);
                CheckRadioButton(hWnd, 1093, 1095, 1095);
                jonesConfig_perfLevel = 4;
                CheckRadioButton(hWnd, 1091, 1092, 1091);
                *(DWORD*)(v6 + 32) = 0;
                result = CheckRadioButton(hWnd, 1088, 1090, 1089);
                jonesConfig_dword_511958 = 1;
                break;

            default:
                return result;
        }
    }
    else
    {
        if ( nResult != 1084 )
        {
            if ( nResult == 1 )
            {
                v7 = GetDlgItem(hWnd, 1051);
                *(DWORD*)(v6 + 36) = SendMessageA(v7, BM_GETCHECK, 0, 0);
                v8 = GetDlgItem(hWnd, 1216);
                v9 = (double)SendMessageA(v8, WM_USER, 0, 0);
                sithRender_g_fogDensity = v9;
                *(float*)(v6 + 52) = v9 * 0.0099999998;

                wuRegistry_SaveInt("Performance Level", jonesConfig_perfLevel);
                jonesConfig_perfLevel = 4;
                if ( JonesMain_HasStarted() && jonesConfig_perfLevel != wuRegistry_GetInt("Performance Level", 4) )
                {
                    String = jonesString_GetString("JONES_STR_PERFORMANCE");
                    if ( String )
                    {
                        jonesConfig_ShowMessageDialog(hWnd, "JONES_STR_DPLY_OPTS", String, 136);
                        InvalidateRect(hWnd, 0, 1);
                    }
                }

                result = 1;
                *(DWORD*)(v6 + 20) = jonesConfig_dword_511958;
                jonesConfig_dword_511958 = 1;
            }

            else if ( nResult != 2 )
            {
                return result;
            }

            return EndDialog(hWnd, result);
        }

        if ( a4 == 1 )
        {
            v11 = GetDlgItem(hWnd, 1084);
            nResulta = GetParent(hWnd);
            v12 = SendMessageA(v11, CB_GETCURSEL, 0, 0);
            *(DWORD*)(v6 + 8) = SendMessageA(v11, CB_GETITEMDATA, v12, 0);
            jonesConfig_sub_40BCD0(hWnd, 0, WindowLongA);
            return jonesConfig_sub_40AE90(nResulta, 0, WindowLongA);
        }
    }

    return result;
}

int J3DAPI jonesConfig_ShowSoundSettingsDialog(HWND hWnd, float* dwInitParam)
{
    GetWindowLongA(hWnd, GWL_HINSTANCE);
    return JonesDialog_ShowDialog((LPCSTR)113, hWnd, jonesConfig_SoundSettingsDialogProc, (LPARAM)dwInitParam);
}

INT_PTR __stdcall jonesConfig_SoundSettingsDialogProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int v5; // ebp
    tSoundHandle hSndFile; // edi
    HWND hDlgItem; // eax
    LRESULT v8; // esi
    float volume; // [esp+0h] [ebp-1Ch]

    if ( msg <= WM_INITDIALOG )
    {
        if ( msg == WM_INITDIALOG )
        {
            jonesConfig_hFontSoundSettings = jonesConfig_InitDialog(hWnd, 0, 113);
            v5 = jonesConfig_sub_40C650(hWnd, wparam, lparam);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return v5;
        }

        if ( msg != 2 )
        {
            return 0;
        }

        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontSoundSettings);
        return 1;
    }

    if ( msg == WM_COMMAND )
    {
        jonesConfig_SoundSettings_HandleWM_COMMAND(hWnd, (unsigned __int16)wparam);
        return 0;
    }
    else
    {
        if ( msg != WM_HSCROLL )
        {
            return 0;
        }

        jonesConfig_HandleWM_HSCROLL(hWnd, (HWND)lparam, (unsigned __int16)wparam);
        if ( (WORD)wparam != 8 )
        {
            return 1;
        }

        hSndFile = Sound_GetSoundHandle(0x8039);
        if ( jonesConfig_hSndChannel && (Sound_GetChannelFlags(jonesConfig_hSndChannel) & SOUND_CHANNEL_PLAYING) != 0 )
        {
            sithSoundMixer_StopSound(jonesConfig_hSndChannel);
        }

        jonesConfig_hSndChannel = 0;
        if ( !hSndFile )
        {
            return 1;
        }

        hDlgItem = GetDlgItem(hWnd, 1050);
        v8 = SendMessageA(hDlgItem, 0x400u, 0, 0);
        if ( jonesConfig_dword_551E14 == v8 )
        {
            return 1;
        }

        volume = (double)v8 * 0.01;
        jonesConfig_hSndChannel = sithSoundMixer_PlaySound(hSndFile, volume, 0.0, (SoundPlayFlag)0);
        jonesConfig_dword_551E14 = v8;
        return 1;
    }
}

int J3DAPI jonesConfig_sub_40C650(HWND hDlg, int a2, LONG dwNewLong)
{
    HWND DlgItem; // edi
    HWND v4; // ebx
    void(__stdcall * v5)(HWND, int, UINT); // edi
    LONG v6; // ebx

    DlgItem = GetDlgItem(hDlg, 1050);
    SendMessageA(DlgItem, 0x406u, 1u, (LPARAM)rdCache_GetVertexPointer(4792)); // Created accessor function in rdCache.c
    SendMessageA(DlgItem, 0x414u, 0x11u, 0);
    SendMessageA(DlgItem, 0x405u, 1u, (__int64)(*(float*)dwNewLong * 100.0));
    SendMessageA(DlgItem, 0x415u, 0, 5);
    v4 = GetDlgItem(hDlg, 1118);
    if ( Sound_Has3DHW() )
    {
        v6 = dwNewLong;
        v5 = (void(__stdcall*)(HWND, int, UINT))CheckDlgButton;
        CheckDlgButton(hDlg, 1118, *(DWORD*)(dwNewLong + 4) != 0);
    }
    else
    {
        v5 = (void(__stdcall*)(HWND, int, UINT))CheckDlgButton;
        CheckDlgButton(hDlg, 1118, 0);
        EnableWindow(v4, 0);
        v6 = dwNewLong;
    }

    GetDlgItem(hDlg, 1051);
    v5(hDlg, 1051, *(DWORD*)(v6 + 8));
    SetWindowLongA(hDlg, 8, v6);
    return 1;
}

int J3DAPI jonesConfig_SoundSettings_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    LONG WindowLongA; // esi
    int result; // eax
    HWND DlgItem; // eax
    HWND v6; // eax
    HWND v7; // eax
    int v8; // eax
    float hWnda; // [esp+14h] [ebp+4h]

    WindowLongA = GetWindowLongA(hWnd, 8);
    if ( nResult == 1 )
    {
        DlgItem = GetDlgItem(hWnd, 1050);
        hWnda = (double)SendMessageA(DlgItem, 0x400u, 0, 0) * 0.01;
        *(float*)WindowLongA = hWnda;
        v6 = GetDlgItem(hWnd, 1118);
        *(DWORD*)(WindowLongA + 4) = SendMessageA(v6, 0xF2u, 0, 0);
        wuRegistry_SaveFloat("Sound Volume", hWnda);
        wuRegistry_SaveIntEx("Sound 3D", *(DWORD*)(WindowLongA + 4));
        v7 = GetDlgItem(hWnd, 1051);
        v8 = SendMessageA(v7, 0xF2u, 0, 0);
        *(DWORD*)(WindowLongA + 8) = v8;
        wuRegistry_SaveIntEx("ReverseSound", v8);
        return EndDialog(hWnd, nResult);
    }

    result = nResult - 2;
    if ( nResult == 2 )
    {
        return EndDialog(hWnd, nResult);
    }

    return result;
}

int J3DAPI jonesConfig_ShowGameOverDialog(HWND hWnd, char* pRestoreFilename, tSoundHandle hSndGameOVerMus, tSoundChannelHandle* pSndChnlMus)
{
    GameOverDialogData data; // [esp+0h] [ebp-10h] BYREF

    data.result = 0;
    data.pRestoreFilename = pRestoreFilename;
    data.sndChnlMusic = 0;
    data.hSndMusic = 0;
    data.sndChnlMusic = *pSndChnlMus;
    data.hSndMusic = hSndGameOVerMus;
    JonesDialog_ShowDialog((LPCSTR)150, hWnd, jonesConfig_GameOverDialogProc, (LPARAM)&data);
    return data.result;
}

INT_PTR __stdcall jonesConfig_GameOverDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int bSuccess; // edi

    if ( uMsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontGameOverDialog);
        return 1;
    }

    else if ( uMsg == WM_INITDIALOG )
    {
        jonesConfig_hFontGameOverDialog = jonesConfig_InitDialog(hWnd, 0, 150);
        bSuccess = jonesConfig_GameOverDialogInit(hWnd, wParam, (GameOverDialogData*)lParam);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
        return bSuccess;
    }
    else
    {
        if ( uMsg == WM_COMMAND )
        {
            jonesConfig_GameOverDialog_HandleWM_COMMAND(hWnd, wParam);
        }

        return 0;
    }
}

void J3DAPI jonesConfig_LoadGameGetLastSavedGamePath(char* pPath, unsigned int size)
{
    const char* pLastFilename; // eax MAPDST
    int filenameSize; // ecx
    const char* pCurText; // esi
    const char* pFilePrefix; // eax
    const char* pSaveGamesDir; // eax
    const char* lpszSaveGamesDir; // [esp-18h] [ebp-12Ch]
    const char* pNdsLevenFilename; // [esp-4h] [ebp-118h]
    char* pFilePart; // [esp+10h] [ebp-104h] BYREF
    char aPath[128]; // [esp+14h] [ebp-100h] BYREF
    char aLastFilePath[128]; // [esp+94h] [ebp-80h] BYREF

    pLastFilename = sithGamesave_GetLastFilename();
    if ( pLastFilename && strlen(pLastFilename) )
    {
        filenameSize = strlen(pLastFilename);
        pCurText = &pLastFilename[filenameSize - 1];
        if ( filenameSize >= 0 )
        {
            while ( *pCurText != '\\' )
            {
                --pCurText;
                if ( --filenameSize < 0 )
                {
                    goto LABEL_8;
                }
            }

            ++pCurText;
        }

    LABEL_8:
        if ( pCurText )
        {
            memset(aLastFilePath, 0, sizeof(aLastFilePath));
            memset(aPath, 0, sizeof(aPath));
            strncpy(aLastFilePath, pLastFilename, pCurText - pLastFilename);
            strncpy(aPath, pCurText, strlen(pCurText));
            SearchPathA(aLastFilePath, aPath, 0, 128u, pPath, &pFilePart);
        }
        else
        {
            lpszSaveGamesDir = sithGetSaveGamesDir();
            SearchPathA(lpszSaveGamesDir, pLastFilename, 0, 128u, pPath, &pFilePart);
        }
    }

    if ( !strlen(pPath) )
    {
        memset(aPath, 0, sizeof(aPath));
        memset(pPath, 0, size);
        if ( sithWorld_g_pCurrentWorld )
        {
            pNdsLevenFilename = sithGetCurrentWorldSaveName();
            pFilePrefix = sithGetAutoSaveFilePrefix();
            sprintf(aPath, "%s%s", pFilePrefix, pNdsLevenFilename);
            stdFnames_ChangeExt(aPath, "nds");
            pSaveGamesDir = sithGetSaveGamesDir();
            SearchPathA(pSaveGamesDir, aPath, 0, 128u, pPath, &pFilePart);
        }
    }
}

int J3DAPI jonesConfig_GameOverDialogInit(HWND hDlg, int a2, GameOverDialogData* pData)
{
    const char* pFilePrefix; // eax
    const char* aPath; // eax
    HWND hBtn; // eax
    tSoundHandle hSnd; // eax
    const char* pNdsFilename; // [esp-4h] [ebp-118h]
    LPSTR pFilePart; // [esp+10h] [ebp-104h] BYREF
    char aFilename[128]; // [esp+14h] [ebp-100h] BYREF
    CHAR aFilePath[128]; // [esp+94h] [ebp-80h] BYREF

    memset(aFilePath, 0, sizeof(aFilePath));
    memset(aFilename, 0, sizeof(aFilename));
    if ( sithWorld_g_pCurrentWorld )
    {
        pNdsFilename = sithGetCurrentWorldSaveName();
        pFilePrefix = sithGetAutoSaveFilePrefix();
        sprintf(aFilename, "%s%s", pFilePrefix, pNdsFilename);
        stdFnames_ChangeExt(aFilename, "nds");
        aPath = sithGetSaveGamesDir();
        SearchPathA(aPath, aFilename, 0, 128u, aFilePath, &pFilePart);
    }

    if ( !strlen(aFilePath) )
    {
        // Disable restart btn
        hBtn = GetDlgItem(hDlg, 1177);          // Restart
        EnableWindow(hBtn, 0);
    }

    hSnd = pData->hSndMusic;
    if ( hSnd )
    {
        pData->sndChnlMusic = sithSoundMixer_PlaySound(hSnd, 1.0, 0.0, (SoundPlayFlag)0);
    }

    strcpy(pData->pRestoreFilename, aFilePath);
    SetWindowLongA(hDlg, DWL_USER, (LONG)pData);
    return 1;
}

void J3DAPI jonesConfig_GameOverDialog_HandleWM_COMMAND(HWND hWnd, uint16_t wParam)
{
    GameOverDialogData* pData; // eax

    pData = (GameOverDialogData*)GetWindowLongA(hWnd, DWL_USER);
    switch ( wParam )
    {
        case 1177u:
            pData->result = 1177;               // restart
            EndDialog(hWnd, 1);
            break;

        case 1178u:
            pData->result = 1178;               // load game
            if ( jonesConfig_GetLoadGameFilePath(hWnd, pData->pRestoreFilename) == 1 )
            {
                InvalidateRect(hWnd, 0, 1);
                EndDialog(hWnd, 1);
            }

            break;

        case 1179u:
            pData->result = 1179;
            EndDialog(hWnd, 1);
            break;
    }
}

int J3DAPI jonesConfig_ShowStatisticsDialog(HWND hWnd, SithGameStatistics* pStatistics)
{
    int dwInitParam[3]; // [esp+0h] [ebp-20h] BYREF
    JonesDialogImageInfo imageInfo; // [esp+Ch] [ebp-14h] BYREF

    if ( !pStatistics )
    {
        return 2;
    }

    memset(&imageInfo, 0, sizeof(imageInfo));
    dwInitParam[1] = (int)pStatistics;
    dwInitParam[0] = (int)&imageInfo;
    return JonesDialog_ShowDialog((LPCSTR)164, hWnd, jonesConfig_StatisticsDialogProc, (LPARAM)dwInitParam);
}

INT_PTR __stdcall jonesConfig_StatisticsDialogProc(HWND hwnd, UINT uMsg, WPARAM wPAram, LPARAM lParam)
{
    INT_PTR result; // eax
    HWND textStatistict; // edi
    const char* pTitleText; // eax MAPDST
    int inited; // ebp
    void* pData_1; // eax
    HDC* v9; // esi
    HBRUSH SolidBrush; // eax
    int* pData; // edi
    HWND hScroll; // ebp
    int scrollPos; // ebx
    int levelNum; // ebp
    int MaxPos; // [esp+10h] [ebp-48h] BYREF
    int MinPos; // [esp+14h] [ebp-44h] BYREF
    struct tagRECT Rect; // [esp+18h] [ebp-40h] BYREF
    DRAWITEMSTRUCT drawitemData; // [esp+28h] [ebp-30h] BYREF
    const char* pSummeryText; // [esp+5Ch] [ebp+4h]
    HWND hTextStatTitle; // [esp+60h] [ebp+8h]
    WPARAM iqpoints; // [esp+64h] [ebp+Ch]

    if ( uMsg > WM_CLOSE )
    {
        switch ( uMsg )
        {
            case WM_DRAWITEM:
                pData_1 = (void*)GetWindowLongA(hwnd, DWL_USER);
                v9 = *(HDC**)pData_1;
                if ( !*(DWORD*)(*(DWORD*)pData_1 + 16) )
                {
                    v9[4] = (HDC)GetBkColor(*(HDC*)(lParam + 24));
                }

                GetClientRect(*(HWND*)(lParam + 20), &Rect);
                SolidBrush = CreateSolidBrush((COLORREF)v9[4]);
                FillRect(*(HDC*)(lParam + 24), &Rect, SolidBrush);
                SetStretchBltMode(*(HDC*)(lParam + 24), STRETCH_HALFTONE);
                jonesConfig_DrawImageOnDialogItem(
                    hwnd,
                    *v9,
                    *(HDC*)(lParam + 24),
                    wPAram,
                    jonesConfig_apDialogIcons[0],// iq.bmp
                    jonesConfig_apDialogIcons[1]);// iq_mask.bmp
                result = 1;
                break;

            case WM_INITDIALOG:
                textStatistict = GetDlgItem(hwnd, 1158);
                jonesConfig_dword_551E1C = jonesConfig_InitDialog(hwnd, 0, 164);
                pTitleText = jonesString_GetString(jonesConfig_JONES_STR_SUMMERY);// "JONES_STR_SUMMARY"
                if ( pTitleText )
                {
                    SetWindowTextA(textStatistict, pTitleText);
                }

                inited = jonesConfig_InitStatisticDialog(hwnd, wPAram, (int*)lParam);
                SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);// TODO: 2nd is HWND_TOPMOST
                result = inited;
                break;

            case WM_COMMAND:
                jonesConfig_StatisticProc_HandleWM_COMMAND(hwnd, wPAram);
                result = 0;
                break;

            case WM_HSCROLL:
                pData = (int*)GetWindowLongA(hwnd, DWL_USER);
                hScroll = GetDlgItem(hwnd, 1162);
                hTextStatTitle = GetDlgItem(hwnd, 1158);
                jonesConfig_sub_40D100((int)hwnd, (HWND)lParam, (unsigned __int16)wPAram, SHIWORD(wPAram));
                scrollPos = GetScrollPos(hScroll, 2);
                if ( scrollPos != pData[2] )
                {
                    GetScrollRange(hScroll, SB_CTL, &MinPos, &MaxPos);
                    if ( scrollPos == MaxPos )
                    {
                        pSummeryText = jonesString_GetString(jonesConfig_JONES_STR_SUMMERY);// "JONES_STR_SUMMARY"
                        levelNum = 17;
                        iqpoints = jonesInventory_GetTotalIQPoints();
                        pTitleText = pSummeryText;
                    }
                    else
                    {
                        if ( scrollPos == jonesConfig_curLevelNum && jonesConfig_curLevelNum > 0 )
                        {
                            pTitleText = jonesString_GetString(jonesConfig_aLevelNames[16]);
                        }
                        else
                        {
                            pTitleText = jonesString_GetString(jonesConfig_aLevelNames[scrollPos]);
                        }

                        levelNum = scrollPos;
                        iqpoints = *(DWORD*)(32 * scrollPos + pData[1] + 44);// pData[1] -> JonesGameStatistics*
                    }

                    if ( pTitleText )
                    {
                        SetWindowTextA(hTextStatTitle, pTitleText);
                    }

                    else if ( scrollPos == jonesConfig_curLevelNum && jonesConfig_curLevelNum > 0 )
                    {
                        SetWindowTextA(hTextStatTitle, jonesConfig_aLevelNames[16]);
                    }
                    else
                    {
                        SetWindowTextA(hTextStatTitle, jonesConfig_aLevelNames[levelNum]);
                    }

                    jonesConfig_SetStatisticsDialogForLevel(hwnd, levelNum, pData);
                    jonesConfig_DrawStatisticDialogIQPoints(hwnd, (JonesDialogImageInfo**)pData, 164, iqpoints);

                    drawitemData.CtlType = ODT_BUTTON;
                    drawitemData.CtlID = 1220;
                    drawitemData.itemID = 0;
                    drawitemData.itemAction = 1;
                    drawitemData.itemState = 0;
                    drawitemData.hwndItem = GetDlgItem(hwnd, 1220);
                    drawitemData.hDC = GetDC(drawitemData.hwndItem);

                    GetClientRect(drawitemData.hwndItem, &drawitemData.rcItem);

                    drawitemData.itemData = 0;

                    SendMessageA(hwnd, WM_DRAWITEM, 1220u, (LPARAM)&drawitemData);
                    ReleaseDC(drawitemData.hwndItem, drawitemData.hDC);
                    pData[2] = scrollPos;
                }

                result = 1;
                break;

            default:
                return 0;
        }
    }

    else if ( uMsg == WM_CLOSE )
    {
        EndDialog(hwnd, 2);
        return 0;
    }

    else if ( uMsg == WM_DESTROY )
    {
        jonesConfig_ResetDialogFont(hwnd, (HFONT)jonesConfig_dword_551E1C);
        return 1;
    }
    else
    {
        return 0;
    }

    return result;
}

int J3DAPI jonesConfig_sub_40D100(int a1, HWND hWnd, int a3, int a4)
{
    int result; // eax
    int v5; // [esp+0h] [ebp-44h]
    int v6; // [esp+4h] [ebp-40h]
    int v7; // [esp+8h] [ebp-3Ch]
    int v8; // [esp+Ch] [ebp-38h]
    LPARAM lParam[7]; // [esp+14h] [ebp-30h] BYREF
    int v10; // [esp+30h] [ebp-14h]
    LPARAM v11; // [esp+34h] [ebp-10h]
    int v12; // [esp+38h] [ebp-Ch]
    LPARAM v13; // [esp+3Ch] [ebp-8h]
    int nPos; // [esp+40h] [ebp-4h]

    nPos = -1;
    lParam[1] = 23;
    SendMessageA(hWnd, 0xEAu, 0, (LPARAM)lParam);
    v10 = lParam[2];
    v12 = lParam[3];
    v13 = lParam[5];
    v11 = lParam[4];
    result = a3;
    switch ( a3 )
    {
        case 0:
            if ( v10 <= v13 - 1 )
            {
                v8 = v13 - 1;
            }
            else
            {
                v8 = v10;
            }

            result = v8;
            nPos = v8;
            break;

        case 1:
            if ( v12 >= v13 + 1 )
            {
                result = v13 + 1;
                v7 = v13 + 1;
            }
            else
            {
                v7 = v12;
            }

            nPos = v7;
            break;

        case 2:
            if ( v10 <= v13 - v11 )
            {
                v6 = v13 - v11;
            }
            else
            {
                result = v10;
                v6 = v10;
            }

            nPos = v6;
            break;

        case 3:
            if ( v12 >= v11 + v13 )
            {
                v5 = v11 + v13;
            }
            else
            {
                v5 = v12;
            }

            result = v5;
            nPos = v5;
            break;

        case 4:
        case 5:
            nPos = a4;
            break;

        case 6:
            nPos = v10;
            break;

        case 7:
            nPos = v12;
            break;

        default:
            break;
    }

    if ( nPos >= 0 )
    {
        return SetScrollPos(hWnd, 2, nPos, 1);
    }

    return result;
}

//void J3DAPI jonesConfig_UpdateCurrentLevelNum()
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_UpdateCurrentLevelNum);
//}
//
//int J3DAPI jonesConfig_DrawImageOnDialogItem(HWND hDlg, HDC hdcWnd, HDC hdcCtrl, int nIDDlgItem, HBITMAP hImage, HBITMAP hMask)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_DrawImageOnDialogItem, hDlg, hdcWnd, hdcCtrl, nIDDlgItem, hImage, hMask);
//}

int J3DAPI jonesConfig_SetStatisticsDialogForLevel(HWND hDlg, int levelNum, int* a3)
{
    int v3; // esi
    int v4; // edx
    HWND hTextTimePassed; // eax
    HWND hTextLvlFinished; // eax
    HWND hTextTreasuresFound; // eax
    HWND hTextHintsSeen; // eax
    HWND hTextDifficultyDrop; // eax
    SithLevelStatistic* pLevelStatistics; // [esp+10h] [ebp-108h]
    SithGameStatistics* pStatistics; // [esp+14h] [ebp-104h]
    char aText[256]; // [esp+18h] [ebp-100h] BYREF

    pStatistics = (SithGameStatistics*)a3[1];
    pLevelStatistics = &pStatistics->aLevelStatistic[levelNum];
    v3 = pLevelStatistics->elapsedTime >> 8;
    v4 = pLevelStatistics->elapsedTime ^ (v3 << 8);
    memset(aText, 0, sizeof(aText));
    if ( v4 >= 10 )
    {
        sprintf(aText, "%i : %i ", v3, v4);
    }
    else
    {
        sprintf(aText, "%i : 0%i ", v3, v4);
    }

    hTextTimePassed = GetDlgItem(hDlg, 1153);
    SetWindowTextA(hTextTimePassed, aText);

    memset(aText, 0, sizeof(aText));
    sprintf(aText, "%i ", pStatistics->curLevelNum);
    hTextLvlFinished = GetDlgItem(hDlg, 1152);
    SetWindowTextA(hTextLvlFinished, aText);

    memset(aText, 0, sizeof(aText));
    sprintf(aText, "%i ", pStatistics->aLevelStatistic[levelNum].numFoundTreasures);
    hTextTreasuresFound = GetDlgItem(hDlg, 1154);
    SetWindowTextA(hTextTreasuresFound, aText);

    memset(aText, 0, sizeof(aText));
    sprintf(aText, "%i ", pStatistics->aLevelStatistic[levelNum].numSeenHints);
    hTextHintsSeen = GetDlgItem(hDlg, 1155);
    SetWindowTextA(hTextHintsSeen, aText);

    memset(aText, 0, sizeof(aText));
    sprintf(aText, "%i ", pStatistics->aLevelStatistic[levelNum].difficultyPenalty);
    hTextDifficultyDrop = GetDlgItem(hDlg, 1156);
    return SetWindowTextA(hTextDifficultyDrop, aText);
}

//void J3DAPI jonesConfig_DrawStatisticDialogIQPoints(HWND hwnd, JonesDialogImageInfo** ppImageInfo, int dlgID, int iqpoints)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_DrawStatisticDialogIQPoints, hwnd, ppImageInfo, dlgID, iqpoints);
//}

int J3DAPI jonesConfig_InitStatisticDialog(HWND hDlg, int a2, int* pData)
{
    HDC* v4; // ebp
    HWND DlgItem; // eax
    HDC DC; // eax
    HWND v7; // eax
    HDC v8; // eax
    int iqPoints; // eax
    HWND v10; // eax
    HWND hScrl; // eax
    SCROLLINFO scrlInfo; // [esp+10h] [ebp-1Ch] BYREF
    SithGameStatistics* pDataa; // [esp+38h] [ebp+Ch]

    v4 = (HDC*)*pData;
    pDataa = (SithGameStatistics*)pData[1];
    DlgItem = GetDlgItem(hDlg, 1135);
    DC = GetDC(DlgItem);
    *v4 = CreateCompatibleDC(DC);
    v7 = GetDlgItem(hDlg, 1135);
    v8 = GetDC(v7);
    v4[1] = CreateCompatibleDC(v8);
    iqPoints = jonesInventory_GetTotalIQPoints();
    jonesConfig_DrawStatisticDialogIQPoints(hDlg, (JonesDialogImageInfo**)pData, 164, iqPoints);
    if ( !pDataa->curLevelNum )
    {
        v10 = GetDlgItem(hDlg, 1133);
        EnableWindow(v10, 0);
    }

    jonesConfig_SetStatisticsDialogForLevel(hDlg, 17, pData);

    scrlInfo.cbSize = sizeof(SCROLLINFO);
    scrlInfo.fMask = SIF_TRACKPOS | SIF_DISABLENOSCROLL | SIF_POS | SIF_PAGE | SIF_RANGE;// aka SIF_ALL
    scrlInfo.nMin = 0;
    scrlInfo.nMax = pDataa->curLevelNum + 1;
    scrlInfo.nPage = 1;
    scrlInfo.nPos = scrlInfo.nMax;
    hScrl = GetDlgItem(hDlg, 1162);
    SendMessageA(hScrl, SBM_SETSCROLLINFO, TRUE, (LPARAM)&scrlInfo);

    pData[2] = scrlInfo.nMax;
    SetWindowLongA(hDlg, DWL_USER, (LONG)pData);
    return 1;
}

void J3DAPI jonesConfig_StatisticProc_HandleWM_COMMAND(HWND hWnd, int16_t wParam)
{
    int v2; // esi
    HDC v3; // [esp-8h] [ebp-14h]

    v2 = *(DWORD*)GetWindowLongA(hWnd, DWL_USER);
    if ( wParam > 0 && wParam <= 2 )
    {
        DeleteObject(*(HGDIOBJ*)(v2 + 8));
        v3 = *(HDC*)v2;
        *(DWORD*)(v2 + 8) = 0;
        DeleteDC(v3);
        DeleteDC(*(HDC*)(v2 + 4));
        EndDialog(hWnd, wParam);
    }
}
//
//int J3DAPI jonesConfig_ShowLevelCompletedDialog(HWND hWnd, int* pBalance, int* apItemsState, int a4, int elapsedTime, int qiPoints, int numFoundTrasures, int foundTrasureValue, int totalTreasureValue)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowLevelCompletedDialog, hWnd, pBalance, apItemsState, a4, elapsedTime, qiPoints, numFoundTrasures, foundTrasureValue, totalTreasureValue);
//}
//
//int __stdcall jonesConfig_LevelCompletedDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LevelCompletedDialogProc, hWnd, uMsg, wParam, lParam);
//}
//
//int J3DAPI jonesConfig_InitLevelCompletedDialog(HWND hDlg, int wParam, tLevelCompletedDialogState* pState)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InitLevelCompletedDialog, hDlg, wParam, pState);
//}
//
//void J3DAPI jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND(HWND hWnd, int wParam)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND, hWnd, wParam);
//}
//
//int J3DAPI jonesConfig_ShowStoreDialog(HWND hWnd, int* pBalance, int* pItemsState, int a4)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowStoreDialog, hWnd, pBalance, pItemsState, a4);
//}
//
//int __stdcall jonesConfig_StoreDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialogProc, hwnd, msg, wparam, lparam);
//}
//
//int J3DAPI jonesConfig_StoreHandleDragEvent(HWND hwnd, HWND hDlgCtrl)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreHandleDragEvent, hwnd, hDlgCtrl);
//}
//
//void J3DAPI jonesConfig_StoreDialog_HandleWM_MBUTTONUP(HWND hWnd)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_MBUTTONUP, hWnd);
//}
//
//BOOL J3DAPI jonesConfig_StoreDialog_HandleWM_MOUSEFIRST(HWND hWnd)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_MOUSEFIRST, hWnd);
//}
//
//int J3DAPI jonesConfig_InitStoreDialog(HWND hDlg, int a2, tStoreCartState* pCart)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InitStoreDialog, hDlg, a2, pCart);
//}
//
//int J3DAPI jonesConfig_StoreInitItemIcons(HWND hWnd, tStoreCartState* pCart)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreInitItemIcons, hWnd, pCart);
//}
//
//LRESULT J3DAPI jonesConfig_StoreSetListColumns(HWND hList, const char* pColumnName)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreSetListColumns, hList, pColumnName);
//}
//
//void J3DAPI jonesConfig_StoreInitItemList(HWND hWnd, int* apItemsState, int listID)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_StoreInitItemList, hWnd, apItemsState, listID);
//}
//
//void J3DAPI jonesConfig_UpdateBalances(HWND hDlg, tStoreCartState* pCart)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_UpdateBalances, hDlg, pCart);
//}
//
//void J3DAPI jonesConfig_AddStoreCartItem(HWND hDlg, tStoreCartState* pCart)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_AddStoreCartItem, hDlg, pCart);
//}
//
//void J3DAPI jonesConfig_RemoveStoreCartItem(HWND hDlg, tStoreCartState* pCart)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_RemoveStoreCartItem, hDlg, pCart);
//}
//
//void J3DAPI jonesConfig_StoreDialog_HandleWM_COMMAND(HWND hWnd, WPARAM wParam)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_COMMAND, hWnd, wParam);
//}
//
//void J3DAPI jonesConfig_ClearStoreCart(HWND hDlg, tStoreCartState* pCart)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_ClearStoreCart, hDlg, pCart);
//}
//
//int J3DAPI jonesConfig_ShowPurchaseMessageBox(HWND hWnd, tStoreCartState* dwInitParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowPurchaseMessageBox, hWnd, dwInitParam);
//}
//
//INT_PTR __stdcall jonesConfig_PurchaseMessageBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_PurchaseMessageBoxProc, hWnd, uMsg, wParam, lParam);
//}
//
//int J3DAPI jonesConfig_InitPurchaseMessageBox(HWND hDlg, int a2, tStoreCartState* pCart)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InitPurchaseMessageBox, hDlg, a2, pCart);
//}
//
//int J3DAPI jonesConfig_ShowDialogInsertCD(HWND hWnd, LPARAM dwInitParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowDialogInsertCD, hWnd, dwInitParam);
//}
//
//INT_PTR __stdcall jonesConfig_DialogInsertCDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_DialogInsertCDProc, hWnd, uMsg, wParam, lParam);
//}
//
//int J3DAPI jonesConfig_InitDialogInsertCD(HWND hDlg, int a2, int cdNum)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InitDialogInsertCD, hDlg, a2, cdNum);
//}
//
//int J3DAPI jonesConfig_InsertCD_HandleWM_COMMAND(HWND hWnd, int nResult)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_InsertCD_HandleWM_COMMAND, hWnd, nResult);
//}

HFONT J3DAPI jonesConfig_InitDialog(HWND hWnd, HFONT hFont, int dlgID)
{
    JonesDialogFontInfo fontInfo;
    fontInfo.bWindowMode = 0;
    fontInfo.hFont       = hFont;

    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( pSettings )
    {
        fontInfo.bWindowMode = pSettings->bWindowMode;
    }

    static float curFontScale = 0; // Changed: Made variable static to preserve state for cases when hFont != NULL. (See jonesConfig_LoadGameDialogHookProc)
                                   // Note, original code somehow managed to preserve the state of this variable on the stack and retrieve the value from it on another call
    if ( !hFont )
    {
        fontInfo.hFont = jonesConfig_CreateDialogFont(hWnd, fontInfo.bWindowMode, (uint16_t)dlgID, &curFontScale);
    }

    fontInfo.dialogID = HIWORD(dlgID);
    if ( !fontInfo.dialogID )
    {
        fontInfo.dialogID = (uint16_t)dlgID;
    }

    fontInfo.hControlFont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
    fontInfo.fontScaleX = curFontScale;
    fontInfo.fontScaleY = curFontScale;
    jonesConfig_SetDialogTitleAndPosition(hWnd, &fontInfo);

    fontInfo.dialogID = dlgID; // Use the original dlgID with potential NOFONTSCALE mask
    EnumChildWindows(hWnd, jonesConfig_SetPositionAndTextCallback, (LPARAM)&fontInfo);
    return fontInfo.hFont;
}

HFONT J3DAPI jonesConfig_CreateDialogFont(HWND hWnd, int bWindowMode, int dlgID, float* pFontScale)
{
    // Function creates dialog font and calculates scale
    // Note the function was adjusted to account for screen DPI

    if ( !hWnd )
    {
        return NULL;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);

    LPCSTR pFontName = jonesString_GetString("JONES_STR_FONT");
    if ( !pFontName )
    {
        STDLOG_ERROR("Error: Could not get font for dlg id:%d\n", dlgID); // Added log
        return NULL;
    }

    LOGFONT lf;
    HFONT hfont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
    GetObject(hfont, sizeof(LOGFONT), &lf);

    // Get system DPI first
    // Added: This was added
    UINT systemDPI = GetDpiForWindow(hWnd);
    float dpiScale = (float)systemDPI / USER_DEFAULT_SCREEN_DPI;

    STDLOG_STATUS("height: %i, width:%i, dpi:%d dpiScale:%f\n", rect.bottom, rect.right, systemDPI, dpiScale);

    double dialogRefHeight = 0;
    for ( size_t i = 0; i < STD_ARRAYLEN(jonesConfig_aDialogSizes); ++i )
    {
        if ( jonesConfig_aDialogSizes[i].dialogID == dlgID )
        {
            dialogRefHeight = jonesConfig_aDialogSizes[i].refHeight * dpiScale; // Added: scale by dpi
            break;
        }
    }

    double scale = 1.0; // Added: Init to 1.0
    if ( dialogRefHeight > 0 ) {
        scale = (dialogRefHeight / (double)rect.bottom) * dpiScale; // Added: scale by dpi
    }

    int cHeight;
    float cHeightf;
    uint32_t scrwidth, scrheight;

    int scaledRefHeight = (int)(RD_REF_HEIGHT * scale);
    int scaledRefWidth  = (int)(RD_REF_WIDTH * scale);

    if ( bWindowMode || !JonesMain_HasStarted() )
    {
        cHeight = lf.lfHeight;
        RECT rectDskt;
        GetWindowRect(GetDesktopWindow(), &rectDskt);
        scrwidth = rectDskt.right - rectDskt.left;
        scrheight = rectDskt.bottom - rectDskt.top;

        if ( (size_t)(rectDskt.bottom - rectDskt.top) < (size_t)scaledRefHeight )
        {
            SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDskt, 0);
            scrheight = rectDskt.bottom;
        }

        if ( scale > 1.0f )
        {
            cHeightf = (float)lf.lfHeight;
            float heightScale = (float)((double)scrheight / scaledRefHeight);
            if ( lf.lfHeight <= (int)(int32_t)((double)lf.lfHeight * heightScale) )
            {
                cHeightf = (float)((double)lf.lfHeight * heightScale);
            }
        }
        else
        {
            if ( scrheight < scaledRefHeight && scrwidth < scaledRefWidth )
            {
                scale = (float)((double)scrheight / scaledRefHeight * scale);
            }
            cHeightf = (float)((double)lf.lfHeight * scale);
        }
    }
    else
    {
        stdDisplay_GetBackBufferSize(&scrwidth, &scrheight);

        // Calculate base font size considering DPI
        cHeight = -MulDiv(10, systemDPI, USER_DEFAULT_SCREEN_DPI); // Changed: to 10 from 8
        cHeightf = (float)cHeight;

        if ( scrheight >= (size_t)scaledRefHeight || scrwidth >= (size_t)scaledRefWidth )
        {
            cHeightf = (float)((double)cHeight * scale);
        }
        else
        {
            if ( scale > 1.0f )
            {
                cHeightf = (float)((double)cHeight * ((double)scrheight / scaledRefHeight));
            }
            else
            {
                scale = (float)((double)scrheight / scaledRefHeight * scale);
                cHeightf = (float)((double)cHeight * scale);
            }
        }
    }

    float cHeighRnd = floorf(cHeightf);
    if ( fabsf(cHeighRnd - cHeightf) < 0.5f )
    {
        cHeightf = cHeighRnd;
    }

    if ( cHeight > (int)cHeightf ) // Changed: Use cHeightf if smaller than cHeight; i.e.: bigger font size
    {
        cHeight = (int)cHeightf;
    }

    // Adjust minimum height based on DPI
    if ( cHeight > -MulDiv(10, systemDPI, USER_DEFAULT_SCREEN_DPI) ) // Changed: to 10 from 9 and dpi scale check
    {
        cHeight = -MulDiv(10, systemDPI, USER_DEFAULT_SCREEN_DPI);
    }

    if ( bWindowMode || !JonesMain_HasStarted() )
    {
        *pFontScale = (float)scale;
    }
    else if ( scale > 1.0f
        && (scrheight <= (size_t)(scaledRefHeight) || scrwidth <= (size_t)(scaledRefWidth)) )
    {
        *pFontScale = (float)((double)scrheight / (scaledRefHeight));
    }
    else
    {
        *pFontScale = (float)scale;
    }

    // Create DPI-aware font
    LOGFONT lf2 = {
        .lfHeight         = cHeight,
        .lfWidth          = 0,
        .lfEscapement     = 0,
        .lfOrientation    = 0,
        .lfWeight         = FW_REGULAR,
        .lfItalic         = FALSE,
        .lfUnderline      = FALSE,
        .lfStrikeOut      = FALSE,
        .lfCharSet        = DEFAULT_CHARSET,
        .lfOutPrecision   = OUT_DEFAULT_PRECIS,
        .lfClipPrecision  = CLIP_CHARACTER_PRECIS,
        .lfQuality        = PROOF_QUALITY,
        .lfPitchAndFamily = FF_DONTCARE
    };
    STD_STRCPY(lf2.lfFaceName, pFontName);

    return CreateFontIndirect(&lf2);
}

void J3DAPI jonesConfig_ResetDialogFont(HWND hWndParent, HFONT hFont)
{
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( hFont && (!pSettings || !pSettings->bWindowMode) )
    {
        EnumChildWindows(hWndParent, jonesConfig_ResetWindowFontCallback, 0);
        DeleteObject((HGDIOBJ)hFont);
    }
}

BOOL CALLBACK jonesConfig_ResetWindowFontCallback(HWND hWnd, LPARAM lparam)
{
    J3D_UNUSED(lparam);
    HFONT hfont = (HFONT)GetWindowLongPtr(hWnd, GWL_USERDATA);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfont, 0);  // 0 - don't repaint
    return TRUE;
}

BOOL CALLBACK jonesConfig_SetPositionAndTextCallback(HWND hCtrl, LPARAM lparam)
{
    // Function resize control by scale, sets font and 
    // replaces all text of control from JONES_STR_* to corresponding text

    // Fixed: Check if hCtrl parent is top dialog, otherwise skip control.
    //        This fixes positioning and scaling of controls with children
    //        as they also get enumerated. So we skip here any child window of the control.
    if ( GetDlgCtrlID(GetParent(hCtrl)) != 0 ) {
        return TRUE;
    }

    if ( !lparam ) { // Added: Added check for null
        return TRUE;
    }
    JonesDialogFontInfo* pFontInfo = (JonesDialogFontInfo*)lparam;

    if ( pFontInfo->hFont )
    {
        // Scale and set font
        jonesConfig_SetWindowFontAndPosition(hCtrl, pFontInfo);
    }

    if ( pFontInfo->dialogID == 154 || pFontInfo->dialogID == 159 ) // Load/Save dialogs
    {
        return TRUE;
    }

    // Replace JONES_STR_* strings to corresponding text

    CHAR aClassName[256] = { 0 };
    GetClassName(hCtrl, aClassName, 256);

    CHAR aText[256] = { 0 };
    if ( strncmpi(aClassName, "BUTTON", STD_ARRAYLEN(aClassName)) == 0 )
    {
        GetWindowText(hCtrl, aText, STD_ARRAYLEN(aText));
        LPCSTR pText = jonesString_GetString(aText);
        if ( pText )
        {
            SetWindowText(hCtrl, pText);
        }

        return TRUE;
    }
    else if ( strncmpi(aClassName, "STATIC", STD_ARRAYLEN(aClassName)) == 0 )
    {
        GetWindowText(hCtrl, aText, STD_ARRAYLEN(aText));
        if ( strchr(aText, '%') )
        {
            return TRUE;
        }

        LPCSTR pText = jonesString_GetString(aText);
        if ( pText )
        {
            SetWindowText(hCtrl, pText);
        }

        return TRUE;

    }

    return TRUE;
}

void J3DAPI jonesConfig_SetWindowFontAndPosition(HWND hCtrl, JonesDialogFontInfo* pFontInfo)
{
    HWND hParent = GetParent(hCtrl);

    // Set font
    if ( pFontInfo->hFont )
    {
        SendMessage(hCtrl, WM_SETFONT, (WPARAM)pFontInfo->hFont, 1); // 1 - repaint
        if ( HIWORD(pFontInfo->dialogID) != JONESCONFIG_NOFONTSCALEMASK )
        {
            SetWindowLongPtr(hCtrl, GWL_USERDATA, (LONG_PTR)pFontInfo->hControlFont);
        }
    }

    RECT rectWindow;
    GetWindowRect(hCtrl, &rectWindow);

    RECT rectClient;
    GetClientRect(hCtrl, &rectClient);

    RECT rectDlgWindow;
    GetWindowRect(hParent, &rectDlgWindow);

    if ( !pFontInfo->bWindowMode || pFontInfo->fontScaleX < 1.0f || pFontInfo->fontScaleY < 1.0f )
    {
        int offsetY = 0;
        if ( HIWORD(pFontInfo->dialogID) != JONESCONFIG_NOFONTSCALEMASK )
        {
        LABEL_17:
            HICON hIcon = (HICON)SendMessage(hCtrl, STM_GETICON, 0, 0);
            HWND dlgItem = GetDlgItem(hParent, 1182);
            if ( dlgItem == hCtrl )
            {
                hIcon = (HICON)dlgItem;
            }

            HWND hwndResumeBtn = NULL;
            HWND hwndThumbnail = NULL;

            if ( pFontInfo->dialogID == 159 || pFontInfo->dialogID == 154 )// Load/Save dialog
            {
                LONG dlgID =(LONG)GetWindowLongPtr(hCtrl, GWL_USERDATA); // TODO: UNUSED
                J3D_UNUSED(dlgID);

                HWND hwndParent = GetParent(hParent);
                if ( hwndParent )
                {
                    HWND dlgItem1137 = GetDlgItem(hwndParent, 1137);
                    if ( dlgItem1137 )
                    {
                        if ( dlgItem1137 != hCtrl )
                        {
                            RECT rectDlgItem1137Window;
                            GetWindowRect(dlgItem1137, &rectDlgItem1137Window);
                            offsetY = (int)((double)(rectDlgItem1137Window.bottom - rectDlgItem1137Window.top) * (1.0f - pFontInfo->fontScaleX));
                        }
                    }
                }

                if ( hCtrl == GetDlgItem(hParent, 1120) )
                {
                    hwndResumeBtn = hCtrl;
                }
                if ( hCtrl == GetDlgItem(hParent, 1163) || hCtrl == GetDlgItem(hParent, 1125) )
                {
                    hwndThumbnail = hCtrl; // Load / Save thumbnail
                    offsetY = 0;
                }
            }

            //if ( (!hIcon || heightDesktop < (size_t)RD_REF_HEIGHT && widthDesktop < (size_t)RD_REF_WIDTH) && !hwndThumbnail )
            {
                double fontScaleX = pFontInfo->fontScaleX;
             /*   if ( hIcon && heightDesktop < (size_t)RD_REF_HEIGHT && widthDesktop < (size_t)RD_REF_WIDTH )
                {
                    fontScaleX = (double)heightDesktop / RD_REF_HEIGHT;
                }*/

                rectWindow.bottom = (LONG)((double)(rectWindow.bottom - rectWindow.top) * fontScaleX) + rectWindow.top;
            }

            //if ( (!hIcon || heightDesktop < (size_t)RD_REF_HEIGHT && widthDesktop < (size_t)RD_REF_WIDTH) && !hwndThumbnail && !hwndResumeBtn )
            {
                double fontScaleY = pFontInfo->fontScaleY;
               /* if ( hIcon && heightDesktop < (size_t)RD_REF_HEIGHT && widthDesktop < (size_t)RD_REF_WIDTH )
                {
                    fontScaleY = (double)widthDesktop / RD_REF_WIDTH;
                }*/

                rectWindow.right = (LONG)((double)(rectWindow.right - rectWindow.left) * fontScaleY) + rectWindow.left;
            }

            if ( !hParent )
            {
                return;
            }

            GetWindowRect(hParent, &rectDlgWindow);
            jonesConfig_GetWindowScreenRect(hParent, &rectClient);

            int posX = (int)((double)(rectWindow.left - rectClient.left) * pFontInfo->fontScaleY);
            int posY = (int)((double)(rectWindow.top - rectClient.top) * pFontInfo->fontScaleX);
            if ( offsetY > 0 && !hwndThumbnail )
            {
                posY += offsetY;
            }

            // Resize and reposition control
            MoveWindow(hCtrl, posX, posY, rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top, /*bRepaint=*/TRUE);

            GetWindowRect(hCtrl, &rectWindow);
            GetClientRect(hCtrl, &rectClient);
            if ( rectWindow.bottom <= rectDlgWindow.bottom && rectWindow.right <= rectDlgWindow.right )
            {
                return;
            }

            int dDlgWinX = rectWindow.right - rectDlgWindow.right;
            int dDlgWinY = rectWindow.bottom - rectDlgWindow.bottom;

            int dlgWidth  = rectDlgWindow.right - rectDlgWindow.left;
            int dlgHeight = rectDlgWindow.bottom - rectDlgWindow.top;

            if ( rectWindow.bottom - rectDlgWindow.bottom <= 0 || dDlgWinX <= 0 )
            {
                if ( dDlgWinY <= 0 )
                {
                    MoveWindow(hParent, rectDlgWindow.left, rectDlgWindow.top, dDlgWinX + dlgWidth, dlgHeight, 1);
                }
                else
                {
                    MoveWindow(hParent, rectDlgWindow.left, rectDlgWindow.top, dlgWidth, dDlgWinY + dlgHeight, 1);
                }
            }
            else
            {
                MoveWindow(hParent, rectDlgWindow.left, rectDlgWindow.top, dDlgWinX + dlgWidth, dDlgWinY + dlgHeight, 1);
            }

            return;
        }

        LONG dlgID = (LONG)GetWindowLongPtr(hCtrl, GWL_USERDATA);
        if ( dlgID == 159 || dlgID == 154 )     // load/save dialogs
        {
            SendMessage(hCtrl, WM_SETFONT, (WPARAM)pFontInfo->hControlFont, 1);// 1 - marks redraw
            return;
        }

        HWND dlgItem1137  = GetDlgItem(hParent, 1137);
        if ( dlgItem1137 ) // note, no dlg item with this ID in resources
        {
            CHAR aClassName[256] = { 0 };
            GetClassName(hCtrl, aClassName, 256);
            if ( dlgItem1137 != hCtrl && strcmp(aClassName, "ToolbarWindow32") )
            {
                RECT rectDlgItem1137Window;
                GetWindowRect(dlgItem1137, &rectDlgItem1137Window);
                offsetY = (int)((double)(rectDlgItem1137Window.bottom - rectDlgItem1137Window.top) * (1.0f - pFontInfo->fontScaleX));
            }

            goto LABEL_17;
        }
    }
}

void J3DAPI jonesConfig_GetWindowScreenRect(HWND hWnd, LPRECT lpRect)
{
    GetClientRect(hWnd, lpRect);

    POINT point = { 0 };
    ClientToScreen(hWnd, &point);
    lpRect->top  = point.y;
    lpRect->left = point.x;

    point.x = lpRect->right;
    point.y = lpRect->bottom;
    ClientToScreen(hWnd, &point);

    lpRect->right  = point.x;
    lpRect->bottom = point.y;
}

void J3DAPI jonesConfig_SetDialogTitleAndPosition(HWND hWnd, JonesDialogFontInfo* pDlgFontInfo)
{
    if ( pDlgFontInfo->dialogID != 154 && pDlgFontInfo->dialogID != 159 && pDlgFontInfo->dialogID != JONESCONFIG_NOFONTSCALEMASK )// if not load/save dialogs
    {
        CHAR aTitleJS[256] = { 0 };
        GetWindowText(hWnd, aTitleJS, STD_ARRAYLEN(aTitleJS));
        if ( strlen(aTitleJS) )
        {
            LPCSTR pTitle = jonesString_GetString(aTitleJS);
            if ( pTitle )
            {
                SetWindowText(hWnd, pTitle);
            }
        }
    }

    RECT rectDeskto;
    HWND hswnDesktop = GetDesktopWindow();
    GetWindowRect(hswnDesktop, &rectDeskto);

    uint32_t width, height;
    height = rectDeskto.bottom - rectDeskto.top;
    width  = rectDeskto.right - rectDeskto.left;

    if ( !pDlgFontInfo->bWindowMode || pDlgFontInfo->fontScaleX < 1.0f || pDlgFontInfo->fontScaleY < 1.0f )
    {
        RECT rectWindow;
        GetWindowRect(hWnd, &rectWindow);

        RECT rectClient;
        GetClientRect(hWnd, &rectClient);

        if ( !pDlgFontInfo->bWindowMode && JonesMain_HasStarted() )
        {
            stdDisplay_GetBackBufferSize(&width, &height);
        }

        if ( pDlgFontInfo->dialogID == 154 || pDlgFontInfo->dialogID == 159 )// load/save dialogs
        {
            int32_t scaledClientWidth = (int32_t)((1.0f - pDlgFontInfo->fontScaleY) * (float)SITHSAVEGAME_THUMB_WIDTH) + rectClient.right;
            int32_t offsetY = (int32_t)((1.0f - pDlgFontInfo->fontScaleX) * (float)SITHSAVEGAME_THUMB_HEIGHT);
            //int32_t scaledClientHeight = offsetY + rectClient.bottom; // TODO: Unused

            LONG winWidth  = rectWindow.right - rectWindow.left - (rectClient.right - scaledClientWidth);
            LONG winHeight = rectWindow.bottom - rectWindow.top + offsetY;

            RECT rectParent;
            jonesConfig_GetWindowScreenRect(GetParent(hWnd), &rectParent);

            RECT rectClientScreen;
            jonesConfig_GetWindowScreenRect(hWnd, &rectClientScreen);

            rectWindow.top    = rectClientScreen.top - rectParent.top;
            rectWindow.left   = rectClientScreen.left - rectParent.left;
            rectWindow.bottom = winHeight + rectClientScreen.top - rectParent.top;
            rectWindow.right  = winWidth + rectClientScreen.left - rectParent.left;
        }
        else
        {
            int32_t scaledClientWidth  = (int32_t)((double)rectClient.right * pDlgFontInfo->fontScaleY);
            int32_t scaledClientHeight = (int32_t)((double)rectClient.bottom * pDlgFontInfo->fontScaleX);
            if ( pDlgFontInfo->dialogID == JONESCONFIG_NOFONTSCALEMASK )
            {
                scaledClientWidth += (int32_t)((1.0f - pDlgFontInfo->fontScaleY) * (float)SITHSAVEGAME_THUMB_WIDTH);
                scaledClientHeight += (int32_t)((1.0f - pDlgFontInfo->fontScaleX) * (float)SITHSAVEGAME_THUMB_HEIGHT);
            }

            LONG winWidth  = rectWindow.right - rectWindow.left - (rectClient.right - scaledClientWidth);
            LONG winHeight = rectWindow.bottom - rectWindow.top - (rectClient.bottom - scaledClientHeight);

            rectWindow.top    = (LONG)(height - winHeight) / 2;
            rectWindow.left   = (LONG)(width - winWidth) / 2;
            rectWindow.bottom = winHeight + rectWindow.top;
            rectWindow.right  = winWidth + rectWindow.left;
        }

        MoveWindow(hWnd, rectWindow.left, rectWindow.top, rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top, 1);
    }
}

int J3DAPI jonesConfig_GetSaveGameFilePath(HWND hWnd, char* pOutFilePath)
{
    char aFileterStr[512] = { 0 };
    const char* pFilterStr = jonesString_GetString("JONES_STR_FILTER");
    if ( pFilterStr ) {
        STD_STRCPY(aFileterStr, pFilterStr);
    }

    char aSaveGameStr[512] = { 0 };
    const char* pSaveGMStr = jonesString_GetString("JONES_STR_SAVEGM");
    if ( pSaveGMStr ) {
        STD_STRCPY(aSaveGameStr, pSaveGMStr);
    }

    if ( !aFileterStr[0] || !aSaveGameStr[0] ) {
        return 2;
    }

    GetWindowLongPtr(hWnd, GWL_HINSTANCE); // ??

    CHAR aCurDir[128] = { 0 };
    GetCurrentDirectory(STD_ARRAYLEN(aCurDir), aCurDir);

    OPENFILENAME ofn = { 0 };
    ofn.lStructSize   = sizeof(OPENFILENAME);
    ofn.hwndOwner     = hWnd;
    ofn.hInstance     = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    char aFilterStr[128] = { 0 };
    STD_FORMAT(aFilterStr, aFileterStr, "(.nds)");
    STD_FORMAT(aFilterStr, "%s%c%s%c", aFilterStr, '\0', "*.nds", '\0'); // Fixed: filtering only by .nds files. Note, 2 terminal nulls are required, that's way null at the end

    ofn.lpstrFilter = aFilterStr;

    memset(&ofn.lpstrCustomFilter, 0, 12);

    char aFilename[128] = { 0 };
    aFilename[0]        = 0;
    ofn.lpstrFile       = aFilename;
    ofn.nMaxFile        = STD_ARRAYLEN(aFilename);

    char aFileTitle[128] = { 0 };
    ofn.lpstrFileTitle   = aFileTitle;
    ofn.nMaxFileTitle    = STD_ARRAYLEN(aFileTitle);

    SaveGameDialogData dialogData = { 0 };
    dialogData.hThumbnail         = NULL;
    ofn.lCustData                 = (LPARAM)&dialogData;

    ofn.lpstrInitialDir = sithGetSaveGamesDir();
    ofn.lpstrTitle      = aSaveGameStr;
    ofn.Flags           = OFN_EXPLORER | OFN_NONETWORKBUTTON | OFN_NOVALIDATE | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
    ofn.nFileOffset     = 0;
    ofn.nFileExtension  = 0;
    ofn.lpstrDefExt     = "nds";
    ofn.lpfnHook        = jonesConfig_SaveGameDialogHookProc;
    ofn.lpTemplateName  = MAKEINTRESOURCE(154);

    uint32_t width, height;
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( pSettings && pSettings->bWindowMode )
    {
        RECT rect;
        GetWindowRect(GetDesktopWindow(), &rect);
        height = rect.bottom - rect.top;
        width  = rect.right - rect.left;
    }
    else {
        stdDisplay_GetBackBufferSize(&width, &height);
    }

    BOOL res = JonesDialog_ShowFileSelectDialog(&ofn,/*bOpen=*/0);
    SetCurrentDirectory(aCurDir);

    if ( !res || !pOutFilePath ) {
        return 2;
    }

    stdFnames_ChangeExt(ofn.lpstrFile, "nds");
    stdUtil_StringCopy(pOutFilePath, 128u, ofn.lpstrFile);
    return 1;
}

UINT_PTR CALLBACK jonesConfig_SaveGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_INITDIALOG:
        {
            return jonesConfig_SaveGameDialogInit(hDlg, wParam, (LPOPENFILENAME)lParam);
        }
        case WM_COMMAND:
        {
            jonesConfig_sub_405F60(hDlg);
            return 0;
        }
        case WM_CLOSE:
        {
            DeleteObject((HGDIOBJ)jonesConfig_hFontSaveGameDlg);
            jonesConfig_hFontSaveGameDlg = NULL;
            return 0;
        }
        case WM_DESTROY:
        {
            HDC* hdc = (HDC*)GetWindowLongPtr(hDlg, DWL_USER);
            DeleteDC(*hdc);
            *hdc = NULL;
            return 1;
        }
        case WM_NOTIFY:
        {
            SaveGameDialogData* pData  = (SaveGameDialogData*)GetWindowLongPtr(hDlg, DWL_USER);
            switch ( ((LPNMHDR)lParam)->code )
            {
                case CDN_FILEOK:
                {
                    OFNOTIFY* pOfNotify = (OFNOTIFY*)lParam;
                    bool bValidFile     = false;
                    CHAR aPath[128]     = { 0 };
                    char aFilename[128] = { 0 };

                    if ( pOfNotify->lpOFN->nFileOffset < 0x8000 )
                    {
                        CHAR aExtension[128] = { 0 };
                        STD_FORMAT(aExtension, ".%s", pOfNotify->lpOFN->lpstrDefExt);

                        CHAR aSearchPath[128] = { 0 };
                        CommDlg_OpenSave_GetSpec(GetParent(hDlg), aFilename, STD_ARRAYLEN(aFilename));

                        size_t nFileOffset = 0;
                        char* pFilename = strstr(pOfNotify->lpOFN->lpstrFile, aFilename);
                        if ( pFilename )
                        {
                            nFileOffset = pFilename - pOfNotify->lpOFN->lpstrFile;
                        }
                        else
                        {
                            nFileOffset = strlen(pOfNotify->lpOFN->lpstrFile);
                        }

                        STD_STRNCPY(aSearchPath, pOfNotify->lpOFN->lpstrFile, nFileOffset);

                        LPCSTR pFilePart; // TODO: this might be used for file name instead of searching for it below?
                        SearchPath(aSearchPath, aFilename, aExtension, STD_ARRAYLEN(aPath), aPath, &pFilePart);

                        CHAR aCurDir[128] = { 0 };
                        STD_STRCPY(aCurDir, aSearchPath);

                        pFilename = strrchr(pOfNotify->lpOFN->lpstrFile, '\\');
                        if ( pFilename )
                        {
                            nFileOffset = pFilename - pOfNotify->lpOFN->lpstrFile;
                        }
                        else
                        {
                            nFileOffset = strlen(pOfNotify->lpOFN->lpstrFile);
                        }

                        STD_STRNCPY(aSearchPath, pOfNotify->lpOFN->lpstrFile, nFileOffset);

                        if ( pOfNotify->lpOFN->nFileExtension )
                        {
                            pFilename = &pOfNotify->lpOFN->lpstrFile[pOfNotify->lpOFN->nFileExtension];
                            if ( !*pFilename )
                            {
                                pFilename = NULL;
                            }
                        }
                        else
                        {
                            pFilename = NULL;
                        }

                        if ( (SetCurrentDirectory(aSearchPath) || strlen(aPath)) && (!pFilename || strcmp(pFilename, pOfNotify->lpOFN->lpstrDefExt) == 0) )
                        {
                            SetCurrentDirectory(aCurDir);
                            bValidFile = true;
                        }

                        size_t nOccurrence = strcspn(aFilename, "?*");
                        if ( nOccurrence != strlen(aFilename) )
                        {
                            bValidFile = false;
                        }

                        // TODO: Replace const 17 with macro or with some STD_ARRAYLEN(aLevels)
                        for ( size_t levelNum = 0; levelNum < 17u; ++levelNum )
                        {
                            const char* pSaveName = sithGetLevelSaveFilename(levelNum);
                            if ( pSaveName )
                            {
                                char aAutoSaveFilename[128] = { 0 };
                                const char* pAutoSavePrefix = sithGetAutoSaveFilePrefix();
                                STD_FORMAT(aAutoSaveFilename, "%s%s", pAutoSavePrefix, pSaveName);
                                if ( !strcmpi(aFilename, aAutoSaveFilename) )
                                {
                                    bValidFile = false;
                                    break;
                                }
                            }
                        }

                        char aQuckSaveFilename[128] = { 0 };
                        const char* pQuickSavePrefix = sithGetQuickSaveFilePrefix();
                        STD_FORMAT(aQuckSaveFilename, "%s.%s", pQuickSavePrefix, pOfNotify->lpOFN->lpstrDefExt);

                        stdFnames_ChangeExt(aFilename, pOfNotify->lpOFN->lpstrDefExt); // Fixed: Added .nds extension to filename here to make sure filename "QUICKSAVE" without ".nds" extension doesn't slip over
                        if ( strcmpi(aFilename, aQuckSaveFilename) == 0 )
                        {
                            bValidFile = false;
                        }
                    }

                    if ( pOfNotify->lpOFN->nFileOffset < 0x8000 && bValidFile )
                    {
                        if ( strlen(aPath) )
                        {
                            STD_STRCPY(pData->aFilePath, aFilename);
                            stdFnames_ChangeExt(pData->aFilePath, pOfNotify->lpOFN->lpstrDefExt);

                            if ( jonesConfig_ShowOverwriteSaveGameDlg(hDlg, pData->aFilePath) == 1 )
                            {
                                return 0;
                            }
                            else
                            {
                                SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                                return 1;
                            }
                        }
                    }
                    else
                    {
                        char* pFormat = (char*)jonesString_GetString("JONES_STR_INVALIDFILE");
                        if ( pFormat )
                        {
                            memset(aFilename, 0, sizeof(aFilename));
                            CommDlg_OpenSave_GetSpec(GetParent(hDlg), aFilename, STD_ARRAYLEN(aFilename));

                            char aErrorText[256] = { 0 };
                            STD_FORMAT(aErrorText, pFormat, aFilename);

                            jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_SAVEGM", aErrorText, 141);
                        }

                        SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                        return 1;
                    }
                }
                case CDN_INITDONE:
                {
                    HWND hThumbnail = GetDlgItem(hDlg, 1125);
                    SetWindowLongPtr(hThumbnail, GWL_USERDATA, 154);

                    HWND hIcon = GetDlgItem(hDlg, 1115);
                    SetWindowLongPtr(hIcon, GWL_USERDATA, 154);

                    jonesConfig_hFontSaveGameDlg = jonesConfig_InitDialog(GetParent(hDlg), NULL, JONESCONFIG_NOFONTSCALE(154));
                    jonesConfig_hFontSaveGameDlg = jonesConfig_InitDialog(hDlg, jonesConfig_hFontSaveGameDlg, 154);
                    SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
                    return 1;
                }
            };
            return 0;
        }
    }

    return 0;
}

int J3DAPI jonesConfig_SaveGameDialogInit(HWND hDlg, int a2, LPOPENFILENAME lpOfn)
{
    J3D_UNUSED(a2);

    SaveGameDialogData* pData = (SaveGameDialogData*)lpOfn->lCustData;
    pData->hThumbnail = sithGamesave_GetScreenShotBitmap();

    HWND hThumbnail = GetDlgItem(hDlg, 1125);
    pData->hdcThumbnail = CreateCompatibleDC(GetDC(hThumbnail));

    hThumbnail = GetDlgItem(hDlg, 1125); // ??
    pData->pfThumbnailProc = GetWindowLongPtr(hThumbnail, GWL_WNDPROC);
    SetWindowLongPtr(hThumbnail, GWL_WNDPROC, (LONG)jonesConfig_SaveGameThumbnailPaintProc);

    SetWindowLongPtr(hDlg, DWL_USER, (LONG)pData);

    RECT thumbRect;
    GetClientRect(hThumbnail, &thumbRect);

    // Added: Calculate thumbRect to screen
    POINT pt = { thumbRect.left, thumbRect.top };
    ClientToScreen(hThumbnail, &pt);
    OffsetRect(&thumbRect, pt.x - thumbRect.left, pt.y - thumbRect.top);

    // Changed: Added scale the thumb size to DPI
    UINT systemDPI = GetDpiForWindow(hDlg);
    double dpiScale = (double)systemDPI / USER_DEFAULT_SCREEN_DPI;
    LONG tbImageWidth  = (LONG)ceil((double)SITHSAVEGAME_THUMB_WIDTH * dpiScale);
    LONG tbImageHeight = (LONG)ceil((double)SITHSAVEGAME_THUMB_HEIGHT * dpiScale);

    LONG thumbWidth  = tbImageWidth - (thumbRect.right - thumbRect.left);
    LONG thumbHeight = tbImageHeight - (thumbRect.bottom - thumbRect.top);

    if ( thumbWidth != 0 || thumbHeight != 0 )
    {
        RECT dlgWndRect;
        GetWindowRect(hDlg, &dlgWndRect);

        RECT thumbWndRect;
        GetWindowRect(hThumbnail, &thumbWndRect);

        // Added: Added padding. This should fix drawing all components right of file list
        const int pad = (int)ceil(10.0 * dpiScale);
        MoveWindow(hDlg,
            dlgWndRect.left,
            dlgWndRect.top,
            thumbWidth + dlgWndRect.right - dlgWndRect.left + pad,
            dlgWndRect.bottom - dlgWndRect.top + pad,
            TRUE
        );

        MoveWindow(
            hThumbnail,
            (thumbWndRect.left - dlgWndRect.left) + (thumbRect.left - thumbWndRect.left), // Added: x + borderSize (thumbRect.left - thumbWndRect.left)... This should fix rendering image on different DPIs
            thumbWndRect.top - dlgWndRect.top,
            thumbWidth + thumbWndRect.right - thumbWndRect.left,
            thumbHeight + thumbWndRect.bottom - thumbWndRect.top,
            TRUE
        );
    }

    HWND h1152 = GetDlgItem(GetParent(hDlg), 1152);  // some other dlgItem
    SendMessage(h1152, EM_LIMITTEXT, 60u, 0);
    return 1;
}

LRESULT CALLBACK jonesConfig_SaveGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hwndParent = (HWND)GetWindowLongPtr(hWnd, GWL_HWNDPARENT);
    SaveGameDialogData* pData = (SaveGameDialogData*)GetWindowLongPtr(hwndParent, DWL_USER);
    if ( uMsg != WM_PAINT || !pData || !pData->hThumbnail )
    {
        if ( !pData ) {
            return 1;
        }
        return CallWindowProc((WNDPROC)pData->pfThumbnailProc, hWnd, uMsg, wParam, lParam);
    }

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, (LPPAINTSTRUCT)&ps);
    SetStretchBltMode(hdc, STRETCH_HALFTONE);
    jonesConfig_DrawImageOnDialogItem(hwndParent, pData->hdcThumbnail, hdc, 1125, pData->hThumbnail, NULL);
    EndPaint(hWnd, &ps);
    return 0;
}

int J3DAPI jonesConfig_ShowExitGameDialog(HWND hWnd, char* pSaveGameFilePath)
{
    GameSaveMsgBoxData data;
    data.dialogID = 211;
    data.pNdsFilePath = pSaveGameFilePath;
    return JonesDialog_ShowDialog((LPCSTR)211, hWnd, jonesConfig_ExitGameDlgProc, (LPARAM)&data);
}

INT_PTR CALLBACK jonesConfig_ExitGameDlgProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    switch ( uMsg )
    {
        case WM_INITDIALOG:
        {
            RECT rectWnd;
            GetClientRect(hWnd, &rectWnd);
            jonesConfig_GetWindowScreenRect(hWnd, &rectWnd);

            RECT rectWndIcon;
            HWND hIcon = GetDlgItem(hWnd, 1182);

            // Added: Make hIcon to be drawn by hWnd -> WM_DRAWITEM
            SetWindowLong(hIcon, GWL_STYLE, GetWindowLong(hIcon, GWL_STYLE) | SS_OWNERDRAW);

            GetWindowRect(hIcon, &rectWndIcon);
            MoveWindow(hIcon, rectWndIcon.top - rectWnd.top, rectWndIcon.left - rectWnd.left, 96, 96, TRUE); // Changed: Shange icon size to 96 from 64

            GameSaveMsgBoxData* pGSData = (GameSaveMsgBoxData*)lparam;
            jonesConfig_hFontExitDlg = jonesConfig_InitDialog(hWnd, 0, pGSData->dialogID);

            int result = jonesConfig_GameSaveSetData(hWnd, wparam, pGSData);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return result;
        }
        case WM_COMMAND:
            jonesConfig_MsgBoxDlg_HandleWM_COMMAND(hWnd, (unsigned __int16)wparam);
            return 0;
        case WM_DESTROY:
            jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontExitDlg);
            return 1;
        case WM_DRAWITEM: // Added: Fixes icon drawing
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lparam;
            if ( pdis->CtlID == 1182 )
            {
                HDC hmemdc = CreateCompatibleDC(pdis->hDC);
                SetStretchBltMode(pdis->hDC, STRETCH_HALFTONE);
                jonesConfig_DrawImageOnDialogItem(hWnd, hmemdc, pdis->hDC, 1182, jonesConfig_apDialogIcons[4], jonesConfig_apDialogIcons[5]); // exit and exitmask bmps
                DeleteDC(hmemdc);
                return TRUE;
            }
            return FALSE;
        }

        default:
            return 0;
    }
}

int J3DAPI jonesConfig_GetLoadGameFilePath(HWND hWnd, char* pDestNdsPath)
{
    char aFilterFormatStr[512] = { 0 };
    const char* pFilterStr = jonesString_GetString("JONES_STR_FILTER");
    if ( pFilterStr )
    {
        STD_STRCPY(aFilterFormatStr, pFilterStr);
    }

    char aLoadGameStr[512] = { 0 };
    const char* pLoadGameStr = jonesString_GetString("JONES_STR_LOADGM");
    if ( pLoadGameStr )
    {
        STD_STRCPY(aLoadGameStr, pLoadGameStr);
    }

    if ( !aFilterFormatStr[0] || !aLoadGameStr[0] )
    {
        return 2;
    }

    char aCwd[128] = { 0 };
    GetCurrentDirectory(STD_ARRAYLEN(aCwd), aCwd);

    LoadGameDialogData data = { 0 };
    data.hThumbnail = 0;

    char aFilterStr[128] = { 0 };
    STD_FORMAT(aFilterStr, aFilterFormatStr, " (.nds)");
    STD_FORMAT(aFilterStr, "%s%c%s%c", aFilterStr, '\0', "*.nds", '\0'); // Fixed: filtering only by .nds files. Note, 2 terminal nulls are required, that's way null at the end

    OPENFILENAME ofn      = { 0 };
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);
    ofn.lpstrFilter       = aFilterStr;
    ofn.lpstrCustomFilter = NULL;

    char aLastFile[128] = { 0 };
    const char* pLastFile = sithGamesave_GetLastFilename();
    if ( pLastFile ) {
        STD_STRCPY(aLastFile, pLastFile);
    }

    ofn.nMaxFile  = STD_ARRAYLEN(aLastFile);
    ofn.lpstrFile = aLastFile;
    if ( strlen(aLastFile) == 0 ) {
        aLastFile[0] = 0;
    }

    char szFileTitle[128] = { 0 };
    ofn.lpstrFileTitle  = szFileTitle;
    ofn.nMaxFileTitle   = STD_ARRAYLEN(szFileTitle);

    ofn.lpstrInitialDir = sithGetSaveGamesDir();
    ofn.lpstrTitle      = aLoadGameStr;
    ofn.Flags           = OFN_EXPLORER | OFN_NONETWORKBUTTON | OFN_NOVALIDATE | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_READONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.nFileOffset     = 0;
    ofn.lpstrDefExt     = "nds";
    ofn.lCustData       = (LPARAM)&data;
    ofn.lpfnHook        = jonesConfig_LoadGameDialogHookProc;
    ofn.lpTemplateName  = MAKEINTRESOURCE(159);

    uint32_t width, height;
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( pSettings && pSettings->bWindowMode || !JonesMain_HasStarted() )
    {
        HWND hwndDesktop = GetDesktopWindow();
        RECT rect;
        GetWindowRect(hwndDesktop, &rect);
        height = rect.bottom - rect.top;
        width = rect.right - rect.left;
    }
    else
    {
        stdDisplay_GetBackBufferSize(&width, &height);
    }

    BOOL bHasFilePath = JonesDialog_ShowFileSelectDialog((LPOPENFILENAME)&ofn, 1);
    SetCurrentDirectory(aCwd);
    if ( !bHasFilePath && !data.unknown36 || !pDestNdsPath )
    {
        return 2;
    }

    if ( bHasFilePath )
    {
        stdFnames_ChangeExt(ofn.lpstrFile, "nds");
        stdUtil_StringCopy(pDestNdsPath, 128, ofn.lpstrFile);
    }
    else
    {
        stdFnames_ChangeExt(data.aFilePath, "nds");
        stdUtil_StringCopy(pDestNdsPath, 128, data.aFilePath);
    }

    return 1;
}

UINT_PTR CALLBACK jonesConfig_LoadGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_INITDIALOG:
        {
            return jonesConfig_LoadGameDialogInit(hDlg, wParam, (LPOPENFILENAME)lParam);
        }
        case WM_COMMAND:
        {
            jonesConfig_sub_405F60(hDlg);
            return FALSE;
        }
        case WM_CLOSE:
        {
            DeleteObject(jonesConfig_hFontLoadGameDlg);
            jonesConfig_hFontLoadGameDlg = NULL;
            return FALSE;
        }
        case WM_DESTROY:
        {
            LoadGameDialogData* pData = (LoadGameDialogData*)GetWindowLongPtr(hDlg, DWL_USER);
            DeleteDC(pData->hdcThumbnail);
            DeleteObject(pData->hThumbnail);
            pData->hThumbnail   = NULL;
            pData->hdcThumbnail = NULL;
            return FALSE;
        }
        case WM_PAINT:
        {
            // Fixed: Added full paint logic.
            //       This should fixed painting the file list on windows 11

            PAINTSTRUCT ps;
            /*HDC hdcThumbnail =*/ BeginPaint(hDlg, &ps);

            LoadGameDialogData* pData = (LoadGameDialogData*)GetWindowLongPtr(hDlg, DWL_USER);

            if ( pData && !pData->bFolderSel )
            {
                HWND hThumbnail = GetDlgItem(hDlg, 1163);
                if ( hThumbnail )
                {
                    InvalidateRect(hThumbnail, NULL, TRUE);  // Mark for repaint
                    UpdateWindow(hThumbnail);  // Force immediate repaint
                }
            }

            HWND hIcon = GetDlgItem(hDlg, 1117);
            if ( hIcon )
            {
                InvalidateRect(hIcon, NULL, TRUE);  // Mark for repaint
                UpdateWindow(hIcon);  // Force immediate repaint
            }

            // End painting
            EndPaint(hDlg, &ps);
            return TRUE;
        }
        case WM_NOTIFY:
        {
            LoadGameDialogData* pData = (LoadGameDialogData*)GetWindowLongPtr(hDlg, DWL_USER);
            NMHDR* pNmHdr = (NMHDR*)lParam;
            STDLOG_STATUS("code: %i\n", pNmHdr->code);

            switch ( pNmHdr->code )
            {
                case CDN_FILEOK:
                {
                    OFNOTIFY* pOfNotify = (OFNOTIFY*)lParam;

                    bool bValidFile = false;
                    CHAR aPath[128] = { 0 };
                    LPOPENFILENAME pofn = pOfNotify->lpOFN;
                    if ( pofn->nFileOffset < 0x8000 )
                    {

                        char aExtension[128] = { 0 };
                        STD_FORMAT(aExtension, ".%s", pofn->lpstrDefExt);

                        char aFilename[128] = { 0 };
                        SendMessage(GetParent(hDlg), CDM_GETSPEC, STD_ARRAYLEN(aFilename), (LPARAM)aFilename); // get selected filename

                        char* pStr = strstr(pofn->lpstrFile, aFilename);
                        size_t strLen;
                        if ( pStr )
                        {
                            strLen = pStr - pofn->lpstrFile;
                        }
                        else
                        {
                            strLen = strlen(pofn->lpstrFile);
                        }

                        CHAR aSearchPath[128] = { 0 };
                        STD_STRNCPY(aSearchPath, pofn->lpstrFile, strLen);

                        LPSTR lpFilePart;
                        SearchPath(aSearchPath, aFilename, aExtension, STD_ARRAYLEN(aPath), aPath, &lpFilePart);
                        if ( strlen(aPath) )
                        {
                            bValidFile = true;
                        }

                        if ( strcspn(aFilename, "?*") != strlen(aFilename) )
                        {
                            bValidFile = false;
                        }
                    }

                    const char* pErrorString = NULL;
                    if ( (pofn->nFileOffset < 0x8000) && bValidFile )
                    {
                        if ( strlen(aPath) )
                        {
                            if ( !JonesMain_HasStarted()
                                || (sithPlayer_g_pLocalPlayerThing->flags & SITH_TF_DYING) != 0
                                || (sithPlayer_g_pLocalPlayerThing->flags & SITH_TF_DESTROYED) != 0
                                || jonesConfig_ShowLoadGameWarningMsgBox(hDlg) == 1 )
                            {
                                return FALSE;
                            }

                            SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                            return TRUE;
                        }

                        pErrorString = jonesString_GetString("JONES_STR_NOFILE");
                        if ( !pErrorString )
                        {
                            SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                            return TRUE;
                        }
                    }
                    else
                    {
                        pErrorString = jonesString_GetString("JONES_STR_INVALIDFILE");
                        if ( !pErrorString )
                        {
                            SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                            return TRUE;
                        }
                    }

                    // Get selected filename
                    CHAR aMessage[256]  = { 0 };
                    char aFilename[128] = { 0 };
                    SendMessage(GetParent(hDlg), CDM_GETSPEC, STD_ARRAYLEN(aFilename), (LPARAM)aFilename);
                    STD_FORMAT(aMessage, pErrorString, aFilename);

                    jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_LOADGM", aMessage, 139);
                    SetWindowLongPtr(hDlg, DWL_MSGRESULT, 1);
                    return TRUE;
                }
                case CDN_FOLDERCHANGE:
                {
                    if ( !pData->hThumbnail )
                    {
                        return TRUE;
                    }

                    HWND hDlgItem = GetDlgItem(hDlg, 1163);
                    pData->bFolderSel = 1;

                    InvalidateRect(hDlgItem, NULL, TRUE);
                    UpdateWindow(hDlg);
                    return TRUE;
                }
                case CDN_SELCHANGE:
                {
                    HWND hThumbnail = GetDlgItem(hDlg, 1163);
                    if ( !pData->bFolderSel )
                    {
                        const char* pExt = NULL;
                        SendMessage(GetParent(hDlg), CDM_GETFILEPATH, STD_ARRAYLEN(pData->aFilePath), (LPARAM)pData->aFilePath);
                        if ( strlen(pData->aFilePath) )
                        {
                            pExt = pData->aFilePath + strlen(pData->aFilePath) - 3;
                        }

                        if ( pExt && strcmp(pExt, "nds") == 0 )
                        {
                            // Load thumbnail of newly selected nds file
                            if ( pData->hThumbnail )
                            {
                                DeleteObject(pData->hThumbnail);
                                pData->hThumbnail = NULL;
                            }

                            pData->hThumbnail = sithGamesave_LoadThumbnail(pData->aFilePath);
                        }
                    }

                    InvalidateRect(hThumbnail, NULL, TRUE);
                    UpdateWindow(hDlg);
                    return TRUE;
                }
                case CDN_INITDONE:
                {
                    HWND hBtn = GetDlgItem(hDlg, 1120);
                    SetWindowLongPtr(hBtn, GWL_USERDATA, 159);

                    HWND hIcon = GetDlgItem(hDlg, 1117);
                    SetWindowLongPtr(hIcon, GWL_USERDATA, 159);

                    HWND hThumbnail = GetDlgItem(hDlg, 1163);
                    SetWindowLongPtr(hThumbnail, GWL_USERDATA, 159);
                    InvalidateRect(hThumbnail, NULL, TRUE);

                    static_assert(JONESCONFIG_NOFONTSCALE(159) == 0x45F009F, "");
                    jonesConfig_hFontLoadGameDlg = jonesConfig_InitDialog(GetParent(hDlg), NULL, JONESCONFIG_NOFONTSCALE(159));
                    jonesConfig_hFontLoadGameDlg = jonesConfig_InitDialog(hDlg, jonesConfig_hFontLoadGameDlg, 159);
                    SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
                    return TRUE;
                }

                default:
                    return FALSE;
            }
        }
    };

    return FALSE;
}

LRESULT CALLBACK jonesConfig_LoadGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hwndParent = (HWND)GetWindowLongPtr(hWnd, GWL_HWNDPARENT);
    LoadGameDialogData* pData = (LoadGameDialogData*)GetWindowLongPtr(hwndParent, DWL_USER);
    if ( !pData ) // Fixed: Moved null check to the top
    {
        return 1;
    }

    if ( uMsg != WM_PAINT )
    {
        return CallWindowProc((WNDPROC)pData->pfThubnailProc, hWnd, uMsg, wParam, lParam);
    }

    if ( !pData->hThumbnail )
    {
        return CallWindowProc((WNDPROC)pData->pfThubnailProc, hWnd, uMsg, wParam, lParam); // Added: Should fix rendering of file list on Windows 11
    }

    if ( !pData->bFolderSel )
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, (LPPAINTSTRUCT)&ps);
        SetStretchBltMode(hdc, STRETCH_HALFTONE);
        jonesConfig_DrawImageOnDialogItem(hwndParent, pData->hdcThumbnail, hdc, 1163, pData->hThumbnail, NULL);// 1163 - thumbnail picture edit control
        EndPaint(hWnd, &ps);
        return 0;
    }

    pData->bFolderSel = 0;

    // TODO: useless scope, found only in debug version
#ifdef J3D_DEBUG
    if ( !pData->hThumbnail )
    {
        return CallWindowProc((WNDPROC)pData->pfThubnailProc, hWnd, uMsg, wParam, lParam); // Added: Should fix rendering of file list on Windows 11
    }
#endif

    DeleteObject((HGDIOBJ)pData->hThumbnail);
    pData->hThumbnail = NULL;
    return CallWindowProc((WNDPROC)pData->pfThubnailProc, hWnd, uMsg, wParam, lParam); // Added: Should fix rendering of file list on Windows 11
}

BOOL J3DAPI jonesConfig_LoadGameDialogInit(HWND hDlg, int a2, LPOPENFILENAME pofn)
{
    J3D_UNUSED(a2);

    LoadGameDialogData* pData = (LoadGameDialogData*)pofn->lCustData;

    RECT btnRect;
    HWND hButton = GetDlgItem(hDlg, 1120); // load last saved game button 
    GetWindowRect(hButton, &btnRect);

    HWND hThumbnail = GetDlgItem(hDlg, 1163);
    HDC dc = GetDC(hThumbnail);
    pData->hdcThumbnail = CreateCompatibleDC(dc);

    hThumbnail = GetDlgItem(hDlg, 1163); // ??
    pData->pfThubnailProc = GetWindowLongPtr(hThumbnail, GWL_WNDPROC);

    HWND hIcon = GetDlgItem(hDlg, 1117);

    SetWindowLongPtr(hThumbnail, GWL_WNDPROC, (LONG_PTR)jonesConfig_LoadGameThumbnailPaintProc);
    SetWindowLongPtr(hDlg, DWL_USER, (LONG_PTR)pData);

    RECT dlgWinRect;
    GetWindowRect(hDlg, &dlgWinRect);

    RECT thumbWinRect;
    GetWindowRect(hThumbnail, &thumbWinRect);

    RECT thumbRect;
    GetClientRect(hThumbnail, &thumbRect);

    RECT iconWinRect;
    GetWindowRect(hIcon, &iconWinRect);

    RECT iconRect;
    GetClientRect(hIcon, &iconRect);

    // LONG dlgWidth  = dlgWinRect.right - dlgWinRect.left;
    // LONG dlgHeight = dlgWinRect.bottom - dlgWinRect.top;

     // Changed: Scale the thumb size to DPI
    UINT systemDPI = GetDpiForWindow(hDlg);
    double dpiScale = (double)systemDPI / USER_DEFAULT_SCREEN_DPI;
    LONG tbImageWidth  = (LONG)ceil((double)SITHSAVEGAME_THUMB_WIDTH * dpiScale);
    LONG tbImageHeight = (LONG)ceil((double)SITHSAVEGAME_THUMB_HEIGHT * dpiScale);

    LONG thmbWidth  = thumbRect.left - thumbRect.right + tbImageWidth;
    LONG thmbHeight = thumbRect.top - thumbRect.bottom + tbImageHeight;

    //LONG thumbPosX = thumbWinRect.left - dlgWinRect.left;
    //LONG thumbPosY = thumbWinRect.top - dlgWinRect.top;

    //LONG thumbWinWidth  = thumbWinRect.right - thumbWinRect.left;
    //LONG thumbWinHeight = thumbWinRect.bottom - thumbWinRect.top;

    //LONG thumbTotalWidth = thmbWidth + thumbWinWidth;
    //LONG thumbTotalHeight = thmbHeight + thumbWinHeight;

    if ( thumbRect.left - thumbRect.right == -tbImageWidth && thumbRect.top - thumbRect.bottom == -tbImageHeight )
    {
        return TRUE;
    }

    if ( thumbRect.left - thumbRect.right == -SITHSAVEGAME_THUMB_WIDTH && thumbRect.top - thumbRect.bottom == -SITHSAVEGAME_THUMB_HEIGHT )
    {
        return 1;
    }

    MoveWindow(
        hDlg,
        dlgWinRect.left,
        dlgWinRect.top,
        thmbWidth + dlgWinRect.right - dlgWinRect.left,
        (LONG)ceil(11.0 * dpiScale) + dlgWinRect.bottom - dlgWinRect.top, // Added: Added padding  11 * dpiScale. This should fix drawing all components right of file list
        TRUE
    );

    MoveWindow(
        hThumbnail,
        (thumbWinRect.left - dlgWinRect.left),
        thumbWinRect.top - dlgWinRect.top,
        thmbWidth + thumbWinRect.right - thumbWinRect.left,
        thmbHeight + thumbWinRect.bottom - thumbWinRect.top,
        TRUE
    );

    LONG width = thumbWinRect.right + thmbWidth - thumbWinRect.left;
    MoveWindow(
        hButton,
        thumbWinRect.left - dlgWinRect.left,
        btnRect.top + thmbHeight - dlgWinRect.top,
        width,
        btnRect.bottom - btnRect.top,
        1
    );

    // TODO: dead code as the button is not hooked to any code
    char aPath[128] = { 0 };
    jonesConfig_LoadGameGetLastSavedGamePath(aPath, sizeof(aPath));
    if ( !strlen(aPath) )
    {
        EnableWindow(hButton, 0); // close window if no game was saved yet
    }

    return TRUE;
}

int J3DAPI jonesConfig_ShowGamePlayOptions(HWND hWnd)
{
    GetWindowLongPtr(hWnd, GWL_HINSTANCE); // TODO: useless
    return JonesDialog_ShowDialog(MAKEINTRESOURCEA(112), hWnd, jonesConfig_GamePlayOptionsProc, 0);
}

INT_PTR CALLBACK jonesConfig_GamePlayOptionsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int bProcessed = 1;
    if ( uMsg > WM_INITDIALOG )
    {
        if ( uMsg == WM_COMMAND )
        {
            jonesConfig_GamePlayOptions_HandleWM_COMMAND(hWnd, LOWORD(wParam));
            return 0;
        }

        if ( uMsg != WM_HSCROLL )
        {
            return 0;
        }


        jonesConfig_HandleWM_HSCROLL(hWnd, (HWND)lParam, LOWORD(wParam));

        HWND hDifSlideer = GetDlgItem(hWnd, 1050);   // Difficulty slider control

        const char* pDifficultyStr = NULL;
        int difficulty = SendMessage(hDifSlideer, TBM_GETPOS, 0, 0);
        switch ( difficulty )
        {
            case 0:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD0");
                break;

            case 1:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD1");
                break;

            case 2:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD2");
                break;

            case 3:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD3");
                break;

            case 4:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD4");
                break;

            case 5:
                pDifficultyStr = jonesString_GetString("JONES_STR_HARD5");
                break;

            default:
                break;
        }

        if ( pDifficultyStr )
        {
            HWND hDifText = GetDlgItem(hWnd, 1215); // Difficulty text control
            SetWindowTextA(hDifText, pDifficultyStr);
        }

        return 1;
    }

    if ( uMsg == WM_INITDIALOG )
    {
        // Changed: Change the order of initialization, to first init dialog 
        //          and then do general dialog init which scales the fonts and inits dialog text
        bProcessed = jonesConfig_GamePlayOptionsInitDlg(hWnd);
        jonesConfig_hFontGamePlayOptionsDlg = jonesConfig_InitDialog(hWnd, NULL, 112);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        if ( uMsg != WM_DESTROY )
        {
            return 0;
        }

        jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontGamePlayOptionsDlg);
    }

    return bProcessed;
}

void J3DAPI jonesConfig_HandleWM_HSCROLL(HWND hDlg, HWND hWnd, uint16_t sbValue)
{
    J3D_UNUSED(hDlg);

    const int maxPos = SendMessage(hWnd, TBM_GETRANGEMAX, 0, 0);
    const int minPos = SendMessage(hWnd, TBM_GETRANGEMIN, 0, 0);
    const int curPos = SendMessage(hWnd, TBM_GETPOS, 0, 0);
    SendMessage(hWnd, TBM_GETPAGESIZE, 0, 0);  // ???

    int newPos = -1;
    switch ( sbValue )
    {
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            newPos = curPos;
            break;

        case SB_LEFT:
            newPos = minPos;
            break;

        case SB_RIGHT:
            newPos = maxPos;
            break;

        default:
            break;
    }

    if ( newPos >= 0 )
    {
        SendMessage(hWnd, TBM_SETPOS, /*redraw=*/1u, newPos);
    }
}

int J3DAPI jonesConfig_GamePlayOptionsInitDlg(HWND hDlg)
{
    // Shot Text option
    HWND hCBShowText = GetDlgItem(hDlg, 1052);
    int bShowText = sithVoice_GetShowText();
    SendMessage(hCBShowText, BM_SETCHECK, bShowText, 0);

    // Show Hints option
    HWND hCBShowHints = GetDlgItem(hDlg, 1051);
    int bShowHints = sithOverlayMap_GetShowHints();
    SendMessage(hCBShowHints, BM_SETCHECK, bShowHints, 0);

    // RotateMap option
    HWND hCBRotateMap = GetDlgItem(hDlg, 1204);
    int  bRotateMap = sithOverlayMap_GetMapRotation();
    SendMessage(hCBRotateMap, BM_SETCHECK, bRotateMap, 0);

    // Default to Run option
    CheckDlgButton(hDlg, 1202, jonesConfig_bDefaultRun);// CB default run

    // Added: Check box "High Poly Objects"
    // Get the position of the base checkbox
    RECT rectCBShowText;
    GetWindowRect(hCBShowText, &rectCBShowText);

    // Convert screen coordinates to client coordinates
    POINT pt = { rectCBShowText.left, rectCBShowText.top };
    ScreenToClient(hDlg, &pt);

    // Calculate the position for the new checkbox
    int x = pt.x;
    int y = pt.y + (rectCBShowText.bottom - rectCBShowText.top) + 14;

    // Create the checkbox
    HWND hCBHiPoly = CreateWindow(
        "BUTTON",               // Class name for button/checkbox
        "JONES_STR_HIPOLY",     // Text displayed on the checkbox
        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        x,
        y,
        150,                   // Width
        20,                    // Height
        hDlg,                  // Parent window handle (the dialog)
        (HMENU)1053,           // Control ID
        GetModuleHandle(NULL), // Instance handle
        NULL                   // Additional creation data
    );
    J3D_UNUSED(hCBHiPoly);

    CheckDlgButton(hDlg, 1053, sithModel_IsHiPolyEnabled());

    // Difficulty slider and text
    HWND hDifSlider = GetDlgItem(hDlg, 1050); // Difficulty slider control

    size_t maxDifficulty = jonesInventory_GetMaxDifficultyLevel();
    SendMessage(hDifSlider, TBM_SETRANGE, 1u, (uint16_t)maxDifficulty << 16);// LWORD is min and HIWORD is max range

    int curDifficulty = sithGetGameDifficulty();
    SendMessage(hDifSlider, TBM_SETPOS, 1u, curDifficulty);

    SendMessage(hDifSlider, TBM_SETTICFREQ, 1u, 0);
    SendMessage(hDifSlider, TBM_SETPAGESIZE, 0, 1);

    const char* pDifficultyStr = NULL;
    switch ( sithGetGameDifficulty() )
    {
        case 0:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD0");
            break;

        case 1:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD1");
            break;

        case 2:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD2");
            break;

        case 3:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD3");
            break;

        case 4:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD4");
            break;

        case 5:
            pDifficultyStr = jonesString_GetString("JONES_STR_HARD5");
            break;

        default:
            break;
    }

    if ( pDifficultyStr )
    {
        HWND  hDifText = GetDlgItem(hDlg, 1215); // Difficulty text control
        SetWindowTextA(hDifText, pDifficultyStr);
    }


    // Added: Resize dialog to fit in new check box
    RECT rectDlg;
    GetWindowRect(hDlg, &rectDlg);
    SetWindowPos(hDlg, NULL, 0, 0, rectDlg.right - rectDlg.left, (rectDlg.bottom - rectDlg.top) + 28, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

    // Added: Move OK & Cancel buttons down
    HWND hBtnOk     = GetDlgItem(hDlg, 1);
    RECT rectBtnOk;
    GetWindowRect(hBtnOk, &rectBtnOk);
    POINT ptBtnOk = { rectBtnOk.left, rectBtnOk.top + (rectBtnOk.bottom - rectBtnOk.top) / 2 + 14 };
    ScreenToClient(hDlg, &ptBtnOk);
    SetWindowPos(hBtnOk, NULL, ptBtnOk.x, ptBtnOk.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

    HWND hBtnCancel = GetDlgItem(hDlg, 2);
    RECT rectBtnCancel;
    GetWindowRect(hBtnCancel, &rectBtnCancel);
    POINT ptBtnCancel = { rectBtnCancel.left, rectBtnCancel.top + (rectBtnCancel.bottom - rectBtnCancel.top) / 2 + 14 };
    ScreenToClient(hDlg, &ptBtnCancel);
    SetWindowPos(hBtnCancel, NULL, ptBtnCancel.x, ptBtnCancel.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

    return 1;
}

void J3DAPI jonesConfig_GamePlayOptions_HandleWM_COMMAND(HWND hDlg, uint16_t controlID)
{
    if ( controlID == 1 ) // OK
    {
        // Get & save show text option
        HWND hCBShowText = GetDlgItem(hDlg, 1052);
        int bShowText = SendMessage(hCBShowText, BM_GETSTATE, 0, 0);
        sithVoice_ShowText(bShowText);

        bShowText = sithVoice_GetShowText();
        wuRegistry_SaveIntEx("Show Text", bShowText);

        // Get & save map rotation option
        HWND hCBMapRotate = GetDlgItem(hDlg, 1204);
        int bRotateMap = SendMessage(hCBMapRotate, BM_GETSTATE, 0, 0);
        sithOverlayMap_EnableMapRotation(bRotateMap);

        bRotateMap = sithOverlayMap_GetMapRotation();
        wuRegistry_SaveIntEx("Map Rotation", bRotateMap);
        // Get & save show hint option
        HWND hCBShowHints = GetDlgItem(hDlg, 1051);
        int bShowHints = SendMessage(hCBShowHints, BM_GETSTATE, 0, 0);
        sithOverlayMap_SetShowHints(bShowHints);

        bShowHints = sithOverlayMap_GetShowHints();
        wuRegistry_SaveIntEx("Show Hints", bShowHints);
        // Get & save difficulty
        HWND hDifSlideer = GetDlgItem(hDlg, 1050);
        int difficulty = SendMessage(hDifSlideer, TBM_GETPOS, 0, 0);
        sithSetGameDifficulty(difficulty);

        difficulty = sithGetGameDifficulty();
        wuRegistry_SaveInt("Difficulty", difficulty);

        // Get & save default to run option
        HWND hCBRun = GetDlgItem(hDlg, 1202);
        jonesConfig_bDefaultRun = SendMessage(hCBRun, BM_GETCHECK, 0, 0);
        wuRegistry_SaveIntEx("Default Run", jonesConfig_bDefaultRun);

        if ( jonesConfig_bDefaultRun )
        {
            sithControl_g_controlOptions |= 0x02;
        }
        else
        {
            sithControl_g_controlOptions &= ~0x02;
        }

        // Added
        // Get & save HiPoly option
        int bCurBHiPoly = sithModel_IsHiPolyEnabled();

        int bHiPoly = IsDlgButtonChecked(hDlg, 1053);
        sithModel_EnableHiPoly(bHiPoly);
        wuRegistry_SaveIntEx("HiPoly", bHiPoly);

        if ( (bHiPoly != 0) != (bCurBHiPoly != 0) )
        {
            const char* pNoteStr = jonesString_GetString("JONES_STR_HIPOLYGO");
            if ( pNoteStr ) {
                pNoteStr = "You must quit and restart the game for the high poly option to take effect.";
            }
            jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_GMPLY_OPTS", pNoteStr, 137);
        }

        // Close dialog
        EndDialog(hDlg, controlID);
    }

    if ( controlID == 2 ) //  CANCEL
    {
        EndDialog(hDlg, controlID);
    }
}

void J3DAPI jonesConfig_EnableMouseControl(int bEnable)
{
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( bEnable )
    {
        sithControl_RebindMouse();
    }

    else if ( pSettings->bWindowMode )
    {
        stdControl_EnableMouse(0);
    }
    else
    {
        sithControl_UnbindMouseAxes();
        stdControl_EnableMouse(1);
    }
}

void jonesConfig_UpdateCurrentLevelNum(void)
{
    jonesConfig_curLevelNum = JonesMain_GetCurrentLevelNum();
}


int J3DAPI jonesConfig_DrawImageOnDialogItem(HWND hDlg, HDC hdcWnd, HDC hdcCtrl, int nIDDlgItem, HBITMAP hImage, HBITMAP hMask)
{
    RECT rect;
    HWND hDlgItem = GetDlgItem(hDlg, nIDDlgItem);
    GetClientRect(hDlgItem, &rect);

    BITMAP bmp;
    GetObject(hImage, sizeof(BITMAP), &bmp);

    if ( hMask )
    {
        SelectObject(hdcWnd, (HGDIOBJ)hMask);
        StretchBlt(hdcCtrl, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcWnd, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);

        SelectObject(hdcWnd, (HGDIOBJ)hImage);
        return StretchBlt(hdcCtrl, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcWnd, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCPAINT);
    }
    else
    {
        SelectObject(hdcWnd, (HGDIOBJ)hImage);
        return StretchBlt(hdcCtrl, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcWnd, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
    }
}

void J3DAPI jonesConfig_DrawStatisticDialogIQPoints(HWND hwnd, JonesDialogImageInfo** ppImageInfo, int dlgID, int iqpoints)
{
    J3D_UNUSED(hwnd);
    J3D_UNUSED(dlgID);

    JonesDialogImageInfo* pImageInfo = *ppImageInfo;
    if ( pImageInfo->hBmp )
    {
        DeleteObject((HGDIOBJ)pImageInfo->hBmp);
        pImageInfo->hBmp = 0;
    }

    SelectObject(pImageInfo->hdcFront, (HGDIOBJ)jonesConfig_apDialogIcons[0]);
    BitBlt(pImageInfo->hdcFront, 39, 207, 127, 46, NULL, 0, 0, BLACKNESS);

    // TODO: add iqoverlay.bmp (icons[2])

    SelectObject(pImageInfo->hdcFront, (HGDIOBJ)jonesConfig_apDialogIcons[1]);
    BitBlt(pImageInfo->hdcFront, 39, 207, 127, 46, NULL, 0, 0, WHITENESS);

    if ( iqpoints < 0 ) {
        iqpoints = 0;
    }

    int points = iqpoints;

    // Calculate required width/height
    int width = 0, height = 0;
    while ( iqpoints >= 0 )
    {
        int digit = iqpoints % 10;
        iqpoints /= 10;
        if ( !iqpoints )
        {
            iqpoints = -1;
        }

        width += jonesConfig_aNumberGlyphMetrics[digit].right - jonesConfig_aNumberGlyphMetrics[digit].left + 1;
        if ( jonesConfig_aNumberGlyphMetrics[digit].bottom - jonesConfig_aNumberGlyphMetrics[digit].top + 1 > height )
        {
            height = jonesConfig_aNumberGlyphMetrics[digit].bottom - jonesConfig_aNumberGlyphMetrics[digit].top + 1;
        }
    }

    BITMAPINFO bmi              = { 0 };
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = width;
    bmi.bmiHeader.biHeight      = -height;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 24;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = 3 * height * width;

    void* ppvBits;
    HBITMAP hBmp = CreateDIBSection(pImageInfo->hdcBack, &bmi, DIB_RGB_COLORS, &ppvBits, NULL, 0);
    pImageInfo->hBmp = hBmp;

    SelectObject(pImageInfo->hdcBack, (HGDIOBJ)pImageInfo->hBmp);
    SelectObject(pImageInfo->hdcFront, (HGDIOBJ)jonesConfig_apDialogIcons[3]); // 3 - numbers bmp

    RECT rc = { 0 };
    rc.bottom = height;
    rc.right  = width;

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(pImageInfo->hdcBack, &rc, hBrush);


    int x = width;
    while ( points >= 0 )
    {
        int digit = points % 10;
        points /= 10;
        if ( !points )
        {
            points = -1;
        }

        x -= jonesConfig_aNumberGlyphMetrics[digit].right - jonesConfig_aNumberGlyphMetrics[digit].left + 1;
        BitBlt(
            pImageInfo->hdcBack,
            x,
            0,
            jonesConfig_aNumberGlyphMetrics[digit].right - jonesConfig_aNumberGlyphMetrics[digit].left + 1,
            jonesConfig_aNumberGlyphMetrics[digit].bottom - jonesConfig_aNumberGlyphMetrics[digit].top + 1,
            pImageInfo->hdcFront,
            jonesConfig_aNumberGlyphMetrics[digit].left,
            jonesConfig_aNumberGlyphMetrics[digit].top,
            SRCCOPY
        );
    }

    x = (127 - width) / 2 + 39;
    int y = (46 - height) / 2 + 207;

    // Draw IQ bmp
    SelectObject(pImageInfo->hdcFront, (HGDIOBJ)jonesConfig_apDialogIcons[0]);
    BitBlt(pImageInfo->hdcFront, x, y, width, height, pImageInfo->hdcBack, 0, 0, SRCAND);

    // Draw IQ mask bmp
    SelectObject(pImageInfo->hdcFront, (HGDIOBJ)jonesConfig_apDialogIcons[1]);
    BitBlt(pImageInfo->hdcFront, x, y, width, height, pImageInfo->hdcBack, 0, 0, SRCCOPY);
}

int J3DAPI jonesConfig_ShowLevelCompletedDialog(HWND hWnd, int* pBalance, int* apItemsState, int a4, int elapsedTime, int qiPoints, int numFoundTrasures, int foundTrasureValue, int totalTreasureValue)
{
    tLevelCompletedDialogState state = { 0 };
    state.balance            = pBalance;
    state.apItemsState       = apItemsState;
    state.unknown2           = a4;
    state.elapsedTime        = elapsedTime;
    state.iqPoints           = qiPoints;
    state.numFoundTrasures   = numFoundTrasures;
    state.foundTreasureValue = foundTrasureValue;
    state.totalTreasureValue = totalTreasureValue;
    state.pStatistics        = sithGamesave_GetGameStatistics();

    if ( !state.pStatistics || !sithGamesave_LockGameStatistics() )
    {
        return jonesConfig_ShowStoreDialog(hWnd, pBalance, apItemsState, a4);
    }

    JonesDialogImageInfo imageInfo = { 0 };
    state.pIQImageInfo = &imageInfo;

    int result = JonesDialog_ShowDialog(MAKEINTRESOURCEA(233), hWnd, jonesConfig_LevelCompletedDialogProc, (LPARAM)&state);
    *pBalance  = *state.balance;
    sithGamesave_UnlockGameStatistics();
    return result;
}

int CALLBACK jonesConfig_LevelCompletedDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_INITDIALOG:
        {
            jonesConfig_hFontLevelCopletedDialog = jonesConfig_InitDialog(hWnd, 0, 233);
            int result  = jonesConfig_InitLevelCompletedDialog(hWnd, wParam, (tLevelCompletedDialogState*)lParam);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return result;
        }
        case WM_COMMAND:
            jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND(hWnd, (uint16_t)wParam);
            return 0;

        case WM_DESTROY:
            jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontLevelCopletedDialog);
            return 1;

        // Removed: The IQ bmp and qi points are drawn in WM_DRAWITEM; fixes drawing the bitmaps
        //case WM_PAINT:
        //{
        //    tLevelCompletedDialogState* pState = (tLevelCompletedDialogState*)GetWindowLongPtr(hWnd, DWL_USER);
        //    HWND hImgCtrl = GetDlgItem(hWnd, 1135);
        //    PAINTSTRUCT paint = { 0 }; // Added: Init to 0
        //    HDC hdcImg = BeginPaint(hWnd, (LPPAINTSTRUCT)&paint);
        //
        //    SetStretchBltMode(hdcImg, STRETCH_HALFTONE);
        //    jonesConfig_DrawImageOnDialogItem(hWnd, pState->pIQImageInfo->hdcFront, hdcImg, 1135, jonesConfig_apDialogIcons[0], jonesConfig_apDialogIcons[1]);//   "iq.bmp" "iqMask.bmp"
        //
        //    EndPaint(hWnd, &paint);
        //    return 0;
        //}

        // Added: Fixes drawing of IQ bmp and iq points. Note, jonesConfig_InitLevelCompletedDialog sets picture control 1135 to be drawn by dialog
        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
            if ( pdis->CtlID == 1135 )
            {
                tLevelCompletedDialogState* pState = (tLevelCompletedDialogState*)GetWindowLongPtr(hWnd, DWL_USER);
                SetStretchBltMode(pdis->hDC, STRETCH_HALFTONE);
                jonesConfig_DrawImageOnDialogItem(hWnd, pState->pIQImageInfo->hdcFront, pdis->hDC, 1135, jonesConfig_apDialogIcons[0], jonesConfig_apDialogIcons[1]); //  "iq.bmp" "iqMask.bmp"
                return TRUE;
            }
            return FALSE;
        }

        default:
            return 0;
    };
}

int J3DAPI jonesConfig_InitLevelCompletedDialog(HWND hDlg, int wParam, tLevelCompletedDialogState* pState)
{
    J3D_UNUSED(wParam);

    HWND DlgItem;
    HDC DC;

    HWND hImgCtrl = GetDlgItem(hDlg, 1135);

    // Added: Make hImgCtrl to be drawn by hDlg -> WM_DRAWITEM
    LONG style = GetWindowLong(hImgCtrl, GWL_STYLE);
    SetWindowLong(hImgCtrl, GWL_STYLE, style | SS_OWNERDRAW);

    pState->pIQImageInfo->hdcFront = CreateCompatibleDC(GetDC(hImgCtrl));

    DlgItem = GetDlgItem(hDlg, 1135);           // ??
    DC = GetDC(DlgItem);
    pState->pIQImageInfo->hdcBack = CreateCompatibleDC(DC);

    jonesConfig_prevLevelNum = pState->pStatistics->curLevelNum - 1;
    jonesConfig_DrawStatisticDialogIQPoints(hDlg, &pState->pIQImageInfo, 233, pState->pStatistics->aLevelStatistic[jonesConfig_prevLevelNum].iqPoints);

    CHAR aText[256] = { 0 };

    int hours = pState->elapsedTime >> 8;
    int minutes = (hours << 8) ^ pState->elapsedTime;

    if ( minutes >= 10 )
    {
        STD_FORMAT(aText, "%i : %i ", hours, minutes);
    }
    else
    {
        STD_FORMAT(aText, "%i : 0%i ", hours, minutes);
    }

    SetWindowText(GetDlgItem(hDlg, 1153), aText);

    memset(aText, 0, sizeof(aText));
    STD_FORMAT(aText, "%i ", pState->iqPoints);
    SetWindowText(GetDlgItem(hDlg, 1154), aText);

    memset(aText, 0, sizeof(aText));
    STD_FORMAT(aText, "%i ", pState->numFoundTrasures);
    SetWindowText(GetDlgItem(hDlg, 1155), aText);

    memset(aText, 0, sizeof(aText));
    STD_FORMAT(aText, "%i ", pState->foundTreasureValue);
    SetWindowText(GetDlgItem(hDlg, 1157), aText);

    memset(aText, 0, sizeof(aText));
    STD_FORMAT(aText, "%i ", pState->totalTreasureValue);
    SetWindowText(GetDlgItem(hDlg, 1156), aText);

    SetWindowLongPtr(hDlg, DWL_USER, (LONG)pState);
    return 1;
}

void J3DAPI jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND(HWND hWnd, int wParam)
{
    tLevelCompletedDialogState* pState = (tLevelCompletedDialogState*)GetWindowLongPtr(hWnd, DWL_USER);
    if ( wParam > 0 && wParam <= 2 ) // 1 or 2 - done
    {
        DeleteObject((HGDIOBJ)pState->pIQImageInfo->hBmp);
        pState->pIQImageInfo->hBmp = NULL;

        DeleteDC(pState->pIQImageInfo->hdcFront);
        DeleteDC(pState->pIQImageInfo->hdcBack);

        // Show store dialog if not bonus level
        if ( pState->pStatistics->curLevelNum + 1 < JONESLEVEL_BONUSLEVELNUM )
        {
            jonesConfig_ShowStoreDialog(hWnd, pState->balance, pState->apItemsState, pState->unknown2);
        }

        InvalidateRect(hWnd, NULL, TRUE);
        EndDialog(hWnd, wParam);
    }
}

int J3DAPI jonesConfig_ShowStoreDialog(HWND hWnd, int* pBalance, int* pItemsState, int a4)
{
    tStoreCartState cart = { 0 };
    cart.balance         = *pBalance;
    cart.apItemsState    = pItemsState;
    cart.unknown20       = a4;

    int result = JonesDialog_ShowDialog(MAKEINTRESOURCEA(190), hWnd, jonesConfig_StoreDialogProc, (LPARAM)&cart);
    *pBalance  = cart.balance;
    return result;
}

int CALLBACK jonesConfig_StoreDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch ( msg )
    {
        case WM_INITDIALOG:
            jonesConfig_hFontStoreDialog = jonesConfig_InitDialog(hwnd, 0, 190);
            int result = jonesConfig_InitStoreDialog(hwnd, wparam, (tStoreCartState*)lparam);
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return result;

        case WM_COMMAND:
            jonesConfig_StoreDialog_HandleWM_COMMAND(hwnd, (uint16_t)wparam);
            return 0;

        case WM_MOUSEFIRST:
            jonesConfig_StoreDialog_HandleWM_MOUSEFIRST(hwnd);
            return 1;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            jonesConfig_StoreDialog_HandleWM_MBUTTONUP(hwnd);
            return 1;

        case WM_NOTIFY:
        {
            tStoreCartState* pCart = (tStoreCartState*)GetWindowLongPtr(hwnd, DWL_USER);
            switch ( ((LPNMHDR)lparam)->code )
            {
                case LVN_BEGINDRAG:
                case LVN_BEGINRDRAG:
                {
                    // Note, lparam is NMLISTVIEW struct here
                    pCart->dragListId = ((LPNMHDR)lparam)->idFrom;
                    jonesConfig_StoreHandleDragEvent(hwnd, GetDlgItem(hwnd, pCart->dragListId));
                } break;
                case NM_DBLCLK:
                {
                    // If double mouse button click, add or remove item to cart based on which list item was clicked
                    if ( ((LPNMHDR)lparam)->idFrom == 1005 ) // available list editor
                    {
                        jonesConfig_AddStoreCartItem(hwnd, pCart);
                    }
                    else if ( ((LPNMHDR)lparam)->idFrom == 1006 ) // cart items list editor
                    {
                        jonesConfig_RemoveStoreCartItem(hwnd, pCart);
                    }
                }
            };
        } return 1;

        case WM_DESTROY:
            jonesConfig_ResetDialogFont(hwnd, jonesConfig_hFontStoreDialog);
            return 1;

        default:
            return 0;
    }
}

int J3DAPI jonesConfig_StoreHandleDragEvent(HWND hwnd, HWND hDlgCtrl)
{
    tStoreCartState* pCart = (tStoreCartState*)GetWindowLongPtr(hwnd, DWL_USER);
    UINT numSelected = ListView_GetSelectedCount(hDlgCtrl);

    SetCapture(hwnd);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    RECT dlgRect, wndRect;
    GetWindowRect(hDlgCtrl, &dlgRect);
    GetWindowRect(hwnd, &wndRect);

    int itemIdx   = -1;
    RECT itemRect = { 0 }; // Added: init to 0
    for ( UINT i = 0; i < numSelected; ++i )
    {
        itemIdx = ListView_GetNextItem(hDlgCtrl, itemIdx, LVNI_SELECTED);
        ListView_GetItemRect(hDlgCtrl, itemIdx, &itemRect, LVIR_SELECTBOUNDS);

        LONG dragX = cursorPos.x - (dlgRect.left + itemRect.left);
        LONG dragY = cursorPos.y - (dlgRect.top + itemRect.top);

        LVITEMA item;
        item.mask     = LVIF_PARAM;
        item.iSubItem = 0;
        item.iItem    = itemIdx;
        ListView_GetItem(hDlgCtrl, &item);

        int imageIdx = HIWORD(item.lParam);

        HIMAGELIST hList = ListView_GetImageList(hDlgCtrl, LVSIL_SMALL);
        if ( !ImageList_BeginDrag(hList, imageIdx, dragX, dragY) )
        {
            ImageList_EndDrag();
            ImageList_DragLeave(hwnd);
            int result = ReleaseCapture();
            pCart->bDragging = 0;
            return result;
        }
    }

    int result = ImageList_DragEnter(hwnd, cursorPos.x - wndRect.left, cursorPos.y - wndRect.top);
    pCart->bDragging = 1;
    return result;
}

void J3DAPI jonesConfig_StoreDialog_HandleWM_MBUTTONUP(HWND hWnd)
{
    tStoreCartState* pCart = (tStoreCartState*)GetWindowLongPtr(hWnd, DWL_USER);
    if ( pCart->bDragging )
    {
        ImageList_EndDrag();
        ImageList_DragLeave(hWnd);

        POINT cursorPos;
        GetCursorPos(&cursorPos);

        RECT rect;
        HWND dlgItem = GetDlgItem(hWnd, 1006);
        GetWindowRect(dlgItem, &rect);

        if ( PtInRect(&rect, cursorPos) && pCart->dragListId == 1005 )// available items list
        {
            jonesConfig_AddStoreCartItem(hWnd, pCart);
        }
        else
        {
            HWND hItemsDialog = GetDlgItem(hWnd, 1005);
            GetWindowRect(hItemsDialog, &rect);
            if ( PtInRect(&rect, cursorPos) )
            {
                if ( pCart->dragListId == 1006 )// cart list
                {
                    jonesConfig_RemoveStoreCartItem(hWnd, pCart);
                }
            }
        }

        pCart->bDragging = 0;
        ReleaseCapture();
    }
}


BOOL J3DAPI jonesConfig_StoreDialog_HandleWM_MOUSEFIRST(HWND hWnd)
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    RECT rect;
    GetWindowRect(hWnd, &rect);
    return ImageList_DragMove(cursorPos.x - rect.left, cursorPos.y - rect.top);
}

int J3DAPI jonesConfig_InitStoreDialog(HWND hDlg, int a2, tStoreCartState* pCart)
{
    J3D_UNUSED(a2);

    HWND hAvailableList = GetDlgItem(hDlg, 1005);
    HWND hCartList      = GetDlgItem(hDlg, 1006);
    HWND hCurrentList   = GetDlgItem(hDlg, 1199);
    if ( !jonesConfig_StoreInitItemIcons(hDlg, pCart) )
    {
        return 0;
    }

    ListView_SetImageList(hAvailableList, pCart->hList, LVSIL_SMALL);
    ListView_SetImageList(hCartList, pCart->hList, LVSIL_SMALL);
    ListView_SetImageList(hCurrentList, pCart->hList, LVSIL_SMALL);

    jonesConfig_StoreSetListColumns(hAvailableList, "JONES_STR_COST");
    jonesConfig_StoreSetListColumns(hCartList, "JONES_STR_COST");
    jonesConfig_StoreSetListColumns(hCurrentList, "JONES_STR_COUNT");

    jonesConfig_StoreInitItemList(hCurrentList, pCart->apItemsState, 1199);
    jonesConfig_StoreInitItemList(hAvailableList, pCart->apItemsState, 1005);

    if ( ListView_GetItemCount(hCurrentList) > ListView_GetCountPerPage(hCurrentList) )
    {
        int colWidth = ListView_GetColumnWidth(hCurrentList, 0);
        int vscrlWidth = GetSystemMetrics(SM_CXVSCROLL);
        ListView_SetColumnWidth(hCurrentList, 0, colWidth - vscrlWidth);
    }

    if ( ListView_GetItemCount(hAvailableList) > ListView_GetCountPerPage(hAvailableList) )
    {
        int colWidth   = ListView_GetColumnWidth(hAvailableList, 0);
        int vscrlWidth = GetSystemMetrics(SM_CXVSCROLL);
        ListView_SetColumnWidth(hAvailableList, 0, colWidth - vscrlWidth);
    }

    pCart->total         = 0;
    pCart->cartListWidth = ListView_GetColumnWidth(hCartList, 0);
    jonesConfig_UpdateBalances(hDlg, pCart);

    SetWindowLongPtr(hDlg, DWL_USER, (LONG_PTR)pCart);
    return 1;
}

int J3DAPI jonesConfig_StoreInitItemIcons(HWND hWnd, tStoreCartState* pCart)
{
    pCart->hList = ImageList_Create(48, 48, ILC_MASK | ILC_COLOR8, STD_ARRAYLEN(JonesHud_aStoreItems), 0); // Changed icon size to 48 from 16
    if ( !pCart->hList )
    {
        return 0;
    }

    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);
    int result = hInstance != NULL;
    for ( size_t i = 0; i < STD_ARRAYLEN(JonesHud_aStoreItems); ++i )
    {
        pCart->aItemIcons[i] = LoadIconA(hInstance, MAKEINTRESOURCEA(JonesHud_aStoreItems[i].iconID));
        result = ImageList_ReplaceIcon(pCart->hList, -1, pCart->aItemIcons[i]);
    }

    return result;
}

LRESULT J3DAPI jonesConfig_StoreSetListColumns(HWND hList, const char* pColumnName)
{
    LVCOLUMNA col = { 0 }; // Added: Init to 0
    col.mask       = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    col.cchTextMax = 256;

    uint32_t  height, width;
    stdDisplay_GetBackBufferSize(&width, &height);

    // Removed: 
  /*float scale = 1.0f;
    if ( (float)height / RD_REF_HEIGHT <= 1.0f )
    {
        scale = (float)height / RD_REF_HEIGHT;
    }*/
    float scale = RD_REF_APECTRATIO / (width / height); // Added: Fixes scaling issue on 16:9 ...
    int pad = (int)(50.0f * scale); // Changed: Change padding to 50 from 40 due to bigger font size
    int colNum = 0;

    RECT rect;
    GetClientRect(hList, &rect);

    col.fmt      = LVCFMT_LEFT;
    col.cx       = rect.right - rect.left - pad;
    col.pszText  = (LPSTR)jonesString_GetString("JONES_STR_ITEMNAME");
    col.iSubItem = colNum;
    ListView_InsertColumn(hList, colNum++, &col);


    col.fmt      = LVCFMT_RIGHT;
    col.cx       = pad;
    col.pszText  = (LPSTR)jonesString_GetString(pColumnName);
    col.iSubItem = colNum;
    return ListView_InsertColumn(hList, colNum, &col);
}

void J3DAPI jonesConfig_StoreInitItemList(HWND hWnd, int* apItemsState, int listID)
{
    LVITEM newItem;
    newItem.mask       = LVIF_STATE | LVIF_PARAM | LVIF_IMAGE | LVIF_TEXT;
    newItem.cchTextMax = 256; // must match aCost
    newItem.state      = 0;
    newItem.stateMask  = 0;

    int imageIdx = 0;
    for ( size_t i = 0; i < STD_ARRAYLEN(JonesHud_aStoreItems); ++i )
    {
        if ( listID == 1005 ) //  available items list
        {
            if ( (apItemsState[i] & 0xF) != 0 ) // if item is available
            {
                newItem.iItem    = imageIdx;
                newItem.iSubItem = 0;
                newItem.pszText  = (LPSTR)jonesString_GetString(JonesHud_aStoreItems[i].aClipName);
                newItem.iImage   = i;
                newItem.lParam   = JonesHud_aStoreItems[i].price | (i << 16);
                ListView_InsertItem(hWnd, &newItem);

                char aCost[256];
                STD_FORMAT(aCost, "%d", JonesHud_aStoreItems[i].price);
                ListView_SetItemText(hWnd, imageIdx++, 1, aCost);
            }

            apItemsState[i] &= ~0xFFFFu;
        }
        else if ( listID == 1199 ) // current inventory list
        {
            if ( (apItemsState[i] & 0xFFF0) >> 4 )
            {
                newItem.iItem    = imageIdx;
                newItem.iSubItem = 0;
                newItem.pszText  = (LPSTR)jonesString_GetString(JonesHud_aStoreItems[i].aName);
                newItem.iImage   = i;
                ListView_InsertItem(hWnd, &newItem);

                char aAmount[256];
                STD_FORMAT(aAmount, "%d", (apItemsState[i] & 0xFFF0) >> 4);// extracts amount
                ListView_SetItemText(hWnd, imageIdx++, 1, aAmount);
            }
        }
    }
}

void J3DAPI jonesConfig_UpdateBalances(HWND hDlg, tStoreCartState* pCart)
{
    CHAR aText[256] = { 0 };
    STD_FORMAT(aText, "%i ", pCart->total);

    HWND hTotalCtrl = GetDlgItem(hDlg, 1173); // total cost
    SetWindowTextA(hTotalCtrl, aText);

    memset(aText, 0, sizeof(aText));
    STD_FORMAT(aText, "%i ", pCart->balance);

    HWND hBalanceCtrl = GetDlgItem(hDlg, 1174); // balance
    SetWindowTextA(hBalanceCtrl, aText);
}

void J3DAPI jonesConfig_AddStoreCartItem(HWND hDlg, tStoreCartState* pCart)
{
    HWND hItemsList = GetDlgItem(hDlg, 1005);        // available items list
    UINT selectedCount = ListView_GetSelectedCount(hItemsList);
    if ( selectedCount )
    {
        int total = 0;
        int itemIdx = -1;
        int bonusMapItemIdx = -1;
        for ( UINT i = 0; i < selectedCount; ++i )
        {
            itemIdx = ListView_GetNextItem(hItemsList, itemIdx, LVNI_SELECTED);

            LVITEM lvitem   = { 0 }; // Added: init to 0
            lvitem.mask     = LVIF_PARAM;
            lvitem.iSubItem = 0;
            lvitem.iItem    = itemIdx;
            ListView_GetItem(hItemsList, &lvitem);

            int storeItemIdx = HIWORD(lvitem.lParam);//  HIWORD
            if ( storeItemIdx > -1 ) // Fixed: Added check for bonusMapItemIdx > -1 
            {
                if ( JonesHud_aStoreItems[storeItemIdx].menuID == JONESHUD_MENU_INVITEM_BONUSMAP )
                {
                    bonusMapItemIdx = storeItemIdx;
                }

                total += JonesHud_aStoreItems[storeItemIdx].price;
            }
        }

        if ( pCart->balance >= total )
        {
            if ( bonusMapItemIdx > -1 && JonesHud_aStoreItems[bonusMapItemIdx].menuID == JONESHUD_MENU_INVITEM_BONUSMAP ) // Fixed: Added check for bonusMapItemIdx > -1 
            {
                const char* pDlgText = jonesString_GetString("JONES_STR_PERU");
                if ( pDlgText )
                {
                    jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_STORE", pDlgText, 191);
                    InvalidateRect(hDlg, 0, 1);
                }
            }

            itemIdx = -1;
            for ( UINT i = 0; i < selectedCount; ++i )
            {
                // Get item from available item list
                itemIdx = ListView_GetNextItem(hItemsList, itemIdx, LVNI_SELECTED);

                char aItemText[256] = { 0 };
                LVITEM item     = { 0 }; // Added: Init to 0
                item.mask       = LVIF_PARAM | LVIF_TEXT;
                item.iSubItem   = 0;
                item.iItem      = itemIdx;
                item.pszText    = aItemText;
                item.cchTextMax = STD_ARRAYLEN(aItemText);
                ListView_GetItem(hItemsList, &item);

                // Add item to purchase list
                int itemStateIdx = HIWORD(item.lParam); // See jonesConfig_StoreInitItemList

                HWND hCartList  = GetDlgItem(hDlg, 1006);// cart list
                item.mask      = LVIF_STATE | LVIF_PARAM | LVIF_IMAGE | LVIF_TEXT;
                item.state     = 0;
                item.stateMask = 0;
                item.iImage    = itemStateIdx;
                item.iItem     = ListView_GetItemCount(hCartList);
                ListView_InsertItem(hCartList, &item);

                // Set item in cart
                memset(aItemText, 0, sizeof(aItemText));
                ListView_GetItemText(hItemsList, itemIdx, 1, aItemText, STD_ARRAYLEN(aItemText));
                ListView_SetItemText(hCartList, item.iItem, 1, aItemText);

                int numItems = pCart->apItemsState[itemStateIdx];
                pCart->apItemsState[itemStateIdx] = ((uint16_t)numItems + 1) | numItems & 0xFFFF0000;

                if ( ListView_GetItemCount(hCartList) > ListView_GetCountPerPage(hCartList) )
                {
                    int vscrollWidth = GetSystemMetrics(SM_CXVSCROLL);
                    ListView_SetColumnWidth(hCartList, 0, pCart->cartListWidth - vscrollWidth);
                }
            }

            pCart->total   += total;
            pCart->balance -= total;
            jonesConfig_UpdateBalances(hDlg, pCart);
        }
        else
        {
            const char* pDlgText = NULL;
            if ( bonusMapItemIdx > -1 && JonesHud_aStoreItems[bonusMapItemIdx].menuID == JONESHUD_MENU_INVITEM_BONUSMAP ) { // Fixed: Added check for bonusMapItemIdx > -1 
                pDlgText = jonesString_GetString("JONES_STR_NOPERU");
            }
            else if ( selectedCount == 1 ) {
                pDlgText = jonesString_GetString("JONES_STR_CANTBUY1");
            }
            else {
                pDlgText = jonesString_GetString("JONES_STR_CANTBUY");
            }

            if ( pDlgText )
            {
                jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_STORE", pDlgText, 191);
                InvalidateRect(hDlg, 0, 1);
            }
        }
    }
}

void J3DAPI jonesConfig_RemoveStoreCartItem(HWND hDlg, tStoreCartState* pCart)
{
    int total = 0;
    HWND hCartList = GetDlgItem(hDlg, 1006);
    UINT selectedCount = ListView_GetSelectedCount(hCartList);
    if ( selectedCount )
    {
        int idx = -1;
        for ( UINT i = 0; i < selectedCount; ++i )
        {
            idx = ListView_GetNextItem(hCartList, idx, LVNI_SELECTED);

            LVITEM lvitem;
            lvitem.mask     = LVIF_PARAM;
            lvitem.iSubItem = 0;
            lvitem.iItem    = idx;
            ListView_GetItem(hCartList, &lvitem);

            total += LOWORD(lvitem.lParam);

            SendMessage(hCartList, LVM_DELETEITEM, idx, 0);

            int numItems = pCart->apItemsState[HIWORD(lvitem.lParam)];
            pCart->apItemsState[HIWORD(lvitem.lParam)] = ((uint16_t)numItems - 1) | numItems & 0xFFFF0000;

            int itemsCount = ListView_GetItemCount(hCartList);
            if ( itemsCount <= ListView_GetCountPerPage(hCartList) )
            {
                ListView_SetColumnWidth(hCartList, 0, LOWORD(pCart->cartListWidth));
            }
        }

        pCart->total   -= total;
        pCart->balance += total;
        jonesConfig_UpdateBalances(hDlg, pCart);
    }
}

void J3DAPI jonesConfig_StoreDialog_HandleWM_COMMAND(HWND hWnd, WPARAM wParam)
{
    tStoreCartState* pCart = (tStoreCartState*)GetWindowLongPtr(hWnd, DWL_USER);
    switch ( (int)wParam )
    {
        case 1:
        case 2:
        {
            if ( pCart->balance <= 0 ) {
                EndDialog(hWnd, wParam);
            }
            else if ( jonesConfig_ShowPurchaseMessageBox(hWnd, pCart) == 1 )
            {
                InvalidateRect(hWnd, 0, 1);
                EndDialog(hWnd, wParam);
            }
        } return;
        case 1168: // Add item
            jonesConfig_AddStoreCartItem(hWnd, pCart);
            return;
        case 1169: // Return item
            jonesConfig_RemoveStoreCartItem(hWnd, pCart);
            return;
        case 1175: // Clear items
            jonesConfig_ClearStoreCart(hWnd, pCart);
            return;

    }
}

void J3DAPI jonesConfig_ClearStoreCart(HWND hDlg, tStoreCartState* pCart)
{
    HWND hWnd = GetDlgItem(hDlg, 1006);
    int count = ListView_GetItemCount(hWnd);
    for ( int i = 0; i < count; ++i )
    {
        LVITEM lvitem;
        lvitem.mask = LVIF_PARAM;
        lvitem.iSubItem = 0;
        lvitem.iItem = i;
        ListView_GetItem(hWnd, &lvitem);

        unsigned int idx = HIWORD(lvitem.lParam);
        pCart->apItemsState[idx] = ((uint16_t)pCart->apItemsState[idx] - 1) | pCart->apItemsState[idx] & 0xFFFF0000;
    }

    pCart->balance += pCart->total;
    pCart->total = 0;
    ListView_DeleteAllItems(hWnd);
    jonesConfig_UpdateBalances(hDlg, pCart);
}

int J3DAPI jonesConfig_ShowPurchaseMessageBox(HWND hWnd, tStoreCartState* dwInitParam)
{
    return JonesDialog_ShowDialog(MAKEINTRESOURCEA(212), hWnd, jonesConfig_PurchaseMessageBoxProc, (LPARAM)dwInitParam);
}

INT_PTR CALLBACK jonesConfig_PurchaseMessageBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_DESTROY:
            jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontPurchaseMessageBox);
            return 1;

        case WM_INITDIALOG:
            jonesConfig_hFontPurchaseMessageBox = jonesConfig_InitDialog(hWnd, 0, 212);
            int bSuccess = jonesConfig_InitPurchaseMessageBox(hWnd, wParam, (tStoreCartState*)lParam);
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
            return bSuccess;

        case WM_COMMAND:
            jonesConfig_MsgBoxDlg_HandleWM_COMMAND(hWnd, (uint16_t)wParam);
            return 0;

        default:
            return 0;
    }
}

int J3DAPI jonesConfig_InitPurchaseMessageBox(HWND hDlg, int a2, tStoreCartState* pCart)
{
    J3D_UNUSED(a2);

    char aText[512] = { 0 };

    if ( pCart->total )
    {
        STD_STRCAT(aText, "\n");
        char* pFormat = (char*)jonesString_GetString("JONES_STR_ADDINV");
        if ( pFormat )
        {
            STD_STRCAT(aText, pFormat);
            STD_STRCAT(aText, " ");
        }

        pFormat = (char*)jonesString_GetString("JONES_STR_SUBCHEST");
        if ( pFormat )
        {
            char aTotalText[256] = { 0 };
            STD_FORMAT(aTotalText, pFormat, pCart->total);
            STD_STRCAT(aText, aTotalText);
            STD_STRCAT(aText, "  ");
        }

        pFormat = (char*)jonesString_GetString("JONES_STR_YESNOBUY");
        if ( pFormat )
        {
            STD_STRCAT(aText, pFormat);
        }
    }
    else
    {
        char* pFormat = (char*)jonesString_GetString("JONES_STR_NOCHANGE");
        if ( pFormat )
        {
            STD_STRCAT(aText, pFormat);
            STD_STRCAT(aText, "  ");
        }

        pFormat = (char*)jonesString_GetString("JONES_STR_ABANDON");
        if ( pFormat )
        {
            STD_STRCAT(aText, pFormat);
        }
    }

    HWND hMsgControl = GetDlgItem(hDlg, 1191);
    jonesConfig_SetTextControl(hDlg, hMsgControl, aText);
    return 1;
}

int J3DAPI jonesConfig_ShowDialogInsertCD(HWND hWnd, LPARAM dwInitParam)
{
    ShowCursor(1);
    GetWindowLongPtr(hWnd, GWL_HINSTANCE); // TODO: ??
    int btnNum = JonesDialog_ShowDialog(MAKEINTRESOURCEA(167), hWnd, jonesConfig_DialogInsertCDProc, dwInitParam);
    ShowCursor(0);
    return btnNum; // 1 - ok or 2 - quit 
}

INT_PTR CALLBACK jonesConfig_DialogInsertCDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
        case WM_DESTROY:
            jonesConfig_ResetDialogFont(hWnd, jonesConfig_hFontDialogInsertCD);
            return 1;

        case WM_INITDIALOG:
            jonesConfig_hFontDialogInsertCD = jonesConfig_InitDialog(hWnd, 0, 167);
            return jonesConfig_InitDialogInsertCD(hWnd, wParam, lParam);

        case WM_COMMAND:
            jonesConfig_InsertCD_HandleWM_COMMAND(hWnd, (uint16_t)wParam);
            return 1;

        default:
            return 0;
    }
}

int J3DAPI jonesConfig_InitDialogInsertCD(HWND hDlg, int a2, int cdNum)
{
    J3D_UNUSED(a2);

    HWND hWnd = GetDlgItem(hDlg, 1134);
    if ( cdNum == 2 )
    {
        const char* pText = jonesString_GetString("JONES_STR_INSERT2");
        if ( pText )
        {
            SetWindowText(hWnd, pText);
        }
    }
    else
    {
        const char* pText = jonesString_GetString("JONES_STR_INSERT1");
        if ( pText )
        {
            SetWindowText(hWnd, pText);
        }
    }

    SetWindowLongPtr(hDlg, DWL_USER, (LONG_PTR)cdNum);
    return 1;
}

int J3DAPI jonesConfig_InsertCD_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    int cdNum = (int)GetWindowLongPtr(hWnd, DWL_USER);
    int prevCdNum = cdNum;
    if ( nResult == 1 ) // ok
    {
        cdNum = JonesFile_GetCurrentCDNum();
        if ( prevCdNum != cdNum )
        {
            return cdNum;
        }

        return EndDialog(hWnd, nResult);
    }

    if ( nResult == 2 ) // quit
    {
        return EndDialog(hWnd, nResult);
    }

    return cdNum;
}