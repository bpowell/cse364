#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <map>
#include <fstream>

class Node{
};

static int get_num(std::string value){

	int val = 0;
	for(int i=0, j=32768; i<value.size(); i++, j/=2){
		if(value[i]=='1')
			val += j;
	}

	return val;
}

static std::map<std::string,std::string> regs;

class Statement : public Node{
	public:
		virtual void code_gen(std::ofstream &bcpu){}
};

class Block{
	public:
		std::vector<Statement*> statements;
		Block(){
	regs.insert(std::pair<std::string,std::string>("zero", "00000"));
	regs.insert(std::pair<std::string,std::string>("a0",   "00001"));
	regs.insert(std::pair<std::string,std::string>("a1",   "00010"));
	regs.insert(std::pair<std::string,std::string>("a2",   "00011"));
	regs.insert(std::pair<std::string,std::string>("a3",   "00100"));
	regs.insert(std::pair<std::string,std::string>("t0",   "00101"));
	regs.insert(std::pair<std::string,std::string>("t1",   "00110"));
	regs.insert(std::pair<std::string,std::string>("t2",   "00111"));
	regs.insert(std::pair<std::string,std::string>("t3",   "01000"));
	regs.insert(std::pair<std::string,std::string>("t4",   "01001"));
	regs.insert(std::pair<std::string,std::string>("t5",   "01010"));
	regs.insert(std::pair<std::string,std::string>("t6",   "01011"));
	regs.insert(std::pair<std::string,std::string>("t7",   "01100"));
	regs.insert(std::pair<std::string,std::string>("t8",   "01101"));
	regs.insert(std::pair<std::string,std::string>("t9",   "01110"));
	regs.insert(std::pair<std::string,std::string>("s0",   "01111"));
	regs.insert(std::pair<std::string,std::string>("s1",   "10000"));
	regs.insert(std::pair<std::string,std::string>("s2",   "10001"));
	regs.insert(std::pair<std::string,std::string>("s3",   "10010"));
	regs.insert(std::pair<std::string,std::string>("s4",   "10011"));
	regs.insert(std::pair<std::string,std::string>("s5",   "10100"));
	regs.insert(std::pair<std::string,std::string>("s6",   "10101"));
	regs.insert(std::pair<std::string,std::string>("s7",   "10110"));
	regs.insert(std::pair<std::string,std::string>("v0",   "10111"));
	regs.insert(std::pair<std::string,std::string>("v1",   "11000"));
	regs.insert(std::pair<std::string,std::string>("sp",   "11001"));
	regs.insert(std::pair<std::string,std::string>("gp",   "11010"));
	regs.insert(std::pair<std::string,std::string>("bp",   "11011"));
	regs.insert(std::pair<std::string,std::string>("ra",   "11100"));
	regs.insert(std::pair<std::string,std::string>("r0",   "11101"));
	regs.insert(std::pair<std::string,std::string>("r1",   "11110"));
	regs.insert(std::pair<std::string,std::string>("one",  "11111"));
		}
		virtual void code_gen(std::ofstream &bcpu){
			std::vector<Statement*>::iterator it = statements.begin();
			for(; it!=statements.end(); ++it){
				(*it)->code_gen(bcpu);
			}
		}
};

class Integer{
	public:
		int value;
		Integer(int value) : value(value) {}
};

class Register{
	public:
		std::string name;
		Register(std::string name) : name(name) {}
};

class MovOp : public Statement{
	public:
		Register *dst;
		Register *src;
		MovOp(Register *dst, Register *src) : dst(dst), src(src) {
		}
		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0000";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			bcpu << std::hex << get_num(out);
		}
};

class AddOp : public Statement{
	public:
		Register *dst;
		Register *src;
		AddOp(Register *dst, Register *src) : dst(dst), src(src) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0011";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			bcpu << std::hex << get_num(out);
		}
};

class MulOp : public Statement{
	public:
		Register *dst;
		Register *src;
		MulOp(Register *dst, Register *src) : dst(dst), src(src) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0110";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			std::cout << out << std::endl;
			bcpu << std::hex << get_num(out);
		}
};

class DivOp : public Statement{
	public:
		Register *dst;
		Register *src;
		DivOp(Register *dst, Register *src) : dst(dst), src(src) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0111";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			std::cout << out << std::endl;
			bcpu << std::hex << get_num(out);
		}
};

class SubOp : public Statement{
	public:
		Register *dst;
		Register *src;
		SubOp(Register *dst, Register *src) : dst(dst), src(src) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0100";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			std::cout << out << std::endl;
			bcpu << std::hex << get_num(out);
		}
};

class AddiOp : public Statement{
	public:
		Register *dst;
		Integer *value;
		AddiOp(Register *dst, Integer *value) : dst(dst), value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0101";
		}
};

class NandOp : public Statement{
	public:
		Register *dst;
		Register *src;
		NandOp(Register *dst, Register *src) : dst(dst), src(src) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1000";
			out += regs.find(dst->name)->second;
			out += regs.find(src->name)->second;
			bcpu << std::hex << get_num(out);
		}
};

class LwOp: public Statement{
	public:
		Register *dst;
		Integer *value;
		LwOp(Register *dst, Integer *value) : dst(dst), value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0001";
		}
};

class SwOp: public Statement{
	public:
		Register *dst;
		Integer *value;
		SwOp(Integer *value, Register *dst) : value(value), dst(dst) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "0010";
		}
};

class BeqOp : public Statement{
	public:
		Register *value;
		BeqOp(Register *value) : value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1100";
		}
};

class BneqOp : public Statement{
	public:
		Register *value;
		BneqOp(Register *value) : value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1101";
		}
};

class BlessOp : public Statement{
	public:
		Register *value;
		BlessOp(Register *value) : value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1110";
		}
};

class BgrtOp : public Statement{
	public:
		Register *value;
		BgrtOp(Register *value) : value(value) {
		}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1111";
		}
};

class SyscallOp : public Statement{
	public:
		SyscallOp(){}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1001";
		}
};

class RetOp : public Statement{
	public:
		RetOp(){}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1011";
		}
};

class JmpOp : public Statement{
	public:
		JmpOp(){}

		virtual void code_gen(std::ofstream &bcpu){
			std::string out = "1010";
		}
};
		
#endif
