#include <gtest/gtest.h>
#include "garbageCollected.hpp"
#include "computedExpression.hpp"
#include "computedExpressionInteger.hpp"

using namespace std;
using namespace Tang;

TEST(Create, Access) {
  auto g = GarbageCollected::make<ComputedExpressionInteger>(3);
  EXPECT_EQ(g->dump(), "3");
  EXPECT_EQ((*g).dump(), "3");
}

TEST(RuleOfFive, CopyConstructor) {
  auto g1 = GarbageCollected::make<ComputedExpressionInteger>(3);
  auto g2{g1};
  EXPECT_EQ(g1->dump(), "3");
  EXPECT_EQ(g2->dump(), "3");
  EXPECT_EQ(&*g1, &*g2);
}

TEST(Recycle, ObjectIsRecycled) {
  ComputedExpression * p{nullptr};
  {
    auto g1 = GarbageCollected::make<ComputedExpressionInteger>(3);
    p = &*g1;
  }
  auto g2 = GarbageCollected::make<ComputedExpressionInteger>(5);
  EXPECT_EQ(p, &*g2);
}

TEST(Recycle, ObjectIsNotRecycled) {
  ComputedExpression * p1{nullptr};
  ComputedExpression * p2{nullptr};
  ComputedExpression * p3{nullptr};
  auto g1 = GarbageCollected::make<ComputedExpressionInteger>(3);
  p1 = &*g1;
  {
    auto g2{g1};
    p2 = &*g2;
  }
  auto g3 = GarbageCollected::make<ComputedExpressionInteger>(8);
  p3 = &*g3;
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

