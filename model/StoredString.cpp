#include <StoredString.h>
#include <cassert>

namespace WSU {
namespace Model {

    void StoredString::appendCharacter(char c) { m_string += c; }

    void StoredString::removeCharacterAtIndex(std::size_t index)
    {
        m_string.erase(index, 1);
    }

    void StoredString::insertCharacterAtIndex(char c, std::size_t index)
    {
        if (index <= m_string.size()) {
            m_string.insert(index, 1, c);
        }
    }

    void StoredString::insertStringAtIndex(
        const std::string& s, std::size_t index)
    {
        if (index <= m_string.size()) {
            m_string.insert(index, s);
        }
    }

    void StoredString::insertStringAtIndex(const char* s, std::size_t index)
    {
        insertStringAtIndex(std::string(s), index);
    }

    void StoredString::insertStringAtIndex(
        const StoredString& s, std::size_t index)
    {
        insertStringAtIndex(s.getString(), index);
    }

    StoredString::Command::Command(StoredString::p_t storedString_p)
    {
        assert(nullptr != storedString_p);
        m_storedString_p = storedString_p;
    }

    StoredString::p_t StoredString::Command::getStoredString() const
    {
        return m_storedString_p;
    }

} // namespace Model

} // namespace WSU