#ifndef InsertCharacterCommand_hpp
#define InsertCharacterCommand_hpp

#include "Command.h"
#include "StoredString.h"
#include <cstdint>
#include <memory>

namespace WSU {
namespace Model {

    /// \imp \ref R1_3 The mechanism for inserting a character at an index in
    /// the stored string is to run() and instance of this class.
    class InsertCharacterAtIndexCommand : public StoredString::Command {
    private:
        /// The character to insert when the command executes
        char m_characterToInsert;

        /// The index at which to insert when the command executes
        size_t m_storedStringIndex;

    public:
        static constexpr const char* name { "insertCharacterAtIndex" };

        /// \param[in] s the string to modify
        /// \param[in] c the character to insert
        /// \param[in] storedStringIndex
        InsertCharacterAtIndexCommand(
            StoredString::p_t s, char c, size_t storedStringIndex);

        virtual void run();
        virtual p_t makeReciprocalCommand();
        virtual std::string getStringRepresentation();
    };

} // namespace Model
} // namespace WSU

#endif /* InsertCharacterCommand_hpp */
