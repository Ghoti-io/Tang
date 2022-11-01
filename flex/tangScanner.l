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
%option yyclass="TangScanner"

/*
 * Use "TangTang" as a name prefix rather than "yy".  In C++, this only applies to
 * yywrap (addressed in the next option) and yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option prefix="TangTang"

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
// Need to find an alternative to cstdlib if compiling on Windows.
#include <cstdlib>

#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "location.hh"

using namespace std;

// yyterminate() is not a function, but a macro.
// The macro does not return the correct type.  It returns an int,
// But the Bison 3 variants requires the return of a Parser::symbol_type.
// Redefine the yyterminate() macro so that it returns the correct type,
// consistent with our use of the Bison variants.
// This macro will be used in Scanner::get_next_token() method (YY_DECL).
// See yyterminate() in http://web.mit.edu/gnu/doc/html/flex_2.html
#define yyterminate() return Tang::TangParser::make_EOF(Tang::location(location))

// Use the YY_USER_ACTION macro to add some housekeeping code.
// Specifically, we use it to update our location information to keep
// it consistent with the lexer location.
// https://www.cs.virginia.edu/~cr4bd/flex-manual/Misc-Macros.html
// yyleng is the length of the currently matched token.
// yytext is a C-string containing the matched text.
// https://www.cs.virginia.edu/~cr4bd/flex-manual/User-Values.html#User-Values
#define YY_USER_ACTION {             \
  location.step();                   \
  for (int i = 0; i < yyleng; ++i) { \
    if (yytext[i] == '\n') {         \
      location.end.column = 0;       \
      location.lines();              \
    }                                \
    else {                           \
      location.columns();            \
    }                                \
  }                                  \
}

%}

/*
 * States used for different parsing modes.  It is useful when needing to
 * create micro-parsers, such as for comments or parsing C-style double-quoted
 * strings.
 * Approach modeled after http://dinosaur.compilertools.net/flex/manpage.html
 *   (search for "C-style")
 * Also given here: https://www.cs.virginia.edu/~cr4bd/flex-manual/Start-Conditions.html
 */
%x SCRIPT

%%
  // Include any initialization code here.  These lines *must* be indented,
  // otherwise, flex will try to interpret them as rules rather than code.
  // (Note: there is no code yet, this is just a placeholder)

<INITIAL,SCRIPT>{
  int {
    return Tang::TangParser::make_CASTINT(Tang::location(location));
  }
  float {
    return Tang::TangParser::make_CASTFLOAT(Tang::location(location));
  }
  bool {
    return Tang::TangParser::make_CASTBOOLEAN(Tang::location(location));
  }
  true {
    return Tang::TangParser::make_BOOLEAN(true, Tang::location(location));
  }
  false {
    return Tang::TangParser::make_BOOLEAN(false, Tang::location(location));
  }
  [0-9]+ {
    int64_t number = strtoll(yytext, 0, 10);
    return Tang::TangParser::make_INTEGER(number, Tang::location(location));
  }
  ([0-9]+\.[0-9]*)|(\.[0-9]+) {
    long double number = strtold(yytext, 0);
    return Tang::TangParser::make_FLOAT(number, Tang::location(location));
  }
  \+ {
    return Tang::TangParser::make_PLUS(Tang::location(location));
  }
  \- {
    return Tang::TangParser::make_MINUS(Tang::location(location));
  }
  \* {
    return Tang::TangParser::make_MULTIPLY(Tang::location(location));
  }
  \/ {
    return Tang::TangParser::make_DIVIDE(Tang::location(location));
  }
  \% {
    return Tang::TangParser::make_MODULO(Tang::location(location));
  }
  \( {
    return Tang::TangParser::make_LPAREN(Tang::location(location));
  }
  \) {
    return Tang::TangParser::make_RPAREN(Tang::location(location));
  }
  \! {
    return Tang::TangParser::make_EXCLAMATIONPOINT(Tang::location(location));
  }
  \< {
    return Tang::TangParser::make_LESSTHAN(Tang::location(location));
  }
  \<= {
    return Tang::TangParser::make_LESSTHANEQUAL(Tang::location(location));
  }
  \> {
    return Tang::TangParser::make_GREATERTHAN(Tang::location(location));
  }
  \>= {
    return Tang::TangParser::make_GREATERTHANEQUAL(Tang::location(location));
  }
  == {
    return Tang::TangParser::make_EQUALCOMPARE(Tang::location(location));
  }
  != {
    return Tang::TangParser::make_NOTEQUAL(Tang::location(location));
  }
  as {
    return Tang::TangParser::make_AS(Tang::location(location));
  }
  ; {
    return Tang::TangParser::make_SEMICOLON(Tang::location(location));
  }
  . {}
  \n {}
  <<EOF>> {
    yyterminate();
  }
}

%%

