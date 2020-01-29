#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.h"

class Lexer {
	public:
		std::string text;
		size_t pos;
		char currentChar;

		void advance();
		void skipWhitespace();
		int integer();
		Token getNextToken();
};

#endif
