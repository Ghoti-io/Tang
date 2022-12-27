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

TEST(Core, HtmlEscapeAscii) {
  UnicodeString s{"$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."};
  EXPECT_EQ(htmlEscapeAscii(""), R"()");
  EXPECT_EQ(htmlEscapeAscii("<"), "&lt;");
  EXPECT_EQ(htmlEscapeAscii(">"), "&gt;");
  EXPECT_EQ(htmlEscapeAscii("&"), "&amp;");
  EXPECT_EQ(htmlEscapeAscii("\""), "&quot;");
  EXPECT_EQ(htmlEscapeAscii("'"), "&apos;");
  EXPECT_EQ(htmlEscapeAscii("bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()`~[]{}|;:',.<>? \""), R"(bacdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&excl;&commat;&num;&dollar;&percnt;&Hat;&amp;&ast;&lpar;&rpar;&grave;~&lsqb;&rsqb;&lcub;&rcub;&verbar;&semi;&colon;&apos;&comma;&period;&lt;&gt;&quest; &quot;)");
  EXPECT_EQ(htmlEscapeAscii("\a"), "&#x7;");
  EXPECT_EQ(htmlEscapeAscii("\b"), "&#x8;");
  EXPECT_EQ(htmlEscapeAscii("\f"), "&#xC;");
  EXPECT_EQ(htmlEscapeAscii("\n"), "&NewLine;");
  EXPECT_EQ(htmlEscapeAscii("\r"), "&#xD;");
  EXPECT_EQ(htmlEscapeAscii("\t"), "&Tab;");
  EXPECT_EQ(htmlEscapeAscii("\v"), "&#xB;");
  EXPECT_EQ(htmlEscapeAscii("\xAA"), "&xFFFD;");
  EXPECT_EQ(htmlEscapeAscii("\xFF"), "&xFFFD;");
  EXPECT_EQ(htmlEscapeAscii(string("\x00", 1)), "&#x0;");
  EXPECT_EQ(htmlEscapeAscii("\x01"), "&#x1;");
  EXPECT_EQ(htmlEscapeAscii(s), "&dollar;&#x1F3F4;&#xE0067;&#xE0062;&#xE0073;&#xE0063;&#xE0074;&#xE007F;&period;");
  // 2-byte Unicode character, Pound Sign (currency)
  EXPECT_EQ(htmlEscapeAscii("\xc2\xa3"), "&pound;");
  // 3-byte Unicode character, Japanese word "yen" (currency)
  EXPECT_EQ(htmlEscapeAscii("\xe5\x86\x86"), "&#x5186;");
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

TEST(UnicodeString, Types) {
  {
    // Default (trusted) string.
    UnicodeString s{"&"};
    EXPECT_EQ(s.render(), "&");
  }
  {
    // Untrusted string.
    UnicodeString s{"&"};
    s.setUntrusted();
    EXPECT_EQ(s.render(), "&amp;");
  }
  {
    // Trusted string.
    UnicodeString s{"<h1>"};
    EXPECT_EQ(s.render(), "<h1>");
  }
  {
    // Untrusted string.
    UnicodeString s{"<h1>"};
    s.setUntrusted();
    EXPECT_EQ(s.render(), "&lt;h1&gt;");
  }
  {
    // Trusted string.
    UnicodeString s{"<h1>Hello\nWorld!</h1>"};
    EXPECT_EQ(s.renderAscii(), "<h1>Hello&NewLine;World!</h1>");
  }
  {
    // Untrusted string.
    UnicodeString s{"<h1>Hello\nWorld!</h1>"};
    s.setUntrusted();
    EXPECT_EQ(s.renderAscii(), "&lt;h1&gt;Hello&NewLine;World&excl;&lt;&sol;h1&gt;");
  }
}

TEST(Core, PercentEncode) {
  {
    // Space becomes a plus.
    UnicodeString s{"abc def"};
    EXPECT_EQ(percentEncode(s), "abc+def");
  }
  {
    // Plus is percent encoded.
    UnicodeString s{"abc+def"};
    EXPECT_EQ(percentEncode(s), "abc%2Bdef");
  }
  {
    // Plus is percent encoded.
    UnicodeString s{"ABC\nDEF"};
    EXPECT_EQ(percentEncode(s), "ABC%0ADEF");
  }
  {
    // Unicode Character is percent encoded.
    // Notice the "$" is also encoded, but the "." did not need to be encoded.
    UnicodeString s{"$\xF0\x9F\x8F\xB4\xF3\xA0\x81\xA7\xF3\xA0\x81\xA2\xF3\xA0\x81\xB3\xF3\xA0\x81\xA3\xF3\xA0\x81\xB4\xF3\xA0\x81\xBF."};
    EXPECT_EQ(percentEncode(s), "%24%F0%9F%8F%B4%F3%A0%81%A7%F3%A0%81%A2%F3%A0%81%B3%F3%A0%81%A3%F3%A0%81%B4%F3%A0%81%BF.");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


