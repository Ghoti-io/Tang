/*
 * Generate a C++ Scanner class.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Cxx.html#Cxx
 */
%option c++

/*
 * Tell flex the name of our scanner class.  It must inherit from yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option yyclass="HtmlEscapeFlexLexer"

/*
 * Use "TangTang" as a name prefix rather than "yy".  In C++, this only applies to
 * yywrap (addressed in the next option) and yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option prefix="TangHtmlEscape"

/*
 * Get rid of yywrap.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Options-Affecting-Scanner-Behavior.html
 */
%option noyywrap

/*
 * Cause the scanner to error (rather than supply an empty default rule)
 * when no match is made.  This is handy for finding hols in our rules.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Debugging-Options.html
 */
%option nodefault

/*
 * Don't include code for the interactive scanner.  We won't use it.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Options-Affecting-Scanner-Behavior.html
 */
%option never-interactive

/*
 * Use a stack to maintain the lexer state.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Scanner-Options.html#Scanner-Options
 */
%option stack

%{

#include "htmlEscape.hpp"

using namespace std;

// yyterminate() is not a function, but a macro.
// The macro does not return the correct type.  It returns an int,
// but we want it to return a string.
// Redefine the yyterminate() macro so that it returns the correct type,
// consistent with our use.
// See yyterminate() in http://web.mit.edu/gnu/doc/html/flex_2.html
#define yyterminate() return ""

%}

validByte [\x80-\xBF]

%%

[\x00-\x7f] {
  // Valid, 1 byte.
  // Match the 5 characters that we want to escape.
  if (yytext[0] == '<') {
    return "&lt;";
  }
  else if (yytext[0] == '>') {
    return "&gt;";
  }
  else if (yytext[0] == '&') {
    return "&amp;";
  }
  else if (yytext[0] == '"') {
    return "&quot;";
  }
  else if (yytext[0] == '\'') {
    return "&apos;";
  }
  return yytext;
}
{validByte} {
  // Invalid, 1st byte cannot start with b10xxxxxx
  return yytext;
}
[\xF8-\xFF] {
  // Invalid, unrecognized 1st byte.
  return yytext;
}

[\xC0-\xC1]{validByte} {
  // Invalid, 2-byte overlong.
  return yytext;
}
[\xC2-\xDF]{validByte} {
  // Valid, 2 bytes.
  return yytext;
}
[\xC0-\xDF] {
  // Invalid, incomplete.
  return yytext;
}

\xE0[\x80-\x9F]{validByte} {
  // Invalid, 3-byte overlong.
  return yytext;
}
\xE0[\A0-\xBF]{validByte} {
  // Valid, 3 bytes.
  return yytext;
}
[\xE1-\xEC]{validByte}{validByte} {
  // Valid, 3 bytes.
  return yytext;
}
\xED[\x80-\x9F]{validByte} {
  // Valid, 3 bytes.
  return yytext;
}
\xED[\xA0-\xBF]{validByte} {
  // Invalid, surrogate.
  return yytext;
}
[\xEE-\xEF]{validByte}{validByte} {
  // Valid, 3 bytes.
  return yytext;
}
[\xE0-\xEF] {
  // Invalid, incomplete.
  return yytext;
}
[\xE0-\xEF]{validByte} {
  // Invalid, incomplete.
  return yytext;
}

\xF0[\x80-\x8F]{validByte}{validByte} {
  // Invalid, overlong.
  return yytext;
}
\xF0[\x90-\xBF]{validByte}{validByte} {
  // Valid, 4 bytes.
  return yytext;
}
[\xF1-\xF3]{validByte}{validByte}{validByte} {
  // Valid, 4 bytes.
  return yytext;
}
\xF4[\x80-\x8F]{validByte}{validByte} {
  // Valid, 4 bytes.
  return yytext;
}
\xF4[\x90-\xBF]{validByte}{validByte} {
  // Invalid, too high.
  return yytext;
}
[\xF5-\xF7]{validByte}{validByte}{validByte} {
  // Invalid, too high.
  return yytext;
}
[\xF0-\xF7] {
  // Invalid, incomplete.
  return yytext;
}
[\xF0-\xF7]{validByte} {
  // Invalid, incomplete.
  return yytext;
}
[\xF0-\xF7]{validByte}{validByte} {
  // Invalid, incomplete.
  return yytext;
}

<<EOF>> { yyterminate(); }


%%

