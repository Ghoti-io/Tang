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
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)3);
  auto p2 = TangBase().compileScript("42");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)42);
  auto p3 = TangBase().compileScript("-42");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)-42);
  auto p4 = TangBase().compileScript("-42");
  EXPECT_EQ(*p4.execute().getResult(), (float_t)-42.0);
  auto p5 = TangBase().compileScript("-42");
  EXPECT_NE(*p5.execute().getResult(), (float_t)-42.5);
}

TEST(Declare, Float) {
  auto p1 = TangBase().compileScript("3.");
  EXPECT_EQ(*p1.execute().getResult(), (float_t)3.);
  auto p2 = TangBase().compileScript("4.2");
  EXPECT_EQ(*p2.execute().getResult(), (float_t)4.2);
  auto p3 = TangBase().compileScript("-4.2");
  EXPECT_EQ(*p3.execute().getResult(), (float_t)-4.2);
  auto p4 = TangBase().compileScript(".2");
  EXPECT_EQ(*p4.execute().getResult(), (float_t).2);
  auto p5 = TangBase().compileScript("0.");
  EXPECT_EQ(*p5.execute().getResult(), (float_t)0.);
  auto p6 = TangBase().compileScript(".0");
  EXPECT_EQ(*p6.execute().getResult(), (float_t)0.);
  auto p7 = TangBase().compileScript("3.0");
  EXPECT_EQ(*p7.execute().getResult(), (integer_t)3);
  auto p8 = TangBase().compileScript("3.5");
  EXPECT_NE(*p8.execute().getResult(), (integer_t)3);
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
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)8);
  auto p2 = TangBase().compileScript("3. + 5");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)8);
  auto p3 = TangBase().compileScript("3. + 5.");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)8);
  auto p4 = TangBase().compileScript("3 + 5.");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)8);
  auto p5 = TangBase().compileScript("3 + -5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)-2);
  auto p6 = TangBase().compileScript("3.5 + 5");
  EXPECT_EQ(*p6.execute().getResult(), (float_t)8.5);
  auto p7 = TangBase().compileScript("3.25 + 5.25");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)8.5);
  auto p8 = TangBase().compileScript("3 + 5.5");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)8.5);
  auto p9 = TangBase().compileScript("3 + 3 + 5.5");
  EXPECT_EQ(*p9.execute().getResult(), (float_t)11.5);
  auto p10 = TangBase().compileScript("\"Hello\" + \" \" + \"World!\"");
  EXPECT_EQ(*p10.execute().getResult(), "Hello World!");
}

TEST(Expression, Subtract) {
  auto p1 = TangBase().compileScript("3 - 5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)-2);
  auto p2 = TangBase().compileScript("3. - 5");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)-2);
  auto p3 = TangBase().compileScript("3. - 5.");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)-2);
  auto p4 = TangBase().compileScript("3 - 5.");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)-2);
  auto p5 = TangBase().compileScript("3 - -5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)8);
  auto p6 = TangBase().compileScript("3.5 - 5");
  EXPECT_EQ(*p6.execute().getResult(), (float_t)-1.5);
  auto p7 = TangBase().compileScript("3.75 - 5.25");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)-1.5);
  auto p8 = TangBase().compileScript("3 - 5.5");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)-2.5);
  auto p9 = TangBase().compileScript("3 - 3 - 5.5");
  EXPECT_EQ(*p9.execute().getResult(), (float_t)-5.5);
}

TEST(Expression, Multiplication) {
  auto p1 = TangBase().compileScript("3 * 5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)15);
  auto p2 = TangBase().compileScript("3. * 5");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)15);
  auto p3 = TangBase().compileScript("3. * 5.");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)15);
  auto p4 = TangBase().compileScript("3 * 5.");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)15);
  auto p5 = TangBase().compileScript("3 * -5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)-15);
  auto p6 = TangBase().compileScript("3.5 * 5");
  EXPECT_EQ(*p6.execute().getResult(), (float_t)17.5);
  auto p7 = TangBase().compileScript("3.25 * 5.25");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)17.0625);
  auto p8 = TangBase().compileScript("3 * 5.5");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)16.5);
  auto p9 = TangBase().compileScript("3 * 3 * 5.5");
  EXPECT_EQ(*p9.execute().getResult(), (float_t)49.5);
  auto p10 = TangBase().compileScript("3 + 3 * 5.5");
  EXPECT_EQ(*p10.execute().getResult(), (float_t)19.5);
  auto p11 = TangBase().compileScript("3 * 3 + 5.5");
  EXPECT_EQ(*p11.execute().getResult(), (float_t)14.5);
}

TEST(Expression, Division) {
  auto p1 = TangBase().compileScript("3 / 5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)0);
  auto p2 = TangBase().compileScript("3. / 5");
  EXPECT_EQ(*p2.execute().getResult(), (float_t).6);
  auto p3 = TangBase().compileScript("3. / 5.");
  EXPECT_EQ(*p3.execute().getResult(), (float_t).6);
  auto p4 = TangBase().compileScript("3 / 5.");
  EXPECT_EQ(*p4.execute().getResult(), (float_t).6);
  auto p5 = TangBase().compileScript("3 / -5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)0);
  auto p6 = TangBase().compileScript("3.5 / 5");
  EXPECT_EQ(*p6.execute().getResult(), (float_t).7);
  auto p7 = TangBase().compileScript("1.5 / .1");
  EXPECT_EQ(*p7.execute().getResult(), (integer_t)15);
  auto p8 = TangBase().compileScript("100 / .1");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)1000.);
  auto p9 = TangBase().compileScript("3 / 3 / 5.");
  EXPECT_EQ(*p9.execute().getResult(), (float_t).2);
  auto p10 = TangBase().compileScript("3 / 0.");
  EXPECT_EQ(*p10.execute().getResult(), Error("Cannot divide by zero."));
  auto p11 = TangBase().compileScript("3. / 0.");
  EXPECT_EQ(*p11.execute().getResult(), Error("Cannot divide by zero."));
  auto p12 = TangBase().compileScript("3 / 0.");
  EXPECT_EQ(*p12.execute().getResult(), Error("Cannot divide by zero."));
  auto p13 = TangBase().compileScript("3. / 0.");
  EXPECT_EQ(*p13.execute().getResult(), Error("Cannot divide by zero."));
}

TEST(Expression, Modulo) {
  auto p1 = TangBase().compileScript("3 % 5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)3);
  auto p2 = TangBase().compileScript("3. % 5");
  EXPECT_EQ(*p2.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p3 = TangBase().compileScript("3. % 5.");
  EXPECT_EQ(*p3.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p4 = TangBase().compileScript("3 % 5.");
  EXPECT_EQ(*p4.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p5 = TangBase().compileScript("3 % -5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)3);
  auto p6 = TangBase().compileScript("3.5 % 5");
  EXPECT_EQ(*p6.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p7 = TangBase().compileScript("3.25 % 5.25");
  EXPECT_EQ(*p7.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p8 = TangBase().compileScript("3 % 5.5");
  EXPECT_EQ(*p8.execute().getResult(), Error{"Don't know how to modulo these values."});
  auto p9 = TangBase().compileScript("13 % 7 % 5");
  EXPECT_EQ(*p9.execute().getResult(), 1);
  auto p10 = TangBase().compileScript("3 % 0");
  EXPECT_EQ(*p10.execute().getResult(), Error("Cannot modulo by zero."));
}

TEST(Expression, UnaryMinus) {
  auto p1 = TangBase().compileScript("3-5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)-2);
  auto p2 = TangBase().compileScript("3--5");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)8);
  auto p3 = TangBase().compileScript("-3.-5.");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)-8);
  auto p4 = TangBase().compileScript("-3--5.");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)2);
  auto p5 = TangBase().compileScript("--5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)5);
  auto p6 = TangBase().compileScript("---5");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)-5);
  auto p7 = TangBase().compileScript("---3.75-----5.25");
  EXPECT_EQ(*p7.execute().getResult(), (integer_t)-9);
}

TEST(Expression, Parentheses) {
  auto p1 = TangBase().compileScript("(3-5)-1");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)-3);
  auto p2 = TangBase().compileScript("3-(5-1)");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)-1);
  auto p3 = TangBase().compileScript("((-(3.)))-(5.)");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)-8);
  auto p4 = TangBase().compileScript("(((((-3.)))))");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)-3);
}

TEST(Expression, TypeCast) {
  auto p1 = TangBase().compileScript("3.5 as int");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)3);
  auto p2 = TangBase().compileScript("7.5 as int / 2");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)3);
  auto p3 = TangBase().compileScript("3 as float / 5");
  EXPECT_EQ(*p3.execute().getResult(), (float_t).6);
  auto p4 = TangBase().compileScript("7 / 5 as float");
  EXPECT_EQ(*p4.execute().getResult(), (float_t)1.4);
  auto p5 = TangBase().compileScript("(7 / 5) as float");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)1);
  auto p6 = TangBase().compileScript("7 as int");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)7);
  auto p7 = TangBase().compileScript("7.5 as float");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)7.5);
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
  EXPECT_EQ(*p14.execute().getResult(), (integer_t)1);
  auto p15 = TangBase().compileScript("false as int");
  EXPECT_EQ(*p15.execute().getResult(), (integer_t)0);
  auto p16 = TangBase().compileScript("true as float");
  EXPECT_EQ(*p16.execute().getResult(), (float_t)1.);
  auto p17 = TangBase().compileScript("false as float");
  EXPECT_EQ(*p17.execute().getResult(), (float_t)0.);
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
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)0);
  auto p6 = TangBase().compileScript("(a = 1) && (a = 2); a;");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)2);
  auto p7 = TangBase().compileScript("(a = 0.) && (a = 2.); a;");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)0.);
  auto p8 = TangBase().compileScript("(a = 1.) && (a = 2.); a;");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)2.);
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
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)2);
  auto p6 = TangBase().compileScript("(a = 1) || (a = 2); a;");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)1);
  auto p7 = TangBase().compileScript("(a = 0.) || (a = 2.); a;");
  EXPECT_EQ(*p7.execute().getResult(), (float_t)2.);
  auto p8 = TangBase().compileScript("(a = 1.) || (a = 2.); a;");
  EXPECT_EQ(*p8.execute().getResult(), (float_t)1.);
  auto p9 = TangBase().compileScript("(a = \"\") || (a = \"foo\"); a;");
  EXPECT_EQ(*p9.execute().getResult(), "foo");
  auto p10 = TangBase().compileScript("(a = \"foo\") || (a = \"bar\"); a;");
  EXPECT_EQ(*p10.execute().getResult(), "foo");
  auto p11 = TangBase().compileScript("(a = null) || (a = 2.); a;");
  EXPECT_EQ(*p11.execute().getResult(), (float_t)2.);
  auto p12 = TangBase().compileScript("(a = true) || (a = null); a;");
  EXPECT_EQ(*p12.execute().getResult(), true);
}

TEST(Expression, Ternary) {
  auto p1 = TangBase().compileScript("true ? 3 : 5");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)3);
  auto p2 = TangBase().compileScript("false ? 3 : 5");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)5);
  auto p3 = TangBase().compileScript("false ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)5);
  auto p4 = TangBase().compileScript("false ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)5);
  auto p5 = TangBase().compileScript("true ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)1);
  auto p6 = TangBase().compileScript("true ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)3);
  auto p7 = TangBase().compileScript("false ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p7.execute().getResult(), (integer_t)3);
  auto p8 = TangBase().compileScript("false ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p8.execute().getResult(), (integer_t)5);
  auto p9 = TangBase().compileScript("true ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p9.execute().getResult(), (integer_t)1);
  auto p10 = TangBase().compileScript("true ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p10.execute().getResult(), (integer_t)1);
}

TEST(Expression, StringIndex) {
  {
    // Tests positive and negative indexes.
    auto p1 = TangBase().compileScript(R"(
      a = "abc";
      print(a[2]);
      print(a[1]);
      print(a[0]);
      print(a[-3]);
      print(a[-2]);
      print(a[-1]);
    )");
    EXPECT_EQ(p1.execute().out, "cbaabc");
  }
  {
    // Tests positive and negative indexes with multi-codepoint content.
    // The 3 code points are: `.`, the Scottish Flag, and `$`
    auto p1 = TangBase().compileScript(R"(
      a = "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.";
      print(a[2]);
      print(a[1]);
      print(a[0]);
      print(a[-3]);
      print(a[-2]);
      print(a[-1]);
    )");
    EXPECT_EQ(p1.execute().out, ".\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF$$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
  }
  {
    // Index out of range
    auto p1 = TangBase().compileScript(R"(
      "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[-4]
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Index out of range."});
  }
  {
    // Index out of range
    auto p1 = TangBase().compileScript(R"(
      "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[3]
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Index out of range."});
  }
  {
    // Printing when index out of range
    auto p1 = TangBase().compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[3]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
}

TEST(Expression, StringSlice) {
  {
    // Slice with all default values.
    // Will create a copy of the string.
    auto p1 = TangBase().compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[::]);
    )");
    EXPECT_EQ(p1.execute().out, "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
  }
  {
    // Slice with default begin and end, but -1 skip.
    // Will reverse the string, keeping multi-codepoints in the correct order.
    auto p1 = TangBase().compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[::-1]);
    )");
    EXPECT_EQ(p1.execute().out, ".\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF$");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::1]);
    )");
    EXPECT_EQ(p1.execute().out, "abcdefghijklmnopqrstuvwxyz");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::2]);
    )");
    EXPECT_EQ(p1.execute().out, "acegikmoqsuwy");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[1::2]);
    )");
    EXPECT_EQ(p1.execute().out, "bdfhjlnprtvxz");
  }
  {
    // Slice with a positive value and non-default begin & end.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[1:17:2]);
    )");
    EXPECT_EQ(p1.execute().out, "bdfhjlnp");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::-1]);
    )");
    EXPECT_EQ(p1.execute().out, "zyxwvutsrqponmlkjihgfedcba");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::-2]);
    )");
    EXPECT_EQ(p1.execute().out, "zxvtrpnljhfdb");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-2::-2]);
    )");
    EXPECT_EQ(p1.execute().out, "ywusqomkigeca");
  }
  {
    // Slice with a negative value and non-default begin & end.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-1:-17:-2]);
    )");
    EXPECT_EQ(p1.execute().out, "zxvtrpnl");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-300:300]);
    )");
    EXPECT_EQ(p1.execute().out, "abcdefghijklmnopqrstuvwxyz");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[300:-300]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array,
    // but reversed.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[300:-300:-1]);
    )");
    EXPECT_EQ(p1.execute().out, "zyxwvutsrqponmlkjihgfedcba");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-300:300:-1]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::0]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0, should return error.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::0]);
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Don't know how to slice this expression."});
  }
  {
    // Double slice, proof of concept.
    auto p1 = TangBase().compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::2][-3::-1]);
    )");
    EXPECT_EQ(p1.execute().out, "usqomkigeca");
  }
}

TEST(Expression, ArrayIndex) {
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[1]);
    )");
    EXPECT_EQ(p1.execute().out, "2");
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "3");
  }
  {
    auto p1 = TangBase().compileScript(R"(
      [1,2,3][1]
    )");
    EXPECT_EQ(*p1.execute().getResult(), 2);
  }
  {
    auto p1 = TangBase().compileScript(R"(
      [1,2,3][4]
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Index out of range."});
  }
  {
    auto p1 = TangBase().compileScript(R"(
      [1,2,3][-1]
    )");
    EXPECT_EQ(*p1.execute().getResult(), 3);
  }
  {
    auto p1 = TangBase().compileScript(R"(
      [1,2,3][-3]
    )");
    EXPECT_EQ(*p1.execute().getResult(), 1);
  }
  {
    auto p1 = TangBase().compileScript(R"(
      [1,2,3][-4]
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Index out of range."});
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,"a",1.5];
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "1a1.500000");
  }
}

TEST(CodeBlock, Statements) {
  auto p1 = TangBase().compileScript("2;");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)2);
  auto p2 = TangBase().compileScript("2; true;");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("2; ((1 + 2.3 + 3) < -7) == true; 42;");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)42);
}

TEST(Assign, Identifier) {
  auto p1 = TangBase().compileScript("a = 1; a;");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)1);
  auto p2 = TangBase().compileScript("a = false; !a;");
  EXPECT_EQ(*p2.execute().getResult(), true);
  auto p3 = TangBase().compileScript("a = b = 1; a = a + b; a;");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)2);
}

TEST(Assign, Index) {
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      a[4] = "foo";
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Index out of range."});
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[0]);
      print(a[1]);
      print(a[2]);
      a[1] = "foo";
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "1231foo3");
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[0]);
      print(a[1]);
      print(a[2]);
      a[4] = "foo";
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "123123");
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[0]);
      print(a[1]);
      print(a[2]);
      a[-3] = "foo";
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "123foo23");
  }
  {
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      print(a[0]);
      print(a[1]);
      print(a[2]);
      a[-1] = "foo";
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "12312foo");
  }
}

TEST(Expression, ArraySlice) {
  {
    // Slice with all default values.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3][::];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3]");
  }
  {
    // Slice with default begin and end, but -1 skip.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3][::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[3,2,1]");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3,4,5,6,7,8,9]");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,3,5,7,9]");
  }
  {
    // Slice with a positive value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][1::2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[2,4,6,8]");
  }
  {
    // Slice with a positive value and non-default begin & end.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][1:7:2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[2,4,6]");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,8,7,6,5,4,3,2,1]");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,7,5,3,1]");
  }
  {
    // Slice with a negative value.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-2::-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[8,6,4,2]");
  }
  {
    // Slice with a negative value and non-default begin & end.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-1:-7:-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,7,5]");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-300:300:1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3,4,5,6,7,8,9]");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][300:-300:1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array,
    // but reversed.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][300:-300:-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,8,7,6,5,4,3,2,1]");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-300:300:-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Slice with a skip value of 0.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::0];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0, should return error.
    auto p1 = TangBase().compileScript(R"(
      [1,2,3,4,5,6,7,8,9][::0]
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Don't know how to slice this expression."});
  }
  {
    // Double slice, proof of concept.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20][::2][-3::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[15,13,11,9,7,5,3,1]");
  }
}

TEST(ControlFlow, IfElse) {
  auto p1 = TangBase().compileScript("a = 1; if (true) a = 2; a;");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)2);
  auto p2 = TangBase().compileScript("a = 1; if (true) a = 2; else a = 3; a;");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)2);
  auto p3 = TangBase().compileScript("a = 1; if (false) a = 2; a;");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)1);
  auto p4 = TangBase().compileScript("a = 1; if (false) a = 2; else a = 3; a;");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)3);
  auto p5 = TangBase().compileScript("a = 1; if (true) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p5.execute().getResult(), (integer_t)3);
  auto p6 = TangBase().compileScript("a = 1; if (true) {b = 3; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p6.execute().getResult(), (integer_t)4);
  auto p7 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p7.execute().getResult(), (integer_t)1);
  auto p8 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p8.execute().getResult(), (integer_t)4);
  auto p9 = TangBase().compileScript("a = 1; if (true) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p9.execute().getResult(), (integer_t)2);
  auto p10 = TangBase().compileScript("a = 1; if (false) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p10.execute().getResult(), (integer_t)4);
  auto p11 = TangBase().compileScript("a = 1; if (true) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p11.execute().getResult(), (integer_t)3);
  auto p12 = TangBase().compileScript("a = 1; if (false) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p12.execute().getResult(), (integer_t)4);
  auto p13 = TangBase().compileScript("a = 1; if (true) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p13.execute().getResult(), (integer_t)3);
  auto p14 = TangBase().compileScript("a = 1; if (true) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p14.execute().getResult(), (integer_t)4);
  auto p15 = TangBase().compileScript("a = 1; if (false) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p15.execute().getResult(), (integer_t)1);
  auto p16 = TangBase().compileScript("a = 1; if (false) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p16.execute().getResult(), (integer_t)1);
  auto p17 = TangBase().compileScript("a = 1; b = 2; if (a != b) a = 3; a;");
  EXPECT_EQ(*p17.execute().getResult(), (integer_t)3);
  auto p18 = TangBase().compileScript("a = 1; b = 2; if (a == b) a = 3; a;");
  EXPECT_EQ(*p18.execute().getResult(), (integer_t)1);
}

TEST(ControlFlow, While) {
  auto p1 = TangBase().compileScript("a = 1; while (a < 10) b = a = a + 1; b;");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)10);
  auto p2 = TangBase().compileScript("a = 1; while (a < 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)10);
  auto p3 = TangBase().compileScript("a = 1; while (a > 10) b = a = a + 1; b;");
  EXPECT_EQ(*p3.execute().getResult(), nullptr);
  auto p4 = TangBase().compileScript("a = 1; while (a > 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p4.execute().getResult(), nullptr);
  auto p5 = TangBase().compileScript("a = 1; while ((a = a + 1) < 10) {} b;");
  EXPECT_EQ(*p5.execute().getResult(), nullptr);
}

TEST(ControlFlow, Break) {
  auto p1 = TangBase().compileScript(R"(
    a = 0;
    while (a < 10) {
      a = a + 1;
      if (a > 5)
        break;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p1.execute().out, "12345Hi");
  auto p2 = TangBase().compileScript(R"(
    for (b = 0; b < 2; b = b + 1) {
      a = 0;
      while (a < 4) {
        a = a + 1;
        if (b % 2) {
          print("Even");
          break;
        }
        else {
          print("Odd");
          break;
        }
        print(a);
      }
    }
    print("Hi");
  )");
  EXPECT_EQ(p2.execute().out, "OddEvenHi");
  auto p3 = TangBase().compileScript(R"(
    for (a = 1; a < 10; a = a + 1) {
      if (a > 5)
        break;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p3.execute().out, "12345Hi");
  auto p4 = TangBase().compileScript(R"(
    print("Hi");
    break;
    print("Hi");
  )");
  EXPECT_EQ(p4.execute().out, "Hi");
  auto p5 = TangBase().compileScript(R"(
    function a() {
      print(1);
      break;
      print(2);
    }
    a();
    print(3);
  )");
  EXPECT_EQ(p5.execute().out, "13");
}

TEST(ControlFlow, Continue) {
  auto p1 = TangBase().compileScript(R"(
    a = 0;
    while (a < 10) {
      a = a + 1;
      if (a > 5)
        continue;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p1.execute().out, "12345Hi");
  auto p2 = TangBase().compileScript(R"(
    a = 0;
    while (a < 10) {
      a = a + 1;
      if (a < 3)
        continue;
      if (a > 7)
        continue;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p2.execute().out, "34567Hi");
  auto p3 = TangBase().compileScript(R"(
    for (a = 1; a < 10; a = a + 1) {
      if (a > 5)
        continue;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p3.execute().out, "12345Hi");
  auto p4 = TangBase().compileScript(R"(
    for (a = 1; a < 10; a = a + 1) {
      if (a < 3)
        continue;
      if (a > 7)
        continue;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p4.execute().out, "34567Hi");
  auto p5 = TangBase().compileScript(R"(
    print("Hi");
    continue;
    print("Hi");
  )");
  EXPECT_EQ(p5.execute().out, "Hi");
  auto p6 = TangBase().compileScript(R"(
    function a() {
      print(1);
      continue;
      print(2);
    }
    a();
    print(3);
  )");
  EXPECT_EQ(p6.execute().out, "13");
}

TEST(ControlFlow, DoWhile) {
  auto p1 = TangBase().compileScript("a = 1; do b = a = a + 1; while (a < 10); b;");
  EXPECT_EQ(*p1.execute().getResult(), (integer_t)10);
  auto p2 = TangBase().compileScript("a = 1; do {a = a + 1; b = a;} while (a < 10); b;");
  EXPECT_EQ(*p2.execute().getResult(), (integer_t)10);
  auto p3 = TangBase().compileScript("a = 1; do b = a = a + 1; while (a > 10); b;");
  EXPECT_EQ(*p3.execute().getResult(), (integer_t)2);
  auto p4 = TangBase().compileScript("a = 1; do {a = a + 1; b = a;} while (a > 10); b;");
  EXPECT_EQ(*p4.execute().getResult(), (integer_t)2);
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
  EXPECT_EQ(*p6.execute().getResult(), (float_t)100.);
}

TEST(ControlFlow, RangedFor) {
  {
    // Simple iterator through an array.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3];
      for (num : a) {
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "123");
  }
  {
    // Simple iterator through an temporary array.
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9];
      for (num : a[::2]) {
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "13579");
  }
  {
    // Simple iterator through a 2-dimensional array.
    auto p1 = TangBase().compileScript(R"(
      a = [[1,2,3],[4,5,6],[7,8,9,10]];
      for (outer : a) {
        for (inner : outer) {
          print(inner);
        }
      }
    )");
    EXPECT_EQ(p1.execute().out, "12345678910");
  }
  {
    // Attempt to iterate through a non-collection.
    auto p1 = TangBase().compileScript(R"(
      a = 3;
      for (num: a) {
        print(num);
      }
    )");
    EXPECT_EQ(*p1.execute().getResult(), Error{"Don't know how to iterate over this expression."});
  }
  {
    // Break
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9];
      for (num : a) {
        if (num > 5) break;
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "12345");
  }
  {
    // Continue
    auto p1 = TangBase().compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9];
      for (num : a) {
        if (num < 5) continue;
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "56789");
  }
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

TEST(Print, Array) {
  {
    // Print out an empty array.
    auto p1 = TangBase().compileScript("print([]);");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Print out an array of numbers, with comma separated values and no spaces
    // after the commas.
    auto p1 = TangBase().compileScript("print([0,1,2]);");
    EXPECT_EQ(p1.execute().out, "[0,1,2]");
  }
  {
    // Print out an array that contains a string, where the string is enclosed
    // in double quotes.
    auto p1 = TangBase().compileScript("print([0,\"a\",2]);");
    EXPECT_EQ(p1.execute().out, "[0,\"a\",2]");
  }
  {
    // Print out an array that contains a string, with contents that must be
    // escaped.
    auto p1 = TangBase().compileScript("print([\"\\\"a\nb\"]);");
    EXPECT_EQ(p1.execute().out, R"(["\"a\nb"])");
  }
}

TEST(Function, Compiled) {
  auto p1 = TangBase().compileScript(R"(
    function printHi() {
      print("Hi");
    }
    printHi();
  )");
  EXPECT_EQ(p1.execute().out, "Hi");
  auto p2 = TangBase().compileScript(R"(
    function printTwice(str) {
      print(str);
      print(str);
    }
    printTwice("Hi");
  )");
  EXPECT_EQ(p2.execute().out, "HiHi");
  auto p3 = TangBase().compileScript(R"(
    function print2then1(str1, str2) {
      print(str2);
      print(str1);
    }
    print2then1("Hi", 3);
  )");
  EXPECT_EQ(p3.execute().out, "3Hi");
  auto p4 = TangBase().compileScript(R"(
    function printHi() {
      print("Hi");
    }
    printHi();
    printHi();
  )");
  EXPECT_EQ(p4.execute().out, "HiHi");
  auto p5 = TangBase().compileScript(R"(
    function print2then1(str1, str2) {
      print(str2);
      print(str1);
    }
    print2then1("Hi", 3);
    print2then1("Hi", 2);
  )");
  EXPECT_EQ(p5.execute().out, "3Hi2Hi");
  auto p6 = TangBase().compileScript(R"(
    a("Hi", 3);
  )");
  EXPECT_EQ(*p6.execute().getResult(), Error{"Function call on unrecognized type."});
  auto p7 = TangBase().compileScript(R"(
    function print2then1(str1, str2) {
      print(str2);
      print(str1);
    }
    a = print2then1;
    a("Hi", 3);
  )");
  EXPECT_EQ(p7.execute().out, "3Hi");
}

TEST(Function, Recursion) {
  auto p1 = TangBase().compileScript(R"(
    function printNtimes(str, n) {
      if (n > 0) {
        printNtimes(str, n - 1);
        print(str);
      }
    }
    printNtimes("-", 3);
  )");
  EXPECT_EQ(p1.execute().out, "---");
  auto p2 = TangBase().compileScript(R"(
    function printNtimes(str, n) {
      function inner(str, n) {
        if (n > 0) {
          printNtimes(str, n - 1);
          print(str);
        }
      }
      inner(str, n);
    }
    printNtimes("-", 3);
  )");
  EXPECT_EQ(p2.execute().out, "---");
  auto p3 = TangBase().compileScript(R"(
    function helper(str, n) {
      printNtimes(str, n);
    }
    function printNtimes(str, n) {
      if (n > 0) {
        helper(str, n - 1);
        print(str);
      }
    }
    printNtimes("-", 3);
  )");
  EXPECT_EQ(p3.execute().out, "---");
}

TEST(Function, FunctionCall) {
  auto p1 = TangBase().compileScript(R"(
    function a(b, c) {}
    a(1);
  )");
  EXPECT_EQ(*p1.execute().getResult(), Error{"Incorrect number of arguments supplied at function call."});
}

TEST(Function, Return) {
  auto p1 = TangBase().compileScript(R"(
    function a(condition) {
      return condition ? 1 : 2;
    }
    print(a(true));
    print(a(false));
    print(a(false));
    print(a(true));
  )");
  EXPECT_EQ(p1.execute().out, "1221");
  auto p2 = TangBase().compileScript(R"(
    function a(condition) {
      if (condition) {
        return 1;
      }
    }
    print(a(true));
    print(a(false));
    print(a(false));
    print(a(true));
  )");
  EXPECT_EQ(p2.execute().out, "11");
  auto p3 = TangBase().compileScript(R"(
    function a(condition) {
      if (condition) {
        return 1;
      }
      print("Hi");
    }
    print(a(true));
    print(a(false));
    print(a(false));
    print(a(true));
  )");
  EXPECT_EQ(p3.execute().out, "1HiHi1");
  auto p4 = TangBase().compileScript(R"(
    function a(condition) {
      if (condition) {
        return;
      }
      print("Hi");
    }
    print(a(true));
    print(a(false));
    print(a(false));
    print(a(true));
  )");
  EXPECT_EQ(p4.execute().out, "HiHi");
}

TEST(Function, PassByValueVsRef) {
  {
    // Test shows:
    //   1. array argument is correctly copied
    //   2. argument does not modify outside scope
    auto p1 = TangBase().compileScript(R"(
      function change(val) {
        val[1] = "foo";
        print(val[0]);
        print(val[1]);
        print(val[2]);
      }
      a = [1,2,3];
      print(a[0]);
      print(a[1]);
      print(a[2]);
      change(a);
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "1231foo3123");
  }
  {
    // Test shows:
    //   1. argument produces COPY opcode.
    auto p1 = TangBase().compileScript(R"(
      function a(a) {
        a = 1;
      }
    )");
    EXPECT_EQ(p1.getBytecode().at(3), (uinteger_t)Opcode::COPY);
  }
  {
    // Test shows:
    //   1. argument does not produce COPY opcode.
    auto p1 = TangBase().compileScript(R"(
      function a(a) {
        b = 1;
      }
    )");
    EXPECT_NE(p1.getBytecode().at(4), (uinteger_t)Opcode::COPY);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

