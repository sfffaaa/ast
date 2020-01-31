#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

TEST(TokenSuit, TokenEqual)
{
	ASSERT_EQ(Token("a", "b"), Token("a", "b")) << "Two tokens should be the same";
	ASSERT_NE(Token("a", "b"), Token("c", "b")) << "Two tokens shouldn't be the same";
	ASSERT_NE(Token("a", "b"), Token("a", "c")) << "Two tokens shouldn't be the same";
}

TEST(LexerSuite, lexerAdvance)
{
	Lexer l = Lexer("1+3");
	ASSERT_EQ(l.getCurrentChar(), '1') << "The currentChar is not correct";
	l.advance();
	ASSERT_EQ(l.getCurrentChar(), '+') << "The currentChar is not correct";
	l.advance();
	ASSERT_EQ(l.getCurrentChar(), '3') << "The currentChar is not correct";
}

TEST(LexerSuite, lexerDigital)
{
	Lexer l = Lexer("10");
	ASSERT_THROW(l.getNextToken(), std::exception);
}

TEST(LexerSuite, lexerSkipWhiteSpace)
{
	Lexer l = Lexer("  1");
	l.skipWhitespace();
	ASSERT_EQ(l.getCurrentChar(), '1') << "The currentChar is not correct";
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
	Parser p = Parser("1");
	Num* root = dynamic_cast<Num*>(p.parse());
	ASSERT_NE(root, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->getToken(), Token(INTEGER_TYPE, "1"));
}

TEST(ParserSuit, parserParser02)
{
	Parser p = Parser("1 + 2");
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
	Parser p = Parser("1 * (2 + 3)");
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

TEST(ParserSuit, parserParser04)
{
	Parser p = Parser("1+2+3");
	BinaryOP* root = dynamic_cast<BinaryOP*>(p.parse());
	ASSERT_NE(root, nullptr) << "Shouldn't be nullptr";
	ASSERT_EQ(root->getToken(), Token(PLUS_TYPE, "+"));
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

TEST(InterpreterSuit, interpreterVisit01)
{
	Interpreter interpreter = Interpreter("1");
	ASSERT_EQ(interpreter.interpret(), 1);
}

TEST(InterpreterSuit, interpreterVisit02)
{
	Interpreter interpreter = Interpreter("1 + 2");
	ASSERT_EQ(interpreter.interpret(), 3);
}

TEST(InterpreterSuit, interpreterVisit03)
{
	Interpreter interpreter = Interpreter("1 + 2 * 3");
	ASSERT_EQ(interpreter.interpret(), 7);
}

TEST(InterpreterSuit, goldenCase01)
{
	Interpreter interpreter = Interpreter("(4 + 5 * (7 - 3)) - 2");
	ASSERT_EQ(interpreter.interpret(), 22);
}

TEST(InterpreterSuit, goldenCase02)
{
	Interpreter interpreter = Interpreter("4+5+7/2");
	ASSERT_EQ(interpreter.interpret(), 12);
}

TEST(InterpreterSuit, goldenCase03)
{
	Interpreter interpreter = Interpreter("10 + 1");
	ASSERT_THROW(interpreter.interpret(), std::exception);
}

TEST(InterpreterSuit, goldenCase04)
{
	Interpreter interpreter = Interpreter("-10");
	ASSERT_THROW(interpreter.interpret(), std::exception);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
