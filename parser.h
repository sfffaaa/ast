#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.h"
#include "lexer.h"

class AST {
	public:
		virtual Token getToken() = 0;
		virtual int visit() = 0;
};

class BinaryOP : public AST {
	public:
		AST* left;
		AST* right;
		Token token;
		Token op;

	Token getToken() { return token; };
	int visit();

	virtual ~BinaryOP() {}
};

class Num : public AST {
	public:
		Token token;

	Token getToken() { return token; };
	int visit() { return stoi(token.value); };
	virtual ~Num() {};
};

class Parser {
	public:
		Lexer lexer;
		Token currentToken;

		void eat(const std::string& tokenType);
		AST* factor();
		AST* term();
		AST* expr();
		AST* parse() { return this->expr(); };
};

#endif
