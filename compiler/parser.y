%{
	#include "node.h"
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <iostream>

	extern int yylex();
	void yyerror(const char *s) { printf("ERROR: %s\n", s); exit(1); }

	Block *pgrm_block;
%}

%union {
	std::string *string;
	Block *block;
	Statement *stmt;
	Expression *expr;
	Identifier *ident;
	int token;
}

%token <string> IDENT INTEGER
%token <token> INT VOID
%token <token> PLUS MINUS MUL DIV
%token <token> IF EQUALEQUAL

%type <block> program stmts block
%type <stmt> stmt def_var def_func call_func if_stmt
%type <ident> ident
%type <expr> expr numeric

%left PLUS MINUS
%left MUL DIV

%start program

%%

program : stmts { pgrm_block = $1; }
	;

stmts : stmt		{ $$ = new Block(); $$->statements.push_back($<stmt>1); }
      | stmts stmt	{ $1->statements.push_back($<stmt>2); }
      ;

stmt : def_var
     | def_func
     | call_func
     | if_stmt
     ;

if_stmt : IF '(' expr EQUALEQUAL expr ')' block { $$ = new IfStatement($3, $4, $5, $7); }
	;

def_var : INT ident ';' { $$ = new Variable($2); }
	| INT ident '=' expr ';' { $$ = new Variable($2, $4); }
	;

block : '{' stmts '}' { $$ = $2; }
      ;

def_func : VOID ident '(' ')' block { $$ = new Function($2, $5); }
	 ;

ident : IDENT { $$ = new Identifier(*$1); }
      ;

numeric : INTEGER { $$ = new Integer(atol($1->c_str())); }
	;

call_func : ident '(' ')' ';' { $$ = new FunctionCall($1); }
	  ;

expr : numeric 
     | ident { $<ident>$ = $1; }
     | expr PLUS expr { $$ = new Math(*$1, '+', *$3); }
     | expr MINUS expr { $$ = new Math(*$1, '-', *$3); }
     | expr MUL expr { $$ = new Math(*$1, '*', *$3); }
     | expr DIV expr { $$ = new Math(*$1, '/', *$3); }
     | '(' expr ')' { $$ = $2; }
     ;

%%
