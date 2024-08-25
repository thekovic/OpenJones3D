#include "std.h"
#include "stdLinkList.h"

#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

void stdLinkList_InstallHooks(void)
{
    J3D_HOOKFUNC(stdLinkList_AddNode);
    J3D_HOOKFUNC(stdLinkList_RemoveNode);
}

void stdLinkList_ResetGlobals(void)
{
}

void J3DAPI stdLinkList_AddNode(tLinkListNode* pCur, tLinkListNode* pNodeToAdd)
{
    STD_ASSERTREL(pCur != ((void*)0));
    STD_ASSERTREL(pNodeToAdd != ((void*)0));
    STD_ASSERTREL(pNodeToAdd->prev == ((void*)0));
    STD_ASSERTREL(pNodeToAdd->next == ((void*)0));

    tLinkListNode* pNext = pCur->next;
    pNodeToAdd->prev     = pCur;
    pNodeToAdd->next     = pCur->next;
    pCur->next           = pNodeToAdd;
    if ( pNext ) {
        pCur->next->prev = pNodeToAdd;
    }
}

void J3DAPI stdLinklist_InsertNode(tLinkListNode* pCur, tLinkListNode* pNodeToInsert)
{
    STD_ASSERTREL(pCur != ((void*)0));
    STD_ASSERTREL(pNodeToInsert != ((void*)0));
    STD_ASSERTREL(pNodeToInsert->prev == ((void*)0));
    STD_ASSERTREL(pNodeToInsert->next == ((void*)0));

    tLinkListNode* pPrev = pCur->prev;
    pNodeToInsert->next  = pCur;
    pNodeToInsert->prev  = pPrev;
    pCur->prev           = pNodeToInsert;

    if ( pPrev ) {
        pPrev->next = pNodeToInsert;
    }
}

void J3DAPI stdLinklist_AppendNode(tLinkListNode* pCur, tLinkListNode* pNodeToAdd)
{
    STD_ASSERTREL(pCur != ((void*)0));
    STD_ASSERTREL(pNodeToAdd != ((void*)0));
    STD_ASSERTREL(pNodeToAdd->prev == ((void*)0));
    STD_ASSERTREL(pNodeToAdd->next == ((void*)0));

    tLinkListNode* pPrev;
    for ( pPrev = pCur; pPrev->next; pPrev = pPrev->next ) {
        ;
    }

    pNodeToAdd->prev = pPrev;
    pNodeToAdd->next = NULL;
    pPrev->next = pNodeToAdd;
}

void J3DAPI stdLinkList_RemoveNode(tLinkListNode* pCur)
{
    STD_ASSERTREL(pCur != ((void*)0));
    if ( pCur->prev ) {
        pCur->prev->next = pCur->next;
    }

    if ( pCur->next ) {
        pCur->next->prev = pCur->prev;
    }

    pCur->next = NULL;
    pCur->prev = NULL;
}


void J3DAPI stdLinklist_NewList(tLinkListNode* pFirstOfNewList)
{
    STD_ASSERTREL(pFirstOfNewList != ((void*)0));
    if ( pFirstOfNewList->prev ) {
        pFirstOfNewList->prev->next = NULL;
    }

    pFirstOfNewList->prev = NULL;
}

void J3DAPI stdLinklist_DetachNode(tLinkListNode* pNode)
{
    pNode->prev = NULL;
    pNode->next = NULL;
}

size_t J3DAPI stdLinklist_GetCount(const tLinkListNode* pCur)
{
    int count = 0;
    while ( pCur )
    {
        ++count;
        pCur = pCur->next;
    }

    return count;
}

tLinkListNode* J3DAPI stdLinklist_GetNode(const tLinkListNode* pFirstNode, int n)
{
    STD_ASSERTREL(n >= 0);
    STD_ASSERTREL(pFirstNode != ((void*)0));

    while ( pFirstNode && n > 0 )
    {
        --n;
        pFirstNode = pFirstNode->next;
    }

    return (tLinkListNode*)pFirstNode;
}

tLinkListNode* J3DAPI stdLinklist_GetLastNode(const tLinkListNode* pCur)
{
    if ( !pCur ) {
        return NULL;
    }

    while ( pCur->next ) {
        pCur = pCur->next;
    }

    return (tLinkListNode*)pCur;
}

tLinkListNode* J3DAPI stdLinklist_GetFirstNode(const tLinkListNode* pCur)
{
    if ( !pCur ) {
        return NULL;
    }

    while ( pCur->prev ) {
        pCur = pCur->prev;
    }

    return (tLinkListNode*)pCur;
}
