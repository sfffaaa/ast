#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.h"

class Lexer {
	public:
		std::string text;
		size_t pos;
		char currentChar;

	public:
		Lexer(std::string t) : text(t), pos(0), currentChar(t[0]) {};

	public:
		void advance();
		void skipWhitespace();
		int integer();
		Token getNextToken();
};

#endif
