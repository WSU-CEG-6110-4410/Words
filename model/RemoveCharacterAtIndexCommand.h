#ifndef RemoveCharacterCommand_hpp
#define RemoveCharacterCommand_hpp

#include "Command.h"
#include "StoredString.h"
#include <cstdint>
#include <memory>

namespace WSU {
namespace Model {

    /// The mechanism for inserting a character at an index in
    /// the stored string is to run() and instance of this class.
    class RemoveCharacterAtIndexCommand : public StoredString::Command {
    private:
        /// The index at which to remove a character when the command executes
        size_t m_storedStringIndex;

    public:
        static constexpr const char* name { "removeCharacterAtIndex" };

        /// \param[in] s the string to modify
        /// \param[in] storedStringIndex
        RemoveCharacterAtIndexCommand(
            StoredString::p_t s, size_t storedStringIndex);

        virtual void run();
        virtual p_t makeReciprocalCommand();
    };

} // namespace Model
} // namespace WSU

#endif /* RemoveCharacterCommand_hpp */
