#include "StoredString.h"
#include <gtest/gtest.h>

TEST(Assert, empty) { GTEST_ASSERT_EQ(true, true); }

TEST(assert, issue11) {
  ASSERT_NO_FATAL_FAILURE(WSU::Model::StoredString storedString{});
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
TEST(assert, issue7_zeroContents)
{
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
TEST(assert, issue9_append) {
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