/**
 * @file
 * Define the Tang::Program::dumpBytecode method.
 */

#include <sstream>
#include <iomanip>
#include <bit>
#include <cmath>
#include "program.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

static const char* description[] = {
  "POP",
  "PEEK",
  "POKE",
  "COPY",
  "JMP",
  "JMPF",
  "JMPF_POP",
  "JMPT",
  "JMPT_POP",
  "NULLVAL",
  "INTEGER",
  "FLOAT",
  "BOOLEAN",
  "STRING",
  "ARRAY",
  "MAP",
  "LIBRARY",
  "LIBRARYSAVE",
  "LIBRARYCOPY",
  "FUNCTION",
  "ASSIGNINDEX",
  "ADD",
  "SUBTRACT",
  "MULTIPLY",
  "DIVIDE",
  "MODULO",
  "NEGATIVE",
  "NOT",
  "LT",
  "LTE",
  "GT",
  "GTE",
  "EQ",
  "NEQ",
  "PERIOD",
  "INDEX",
  "SLICE",
  "GETITERATOR",
  "ITERATORNEXT",
  "ISITERATOREND",
  "CASTINTEGER",
  "CASTFLOAT",
  "CASTBOOLEAN",
  "CASTSTRING",
  "CALLFUNC",
  "CALLFUNC_I",
  "RETURN",
  "PRINT",
};

ostream & Tang::operator<<(ostream & lhs, const Opcode & rhs) {
  if ((uinteger_t)rhs >= (uinteger_t)sizeof(description)) {
    return lhs << "UNKNOWN";
  }
  return lhs << description[(int)rhs];
}

