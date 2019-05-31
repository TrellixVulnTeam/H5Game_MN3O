%{
	#include <stdio.h>
	#include "pwdist.tab.h"

	void yyerror(char*);
	void comment();
	extern int mylinenum;
%}


%%

"//" {
	comment();
}
"namespace" {
	return K_NAMESPACE;
}

"method" {
	return K_METHOD;
}

"object" {
	return K_OBJECT;
}

"int32" {
	return K_TYPE_I32;
}

"int64" {
	return K_TYPE_I64;
}

"const char*" {
	return K_TYPE_STR;
}

"double" {
	return K_TYPE_DEC;
}

"pwdist::Chunk" {
	return K_TYPE_BUF;
}

"const std::string&" {
	return K_TYPE_STDSTR;
}

"bool" {
	return K_TYPE_BOOL;
}

"char" {
	return K_TYPE_CHAR;
}

"short" {
	return K_TYPE_SHORT;
}

"optional" {
	return K_OPTIONAL;
}

[""""][a-zA-Z_\/\\0-9\.\{\}]+[""""] {
	yylval.tok = strdup(yytext);
//	printf("tok_string =%s\n",yylval.tok);
	return TOK_STRING;
}

[a-zA-Z_][a-zA-Z_0-9]* {
	yylval.tok = strdup(yytext);
	return TOK;
}



[\=\[\]\(\)\{\},\:] {
	return *yytext;
}

[\t\ \r] {
	// printf("got \\t\n");
}

[\n] {
	mylinenum ++;
}

%%

int mylinenum = 1;

void yyerror(char* s){
	fprintf(stderr,"lineno = %d, %s\n",mylinenum,s);
}

/*
int readinttype()
{
	int c = 0;
	int n = 0;
	char buf[1000] = "";
	
	while(c = input())
	{
		if(c == -1)
			break;
		if(c == ' ')
			break;
		buf[n++] = c;
	}
	buf[n] = '\0';

	printf("buf = %s\n",buf);

	if(strcmp(buf,"32"))
	{
		return K_TYPE_I32;
	}
	if(strcmp(buf,"64"))
		return K_TYPE_I64;
	yyerror("error int type,expect int32 or int64");
	return -1;
}
*/

void comment() {
	int c = 0;
	mylinenum ++;
	while(c = input()) 
	{
		if(c == -1)
			break;
		if(c == '\n')
			break ;\
	}
}
