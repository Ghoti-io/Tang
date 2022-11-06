/**
 * @file
 * Define the Tang::Program::execute method.
 */

#include <bit>
#include <cmath>
#include "program.hpp"
#include "opcode.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"

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
      case Opcode::POP: {
        STACKCHECK(1);
        stack.pop_back();
        ++pc;
        break;
      }
      case Opcode::PEEK: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack.push_back(stack[fp + position]);
        pc += 2;
        break;
      }
      case Opcode::POKE: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack[fp + position] = stack.back();
        pc += 2;
        break;
      }
      case Opcode::JMP: {
        EXECUTEPROGRAMCHECK(1);
        pc = this->bytecode[pc + 1];
        break;
      }
      case Opcode::JMPF_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        stack.pop_back();
        if (condition == false) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::JMPT_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        stack.pop_back();
        if (condition == true) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::NULLVAL: {
        stack.push_back(GarbageCollected::make<ComputedExpression>());
        ++pc;
        break;
      }
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
      case Opcode::BOOLEAN: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionBoolean>(this->bytecode[pc + 1] ? true : false));
        pc += 2;
        break;
      }
      case Opcode::STRING: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[pc + 1];
        auto bytes = ceil((double)size / sizeof(uint64_t));
        EXECUTEPROGRAMCHECK(1 + bytes);
        // Construct the string.
        string temp{};
        for (size_t i = 0; i < bytes; ++i) {
          for (size_t j = 0; j < sizeof(uint64_t); ++j) {
            if (((i * 8) + j) < size) {
              temp += (unsigned char)((this->bytecode[pc + 2 + i] >> (8 * (7 - j))) & 0xFF);
            }
          }
        }
        stack.push_back(GarbageCollected::make<ComputedExpressionString>(temp));
        pc += bytes + 2;
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
      case Opcode::NOT: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(!operand);
        ++pc;
        break;
      }
      case Opcode::LT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs < rhs);
        ++pc;
        break;
      }
      case Opcode::LTE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs <= rhs);
        ++pc;
        break;
      }
      case Opcode::GT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs > rhs);
        ++pc;
        break;
      }
      case Opcode::GTE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs >= rhs);
        ++pc;
        break;
      }
      case Opcode::EQ: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs == rhs);
        ++pc;
        break;
      }
      case Opcode::NEQ: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs != rhs);
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
      case Opcode::CASTBOOLEAN: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__boolean());
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

