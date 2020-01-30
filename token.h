#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

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
};

#endif
