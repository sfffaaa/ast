#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.h"

class Interpreter {
	public:
		Parser parser;
		int visit();
		int interpret();

	private:
		int visit_imp(AST* node) {
			return node->visit();
		};
};

#endif
