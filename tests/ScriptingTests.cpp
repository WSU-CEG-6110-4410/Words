#include "CommandFactory.h"
#include "CommandFactoryAutoRegister.h"
#include "InsertCharacterAtIndexCommand.h"
#include <gtest/gtest.h>

using WSU::Controller::CommandFactoryAutoRegister;
using WSU::Controller::CommandFactoryRegistry;
using WSU::Model::InsertCharacterAtIndexCommand;
using WSU::Model::StoredString;

StoredString::p_t sharedString_p { new WSU::Model::StoredString {} };

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19).
/// This declaration forces instantiation of
/// CommandFactoryAutoRegister instances at run time, and the instantiations
/// have the side effect of associating factory functions with a names via
/// CommandFactoryRegistry. The associations enable translation of scripting
/// language commands encoded as strings into Model::Command instances that
/// may be run (to execute the script) at run time.
static std::array<CommandFactoryAutoRegister, 2> autoRegisterers {
    WSU::Controller::InsertCharacterAtIndexAutoRegister { sharedString_p },
    WSU::Controller::RemoveCharacterAtIndexAutoRegister { sharedString_p },
};

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_insertCharacterAtIndex)
{
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "insertCharacterAtIndex", R"(
            {
                "character" : "W",
                "index" : 0
            })") };
    command_p->run();
    GTEST_ASSERT_EQ("W", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex)
{
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "removeCharacterAtIndex", R"(
            {
                 "index" : 0
            })") };
    command_p->run();
    GTEST_ASSERT_EQ("", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_insertCharacterAtIndex_errorJSONProperty)
{
    WSU::Model::Command::p_t command_p;
    EXPECT_THROW(
        command_p = WSU::Model::Command::p_t { CommandFactoryRegistry::make(
            "insertCharacterAtIndex", R"(
            {
                "character!" : "W",
                "index" : 0
            })") },
        std::invalid_argument);
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorJSONProperty)
{
    WSU::Model::Command::p_t command_p;
    EXPECT_THROW(
        command_p = WSU::Model::Command::p_t { CommandFactoryRegistry::make(
            "removeCharacterAtIndex", R"(
            {
                  "index!" : 0
            })") },
        std::invalid_argument);
    GTEST_ASSERT_EQ("", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_removeCharacterAtIndex_errorJSONSyntax)
{
    WSU::Model::Command::p_t command_p;
    EXPECT_THROW(
        command_p = WSU::Model::Command::p_t { CommandFactoryRegistry::make(
            "removeCharacterAtIndex", R"(
            {
                "command" --- "removeCharacterAtIndex",
                 "index!" : 0
            })") },
        std::invalid_argument);
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry,
    issue19_removeCharacterAtIndex_errorNonexistentCommand)
{
    WSU::Model::Command::p_t command_p { CommandFactoryRegistry::make(
        "fuCharacterAtIndex", R"(
            {
                  "index!" : 0
            })") };
    GTEST_ASSERT_EQ(nullptr, command_p);
    GTEST_ASSERT_EQ("", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_oneLineScript)
{
    std::istringstream iss {
        R"(insertCharacterAtIndex {"character" : "H","index" : 0})"
    };
    WSU::Controller::ScriptRunner::run(iss);
    GTEST_ASSERT_EQ("H", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_multiLineScript0)
{
    std::istringstream iss {
        R"(
        insertCharacterAtIndex {"character" : "H","index" : 0}
        insertCharacterAtIndex {"character" : "e","index" : 1}
        insertCharacterAtIndex {"character" : "l","index" : 2}
        insertCharacterAtIndex {"character" : "o","index" : 3}
        insertCharacterAtIndex {"character" : "l","index" : 3}
        )"
    };
    WSU::Controller::ScriptRunner::run(iss);
    GTEST_ASSERT_EQ("HelloH", sharedString_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
TEST(CommandFactoryRegistry, issue19_multiLineScript1)
{
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
    WSU::Controller::ScriptRunner::run(iss);
    GTEST_ASSERT_EQ("Hello world!HelloH", sharedString_p->getString());
}
