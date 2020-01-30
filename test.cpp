#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"
#include "token.h"

TEST(TokenSuit, TokenEqual)
{
	EXPECT_EQ(Token("a", "b"), Token("a", "b")) << "Two tokens should be the same";
	EXPECT_NE(Token("a", "b"), Token("c", "b")) << "Two tokens shouldn't be the same";
	EXPECT_NE(Token("a", "b"), Token("a", "c")) << "Two tokens shouldn't be the same";
}

TEST(LexerSuite, lexerAdvance)
{
	Lexer l = Lexer("1+3");
	EXPECT_EQ(l.currentChar, '1') << "The currentChar is not correct";
	l.advance();
	EXPECT_EQ(l.currentChar, '+') << "The currentChar is not correct";
	l.advance();
	EXPECT_EQ(l.currentChar, '3') << "The currentChar is not correct";
}

TEST(LexerSuite, lexerSkipWhiteSpace)
{
	Lexer l = Lexer("  1");
	l.skipWhitespace();
	EXPECT_EQ(l.currentChar, '1') << "The currentChar is not correct";
}

TEST(LexerSuit, lexerGetNextToken)
{
	Lexer l = Lexer("1+2");
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "1")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("PLUS", "+")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "2")) << "The token isn't the same";
}

TEST(LexerSuit, lexerGetNextTokenMultiple)
{
	Lexer l = Lexer(" 1 + 2   / 3     * 4");
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "1")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("PLUS", "+")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "2")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("DIV", "/")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "3")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("MUL", "*")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token("INTEGER", "4")) << "The token isn't the same";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
