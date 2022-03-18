#ifndef RemoveCharacterCommand_hpp
#define RemoveCharacterCommand_hpp

#include "Command.h"
#include "StoredString.h"
#include <cstdint>
#include <memory>

namespace WSU {
namespace Model {

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
    /// Instances of this class encapsulate "commands" that store information
    /// sufficient to run the command at a later time. Commands may be stored in
    /// a stack for "undo" operations or in a queue to form a "script" of
    /// commands that may run in sequence to run the "script".
    /// Run an instance of this command to remove a character at an index in
    /// a stored string.
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

        /// Call this function to run the command
        virtual void run();

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
        /// This function returns a command that when run undoes the effects of
        /// running this command.
        virtual p_t makeReciprocalCommand();
    };

} // namespace Model
} // namespace WSU

#endif /* RemoveCharacterCommand_hpp */
