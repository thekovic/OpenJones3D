#include "sithCommand.h"

#include <j3dcore/j3dhook.h>

#include <sith/Cog/sithCog.h>
#include <sith/Devices/sithConsole.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/Gameplay/sithPlayer.h>
#include <sith/Main/sithMain.h>
#include <sith/Main/sithString.h>
#include <sith/RTI/symbols.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithWorld.h>

#include <rdroid/Math/rdMatrix.h>

#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

static char aCipherTextBuf[256] = { 0 }; // Added: Init to 0

int J3DAPI sithCommand_DebugMode(const SithConsoleCommand* pFunc, const char* pArg);

int J3DAPI sithCommand_Wuss(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_Fixme(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_Ouch(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_MakeMePirate(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_Coords(const SithConsoleCommand* pFunc, const char* pArg);

int J3DAPI sithCommand_Memory(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_DynamicMemory(const SithConsoleCommand* pFunc, const char* pArg);
int J3DAPI sithCommand_MemoryDump(const SithConsoleCommand* pFunc, const char* pArg);

const char* J3DAPI sithCommand_CipherText(const char* pText);

void sithCommand_InstallHooks(void)
{
    J3D_HOOKFUNC(sithCommand_RegisterCommands);
    J3D_HOOKFUNC(sithCommand_DebugMode);
    J3D_HOOKFUNC(sithCommand_Wuss);
    J3D_HOOKFUNC(sithCommand_Fixme);
    J3D_HOOKFUNC(sithCommand_Ouch);
    J3D_HOOKFUNC(sithCommand_Coords);
    J3D_HOOKFUNC(sithCommand_Memory);
    J3D_HOOKFUNC(sithCommand_DynamicMemory);
    J3D_HOOKFUNC(sithCommand_MemoryDump);
    J3D_HOOKFUNC(sithCommand_CipherText);
}

void sithCommand_ResetGlobals(void)
{}

void sithCommand_RegisterCommands(void)
{
    // taklit_marion
    sithConsole_RegisterCommand(sithCommand_DebugMode, sithCommand_CipherText("VCINKV}OCPKML"), 4);

    // urgon_elsa
    sithConsole_RegisterCommand(sithCommand_Wuss, sithCommand_CipherText("WPEML}GNQC"), 0);

    // azerim_sophia
    sithConsole_RegisterCommand(sithCommand_Ouch, sithCommand_CipherText("CXGPKO}QMRJKC"), 0);

    sithConsole_RegisterCommand(sithCommand_Fixme, "fixme", 0);
    sithConsole_RegisterCommand(sithCommand_MakeMePirate, "makemeapirate", 0);
    sithConsole_RegisterCommand(sithCommand_Coords, "coords", 0);

    sithConsole_RegisterCommand(sithCommand_Memory, "mem", 0);
    sithConsole_RegisterCommand(sithCommand_DynamicMemory, "dynamicmem", 0);
    sithConsole_RegisterCommand(sithCommand_MemoryDump, "memdump", 0);
}

int J3DAPI sithCommand_DebugMode(const SithConsoleCommand* pFunc, const char* pArg)
{
    SITH_ASSERTREL(pFunc);

    // Added: Init to null and 0
    int* pFlags  = NULL;
    int newFlags = 0;
    switch ( pFunc->flags )
    {
        case 0:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_AIEVENTS_DISABLED;
            break;

        case 1:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_PUPPETSYSTEM_DISABLED;
            break;

        case 2:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_TRACKSHOTS;
            break;

        case 3:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_AIDISABLED;
            break;

        case 4:  // invul
            if ( !sithWorld_g_pCurrentWorld || !sithWorld_g_pCurrentWorld->pLocalPlayer || sithWorld_g_pCurrentWorld->pLocalPlayer->type != SITH_THING_PLAYER )
            {
                return 0;
            }

            pFlags = (int*)&sithWorld_g_pCurrentWorld->pLocalPlayer->thingInfo.actorInfo.flags;
            newFlags = SITHDEBUG_INVULNERABLE;
            break;

        case 5:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_AINOTARGET;
            break;

        case 6:
            pFlags = &sithMain_g_sith_mode.debugModeFlags;
            newFlags = SITHDEBUG_SLOWMODE;
            break;

        default:
            return 0;
    }

    // Set/Clear flag
    if ( pArg )
    {
        bool bON;
        if ( sithCommand_ParseBool(pArg, &bON) )
        {
            if ( bON )
            {
                *pFlags |= newFlags;
                if ( pFunc->flags == 4 ) // invul
                {
                    sithPlayer_g_bPlayerInvulnerable = 1;
                }
            }
            else
            {
                *pFlags &= ~newFlags;
                if ( pFunc->flags == 4 )    // invul
                {
                    sithPlayer_g_bPlayerInvulnerable = 0;
                }
            }
        }
    }

    // Print command state to console
    wchar_t awComName[32];
    STD_TOWSTR(awComName, pFunc->aName);

    const wchar_t* pwState;
    if ( (newFlags & *pFlags) != 0 ) {
        pwState = sithString_GetString("ON");
    }
    else {
        pwState = sithString_GetString("OFF");
    }

    wchar_t awText[128];
    const wchar_t* pwFormat = sithString_GetString("%s_IS_%s"); // Note, bug calling sithString_GetString will override pwState due to stdStrTable internal cache
    STD_WFORMAT(awText, pwFormat, awComName, pwState);
    sithConsole_PrintWString(awText);

    return 1;
}

int J3DAPI sithCommand_Wuss(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    if ( !sithPlayer_g_pLocalPlayerThing ) {
        return 0;
    }

    SithCog* pCog = sithCog_GetCogByIndex(SITHWORLD_STATICINDEX(31)); //0x801F
    if ( !pCog ) {
        return 0;
    }

    sithCog_SendMessage(pCog, SITHCOG_MSG_SELECTED, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, sithPlayer_g_pLocalPlayerThing->idx, 0);
    return 1;
}

int J3DAPI sithCommand_Fixme(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    SithThing* pThing = sithPlayer_g_pLocalPlayerThing;
    if ( !sithPlayer_g_pLocalPlayerThing ) {
        return 0;
    }

    sithPlayer_g_pLocalPlayerThing->moveStatus = SITHPLAYERMOVE_STILL;
    pThing->collide.movesize = 0.04f;

    pThing->thingInfo.actorInfo.bControlsDisabled = 0;
    pThing->thingInfo.actorInfo.bForceMovePlay    = 0;

    pThing->moveInfo.physics.flags &= ~SITH_PF_ALIGNSURFACE;
    pThing->moveInfo.physics.flags |= SITH_PF_ALIGNUP;  // 0x800 - SITH_PF_ALIGNUP
    pThing->moveInfo.physics.height = 0.09f;

    sithPuppet_SetMoveMode(pThing, SITHPUPPET_MOVEMODE_NORMAL);
    return 1;
}

int J3DAPI sithCommand_Ouch(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    if ( !sithPlayer_g_pLocalPlayerThing ) {
        return 0;
    }

    SithCog* pCog = sithCog_GetCogByIndex(SITHWORLD_STATICINDEX(32)); // 0x8020
    if ( !pCog ) {
        return 0;
    }

    sithCog_SendMessage(pCog, SITHCOG_MSG_SELECTED, SITHCOG_SYM_REF_NONE, 0, SITHCOG_SYM_REF_THING, sithPlayer_g_pLocalPlayerThing->idx, 0);
    return 1;
}

int J3DAPI sithCommand_MakeMePirate(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    return sithPlayer_ToggleGuybrush();
}

int J3DAPI sithCommand_Coords(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    if ( !sithWorld_g_pCurrentWorld || !sithWorld_g_pCurrentWorld->pLocalPlayer )
    {
        sithConsole_PrintString("No world.");
        return 0;
    }

    SithThing* pPlayer = sithWorld_g_pCurrentWorld->pLocalPlayer;
    if ( !pPlayer->pInSector )
    {
        sithConsole_PrintString("Thing is not in world");
    }
    else
    {
        rdVector3 pyr;
        rdMatrix_ExtractAngles34(&pPlayer->orient, &pyr);
        int secIdx = sithSector_GetSectorIndex(pPlayer->pInSector);

        STD_FORMAT(
            std_g_genBuffer,
            "Pos: (%.2f, %.2f, %.2f) PYR: (%.2f, %.2f, %.2f) Sector: %d.",
            pPlayer->pos.x,
            pPlayer->pos.y,
            pPlayer->pos.z,
            pyr.pitch,
            pyr.yaw,
            pyr.roll,
            secIdx
        );
        sithConsole_PrintString(std_g_genBuffer);
    }

    return 1;
}

int J3DAPI sithCommand_Memory(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);

    const SithWorld* pWorld = sithWorld_g_pCurrentWorld;
    if ( pArg ) {
        pWorld = sithWorld_g_pStaticWorld;
    }

    if ( !pWorld )
    {
        sithConsole_PrintString("No world.");
        return 0;
    }

    size_t aMemUsed[17] = { 0 }; // Added: Init to 0
    size_t aCount[17]   = { 0 }; // Added: Init to 0
    sithWorld_GetMemoryUsage(pWorld, aMemUsed, aCount);

    size_t totalUsed = 0;

    STD_FORMAT(std_g_genBuffer, "%5d Materials        %8d bytes.", aCount[0], aMemUsed[0]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[0];

    STD_FORMAT(std_g_genBuffer, "%5d Models           %8d bytes.", aCount[10], aMemUsed[10]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[10];

    STD_FORMAT(std_g_genBuffer, "%5d Keyframes        %8d bytes.", aCount[11], aMemUsed[11]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[11];

    STD_FORMAT(std_g_genBuffer, "%5d World Vertices   %8d bytes.", aCount[1], aMemUsed[1]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[1];

    STD_FORMAT(std_g_genBuffer, "%5d World TexVerts   %8d bytes.", aCount[2], aMemUsed[2]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[2];

    STD_FORMAT(std_g_genBuffer, "%5d Surfaces         %8d bytes.", aCount[3], aMemUsed[3]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[3];

    STD_FORMAT(std_g_genBuffer, "%5d Sectors          %8d bytes.", aCount[5], aMemUsed[5]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[5];

    STD_FORMAT(std_g_genBuffer, "%5d Cog Scripts\t\t%8d bytes.", aCount[8], aMemUsed[8]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[8];

    STD_FORMAT(std_g_genBuffer, "%5d Cogs             %8d bytes.", aCount[7], aMemUsed[7]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[7];

    STD_FORMAT(std_g_genBuffer, "%5d Adjoins          %8d bytes.", aCount[4], aMemUsed[4]);
    sithConsole_PrintString(std_g_genBuffer);
    totalUsed += aMemUsed[4];

    STD_FORMAT(std_g_genBuffer, "Total Memory Used:   %8d bytes.", totalUsed);
    sithConsole_PrintString(std_g_genBuffer);
    return 1;
}

int J3DAPI sithCommand_DynamicMemory(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    STD_FORMAT(
        std_g_genBuffer,
        "NumAllocs: %d TotalMemAlloc: %d bytes MaxMemAlloc: %d bytes",
        stdMemory_g_curState.totalAllocs,
        stdMemory_g_curState.totalBytes,
        stdMemory_g_curState.maxBytes
    );
    sithConsole_PrintString(std_g_genBuffer);
    return 1;
}

int J3DAPI sithCommand_MemoryDump(const SithConsoleCommand* pFunc, const char* pArg)
{
    J3D_UNUSED(pFunc);
    J3D_UNUSED(pArg);

    tFileHandle fh = sith_g_pHS->pFileOpen("memdump.txt", "w+");
    if ( !fh ) {
        return 0;
    }

    sith_g_pHS->pFilePrintf(
        fh,
        "Total Memory allocated: %d bytes   # Allocations: %d  Max Memory used: %d bytes\n\n",
        stdMemory_g_curState.totalBytes,
        stdMemory_g_curState.totalAllocs,
        stdMemory_g_curState.maxBytes
    );

    for ( tMemoryHeader* pMemHeader = stdMemory_g_curState.header.pNext; pMemHeader; pMemHeader = pMemHeader->pNext )
    {
        sith_g_pHS->pFilePrintf(fh, "%25s:  line %3d   %8d bytes   #%d\n", pMemHeader->pFilename, pMemHeader->line, pMemHeader->size, pMemHeader->number);
    }

    sith_g_pHS->pFileClose(fh);
    sithConsole_PrintString("Memory dump file 'memdump.txt' written.");
    return 1;
}

const char* J3DAPI sithCommand_CipherText(const char* pText)
{
    // Function goes over all characters of text and xor each char with 34 (22h)
    // def decrypt_cheat_text(enc_cheat):
    //      cheat = ""
    //      for c in enc_cheat:
    //          cheat += chr(ord(c) ^ 34)
    //      return cheat

    size_t len = strlen(pText);
    size_t i = 0;
    for ( ; i < len; ++i ) {
        aCipherTextBuf[i] = pText[i] ^ 34;
    }
    aCipherTextBuf[i] = 0;

    return aCipherTextBuf;
}
