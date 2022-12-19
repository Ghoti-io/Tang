/**
 * @file
 * Define the Tang::Context class.
 */

#include "context.hpp"
#include "program.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

Context::Context() : computedExpressionOut{GarbageCollected::make<ComputedExpressionString>("")} {}

