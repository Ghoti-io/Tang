/**
 * @file
 * Define the Tang::Program::execute method.
 */

#include <bit>
#include "program.hpp"
#include "opcode.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"

using namespace std;
using namespace Tang;

/**
 * Verify the size of the Bytecode vector so that it may be safely accessed.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define EXECUTEPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) { \
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Opcode instruction truncated."})); \
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
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Insufficient stack depth."})); \
    pc = this->bytecode.size(); \
    break; \
  }

Program& Program::execute() {
  size_t pc{0};
  size_t fp{0};
  vector<GarbageCollected> stack;

  while (pc < this->bytecode.size()) {
    switch ((Opcode)this->bytecode[pc]) {
      case Opcode::INTEGER: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionInteger>((int64_t)this->bytecode[pc + 1]));
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionFloat>(bit_cast<double>(this->bytecode[pc + 1])));
        pc += 2;
        break;
      }
      case Opcode::ADD: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs + rhs);
        ++pc;
        break;
      }
      case Opcode::SUBTRACT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs - rhs);
        ++pc;
        break;
      }
      case Opcode::MULTIPLY: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs * rhs);
        ++pc;
        break;
      }
      case Opcode::DIVIDE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs / rhs);
        ++pc;
        break;
      }
      case Opcode::MODULO: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs % rhs);
        ++pc;
        break;
      }
      case Opcode::NEGATIVE: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(-operand);
        ++pc;
        break;
      }
      case Opcode::CASTINTEGER: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__integer());
        ++pc;
        break;
      }
      case Opcode::CASTFLOAT: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__float());
        ++pc;
        break;
      }
      default: {
        // We should never reach this.
        stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Unrecognized Opcode."}));
        pc = stack.size();
        break;
      }
    }
  }

  // Verify that there is at least one value on the stack.  If not, set a
  // runtime error.
  if (!stack.size()) {
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Stack is empty."}));
  }

  // Empty the stack, but save the top of the stack.
  this->result = stack.back();
  stack.clear();

  return *this;
}

