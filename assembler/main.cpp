#include <iostream>
#include "node.h"
#include <typeinfo>
#include <cstdio>
#include <cstdlib>
#include <fstream>

extern int yyparse();
extern FILE *yyin;
extern Block *pgrm_block;
extern std::map<std::string,std::string> regs;

int main(int argc, char * argv[])
{

	FILE *fp = fopen("bcpu.asm", "r");
	yyin = fp;
	yyparse();
	fclose(fp);

	std::ofstream bcpu;
	bcpu.open("bcpu.o", std::ios::out);

	for(std::vector<Statement*>::iterator it = pgrm_block->statements.begin(); it!=pgrm_block->statements.end(); ++it){
		(*it)->code_gen(bcpu);
	}

	bcpu.close();

	return 0;
}
