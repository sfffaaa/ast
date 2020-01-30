#include <iostream>
#include <gtest/gtest.h>

TEST(IntegerInputsSuite, simpleSum)
{
  EXPECT_EQ(5, 6) << "The sum is not correct";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
