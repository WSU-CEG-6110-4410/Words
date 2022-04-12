#include "InsertCharacterAtIndexCommand.h"
#include "RemoveCharacterAtIndexCommand.h"
#include <cassert>
#include <functional>

namespace WSU {
namespace Model {

    InsertCharacterAtIndexCommand::InsertCharacterAtIndexCommand(
        StoredString::p_t s, char c, size_t storedStringIndex)
        : StoredString::Command(s)
        , m_characterToInsert(c)
        , m_storedStringIndex(storedStringIndex)
    {
        // Intentionally empty
    }

    void InsertCharacterAtIndexCommand::run()
    {
        getStoredString()->insertCharacterAtIndex(
            m_characterToInsert, m_storedStringIndex);
    }

    Command::p_t InsertCharacterAtIndexCommand::makeReciprocalCommand()
    {
        return Command::p_t { new RemoveCharacterAtIndexCommand {
            getStoredString(), m_storedStringIndex } };
    }

} // namespace Model
} // namespace WSU
