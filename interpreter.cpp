#include "interpreter.h"

int Interpreter::interpret() {
	AST* root = this->parser.parse();
	int ret = this->visit(root);
	//[TODO] Clean tree;
	return ret;
}
