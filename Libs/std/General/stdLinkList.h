#ifndef STD_STDLINKLIST_H
#define STD_STDLINKLIST_H
#include <j3dcore/j3d.h>
#include <std/types.h>
#include <std/RTI/addresses.h>

J3D_EXTERN_C_START

void J3DAPI stdLinkList_AddNode(tLinkListNode* pCur, tLinkListNode* pNodeToAdd);
void J3DAPI stdLinkList_RemoveNode(tLinkListNode* pCur);

// Helper hooking functions
void stdLinkList_InstallHooks(void);
void stdLinkList_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // STD_STDLINKLIST_H
