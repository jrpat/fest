#include "fest.h"


TEST(char_equal) {
  char a='a', b='a';
  IS_EQc(a, b);
  IS_EQc('a', b);
  IS_EQc('a', 'a');
}

TEST(char_not_equal) {
  char a='a', b='z';
  IS_NEc(a, b);
  IS_NEc('a', b);
  IS_NEc('a', 'z');
}

TEST(char_less_than) {
  char a='a', b='z';
  IS_LTc(a, b);
  IS_LTc('a', b);
  IS_LTc('a', 'z');
}

TEST(char_greater_than) {
  char a='z', b='a';
  IS_GTc(a, b);
  IS_GTc('z', b);
  IS_GTc('z', 'a');
}

TEST(char_less_equal) {
  char a='a', b='z';
  IS_LEc(a, b);
  IS_LEc(b, b);
  IS_LEc('a', b);
  IS_LEc('z', b);
  IS_LEc('a', 'a');
  IS_LEc('z', 'z');
}

TEST(char_greater_equal) {
  char a='z', b='a';
  IS_GEc(a, b);
  IS_GEc(b, b);
  IS_GEc('a', b);
  IS_GEc('z', b);
  IS_GEc('a', 'a');
  IS_GEc('z', 'z');
}

