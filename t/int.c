#include "fest.h"


TEST(int_equal) {
  char a=1, b=1;
  IS_EQi(a, b);
  IS_EQi(1, b);
  IS_EQi(1, 1);
}

TEST(int_not_equal) {
  char a=1, b=9;
  IS_NEi(a, b);
  IS_NEi(1, b);
  IS_NEi(1, 9);
}

TEST(int_less_than) {
  char a=1, b=9;
  IS_LTi(a, b);
  IS_LTi(1, b);
  IS_LTi(1, 9);
}

TEST(int_greater_than) {
  char a=9, b=1;
  IS_GTi(a, b);
  IS_GTi(9, b);
  IS_GTi(9, 1);
}

TEST(int_less_equal) {
  char a=1, b=9;
  IS_LEi(a, b);
  IS_LEi(b, b);
  IS_LEi(1, b);
  IS_LEi(9, b);
  IS_LEi(1, 1);
  IS_LEi(9, 9);
}

TEST(int_greater_equal) {
  char a=9, b=1;
  IS_GEi(a, b);
  IS_GEi(b, b);
  IS_GEi(1, b);
  IS_GEi(9, b);
  IS_GEi(1, 1);
  IS_GEi(9, 9);
}

