#include "InsertCharacterAtIndexCommand.h"
#include <gtest/gtest.h>

using WSU::Model::InsertCharacterAtIndexCommand;
using WSU::Model::StoredString;

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_create_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    ASSERT_NE(nullptr, command_p);
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_run_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    command_p->run();
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_functor_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    InsertCharacterAtIndexCommand command { string_p, 'H', 0 };
    command();
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_reciprical_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    InsertCharacterAtIndexCommand command { string_p, 'H', 0 };
    WSU::Model::Command::p_t recipricalCommand_p {
        command.makeReciprocalCommand()
    };
    ASSERT_NE(nullptr, recipricalCommand_p);
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand, issue15_execute_reciprical_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    InsertCharacterAtIndexCommand command { string_p, 'H', 0 };
    WSU::Model::Command::p_t recipricalCommand_p {
        command.makeReciprocalCommand()
    };
    command();
    GTEST_ASSERT_EQ("H", string_p->getString());
    recipricalCommand_p->run();
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(InsertCharacterAtIndexCommand,
    issue15_execute_reciprical_reciprical_command)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    InsertCharacterAtIndexCommand command { string_p, 'H', 0 };
    WSU::Model::Command::p_t recipricalCommand_p {
        command.makeReciprocalCommand()
    };
    command();
    GTEST_ASSERT_EQ("H", string_p->getString());
    WSU::Model::Command::p_t recipricalRecipricalCommand_p {
        recipricalCommand_p->makeReciprocalCommand()
    };
    recipricalCommand_p->run();
    GTEST_ASSERT_EQ("", string_p->getString());
    recipricalRecipricalCommand_p->run();
    GTEST_ASSERT_EQ("H", string_p->getString());
}
