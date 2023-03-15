/**
 * @file
 * Declare the Tang::ComputedExpressionIterator class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONITERATOR_HPP
#define TANG_COMPUTEDEXPRESSIONITERATOR_HPP

#include <vector>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Iterator that is the result of a computation.
   */
  class ComputedExpressionIterator : public ComputedExpression {
    public:
      /**
       * Construct an Iterator result.
       *
       * @param collection The collection through which the iterator processes
       */
      ComputedExpressionIterator(Tang::SPCE collection);

      virtual std::string dump() const override;
      virtual SPCE __iteratorNext(size_t index) const override;

    private:
      /**
       * The target collection.
       */
      Tang::SPCE collection;

      /**
       * The next index.
       */
      mutable size_t index;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONITERATOR_HPP

