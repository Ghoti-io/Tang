/**
 * @file
 * Declare the Tang::HtmlEscapeAscii used to tokenize a Tang script.
 */

#ifndef TANG_HTMLESCAPEASCII_HPP
#define TANG_HTMLESCAPEASCII_HPP

// The FlexLexer.h header file is intended to be able to be included multiple
// times, once for each unique lexer class created.  As such, we need to include
// the header file here, using the correct definition of the yyFlexLexer macro.
// This should use the prefix specified in tpt.l.
#ifndef FLEXINT_H
#undef yyFlexLexer
#define yyFlexLexer TangHtmlEscapeAsciiFlexLexer
#include <FlexLexer.h>
#endif //FLEXINT_H

// YY_DECL is defined in scanner.cpp *before* this header file was included.
// The default definition of YY_DECL (int) doesn't return the correct type, so
// we redefine it to be the type that we need (for use with Bison 3).
// symbol_type is defined in the bison header file.
#undef YY_DECL
#define YY_DECL std::string Tang::HtmlEscapeAscii::get_next_token()

// Now, the normal header contents.

namespace Tang {
  /**
   * The Flex lexer class for the main Tang language.
   *
   * Flex requires that our lexer class inherit from yyFlexLexer, an
   * "intermediate" class whose real name is "TangTangFlexLexer".
   * We are subclassing it so that we can override the return type of
   * get_next_token(), for compatibility with Bison 3 tokens.
   */
  class HtmlEscapeAscii : public yyFlexLexer {
  public:
    /**
     * The constructor for the Scanner.
     *
     * The design of the Flex lexer is to tokenize the contents of an input
     * stream, and to write any error messages to an output stream.  In our
     * implementation, however, errors are returned differently, so the output
     * stream is never used.  It's presence is retained, however, in case
     * it is needed in the future.
     *
     * For now, the general approach should be to supply the input as a string
     * stream, and to use std::cout as the output.
     *
     * @param arg_yyin The input stream to be tokenized
     * @param arg_yyout The output stream (not currently used)
     */
    HtmlEscapeAscii(std::istream& arg_yyin, std::ostream& arg_yyout) : yyFlexLexer(arg_yyin, arg_yyout) {}
    
    /**
     * Extract the next token from the input string.
     *
     * @return The next unescaped character.
     */
    virtual std::string get_next_token();
  };
}

#endif // TANG_HTMLESCAPEASCII_HPP

