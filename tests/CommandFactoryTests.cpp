#include "CommandFactory.h"
#include <gtest/gtest.h>

using WSU::Controller::CommandFactoryRegistry;
using WSU::Model::StoredString;

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_insertCharacterAtIndex)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "insertCharacterAtIndex", string_p, R"(
            {
                "command" : "insertCharacterAtIndex",
                "character" : "W",
                "index" : 0
            })") };
    command_p->run();
    GTEST_ASSERT_EQ("W", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", string_p, R"(
            {
                "command" : "removeCharacterAtIndex",
                 "index" : 0
            })") };
    command_p->run();
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_insertCharacterAtIndex_errorProperty)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "insertCharacterAtIndex", string_p, R"(
            {
                "command" : "insertCharacterAtIndex",
                "character!" : "W",
                "index" : 0
            })") };
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorProperty)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", string_p, R"(
            {
                "command" : "removeCharacterAtIndex",
                 "index!" : 0
            })") };
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorSyntax)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", string_p, R"(
            {
                "command" --- "removeCharacterAtIndex",
                 "index!" : 0
            })") };
    GTEST_ASSERT_EQ("", string_p->getString());
}
