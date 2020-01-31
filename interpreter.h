#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.h"

class Interpreter {
	public:
		Parser parser;
		int interpret();

	public:
		Interpreter(const std::string& s) : parser(Parser(s)) {};

	private:
		int visit(AST* node) {
			return node->visit();
		};
};

#endif
