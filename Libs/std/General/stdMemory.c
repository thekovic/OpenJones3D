#include "std.h"
#include "stdMemory.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdMemory_aZoneData J3D_DECL_FAR_ARRAYVAR(stdMemory_aZoneData, tMemoryBlock(*)[8456])
//#define bStartup J3D_DECL_FAR_VAR(bStartup, int)
//#define bOpen J3D_DECL_FAR_VAR(bOpen, int)

static bool bStartup = false;
static bool bOpen    = false;

void stdMemory_InstallHooks(void)
{
    J3D_HOOKFUNC(stdMemory_Startup);
    J3D_HOOKFUNC(stdMemory_Shutdown);
    J3D_HOOKFUNC(stdMemory_Open);
    J3D_HOOKFUNC(stdMemory_Close);
    J3D_HOOKFUNC(stdMemory_Malloc);
    J3D_HOOKFUNC(stdMemory_Free);
    J3D_HOOKFUNC(stdMemory_Realloc);
    // J3D_HOOKFUNC(stdMemory_BlockMalloc);
    // J3D_HOOKFUNC(stdMemory_BlockFree);
    // J3D_HOOKFUNC(stdMemory_BlockRealloc);
    // J3D_HOOKFUNC(stdMemory_BlockAlloc);
}

void stdMemory_ResetGlobals(void)
{
    memset(&stdMemory_aZoneData, 0, sizeof(stdMemory_aZoneData));
    //memset(&bStartup, 0, sizeof(bStartup));
    //memset(&bOpen, 0, sizeof(bOpen));
    //memset(&stdMemory_g_curState, 0, sizeof(stdMemory_g_curState));
}

void* J3DAPI stdMemory_BlockMalloc(size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockMalloc, size);
}

void J3DAPI stdMemory_BlockFree(void* pMemory)
{
    J3D_TRAMPOLINE_CALL(stdMemory_BlockFree, pMemory);
}

void* J3DAPI stdMemory_BlockRealloc(void* pData, size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockRealloc, pData, size);
}

void* J3DAPI stdMemory_BlockAlloc(size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdMemory_BlockAlloc, size);
}

int stdMemory_Startup(void)
{
    STD_ASSERTREL(bStartup == false);
    memset(&stdMemory_g_curState, 0, sizeof(stdMemory_g_curState));
    bStartup = true;
    return 1;
}

void stdMemory_Shutdown(void)
{
    STD_ASSERTREL(bStartup == true);
    // TODO: Should we close the system here?
    bStartup = false;
}

int stdMemory_Open(void)
{
    STD_ASSERTREL(bStartup == true);
    if ( bOpen )
    {
        STDLOG_ERROR("Warning: System already open!\n");
        return 0;
    }
    else
    {
        bOpen = true;
        return 1;
    }
}

void stdMemory_Close(void)
{
    if ( bOpen )
    {
        STDLOG_ERROR("Warning: System already closed!\n");
        return;
    }

    STDLOG_STATUS("Maximum dynamic memory used: %d bytes.\n", stdMemory_g_curState.maxBytes);
    if ( stdMemory_g_curState.totalAllocs || stdMemory_g_curState.totalBytes )
    {
        STDLOG_ERROR("UNFREED MEMORY ALERT!\n\n");
        std_g_pHS->pErrorPrint("File\tLine\tSize\tNumber\n\n");

        tMemoryHeader* pCur = stdMemory_g_curState.header.pNext;
        size_t count = 0;
        while ( pCur && count < 100 )
        {
            std_g_pHS->pErrorPrint("%s\t%d\t%d\t%d\n", pCur->pFilename, pCur->line, pCur->size, pCur->number);
            pCur = pCur->pNext;;
            ++count;
        }
    }

    bOpen = false;
}

void* J3DAPI stdMemory_Malloc(size_t size, const char* pFilename, size_t line)
{
    size_t totalBytes;
    tMemoryHeader* pData;

    pData = (tMemoryHeader*)std_g_pHS->pMalloc(size + sizeof(tMemoryHeap));
    if ( !pData )
    {
        return 0;
    }

    pData->number = stdMemory_g_curState.totalAllocs;
    pData->id = (uint32_t)pData;
    pData->size = size;
    pData->pFilename = pFilename;
    pData->line = line;
    pData->pNext = stdMemory_g_curState.header.pNext;
    if ( pData->pNext )
    {
        pData->pNext->pPrev = pData;
    }

    pData->pPrev = &stdMemory_g_curState.header;
    stdMemory_g_curState.header.pNext = pData;

    memset(&pData[1], 0xCC, size);

    pData->magic = 0x12345678;
    *(int*)((char*)&pData[1].number + size) = 0x12345678;
    stdMemory_g_curState.totalBytes += size;

    if ( stdMemory_g_curState.maxBytes <= stdMemory_g_curState.totalBytes )
    {
        totalBytes = stdMemory_g_curState.totalBytes;
    }
    else
    {
        totalBytes = stdMemory_g_curState.maxBytes;
    }

    stdMemory_g_curState.maxBytes = totalBytes;
    ++stdMemory_g_curState.totalAllocs;
    return &pData[1];
}

void J3DAPI stdMemory_Free(void* pBytes)
{
    tMemoryHeader* pHeader = (tMemoryHeader*)((char*)pBytes - sizeof(tMemoryHeader));
    STD_ASSERTREL((pHeader != ((void*)0)) && ((uint32_t)pHeader == pHeader->id));
    STD_ASSERTREL(pHeader->magic == 0x12345678);
    STD_ASSERTREL(*(uint32_t*)((uint8_t*)pBytes + pHeader->size) == 0x12345678);
    memset(pBytes, 0xDD, pHeader->size);
    if ( pHeader->pNext )
    {
        pHeader->pNext->pPrev = pHeader->pPrev;
    }

    STD_ASSERTREL(pHeader->pPrev);
    pHeader->pPrev->pNext = pHeader->pNext;
    stdMemory_g_curState.totalBytes -= pHeader->size;
    --stdMemory_g_curState.totalAllocs;
    std_g_pHS->pFree(pHeader);
}

void* J3DAPI stdMemory_Realloc(void* pBytes, size_t size, const char* pFilename, size_t line)
{
    size_t totalBytes;
    tMemoryHeap* pHeap;
    tMemoryHeader* pHeader;
    size_t v8;

    if ( !pBytes )
    {
        return stdMemory_Malloc(size, pFilename, line);
    }

    if ( size )
    {
        pHeader = (tMemoryHeader*)((char*)pBytes - sizeof(tMemoryHeader));
        STD_ASSERTREL((pHeader != ((void*)0)) && ((uint32_t)pHeader == pHeader->id));
        v8 = pHeader->size;
        pHeap = (tMemoryHeap*)std_g_pHS->pRealloc(pHeader, size + sizeof(tMemoryHeap));
        if ( pHeap )
        {
            pHeap->header.id = (uint32_t)pHeap;
            pHeap->header.size = size;
            pHeap->header.pFilename = pFilename;
            pHeap->header.line = line;
            if ( pHeap->header.pNext )
            {
                pHeap->header.pNext->pPrev = &pHeap->header;
            }

            if ( pHeap->header.pPrev )
            {
                pHeap->header.pPrev->pNext = &pHeap->header;
            }

            pHeap->header.magic = 0x12345678;
            *(void**)((char*)&pHeap->pMemory + size) = (void*)0x12345678;
            stdMemory_g_curState.totalBytes += size - v8;
            if ( stdMemory_g_curState.maxBytes <= stdMemory_g_curState.totalBytes )
            {
                totalBytes = stdMemory_g_curState.totalBytes;
            }
            else
            {
                totalBytes = stdMemory_g_curState.maxBytes;
            }

            stdMemory_g_curState.maxBytes = totalBytes;
            return &pHeap->pMemory;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        stdMemory_Free(pBytes);
        return 0;
    }
}
