/**
 * @file
 *
 * Contains the code to interface with the ICU library.
 */

#ifndef TANG_UNICODESTRING_HPP
#define TANG_UNICODESTRING_HPP

#include <string>

namespace Tang {
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
    std::string substr(size_t position, size_t length);

  private:
    /**
     * The UTF-8 encoded string.
     */
    std::string src;
  };
}

#endif // TANG_UNICODESTRING_HPP

