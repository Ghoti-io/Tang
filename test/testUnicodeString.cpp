/**
 * @file
 *
 * Contains tests for the Tang::UnicodeString class.
 */

#include <gtest/gtest.h>
#include <iostream>
#include "unicodeString.hpp"

using namespace std;
using namespace Tang;

TEST(Core, Unescape) {
  EXPECT_EQ(unescape(""), R"()");
  EXPECT_EQ(unescape("bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~[]{}|;:',.<>? \""), R"(bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~[]{}|;:',.<>? \")");
  EXPECT_EQ(unescape("\""), R"(\")");
  EXPECT_EQ(unescape("\a"), R"(\a)");
  EXPECT_EQ(unescape("\b"), R"(\b)");
  EXPECT_EQ(unescape("\f"), R"(\f)");
  EXPECT_EQ(unescape("\n"), R"(\n)");
  EXPECT_EQ(unescape("\r"), R"(\r)");
  EXPECT_EQ(unescape("\t"), R"(\t)");
  EXPECT_EQ(unescape("\v"), R"(\v)");
  EXPECT_EQ(unescape("\xAA"), R"(\xAA)");
  EXPECT_EQ(unescape("\xFF"), R"(\xFF)");
  EXPECT_EQ(unescape(string("\x00", 1)), R"(\x00)");
  EXPECT_EQ(unescape("\x01"), R"(\x01)");
}

TEST(Core, HtmlEscape) {
  UnicodeString s{"$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."};
  EXPECT_EQ(htmlEscape(""), R"()");
  EXPECT_EQ(htmlEscape("<"), "&lt;");
  EXPECT_EQ(htmlEscape(">"), "&gt;");
  EXPECT_EQ(htmlEscape("&"), "&amp;");
  EXPECT_EQ(htmlEscape("\""), "&quot;");
  EXPECT_EQ(htmlEscape("'"), "&apos;");
  EXPECT_EQ(htmlEscape("bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~[]{}|;:',.<>? \""), R"(bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&amp;*()`~[]{}|;:&apos;,.&lt;&gt;? &quot;)");
  EXPECT_EQ(htmlEscape("\a"), "\a");
  EXPECT_EQ(htmlEscape("\b"), "\b");
  EXPECT_EQ(htmlEscape("\f"), "\f");
  EXPECT_EQ(htmlEscape("\n"), "\n");
  EXPECT_EQ(htmlEscape("\r"), "\r");
  EXPECT_EQ(htmlEscape("\t"), "\t");
  EXPECT_EQ(htmlEscape("\v"), "\v");
  EXPECT_EQ(htmlEscape("\xAA"), "\xAA");
  EXPECT_EQ(htmlEscape("\xFF"), "\xFF");
  EXPECT_EQ(htmlEscape(string("\x00", 1)), "\x00");
  EXPECT_EQ(htmlEscape("\x01"), "\x01");
  EXPECT_EQ(htmlEscape(s), "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
}

TEST(UnicodeString, SubString) {
  {
    // Testing an empty string.
    UnicodeString s{""};
    EXPECT_EQ(s.substr(0, 0), "");
    EXPECT_EQ(s.substr(0, 1), "");
  }
  {
    // Testing a string with one character.
    UnicodeString s{"a"};
    EXPECT_EQ(s.substr(0, 0), "");
    EXPECT_EQ(s.substr(0, 1), "a");
    EXPECT_EQ(s.substr(3, 1), "");
  }
  {
    // Testing multiple graphemes, each made of a single unicode codepoint.
    UnicodeString s{"$\u00A3\u5186"};
    EXPECT_EQ(s.substr(0, 1), "$");
    EXPECT_EQ(s.substr(1, 1), "\u00A3");
    EXPECT_EQ(s.substr(0, 2), "$\u00A3");
    EXPECT_EQ(s.substr(2, 1), "\u5186");
    EXPECT_EQ(s.substr(1, 2), "\u00A3\u5186");
    EXPECT_EQ(s.substr(0, 3), "$\u00A3\u5186");
  }
  {
    // Testing multiple graphemes, one of which is is made of multiple
    // codepoints.
    // The long string of hex values is a UTF-8 encoding of the Scottish Flag.
    UnicodeString s{"$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."};
    EXPECT_EQ(s.substr(0, 0), "");
    EXPECT_EQ(s.substr(0, 1), "$");
    EXPECT_EQ(s.substr(1, 1), "\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF");
    EXPECT_EQ(s.substr(2, 1), ".");
    EXPECT_EQ(s.substr(0, 2), "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF");
    EXPECT_EQ(s.substr(1, 2), "\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
    EXPECT_EQ(s.substr(0, 3), "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
    EXPECT_EQ(s.substr(0, 30), "$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF.");
    EXPECT_EQ(s.substr(15, 0), "");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


