#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"
#include "token.h"
#include "parser.h"

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
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "1")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(PLUS_TYPE, "+")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "2")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(EOF_TYPE, "")) << "The token isn't the same";
}

TEST(LexerSuit, lexerGetNextTokenMultiple)
{
	Lexer l = Lexer(" 1 + 2   / (3     * 4)");
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "1")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(PLUS_TYPE, "+")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "2")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(DIVIDE_TYPE, "/")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(LPAREN_TYPE, "(")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "3")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(MULTIPLE_TYPE, "*")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "4")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(RPAREN_TYPE, ")")) << "The token isn't the same";
	EXPECT_EQ(l.getNextToken(), Token(EOF_TYPE, "")) << "The token isn't the same";
}

TEST(ParserSuit, parserParser01)
{
	Lexer l = Lexer("1");
	Parser p = Parser(l);
	EXPECT_EQ(p.parse()->getToken(), Token(INTEGER_TYPE, "1"));
}

TEST(ParserSuit, parserParser02)
{
	Lexer l = Lexer("1 + 2");
	Parser p = Parser(l);
	BinaryOP* root = dynamic_cast<BinaryOP*>(p.parse());
	EXPECT_EQ(root->getToken(), Token(PLUS_TYPE, "+"));
	EXPECT_EQ(root->left->getToken(), Token(INTEGER_TYPE, "1"));
	EXPECT_EQ(root->right->getToken(), Token(INTEGER_TYPE, "2"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
