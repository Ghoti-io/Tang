/**
 * @file
 * Define the Tang::AstNodeRangedFor class.
 */

#include <string>
#include <sstream>
#include <bit>
#include "astNodeRangedFor.hpp"
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

  // Compile the Collection expression.
  this->collection->compile(program);

  // Call the GETITERATOR opcode.
  program.addBytecode((uinteger_t)Opcode::GETITERATOR);

  // Save to Iterator variable.
  auto & identifier = program.getIdentifiers();
  program.addBytecode((uinteger_t)Opcode::POKE);
  program.addBytecode((uinteger_t)identifier.at(this->iteratorVariableName));

  // Call ITERATORNEXT
  auto callIteratorNext = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::ITERATORNEXT);

  // Assign top of stack to Target variable.
  program.addBytecode((uinteger_t)Opcode::POKE);
  program.addBytecode((uinteger_t)identifier.at(this->target->name));

  // If Target variable is IteratorEnd, exit loop.
  program.addBytecode((uinteger_t)Opcode::ISITERATOREND);
  auto isIteratorEndJump = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMPT_POP);
  program.addBytecode((uinteger_t)0);

  // Compile the code block and clean up the stack afterwards.
  this->codeBlock->compile(program);
  program.addBytecode((uinteger_t)Opcode::POP);

  // Push Iterator variable onto stack.
  auto loadIterator = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::PEEK);
  program.addBytecode((uinteger_t)identifier.at(this->iteratorVariableName));

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
  program.popContinueStack(loadIterator);
}

void AstNodeRangedFor::compilePreprocess(Program & program, PreprocessState state) const {
  program.addIdentifier(this->iteratorVariableName);
  program.addIdentifierAssigned(this->iteratorVariableName);
  this->target->compilePreprocess(program, state);
  this->collection->compilePreprocess(program, state);
  this->codeBlock->compilePreprocess(program, state);
}

