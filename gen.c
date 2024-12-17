#include <stdio.h>
#include <string.h>
#include "type.h"
typedef enum op {OP_NULL, LOD,LDX,LDXB, LDA, LITI, STO,STOB,STX,STXB,
	SUBI,SUBF,DIVI,DIVF,ADDI,ADDF,OFFSET,MULI,MULF, MOD, 
	LSSI,LSSF,GTRI,GTRF, LEQI,LEQF,GEQI,GEQF,NEQI,NEQF,EQLI,EQLF, 
	NOT, OR, AND, CVTI,CVTF, JPC,JPCR,JMP,JPT,JPTR,INT,
	INCI,INCF,DECI,DECF,SUP, CAL,ADDR, RET, MINUSI,MINUSF,CHK,
	LDI,LDIB,	 POP, POPB } OPCODE;
char *opcode_name[]={"OP_NULL", "LOD","LDX","LDXB", "LDA","LITI", 
	"STO","STOB","STX","STXB", "SUBI","SUBF","DIVI","DIVF","ADDI","ADDF", 	"OFFSET","MULI","MULF", "MOD",	"LSSI","LSSF","GTRI","GTRF", 	
	"LEQI","LEQF","GEQI","GEQF","NEQI","NEQF","EQLI","EQLF", 
	"NOT", "OR", "AND", "CVTI","CVTF", "JPC","JPCR", "JMP","JPT","JPTR", 	"INT","INCI","INCF","DECI","DECF","SUP","CAL","ADDR","RET", 	
	"MINUSI","MINUSF","CHK","LDI","LDIB", "POP","POPB"} ;

void code_generation(A_NODE *);
void gen_literal_table();
void gen_program(A_NODE *);
void gen_expression(A_NODE *);
void gen_expression_left(A_NODE *);
void gen_arg_expression(A_NODE *);
void gen_statement(A_NODE *, int, int);
void gen_statement_list(A_NODE *,int, int);
void gen_initializer_global(A_NODE *, A_TYPE *, int);
void gen_initializer_local(A_NODE *, A_TYPE *, int);
void gen_declaration_list(A_ID *);
void gen_declaration(A_ID *);
void gen_code_i(OPCODE,int,int);
void gen_code_f(OPCODE,int,float);
void gen_code_s(OPCODE,int,char *);
void gen_code_l(OPCODE, int, int);
void gen_label_number(int);
void gen_label_name(char *);
void gen_error();
int  get_label();
int label_no=0;
int gen_err=0;
extern FILE *fout;
extern A_TYPE *int_type, *float_type, *char_type, *void_type, *string_type;
extern A_LITERAL literal_table[];
extern int literal_no;
void code_generation(A_NODE *node) 
{	
	gen_program(node);
	gen_literal_table();
}
void gen_literal_table()
{
	int i;
	for (i=1;i<=literal_no; i++) {
		fprintf(fout,".literal %5d  ",literal_table[i].addr);
		if (literal_table[i].type==int_type)
			fprintf(fout,"%d\n",literal_table[i].value.i);
		else if (literal_table[i].type==float_type)
			fprintf(fout,"%f\n",literal_table[i].value.f);
		else if (literal_table[i].type==char_type)
			fprintf(fout,"%d\n",literal_table[i].value.c);
		else if (literal_table[i].type==string_type)
			fprintf(fout,"%s\n",literal_table[i].value.s);
	}
}
void gen_program(A_NODE *node)
{
	switch(node->name) {
	   case N_PROGRAM : 
		???????	
		gen_declaration_list(node->clink);
		break;
	  }
}
void gen_expression(A_NODE *node)
{
	A_ID *id;
	A_TYPE *t;
	int I, ll; 
	switch(node->name) {
	   case N_EXP_IDENT : 
		id=node->clink;
		t=id->type;
		switch (id->kind) {
		   case ID_VAR:
		   case ID_PARM:
		   case ID_ENUM_LITERAL:
		   ??????????
		}
		break;
	   case N_EXP_INT_CONST :
		?????????
	   case N_EXP_FLOAT_CONST :
		??????????
	   case N_EXP_CHAR_CONST :
		???????????
	   case N_EXP_STRING_LITERAL :
		???????????
	   case N_EXP_ARRAY :
		???????????
	   case N_EXP_FUNCTION_CALL : 
		?????????????
	   case N_EXP_STRUCT : 
		// not implemented yet
		break;
	   case N_EXP_ARROW:
		// not implemented yet
		break;
	   case N_EXP_POST_INC :
		?????????????
	   case N_EXP_POST_DEC :
		??????????????????
	   case N_EXP_PRE_INC :
		?????????????????
	   case N_EXP_PRE_DEC :
		?????????????
	   case N_EXP_NOT :
		????????????
	   case N_EXP_PLUS :
		????????????
	   case N_EXP_MINUS :
		????????????
	   case N_EXP_AMP :
		????????????
	   case N_EXP_STAR :
		????????????
	   case N_EXP_SIZE_EXP :
		????????????
	   case N_EXP_SIZE_TYPE :
		????????????
	   case N_EXP_CAST :
		????????????
	   case N_EXP_MUL :
		????????????
	   case N_EXP_DIV :
		????????????
	   case N_EXP_MOD :
		????????????
   	   case N_EXP_ADD :
		????????????
	   case N_EXP_SUB : 
		????????????
	   case N_EXP_LSS :
		????????????
	   case N_EXP_GTR :
		????????????
	   case N_EXP_LEQ :
		????????????
	   case N_EXP_GEQ :
		????????????
	   case N_EXP_NEQ :
		????????????
	   case N_EXP_EQL :
		????????????
	   case N_EXP_AND :
		????????????
	   case N_EXP_OR :
		????????????
	   case N_EXP_ASSIGN : 
		????????????
	}
}
void gen_expression_left(A_NODE *node)
{
	A_ID *id;
	A_TYPE *t;
	int result;
	switch(node->name) {
	   case N_EXP_IDENT : 
		id=node->clink;
		t=id->type;
		switch (id->kind) {
		   case ID_VAR:
		   case ID_PARM:
		   case ID_FUNC:
		}
		break;
	   case N_EXP_ARRAY :
		?????????????
	   case N_EXP_STRUCT : 
		// not implemented yet
		break;
	   case N_EXP_ARROW :
		// not implemented yet
		break;
	   case N_EXP_STAR :
		??????????????????
	   case N_EXP_INT_CONST :
	   case N_EXP_FLOAT_CONST :
	   case N_EXP_CHAR_CONST :
	   case N_EXP_STRING_LITERAL :
	   case N_EXP_FUNCTION_CALL : 
	   case N_EXP_POST_INC :
	   case N_EXP_POST_DEC :
	   case N_EXP_PRE_INC :
	   case N_EXP_PRE_DEC :
	   case N_EXP_NOT :
	   case N_EXP_MINUS :
	   case N_EXP_SIZE_EXP :
	   case N_EXP_SIZE_TYPE :
	   case N_EXP_CAST :
	   case N_EXP_MUL :
	   case N_EXP_DIV :
	   case N_EXP_MOD :
	   case N_EXP_ADD :
	   case N_EXP_SUB : 
	   case N_EXP_LSS :
	   case N_EXP_GTR :
	   case N_EXP_LEQ :
	   case N_EXP_GEQ :
	   case N_EXP_NEQ :
	   case N_EXP_EQL :
	   case N_EXP_AMP :
	   case N_EXP_AND :
	   case N_EXP_OR :
	   case N_EXP_ASSIGN :
		gen_error(12,node->line);
		break;
	}
}
void  gen_arg_expression(A_NODE *node)
{
	A_NODE *n;
	switch(node->name) {
	   case N_ARG_LIST : 
		gen_expression(node->llink);
		gen_arg_expression(node->rlink);
		break;
	   case N_ARG_LIST_NIL : 
		break;
	   default :
		gen_error(100,node->line);
		break;
	}	
}
int get_label()
{
	label_no++;
	return(label_no);
}
void gen_statement(A_NODE *node, int cont_label, int break_label)
{
	A_NODE *n;
	int i,l1,l2,l3;
	switch(node->name) {
	   case N_STMT_LABEL_CASE :
		// not implemented
		break;
	   case N_STMT_LABEL_DEFAULT :
		// not implemented
		break;
	   case N_STMT_COMPOUND:
		????????
		break;
	   case N_STMT_EMPTY:
		break;
	   case N_STMT_EXPRESSION:
		????????
		break;
	   case N_STMT_IF:
		????????
		break;
	   case N_STMT_IF_ELSE:
		????????
		break;
	   case N_STMT_SWITCH:
		// not implemented
		break;
	   case N_STMT_WHILE:
		????????
		break;
	   case N_STMT_DO:
		????????
		break;
	   case N_STMT_FOR:
		??????????????
		break;
	   case N_STMT_CONTINUE:
		break;
	   case N_STMT_BREAK:
		break;
	   case N_STMT_RETURN:
		break;
	}
}
void gen_statement_list(A_NODE *node, int cont_label, int break_label)
{
	switch(node->name) {
	   case N_STMT_LIST:
		gen_statement(node->llink,cont_label, break_label);
		gen_statement_list(node->rlink,cont_label, break_label);
		break;
	   case N_STMT_LIST_NIL:
		break;
	   default :
		gen_error(100,node->line);
		break;
		
	}
}
void gen_initializer_global(A_NODE *node, A_TYPE *t, int addr)
{
}
void gen_initializer_local(A_NODE *node, A_TYPE *t, int addr)
{
}
void gen_declaration_list(A_ID *id)
{
	while (id) {
		gen_declaration(id);
		id=id->link;
	}
}
void gen_declaration(A_ID *id)
{
	int i;
	A_NODE *node;
	switch (id->kind) {
		case ID_VAR:
			break;
		case ID_FUNC:
			break;
		case ID_PARM:
		case ID_TYPE:
		case ID_ENUM:
		case ID_STRUCT:
		case ID_FIELD:
		case ID_ENUM_LITERAL:
		case ID_NULL:  
			break;
	}
}
void gen_error(int i, int ll, char *s )
{
	gen_err++;
	printf("*** error at line %d: ",ll);
  	switch (i) {
		case 11: printf("illegal identifier in expression \n");
			break;
		case 12: printf("illegal l-value expression \n");
			break;
		case 13: printf("identifier %s not l-value expression \n",s);
			break;
		case 20: printf("illegal default label in switch statement \n");
			break;
		case 21: printf("illegal case label in switch statement \n");
			break;
		case 22: printf("no destination for continue statement \n");
			break;
		case 23: printf("no destination for break statement \n");
			break;
		case 100: printf("fatal compiler error during code generation\n");
			break;
		default: printf("unknown \n");
			break;
	}
}
void gen_code_i(OPCODE op,  int l, int a)
{
	fprintf(fout,"\t%9s   %d, %d\n",opcode_name[op],l,a);
}
void gen_code_f(OPCODE op,  int l, float a)
{
	fprintf(fout,"\t%9s   %d, %f\n",opcode_name[op],l,a);
}
void gen_code_s(OPCODE op,  int l, char *a)
{
	fprintf(fout,"\t%9s   %d, %s\n",opcode_name[op],l,a);
}
void gen_code_l(OPCODE op,  int l, int a)
{
	fprintf(fout,"\t%9s   %d, L%d\n",opcode_name[op],l,a);
}
void gen_label_number(int i)
{
	fprintf(fout,"L%d:\n",i);
	
}
void gen_label_name(char *s)
{
	fprintf(fout,"%s:\n",s);
	
}
