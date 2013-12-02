#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <map>
#include <fstream>

static int stack_pointer;

class Node{
};

class Expression : public Node{
	public:
		virtual void code_gen(std::ofstream &bcpu){}
		int rvalue;
		std::string name;
		Expression(int rvalue) : rvalue(rvalue) {}
		Expression(int rvalue, std::string name) : rvalue(rvalue), name(name) {}
};

static std::map<std::string,int> vars;

class Statement : public Node{
	public:
		virtual void code_gen(std::ofstream &bcpu){}
};

class Integer : public Expression{
	public:
		Integer(int rvalue) : Expression(rvalue) {}
		virtual void code_gen(std::ofstream &bcpu){
			bcpu << rvalue;
		}
};

class Identifier : public Expression{
	public:
		Identifier(std::string name) : Expression(0, name) {}
		virtual void code_gen(std::ofstream &bcpu){
		}
};

class Math : public Expression{
	public:
		char op;
		Expression &rhs;
		Expression &lhs;
		int rv, lv;
		Math(Expression &lhs, char op, Expression &rhs) : Expression(0), lhs(lhs), op(op), rhs(rhs) {}
		virtual void code_gen(std::ofstream &bcpu){
			int lv, rv;
			if(typeid(lhs)==typeid(Math)){
				lhs.code_gen(bcpu);
				lv = lhs.rvalue;
			}else if(typeid(lhs)==typeid(Identifier)){
				if(vars.count(lhs.name)>0){
					lv = vars.find(lhs.name)->second;
				}else{
					std::cerr << "Invalid identifier\n";
					std::cerr << lhs.name << std::endl;
					return;
				}
			}else if(typeid(lhs)==typeid(Integer)){
				lv = lhs.rvalue;
			}

			if(typeid(rhs)==typeid(Math)){
				rhs.code_gen(bcpu);
				rv = rhs.rvalue;
			}else if(typeid(rhs)==typeid(Identifier)){
				if(vars.count(rhs.name)>0){
					rv = vars.find(rhs.name)->second;
				}else{
					std::cerr << "Invalid identifier\n";
					std::cerr << rhs.name << std::endl;
					return;
				}
			}else if(typeid(rhs)==typeid(Integer)){
				rv = rhs.rvalue;
			}

			switch(op){
				case '+':
					rvalue = rv + lv;
					bcpu << rvalue;
					break;
				case '-':
					rvalue = rv - lv;
					bcpu << rvalue;
					break;
				case '*':
					rvalue = rv * lv;
					bcpu << rvalue;
					break;
				case '/':
					rvalue = rv / lv;
					bcpu << rvalue;
					break;
			}
			bcpu << std::endl;
		}
};

class Block : public Expression{
	public:
		std::vector<Statement*> statements;
		Block() : Expression(0) {}
		virtual void code_gen(std::ofstream &bcpu){
			std::vector<Statement*>::iterator it = statements.begin();
			for(; it!=statements.end(); ++it){
				(*it)->code_gen(bcpu);
			}
		}
};


class FunctionCall : public Statement{
	public:
		Identifier *id;
		FunctionCall(Identifier *id) : id(id) {}
		virtual void code_gen(std::ofstream &bcpu){
			bcpu << "jmp " << id->name << std::endl;
		}
};

class IfStatement : public Statement{
	public:
		Expression *lhs;
		Expression *rhs;
		Block *block;
		int op;
		IfStatement(Expression *lhs, int op, Expression *rhs, Block *block) : lhs(lhs), op(op), rhs(rhs), block(block) {}
		virtual void code_gen(std::ofstream &bcpu){
			lhs->code_gen(bcpu);
			bcpu << "==" << std::endl;
			rhs->code_gen(bcpu);
			block->code_gen(bcpu);
		}
};

class Function : public Statement{
	public:
		Identifier *id;
		Block *block;
		Function(Identifier *id, Block *block) : id(id), block(block) {}
		virtual void code_gen(std::ofstream &bcpu){
			bcpu << id->name << ":" << std::endl;
			block->code_gen(bcpu);
		}
};


class Variable : public Statement{
	public:
		Identifier *ident;
		Expression *expr;
		int sp;
		Variable(Identifier *ident) : ident(ident), expr(NULL) {
			stack_pointer++;
			sp = stack_pointer;
		}
		Variable(Identifier *ident, Expression *expr) : ident(ident), expr(expr) {
			stack_pointer++;
			sp = stack_pointer;
			vars.insert(std::pair<std::string,int>(ident->name, expr->rvalue));
		}
		virtual void code_gen(std::ofstream &bcpu){
			ident->code_gen(bcpu);
			if(expr!=NULL){
				bcpu << "lw bp+" << sp*4 << ", ";
				expr->code_gen(bcpu);
				bcpu << std::endl;
			}
		}
};


#endif
