#include "sithCogExec.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>


void sithCogExec_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogExec_Execute);
    // J3D_HOOKFUNC(sithCogExec_ExecuteMessage);
    // J3D_HOOKFUNC(sithCogExec_PopSymbol);
    // J3D_HOOKFUNC(sithCogExec_PopFlex);
    // J3D_HOOKFUNC(sithCogExec_PopInt);
    // J3D_HOOKFUNC(sithCogExec_PopArray);
    // J3D_HOOKFUNC(sithCogExec_PopVector);
    // J3D_HOOKFUNC(sithCogExec_PopCog);
    // J3D_HOOKFUNC(sithCogExec_PopThing);
    // J3D_HOOKFUNC(sithCogExec_TryPopThing);
    // J3D_HOOKFUNC(sithCogExec_PopTemplate);
    // J3D_HOOKFUNC(sithCogExec_PopSound);
    // J3D_HOOKFUNC(sithCogExec_PopSector);
    // J3D_HOOKFUNC(sithCogExec_PopSurface);
    // J3D_HOOKFUNC(sithCogExec_PopMaterial);
    // J3D_HOOKFUNC(sithCogExec_PopModel3);
    // J3D_HOOKFUNC(sithCogExec_PopKeyframe);
    // J3D_HOOKFUNC(sithCogExec_PopAIClass);
    // J3D_HOOKFUNC(sithCogExec_PopString);
    // J3D_HOOKFUNC(sithCogExec_PushStack);
    // J3D_HOOKFUNC(sithCogExec_PushInt);
    // J3D_HOOKFUNC(sithCogExec_PushFlex);
    // J3D_HOOKFUNC(sithCogExec_PushVector);
    // J3D_HOOKFUNC(sithCogExec_GetOpCode);
    // J3D_HOOKFUNC(sithCogExec_ResetStack);
    // J3D_HOOKFUNC(sithCogExec_PushCallstack);
    // J3D_HOOKFUNC(sithCogExec_PopCallstack);
    // J3D_HOOKFUNC(sithCogExec_PopStack);
    // J3D_HOOKFUNC(sithCogExec_FunctionCallOp);
    // J3D_HOOKFUNC(sithCogExec_RetOp);
    // J3D_HOOKFUNC(sithCogExec_PushNumberOp);
    // J3D_HOOKFUNC(sithCogExec_PushVectorOp);
    // J3D_HOOKFUNC(sithCogExec_CallOp);
    // J3D_HOOKFUNC(sithCogExec_JmpnzOp);
    // J3D_HOOKFUNC(sithCogExec_JmpzOp);
    // J3D_HOOKFUNC(sithCogExec_JmpOp);
    // J3D_HOOKFUNC(sithCogExec_ArrayOp);
    // J3D_HOOKFUNC(sithCogExec_NegFalseOps);
    // J3D_HOOKFUNC(sithCogExec_AssignOp);
    // J3D_HOOKFUNC(sithCogExec_IntererOps);
    // J3D_HOOKFUNC(sithCogExec_FloatOps);
    // J3D_HOOKFUNC(sithCogExec_GetSymbolValue);
}

void sithCogExec_ResetGlobals(void)
{

}

void J3DAPI sithCogExec_Execute(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_Execute, pCog);
}

void J3DAPI sithCogExec_ExecuteMessage(SithCog* pCog, int handlerNum)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_ExecuteMessage, pCog, handlerNum);
}

int J3DAPI sithCogExec_PopSymbol(SithCog* pCog, SithCogSymbolValue* pVal)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopSymbol, pCog, pVal);
}

float J3DAPI sithCogExec_PopFlex(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopFlex, pCog);
}

int J3DAPI sithCogExec_PopInt(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopInt, pCog);
}

int J3DAPI sithCogExec_PopArray(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopArray, pCog);
}

int J3DAPI sithCogExec_PopVector(SithCog* pCog, rdVector3* vec)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopVector, pCog, vec);
}

SithCog* J3DAPI sithCogExec_PopCog(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopCog, pCog);
}

SithThing* J3DAPI sithCogExec_PopThing(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopThing, pCog);
}

SithThing* J3DAPI sithCogExec_TryPopThing(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_TryPopThing, pCog);
}

SithThing* J3DAPI sithCogExec_PopTemplate(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopTemplate, pCog);
}

tSoundHandle J3DAPI sithCogExec_PopSound(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopSound, pCog);
}

SithSector* J3DAPI sithCogExec_PopSector(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopSector, pCog);
}

SithSurface* J3DAPI sithCogExec_PopSurface(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopSurface, pCog);
}

rdMaterial* J3DAPI sithCogExec_PopMaterial(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopMaterial, pCog);
}

rdModel3* J3DAPI sithCogExec_PopModel3(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopModel3, pCog);
}

rdKeyframe* J3DAPI sithCogExec_PopKeyframe(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopKeyframe, pCog);
}

SithAIClass* J3DAPI sithCogExec_PopAIClass(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopAIClass, pCog);
}

const char* J3DAPI sithCogExec_PopString(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopString, pCog);
}

int J3DAPI sithCogExec_PushStack(SithCog* pCog, SithCogSymbolValue* pValue)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PushStack, pCog, pValue);
}

int J3DAPI sithCogExec_PushInt(SithCog* pCog, int val)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PushInt, pCog, val);
}

int J3DAPI sithCogExec_PushFlex(SithCog* pCog, float val)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PushFlex, pCog, val);
}

int J3DAPI sithCogExec_PushVector(SithCog* pCog, const rdVector3* vec)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PushVector, pCog, vec);
}

int J3DAPI sithCogExec_GetOpCode(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_GetOpCode, pCog);
}

void J3DAPI sithCogExec_ResetStack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_ResetStack, pCog);
}

void J3DAPI sithCogExec_PushCallstack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_PushCallstack, pCog);
}

void J3DAPI sithCogExec_PopCallstack(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_PopCallstack, pCog);
}

signed int J3DAPI sithCogExec_PopStack(SithCog* pCog, SithCogSymbolValue* pValue)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PopStack, pCog, pValue);
}

// calls function
void J3DAPI sithCogExec_FunctionCallOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_FunctionCallOp, pCog);
}

void J3DAPI sithCogExec_RetOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_RetOp, pCog);
}

int J3DAPI sithCogExec_PushNumberOp(SithCog* pCog, int opcode)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_PushNumberOp, pCog, opcode);
}

void J3DAPI sithCogExec_PushVectorOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_PushVectorOp, pCog);
}

void J3DAPI sithCogExec_CallOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_CallOp, pCog);
}

// Jump if non zero value is on stack
void J3DAPI sithCogExec_JmpnzOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_JmpnzOp, pCog);
}

// Jump if zero is on stack
void J3DAPI sithCogExec_JmpzOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_JmpzOp, pCog);
}

void J3DAPI sithCogExec_JmpOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_JmpOp, pCog);
}

int J3DAPI sithCogExec_ArrayOp(SithCog* pCog)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_ArrayOp, pCog);
}

void J3DAPI sithCogExec_NegFalseOps(SithCog* pCog, int opcode)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_NegFalseOps, pCog, opcode);
}

void J3DAPI sithCogExec_AssignOp(SithCog* pCog)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_AssignOp, pCog);
}

void J3DAPI sithCogExec_IntererOps(SithCog* pCog, int opcode)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_IntererOps, pCog, opcode);
}

void J3DAPI sithCogExec_FloatOps(SithCog* pCog, int opcode)
{
    J3D_TRAMPOLINE_CALL(sithCogExec_FloatOps, pCog, opcode);
}

SithCogSymbolValue* J3DAPI sithCogExec_GetSymbolValue(SithCogSymbolValue* pDest, SithCog* pCog, SithCogSymbolValue* pValue)
{
    return J3D_TRAMPOLINE_CALL(sithCogExec_GetSymbolValue, pDest, pCog, pValue);
}
