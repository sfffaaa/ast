#include <iostream>
#include <gtest/gtest.h>

#include "lexer.h"
#include "token.h"

TEST(LexerSuite, lexerAdvance)
{
	Lexer l = Lexer("1+3");
	EXPECT_EQ(l.currentChar, '1') << "The currentChar is not correct";
	l.advance();
	EXPECT_EQ(l.currentChar, '+') << "The currentChar is not correct";
	l.advance();
	EXPECT_EQ(l.currentChar, '3') << "The currentChar is not correct";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
