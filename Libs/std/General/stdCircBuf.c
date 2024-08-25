#include "std.h"
#include "stdMemory.h"
#include "stdCircBuf.h"

#include <j3dcore/j3dhook.h>
#include <std/RTI/symbols.h>

void stdCircBuf_InstallHooks(void)
{
    J3D_HOOKFUNC(stdCircBuf_New);
    J3D_HOOKFUNC(stdCircBuf_Free);
    J3D_HOOKFUNC(stdCircBuf_Purge);
    J3D_HOOKFUNC(stdCircBuf_GetNextElement);
}

void stdCircBuf_ResetGlobals(void)
{

}

int J3DAPI stdCircBuf_New(tCircularBuffer* pCirc, int numElementsDesired, int sizeOfEachElement)
{
    STD_ASSERTREL(pCirc != ((void*)0));
    STD_ASSERTREL(numElementsDesired > 0);
    STD_ASSERTREL(sizeOfEachElement > 0);

    memset(pCirc, 0, sizeof(tCircularBuffer));

    pCirc->paElements = (uint8_t*)STDMALLOC(sizeOfEachElement * numElementsDesired);
    if ( !pCirc->paElements )
    {
        return 0;
    }

    memset(pCirc->paElements, 0, sizeOfEachElement * numElementsDesired);
    pCirc->numAllocated = numElementsDesired;
    pCirc->elementSize = sizeOfEachElement;
    return 1;
}

void J3DAPI stdCircBuf_Free(tCircularBuffer* pCirc)
{
    if ( pCirc->paElements )
    {
        stdMemory_Free(pCirc->paElements);
    }

    pCirc->numAllocated = 0;
    pCirc->paElements = 0;
    pCirc->numValidElements = 0;
}

void J3DAPI stdCircBuf_Purge(tCircularBuffer* pCirc)
{
    STD_ASSERTREL(pCirc != ((void*)0));
    if ( pCirc->paElements && pCirc->numValidElements )
    {
        --pCirc->numValidElements;
        STD_ASSERT(pCirc->paElements != ((void*)0));
        pCirc->iFirst = (pCirc->iFirst + 1) % pCirc->numAllocated;
    }
}

void* J3DAPI stdCircBuf_GetNextElement(tCircularBuffer* pCirc)
{
    int idx;

    STD_ASSERTREL(pCirc != ((void*)0));
    if ( !pCirc->paElements )
    {
        return NULL;
    }

    if ( pCirc->numValidElements >= pCirc->numAllocated )
    {
        stdCircBuf_Purge(pCirc);
    }

    STD_ASSERTREL(pCirc->numValidElements <= pCirc->numAllocated);
    STD_ASSERTREL(pCirc->iFirst < pCirc->numAllocated);

    idx = (pCirc->numValidElements + pCirc->iFirst) % pCirc->numAllocated;
    ++pCirc->numValidElements;
    STD_ASSERTREL(pCirc->paElements != ((void*)0));
    return &pCirc->paElements[pCirc->elementSize * idx];
}
