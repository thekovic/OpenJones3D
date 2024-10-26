#include "jonesConfig.h"
#include <j3dcore/j3dhook.h>

#include <Jones3D/Main/JonesMain.h>
#include <Jones3D/Main/jonesString.h>
#include <Jones3D/RTI/symbols.h>

#include <sith/Devices/sithControl.h>
#include <sith/DSS/sithGamesave.h>
#include <sith/Gameplay/sithPlayer.h>

#include <std/General/std.h>
#include <std/General/stdUtil.h>
#include <std/Win95/stdControl.h>

typedef struct sLoadGameDialogData
{
    HDC hdc;
    char aFilePath[128];
    HBITMAP hThumbnail;
    int pfWndProc;
    int bFolderSel;
    int unknown36;
    int unknown37;
} LoadGameDialogData;


#define jonesConfig_aStoreItems J3D_DECL_FAR_ARRAYVAR(jonesConfig_aStoreItems, tStoreItem(*)[14])
#define jonesConfig_aNumberGlyphMetrics J3D_DECL_FAR_ARRAYVAR(jonesConfig_aNumberGlyphMetrics, StdRect(*)[10])
#define jonesConfig_apDialogIconFiles J3D_DECL_FAR_ARRAYVAR(jonesConfig_apDialogIconFiles, char*(*)[6])
#define jonesConfig_aLevelNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aLevelNames, const char*(*)[17])
#define jonesConfig_JONES_STR_SUMMERY J3D_DECL_FAR_VAR(jonesConfig_JONES_STR_SUMMERY, const char*)
#define jonesConfig_aJonesControlActionNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aJonesControlActionNames, const char*(*)[37])
#define jonesConfig_aJonesCapControlActionNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aJonesCapControlActionNames, const char*(*)[37])
#define jonesConfig_aDfltKeySets J3D_DECL_FAR_ARRAYVAR(jonesConfig_aDfltKeySets, int*(*)[3])
#define jonesConfig_aDfltKeySetNames J3D_DECL_FAR_ARRAYVAR(jonesConfig_aDfltKeySetNames, const char*(*)[3])
#define jonesConfig_aControlKeyStrings J3D_DECL_FAR_ARRAYVAR(jonesConfig_aControlKeyStrings, const char*(*)[223])
#define jonesConfig_aFontScaleFactors J3D_DECL_FAR_ARRAYVAR(jonesConfig_aFontScaleFactors, tJonesDialogFontScaleMetrics(*)[21])
#define jonesConfig_dword_511954 J3D_DECL_FAR_VAR(jonesConfig_dword_511954, int)
#define jonesConfig_dword_511958 J3D_DECL_FAR_VAR(jonesConfig_dword_511958, int)
#define jonesConfig_perfLevel J3D_DECL_FAR_VAR(jonesConfig_perfLevel, int)
#define jonesConfig_prevLevelNum J3D_DECL_FAR_VAR(jonesConfig_prevLevelNum, int)
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
#define jonesConfig_hFontSaveGameDlg J3D_DECL_FAR_VAR(jonesConfig_hFontSaveGameDlg, HFONT)
#define jonesConfig_hFontExitDlg J3D_DECL_FAR_VAR(jonesConfig_hFontExitDlg, HFONT)
#define jonesConfig_hFontGameSaveMsgBox J3D_DECL_FAR_VAR(jonesConfig_hFontGameSaveMsgBox, HFONT)
#define jonesConfig_hFontLoadGameDlg J3D_DECL_FAR_VAR(jonesConfig_hFontLoadGameDlg, HFONT)
#define jonesConfig_hFontGamePlayOptionsDlg J3D_DECL_FAR_VAR(jonesConfig_hFontGamePlayOptionsDlg, HFONT)
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
#define jonesConfig_hFontLevelCopletedDialog J3D_DECL_FAR_VAR(jonesConfig_hFontLevelCopletedDialog, HFONT)
#define jonesConfig_hFontStoreDialog J3D_DECL_FAR_VAR(jonesConfig_hFontStoreDialog, HFONT)
#define jonesConfig_hFontPurchaseMessageBox J3D_DECL_FAR_VAR(jonesConfig_hFontPurchaseMessageBox, HFONT)
#define jonesConfig_hFontDialogInsertCD J3D_DECL_FAR_VAR(jonesConfig_hFontDialogInsertCD, HFONT)

void jonesConfig_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(jonesConfig_Startup);
    // J3D_HOOKFUNC(jonesConfig_InitKeySetsPath);
    // J3D_HOOKFUNC(jonesConfig_InitKeyActions);
    // J3D_HOOKFUNC(jonesConfig_Shutdown);
    // J3D_HOOKFUNC(jonesConfig_ControlToString);
    // J3D_HOOKFUNC(jonesConfig_ShowMessageDialog);
    // J3D_HOOKFUNC(jonesConfig_MessageDialogProc);
    // J3D_HOOKFUNC(jonesConfig_sub_4025F0);
    // J3D_HOOKFUNC(jonesConfig_sub_402670);
    // J3D_HOOKFUNC(jonesConfig_SetTextControl);
    // J3D_HOOKFUNC(jonesConfig_sub_402A90);
    // J3D_HOOKFUNC(jonesConfig_NewControlScheme);
    // J3D_HOOKFUNC(jonesConfig_LoadConstrolsScheme);
    // J3D_HOOKFUNC(jonesConfig_GetEntryIndex);
    // J3D_HOOKFUNC(jonesConfig_GetValueIndex);
    // J3D_HOOKFUNC(jonesConfig_GetControllerKeySchemeIndex);
    // J3D_HOOKFUNC(jonesConfig_SetDefaultControlScheme);
    // J3D_HOOKFUNC(jonesConfig_BindControls);
    // J3D_HOOKFUNC(jonesConfig_BindJoystickControl);
    // J3D_HOOKFUNC(jonesConfig_InitDialogText);
    // J3D_HOOKFUNC(jonesConfig_CreateDialogFont);
    // J3D_HOOKFUNC(jonesConfig_ResetDialogFont);
    // J3D_HOOKFUNC(jonesConfig_SetWindowFontCallback);
    // J3D_HOOKFUNC(jonesConfig_PositionAndSetTextCallback);
    // J3D_HOOKFUNC(jonesConfig_sub_4045E0);
    // J3D_HOOKFUNC(jonesConfig_GetWindowScreenRect);
    // J3D_HOOKFUNC(jonesConfig_SetDialogTitleAndPosition);
    // J3D_HOOKFUNC(jonesConfig_GetSaveGameFilePath);
    // J3D_HOOKFUNC(jonesConfig_SaveGameDialogHookProc);
    // J3D_HOOKFUNC(jonesConfig_SaveGameDialogInit);
    // J3D_HOOKFUNC(jonesConfig_SaveGameThumbnailPaintProc);
    // J3D_HOOKFUNC(jonesConfig_ShowOverwriteSaveGameDlg);
    // J3D_HOOKFUNC(jonesConfig_ShowExitGameDialog);
    // J3D_HOOKFUNC(jonesConfig_ExitGameDlgProc);
    // J3D_HOOKFUNC(jonesConfig_SaveGameMsgBoxProc);
    // J3D_HOOKFUNC(jonesConfig_GameSaveSetData);
    // J3D_HOOKFUNC(jonesConfig_MsgBoxDlg_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_GetLoadGameFilePath);
    // J3D_HOOKFUNC(jonesConfig_sub_405F60);
    J3D_HOOKFUNC(jonesConfig_LoadGameDialogHookProc);
    // J3D_HOOKFUNC(jonesConfig_ShowLoadGameDialog);
    // J3D_HOOKFUNC(jonesConfig_LoadGameDialogInit);
    // J3D_HOOKFUNC(jonesConfig_LoadGameThumbnailPaintProc);
    // J3D_HOOKFUNC(jonesConfig_ShowGamePlayOptions);
    // J3D_HOOKFUNC(jonesConfig_GamePlayOptionsProc);
    // J3D_HOOKFUNC(jonesConfig_sub_406A00);
    // J3D_HOOKFUNC(jonesConfig_GamePlayOptionsInitDlg);
    // J3D_HOOKFUNC(jonesConfig_GamePlayOptions_HandleWM_COMMAND);
    J3D_HOOKFUNC(jonesConfig_EnableMouseControl);
    // J3D_HOOKFUNC(jonesConfig_FreeControlScheme);
    // J3D_HOOKFUNC(jonesConfig_FreeControlConfigEntry);
    // J3D_HOOKFUNC(jonesConfig_ShowControlOptions);
    // J3D_HOOKFUNC(jonesConfig_CopyControlConfig);
    // J3D_HOOKFUNC(jonesConfig_CopyControlSchemes);
    // J3D_HOOKFUNC(jonesConfig_InitControlsConfig);
    // J3D_HOOKFUNC(jonesConfig_LoadControlsSchemesFromSystem);
    // J3D_HOOKFUNC(jonesConfig_SetDefaultControlSchemes);
    // J3D_HOOKFUNC(jonesConfig_ControlOptionsProc);
    // J3D_HOOKFUNC(jonesConfig_InitControlOptionsDlg);
    // J3D_HOOKFUNC(jonesConfig_ControlOptions_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_WriteScheme);
    // J3D_HOOKFUNC(jonesConfig_sub_407F60);
    // J3D_HOOKFUNC(jonesConfig_sub_408000);
    // J3D_HOOKFUNC(jonesConfig_sub_408260);
    // J3D_HOOKFUNC(jonesConfig_sub_408400);
    // J3D_HOOKFUNC(jonesConfig_CreateNewSchemeAction);
    // J3D_HOOKFUNC(jonesConfig_ShowCreateControlSchemeDialog);
    // J3D_HOOKFUNC(jonesConfig_CreateControlSchemeProc);
    // J3D_HOOKFUNC(jonesConfig_InitCreateControlScheme);
    // J3D_HOOKFUNC(jonesConfig_CreateControlScheme_Handle_WM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowEditControlShemeDialog);
    // J3D_HOOKFUNC(jonesConfig_EditControlSchemProc);
    // J3D_HOOKFUNC(jonesConfig_InitEditControlSchemeDlg);
    // J3D_HOOKFUNC(jonesConfig_sub_408ED0);
    // J3D_HOOKFUNC(jonesConfig_sub_408FC0);
    // J3D_HOOKFUNC(jonesConfig_sub_409200);
    // J3D_HOOKFUNC(jonesConfig_sub_409530);
    // J3D_HOOKFUNC(jonesConfig_sub_4096F0);
    // J3D_HOOKFUNC(jonesConfig_sub_4097D0);
    // J3D_HOOKFUNC(jonesConfig_sub_409BC0);
    // J3D_HOOKFUNC(jonesConfig_AssignKeyAction);
    // J3D_HOOKFUNC(jonesConfig_sub_409F70);
    // J3D_HOOKFUNC(jonesConfig_AssignKeyDlgProc);
    // J3D_HOOKFUNC(jonesConfig_sub_40A1A0);
    // J3D_HOOKFUNC(jonesConfig_AssignControlKey);
    // J3D_HOOKFUNC(jonesConfig_sub_40A500);
    // J3D_HOOKFUNC(jonesConfig_AssignKeyDlg_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowReassignKeyMsgBox);
    // J3D_HOOKFUNC(jonesConfig_ReassignKeyDialogProc);
    // J3D_HOOKFUNC(jonesConfig_SetReassignKeyDialogText);
    // J3D_HOOKFUNC(jonesConfig_sub_40AA10);
    // J3D_HOOKFUNC(jonesConfig_ShowDisplaySettingsDialog);
    // J3D_HOOKFUNC(jonesConfig_DisplaySettingsDialogProc);
    // J3D_HOOKFUNC(jonesConfig_sub_40AE90);
    // J3D_HOOKFUNC(jonesConfig_sub_40B530);
    // J3D_HOOKFUNC(jonesConfig_sub_40B5A0);
    // J3D_HOOKFUNC(jonesConfig_ShowAdvanceDisplaySettings);
    // J3D_HOOKFUNC(jonesConfig_AdvanceDisplaySettingsDialog);
    // J3D_HOOKFUNC(jonesConfig_sub_40BC40);
    // J3D_HOOKFUNC(jonesConfig_sub_40BCD0);
    // J3D_HOOKFUNC(jonesConfig_sub_40C090);
    // J3D_HOOKFUNC(jonesConfig_ShowSoundSettingsDialog);
    // J3D_HOOKFUNC(jonesConfig_SoundSettingsDialogProc);
    // J3D_HOOKFUNC(jonesConfig_sub_40C650);
    // J3D_HOOKFUNC(jonesConfig_SoundSettings_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowGameOverDialog);
    // J3D_HOOKFUNC(jonesConfig_GameOverDialogProc);
    // J3D_HOOKFUNC(jonesConfig_LoadGameGetLastSavedGamePath);
    // J3D_HOOKFUNC(jonesConfig_GameOverDialogInit);
    // J3D_HOOKFUNC(jonesConfig_GameOverDialog_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowStatisticsDialog);
    // J3D_HOOKFUNC(jonesConfig_StatisticsDialogProc);
    // J3D_HOOKFUNC(jonesConfig_sub_40D100);
    // J3D_HOOKFUNC(jonesConfig_UpdateCurrentLevelNum);
    // J3D_HOOKFUNC(jonesConfig_DrawImageOnDialogItem);
    // J3D_HOOKFUNC(jonesConfig_SetStatisticsDialogForLevel);
    // J3D_HOOKFUNC(jonesConfig_DrawStatisticDialogIQPoints);
    // J3D_HOOKFUNC(jonesConfig_InitStatisticDialog);
    // J3D_HOOKFUNC(jonesConfig_StatisticProc_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowLevelCompletedDialog);
    // J3D_HOOKFUNC(jonesConfig_LevelCompletedDialogProc);
    // J3D_HOOKFUNC(jonesConfig_InitLevelCompletedDialog);
    // J3D_HOOKFUNC(jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ShowStoreDialog);
    // J3D_HOOKFUNC(jonesConfig_StoreDialogProc);
    // J3D_HOOKFUNC(jonesConfig_StoreHandleDragEvent);
    // J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_MBUTTONUP);
    // J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_MOUSEFIRST);
    // J3D_HOOKFUNC(jonesConfig_InitStoreDialog);
    // J3D_HOOKFUNC(jonesConfig_StoreInitItemIcons);
    // J3D_HOOKFUNC(jonesConfig_StoreSetListColumns);
    // J3D_HOOKFUNC(jonesConfig_StoreInitItemList);
    // J3D_HOOKFUNC(jonesConfig_UpdateBalances);
    // J3D_HOOKFUNC(jonesConfig_AddStoreCartItem);
    // J3D_HOOKFUNC(jonesConfig_RemoveStoreCartItem);
    // J3D_HOOKFUNC(jonesConfig_StoreDialog_HandleWM_COMMAND);
    // J3D_HOOKFUNC(jonesConfig_ClearStoreCart);
    // J3D_HOOKFUNC(jonesConfig_ShowPurchaseMessageBox);
    // J3D_HOOKFUNC(jonesConfig_PurchaseMessageBoxProc);
    // J3D_HOOKFUNC(jonesConfig_InitPurchaseMessageBox);
    // J3D_HOOKFUNC(jonesConfig_ShowDialogInsertCD);
    // J3D_HOOKFUNC(jonesConfig_DialogInsertCDProc);
    // J3D_HOOKFUNC(jonesConfig_InitDialogInsertCD);
    // J3D_HOOKFUNC(jonesConfig_InsertCD_HandleWM_COMMAND);
}

void jonesConfig_ResetGlobals(void)
{
    StdRect jonesConfig_aNumberGlyphMetrics_tmp[10] = {
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
    memcpy(&jonesConfig_aNumberGlyphMetrics, &jonesConfig_aNumberGlyphMetrics_tmp, sizeof(jonesConfig_aNumberGlyphMetrics));

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
      "Y",
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

    tJonesDialogFontScaleMetrics jonesConfig_aFontScaleFactors_tmp[21] = {
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
    memcpy(&jonesConfig_aFontScaleFactors, &jonesConfig_aFontScaleFactors_tmp, sizeof(jonesConfig_aFontScaleFactors));

    int jonesConfig_dword_511954_tmp = 1;
    memcpy(&jonesConfig_dword_511954, &jonesConfig_dword_511954_tmp, sizeof(jonesConfig_dword_511954));

    int jonesConfig_dword_511958_tmp = 1;
    memcpy(&jonesConfig_dword_511958, &jonesConfig_dword_511958_tmp, sizeof(jonesConfig_dword_511958));

    int jonesConfig_perfLevel_tmp = 4;
    memcpy(&jonesConfig_perfLevel, &jonesConfig_perfLevel_tmp, sizeof(jonesConfig_perfLevel));

    int jonesConfig_prevLevelNum_tmp = -1;
    memcpy(&jonesConfig_prevLevelNum, &jonesConfig_prevLevelNum_tmp, sizeof(jonesConfig_prevLevelNum));

    float jonesConfig_g_fogDensity_tmp = 100.0f;
    memcpy(&jonesConfig_g_fogDensity, &jonesConfig_g_fogDensity_tmp, sizeof(jonesConfig_g_fogDensity));

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
    memset(&jonesConfig_hFontSaveGameDlg, 0, sizeof(jonesConfig_hFontSaveGameDlg));
    memset(&jonesConfig_hFontExitDlg, 0, sizeof(jonesConfig_hFontExitDlg));
    memset(&jonesConfig_hFontGameSaveMsgBox, 0, sizeof(jonesConfig_hFontGameSaveMsgBox));
    memset(&jonesConfig_hFontLoadGameDlg, 0, sizeof(jonesConfig_hFontLoadGameDlg));
    memset(&jonesConfig_hFontGamePlayOptionsDlg, 0, sizeof(jonesConfig_hFontGamePlayOptionsDlg));
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
    memset(&jonesConfig_hFontLevelCopletedDialog, 0, sizeof(jonesConfig_hFontLevelCopletedDialog));
    memset(&jonesConfig_hFontStoreDialog, 0, sizeof(jonesConfig_hFontStoreDialog));
    memset(&jonesConfig_hFontPurchaseMessageBox, 0, sizeof(jonesConfig_hFontPurchaseMessageBox));
    memset(&jonesConfig_hFontDialogInsertCD, 0, sizeof(jonesConfig_hFontDialogInsertCD));
}

int jonesConfig_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_Startup);
}

int J3DAPI jonesConfig_InitKeySetsPath()
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitKeySetsPath);
}

int J3DAPI jonesConfig_InitKeyActions()
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitKeyActions);
}

void jonesConfig_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_Shutdown);
}

void J3DAPI jonesConfig_ControlToString(unsigned int controlId, char* pDest)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_ControlToString, controlId, pDest);
}

int J3DAPI jonesConfig_ShowMessageDialog(HWND hWnd, const char* pTitle, const char* pText, int iconID)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowMessageDialog, hWnd, pTitle, pText, iconID);
}

BOOL __stdcall jonesConfig_MessageDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_MessageDialogProc, hwnd, uMsg, wParam, a4);
}

void J3DAPI jonesConfig_sub_4025F0(HWND hWnd, uint16_t* a2)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_sub_4025F0, hWnd, a2);
}

int J3DAPI jonesConfig_sub_402670(HWND hDlg, int a2, uint16_t* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_402670, hDlg, a2, dwNewLong);
}

int J3DAPI jonesConfig_SetTextControl(HWND hDlg, HWND hWnd, const char* aText)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetTextControl, hDlg, hWnd, aText);
}

BOOL J3DAPI jonesConfig_sub_402A90(HWND hDlg, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_402A90, hDlg, nResult);
}

JonesControlsScheme* J3DAPI jonesConfig_NewControlScheme()
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_NewControlScheme);
}

int J3DAPI jonesConfig_LoadConstrolsScheme(const char* pFilePath, JonesControlsScheme* pConfig)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadConstrolsScheme, pFilePath, pConfig);
}

int J3DAPI jonesConfig_GetEntryIndex(int* argNum, StdConffileEntry* pEntry, int a3, const char** apStringList, int size)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GetEntryIndex, argNum, pEntry, a3, apStringList, size);
}

int J3DAPI jonesConfig_GetValueIndex(char* pValue, const char** apStringList, int size)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GetValueIndex, pValue, apStringList, size);
}

int J3DAPI jonesConfig_GetControllerKeySchemeIndex(int* pArgNum, StdConffileEntry* pEntry)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GetControllerKeySchemeIndex, pArgNum, pEntry);
}

int J3DAPI jonesConfig_SetDefaultControlScheme(JonesControlsScheme* pScheme, int num)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetDefaultControlScheme, pScheme, num);
}

void J3DAPI jonesConfig_BindControls(JonesControlsScheme* pConfig)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_BindControls, pConfig);
}

void J3DAPI jonesConfig_BindJoystickControl(SithControlFunction functionId, int controlId)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_BindJoystickControl, functionId, controlId);
}

HFONT J3DAPI jonesConfig_InitDialogText(HWND hWnd, HFONT hFont, int dlgID)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitDialogText, hWnd, hFont, dlgID);
}

HFONT J3DAPI jonesConfig_CreateDialogFont(HWND hWnd, int bWindowMode, int dlgResNum, float* pFontScale)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_CreateDialogFont, hWnd, bWindowMode, dlgResNum, pFontScale);
}

void J3DAPI jonesConfig_ResetDialogFont(HWND hWndParent, HFONT hFont)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_ResetDialogFont, hWndParent, hFont);
}

int __stdcall jonesConfig_SetWindowFontCallback(HWND hWnd, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetWindowFontCallback, hWnd, lparam);
}

BOOL __stdcall jonesConfig_PositionAndSetTextCallback(HWND hwnd, JonesDialogFontInfo* lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_PositionAndSetTextCallback, hwnd, lparam);
}

void J3DAPI jonesConfig_sub_4045E0(HWND hwnd, JonesDialogFontInfo* pFontInfo)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_sub_4045E0, hwnd, pFontInfo);
}

void J3DAPI jonesConfig_GetWindowScreenRect(HWND hWnd, LPRECT lpRect)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_GetWindowScreenRect, hWnd, lpRect);
}

void J3DAPI jonesConfig_SetDialogTitleAndPosition(HWND hWnd, JonesDialogFontInfo* pDlgFontInfo)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_SetDialogTitleAndPosition, hWnd, pDlgFontInfo);
}

int J3DAPI jonesConfig_GetSaveGameFilePath(HWND hWnd, char* pOutFilePath)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GetSaveGameFilePath, hWnd, pOutFilePath);
}

UINT_PTR __stdcall jonesConfig_SaveGameDialogHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameDialogHookProc, hDlg, msg, wParam, lParam);
}

int J3DAPI jonesConfig_SaveGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA lpOfn)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameDialogInit, hDlg, a2, lpOfn);
}

LRESULT __stdcall jonesConfig_SaveGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameThumbnailPaintProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_ShowOverwriteSaveGameDlg(HWND hWnd, char* aFilePath)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowOverwriteSaveGameDlg, hWnd, aFilePath);
}

int J3DAPI jonesConfig_ShowExitGameDialog(HWND hWnd, char* pSaveGameFilePath)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowExitGameDialog, hWnd, pSaveGameFilePath);
}

INT_PTR __stdcall jonesConfig_ExitGameDlgProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ExitGameDlgProc, hWnd, uMsg, wparam, lparam);
}

INT_PTR __stdcall jonesConfig_SaveGameMsgBoxProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SaveGameMsgBoxProc, hWnd, umsg, wParam, lParam);
}

int J3DAPI jonesConfig_GameSaveSetData(HWND hDlg, int a2, GameSaveMsgBoxData* pData)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GameSaveSetData, hDlg, a2, pData);
}

void J3DAPI jonesConfig_MsgBoxDlg_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_MsgBoxDlg_HandleWM_COMMAND, hWnd, nResult);
}

int J3DAPI jonesConfig_GetLoadGameFilePath(HWND hWnd, char* pDestNdsPath)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GetLoadGameFilePath, hWnd, pDestNdsPath);
}

void* J3DAPI jonesConfig_sub_405F60(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_405F60, hWnd);
}

//UINT_PTR __stdcall jonesConfig_LoadGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lparam)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameDialogHookProc, hDlg, uMsg, wParam, lparam);
//}

int J3DAPI jonesConfig_ShowLoadGameDialog(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowLoadGameDialog, hWnd);
}

//int J3DAPI jonesConfig_LoadGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA pofn)
//{
//    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameDialogInit, hDlg, a2, pofn);
//}

LRESULT __stdcall jonesConfig_LoadGameThumbnailPaintProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameThumbnailPaintProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_ShowGamePlayOptions(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowGamePlayOptions, hWnd);
}

INT_PTR __stdcall jonesConfig_GamePlayOptionsProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptionsProc, hWnd, msg, wparam, lparam);
}

LRESULT J3DAPI jonesConfig_sub_406A00(HWND hDlg, HWND hWnd, int a3)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_406A00, hDlg, hWnd, a3);
}

int J3DAPI jonesConfig_GamePlayOptionsInitDlg(HWND hDlg)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptionsInitDlg, hDlg);
}

int J3DAPI jonesConfig_GamePlayOptions_HandleWM_COMMAND(HWND hDlg, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GamePlayOptions_HandleWM_COMMAND, hDlg, nResult);
}

//void J3DAPI jonesConfig_EnableMouseControl(int bEnable)
//{
//    J3D_TRAMPOLINE_CALL(jonesConfig_EnableMouseControl, bEnable);
//}

void J3DAPI jonesConfig_FreeControlScheme(JonesControlsScheme* pConfig)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_FreeControlScheme, pConfig);
}

void J3DAPI jonesConfig_FreeControlConfigEntry(JonesControlsConfig* pConfig)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_FreeControlConfigEntry, pConfig);
}

int J3DAPI jonesConfig_ShowControlOptions(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowControlOptions, hWnd);
}

int J3DAPI jonesConfig_CopyControlConfig(JonesControlsConfig* pSrc, JonesControlsConfig* pDst)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_CopyControlConfig, pSrc, pDst);
}

JonesControlsScheme* J3DAPI jonesConfig_CopyControlSchemes(JonesControlsScheme* aSchemes, int start, int sizeScheme)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_CopyControlSchemes, aSchemes, start, sizeScheme);
}

int J3DAPI jonesConfig_InitControlsConfig()
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitControlsConfig);
}

int J3DAPI jonesConfig_LoadControlsSchemesFromSystem(JonesControlsConfig* pConfig)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_LoadControlsSchemesFromSystem, pConfig);
}

int J3DAPI jonesConfig_SetDefaultControlSchemes(JonesControlsConfig* pConfig)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetDefaultControlSchemes, pConfig);
}

INT_PTR __stdcall jonesConfig_ControlOptionsProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ControlOptionsProc, hwnd, umsg, wparam, lparam);
}

int J3DAPI jonesConfig_InitControlOptionsDlg(HWND hDlg, int a2, JonesControlsConfig* pConfig)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitControlOptionsDlg, hDlg, a2, pConfig);
}

void J3DAPI jonesConfig_ControlOptions_HandleWM_COMMAND(HWND hWnd, int ctrlID, int a3, int16_t a4)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_ControlOptions_HandleWM_COMMAND, hWnd, ctrlID, a3, a4);
}

int J3DAPI jonesConfig_WriteScheme(JonesControlsScheme* pScheme)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_WriteScheme, pScheme);
}

int J3DAPI jonesConfig_sub_407F60(HWND hDlg)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_407F60, hDlg);
}

LRESULT J3DAPI jonesConfig_sub_408000(HWND hDlg, int a2)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_408000, hDlg, a2);
}

void J3DAPI jonesConfig_sub_408260(HWND hDlg, JonesControlsConfig* a2)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_sub_408260, hDlg, a2);
}

JonesControlsScheme* J3DAPI jonesConfig_sub_408400(JonesControlsConfig* pConfig)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_408400, pConfig);
}

void J3DAPI jonesConfig_CreateNewSchemeAction(HWND hDlg, JonesControlsConfig* pConfig)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_CreateNewSchemeAction, hDlg, pConfig);
}

int J3DAPI jonesConfig_ShowCreateControlSchemeDialog(HWND hWnd, char* pDstSchemeName)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowCreateControlSchemeDialog, hWnd, pDstSchemeName);
}

INT_PTR __stdcall jonesConfig_CreateControlSchemeProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_CreateControlSchemeProc, hWnd, msg, wparam, lparam);
}

int J3DAPI jonesConfig_InitCreateControlScheme(HWND hDlg, int a2, char* pSchemeName)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitCreateControlScheme, hDlg, a2, pSchemeName);
}

void J3DAPI jonesConfig_CreateControlScheme_Handle_WM_COMMAND(HWND hWnd, int16_t nResult)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_CreateControlScheme_Handle_WM_COMMAND, hWnd, nResult);
}

int J3DAPI jonesConfig_ShowEditControlShemeDialog(HWND hWnd, void* dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowEditControlShemeDialog, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_EditControlSchemProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_EditControlSchemProc, hWnd, msg, wparam, lparam);
}

int J3DAPI jonesConfig_InitEditControlSchemeDlg(HWND hDlg, int a2, void* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitEditControlSchemeDlg, hDlg, a2, dwNewLong);
}

LRESULT J3DAPI jonesConfig_sub_408ED0(HWND hWnd, char* pKey)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_408ED0, hWnd, pKey);
}

const char** J3DAPI jonesConfig_sub_408FC0(HWND hWnd, int a2, JonesControlsScheme* a3)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_408FC0, hWnd, a2, a3);
}

char J3DAPI jonesConfig_sub_409200(HWND hWnd, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_409200, hWnd, nResult);
}

LPARAM J3DAPI jonesConfig_sub_409530(HWND hWnd, HWND a2, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_409530, hWnd, a2, a3, a4);
}

int J3DAPI jonesConfig_sub_4096F0(int a1, HWND hWnd, int a3, HWND* a4, uint32_t* a5)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_4096F0, a1, hWnd, a3, a4, a5);
}

char J3DAPI jonesConfig_sub_4097D0(HWND a1, HWND hWnd, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_4097D0, a1, hWnd, a3, a4);
}

LPARAM J3DAPI jonesConfig_sub_409BC0(int a1, HWND hWnd, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_409BC0, a1, hWnd, a3, a4);
}

int J3DAPI jonesConfig_AssignKeyAction(HWND hWnd, uint32_t* dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_AssignKeyAction, hWnd, dwInitParam);
}

int J3DAPI jonesConfig_sub_409F70(int a1, int a2, int* a3, int a4, int* a5)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_409F70, a1, a2, a3, a4, a5);
}

INT_PTR __stdcall jonesConfig_AssignKeyDlgProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_AssignKeyDlgProc, hWnd, msg, wparam, lparam);
}

int J3DAPI jonesConfig_sub_40A1A0(HWND hDlg, int a2, uint32_t* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40A1A0, hDlg, a2, dwNewLong);
}

void J3DAPI jonesConfig_AssignControlKey(HWND hWnd)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_AssignControlKey, hWnd);
}

int J3DAPI jonesConfig_sub_40A500(int a1)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40A500, a1);
}

void J3DAPI jonesConfig_AssignKeyDlg_HandleWM_COMMAND(HWND hWnd, int a2)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_AssignKeyDlg_HandleWM_COMMAND, hWnd, a2);
}

int J3DAPI jonesConfig_ShowReassignKeyMsgBox(HWND hWnd, LPARAM dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowReassignKeyMsgBox, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_ReassignKeyDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ReassignKeyDialogProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_SetReassignKeyDialogText(HWND hDlg, int a2, void* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetReassignKeyDialogText, hDlg, a2, dwNewLong);
}

int J3DAPI jonesConfig_sub_40AA10(HWND hWnd, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40AA10, hWnd, nResult);
}

int J3DAPI jonesConfig_ShowDisplaySettingsDialog(HWND hWnd, StdDisplayEnvironment* pDisplayEnv, JonesDisplaySettings* pDSettings)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowDisplaySettingsDialog, hWnd, pDisplayEnv, pDSettings);
}

INT_PTR __stdcall jonesConfig_DisplaySettingsDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_DisplaySettingsDialogProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_sub_40AE90(HWND hDlg, int a2, int* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40AE90, hDlg, a2, dwNewLong);
}

int J3DAPI jonesConfig_sub_40B530(const char* a1, const char* a2, int a3)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40B530, a1, a2, a3);
}

int J3DAPI jonesConfig_sub_40B5A0(HWND hWnd, int nResult, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40B5A0, hWnd, nResult, a3, a4);
}

uint32_t J3DAPI jonesConfig_ShowAdvanceDisplaySettings(HWND hWnd, LPARAM dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowAdvanceDisplaySettings, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_AdvanceDisplaySettingsDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_AdvanceDisplaySettingsDialog, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_sub_40BC40(int a1, int a2, int a3)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40BC40, a1, a2, a3);
}

int J3DAPI jonesConfig_sub_40BCD0(HWND hDlg, int a2, uint32_t* dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40BCD0, hDlg, a2, dwNewLong);
}

int J3DAPI jonesConfig_sub_40C090(HWND hWnd, int nResult, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40C090, hWnd, nResult, a3, a4);
}

int J3DAPI jonesConfig_ShowSoundSettingsDialog(HWND hWnd, float* dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowSoundSettingsDialog, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_SoundSettingsDialogProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SoundSettingsDialogProc, hWnd, msg, wparam, lparam);
}

int J3DAPI jonesConfig_sub_40C650(HWND hDlg, int a2, LONG dwNewLong)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40C650, hDlg, a2, dwNewLong);
}

int J3DAPI jonesConfig_SoundSettings_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SoundSettings_HandleWM_COMMAND, hWnd, nResult);
}

int J3DAPI jonesConfig_ShowGameOverDialog(HWND hWnd, char* pRestoreFilename, tSoundHandle hSndGameOVerMus, tSoundChannelHandle* pSndChnlMus)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowGameOverDialog, hWnd, pRestoreFilename, hSndGameOVerMus, pSndChnlMus);
}

INT_PTR __stdcall jonesConfig_GameOverDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GameOverDialogProc, hWnd, uMsg, wParam, lParam);
}

void J3DAPI jonesConfig_LoadGameGetLastSavedGamePath(char* pPath, unsigned int size)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_LoadGameGetLastSavedGamePath, pPath, size);
}

int J3DAPI jonesConfig_GameOverDialogInit(HWND hDlg, int a2, GameOverDialogData* pData)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_GameOverDialogInit, hDlg, a2, pData);
}

void J3DAPI jonesConfig_GameOverDialog_HandleWM_COMMAND(HWND hWnd, uint16_t wParam)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_GameOverDialog_HandleWM_COMMAND, hWnd, wParam);
}

int J3DAPI jonesConfig_ShowStatisticsDialog(HWND hWnd, SithGameStatistics* pStatistics)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowStatisticsDialog, hWnd, pStatistics);
}

INT_PTR __stdcall jonesConfig_StatisticsDialogProc(HWND hwnd, UINT uMsg, WPARAM wPAram, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StatisticsDialogProc, hwnd, uMsg, wPAram, lParam);
}

int J3DAPI jonesConfig_sub_40D100(int a1, HWND hWnd, int a3, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_sub_40D100, a1, hWnd, a3, a4);
}

void J3DAPI jonesConfig_UpdateCurrentLevelNum()
{
    J3D_TRAMPOLINE_CALL(jonesConfig_UpdateCurrentLevelNum);
}

int J3DAPI jonesConfig_DrawImageOnDialogItem(HWND hDlg, HDC hdcWnd, HDC hdcCtrl, int nIDDlgItem, HBITMAP hImage, HBITMAP hMask)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_DrawImageOnDialogItem, hDlg, hdcWnd, hdcCtrl, nIDDlgItem, hImage, hMask);
}

int J3DAPI jonesConfig_SetStatisticsDialogForLevel(HWND hDlg, int levelNum, int* a3)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_SetStatisticsDialogForLevel, hDlg, levelNum, a3);
}

void J3DAPI jonesConfig_DrawStatisticDialogIQPoints(HWND hwnd, JonesDialogImageInfo** ppImageInfo, int dlgID, int iqpoints)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_DrawStatisticDialogIQPoints, hwnd, ppImageInfo, dlgID, iqpoints);
}

int J3DAPI jonesConfig_InitStatisticDialog(HWND hDlg, int a2, int* pData)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitStatisticDialog, hDlg, a2, pData);
}

void J3DAPI jonesConfig_StatisticProc_HandleWM_COMMAND(HWND hWnd, int16_t wParam)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_StatisticProc_HandleWM_COMMAND, hWnd, wParam);
}

int J3DAPI jonesConfig_ShowLevelCompletedDialog(HWND hWnd, int* pBalance, int* apItemsState, int a4, int elapsedTime, int qiPoints, int numFoundTrasures, int foundTrasureValue, int totalTreasureValue)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowLevelCompletedDialog, hWnd, pBalance, apItemsState, a4, elapsedTime, qiPoints, numFoundTrasures, foundTrasureValue, totalTreasureValue);
}

int __stdcall jonesConfig_LevelCompletedDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_LevelCompletedDialogProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_InitLevelCompletedDialog(HWND hDlg, int wParam, tLevelCompletedDialogState* pState)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitLevelCompletedDialog, hDlg, wParam, pState);
}

void J3DAPI jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND(HWND hWnd, int wParam)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_ChapterCompleteDialog_HandleWM_COMMAND, hWnd, wParam);
}

int J3DAPI jonesConfig_ShowStoreDialog(HWND hWnd, int* pBalance, int* pItemsState, int a4)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowStoreDialog, hWnd, pBalance, pItemsState, a4);
}

int __stdcall jonesConfig_StoreDialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialogProc, hwnd, msg, wparam, lparam);
}

int J3DAPI jonesConfig_StoreHandleDragEvent(HWND hwnd, HWND hDlgCtrl)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreHandleDragEvent, hwnd, hDlgCtrl);
}

void J3DAPI jonesConfig_StoreDialog_HandleWM_MBUTTONUP(HWND hWnd)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_MBUTTONUP, hWnd);
}

BOOL J3DAPI jonesConfig_StoreDialog_HandleWM_MOUSEFIRST(HWND hWnd)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_MOUSEFIRST, hWnd);
}

int J3DAPI jonesConfig_InitStoreDialog(HWND hDlg, int a2, tStoreCartState* pCart)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitStoreDialog, hDlg, a2, pCart);
}

int J3DAPI jonesConfig_StoreInitItemIcons(HWND hWnd, tStoreCartState* pCart)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreInitItemIcons, hWnd, pCart);
}

LRESULT J3DAPI jonesConfig_StoreSetListColumns(HWND hList, const char* pColumnName)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_StoreSetListColumns, hList, pColumnName);
}

void J3DAPI jonesConfig_StoreInitItemList(HWND hWnd, int* apItemsState, int listID)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_StoreInitItemList, hWnd, apItemsState, listID);
}

void J3DAPI jonesConfig_UpdateBalances(HWND hDlg, tStoreCartState* pCart)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_UpdateBalances, hDlg, pCart);
}

void J3DAPI jonesConfig_AddStoreCartItem(HWND hDlg, tStoreCartState* pCart)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_AddStoreCartItem, hDlg, pCart);
}

void J3DAPI jonesConfig_RemoveStoreCartItem(HWND hDlg, tStoreCartState* pCart)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_RemoveStoreCartItem, hDlg, pCart);
}

void J3DAPI jonesConfig_StoreDialog_HandleWM_COMMAND(HWND hWnd, WPARAM wParam)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_StoreDialog_HandleWM_COMMAND, hWnd, wParam);
}

void J3DAPI jonesConfig_ClearStoreCart(HWND hDlg, tStoreCartState* pCart)
{
    J3D_TRAMPOLINE_CALL(jonesConfig_ClearStoreCart, hDlg, pCart);
}

int J3DAPI jonesConfig_ShowPurchaseMessageBox(HWND hWnd, tStoreCartState* dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowPurchaseMessageBox, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_PurchaseMessageBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_PurchaseMessageBoxProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_InitPurchaseMessageBox(HWND hDlg, int a2, tStoreCartState* pCart)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitPurchaseMessageBox, hDlg, a2, pCart);
}

int J3DAPI jonesConfig_ShowDialogInsertCD(HWND hWnd, LPARAM dwInitParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_ShowDialogInsertCD, hWnd, dwInitParam);
}

INT_PTR __stdcall jonesConfig_DialogInsertCDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_DialogInsertCDProc, hWnd, uMsg, wParam, lParam);
}

int J3DAPI jonesConfig_InitDialogInsertCD(HWND hDlg, int a2, int cdNum)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InitDialogInsertCD, hDlg, a2, cdNum);
}

int J3DAPI jonesConfig_InsertCD_HandleWM_COMMAND(HWND hWnd, int nResult)
{
    return J3D_TRAMPOLINE_CALL(jonesConfig_InsertCD_HandleWM_COMMAND, hWnd, nResult);
}

UINT_PTR __stdcall jonesConfig_LoadGameDialogHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
    UINT_PTR v4;
    HWND hThumbnail;
    HWND hIcon;
    LoadGameDialogData* pData;
    HWND hBtn;
    LPOPENFILENAMEA pOFN;
    HWND hParent;
    char* pStr;
    const char* v17;
    unsigned int strLen;
    const char* pString;
    const char* v21;
    HWND hDlgItem;
    int bValidFile;
    LPSTR lpFilePart;
    char aFilename[128];
    CHAR aSearchPath[256];
    CHAR aBuffer[128];
    char aExtension[128];

    v4 = 0;

    if ( uMsg > WM_PAINT )
    {
        if ( uMsg > WM_NOTIFY )
        {
            if ( uMsg == WM_INITDIALOG )
            {
                return jonesConfig_LoadGameDialogInit(hDlg, wParam, (LPOPENFILENAMEA)lparam);
            }

            if ( uMsg != WM_COMMAND )
            {
                return v4;
            }

            jonesConfig_sub_405F60(hDlg);
            return 0;
        }

        if ( uMsg != WM_NOTIFY )
        {
            if ( uMsg != WM_CLOSE )
            {
                return v4;
            }

            DeleteObject(jonesConfig_hFontLoadGameDlg);
            jonesConfig_hFontLoadGameDlg = 0;
            return 0;
        }

        pData = (LoadGameDialogData*)GetWindowLong(hDlg, DWL_USER);

        STDLOG_STATUS("code: %i\n", *(uint32_t*)(lparam + 8));

        switch ( *(uint32_t*)(lparam + 8) )
        {
            case CDN_FILEOK:
                pOFN = *(LPOPENFILENAMEA*)(lparam + 12);// lparam is OFNOTIFYA struct here
                bValidFile = 0;
                if ( (int16_t)pOFN->nFileOffset > 0 )
                {
                    memset(aBuffer, 0, sizeof(aBuffer));
                    memset(aSearchPath, 0, 128u);
                    memset(aExtension, 0, sizeof(aExtension));
                    memset(aFilename, 0, sizeof(aFilename));

                    //sprintf(aExtension, ".%s", pOFN->lpstrDefExt);
                    STD_FORMAT(aExtension, ".%s", pOFN->lpstrDefExt);

                    hParent = GetParent(hDlg);
                    SendMessage(hParent, CDM_GETSPEC, 128u, (LPARAM)aFilename);// get selected filename
                    pStr = strstr(*(const char**)(*(uint32_t*)(lparam + 12) + 28), aFilename);// pStr = strstr(pofn->lpOFN->lpstrFile, aFilename);
                    v17 = *(const char**)(*(uint32_t*)(lparam + 12) + 28);// lpstrFile = pofn->lpOFN->lpstrFile;
                    if ( pStr )
                    {
                        strLen = pStr - v17;
                    }
                    else
                    {
                        strLen = strlen(*(const char**)(*(uint32_t*)(lparam + 12) + 28));// v18 = strlen(pofn->lpOFN->lpstrFile);
                    }

                    //strncpy(aSearchPath, v17, strLen);
                    STD_STRNCPY(aSearchPath, v17, strLen);
                    SearchPath(aSearchPath, aFilename, aExtension, 128u, aBuffer, &lpFilePart);
                    if ( strlen(aBuffer) )
                    {
                        bValidFile = 1;
                    }

                    if ( strcspn(aFilename, "?*") != strlen(aFilename) )
                    {
                        bValidFile = 0;
                    }
                }

                if ( *(int16_t*)(*(uint32_t*)(lparam + 12) + 56) >= 0 && bValidFile )// if ( (lparam->lpOFN->nFileOffset & 0x8000u) == 0 && v24 )
                {
                    if ( strlen(aBuffer) )
                    {
                        if ( !JonesMain_IsOpen()
                          || (sithPlayer_g_pLocalPlayerThing->flags & SITH_TF_DYING) != 0
                          || (sithPlayer_g_pLocalPlayerThing->flags & SITH_TF_DESTROYED) != 0
                          || jonesConfig_ShowLoadGameDialog(hDlg) == 1 )
                        {
                            return 0;
                        }

                    LABEL_34:
                        SetWindowLong(hDlg, 0, 1);
                        return 1;
                    }

                    pString = jonesString_GetString("JONES_STR_NOFILE");
                    if ( !pString )
                    {
                        goto LABEL_34;
                    }
                }
                else
                {
                    pString = jonesString_GetString("JONES_STR_INVALIDFILE");
                    if ( !pString )
                    {
                        goto LABEL_34;
                    }
                }

                memset(aSearchPath, 0, sizeof(aSearchPath));
                hParent = GetParent(hDlg);
                SendMessage(hParent, CDM_GETSPEC, 128u, (LPARAM)aFilename);// get filename
                //sprintf(aSearchPath, pString, aFilename);
                STD_FORMAT(aSearchPath, pString, aFilename);
                jonesConfig_ShowMessageDialog(hDlg, "JONES_STR_LOADGM", aSearchPath, 139);
                goto LABEL_34;

            case CDN_FOLDERCHANGE:
                if ( !pData->hThumbnail )
                {
                    return 1;
                }

                hDlgItem = GetDlgItem(hDlg, 1163);
                pData->bFolderSel = 1;
                InvalidateRect(hDlgItem, 0, 1);

            LABEL_46:
                UpdateWindow(hDlg);
                return 1;

            case CDN_SELCHANGE:
                hThumbnail = GetDlgItem(hDlg, 1163);
                if ( !pData->bFolderSel )
                {
                    v21 = 0;
                    hParent = GetParent(hDlg);
                    SendMessage(hParent, CDM_GETFILEPATH, 128u, (LPARAM)pData->aFilePath);
                    if ( strlen(pData->aFilePath) )
                    {
                        v21 = (char*)&pData->hdc + strlen(pData->aFilePath) + 1;// ??
                    }

                    if ( v21 && !strcmp(v21, "nds") )
                    {
                        if ( pData->hThumbnail )
                        {
                            DeleteObject(pData->hThumbnail);
                            pData->hThumbnail = 0;
                        }

                        pData->hThumbnail = sithGamesave_LoadThumbnail(pData->aFilePath);
                    }
                }

                InvalidateRect(hThumbnail, 0, 1);
                goto LABEL_46;

            case CDN_FIRST:
                // CDN_INITDONE
                hBtn = GetDlgItem(hDlg, 1120);
                SetWindowLong(hBtn, GWL_USERDATA, 159);

                hIcon = GetDlgItem(hDlg, 1117);
                SetWindowLong(hIcon, GWL_USERDATA, 159);

                hThumbnail = GetDlgItem(hDlg, 1163);
                SetWindowLong(hThumbnail, GWL_USERDATA, 159);

                hParent = GetParent(hDlg);
                jonesConfig_hFontLoadGameDlg = jonesConfig_InitDialogText(hParent, 0, 0x45F009F);
                jonesConfig_hFontLoadGameDlg = jonesConfig_InitDialogText(hDlg, jonesConfig_hFontLoadGameDlg, 159);
                SetWindowPos(hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
                return 1;

            default:
                return v4;
        }
    }

    if ( uMsg != WM_PAINT )
    {
        if ( uMsg != WM_DESTROY )
        {
            return v4;
        }

        pData = (LoadGameDialogData*)GetWindowLong(hDlg, DWL_USER);
        DeleteDC(pData->hdc);
        DeleteObject(pData->hThumbnail);
        pData->hThumbnail = 0;
        pData->hdc = 0;
        return 0;
    }

    if ( !((LoadGameDialogData*)GetWindowLong(hDlg, DWL_USER))->bFolderSel )
    {
        hThumbnail = GetDlgItem(hDlg, 1163);
        UpdateWindow(hThumbnail);
    }

    hIcon = GetDlgItem(hDlg, 1117);
    UpdateWindow(hIcon);
    return 1;
}

int J3DAPI jonesConfig_LoadGameDialogInit(HWND hDlg, int a2, LPOPENFILENAMEA pofn)
{
    J3D_UNUSED(a2);

    LoadGameDialogData* pData;
    HDC dc;
    HWND hThumbnail;
    int thmbWidth;
    int thmbHeight;
    int width;
    RECT dlgRect;
    RECT dlgWinRect;
    HWND hButton;
    RECT thumbWinRect;
    RECT thumbRect;
    RECT btnRect;
    RECT iconRect;
    RECT iconWinRect;
    char aPath[128];

    pData = (LoadGameDialogData*)pofn->lCustData;
    hButton = GetDlgItem(hDlg, 1120); // load last saved game button
    GetWindowRect(hButton, &btnRect);

    hThumbnail = GetDlgItem(hDlg, 1163);
    dc = GetDC(hThumbnail);
    pData->hdc = CreateCompatibleDC(dc);

    hThumbnail = GetDlgItem(hDlg, 1163);
    pData->pfWndProc = GetWindowLong(hThumbnail, GWL_WNDPROC);

    HWND hIcon = GetDlgItem(hDlg, 1117);

    SetWindowLong(hThumbnail, GWL_WNDPROC, (LONG)jonesConfig_LoadGameThumbnailPaintProc);
    SetWindowLong(hDlg, DWL_USER, (LONG)pData);

    GetWindowRect(hDlg, &dlgWinRect);
    GetWindowRect(hDlg, &dlgRect);
    GetWindowRect(hThumbnail, &thumbWinRect);
    GetClientRect(hThumbnail, &thumbRect);
    GetWindowRect(hIcon, &iconWinRect);
    GetClientRect(hIcon, &iconRect);

    int dlgWidth  = dlgWinRect.right - dlgWinRect.left;
    int dlgHeight = dlgWinRect.bottom - dlgWinRect.top;

    // Changed: Doubled the thumbnail size
    int tbImageWidth  = SITHSAVEGAME_THUMB_WIDTH * 2;
    int tbImageHeight = SITHSAVEGAME_THUMB_HEIGHT * 2;

    thmbWidth = thumbRect.left - thumbRect.right + tbImageWidth;
    thmbHeight = thumbRect.top - thumbRect.bottom + tbImageHeight;

    int thumbPosX = thumbWinRect.left - dlgWinRect.left;
    int thumbPosY = thumbWinRect.top - dlgWinRect.top;

    int thumbWinWidth  = thumbWinRect.right - thumbWinRect.left;
    int thumbWinHeight = thumbWinRect.bottom - thumbWinRect.top;

    int thumbTotalWidth = thmbWidth + thumbWinWidth;
    int thumbTotalHeight = thmbHeight + thumbWinHeight;

    if ( thumbRect.left - thumbRect.right == -tbImageWidth && thumbRect.top - thumbRect.bottom == -tbImageHeight )
    {
        return 1;
    }

    //int iconWidth = iconRect.right - iconRect.left;
    //int iconHeight = iconRect.bottom - iconRect.top;

    MoveWindow(
        hDlg,
        dlgWinRect.left,
        dlgWinRect.top,
        //thmbWidth + dlgWidth,
        thumbTotalWidth + dlgWidth,
        dlgHeight,
        1
    );

    MoveWindow(
        hThumbnail,
        thumbPosX,
        thumbPosY,
        thumbTotalWidth,
        thumbTotalHeight,
        1
    );



    width = thumbWinRect.right + thmbWidth - thumbWinRect.left;
    //MoveWindow(
    //    hButton,
    //    thumbWinRect.left - dlgWinRect.left,
    //    btnRect.top + thmbHeight - dlgWinRect.top,
    //    width,
    //    btnRect.bottom - btnRect.top,
    //    1
    //);

    //MoveWindow(
    //    hIcon,
    //    thumbWinRect.left - dlgWinRect.left,
    //    thumbWinRect.top + thumbTotalHeight - dlgWinRect.top,
    //    thumbWinRect.right - thumbWinRect.left,
    //    thumbWinRect.bottom - thumbWinRect.top,
    //    1
    //);


    memset(aPath, 0, sizeof(aPath));
    jonesConfig_LoadGameGetLastSavedGamePath(aPath, sizeof(aPath));
    if ( !strlen(aPath) )
    {
        EnableWindow(hButton, 0); // close window if no game was saved yet
    }

    return 1;
}

void J3DAPI jonesConfig_EnableMouseControl(int bEnable)
{
    JonesDisplaySettings* pSettings = JonesMain_GetDisplaySettings();
    if ( bEnable )
    {
        sithControl_UnbindMouseAxes();
        sithControl_RegisterMouseBindings();
    }

    else if ( pSettings->windowMode )
    {
        stdControl_EnableMouse(0);
    }
    else
    {
        sithControl_UnbindMouseAxes();
        stdControl_EnableMouse(1);
    }
}