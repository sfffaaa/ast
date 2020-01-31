#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.h"

class Lexer {
	private:
		std::string text;
		size_t pos;
		char currentChar;

	public:
		Lexer(const std::string& t) : text(t), pos(0), currentChar(t[0]) {};

	public:
		char getCurrentChar() {return currentChar; };
		void advance();
		void skipWhitespace();
		Token getNextToken();

	private:
		std::string integer();
};

#endif
