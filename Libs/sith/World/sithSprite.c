#include "sithSprite.h"
#include <j3dcore/j3dhook.h>

#include <rdroid/Engine/rdThing.h>
#include <rdroid/Math/rdMatrix.h>
#include <rdroid/Math/rdVector.h>
#include <rdroid/Primitives/rdModel3.h>
#include <rdroid/Primitives/rdSprite.h>

#include <sith/RTI/symbols.h>
#include <sith/World/sithThing.h>
#include <sith/World/sithWorld.h>

#include <std/General/stdConffile.h>
#include <std/General/stdHashtbl.h>
#include <std/General/stdMemory.h>
#include <std/General/stdUtil.h>

static tHashTable* sithSprite_pHashtable;

rdSprite3* J3DAPI sithSprite_CacheFind(const char* pName);
void J3DAPI sithSprite_CacheAdd(rdSprite3* pSprite);
void J3DAPI sithSprite_CacheRemove(const rdSprite3* pSprite);

void sithSprite_InstallHooks(void)
{
    J3D_HOOKFUNC(sithSprite_Startup);
    J3D_HOOKFUNC(sithSprite_Shutdown);
    J3D_HOOKFUNC(sithSprite_Update);
    J3D_HOOKFUNC(sithSprite_Draw);
    J3D_HOOKFUNC(sithSprite_Create);
    J3D_HOOKFUNC(sithSprite_ReadStaticSpritesListText);
    J3D_HOOKFUNC(sithSprite_WriteStaticSpritesListBinary);
    J3D_HOOKFUNC(sithSprite_ReadStaticSpritesListBinary);
    J3D_HOOKFUNC(sithSprite_FreeWorldSprites);
    J3D_HOOKFUNC(sithSprite_Load);
    J3D_HOOKFUNC(sithSprite_AllocWorldSprites);
    J3D_HOOKFUNC(sithSprite_Initialize);
    J3D_HOOKFUNC(sithSprite_CacheFind);
    J3D_HOOKFUNC(sithSprite_CacheAdd);
    J3D_HOOKFUNC(sithSprite_CacheRemove);
}

void sithSprite_ResetGlobals(void)
{}

int sithSprite_Startup(void)
{
    sithSprite_pHashtable = stdHashtbl_New(128u);
    if ( !sithSprite_pHashtable )
    {
        SITHLOG_ERROR("Failed to allocate memory for sprites.\n");
        return 1;
    }

    return 0;
}

void sithSprite_Shutdown(void)
{
    if ( sithSprite_pHashtable )
    {
        stdHashtbl_Free(sithSprite_pHashtable);
    }

    sithSprite_pHashtable = NULL;
}

void J3DAPI sithSprite_Update(SithThing* pThing, uint32_t secDeltaTime)
{
    J3D_UNUSED(secDeltaTime);
    SITH_ASSERTREL(pThing->renderData.data.pSprite3);

    SithThing* pThingMeshAttached = pThing->thingInfo.spriteInfo.pThingMeshAttached;
    if ( pThingMeshAttached )
    {
        if ( pThingMeshAttached->type )
        {
            int bSkipBuildingJoints = pThingMeshAttached->renderData.bSkipBuildingJoints;
            pThingMeshAttached->renderData.bSkipBuildingJoints = 1;

            rdMatrix34 meshOrient;
            rdModel3_GetMeshMatrix(&pThingMeshAttached->renderData, &pThingMeshAttached->orient, pThing->thingInfo.spriteInfo.attachMeshNum, &meshOrient);
            pThingMeshAttached->renderData.bSkipBuildingJoints = bSkipBuildingJoints;

            rdVector_Copy3(&pThing->pos, &meshOrient.dvec);
            rdMatrix_Copy34(&pThing->orient, &pThingMeshAttached->orient);
            sithThing_SetSector(pThing, pThingMeshAttached->pInSector, /*bNotidy*/1);
        }
    }
}

int J3DAPI sithSprite_Draw(SithThing* pThing)
{
    if ( !pThing->renderData.data.pSprite3 )
    {
        SITHLOG_ERROR("No rdsprite data in sithSprite_Draw().\n");
        return 0;
    }

    if ( (pThing->flags & SITH_TF_AIRDESTROYED) != 0 && pThing->pInSector && (pThing->pInSector->flags & SITH_SECTOR_UNDERWATER) == 0 )
    {
        sithThing_DestroyThing(pThing);
        return 0;
    }

    rdSprite3* pSprite3             = pThing->renderData.data.pSprite3;
    pSprite3->width                 = pThing->thingInfo.spriteInfo.width;
    pSprite3->height                = pThing->thingInfo.spriteInfo.height;
    pSprite3->widthHalf             = pSprite3->width / 2.0f;
    pSprite3->heightHalf            = pSprite3->height / 2.0f;
    pSprite3->face.extraLight.alpha = pThing->thingInfo.spriteInfo.alpha;
    pSprite3->rollAngle             = pThing->thingInfo.spriteInfo.rollAngle;

    return rdThing_Draw(&pThing->renderData, &pThing->orient);
}

void J3DAPI sithSprite_Create(SithThing* pThing)
{
    if ( !pThing->renderData.data.pSprite3 )
    {
        SITHLOG_ERROR("No rdsprite data in sithSprite_Draw().\n");
        return;
    }

    pThing->thingInfo.spriteInfo.width  = pThing->renderData.data.pSprite3->width;
    pThing->thingInfo.spriteInfo.height = pThing->renderData.data.pSprite3->height;
    pThing->thingInfo.spriteInfo.alpha  = pThing->renderData.data.pSprite3->face.extraLight.alpha;
}

int J3DAPI sithSprite_WriteStaticSpritesListText(const SithWorld* pWorld)
{
    if ( stdConffile_WriteLine("###### Sprite information ######\n")
        || stdConffile_WriteLine("Section: SPRITES\n\n")
        || stdConffile_Printf("World sprites %d\n\n", pWorld->numSprites) )
    {
        return 1;
    }

    for ( size_t i = 0; i < pWorld->numSprites; ++i )
    {
        if ( stdConffile_Printf("%d: %s\n", i, pWorld->aSprites[i].aName) )
        {
            return 1;
        }
    }

    return stdConffile_WriteLine("end\n") || stdConffile_WriteLine("################################\n\n\n");
}

int J3DAPI sithSprite_ReadStaticSpritesListText(SithWorld* pWorld, int bSkip)
{
    if ( bSkip )
    {
        return 1;
    }

    SITH_ASSERTREL(pWorld != NULL);
    SITH_ASSERTREL(pWorld->aSprites == NULL);
    SITH_ASSERTREL(pWorld->numSprites == 0);

    stdConffile_ReadArgs();
    if ( strcmp(stdConffile_g_entry.aArgs[0].argValue, "world") || strcmp(stdConffile_g_entry.aArgs[1].argValue, "sprites") ) // TODO: Replace with strcmpi
    {
        SITHLOG_ERROR("Parse error reading static sprites list line %d.\n", stdConffile_GetLineNumber());
        return 1;
    }

    size_t numSprites = atoi(stdConffile_g_entry.aArgs[2].argValue);
    if ( !numSprites )
    {
        return 0;
    }

    if ( sithSprite_AllocWorldSprites(pWorld, numSprites) )
    {
        SITHLOG_ERROR("Memory error while reading sprites, line %d.\n", stdConffile_GetLineNumber());
        return 1;
    }

    float progress = 70.0f;
    sithWorld_UpdateLoadProgress(progress);

    const float progressDelta = 10.0f / (float)numSprites;
    while ( stdConffile_ReadArgs() && strcmp(stdConffile_g_entry.aArgs[0].argValue, "end") ) // TODO: Replace with strcmpi
    {
        if ( !sithSprite_Load(pWorld, stdConffile_g_entry.aArgs[1].argValue) )
        {
            SITHLOG_ERROR("Parse error while reading sprites, line %d.\n", stdConffile_GetLineNumber());
            return 1;
        }

        progress += progressDelta;
        sithWorld_UpdateLoadProgress(progress);
    }

    sithWorld_UpdateLoadProgress(80.0f);
    SITHLOG_STATUS("Sprites read.  Sprite array space %d, used %d.\n", pWorld->sizeSprites, pWorld->numSprites);

    SITH_ASSERTREL(pWorld->numSprites <= pWorld->sizeSprites);
    return 0;
}

int J3DAPI sithSprite_WriteStaticSpritesListBinary(tFileHandle fh, SithWorld* pWorld)
{
    for ( size_t i = 0; i < pWorld->numSprites; ++i )
    {
        static_assert(STD_ARRAYLEN(pWorld->aSprites[i].aName) == 64, "STD_ARRAYLEN(pWorld->aSprites[i].aName) == 64");
        if ( sith_g_pHS->pFileWrite(fh, &pWorld->aSprites[i].aName, STD_ARRAYLEN(pWorld->aSprites[i].aName)) != STD_ARRAYLEN(pWorld->aSprites[i].aName) )
        {
            return 1;
        }
    }

    return 0;
}

int J3DAPI sithSprite_ReadStaticSpritesListBinary(tFileHandle fh, SithWorld* pWorld)
{
    size_t numSprites = pWorld->numSprites;
    if ( sithSprite_AllocWorldSprites(pWorld, numSprites) )
    {
        return 1;
    }

    for ( size_t i = 0; i < numSprites; ++i )
    {
        char aFilename[64]; // Note, must be 64
        if ( sith_g_pHS->pFileRead(fh, aFilename, STD_ARRAYLEN(aFilename)) != STD_ARRAYLEN(aFilename)
            || !sithSprite_Load(pWorld, aFilename) )
        {
            return 1;
        }
    }

    return 0;
}

void J3DAPI sithSprite_FreeWorldSprites(SithWorld* pWorld)
{
    SITH_ASSERTREL(pWorld != NULL);

    if ( !pWorld->sizeSprites )
    {
        SITH_ASSERTREL(pWorld->aSprites == NULL);
        return;
    }

    SITH_ASSERTREL(pWorld->aSprites != NULL);
    for ( size_t i = 0; i < pWorld->numSprites; ++i )
    {
        sithSprite_CacheRemove(&pWorld->aSprites[i]);
        rdSprite_FreeEntry(&pWorld->aSprites[i]);
    }

    stdMemory_Free(pWorld->aSprites);
    pWorld->aSprites    = NULL;
    pWorld->numSprites  = 0;
    pWorld->sizeSprites = 0;
}

rdSprite3* J3DAPI sithSprite_Load(SithWorld* pWorld, const char* pName)
{
    SITH_ASSERTREL(pWorld != NULL);
    SITH_ASSERTREL(pWorld->aSprites != NULL);

    rdSprite3* pSprite3 = sithSprite_CacheFind(pName);
    if ( pSprite3 )
    {
        return pSprite3;
    }

    SITH_ASSERTREL(pWorld->numSprites <= pWorld->sizeSprites);
    if ( pWorld->numSprites >= pWorld->sizeSprites )
    {
        SITHLOG_ERROR("No space to define new sprite '%s'.\n", pName);
        return NULL;
    }

    pSprite3 = &pWorld->aSprites[pWorld->numSprites];

    char aPath[128];
    STD_FORMAT(aPath, "%s%c%s", "misc\\spr", '\\', pName);
    if ( !stdConffile_Open(aPath) )
    {
        if ( !strcmp(pName, "default.spr") ) // TODO: Replace with strcmpi
        {
            return NULL;
        }

        pSprite3 = sithSprite_Load(pWorld, "default.spr");
        if ( !pSprite3 )
        {
            SITHLOG_ERROR("Sprite %s not found, no default found.\n", pName);
            return NULL;
        }

        SITHLOG_ERROR("Sprite %s not found, using default.\n", pName);
        return pSprite3;
    }

    // Parse spr file

    if ( !stdConffile_ReadArgs() || stdConffile_g_entry.numArgs != 14 )
    {
        SITHLOG_ERROR("Bad data in sprite file %s.\n", pName);
        stdConffile_Close();
        return NULL;
    }

    char aMatFilename[64];
    STD_STRCPY(aMatFilename, stdConffile_g_entry.aArgs[0].argValue);

    unsigned type = atoi(stdConffile_g_entry.aArgs[1].argValue);
    float width   = atof(stdConffile_g_entry.aArgs[2].argValue);
    float height  = atof(stdConffile_g_entry.aArgs[3].argValue);

    rdGeometryMode geo = atoi(stdConffile_g_entry.aArgs[4].argValue);
    rdLightMode light  = atoi(stdConffile_g_entry.aArgs[5].argValue);
    atoi(stdConffile_g_entry.aArgs[6].argValue);// Skip tex mode

    rdVector4 extraLight;
    extraLight.red   = atof(stdConffile_g_entry.aArgs[7].argValue);
    extraLight.green = atof(stdConffile_g_entry.aArgs[8].argValue);
    extraLight.blue  = atof(stdConffile_g_entry.aArgs[9].argValue);
    extraLight.alpha = atof(stdConffile_g_entry.aArgs[10].argValue);

    rdVector3 offset;
    offset.x = atof(stdConffile_g_entry.aArgs[11].argValue);
    offset.y = atof(stdConffile_g_entry.aArgs[12].argValue);
    offset.z = atof(stdConffile_g_entry.aArgs[13].argValue);

    // Finished parsing
    stdConffile_Close();

    if ( type > 2 || width <= 0.0f || height <= 0.0f )
    {
        SITHLOG_ERROR("Bad sprite params.\n");
        return NULL;
    }

    if ( !rdSprite_NewEntry(pSprite3, pName, type, aMatFilename, width, height, geo, light, &extraLight, &offset) )
    {
        SITHLOG_ERROR("Failed to load sprite '%s'.\n", pName);
        return NULL;
    }

    sithSprite_CacheAdd(pSprite3);
    ++pWorld->numSprites;
    return pSprite3;
}

int J3DAPI sithSprite_AllocWorldSprites(SithWorld* pWorld, size_t size)
{
    SITH_ASSERTREL(pWorld->aSprites == NULL);

    pWorld->aSprites = (rdSprite3*)STDMALLOC(sizeof(rdSprite3) * size);
    if ( !pWorld->aSprites )
    {
        SITHLOG_ERROR("Failed to allocate sprites array.\n");
        return 1;
    }

    pWorld->sizeSprites = size;
    pWorld->numSprites  = 0;
    memset(pWorld->aSprites, 0, sizeof(rdSprite3) * pWorld->sizeSprites);
    return 0;
}

void J3DAPI sithSprite_Initialize(SithThing* pThing)
{
    rdVector3 pyr;
    rdMatrix_ExtractAngles34(&pThing->orient, &pyr);
    if ( pyr.roll != 0.0f )
    {
        if ( pyr.roll < 0.0f )
        {
            pyr.roll = pyr.roll + 360.0f;
        }

        pThing->thingInfo.spriteInfo.rollAngle = pyr.roll;
    }
}

rdSprite3* J3DAPI sithSprite_CacheFind(const char* pName)
{
    SITH_ASSERTREL(pName != NULL);
    SITH_ASSERTREL(sithSprite_pHashtable != NULL);

    return (rdSprite3*)stdHashtbl_Find(sithSprite_pHashtable, pName);
}

void J3DAPI sithSprite_CacheAdd(rdSprite3* pSprite)
{
    SITH_ASSERTREL(pSprite != NULL);
    SITH_ASSERTREL(strlen(pSprite->aName) > 0);
    SITH_ASSERTREL(sithSprite_pHashtable != NULL);

    stdHashtbl_Add(sithSprite_pHashtable, pSprite->aName, pSprite);
}

void J3DAPI sithSprite_CacheRemove(const rdSprite3* pSprite)
{
    SITH_ASSERTREL(pSprite != NULL);
    SITH_ASSERTREL(strlen(pSprite->aName) > 0);
    SITH_ASSERTREL(sithSprite_pHashtable != NULL);

    stdHashtbl_Remove(sithSprite_pHashtable, pSprite->aName);
}
