#include "fest.h"

TEST(fail_on_purpose) {
  int a = 1;
  IS_EQi(9, a);
}

