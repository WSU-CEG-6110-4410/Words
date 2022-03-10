#include "InsertCharacterAtIndexCommand.h"
#include <gtest/gtest.h>

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_create_commnd)
{
    WSU::Model::StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p {
        new WSU::Model::InsertCharacterAtIndexCommand { string_p, 'H', 0 }
    };
    ASSERT_NE(nullptr, command_p);
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_run_commnd)
{
    WSU::Model::StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p {
        new WSU::Model::InsertCharacterAtIndexCommand { string_p, 'H', 0 }
    };
    command_p->run();
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_functor)
{
    WSU::Model::StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::InsertCharacterAtIndexCommand command { string_p, 'H', 0 };
    command();
    GTEST_ASSERT_EQ("H", string_p->getString());
}
