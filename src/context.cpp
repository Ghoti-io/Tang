/**
 * @file
 * Define the Tang::Context class.
 */

#include "context.hpp"
#include "program.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

Context::Context(ContextData && data) : data{move(data)}, computedExpressionOut{GarbageCollected::make<ComputedExpressionString>("")} {}

