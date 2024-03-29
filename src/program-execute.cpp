/**
 * @file
 * Define the Tang::Program::execute method.
 */

#include <bit>
#include <cmath>
#include "program.hpp"
#include "context.hpp"
#include "opcode.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionLibrary.hpp"
#include "computedExpressionMap.hpp"
#include "computedExpressionCompiledFunction.hpp"
#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionNativeLibraryFunction.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionIteratorEnd.hpp"
#include "tangBase.hpp"

using namespace std;
using namespace Tang;

/**
 * Verify the size of the Bytecode vector so that it may be safely accessed.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define EXECUTEPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) { \
    stack.push_back(make_shared<ComputedExpressionError>(Error{"Opcode instruction truncated."})); \
    pc = this->bytecode.size(); \
    break; \
  }


/**
 * Verify the size of the stack vector so that it may be safely accessed.
 *
 * @param x The number of entries that should exist in the stack.
 */
#define STACKCHECK(x) \
  if (stack.size() < (fp + (x))) { \
    stack.push_back(make_shared<ComputedExpressionError>(Error{"Insufficient stack depth."})); \
    pc = this->bytecode.size(); \
    break; \
  }


/**
 * Unary operation macro, in which the operand is popped from the top of the
 * stack.  The result is pushed to the top of the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define UNARYOP_S(EXPRESSION) \
        STACKCHECK(1); \
        auto & operand = stack.back(); \
        stack.back() = (EXPRESSION); \
        ++pc;


/**
 * Unary operation macro, in which the operand is read from an index location
 * within the stack (indexed from the `fp`).  The result is pushed to the top
 * of the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define UNARYOP_I(EXPRESSION) \
        EXECUTEPROGRAMCHECK(1); \
        auto index = this->bytecode[pc + 1]; \
        STACKCHECK(index); \
        auto & operand = stack[fp + index]; \
        stack.emplace_back(EXPRESSION); \
        pc += 2;


/**
 * Iterator macro, similar to UNARYOP_S, but it writes the result to a stack
 * position, rather than pushing the result to the top of the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define ITERATOROP_SI(EXPRESSION) \
        EXECUTEPROGRAMCHECK(1); \
        auto position = this->bytecode[pc + 1]; \
        STACKCHECK(position); \
        auto & operand = stack.back(); \
        stack[fp + position] = (EXPRESSION); \
        stack.pop_back(); \
        pc += 2;


/**
 * Iterator macro, similar to UNARYOP_I, but it writes the result to a stack
 * position, rather than pushing the result to the top of the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define ITERATOROP_II(EXPRESSION) \
        EXECUTEPROGRAMCHECK(2); \
        auto index = this->bytecode[pc + 1]; \
        auto position = this->bytecode[pc + 2]; \
        STACKCHECK(index); \
        STACKCHECK(position); \
        auto & operand = stack[fp + index]; \
        stack[fp + position] = (EXPRESSION); \
        pc += 3;


/**
 * Binary operation macro, in which the rhs is read from the top of the stack,
 * followed by the lhs from the top of the stack.  Both are removed from the
 * stack.  The EXPRESSION is executed and the result is pushed onto the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define BINARYOP_SS(EXPRESSION) \
        STACKCHECK(2); \
        auto top = stack.size(); \
        auto & rhs = stack[top - 1]; \
        auto & lhs = stack[top - 2]; \
        stack[top - 2] = (EXPRESSION); \
        stack.pop_back(); \
        ++pc;


/**
 * Binary operation macro, in which the rhs is read from an index position
 * within the stack (fp + rhsIndex), followed by the lhs from the top of the
 * stack.  Lhs is removed from the stack.  The EXPRESSION is executed and the
 * result is pushed onto the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define BINARYOP_SI(EXPRESSION) \
        EXECUTEPROGRAMCHECK(1); \
        auto rhsIndex = this->bytecode[pc + 1]; \
        STACKCHECK(rhsIndex); \
        auto & rhs = stack[fp + rhsIndex]; \
        auto & lhs = stack.back(); \
        stack.back() = (EXPRESSION); \
        pc += 2;


/**
 * Binary operation macro, in which the rhs is read from the top of the stack,
 * and the lhs is read from an index position within the stack (fp + lhsIndex).
 * Rhs is removed from the stack.  The EXPRESSION is executed and the result is
 * pushed onto the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define BINARYOP_IS(EXPRESSION) \
        EXECUTEPROGRAMCHECK(1); \
        auto lhsIndex = this->bytecode[pc + 1]; \
        STACKCHECK(lhsIndex); \
        auto & rhs = stack.back(); \
        auto & lhs = stack[fp + lhsIndex]; \
        stack.back() = (EXPRESSION); \
        pc += 2;


/**
 * Binary operation macro, in which the lhs and rhs are read from index
 * positions within the stack (fp+lhsIndex and fp+rhsIndex, respectively).
 * The EXPRESSION is executed and the result is pushed onto the stack.
 *
 * @param EXPRESSION The expression to evaluate.
 */
#define BINARYOP_II(EXPRESSION) \
        EXECUTEPROGRAMCHECK(2); \
        auto lhsIndex = this->bytecode[pc + 1]; \
        auto rhsIndex = this->bytecode[pc + 2]; \
        STACKCHECK(lhsIndex); \
        STACKCHECK(rhsIndex); \
        auto & lhs = stack[fp + lhsIndex]; \
        auto & rhs = stack[fp + rhsIndex]; \
        stack.emplace_back(EXPRESSION); \
        pc += 3;


static void callFunc(SPCE & function, uinteger_t argc, size_t & pc, size_t & fp, vector<SPCE> & stack, vector<size_t> & pcStack, vector<size_t> & fpStack, Bytecode & bytecode, Context & context, size_t opcodeSize) {
  // Compiled functions make use of the arguments on the stack.
  // They will clean up the stack when they finish, via the RETURN
  // opcode.
  if (typeid(*function) == typeid(ComputedExpressionCompiledFunction)) {
    auto & funcConv = static_cast<ComputedExpressionCompiledFunction &>(*function);

    // Verify that the correct number of arguments has been passed.
    if (argc != funcConv.getArgc()) {
      // Incorrect number of arguments passed.
      // Clear the arguments from the stack.
      for (uinteger_t i = 0; i < argc; ++i) {
        stack.pop_back();
      }

      // Push an error onto the stack.
      stack.push_back(make_shared<ComputedExpressionError>(Error{"Incorrect number of arguments supplied at function call."}));
      pc += opcodeSize;
    }
    else {
      // Save the current execution environment so that it can be restored
      // when RETURNing from the function.
      pcStack.push_back(pc + opcodeSize);
      fpStack.push_back(fp);

      // Set the new pc and fp.
      pc = funcConv.getPc();
      fp = stack.size() - argc;
    }
  }

  // Compiled functions make use of the arguments on the stack.
  // They will clean up the stack when they finish, via the RETURN
  // opcode.
  else if (typeid(*function) == typeid(ComputedExpressionNativeBoundFunction)) {
    auto & funcConv = static_cast<ComputedExpressionNativeBoundFunction &>(*function);

    // Populate argv to use when calling the function.
    vector<SPCE> argv{};
    argv.reserve(argc);
    auto iter = stack.end() - argc;
    while (iter != stack.end()) {
      argv.push_back(*iter);
      ++iter;
    }

    // Remove the arguments from the stack.
    for (uinteger_t i = 0; i < argc; ++i) {
      stack.pop_back();
    }

    // Verify that the number of arguments supplied matches the number
    // of arguments expected.
    if ((size_t)argc != funcConv.getArgc()) {
      stack.push_back(make_shared<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));
      pc += opcodeSize;
    }

    // Make sure that there is an object that was bound to the function.
    else if (funcConv.target) {
      // Verify that the target is the correct type.
      // It is impossible for the target to not be the correct type under
      // normal circumstances.  This is just a safety check.
      if (type_index(typeid(**funcConv.target)) != funcConv.getTargetTypeIndex()) {
        stack.push_back(make_shared<ComputedExpressionError>(Error{"Type mismatch of object method to its target object."}));
      }
      else {
        stack.push_back(funcConv.getFunction()(*funcConv.target, argv));
      }
      pc += opcodeSize;
    }
    else {
      // There is no function target.  This is impossible under normal
      // circumstances, but we must account for it, just in case.
      stack.push_back(make_shared<ComputedExpressionError>(Error{"Method is not bound to any object."}));
      pc += opcodeSize;
    }
  }

  // Compiled functions make use of the arguments on the stack.
  // They will clean up the stack when they finish, via the RETURN
  // opcode.
  else if (typeid(*function) == typeid(ComputedExpressionNativeFunction)) {
    auto & funcConv = static_cast<ComputedExpressionNativeFunction &>(*function);

    // Populate argv to use when calling the function.
    vector<SPCE> argv{};
    argv.reserve(argc);
    auto iter = stack.end() - argc;
    while (iter != stack.end()) {
      argv.push_back(*iter);
      ++iter;
    }

    // Remove the arguments from the stack.
    for (uinteger_t i = 0; i < argc; ++i) {
      stack.pop_back();
    }

    // Verify that the number of arguments supplied matches the number
    // of arguments expected.
    if ((size_t)argc != funcConv.getArgc()) {
      stack.push_back(make_shared<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));
      pc += opcodeSize;
    }
    else {
      // Call the Native function.
      stack.push_back(funcConv.getFunction()(argv, context));
      pc += opcodeSize;
    }
  }
  else {
    // Error: We don't know what to do.
    // Clear the arguments from the stack.
    for (uinteger_t i = 0; i < argc; ++i) {
      stack.pop_back();
    }

    stack.push_back(make_shared<ComputedExpressionError>(Error{"Function call on unrecognized type."}));
    pc = bytecode.size();
  }
}

Context Program::execute() {
  return this->execute(ContextData{});
}

Context Program::execute(ContextData && data) {
  Context context{move(data)};

  // The program counter of the current instruction.
  size_t pc{0};

  // The frame pointer (an index into the stack frame).
  size_t fp{0};

  // The execution stack.
  vector<SPCE> stack;

  // The stack of program counters used to recover the previous pc when
  // returning from a function.
  vector<size_t> pcStack{};

  // The stack of frame pointers, used to recover the previous fp when
  // returning from a function.
  vector<size_t> fpStack{};

  // The stack of library aliases, used to propagate loaded libraries into
  // the environment of compiled functions during execution.
  vector<map<uinteger_t, SPCE>> libraryAliasStack{{}};

  while (pc < this->bytecode.size()) {
    switch ((Opcode)this->bytecode[pc]) {
      case Opcode::POP: {
        STACKCHECK(1);
        stack.pop_back();
        ++pc;
      }
      break;
      case Opcode::PEEK: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack.push_back(stack[fp + position]);
        pc += 2;
      }
      break;
      case Opcode::POKE: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack[fp + position] = stack.back();
        pc += 2;
      }
      break;
      case Opcode::COPY: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        auto targetPosition = fp + position;
        if (stack[targetPosition]->isCopyNeeded()) {
          stack[targetPosition] = stack[targetPosition]->makeCopy();
        }
        pc += 2;
      }
      break;
      case Opcode::JMP: {
        EXECUTEPROGRAMCHECK(1);
        pc = this->bytecode[pc + 1];
      }
      break;
      case Opcode::JMPF_S: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto & condition = stack.back();
        pc = (*condition == false)
          ? this->bytecode[pc + 1]
          : (pc + 2);
      }
      break;
      case Opcode::JMPF_I: {
        EXECUTEPROGRAMCHECK(2);
        auto index = this->bytecode[pc + 1];
        STACKCHECK(index);
        pc = (*stack[fp + index] == false)
          ? this->bytecode[pc + 2]
          : (pc + 3);
      }
      break;
      case Opcode::JMPF_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        pc = (*stack.back() == false)
          ? this->bytecode[pc + 1]
          : (pc + 2);
        stack.pop_back();
      }
      break;
      case Opcode::JMPT_S: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        pc = (*stack.back() == true)
          ? this->bytecode[pc + 1]
          : (pc + 2);
      }
      break;
      case Opcode::JMPT_I: {
        EXECUTEPROGRAMCHECK(2);
        auto index = this->bytecode[pc + 1];
        STACKCHECK(index);
        pc = (*stack[fp + index] == true)
          ? this->bytecode[pc + 2]
          : (pc + 3);
      }
      break;
      case Opcode::JMPT_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        pc = (*stack.back() == true)
          ? this->bytecode[pc + 1]
          : (pc + 2);
        stack.pop_back();
      }
      break;
      case Opcode::NULLVAL: {
        stack.push_back(make_shared<ComputedExpression>());
        ++pc;
      }
      break;
      case Opcode::INTEGER: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(make_shared<ComputedExpressionInteger>((integer_t)this->bytecode[pc + 1]));
        pc += 2;
      }
      break;
      case Opcode::FLOAT: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(make_shared<ComputedExpressionFloat>(bit_cast<float_t>(this->bytecode[pc + 1])));
        pc += 2;
      }
      break;
      case Opcode::BOOLEAN: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(make_shared<ComputedExpressionBoolean>(this->bytecode[pc + 1] ? true : false));
        pc += 2;
      }
      break;
      case Opcode::STRING: {
        EXECUTEPROGRAMCHECK(2);
        UnicodeString::Type type = (UnicodeString::Type) this->bytecode[pc + 1];
        auto size = this->bytecode[pc + 2];
        auto bytes = ceil((double)size / sizeof(uinteger_t));
        EXECUTEPROGRAMCHECK(2 + bytes);

        // Extract the letters of the string from the bytecode.
        // TODO make this faster by using a char * buffer.
        string temp{};
        for (size_t i = 0; i < bytes; ++i) {
          for (size_t j = 0; j < sizeof(uinteger_t); ++j) {
            if ((uinteger_t)((i * sizeof(uinteger_t)) + j) < size) {
              temp += (unsigned char)
                ((this->bytecode[pc + 3 + i] >> (8 * (sizeof(uinteger_t) - 1 - j))) & 0xFF);
            }
          }
        }

        // Finally construct the string object.
        auto gcString = make_shared<ComputedExpressionString>(temp);

        // Set the string as Untrusted if necessary.
        if (type == UnicodeString::Type::Untrusted) {
          static_cast<ComputedExpressionString &>(*gcString).setUntrusted();
        }
        // Set the string as Percent if necessary.
        else if (type == UnicodeString::Type::Percent) {
          static_cast<ComputedExpressionString &>(*gcString).setPercent();
        }

        stack.push_back(gcString);
        pc += bytes + 3;
      }
      break;
      case Opcode::ARRAY: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[pc + 1];
        STACKCHECK(size);
        vector<SPCE> contents;
        contents.reserve(size);
        // TODO: Rather copying one-by-one, copy the range using an iterator.
        for (uinteger_t i = 0; i < size; ++i) {
          contents.push_back(stack[stack.size() - size + i]);
        }
        for (uinteger_t i = 0; i < size; ++i) {
          stack.pop_back();
        }
        stack.push_back(make_shared<ComputedExpressionArray>(contents));
        pc += 2;
      }
      break;
      case Opcode::MAP: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[pc + 1];
        STACKCHECK(size * 2);
        map<string, SPCE> contents;
        for (uinteger_t i = 0; i < size; ++i) {
          auto top = stack.size();
          auto & value = stack[top - 1];
          auto & key = stack[top - 2];
          if (typeid(*key) == typeid(ComputedExpressionString)) {
            contents.insert({static_cast<ComputedExpressionString &>(*key).dump(), value});
          }
          stack.pop_back();
          stack.pop_back();
        }
        stack.push_back(make_shared<ComputedExpressionMap>(contents));
        pc += 2;
      }
      break;
      case Opcode::LIBRARY: {
        STACKCHECK(1);
        auto & name = stack.back();

        if (typeid(*name) == typeid(ComputedExpressionString)) {
          auto & nameConv = static_cast<ComputedExpressionString &>(*name);
          auto & libraries = tang->getLibraries();
          auto nameLiteral = nameConv.dump();
          stack.back() = libraries.count(nameLiteral)
            ? libraries.at(nameLiteral)(context)
            : make_shared<ComputedExpressionError>(Error{"Unknown Library"});
        }
        else {
          // We can't use this CE to access a library.
          stack.back() = make_shared<ComputedExpressionError>(Error{"Unrecognized operand on LIBRARY opcode."});
        }

        ++pc;
      }
      break;
      case Opcode::LIBRARYSAVE: {
        EXECUTEPROGRAMCHECK(1);
        auto index = this->bytecode[pc + 1];
        libraryAliasStack.back().insert({index, stack.back()});

        pc += 2;
      }
      break;
      case Opcode::LIBRARYCOPY: {
        EXECUTEPROGRAMCHECK(1);
        auto index = this->bytecode[pc + 1];
        auto & aliases = libraryAliasStack.back();
        if (aliases.count(index)) {
          stack.push_back(aliases.at(index));
        }
        else {
          stack.push_back(make_shared<ComputedExpression>());
        }

        pc += 2;
      }
      break;
      case Opcode::FUNCTION: {
        EXECUTEPROGRAMCHECK(2);
        auto argc = this->bytecode[pc + 1];
        auto targetPc = this->bytecode[pc + 2];
        stack.push_back(make_shared<ComputedExpressionCompiledFunction>((uint32_t)argc, (integer_t)targetPc));
        pc += 3;
      }
      break;
      case Opcode::ASSIGNINDEX: {
        STACKCHECK(3);
        auto top = stack.size();
        auto & index = stack[top - 1];
        auto & collection = stack[top - 2];
        auto & value = stack[top - 3];
        stack[top - 3] = collection->__assign_index(index, value);
        stack.pop_back();
        stack.pop_back();
        ++pc;
      }
      break;
      case Opcode::ADD_SS: {
        BINARYOP_SS(lhs + rhs);
      }
      break;
      case Opcode::ADD_SI: {
        BINARYOP_SI(lhs + rhs);
      }
      break;
      case Opcode::ADD_IS: {
        BINARYOP_IS(lhs + rhs);
      }
      break;
      case Opcode::ADD_II: {
        BINARYOP_II(lhs + rhs);
      }
      break;
      case Opcode::SUBTRACT_SS: {
        BINARYOP_SS(lhs - rhs);
      }
      break;
      case Opcode::SUBTRACT_SI: {
        BINARYOP_SI(lhs - rhs);
      }
      break;
      case Opcode::SUBTRACT_IS: {
        BINARYOP_IS(lhs - rhs);
      }
      break;
      case Opcode::SUBTRACT_II: {
        BINARYOP_II(lhs - rhs);
      }
      break;
      case Opcode::MULTIPLY_SS: {
        BINARYOP_SS(lhs * rhs);
      }
      break;
      case Opcode::MULTIPLY_SI: {
        BINARYOP_SI(lhs * rhs);
      }
      break;
      case Opcode::MULTIPLY_IS: {
        BINARYOP_IS(lhs * rhs);
      }
      break;
      case Opcode::MULTIPLY_II: {
        BINARYOP_II(lhs * rhs);
      }
      break;
      case Opcode::DIVIDE_SS: {
        BINARYOP_SS(lhs / rhs);
      }
      break;
      case Opcode::DIVIDE_SI: {
        BINARYOP_SI(lhs / rhs);
      }
      break;
      case Opcode::DIVIDE_IS: {
        BINARYOP_IS(lhs / rhs);
      }
      break;
      case Opcode::DIVIDE_II: {
        BINARYOP_II(lhs / rhs);
      }
      break;
      case Opcode::MODULO_SS: {
        BINARYOP_SS(lhs % rhs);
      }
      break;
      case Opcode::MODULO_SI: {
        BINARYOP_SI(lhs % rhs);
      }
      break;
      case Opcode::MODULO_IS: {
        BINARYOP_IS(lhs % rhs);
      }
      break;
      case Opcode::MODULO_II: {
        BINARYOP_II(lhs % rhs);
      }
      break;
      case Opcode::NEGATIVE_S: {
        UNARYOP_S(-operand);
      }
      break;
      case Opcode::NEGATIVE_I: {
        UNARYOP_I(-operand);
      }
      break;
      case Opcode::NOT_S: {
        UNARYOP_S(!operand);
      }
      break;
      case Opcode::NOT_I: {
        UNARYOP_I(!operand);
      }
      break;
      case Opcode::LT_SS: {
        BINARYOP_SS(lhs < rhs);
      }
      break;
      case Opcode::LT_SI: {
        BINARYOP_SI(lhs < rhs);
      }
      break;
      case Opcode::LT_IS: {
        BINARYOP_IS(lhs < rhs);
      }
      break;
      case Opcode::LT_II: {
        BINARYOP_II(lhs < rhs);
      }
      break;
      case Opcode::LTE_SS: {
        BINARYOP_SS(lhs <= rhs);
      }
      break;
      case Opcode::LTE_SI: {
        BINARYOP_SI(lhs <= rhs);
      }
      break;
      case Opcode::LTE_IS: {
        BINARYOP_IS(lhs <= rhs);
      }
      break;
      case Opcode::LTE_II: {
        BINARYOP_II(lhs <= rhs);
      }
      break;
      case Opcode::GT_SS: {
        BINARYOP_SS(lhs > rhs);
      }
      break;
      case Opcode::GT_SI: {
        BINARYOP_SI(lhs > rhs);
      }
      break;
      case Opcode::GT_IS: {
        BINARYOP_IS(lhs > rhs);
      }
      break;
      case Opcode::GT_II: {
        BINARYOP_II(lhs > rhs);
      }
      break;
      case Opcode::GTE_SS: {
        BINARYOP_SS(lhs >= rhs);
      }
      break;
      case Opcode::GTE_SI: {
        BINARYOP_SI(lhs >= rhs);
      }
      break;
      case Opcode::GTE_IS: {
        BINARYOP_IS(lhs >= rhs);
      }
      break;
      case Opcode::GTE_II: {
        BINARYOP_II(lhs >= rhs);
      }
      break;
      case Opcode::EQ_SS: {
        BINARYOP_SS(lhs == rhs);
      }
      break;
      case Opcode::EQ_SI: {
        BINARYOP_SI(lhs == rhs);
      }
      break;
      case Opcode::EQ_IS: {
        BINARYOP_IS(lhs == rhs);
      }
      break;
      case Opcode::EQ_II: {
        BINARYOP_II(lhs == rhs);
      }
      break;
      case Opcode::NEQ_SS: {
        BINARYOP_SS(lhs != rhs);
      }
      break;
      case Opcode::NEQ_SI: {
        BINARYOP_SI(lhs != rhs);
      }
      break;
      case Opcode::NEQ_IS: {
        BINARYOP_IS(lhs != rhs);
      }
      break;
      case Opcode::NEQ_II: {
        BINARYOP_II(lhs != rhs);
      }
      break;
      case Opcode::PERIOD_SS: {
        // Can't use BINARYOP_SS because it will set the stack value too soon.
        STACKCHECK(2);
        auto top = stack.size();
        auto & rhs = stack[top - 1];
        auto & lhs = stack[top - 2];

        auto tmp = lhs->__period(rhs, this->tang);

        // Resolve any library attribute requests.
        // This could not be done earlier, because __period() does not have
        // access to the context object, which is needed by the library
        // attribute function.  So we clean up that part now.
        while (typeid(*tmp) == typeid(ComputedExpressionNativeLibraryFunction)) {
          tmp = static_cast<ComputedExpressionNativeLibraryFunction &>(*tmp).getFunction()(context);
        }

        // Set the target of a native bound function.
        // This could not be done earlier, because __period() does not have
        // access to the target object (lhs).  So we clean up that part now.
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }

        // Finally, push the result onto the stack.
        stack.pop_back();
        stack.back() = tmp;
        ++pc;
      }
      break;
      case Opcode::PERIOD_SI: {
        // Can't use BINARYOP_SI because it will set the stack value too soon.
        EXECUTEPROGRAMCHECK(1);
        auto rhsIndex = this->bytecode[pc + 1];
        STACKCHECK(rhsIndex);
        auto & rhs = stack[fp + rhsIndex];
        auto & lhs = stack.back();

        auto tmp = lhs->__period(rhs, this->tang);

        // Resolve any library attribute requests.
        // This could not be done earlier, because __period() does not have
        // access to the context object, which is needed by the library
        // attribute function.  So we clean up that part now.
        while (typeid(*tmp) == typeid(ComputedExpressionNativeLibraryFunction)) {
          tmp = static_cast<ComputedExpressionNativeLibraryFunction &>(*tmp).getFunction()(context);
        }

        // Set the target of a native bound function.
        // This could not be done earlier, because __period() does not have
        // access to the target object (lhs).  So we clean up that part now.
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }

        // Finally, push the result onto the stack.
        stack.back() = tmp;
        pc += 2;
      }
      break;
      case Opcode::PERIOD_IS: {
        // Can't use BINARYOP_IS because it will set the stack value too soon.
        EXECUTEPROGRAMCHECK(1);
        auto lhsIndex = this->bytecode[pc + 1];
        STACKCHECK(lhsIndex);
        auto & rhs = stack.back();
        auto & lhs = stack[fp + lhsIndex];

        auto tmp = lhs->__period(rhs, this->tang);

        // Resolve any library attribute requests.
        // This could not be done earlier, because __period() does not have
        // access to the context object, which is needed by the library
        // attribute function.  So we clean up that part now.
        while (typeid(*tmp) == typeid(ComputedExpressionNativeLibraryFunction)) {
          tmp = static_cast<ComputedExpressionNativeLibraryFunction &>(*tmp).getFunction()(context);
        }

        // Set the target of a native bound function.
        // This could not be done earlier, because __period() does not have
        // access to the target object (lhs).  So we clean up that part now.
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }

        // Finally, push the result onto the stack.
        stack.back() = tmp;
        pc += 2;
      }
      break;
      case Opcode::PERIOD_II: {
        // Can't use BINARYOP_II because it will set the stack value too soon.
        EXECUTEPROGRAMCHECK(2);
        auto lhsIndex = this->bytecode[pc + 1];
        auto rhsIndex = this->bytecode[pc + 2];
        STACKCHECK(lhsIndex);
        STACKCHECK(rhsIndex);
        auto & lhs = stack[fp + lhsIndex];
        auto & rhs = stack[fp + rhsIndex];

        auto tmp = lhs->__period(rhs, this->tang);

        // Resolve any library attribute requests.
        // This could not be done earlier, because __period() does not have
        // access to the context object, which is needed by the library
        // attribute function.  So we clean up that part now.
        while (typeid(*tmp) == typeid(ComputedExpressionNativeLibraryFunction)) {
          tmp = static_cast<ComputedExpressionNativeLibraryFunction &>(*tmp).getFunction()(context);
        }

        // Set the target of a native bound function.
        // This could not be done earlier, because __period() does not have
        // access to the target object (lhs).  So we clean up that part now.
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }

        // Finally, push the result onto the stack.
        stack.emplace_back(tmp);
        pc += 3;
      }
      break;
      case Opcode::INDEX_SS: {
        BINARYOP_SS(lhs->__index(rhs));
      }
      break;
      case Opcode::INDEX_SI: {
        BINARYOP_SI(lhs->__index(rhs));
      }
      break;
      case Opcode::INDEX_IS: {
        BINARYOP_IS(lhs->__index(rhs));
      }
      break;
      case Opcode::INDEX_II: {
        BINARYOP_II(lhs->__index(rhs));
      }
      break;
      case Opcode::SLICE: {
        STACKCHECK(4);
        auto skip = stack.back();
        stack.pop_back();
        auto end = stack.back();
        stack.pop_back();
        auto begin = stack.back();
        stack.pop_back();
        auto container = stack.back();
        stack.pop_back();
        stack.push_back(container->__slice(begin, end, skip));
        ++pc;
      }
      break;
      case Opcode::GETITERATOR_SI: {
        ITERATOROP_SI(operand->__getIterator(operand));
      }
      break;
      case Opcode::GETITERATOR_II: {
        ITERATOROP_II(operand->__getIterator(operand));
      }
      break;
      case Opcode::ITERATORNEXT_II: {
        ITERATOROP_II(operand->__iteratorNext());
      }
      break;
      case Opcode::ISITERATOREND_I: {
        UNARYOP_I(make_shared<ComputedExpressionBoolean>((typeid(*operand) == typeid(ComputedExpressionIteratorEnd)) || (typeid(*operand) == typeid(ComputedExpressionError))));
      }
      break;
      case Opcode::CASTINTEGER_S: {
        UNARYOP_S(operand->__integer());
      }
      break;
      case Opcode::CASTINTEGER_I: {
        UNARYOP_I(operand->__integer());
      }
      break;
      case Opcode::CASTFLOAT_S: {
        UNARYOP_S(operand->__float());
      }
      break;
      case Opcode::CASTFLOAT_I: {
        UNARYOP_I(operand->__float());
      }
      break;
      case Opcode::CASTBOOLEAN_S: {
        UNARYOP_S(operand->__boolean());
      }
      break;
      case Opcode::CASTBOOLEAN_I: {
        UNARYOP_I(operand->__boolean());
      }
      break;
      case Opcode::CASTSTRING_S: {
        UNARYOP_S(operand->__string());
      }
      break;
      case Opcode::CASTSTRING_I: {
        UNARYOP_I(operand->__string());
      }
      break;
      case Opcode::CALLFUNC: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto function = stack.back();
        stack.pop_back();
        auto argc = this->bytecode[pc + 1];
        STACKCHECK(argc);
        // Call the function.
        callFunc(function, argc, pc, fp, stack, pcStack, fpStack, this->bytecode, context, 2);
      }
      break;
      case Opcode::CALLFUNC_I: {
        EXECUTEPROGRAMCHECK(2);
        auto position = this->bytecode[pc + 2];
        STACKCHECK(position);
        auto & function = stack[fp + position];
        auto argc = this->bytecode[pc + 1];
        STACKCHECK(argc);

        // Call the function.
        callFunc(function, argc, pc, fp, stack, pcStack, fpStack, this->bytecode, context, 3);
      }
      break;
      case Opcode::RETURN: {
        EXECUTEPROGRAMCHECK(1);
        size_t pop = this->bytecode[pc + 1];
        STACKCHECK(pop + 1);

        // Save the top of the stack as the return value.
        auto returnVal = stack.back();

        // Remove the stack down to the fp + 1.
        for (size_t i = 0; i < pop; ++i) {
          stack.pop_back();
        }

        // Put the return value back on the stack.
        stack.back() = returnVal;

        // Restore the pc and fp.
        pc = pcStack.back();
        fp = fpStack.back();
        pcStack.pop_back();
        fpStack.pop_back();
      }
      break;
      case Opcode::PRINT_S: {
        STACKCHECK(1);
        auto & expression = stack.back();

        // Try to convert the expression to a string.
        auto result = expression->__string();
        if (typeid(*result) == typeid(ComputedExpressionString)) {
          // We know that both our private member and `result` are a
          // ComputedExpressionString, so combine them here.
          static_cast<ComputedExpressionString &>(*context.computedExpressionOut) += static_cast<ComputedExpressionString &>(*result);
          // Push an empty value onto the stack.
          stack.back() = make_shared<ComputedExpression>();
        }
        else if (typeid(*result) != typeid(ComputedExpressionError)) {
          // __string returned neither a string nor an error, so report that.
          stack.back() = make_shared<ComputedExpressionError>(Error{"Argument not recognized as a string or error type."});
        }
        else {
          // __string returned an error, pass that back to the stack.
          stack.back() = result;
        }

        ++pc;
      }
      break;
      case Opcode::PRINT_I: {
        EXECUTEPROGRAMCHECK(1);
        auto index = this->bytecode[pc + 1];
        STACKCHECK(index);
        auto & expression = stack[fp + index];

        // Try to convert the expression to a string.
        auto result = expression->__string();
        if (typeid(*result) == typeid(ComputedExpressionString)) {
          // We know that both our private member and `result` are a
          // ComputedExpressionString, so combine them here.
          static_cast<ComputedExpressionString &>(*context.computedExpressionOut) += static_cast<ComputedExpressionString &>(*result);
          // Push an empty value onto the stack.
          stack.emplace_back(make_shared<ComputedExpression>());
        }
        else if (typeid(*result) != typeid(ComputedExpressionError)) {
          // __string returned neither a string nor an error, so report that.
          stack.emplace_back(make_shared<ComputedExpressionError>(Error{"Argument not recognized as a string or error type."}));
        }
        else {
          // __string returned an error, pass that back to the stack.
          stack.emplace_back(result);
        }

        pc += 2;
      }
      break;
      default: {
        // We should never reach this.
        stack.emplace_back(make_shared<ComputedExpressionError>(Error{"Unrecognized Opcode."}));
        pc = this->bytecode.size();
      }
      break;
    }
  }

  // Verify that there is at least one value on the stack.  If not, set a
  // runtime error.
  if (!stack.size()) {
    stack.push_back(make_shared<ComputedExpressionError>(Error{"Stack is empty."}));
  }

  // Empty the stack, but save the top of the stack.
  context.result = stack.back();
  stack.clear();

  // Render the output to `out`.
  context.out = context.computedExpressionOut->dump();

  return context;
}

