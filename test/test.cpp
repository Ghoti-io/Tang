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


TEST(Declare, Null) {
  auto p1 = TangBase().compileScript("null");
  EXPECT_EQ(*p1.execute().getResult(), nullptr);
}

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

TEST(Declare, Boolean) {
  auto p1 = TangBase().compileScript("true");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("false");
  EXPECT_EQ(*p2.execute().getResult(), false);
}

TEST(Declare, String) {
  auto p1 = TangBase().compileScript("\"\"");
  EXPECT_EQ(*p1.execute().getResult(), string(""));
  EXPECT_EQ(*p1.execute().getResult(), "");
  EXPECT_NE(*p1.execute().getResult(), nullptr);
  auto p2 = TangBase().compileScript("\"Hello World!\"");
  EXPECT_EQ(*p2.execute().getResult(), "Hello World!");
  EXPECT_NE(*p2.execute().getResult(), nullptr);
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
  auto p10 = TangBase().compileScript("\"Hello\" + \" \" + \"World!\"");
  EXPECT_EQ(*p10.execute().getResult(), "Hello World!");
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
  auto p8 = TangBase().compileScript("0 as bool");
  EXPECT_EQ(*p8.execute().getResult(), false);
  auto p9 = TangBase().compileScript("1 as bool");
  EXPECT_EQ(*p9.execute().getResult(), true);
  auto p10 = TangBase().compileScript("0. as bool");
  EXPECT_EQ(*p10.execute().getResult(), false);
  auto p11 = TangBase().compileScript("1. as bool");
  EXPECT_EQ(*p11.execute().getResult(), true);
  auto p12 = TangBase().compileScript(".5 as int as bool");
  EXPECT_EQ(*p12.execute().getResult(), false);
  auto p13 = TangBase().compileScript("1.5 as int as bool");
  EXPECT_EQ(*p13.execute().getResult(), true);
  auto p14 = TangBase().compileScript("true as int");
  EXPECT_EQ(*p14.execute().getResult(), 1);
  auto p15 = TangBase().compileScript("false as int");
  EXPECT_EQ(*p15.execute().getResult(), 0);
  auto p16 = TangBase().compileScript("true as float");
  EXPECT_EQ(*p16.execute().getResult(), 1.);
  auto p17 = TangBase().compileScript("false as float");
  EXPECT_EQ(*p17.execute().getResult(), 0.);
  auto p18 = TangBase().compileScript("true as bool");
  EXPECT_EQ(*p18.execute().getResult(), true);
  auto p19 = TangBase().compileScript("false as bool");
  EXPECT_EQ(*p19.execute().getResult(), false);
}

TEST(Expression, Not) {
  auto p1 = TangBase().compileScript("!true");
  EXPECT_EQ(*p1.execute().getResult(), false);
  auto p2 = TangBase().compileScript("!false");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("!3");
  EXPECT_EQ(*p3.execute().getResult(), false);
  auto p4 = TangBase().compileScript("!0");
  EXPECT_EQ(*p4.execute().getResult(), true);
  auto p5 = TangBase().compileScript("!3.");
  EXPECT_EQ(*p5.execute().getResult(), false);
  auto p6 = TangBase().compileScript("!0.");
  EXPECT_EQ(*p6.execute().getResult(), true);
  auto p7 = TangBase().compileScript("!-3");
  EXPECT_EQ(*p7.execute().getResult(), false);
}

TEST(Expression, LessThan) {
  auto p1 = TangBase().compileScript("2 < 3");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("2 < 2");
  EXPECT_EQ(*p2.execute().getResult(), false);
  auto p3 = TangBase().compileScript("2 < 1");
  EXPECT_EQ(*p3.execute().getResult(), false);
  auto p4 = TangBase().compileScript("2 < 3.");
  EXPECT_EQ(*p4.execute().getResult(), true);
  auto p5 = TangBase().compileScript("2 < 2.");
  EXPECT_EQ(*p5.execute().getResult(), false);
  auto p6 = TangBase().compileScript("2 < 1.");
  EXPECT_EQ(*p6.execute().getResult(), false);
  auto p7 = TangBase().compileScript("2. < 3");
  EXPECT_EQ(*p7.execute().getResult(), true);
  auto p8 = TangBase().compileScript("2. < 2");
  EXPECT_EQ(*p8.execute().getResult(), false);
  auto p9 = TangBase().compileScript("2. < 1");
  EXPECT_EQ(*p9.execute().getResult(), false);
  auto p10 = TangBase().compileScript("2. < 3.");
  EXPECT_EQ(*p10.execute().getResult(), true);
  auto p11 = TangBase().compileScript("2. < 2.");
  EXPECT_EQ(*p11.execute().getResult(), false);
  auto p12 = TangBase().compileScript("2. < 1.");
  EXPECT_EQ(*p12.execute().getResult(), false);
  auto p13 = TangBase().compileScript("2 < true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. < true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false < true");
  EXPECT_EQ(*p15.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p16 = TangBase().compileScript("\"a\" < \"b\"");
  EXPECT_EQ(*p16.execute().getResult(), true);
  auto p17 = TangBase().compileScript("\"b\" < \"a\"");
  EXPECT_EQ(*p17.execute().getResult(), false);
}

TEST(Expression, LessThanEqual) {
  auto p1 = TangBase().compileScript("2 <= 3");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("2 <= 2");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("2 <= 1");
  EXPECT_EQ(*p3.execute().getResult(), false);
  auto p4 = TangBase().compileScript("2 <= 3.");
  EXPECT_EQ(*p4.execute().getResult(), true);
  auto p5 = TangBase().compileScript("2 <= 2.");
  EXPECT_EQ(*p5.execute().getResult(), true);
  auto p6 = TangBase().compileScript("2 <= 1.");
  EXPECT_EQ(*p6.execute().getResult(), false);
  auto p7 = TangBase().compileScript("2. <= 3");
  EXPECT_EQ(*p7.execute().getResult(), true);
  auto p8 = TangBase().compileScript("2. <= 2");
  EXPECT_EQ(*p8.execute().getResult(), true);
  auto p9 = TangBase().compileScript("2. <= 1");
  EXPECT_EQ(*p9.execute().getResult(), false);
  auto p10 = TangBase().compileScript("2. <= 3.");
  EXPECT_EQ(*p10.execute().getResult(), true);
  auto p11 = TangBase().compileScript("2. <= 2.");
  EXPECT_EQ(*p11.execute().getResult(), true);
  auto p12 = TangBase().compileScript("2. <= 1.");
  EXPECT_EQ(*p12.execute().getResult(), false);
  auto p13 = TangBase().compileScript("2 <= true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. <= true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false <= true");
  EXPECT_EQ(*p15.execute().getResult(), Error{"Don't know how to compare these values."});
}

TEST(Expression, GreaterThan) {
  auto p1 = TangBase().compileScript("2 > 3");
  EXPECT_EQ(*p1.execute().getResult(), false);
  auto p2 = TangBase().compileScript("2 > 2");
  EXPECT_EQ(*p2.execute().getResult(), false);
  auto p3 = TangBase().compileScript("2 > 1");
  EXPECT_EQ(*p3.execute().getResult(), true);
  auto p4 = TangBase().compileScript("2 > 3.");
  EXPECT_EQ(*p4.execute().getResult(), false);
  auto p5 = TangBase().compileScript("2 > 2.");
  EXPECT_EQ(*p5.execute().getResult(), false);
  auto p6 = TangBase().compileScript("2 > 1.");
  EXPECT_EQ(*p6.execute().getResult(), true);
  auto p7 = TangBase().compileScript("2. > 3");
  EXPECT_EQ(*p7.execute().getResult(), false);
  auto p8 = TangBase().compileScript("2. > 2");
  EXPECT_EQ(*p8.execute().getResult(), false);
  auto p9 = TangBase().compileScript("2. > 1");
  EXPECT_EQ(*p9.execute().getResult(), true);
  auto p10 = TangBase().compileScript("2. > 3.");
  EXPECT_EQ(*p10.execute().getResult(), false);
  auto p11 = TangBase().compileScript("2. > 2.");
  EXPECT_EQ(*p11.execute().getResult(), false);
  auto p12 = TangBase().compileScript("2. > 1.");
  EXPECT_EQ(*p12.execute().getResult(), true);
  auto p13 = TangBase().compileScript("2 > true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. > true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false > true");
  EXPECT_EQ(*p15.execute().getResult(), Error{"Don't know how to compare these values."});
}

TEST(Expression, GreaterThanEqual) {
  auto p1 = TangBase().compileScript("2 >= 3");
  EXPECT_EQ(*p1.execute().getResult(), false);
  auto p2 = TangBase().compileScript("2 >= 2");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("2 >= 1");
  EXPECT_EQ(*p3.execute().getResult(), true);
  auto p4 = TangBase().compileScript("2 >= 3.");
  EXPECT_EQ(*p4.execute().getResult(), false);
  auto p5 = TangBase().compileScript("2 >= 2.");
  EXPECT_EQ(*p5.execute().getResult(), true);
  auto p6 = TangBase().compileScript("2 >= 1.");
  EXPECT_EQ(*p6.execute().getResult(), true);
  auto p7 = TangBase().compileScript("2. >= 3");
  EXPECT_EQ(*p7.execute().getResult(), false);
  auto p8 = TangBase().compileScript("2. >= 2");
  EXPECT_EQ(*p8.execute().getResult(), true);
  auto p9 = TangBase().compileScript("2. >= 1");
  EXPECT_EQ(*p9.execute().getResult(), true);
  auto p10 = TangBase().compileScript("2. >= 3.");
  EXPECT_EQ(*p10.execute().getResult(), false);
  auto p11 = TangBase().compileScript("2. >= 2.");
  EXPECT_EQ(*p11.execute().getResult(), true);
  auto p12 = TangBase().compileScript("2. >= 1.");
  EXPECT_EQ(*p12.execute().getResult(), true);
  auto p13 = TangBase().compileScript("2 >= true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. >= true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false >= true");
  EXPECT_EQ(*p15.execute().getResult(), Error{"Don't know how to compare these values."});
}

TEST(Expression, Equal) {
  auto p1 = TangBase().compileScript("2 == 3");
  EXPECT_EQ(*p1.execute().getResult(), false);
  auto p2 = TangBase().compileScript("2 == 2");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("2 == 1");
  EXPECT_EQ(*p3.execute().getResult(), false);
  auto p4 = TangBase().compileScript("2 == 3.");
  EXPECT_EQ(*p4.execute().getResult(), false);
  auto p5 = TangBase().compileScript("2 == 2.");
  EXPECT_EQ(*p5.execute().getResult(), true);
  auto p6 = TangBase().compileScript("2 == 1.");
  EXPECT_EQ(*p6.execute().getResult(), false);
  auto p7 = TangBase().compileScript("2. == 3");
  EXPECT_EQ(*p7.execute().getResult(), false);
  auto p8 = TangBase().compileScript("2. == 2");
  EXPECT_EQ(*p8.execute().getResult(), true);
  auto p9 = TangBase().compileScript("2. == 1");
  EXPECT_EQ(*p9.execute().getResult(), false);
  auto p10 = TangBase().compileScript("2. == 3.");
  EXPECT_EQ(*p10.execute().getResult(), false);
  auto p11 = TangBase().compileScript("2. == 2.");
  EXPECT_EQ(*p11.execute().getResult(), true);
  auto p12 = TangBase().compileScript("2. == 1.");
  EXPECT_EQ(*p12.execute().getResult(), false);
  auto p13 = TangBase().compileScript("2 == true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. == true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false == true");
  EXPECT_EQ(*p15.execute().getResult(), false);
  auto p16 = TangBase().compileScript("true == true");
  EXPECT_EQ(*p16.execute().getResult(), true);
  auto p17 = TangBase().compileScript("false == false");
  EXPECT_EQ(*p17.execute().getResult(), true);
  auto p18 = TangBase().compileScript("null == null");
  EXPECT_EQ(*p18.execute().getResult(), true);
  auto p19 = TangBase().compileScript("null == 0");
  EXPECT_EQ(*p19.execute().getResult(), false);
  auto p20 = TangBase().compileScript("0 == null");
  EXPECT_EQ(*p20.execute().getResult(), false);
  auto p21 = TangBase().compileScript("0. == null");
  EXPECT_EQ(*p21.execute().getResult(), false);
  auto p22 = TangBase().compileScript("false == null");
  EXPECT_EQ(*p22.execute().getResult(), false);
  auto p23 = TangBase().compileScript("\"a\" == \"b\"");
  EXPECT_EQ(*p23.execute().getResult(), false);
  auto p24 = TangBase().compileScript("\"a\" == \"a\"");
  EXPECT_EQ(*p24.execute().getResult(), true);
}

TEST(Expression, NotEqual) {
  auto p1 = TangBase().compileScript("2 != 3");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("2 != 2");
  EXPECT_EQ(*p2.execute().getResult(), false);
  auto p3 = TangBase().compileScript("2 != 1");
  EXPECT_EQ(*p3.execute().getResult(), true);
  auto p4 = TangBase().compileScript("2 != 3.");
  EXPECT_EQ(*p4.execute().getResult(), true);
  auto p5 = TangBase().compileScript("2 != 2.");
  EXPECT_EQ(*p5.execute().getResult(), false);
  auto p6 = TangBase().compileScript("2 != 1.");
  EXPECT_EQ(*p6.execute().getResult(), true);
  auto p7 = TangBase().compileScript("2. != 3");
  EXPECT_EQ(*p7.execute().getResult(), true);
  auto p8 = TangBase().compileScript("2. != 2");
  EXPECT_EQ(*p8.execute().getResult(), false);
  auto p9 = TangBase().compileScript("2. != 1");
  EXPECT_EQ(*p9.execute().getResult(), true);
  auto p10 = TangBase().compileScript("2. != 3.");
  EXPECT_EQ(*p10.execute().getResult(), true);
  auto p11 = TangBase().compileScript("2. != 2.");
  EXPECT_EQ(*p11.execute().getResult(), false);
  auto p12 = TangBase().compileScript("2. != 1.");
  EXPECT_EQ(*p12.execute().getResult(), true);
  auto p13 = TangBase().compileScript("2 != true");
  EXPECT_EQ(*p13.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p14 = TangBase().compileScript("2. != true");
  EXPECT_EQ(*p14.execute().getResult(), Error{"Don't know how to compare these values."});
  auto p15 = TangBase().compileScript("false != true");
  EXPECT_EQ(*p15.execute().getResult(), true);
}

TEST(Expression, And) {
  auto p1 = TangBase().compileScript("true && true");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("true && false");
  EXPECT_EQ(*p2.execute().getResult(), false);
  auto p3 = TangBase().compileScript("false && true");
  EXPECT_EQ(*p3.execute().getResult(), false);
  auto p4 = TangBase().compileScript("false && false");
  EXPECT_EQ(*p4.execute().getResult(), false);
  auto p5 = TangBase().compileScript("(a = 0) && (a = 2); a;");
  EXPECT_EQ(*p5.execute().getResult(), 0);
  auto p6 = TangBase().compileScript("(a = 1) && (a = 2); a;");
  EXPECT_EQ(*p6.execute().getResult(), 2);
  auto p7 = TangBase().compileScript("(a = 0.) && (a = 2.); a;");
  EXPECT_EQ(*p7.execute().getResult(), 0.);
  auto p8 = TangBase().compileScript("(a = 1.) && (a = 2.); a;");
  EXPECT_EQ(*p8.execute().getResult(), 2.);
  auto p9 = TangBase().compileScript("(a = \"\") && (a = \"foo\"); a;");
  EXPECT_EQ(*p9.execute().getResult(), "");
  auto p10 = TangBase().compileScript("(a = \"foo\") && (a = \"bar\"); a;");
  EXPECT_EQ(*p10.execute().getResult(), "bar");
  auto p11 = TangBase().compileScript("(a = null) && (a = 2.); a;");
  EXPECT_EQ(*p11.execute().getResult(), nullptr);
  auto p12 = TangBase().compileScript("(a = true) && (a = null); a;");
  EXPECT_EQ(*p12.execute().getResult(), nullptr);
}

TEST(Expression, Or) {
  auto p1 = TangBase().compileScript("true || true");
  EXPECT_EQ(*p1.execute().getResult(), true);
  auto p2 = TangBase().compileScript("true || false");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("false || true");
  EXPECT_EQ(*p3.execute().getResult(), true);
  auto p4 = TangBase().compileScript("false || false");
  EXPECT_EQ(*p4.execute().getResult(), false);
  auto p5 = TangBase().compileScript("(a = 0) || (a = 2); a;");
  EXPECT_EQ(*p5.execute().getResult(), 2);
  auto p6 = TangBase().compileScript("(a = 1) || (a = 2); a;");
  EXPECT_EQ(*p6.execute().getResult(), 1);
  auto p7 = TangBase().compileScript("(a = 0.) || (a = 2.); a;");
  EXPECT_EQ(*p7.execute().getResult(), 2.);
  auto p8 = TangBase().compileScript("(a = 1.) || (a = 2.); a;");
  EXPECT_EQ(*p8.execute().getResult(), 1.);
  auto p9 = TangBase().compileScript("(a = \"\") || (a = \"foo\"); a;");
  EXPECT_EQ(*p9.execute().getResult(), "foo");
  auto p10 = TangBase().compileScript("(a = \"foo\") || (a = \"bar\"); a;");
  EXPECT_EQ(*p10.execute().getResult(), "foo");
  auto p11 = TangBase().compileScript("(a = null) || (a = 2.); a;");
  EXPECT_EQ(*p11.execute().getResult(), 2.);
  auto p12 = TangBase().compileScript("(a = true) || (a = null); a;");
  EXPECT_EQ(*p12.execute().getResult(), true);
}

TEST(Expression, Ternary) {
  auto p1 = TangBase().compileScript("true ? 3 : 5");
  EXPECT_EQ(*p1.execute().getResult(), 3);
  auto p2 = TangBase().compileScript("false ? 3 : 5");
  EXPECT_EQ(*p2.execute().getResult(), 5);
  auto p3 = TangBase().compileScript("false ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p3.execute().getResult(), 5);
  auto p4 = TangBase().compileScript("false ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p4.execute().getResult(), 5);
  auto p5 = TangBase().compileScript("true ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p5.execute().getResult(), 1);
  auto p6 = TangBase().compileScript("true ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p6.execute().getResult(), 3);
  auto p7 = TangBase().compileScript("false ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p7.execute().getResult(), 3);
  auto p8 = TangBase().compileScript("false ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p8.execute().getResult(), 5);
  auto p9 = TangBase().compileScript("true ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p9.execute().getResult(), 1);
  auto p10 = TangBase().compileScript("true ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p10.execute().getResult(), 1);
}

TEST(CodeBlock, Statements) {
  auto p1 = TangBase().compileScript("2;");
  EXPECT_EQ(*p1.execute().getResult(), 2);
  auto p2 = TangBase().compileScript("2; true;");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("2; ((1 + 2.3 + 3) < -7) == true; 42;");
  EXPECT_EQ(*p3.execute().getResult(), 42);
}

TEST(Assign, Identifier) {
  auto p1 = TangBase().compileScript("a = 1; a;");
  EXPECT_EQ(*p1.execute().getResult(), 1);
  auto p2 = TangBase().compileScript("a = false; !a;");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("a = b = 1; a = a + b; a;");
  EXPECT_EQ(*p3.execute().getResult(), 2);
}

TEST(ControlFlow, IfElse) {
  auto p1 = TangBase().compileScript("a = 1; if (true) a = 2; a;");
  EXPECT_EQ(*p1.execute().getResult(), 2);
  auto p2 = TangBase().compileScript("a = 1; if (true) a = 2; else a = 3; a;");
  EXPECT_EQ(*p2.execute().getResult(), 2);
  auto p3 = TangBase().compileScript("a = 1; if (false) a = 2; a;");
  EXPECT_EQ(*p3.execute().getResult(), 1);
  auto p4 = TangBase().compileScript("a = 1; if (false) a = 2; else a = 3; a;");
  EXPECT_EQ(*p4.execute().getResult(), 3);
  auto p5 = TangBase().compileScript("a = 1; if (true) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p5.execute().getResult(), 3);
  auto p6 = TangBase().compileScript("a = 1; if (true) {b = 3; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p6.execute().getResult(), 4);
  auto p7 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p7.execute().getResult(), 1);
  auto p8 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p8.execute().getResult(), 4);
  auto p9 = TangBase().compileScript("a = 1; if (true) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p9.execute().getResult(), 2);
  auto p10 = TangBase().compileScript("a = 1; if (false) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p10.execute().getResult(), 4);
  auto p11 = TangBase().compileScript("a = 1; if (true) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p11.execute().getResult(), 3);
  auto p12 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p12.execute().getResult(), 4);
  auto p13 = TangBase().compileScript("a = 1; if (true) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p13.execute().getResult(), 3);
  auto p14 = TangBase().compileScript("a = 1; if (true) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p14.execute().getResult(), 4);
  auto p15 = TangBase().compileScript("a = 1; if (false) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p15.execute().getResult(), 1);
  auto p16 = TangBase().compileScript("a = 1; if (false) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p16.execute().getResult(), 1);
  auto p17 = TangBase().compileScript("a = 1; b = 2; if (a != b) a = 3; a;");
  EXPECT_EQ(*p17.execute().getResult(), 3);
  auto p18 = TangBase().compileScript("a = 1; b = 2; if (a == b) a = 3; a;");
  EXPECT_EQ(*p18.execute().getResult(), 1);
}

TEST(ControlFlow, While) {
  auto p1 = TangBase().compileScript("a = 1; while (a < 10) b = a = a + 1; b;");
  EXPECT_EQ(*p1.execute().getResult(), 10);
  auto p2 = TangBase().compileScript("a = 1; while (a < 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p2.execute().getResult(), 10);
  auto p3 = TangBase().compileScript("a = 1; while (a > 10) b = a = a + 1; b;");
  EXPECT_EQ(*p3.execute().getResult(), nullptr);
  auto p4 = TangBase().compileScript("a = 1; while (a > 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p4.execute().getResult(), nullptr);
  auto p5 = TangBase().compileScript("a = 1; while ((a = a + 1) < 10) {} b;");
  EXPECT_EQ(*p5.execute().getResult(), nullptr);
}

TEST(ControlFlow, DoWhile) {
  auto p1 = TangBase().compileScript("a = 1; do b = a = a + 1; while (a < 10); b;");
  EXPECT_EQ(*p1.execute().getResult(), 10);
  auto p2 = TangBase().compileScript("a = 1; do {a = a + 1; b = a;} while (a < 10); b;");
  EXPECT_EQ(*p2.execute().getResult(), 10);
  auto p3 = TangBase().compileScript("a = 1; do b = a = a + 1; while (a > 10); b;");
  EXPECT_EQ(*p3.execute().getResult(), 2);
  auto p4 = TangBase().compileScript("a = 1; do {a = a + 1; b = a;} while (a > 10); b;");
  EXPECT_EQ(*p4.execute().getResult(), 2);
}

TEST(ControlFlow, For) {
  auto p1 = TangBase().compileScript(R"(
    a = "";
    for (i = 0; i < 10; i = i + 1) {
      a = a + "-";
    }
    a;
  )");
  EXPECT_EQ(*p1.execute().getResult(), "----------");
  auto p2 = TangBase().compileScript(R"(
    a = "";
    for (i = 0; i < 3; i = i + 1)
      a = a + "-";
    a;
  )");
  EXPECT_EQ(*p2.execute().getResult(), "---");
  auto p3 = TangBase().compileScript(R"(
    a = "";
    i = 0;
    for (; i < 3;) {
      a = a + "-";
      i = i + 1;
    }
    a;
  )");
  EXPECT_EQ(*p3.execute().getResult(), "---");
  auto p4 = TangBase().compileScript(R"(
    for (i = 0; i > 10; i = i + 1) {
      a = "-";
    }
    a;
  )");
  EXPECT_EQ(*p4.execute().getResult(), nullptr);
  auto p5 = TangBase().compileScript(R"(
    for (i = 0; i > 10; i = i + 1)
      a = "-";
    a;
  )");
  EXPECT_EQ(*p5.execute().getResult(), nullptr);
  auto p6 = TangBase().compileScript(R"(
    a = 0;
    for (i = 0; i < 10; i = i + 1)
      for (j = 0; j < 10; j = j + 1)
        a = a + 1;
    a;
  )");
  EXPECT_EQ(*p6.execute().getResult(), 100);
}

TEST(Print, Default) {
  auto p1 = TangBase().compileScript("print(\"\");");
  EXPECT_EQ(p1.out, "");
  EXPECT_EQ(p1.execute().out, "");
  auto p2 = TangBase().compileScript("print(\"Hello World!\");");
  EXPECT_EQ(p2.out, "");
  EXPECT_EQ(p2.execute().out, "Hello World!");
  EXPECT_EQ(p2.out, "Hello World!");
  auto p3 = TangBase().compileScript("print(3);");
  EXPECT_EQ(p3.execute().out, "3");
  auto p4 = TangBase().compileScript("print(3.);");
  EXPECT_EQ(p4.execute().out, "3.000000");
  auto p5 = TangBase().compileScript("print(true);");
  EXPECT_EQ(p5.execute().out, "");
  auto p6 = TangBase().compileScript("print(false);");
  EXPECT_EQ(p6.execute().out, "");
  auto p7 = TangBase().compileScript("print(null);");
  EXPECT_EQ(p7.execute().out, "");
  auto p8 = TangBase().compileScript("a = \"Hi\"; print(a);");
  EXPECT_EQ(p8.execute().out, "Hi");
  auto p9 = TangBase().compileScript("print(3 + 5);");
  EXPECT_EQ(p9.execute().out, "8");
  auto p10 = TangBase().compileScript("print(3 + null);");
  EXPECT_EQ(*p10.execute().getResult(), Error{"Don't know how to add these values."});
  auto p11 = TangBase().compileScript(R"(
    for (i = 0; i < 10; i = i + 1) {
      print("-");
    }
  )");
  EXPECT_EQ(p11.execute().out, "----------");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

