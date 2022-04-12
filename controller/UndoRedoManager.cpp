#include "UndoRedoManager.h"

namespace WSU {
namespace Controller {

    void UndoRedoManager::undo()
    {
        m_isUndoing = true;
        auto cmd_p = m_undoStack.back();
        m_undoStack.pop_back();
        runCommand(cmd_p);
        m_isUndoing = false;
    }

    void UndoRedoManager::redo()
    {
        auto cmd_p = m_redoStack.back();
        m_redoStack.pop_back();
        runCommand(cmd_p);
    }

    void UndoRedoManager::runCommand(Model::StoredString::Command::p_t cmd_p)
    {
        if (!m_isUndoing) {
            m_undoStack.push_back(cmd_p->makeReciprocalCommand());
        } else {
            m_redoStack.push_back(cmd_p->makeReciprocalCommand());
        }
        cmd_p->run();
    }

} // namespace Controller
} // namespace WSU
