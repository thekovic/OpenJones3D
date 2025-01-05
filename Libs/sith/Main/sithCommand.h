#ifndef SITH_SITHCOMMAND_H
#define SITH_SITHCOMMAND_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void sithCommand_RegisterCommands(void);

// Helper hooking functions
void sithCommand_InstallHooks(void);
void sithCommand_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOMMAND_H
