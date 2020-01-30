#include "lexer.h"
#include <iostream>

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
