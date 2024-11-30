#include <stdio.h>
#include <stdint.h>

#include "types.h" // Should be included first due to Windows.h / CommCtrl.h conflict

#include <j3dcore/j3d.h>
#include <j3dcore/j3dhook.h>

#include "Display/JonesConsole.h"
#include "Display/JonesHud.h"
#include "Display/jonesConfig.h"
#include "Display/JonesDisplay.h"
#include "Gui/JonesDialog.h"
#include "Main/JonesMain.h"
#include "Main/JonesFile.h"
#include "Main/jonesString.h"
#include "Play/jonesCog.h"
#include "Play/JonesControl.h"
#include "Play/jonesInventory.h"
#include "RTI/addresses.h"
#include "RTI/symbols.h"

#include <rdroid/Engine/rdCamera.h>
#include <rdroid/Engine/rdMaterial.h>
#include <rdroid/Engine/rdKeyframe.h>
#include <rdroid/Engine/rdClip.h>
#include <rdroid/Engine/rdQClip.h>
#include <rdroid/Engine/rdCanvas.h>
#include <rdroid/Engine/rdThing.h>
#include <rdroid/Engine/rdPuppet.h>
#include <rdroid/Engine/rdLight.h>
#include <rdroid/Main/rdroid.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Math/rdMath.h>
#include <rdroid/Primitives/rdWallpaper.h>
#include <rdroid/Primitives/rdModel3.h>
#include <rdroid/Primitives/rdParticle.h>
#include <rdroid/Primitives/rdFont.h>
#include <rdroid/Primitives/rdPrimit2.h>
#include <rdroid/Primitives/rdPolyline.h>
#include <rdroid/Primitives/rdSprite.h>
#include <rdroid/Primitives/rdPrimit3.h>
#include <rdroid/Raster/rdCache.h>
#include <rdroid/Raster/rdFace.h>

#include <sith/AI/sithAIInstinct.h>
#include <sith/AI/sithAI.h>
#include <sith/AI/sithAIClass.h>
#include <sith/AI/sithAIMove.h>
#include <sith/AI/sithAIUtil.h>
#include <sith/AI/sithAIAwareness.h>
#include <sith/Cog/sithCogYacc.h>
#include <sith/Cog/sithCogParse.h>
#include <sith/Cog/sithCog.h>
#include <sith/Cog/sithCogFunctionAI.h>
#include <sith/Cog/sithCogExec.h>
#include <sith/Cog/sithCogFunctionPlayer.h>
#include <sith/Cog/sithCogFunctionSector.h>
#include <sith/Cog/sithCogFunctionSound.h>
#include <sith/Cog/sithCogFunctionSurface.h>
#include <sith/Cog/sithCogFunctionThing.h>
#include <sith/Cog/sithCogFunction.h>
#include <sith/Devices/sithSoundMixer.h>
#include <sith/Devices/sithControl.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Devices/sithSound.h>
#include <sith/Devices/sithComm.h>
#include <sith/Dss/sithGamesave.h>
#include <sith/Dss/sithMulti.h>
#include <sith/Dss/sithDSS.h>
#include <sith/Dss/sithDSSCog.h>
#include <sith/Dss/sithDSSThing.h>
#include <sith/Engine/sithCamera.h>
#include <sith/Engine/sithRender.h>
#include <sith/Engine/sithRenderSky.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Engine/sithAnimate.h>
#include <sith/Engine/sithPhysics.h>
#include <sith/Engine/sithCollision.h>
#include <sith/Engine/sithIntersect.h>
#include <sith/Engine/sithShadow.h>
#include <sith/Engine/sithParticle.h>
#include <sith/Engine/sithPathMove.h>
#include <sith/Gameplay/sithOverlayMap.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Gameplay/sithPlayerControls.h>
#include <sith/Gameplay/sithInventory.h>
#include <sith/Gameplay/sithPlayerActions.h>
#include <sith/Gameplay/sithFX.h>
#include <sith/Gameplay/sithWhip.h>
#include <sith/Gameplay/sithVehicleControls.h>
#include <sith/Gameplay/sithTime.h>
#include <sith/Gameplay/sithEvent.h>
#include <sith/Main/sithMain.h>
#include <sith/Main/sithString.h>
#include <sith/Main/sithCommand.h>
#include <sith/World/sithWorld.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithVoice.h>
#include <sith/World/sithWeapon.h>
#include <sith/World/sithSoundClass.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithTemplate.h>
#include <sith/World/sithMaterial.h>
#include <sith/World/sithSurface.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithSprite.h>
#include <sith/World/sithExplosion.h>
#include <sith/World/sithActor.h>
#include <sith/World/sithItem.h>
#include <sith/World/sithPVS.h>

#include <sound/Driver.h>
#include <sound/AudioLib.h>
#include <sound/Sound.h>

#include <std/General/stdHashtbl.h>
#include <std/General/stdMath.h>
#include <std/General/std.h>
#include <std/General/stdMemory.h>
#include <std/General/stdConffile.h>
#include <std/General/stdPlatform.h>
#include <std/General/stdEffect.h>
#include <std/General/stdStrTable.h>
#include <std/General/stdBmp.h>
#include <std/General/stdFnames.h>
#include <std/General/stdUtil.h>
#include <std/General/stdFileUtil.h>
#include <std/General/stdCircBuf.h>
#include <std/General/stdColor.h>
#include <std/General/stdLinkList.h>
#include <std/Win95/stdControl.h>
#include <std/Win95/stdDisplay.h>
#include <std/Win95/std3D.h>
#include <std/Win95/stdComm.h>
#include <std/Win95/stdWin95.h>
#include <std/Win95/stdGob.h>
#include <std/Win95/stdConsole.h>

#include <w32util/wuRegistry.h>
#include <wkernel/wkernel.h>

static const char* appName = "Open Jones 3D";

bool InstallHooks(void);
bool ResetGlobals(void);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
    J3D_UNUSED(hModule);
    J3D_UNUSED(lpReserved);
    switch ( dwReason )
    {
        case DLL_PROCESS_ATTACH:
        {
            // Enable HIDPI
            SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

        #ifdef _DEBUG
            // For debugging purposes to stop execution here
            MessageBox(NULL, "Attached to Indy3D.exe process.", "Jones3D",
                MB_ICONINFORMATION | MB_DEFBUTTON1
            );
        #endif

            // Init function hooks
            if ( !InstallHooks() )
            {
                printf("CRITICAL ERROR: Failed to install hooks!\n");
                MessageBox(NULL, "Failed to install function hooks!", "Jones3D",
                    MB_ICONINFORMATION | MB_DEFBUTTON1
                );
            }

            if ( !ResetGlobals() )
            {
                printf("CRITICAL ERROR: Failed to reset global vars!\n");
                MessageBox(NULL, "Failed to reset global variables!", "Jones3D",
                    MB_ICONINFORMATION | MB_DEFBUTTON1
                );
            }
        }
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

int Startup(const char* aCmd)
{
    if ( JonesMain_Startup(aCmd) )
    {
        JonesMain_Shutdown();
        return -1;
    }
    return 0;
}

// Indy3D.exe entry point
int WINAPI Indy3D_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    JonesMain_g_mainMutex = CreateMutex(NULL, /*CreateMutex=*/TRUE, "INDY3D");
    if ( GetLastError() != ERROR_ALREADY_EXISTS )
    {
        wkernel_SetProcessProc(JonesMain_Process);
        wkernel_SetStartupCallback(Startup);
        wkernel_SetShutdownCallback(JonesMain_Shutdown);
        return wkernel_Run(hInstance, hPrevInstance, lpCmdLine, nShowCmd, appName);
    }

    CloseHandle(JonesMain_g_mainMutex);
    return -1;
}

bool InstallHooks(void)
{
    J3DHookContext ctx;
    if ( !J3DStartHookContext(&ctx, EXE_TEXT_START_ADDR, EXE_TEXT_END_ADDR) ) {
        return false;
    }

    J3D_HOOKFUNC(Indy3D_WinMain);

    AudioLib_InstallHooks();
    Driver_InstallHooks();

    JonesConsole_InstallHooks();
    JonesControl_InstallHooks();
    JonesDialog_InstallHooks();
    JonesDisplay_InstallHooks();
    JonesFile_InstallHooks();
    JonesHud_InstallHooks();
    JonesMain_InstallHooks();

    Sound_InstallHooks();

    jonesCog_InstallHooks();
    jonesConfig_InstallHooks();
    jonesInventory_InstallHooks();
    jonesString_InstallHooks();

    rdCache_InstallHooks();
    rdCamera_InstallHooks();
    rdCanvas_InstallHooks();
    rdClip_InstallHooks();
    rdFace_InstallHooks();
    rdFont_InstallHooks();
    rdKeyframe_InstallHooks();
    rdLight_InstallHooks();
    rdMaterial_InstallHooks();
    rdMath_InstallHooks();
    rdMatrix_InstallHooks();
    rdModel3_InstallHooks();
    rdParticle_InstallHooks();
    rdPolyline_InstallHooks();
    rdPrimit2_InstallHooks();
    rdPrimit3_InstallHooks();
    rdPuppet_InstallHooks();
    rdQClip_InstallHooks();
    rdSprite_InstallHooks();
    rdThing_InstallHooks();
    rdVector_InstallHooks();
    rdWallpaper_InstallHooks();
    rdroid_InstallHooks();

    sithAIAwareness_InstallHooks();
    sithAIClass_InstallHooks();
    sithAIInstinct_InstallHooks();
    sithAIMove_InstallHooks();
    sithAIUtil_InstallHooks();
    sithAI_InstallHooks();
    sithActor_InstallHooks();
    sithAnimate_InstallHooks();
    sithCamera_InstallHooks();
    sithCogExec_InstallHooks();
    sithCogFunctionAI_InstallHooks();
    sithCogFunctionPlayer_InstallHooks();
    sithCogFunctionSector_InstallHooks();
    sithCogFunctionSound_InstallHooks();
    sithCogFunctionSurface_InstallHooks();
    sithCogFunctionThing_InstallHooks();
    sithCogFunction_InstallHooks();
    sithCogParse_InstallHooks();
    sithCogYacc_InstallHooks();
    sithCog_InstallHooks();
    sithCollision_InstallHooks();
    sithComm_InstallHooks();
    sithCommand_InstallHooks();
    sithConsole_InstallHooks();
    sithControl_InstallHooks();
    sithDSSCog_InstallHooks();
    sithDSSThing_InstallHooks();
    sithDSS_InstallHooks();
    sithEvent_InstallHooks();
    sithExplosion_InstallHooks();
    sithFX_InstallHooks();
    sithGamesave_InstallHooks();
    sithIntersect_InstallHooks();
    sithInventory_InstallHooks();
    sithItem_InstallHooks();
    sithMain_InstallHooks();
    sithMaterial_InstallHooks();
    sithModel_InstallHooks();
    sithMulti_InstallHooks();
    sithOverlayMap_InstallHooks();
    sithPVS_InstallHooks();
    sithParticle_InstallHooks();
    sithPathMove_InstallHooks();
    sithPhysics_InstallHooks();
    sithPlayerActions_InstallHooks();
    sithPlayerControls_InstallHooks();
    sithPlayer_InstallHooks();
    sithPuppet_InstallHooks();
    sithRender_InstallHooks();
    sithRenderSky_InstallHooks();
    sithSector_InstallHooks();
    sithShadow_InstallHooks();
    sithSoundClass_InstallHooks();
    sithSoundMixer_InstallHooks();
    sithSound_InstallHooks();
    sithSprite_InstallHooks();
    sithString_InstallHooks();
    sithSurface_InstallHooks();
    sithTemplate_InstallHooks();
    sithThing_InstallHooks();
    sithTime_InstallHooks();
    sithVehicleControls_InstallHooks();
    sithVoice_InstallHooks();
    sithWeapon_InstallHooks();
    sithWhip_InstallHooks();
    sithWorld_InstallHooks();

    std3D_InstallHooks();
    stdBmp_InstallHooks();
    stdCircBuf_InstallHooks();
    stdColor_InstallHooks();
    stdComm_InstallHooks();
    stdConffile_InstallHooks();
    stdConsole_InstallHooks();
    stdControl_InstallHooks();
    stdDisplay_InstallHooks();
    stdEffect_InstallHooks();
    stdFileUtil_InstallHooks();
    stdFnames_InstallHooks();
    stdGob_InstallHooks();
    stdHashtbl_InstallHooks();
    stdLinkList_InstallHooks();
    stdMath_InstallHooks();
    stdMemory_InstallHooks();
    stdPlatform_InstallHooks();
    stdStrTable_InstallHooks();
    stdUtil_InstallHooks();
    stdWin95_InstallHooks();
    std_InstallHooks();

    wkernel_InstallHooks();
    wuRegistry_InstallHooks();

    return J3DEndHookContext(&ctx);
}

bool ResetGlobals(void)
{
    J3DHookContext ctx;
    if ( !J3DStartHookContext(&ctx, EXE_RDATA_START_ADDR, EXE_RDATA_END_ADDR) ) {
        return false;
    }

    AudioLib_ResetGlobals();
    Driver_ResetGlobals();
    JonesConsole_ResetGlobals();
    JonesControl_ResetGlobals();
    JonesDialog_ResetGlobals();
    JonesDisplay_ResetGlobals();
    JonesFile_ResetGlobals();
    JonesHud_ResetGlobals();
    JonesMain_ResetGlobals();
    Sound_ResetGlobals();
    jonesCog_ResetGlobals();
    jonesConfig_ResetGlobals();
    jonesInventory_ResetGlobals();
    jonesString_ResetGlobals();
    rdCache_ResetGlobals();
    rdCamera_ResetGlobals();
    rdCanvas_ResetGlobals();
    rdClip_ResetGlobals();
    rdFace_ResetGlobals();
    rdFont_ResetGlobals();
    rdKeyframe_ResetGlobals();
    rdLight_ResetGlobals();
    rdMaterial_ResetGlobals();
    rdMath_ResetGlobals();
    rdMatrix_ResetGlobals();
    rdModel3_ResetGlobals();
    rdParticle_ResetGlobals();
    rdPolyline_ResetGlobals();
    rdPrimit2_ResetGlobals();
    rdPrimit3_ResetGlobals();
    rdPuppet_ResetGlobals();
    rdQClip_ResetGlobals();
    rdSprite_ResetGlobals();
    rdThing_ResetGlobals();
    rdVector_ResetGlobals();
    rdWallpaper_ResetGlobals();
    rdroid_ResetGlobals();
    sithAIAwareness_ResetGlobals();
    sithAIClass_ResetGlobals();
    sithAIInstinct_ResetGlobals();
    sithAIMove_ResetGlobals();
    sithAIUtil_ResetGlobals();
    sithAI_ResetGlobals();
    sithActor_ResetGlobals();
    sithAnimate_ResetGlobals();
    sithCamera_ResetGlobals();
    sithCogExec_ResetGlobals();
    sithCogFunctionAI_ResetGlobals();
    sithCogFunctionPlayer_ResetGlobals();
    sithCogFunctionSector_ResetGlobals();
    sithCogFunctionSound_ResetGlobals();
    sithCogFunctionSurface_ResetGlobals();
    sithCogFunctionThing_ResetGlobals();
    sithCogFunction_ResetGlobals();
    sithCogParse_ResetGlobals();
    sithCogYacc_ResetGlobals();
    sithCog_ResetGlobals();
    sithCollision_ResetGlobals();
    sithComm_ResetGlobals();
    sithCommand_ResetGlobals();
    sithConsole_ResetGlobals();
    sithControl_ResetGlobals();
    sithDSSCog_ResetGlobals();
    sithDSSThing_ResetGlobals();
    sithDSS_ResetGlobals();
    sithEvent_ResetGlobals();
    sithExplosion_ResetGlobals();
    sithFX_ResetGlobals();
    sithGamesave_ResetGlobals();
    sithIntersect_ResetGlobals();
    sithInventory_ResetGlobals();
    sithItem_ResetGlobals();
    sithMain_ResetGlobals();
    sithMaterial_ResetGlobals();
    sithModel_ResetGlobals();
    sithMulti_ResetGlobals();
    sithOverlayMap_ResetGlobals();
    sithPVS_ResetGlobals();
    sithParticle_ResetGlobals();
    sithPathMove_ResetGlobals();
    sithPhysics_ResetGlobals();
    sithPlayerActions_ResetGlobals();
    sithPlayerControls_ResetGlobals();
    sithPlayer_ResetGlobals();
    sithPuppet_ResetGlobals();
    sithRender_ResetGlobals();
    sithRenderSky_ResetGlobals();
    sithSector_ResetGlobals();
    sithShadow_ResetGlobals();
    sithSoundClass_ResetGlobals();
    sithSoundMixer_ResetGlobals();
    sithSound_ResetGlobals();
    sithSprite_ResetGlobals();
    sithString_ResetGlobals();
    sithSurface_ResetGlobals();
    sithTemplate_ResetGlobals();
    sithThing_ResetGlobals();
    sithTime_ResetGlobals();
    sithVehicleControls_ResetGlobals();
    sithVoice_ResetGlobals();
    sithWeapon_ResetGlobals();
    sithWhip_ResetGlobals();
    sithWorld_ResetGlobals();
    std3D_ResetGlobals();
    stdBmp_ResetGlobals();
    stdCircBuf_ResetGlobals();
    stdColor_ResetGlobals();
    stdComm_ResetGlobals();
    stdConffile_ResetGlobals();
    stdConsole_ResetGlobals();
    stdControl_ResetGlobals();
    stdDisplay_ResetGlobals();
    stdEffect_ResetGlobals();
    stdFileUtil_ResetGlobals();
    stdFnames_ResetGlobals();
    stdGob_ResetGlobals();
    stdHashtbl_ResetGlobals();
    stdLinkList_ResetGlobals();
    stdMath_ResetGlobals();
    stdMemory_ResetGlobals();
    stdPlatform_ResetGlobals();
    stdStrTable_ResetGlobals();
    stdUtil_ResetGlobals();
    stdWin95_ResetGlobals();
    std_ResetGlobals();
    wkernel_ResetGlobals();
    wuRegistry_ResetGlobals();

    return J3DEndHookContext(&ctx);
}