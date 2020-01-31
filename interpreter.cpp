#include "interpreter.h"

int Interpreter::interpret() {
	AST* root = this->parser.parse();

	int ret = this->visit(root);
	root->cleanSubtree();
	delete root;

	return ret;
}
