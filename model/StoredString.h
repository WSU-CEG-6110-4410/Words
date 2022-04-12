#ifndef StoredString_H
#define StoredString_H

#include "Command.h"
#include <string>

/// This entire project is part of a demonstration for Wright State University
/// (WSU) CSE-4110 "Intro. Software Eng." Spring 2021.
namespace WSU {

/// \anchor Model Model Subsystem
///
/// This Module contains components that are part of the Model subsystem within
/// the overall [MVC
/// Design](md__home_user_WordsExampleSpring2022_Overview.html).
namespace Model {

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
    /// This class implements the core of the Model subsystem with and
    /// provides storage for a string.
    class StoredString {
    private:
        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
        /// This member variable is used to store the characters of a string.
        std::string m_string;

    public:
        typedef std::shared_ptr<StoredString> p_t;

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
        /// \return reference to the stored string.
        const std::string& getString() const { return m_string; }

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
        /// This function appends a single character to the stored string.
        ///
        ///\param c : The character to append
        void appendCharacter(char c);

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/11)
        /// This function removes a single character at the specified
        /// index from the stored string.
        ///
        ///\param index : a valid index within the stored string
        void removeCharacterAtIndex(std::size_t index);

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/10)
        /// This function inserts a single character at the specified
        /// index in the stored string. All characters in the stored string
        /// before the insert remain in the stored string after the insert.
        /// Characters from index to the end of the string are moved to
        /// new indexes starting at index+1 in order to make room for the
        /// character inserted by this function. If index equals the
        /// current length of the stored string, character insertion
        /// produces the same result as the appendCharacter(char) function.
        /// If an index greater than the current length of the stored string is
        /// specified, the stored string is not modified.
        void insertCharacterAtIndex(char c, std::size_t index);

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/14)
        /// This function inserts all of the characters in s into the stored
        /// string starting at index within the stored string. All characters in
        /// the stored string before the insert remain in the stored string
        /// after the insert. Charcaters from index to the end of the string are
        /// moved to new indexes starting at index plus the length of s in order
        /// to make room for the character inserted by this function. If index
        /// equals the current length of the stored string, the characters of s
        /// are appended to the stored string. If an index greater than the
        /// current length of the stored string is specified, the stored string
        /// is not modified.
        void insertStringAtIndex(const std::string& s, std::size_t index);

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/14)
        /// This function inserts all of the characters in s into the stored
        /// string starting at index within the stored string. All characters in
        /// the stored string before the insert remain in the stored string
        /// after the insert. Characters from index to the end of the string are
        /// moved to new indexes starting at index plus the length of s in order
        /// to make room for the character inserted by this function. If index
        /// equals the current length of the stored string, the characters of s
        /// are appended to the stored string. If an index greater than the
        /// current length of the stored string is specified, the stored string
        /// is not modified.
        void insertStringAtIndex(const char* s, std::size_t index);

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/14)
        /// This function inserts all of the characters in s into the stored
        /// string starting at index within the stored string. All characters in
        /// the stored string before the insert remain in the stored string
        /// after the insert. Characters from index to the end of the string are
        /// moved to new indexes starting at index plus the length of s in order
        /// to make room for the character inserted by this function. If index
        /// equals the current length of the stored string, the characters of s
        /// are appended to the stored string. If an index greater than the
        /// current length of the stored string is specified, the stored string
        /// is not modified.
        void insertStringAtIndex(const StoredString& s, std::size_t index);

        /// This type defines a pointer to a Command
        typedef typename WSU::Model::Command::p_t command_p_t;

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
        /// This is an abstract base class for Commands that operate upon Stored
        /// String instances. Commands are pert of the "Command" Design Pattern
        /// and used to implement undo/redo.
        class Command : public WSU::Model::Command {
        private:
            /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
            /// This is a pointer to the string to be modified by the command
            /// when the command is executed (possibly as part of an undo/redo
            /// operation.)
            StoredString::p_t m_storedString_p;

        public:
            Command(StoredString::p_t storedString_p);

            /// \return a pointer to the string effected by the Command
            StoredString::p_t getStoredString() const;
        };

        /// Type for Factory Methods. Having a standard type simplifies use of
        /// [Factory
        /// Methods](https://en.wikipedia.org/wiki/Factory_method_pattern)
        /// because the caller need not know any details (like special
        /// arguments) about the object(s) created by the Factory Method.
        typedef std::function<command_p_t(p_t storedString_p, std::string args)>
            commandFactory_t;

    }; // class StoredString

} // namespace Model
} // namespace WSU

#endif // StoredString_H
