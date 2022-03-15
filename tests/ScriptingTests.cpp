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
                 "index" : 0
            })") };
    command_p->run();
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_insertCharacterAtIndex_errorJSONProperty)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "insertCharacterAtIndex", string_p, R"(
            {
                "character!" : "W",
                "index" : 0
            })") };
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorJSONProperty)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", string_p, R"(
            {
                  "index!" : 0
            })") };
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorJSONSyntax)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", string_p, R"(
            {
                "command" --- "removeCharacterAtIndex",
                 "index!" : 0
            })") };
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry,
    issue19_removeCharacterAtIndex_errorNonexistentCommand)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "fuCharacterAtIndex", string_p, R"(
            {
                  "index!" : 0
            })") };
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_oneLineScript)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    std::istringstream iss {
        R"(insertCharacterAtIndex {"character" : "H","index" : 0})"
    };
    WSU::Controller::ScriptRunner::run(iss, string_p);
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_multiLineScript0)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    std::istringstream iss {
        R"(
        insertCharacterAtIndex {"character" : "H","index" : 0}
        insertCharacterAtIndex {"character" : "e","index" : 1}
        insertCharacterAtIndex {"character" : "l","index" : 2}
        insertCharacterAtIndex {"character" : "o","index" : 3}
        insertCharacterAtIndex {"character" : "l","index" : 3}
        )"
    };
    WSU::Controller::ScriptRunner::run(iss, string_p);
    GTEST_ASSERT_EQ("Hello", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_multiLineScript1)
{
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    std::istringstream iss {
        R"(
        insertCharacterAtIndex {"character" : "!","index" : 0}
        insertCharacterAtIndex {"character" : "d","index" : 0}
        insertCharacterAtIndex {"character" : "l","index" : 0}
        insertCharacterAtIndex {"character" : "r","index" : 0}
        insertCharacterAtIndex {"character" : "o","index" : 0}
        insertCharacterAtIndex {"character" : "w","index" : 0}
        insertCharacterAtIndex {"character" : " ","index" : 0}
        insertCharacterAtIndex {"character" : "!","index" : 0}
        insertCharacterAtIndex {"character" : "H","index" : 0}
        insertCharacterAtIndex {"character" : "e","index" : 1}
        insertCharacterAtIndex {"character" : "l","index" : 2}
        insertCharacterAtIndex {"character" : "o","index" : 3}
        insertCharacterAtIndex {"character" : "l","index" : 3}
        removeCharacterAtIndex {"index" : 5}
        )"
    };
    WSU::Controller::ScriptRunner::run(iss, string_p);
    GTEST_ASSERT_EQ("Hello world!", string_p->getString());
}
