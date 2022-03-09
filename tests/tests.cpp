#include "StoredString.h"
#include <gtest/gtest.h>

TEST(Assert, empty) { GTEST_ASSERT_EQ(true, true); }

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
TEST(StoredString, issue7_createStoredString) {
  ASSERT_NO_FATAL_FAILURE(WSU::Model::StoredString storedString{});
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
TEST(assert, issue7_zeroContents)
{
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
TEST(StoredString, issue9_append) {
  WSU::Model::StoredString storedString{};
  GTEST_ASSERT_EQ("", storedString.getString());
  storedString.appendCharacter('W');
  GTEST_ASSERT_EQ("W", storedString.getString());
  storedString.appendCharacter('o');
  GTEST_ASSERT_EQ("Wo", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/11)
TEST(StoredString, issue11_remove) {
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

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/10)
TEST(StoredString, issue10_insertChar)
{
  WSU::Model::StoredString storedString{};

  // Insert into empty string
  storedString.insertCharacterAtIndex('W', 0);
  GTEST_ASSERT_EQ("W", storedString.getString());

  storedString.appendCharacter('o');
  storedString.appendCharacter('r');
  storedString.appendCharacter('d');

  // Insert into middle of string
  storedString.insertCharacterAtIndex('l', 3);
  GTEST_ASSERT_EQ("World", storedString.getString());

  // Insert at end of non-empty string
  storedString.insertCharacterAtIndex('!', 5);
  GTEST_ASSERT_EQ("World!", storedString.getString());

  // Insert past end of non-empty string and string is not modified
  storedString.insertCharacterAtIndex('!', 10);
  GTEST_ASSERT_EQ("World!", storedString.getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/10)
TEST(StoredString, issue10_insertString)
{
  WSU::Model::StoredString storedString{};

  // Insert into empty string
  storedString.insertStringAtIndex("W", 0);
  GTEST_ASSERT_EQ("W", storedString.getString());

  storedString.appendCharacter('o');
  storedString.appendCharacter('r');
  storedString.appendCharacter('d');

  // Insert into middle of string
  storedString.insertStringAtIndex(std::string("l"), 3);
  GTEST_ASSERT_EQ("World", storedString.getString());

  // Insert at end of non-empty string
  storedString.insertStringAtIndex("!", 5);
  GTEST_ASSERT_EQ("World!", storedString.getString());

  // Insert past end of non-empty string and string is not modified
  storedString.insertStringAtIndex("!", 10);
  GTEST_ASSERT_EQ("World!", storedString.getString());

  // Needed for subsequent test cases
  WSU::Model::StoredString secondStoredString{};
  secondStoredString.insertStringAtIndex("Hello ", 0);
  GTEST_ASSERT_EQ("Hello ", secondStoredString.getString());

  // Version that accepts StoredString argument at end
  secondStoredString.insertStringAtIndex(storedString, 6);
  GTEST_ASSERT_EQ("Hello World!", secondStoredString.getString());

  // Version that accepts StoredString argument at middle
  secondStoredString.insertStringAtIndex(storedString, 6);
  GTEST_ASSERT_EQ("Hello World!World!", secondStoredString.getString());

  // Version that accepts StoredString argument at beginning
  secondStoredString.insertStringAtIndex(storedString, 0);
  GTEST_ASSERT_EQ("World!Hello World!World!", secondStoredString.getString());

  // Inserting StoredString into itself at beginning
  storedString.insertStringAtIndex(storedString, 0);
  GTEST_ASSERT_EQ("World!World!", storedString.getString());

  // Inserting StoredString into itself at end
  storedString.insertStringAtIndex(storedString, 0);
  GTEST_ASSERT_EQ("World!World!World!World!", storedString.getString());

  // Inserting StoredString into itself at middle
  storedString.insertStringAtIndex(storedString, 1);
  GTEST_ASSERT_EQ("WWorld!World!World!World!orld!World!World!World!", storedString.getString());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}