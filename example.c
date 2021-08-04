#include "ztest.h"


TEST(group_one, test_one) {
  int a = 1;
  int b = 2;
  IS( a != b );
  IS( a == b/2 )
}

TEST(group_one, test_two) {
  int a = 11;
  int b = 22;
  IS( a > 10   , "a is large" );
  IS( a == b/2 , "b is twice a" );
}

TEST(group_two, test_one) {
  const char *sa = "zfoo";
  const char *sb = "zbar";
  IS( !STREQ(sa, sb) );
  IS( sa[0] == sb[0] );
}

TEST(group_two, test_two) {
  const char *sa = "zfoo";
  const char *sb = "zbar";
  IS( STREQ(sa, sb)  , "strings are equal" ); /* this will fail */
  IS( sa[0] == sb[0] , "first chars are equal" );
}


ZTEST_MAIN

