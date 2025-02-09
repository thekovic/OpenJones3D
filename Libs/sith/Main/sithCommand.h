#ifndef SITH_SITHCOMMAND_H
#define SITH_SITHCOMMAND_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

#include <stdbool.h>

J3D_EXTERN_C_START

void sithCommand_RegisterCommands(void);


inline bool sithCommand_ParseBool(const char* pStr, bool* pOut) // Added
{
    if ( !pStr || !pOut ) {
        return false;
    }

    if ( strcmpi(pStr, "on") == 0 || strcmpi(pStr, "1") == 0 )
    {
        *pOut = true;
        return true;
    }
    else if ( strcmpi(pStr, "off") == 0 || strcmpi(pStr, "0") == 0 )
    {
        *pOut = false;
        return true;
    }

    return false;
}

// Helper hooking functions
void sithCommand_InstallHooks(void);
void sithCommand_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOMMAND_H
