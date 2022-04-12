#include "RemoveCharacterAtIndexCommand.h"
#include "InsertCharacterAtIndexCommand.h"
#include <cassert>
#include <functional>

namespace WSU {
namespace Model {

    RemoveCharacterAtIndexCommand::RemoveCharacterAtIndexCommand(
        StoredString::p_t s_p, size_t storedStringIndex)
        : StoredString::Command(s_p)
        , m_storedStringIndex(storedStringIndex)
    {
        // Intentionally empty
    }

    void RemoveCharacterAtIndexCommand::run()
    {
        getStoredString()->removeCharacterAtIndex(m_storedStringIndex);
    }

    Command::p_t RemoveCharacterAtIndexCommand::makeReciprocalCommand()
    {
        return Command::p_t { new InsertCharacterAtIndexCommand {
            getStoredString(),
            getStoredString()->getString()[m_storedStringIndex],
            m_storedStringIndex } };
    }

} // namespace Model
} // namespace WSU
