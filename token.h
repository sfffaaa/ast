#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

#define INTEGER_TYPE "INTEGER"
#define PLUS_TYPE "PLUS"
#define MINUS_TYPE "MINUS"
#define MULTIPLE_TYPE "MUL"
#define DIVIDE_TYPE "DIV"
#define LPAREN_TYPE "LPAREN"
#define RPAREN_TYPE "RPAREN"
#define EOF_TYPE "EOF"

class Token {
	public:
		std::string type;
		std::string value;

	public:
		Token(std::string t, const std::string v) :
			type(t),
			value(v) {};

	public:
		friend bool operator == (const Token& ls, const Token& rs) {
			return ls.type == rs.type && ls.value == rs.value;
		};

		friend bool operator != (const Token& ls, const Token& rs) {
			return !(ls == rs);
		};

		friend std::ostream& operator<< (std::ostream& out, const Token& t) {
			out << "Token(" << t.type << ", " << t.value << ")";
			return out;
		};
};

#endif
