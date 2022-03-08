#include <StoredString.h>
#include <cassert>

namespace WSU {
namespace Model {

void StoredString::appendCharacter(char c) { m_string += c; }

void StoredString::removeCharacterAtIndex(std::size_t index) {
  m_string.erase(index, 1);
}

void StoredString::insertCharacterAtIndex(char c, std::size_t index) {
  if (index <= m_string.size()) {
    m_string.insert(index, 1, c);
  }
}

} // namespace Model

} // namespace WSU