#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "y.tab.h"

extern char *yytext;
A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_NODE *root;		// 루트노드 즉, 최상위 노드
A_ID *current_id = NIL; // 현재 가리키고 있는 심볼테이블 주소

int syntax_err= 0;	// 에러 횟수 저장을 위한 변수 초기화
int line_no = 1;	// 라인 번호 초기화
int current_level = 0;  // 스코프를 위한 레벨값에 대한 변수 초기화


//=========================== 함수 프로토타입 시작 =======================================

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);	// 새로운 노드를 만드는 함수
A_NODE *makeNodeList(NODE_NAME, A_NODE *, A_NODE *);		// 두 개 이상의 단일 노드를 연결하는 함수
A_ID *makeIdentifier(char *);					// 새로운 명칭 추가 함수
A_ID *makeDummyIdentifier();					// 명칭없이 타입만 선언되는 경우 호출됨
A_TYPE *makeType(T_KIND);
A_SPECIFIER *makeSpecifier(A_TYPE *, S_KIND); 			// 선언 지시자 생성하는 함수

A_ID *searchIdentifier(char *, A_ID *);
A_ID *searchIdentifierAtCurrentLevel(char *, A_ID *); // 현재 레벨에서 같은 명칭을 갖고 있는 심볼테이블을 반환하는 함수

A_SPECIFIER *updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND); // 명시자 테이블을 합치는 함수
void checkForwardReference();			// 전방참조에 대한 완전한 선언 여부 확인하는 함수
void setDefaultSpecifier(A_SPECIFIER *);	// 반환타입이나 storage class가 지정되지 않은 경우 기본값으로 설정하는 함수
A_ID *linkDeclaratorList(A_ID *, A_ID *);	// 인자로 받은 두 개의 심볼테이블 목록을 연결하는 함수
A_ID *getIdentifierDeclared(char *);		// 명칭의 사용 가능 여부 검사하는 함수
A_TYPE *getTypeOfStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

A_ID *setDeclaratorInit(A_ID *, A_NODE *);  	 // 심볼테이블에 신택스 트리 연결하는 함수
A_ID *setDeclaratorKind(A_ID *, ID_KIND );
A_ID *setDeclaratorType(A_ID *, A_TYPE *); 	 // 심볼테이블의 타입 정보 설정하는 함수
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

//=========================== 함수 프로토타입 끝===========================================



//=========================== 함수 구현부 시작 ============================================


// 새로운 노드 만드는 함수
A_NODE *makeNode(NODE_NAME n, A_NODE *a, A_NODE *b, A_NODE *c){
	A_NODE *m;
	m = (A_NODE*)malloc(sizeof(A_NODE));
	m->name = n;
	m->llink = a;
	m->clink = b;
	m->rlink = c;
	m->type = NIL;
	m->line = line_no;
	m->value = 0;
	return(m);
}

// 두 개 이상의 단일 노드를 연결하는 함수
A_NODE *makeNodeList(NODE_NAME name, A_NODE *a, A_NODE *b){
	A_NODE *k, *m; // k : 연결 목적 노드에 새로운 노드 연결을 위한 노드 , m : 새로운 노드 만들 때 오른쪽 자식노드로 연결하려는 단말노드
	k=a;
	while (k->rlink) k = k->rlink; // 가장 마지막 노드 선택
	// 가장 오른쪽 자식은 빈노드로 만들기로 약속 -> 새로운 빈 노드 생성
	m = (A_NODE*)malloc(sizeof(A_NODE));
	m->name = k->name;
	m->llink = NIL;
	m->clink = NIL;
	m->rlink = NIL;
	m->type = NIL;
	m->line = line_no;
	m->value = 0;
	// 연결을 위해 만들어진 노드의 이름 설정 & 새로운 노드 자식으로 연결
	k->name = name;
	k->llink = b; // 새로운 노드 왼쪽 자식으로 연결
	k->rlink = m; // 빈 노드 오른쪽 자식으로 연결
	return(a);
}


// 새로운 명칭 추가 처리 함수
A_ID *makeIdentifier(char *s){
    A_ID *id;
    id = malloc(sizeof(A_ID));
    id->name = s;
    id->kind = 0;
    id->specifier = 0;
    id->level = current_level;
    id->address = 0;
    id->init = NIL;
    id->type = NIL;
    id->link = NIL;
    id->line = line_no;
    id->value = 0;
    id->prev = current_id;
    current_id = id; // 새로운 명칭을 사용가능 한 명칭 목록의 맨 앞에 추가
    return id;
}


// 명칭을 갖지 않는 새로운 심볼테이블 하나 생성하고 그 주소 반환하는 함수. 명칭없이 타입만 선언되는 경우에만 호출됨
A_ID *makeDummyIdentifier(){
	A_ID *id;
	id = malloc(sizeof(A_ID));
	id->name = "";
	id->kind = 0;
	id->specifier = 0;
	id->level = current_level;
	id->address = 0;
	id->init = NIL;
	id->type = NIL;
	id->link = NIL;
	id->line = line_no;
	id->value = 0;
	id->prev = 0;
	return(id);
}


// 새로운 타입 테이블을 만드는 함수
A_TYPE *makeType(T_KIND k){
	A_TYPE *t;
	t = malloc(sizeof(A_TYPE));
	t->kind = k;
	t->size = 0;
	t->size = 0;
	t->local_var_size = 0;
	t->element_type = NIL;
	t->field = NIL;
	t->expr = NIL;
	t->check = FALSE;
	t->prt = FALSE;
	t->line = line_no;
	return(t);
}


 // 새로운 선언 지시자 생성하는 함수
A_SPECIFIER *makeSpecifier(A_TYPE *t, S_KIND s){
	A_SPECIFIER *p;
	p = malloc(sizeof(A_SPECIFIER));
	p->type = t;
	p->stor = s;
	p->line = line_no;
	return(p);
}


// 심볼테이블에서 주어진 명칭이 있는지 확인하는 함수
A_ID *searchIdentifier(char *s, A_ID *id){
	while(id){
		if(strcmp(id->name,s)==0) break;
		id = id->prev;
	}
	return(id);
}



// current_level의 범위에서 전달받은 명칭과 같은 함수 명칭을 갖는 심볼테이블 반환하는 함수
A_ID *searchIdentifierAtCurrentLevel(char *s, A_ID *id){
	while(id){
		if(id->level < current_level) return (NIL);
		if(strcmp(id->name, s) == 0) break;
		id=id->prev;
	}
	return(id);
}


// 전방참조에 대한 완전한 선언 존재 여부 검사하는 함수
void checkForwardReference() {
    A_ID *id ;
    A_TYPE *t;
    id = current_id;
    while (id) {
        if (id->level < current_level) break;
        t = id->type;
        if (id->kind == ID_NULL)
            syntax_error(31, id->name);
        else if ((id->kind == ID_STRUCT || id->kind == ID_ENUM) && t->field == NIL)
            syntax_error(32, id->name);
        id = id->prev;
    }
}


// 명시자 기본값 설정하는 함수
void setDefaultSpecifier(A_SPECIFIER *p){
	A_TYPE *t ;
	if(p->type == NIL) p->type = int_type;  // 반환 타입이 지정되지 않았다면, 정수형 타입으로 설정
	if(p->stor == S_NULL) p->stor = S_AUTO; // storage class가 없다면, auto로 설정
}


// 명시자 테이블을 합치는 함수
A_SPECIFIER *updateSpecifier(A_SPECIFIER *p, A_TYPE *t, S_KIND s){
	if(t)
		if(p->type)
			if(p->type!=t) syntax_error(24); // 올바른 타입 명시자가 아님 -> 에러
		else
			p->type = t;
	if(s){
		if(p->stor)
			if(s != p->stor) syntax_error(24); // 올바른 기억장소 명시자가 아님 -> 에러
		else
			p->stor = s;
	}
	return(p);
}


// 두 개의 심볼테이블 연결하는 함수
A_ID *linkDeclaratorList(A_ID *id1, A_ID *id2){
	A_ID *m = id1;
	if(id1 == NIL) return(id2); // 첫 번째로 받은 심볼테이블이 없는 경우, 연결할 필요 없으므로 두 번째 심볼테이블 반환
	while(m->link)
		m = m->link;
	m->link = id2;  // id1에 id2 연결
	return (id1);   // id1에 id2가 연결되었으므로 id1반환
}



// 명칭의 사용가능 여부 검사하는 함수
A_ID *getIdentifierDeclared(char *s){
	A_ID *id;
	id = searchIdentifier(s, current_id);
	if(id==NIL) syntax_error(13,s); // 명칭이 선언되지 않았기 때문에 에러
	return(id);
}


// 명칭의 사용가능 여부를 판단하고, 명칭의 종류가 구조체 혹은 나열형 명칭인지 검사.
// (명칭이 앞서 선언되지 않은 경우 뒷 부분에 선언될 수 있으므로, 새로운 명칭과 타입으로 사용할 수 있도록 등록)
A_TYPE *getTypeOfStructOrEnumIdentifier(T_KIND k, char *s, ID_KIND kk){
	A_TYPE *t;
	A_ID *id;
	id =searchIdentifier(s,current_id); // 중복 검사
	if(id)
		if(id->kind==kk && id->type->kind==k)
			return(id->type);
		else
			syntax_error(11,s); // 다른 종류, 타입인데 같은 명칭인 경우 에러

	// 앞에 중복되는 명칭 없으므로 새롭게 등록
	t = makeType(k); 	// 새로운 타입 테이블 생성
	id = makeIdentifier(s); // 명칭에 대한 명시자 생성
	id->kind = kk; 		// 심볼테이블 종류 설정
	id->type = t; 		// 심볼테이블이 타입테이블 주소갖도록 설정
	return (t); 		// 타입테이블 반환
}


// 심볼테이블에 신택스 트리 연결하는 함수
A_ID *setDeclaratorInit(A_ID *id, A_NODE *node){
	id->init = node;
	return(id);
}


// 현재 레벨에서 중복선언 검사 후, 주어진 심볼(첫번째 인자)의 종류를 주어진 종류(두번째 인자)로 설정하고 그 주소 리턴 
A_ID *setDeclaratorKind(A_ID *id, ID_KIND k){
	A_ID *a;
	a = searchIdentifierAtCurrentLevel(id->name, id->prev);
	if(a)
		syntax_error(12, id->name); // 중복 선언된 경우 에러
	id->kind = k; // 명칭의 종류 설정
	return(id); // 명칭 주소 반환
}


// 심볼테이블의 타입 정보 설정하는 함수
A_ID *setDeclaratorType(A_ID *id, A_TYPE *t){
	id->type = t;
	return (id);
}



// 선언문이나 element의 타입을 설정하는 함수
A_ID *setDeclaratorElementType(A_ID *id, A_TYPE *t){
	A_TYPE *tt;
	if(id->type==NIL) id->type = t;
	else{
		tt = id->type;
		while(tt->element_type)
			tt = tt->element_type;
		tt->element_type = t;
	}
	return(id);
}


// initialize() 함수에서만 사용하는 것으로 심볼테이블 타입과 종류 설정
A_ID *setDeclaratorTypeAndKind(A_ID *id, A_TYPE *t, ID_KIND k){
	id = setDeclaratorElementType(id, t);
	id = setDeclaratorKind(id, k);
	return (id);
}


// 함수 선언문을 위한 검사와 값 설정하는 함수
A_ID *setFunctionDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p){
	A_ID *a;
	// storage class 검사 - 이미 존재하면 에러
	if(p->stor)
		syntax_error(25);
	setDefaultSpecifier(p);
	// 함수 명칭이 파라미터 목록 바로 직전에 있는지 검사
	if(id->type->kind != T_FUNC){
		syntax_error(21);
		return(id);
	}else{
		id=setDeclaratorElementType(id, p->type);
		id->kind = ID_FUNC;
	}
	// 중복 선언 검사
	a = searchIdentifierAtCurrentLevel(id->name, id->prev);
	if(a)
	    if(a->kind != ID_FUNC || a->type->expr)
		syntax_error(12, id->name);
	    else{ // 프로토타입 검사 : 파라미터와 반환타입 검사
		if(isNotSameFormalParameters(a->type->field, id->type->field))
			syntax_error(22, id->name);
		if(isNotSameType(a->type->element_type, id->type->element_type))
			syntax_error(26,a->name);
	    }
	// 스코프 범위 변경 및 빈 필드 검사
	a = id->type->field;
	while(a){
		if(strlen(a->name))
			current_id = a;
		else if(a->type)
			syntax_error(23);
		a=a->link;
	}
	return(id);
}

// 함수 몸체에 신택스 트리 연결
A_ID *setFunctionDeclaratorBody(A_ID *id, A_NODE *n){
	id->type->expr = n;
	return(id);
}


//심볼테이블들을 검사하고, 명시자 테이블로부터 심볼테이블 속성을 결정하고 저장하는 함수
A_ID *setDeclaratorListSpecifier(A_ID *id, A_SPECIFIER *p){
	A_ID *a;
	setDefaultSpecifier(p); // 지정되지 않은 경우, 기본 타입으로 설정
	a = id;
	while(a){
	  // 심볼테이블 명칭 중복 선언 검사
	  if(strlen(a->name) && searchIdentifierAtCurrentLevel(a->name, a->prev))
		syntax_error(12,a->name);
	  // 선언문 혹은 함수나 배열인 경우 타입 설정
	  a = setDeclaratorElementType(a,p->type);
	  // 명칭의 종류 설정
	  if(p->stor == S_TYPEDEF)
	      a->kind = ID_TYPE;
	  else if(a->type->kind == T_FUNC)
	      a->kind = ID_FUNC;
	  else
	      a->kind = ID_VAR;

	  a->specifier = p->stor; // 명시자 설정

	  if(a->specifier == S_NULL)
	      a->specifier = S_AUTO;

	  a = a->link;
	}
	return (id);
}


// 심볼테이블의 타입 정보를 설정하고 명칭 종류를 ID_PARAM으로 설정하며 파라미터 검사
A_ID *setParameterDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p){
	// 중복 선언 검사
	if(searchIdentifierAtCurrentLevel(id->name, id->prev))
		syntax_error(12, id->name);

	// 파라미터에 storage class, void type이 사용되었는지 검사
	if(p->stor || p->type == void_type)
		syntax_error(14);

	setDefaultSpecifier(p);
	id = setDeclaratorElementType(id, p->type);
	id->kind = ID_PARM;
	return(id);
}


// 심볼테이블을 검사하고, 각 심볼의 종류를 ID_FIELD로 하고, 타입을 타입테이블 주소로 설정하는 함수
A_ID *setStructDeclaratorListSpecifier(A_ID *id, A_TYPE *t){
	A_ID *a;
	a=id;
	while(a){
		if(searchIdentifierAtCurrentLevel(a->name, a->prev))
			syntax_error(12, a->name);
		a = setDeclaratorElementType(a,t);
		a->kind = ID_FIELD; // 종류를 ID_FIELD로 변경
		a = a->link;
	}
	return (id); // 심볼 종류과 타입테이블 주소가 설정된 심볼테이블 반환
}


// 타입명시자의 기억 장소 명시자 포함 여부 검사 후, 주어진 타입의 엘리먼트 타입으로 타입명시자 지정
A_TYPE *setTypeNameSpecifier(A_TYPE *t, A_SPECIFIER *p){
	// 타입 명시자에 기억 장소 명시자(storage class)가 있는지 검사
	if(p->stor)
		syntax_error(20);
	setDefaultSpecifier(p);
	t = setTypeElementType(t, p->type);
	return(t);
}


// 첫 번째 인자로 주어진 타입 테이블의 엘리먼트 타입으로 두 번째 인자로 주어진 타입테이블을 연결하는 함수
A_TYPE *setTypeElementType(A_TYPE *t, A_TYPE *s){
	A_TYPE *q ;
	if(t==NIL)
		return(s);
	q = t;
	while(q->element_type) // 배열이나 포인터 등 복합구조의 타입인 경우 마지막 엘리먼트 타입으로 연결해야 함
		q = q->element_type; // 마지막 엘리먼트 타입 찾음
	q->element_type = s; // 연결
	return(t); // 연결된 타입테이블 반환
}


// 타입테이블의 필드 목록을 심볼테이블 목록으로 설정
A_TYPE *setTypeField(A_TYPE *t, A_ID *n){
	t->field = n;
	return(t); // 타입테이블 반환
}



// 타입테이블의 <expr> 필드에 신택스 트리 연결
A_TYPE *setTypeExpr(A_TYPE *t, A_NODE *n){
	t->expr = n;
	return (t);
}


// 구조체 혹은 enum 타입을 새로 선언하기 위해 명칭에 대한 심볼테이블을 생성하고 타입테이블을 생성하여 그 주소를 심볼테이블에 저장하는 함수
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND k, char *s, ID_KIND kk){
	A_TYPE *t;
	A_ID *id, *a;
	// 중복 선언 및 전방참조 검사
	a = searchIdentifierAtCurrentLevel(s,current_id);
	if(a)
		if(a->kind==kk && a->type->kind == k)
			if(a->type->field)
				syntax_error(12,s); // 중복 선언 에러
			else
				return(a->type);
		else
			syntax_error(12,s); // 중복 선언 에러
	// 새로운 구조체나 나열형 타입 생성
	id = makeIdentifier(s);
	t = makeType(k); // 타입 테이블 생성
	id->type=t;
	id->kind=kk;
	return (t);
}


//initialize() 함수에서만 사용하는 것으로 심볼테이블 타입과 종류 설정
A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *t, ID_KIND k, A_ID *id){
	if(searchIdentifierAtCurrentLevel(id->name, id->prev))
		syntax_error(12, id->name);
	id->type = t;
	id->kind = k;
	return(t);
}



// 프로토타입의 파라미터 일치 여부 확인하는 함수
BOOLEAN isNotSameFormalParameters(A_ID *a, A_ID *b){
	if(a == NIL)
		return (FALSE); // 프로토타입에 파라미터 없는 경우 false 반환
	while(a){
		if(b == NIL || isNotSameType(a->type, b->type))
			return (TRUE); // 다른 함수인 경우 비교할 필요 없으므로 true 반환
		a=a->link;
		b=b->link;
	}
	if(b)
		return (TRUE);
	else
		return (FALSE);
}



// 프로토타입의 반환 타입 일치 여부 확인하는 함수
BOOLEAN isNotSameType(A_TYPE *t1, A_TYPE *t2){
	if(isPointerOrArrayType(t1) || isPointerOrArrayType(t2))
		return (isNotSameType(t1->element_type, t2->element_type));
	else
		return(t1!=t2);
}


// 신택스 분석 시작 전 준비 과정 수행하는 함수
void initialize(){
	// 초기 데이터 타입 설정
	int_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("int"));
	float_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("float"));
	char_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("char"));
	void_type = setTypeAndKindOfDeclarator(makeType(T_VOID), ID_TYPE, makeIdentifier("void"));
	string_type = setTypeElementType(makeType(T_POINTER), char_type);

	int_type->size = 4;	int_type->check = TRUE;
	float_type->size = 4;	float_type->check = TRUE;
	char_type->size = 1;	char_type->check = TRUE;
	void_type->size = 0;	void_type->check = TRUE;
	string_type->size = 4;	string_type->check = TRUE;

	// printf(char *,...) 라이브러리 함수
	setDeclaratorTypeAndKind(
		makeIdentifier("printf"),
		setTypeField(
			setTypeElementType(makeType(T_FUNC), void_type),
			linkDeclaratorList(
				setDeclaratorTypeAndKind(makeDummyIdentifier(), string_type, ID_PARM),
				setDeclaratorKind(makeDummyIdentifier(), ID_PARM)
			)
		),
		ID_FUNC
	);


	// scanf(char *,...) 라이브러리 함수
	setDeclaratorTypeAndKind(
		makeIdentifier("scanf"),
		setTypeField(
			setTypeElementType(makeType(T_FUNC), void_type),
			linkDeclaratorList(
				setDeclaratorTypeAndKind(makeDummyIdentifier(), string_type, ID_PARM),
				setDeclaratorKind(makeDummyIdentifier(), ID_PARM)
			)
		),
		ID_FUNC
	);


	// malloc(int) 라이브러리 함수
	setDeclaratorTypeAndKind(
		makeIdentifier("malloc"),
		setTypeField(
			setTypeElementType(makeType(T_FUNC), string_type),
			setDeclaratorTypeAndKind(makeDummyIdentifier(), int_type, ID_PARM)
		),
		ID_FUNC
	);

}


// 신택스 에러 메시지 출력 함수
void syntax_error(int i, char *s){
	syntax_err++;
	printf("line %d : syntax error: ", line_no);
	switch(i){
		case 11 : printf("illegal referencing struct ot union identifier %s",s);
			  break;
		case 12 : printf("redeclaration of identifier %s",s);
			  break;
		case 13 : printf("undefined identifier %s",s);
			  break;
		case 14 : printf("illegal type specifier in formal parameter");
			  break;
		case 20 : printf("illegal storage class in type specifiers");
			  break;
		case 21 : printf("illegal function declarator");
			  break;
		case 22 : printf("conflicting parm type in prototype fnctionr %s",s);
			  break;
		case 23 : printf("empty parameter name");
			  break;
		case 24 : printf("illegal declaration specifiers");
			  break;
		case 25 : printf("illegal function specifiers");
			  break;
		case 26 : printf("illegal referencing struct ot union identifier %s",s);
			  break;
		case 31 : printf("undefined type for Identifier %s",s);
			  break;
		case 32 : printf("incomplete forward reference for identifier %s",s);
			  break;
		default : printf("unkown");
			  break;
	}

	if(strlen(yytext) == 0) printf(" at end \n");
	else printf(" near %s\n", yytext);
}
