%{
#include <sith/Cog/sithCogExec.h>
#include <sith/Main/sithMain.h>

#include <stdio.h>
%}

%token IDENTIFIER CONSTANT_INT CONSTANT_FLOAT STRING_LITERAL VECTOR_LITERAL
%token LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP
%token TYPE_NAME
%nonassoc IFX
%token IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN CALL

%nonassoc ELSE

%union {
    void *pointerValue;
    float floatValue;
    int intValue;
    rdVector3 vecValue;
    SithCogSyntaxNode *pNode;
}

%{
extern int yylex(void);
extern size_t yylinenum;
static SithCogSyntaxNode* pBranchNode;
static SithCogSyntaxNode* pConditionNode;

uint32_t sithCogParse_GetNextLabel(void);
uint32_t J3DAPI sithCogParse_GetSymbolLabel(size_t symbolId);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeLeafNode(SithCogExecOpcode opcode, int symbolId);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeVectorLeafNode(SithCogExecOpcode opcode, const YYSTYPE* pVal);
SithCogSyntaxNode* J3DAPI sithCogParse_MakeNode(SithCogSyntaxNode* pLeft, SithCogSyntaxNode* pRight, SithCogExecOpcode opcode, int value);
%}

%start statement_list
%%

primary_expression
    : IDENTIFIER         { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_PUSHSYMBOL, $1.intValue); }
    | CONSTANT_INT       { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_PUSHINT, $1.intValue); }
    | CONSTANT_FLOAT     { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_PUSHFLOAT, $1.intValue); }
    | STRING_LITERAL     { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_PUSHSYMBOL, $1.intValue); }
    | VECTOR_LITERAL     { $$.pNode = sithCogParse_MakeVectorLeafNode( SITHCOGEXEC_OPCODE_PUSHVECTOR, &$1.vecValue); }
    | '(' expression ')' { $$.pNode = $2.pNode; }
    ;

postfix_expression
    : primary_expression
    | postfix_expression '[' expression ']'                 { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_ARRAYIDX, 0); }
    | postfix_expression '(' ')'                            { $$.pNode = sithCogParse_MakeNode($1.pNode, NULL,  SITHCOGEXEC_OPCODE_CALLFUNC, 0); }
    | postfix_expression '(' argument_expression_list ')'   { $$.pNode = sithCogParse_MakeNode($3.pNode, $1.pNode,  SITHCOGEXEC_OPCODE_CALLFUNC, 0); }
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list ',' assignment_expression    { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_NOP, 0); }
    ;

unary_operator
    : '-'                                                   { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_NEG, 0); }
    | '!'                                                   { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_CMPFALSE, 0); }
    ;

unary_expression
    : postfix_expression
    | unary_operator unary_expression                       { $$.pNode = sithCogParse_MakeNode($2.pNode, $1.pNode,  SITHCOGEXEC_OPCODE_NOP, 0); }
    ;

multiplicative_expression
    : unary_expression
    | multiplicative_expression '*' unary_expression        { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_MUL, 0); }
    | multiplicative_expression '/' unary_expression        { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_DIV, 0); }
    | multiplicative_expression '%' unary_expression        { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_MOD, 0); }
    ;

additive_expression
    : multiplicative_expression
    | additive_expression '+' multiplicative_expression     { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_ADD, 0); }
    | additive_expression '-' multiplicative_expression     { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_SUB, 0); }
    ;

relational_expression
    : additive_expression
    | relational_expression '<' additive_expression         { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPLS, 0); }
    | relational_expression '>' additive_expression         { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPGT, 0); }
    | relational_expression LE_OP additive_expression       { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPLE, 0); }
    | relational_expression GE_OP additive_expression       { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPGE, 0); }
    ;

equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression       { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPEQ, 0); }
    | equality_expression NE_OP relational_expression       { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPNE, 0); }
    ;

and_expression
    : equality_expression
    | and_expression '&' equality_expression                { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_AND, 0); }
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression '^' and_expression            { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_XOR, 0); }
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression '|' exclusive_or_expression   { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_OR, 0); }
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPAND, 0); }
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression    { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_CMPOR, 0); }
    ;

assignment_expression
    : logical_or_expression
    | unary_expression '=' assignment_expression            { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_ASSIGN, 0); }
    ;

expression
    : assignment_expression
    | expression ',' assignment_expression                  { $$.pNode = sithCogParse_MakeNode($1.pNode, $3.pNode,  SITHCOGEXEC_OPCODE_NOP, 0); }
    ;

statement
    : labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;

labeled_statement
    : IDENTIFIER ':' statement                              { 
                                                                $$.pNode = sithCogParse_MakeNode($3.pNode, NULL,  SITHCOGEXEC_OPCODE_NOP, 0); 
                                                                $$.pNode-> parentLabel = sithCogParse_GetSymbolLabel($1.intValue);
                                                            }
    ;

compound_statement
    : '{' '}'                                               { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_NOP, 0); }
    | '{' statement_list '}'                                { $$.pNode = $2.pNode; }
    ;

statement_list
    : statement
    | statement_list statement                              { $$.pNode = sithCogParse_MakeNode($1.pNode, $2.pNode,  SITHCOGEXEC_OPCODE_NOP, 0);  }
    ;

expression_statement
    : ';'                                                   { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_NOP, 0); }
    | expression ';'                                        { /* expression ; */ }
    ;

selection_statement
    : IF '(' expression ')' statement %prec IFX             {
                                                                pBranchNode = sithCogParse_MakeNode($5.pNode, NULL,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                                pBranchNode->childLabel = sithCogParse_GetNextLabel();
                                                                pConditionNode = sithCogParse_MakeNode($3.pNode, NULL,  SITHCOGEXEC_OPCODE_JZ, pBranchNode->childLabel);
                                                                $$.pNode = sithCogParse_MakeNode(pConditionNode, pBranchNode,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                            }
    | IF '(' expression ')' statement ELSE statement        {
                                                                pBranchNode = sithCogParse_MakeNode($7.pNode, NULL,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                                pBranchNode-> parentLabel = sithCogParse_GetNextLabel();
                                                                pBranchNode->childLabel = sithCogParse_GetNextLabel();
                                                                pConditionNode = sithCogParse_MakeNode($3.pNode, NULL,  SITHCOGEXEC_OPCODE_JZ, pBranchNode-> parentLabel);
                                                                pConditionNode = sithCogParse_MakeNode(pConditionNode, $5.pNode,  SITHCOGEXEC_OPCODE_JMP, pBranchNode->childLabel);
                                                                $$.pNode = sithCogParse_MakeNode(pConditionNode, pBranchNode,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                            }
    ;

iteration_statement
    : WHILE '(' expression ')' statement                    {
                                                                pBranchNode = sithCogParse_MakeNode($3.pNode, NULL,  SITHCOGEXEC_OPCODE_JZ, 0);// expression (cond)
                                                                $$.pNode = sithCogParse_MakeNode(pBranchNode, $5.pNode,  SITHCOGEXEC_OPCODE_JMP, 0);
                                                                $$.pNode->childLabel = sithCogParse_GetNextLabel();
                                                                $$.pNode-> parentLabel = sithCogParse_GetNextLabel();
                                                                pBranchNode->value = $$.pNode->childLabel;
                                                                $$.pNode->value = $$.pNode-> parentLabel;
                                                            }
    | DO statement WHILE '(' expression ')' ';'             {
                                                                $$.pNode = sithCogParse_MakeNode($2.pNode, $5.pNode,  SITHCOGEXEC_OPCODE_JNZ, 0);
                                                                $$.pNode-> parentLabel = sithCogParse_GetNextLabel();
                                                                $$.pNode->value = $$.pNode-> parentLabel;
                                                            }
    | FOR '(' expression_statement expression_statement expression ')' statement {
                                                                                     pBranchNode = sithCogParse_MakeNode($7.pNode, NULL,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                                                     pBranchNode->childLabel = sithCogParse_GetNextLabel();
                                                                                     
                                                                                     pConditionNode = sithCogParse_MakeNode($4.pNode, NULL,  SITHCOGEXEC_OPCODE_JZ, pBranchNode->childLabel);
                                                                                     pConditionNode-> parentLabel = sithCogParse_GetNextLabel();
                                                                                     $$.pNode = sithCogParse_MakeNode(pBranchNode, $5.pNode,  SITHCOGEXEC_OPCODE_JMP, pConditionNode-> parentLabel);
                                                                                     pConditionNode->value = sithCogParse_GetNextLabel();
                                                                                     $$.pNode->childLabel = pConditionNode->value;
                                                                                     SithCogSyntaxNode* tmp3 = sithCogParse_MakeNode($3.pNode, pConditionNode,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                                                     $$.pNode = sithCogParse_MakeNode(tmp3, $$.pNode,  SITHCOGEXEC_OPCODE_NOP, 0);
                                                                                 }
    ;

jump_statement
    : GOTO IDENTIFIER ';'       { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_JMP, sithCogParse_GetSymbolLabel($2.intValue)); }
    | CALL IDENTIFIER ';'       { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_CALL, sithCogParse_GetSymbolLabel($2.intValue)); }
    | RETURN ';'                { $$.pNode = sithCogParse_MakeLeafNode( SITHCOGEXEC_OPCODE_RET, 0); }
    ;

%%

extern char yytext[];

void yyerror(char* s)
{
    SITHLOG_ERROR("PARSER %s: line %d.\n", s, yylinenum);
}
