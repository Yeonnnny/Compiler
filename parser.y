%{
#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;

#include "type.h"

extern A_TYPE *int_type, *float_type, *char_type, *string_type, *void_type; 

// 신택스 분석 관연 전역 변수
extern int line_no;		// 라인 번호를 위한 변수
extern int syntax_err;		// 신택스 에러 횟수 저장을 위한 변수
extern A_NODE *root;		// 시작 노드
extern A_ID *current_id;	// 현재 가리키고 있는 심볼테이블 주소 
extern int current_level;	// 스코프를 위한 레벨값에 대한 변수

// 시멘틱 분석 관련 전역 변수
extern int global_address;
extern int semantic_err;
extern int literal_no;
extern int literal_size;

void yyerror(const char *);
int yylex(); 

//=========================== 신택스 분석관련 함수 프로토타입 ===============================

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);	// 새로운 노드를 만드는 함수
A_NODE *makeNodeList(NODE_NAME, A_NODE *, A_NODE *);		// 두 개 이상의 단일 노드를 연결하는 함수
A_ID *makeIdentifier(char *);					// 새로운 명칭 추가 함수
A_ID *makeDummyIdentifier();					// 명칭없이 타입만 선언되는 경우 호출됨
A_TYPE *makeType(T_KIND);
A_SPECIFIER *makeSpecifier(A_TYPE *, S_KIND);                   // 선언 지시자 생성하는 함수

A_ID *searchIdentifier(char *, A_ID *);
A_ID *searchIdentifierAtCurrentLevel(char *, A_ID *); // 현재 레벨에서 같은 명칭을 갖고 있는 심볼테이블을 반환하는 함수

A_SPECIFIER *updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND); // 명시자 테이블을 합치는 함수
void checkForwardReference();			// 전방참조에 대한 완전한 선언 여부 확인하는 함수
void setDefaultSpecifier(A_SPECIFIER *);	// 반환타입이나 storage class가 지정되지 않은 경우 기본값으로 설정하는 함수
A_ID *linkDeclaratorList(A_ID *, A_ID *);	// 인자로 받은 두 개의 심볼테이블 목록을 연결하는 함수
A_ID *getIdentifierDeclared(char *);		// 명칭의 사용 가능 여부 검사하는 함수
A_TYPE *getTypeOfStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

A_ID *setDeclaratorInit(A_ID *, A_NODE *);	 // 심볼테이블에 신택스 트리 연결하는 함수
A_ID *setDeclaratorKind(A_ID *, ID_KIND );
A_ID *setDeclaratorType(A_ID *, A_TYPE *);	 // 심볼테이블의 타입 정보 설정하는 함수
A_ID *setDeclaratorElementType(A_ID*, A_TYPE *); // 선언문이나 element의 타입을 설정하는 함수
A_ID *setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);
A_ID *setDeclaratorListSpecifier(A_ID *, A_SPECIFIER *);	// 심볼테이블들을 검사하고, 명시자 테이블로부터 심볼테이블 속성을 결정하고 저장하는 함수
A_ID *setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);	// 함수 명칭 심볼테이블과 몸체에 대한 신택스 트리 연결하는 함수
A_ID *setFunctionDeclaratorBody(A_ID *, A_NODE *);		// 함수 몸체에서 명칭에 대한 심볼테이블과 신택스 트리 연결하는 함수
A_ID *setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);	// 심볼테이블의 타입 정보를 설정하고 명칭 종류를 ID_PARAM으로 설정하며 파라미터 검사
A_ID *setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);
A_TYPE *setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);	// 타입명시자의 기억 장소 명시자 포함 여부 검사 후, 주어진 타입의 엘리먼트 타입으로 타입명시자 지정
A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);		// 첫 번째 인자로 주어진 타입 테이블의 엘리먼트 타입으로 두 번째 인자로 주어진 타입테이블을 연결하는 함수
A_TYPE *setTypeField(A_TYPE *, A_ID *);
A_TYPE *setTypeExpr(A_TYPE *, A_NODE *); // 타입테이블의 <expr> 필드에 신택스 트리 연결
A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

BOOLEAN isNotSameFormalParameters(A_ID *, A_ID *);	// 전달 받은 두 심볼테이블(파라미터 정보를 담은)이 같은지 확인하는 함수
BOOLEAN isNotSameType(A_TYPE *, A_TYPE*);		// 전달받은 두 타입이 같은지 확인하는 함수
BOOLEAN isPointerOrArrayType(A_TYPE *);			// 타입이 pointer인지 array인지 확인하는 함수

void syntax_error();
void initialize();

//===========================================================================================

%}


%start program

// 토큰 정의
%token IDENTIFIER TYPE_IDENTIFIER
%token INTEGER_CONSTANT FLOAT_CONSTANT CHARACTER_CONSTANT STRING_LITERAL
%token PLUS MINUS PLUSPLUS MINUSMINUS BAR BARBAR AMP AMPAMP 
%token ARROW LSS GTR LEQ GEQ EQL NEQ DOTDOTDOT
%token SEMICOLON COLON LP RP LB RB LR RR
%token PERIOD COMMA EXCL STAR SLASH PERCENT ASSIGN
%token AUTO_SYM STATIC_SYM TYPEDEF_SYM 
%token STRUCT_SYM UNION_SYM ENUM_SYM SIZEOF_SYM 
%token IF_SYM ELSE_SYM FOR_SYM WHILE_SYM DO_SYM CONTINUE_SYM
%token BREAK_SYM RETURN_SYM SWITCH_SYM CASE_SYM DEFAULT_SYM
%%

// 프로그램의 시작점
program
    : translation_unit
      {root = makeNode(N_PROGRAM,NIL,$1,NIL); checkForwardReference();}
    ;
     // 프로그램 시작 시 새로운 노드 생성 - root에 최종적인 신택스 트리의 주소 저장
     // 전방참조의 완전한 선언 등장 여부 확인

translation_unit
    : external_declaration		    {$$ = $1;}
    | translation_unit external_declaration {$$ = linkDeclaratorList($1, $2);}
    ;

external_declaration
    : function_definition {$$=$1;}
    | declaration	  {$$=$1;}
    ;


// 함수 선언문
function_definition
    : declaration_specifiers declarator{$$=setFunctionDeclaratorSpecifier($2,$1);} 
      compound_statement {$$=setFunctionDeclaratorBody($3,$4);}
    | declarator {$$=setFunctionDeclaratorSpecifier($1,makeSpecifier(int_type,0));} 
      compound_statement {$$=setFunctionDeclaratorBody($2,$3);}
    ;
     // 선언 지시자가 없는 함수 선언문은 반환 타입을 정수형으로 하기로 약속했기에 int_type의 타입 테이블을 가리킴


// 일반 선언문
declaration_list_opt
    : /*empty*/			  {$$=NIL;}
    | declaration_list		  {$$=$1;}
    ;

declaration_list
    : declaration		   {$$=$1;}
    | declaration_list declaration {$$=linkDeclaratorList($1,$2);}
    ;

declaration
    : declaration_specifiers init_declarator_list_opt SEMICOLON {$$=setDeclaratorListSpecifier($2,$1);}
    ;

declaration_specifiers
    : type_specifier					{$$=makeSpecifier($1,0);}
    | storage_class_specifier				{$$=makeSpecifier(0,$1);}
    | type_specifier declaration_specifiers		{$$=updateSpecifier($2,$1,0);}
    | storage_class_specifier declaration_specifiers	{$$=updateSpecifier($2,0,$1);}
    ;

storage_class_specifier
    : AUTO_SYM		{$$=S_AUTO;}
    | STATIC_SYM	{$$=S_STATIC;}
    | TYPEDEF_SYM	{$$=S_TYPEDEF;}
    ;

init_declarator_list_opt
    : /* empty */		{$$=makeDummyIdentifier();}
    | init_declarator_list	{$$=$1;}
    ;


// 초기화 선언자
init_declarator_list
    : init_declarator				 {$$=$1;}
    | init_declarator_list COMMA init_declarator {$$=linkDeclaratorList($1,$3);}
    ;

init_declarator
    : declarator		    {$$=$1;}
    | declarator ASSIGN initializer {$$=setDeclaratorInit($1,$3);}
    ;


// 초기화
initializer
    : constant_expression	{$$=makeNode(N_INIT_LIST_ONE, NIL, $1, NIL);}
    | LR initializer_list RR	{$$=$2;}
    ;

initializer_list
    : initializer			 {$$=makeNode(N_INIT_LIST,$1,NIL,makeNode(N_INIT_LIST_NIL, NIL,NIL,NIL));} // 초기화 수식이 여러 개인 경우는 마지막의 오른쪽 노드를 NIL로 만듦
    | initializer_list COMMA initializer {$$=makeNodeList(N_INIT_LIST,$1,$3);}
    ;


// 타입 명시자
type_specifier
    : struct_type_specifier	{$$=$1;}
    | enum_type_specifier	{$$=$1;}
    | TYPE_IDENTIFIER		{$$=$1;}
    ;

// 구조체 타입 명시자
struct_type_specifier
    : struct_or_union IDENTIFIER 
      {$$ = setTypeStructOrEnumIdentifier($1,$2,ID_STRUCT);} 
      LR {$$=current_id; current_level++;} struct_declaration_list RR 
      {checkForwardReference(); $$=setTypeField($3,$6); current_level--; current_id=$5;}  
    | struct_or_union {$$=makeType($1);} LR {$$=current_id; current_level++;} 
      struct_declaration_list RR {checkForwardReference(); $$=setTypeField($2,$5); current_level--; current_id=$4;} 
    | struct_or_union IDENTIFIER {$$=getTypeOfStructOrEnumIdentifier($1,$2,ID_STRUCT);}
    ;
     // makeIdentifier() : 명칭이 등장할 때, 해당 명칭의 사용가능 여부를 확인하고 심볼테이블에 추가
     // setTypeStructOrEnumIdentifier() : 구조체나 나열형 타입으로 명시자를 설정하는 함수
     // checkForwardReference() : 구조체필드 선언문 목록만 존재할 때 나중에 완전히 선언되는지 검사 해야 함 
     // setTypeField() : 구조체 몸체에 선언된 변수를 field 타입으로 설정하는 함수
     // current_id : 스코프에 따라 심볼테이블을 가리키도록 지정
     // current_level : 구조체 선언문의 필드 선언문 목록에 대한 레벨값 처리

struct_or_union
    : STRUCT_SYM  {$$=T_STRUCT;}
    | UNION_SYM   {$$=T_UNION;}
    ;

struct_declaration_list
    : struct_declaration			 {$$=$1;}
    | struct_declaration_list struct_declaration {$$=linkDeclaratorList($1,$2);}
    ;

struct_declaration
    : type_specifier struct_declarator_list SEMICOLON {$$=setStructDeclaratorListSpecifier($2,$1);}
    ;

struct_declarator_list
    : struct_declarator				     {$$=$1;}
    | struct_declarator_list COMMA struct_declarator {$$=linkDeclaratorList($1,$3);}
    ;

struct_declarator
    : declarator {$$=$1;}
    ;

// 나열형 타입 명시자
enum_type_specifier
    : ENUM_SYM IDENTIFIER		{$$=setTypeStructOrEnumIdentifier(T_ENUM, $2, ID_ENUM);} 
      LR enumerator_list RR		{$$=setTypeField($3,$5);}
    | ENUM_SYM				{$$=makeType(T_ENUM);}
      LR enumerator_list RR		{$$=setTypeField($2,$4);}
    | ENUM_SYM IDENTIFIER		{$$=getTypeOfStructOrEnumIdentifier(T_ENUM, $2, ID_ENUM);}
    ;

enumerator_list
    : enumerator			{$$=$1;}
    | enumerator_list COMMA enumerator	{$$=linkDeclaratorList($1,$3);}
    ;

enumerator
    : IDENTIFIER {$$=setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL);}
    | IDENTIFIER {$$=setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL);}
      ASSIGN expression {$$=setDeclaratorInit($2,$4);} 
    ;


// 선언자
// 일반 선언자
declarator
    : pointer direct_declarator {$$=setDeclaratorElementType($2,$1);}
    | direct_declarator		{$$=$1;}
    ;

pointer
    : STAR			{$$=makeType(T_POINTER);}
    | STAR pointer		{$$=setTypeElementType($2, makeType(T_POINTER));}
    ;


// 직접 선언자
direct_declarator
    : IDENTIFIER	 {$$=makeIdentifier($1);}
    | LP declarator RP	 {$$=$2;}
    | direct_declarator LB constant_expression_opt RB
      {$$ = setDeclaratorElementType($1, setTypeExpr(makeType(T_ARRAY),$3));}
    | direct_declarator LP {$$=current_id; current_level++;} 
      parameter_type_list_opt RP
      {checkForwardReference(); current_level--; current_id=$3;
      $$=setDeclaratorElementType($1, setTypeField(makeType(T_FUNC),$4));}
    ;


// 파라미터 타입 목록
parameter_type_list_opt
    : /* empty */		{$$=NIL;}
    | parameter_type_list	{$$=$1;}
    ;

parameter_type_list
    : parameter_list			{$$=$1;}
    | parameter_list COMMA DOTDOTDOT	{$$=linkDeclaratorList($1, setDeclaratorKind(makeDummyIdentifier(),ID_PARM));}
    ;

parameter_list
    : parameter_declaration			 {$$=$1;}
    | parameter_list COMMA parameter_declaration {$$=linkDeclaratorList($1,$3);}
    ;

// 파라미터 선언문
parameter_declaration
    : declaration_specifiers declarator		     {$$=setParameterDeclaratorSpecifier($2,$1);}
    | declaration_specifiers abstract_declarator_opt {$$=setParameterDeclaratorSpecifier(setDeclaratorType(makeDummyIdentifier(),$2),$1);}
    ;

// 추상 선언자
abstract_declarator_opt
    : /*empty*/		   {$$=NIL;}
    | abstract_declarator  {$$=$1;}
    ;

abstract_declarator
    : direct_abstract_declarator	  {$$=$1;}
    | pointer				  {$$=makeType(T_POINTER);}
    | pointer direct_abstract_declarator  {$$=setTypeElementType($2, makeType(T_POINTER));}
    ;

direct_abstract_declarator
    : LP abstract_declarator RP	{$$=$2;}
    | LB constant_expression_opt RB {$$=setTypeExpr(makeType(T_ARRAY),$2);}
    | direct_abstract_declarator LB constant_expression_opt RB  {$$=setTypeElementType($1,setTypeExpr(makeType(T_ARRAY),$3));}
    | LP parameter_type_list_opt RP {$$=setTypeExpr(makeType(T_FUNC),$2);}
    | direct_abstract_declarator LP parameter_type_list_opt RP {$$=setTypeElementType($1,setTypeExpr(makeType(T_FUNC),$3));}
    ;

// 명령문
statement_list_opt
    : /*empty*/	     {$$=makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL);}
    | statement_list {$$=$1;}
    ;

statement_list
    : statement			{$$=makeNode(N_STMT_LIST, $1, NIL, makeNode(N_STMT_LIST_NIL,NIL,NIL,NIL));}
    | statement_list statement  {$$=makeNodeList(N_STMT_LIST, $1, $2);}
    ;

statement
    : labeled_statement    {$$=$1;}  
    | compound_statement   {$$=$1;}
    | expression_statement {$$=$1;}
    | selection_statement  {$$=$1;}
    | iteration_statement  {$$=$1;}
    | jump_statement       {$$=$1;}
    ;

// 레이블된 명령문
labeled_statement
    : CASE_SYM constant_expression COLON statement {$$=makeNode(N_STMT_LABEL_CASE, $2, NIL, $4);}
    | DEFAULT_SYM COLON statement {$$=makeNode(N_STMT_LABEL_DEFAULT, NIL, $3, NIL);}
    ;

// 복합문
compound_statement
    : LR{$$=current_id; current_level++;} declaration_list_opt
      statement_list_opt RR{checkForwardReference(); 
      $$=makeNode(N_STMT_COMPOUND, $3, NIL, $4); current_id=$2; current_level--;} 
    ;
	// 나중에 완전히 선언되는가를 검사
	// 함수 선언문의 몸체나 복합문의 레벨값 처리 
	//  current_id를 몸체나 복합문의 분석 전 저장했던 값으로 변경 


// 수식문
expression_statement
    : SEMICOLON		   {$$=makeNode(N_STMT_EMPTY, NIL,NIL,NIL);}
    | expression SEMICOLON {$$=makeNode(N_STMT_EXPRESSION, NIL, $1, NIL);}
    ;


// 선택문
selection_statement
    : IF_SYM LP expression RP statement			   {$$=makeNode(N_STMT_IF, $3, NIL, $5);}
    | IF_SYM LP expression RP statement ELSE_SYM statement {$$=makeNode(N_STMT_IF_ELSE, $3, $5, $7);}
    | SWITCH_SYM LP expression RP statement		   {$$=makeNode(N_STMT_SWITCH, $3, NIL, $5);}
    ;


// 반복문
iteration_statement
    : WHILE_SYM LP expression RP statement		    {$$=makeNode(N_STMT_WHILE, $3, NIL, $5);}
    | DO_SYM statement WHILE_SYM LP expression RP SEMICOLON {$$=makeNode(N_STMT_DO, $2, NIL, $5);}
    | FOR_SYM LP for_expression RP statement		    {$$=makeNode(N_STMT_FOR, $3, NIL, $5);}
    ;

for_expression
    : expression_opt SEMICOLON expression_opt SEMICOLON expression_opt 
      {$$=makeNode(N_FOR_EXP, $1, $3, $5);}
    ;

expression_opt
    : /*empty*/  {$$=NIL;}
    | expression {$$=$1;}
    ;

// 분기문
jump_statement
    : RETURN_SYM expression_opt SEMICOLON {$$=makeNode(N_STMT_RETURN, NIL,$2,NIL);}
    | CONTINUE_SYM SEMICOLON		  {$$=makeNode(N_STMT_CONTINUE, NIL,NIL,NIL);}
    | BREAK_SYM SEMICOLON		  {$$=makeNode(N_STMT_BREAK, NIL,NIL,NIL);}
    ;


// 매개변수 리스트
arg_expression_list_opt
    : /*empty*/		  {$$=makeNode(N_ARG_LIST_NIL, NIL,NIL,NIL);}
    | arg_expression_list {$$=$1;}
    ;

arg_expression_list
    : assignment_expression {$$=makeNode(N_ARG_LIST, $1, NIL, makeNode(N_ARG_LIST_NIL, NIL,NIL,NIL));}
    | arg_expression_list COMMA assignment_expression {$$=makeNodeList(N_ARG_LIST, $1, $3);}
    ;


// 상수 수식
constant_expression_opt
    : /*empty*/           {$$=NIL;}
    | constant_expression {$$=$1;}
    ;

constant_expression
    : expression {$$=$1;}
    ;

// 일반 수식
expression 
    : comma_expression {$$=$1;}
    ;

comma_expression
    : assignment_expression {$$=$1;}
    ;

assignment_expression
    : conditional_expression {$$=$1;}
    | unary_expression ASSIGN assignment_expression {$$=makeNode(N_EXP_ASSIGN, $1, NIL, $3);}
    ;

conditional_expression
    : logical_or_expression {$$=$1;}
    ;

// 논리 수식
logical_or_expression
    : logical_and_expression {$$=$1;}
    | logical_or_expression BARBAR logical_and_expression {$$=makeNode(N_EXP_OR, $1, NIL, $3);}
    ;

logical_and_expression
    : equality_expression {$$=$1;}
    | logical_and_expression AMPAMP equality_expression {$$=makeNode(N_EXP_AND, $1, NIL, $3);}
    ;

equality_expression
    : relational_expression {$$=$1;}
    | equality_expression EQL relational_expression {$$=makeNode(N_EXP_EQL, $1, NIL, $3);}
    | equality_expression NEQ relational_expression {$$=makeNode(N_EXP_NEQ, $1, NIL, $3);}
    ;

// 관계 수식
relational_expression
    : shift_expression {$$=$1;}
    | relational_expression LSS shift_expression {$$=makeNode(N_EXP_LSS, $1, NIL, $3);}
    | relational_expression GTR shift_expression {$$=makeNode(N_EXP_GTR, $1, NIL, $3);}
    | relational_expression LEQ shift_expression {$$=makeNode(N_EXP_LEQ, $1, NIL, $3);}
    | relational_expression GEQ shift_expression {$$=makeNode(N_EXP_GEQ, $1, NIL, $3);}
    ;

shift_expression
    : additive_expression {$$=$1;}
    ;

// 이항 연산 수식
// 산술 수식
additive_expression
    : multiplicative_expression {$$=$1;}
    | additive_expression PLUS multiplicative_expression  {$$=makeNode(N_EXP_ADD, $1, NIL, $3);}
    | additive_expression MINUS multiplicative_expression {$$=makeNode(N_EXP_SUB, $1, NIL, $3);}
    ;

multiplicative_expression
    : cast_expression {$$=$1;}
    | multiplicative_expression STAR cast_expression    {$$=makeNode(N_EXP_MUL, $1, NIL, $3);}
    | multiplicative_expression SLASH cast_expression   {$$=makeNode(N_EXP_DIV, $1, NIL, $3);}
    | multiplicative_expression PERCENT cast_expression {$$=makeNode(N_EXP_MOD, $1, NIL, $3);}
    ;

// 타입 변환 수식
cast_expression
    : unary_expression	{$$=$1;}
    | LP type_name RP cast_expression {$$=makeNode(N_EXP_CAST, $2, NIL, $4);}
    ;


// 단항 수식
unary_expression
    : postfix_expression	  {$$=$1;}
    | PLUSPLUS unary_expression	  {$$=makeNode(N_EXP_PRE_INC, NIL, $2, NIL);}
    | MINUSMINUS unary_expression {$$=makeNode(N_EXP_PRE_DEC, NIL, $2, NIL);}
    | AMP cast_expression	  {$$=makeNode(N_EXP_AMP, NIL, $2, NIL);}
    | STAR cast_expression	  {$$=makeNode(N_EXP_STAR, NIL, $2, NIL);}
    | EXCL cast_expression	  {$$=makeNode(N_EXP_NOT, NIL, $2, NIL);}
    | MINUS cast_expression	  {$$=makeNode(N_EXP_MINUS, NIL, $2, NIL);}
    | PLUS cast_expression	  {$$=makeNode(N_EXP_PLUS, NIL, $2, NIL);}
    | SIZEOF_SYM unary_expression {$$=makeNode(N_EXP_SIZE_EXP, NIL, $2, NIL);}
    | SIZEOF_SYM LP type_name RP  {$$=makeNode(N_EXP_SIZE_TYPE, NIL, $3, NIL);}
    ;


// 후위 수식
postfix_expression
    : primary_expression		   {$$=$1;}
    | postfix_expression LB expression RB  {$$=makeNode(N_EXP_ARRAY, $1, NIL, $3);}
    | postfix_expression LP arg_expression_list_opt RP {$$=makeNode(N_EXP_FUNCTION_CALL, $1, NIL, $3);}
    | postfix_expression PERIOD IDENTIFIER {$$=makeNode(N_EXP_STRUCT, $1, NIL, $3);}
    | postfix_expression ARROW IDENTIFIER  {$$=makeNode(N_EXP_ARROW, $1, NIL, $3);}
    | postfix_expression PLUSPLUS	   {$$=makeNode(N_EXP_POST_INC, NIL, $1, NIL);}
    | postfix_expression MINUSMINUS	   {$$=makeNode(N_EXP_POST_DEC, NIL, $1, NIL);}
    ;


// 기본 수식
primary_expression
    : IDENTIFIER	  {$$=makeNode(N_EXP_IDENT, NIL, getIdentifierDeclared($1),NIL);}
    | INTEGER_CONSTANT	  {$$=makeNode(N_EXP_INT_CONST, NIL, $1, NIL);}
    | FLOAT_CONSTANT	  {$$=makeNode(N_EXP_FLOAT_CONST, NIL, $1, NIL);}
    | CHARACTER_CONSTANT  {$$=makeNode(N_EXP_CHAR_CONST, NIL, $1, NIL);}
    | STRING_LITERAL	  {$$=makeNode(N_EXP_STRING_LITERAL, NIL, $1, NIL);}
    | LP expression RP	  {$$=$2;}
    ;


type_name
    : declaration_specifiers abstract_declarator_opt {$$=setTypeNameSpecifier($2,$1);}
    ;


%%

extern char *yytext;

void yyerror(const char *s) {
    syntax_err ++;
    printf("line %d : %s near %s\n",line_no, s, yytext);
}

// 메인 함수
int main() {
    
	initialize();

	yyparse();

	// 신택스 분석
	if(syntax_err) exit(1);

	print_ast(root);

	// 시멘틱 분석
	semantic_analysis(root);

	if(semantic_err) exit(1);

	print_sem_ast(root);

	exit(0);
}
