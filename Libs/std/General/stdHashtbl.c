#include "std.h"
#include "stdHashtbl.h"
#include "stdLinklist.h"
#include "stdMemory.h"
#include "stdUtil.h"

#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

static size_t stdHashtbl_aPrimeTable[32] = {
    23u,   53u,   79u,   101u,  151u,  211u,  251u,  307u,
    353u,  401u,  457u,  503u,  557u,  601u,  653u,  701u,
    751u,  809u,  853u,  907u,  953u,  1009u, 1103u, 1201u,
    1301u, 1409u, 1511u, 1601u, 1709u, 1801u, 1901u, 1999u
};

static inline unsigned int J3DAPI CalculateHash(const char* pData, signed int hashSize);
static inline size_t J3DAPI GetNextPrime(size_t nextPrime);
static inline int J3DAPI isPrime(size_t val);

void stdHashtbl_InstallHooks(void)
{
    J3D_HOOKFUNC(stdHashtbl_New);
    J3D_HOOKFUNC(CalculateHash);
    J3D_HOOKFUNC(GetNextPrime);
    J3D_HOOKFUNC(isPrime);
    J3D_HOOKFUNC(stdHashtbl_nextPrime);
    J3D_HOOKFUNC(stdHashtbl_Free);
    J3D_HOOKFUNC(stdHashtbl_FreeListNodes);
    J3D_HOOKFUNC(stdHashtbl_Add);
    J3D_HOOKFUNC(stdHashtbl_GetTailNode);
    J3D_HOOKFUNC(stdHashtbl_Find);
    J3D_HOOKFUNC(stdHashtbl_FindNode);
    J3D_HOOKFUNC(stdHashtbl_Remove);
}

void stdHashtbl_ResetGlobals(void)
{
    /*int stdHashtbl_aPrimeTable_tmp[32] = {
        23u,   53u,   79u,   101u,  151u,  211u,  251u,  307u,
        353u,  401u,  457u,  503u,  557u,  601u,  653u,  701u,
        751u,  809u,  853u,  907u,  953u,  1009u, 1103u, 1201u,
        1301u, 1409u, 1511u, 1601u, 1709u, 1801u, 1901u, 1999u
    };
    memcpy(&stdHashtbl_aPrimeTable, &stdHashtbl_aPrimeTable_tmp, sizeof(stdHashtbl_aPrimeTable));*/

}

unsigned int J3DAPI CalculateHash(const char* pData, signed int hashSize)
{
    signed int hashValue = 0;
    while ( *pData ) {
        hashValue = *pData++ + 65599 * hashValue;
    }

    hashValue = abs(hashValue % hashSize);
    STD_ASSERTREL(hashValue >= 0);
    STD_ASSERTREL(hashValue < hashSize);
    return hashValue;
}

size_t J3DAPI GetNextPrime(size_t nextPrime)
{
    for ( size_t i = 0; i < STD_ARRAYLEN(stdHashtbl_aPrimeTable); ++i )
    {
        if ( nextPrime < stdHashtbl_aPrimeTable[i] )
        {
            nextPrime = stdHashtbl_aPrimeTable[i];
            break;
        }
    }

    if ( nextPrime > 1999u ) {
        nextPrime = stdHashtbl_nextPrime(nextPrime);
    }

    STD_ASSERTREL(isPrime(nextPrime));
    return nextPrime;
}

int J3DAPI isPrime(size_t val)
{
    if ( val < 2 ) {
        return 0;
    }

    for ( size_t i = 2; i < (val - 1); ++i )
    {
        if ( !(val % i) ) {
            return 0;
        }
    }

    return 1;
}

tHashTable* J3DAPI stdHashtbl_New(size_t size)
{
    tHashTable* pTable = (tHashTable*)STDMALLOC(sizeof(tHashTable));
    if ( !pTable ) {
        return NULL;
    }

    memset(pTable, 0, sizeof(tHashTable));

    pTable->numNodes = GetNextPrime(size);
    pTable->paNodes = (tLinkListNode*)STDMALLOC(sizeof(tLinkListNode) * pTable->numNodes);
    if ( !pTable->paNodes ) {
        return NULL;
    }

    memset(pTable->paNodes, 0, sizeof(tLinkListNode) * pTable->numNodes);
    pTable->pfHashFunc = CalculateHash;
    return pTable;
}

size_t J3DAPI stdHashtbl_nextPrime(size_t candidate)
{
    while ( !isPrime(candidate) ) {
        ++candidate;
    }

    STD_ASSERTREL(isPrime(candidate));
    return candidate;
}

void J3DAPI stdHashtbl_Free(tHashTable* pTable)
{

    STD_ASSERTREL(pTable != NULL);
    for ( size_t i = 0; i < pTable->numNodes; ++i ) {
        stdHashtbl_FreeListNodes(&pTable->paNodes[i]);
    }

    stdMemory_Free(pTable->paNodes);
    stdMemory_Free(pTable);
}

void J3DAPI stdHashtbl_FreeListNodes(tLinkListNode* pNode)
{
    tLinkListNode* pNextNode = NULL;
    for ( tLinkListNode* pCurNode = pNode->next; pCurNode; pCurNode = pNextNode )
    {
        pNextNode = pCurNode->next;
        stdMemory_Free(pCurNode);
    }
}

int J3DAPI stdHashtbl_Add(tHashTable* pTable, const char* pName, void* pData)
{
    STD_ASSERTREL(pTable != NULL);
    STD_ASSERTREL(pData != NULL);

    if ( stdHashtbl_Find(pTable, pName) ) {
        return 0;
    }

    unsigned int nodeIdx = pTable->pfHashFunc(pName, pTable->numNodes);
    tLinkListNode* pCur = stdHashtbl_GetTailNode(&pTable->paNodes[nodeIdx]);
    if ( pCur->name )
    {
        tLinkListNode* pNode = (tLinkListNode*)STDMALLOC(sizeof(tLinkListNode));
        if ( !pNode ) {
            return 0;
        }

        memset(pNode, 0, sizeof(tLinkListNode));
        pNode->name = pName;
        pNode->data = pData;
        stdLinkList_AddNode(pCur, pNode);
    }
    else
    {
        memset(&pTable->paNodes[nodeIdx], 0, sizeof(pTable->paNodes[nodeIdx]));
        pTable->paNodes[nodeIdx].name = pName;
        pTable->paNodes[nodeIdx].data = pData;
    }

    return 1;
}

tLinkListNode* J3DAPI stdHashtbl_GetTailNode(const tLinkListNode* pCur)
{
    STD_ASSERTREL(pCur != NULL);
    while ( pCur->next ) {
        pCur = pCur->next;
    }

    return (tLinkListNode*)pCur;
}

void* J3DAPI stdHashtbl_Find(const tHashTable* pTable, const char* pName)
{
    int pNodeHash;
    tLinkListNode* pNode = stdHashtbl_FindNode(pTable, pName, &pNodeHash);
    if ( pNode ) {
        return pNode->data;
    }
    return NULL;
}

tLinkListNode* J3DAPI stdHashtbl_FindNode(const tHashTable* pTable, const char* pName, int* pNodeIdx)
{
    if ( !pTable ) {
        return NULL;
    }

    *pNodeIdx = pTable->pfHashFunc(pName, pTable->numNodes);
    for ( tLinkListNode* pCurNode = &pTable->paNodes[*pNodeIdx]; pCurNode && pCurNode->name; pCurNode = pCurNode->next )
    {
        if ( streq(pCurNode->name, pName) ) {
            return pCurNode;
        }
    }

    return NULL;
}

int J3DAPI stdHashtbl_Remove(tHashTable* pTable, const char* pName)
{
    STD_ASSERTREL(pTable != NULL);

    int nodeIdx = -1;
    tLinkListNode* pNode = stdHashtbl_FindNode(pTable, pName, &nodeIdx);
    if ( !pNode ) {
        return 0;
    }

    tLinkListNode* pNodeNext = pNode->next;
    stdLinkList_RemoveNode(pNode);

    if ( &pTable->paNodes[nodeIdx] == pNode )
    {
        if ( pNodeNext )
        {
            memcpy(&pTable->paNodes[nodeIdx], pNodeNext, sizeof(pTable->paNodes[nodeIdx]));
            tLinkListNode* pNext = pTable->paNodes[nodeIdx].next;
            if ( pNext ) {
                pNext->prev = &pTable->paNodes[nodeIdx];
            }
            stdMemory_Free(pNodeNext);
        }
        else {
            memset(&pTable->paNodes[nodeIdx], 0, sizeof(pTable->paNodes[nodeIdx]));
        }
    }
    else {
        stdMemory_Free(pNode);
    }

    return 1;
}

void J3DAPI stdHashtbl_PrintTableDiagnostics(tHashTable* pTable)
{
    STD_ASSERTREL(pTable != NULL);
    std_g_pHS->pDebugPrint("\nHASHTABLE Diagnostics\n");
    std_g_pHS->pDebugPrint("---------------------\n");

    size_t usedIndices = 0;
    size_t totalNodes = 0;
    size_t maxLookup = 0;
    for ( size_t i = 0; i < pTable->numNodes; ++i )
    {
        if ( pTable->paNodes[i].name )
        {
            ++usedIndices;
            size_t numNodes = stdLinklist_GetCount(&pTable->paNodes[i]);
            totalNodes += numNodes;
            if ( numNodes > maxLookup )
            {
                maxLookup = numNodes;
            }
        }
    }

    std_g_pHS->pDebugPrint(" Maximum Lookups = %d\n", maxLookup);
    std_g_pHS->pDebugPrint(" Filled Indices = %d/%d (%2.2f%%)\n", usedIndices, pTable->numNodes, (double)usedIndices * 100.0f / (double)pTable->numNodes);
    std_g_pHS->pDebugPrint(" Average Lookup = %2.2f\n", (double)totalNodes / (double)usedIndices);
    std_g_pHS->pDebugPrint(" Weighted Lookup = %2.2f\n", (double)totalNodes / (double)pTable->numNodes);
    std_g_pHS->pDebugPrint("---------------------\n");
}

void J3DAPI stdHashtbl_DumpTable(tHashTable* pTable)
{
    STD_ASSERTREL(pTable != NULL);
    std_g_pHS->pDebugPrint("\nHASHTABLE\n---------\n");
    for ( size_t i = 0; i < pTable->numNodes; ++i )
    {
        std_g_pHS->pDebugPrint("Index: %d\t", i);
        std_g_pHS->pDebugPrint("Strings:");
        tLinkListNode* pNode = &pTable->paNodes[i];
        while ( pNode )
        {
            std_g_pHS->pDebugPrint(" '%s'", pNode->name);
            pNode = pNode->next;
        }

        std_g_pHS->pDebugPrint("\n");
    }
}
