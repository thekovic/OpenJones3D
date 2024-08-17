#include "stdLinkList.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdLinkList_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdLinkList_AddNode);
    // J3D_HOOKFUNC(stdLinkList_RemoveNode);
}

void stdLinkList_ResetGlobals(void)
{

}

void J3DAPI stdLinkList_AddNode(tLinkListNode* pCur, tLinkListNode* pNodeToAdd)
{
    J3D_TRAMPOLINE_CALL(stdLinkList_AddNode, pCur, pNodeToAdd);
}

void J3DAPI stdLinkList_RemoveNode(tLinkListNode* pCur)
{
    J3D_TRAMPOLINE_CALL(stdLinkList_RemoveNode, pCur);
}
