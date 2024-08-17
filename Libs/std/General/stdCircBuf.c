#include "stdCircBuf.h"
#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>


void stdCircBuf_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(stdCircBuf_New);
    // J3D_HOOKFUNC(stdCircBuf_Free);
    // J3D_HOOKFUNC(stdCircBuf_Purge);
    // J3D_HOOKFUNC(stdCircBuf_GetNextElement);
}

void stdCircBuf_ResetGlobals(void)
{

}

int J3DAPI stdCircBuf_New(tCircularBuffer* pCirc, int numElementsDesired, int sizeOfEachElement)
{
    return J3D_TRAMPOLINE_CALL(stdCircBuf_New, pCirc, numElementsDesired, sizeOfEachElement);
}

void J3DAPI stdCircBuf_Free(tCircularBuffer* pCirc)
{
    J3D_TRAMPOLINE_CALL(stdCircBuf_Free, pCirc);
}

void J3DAPI stdCircBuf_Purge(tCircularBuffer* pCirc)
{
    J3D_TRAMPOLINE_CALL(stdCircBuf_Purge, pCirc);
}

void* J3DAPI stdCircBuf_GetNextElement(tCircularBuffer* pCirc)
{
    return J3D_TRAMPOLINE_CALL(stdCircBuf_GetNextElement, pCirc);
}
