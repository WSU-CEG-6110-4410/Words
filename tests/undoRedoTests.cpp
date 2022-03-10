#include "InsertCharacterAtIndexCommand.h"
#include "UndoRedoManager.h"
#include <gtest/gtest.h>

using WSU::Controller::UndoRedoManager;
using WSU::Model::InsertCharacterAtIndexCommand;
using WSU::Model::StoredString;

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(UndoRedo, issue15_create_undoRedoManager)
{
    auto manager_p
        = std::shared_ptr<UndoRedoManager> { new UndoRedoManager {} };
    ASSERT_NE(nullptr, manager_p);
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(UndoRedo, issue15_UndoRedoManager_runCommand)
{
    auto manager_p
        = std::shared_ptr<UndoRedoManager> { new UndoRedoManager {} };
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    manager_p->runCommand(command_p);
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(UndoRedo, issue15_UndoRedoManager_undo)
{
    auto manager_p
        = std::shared_ptr<UndoRedoManager> { new UndoRedoManager {} };
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    manager_p->runCommand(command_p);
    GTEST_ASSERT_EQ("H", string_p->getString());
    manager_p->undo();
    GTEST_ASSERT_EQ("", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(UndoRedo, issue15_UndoRedoManager_redo)
{
    auto manager_p
        = std::shared_ptr<UndoRedoManager> { new UndoRedoManager {} };
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    manager_p->runCommand(command_p);
    GTEST_ASSERT_EQ("H", string_p->getString());
    manager_p->undo();
    GTEST_ASSERT_EQ("", string_p->getString());
    manager_p->redo();
    GTEST_ASSERT_EQ("H", string_p->getString());
}

/// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
TEST(UndoRedo, issue15_UndoRedoManager_undoRedo_many)
{
    auto manager_p
        = std::shared_ptr<UndoRedoManager> { new UndoRedoManager {} };
    StoredString::p_t string_p { new WSU::Model::StoredString {} };
    WSU::Model::Command::p_t command_p { new InsertCharacterAtIndexCommand {
        string_p, 'H', 0 } };
    static constexpr int32_t interationsNumber { 1000 };
    for (int32_t i = 0; i < interationsNumber; ++i) {
        manager_p->runCommand(command_p);
    }
    GTEST_ASSERT_EQ(1000, string_p->getString().size());
    for (int32_t i = 0; i < interationsNumber; ++i) {
        manager_p->undo();
    }
    GTEST_ASSERT_EQ("", string_p->getString());
    for (int32_t i = 0; i < 3; ++i) {
        manager_p->redo();
    }
    GTEST_ASSERT_EQ("HHH", string_p->getString());
}
