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

Token Lexer::getNextToken() {
	while (this->currentChar != '\0') {
		if (isspace(this->currentChar)) {
			this->skipWhitespace();
		} else if (isdigit(this->currentChar)) {
			Token t("INTEGER", std::string("") + this->currentChar);
			this->advance();
			return t;
		} else if (this->currentChar == '+') {
			this->advance();
			return Token("PLUS", "+");
		} else if (this->currentChar == '-') {
			this->advance();
			return Token("MINUS", "-");
		} else if (this->currentChar == '*') {
			this->advance();
			return Token("MUL", "*");
		} else if (this->currentChar == '/') {
			this->advance();
			return Token("DIV", "/");
		} else if (this->currentChar == '(') {
			this->advance();
			return Token("LPAREN", "(");
		} else if (this->currentChar == ')') {
			this->advance();
			return Token("RPAREN", ")");
		} else {
			throw std::exception();
		}
	}
	return Token("EOF", "");
}
