#include <iostream>
#include "node.h"
#include <typeinfo>
#include <cstdio>
#include <cstdlib>
#include <fstream>

extern int yyparse();
extern FILE *yyin;
extern Block *pgrm_block;

int main(int argc, char * argv[])
{
	stack_pointer = 0;
	if(argc<2){
		std::cout << "need file name\n";
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");
	yyin = fp;
	yyparse();
	fclose(fp);

	std::ofstream bcpu;
	std::ofstream x86_64;
	bcpu.open("bcpu.asm", std::ios::out);
	x86_64.open("x86_64.asm", std::ios::out);

	x86_64 << "global _start\nSECTION .text\n\n_start:\n";

	for(std::vector<Statement*>::iterator it = pgrm_block->statements.begin(); it!=pgrm_block->statements.end(); ++it){
		std::cout << "Type " << typeid(**it).name() << std::endl;
		(*it)->code_gen(bcpu, x86_64);
		std::cout << std::endl;
	}

	bcpu.close();
	x86_64.close();

	return 0;
}
