/**
 * @file
 * Declare the Tang::AstNodeString class.
 */

#ifndef TANG_ASTNODESTRING_HPP
#define TANG_ASTNODESTRING_HPP

#include "astNode.hpp"
#include "unicodeString.hpp"

namespace Tang {
  /**
   * An AstNode that represents a string literal.
   */
  class AstNodeString : public AstNode {
  public:
    /**
     * Construct a Trusted string.
     *
     * @param text The string to represent.
     * @param location The location associated with the expression.
     */
    AstNodeString(const std::string & text, Tang::location location);

    /**
     * Construct a string that is either Trusted or Untrusted.
     *
     * @param text The string to represent.
     * @param type The UnicodeString::Type that the string should be considered.
     * @param location The location associated with the expression.
     */
    AstNodeString(const std::string & text, UnicodeString::Type type, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

    /**
     * Compile the string and push it onto the stack.
     *
     * @param program The Program which will hold the generated Bytecode.
     */
    void compileLiteral(Tang::Program & program) const;

    /**
     * Get the string value that this AST node represents.
     *
     * @return The string value that this AST node represents.
     */
    const std::string & getVal() const;

    /**
     * Get the type of string that this AST node represents.
     *
     * @return The type of string that this AST node represents.
     */
    const UnicodeString::Type & getType() const;

  private:
    /**
     * The string value being stored.
     */
    std::string val;

    /**
     * The UnicodeString::Type that the string should be considered.
     */
    UnicodeString::Type type;
  };
}

#endif // TANG_ASTNODESTRING_HPP

