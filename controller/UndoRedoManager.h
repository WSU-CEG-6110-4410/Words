#ifndef UndoRedoManager_H
#define UndoRedoManager_H
#include "StoredString.h"
#include <vector>

namespace WSU {
namespace Controller {

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
    /// This class provides a mechanism for undo and redo of previously
    /// performed commands.
    class UndoRedoManager {
    private:
        /// Use a vector as a stack of commands
        std::vector<Model::StoredString::Command::p_t> m_undoStack;

        /// Use a vector as a stack of commands
        std::vector<Model::StoredString::Command::p_t> m_redoStack;

        /// Variable is used to detect when a command is run as result
        /// of an undo so a reciprocal command is pushed onto the redo stack.
        bool m_isUndoing { false };

    public:
        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/16)
        /// Call this function to undo the most recent command run via 
        /// runCommand() that hasn't already been undone.
        void undo();

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/17)
        /// Call this function to redo the most recently undone command that
        /// hasn't already been redone. 
        void redo();

        /// This function pushes a reciprocal of
        /// cmd_p onto an undo or redo stack based on whether the function is
        /// called in the midst of an undo operation or not.
        void runCommand(Model::StoredString::Command::p_t cmd_p);
    };

} // namespace Controller
} // namespace WSU

#endif
