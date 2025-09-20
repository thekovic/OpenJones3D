#ifndef JONES3D_JONESDISPLAY_H
#define JONES3D_JONESDISPLAY_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define JONESDISPLAY_CFG_GRAPHICS_ALLDEVICES       "graphics.allDevices"
#define JONESDISPLAY_CFG_GRAPHICS_WINDOW           "graphics.window"
#define JONESDISPLAY_CFG_GRAPHICS_DUALMONITOR      "graphics.dualMonitor"
#define JONESDISPLAY_CFG_GRAPHICS_BUFFERING        "graphics.buffering"
#define JONESDISPLAY_CFG_GRAPHICS_MIPMAPFILTER     "graphics.mipmapFilter"
#define JONESDISPLAY_CFG_GRAPHICS_FOG              "graphics.fog"
#define JONESDISPLAY_CFG_GRAPHICS_FOGDENSITY       "graphics.fogDensity"
#define JONESDISPLAY_CFG_GRAPHICS_GEOMETRYMODE     "graphics.geometryMode"
#define JONESDISPLAY_CFG_GRAPHICS_LIGHTINGMODE     "graphics.lightingMode"
#define JONESDISPLAY_CFG_GRAPHICS_HIPOLY           "graphics.hipoly"
#define JONESDISPLAY_CFG_GRAPHICS_DISPLAY          "graphics.display"
#define JONESDISPLAY_CFG_GRAPHICS_DEVICE           "graphics.device"
#define JONESDISPLAY_CFG_GRAPHICS_WIDTH            "graphics.width"
#define JONESDISPLAY_CFG_GRAPHICS_HEIGHT           "graphics.height"
#define JONESDISPLAY_CFG_GRAPHICS_BPP              "graphics.bpp"
#define JONESDISPLAY_CFG_GRAPHICS_REFRESHRATE      "graphics.refreshRate"
#define JONESDISPLAY_CFG_GRAPHICS_PERFORMANCELEVEL "graphics.performanceLevel"

// Returns 0 for success and 1 indicating error
int J3DAPI JonesDisplay_Startup(JonesDisplaySettings* pSettings);
void JonesDisplay_Shutdown(void);

int J3DAPI JonesDisplay_Open(JonesDisplaySettings* pSettings);
void JonesDisplay_Close(void);

int J3DAPI JonesDisplay_Restart(JonesDisplaySettings* pSettings);
void J3DAPI JonesDisplay_SetDefaultVideoMode(const StdDisplayEnvironment* pEnv, JonesDisplaySettings* pDisplaySettings);

void J3DAPI JonesDisplay_EnableDualMonitor(int bEnable);
int J3DAPI JonesDisplay_UpdateDualScreenWindowSize(const JonesDisplaySettings* pSettings);

void J3DAPI JonesDisplay_OpenLoadScreen(const char* pMatFilePath, float wlStartX, float wlStartY, float wlEndX, float wlEndY, int bPrimaryMusicTheme);
void JonesDisplay_CloseLoadScreen(void);
void J3DAPI JonesDisplay_UpdateLoadProgress(float progress);

int JonesDisplay_ShowSplashDemo(void); // Added

// Helper hooking functions
void JonesDisplay_InstallHooks(void);
void JonesDisplay_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESDISPLAY_H
