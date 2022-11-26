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
    EXPECT_EQ(s.substr(15, 0), "");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


