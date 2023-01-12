/**
 * @file
 * Declare the Opcodes used in the Bytecode representation of a program.
 */

#ifndef TANG_OPCODE_HPP
#define TANG_OPCODE_HPP

#include <ostream>

namespace Tang {
  /**
   * All possible Opcodes that may be used in the Bytecode.
   *
   * For S/I suffixed Opcodes, (S) indicates that a value will be popped from
   * the stack, and (I) indicates that an index is provided in the bytecode, to
   * be referenced from the frame pointer (fp) during execution.
   *
   * The S/I order in the Opcode indicates the nature (stack or index) of the
   * associated values.  For example, ADD_SS will add a lhs + rhs.  The lhs
   * will have been pushed onto the stack first, followed by the rhs.
   */
  enum class Opcode {
    POP,      ///< Pop a val
    PEEK,     ///< Stack # (from fp): push val from stack #
    POKE,     ///< Stack # (from fp): Copy a val, store @ stack #
    COPY,     ///< Stack # (from fp): Deep copy val @ stack #, store @ stack #
    JMP,      ///< PC #: set pc to PC #
    JMPF_S,   ///< PC #: read val, if false, set pc to PC #
    JMPF_I,   ///< PC #: read val, if false, set pc to PC #
    JMPF_POP, ///< PC #: pop val, if false, set pc to PC #
    JMPT_S,   ///< PC #: read val, if true, set pc to PC #
    JMPT_I,   ///< PC #: read val, if true, set pc to PC #
    JMPT_POP, ///< PC #: pop val, if true, set pc to PC #
    NULLVAL,  ///< Push a null onto the stack
    INTEGER,  ///< Push an integer onto the stack
    FLOAT,    ///< Push a floating point number onto the stack
    BOOLEAN,  ///< Push a boolean onto the stack
    STRING,   ///< Get len, char string: push string
    ARRAY,    ///< Get len, pop `len` items, putting them into an array
              ///<   with the last array item popped first
    MAP,      ///< Get len, pop `len` value then key pairs, putting them into
              ///<   a map
    LIBRARY,  ///< Pop name, push Library identified by name
    LIBRARYSAVE, ///< Get index, save top of stack to library[index]
    LIBRARYCOPY, ///< Get index, load from library[index]
    FUNCTION, ///< Get argc, PC#: push function(argc, PC #)
    ASSIGNINDEX, ///< Pop index, pop collection, pop value,
                 ///<   push (collection[index] = value)
    ADD_SS,      ///< Push lhs + rhs
    ADD_SI,      ///< Push lhs + rhs
    ADD_IS,      ///< Push lhs + rhs
    ADD_II,      ///< Push lhs + rhs
    SUBTRACT_SS, ///< Push lhs - rhs
    SUBTRACT_SI, ///< Push lhs - rhs
    SUBTRACT_IS, ///< Push lhs - rhs
    SUBTRACT_II, ///< Push lhs - rhs
    MULTIPLY_SS, ///< Push lhs * rhs
    MULTIPLY_SI, ///< Push lhs * rhs
    MULTIPLY_IS, ///< Push lhs * rhs
    MULTIPLY_II, ///< Push lhs * rhs
    DIVIDE_SS,   ///< Push lhs / rhs
    DIVIDE_SI,   ///< Push lhs / rhs
    DIVIDE_IS,   ///< Push lhs / rhs
    DIVIDE_II,   ///< Push lhs / rhs
    MODULO_SS,   ///< Push lhs % rhs
    MODULO_SI,   ///< Push lhs % rhs
    MODULO_IS,   ///< Push lhs % rhs
    MODULO_II,   ///< Push lhs % rhs
    NEGATIVE_S,  ///< Push negative val
    NEGATIVE_I,  ///< Push negative val
    NOT_S,       ///< Push logical not of val
    NOT_I,       ///< Push logical not of val
    LT_SS,       ///< Push lhs < rhs
    LT_SI,       ///< Push lhs < rhs
    LT_IS,       ///< Push lhs < rhs
    LT_II,       ///< Push lhs < rhs
    LTE_SS,      ///< Push lhs <= rhs
    LTE_SI,      ///< Push lhs <= rhs
    LTE_IS,      ///< Push lhs <= rhs
    LTE_II,      ///< Push lhs <= rhs
    GT_SS,       ///< Push lhs > rhs
    GT_SI,       ///< Push lhs > rhs
    GT_IS,       ///< Push lhs > rhs
    GT_II,       ///< Push lhs > rhs
    GTE_SS,      ///< Push lhs >= rhs
    GTE_SI,      ///< Push lhs >= rhs
    GTE_IS,      ///< Push lhs >= rhs
    GTE_II,      ///< Push lhs >= rhs
    EQ_SS,       ///< Push lhs == rhs
    EQ_SI,       ///< Push lhs == rhs
    EQ_IS,       ///< Push lhs == rhs
    EQ_II,       ///< Push lhs == rhs
    NEQ_SS,      ///< Push lhs != rhs
    NEQ_SI,      ///< Push lhs != rhs
    NEQ_IS,      ///< Push lhs != rhs
    NEQ_II,      ///< Push lhs != rhs
    PERIOD,   ///< Pop rhs, pop lhs, push lhs.rhs
    INDEX,    ///< Pop index, pop collection, push collection[index]
    SLICE,    ///< Pop skip, pop end, pop begin, pop collection,
              ///<   push collection[begin:end:skip]
    GETITERATOR, ///< Pop a collection, push the collection iterator
    ITERATORNEXT,///< Pop an iterator, push the next iterator value
    ISITERATOREND,///< Pop a val, push bool(is val == iterator end)
    CASTINTEGER_S,///< Typecast to int, push
    CASTINTEGER_I,///< Typecast to int, push
    CASTFLOAT_S,  ///< Typecast to float, push
    CASTFLOAT_I,  ///< Typecast to float, push
    CASTBOOLEAN_S,///< Typecast to boolean, push
    CASTBOOLEAN_I,///< Typecast to boolean, push
    CASTSTRING_S, ///< Typecast to string, push
    CASTSTRING_I, ///< Typecast to string, push
    CALLFUNC,    ///< Get argc, Pop a function, execute function if argc matches.
    CALLFUNC_I,  ///< Get argc, get index, execute function at index if argc
                 ///<   matches.
    RETURN,   ///< Get stack #, pop return val, pop (stack #) times,
              ///< push val, restore fp, restore pc
    PRINT,    ///< Pop val, print(val), push error or NULL
  };

  /**
   * Helper to output the name of an opcode.
   *
   * @param lhs The ostream to write into.
   * @param rhs The Opcode whose name should be output.
   * @return The ostream that was written to.
   */
  std::ostream & operator<<(std::ostream & lhs, const Tang::Opcode & rhs);
}

#endif // TANG_OPCODE_HPP

