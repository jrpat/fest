> This readme is automatically generated from `fest.h` and `t/test`. See `Makefile`.


Fest
====

A `f`eatherweight t`est`ing library for C

Fest has no dependencies except:
- a C99 compiler
- string.h
- stdio.h


USAGE
-----

Tests can be spread across multiple compilation units.

To define a test, first:

    #include "fest.h"

then:

    TEST(test_name) {
      // chars
      IS_EQc(expected, actual)   //  expected == actual
      IS_NEc(expected, actual)   //  expected != actual
      IS_LTc(expected, actual)   //  expected <  actual
      IS_GTc(expected, actual)   //  expected >  actual
      IS_LEc(expected, actual)   //  expected <= actual
      IS_GEc(expected, actual)   //  expected >= actual

      // ints
      IS_EQi(expected, actual)   //  expected == actual
      IS_NEi(expected, actual)   //  expected != actual
      IS_LTi(expected, actual)   //  expected <  actual
      IS_GTi(expected, actual)   //  expected >  actual
      IS_LEi(expected, actual)   //  expected <= actual
      IS_GEi(expected, actual)   //  expected >= actual

      // doubles
      IS_EQd(expected, actual)   //  expected == actual
      IS_NEd(expected, actual)   //  expected != actual
      IS_LTd(expected, actual)   //  expected <  actual
      IS_GTd(expected, actual)   //  expected >  actual
      IS_LEd(expected, actual)   //  expected <= actual
      IS_GEd(expected, actual)   //  expected >= actual

      // pointers
      IS_EQp(expected, actual)   //  expected == actual
      IS_NEp(expected, actual)   //  expected != actual

      // strings
      IS_EQs(expected, actual)   //  strcmp(expected, actual) == 0
      IS_NEs(expected, actual)   //  strcmp(expected, actual) != 0
      
      // sized strings
      IS_EQz(exp, actual, len)   //  strncmp(exp, act, len) == 0
      IS_NEz(exp, actual, len)   //  strncmp(exp, act, len) != 0
    }


In your main compilation unit:

    FEST_INIT();  // set up global test state

    int main() {
      return FEST_RUN();
    }

or use the convenience macro which does the above for you:

    FEST_MAIN


Skip certain tests:

    SKIP_TEST(name_of_test);  // must be run inside a function


CONFIGURATION
-------------

Set the width of the output to N characters (maximum 60):

    cc ... -DFEST_WIDTH=N



SAMPLE OUTPUT
-------------

The output of `make test-pass`:
```

--------------------------------
Test                      Result
--------------------------------
char_equal ....................✔
char_not_equal ................✔
char_less_than ................✔
char_greater_than .............✔
char_less_equal ...............✔
char_greater_equal ............✔
double_equal ..................✔
double_not_equal ..............✔
double_less_than ..............✔
double_greater_than ...........✔
double_less_equal .............✔
double_greater_equal ..........✔
int_equal .....................✔
int_not_equal .................✔
int_less_than .................✔
int_greater_than ..............✔
int_less_equal ................✔
int_greater_equal .............✔
pointer_equal .................✔
pointer_not_equal .............✔
string_equal ..................✔
string_not_equal ..............✔
sized_string_equal ............✔
sized_string_not_equal ........✔

OK

```

The output of `make test-fail`:
```

--------------------------------
Test                      Result
--------------------------------
char_equal ....................✔
char_not_equal ................✔
char_less_than ................✔
char_greater_than .............✔
char_less_equal ...............✔
char_greater_equal ............✔
double_equal ..................✔
double_not_equal ..............✔
double_less_than ..............✔
double_greater_than ...........✔
double_less_equal .............✔
double_greater_equal ..........✔
fail_on_purpose ...............
  t/fail.c:5: fail: a == 9  // got 1
int_equal .....................✔
int_not_equal .................✔
int_less_than .................✔
int_greater_than ..............✔
int_less_equal ................✔
int_greater_equal .............✔
pointer_equal .................✔
pointer_not_equal .............✔
string_equal ..................✔
string_not_equal ..............✔
sized_string_equal ............✔
sized_string_not_equal ........✔

FAILED

```
