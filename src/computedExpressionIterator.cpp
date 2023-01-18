/**
 * @file
 * Define the Tang::ComputedExpressionIterator class.
 */

#include <sstream>
#include "computedExpressionIterator.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionIterator::ComputedExpressionIterator(SPCE collection) : collection{collection}, index{0} {}

string ComputedExpressionIterator::dump() const {
  return (stringstream{} << "Iterator (" << this->index << ")").str();
}

SPCE ComputedExpressionIterator::__iteratorNext([[maybe_unused]] size_t index) const {
  return this->collection->__iteratorNext(this->index++);
}

