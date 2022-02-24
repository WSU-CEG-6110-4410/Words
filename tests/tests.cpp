#include "StoredString.h"
#include <gtest/gtest.h>

TEST(Assert, empty) { GTEST_ASSERT_EQ(true, true); }

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7) 
TEST(assert, issue7_createStoredString)
{
  ASSERT_NO_FATAL_FAILURE(WSU::Model::StoredString storedString{});
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
TEST(assert, issue7_zeroContenets)
{
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
TEST(assert, issue9_append)
{
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
  storedString.appendCharacter('W');
  GTEST_ASSERT_EQ("W", storedString.getString());
  storedString.appendCharacter('o');
  GTEST_ASSERT_EQ("Wo", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/11)
TEST(assert, issue11_remove)
{
  WSU::Model::StoredString storedString{};
  storedString.appendCharacter('W');
  storedString.appendCharacter('o');
  storedString.appendCharacter('r');
  storedString.appendCharacter('l');
  storedString.appendCharacter('d');
  storedString.appendCharacter('!');
  GTEST_ASSERT_EQ("World!", storedString.getString());
  storedString.removeCharacterAtIndex(5); // remove at end
  GTEST_ASSERT_EQ("World", storedString.getString());
  storedString.removeCharacterAtIndex(1); // remove in middle
  GTEST_ASSERT_EQ("Wrld", storedString.getString());
  storedString.removeCharacterAtIndex(0); // remove at start
  GTEST_ASSERT_EQ("rld", storedString.getString());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}