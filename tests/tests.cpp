#include "StoredString.h"
#include <gtest/gtest.h>

TEST(Assert, empty) { GTEST_ASSERT_EQ(true, true); }

TEST(assert, issue11) {
  ASSERT_NO_FATAL_FAILURE(WSU::Model::StoredString storedString{});
}

TEST(assert, issue11_zeroContenets) {
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
}

TEST(assert, issue13_append) {
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
  storedString.appendCharacter('W');
  GTEST_ASSERT_EQ("W", storedString.getString());
  storedString.appendCharacter('o');
  GTEST_ASSERT_EQ("Wo", storedString.getString());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}