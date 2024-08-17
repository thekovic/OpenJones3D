#include "sithCogParse.h"
#include <j3dcore/j3dhook.h>
#include <sith/RTI/symbols.h>

#define sithCogParse_nextlabel J3D_DECL_FAR_VAR(sithCogParse_nextlabel, int)
#define sithCogParse_bSkipYYRestart J3D_DECL_FAR_VAR(sithCogParse_bSkipYYRestart, int)
#define sithCogParse_pCurrentSymbols J3D_DECL_FAR_VAR(sithCogParse_pCurrentSymbols, SithCogSymbolTable*)
#define sithCogParse_aLabelTable J3D_DECL_FAR_ARRAYVAR(sithCogParse_aLabelTable, int(*)[1024])
#define sithCogParse_pCurrentCode J3D_DECL_FAR_VAR(sithCogParse_pCurrentCode, int*)
#define sithCogParse_pCurrentRoot J3D_DECL_FAR_VAR(sithCogParse_pCurrentRoot, SithCogSyntaxNode*)
#define sithCogParse_pSyntaxTree J3D_DECL_FAR_VAR(sithCogParse_pSyntaxTree, SithCogSyntaxNode*)
#define sithCogParse_pCurrentScript J3D_DECL_FAR_VAR(sithCogParse_pCurrentScript, SithCogScript*)
#define sithCogParse_codepos J3D_DECL_FAR_VAR(sithCogParse_codepos, int)
#define sithCogParse_numTreeNodes J3D_DECL_FAR_VAR(sithCogParse_numTreeNodes, int)
#define sithCogParse_syntaxTreeSize J3D_DECL_FAR_VAR(sithCogParse_syntaxTreeSize, int)

void sithCogParse_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(sithCogParse_FreeParseTree);
    // J3D_HOOKFUNC(sithCogParse_Load);
    // J3D_HOOKFUNC(sithCogParse_ParseSectionCode);
    // J3D_HOOKFUNC(sithCogParse_DuplicateSymbolTable);
    // J3D_HOOKFUNC(sithCogParse_AllocSymbolTable);
    // J3D_HOOKFUNC(sithCogParse_FreeSymbolTable);
    // J3D_HOOKFUNC(sithCogParse_AddSymbol);
    // J3D_HOOKFUNC(sithCogParse_SetSymbolValue);
    // J3D_HOOKFUNC(sithCogParse_GetSymbol);
    // J3D_HOOKFUNC(sithCogParse_GetSymbolByID);
    // J3D_HOOKFUNC(sithCogParse_GetSymbolLabel);
    // J3D_HOOKFUNC(sithCogParse_MakeLeafNode);
    // J3D_HOOKFUNC(sithCogParse_MakeVectorLeafNode);
    // J3D_HOOKFUNC(sithCogParse_MakeNode);
    // J3D_HOOKFUNC(sithCogParse_LexerGetSymbol);
    // J3D_HOOKFUNC(sithCogParse_LexerSetStringLiteral);
    // J3D_HOOKFUNC(sithCogParse_LexerSetVectorLiteral);
    // J3D_HOOKFUNC(sithCogParse_GetNextLabel);
    // J3D_HOOKFUNC(sithCogParse_GetNextNode);
    // J3D_HOOKFUNC(sithCogParse_ResetTreeNodes);
    // J3D_HOOKFUNC(sithCogParse_GenerateLabelTable);
    // J3D_HOOKFUNC(sithCogParse_GenerateCode);
    // J3D_HOOKFUNC(sithCogParse_ParseSymbols);
    // J3D_HOOKFUNC(sithCogParse_ParseSymbolRef);
    // J3D_HOOKFUNC(sithCogParse_ParseFlex);
    // J3D_HOOKFUNC(sithCogParse_ParseInt);
    // J3D_HOOKFUNC(sithCogParse_ParseVector);
    // J3D_HOOKFUNC(sithCogParse_ParseMessage);
    // J3D_HOOKFUNC(sithCogParse_InitScriptMessageHandlers);
}

void sithCogParse_ResetGlobals(void)
{
    int sithCogParse_nextlabel_tmp = 1;
    memcpy(&sithCogParse_nextlabel, &sithCogParse_nextlabel_tmp, sizeof(sithCogParse_nextlabel));
    
    int sithCogParse_bSkipYYRestart_tmp = 1;
    memcpy(&sithCogParse_bSkipYYRestart, &sithCogParse_bSkipYYRestart_tmp, sizeof(sithCogParse_bSkipYYRestart));
    
    memset(&sithCogParse_pCurrentSymbols, 0, sizeof(sithCogParse_pCurrentSymbols));
    memset(&sithCogParse_aLabelTable, 0, sizeof(sithCogParse_aLabelTable));
    memset(&sithCogParse_pCurrentCode, 0, sizeof(sithCogParse_pCurrentCode));
    memset(&sithCogParse_pCurrentRoot, 0, sizeof(sithCogParse_pCurrentRoot));
    memset(&sithCogParse_pSyntaxTree, 0, sizeof(sithCogParse_pSyntaxTree));
    memset(&sithCogParse_pCurrentScript, 0, sizeof(sithCogParse_pCurrentScript));
    memset(&sithCogParse_codepos, 0, sizeof(sithCogParse_codepos));
    memset(&sithCogParse_numTreeNodes, 0, sizeof(sithCogParse_numTreeNodes));
    memset(&sithCogParse_syntaxTreeSize, 0, sizeof(sithCogParse_syntaxTreeSize));
}

void J3DAPI sithCogParse_FreeParseTree()
{
    J3D_TRAMPOLINE_CALL(sithCogParse_FreeParseTree);
}

int J3DAPI sithCogParse_Load(const char* pFilename, SithCogScript* pScript, int bParseDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_Load, pFilename, pScript, bParseDescription);
}

signed int J3DAPI sithCogParse_ParseSectionCode(SithCogScript* pScript)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseSectionCode, pScript);
}

SithCogSymbolTable* J3DAPI sithCogParse_DuplicateSymbolTable(const SithCogSymbolTable* pSource)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_DuplicateSymbolTable, pSource);
}

SithCogSymbolTable* J3DAPI sithCogParse_AllocSymbolTable(int numElements)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_AllocSymbolTable, numElements);
}

int J3DAPI sithCogParse_FreeSymbolTable(SithCogSymbolTable* pTable)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_FreeSymbolTable, pTable);
}

SithCogSymbol* J3DAPI sithCogParse_AddSymbol(SithCogSymbolTable* pTable, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_AddSymbol, pTable, pName);
}

void J3DAPI sithCogParse_SetSymbolValue(SithCogSymbol* pSymbol, const SithCogSymbolValue* pValue)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_SetSymbolValue, pSymbol, pValue);
}

SithCogSymbol* J3DAPI sithCogParse_GetSymbol(const SithCogSymbolTable* pLocal, const char* pName)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_GetSymbol, pLocal, pName);
}

SithCogSymbol* J3DAPI sithCogParse_GetSymbolByID(const SithCogSymbolTable* pTable, unsigned int symbolId)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_GetSymbolByID, pTable, symbolId);
}

int J3DAPI sithCogParse_GetSymbolLabel(unsigned int symbolId)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_GetSymbolLabel, symbolId);
}

SithCogSyntaxNode* J3DAPI sithCogParse_MakeLeafNode(int opcode, int symbolId)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_MakeLeafNode, opcode, symbolId);
}

SithCogSyntaxNode* J3DAPI sithCogParse_MakeVectorLeafNode(int opcode, const YYSTYPE* pVal)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_MakeVectorLeafNode, opcode, pVal);
}

SithCogSyntaxNode* J3DAPI sithCogParse_MakeNode(SithCogSyntaxNode* pLeft, SithCogSyntaxNode* pRight, int opcode, int value)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_MakeNode, pLeft, pRight, opcode, value);
}

void J3DAPI sithCogParse_LexerGetSymbol(const char* pName)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_LexerGetSymbol, pName);
}

void J3DAPI sithCogParse_LexerSetStringLiteral(const char* pString)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_LexerSetStringLiteral, pString);
}

void J3DAPI sithCogParse_LexerSetVectorLiteral(const char* pString)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_LexerSetVectorLiteral, pString);
}

int J3DAPI sithCogParse_GetNextLabel()
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_GetNextLabel);
}

SithCogSyntaxNode* J3DAPI sithCogParse_GetNextNode()
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_GetNextNode);
}

void J3DAPI sithCogParse_ResetTreeNodes()
{
    J3D_TRAMPOLINE_CALL(sithCogParse_ResetTreeNodes);
}

void J3DAPI sithCogParse_GenerateLabelTable(const SithCogSyntaxNode* pRoot)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_GenerateLabelTable, pRoot);
}

void J3DAPI sithCogParse_GenerateCode(const SithCogSyntaxNode* pNode)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_GenerateCode, pNode);
}

signed int J3DAPI sithCogParse_ParseSymbols(SithCogScript* pScript, int bParseDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseSymbols, pScript, bParseDescription);
}

int J3DAPI sithCogParse_ParseSymbolRef(SithCogScript* pScript, SithCogSymbolRefType symbolType, int bCopySymbolDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseSymbolRef, pScript, symbolType, bCopySymbolDescription);
}

int J3DAPI sithCogParse_ParseFlex(SithCogScript* pScript, int bParseDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseFlex, pScript, bParseDescription);
}

signed int J3DAPI sithCogParse_ParseInt(SithCogScript* pScript, int bCopyDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseInt, pScript, bCopyDescription);
}

signed int J3DAPI sithCogParse_ParseVector(SithCogScript* pScript, int bParseDescription)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseVector, pScript, bParseDescription);
}

int J3DAPI sithCogParse_ParseMessage(SithCogScript* pScript)
{
    return J3D_TRAMPOLINE_CALL(sithCogParse_ParseMessage, pScript);
}

void J3DAPI sithCogParse_InitScriptMessageHandlers(SithCogScript* pScript)
{
    J3D_TRAMPOLINE_CALL(sithCogParse_InitScriptMessageHandlers, pScript);
}
