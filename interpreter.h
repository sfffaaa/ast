#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.h"

class Interpreter {
	public:
		Parser parser;
		int interpret();

	public:
		Interpreter(Parser p) : parser(p) {};

	private:
		int visit(AST* node) {
			return node->visit();
		};
};

#endif
