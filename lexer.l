digit   [0-9]
letter  [a-zA-Z_] 
delim   [ \t]
line	[\n]
ws	{delim}+

%{
#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;

#include "y.tab.h"
#include "type.h"
// extern int yylval;
extern int line_no;
extern A_ID *current_id;
char *makeString(char *);
int checkIdentifier(char *);

%}

%%
{ws}    { }
{line}  { line_no++; }

"//"[^\n]*			{ /*한 줄 주석*/ }
"/*"(.|\n)*?"*/"		{ /*여러 줄 주석*/ }

auto             { return(AUTO_SYM); }
break            { return(BREAK_SYM); }
case             { return(CASE_SYM); }
continue         { return(CONTINUE_SYM); }
default          { return(DEFAULT_SYM); }
do               { return(DO_SYM); }
else             { return(ELSE_SYM); }
enum             { return(ENUM_SYM); }
for              { return(FOR_SYM); }
if               { return(IF_SYM); }
return           { return(RETURN_SYM); }
sizeof           { return(SIZEOF_SYM); }
static           { return(STATIC_SYM); }
struct           { return(STRUCT_SYM); }
switch           { return(SWITCH_SYM); }
typedef          { return(TYPEDEF_SYM); }
union            { return(UNION_SYM); }
while            { return(WHILE_SYM); }

"\+\+"           { return(PLUSPLUS); }
"\-\-"           { return(MINUSMINUS); }
"\->"            { return(ARROW); }
"<"              { return(LSS); }
">"              { return(GTR); }
"<="             { return(LEQ); }
">="             { return(GEQ); }
"=="             { return(EQL); }
"!="             { return(NEQ); }
"&&"             { return(AMPAMP); }
"||"             { return(BARBAR); }
"\.\.\."         { return(DOTDOTDOT); }
"\("             { return(LP); }
"\)"             { return(RP); }
"\["             { return(LB); }
"\]"             { return(RB); }
"\{"             { return(LR); }
"\}"             { return(RR); }
"\:"             { return(COLON); }
"\."             { return(PERIOD); }
"\,"             { return(COMMA); }
"\!"             { return(EXCL); }
"\*"             { return(STAR); }
"\/"             { return(SLASH); }
"\%"             { return(PERCENT); }
"\&"             { return(AMP); }
"\;"             { return(SEMICOLON); }
"\+"             { return(PLUS); }
"\-"             { return(MINUS); }
"\="             { return(ASSIGN); }

{digit}+                    { yylval=atoi(yytext); return(INTEGER_CONSTANT);}		// 정수인 경우, yylval에 그 정수 값을 저장
{digit}+"."+{digit}+        { yylval=makeString(yytext); return(FLOAT_CONSTANT);}	// 실수인 경우, 그 스트링을 복사해 주소를 yylval에 저장
{letter}({letter}|{digit})* { return(checkIdentifier(yytext)); }			// yytext 값이 타입명칭인지 확인
\"([^\"\n]|\\["\n])*\"      { yylval=makeString(yytext); return(STRING_LITERAL);}	// 문자열인 경우, 그 문자열의 길이+1만큼에 대한 메모리를 할당하고 그 문자열을 복사해 주소를 yylval에 저장
\'([^\'\n]|\'\')\'          { yylval=*(yytext+1); return(CHARACTER_CONSTANT);}		// 문자 1개인 경우, 값+1에 대한 주소를 yylval에 저장
%%

// 전달받은 스트링 크기만큼 메모리를 할당하고, 그 스트링을 복사한 뒤 주소값을 반환하는 함수
char *makeString(char *s){
	char *t;
	t = malloc(strlen(s)+1);
	strcpy(t,s);
	return(t);
}


// 전달받은 스트링 명칭을 검사하여 타입 명칭인 경우 IDENTIFIER를 반환하는 함수 
int checkIdentifier(char *s){
	A_ID *id;
	char *t;
	id = current_id; // 현재 레벨에서 명칭을 검사하기 위함
	while(id){
		if(strcmp(id->name,s)==0) // 동일한 명칭을 발견한 경우
			break;
		id=id->prev;
	}

	if(id==0){ 
		yylval = makeString(s);  // 명칭의 스트링을 주소를 yylval에 저장
		return(IDENTIFIER); 
	}else if(id->kind == ID_TYPE){ 
		yylval = id->type;
		return(TYPE_IDENTIFIER);
	}else{
		yylval = id->name;
		return(IDENTIFIER);
	}
}


int yywrap() {
    return 1;
}
