/**
 * @file
 *
 * Contains the code to interface with the ICU library.
 */

#ifndef TANG_UNICODESTRING_HPP
#define TANG_UNICODESTRING_HPP

#include <string>
#include <memory>
#include <vector>

namespace Tang {
  /**
   * Return an "unescaped" version of the provided string, which, when
   * interpreted by Tang, should result in a representation equivalent to the
   * original source string.
   *
   * @param str The string to be unescaped.
   * @return An "unescaped" version of the provided string.
   */
  std::string unescape(const std::string & str);

  /**
   * Return an "html escaped" version of the provided string.
   *
   * Only "critical" characters `<`, `>`, `&`, `"`, and `'` will be escaped.
   * All other characters will be allowed through unaltered.  The result is a
   * UTF-8 encoded string that is safe for inclusion in an HTML template
   * without disturbing the HTML structure.
   *
   * @param str The string to be escaped.
   * @return An "escaped" version of the provided string.
   */
  std::string htmlEscape(const std::string & str);

  /**
   * Represents a UTF-8 encoded string that is Unicode-aware.
   *
   * This class serves as the interface between the Tang language and the ICU
   * library.
   */
  class UnicodeString {
  public:
    /**
     * Construct a Tang::UnicodeString object, which acts as the interface to
     * the ICU library.
     *
     * @param src A UTF-8 encoded string.
     */
    UnicodeString(const std::string & src);

    /**
     * Return a Unicode grapheme-aware substring.
     *
     * @param position The 0-based position of the first grapheme.
     * @param length The maximum number of graphemes to return.
     * @return The requested substring.
     */
    std::string substr(size_t position, size_t length) const;

    /**
     * Compare two UnicodeStrings.
     *
     * @param rhs The string to compare against.
     * @return Returns true if the two strings are equal.
     */
    bool operator==(const UnicodeString & rhs) const;

    /**
     * Compare two UnicodeStrings.
     *
     * @param rhs The string to compare against.
     * @return Returns true if the rhs string is greater than or equal to the
     *   object string.
     */
    bool operator<(const UnicodeString & rhs) const;

    /**
     * Create a new UnicodeString that is the concatenation of two
     * UnicodeStrings.
     *
     * @param rhs The string to append to the current object string.
     * @return Returns the result of the concatenation.
     */
    UnicodeString operator+(const UnicodeString & rhs) const;

    /**
     * Cast the current UnicodeString object to a std::string, UTF-8 encoded.
     *
     * @return Returns the std::string version of the UnicodeString.
     */
    operator std::string() const;

    /**
     * Return the length of the UnicodeString in graphemes.
     *
     * Note: this is *not* the number of bytes, chars, or codepoints, but is
     * the length in graphemes, as defined by ICU.
     *
     * @return Returns the length of the UnicodeString in graphemes.
     */
    size_t length() const;

    /**
     * Return the length of the UnicodeString in bytes.
     *
     * Note: this is *not* the number of codepoints or graphemes, but is the
     * acutal number of bytes in memory.
     *
     * @return Returns the length of the UnicodeString in bytes.
     */
    size_t bytesLength() const;

  private:
    /**
     * The UTF-8 encoded string.
     */
    std::string src;

    /**
     * Cache of the grapheme offsets, if they happen to be calculated.
     */
    mutable std::shared_ptr<std::vector<size_t>> graphemeOffsets;

    /**
     * Cache of the ICU Unicode string.
     */
    mutable std::shared_ptr<void> uString;

    /**
     * Calculate cachable values for the object.
     */
    void generateCachedValues() const;
  };
}

#endif // TANG_UNICODESTRING_HPP

