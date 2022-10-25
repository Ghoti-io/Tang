#include <gtest/gtest.h>
#include <iostream>
#include "tang.hpp"

using namespace std;
using namespace Tang;

TEST(Integer, Integer) {
  auto p1 = TangBase().compileScript("3");
  EXPECT_EQ(*p1.execute().getResult(), 3);
  auto p2 = TangBase().compileScript("42");
  EXPECT_EQ(*p2.execute().getResult(), 42);
  auto p3 = TangBase().compileScript("-42");
  EXPECT_EQ(*p3.execute().getResult(), -42);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

