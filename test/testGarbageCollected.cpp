#include <gtest/gtest.h>
#include "garbageCollected.hpp"
#include "computedExpression.hpp"

using namespace std;
using namespace Tang;

TEST(Create, Access) {
  GarbageCollected<ComputedExpressionInteger> g{3};
  EXPECT_EQ(g->dump(), "3");
  EXPECT_EQ((*g).dump(), "3");
}

TEST(RuleOfFive, CopyConstructor) {
  GarbageCollected<ComputedExpressionInteger> g1{3};
  auto g2{g1};
  EXPECT_EQ(g1->dump(), "3");
  EXPECT_EQ(g2->dump(), "3");
  EXPECT_EQ(&*g1, &*g2);
}

TEST(Recycle, ObjectIsRecycled) {
  ComputedExpressionInteger * p{nullptr};
  {
    GarbageCollected<ComputedExpressionInteger> g1{3};
    p = &*g1;
  }
  GarbageCollected<ComputedExpressionInteger> g2{5};
  EXPECT_EQ(p, &*g2);
}

TEST(Recycle, ObjectIsNotRecycled) {
  ComputedExpressionInteger * p1{nullptr};
  ComputedExpressionInteger * p2{nullptr};
  ComputedExpressionInteger * p3{nullptr};
  GarbageCollected<ComputedExpressionInteger> g1{3};
  p1 = &*g1;
  {
    auto g2{g1};
    p2 = &*g2;
  }
  GarbageCollected<ComputedExpressionInteger> g3{8};
  p3 = &*g3;
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

