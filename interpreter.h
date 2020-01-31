#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.h"

class Interpreter {
	private:
		Parser parser;

	public:
		Interpreter(const std::string& s) : parser(Parser(s)) {};

	public:
		int interpret();

	private:
		int visit(AST* node) {
			return node->visit();
		};
};

#endif
