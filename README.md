# ZeptoTest

A featherweight, single-header testing library for C

**Goals:**
- API is minimal and ergonomic
- Output looks nice and is easy to read
- Every reasonable option is configurable
- Library source is easily understandable
- Runtime overhead is minimal


**Basic Usage:**
- `#include "ztest.h"` in any file which will contain a test.
- Define tests using `TEST(group, name) { ... }`
- Inside tests, run test cases using `IS( ...body... )`
  - *See below for more on `IS()`*
- In your main `test.c`, use `ZTEST_MAIN` to define a `main()`.
  - *See below for more flexible options*



## Main API

**`TEST(group, name) { ... }`**                                     <br>
Defines a test called `name` in group `group`.                      <br>
Both `group` and `name` must be valid C identifiers.                <br>

**`IS( ...body... , "description" )`**                              <br>
Runs a test case.                                                   <br>
The pass/fail output will be `description`.                         <br>

**`IS( ...body... )`**                                              <br>
Runs a test case.                                                   <br>
The pass/fail output will be body.                                  <br>

**`ZTEST_INIT();`**                                                 <br>
Sets up the top-level state for ZTest.                              <br>
Call this once, in top-level scope.

**`ztest_runall(groupc, groupv)`**                                  <br>
Runs defined tests.                                                 <br>
If `groupc > 0`, only runs tests in groups contained in `groupv`.   <br>
If `groupc == 0`, `groupv` is ignored.                              <br>



## Utility Macros

**`ZSTREQ(a, b)`**                                                  <br>
Compares strings a and b.                                           <br>
Synonym for `(0 == strcmp(a, b))`                                   <br>

**`ZTEST_MAIN`**                                                    <br>
Sets up your `main()` function as follows:
```c
ZTEST_INIT();
int main(int argc, const char *argv[]) {
  ztest_runall(argc, argv);
}
```



## Configuration
To configure, set these macros somewhere before including this
file for the first time. (Recommended: `-D` compiler flags)

**`#define ZTEST_SHOW_TESTS  1|0`**                                 <br>
Output each TEST as it is run?                                      <br>
*Default: `1`*                                                      <br>

**`#define ZTEST_SHOW_TIMER  1|0`**                                 <br>
Show the time each TEST took to run?                                <br>
*Default: `1`*                                                      <br>

**`#define ZTEST_SPACE_TESTS 1|0`**                                 <br>
Add spaces in between TESTs in the output?                          <br>
*Default: `0`*                                                      <br>

**`#define ZTEST_SHOW_PASSES 1|0`**                                 <br>
Show each passing IS() case?                                        <br>
*Default: `0`*                                                      <br>

**`#define ZTEST_SHOW_FAILS  1|0`**                                 <br>
Show each failing IS() case?                                        <br>
*Default: `1`*                                                      <br>

**`#define ZTEST_COLOR_PASS  "<ansi code>"`**                       <br>
Color for passing cases                                             <br>
*Default: `"\033[32m"` (green)*                                     <br>

**`#define ZTEST_COLOR_FAIL  "<ansi code>"`**                       <br>
Color for failing cases                                             <br>
*Default: `"\033[31m"` (red)*                                       <br>

**`#define ZTEST_COLOR_DIM   "<ansi code>"`**                       <br>
Color for "faded" parts of the output                               <br>
*Default: `"\033[90m"` (grey)*

**`#define ZTEST_MALLOC      my_malloc`**                           <br>
**`#define ZTEST_FREE        my_free`**                             <br>
Use a custom malloc function                                        <br>
*Default: `malloc`/`free`*                                          <br>
*(Note: If one is defined, the other must also be)*                 <br>



## Example Output

*Note: In the shell, these would be colorized*

Default output: (`make example-default`)
```
┌──────────────────────────────────────┐
│            Starting Tests            │
└──────────────────────────────────────┘

 ┌─group_one.test_one
 └─DONE in 545ns. 2 passed.
 ┌─group_one.test_two
 └─DONE in 345ns. 2 passed.
 ┌─group_two.test_one
 └─DONE in 2425ns. 2 passed.
 ┌─group_two.test_two
 ├ FAIL: strings are equal
 └─DONE in 1650ns. 1 passed. 1 failed.

┌──────────────────────────────────────┐
│ Testing          ┊          7 Passed │
│ Complete         ┊          1 Failed │
└──────────────────────────────────────┘
```

-----

No timer, show passes, space tests: (`make example-verbose`)
```
┌──────────────────────────────────────┐
│            Starting Tests            │
└──────────────────────────────────────┘

 ┌─group_one.test_one
 ├ PASS: a != b
 ├ PASS: a == b/2
 └─DONE. 2 passed.

 ┌─group_one.test_two
 ├ PASS: a is large
 ├ PASS: b is twice a
 └─DONE. 2 passed.

 ┌─group_two.test_one
 ├ PASS: !(0 == strcmp((sa), (sb)))
 ├ PASS: sa[0] == sb[0]
 └─DONE. 2 passed.

 ┌─group_two.test_two
 ├ FAIL: strings are equal
 ├ PASS: first chars are equal
 └─DONE. 1 passed. 1 failed.

┌──────────────────────────────────────┐
│ Testing          ┊          7 Passed │
│ Complete         ┊          1 Failed │
└──────────────────────────────────────┘
```



## Notes

- Test are run in the order they are defined.

- ZTest has no concept of setup/teardown. If several tests require the
  same setup/teardown, simply create functions like `setup_foo()` +
  `teardown_foo()`, and call them at the beginning/end of the test.

- When using `ZTEST_MAIN`, you can run tests from only some groups using
  command-line arguments:
```sh
./my-tests some_group other_group
```

- If the body of an `IS()` is a macro, it will be expanded before being
  stringified. If this is too verbose/messy, use a `"description"`.

- ZTest uses `timespec_get` if `ZTEST_SHOW_TIMER` is enabled,
  so a C11 compiler is needed for that feature.



## TODO

- [ ] Group setup/teardown?
- [ ] Is it possible for `IS` to print unexpanded bodies?

