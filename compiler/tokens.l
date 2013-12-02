%{
#include <string>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
#define YY_SKIP_YYWRAP
%}

%option noyywrap

%%

[ \n\t]			;
"int"			return TOKEN(INT);
"void"			return TOKEN(VOID);
"if"			return TOKEN(IF);
[a-zA-Z_][a-zA-Z0-9_]*	SAVE_TOKEN; return IDENT;
[0-9]+			SAVE_TOKEN; return INTEGER;
";"			return ';';
"="			return '=';
"+"			return TOKEN(PLUS);
"-"			return TOKEN(MINUS);
"*"			return TOKEN(MUL);
"/"			return TOKEN(DIV);
"("			return '(';
")"			return ')';
"{"			return '{';
"}"			return '}';
"=="			return TOKEN(EQUALEQUAL);
.                       printf("Unknown token!\n"); yyterminate();

%%
