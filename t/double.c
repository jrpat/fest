#include "fest.h"


TEST(double_equal) {
  char a=1.0, b=1.0;
  IS_EQi(a, b);
  IS_EQi(1.0, b);
  IS_EQi(1.0, 1.0);
}

TEST(double_not_equal) {
  char a=1.0, b=9.0;
  IS_NEi(a, b);
  IS_NEi(1.0, b);
  IS_NEi(1.0, 9.0);
}

TEST(double_less_than) {
  char a=1.0, b=9.0;
  IS_LTi(a, b);
  IS_LTi(1.0, b);
  IS_LTi(1.0, 9.0);
}

TEST(double_greater_than) {
  char a=9.0, b=1.0;
  IS_GTi(a, b);
  IS_GTi(9.0, b);
  IS_GTi(9.0, 1.0);
}

TEST(double_less_equal) {
  char a=1.0, b=9.0;
  IS_LEi(a, b);
  IS_LEi(b, b);
  IS_LEi(1.0, b);
  IS_LEi(9.0, b);
  IS_LEi(1.0, 1.0);
  IS_LEi(9.0, 9.0);
}

TEST(double_greater_equal) {
  char a=9.0, b=1.0;
  IS_GEi(a, b);
  IS_GEi(b, b);
  IS_GEi(1.0, b);
  IS_GEi(9.0, b);
  IS_GEi(1.0, 1.0);
  IS_GEi(9.0, 9.0);
}

