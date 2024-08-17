#include "stdHashtbl.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

#define stdHashtbl_aPrimeTable J3D_DECL_FAR_ARRAYVAR(stdHashtbl_aPrimeTable, int(*)[32])

void stdHashtbl_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdHashtbl_New);
    // J3D_HOOKFUNC(stdHashtbl_CalculateHash);
    // J3D_HOOKFUNC(stdHashtbl_GetNextPrime);
    // J3D_HOOKFUNC(stdHashtbl_isPrime);
    // J3D_HOOKFUNC(stdHashtbl_nextPrime);
    // J3D_HOOKFUNC(stdHashtbl_Free);
    // J3D_HOOKFUNC(stdHashtbl_FreeListNodes);
    // J3D_HOOKFUNC(stdHashtbl_Add);
    // J3D_HOOKFUNC(stdHashtbl_GetTailNode);
    // J3D_HOOKFUNC(stdHashtbl_Find);
    // J3D_HOOKFUNC(stdHashtbl_FindNode);
    // J3D_HOOKFUNC(stdHashtbl_Remove);
}

void stdHashtbl_ResetGlobals(void)
{
    int stdHashtbl_aPrimeTable_tmp[32] = {
      23,
      53,
      79,
      101,
      151,
      211,
      251,
      307,
      353,
      401,
      457,
      503,
      557,
      601,
      653,
      701,
      751,
      809,
      853,
      907,
      953,
      1009,
      1103,
      1201,
      1301,
      1409,
      1511,
      1601,
      1709,
      1801,
      1901,
      1999
    };
    memcpy(&stdHashtbl_aPrimeTable, &stdHashtbl_aPrimeTable_tmp, sizeof(stdHashtbl_aPrimeTable));
    
}

tHashTable* J3DAPI stdHashtbl_New(size_t size)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_New, size);
}

unsigned int J3DAPI stdHashtbl_CalculateHash(const char* pData, signed int hashSize)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_CalculateHash, pData, hashSize);
}

size_t J3DAPI stdHashtbl_GetNextPrime(size_t nextPrime)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_GetNextPrime, nextPrime);
}

int J3DAPI stdHashtbl_isPrime(size_t val)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_isPrime, val);
}

size_t J3DAPI stdHashtbl_nextPrime(size_t candidate)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_nextPrime, candidate);
}

void J3DAPI stdHashtbl_Free(tHashTable* pTable)
{
    J3D_TRAMPOLINE_CALL(stdHashtbl_Free, pTable);
}

void J3DAPI stdHashtbl_FreeListNodes(tLinkListNode* pNode)
{
    J3D_TRAMPOLINE_CALL(stdHashtbl_FreeListNodes, pNode);
}

int J3DAPI stdHashtbl_Add(tHashTable* pTable, const char* pName, void* pData)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_Add, pTable, pName, pData);
}

tLinkListNode* J3DAPI stdHashtbl_GetTailNode(const tLinkListNode* pCur)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_GetTailNode, pCur);
}

void* J3DAPI stdHashtbl_Find(const tHashTable* pTable, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_Find, pTable, pName);
}

tLinkListNode* J3DAPI stdHashtbl_FindNode(const tHashTable* pTable, const char* pName, int* pNodeHash)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_FindNode, pTable, pName, pNodeHash);
}

int J3DAPI stdHashtbl_Remove(tHashTable* pTable, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(stdHashtbl_Remove, pTable, pName);
}
