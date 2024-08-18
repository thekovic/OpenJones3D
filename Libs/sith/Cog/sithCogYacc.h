#ifndef SITH_SITHCOGYACC_H
#define SITH_SITHCOGYACC_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

#include <stdio.h>

J3D_EXTERN_C_START

#define sithCogYacc_g_yylineno J3D_DECL_FAR_VAR(sithCogYacc_g_yylineno, int)
// extern int sithCogYacc_g_yylineno;

//#define sithCogYacc_g_yylval J3D_DECL_FAR_VAR(sithCogYacc_g_yylval, YYSTYPE)
// extern YYSTYPE sithCogYacc_g_yylval;

void J3DAPI sithCogYacc_yyerror(const char* msg);
int J3DAPI sithCogYacc_yyparse();
int J3DAPI sithCogYacc_yylex();
int sithCogYacc_yy_get_next_buffer(void);
int sithCogYacc_yy_get_previous_state(void);
int J3DAPI sithCogYacc_yy_try_NUL_trans(int yy_current_state);
void J3DAPI sithCogYacc_yyrestart(FILE* input_file);
void sithCogYacc_yy_load_buffer_state(void);
//YY_BUFFER_STATE J3DAPI sithCogYacc_yy_create_buffer(FILE* file, int size);
//void J3DAPI sithCogYacc_yy_init_buffer(YY_BUFFER_STATE b, FILE* file);

// Helper hooking functions
void sithCogYacc_InstallHooks(void);
void sithCogYacc_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHCOGYACC_H
