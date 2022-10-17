#ifndef TANG_PROGRAM_HPP
#define TANG_PROGRAM_HPP

#include <string>
#include <optional>
#include "ast.hpp"
#include "error.hpp"

namespace Tang {
  class Program {
  public:
    enum CodeType {
      Script,
      Template
    };

    Program(std::string code, CodeType codeType);

    std::string getCode() const;
    std::optional<const AstNode *> getAst() const;
    void execute();
    std::string out;
  private:
    void compile();
    std::string code;
    CodeType codeType;
    AstNode * ast;
    Error * error;
  };
}

#endif // TANG_PROGRAM_HPP

