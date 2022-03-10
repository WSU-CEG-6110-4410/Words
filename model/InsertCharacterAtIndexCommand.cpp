#include "InsertCharacterAtIndexCommand.h"
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
        return nullptr;
    }

    std::string InsertCharacterAtIndexCommand::getStringRepresentation()
    {
        return "";
    }

} // namespace Model
} // namespace WSU
