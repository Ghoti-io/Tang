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
%x SCRIPT TEMPLATE QUICKPRINT doubleQuoteString singleLineComment multiLineComment

%%
  // Include any initialization code here.  These lines *must* be indented,
  // otherwise, flex will try to interpret them as rules rather than code.
  // (Note: there is no code yet, this is just a placeholder)

  // Holds the contents of a double-quoted string as it is being parsed.
  std::string stringBuffer;

  // Indicates whether or not the current double-quoted string is trusted
  // or untrusted.
  bool isTrusted{false};

  // Flag variable to track whether or not the EOF has been seen, for use when
  // parsing templates.
  bool eofSeen{false};

<TEMPLATE>{
  "<%=" {
    yy_push_state(QUICKPRINT);
    if (stringBuffer.length()) {
      return Tang::TangParser::make_QUICKPRINTBEGINANDSTRING(stringBuffer, Tang::location(location));
    }
    return Tang::TangParser::make_QUICKPRINTBEGIN(Tang::location(location));
  }
  "<%" {
    yy_push_state(SCRIPT);
    if (stringBuffer.length()) {
      return Tang::TangParser::make_TEMPLATESTRING(stringBuffer, Tang::location(location));
    }
  }
  [^<]+ {
    stringBuffer += yytext;
  }
  "<" {
    stringBuffer += yytext;
  }
  <<EOF>> {
    if (!eofSeen && stringBuffer.length()) {
      eofSeen = true;
      return Tang::TangParser::make_TEMPLATESTRING(stringBuffer, Tang::location(location));
    }
    yyterminate();
  }
}

<INITIAL,SCRIPT,QUICKPRINT,singleLineComment,multiLineComment>{
  <<EOF>> {
    yyterminate();
  }
}

<INITIAL,SCRIPT>{
  "%>" {
    // Exit out of SCRIPT mode and return to TEMPLATE mode.
    // Error if we weren't actually in TEMPLATE mode to begin with.
    if (yy_start_stack_ptr < 1) {
      // Can't pop the stack.  This is an error.
      return Tang::TangParser::make_UNEXPECTEDSCRIPTEND(Tang::location(location));
    }
    yy_pop_state();
    stringBuffer.clear();
  }
}

<QUICKPRINT>{
  "%>" {
    // Exit out of QUICKPRINT mode and return to TEMPLATE mode.
    yy_pop_state();
    stringBuffer.clear();
    return Tang::TangParser::make_QUICKPRINTEND(Tang::location(location));
  }
}

<INITIAL,SCRIPT,QUICKPRINT>{
  \/\/ {
    // Beginning of a single line comment.
    yy_push_state(singleLineComment);
  }
  \/\* {
    // Beginning of a multi line comment.
    yy_push_state(multiLineComment);
  }
  \!\" {
    // The start of a new, double-quoted string.
    stringBuffer.clear();
    isTrusted = false;
    yy_push_state(doubleQuoteString);
  }
  \" {
    // The start of a new, double-quoted string.
    stringBuffer.clear();
    isTrusted = true;
    yy_push_state(doubleQuoteString);
  }
  if {
    return Tang::TangParser::make_IF(Tang::location(location));
  }
  else {
    return Tang::TangParser::make_ELSE(Tang::location(location));
  }
  do {
    return Tang::TangParser::make_DO(Tang::location(location));
  }
  while {
    return Tang::TangParser::make_WHILE(Tang::location(location));
  }
  for {
    return Tang::TangParser::make_FOR(Tang::location(location));
  }
  null {
    return Tang::TangParser::make_NULL(Tang::location(location));
  }
  int {
    return Tang::TangParser::make_CASTINT(Tang::location(location));
  }
  float {
    return Tang::TangParser::make_CASTFLOAT(Tang::location(location));
  }
  bool {
    return Tang::TangParser::make_CASTBOOLEAN(Tang::location(location));
  }
  string {
    return Tang::TangParser::make_CASTSTRING(Tang::location(location));
  }
  true {
    return Tang::TangParser::make_BOOLEAN(true, Tang::location(location));
  }
  false {
    return Tang::TangParser::make_BOOLEAN(false, Tang::location(location));
  }
  function {
    return Tang::TangParser::make_FUNCTION(Tang::location(location));
  }
  return {
    return Tang::TangParser::make_RETURN(Tang::location(location));
  }
  break {
    return Tang::TangParser::make_BREAK(Tang::location(location));
  }
  continue {
    return Tang::TangParser::make_CONTINUE(Tang::location(location));
  }
  print {
    return Tang::TangParser::make_PRINT(Tang::location(location));
  }
  [0-9]+ {
    int64_t number = strtoll(yytext, 0, 10);
    return Tang::TangParser::make_INTEGER(number, Tang::location(location));
  }
  ([0-9]+\.[0-9]*)|(\.[0-9]+) {
    long double number = strtold(yytext, 0);
    return Tang::TangParser::make_FLOAT(number, Tang::location(location));
  }
  = {
    return Tang::TangParser::make_ASSIGN(Tang::location(location));
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
  \{ {
    return Tang::TangParser::make_LBRACE(Tang::location(location));
  }
  \} {
    return Tang::TangParser::make_RBRACE(Tang::location(location));
  }
  \[ {
    return Tang::TangParser::make_LBRACKET(Tang::location(location));
  }
  \] {
    return Tang::TangParser::make_RBRACKET(Tang::location(location));
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
  && {
    return Tang::TangParser::make_AND(Tang::location(location));
  }
  \|\| {
    return Tang::TangParser::make_OR(Tang::location(location));
  }
  as {
    return Tang::TangParser::make_AS(Tang::location(location));
  }
  \? {
    return Tang::TangParser::make_QUESTIONMARK(Tang::location(location));
  }
  : {
    return Tang::TangParser::make_COLON(Tang::location(location));
  }
  ; {
    return Tang::TangParser::make_SEMICOLON(Tang::location(location));
  }
  , {
    return Tang::TangParser::make_COMMA(Tang::location(location));
  }
  [a-zA-Z_][a-zA-Z0-9_]* {
    return Tang::TangParser::make_IDENTIFIER(yytext, Tang::location(location));
  }
  \. {
    return Tang::TangParser::make_PERIOD(Tang::location(location));
  }
  . {}
  \n {}
}

<singleLineComment>{
  \n {
    yy_pop_state();
  }
  .+ {}
}

<multiLineComment>{
  \*\/ {
    yy_pop_state();
  }
  [^*]+ {}
  \* {}
}

<doubleQuoteString>{
  <<EOF>> {
    return Tang::TangParser::make_STRINGERROR(Tang::location(location));
  }
  \" {
    // Found the end of a double-quoted string.
    yy_pop_state();
    return Tang::TangParser::make_STRING({stringBuffer, isTrusted}, Tang::location(location));
  }
  \\[0-7]{1,3} {
    // Interpret an escaped octal number.
    unsigned char result = yytext[1] - '0';
    if (yytext[2]) {
      result <<= 3;
      result += yytext[2] - '0';
      if (yytext[3]) {
        result <<= 3;
        result += yytext[3] - '0';
      }
    }
    stringBuffer += result;
  }
  \\x[a-fA-F0-9]{1,2} {
    // Match a hexadecimal char.
    unsigned char result{0};
    for (int i = 2; i < yyleng; ++i) {
      result <<= 4;
      if (yytext[i] >= 'a' && yytext[i] <= 'f') {
        result += 10 + yytext[i] - 'a';
      }
      else if (yytext[i] >= 'A' && yytext[i] <= 'F') {
        result += 10 + yytext[i] - 'A';
      }
      else {
        result += yytext[i] - '0';
      }
    }
    stringBuffer += result;
  }
  \\[0-9]+ {
    // Generate Error - Bad escape sequence.
    // Something like "\48" or "\07777777"
    return Tang::TangParser::make_STRINGERROR(Tang::location(location));
  }
  \n|\\n {
    // Matches either an explicit or escaped newline.
    stringBuffer += "\n";
  }
  \t|\\t {
    // Matches either an explicit or escaped tab.
    stringBuffer += "\t";
  }
  \r|\\r {
    // Matches either an explicit or escaped carriage return.
    stringBuffer += "\r";
  }
  \b|\\b {
    // Matches either an explicit or escaped bell.
    stringBuffer += "\b";
  }
  \f|\\f {
    // Matches either an explicit or escaped form feed.
    stringBuffer += "\f";
  }
  \\(.|\n) {
    // Any other escaped character.
    stringBuffer += yytext[1];
  }
  [^\\\n\"]+ {
    // " <-- to fix the highlighting in Vim.
    // Any other character in the string.
    stringBuffer += yytext;
  }
  \\ {
    // Because we specified escape characters, we also need to specify what to
    // do if we see only a single backslash at the end of the input.
    return Tang::TangParser::make_STRINGERROR(Tang::location(location));
  }
}

%%

