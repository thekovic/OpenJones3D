#ifndef SITH_SITHCOGPARSE_H
#define SITH_SITHCOGPARSE_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

void J3DAPI sithCogParse_FreeParseTree();
int J3DAPI sithCogParse_Load(const char* pFilename, SithCogScript* pScript, int bParseDescription);
signed int J3DAPI sithCogParse_ParseSectionCode(SithCogScript* pScript);
SithCogSymbolTable* J3DAPI sithCogParse_DuplicateSymbolTable(const SithCogSymbolTable* pSource);
SithCogSymbolTable* J3DAPI sithCogParse_AllocSymbolTable(int numElements);
int J3DAPI sithCogParse_FreeSymbolTable(SithCogSymbolTable* pTable);
SithCogSymbol* J3DAPI sithCogParse_AddSymbol(SithCogSymbolTable* pTable, const char* pName);
void J3DAPI sithCogParse_SetSymbolValue(SithCogSymbol* pSymbol, const SithCogSymbolValue* pValue);
SithCogSymbol* J3DAPI sithCogParse_GetSymbol(const SithCogSymbolTable* pLocal, const char* pName);
SithCogSymbol* J3DAPI sithCogParse_GetSymbolByID(const SithCogSymbolTable* pTable, unsigned int symbolId);
int J3DAPI sithCogParse_GetSymbolLabel(unsigned int symbolId);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeLeafNode(int opcode, int symbolId);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeVectorLeafNode(int opcode, const YYSTYPE* pVal);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeNode(SithCogSyntaxNode* pLeft, SithCogSyntaxNode* pRight, int opcode, int value);
void J3DAPI sithCogParse_LexerGetSymbol(const char* pName);
void J3DAPI sithCogParse_LexerSetStringLiteral(const char* pString);
void J3DAPI sithCogParse_LexerSetVectorLiteral(const char* pString);
int J3DAPI sithCogParse_GetNextLabel();
SithCogSyntaxNode* J3DAPI sithCogParse_GetNextNode();
void J3DAPI sithCogParse_ResetTreeNodes();
void J3DAPI sithCogParse_GenerateLabelTable(const SithCogSyntaxNode* pRoot);
void J3DAPI sithCogParse_GenerateCode(const SithCogSyntaxNode* pNode);
signed int J3DAPI sithCogParse_ParseSymbols(SithCogScript* pScript, int bParseDescription);
int J3DAPI sithCogParse_ParseSymbolRef(SithCogScript* pScript, SithCogSymbolRefType symbolType, int bCopySymbolDescription);
int J3DAPI sithCogParse_ParseFlex(SithCogScript* pScript, int bParseDescription);
signed int J3DAPI sithCogParse_ParseInt(SithCogScript* pScript, int bCopyDescription);
signed int J3DAPI sithCogParse_ParseVector(SithCogScript* pScript, int bParseDescription);
int J3DAPI sithCogParse_ParseMessage(SithCogScript* pScript);
void J3DAPI sithCogParse_InitScriptMessageHandlers(SithCogScript* pScript);

// Helper hooking functions
void sithCogParse_InstallHooks(void);
void sithCogParse_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGPARSE_H
