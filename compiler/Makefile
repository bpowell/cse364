CXX = clang++
compiler=compiler

all: tokens.cpp parser.cpp $(compiler)

tokens.cpp:
	lex -o tokens.cpp tokens.l

parser.cpp:
	bison -d -o parser.cpp parser.y --verbose

$(compiler):
	$(CXX) parser.cpp tokens.cpp main.cpp -o $(compiler)

clean:
	rm tokens.cpp parser.cpp parser.hpp parser.output $(compiler)
