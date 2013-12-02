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
	bcpu.open("bcpu.asm", std::ios::out);

	for(std::vector<Statement*>::iterator it = pgrm_block->statements.begin(); it!=pgrm_block->statements.end(); ++it){
		std::cout << "Type " << typeid(**it).name() << std::endl;
		(*it)->code_gen(bcpu);
		std::cout << std::endl;
	}

	bcpu.close();

	return 0;
}
