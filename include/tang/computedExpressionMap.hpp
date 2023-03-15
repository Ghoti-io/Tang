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
      ComputedExpressionMap(std::map<std::string, Tang::SPCE> contents);

      virtual std::string dump() const override;
      virtual bool isCopyNeeded() const override;
      SPCE makeCopy() const override;
      virtual SPCE __index(const SPCE & index) const override;
      virtual SPCE __getIterator(const SPCE & collection) const override;
      virtual SPCE __iteratorNext(size_t index) const override;
      virtual SPCE __assign_index(const SPCE & index, const SPCE & value) override;
      virtual SPCE __string() const override;
      virtual SPCE __boolean() const override;

    private:
      /**
       * The map contents.
       */
      std::map<std::string, Tang::SPCE> contents;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONMAP_HPP

