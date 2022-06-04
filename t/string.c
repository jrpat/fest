#include "fest.h"
  

TEST(string_equal) {
  const char *a="aaa", *b="aaa";
  IS_EQs(a, b);
  IS_EQs("aaa", b);
  IS_EQs("aaa", "aaa");
}

TEST(string_not_equal) {
  const char *a="aaa", *b="aaz";
  IS_NEs(a, b);
  IS_NEs("aaa", b);
  IS_NEs("aaa", "aaz");
}


TEST(sized_string_equal) {
  const char *a="aaa", *b="aaz";
  IS_EQz(a, b, 2);
  IS_EQz("aaa", b, 2);
  IS_EQz("aaa", "aaa", 2);
}

TEST(sized_string_not_equal) {
  const char *a="aaa", *b="aaz";
  IS_NEz(a, b, 3);
  IS_NEz("aaa", b, 3);
  IS_NEz("aaa", "aaz", 3);
}
