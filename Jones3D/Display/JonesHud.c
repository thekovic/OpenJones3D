#include "JonesHud.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define JonesHud_colorGreen J3D_DECL_FAR_VAR(JonesHud_colorGreen, const rdVector4)
#define JonesHud_colorYellow J3D_DECL_FAR_VAR(JonesHud_colorYellow, const rdVector4)
#define JonesHud_colorRed J3D_DECL_FAR_VAR(JonesHud_colorRed, const rdVector4)
#define JonesHud_colorBlack J3D_DECL_FAR_VAR(JonesHud_colorBlack, rdVector4)
#define JonesHud_overlayColor J3D_DECL_FAR_VAR(JonesHud_overlayColor, const rdVector4)
#define JonesHud_breathIndicatorColor J3D_DECL_FAR_VAR(JonesHud_breathIndicatorColor, const rdVector4)
#define JonesHud_colorPink J3D_DECL_FAR_VAR(JonesHud_colorPink, rdVector4)
#define JonesHud_camViewPos J3D_DECL_FAR_VAR(JonesHud_camViewPos, rdVector3)
#define JonesHud_pyrInventoryOrient J3D_DECL_FAR_VAR(JonesHud_pyrInventoryOrient, rdVector3)
#define JonesHud_vecSelectedMenuItemScale J3D_DECL_FAR_VAR(JonesHud_vecSelectedMenuItemScale, rdVector3)
#define JonesHud_aStoreItemsInfo J3D_DECL_FAR_ARRAYVAR(JonesHud_aStoreItemsInfo, tStoreItem(*)[14])
#define JonesHud_aDfltMenuItemsOrients J3D_DECL_FAR_ARRAYVAR(JonesHud_aDfltMenuItemsOrients, tMenuItemOrientInfo(*)[134])
#define JonesHud_apMenuIconModelNames J3D_DECL_FAR_ARRAYVAR(JonesHud_apMenuIconModelNames, char*(*)[134])
#define JonesHud_apItemNames J3D_DECL_FAR_ARRAYVAR(JonesHud_apItemNames, char*(*)[134])
#define JonesHud_aSoundFxIdxs J3D_DECL_FAR_ARRAYVAR(JonesHud_aSoundFxIdxs, int(*)[13])
#define JonesHud_aCreditFontColors J3D_DECL_FAR_ARRAYVAR(JonesHud_aCreditFontColors, const rdVector4(*)[12])
#define JonesHud_aCredits J3D_DECL_FAR_ARRAYVAR(JonesHud_aCredits, tJonesCreditEntry(*)[325])
#define JonesHud_msecMenuItemMoveDuration J3D_DECL_FAR_VAR(JonesHud_msecMenuItemMoveDuration, unsigned int)
#define JonesHud_selectedWeaponID J3D_DECL_FAR_VAR(JonesHud_selectedWeaponID, SithWeaponId)
#define JonesHud_curEnduranceIndAlpha J3D_DECL_FAR_VAR(JonesHud_curEnduranceIndAlpha, float)
#define JonesHud_curEnduranceState J3D_DECL_FAR_VAR(JonesHud_curEnduranceState, float)
#define JonesHud_curKeyId J3D_DECL_FAR_VAR(JonesHud_curKeyId, int)
#define JonesHud_curWhoopsSndFxIdx J3D_DECL_FAR_VAR(JonesHud_curWhoopsSndFxIdx, int)
#define JonesHud_bCutsceneStart J3D_DECL_FAR_VAR(JonesHud_bCutsceneStart, int)
#define JonesHud_healthIndBarPos J3D_DECL_FAR_VAR(JonesHud_healthIndBarPos, rdVector4)
#define JonesHud_msecDeltaTime J3D_DECL_FAR_VAR(JonesHud_msecDeltaTime, size_t)
#define JonesHud_apMenuItems J3D_DECL_FAR_ARRAYVAR(JonesHud_apMenuItems, JonesHudMenuItem*(*)[134])
#define JonesHud_hudState J3D_DECL_FAR_VAR(JonesHud_hudState, int)
#define JonesHud_msecGameOverWaitDeltaTime J3D_DECL_FAR_VAR(JonesHud_msecGameOverWaitDeltaTime, unsigned int)
#define JonesHud_enduranceIndBarPos J3D_DECL_FAR_VAR(JonesHud_enduranceIndBarPos, rdVector4)
#define JonesHud_creditsSomeIdx J3D_DECL_FAR_VAR(JonesHud_creditsSomeIdx, int)
#define JonesHud_screenHeightScalar J3D_DECL_FAR_VAR(JonesHud_screenHeightScalar, float)
#define JonesHud_screenWidthScalar J3D_DECL_FAR_VAR(JonesHud_screenWidthScalar, float)
#define JonesHud_selectedTreasuresMenuItemID J3D_DECL_FAR_VAR(JonesHud_selectedTreasuresMenuItemID, int)
#define JonesHud_healthIndRect J3D_DECL_FAR_VAR(JonesHud_healthIndRect, JonesHudRect)
#define JonesHud_indScale J3D_DECL_FAR_VAR(JonesHud_indScale, float)
#define JonesHud_curCelNum J3D_DECL_FAR_VAR(JonesHud_curCelNum, int)
#define JonesHud_msecTime J3D_DECL_FAR_VAR(JonesHud_msecTime, unsigned int)
#define JonesHud_camViewMatrix J3D_DECL_FAR_VAR(JonesHud_camViewMatrix, rdMatrix34)
#define JonesHud_pCreditsFont2 J3D_DECL_FAR_VAR(JonesHud_pCreditsFont2, rdFont*)
#define JonesHud_aSlectedNdsFilePath J3D_DECL_FAR_ARRAYVAR(JonesHud_aSlectedNdsFilePath, char(*)[128])
#define JonesHud_rootMenuItemId J3D_DECL_FAR_VAR(JonesHud_rootMenuItemId, int)
#define JonesHud_maxItemZ J3D_DECL_FAR_VAR(JonesHud_maxItemZ, float)
#define JonesHud_bIMPState J3D_DECL_FAR_VAR(JonesHud_bIMPState, int)
#define JonesHud_bBonusMapBought J3D_DECL_FAR_VAR(JonesHud_bBonusMapBought, int)
#define JonesHud_apCreditsMats J3D_DECL_FAR_ARRAYVAR(JonesHud_apCreditsMats, rdMaterial*(*)[325])
#define JonesHud_pCreditsFont1 J3D_DECL_FAR_VAR(JonesHud_pCreditsFont1, rdFont*)
#define JonesHud_msecLastKeyPressTime J3D_DECL_FAR_VAR(JonesHud_msecLastKeyPressTime, int)
#define JonesHud_selectedWeaponMenuItemID J3D_DECL_FAR_VAR(JonesHud_selectedWeaponMenuItemID, int)
#define JonesHud_selectedOptionsMenuItemID J3D_DECL_FAR_VAR(JonesHud_selectedOptionsMenuItemID, int)
#define JonesHud_msecRaftIndicatorFadeTime J3D_DECL_FAR_VAR(JonesHud_msecRaftIndicatorFadeTime, int)
#define JonesHud_foundTreasureValue J3D_DECL_FAR_VAR(JonesHud_foundTreasureValue, int)
#define JonesHud_curHealth J3D_DECL_FAR_VAR(JonesHud_curHealth, float)
#define JonesHud_creditTextHeight J3D_DECL_FAR_VAR(JonesHud_creditTextHeight, float)
#define JonesHud_nearClipPlane J3D_DECL_FAR_VAR(JonesHud_nearClipPlane, float)
#define JonesHud_aActivateKeyIds J3D_DECL_FAR_ARRAYVAR(JonesHud_aActivateKeyIds, int(*)[8])
#define JonesHud_aCosSinTableScaled J3D_DECL_FAR_ARRAYVAR(JonesHud_aCosSinTableScaled, float(*)[24][2])
#define JonesHud_bInterfaceEnabled J3D_DECL_FAR_VAR(JonesHud_bInterfaceEnabled, int)
#define JonesHud_bufferHeight J3D_DECL_FAR_VAR(JonesHud_bufferHeight, uint32_t)
#define JonesHud_aCreditsTextHeights J3D_DECL_FAR_ARRAYVAR(JonesHud_aCreditsTextHeights, float(*)[325])
#define JonesHud_levelStartIQPoints J3D_DECL_FAR_VAR(JonesHud_levelStartIQPoints, int)
#define JonesHud_enduranceRect J3D_DECL_FAR_VAR(JonesHud_enduranceRect, JonesHudRect)
#define JonesHud_dword_554FDC J3D_DECL_FAR_VAR(JonesHud_dword_554FDC, int)
#define JonesHud_flt_554FE0 J3D_DECL_FAR_VAR(JonesHud_flt_554FE0, float)
#define JonesHud_flt_554FE4 J3D_DECL_FAR_VAR(JonesHud_flt_554FE4, float)
#define JonesHud_creditsSomeIdx_0 J3D_DECL_FAR_VAR(JonesHud_creditsSomeIdx_0, int)
#define JonesHud_selectedItemsMenuItemID J3D_DECL_FAR_VAR(JonesHud_selectedItemsMenuItemID, int)
#define JonesHud_numFoundTreasures J3D_DECL_FAR_VAR(JonesHud_numFoundTreasures, int)
#define JonesHud_creditsSomeIdx_1 J3D_DECL_FAR_VAR(JonesHud_creditsSomeIdx_1, int)
#define JonesHud_aSoundFxHandles J3D_DECL_FAR_ARRAYVAR(JonesHud_aSoundFxHandles, tSoundHandle(*)[13])
#define JonesHud_flt_555034 J3D_DECL_FAR_VAR(JonesHud_flt_555034, float)
#define JonesHud_flt_555038 J3D_DECL_FAR_VAR(JonesHud_flt_555038, float)
#define JonesHud_flt_55503C J3D_DECL_FAR_VAR(JonesHud_flt_55503C, float)
#define JonesHud_bufferWidth J3D_DECL_FAR_VAR(JonesHud_bufferWidth, uint32_t)
#define JonesHud_healthIndAlpha J3D_DECL_FAR_VAR(JonesHud_healthIndAlpha, float)
#define JonesHud_bFadeHealthHUD J3D_DECL_FAR_VAR(JonesHud_bFadeHealthHUD, int)
#define JonesHud_aCosSinTable J3D_DECL_FAR_ARRAYVAR(JonesHud_aCosSinTable, float(*)[24][2])
#define JonesHud_msecHealthIndLastFadeUpdate J3D_DECL_FAR_VAR(JonesHud_msecHealthIndLastFadeUpdate, unsigned int)
#define JonesHud_playerHealthFadeStart J3D_DECL_FAR_VAR(JonesHud_playerHealthFadeStart, float)
#define JonesHud_bStartup J3D_DECL_FAR_VAR(JonesHud_bStartup, int)
#define JonesHud_bOpen J3D_DECL_FAR_VAR(JonesHud_bOpen, int)
#define JonesHud_pArrowUp J3D_DECL_FAR_VAR(JonesHud_pArrowUp, rdMaterial*)
#define JonesHud_pArrowDown J3D_DECL_FAR_VAR(JonesHud_pArrowDown, rdMaterial*)
#define JonesHud_bHealthIndFadeSet J3D_DECL_FAR_VAR(JonesHud_bHealthIndFadeSet, int)
#define JonesHud_pHudBaseMat J3D_DECL_FAR_VAR(JonesHud_pHudBaseMat, rdMaterial*)
#define JonesHud_pHealthOverlay J3D_DECL_FAR_VAR(JonesHud_pHealthOverlay, rdMaterial*)
#define JonesHud_pHealthOverlayHitMat J3D_DECL_FAR_VAR(JonesHud_pHealthOverlayHitMat, rdMaterial*)
#define JonesHud_pPoisonedOverlayMat J3D_DECL_FAR_VAR(JonesHud_pPoisonedOverlayMat, rdMaterial*)
#define JonesHud_pEnduranceOverlayMat J3D_DECL_FAR_VAR(JonesHud_pEnduranceOverlayMat, rdMaterial*)
#define JonesHud_pMenuFont J3D_DECL_FAR_VAR(JonesHud_pMenuFont, rdFont*)
#define JonesHud_pMenuItemLinkedList J3D_DECL_FAR_VAR(JonesHud_pMenuItemLinkedList, JonesHudMenuItem*)
#define JonesHud_pCloseMenuItem J3D_DECL_FAR_VAR(JonesHud_pCloseMenuItem, JonesHudMenuItem*)
#define JonesHud_item_flag_state_55514C J3D_DECL_FAR_VAR(JonesHud_item_flag_state_55514C, int)
#define JonesHud_pCurSelectedMenuItem J3D_DECL_FAR_VAR(JonesHud_pCurSelectedMenuItem, JonesHudMenuItem*)
#define JonesHud_pCurInvChangedItem J3D_DECL_FAR_VAR(JonesHud_pCurInvChangedItem, JonesHudMenuItem*)
#define JonesHud_bExitActivated J3D_DECL_FAR_VAR(JonesHud_bExitActivated, int)
#define JonesHud_dword_55515C J3D_DECL_FAR_VAR(JonesHud_dword_55515C, int)
#define JonesHud_bRestoreActivated J3D_DECL_FAR_VAR(JonesHud_bRestoreActivated, int)
#define JonesHud_bRestoreGameStatistics J3D_DECL_FAR_VAR(JonesHud_bRestoreGameStatistics, int)
#define JonesHud_bItemActivated J3D_DECL_FAR_VAR(JonesHud_bItemActivated, int)
#define JonesHud_bMenuEnabled J3D_DECL_FAR_VAR(JonesHud_bMenuEnabled, int)
#define JonesHud_pHudCamera J3D_DECL_FAR_VAR(JonesHud_pHudCamera, rdCamera*)
#define JonesHud_pHudCanvas J3D_DECL_FAR_VAR(JonesHud_pHudCanvas, rdCanvas*)
#define JonesHud_bMapOpen J3D_DECL_FAR_VAR(JonesHud_bMapOpen, int)
#define JonesHud_bShowMenu J3D_DECL_FAR_VAR(JonesHud_bShowMenu, int)
#define JonesHud_hCurSndChannel J3D_DECL_FAR_VAR(JonesHud_hCurSndChannel, tSoundChannelHandle)
#define JonesHud_bFadingHealthHUD J3D_DECL_FAR_VAR(JonesHud_bFadingHealthHUD, int)
#define JonesHud_hitOverlayAlphaState J3D_DECL_FAR_VAR(JonesHud_hitOverlayAlphaState, float)
#define JonesHud_hitOverlayAlpha J3D_DECL_FAR_VAR(JonesHud_hitOverlayAlpha, float)
#define JonesHud_bKeyStateUpdated J3D_DECL_FAR_VAR(JonesHud_bKeyStateUpdated, int)
#define JonesHud_hProcessHelp J3D_DECL_FAR_VAR(JonesHud_hProcessHelp, HANDLE)
#define JonesHud_msecCreditsElapsedTime J3D_DECL_FAR_VAR(JonesHud_msecCreditsElapsedTime, int)
#define JonesHud_msecCreditsFadeStart J3D_DECL_FAR_VAR(JonesHud_msecCreditsFadeStart, int)
#define JonesHud_creditsSomeHeightRatio J3D_DECL_FAR_VAR(JonesHud_creditsSomeHeightRatio, float)
#define JonesHud_bFinishingCredits J3D_DECL_FAR_VAR(JonesHud_bFinishingCredits, int)
#define JonesHud_bSomeCreditsBoolean J3D_DECL_FAR_VAR(JonesHud_bSomeCreditsBoolean, int)

void JonesHud_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(JonesHud_Startup);
    // J3D_HOOKFUNC(JonesHud_Shutdown);
    // J3D_HOOKFUNC(JonesHud_Open);
    // J3D_HOOKFUNC(JonesHud_Close);
    // J3D_HOOKFUNC(JonesHud_ToggleMenu);
    // J3D_HOOKFUNC(JonesHud_EnableMenu);
    // J3D_HOOKFUNC(JonesHud_IsMenuEnabled);
    // J3D_HOOKFUNC(JonesHud_Render);
    // J3D_HOOKFUNC(JonesHud_Update);
    // J3D_HOOKFUNC(JonesHud_SetCanvasSize);
    // J3D_HOOKFUNC(JonesHud_UpdateSinCosTable);
    // J3D_HOOKFUNC(JonesHud_UpdateHUDLayout);
    // J3D_HOOKFUNC(JonesHud_MenuOpen);
    // J3D_HOOKFUNC(JonesHud_MenuClose);
    // J3D_HOOKFUNC(JonesHud_StartItemTranslation);
    // J3D_HOOKFUNC(JonesHud_HasTimeElapsed);
    // J3D_HOOKFUNC(JonesHud_RenderEnduranceIndicator);
    // J3D_HOOKFUNC(JonesHud_DrawEnduranceIndicator);
    // J3D_HOOKFUNC(JonesHud_SetFadeHealthHUD);
    // J3D_HOOKFUNC(JonesHud_RenderFadeHealthIndicator);
    // J3D_HOOKFUNC(JonesHud_DrawHealthIndicator);
    // J3D_HOOKFUNC(JonesHud_DrawHealthHitOverlay);
    // J3D_HOOKFUNC(JonesHud_RenderHealthIndicator);
    // J3D_HOOKFUNC(JonesHud_DrawHealthIndicatorBase);
    // J3D_HOOKFUNC(JonesHud_DrawHealthIndicatorBar);
    // J3D_HOOKFUNC(JonesHud_DrawIndicatorBar);
    // J3D_HOOKFUNC(JonesHud_Draw);
    // J3D_HOOKFUNC(JonesHud_ProcessMenuItems);
    // J3D_HOOKFUNC(JonesHud_MenuMoveLeft);
    // J3D_HOOKFUNC(JonesHud_MenuMoveRight);
    // J3D_HOOKFUNC(JonesHud_MenuMoveDown);
    // J3D_HOOKFUNC(JonesHud_SetSelectedMenuItem);
    // J3D_HOOKFUNC(JonesHud_MenuMoveUp);
    // J3D_HOOKFUNC(JonesHud_BindActivateControlKeys);
    // J3D_HOOKFUNC(JonesHud_GetKey);
    // J3D_HOOKFUNC(JonesHud_InitializeMenu);
    // J3D_HOOKFUNC(JonesHud_InitializeMenuSounds);
    // J3D_HOOKFUNC(JonesHud_NewMenuItem);
    // J3D_HOOKFUNC(JonesHud_FreeMenuItem);
    // J3D_HOOKFUNC(JonesHud_UpdateItem);
    // J3D_HOOKFUNC(JonesHud_RenderMenuItems);
    // J3D_HOOKFUNC(JonesHud_RenderMenuItem);
    // J3D_HOOKFUNC(JonesHud_MenuActivateItem);
    // J3D_HOOKFUNC(JonesHud_ResetMenuItems);
    // J3D_HOOKFUNC(JonesHud_SetLeftRightItems);
    // J3D_HOOKFUNC(JonesHud_SetDownUpItems);
    // J3D_HOOKFUNC(JonesHud_sub_4198E0);
    // J3D_HOOKFUNC(JonesHud_sub_419B50);
    // J3D_HOOKFUNC(JonesHud_InventoryItemChanged);
    // J3D_HOOKFUNC(JonesHud_RenderInventoryItemChange);
    // J3D_HOOKFUNC(JonesHud_DrawMenuItemIcon);
    // J3D_HOOKFUNC(JonesHud_ShowLevelCompleted);
    // J3D_HOOKFUNC(JonesHud_OpenHelp);
    // J3D_HOOKFUNC(JonesHud_ShowGameOverDialog);
    // J3D_HOOKFUNC(JonesHud_GetHealthBarAlpha);
    // J3D_HOOKFUNC(JonesHud_SetHealthBarAlpha);
    // J3D_HOOKFUNC(JonesHud_CutsceneStart);
    // J3D_HOOKFUNC(JonesHud_EnableInterface);
    // J3D_HOOKFUNC(JonesHud_DrawCredits);
    // J3D_HOOKFUNC(JonesHud_InitializeGameStatistics);
    // J3D_HOOKFUNC(JonesHud_RestoreGameStatistics);
    // J3D_HOOKFUNC(JonesHud_RestoreTreasuresStatistics);
}

void JonesHud_ResetGlobals(void)
{
    const rdVector4 JonesHud_colorGreen_tmp = { { 0.14f }, { 0.69f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector4 *)&JonesHud_colorGreen, &JonesHud_colorGreen_tmp, sizeof(JonesHud_colorGreen));
    
    const rdVector4 JonesHud_colorYellow_tmp = { { 1.0f }, { 0.76999998f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector4 *)&JonesHud_colorYellow, &JonesHud_colorYellow_tmp, sizeof(JonesHud_colorYellow));
    
    const rdVector4 JonesHud_colorRed_tmp = { { 0.82999998f }, { 0.055f }, { 0.0f }, { 0.0f } };
    memcpy((rdVector4 *)&JonesHud_colorRed, &JonesHud_colorRed_tmp, sizeof(JonesHud_colorRed));
    
    rdVector4 JonesHud_colorBlack_tmp = { { 0.0099999998f }, { 0.0099999998f }, { 0.0099999998f }, { 0.0f } };
    memcpy(&JonesHud_colorBlack, &JonesHud_colorBlack_tmp, sizeof(JonesHud_colorBlack));
    
    const rdVector4 JonesHud_overlayColor_tmp = { { 1.0f }, { 1.0f }, { 1.0f }, { 0.0f } };
    memcpy((rdVector4 *)&JonesHud_overlayColor, &JonesHud_overlayColor_tmp, sizeof(JonesHud_overlayColor));
    
    const rdVector4 JonesHud_breathIndicatorColor_tmp = { { 0.40000001f }, { 0.69999999f }, { 0.89999998f }, { 0.0f } };
    memcpy((rdVector4 *)&JonesHud_breathIndicatorColor, &JonesHud_breathIndicatorColor_tmp, sizeof(JonesHud_breathIndicatorColor));
    
    rdVector4 JonesHud_colorPink_tmp = { { 1.0f }, { 0.0f }, { 1.0f }, { 0.0f } };
    memcpy(&JonesHud_colorPink, &JonesHud_colorPink_tmp, sizeof(JonesHud_colorPink));
    
    rdVector3 JonesHud_camViewPos_tmp = { { 0.0f }, { -2.0f }, { 0.64999998f } };
    memcpy(&JonesHud_camViewPos, &JonesHud_camViewPos_tmp, sizeof(JonesHud_camViewPos));
    
    rdVector3 JonesHud_pyrInventoryOrient_tmp = { { -17.700001f }, { 0.0f }, { 0.0f } };
    memcpy(&JonesHud_pyrInventoryOrient, &JonesHud_pyrInventoryOrient_tmp, sizeof(JonesHud_pyrInventoryOrient));
    
    rdVector3 JonesHud_vecSelectedMenuItemScale_tmp = { { 1.25f }, { 1.25f }, { 1.25f } };
    memcpy(&JonesHud_vecSelectedMenuItemScale, &JonesHud_vecSelectedMenuItemScale_tmp, sizeof(JonesHud_vecSelectedMenuItemScale));
    
    tStoreItem JonesHud_aStoreItemsInfo_tmp[14] = {
      { 204, "JONES_STR_STORE_MAUSER", "JONES_STR_CLIP_MAUSER", 4, 50, 5 },
      { 198, "JONES_STR_STORE_PPSH41", "JONES_STR_CLIP_PPSH41", 7, 100, 20 },
      { 203, "JONES_STR_STORE_SIMINOV", "JONES_STR_CLIP_SIMINOV", 5, 50, 5 },
      { 199, "JONES_STR_STORE_TOKAREV", "JONES_STR_CLIP_TOKAREV", 3, 50, 10 },
      { 200, "JONES_STR_STORE_TOZ34", "JONES_STR_STORE_TOZ34", 8, 50, 5 },
      { 202, "JONES_STR_STORE_SATCHEL", "JONES_STR_STORE_SATCHEL", 10, 40, 3 },
      { 197, "JONES_STR_STORE_GRENADE", "JONES_STR_STORE_GRENADE", 9, 20, 3 },
      { 193, "JONES_STR_STORE_BAZOOKA", "JONES_STR_STORE_BAZOOKA", 11, 30, 3 },
      { 194, "JONES_STR_STORE_MEDICINE", "JONES_STR_STORE_MEDICINE", 21, 100, 1 },
      { 196, "JONES_STR_STORE_1STAID", "JONES_STR_STORE_1STAID", 22, 300, 1 },
      { 192, "JONES_STR_STORE_VENOM", "JONES_STR_STORE_VENOM", 25, 50, 1 },
      { 201, "JONES_STR_STORE_MAP", "JONES_STR_STORE_MAP", 123, 2500, 0 },
      { 217, "JONES_STR_STORE_BIGHERB", "JONES_STR_STORE_BIGHERB", 24, 300, 1 },
      { 227, "JONES_STR_STORE_SMALLHERB", "JONES_STR_STORE_SMALLHERB", 23, 100, 1 }
    };
    memcpy(&JonesHud_aStoreItemsInfo, &JonesHud_aStoreItemsInfo_tmp, sizeof(JonesHud_aStoreItemsInfo));
    
    tMenuItemOrientInfo JonesHud_aDfltMenuItemsOrients_tmp[134] = {
      { 1.1f, { { 0.0f }, { 270.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 1.0f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.85000002f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.80000001f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.89999998f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 1.0f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 1.0f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 1.05f, { { 60.0f }, { 90.0f }, { 90.0f } } },
      { 0.60000002f, { { 135.0f }, { 90.0f }, { 135.0f } } },
      { 0.89999998f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 1.0f, { { 60.0f }, { 90.0f }, { 90.0f } } },
      { 0.80000001f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 1.0f, { { 90.0f }, { 180.0f }, { 0.0f } } },
      { 1.0f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.80000001f, { { 45.0f }, { 315.0f }, { 90.0f } } },
      { 0.80000001f, { { 225.0f }, { 270.0f }, { 0.0f } } },
      { 1.25f, { { 225.0f }, { 270.0f }, { 0.0f } } },
      { 1.25f, { { 225.0f }, { 270.0f }, { 0.0f } } },
      { 0.69999999f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.89999998f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 30.0f }, { 0.0f }, { 315.0f } } },
      { 1.1f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.64999998f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.94999999f, { { 270.0f }, { 180.0f }, { 0.0f } } },
      { 1.1f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.05f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.05f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.69999999f, { { 0.0f }, { 180.0f }, { 0.0f } } },
      { 1.25f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.25f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.60000002f, { { 30.0f }, { 270.0f }, { 0.0f } } },
      { 0.60000002f, { { 30.0f }, { 270.0f }, { 0.0f } } },
      { 0.60000002f, { { 30.0f }, { 270.0f }, { 0.0f } } },
      { 0.60000002f, { { 30.0f }, { 270.0f }, { 0.0f } } },
      { 1.25f, { { 0.0f }, { 150.0f }, { 0.0f } } },
      { 1.0f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 1.1f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 0.69999999f, { { 45.0f }, { 90.0f }, { 0.0f } } },
      { 0.80000001f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.80000001f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.80000001f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 1.0f, { { 45.0f }, { 200.0f }, { 120.0f } } },
      { 0.85000002f, { { 45.0f }, { 135.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 1.0f, { { 315.0f }, { 0.0f }, { 0.0f } } },
      { 0.94999999f, { { 315.0f }, { 0.0f }, { 0.0f } } },
      { 0.64999998f, { { 315.0f }, { 0.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 0.64999998f, { { 45.0f }, { 315.0f }, { 0.0f } } },
      { 0.85000002f, { { 270.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 300.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 300.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 300.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 300.0f }, { 0.0f } } },
      { 0.69999999f, { { 45.0f }, { 315.0f }, { 0.0f } } },
      { 0.75f, { { 45.0f }, { 225.0f }, { 0.0f } } },
      { 0.55000001f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.80000001f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 270.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.85000002f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.80000001f, { { 240.0f }, { 315.0f }, { 0.0f } } },
      { 0.80000001f, { { 240.0f }, { 315.0f }, { 0.0f } } },
      { 0.80000001f, { { 240.0f }, { 315.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 90.0f }, { 90.0f } } },
      { 0.89999998f, { { 45.0f }, { 90.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 225.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 225.0f }, { 0.0f } } },
      { 0.75f, { { 45.0f }, { 135.0f }, { 0.0f } } },
      { 0.85000002f, { { 225.0f }, { 225.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 270.0f }, { 90.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.80000001f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.75f, { { 0.0f }, { 45.0f }, { 45.0f } } },
      { 0.85000002f, { { 0.0f }, { 25.0f }, { 45.0f } } },
      { 1.0f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 0.69999999f, { { 45.0f }, { 270.0f }, { 90.0f } } },
      { 0.80000001f, { { 45.0f }, { 270.0f }, { 0.0f } } },
      { 1.0f, { { 315.0f }, { 270.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 80.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 240.0f }, { 0.0f } } },
      { 0.89999998f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 225.0f }, { 45.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 135.0f }, { 0.0f } } },
      { 0.69999999f, { { 225.0f }, { 225.0f }, { 0.0f } } },
      { 0.75f, { { 0.0f }, { 180.0f }, { 45.0f } } },
      { 0.85000002f, { { 90.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 45.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 135.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 45.0f }, { 0.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.64999998f, { { 45.0f }, { 90.0f }, { 0.0f } } },
      { 0.69999999f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.75f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.75f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.75f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 1.0f, { { 0.0f }, { 180.0f }, { 0.0f } } },
      { 0.85000002f, { { 315.0f }, { 270.0f }, { 90.0f } } },
      { 0.85000002f, { { 135.0f }, { 270.0f }, { 90.0f } } },
      { 0.80000001f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.75f, { { 0.0f }, { 225.0f }, { 135.0f } } },
      { 0.75f, { { 225.0f }, { 225.0f }, { 0.0f } } },
      { 0.75f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 200.0f }, { 0.0f } } },
      { 0.85000002f, { { 225.0f }, { 225.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 225.0f }, { 45.0f } } },
      { 0.85000002f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.89999998f, { { 45.0f }, { 45.0f }, { 0.0f } } },
      { 0.80000001f, { { 45.0f }, { 270.0f }, { 0.0f } } },
      { 0.85000002f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.85000002f, { { 0.0f }, { 0.0f }, { 0.0f } } },
      { 1.1f, { { 0.0f }, { 150.0f }, { 0.0f } } },
      { 0.85000002f, { { 45.0f }, { 315.0f }, { 0.0f } } },
      { 1.0f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 1.0f, { { 90.0f }, { 90.0f }, { 0.0f } } },
      { 0.80000001f, { { 90.0f }, { 150.0f }, { 0.0f } } },
      { 1.0f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 0.94999999f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 0.94999999f, { { 90.0f }, { 330.0f }, { 0.0f } } },
      { 1.0f, { { 90.0f }, { 330.0f }, { 0.0f } } }
    };
    memcpy(&JonesHud_aDfltMenuItemsOrients, &JonesHud_aDfltMenuItemsOrients_tmp, sizeof(JonesHud_aDfltMenuItemsOrients));
    
    char *JonesHud_apMenuIconModelNames_tmp[134] = {
      "weap_gloves_inv.3do",
      "weap_whip_inv.3do",
      "weap_revolver_inv.3do",
      "weap_tokarev_inv.3do",
      "weap_mauser_inv.3do",
      "weap_simonov_inv.3do",
      "weap_machete_inv.3do",
      "weap_ppsh41_inv.3do",
      "weap_toz34_inv.3do",
      "weap_grenade_inv.3do",
      "weap_satchel_inv.3do",
      "weap_bazooka_inv.3do",
      "gen_ammo_mauser.3do",
      "gen_ammo_ppsh41.3do",
      "gen_ammo_simonov.3do",
      "gen_ammo_tokarev.3do",
      "gen_ammo_toz34.3do",
      "gen_rckt_bzooka.3do",
      "weap_rocket_pack.3do",
      "weap_grenade_pack.3do",
      "weap_satchel_pack.3do",
      "gen_icon_hlthsml.3do",
      "gen_icon_hlthbig.3do",
      "gen_herb_small.3do",
      "gen_herb_big.3do",
      "gen_icon_bite.3do",
      NULL,
      "gen_coins_gold.3do",
      "gen_coins_slvr.3do",
      "gen_idol_gold.3do",
      "gen_idol_slvr.3do",
      "pru_idol.3do",
      "gen_ingots_gold.3do",
      "gen_ingots_slvr.3do",
      "gen_gem_red.3do",
      "gen_gem_green.3do",
      "gen_gem_blue.3do",
      "aet_gem04.3do",
      "riv_box_cash.3do",
      "gen_icon_chest.3do",
      "gen_icon_zippo.3do",
      "gen_icon_chalk.3do",
      "imp1_vibrat_inv.3do",
      "imp2_invis_inv.3do",
      "imp3_levit_inv.3do",
      "imp4_energ_inv.3do",
      "imp5_dial_inv.3do",
      "cyn_potshard.3do",
      "bab_gear_elev.3do",
      "bab_tu_key.3do",
      "bab_tblt_a.3do",
      "bab_tblt_b.3do",
      "bab_tblt_c.3do",
      "bab_idol_mrdk.3do",
      "riv_raft_inflt1_inv.3do",
      "riv_kit_ptch.3do",
      "riv_cndl_awind.3do",
      "riv_cndl_bwind.3do",
      "riv_cndl_cwind.3do",
      "riv_cndl_dwind.3do",
      "riv_coin.3do",
      "shs_key_sealdoor.3do",
      "shs_bulb_pot.3do",
      "shs_bulb_leafstem.3do",
      "shs_bulb_bud.3do",
      "gen_bronz_key.3do",
      "shs_key_lady.3do",
      "shw_jar_oil.3do",
      "shw_divkeyblue.3do",
      "shw_divkeygold.3do",
      "shw_divkeyred.3do",
      "lag_key_pdlck.3do",
      "lag_shovel_fold.3do",
      "lag_plane_prop.3do",
      "lag_hammer_small.3do",
      "lag_dvice_armng.3do",
      "lag_crnk_rsty.3do",
      "vol_key_sharkgate.3do",
      NULL,
      NULL,
      "vol_tram_wheel.3do",
      "vol_key_cuffs.3do",
      "tem_key_statue.3do",
      "tem_key_statue_b.3do",
      "tem_key_mnky.3do",
      "tem_sharkey.3do",
      "teo_key_water.3do",
      "teo_idol_bird.3do",
      "teo_idol_fish.3do",
      "teo_idol_jag.3do",
      "teo_mirror.3do",
      NULL,
      "gen_icon_crnk.3do",
      "pyr_minecar_whl.3do",
      "pyr_gem_eye.3do",
      "pyr_watch.3do",
      NULL,
      "pyr_ngin_chain.3do",
      "bab_jcan_gas.3do",
      "pyr_kndlng_cone.3do",
      "gen_bucket_wood.3do",
      "sol_oilcan_oz.3do",
      NULL,
      NULL,
      "sol_fuse_rplc.3do",
      NULL,
      "sol_gem_a.3do",
      "sol_gem_b.3do",
      "sol_gem_c.3do",
      NULL,
      "sol_pymd_key.3do",
      "sol_key_oil.3do",
      "gen_lever_stick.3do",
      "nub_anubis_arm.3do",
      "nub_gear_turtle.3do",
      "nub_key_elvtr.3do",
      "nub_rb_eye.3do",
      "inf_robo_head.3do",
      "aet_marduk_key.3do",
      "aet_mirror.3do",
      "shs_plank_2m.3do",
      "tem_pikes_floor.3do",
      "pru_key_sqr.3do",
      "gen_icon_bonusmap.3do",
      NULL,
      "iq_icon.3do",
      "gen_icon_help.3do",
      "gen_icon_camera.3do",
      "gen_icon_film.3do",
      "gen_icon_telgrf.3do",
      "gen_icon_type.3do",
      "gen_icon_tv.3do",
      "gen_icon_radio.3do",
      "gen_icon_exit.3do"
    };
    memcpy(&JonesHud_apMenuIconModelNames, &JonesHud_apMenuIconModelNames_tmp, sizeof(JonesHud_apMenuIconModelNames));
    
    char *JonesHud_apItemNames_tmp[134] = {
      "JONES_STR_INV_FISTS",
      "JONES_STR_INV_WHIP",
      "JONES_STR_INV_REVOLVER",
      "JONES_STR_INV_TOKEREV",
      "JONES_STR_INV_MAUSER",
      "JONES_STR_INV_SIMONOV",
      "JONES_STR_INV_MACHETE",
      "JONES_STR_INV_PPSH41",
      "JONES_STR_INV_TOZ34",
      "JONES_STR_INV_GRENADE",
      "JONES_STR_INV_SATCHEL",
      "JONES_STR_INV_BAZOOKA",
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      "JONES_STR_INV_MEDICINE",
      "JONES_STR_INV_1STAID",
      "JONES_STR_INV_HERBSML",
      "JONES_STR_INV_HERBLARGE",
      "JONES_STR_INV_VENOM",
      "JONES_STR_INV_TICKET",
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
      "JONES_STR_INV_TREASURE",
      "JONES_STR_INV_LIGHTER",
      "JONES_STR_INV_CHALK",
      "JONES_STR_INV_SEISMIC",
      "JONES_STR_INV_INVISO",
      "JONES_STR_INV_ANTIGRAV",
      "JONES_STR_INV_POWER",
      "JONES_STR_INV_DILATOR",
      "JONES_STR_INV_SHARD",
      "JONES_STR_INV_EGEAR",
      "JONES_STR_INV_TRNKEY",
      "JONES_STR_INV_TBLA",
      "JONES_STR_INV_TBLB",
      "JONES_STR_INV_TBLC",
      "JONES_STR_INV_MARDUK",
      "JONES_STR_INV_DFLRFT",
      "JONES_STR_INV_RFTKIT",
      "JONES_STR_INV_CDLA",
      "JONES_STR_INV_CDLB",
      "JONES_STR_INV_CDLC",
      "JONES_STR_INV_CDLD",
      "JONES_STR_INV_COIN",
      "JONES_STR_INV_SEALKEY",
      "JONES_STR_INV_BULBPOT",
      "JONES_STR_INV_LEAF",
      "JONES_STR_INV_FLOWER",
      "JONES_STR_INV_BRONZEKEY",
      "JONES_STR_INV_LADYKEY",
      "JONES_STR_INV_OILJAR",
      "JONES_STR_INV_BLUDVKEY",
      "JONES_STR_INV_GLDDVKEY",
      "JONES_STR_INV_GRNTDVKEY",
      "JONES_STR_INV_PDLCKKY",
      "JONES_STR_INV_ENTOOL",
      "JONES_STR_INV_ZPROP",
      "JONES_STR_INV_RSTYHMMR",
      "JONES_STR_INV_ARMDVCE",
      "JONES_STR_INV_CRANK",
      "JONES_STR_INV_SHKGTKEY",
      "JONES_STR_INV_BLCKTKL",
      "JONES_STR_INV_SHKLKEY",
      "JONES_STR_INV_TRAMWHEEL",
      "JONES_STR_INV_CUFFKEY",
      "JONES_STR_INV_STUKEYA",
      "JONES_STR_INV_STUKEYB",
      "JONES_STR_INV_MKYKEY",
      "JONES_STR_INV_SHKKEY",
      "JONES_STR_INV_WTRKEY",
      "JONES_STR_INV_BRDIDL",
      "JONES_STR_INV_FSHIDL",
      "JONES_STR_INV_JGRIDL",
      "JONES_STR_INV_MIRROR",
      "JONES_STR_INV_DCKKEY",
      "JONES_STR_INV_CRNK",
      "JONES_STR_INV_MCRWHL",
      "JONES_STR_INV_GEMEYE",
      "JONES_STR_INV_WTCH",
      "JONES_STR_INV_RAIL",
      "JONES_STR_INV_DRVCHAIN",
      "JONES_STR_INV_GASCAN",
      "JONES_STR_INV_KNDLNG",
      "JONES_STR_INV_BUCKET",
      "JONES_STR_INV_OILCAN",
      "JONES_STR_INV_TRACK",
      "JONES_STR_INV_TRCKTIE",
      "JONES_STR_INV_FUSE",
      "JONES_STR_INV_MCRWHL",
      "JONES_STR_INV_GEMA",
      "JONES_STR_INV_GEMB",
      "JONES_STR_INV_GEMC",
      "JONES_STR_INV_HORUSEYE",
      "JONES_STR_INV_PYRKEY",
      "JONES_STR_INV_OILKEY",
      "JONES_STR_INV_STICK",
      "JONES_STR_INV_ARM",
      "JONES_STR_INV_BRZEGEAR",
      "JONES_STR_INV_BRZEKEY",
      "JONES_STR_INV_BOSSEYE",
      "JONES_STR_INV_ROBOT",
      "JONES_STR_INV_AETKEY",
      "JONES_STR_INV_MIRROR",
      "JONES_STR_INV_PLANK",
      "JONES_STR_INV_SPIKE",
      "JONES_STR_INV_SQRKEY",
      "JONES_STR_INV_MAP",
      "JONES_STR_INV_STATS",
      "JONES_STR_INV_STATS",
      "JONES_STR_INV_HELP",
      "JONES_STR_INV_SAVE",
      "JONES_STR_INV_LOAD",
      "JONES_STR_INV_DFCTLY",
      "JONES_STR_INV_CONFIG",
      "JONES_STR_INV_DSPLY",
      "JONES_STR_INV_SND",
      "JONES_STR_INV_EXIT"
    };
    memcpy(&JonesHud_apItemNames, &JonesHud_apItemNames_tmp, sizeof(JonesHud_apItemNames));
    
    int JonesHud_aSoundFxIdxs_tmp[13] = { -1, 52, 54, 53, -1, 57, 56, 59, 60, 61, 62, 136, 137 };
    memcpy(&JonesHud_aSoundFxIdxs, &JonesHud_aSoundFxIdxs_tmp, sizeof(JonesHud_aSoundFxIdxs));
    
    const rdVector4 JonesHud_aCreditFontColors_tmp[12] = {
      { { 1.0f }, { 1.0f }, { 1.0f }, { 1.0f } },
      { { 0.95599997f }, { 0.043000001f }, { 0.88999999f }, { 1.0f } },
      { { 0.59200001f }, { 0.0070000002f }, { 0.98400003f }, { 1.0f } },
      { { 0.011f }, { 0.88999999f }, { 0.98799998f }, { 1.0f } },
      { { 0.0f }, { 0.588f }, { 0.0f }, { 1.0f } },
      { { 0.88999999f }, { 0.97600001f }, { 0.011f }, { 1.0f } },
      { { 1.0f }, { 0.0f }, { 0.50099999f }, { 1.0f } },
      { { 1.0f }, { 0.0f }, { 0.0f }, { 1.0f } },
      { { 0.0f }, { 1.0f }, { 0.0f }, { 1.0f } },
      { { 0.0f }, { 0.0f }, { 1.0f }, { 1.0f } },
      { { 1.0f }, { 0.329f }, { 0.0070000002f }, { 1.0f } },
      { { 0.94499999f }, { 0.70899999f }, { 0.086000003f }, { 1.0f } }
    };
    memcpy((rdVector4 *)&JonesHud_aCreditFontColors, &JonesHud_aCreditFontColors_tmp, sizeof(JonesHud_aCreditFontColors));
    
    tJonesCreditEntry JonesHud_aCredits_tmp[325] = {
      {
        {
          'g',
          'e',
          'n',
          '_',
          '4',
          '_',
          'p',
          'y',
          'r',
          'a',
          'm',
          'i',
          'd',
          '.',
          'm',
          'a',
          't',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0',
          '\0'
        },
        4,
        1
      },
      { "JONES_STR_HGAME", 2, 1 },
      { "(in alphabetical order)", 16, 0 },
      { "     ", 1, 0 },
      { "JONES_STR_TPROJECT", 16, 1 },
      { "HAL BARWOOD", 1, 0 },
      { "gen_4_selfportrait.mat", 4, 2 },
      { "JONES_STR_HENGINE", 2, 2 },
      { "JONES_STR_TLEADPGR", 16, 2 },
      { "PAUL D. LeFEVRE", 1, 0 },
      { "JONES_STR_TPGRS", 16, 2 },
      { "GARY KEITH BRUBAKER", 1, 0 },
      { "PATRICK McCARTHY", 1, 0 },
      { "IFE OLOWE", 1, 0 },
      { "MATTHEW D. RUSSELL", 1, 0 },
      { "STEVE SCHOLL", 1, 0 },
      { "RANDY TUDOR", 1, 0 },
      { "gen_4_sunrise.mat", 4, 3 },
      { "JONES_STR_HWORLD", 2, 3 },
      { "JONES_STR_TLEADLD", 16, 3 },
      { "STEVEN CHEN", 1, 0 },
      { "JONES_STR_TLD", 16, 3 },
      { "JOSEPH CHIANG", 1, 0 },
      { "REED K. DERLETH", 1, 0 },
      { "GEOFF JONES", 1, 0 },
      { "TIM LONGO", 1, 0 },
      { "CHRISTOPHER W. McGEE", 1, 0 },
      { "TIMOTHY R. MILLER", 1, 0 },
      { "DONALD SIELKE", 1, 0 },
      { "PAUL \"Skitoman\" ZABIEREK", 1, 0 },
      { "JONES_STR_TPLCMNT", 16, 3 },
      { "JESSE MOORE", 1, 0 },
      { "gen_4_eye.mat", 4, 4 },
      { "JONES_STR_HART", 2, 4 },
      { "JONES_STR_TART", 16, 4 },
      { "WILLIAM TILLER", 1, 0 },
      { "JONES_STR_TTEXTURE", 16, 4 },
      { "KIM BALESTRERI", 1, 0 },
      { "KATHY HSIEH", 1, 0 },
      { "GREGORY A. KNIGHT", 1, 0 },
      { "KAREN PURDY", 1, 0 },
      { "NATHAN STAPLEY", 1, 0 },
      { "TIM Y. TAO", 1, 0 },
      { "gen_4x_indy2.mat", 4, 5 },
      { "JONES_STR_HMOTION", 2, 5 },
      { "JONES_STR_TLEADANIM", 16, 5 },
      { "DEREK SAKAI", 1, 0 },
      { "JONES_STR_TANIM", 16, 5 },
      { "YOKO (YANG-JA) BALLARD", 1, 0 },
      { "ANSON JEW", 1, 0 },
      { "gen_4_hawk.mat", 4, 6 },
      { "JONES_STR_HSHAPES", 2, 6 },
      { "JONES_STR_TCHAR", 16, 6 },
      { "LEA MAI NGUYEN", 1, 0 },
      { "JONES_STR_TMODEL", 16, 6 },
      { "MIKE DACKO", 1, 0 },
      { "gen_4x_x.mat", 4, 7 },
      { "JONES_STR_HFLASH", 2, 7 },
      { "JONES_STR_TVISUAL", 16, 7 },
      { "JOSEF RICHARDSON", 1, 0 },
      { "gen_4x_check.mat", 4, 8 },
      { "JONES_STR_HARTPATH", 2, 8 },
      { "JONES_STR_TLDARTTECH", 16, 8 },
      { "HARLEY BALDWIN", 1, 0 },
      { "JONES_STR_TARTTECH", 16, 8 },
      { "LISSA KLANOR", 1, 0 },
      { "gen_4x_happy.mat", 4, 9 },
      { "JONES_STR_HDIGGRS", 2, 9 },
      { "JONES_STR_TSNDPGR", 16, 9 },
      { "MIKE McMAHON", 1, 0 },
      { "JONES_STR_TVIDEO", 16, 9 },
      { "VINCE LEE", 1, 0 },
      { "JONES_STR_TVIDEOADPT", 16, 9 },
      { "ANDRE BREMER", 1, 0 },
      { "JONES_STR_TINSTALL", 16, 9 },
      { "DARREN JOHNSON", 1, 0 },
      { "JOE LIGMAN", 1, 0 },
      { "JONES_STR_TTOOL", 16, 9 },
      { "AMIT SHALEV", 1, 0 },
      { "JONES_STR_TSPPGR", 16, 9 },
      { "INGAR SHU", 1, 0 },
      { "HWEI-LI TSAO", 1, 0 },
      { "JONES_STR_TANIM", 16, 9 },
      { "JOHN McLAUGHLIN", 1, 0 },
      { "VAMBERTO MADURO", 1, 0 },
      { "JONES_STR_TEFFECTS", 16, 9 },
      { "C. ANDREW NELSON", 1, 0 },
      { "JONES_STR_TTEXTURE", 16, 9 },
      { "CATHERINE \"Cat\" TILLER", 1, 0 },
      { "gen_4_star.mat", 4, 10 },
      { "JONES_STR_HVOICE", 2, 10 },
      { "JONES_STR_TINDY", 16, 10 },
      { "DOUG LEE", 1, 0 },
      { "JONES_STR_TSOPHIA", 16, 10 },
      { "TASIA VALENZA", 1, 0 },
      { "JONES_STR_TVOL", 16, 10 },
      { "VICTOR RAIDER-WEXLER", 1, 0 },
      { "JONES_STR_TTURNER", 16, 10 },
      { "BRUCE McGILL", 1, 0 },
      { "JONES_STR_TPRIEST", 16, 10 },
      { "CAROLYN SEYMOUR", 1, 0 },
      { "JONES_STR_TBOY", 16, 10 },
      { "GREY DELISLE", 1, 0 },
      { "JONES_STR_TMILITARY", 16, 10 },
      { "ADAM GREGOR", 1, 0 },
      { "ANDREW KOCHERGIN", 1, 0 },
      { "PHIL PROCTOR", 1, 0 },
      { "VLADIMIR ROMANOV", 1, 0 },
      { "JONES_STR_TMARDUK", 16, 10 },
      { "ADAM GREGOR", 1, 0 },
      { "DOUG LEE", 1, 0 },
      { "gen_4_pound.mat", 4, 1 },
      { "JONES_STR_HVPROD", 2, 1 },
      { "JONES_STR_TVPROD", 16, 1 },
      { "DARRAGH O'FARRELL", 1, 0 },
      { "JONES_STR_TVEDIT", 16, 1 },
      { "COYA ELLIOTT", 1, 0 },
      { "CINDY WONG", 1, 0 },
      { "JONES_STR_TVMGR", 16, 1 },
      { "TAMLYNN NIGLIO", 1, 0 },
      { "JONES_STR_TVCOORD", 16, 1 },
      { "PEGGY BARTLETT", 1, 0 },
      { "JONES_STR_TVRECORD", 16, 1 },
      { "SCREENMUSIC STUDIOS", 1, 0 },
      { "Studio City, California", 1, 0 },
      { "LUCASARTS ENTERTAINMENT COMPANY, LLC", 1, 0 },
      { "San Rafael, California", 1, 0 },
      { "gen_4x_circle.mat", 4, 2 },
      { "JONES_STR_HSOUND", 2, 2 },
      { "JONES_STR_TMUSIC", 16, 2 },
      { "CLINT BAJAKIAN", 1, 0 },
      { "JONES_STR_TSNDDSN", 16, 2 },
      { "DAVID LEVISON", 1, 0 },
      { "JONES_STR_TCOMPOSE", 16, 2 },
      { "JOHN WILLIAMS", 1, 0 },
      { "JONES_STR_TSNDASST", 16, 2 },
      { "MICHAEL FRAYNE", 1, 0 },
      { "JORY PRUM", 1, 0 },
      { "JONES_STR_TSNDCOORD", 16, 2 },
      { "KRISTEN BECHT", 1, 0 },
      { "gen_4_five.mat", 4, 3 },
      { "JONES_STR_HPROD", 2, 3 },
      { "JONES_STR_TPRODMGR", 16, 3 },
      { "WAYNE CLINE", 1, 0 },
      { "JONES_STR_TPRODCOORD", 16, 3 },
      { "JENNIFER O'NEAL", 1, 0 },
      { "KELLIE TAUZIN", 1, 0 },
      { "gen_4_skull.mat", 4, 4 },
      { "JONES_STR_HQA", 2, 4 },
      { "JONES_STR_TLEADTEST", 16, 4 },
      { "JOHN \"Buzz\" BUZOLICH", 1, 0 },
      { "JOHN \"Grandpa\" HANNON", 1, 0 },
      { "JONES_STR_TLEADTESTASST", 16, 4 },
      { "BRENT JAY ANDAYA JALIPA II", 1, 0 },
      { "JONES_STR_TTEST", 16, 4 },
      { "PHILLIP \"Philthy\" BERRY", 1, 0 },
      { "GABRIELLE BROWN", 1, 0 },
      { "SHANG-JU CHEN", 1, 0 },
      { "G.W. CHILDS", 1, 0 },
      { "JEFFREY DAY", 1, 0 },
      { "JOHN DRAKE", 1, 0 },
      { "ERIK ELLICOCK", 1, 0 },
      { "BRYAN ERCK", 1, 0 },
      { "DEREK FLIPPO", 1, 0 },
      { "CATHERINE HAIGLER", 1, 0 },
      { "CHANE HOLLANDER", 1, 0 },
      { "HANS LARSON", 1, 0 },
      { "RICARDO LIU", 1, 0 },
      { "TROY MASHBURN", 1, 0 },
      { "CHUCK McFADDEN", 1, 0 },
      { "MATTHEW \"Cyrus\" McMANUS", 1, 0 },
      { "ORION NEMETH", 1, 0 },
      { "TODD STRITTER", 1, 0 },
      { "TORII SWADER", 1, 0 },
      { "JOSEPH TALAVERA II", 1, 0 },
      { "JULIO TORRES", 1, 0 },
      { "JONES_STR_TINTLTEST", 16, 4 },
      { "JEFF SANDERS", 1, 0 },
      { "JONES_STR_TCOMP", 16, 4 },
      { "CHIP HINNENBERG", 1, 0 },
      { "JONES_STR_TCOMPTEST", 16, 4 },
      { "KARSTEN AGLER", 1, 0 },
      { "DARREN BROWN", 1, 0 },
      { "JIM DAVISON", 1, 0 },
      { "MARCUS P. GAINES", 1, 0 },
      { "DOYLE GILSTRAP", 1, 0 },
      { "JASON LAUBOROUGH", 1, 0 },
      { "DAN MIHOERCK", 1, 0 },
      { "CHARLES W. SMITH", 1, 0 },
      { "SCOTT TINGLEY", 1, 0 },
      { "AARON YOUNG", 1, 0 },
      { "JONES_STR_TEBOOK", 16, 4 },
      { "LYNN TAYLOR", 1, 0 },
      { "JONES_STR_TPRODBURN", 16, 4 },
      { "WENDY \"Cupcake\" KAPLAN", 1, 0 },
      { "KELLIE \"Twinky\" WALKER", 1, 0 },
      { "gen_4_questionmark.mat", 4, 5 },
      { "JONES_STR_HSUP", 2, 5 },
      { "JONES_STR_TSUPMGR", 16, 5 },
      { "PAUL PURDY", 1, 0 },
      { "JONES_STR_THINT", 16, 5 },
      { "TABITHA TOSTI", 1, 0 },
      { "gen_4x_indy.mat", 4, 6 },
      { "JONES_STR_HSHOP", 2, 6 },
      { "JONES_STR_TSHOPMGR", 16, 6 },
      { "TOM BYRON", 1, 0 },
      { "JONES_STR_TPRMGR", 16, 6 },
      { "TOM SARRIS", 1, 0 },
      { "JONES_STR_TPACKDSN", 16, 6 },
      { "SOO HOO DESIGN", 1, 0 },
      { "JONES_STR_TPACKPICT", 16, 6 },
      { "DREW STRUZAN", 1, 0 },
      { "BRUCE WOLF", 1, 0 },
      { "JONES_STR_TBOOK", 16, 6 },
      { "JO \"Captain Tripps\" ASHBURN", 1, 0 },
      { "MOLLIE BOERO", 1, 0 },
      { "JONES_STR_TBOOKDSN", 16, 6 },
      { "PATTY HILL", 1, 0 },
      { "JONES_STR_TPRSP", 16, 6 },
      { "HEATHER TWIST", 1, 0 },
      { "JOSH MOORE", 1, 0 },
      { "JONES_STR_TSHOPCOORD", 16, 6 },
      { "ANNE BARSON", 1, 0 },
      { "gen_4_hammer&sickle.mat", 4, 7 },
      { "JONES_STR_HINTL", 2, 7 },
      { "JONES_STR_TLCLINTL", 16, 7 },
      { "ADAM PASZTORY", 1, 0 },
      { "JONES_STR_TINTLDEVSP", 16, 7 },
      { "THERESA O'CONNOR", 1, 0 },
      { "JONES_STR_TINTLPROD", 16, 7 },
      { "BENJAMIN BECKER", 1, 0 },
      { "JONES_STR_TINTLDEV", 16, 7 },
      { "ARIC WILMUNDER", 1, 0 },
      { "JONES_STR_INTLCOORD", 16, 7 },
      { "LEE SUSEN", 1, 0 },
      { "JONES_STR_TINTLPR", 16, 7 },
      { "KATHY APOSTOLI", 1, 0 },
      { "gen_4_alien.mat", 4, 8 },
      { "JONES_STR_HSTAFF", 2, 8 },
      { "JONES_STR_TPRES", 16, 8 },
      { "JACK SORENSEN", 1, 0 },
      { "JONES_STR_TDIRDEV", 16, 8 },
      { "STEVE DAUTERMAN", 1, 0 },
      { "SIMON JEFFERY", 1, 0 },
      { "JONES_STR_TSHOPDIR", 16, 8 },
      { "MARY BIHR", 1, 0 },
      { "JONES_STR_TTECHDIR", 16, 8 },
      { "MALCOLM JOHNSON", 1, 0 },
      { "JONES_STR_TARTDIR", 16, 8 },
      { "KAREN CHELINI", 1, 0 },
      { "JONES_STR_TPRODDIR", 16, 8 },
      { "CAMELA MARTIN", 1, 0 },
      { "JONES_STR_TPRODBIS", 16, 8 },
      { "JEREMY SALESIN", 1, 0 },
      { "JONES_STR_TCTRLR", 16, 8 },
      { "TOM McCARTHY", 1, 0 },
      { "JONES_STR_TQADIR", 16, 8 },
      { "MARK CARTWRIGHT", 1, 0 },
      { "JONES_STR_TQAMGR", 16, 8 },
      { "DAN PETTIT", 1, 0 },
      { "JONES_STR_TSNDMGR", 16, 8 },
      { "MICHAEL LAND", 1, 0 },
      { "JONES_STR_TSALEMGR", 16, 8 },
      { "MEREDITH CAHILL", 1, 0 },
      { "JONES_STR_TINTLMGR", 16, 8 },
      { "LISA STAR", 1, 0 },
      { "JONES_STR_TCHMGR", 16, 8 },
      { "TIM MOORE", 1, 0 },
      { "JONES_STR_TBIS", 16, 8 },
      { "JOCELYN LAMM", 1, 0 },
      { "JANNETT SHIRLEY-PAUL", 1, 0 },
      { "JONES_STR_TADMIN", 16, 8 },
      { "CATHERINE DURAND", 1, 0 },
      { "DENISE GOLLAHER", 1, 0 },
      { "JOHN KNOWLES", 1, 0 },
      { "SANDI MANESIS", 1, 0 },
      { "GABRIEL McDONALD", 1, 0 },
      { "LISA SWART", 1, 0 },
      { "gen_4_ankh.mat", 4, 9 },
      { "JONES_STR_HTHANKS", 2, 9 },
      { "BARBARA BARWOOD", 1, 0 },
      { "MICHELLE MORRIS BRUBAKER", 1, 0 },
      { "THE CHIANG GANG", 1, 0 },
      { "BETH CONNELL & the 008 posse", 1, 0 },
      { "Thanks to JENNIFER for the salsa", 1, 0 },
      { "AMY EWING", 1, 0 },
      { "DR. & MRS. JONES (Bill & Lida)", 1, 0 },
      { "JENNIFER LONGO", 1, 0 },
      { "LIVIA MACKIN", 1, 0 },
      { "RACHEL SAIDMAN", 1, 0 },
      { "SUZIE, HEATHER & KIMMY SIELKE", 1, 0 },
      { "AMY TILLER", 1, 0 },
      { "GINA VENTURI", 1, 0 },
      { "VENUS & MATTHEW", 1, 0 },
      { "ELISA, NICK, JUSTICE & LIBERTY TUDOR", 1, 0 },
      { "TAC", 1, 0 },
      { "BEAN", 1, 0 },
      { "EDISON & OTHELLO", 1, 0 },
      { "MILO & CECIL", 1, 0 },
      { "PIXEL", 1, 0 },
      { "gen_4x_guy.mat", 4, 10 },
      { "JONES_STR_HTIP", 2, 10 },
      { "JONES_STR_TNGINEDEV", 16, 10 },
      { "RAY GRESKO", 1, 0 },
      { "ROB HUEBNER", 1, 0 },
      { "CHE-YUAN WANG", 1, 0 },
      { "WINSTON WOLFF", 1, 0 },
      { "JONES_STR_TCONSOLE", 16, 10 },
      { "PATRICK COSTELLO", 1, 0 },
      { "JONATHAN MENZIES", 1, 0 },
      { "NICK PAVIS", 1, 0 },
      { "JONES_STR_TPGRSUP", 16, 10 },
      { "BOB I. JUDELSON", 1, 0 },
      { "CHRIS KASTENSMIDT", 1, 0 },
      { "THE INTEL CORPORATION", 1, 0 },
      { "JONES_STR_TBOW", 16, 10 },
      { "HARRISON FORD", 1, 0 },
      { "STEVEN SPIELBERG", 1, 0 },
      { "gen_4_r2d2.mat", 4, 1 },
      { "JONES_STR_HSPTHXS", 2, 1 },
      { "GEORGE LUCAS", 1, 0 },
      { "mat\\gg_a.mat", 12, 11 },
      { "mat\\gg_b.mat", 12, 11 },
      { "\xA9 LUCASARTS ENTERTAINMENT COMPANY LLC", 2, 0 },
      { "JONES_STR_HCOPY", 2, 0 }
    };
    memcpy(&JonesHud_aCredits, &JonesHud_aCredits_tmp, sizeof(JonesHud_aCredits));
    
    unsigned int JonesHud_msecMenuItemMoveDuration_tmp = 250u;
    memcpy(&JonesHud_msecMenuItemMoveDuration, &JonesHud_msecMenuItemMoveDuration_tmp, sizeof(JonesHud_msecMenuItemMoveDuration));
    
    SithWeaponId JonesHud_selectedWeaponID_tmp = -1;
    memcpy(&JonesHud_selectedWeaponID, &JonesHud_selectedWeaponID_tmp, sizeof(JonesHud_selectedWeaponID));
    
    float JonesHud_curEnduranceIndAlpha_tmp = 0.2f;
    memcpy(&JonesHud_curEnduranceIndAlpha, &JonesHud_curEnduranceIndAlpha_tmp, sizeof(JonesHud_curEnduranceIndAlpha));
    
    float JonesHud_curEnduranceState_tmp = -1.0f;
    memcpy(&JonesHud_curEnduranceState, &JonesHud_curEnduranceState_tmp, sizeof(JonesHud_curEnduranceState));
    
    int JonesHud_curKeyId_tmp = -1;
    memcpy(&JonesHud_curKeyId, &JonesHud_curKeyId_tmp, sizeof(JonesHud_curKeyId));
    
    int JonesHud_curWhoopsSndFxIdx_tmp = -1;
    memcpy(&JonesHud_curWhoopsSndFxIdx, &JonesHud_curWhoopsSndFxIdx_tmp, sizeof(JonesHud_curWhoopsSndFxIdx));
    
    memset(&JonesHud_bCutsceneStart, 0, sizeof(JonesHud_bCutsceneStart));
    memset(&JonesHud_healthIndBarPos, 0, sizeof(JonesHud_healthIndBarPos));
    memset(&JonesHud_msecDeltaTime, 0, sizeof(JonesHud_msecDeltaTime));
    memset(&JonesHud_apMenuItems, 0, sizeof(JonesHud_apMenuItems));
    memset(&JonesHud_hudState, 0, sizeof(JonesHud_hudState));
    memset(&JonesHud_msecGameOverWaitDeltaTime, 0, sizeof(JonesHud_msecGameOverWaitDeltaTime));
    memset(&JonesHud_enduranceIndBarPos, 0, sizeof(JonesHud_enduranceIndBarPos));
    memset(&JonesHud_creditsSomeIdx, 0, sizeof(JonesHud_creditsSomeIdx));
    memset(&JonesHud_screenHeightScalar, 0, sizeof(JonesHud_screenHeightScalar));
    memset(&JonesHud_screenWidthScalar, 0, sizeof(JonesHud_screenWidthScalar));
    memset(&JonesHud_selectedTreasuresMenuItemID, 0, sizeof(JonesHud_selectedTreasuresMenuItemID));
    memset(&JonesHud_healthIndRect, 0, sizeof(JonesHud_healthIndRect));
    memset(&JonesHud_indScale, 0, sizeof(JonesHud_indScale));
    memset(&JonesHud_curCelNum, 0, sizeof(JonesHud_curCelNum));
    memset(&JonesHud_msecTime, 0, sizeof(JonesHud_msecTime));
    memset(&JonesHud_camViewMatrix, 0, sizeof(JonesHud_camViewMatrix));
    memset(&JonesHud_pCreditsFont2, 0, sizeof(JonesHud_pCreditsFont2));
    memset(&JonesHud_aSlectedNdsFilePath, 0, sizeof(JonesHud_aSlectedNdsFilePath));
    memset(&JonesHud_rootMenuItemId, 0, sizeof(JonesHud_rootMenuItemId));
    memset(&JonesHud_maxItemZ, 0, sizeof(JonesHud_maxItemZ));
    memset(&JonesHud_bIMPState, 0, sizeof(JonesHud_bIMPState));
    memset(&JonesHud_bBonusMapBought, 0, sizeof(JonesHud_bBonusMapBought));
    memset(&JonesHud_apCreditsMats, 0, sizeof(JonesHud_apCreditsMats));
    memset(&JonesHud_pCreditsFont1, 0, sizeof(JonesHud_pCreditsFont1));
    memset(&JonesHud_msecLastKeyPressTime, 0, sizeof(JonesHud_msecLastKeyPressTime));
    memset(&JonesHud_selectedWeaponMenuItemID, 0, sizeof(JonesHud_selectedWeaponMenuItemID));
    memset(&JonesHud_selectedOptionsMenuItemID, 0, sizeof(JonesHud_selectedOptionsMenuItemID));
    memset(&JonesHud_msecRaftIndicatorFadeTime, 0, sizeof(JonesHud_msecRaftIndicatorFadeTime));
    memset(&JonesHud_foundTreasureValue, 0, sizeof(JonesHud_foundTreasureValue));
    memset(&JonesHud_curHealth, 0, sizeof(JonesHud_curHealth));
    memset(&JonesHud_creditTextHeight, 0, sizeof(JonesHud_creditTextHeight));
    memset(&JonesHud_nearClipPlane, 0, sizeof(JonesHud_nearClipPlane));
    memset(&JonesHud_aActivateKeyIds, 0, sizeof(JonesHud_aActivateKeyIds));
    memset(&JonesHud_aCosSinTableScaled, 0, sizeof(JonesHud_aCosSinTableScaled));
    memset(&JonesHud_bInterfaceEnabled, 0, sizeof(JonesHud_bInterfaceEnabled));
    memset(&JonesHud_bufferHeight, 0, sizeof(JonesHud_bufferHeight));
    memset(&JonesHud_aCreditsTextHeights, 0, sizeof(JonesHud_aCreditsTextHeights));
    memset(&JonesHud_levelStartIQPoints, 0, sizeof(JonesHud_levelStartIQPoints));
    memset(&JonesHud_enduranceRect, 0, sizeof(JonesHud_enduranceRect));
    memset(&JonesHud_dword_554FDC, 0, sizeof(JonesHud_dword_554FDC));
    memset(&JonesHud_flt_554FE0, 0, sizeof(JonesHud_flt_554FE0));
    memset(&JonesHud_flt_554FE4, 0, sizeof(JonesHud_flt_554FE4));
    memset(&JonesHud_creditsSomeIdx_0, 0, sizeof(JonesHud_creditsSomeIdx_0));
    memset(&JonesHud_selectedItemsMenuItemID, 0, sizeof(JonesHud_selectedItemsMenuItemID));
    memset(&JonesHud_numFoundTreasures, 0, sizeof(JonesHud_numFoundTreasures));
    memset(&JonesHud_creditsSomeIdx_1, 0, sizeof(JonesHud_creditsSomeIdx_1));
    memset(&JonesHud_aSoundFxHandles, 0, sizeof(JonesHud_aSoundFxHandles));
    memset(&JonesHud_flt_555034, 0, sizeof(JonesHud_flt_555034));
    memset(&JonesHud_flt_555038, 0, sizeof(JonesHud_flt_555038));
    memset(&JonesHud_flt_55503C, 0, sizeof(JonesHud_flt_55503C));
    memset(&JonesHud_bufferWidth, 0, sizeof(JonesHud_bufferWidth));
    memset(&JonesHud_healthIndAlpha, 0, sizeof(JonesHud_healthIndAlpha));
    memset(&JonesHud_bFadeHealthHUD, 0, sizeof(JonesHud_bFadeHealthHUD));
    memset(&JonesHud_aCosSinTable, 0, sizeof(JonesHud_aCosSinTable));
    memset(&JonesHud_msecHealthIndLastFadeUpdate, 0, sizeof(JonesHud_msecHealthIndLastFadeUpdate));
    memset(&JonesHud_playerHealthFadeStart, 0, sizeof(JonesHud_playerHealthFadeStart));
    memset(&JonesHud_bStartup, 0, sizeof(JonesHud_bStartup));
    memset(&JonesHud_bOpen, 0, sizeof(JonesHud_bOpen));
    memset(&JonesHud_pArrowUp, 0, sizeof(JonesHud_pArrowUp));
    memset(&JonesHud_pArrowDown, 0, sizeof(JonesHud_pArrowDown));
    memset(&JonesHud_bHealthIndFadeSet, 0, sizeof(JonesHud_bHealthIndFadeSet));
    memset(&JonesHud_pHudBaseMat, 0, sizeof(JonesHud_pHudBaseMat));
    memset(&JonesHud_pHealthOverlay, 0, sizeof(JonesHud_pHealthOverlay));
    memset(&JonesHud_pHealthOverlayHitMat, 0, sizeof(JonesHud_pHealthOverlayHitMat));
    memset(&JonesHud_pPoisonedOverlayMat, 0, sizeof(JonesHud_pPoisonedOverlayMat));
    memset(&JonesHud_pEnduranceOverlayMat, 0, sizeof(JonesHud_pEnduranceOverlayMat));
    memset(&JonesHud_pMenuFont, 0, sizeof(JonesHud_pMenuFont));
    memset(&JonesHud_pMenuItemLinkedList, 0, sizeof(JonesHud_pMenuItemLinkedList));
    memset(&JonesHud_pCloseMenuItem, 0, sizeof(JonesHud_pCloseMenuItem));
    memset(&JonesHud_item_flag_state_55514C, 0, sizeof(JonesHud_item_flag_state_55514C));
    memset(&JonesHud_pCurSelectedMenuItem, 0, sizeof(JonesHud_pCurSelectedMenuItem));
    memset(&JonesHud_pCurInvChangedItem, 0, sizeof(JonesHud_pCurInvChangedItem));
    memset(&JonesHud_bExitActivated, 0, sizeof(JonesHud_bExitActivated));
    memset(&JonesHud_dword_55515C, 0, sizeof(JonesHud_dword_55515C));
    memset(&JonesHud_bRestoreActivated, 0, sizeof(JonesHud_bRestoreActivated));
    memset(&JonesHud_bRestoreGameStatistics, 0, sizeof(JonesHud_bRestoreGameStatistics));
    memset(&JonesHud_bItemActivated, 0, sizeof(JonesHud_bItemActivated));
    memset(&JonesHud_bMenuEnabled, 0, sizeof(JonesHud_bMenuEnabled));
    memset(&JonesHud_pHudCamera, 0, sizeof(JonesHud_pHudCamera));
    memset(&JonesHud_pHudCanvas, 0, sizeof(JonesHud_pHudCanvas));
    memset(&JonesHud_bMapOpen, 0, sizeof(JonesHud_bMapOpen));
    memset(&JonesHud_bShowMenu, 0, sizeof(JonesHud_bShowMenu));
    memset(&JonesHud_hCurSndChannel, 0, sizeof(JonesHud_hCurSndChannel));
    memset(&JonesHud_bFadingHealthHUD, 0, sizeof(JonesHud_bFadingHealthHUD));
    memset(&JonesHud_hitOverlayAlphaState, 0, sizeof(JonesHud_hitOverlayAlphaState));
    memset(&JonesHud_hitOverlayAlpha, 0, sizeof(JonesHud_hitOverlayAlpha));
    memset(&JonesHud_bKeyStateUpdated, 0, sizeof(JonesHud_bKeyStateUpdated));
    memset(&JonesHud_hProcessHelp, 0, sizeof(JonesHud_hProcessHelp));
    memset(&JonesHud_msecCreditsElapsedTime, 0, sizeof(JonesHud_msecCreditsElapsedTime));
    memset(&JonesHud_msecCreditsFadeStart, 0, sizeof(JonesHud_msecCreditsFadeStart));
    memset(&JonesHud_creditsSomeHeightRatio, 0, sizeof(JonesHud_creditsSomeHeightRatio));
    memset(&JonesHud_bFinishingCredits, 0, sizeof(JonesHud_bFinishingCredits));
    memset(&JonesHud_bSomeCreditsBoolean, 0, sizeof(JonesHud_bSomeCreditsBoolean));
}

int JonesHud_Startup(void)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_Startup);
}

void JonesHud_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(JonesHud_Shutdown);
}

int J3DAPI JonesHud_Open()
{
    return J3D_TRAMPOLINE_CALL(JonesHud_Open);
}

int JonesHud_Close(void)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_Close);
}

void J3DAPI JonesHud_ToggleMenu()
{
    J3D_TRAMPOLINE_CALL(JonesHud_ToggleMenu);
}

void J3DAPI JonesHud_EnableMenu(int bEnable)
{
    J3D_TRAMPOLINE_CALL(JonesHud_EnableMenu, bEnable);
}

int J3DAPI JonesHud_IsMenuEnabled()
{
    return J3D_TRAMPOLINE_CALL(JonesHud_IsMenuEnabled);
}

void J3DAPI JonesHud_Render()
{
    J3D_TRAMPOLINE_CALL(JonesHud_Render);
}

void J3DAPI JonesHud_Update(const SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(JonesHud_Update, pWorld);
}

int J3DAPI JonesHud_SetCanvasSize(int width, int height)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_SetCanvasSize, width, height);
}

void J3DAPI JonesHud_UpdateSinCosTable()
{
    J3D_TRAMPOLINE_CALL(JonesHud_UpdateSinCosTable);
}

void J3DAPI JonesHud_UpdateHUDLayout(unsigned int width, unsigned int height)
{
    J3D_TRAMPOLINE_CALL(JonesHud_UpdateHUDLayout, width, height);
}

void J3DAPI JonesHud_MenuOpen()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuOpen);
}

void JonesHud_MenuClose(void)
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuClose);
}

void J3DAPI JonesHud_StartItemTranslation(JonesHudMenuItem* pItem, uint32_t msecDuration, float distance, int bMoveUp)
{
    J3D_TRAMPOLINE_CALL(JonesHud_StartItemTranslation, pItem, msecDuration, distance, bMoveUp);
}

int J3DAPI JonesHud_HasTimeElapsed(unsigned int msecDuration, unsigned int msecDeltaTime, unsigned int msecTime)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_HasTimeElapsed, msecDuration, msecDeltaTime, msecTime);
}

void J3DAPI JonesHud_RenderEnduranceIndicator(float enduranceState)
{
    J3D_TRAMPOLINE_CALL(JonesHud_RenderEnduranceIndicator, enduranceState);
}

void J3DAPI JonesHud_DrawEnduranceIndicator(float state, float alpha)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawEnduranceIndicator, state, alpha);
}

void J3DAPI JonesHud_SetFadeHealthHUD(int bShow, int bFade)
{
    J3D_TRAMPOLINE_CALL(JonesHud_SetFadeHealthHUD, bShow, bFade);
}

int J3DAPI JonesHud_RenderFadeHealthIndicator(int bFade)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_RenderFadeHealthIndicator, bFade);
}

void J3DAPI JonesHud_DrawHealthIndicator(float hitDelta, float health, float alpha)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawHealthIndicator, hitDelta, health, alpha);
}

void J3DAPI JonesHud_DrawHealthHitOverlay(float hitDelta, float z, float rhw)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawHealthHitOverlay, hitDelta, z, rhw);
}

void J3DAPI JonesHud_RenderHealthIndicator(float healthState)
{
    J3D_TRAMPOLINE_CALL(JonesHud_RenderHealthIndicator, healthState);
}

void J3DAPI JonesHud_DrawHealthIndicatorBase(float state, float alpha, float z, float w)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawHealthIndicatorBase, state, alpha, z, w);
}

void J3DAPI JonesHud_DrawHealthIndicatorBar(float health, float alpha, float z, float w)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawHealthIndicatorBar, health, alpha, z, w);
}

// Note, pos is in screen coords
void J3DAPI JonesHud_DrawIndicatorBar(const rdVector4* pPos, float scale, const rdVector4* pColor, float angle, int bArc)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawIndicatorBar, pPos, scale, pColor, angle, bArc);
}

void J3DAPI JonesHud_Draw(const rdMaterial* pMaterial, const JonesHudRect* rect, float z, float rhw, const rdVector4* pColor, int celNum, int bAlpha)
{
    J3D_TRAMPOLINE_CALL(JonesHud_Draw, pMaterial, rect, z, rhw, pColor, celNum, bAlpha);
}

void J3DAPI JonesHud_ProcessMenuItems()
{
    J3D_TRAMPOLINE_CALL(JonesHud_ProcessMenuItems);
}

void J3DAPI JonesHud_MenuMoveLeft()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuMoveLeft);
}

void J3DAPI JonesHud_MenuMoveRight()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuMoveRight);
}

void J3DAPI JonesHud_MenuMoveDown()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuMoveDown);
}

void J3DAPI JonesHud_SetSelectedMenuItem(int menuId, JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_SetSelectedMenuItem, menuId, pItem);
}

void J3DAPI JonesHud_MenuMoveUp()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuMoveUp);
}

void J3DAPI JonesHud_BindActivateControlKeys(int* aKeyIds, int numKeys)
{
    J3D_TRAMPOLINE_CALL(JonesHud_BindActivateControlKeys, aKeyIds, numKeys);
}

int J3DAPI JonesHud_GetKey(unsigned int keyId)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_GetKey, keyId);
}

int JonesHud_InitializeMenu(void)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_InitializeMenu);
}

void JonesHud_InitializeMenuSounds(void)
{
    J3D_TRAMPOLINE_CALL(JonesHud_InitializeMenuSounds);
}

JonesHudMenuItem* J3DAPI JonesHud_NewMenuItem(rdModel3* pItemIcon3)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_NewMenuItem, pItemIcon3);
}

void J3DAPI JonesHud_FreeMenuItem(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_FreeMenuItem, pItem);
}

void J3DAPI JonesHud_UpdateItem(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_UpdateItem, pItem);
}

void J3DAPI JonesHud_RenderMenuItems(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_RenderMenuItems, pItem);
}

// Function formats and displays inventory items and its text
void J3DAPI JonesHud_RenderMenuItem(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_RenderMenuItem, pItem);
}

void J3DAPI JonesHud_MenuActivateItem()
{
    J3D_TRAMPOLINE_CALL(JonesHud_MenuActivateItem);
}

void J3DAPI JonesHud_ResetMenuItems()
{
    J3D_TRAMPOLINE_CALL(JonesHud_ResetMenuItems);
}

void J3DAPI JonesHud_SetLeftRightItems(JonesHudMenuItem* pItem1, JonesHudMenuItem* pItem2)
{
    J3D_TRAMPOLINE_CALL(JonesHud_SetLeftRightItems, pItem1, pItem2);
}

void J3DAPI JonesHud_SetDownUpItems(JonesHudMenuItem* pItem1, JonesHudMenuItem* pItem2)
{
    J3D_TRAMPOLINE_CALL(JonesHud_SetDownUpItems, pItem1, pItem2);
}

void J3DAPI JonesHud_sub_4198E0(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_sub_4198E0, pItem);
}

void J3DAPI JonesHud_sub_419B50(JonesHudMenuItem* pItem)
{
    J3D_TRAMPOLINE_CALL(JonesHud_sub_419B50, pItem);
}

void J3DAPI JonesHud_InventoryItemChanged(int typeId)
{
    J3D_TRAMPOLINE_CALL(JonesHud_InventoryItemChanged, typeId);
}

void J3DAPI JonesHud_RenderInventoryItemChange()
{
    J3D_TRAMPOLINE_CALL(JonesHud_RenderInventoryItemChange);
}

void J3DAPI JonesHud_DrawMenuItemIcon(const JonesHudMenuItem* pItem, float scale)
{
    J3D_TRAMPOLINE_CALL(JonesHud_DrawMenuItemIcon, pItem, scale);
}

// Returns 1 when bonus map was bought
int JonesHud_ShowLevelCompleted(void)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_ShowLevelCompleted);
}

HANDLE J3DAPI JonesHud_OpenHelp(HANDLE proces)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_OpenHelp, proces);
}

void J3DAPI JonesHud_ShowGameOverDialog(int bPlayDiedMusic)
{
    J3D_TRAMPOLINE_CALL(JonesHud_ShowGameOverDialog, bPlayDiedMusic);
}

float J3DAPI JonesHud_GetHealthBarAlpha()
{
    return J3D_TRAMPOLINE_CALL(JonesHud_GetHealthBarAlpha);
}

void J3DAPI JonesHud_SetHealthBarAlpha(float a1)
{
    J3D_TRAMPOLINE_CALL(JonesHud_SetHealthBarAlpha, a1);
}

void J3DAPI JonesHud_CutsceneStart(int a1)
{
    J3D_TRAMPOLINE_CALL(JonesHud_CutsceneStart, a1);
}

void J3DAPI JonesHud_EnableInterface(int bEnable)
{
    J3D_TRAMPOLINE_CALL(JonesHud_EnableInterface, bEnable);
}

int J3DAPI JonesHud_DrawCredits(int bEndCredits, tSoundChannelHandle hSndChannel)
{
    return J3D_TRAMPOLINE_CALL(JonesHud_DrawCredits, bEndCredits, hSndChannel);
}

void J3DAPI JonesHud_InitializeGameStatistics()
{
    J3D_TRAMPOLINE_CALL(JonesHud_InitializeGameStatistics);
}

void J3DAPI JonesHud_RestoreGameStatistics()
{
    J3D_TRAMPOLINE_CALL(JonesHud_RestoreGameStatistics);
}

void J3DAPI JonesHud_RestoreTreasuresStatistics()
{
    J3D_TRAMPOLINE_CALL(JonesHud_RestoreTreasuresStatistics);
}
