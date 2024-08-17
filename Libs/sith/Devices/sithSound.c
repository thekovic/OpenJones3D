#include "sithSound.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithSound_bStartup J3D_DECL_FAR_VAR(sithSound_bStartup, int)
#define sithSound_bSkipRestoringSounds J3D_DECL_FAR_VAR(sithSound_bSkipRestoringSounds, int)

void sithSound_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithSound_InitializeSound);
    // J3D_HOOKFUNC(sithSound_Startup);
    // J3D_HOOKFUNC(sithSound_Shutdown);
    // J3D_HOOKFUNC(sithSound_NDYReadSoundSection);
    // J3D_HOOKFUNC(sithSound_CNDWriteSoundSection);
    // J3D_HOOKFUNC(sithSound_CNDReadSoundSection);
    // J3D_HOOKFUNC(sithSound_FreeWorldSounds);
    // J3D_HOOKFUNC(sithSound_Load);
    // J3D_HOOKFUNC(sithSound_SetSkipRestoringSounds);
}

void sithSound_ResetGlobals(void)
{
    memset(&sithSound_bStartup, 0, sizeof(sithSound_bStartup));
    memset(&sithSound_bSkipRestoringSounds, 0, sizeof(sithSound_bSkipRestoringSounds));
}

int J3DAPI sithSound_InitializeSound(tHostServices* pHS)
{
    return J3D_TRAMPOLINE_CALL(sithSound_InitializeSound, pHS);
}

int J3DAPI sithSound_Startup(int bSound3D)
{
    return J3D_TRAMPOLINE_CALL(sithSound_Startup, bSound3D);
}

void sithSound_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithSound_Shutdown);
}

int J3DAPI sithSound_NDYReadSoundSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithSound_NDYReadSoundSection, pWorld, bSkip);
}

int J3DAPI sithSound_CNDWriteSoundSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSound_CNDWriteSoundSection, fh, pWorld);
}

int J3DAPI sithSound_CNDReadSoundSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithSound_CNDReadSoundSection, fh, pWorld);
}

void J3DAPI sithSound_FreeWorldSounds(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithSound_FreeWorldSounds, pWorld);
}

tSoundHandle J3DAPI sithSound_Load(SithWorld* pWorld, const char* filename)
{
    return J3D_TRAMPOLINE_CALL(sithSound_Load, pWorld, filename);
}

void J3DAPI sithSound_SetSkipRestoringSounds(int bSkip)
{
    J3D_TRAMPOLINE_CALL(sithSound_SetSkipRestoringSounds, bSkip);
}
