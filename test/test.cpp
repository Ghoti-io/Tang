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

auto tang = TangBase::make_shared();

TEST(Declare, Null) {
  auto p1 = tang->compileScript("null");
  EXPECT_EQ(*p1.execute().result, nullptr);
}

TEST(Declare, Integer) {
  auto p1 = tang->compileScript("3");
  EXPECT_EQ(*p1.execute().result, (integer_t)3);
  auto p2 = tang->compileScript("42");
  EXPECT_EQ(*p2.execute().result, (integer_t)42);
  auto p3 = tang->compileScript("-42");
  EXPECT_EQ(*p3.execute().result, (integer_t)-42);
  auto p4 = tang->compileScript("-42");
  EXPECT_EQ(*p4.execute().result, (float_t)-42.0);
  auto p5 = tang->compileScript("-42");
  EXPECT_NE(*p5.execute().result, (float_t)-42.5);
}

TEST(Declare, Float) {
  auto p1 = tang->compileScript("3.");
  EXPECT_EQ(*p1.execute().result, (float_t)3.);
  auto p2 = tang->compileScript("4.2");
  EXPECT_EQ(*p2.execute().result, (float_t)4.2);
  auto p3 = tang->compileScript("-4.2");
  EXPECT_EQ(*p3.execute().result, (float_t)-4.2);
  auto p4 = tang->compileScript(".2");
  EXPECT_EQ(*p4.execute().result, (float_t).2);
  auto p5 = tang->compileScript("0.");
  EXPECT_EQ(*p5.execute().result, (float_t)0.);
  auto p6 = tang->compileScript(".0");
  EXPECT_EQ(*p6.execute().result, (float_t)0.);
  auto p7 = tang->compileScript("3.0");
  EXPECT_EQ(*p7.execute().result, (integer_t)3);
  auto p8 = tang->compileScript("3.5");
  EXPECT_NE(*p8.execute().result, (integer_t)3);
}

TEST(Declare, Boolean) {
  auto p1 = tang->compileScript("true");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("false");
  EXPECT_EQ(*p2.execute().result, false);
}

TEST(Declare, String) {
  {
    // Construct an empty string.
    auto p1 = tang->compileScript("\"\"");
    EXPECT_EQ(*p1.execute().result, string(""));
    EXPECT_EQ(*p1.execute().result, "");
    EXPECT_NE(p1.execute().result, nullopt);
  }
  {
    // Construct a string that is not empty
    auto p1 = tang->compileScript("\"Hello World!\"");
    EXPECT_EQ(*p1.execute().result, "Hello World!");
    EXPECT_NE(p1.execute().result, nullopt);
  }
  {
    // String ending with EOF
    auto p1 = tang->compileScript("\"Hello World!");
    EXPECT_EQ(*p1.getResult(), Error{"syntax error, unexpected Malformed String"});
  }
  {
    // String ending with EOF, as part of an expression
    auto p1 = tang->compileScript("a = \"Hello World!");
    EXPECT_EQ(*p1.getResult(), Error{"syntax error, unexpected Malformed String"});
  }
  {
    // String ending with EOF, as part of an expression in a series of
    // expressions.
    auto p1 = tang->compileScript("a = 1; a = \"Hello World!");
    EXPECT_EQ(*p1.getResult(), Error{"syntax error, unexpected Malformed String"});
  }
}

TEST(Expression, Add) {
  auto p1 = tang->compileScript("3 + 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)8);
  auto p2 = tang->compileScript("3. + 5");
  EXPECT_EQ(*p2.execute().result, (integer_t)8);
  auto p3 = tang->compileScript("3. + 5.");
  EXPECT_EQ(*p3.execute().result, (integer_t)8);
  auto p4 = tang->compileScript("3 + 5.");
  EXPECT_EQ(*p4.execute().result, (integer_t)8);
  auto p5 = tang->compileScript("3 + -5");
  EXPECT_EQ(*p5.execute().result, (integer_t)-2);
  auto p6 = tang->compileScript("3.5 + 5");
  EXPECT_EQ(*p6.execute().result, (float_t)8.5);
  auto p7 = tang->compileScript("3.25 + 5.25");
  EXPECT_EQ(*p7.execute().result, (float_t)8.5);
  auto p8 = tang->compileScript("3 + 5.5");
  EXPECT_EQ(*p8.execute().result, (float_t)8.5);
  auto p9 = tang->compileScript("3 + 3 + 5.5");
  EXPECT_EQ(*p9.execute().result, (float_t)11.5);
  auto p10 = tang->compileScript("\"Hello\" + \" \" + \"World!\"");
  EXPECT_EQ(*p10.execute().result, "Hello World!");
}

TEST(Expression, Subtract) {
  auto p1 = tang->compileScript("3 - 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)-2);
  auto p2 = tang->compileScript("3. - 5");
  EXPECT_EQ(*p2.execute().result, (integer_t)-2);
  auto p3 = tang->compileScript("3. - 5.");
  EXPECT_EQ(*p3.execute().result, (integer_t)-2);
  auto p4 = tang->compileScript("3 - 5.");
  EXPECT_EQ(*p4.execute().result, (integer_t)-2);
  auto p5 = tang->compileScript("3 - -5");
  EXPECT_EQ(*p5.execute().result, (integer_t)8);
  auto p6 = tang->compileScript("3.5 - 5");
  EXPECT_EQ(*p6.execute().result, (float_t)-1.5);
  auto p7 = tang->compileScript("3.75 - 5.25");
  EXPECT_EQ(*p7.execute().result, (float_t)-1.5);
  auto p8 = tang->compileScript("3 - 5.5");
  EXPECT_EQ(*p8.execute().result, (float_t)-2.5);
  auto p9 = tang->compileScript("3 - 3 - 5.5");
  EXPECT_EQ(*p9.execute().result, (float_t)-5.5);
}

TEST(Expression, Multiplication) {
  auto p1 = tang->compileScript("3 * 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)15);
  auto p2 = tang->compileScript("3. * 5");
  EXPECT_EQ(*p2.execute().result, (integer_t)15);
  auto p3 = tang->compileScript("3. * 5.");
  EXPECT_EQ(*p3.execute().result, (integer_t)15);
  auto p4 = tang->compileScript("3 * 5.");
  EXPECT_EQ(*p4.execute().result, (integer_t)15);
  auto p5 = tang->compileScript("3 * -5");
  EXPECT_EQ(*p5.execute().result, (integer_t)-15);
  auto p6 = tang->compileScript("3.5 * 5");
  EXPECT_EQ(*p6.execute().result, (float_t)17.5);
  auto p7 = tang->compileScript("3.25 * 5.25");
  EXPECT_EQ(*p7.execute().result, (float_t)17.0625);
  auto p8 = tang->compileScript("3 * 5.5");
  EXPECT_EQ(*p8.execute().result, (float_t)16.5);
  auto p9 = tang->compileScript("3 * 3 * 5.5");
  EXPECT_EQ(*p9.execute().result, (float_t)49.5);
  auto p10 = tang->compileScript("3 + 3 * 5.5");
  EXPECT_EQ(*p10.execute().result, (float_t)19.5);
  auto p11 = tang->compileScript("3 * 3 + 5.5");
  EXPECT_EQ(*p11.execute().result, (float_t)14.5);
}

TEST(Expression, Division) {
  auto p1 = tang->compileScript("3 / 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)0);
  auto p2 = tang->compileScript("3. / 5");
  EXPECT_EQ(*p2.execute().result, (float_t).6);
  auto p3 = tang->compileScript("3. / 5.");
  EXPECT_EQ(*p3.execute().result, (float_t).6);
  auto p4 = tang->compileScript("3 / 5.");
  EXPECT_EQ(*p4.execute().result, (float_t).6);
  auto p5 = tang->compileScript("3 / -5");
  EXPECT_EQ(*p5.execute().result, (integer_t)0);
  auto p6 = tang->compileScript("3.5 / 5");
  EXPECT_EQ(*p6.execute().result, (float_t).7);
  auto p7 = tang->compileScript("1.5 / .1");
  EXPECT_EQ(*p7.execute().result, (integer_t)15);
  auto p8 = tang->compileScript("100 / .1");
  EXPECT_EQ(*p8.execute().result, (float_t)1000.);
  auto p9 = tang->compileScript("3 / 3 / 5.");
  EXPECT_EQ(*p9.execute().result, (float_t).2);
  auto p10 = tang->compileScript("3 / 0.");
  EXPECT_EQ(*p10.execute().result, Error("Cannot divide by zero."));
  auto p11 = tang->compileScript("3. / 0.");
  EXPECT_EQ(*p11.execute().result, Error("Cannot divide by zero."));
  auto p12 = tang->compileScript("3 / 0.");
  EXPECT_EQ(*p12.execute().result, Error("Cannot divide by zero."));
  auto p13 = tang->compileScript("3. / 0.");
  EXPECT_EQ(*p13.execute().result, Error("Cannot divide by zero."));
}

TEST(Expression, Modulo) {
  auto p1 = tang->compileScript("3 % 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)3);
  auto p2 = tang->compileScript("3. % 5");
  EXPECT_EQ(*p2.execute().result, Error{"Don't know how to modulo these values."});
  auto p3 = tang->compileScript("3. % 5.");
  EXPECT_EQ(*p3.execute().result, Error{"Don't know how to modulo these values."});
  auto p4 = tang->compileScript("3 % 5.");
  EXPECT_EQ(*p4.execute().result, Error{"Don't know how to modulo these values."});
  auto p5 = tang->compileScript("3 % -5");
  EXPECT_EQ(*p5.execute().result, (integer_t)3);
  auto p6 = tang->compileScript("3.5 % 5");
  EXPECT_EQ(*p6.execute().result, Error{"Don't know how to modulo these values."});
  auto p7 = tang->compileScript("3.25 % 5.25");
  EXPECT_EQ(*p7.execute().result, Error{"Don't know how to modulo these values."});
  auto p8 = tang->compileScript("3 % 5.5");
  EXPECT_EQ(*p8.execute().result, Error{"Don't know how to modulo these values."});
  auto p9 = tang->compileScript("13 % 7 % 5");
  EXPECT_EQ(*p9.execute().result, 1);
  auto p10 = tang->compileScript("3 % 0");
  EXPECT_EQ(*p10.execute().result, Error("Cannot modulo by zero."));
}

TEST(Expression, UnaryMinus) {
  auto p1 = tang->compileScript("3-5");
  EXPECT_EQ(*p1.execute().result, (integer_t)-2);
  auto p2 = tang->compileScript("3--5");
  EXPECT_EQ(*p2.execute().result, (integer_t)8);
  auto p3 = tang->compileScript("-3.-5.");
  EXPECT_EQ(*p3.execute().result, (integer_t)-8);
  auto p4 = tang->compileScript("-3--5.");
  EXPECT_EQ(*p4.execute().result, (integer_t)2);
  auto p5 = tang->compileScript("--5");
  EXPECT_EQ(*p5.execute().result, (integer_t)5);
  auto p6 = tang->compileScript("---5");
  EXPECT_EQ(*p6.execute().result, (integer_t)-5);
  auto p7 = tang->compileScript("---3.75-----5.25");
  EXPECT_EQ(*p7.execute().result, (integer_t)-9);
}

TEST(Expression, Parentheses) {
  auto p1 = tang->compileScript("(3-5)-1");
  EXPECT_EQ(*p1.execute().result, (integer_t)-3);
  auto p2 = tang->compileScript("3-(5-1)");
  EXPECT_EQ(*p2.execute().result, (integer_t)-1);
  auto p3 = tang->compileScript("((-(3.)))-(5.)");
  EXPECT_EQ(*p3.execute().result, (integer_t)-8);
  auto p4 = tang->compileScript("(((((-3.)))))");
  EXPECT_EQ(*p4.execute().result, (integer_t)-3);
}

TEST(Expression, TypeCast) {
  auto p1 = tang->compileScript("3.5 as int");
  EXPECT_EQ(*p1.execute().result, (integer_t)3);
  auto p2 = tang->compileScript("7.5 as int / 2");
  EXPECT_EQ(*p2.execute().result, (integer_t)3);
  auto p3 = tang->compileScript("3 as float / 5");
  EXPECT_EQ(*p3.execute().result, (float_t).6);
  auto p4 = tang->compileScript("7 / 5 as float");
  EXPECT_EQ(*p4.execute().result, (float_t)1.4);
  auto p5 = tang->compileScript("(7 / 5) as float");
  EXPECT_EQ(*p5.execute().result, (integer_t)1);
  auto p6 = tang->compileScript("7 as int");
  EXPECT_EQ(*p6.execute().result, (integer_t)7);
  auto p7 = tang->compileScript("7.5 as float");
  EXPECT_EQ(*p7.execute().result, (float_t)7.5);
  auto p8 = tang->compileScript("0 as bool");
  EXPECT_EQ(*p8.execute().result, false);
  auto p9 = tang->compileScript("1 as bool");
  EXPECT_EQ(*p9.execute().result, true);
  auto p10 = tang->compileScript("0. as bool");
  EXPECT_EQ(*p10.execute().result, false);
  auto p11 = tang->compileScript("1. as bool");
  EXPECT_EQ(*p11.execute().result, true);
  auto p12 = tang->compileScript(".5 as int as bool");
  EXPECT_EQ(*p12.execute().result, false);
  auto p13 = tang->compileScript("1.5 as int as bool");
  EXPECT_EQ(*p13.execute().result, true);
  auto p14 = tang->compileScript("true as int");
  EXPECT_EQ(*p14.execute().result, (integer_t)1);
  auto p15 = tang->compileScript("false as int");
  EXPECT_EQ(*p15.execute().result, (integer_t)0);
  auto p16 = tang->compileScript("true as float");
  EXPECT_EQ(*p16.execute().result, (float_t)1.);
  auto p17 = tang->compileScript("false as float");
  EXPECT_EQ(*p17.execute().result, (float_t)0.);
  auto p18 = tang->compileScript("true as bool");
  EXPECT_EQ(*p18.execute().result, true);
  auto p19 = tang->compileScript("false as bool");
  EXPECT_EQ(*p19.execute().result, false);
}

TEST(Expression, Not) {
  auto p1 = tang->compileScript("!true");
  EXPECT_EQ(*p1.execute().result, false);
  auto p2 = tang->compileScript("!false");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("!3");
  EXPECT_EQ(*p3.execute().result, false);
  auto p4 = tang->compileScript("!0");
  EXPECT_EQ(*p4.execute().result, true);
  auto p5 = tang->compileScript("!3.");
  EXPECT_EQ(*p5.execute().result, false);
  auto p6 = tang->compileScript("!0.");
  EXPECT_EQ(*p6.execute().result, true);
  auto p7 = tang->compileScript("!-3");
  EXPECT_EQ(*p7.execute().result, false);
}

TEST(Expression, LessThan) {
  auto p1 = tang->compileScript("2 < 3");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("2 < 2");
  EXPECT_EQ(*p2.execute().result, false);
  auto p3 = tang->compileScript("2 < 1");
  EXPECT_EQ(*p3.execute().result, false);
  auto p4 = tang->compileScript("2 < 3.");
  EXPECT_EQ(*p4.execute().result, true);
  auto p5 = tang->compileScript("2 < 2.");
  EXPECT_EQ(*p5.execute().result, false);
  auto p6 = tang->compileScript("2 < 1.");
  EXPECT_EQ(*p6.execute().result, false);
  auto p7 = tang->compileScript("2. < 3");
  EXPECT_EQ(*p7.execute().result, true);
  auto p8 = tang->compileScript("2. < 2");
  EXPECT_EQ(*p8.execute().result, false);
  auto p9 = tang->compileScript("2. < 1");
  EXPECT_EQ(*p9.execute().result, false);
  auto p10 = tang->compileScript("2. < 3.");
  EXPECT_EQ(*p10.execute().result, true);
  auto p11 = tang->compileScript("2. < 2.");
  EXPECT_EQ(*p11.execute().result, false);
  auto p12 = tang->compileScript("2. < 1.");
  EXPECT_EQ(*p12.execute().result, false);
  auto p13 = tang->compileScript("2 < true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. < true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false < true");
  EXPECT_EQ(*p15.execute().result, Error{"Don't know how to compare these values."});
  auto p16 = tang->compileScript("\"a\" < \"b\"");
  EXPECT_EQ(*p16.execute().result, true);
  auto p17 = tang->compileScript("\"b\" < \"a\"");
  EXPECT_EQ(*p17.execute().result, false);
}

TEST(Expression, LessThanEqual) {
  auto p1 = tang->compileScript("2 <= 3");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("2 <= 2");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("2 <= 1");
  EXPECT_EQ(*p3.execute().result, false);
  auto p4 = tang->compileScript("2 <= 3.");
  EXPECT_EQ(*p4.execute().result, true);
  auto p5 = tang->compileScript("2 <= 2.");
  EXPECT_EQ(*p5.execute().result, true);
  auto p6 = tang->compileScript("2 <= 1.");
  EXPECT_EQ(*p6.execute().result, false);
  auto p7 = tang->compileScript("2. <= 3");
  EXPECT_EQ(*p7.execute().result, true);
  auto p8 = tang->compileScript("2. <= 2");
  EXPECT_EQ(*p8.execute().result, true);
  auto p9 = tang->compileScript("2. <= 1");
  EXPECT_EQ(*p9.execute().result, false);
  auto p10 = tang->compileScript("2. <= 3.");
  EXPECT_EQ(*p10.execute().result, true);
  auto p11 = tang->compileScript("2. <= 2.");
  EXPECT_EQ(*p11.execute().result, true);
  auto p12 = tang->compileScript("2. <= 1.");
  EXPECT_EQ(*p12.execute().result, false);
  auto p13 = tang->compileScript("2 <= true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. <= true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false <= true");
  EXPECT_EQ(*p15.execute().result, Error{"Don't know how to compare these values."});
}

TEST(Expression, GreaterThan) {
  auto p1 = tang->compileScript("2 > 3");
  EXPECT_EQ(*p1.execute().result, false);
  auto p2 = tang->compileScript("2 > 2");
  EXPECT_EQ(*p2.execute().result, false);
  auto p3 = tang->compileScript("2 > 1");
  EXPECT_EQ(*p3.execute().result, true);
  auto p4 = tang->compileScript("2 > 3.");
  EXPECT_EQ(*p4.execute().result, false);
  auto p5 = tang->compileScript("2 > 2.");
  EXPECT_EQ(*p5.execute().result, false);
  auto p6 = tang->compileScript("2 > 1.");
  EXPECT_EQ(*p6.execute().result, true);
  auto p7 = tang->compileScript("2. > 3");
  EXPECT_EQ(*p7.execute().result, false);
  auto p8 = tang->compileScript("2. > 2");
  EXPECT_EQ(*p8.execute().result, false);
  auto p9 = tang->compileScript("2. > 1");
  EXPECT_EQ(*p9.execute().result, true);
  auto p10 = tang->compileScript("2. > 3.");
  EXPECT_EQ(*p10.execute().result, false);
  auto p11 = tang->compileScript("2. > 2.");
  EXPECT_EQ(*p11.execute().result, false);
  auto p12 = tang->compileScript("2. > 1.");
  EXPECT_EQ(*p12.execute().result, true);
  auto p13 = tang->compileScript("2 > true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. > true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false > true");
  EXPECT_EQ(*p15.execute().result, Error{"Don't know how to compare these values."});
}

TEST(Expression, GreaterThanEqual) {
  auto p1 = tang->compileScript("2 >= 3");
  EXPECT_EQ(*p1.execute().result, false);
  auto p2 = tang->compileScript("2 >= 2");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("2 >= 1");
  EXPECT_EQ(*p3.execute().result, true);
  auto p4 = tang->compileScript("2 >= 3.");
  EXPECT_EQ(*p4.execute().result, false);
  auto p5 = tang->compileScript("2 >= 2.");
  EXPECT_EQ(*p5.execute().result, true);
  auto p6 = tang->compileScript("2 >= 1.");
  EXPECT_EQ(*p6.execute().result, true);
  auto p7 = tang->compileScript("2. >= 3");
  EXPECT_EQ(*p7.execute().result, false);
  auto p8 = tang->compileScript("2. >= 2");
  EXPECT_EQ(*p8.execute().result, true);
  auto p9 = tang->compileScript("2. >= 1");
  EXPECT_EQ(*p9.execute().result, true);
  auto p10 = tang->compileScript("2. >= 3.");
  EXPECT_EQ(*p10.execute().result, false);
  auto p11 = tang->compileScript("2. >= 2.");
  EXPECT_EQ(*p11.execute().result, true);
  auto p12 = tang->compileScript("2. >= 1.");
  EXPECT_EQ(*p12.execute().result, true);
  auto p13 = tang->compileScript("2 >= true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. >= true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false >= true");
  EXPECT_EQ(*p15.execute().result, Error{"Don't know how to compare these values."});
}

TEST(Expression, Equal) {
  auto p1 = tang->compileScript("2 == 3");
  EXPECT_EQ(*p1.execute().result, false);
  auto p2 = tang->compileScript("2 == 2");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("2 == 1");
  EXPECT_EQ(*p3.execute().result, false);
  auto p4 = tang->compileScript("2 == 3.");
  EXPECT_EQ(*p4.execute().result, false);
  auto p5 = tang->compileScript("2 == 2.");
  EXPECT_EQ(*p5.execute().result, true);
  auto p6 = tang->compileScript("2 == 1.");
  EXPECT_EQ(*p6.execute().result, false);
  auto p7 = tang->compileScript("2. == 3");
  EXPECT_EQ(*p7.execute().result, false);
  auto p8 = tang->compileScript("2. == 2");
  EXPECT_EQ(*p8.execute().result, true);
  auto p9 = tang->compileScript("2. == 1");
  EXPECT_EQ(*p9.execute().result, false);
  auto p10 = tang->compileScript("2. == 3.");
  EXPECT_EQ(*p10.execute().result, false);
  auto p11 = tang->compileScript("2. == 2.");
  EXPECT_EQ(*p11.execute().result, true);
  auto p12 = tang->compileScript("2. == 1.");
  EXPECT_EQ(*p12.execute().result, false);
  auto p13 = tang->compileScript("2 == true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. == true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false == true");
  EXPECT_EQ(*p15.execute().result, false);
  auto p16 = tang->compileScript("true == true");
  EXPECT_EQ(*p16.execute().result, true);
  auto p17 = tang->compileScript("false == false");
  EXPECT_EQ(*p17.execute().result, true);
  auto p18 = tang->compileScript("null == null");
  EXPECT_EQ(*p18.execute().result, true);
  auto p19 = tang->compileScript("null == 0");
  EXPECT_EQ(*p19.execute().result, false);
  auto p20 = tang->compileScript("0 == null");
  EXPECT_EQ(*p20.execute().result, false);
  auto p21 = tang->compileScript("0. == null");
  EXPECT_EQ(*p21.execute().result, false);
  auto p22 = tang->compileScript("false == null");
  EXPECT_EQ(*p22.execute().result, false);
  auto p23 = tang->compileScript("\"a\" == \"b\"");
  EXPECT_EQ(*p23.execute().result, false);
  auto p24 = tang->compileScript("\"a\" == \"a\"");
  EXPECT_EQ(*p24.execute().result, true);
}

TEST(Expression, NotEqual) {
  auto p1 = tang->compileScript("2 != 3");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("2 != 2");
  EXPECT_EQ(*p2.execute().result, false);
  auto p3 = tang->compileScript("2 != 1");
  EXPECT_EQ(*p3.execute().result, true);
  auto p4 = tang->compileScript("2 != 3.");
  EXPECT_EQ(*p4.execute().result, true);
  auto p5 = tang->compileScript("2 != 2.");
  EXPECT_EQ(*p5.execute().result, false);
  auto p6 = tang->compileScript("2 != 1.");
  EXPECT_EQ(*p6.execute().result, true);
  auto p7 = tang->compileScript("2. != 3");
  EXPECT_EQ(*p7.execute().result, true);
  auto p8 = tang->compileScript("2. != 2");
  EXPECT_EQ(*p8.execute().result, false);
  auto p9 = tang->compileScript("2. != 1");
  EXPECT_EQ(*p9.execute().result, true);
  auto p10 = tang->compileScript("2. != 3.");
  EXPECT_EQ(*p10.execute().result, true);
  auto p11 = tang->compileScript("2. != 2.");
  EXPECT_EQ(*p11.execute().result, false);
  auto p12 = tang->compileScript("2. != 1.");
  EXPECT_EQ(*p12.execute().result, true);
  auto p13 = tang->compileScript("2 != true");
  EXPECT_EQ(*p13.execute().result, Error{"Don't know how to compare these values."});
  auto p14 = tang->compileScript("2. != true");
  EXPECT_EQ(*p14.execute().result, Error{"Don't know how to compare these values."});
  auto p15 = tang->compileScript("false != true");
  EXPECT_EQ(*p15.execute().result, true);
}

TEST(Expression, And) {
  auto p1 = tang->compileScript("true && true");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("true && false");
  EXPECT_EQ(*p2.execute().result, false);
  auto p3 = tang->compileScript("false && true");
  EXPECT_EQ(*p3.execute().result, false);
  auto p4 = tang->compileScript("false && false");
  EXPECT_EQ(*p4.execute().result, false);
  auto p5 = tang->compileScript("(a = 0) && (a = 2); a;");
  EXPECT_EQ(*p5.execute().result, (integer_t)0);
  auto p6 = tang->compileScript("(a = 1) && (a = 2); a;");
  EXPECT_EQ(*p6.execute().result, (integer_t)2);
  auto p7 = tang->compileScript("(a = 0.) && (a = 2.); a;");
  EXPECT_EQ(*p7.execute().result, (float_t)0.);
  auto p8 = tang->compileScript("(a = 1.) && (a = 2.); a;");
  EXPECT_EQ(*p8.execute().result, (float_t)2.);
  auto p9 = tang->compileScript("(a = \"\") && (a = \"foo\"); a;");
  EXPECT_EQ(*p9.execute().result, "");
  auto p10 = tang->compileScript("(a = \"foo\") && (a = \"bar\"); a;");
  EXPECT_EQ(*p10.execute().result, "bar");
  auto p11 = tang->compileScript("(a = null) && (a = 2.); a;");
  EXPECT_EQ(*p11.execute().result, nullptr);
  auto p12 = tang->compileScript("(a = true) && (a = null); a;");
  EXPECT_EQ(*p12.execute().result, nullptr);
}

TEST(Expression, Or) {
  auto p1 = tang->compileScript("true || true");
  EXPECT_EQ(*p1.execute().result, true);
  auto p2 = tang->compileScript("true || false");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("false || true");
  EXPECT_EQ(*p3.execute().result, true);
  auto p4 = tang->compileScript("false || false");
  EXPECT_EQ(*p4.execute().result, false);
  auto p5 = tang->compileScript("(a = 0) || (a = 2); a;");
  EXPECT_EQ(*p5.execute().result, (integer_t)2);
  auto p6 = tang->compileScript("(a = 1) || (a = 2); a;");
  EXPECT_EQ(*p6.execute().result, (integer_t)1);
  auto p7 = tang->compileScript("(a = 0.) || (a = 2.); a;");
  EXPECT_EQ(*p7.execute().result, (float_t)2.);
  auto p8 = tang->compileScript("(a = 1.) || (a = 2.); a;");
  EXPECT_EQ(*p8.execute().result, (float_t)1.);
  auto p9 = tang->compileScript("(a = \"\") || (a = \"foo\"); a;");
  EXPECT_EQ(*p9.execute().result, "foo");
  auto p10 = tang->compileScript("(a = \"foo\") || (a = \"bar\"); a;");
  EXPECT_EQ(*p10.execute().result, "foo");
  auto p11 = tang->compileScript("(a = null) || (a = 2.); a;");
  EXPECT_EQ(*p11.execute().result, (float_t)2.);
  auto p12 = tang->compileScript("(a = true) || (a = null); a;");
  EXPECT_EQ(*p12.execute().result, true);
}

TEST(Expression, Ternary) {
  auto p1 = tang->compileScript("true ? 3 : 5");
  EXPECT_EQ(*p1.execute().result, (integer_t)3);
  auto p2 = tang->compileScript("false ? 3 : 5");
  EXPECT_EQ(*p2.execute().result, (integer_t)5);
  auto p3 = tang->compileScript("false ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p3.execute().result, (integer_t)5);
  auto p4 = tang->compileScript("false ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p4.execute().result, (integer_t)5);
  auto p5 = tang->compileScript("true ? true ? 1 : 3 : 5");
  EXPECT_EQ(*p5.execute().result, (integer_t)1);
  auto p6 = tang->compileScript("true ? false ? 1 : 3 : 5");
  EXPECT_EQ(*p6.execute().result, (integer_t)3);
  auto p7 = tang->compileScript("false ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p7.execute().result, (integer_t)3);
  auto p8 = tang->compileScript("false ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p8.execute().result, (integer_t)5);
  auto p9 = tang->compileScript("true ? 1 : true ? 3 : 5");
  EXPECT_EQ(*p9.execute().result, (integer_t)1);
  auto p10 = tang->compileScript("true ? 1 : false ? 3 : 5");
  EXPECT_EQ(*p10.execute().result, (integer_t)1);
}

TEST(Expression, StringIndex) {
  {
    // Tests positive and negative indexes.
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
      "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[-4]
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Index out of range."});
  }
  {
    // Index out of range
    auto p1 = tang->compileScript(R"(
      "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[3]
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Index out of range."});
  }
  {
    // Printing when index out of range
    auto p1 = tang->compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[3]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
}

TEST(Expression, StringSlice) {
  {
    // Slice with all default values.
    // Will create a copy of the string.
    auto p1 = tang->compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[::]);
    )");
    EXPECT_EQ(p1.execute().out, "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
  }
  {
    // Slice with default begin and end, but -1 skip.
    // Will reverse the string, keeping multi-codepoints in the correct order.
    auto p1 = tang->compileScript(R"(
      print("$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."[::-1]);
    )");
    EXPECT_EQ(p1.execute().out, ".\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF$");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::1]);
    )");
    EXPECT_EQ(p1.execute().out, "abcdefghijklmnopqrstuvwxyz");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::2]);
    )");
    EXPECT_EQ(p1.execute().out, "acegikmoqsuwy");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[1::2]);
    )");
    EXPECT_EQ(p1.execute().out, "bdfhjlnprtvxz");
  }
  {
    // Slice with a positive value and non-default begin & end.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[1:17:2]);
    )");
    EXPECT_EQ(p1.execute().out, "bdfhjlnp");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::-1]);
    )");
    EXPECT_EQ(p1.execute().out, "zyxwvutsrqponmlkjihgfedcba");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::-2]);
    )");
    EXPECT_EQ(p1.execute().out, "zxvtrpnljhfdb");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-2::-2]);
    )");
    EXPECT_EQ(p1.execute().out, "ywusqomkigeca");
  }
  {
    // Slice with a negative value and non-default begin & end.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-1:-17:-2]);
    )");
    EXPECT_EQ(p1.execute().out, "zxvtrpnl");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-300:300]);
    )");
    EXPECT_EQ(p1.execute().out, "abcdefghijklmnopqrstuvwxyz");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[300:-300]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array,
    // but reversed.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[300:-300:-1]);
    )");
    EXPECT_EQ(p1.execute().out, "zyxwvutsrqponmlkjihgfedcba");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[-300:300:-1]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::0]);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0, should return error.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::0]);
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Don't know how to slice this expression."});
  }
  {
    // Double slice, proof of concept.
    auto p1 = tang->compileScript(R"(
      print("abcdefghijklmnopqrstuvwxyz"[::2][-3::-1]);
    )");
    EXPECT_EQ(p1.execute().out, "usqomkigeca");
  }
  {
    // Slice across concatenated strings.
    // Begin in partial chunk.
    // Full chunk in middle.
    // End with partial chunk.
    auto p1 = tang->compileScript(R"(
      print(("abc" + "def" + "ghi")[2:7]);
    )");
    EXPECT_EQ(p1.execute().out, "cdefg");
  }
  {
    // Slice across concatenated strings.
    // Skip chunk at start.
    // Begin with full chunk.
    // End with full chunk.
    // Skip chunk at end.
    auto p1 = tang->compileScript(R"(
      print(("abc" + "def" + "ghi" + "jkl")[3:-3]);
    )");
    EXPECT_EQ(p1.execute().out, "defghi");
  }
}

TEST(Expression, ArrayIndex) {
  {
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a[1]);
    )");
    EXPECT_EQ(p1.execute().out, "2");
  }
  {
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "3");
  }
  {
    auto p1 = tang->compileScript(R"(
      [1,2,3][1]
    )");
    EXPECT_EQ(*p1.execute().result, 2);
  }
  {
    auto p1 = tang->compileScript(R"(
      [1,2,3][4]
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Index out of range."});
  }
  {
    auto p1 = tang->compileScript(R"(
      [1,2,3][-1]
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    auto p1 = tang->compileScript(R"(
      [1,2,3][-3]
    )");
    EXPECT_EQ(*p1.execute().result, 1);
  }
  {
    auto p1 = tang->compileScript(R"(
      [1,2,3][-4]
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Index out of range."});
  }
  {
    auto p1 = tang->compileScript(R"(
      a = [1,"a",1.5];
      print(a[0]);
      print(a[1]);
      print(a[2]);
    )");
    EXPECT_EQ(p1.execute().out, "1a1.500000");
  }
}

TEST(Expression, Map) {
  {
    // An empty object can be created.
    auto p1 = tang->compileScript(R"(
      {:} as string
    )");
    // TODO: Add support for testing the ComputedExpression value.
    EXPECT_EQ(*p1.execute().result, "{}");
  }
  {
    // An empty object should be false
    auto p1 = tang->compileScript(R"(
      {:} as bool
    )");
    EXPECT_EQ(*p1.execute().result, false);
  }
  {
    // A non-empty object should be true
    auto p1 = tang->compileScript(R"(
      {foo:5} as bool
    )");
    EXPECT_EQ(*p1.execute().result, true);
  }
  {
    // A non-empty object cast to a string.
    auto p1 = tang->compileScript(R"(
      {foo:5} as string
    )");
    EXPECT_EQ(*p1.execute().result, "{foo:5}");
  }
  {
    // A value can be set and retrieved via a key.
    auto p1 = tang->compileScript(R"(
      a = {foo:5};
      print(a["foo"]);
    )");
    EXPECT_EQ(p1.execute().out, "5");
  }
  {
    // Multiple values can be set and retrieved via a key.
    auto p1 = tang->compileScript(R"(
      a = {foo:5, bar:3};
      print(a["bar"]);
      print(a["foo"]);
    )");
    EXPECT_EQ(p1.execute().out, "35");
  }
  {
    // Multiple values can be set and retrieved via a key.
    // Only one key is referenced.
    auto p1 = tang->compileScript(R"(
      a = {foo:5, bar:3};
      print(a["bar"]);
    )");
    EXPECT_EQ(p1.execute().out, "3");
  }
  {
    // Unassigned values return nothing.
    auto p1 = tang->compileScript(R"(
      a = {foo:5, bar:3};
      print(a["baz"]);
      a["baz"];
    )");
    auto context = p1.execute();
    EXPECT_EQ(context.out, "");
    EXPECT_EQ(*context.result, Error{"Index does not exist in map"});
  }
}

TEST(CodeBlock, Statements) {
  auto p1 = tang->compileScript("2;");
  EXPECT_EQ(*p1.execute().result, (integer_t)2);
  auto p2 = tang->compileScript("2; true;");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("2; ((1 + 2.3 + 3) < -7) == true; 42;");
  EXPECT_EQ(*p3.execute().result, (integer_t)42);
}

TEST(Assign, Identifier) {
  auto p1 = tang->compileScript("a = 1; a;");
  EXPECT_EQ(*p1.execute().result, (integer_t)1);
  auto p2 = tang->compileScript("a = false; !a;");
  EXPECT_EQ(*p2.execute().result, true);
  auto p3 = tang->compileScript("a = b = 1; a = a + b; a;");
  EXPECT_EQ(*p3.execute().result, (integer_t)2);
}

TEST(Assign, Index) {
  {
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      a[4] = "foo";
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Index out of range."});
  }
  {
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
      a = [1,2,3][::];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3]");
  }
  {
    // Slice with default begin and end, but -1 skip.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3][::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[3,2,1]");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3,4,5,6,7,8,9]");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,3,5,7,9]");
  }
  {
    // Slice with a positive value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][1::2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[2,4,6,8]");
  }
  {
    // Slice with a positive value and non-default begin & end.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][1:7:2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[2,4,6]");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,8,7,6,5,4,3,2,1]");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,7,5,3,1]");
  }
  {
    // Slice with a negative value.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-2::-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[8,6,4,2]");
  }
  {
    // Slice with a negative value and non-default begin & end.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-1:-7:-2];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,7,5]");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-300:300:1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3,4,5,6,7,8,9]");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][300:-300:1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Slice with a begin & end out of range, should produce copy of array,
    // but reversed.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][300:-300:-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[9,8,7,6,5,4,3,2,1]");
  }
  {
    // Slice with a begin & end out of range, should produce and empty array.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][-300:300:-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Slice with a skip value of 0.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9][::0];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Slice with a skip value of 0, should return error.
    auto p1 = tang->compileScript(R"(
      [1,2,3,4,5,6,7,8,9][::0]
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Don't know how to slice this expression."});
  }
  {
    // Double slice, proof of concept.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20][::2][-3::-1];
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "[15,13,11,9,7,5,3,1]");
  }
}

TEST(ControlFlow, IfElse) {
  auto p1 = tang->compileScript("a = 1; if (true) a = 2; a;");
  EXPECT_EQ(*p1.execute().result, (integer_t)2);
  auto p2 = tang->compileScript("a = 1; if (true) a = 2; else a = 3; a;");
  EXPECT_EQ(*p2.execute().result, (integer_t)2);
  auto p3 = tang->compileScript("a = 1; if (false) a = 2; a;");
  EXPECT_EQ(*p3.execute().result, (integer_t)1);
  auto p4 = tang->compileScript("a = 1; if (false) a = 2; else a = 3; a;");
  EXPECT_EQ(*p4.execute().result, (integer_t)3);
  auto p5 = tang->compileScript("a = 1; if (true) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p5.execute().result, (integer_t)3);
  auto p6 = tang->compileScript("a = 1; if (true) {b = 3; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p6.execute().result, (integer_t)4);
  auto p7 = tang->compileScript("a = 1; if (false) {b = 2; a = a + b;} a;");
  EXPECT_EQ(*p7.execute().result, (integer_t)1);
  auto p8 = tang->compileScript("a = 1; if (false) {b = 2; a = a + b;} else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p8.execute().result, (integer_t)4);
  auto p9 = tang->compileScript("a = 1; if (true) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p9.execute().result, (integer_t)2);
  auto p10 = tang->compileScript("a = 1; if (false) a = 2; else {b = 3; a = a + b;} a;");
  EXPECT_EQ(*p10.execute().result, (integer_t)4);
  auto p11 = tang->compileScript("a = 1; if (true) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p11.execute().result, (integer_t)3);
  auto p12 = tang->compileScript("a = 1; if (false) {b = 2; a = a + b;} else a = 4; a;");
  EXPECT_EQ(*p12.execute().result, (integer_t)4);
  auto p13 = tang->compileScript("a = 1; if (true) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p13.execute().result, (integer_t)3);
  auto p14 = tang->compileScript("a = 1; if (true) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p14.execute().result, (integer_t)4);
  auto p15 = tang->compileScript("a = 1; if (false) if (true) a = 3; else a = 4; a;");
  EXPECT_EQ(*p15.execute().result, (integer_t)1);
  auto p16 = tang->compileScript("a = 1; if (false) if (false) a = 3; else a = 4; a;");
  EXPECT_EQ(*p16.execute().result, (integer_t)1);
  auto p17 = tang->compileScript("a = 1; b = 2; if (a != b) a = 3; a;");
  EXPECT_EQ(*p17.execute().result, (integer_t)3);
  auto p18 = tang->compileScript("a = 1; b = 2; if (a == b) a = 3; a;");
  EXPECT_EQ(*p18.execute().result, (integer_t)1);
}

TEST(ControlFlow, While) {
  auto p1 = tang->compileScript("a = 1; while (a < 10) b = a = a + 1; b;");
  EXPECT_EQ(*p1.execute().result, (integer_t)10);
  auto p2 = tang->compileScript("a = 1; while (a < 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p2.execute().result, (integer_t)10);
  auto p3 = tang->compileScript("a = 1; while (a > 10) b = a = a + 1; b;");
  EXPECT_EQ(*p3.execute().result, nullptr);
  auto p4 = tang->compileScript("a = 1; while (a > 10) {a = a + 1; b = a;} b;");
  EXPECT_EQ(*p4.execute().result, nullptr);
  auto p5 = tang->compileScript("a = 1; while ((a = a + 1) < 10) {} b;");
  EXPECT_EQ(*p5.execute().result, nullptr);
}

TEST(ControlFlow, Break) {
  auto p1 = tang->compileScript(R"(
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
  auto p2 = tang->compileScript(R"(
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
  auto p3 = tang->compileScript(R"(
    for (a = 1; a < 10; a = a + 1) {
      if (a > 5)
        break;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p3.execute().out, "12345Hi");
  auto p4 = tang->compileScript(R"(
    print("Hi");
    break;
    print("Hi");
  )");
  EXPECT_EQ(p4.execute().out, "Hi");
  auto p5 = tang->compileScript(R"(
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
  auto p1 = tang->compileScript(R"(
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
  auto p2 = tang->compileScript(R"(
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
  auto p3 = tang->compileScript(R"(
    for (a = 1; a < 10; a = a + 1) {
      if (a > 5)
        continue;
      print(a);
    }
    print("Hi");
  )");
  EXPECT_EQ(p3.execute().out, "12345Hi");
  auto p4 = tang->compileScript(R"(
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
  auto p5 = tang->compileScript(R"(
    print("Hi");
    continue;
    print("Hi");
  )");
  EXPECT_EQ(p5.execute().out, "Hi");
  auto p6 = tang->compileScript(R"(
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
  auto p1 = tang->compileScript("a = 1; do b = a = a + 1; while (a < 10); b;");
  EXPECT_EQ(*p1.execute().result, (integer_t)10);
  auto p2 = tang->compileScript("a = 1; do {a = a + 1; b = a;} while (a < 10); b;");
  EXPECT_EQ(*p2.execute().result, (integer_t)10);
  auto p3 = tang->compileScript("a = 1; do b = a = a + 1; while (a > 10); b;");
  EXPECT_EQ(*p3.execute().result, (integer_t)2);
  auto p4 = tang->compileScript("a = 1; do {a = a + 1; b = a;} while (a > 10); b;");
  EXPECT_EQ(*p4.execute().result, (integer_t)2);
}

TEST(ControlFlow, For) {
  auto p1 = tang->compileScript(R"(
    a = "";
    for (i = 0; i < 10; i = i + 1) {
      a = a + "-";
    }
    a;
  )");
  EXPECT_EQ(*p1.execute().result, "----------");
  auto p2 = tang->compileScript(R"(
    a = "";
    for (i = 0; i < 3; i = i + 1)
      a = a + "-";
    a;
  )");
  EXPECT_EQ(*p2.execute().result, "---");
  auto p3 = tang->compileScript(R"(
    a = "";
    i = 0;
    for (; i < 3;) {
      a = a + "-";
      i = i + 1;
    }
    a;
  )");
  EXPECT_EQ(*p3.execute().result, "---");
  auto p4 = tang->compileScript(R"(
    for (i = 0; i > 10; i = i + 1) {
      a = "-";
    }
    a;
  )");
  EXPECT_EQ(*p4.execute().result, nullptr);
  auto p5 = tang->compileScript(R"(
    for (i = 0; i > 10; i = i + 1)
      a = "-";
    a;
  )");
  EXPECT_EQ(*p5.execute().result, nullptr);
  auto p6 = tang->compileScript(R"(
    a = 0;
    for (i = 0; i < 10; i = i + 1)
      for (j = 0; j < 10; j = j + 1)
        a = a + 1;
    a;
  )");
  EXPECT_EQ(*p6.execute().result, (float_t)100.);
}

TEST(ControlFlow, RangedFor) {
  {
    // Simple iterator through an array.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      for (num : a) {
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "123");
  }
  {
    // Simple iterator through an temporary array.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9];
      for (num : a[::2]) {
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "13579");
  }
  {
    // Simple iterator through a 2-dimensional array.
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
      a = 3;
      for (num: a) {
        print(num);
      }
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Don't know how to iterate over this expression."});
  }
  {
    // Break
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
      a = [1,2,3,4,5,6,7,8,9];
      for (num : a) {
        if (num < 5) continue;
        print(num);
      }
    )");
    EXPECT_EQ(p1.execute().out, "56789");
  }
  {
    // Iterate through a string.
    auto p1 = tang->compileScript(R"(
      a = "abcde";
      for (char : a) {
        print(char);
        print("-");
      }
    )");
    EXPECT_EQ(p1.execute().out, "a-b-c-d-e-");
  }
  {
    // Iterate through a temporary string.
    auto p1 = tang->compileScript(R"(
      a = "abcdefghijklmnopqrstuvwxyz";
      for (char : a[::3]) {
        print(char);
        print("-");
      }
    )");
    EXPECT_EQ(p1.execute().out, "a-d-g-j-m-p-s-v-y-");
  }
  {
    // Iterate through an empty string.
    auto p1 = tang->compileScript(R"(
      a = "";
      for (char : a) {
        print(char);
        print("-");
      }
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
}

TEST(Print, Default) {
  auto p1 = tang->compileScript("print(\"\");");
  EXPECT_EQ(p1.execute().out, "");
  auto p2 = tang->compileScript("print(\"Hello World!\");");
  EXPECT_EQ(p2.execute().out, "Hello World!");
  auto p3 = tang->compileScript("print(3);");
  EXPECT_EQ(p3.execute().out, "3");
  auto p4 = tang->compileScript("print(3.);");
  EXPECT_EQ(p4.execute().out, "3.000000");
  auto p5 = tang->compileScript("print(true);");
  EXPECT_EQ(p5.execute().out, "");
  auto p6 = tang->compileScript("print(false);");
  EXPECT_EQ(p6.execute().out, "");
  auto p7 = tang->compileScript("print(null);");
  EXPECT_EQ(p7.execute().out, "");
  auto p8 = tang->compileScript("a = \"Hi\"; print(a);");
  EXPECT_EQ(p8.execute().out, "Hi");
  auto p9 = tang->compileScript("print(3 + 5);");
  EXPECT_EQ(p9.execute().out, "8");
  auto p10 = tang->compileScript("print(3 + null);");
  EXPECT_EQ(*p10.execute().result, Error{"Don't know how to add these values."});
  auto p11 = tang->compileScript(R"(
    for (i = 0; i < 10; i = i + 1) {
      print("-");
    }
  )");
  EXPECT_EQ(p11.execute().out, "----------");
}

TEST(Print, Array) {
  {
    // Print out an empty array.
    auto p1 = tang->compileScript("print([]);");
    EXPECT_EQ(p1.execute().out, "[]");
  }
  {
    // Print out an array of numbers, with comma separated values and no spaces
    // after the commas.
    auto p1 = tang->compileScript("print([0,1,2]);");
    EXPECT_EQ(p1.execute().out, "[0,1,2]");
  }
  {
    // Print out an array that contains a string, where the string is enclosed
    // in double quotes.
    auto p1 = tang->compileScript("print([0,\"a\",2]);");
    EXPECT_EQ(p1.execute().out, "[0,\"a\",2]");
  }
  {
    // Print out an array that contains a string, with contents that must be
    // escaped.
    auto p1 = tang->compileScript("print([\"\\\"a\nb\"]);");
    EXPECT_EQ(p1.execute().out, R"(["\"a\nb"])");
  }
}

TEST(Function, Compiled) {
  auto p1 = tang->compileScript(R"(
    function printHi() {
      print("Hi");
    }
    printHi();
  )");
  EXPECT_EQ(p1.execute().out, "Hi");
  auto p2 = tang->compileScript(R"(
    function printTwice(str) {
      print(str);
      print(str);
    }
    printTwice("Hi");
  )");
  EXPECT_EQ(p2.execute().out, "HiHi");
  auto p3 = tang->compileScript(R"(
    function print2then1(str1, str2) {
      print(str2);
      print(str1);
    }
    print2then1("Hi", 3);
  )");
  EXPECT_EQ(p3.execute().out, "3Hi");
  auto p4 = tang->compileScript(R"(
    function printHi() {
      print("Hi");
    }
    printHi();
    printHi();
  )");
  EXPECT_EQ(p4.execute().out, "HiHi");
  auto p5 = tang->compileScript(R"(
    function print2then1(str1, str2) {
      print(str2);
      print(str1);
    }
    print2then1("Hi", 3);
    print2then1("Hi", 2);
  )");
  EXPECT_EQ(p5.execute().out, "3Hi2Hi");
  auto p6 = tang->compileScript(R"(
    a("Hi", 3);
  )");
  EXPECT_EQ(*p6.execute().result, Error{"Function call on unrecognized type."});
  auto p7 = tang->compileScript(R"(
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
  auto p1 = tang->compileScript(R"(
    function printNtimes(str, n) {
      if (n > 0) {
        printNtimes(str, n - 1);
        print(str);
      }
    }
    printNtimes("-", 3);
  )");
  EXPECT_EQ(p1.execute().out, "---");
  auto p2 = tang->compileScript(R"(
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
  auto p3 = tang->compileScript(R"(
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
  auto p1 = tang->compileScript(R"(
    function a(b, c) {}
    a(1);
  )");
  EXPECT_EQ(*p1.execute().result, Error{"Incorrect number of arguments supplied at function call."});
}

TEST(Function, Return) {
  auto p1 = tang->compileScript(R"(
    function a(condition) {
      return condition ? 1 : 2;
    }
    print(a(true));
    print(a(false));
    print(a(false));
    print(a(true));
  )");
  EXPECT_EQ(p1.execute().out, "1221");
  auto p2 = tang->compileScript(R"(
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
  auto p3 = tang->compileScript(R"(
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
  auto p4 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
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
    auto p1 = tang->compileScript(R"(
      function a(a) {
        a = 1;
      }
    )");
    EXPECT_EQ(p1.getBytecode().at(3), (uinteger_t)Opcode::COPY);
  }
  {
    // Test shows:
    //   1. argument does not produce COPY opcode.
    auto p1 = tang->compileScript(R"(
      function a(a) {
        b = 1;
      }
    )");
    EXPECT_NE(p1.getBytecode().at(4), (uinteger_t)Opcode::COPY);
  }
}

TEST(ClassFunctions, General) {
  {
    // Bound function call
    auto p1 = tang->compileScript(R"(
      "Hello World".length(1)
    )");
    EXPECT_EQ(*p1.execute().result, Error{"Incorrect number of arguments provided to object method."});
  }
}

TEST(ClassFunctions, String) {
  {
    // Bound function call
    auto p1 = tang->compileScript(R"(
      a = "Hello World";
      print(a.length());
    )");
    EXPECT_EQ(p1.execute().out, "11");
  }
  {
    // Bound function assignment
    auto p1 = tang->compileScript(R"(
      a = "Hello World";
      b = a.length;
      print(b());
    )");
    EXPECT_EQ(p1.execute().out, "11");
  }
  {
    // Bound function assignment does not change
    auto p1 = tang->compileScript(R"(
      a = "Hello World";
      b = a.length;
      a = "Goodbye";
      print(b());
      print(a.length());
    )");
    EXPECT_EQ(p1.execute().out, "117");
  }
  {
    // Bound function works on directly instantiated object.
    auto p1 = tang->compileScript(R"(
      "Hello World!".length()
    )");
    EXPECT_EQ(*p1.execute().result, 12);
  }
  {
    // Bound function works on concatenated object.
    auto p1 = tang->compileScript(R"(
      ("Hello" + " " + "World!!!").length()
    )");
    EXPECT_EQ(*p1.execute().result, 14);
  }
}

TEST(ClassFunctions, Array) {
  {
    // Test length.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a.length());
    )");
    EXPECT_EQ(p1.execute().out, "3");
  }
  {
    // Test append.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a);
      print(a.length());
      a.append("foo");
      print(a);
      print(a.length());
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3]3[1,2,3,\"foo\"]4");
  }
  {
    // Test the return value of append().
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a.append("foo"));
    )");
    EXPECT_EQ(p1.execute().out, "[1,2,3,\"foo\"]");
  }
  {
    // Test chained methods.
    auto p1 = tang->compileScript(R"(
      a = [1,2,3];
      print(a.append("foo").length());
    )");
    EXPECT_EQ(p1.execute().out, "4");
  }
}

TEST(Syntax, SingleLineComment) {
  {
    // Single line comment on its own line.
    auto p1 = tang->compileScript(R"(
      // This is a test.
      a = 3;
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    // Single line comment containing code.
    auto p1 = tang->compileScript(R"(
      a = 3;
      // a = 4;
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    // Single line comment interrupting an expression.
    auto p1 = tang->compileScript(R"(
      a = // This is a test.
        5;
    )");
    EXPECT_EQ(*p1.execute().result, 5);
  }
  {
    // Single line comment as the only thing in the script.
    auto p1 = tang->compileScript(R"(
      // This is a test.
    )");
    EXPECT_EQ(p1.execute().out, "");
  }
  {
    // Single line comment not ending with a newline as the only thing in the
    // script.
    auto p1 = tang->compileScript("// This is a test.");
    EXPECT_EQ(p1.execute().out, "");
  }
}

TEST(Syntax, MultiLineComment) {
  {
    // Multi line comment on its own line.
    auto p1 = tang->compileScript(R"(
      /* This is a test. */
      a = 3;
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    // Multi line comment across multiple lines.
    auto p1 = tang->compileScript(R"(
      /*
       * This is a test.
       */
      a = 3;
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    // Multi line comment containing code.
    auto p1 = tang->compileScript(R"(
      a = 3;
      /*
       * a = 4;
       */
    )");
    EXPECT_EQ(*p1.execute().result, 3);
  }
  {
    // Multi line comment interrupting an expression.
    auto p1 = tang->compileScript(R"(
      a = /*
           * This is a test.
           */
        8;
    )");
    EXPECT_EQ(*p1.execute().result, 8);
  }
  {
    // Multi line comment with slashes that should be ignored.
    auto p1 = tang->compileScript(R"(
      a = /*
           * / This is a test.
           */
        8;
    )");
    EXPECT_EQ(*p1.execute().result, 8);
  }
  {
    // Multi line comment without being closed.
    auto p1 = tang->compileScript(R"(
      a = /*
           * This is a test.
    )");
    EXPECT_EQ(*p1.getResult(), Error{"syntax error, unexpected end of code"});
  }
  {
    // Multi line comment without being closed.
    auto p1 = tang->compileScript(R"(
      a = 3/*
            * This is a test.
    )");
    EXPECT_EQ(p1.getResult(), nullopt);
    EXPECT_EQ(*p1.execute().result, 3);
  }
}

TEST(Syntax, UntrustedString) {
  auto tang = TangBase::make_shared();
  auto & methods = tang->getObjectMethods();
  methods[type_index(typeid(ComputedExpressionString))]["make_untrusted"] = {0,
    [](GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
      auto copy = target->makeCopy();
      // We know that `target` is a GC String, so `copy` will be as well.
      // Therefore, it is safe to perform the static cast.
      static_cast<ComputedExpressionString &>(*copy).setUntrusted();
      return copy;
  }};
  {
    // Trusted String.
    auto p1 = tang->compileScript(R"(
      print("<h1>");
    )");
    EXPECT_EQ(p1.execute().out, "<h1>");
  }
  {
    // Trusted String.
    auto p1 = tang->compileScript(R"(
      print("<h1>".length());
    )");
    EXPECT_EQ(p1.execute().out, "4");
  }
  {
    // Untrusted String.
    auto p1 = tang->compileScript(R"(
      print("<h1>".make_untrusted());
    )");
    EXPECT_EQ(p1.execute().out, "&lt;h1&gt;");
  }
  {
    // Combined Trusted & Untrusted Strings.
    auto p1 = tang->compileScript(R"(
      a = "<h1>";
      print(a + a.make_untrusted() + a);
    )");
    EXPECT_EQ(p1.execute().out, "<h1>&lt;h1&gt;<h1>");
  }
}

TEST(Syntax, UntrustedStringLiteral) {
  {
    // Untrusted String Literal
    auto p1 = tang->compileScript(R"(
      a = !"<h1>";
      print(a);
    )");
    EXPECT_EQ(p1.execute().out, "&lt;h1&gt;");
  }
  {
    // Untrusted and Trusted String Literals are separate.
    auto p1 = tang->compileScript(R"(
      a = !"<h1>";
      b = "<h1>";
      print(a);
      print(b);
    )");
    EXPECT_EQ(p1.execute().out, "&lt;h1&gt;<h1>");
  }
}

TEST(NativeFunctions, General) {
  auto tang = TangBase::make_shared();
  auto & methods = tang->getObjectMethods();
  // Add `custom_function` as a method to any ComputedExpressionString.
  methods[type_index(typeid(ComputedExpressionString))]["custom_function"] = {0,
    []([[maybe_unused]] GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
      // `custom_function() will return a ComputedExpressionNativeFunction.
      return GarbageCollected::make<ComputedExpressionNativeFunction>(
        []([[maybe_unused]] vector<GarbageCollected>& args, [[maybe_unused]] Context & context) {
          // We are in a ComputedExpressionNativeFunction.  It has access to
          // the execution Context.  This function will use the Context to
          // store a variable that it  will increment each time that the
          // function is called.
          int count = 0;

          // Check to see if the variable already exists.
          if (context.data.count("custom_function")) {
            auto & val = context.data.at("custom_function");
            if (val.type() != typeid(int)) {
              // The variable is not the type that was expected, so something
              // went wrong.  Rather than overwriting the function, we will
              // simply return an error.
              return GarbageCollected::make<ComputedExpressionError>(Error{"Something went wrong!"});
            }
            // The variable exists as an integer.  Increment it.
            count = any_cast<int>(val) + 1;
            val = count;
          }
          else {
            // The variable did not exist, set it.
            context.data["custom_function"] = (int)0;
          }
          // Return the `count` as an integer.
          return GarbageCollected::make<ComputedExpressionInteger>(count);
        }, (size_t)0);
    }};

  // Test Native Function.
  // We don't have a way to access a native function (yet), so we will use
  // our ability to inject a native bound function into an object, and it
  // can then provide a native function.
  // This can be simplified later when we implement libraries.
  auto p0 = tang->compileScript(R"(
    a = "".custom_function();
    print(a());
    print(a());
    print(a());
  )");
  {
    // Test Native Function.
    // We don't have a way to access a native function (yet), so we will use
    // our ability to inject a native bound function into an object, and it
    // can then provide a native function.
    // This can be simplified later when we implement libraries.
    EXPECT_EQ(p0.execute().out, "012");
  }
  {
    // Demonstrate that the execution context is not persisted when the program
    // is executed a second time.
    // Notice, the output is not "345".
    EXPECT_EQ(p0.execute().out, "012");
  }
  {
    // Demonstrate that the native function returned by `custom_function` will
    // increment the same internal value, regardless of the string on which it
    // is defined.
    auto p1 = tang->compileScript(R"(
      print("a".custom_function()());
      print("b".custom_function()());
      print("c".custom_function()());
    )");
    EXPECT_EQ(p1.execute().out, "012");
  }
}

TEST(Context, General) {
  auto tang = TangBase::make_shared();
  auto & methods = tang->getObjectMethods();
  // Add `custom_function` as a method to any ComputedExpressionString.
  methods[type_index(typeid(ComputedExpressionString))]["custom_function"] = {0,
    []([[maybe_unused]] GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
      // `custom_function() will return a ComputedExpressionNativeFunction.
      return GarbageCollected::make<ComputedExpressionNativeFunction>(
        []([[maybe_unused]] vector<GarbageCollected>& args, [[maybe_unused]] Context & context) {
          // We are in a ComputedExpressionNativeFunction.  It has access to
          // the execution Context.  This function will use the Context to
          // store a variable that it  will increment each time that the
          // function is called.
          int count = 0;

          // Check to see if the variable already exists.
          if (context.data.count("custom_function")) {
            auto & val = context.data.at("custom_function");
            if (val.type() != typeid(int)) {
              // The variable is not the type that was expected, so something
              // went wrong.  Rather than overwriting the function, we will
              // simply return an error.
              return GarbageCollected::make<ComputedExpressionError>(Error{"Something went wrong!"});
            }
            // The variable exists as an integer.  Increment it.
            count = any_cast<int>(val) + 1;
            val = count;
          }
          else {
            // The variable did not exist, set it.
            context.data["custom_function"] = (int)0;
          }
          // Return the `count` as an integer.
          return GarbageCollected::make<ComputedExpressionInteger>(count);
        }, (size_t)0);
    }};

  {
    // Test Native Function.
    // We don't have a way to access a native function (yet), so we will use
    // our ability to inject a native bound function into an object, and it
    // can then provide a native function.
    // This can be simplified later when we implement libraries.
    auto p1 = tang->compileScript(R"(
      a = "".custom_function();
      print(a());
      print(a());
      print(a());
    )");
    EXPECT_EQ(p1.execute({{"custom_function", (int)-4}}).out, "-3-2-1");
  }
}

TEST(Compile, Template) {
  {
    // Compile a simple template that contains no script.
    auto p1 = tang->compileTemplate(R"(Hello World!)");
    auto context = p1.execute();
    EXPECT_EQ(*context.result, nullptr);
    EXPECT_EQ(context.out, "Hello World!");
  }
  {
    // Compile a simple template that contains a script.
    auto p1 = tang->compileTemplate(R"(Hello <%
      a = 1;
      print(a);
      %> World!)");
    auto context = p1.execute();
    EXPECT_EQ(*context.result, nullptr);
    EXPECT_EQ(context.out, "Hello 1 World!");
  }
  {
    // Compile a simple template that contains multiple script sections.
    auto p1 = tang->compileTemplate(R"(Fish <%
        a = "|";
        print(a);
      %> And <%
        print(a);
      %> Chips)");
    auto context = p1.execute();
    EXPECT_EQ(*context.result, nullptr);
    EXPECT_EQ(context.out, "Fish | And | Chips");
  }
  {
    // Verify behavior of trusted and untrusted strings.
    auto p1 = tang->compileTemplate(R"(<h1><% print(!"<h1>"); %></h1>)");
    auto context = p1.execute();
    EXPECT_EQ(*context.result, nullptr);
    EXPECT_EQ(context.out, "<h1>&lt;h1&gt;</h1>");
  }
  {
    // Verify error when trying to exit from a script when not acutally
    // compiling a template.
    auto p1 = tang->compileScript(R"(a = 1;%>)");
    EXPECT_EQ(*p1.getResult(), Error{"syntax error, unexpected %>, expecting end of code"});
  }
}

TEST(Compile, ShortCodes) {
  auto tang = TangBase::make_shared();
  auto & methods = tang->getObjectMethods();
  // Add `custom_function` as a method to any ComputedExpressionString.
  methods[type_index(typeid(ComputedExpressionString))]["custom_function"] = {0,
    []([[maybe_unused]] GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
      // `custom_function() will return a ComputedExpressionNativeFunction.
      return GarbageCollected::make<ComputedExpressionNativeFunction>(
        []([[maybe_unused]] vector<GarbageCollected>& args, [[maybe_unused]] Context & context) {
          // We are in a ComputedExpressionNativeFunction.  It has access to
          // the execution Context.  This function will use the Context to
          // store a variable that it  will increment each time that the
          // function is called.
          int count = 0;

          // Check to see if the variable already exists.
          if (context.data.count("custom_function")) {
            auto & val = context.data.at("custom_function");
            if (val.type() != typeid(int)) {
              // The variable is not the type that was expected, so something
              // went wrong.  Rather than overwriting the function, we will
              // simply return an error.
              return GarbageCollected::make<ComputedExpressionError>(Error{"Something went wrong!"});
            }
            // The variable exists as an integer.  Increment it.
            count = any_cast<int>(val) + 1;
            val = count;
          }
          else {
            // The variable did not exist, set it.
            context.data["custom_function"] = (int)0;
          }
          // Return the `count` as an integer.
          return GarbageCollected::make<ComputedExpressionInteger>(count);
        }, (size_t)0);
    }};

  {
    // Compile a simple short code template.
    auto p1 = tang->compileTemplate(R"(1 + 1 = <%= 1 + 1 %>)");
    EXPECT_EQ(p1.getResult(), nullopt);
    EXPECT_EQ(p1.execute().out, "1 + 1 = 2");
  }
  {
    // Compile a template with multiple short codes.
    auto p1 = tang->compileTemplate(R"(-<%=
        "".custom_function()()
      %>-<%=
        "Hello"
      %>-<%=
        "".custom_function()()
      %>-<%=
        "World"
      %>-<%=
        "".custom_function()()
      %>-)");
    EXPECT_EQ(p1.getResult(), nullopt);
    EXPECT_EQ(p1.execute().out, "-0-Hello-1-World-2-");
  }
  {
    // Syntax error on unterminated short code.
    auto p1 = tang->compileTemplate(R"(-<%= )");
    EXPECT_EQ(p1.getResult(), Error{"syntax error, unexpected end of code"});
  }
  {
    // Syntax error on empty short code.
    auto p1 = tang->compileTemplate(R"(-<%= %>)");
    EXPECT_EQ(p1.getResult(), Error{"syntax error, unexpected <%= %> closing tag"});
  }
  {
    // Template only includes a short code.
    auto p1 = tang->compileTemplate(R"(<%= 3 %>)");
    EXPECT_EQ(p1.getResult(), nullopt);
    EXPECT_EQ(p1.execute().out, "3");
  }
}

TEST(Library, Use) {
  {
    // "use" invocation
    auto p1 = tang->compileScript(R"(
      use math;
      print(math.abs(3.5));
    )");
    EXPECT_EQ(p1.execute().out, "3");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

