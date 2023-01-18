/**
 * @file
 * Declare the Tang::ComputedExpressionNativeBoundFunction class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP
#define TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP

#include <optional>
#include <typeindex>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a NativeBound Function declared in the script.
   */
  class ComputedExpressionNativeBoundFunction : public ComputedExpression {
    public:
      /**
       * Construct an NativeBoundFunction.
       *
       * The object itself is designed to be safe in that, once it is
       * constructed, the method function pointer, argument count, and target
       * type cannot be changed, but can only be accessible through a getter.
       *
       * The target value that the function is bound to, however, cannot be set
       * when the object is created, due to the design of the compiler.  It is
       * therefore exposed, regardless of being made public or via a setter
       * function.
       *
       * The current design of the VM will set the correct target, but because
       * the target is exposed, it is possible that some bad actor could modify
       * it.  It is therefore necessary to verify that the type of the bound
       * object and the type that was known when this object is created are, in
       * fact, the same.  That is why we store the target object type
       * information and protect it behind a getter function.
       *
       * When the VM executes the bound method, it will perform a type check to
       * verify that the bound object is of the same type as that of the method
       * that is defined in TangBase::getObjectMethods().
       *
       * It should be safe, then, to assume that within a NativeBoundFunction,
       * the type is the expected type.  No ComputedExpression type, then,
       * should "steal" a NativeBoundFunction from another ComputedExpression
       * definition, as it is assumed that the bound target that is provided
       * to any NativeBoundFunction is the same as the type on which it was
       * originally defined.
       *
       * For example, a NativeBoundFunction declared in
       * ComputedExpressionString may assume that the bound target is also a
       * ComputedExpressionString.  If another class, such as
       * ComputedExpressionArray, were to try to copy the NativeBoundFunction
       * (as a pointer reference), the function will still expect that the
       * bound target is a ComputedExpressionString, and will probably cause
       * a segmentation fault.  Just don't do it.
       *
       * @param nativeBoundFunction The native bound function to be executed.
       * @param argc The count of arguments that this function expects.
       * @param targetTypeIndex The type of the value to which the function is
       *   bound.
       */
      ComputedExpressionNativeBoundFunction(NativeBoundFunction nativeBoundFunction, size_t argc, std::type_index targetTypeIndex);

      virtual std::string dump() const override;
      SPCE makeCopy() const override;
      virtual SPCE __equal(const SPCE & rhs) const override;

      /**
       * The target object that the function is bound to.
       */
      std::optional<SPCE> target;

      /**
       * Get the native bound function to be executed.
       *
       * @return The native bound function to be executed.
       */
      NativeBoundFunction getFunction() const;

      /**
       * Get the count of arguments that this function expects.
       *
       * @return The count of arguments that this function expects.
       */
      size_t getArgc() const;

      /**
       * Get the type of the value to which the function is bound.
       *
       * @return The type of the value to which the function is bound.
       */
      const std::type_index & getTargetTypeIndex() const;

    private:
      /**
       * The native bound function to be executed.
       */
      NativeBoundFunction nativeBoundFunction;

      /**
       * The count of arguments that this function expects.
       */
      size_t argc;

      /**
       * The type of the value to which the function is bound.
       */
      std::type_index targetTypeIndex;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP

