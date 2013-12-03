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
[0-9]+			SAVE_TOKEN; return INTEGER;
","			return ',';

"mov"			return TOKEN(MOV);
"add"			return TOKEN(ADD);
"sub"			return TOKEN(SUB);
"mul"			return TOKEN(MUL);
"div"			return TOKEN(DIV);
"addi"			return TOKEN(ADDI);
"lw"			return TOKEN(LW);
"sw"			return TOKEN(SW);
"nand"			return TOKEN(NAND);
"beq"			return TOKEN(BEQ);
"bneq"			return TOKEN(BNEQ);
"bless"			return TOKEN(BLESS);
"bgrt"			return TOKEN(BGRT);
"syscall"		return TOKEN(SYSCALL);
"ret"			return TOKEN(RET);
"jmp"			return TOKEN(JMP);

"zero"			SAVE_TOKEN; return REG;
"a0"			SAVE_TOKEN; return REG;
"a1"			SAVE_TOKEN; return REG;
"a2"			SAVE_TOKEN; return REG;
"a3"			SAVE_TOKEN; return REG;
"t0"			SAVE_TOKEN; return REG;
"t1"			SAVE_TOKEN; return REG;
"t2"			SAVE_TOKEN; return REG;
"t3"			SAVE_TOKEN; return REG;
"t4"			SAVE_TOKEN; return REG;
"t5"			SAVE_TOKEN; return REG;
"t6"			SAVE_TOKEN; return REG;
"t7"			SAVE_TOKEN; return REG;
"t8"			SAVE_TOKEN; return REG;
"t9"			SAVE_TOKEN; return REG;
"s0"			SAVE_TOKEN; return REG;
"s1"			SAVE_TOKEN; return REG;
"s2"			SAVE_TOKEN; return REG;
"s3"			SAVE_TOKEN; return REG;
"s4"			SAVE_TOKEN; return REG;
"s5"			SAVE_TOKEN; return REG;
"s6"			SAVE_TOKEN; return REG;
"s7"			SAVE_TOKEN; return REG;
"v0"			SAVE_TOKEN; return REG;
"v1"			SAVE_TOKEN; return REG;
"sp"			SAVE_TOKEN; return REG;
"gp"			SAVE_TOKEN; return REG;
"bp"			SAVE_TOKEN; return REG;
"ra"			SAVE_TOKEN; return REG;
"r0"			SAVE_TOKEN; return REG;
"r1"			SAVE_TOKEN; return REG;
"one"			SAVE_TOKEN; return REG;

.                       printf("Unknown token!\n"); yyterminate();

%%
