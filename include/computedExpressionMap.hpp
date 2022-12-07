/**
 * @file
 * Declare the Tang::ComputedExpressionMap class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONMAP_HPP
#define TANG_COMPUTEDEXPRESSIONMAP_HPP

#include <map>
#include <string>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Map that is the result of a computation.
   */
  class ComputedExpressionMap : public ComputedExpression {
    public:
      /**
       * Construct an Map result.
       *
       * @param contents The map of key value pairs.
       */
      ComputedExpressionMap(std::map<std::string, Tang::GarbageCollected> contents);

      virtual std::string dump() const override;
      virtual bool isCopyNeeded() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __index(const GarbageCollected & index) const override;
      virtual GarbageCollected __getIterator(const GarbageCollected & collection) const override;
      virtual GarbageCollected __iteratorNext(size_t index) const override;
      virtual GarbageCollected __assign_index(const GarbageCollected & index, const GarbageCollected & value) override;
      virtual GarbageCollected __string() const override;
      virtual GarbageCollected __boolean() const override;

    private:
      /**
       * The map contents.
       */
      std::map<std::string, Tang::GarbageCollected> contents;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONMAP_HPP

