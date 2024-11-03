#include "sithWorld.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>
#include <sith/AI/sithAIClass.h>
#include <sith/Cog/sithCog.h>
#include <sith/Devices/sithSound.h>
#include <sith/Engine/sithPuppet.h>
#include <sith/World/sithMaterial.h>
#include <sith/World/sithModel.h>
#include <sith/World/sithPVS.h>
#include <sith/World/sithSector.h>
#include <sith/World/sithSoundClass.h>
#include <sith/World/sithSprite.h>
#include <sith/World/sithSurface.h>
#include <sith/World/sithTemplate.h>
#include <sith/World/sithThing.h>

#define sithWorld_aCopyrightSymbol J3D_DECL_FAR_ARRAYVAR(sithWorld_aCopyrightSymbol, const char(*)[1216])
#define sithWorld_aCNDSectionParsers J3D_DECL_FAR_ARRAYVAR(sithWorld_aCNDSectionParsers, const CndSectionParser(*)[17])
#define sithWorld_pfLoadProgressCallback J3D_DECL_FAR_VAR(sithWorld_pfLoadProgressCallback, SithWorldLoadProgressCallback)
#define sithWorld_aCopyrightBuf J3D_DECL_FAR_ARRAYVAR(sithWorld_aCopyrightBuf, char(*)[1216])
#define sithWorld_aNdyParseHandlers J3D_DECL_FAR_ARRAYVAR(sithWorld_aNdyParseHandlers, SithWorldNdyParseHandler(*)[32])
#define sithWorld_aCurSection J3D_DECL_FAR_ARRAYVAR(sithWorld_aCurSection, char(*)[256])
#define sithWorld_numNdyParseHandlers J3D_DECL_FAR_VAR(sithWorld_numNdyParseHandlers, int)
#define sithWorld_bWorldStartup J3D_DECL_FAR_VAR(sithWorld_bWorldStartup, int)
#define sithWorld_bValidCopyright J3D_DECL_FAR_VAR(sithWorld_bValidCopyright, int)

void sithWorld_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithWorld_Startup);
    // J3D_HOOKFUNC(sithWorld_Shutdown);
    // J3D_HOOKFUNC(sithWorld_SetLoadProgressCallback);
    // J3D_HOOKFUNC(sithWorld_UpdateLoadProgress);
    // J3D_HOOKFUNC(sithWorld_Load);
    // J3D_HOOKFUNC(sithWorld_LoadPostProcess);
    // J3D_HOOKFUNC(sithWorld_LoadEntryText);
    // J3D_HOOKFUNC(sithWorld_Close);
    // J3D_HOOKFUNC(sithWorld_New);
    // J3D_HOOKFUNC(sithWorld_Free);
    // J3D_HOOKFUNC(sithWorld_NDYReadHeaderSection);
    // J3D_HOOKFUNC(sithWorld_NDYReadCopyrightSection);
    // J3D_HOOKFUNC(sithWorld_GetMemoryUsage);
    // J3D_HOOKFUNC(sithWorld_RegisterTextSectionParser);
    // J3D_HOOKFUNC(sithWorld_ResetRenderState);
    // J3D_HOOKFUNC(sithWorld_ValidateWorld);
    // J3D_HOOKFUNC(sithWorld_InitPlayers);
    // J3D_HOOKFUNC(sithWorld_NDYReadSection);
    // J3D_HOOKFUNC(sithWorld_NDYGetSectionParserIndex);
    // J3D_HOOKFUNC(sithWorld_NDYReadGeoresourceSection);
    // J3D_HOOKFUNC(sithWorld_CNDWriteGeoresourceSection);
    // J3D_HOOKFUNC(sithWorld_CNDReadGeoresourceSection);
    // J3D_HOOKFUNC(sithWorld_LoadEntryBinary);
}

void sithWorld_ResetGlobals(void)
{
    const char sithWorld_aCopyrightSymbol_tmp[1217] = "................................................@...@...@...@................@...@..@..@...@....................@.@.@.@.@.@.....@@@@@@@@......@...........@.....@@@@@@@@....@@......@@@....@....@@.....@.....@......@@@.....@@..@@.@@@@@......@.....@@@......@@.@@@@@@@@.......@....@@.....@@...@@@@@@@@.........@@@@@@@@@@.....@@@@@@@@..........@@@@@@........@@.....@..........@@@@@.........@@.@@@@@.........@@@@@@.........@@.....@.........@@@@@@.........@@@@@@@@.........@@@@@@.........@@@@@@@@.........@@@@@@@........@@@...@@.........@@@@@@@........@@.@@@.@.........@.....@........@@..@..@........@.......@.......@@@@@@@@........@.......@.......@@@@@@@@.......@........@.......@@..@@@@.......@........@.......@@@@..@@......@.........@.......@@@@.@.@......@.........@.......@@....@@........................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@.@@..@@@@@..@@@@@@@@@@.@@@@@@@@@.@.@.@@@@.@.@@@.@..@@...@@@..@@@..@@@@@@....@@@..@@@@@.@@@@.@@@@@@@@@@...@@.@@@.@@@@@..@@...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.(c).lucasarts.entertainment..@@.........company.llc..........@@....(c).lucasfilm.ltd.&.tm....@@.....all.rights.reserved......@@...used.under.authorization...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    memcpy((char*)&sithWorld_aCopyrightSymbol, &sithWorld_aCopyrightSymbol_tmp, sizeof(sithWorld_aCopyrightSymbol));

    const CndSectionParser sithWorld_aCNDSectionParsers_tmp[17] = {
      { "sounds", &sithSound_CNDReadSoundSection, &sithSound_CNDWriteSoundSection },
      {
        "materials",
        &sithMaterial_CNDReadMaterialSection,
        &sithMaterial_CNDWriteMaterialSection
      },
      {
        "georesource",
        &sithWorld_CNDReadGeoresourceSection,
        &sithWorld_CNDWriteGeoresourceSection
      },
      {
        "adjoins",
        &sithSurface_CNDReadAdjoinSection,
        &sithSurface_CNDWriteAdjoinSection
      },
      {
        "surfaces",
        &sithSurface_CNDReadSurfaceSection,
        &sithSurface_CNDWriteSurfaceSection
      },
      {
        "sectors",
        &sithSector_LoadBinary,
        &sithSector_WriteBinary
      },
      {
        "aiclasses",
        &sithAIClass_CNDReadAIClassSection,
        &sithAIClass_CNDWriteAIClassSection
      },
      { "models", &sithModel_CNDReadModelSection, &sithModel_CNDWriteModelSection },
      {
        "sprites",
        &sithSprite_CNDReadSpriteSection,
        &sithSprite_CNDWriteSpriteSection
      },
      {
        "keyframes",
        &sithPuppet_CNDReadKeyframeSection,
        &sithPuppet_CNDWriteKeyframeSection
      },
      {
        "animclass",
        &sithPuppet_CNDReadPuppetSection,
        &sithPuppet_CNDWritePuppetSection
      },
      {
        "soundclasses",
        &sithSoundClass_CNDReadSoundClassSection,
        &sithSoundClass_CNDWriteSoundClassSection
      },
      {
        "cogcripts",
        &sithCog_LoadCogScriptsBinary,
        &sithCog_WriteCogScriptsBinary
      },
      { "cogs", &sithCog_LoadBinary, &sithCog_WriteBinary },
      {
        "templates",
        &sithTemplate_CNDReadTemplateSection,
        &sithTemplate_CNDWriteTemplateSection
      },
      { "things", &sithThing_CNDReadThingSection, &sithThing_CNDWriteThingSection },
      { "pvs", &sithPVS_LoadBinary, &sithPVS_WriteBinary }
    };
    memcpy((CndSectionParser*)&sithWorld_aCNDSectionParsers, &sithWorld_aCNDSectionParsers_tmp, sizeof(sithWorld_aCNDSectionParsers));

    memset(&sithWorld_pfLoadProgressCallback, 0, sizeof(sithWorld_pfLoadProgressCallback));
    memset(&sithWorld_aCopyrightBuf, 0, sizeof(sithWorld_aCopyrightBuf));
    memset(&sithWorld_aNdyParseHandlers, 0, sizeof(sithWorld_aNdyParseHandlers));
    memset(&sithWorld_g_pCurrentWorld, 0, sizeof(sithWorld_g_pCurrentWorld));
    memset(&sithWorld_g_pStaticWorld, 0, sizeof(sithWorld_g_pStaticWorld));
    memset(&sithWorld_g_pLastLoadedWorld, 0, sizeof(sithWorld_g_pLastLoadedWorld));
    memset(&sithWorld_aCurSection, 0, sizeof(sithWorld_aCurSection));
    memset(&sithWorld_g_bLoading, 0, sizeof(sithWorld_g_bLoading));
    memset(&sithWorld_numNdyParseHandlers, 0, sizeof(sithWorld_numNdyParseHandlers));
    memset(&sithWorld_bWorldStartup, 0, sizeof(sithWorld_bWorldStartup));
    memset(&sithWorld_bValidCopyright, 0, sizeof(sithWorld_bValidCopyright));
}

int J3DAPI sithWorld_Startup()
{
    return J3D_TRAMPOLINE_CALL(sithWorld_Startup);
}

void sithWorld_Shutdown(void)
{
    J3D_TRAMPOLINE_CALL(sithWorld_Shutdown);
}

void J3DAPI sithWorld_SetLoadProgressCallback(SithWorldLoadProgressCallback pfProgressCallback)
{
    J3D_TRAMPOLINE_CALL(sithWorld_SetLoadProgressCallback, pfProgressCallback);
}

void J3DAPI sithWorld_UpdateLoadProgress(float progress)
{
    J3D_TRAMPOLINE_CALL(sithWorld_UpdateLoadProgress, progress);
}

int J3DAPI sithWorld_Load(SithWorld* pWorld, const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_Load, pWorld, pFilename);
}

int J3DAPI sithWorld_LoadPostProcess(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_LoadPostProcess, pWorld);
}

int J3DAPI sithWorld_LoadEntryText(SithWorld* pWorld, const char* pFilename, int bSkipParsing)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_LoadEntryText, pWorld, pFilename, bSkipParsing);
}

void J3DAPI sithWorld_Close(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithWorld_Close, pWorld);
}

SithWorld* sithWorld_New(void)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_New);
}

void J3DAPI sithWorld_Free(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithWorld_Free, pWorld);
}

signed int J3DAPI sithWorld_NDYReadHeaderSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_NDYReadHeaderSection, pWorld, bSkip);
}

int J3DAPI sithWorld_NDYReadCopyrightSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_NDYReadCopyrightSection, pWorld, bSkip);
}

void J3DAPI sithWorld_GetMemoryUsage(const SithWorld* pWorld, int* aMemUsed, int* aCount)
{
    J3D_TRAMPOLINE_CALL(sithWorld_GetMemoryUsage, pWorld, aMemUsed, aCount);
}

int J3DAPI sithWorld_RegisterTextSectionParser(const char* aSectionName, SithWorldSectionParseFunc pfParseFunction)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_RegisterTextSectionParser, aSectionName, pfParseFunction);
}

void J3DAPI sithWorld_ResetRenderState(SithWorld* pWorld)
{
    J3D_TRAMPOLINE_CALL(sithWorld_ResetRenderState, pWorld);
}

int J3DAPI sithWorld_ValidateWorld(const SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_ValidateWorld, pWorld);
}

int J3DAPI sithWorld_InitPlayers(SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_InitPlayers, pWorld);
}

int J3DAPI sithWorld_NDYReadSection(SithWorld* pWorld, const char* aSectionName, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_NDYReadSection, pWorld, aSectionName, bSkip);
}

int J3DAPI sithWorld_NDYGetSectionParserIndex(const char* aSectionName)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_NDYGetSectionParserIndex, aSectionName);
}

int J3DAPI sithWorld_NDYReadGeoresourceSection(SithWorld* pWorld, int bSkip)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_NDYReadGeoresourceSection, pWorld, bSkip);
}

int J3DAPI sithWorld_CNDWriteGeoresourceSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_CNDWriteGeoresourceSection, fh, pWorld);
}

int J3DAPI sithWorld_CNDReadGeoresourceSection(tFileHandle fh, SithWorld* pWorld)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_CNDReadGeoresourceSection, fh, pWorld);
}

// local variable allocation has failed, the output may be wrong!
int J3DAPI sithWorld_LoadEntryBinary(SithWorld* pWorld, const char* pFilePath)
{
    return J3D_TRAMPOLINE_CALL(sithWorld_LoadEntryBinary, pWorld, pFilePath);
}
