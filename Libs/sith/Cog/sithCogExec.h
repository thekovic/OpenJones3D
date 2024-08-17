#ifndef SITH_SITHCOGEXEC_H
#define SITH_SITHCOGEXEC_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithCogExec_Execute(SithCog* pCog);
void J3DAPI sithCogExec_ExecuteMessage(SithCog* pCog, int handlerNum);
int J3DAPI sithCogExec_PopSymbol(SithCog* pCog, SithCogSymbolValue* pVal);
float J3DAPI sithCogExec_PopFlex(SithCog* pCog);
int J3DAPI sithCogExec_PopInt(SithCog* pCog);
int J3DAPI sithCogExec_PopArray(SithCog* pCog);
int J3DAPI sithCogExec_PopVector(SithCog* pCog, rdVector3* vec);
SithCog* J3DAPI sithCogExec_PopCog(SithCog* pCog);
SithThing* J3DAPI sithCogExec_PopThing(SithCog* pCog);
SithThing* J3DAPI sithCogExec_TryPopThing(SithCog* pCog);
SithThing* J3DAPI sithCogExec_PopTemplate(SithCog* pCog);
tSoundHandle J3DAPI sithCogExec_PopSound(SithCog* pCog);
SithSector* J3DAPI sithCogExec_PopSector(SithCog* pCog);
SithSurface* J3DAPI sithCogExec_PopSurface(SithCog* pCog);
rdMaterial* J3DAPI sithCogExec_PopMaterial(SithCog* pCog);
rdModel3* J3DAPI sithCogExec_PopModel3(SithCog* pCog);
rdKeyframe* J3DAPI sithCogExec_PopKeyframe(SithCog* pCog);
SithAIClass* J3DAPI sithCogExec_PopAIClass(SithCog* pCog);
const char* J3DAPI sithCogExec_PopString(SithCog* pCog);
int J3DAPI sithCogExec_PushStack(SithCog* pCog, SithCogSymbolValue* pValue);
int J3DAPI sithCogExec_PushInt(SithCog* pCog, int val);
int J3DAPI sithCogExec_PushFlex(SithCog* pCog, float val);
int J3DAPI sithCogExec_PushVector(SithCog* pCog, const rdVector3* vec);
int J3DAPI sithCogExec_GetOpCode(SithCog* pCog);
void J3DAPI sithCogExec_ResetStack(SithCog* pCog);
void J3DAPI sithCogExec_PushCallstack(SithCog* pCog);
void J3DAPI sithCogExec_PopCallstack(SithCog* pCog);
signed int J3DAPI sithCogExec_PopStack(SithCog* pCog, SithCogSymbolValue* pValue);
// calls function
void J3DAPI sithCogExec_FunctionCallOp(SithCog* pCog);
void J3DAPI sithCogExec_RetOp(SithCog* pCog);
int J3DAPI sithCogExec_PushNumberOp(SithCog* pCog, int opcode);
void J3DAPI sithCogExec_PushVectorOp(SithCog* pCog);
void J3DAPI sithCogExec_CallOp(SithCog* pCog);
// Jump if non zero value is on stack
void J3DAPI sithCogExec_JmpnzOp(SithCog* pCog);
// Jump if zero is on stack
void J3DAPI sithCogExec_JmpzOp(SithCog* pCog);
void J3DAPI sithCogExec_JmpOp(SithCog* pCog);
int J3DAPI sithCogExec_ArrayOp(SithCog* pCog);
void J3DAPI sithCogExec_NegFalseOps(SithCog* pCog, int opcode);
void J3DAPI sithCogExec_AssignOp(SithCog* pCog);
void J3DAPI sithCogExec_IntererOps(SithCog* pCog, int opcode);
void J3DAPI sithCogExec_FloatOps(SithCog* pCog, int opcode);
SithCogSymbolValue* J3DAPI sithCogExec_GetSymbolValue(SithCogSymbolValue* pDest, SithCog* pCog, SithCogSymbolValue* pValue);

// Helper hooking functions
void sithCogExec_InstallHooks(void);
void sithCogExec_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGEXEC_H
