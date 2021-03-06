#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.h"
#include "lexer.h"

class AST {
	protected:
		Token token;

	public:
		AST(Token t) : token(t) {};

	public:
		Token getToken() { return token; };
		virtual int visit() = 0;
		virtual void cleanSubtree() = 0;

		virtual ~AST() {};
};

class BinaryOP : public AST {
	public:
		AST* left;
		AST* right;

	public:
		BinaryOP(AST* l, Token t, AST* r) : AST(t), left(l), right(r) {
			if (!l || !r) {
				throw std::exception();
			}
		};
		int visit();
		void cleanSubtree();
};

class Num : public AST {
	public:
		Num(Token t) : AST(t) {};

	int visit() {
		return stoi(token.value);
	};
	void cleanSubtree() {};
};

class Parser {
	private:
		Lexer lexer;
		Token currentToken;

	public:
		Parser(const std::string& s): lexer(Lexer(s)), currentToken(Token("EOP", "")) {};

	public:
		AST* parse();

	private:
		void eat(const std::string& tokenType);
		AST* factor();
		AST* term();
		AST* expr();
};

#endif
