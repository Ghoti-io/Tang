/**
 * @file
 * Declare the Tang::ComputedExpressionString class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONSTRING_HPP
#define TANG_COMPUTEDEXPRESSIONSTRING_HPP

#include <optional>
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
      SPCE makeCopy() const override;
      virtual bool is_equal(const bool & val) const override;
      virtual bool is_equal(const std::string & val) const override;
      virtual SPCE __index(const SPCE & index) const override;
      virtual SPCE __slice(const SPCE & begin, const SPCE & end, const SPCE & skip) const override;
      virtual SPCE __getIterator(const SPCE & collection) const override;
      virtual SPCE __iteratorNext(size_t index) const override;
      virtual SPCE __add(const SPCE & rhs) const override;
      virtual SPCE __not() const override;
      virtual SPCE __lessThan(const SPCE & rhs) const override;
      virtual SPCE __equal(const SPCE & rhs) const override;
      virtual SPCE __boolean() const override;
      virtual SPCE __string() const override;

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

      /**
       * Set all of the string parts to UnicodeString::Type::Untrusted.
       */
      void setUntrusted();

      /**
       * Set all of the string parts to UnicodeString::Type::Percent.
       */
      void setPercent();

    private:
      /**
       * The string value.
       */
      std::vector<UnicodeString> stringParts;

      /**
       * Cache of the string length in graphemes.
       */
      mutable std::optional<size_t> cachedLength;

      /**
       * Cache of the string length in bytes.
       */
      mutable std::optional<size_t> cachedBytesLength;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONSTRING_HPP

