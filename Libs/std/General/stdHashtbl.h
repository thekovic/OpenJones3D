#ifndef STD_STDHASHTBL_H
#define STD_STDHASHTBL_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

tHashTable* J3DAPI stdHashtbl_New(size_t size);
unsigned int J3DAPI stdHashtbl_CalculateHash(const char* pData, signed int hashSize);
size_t J3DAPI stdHashtbl_GetNextPrime(size_t nextPrime);
int J3DAPI stdHashtbl_isPrime(size_t val);
size_t J3DAPI stdHashtbl_nextPrime(size_t candidate);
void J3DAPI stdHashtbl_Free(tHashTable* pTable);
void J3DAPI stdHashtbl_FreeListNodes(tLinkListNode* pNode);
int J3DAPI stdHashtbl_Add(tHashTable* pTable, const char* pName, void* pData);
tLinkListNode* J3DAPI stdHashtbl_GetTailNode(const tLinkListNode* pCur);
void* J3DAPI stdHashtbl_Find(const tHashTable* pTable, const char* pName);
tLinkListNode* J3DAPI stdHashtbl_FindNode(const tHashTable* pTable, const char* pName, int* pNodeHash);
int J3DAPI stdHashtbl_Remove(tHashTable* pTable, const char* pName);

// Helper hooking functions
void stdHashtbl_InstallHooks(void);
void stdHashtbl_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDHASHTBL_H
