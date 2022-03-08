#ifndef StoredString_H
#define StoredString_H

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
        /// Charcaters from index to the end of the string are moved to
        /// new indexes starting at index+1 in order to make room for the
        /// character inserted by this function. If index equals the
        /// current length of the stored string, character insertion
        /// produces the same result as the appendCharacter(char) function.
        /// It is an error to specify an index greater than the current length
        /// of the stored string.
        void insertCharacterAtIndex(char c, std::size_t index);

    }; // class StoredString

} // namespace Model
} // namespace WSU

#endif // StoredString_H
