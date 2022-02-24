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
  class StoredString
  {
  private:
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/7)
    /// This member variable is used to store the characters of a string.
    std::string m_string;

  public:
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
    /// \return reference to the stored string.
    const std::string &getString() const { return m_string; }

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/9)
    /// This function appends a single character to the stored string.
    ///
    ///\param c : The character to append
    void appendCharacter(char c);
}; // class StoredString

} // namespace Model
} // namespace WSU

#endif // StoredString_H
