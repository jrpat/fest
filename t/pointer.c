#include "fest.h"
  

TEST(pointer_equal) {
  const char *a="aaa", *b=a;
  IS_EQp(a, b);
}

TEST(pointer_not_equal) {
  const char *a="aaa", *b="aaz";
  IS_NEp(a, b);
}

