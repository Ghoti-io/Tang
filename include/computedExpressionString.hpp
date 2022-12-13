/**
 * @file
 * Declare the Tang::ComputedExpressionString class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONSTRING_HPP
#define TANG_COMPUTEDEXPRESSIONSTRING_HPP

#include "macros.hpp"
#include "computedExpression.hpp"
#include "unicodeString.hpp"

namespace Tang {
  /**
   * Represents a String that is the result of a computation.
   */
  class ComputedExpressionString : public ComputedExpression {
    public:
      /**
       * Construct a String result.
       *
       * @param val The string value.
       */
      ComputedExpressionString(const std::string & val);

      /**
       * Construct a String result from a vector of UnicodeString objects.
       *
       * @param stringParts The vector of UnicodeString objects.
       */
      ComputedExpressionString(const std::vector<UnicodeString> & stringParts);

      virtual std::string dump() const override;
      virtual std::string __asCode() const override;
      GarbageCollected makeCopy() const override;
      virtual bool is_equal(const bool & val) const override;
      virtual bool is_equal(const string & val) const override;
      virtual GarbageCollected __index(const GarbageCollected & index) const override;
      virtual GarbageCollected __slice(const GarbageCollected & begin, const GarbageCollected & end, const GarbageCollected & skip) const override;
      virtual GarbageCollected __getIterator(const GarbageCollected & collection) const override;
      virtual GarbageCollected __iteratorNext(size_t index) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __not() const override;
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __boolean() const override;
      virtual GarbageCollected __string() const override;

      /**
       * Return the collection of string values that are stored in this object.
       *
       * @return The collection of string values.
       */
      const std::vector<UnicodeString>& getValue() const;

      /**
       * Return the number of graphemes contained in the string.
       *
       * @return The number of graphemes contained in the string.
       */
      size_t length() const;

      /**
       * Return the number of bytes required by the string, stored as UTF-8.
       *
       * @return The number of bytes required by the string, stored as UTF-8.
       */
      size_t bytesLength() const;

      /**
       * Return the member functions implemented for this particular
       * expression type.
       *
       * @return The member functions implemented.
       */
      static NativeBoundFunctionMap getMethods();

      /**
       * Helper function to copy the contents of the rhs string into the
       * current string.
       *
       * @param rhs The right hand side of the operation.
       * @return The result of the operation.
       */
      ComputedExpressionString & operator+=(const ComputedExpressionString &rhs);

    private:
      /**
       * The string value.
       */
      std::vector<UnicodeString> stringParts;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONSTRING_HPP

