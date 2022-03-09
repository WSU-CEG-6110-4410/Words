#include <StoredString.h>
#include <cassert>

namespace WSU {
namespace Model {

void StoredString::appendCharacter(char c) { m_string += c; }

void StoredString::removeCharacterAtIndex(std::size_t index)
{
    m_string.erase(index, 1);
}

} // namespace Model

} // namespace WSU