%{
	#include <stdio.h>
	#include "pwdist_lexer.h"

	extern void yyerror(const char*);
	extern int input();

	char* gp_last_attr_value = 0;
	char  gb_return_params = 0;
%}


%union {
	char* tok;
}
%token <tok> TOK
%token <tok> TOK_STRING
%token K_NAMESPACE
%token K_METHOD
%token K_OBJECT
%token K_OPTIONAL

%token K_TYPE_I32
%token K_TYPE_I64
%token K_TYPE_STR
%token K_TYPE_DEC
%token K_TYPE_BUF

%token K_TYPE_BOOL
%token K_TYPE_CHAR
%token K_TYPE_SHORT
%token K_TYPE_STDSTR


%destructor { free ($$); } TOK TOK_STRING

%%

input:
	| input line
;

line: 	expr
;

expr:
	namespaceexpr
;

attrsexp: 
	'[' TOK '=' attrvalue ']' { on_attr($<tok>2,gp_last_attr_value);}
	| attrsexp '[' TOK '=' attrvalue ']' { on_attr($<tok>3,gp_last_attr_value);}
;
attrvalue:
	TOK	{ gp_last_attr_value = $<tok>1; }
	| TOK_STRING { gp_last_attr_value = $<tok>1; }
;

namespaceexpr_began:
	attrsexp K_NAMESPACE TOK '{' { on_namespace_began($<tok>3); }
	| K_NAMESPACE TOK '{' { on_namespace_began($<tok>2); }
;

namespaceexpr_ended:
	objectexpr '}' { on_namespace_ended();  }
;

namespaceexpr: 
	namespaceexpr_began namespaceexpr_ended
;

objectsexpr_began:
	attrsexp K_OBJECT TOK '{' { on_object_began($<tok>3,""); }
	| attrsexp K_OBJECT TOK ':' TOK '{' { on_object_began($<tok>3,$<tok>5); }
	| K_OBJECT TOK '{' { on_object_began($<tok>2,"");}
	| K_OBJECT TOK ':' TOK '{' { on_object_began($<tok>2,$<tok>4);}
;

objectsexpr_ended:
	methodsexpr '}' { on_object_ended(); }
;

objectexpr:
	objectsexpr_began objectsexpr_ended
	| objectexpr objectsexpr_began objectsexpr_ended
;

methodsexpr:
	methodexpr
	| methodsexpr methodexpr
;

methodexpr_began:
	K_METHOD TOK { on_method_began($<tok>2); }
;

methodexpr_ended:
	'(' { gb_return_params = 0; }
	paramsexpr 
	')' 
	'(' { gb_return_params = 1; }
	returnexpr
	')'
	{ on_method_ended(); }
;

methodexpr: 
	methodexpr_began methodexpr_ended
;

paramsexpr:
	| paramexpr
	| paramsexpr ',' paramexpr
;

returnexpr:
	| paramexpr
	| returnexpr ',' paramexpr
;

paramexpr:
	K_TYPE_I32 TOK { on_method_param(K_TYPE_I32,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_I32 TOK { on_method_param(K_TYPE_I32,$<tok>3,gb_return_params,1); }

	| K_TYPE_I64 TOK { on_method_param(K_TYPE_I64,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_I64 TOK { on_method_param(K_TYPE_I64,$<tok>3,gb_return_params,1); }

	| K_TYPE_DEC TOK { on_method_param(K_TYPE_DEC,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_DEC TOK { on_method_param(K_TYPE_DEC,$<tok>3,gb_return_params,1); }

	| K_TYPE_STR TOK { on_method_param(K_TYPE_STR,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_STR TOK { on_method_param(K_TYPE_STR,$<tok>3,gb_return_params,1); }

	| K_TYPE_BUF TOK { on_method_param(K_TYPE_BUF,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_BUF TOK { on_method_param(K_TYPE_BUF,$<tok>3,gb_return_params,1); }

	| K_TYPE_BOOL TOK { on_method_param(K_TYPE_BOOL,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_BOOL TOK { on_method_param(K_TYPE_BOOL,$<tok>3,gb_return_params,1); }

	| K_TYPE_CHAR TOK { on_method_param(K_TYPE_CHAR,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_CHAR TOK { on_method_param(K_TYPE_CHAR,$<tok>3,gb_return_params,1); }

	| K_TYPE_SHORT TOK { on_method_param(K_TYPE_SHORT,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_SHORT TOK { on_method_param(K_TYPE_SHORT,$<tok>3,gb_return_params,1); }

	| K_TYPE_STDSTR TOK { on_method_param(K_TYPE_STDSTR,$<tok>2,gb_return_params,0); }
	| K_OPTIONAL K_TYPE_STDSTR TOK { on_method_param(K_TYPE_STDSTR,$<tok>3,gb_return_params,1); }
;


%%


int main(void)
{
	yyparse();
	generate();
	return 0;
}
