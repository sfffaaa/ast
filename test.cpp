#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"
#include "token.h"
#include "parser.h"

TEST(TokenSuit, TokenEqual)
{
	ASSERT_EQ(Token("a", "b"), Token("a", "b")) << "Two tokens should be the same";
	ASSERT_NE(Token("a", "b"), Token("c", "b")) << "Two tokens shouldn't be the same";
	ASSERT_NE(Token("a", "b"), Token("a", "c")) << "Two tokens shouldn't be the same";
}

TEST(LexerSuite, lexerAdvance)
{
	Lexer l = Lexer("1+3");
	ASSERT_EQ(l.currentChar, '1') << "The currentChar is not correct";
	l.advance();
	ASSERT_EQ(l.currentChar, '+') << "The currentChar is not correct";
	l.advance();
	ASSERT_EQ(l.currentChar, '3') << "The currentChar is not correct";
}

TEST(LexerSuite, lexerSkipWhiteSpace)
{
	Lexer l = Lexer("  1");
	l.skipWhitespace();
	ASSERT_EQ(l.currentChar, '1') << "The currentChar is not correct";
}

TEST(LexerSuit, lexerGetNextToken)
{
	Lexer l = Lexer("1+2");
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "1")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(PLUS_TYPE, "+")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "2")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(EOF_TYPE, "")) << "The token isn't the same";
}

TEST(LexerSuit, lexerGetNextTokenMultiple)
{
	Lexer l = Lexer(" 1 + 2   / (3     * 4)");
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "1")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(PLUS_TYPE, "+")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "2")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(DIVIDE_TYPE, "/")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(LPAREN_TYPE, "(")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "3")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(MULTIPLE_TYPE, "*")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(INTEGER_TYPE, "4")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(RPAREN_TYPE, ")")) << "The token isn't the same";
	ASSERT_EQ(l.getNextToken(), Token(EOF_TYPE, "")) << "The token isn't the same";
}

TEST(ParserSuit, parserParser01)
{
	Lexer l = Lexer("1");
	Parser p = Parser(l);
	Num* root = dynamic_cast<Num*>(p.parse());
	ASSERT_NE(root, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->getToken(), Token(INTEGER_TYPE, "1"));
}

TEST(ParserSuit, parserParser02)
{
	Lexer l = Lexer("1 + 2");
	Parser p = Parser(l);
	BinaryOP* root = dynamic_cast<BinaryOP*>(p.parse());
	ASSERT_NE(root, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->getToken(), Token(PLUS_TYPE, "+"));
	ASSERT_NE(root->left, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->left->getToken(), Token(INTEGER_TYPE, "1"));
	ASSERT_NE(root->right, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->right->getToken(), Token(INTEGER_TYPE, "2"));
}

TEST(ParserSuit, parserParser03)
{
	Lexer l = Lexer("1 * (2 + 3)");
	Parser p = Parser(l);
	BinaryOP* root = dynamic_cast<BinaryOP*>(p.parse());
	ASSERT_NE(root, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->getToken(), Token(MULTIPLE_TYPE, "*"));
	ASSERT_NE(root->left, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->left->getToken(), Token(INTEGER_TYPE, "1"));
	ASSERT_NE(root->right, nullptr) << "Shouldn't be nullptr";
	BinaryOP* node = dynamic_cast<BinaryOP*>(root->right);
	ASSERT_EQ(node->getToken(), Token(PLUS_TYPE, "+"));
	ASSERT_NE(node->left, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(node->left->getToken(), Token(INTEGER_TYPE, "2"));
	ASSERT_NE(node->right, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(node->right->getToken(), Token(INTEGER_TYPE, "3"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
