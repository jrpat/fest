#include "fest.h"

FEST_INIT();

int main(int argc, const char *argv[]) {
  if (! ((argc > 1) && !strcmp("fail", argv[1]))) {
    SKIP_TEST(fail_on_purpose);
  }
  return FEST_RUN();
}

