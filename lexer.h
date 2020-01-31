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
		Token getNextToken();

		// Should be private but now public for testing
		char getCurrentChar() {return currentChar; };
		void advance();
		void skipWhitespace();

	private:
		std::string integer();
};

#endif
