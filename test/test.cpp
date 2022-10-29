/**
 * @file
 *
 * Test the general language behaviors.
 */

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

TEST(Expression, Add) {
  auto p1 = TangBase().compileScript("3 + 5");
  EXPECT_EQ(*p1.execute().getResult(), 8);
  auto p2 = TangBase().compileScript("3. + 5");
  EXPECT_EQ(*p2.execute().getResult(), 8);
  auto p3 = TangBase().compileScript("3. + 5.");
  EXPECT_EQ(*p3.execute().getResult(), 8);
  auto p4 = TangBase().compileScript("3 + 5.");
  EXPECT_EQ(*p4.execute().getResult(), 8);
  auto p5 = TangBase().compileScript("3 + -5");
  EXPECT_EQ(*p5.execute().getResult(), -2);
  auto p6 = TangBase().compileScript("3.5 + 5");
  EXPECT_EQ(*p6.execute().getResult(), 8.5);
  auto p7 = TangBase().compileScript("3.25 + 5.25");
  EXPECT_EQ(*p7.execute().getResult(), 8.5);
  auto p8 = TangBase().compileScript("3 + 5.5");
  EXPECT_EQ(*p8.execute().getResult(), 8.5);
  auto p9 = TangBase().compileScript("3 + 3 + 5.5");
  EXPECT_EQ(*p9.execute().getResult(), 11.5);
}

TEST(Expression, Subtract) {
  auto p1 = TangBase().compileScript("3 - 5");
  EXPECT_EQ(*p1.execute().getResult(), -2);
  auto p2 = TangBase().compileScript("3. - 5");
  EXPECT_EQ(*p2.execute().getResult(), -2);
  auto p3 = TangBase().compileScript("3. - 5.");
  EXPECT_EQ(*p3.execute().getResult(), -2);
  auto p4 = TangBase().compileScript("3 - 5.");
  EXPECT_EQ(*p4.execute().getResult(), -2);
  auto p5 = TangBase().compileScript("3 - -5");
  EXPECT_EQ(*p5.execute().getResult(), 8);
  auto p6 = TangBase().compileScript("3.5 - 5");
  EXPECT_EQ(*p6.execute().getResult(), -1.5);
  auto p7 = TangBase().compileScript("3.75 - 5.25");
  EXPECT_EQ(*p7.execute().getResult(), -1.5);
  auto p8 = TangBase().compileScript("3 - 5.5");
  EXPECT_EQ(*p8.execute().getResult(), -2.5);
  auto p9 = TangBase().compileScript("3 - 3 - 5.5");
  EXPECT_EQ(*p9.execute().getResult(), -5.5);
}

TEST(Expression, Multiplication) {
  auto p1 = TangBase().compileScript("3 * 5");
  EXPECT_EQ(*p1.execute().getResult(), 15);
  auto p2 = TangBase().compileScript("3. * 5");
  EXPECT_EQ(*p2.execute().getResult(), 15);
  auto p3 = TangBase().compileScript("3. * 5.");
  EXPECT_EQ(*p3.execute().getResult(), 15);
  auto p4 = TangBase().compileScript("3 * 5.");
  EXPECT_EQ(*p4.execute().getResult(), 15);
  auto p5 = TangBase().compileScript("3 * -5");
  EXPECT_EQ(*p5.execute().getResult(), -15);
  auto p6 = TangBase().compileScript("3.5 * 5");
  EXPECT_EQ(*p6.execute().getResult(), 17.5);
  auto p7 = TangBase().compileScript("3.25 * 5.25");
  EXPECT_EQ(*p7.execute().getResult(), 17.0625);
  auto p8 = TangBase().compileScript("3 * 5.5");
  EXPECT_EQ(*p8.execute().getResult(), 16.5);
  auto p9 = TangBase().compileScript("3 * 3 * 5.5");
  EXPECT_EQ(*p9.execute().getResult(), 49.5);
  auto p10 = TangBase().compileScript("3 + 3 * 5.5");
  EXPECT_EQ(*p10.execute().getResult(), 19.5);
  auto p11 = TangBase().compileScript("3 * 3 + 5.5");
  EXPECT_EQ(*p11.execute().getResult(), 14.5);
}

TEST(Expression, Division) {
  auto p1 = TangBase().compileScript("3 / 5");
  EXPECT_EQ(*p1.execute().getResult(), 0);
  auto p2 = TangBase().compileScript("3. / 5");
  EXPECT_EQ(*p2.execute().getResult(), .6);
  auto p3 = TangBase().compileScript("3. / 5.");
  EXPECT_EQ(*p3.execute().getResult(), .6);
  auto p4 = TangBase().compileScript("3 / 5.");
  EXPECT_EQ(*p4.execute().getResult(), .6);
  auto p5 = TangBase().compileScript("3 / -5");
  EXPECT_EQ(*p5.execute().getResult(), 0);
  auto p6 = TangBase().compileScript("3.5 / 5");
  EXPECT_EQ(*p6.execute().getResult(), .7);
  auto p7 = TangBase().compileScript("1.5 / .1");
  EXPECT_EQ(*p7.execute().getResult(), 15);
  auto p8 = TangBase().compileScript("100 / .1");
  EXPECT_EQ(*p8.execute().getResult(), 1000);
  auto p9 = TangBase().compileScript("3 / 3 / 5.");
  EXPECT_EQ(*p9.execute().getResult(), .2);
  auto p10 = TangBase().compileScript("3 / 0");
  EXPECT_EQ(*p10.execute().getResult(), Error("Cannot divide by zero."));
  auto p11 = TangBase().compileScript("3. / 0");
  EXPECT_EQ(*p11.execute().getResult(), Error("Cannot divide by zero."));
  auto p12 = TangBase().compileScript("3 / 0.");
  EXPECT_EQ(*p12.execute().getResult(), Error("Cannot divide by zero."));
  auto p13 = TangBase().compileScript("3. / 0.");
  EXPECT_EQ(*p13.execute().getResult(), Error("Cannot divide by zero."));
}

TEST(Expression, Modulo) {
  auto p1 = TangBase().compileScript("3 + 5");
  EXPECT_EQ(*p1.execute().getResult(), 8);
  auto p2 = TangBase().compileScript("3. + 5");
  EXPECT_EQ(*p2.execute().getResult(), 8);
  auto p3 = TangBase().compileScript("3. + 5.");
  EXPECT_EQ(*p3.execute().getResult(), 8);
  auto p4 = TangBase().compileScript("3 + 5.");
  EXPECT_EQ(*p4.execute().getResult(), 8);
  auto p5 = TangBase().compileScript("3 + -5");
  EXPECT_EQ(*p5.execute().getResult(), -2);
  auto p6 = TangBase().compileScript("3.5 + 5");
  EXPECT_EQ(*p6.execute().getResult(), 8.5);
  auto p7 = TangBase().compileScript("3.25 + 5.25");
  EXPECT_EQ(*p7.execute().getResult(), 8.5);
  auto p8 = TangBase().compileScript("3 + 5.5");
  EXPECT_EQ(*p8.execute().getResult(), 8.5);
  auto p9 = TangBase().compileScript("3 + 3 + 5.5");
  EXPECT_EQ(*p9.execute().getResult(), 11.5);
  auto p10 = TangBase().compileScript("3 % 0");
  EXPECT_EQ(*p10.execute().getResult(), Error("Cannot modulo by zero."));
}

TEST(Expression, UnaryMinus) {
  auto p1 = TangBase().compileScript("3-5");
  EXPECT_EQ(*p1.execute().getResult(), -2);
  auto p2 = TangBase().compileScript("3--5");
  EXPECT_EQ(*p2.execute().getResult(), 8);
  auto p3 = TangBase().compileScript("-3.-5.");
  EXPECT_EQ(*p3.execute().getResult(), -8);
  auto p4 = TangBase().compileScript("-3--5.");
  EXPECT_EQ(*p4.execute().getResult(), 2);
  auto p5 = TangBase().compileScript("--5");
  EXPECT_EQ(*p5.execute().getResult(), 5);
  auto p6 = TangBase().compileScript("---5");
  EXPECT_EQ(*p6.execute().getResult(), -5);
  auto p7 = TangBase().compileScript("---3.75-----5.25");
  EXPECT_EQ(*p7.execute().getResult(), -9);
}

TEST(Expression, Parentheses) {
  auto p1 = TangBase().compileScript("(3-5)-1");
  EXPECT_EQ(*p1.execute().getResult(), -3);
  auto p2 = TangBase().compileScript("3-(5-1)");
  EXPECT_EQ(*p2.execute().getResult(), -1);
  auto p3 = TangBase().compileScript("((-(3.)))-(5.)");
  EXPECT_EQ(*p3.execute().getResult(), -8);
  auto p4 = TangBase().compileScript("(((((-3)))))");
  EXPECT_EQ(*p4.execute().getResult(), -3);
}

TEST(Expression, TypeCast) {
  auto p1 = TangBase().compileScript("3.5 as int");
  EXPECT_EQ(*p1.execute().getResult(), 3);
  auto p2 = TangBase().compileScript("7.5 as int / 2");
  EXPECT_EQ(*p2.execute().getResult(), 3);
  auto p3 = TangBase().compileScript("3 as float / 5");
  EXPECT_EQ(*p3.execute().getResult(), .6);
  auto p4 = TangBase().compileScript("7 / 5 as float");
  EXPECT_EQ(*p4.execute().getResult(), 1.4);
  auto p5 = TangBase().compileScript("(7 / 5) as float");
  EXPECT_EQ(*p5.execute().getResult(), 1);
  auto p6 = TangBase().compileScript("7 as int");
  EXPECT_EQ(*p6.execute().getResult(), 7);
  auto p7 = TangBase().compileScript("7.5 as float");
  EXPECT_EQ(*p7.execute().getResult(), 7.5);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

