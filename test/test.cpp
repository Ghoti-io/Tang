#include <gtest/gtest.h>
#include <iostream>
#include "tang.hpp"

using namespace std;
using namespace Tang;

TEST(Declare, Integer) {
  auto p1 = TangBase().compileScript("3");
  EXPECT_EQ(*p1.execute().getResult(), 3);
  auto p2 = TangBase().compileScript("42");
  EXPECT_EQ(*p2.execute().getResult(), 42);
  auto p3 = TangBase().compileScript("-42");
  EXPECT_EQ(*p3.execute().getResult(), -42);
  auto p4 = TangBase().compileScript("-42");
  EXPECT_EQ(*p4.execute().getResult(), -42.0);
  auto p5 = TangBase().compileScript("-42");
  EXPECT_NE(*p5.execute().getResult(), -42.5);
}

TEST(Declare, Float) {
  auto p1 = TangBase().compileScript("3.");
  EXPECT_EQ(*p1.execute().getResult(), 3.);
  auto p2 = TangBase().compileScript("4.2");
  EXPECT_EQ(*p2.execute().getResult(), 4.2);
  auto p3 = TangBase().compileScript("-4.2");
  EXPECT_EQ(*p3.execute().getResult(), -4.2);
  auto p4 = TangBase().compileScript(".2");
  EXPECT_EQ(*p4.execute().getResult(), .2);
  auto p5 = TangBase().compileScript("0.");
  EXPECT_EQ(*p5.execute().getResult(), 0.);
  auto p6 = TangBase().compileScript(".0");
  EXPECT_EQ(*p6.execute().getResult(), 0.);
  auto p7 = TangBase().compileScript("3.0");
  EXPECT_EQ(*p7.execute().getResult(), 3);
  auto p8 = TangBase().compileScript("3.5");
  EXPECT_NE(*p8.execute().getResult(), 3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

