#include "token.h"
#include "parser.h"

void Parser::eat(const std::string& tokenType) {
	if (this->currentToken.type == tokenType) {
		this->currentToken = this->lexer.getNextToken();
	} else {
		throw std::exception();
	}
}

AST* Parser::factor() {
	Token t = this->currentToken;
	if (t.type == INTEGER_TYPE) {
		this->eat(INTEGER_TYPE);
		return new Num(t);
	} else if (t.type == LPAREN_TYPE) {
		this->eat(LPAREN_TYPE);
		AST* node = this->expr();
		this->eat(RPAREN_TYPE);
		return node;
	} else {
		throw std::exception();
	}
}

AST* Parser::term() {
	AST* node = this->factor();
	while (this->currentToken.type == MULTIPLE_TYPE || this->currentToken.type == DIVIDE_TYPE) {
		Token t = this->currentToken;
		if (t.type == MULTIPLE_TYPE) {
			this->eat(MULTIPLE_TYPE);
		} else if (t.type == DIVIDE_TYPE) {
			this->eat(DIVIDE_TYPE);
		}
		AST* root = new BinaryOP(node, t, this->term());
		return root;
	}
	return node;
}

AST* Parser::expr() {
	AST* node = this->term();
	while (this->currentToken.type == PLUS_TYPE || this->currentToken.type == MINUS_TYPE) {
		Token t = this->currentToken;
		if (t.type == PLUS_TYPE) {
			this->eat(PLUS_TYPE);
		} else if (t.type == MINUS_TYPE) {
			this->eat(MINUS_TYPE);
		}
		AST* root = new BinaryOP(node, t, this->expr());
		return root;
	}
	return node;
}

AST* Parser::parse() {
	this->currentToken = this->lexer.getNextToken();
	return this->expr();
}

int BinaryOP::visit() {
	if (this->token.type == PLUS_TYPE) {
		return left->visit() + right->visit();
	} else if (this->token.type == MINUS_TYPE) {
		return left->visit() - right->visit();
	} else if (this->token.type == MULTIPLE_TYPE) {
		return left->visit() * right->visit();
	} else if (this->token.type == DIVIDE_TYPE) {
		return left->visit() / right->visit();
	} else {
		throw std::exception();
	}
}

void BinaryOP::cleanSubtree() {
	if (this->left) {
		this->left->cleanSubtree();
		delete this->left;
		this->left = nullptr;
	}
	if (this->right) {
		right->cleanSubtree();
		delete this->right;
		this->right = nullptr;
	}
}
