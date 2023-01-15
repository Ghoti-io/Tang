/**
 * @file
 * Define the Tang::AstNodeRangedFor class.
 */

#include <string>
#include <sstream>
#include <bit>
#include "astNodeIdentifier.hpp"
#include "astNodeRangedFor.hpp"
#include "astNodeString.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeRangedFor::AstNodeRangedFor(shared_ptr<AstNodeIdentifier> target, shared_ptr<AstNode> collection, shared_ptr<AstNode> codeBlock, Tang::location location) : AstNode(location), target{target}, collection{collection}, codeBlock{codeBlock} {
  this->iteratorVariableName = (stringstream{} << (uintptr_t)this).str();
}

string AstNodeRangedFor::dump(string indent) const {
  return indent + "Ranged For:"
    + indent + "  Target:\n"
    + this->target->dump(indent + "    ")
    + indent + "  Collection:\n"
    + this->collection->dump(indent + "    ")
    + indent + "  Code Block:\n"
    + this->codeBlock->dump(indent + "    ");
}

void AstNodeRangedFor::compile(Tang::Program & program) const {
  // Start new environments for `break` and `continue` statements.
  program.pushBreakStack();
  program.pushContinueStack();

  // Save the iterator's stack index position and the target variable's stack
  // position so that we can access them directly.
  auto & identifier = program.getIdentifiers();
  uinteger_t iteratorIndex = (uinteger_t)identifier.at(this->iteratorVariableName);
  uinteger_t targetIndex = (uinteger_t)identifier.at(this->target->name);

  // Call the correct GETITERATOR opcode.
  // Note: we are using UNARYOP, even though this bytecode has an an additional
  // index location provided.  The additional index location is not treated the
  // same as in a BINARYOP or UNARYOP, but UNARYOP is the closest, so we will
  // reuse its functionality here.
  UNARYOP(this->collection, GETITERATOR_SI, GETITERATOR_II);
  program.addBytecode(iteratorIndex);

  // Call ITERATORNEXT
  auto callIteratorNext = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::ITERATORNEXT_II);
  program.addBytecode(iteratorIndex);
  program.addBytecode(targetIndex);

  // If Target variable is IteratorEnd, exit loop.
  program.addBytecode((uinteger_t)Opcode::ISITERATOREND_I);
  program.addBytecode(targetIndex);
  auto isIteratorEndJump = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMPT_POP);
  program.addBytecode((uinteger_t)0);

  // Compile the code block and clean up the stack afterwards.
  this->codeBlock->compile(program);
  program.addBytecode((uinteger_t)Opcode::POP);

  // GOTO "Call ITERATORNEXT".
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode((uinteger_t)callIteratorNext);

  // Leave something on the stack.  It may be optimized away later.
  program.addBytecode((uinteger_t)Opcode::NULLVAL);

  // We now know where the code after the for() statement will be.
  // The parent will add a POP instruction, so account for that by using "+ 1".
  program.setJumpTarget(isIteratorEndJump, program.getBytecode().size() + 1);

  // We now know where a `break` statement should jump to.
  // The parent will add a POP instruction, so account for that by using "+ 1".
  program.popBreakStack(program.getBytecode().size() + 1);

  // We now know where a `continue` statement should jump to.
  program.popContinueStack(callIteratorNext);
}

void AstNodeRangedFor::compilePreprocess(Program & program, PreprocessState state) const {
  program.addIdentifier(this->iteratorVariableName);
  program.addIdentifierAssigned(this->iteratorVariableName);
  this->target->compilePreprocess(program, state);
  this->collection->compilePreprocess(program, state);
  this->codeBlock->compilePreprocess(program, state);
}

