#include "lexer.h"
#include "token.h"

void Lexer::advance() {
	this->pos += 1;
	if (this->pos >= this->text.length()) {
		this->currentChar = '\0';
	} else {
		this->currentChar = this->text[this->pos];
	}
}

void Lexer::skipWhitespace() {
	while (this->currentChar != '\0' && isspace(this->currentChar)) {
		this->advance();
	}
}

std::string Lexer::integer() {
	std::string result("");
	while (this->currentChar != '\0' && isdigit(this->currentChar)) {
		result += this->currentChar;
		this->advance();
	}
	if (result.length() > 1) {
		throw std::exception();
	} else {
		return result;
	}
}

Token Lexer::getNextToken() {
	while (this->currentChar != '\0') {
		if (isspace(this->currentChar)) {
			this->skipWhitespace();
		} else if (isdigit(this->currentChar)) {
			Token t(INTEGER_TYPE, this->integer());
			return t;
		} else if (this->currentChar == '+') {
			this->advance();
			return Token(PLUS_TYPE, "+");
		} else if (this->currentChar == '-') {
			this->advance();
			return Token(MINUS_TYPE, "-");
		} else if (this->currentChar == '*') {
			this->advance();
			return Token(MULTIPLE_TYPE, "*");
		} else if (this->currentChar == '/') {
			this->advance();
			return Token(DIVIDE_TYPE, "/");
		} else if (this->currentChar == '(') {
			this->advance();
			return Token(LPAREN_TYPE, "(");
		} else if (this->currentChar == ')') {
			this->advance();
			return Token(RPAREN_TYPE, ")");
		} else {
			throw std::exception();
		}
	}
	return Token("EOF", "");
}
