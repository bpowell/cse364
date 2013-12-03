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
	int token;
	Register *reg;
	Integer *numeric;
}

%token <string> REG INTEGER
%token <token> MOV ADD SUB MUL DIV 
%token <token> ADDI LW SW NAND BEQ 
%token <token> BNEQ BLESS BGRT 
%token <token> SYSCALL RET JMP

%type <block> program stmts block
%type <stmt> stmt mov_op add_op sub_op mul_op div_op addi_op
%type <stmt> lw_op sw_op nand_op beq_op bneq_op bless_op bgrt_op
%type <stmt> syscall_op ret_op jmp_op
%type <numeric> numeric
%type <reg> reg

%left PLUS MINUS
%left MUL DIV

%start program

%%

program : stmts { pgrm_block = $1; }
	;

block : stmts { $$ = $1; }
      ;

stmts : stmt		{ $$ = new Block(); $$->statements.push_back($<stmt>1); }
      | stmts stmt	{ $1->statements.push_back($<stmt>2); }
      ;

stmt : mov_op
     | add_op | sub_op | mul_op | div_op | addi_op
     | lw_op | sw_op | nand_op 
     | beq_op | bneq_op | bless_op | bgrt_op
     | syscall_op | ret_op | jmp_op
     ;

reg : REG { $$ = new Register($1->c_str()); }
    ;

numeric : INTEGER { $$ = new Integer(atol($1->c_str())); }
	;

mov_op : MOV reg ',' reg { $$ = new MovOp($2, $4); }
       ;

add_op : ADD reg ',' reg { $$ = new AddOp($2, $4); }
       ;

mul_op : MUL reg ',' reg { $$ = new MulOp($2, $4); }
       ;

div_op : DIV reg ',' reg { $$ = new DivOp($2, $4); }
       ;

sub_op : SUB reg ',' reg { $$ = new SubOp($2, $4); }
       ;

addi_op : ADDI reg ',' numeric { $$ = new AddiOp($2, $4); }
	;

lw_op : LW reg ',' numeric { $$ = new LwOp($2, $4); }
      ;

sw_op : SW numeric ',' reg { $$ = new SwOp($2, $4); }
      ;


nand_op : NAND reg ',' reg { $$ = new NandOp($2, $4); }
	;

beq_op : BEQ reg { $$ = new BeqOp($2); }
       ;

bneq_op : BNEQ reg { $$ = new BneqOp($2); }
       ;

bless_op : BLESS reg { $$ = new BlessOp($2); }
       ;

bgrt_op : BGRT reg { $$ = new BgrtOp($2); }
       ;

syscall_op : SYSCALL { $$ = new SyscallOp(); }
	   ;

ret_op : RET { $$ = new RetOp(); }
       ;

jmp_op : JMP { $$ = new JmpOp(); }
       ;
%%
