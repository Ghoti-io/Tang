/**
 * @file
 * Declare the Tang::ComputedExpressionArray class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONARRAY_HPP
#define TANG_COMPUTEDEXPRESSIONARRAY_HPP

#include <vector>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Array that is the result of a computation.
   */
  class ComputedExpressionArray : public ComputedExpression {
    public:
      /**
       * Construct an Array result.
       *
       * @param val The integer value.
       */
      ComputedExpressionArray(std::vector<Tang::SPCE> contents);

      virtual std::string dump() const override;
      virtual bool isCopyNeeded() const override;
      SPCE makeCopy() const override;
      virtual SPCE __index(const SPCE & index) const override;
      virtual SPCE __slice(const SPCE & begin, const SPCE & end, const SPCE & skip) const override;
      virtual SPCE __getIterator(const SPCE & collection) const override;
      virtual SPCE __iteratorNext(size_t index) const override;
      virtual SPCE __assign_index(const SPCE & index, const SPCE & value) override;
      virtual SPCE __string() const override;

      /**
       * Return the contents of this object.
       *
       * @return The contents of this object.
       */
      const std::vector<Tang::SPCE> & getContents() const;

      /**
       * Append an item to the contents of this array object.
       *
       * @param item The value to append to the this array.
       */
      void append(const Tang::SPCE & item);

      /**
       * Return the member functions implemented for this particular
       * expression type.
       *
       * @return The member functions implemented.
       */
      static NativeBoundFunctionMap getMethods();

    private:
      /**
       * The array contents.
       */
      std::vector<Tang::SPCE> contents;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONARRAY_HPP

