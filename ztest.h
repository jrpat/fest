#ifndef ZTEST__H
#define ZTEST__H

/*
** ZeptoTest - a featherweight testing library for C
**  
**  Goals
**  -----
**    - API is minimal and ergonomic
**    - Output looks nice and is easy to read
**    - Every reasonable option is configurable
**    - Library source is easily understandable
**
**  Main API
**  --------
**    TEST(group, name) { ... }
**      Defines a test named "group.name"
**
**    IS( ...body... , "description" );
**      Runs a test case.
**      The pass/fail output will be "description".
**
**    IS( ...body... );
**      Runs a test case.
**      The pass/fail output will be body.
**
**    ZTEST_INIT();
**      Sets up the top-level state for ZTest.
**      Call this once, in top-level scope.
**
**    ztest_runall(groupc, groupv)
**      Run defined tests.
**      If groupc > 0, only runs tests in groups contained in groupv.
**      If groupc == 0, groupv is ignored.
**
**
**  Utility Macros
**  --------------
**    STREQ(a, b)
**      Compares strings a and b.
**      Synonym for (0 == strcmp(a, b))
**
**    ZTEST_MAIN
**      Helper which sets up a main() function:
**        - Calls ZTEST_INIT()
**        - Defines `int main()` which calls ztest_runall(), using any
**          command-line arguments as group names.
**
**
**  Configuration
**  -------------
**    To configure, set these macros somewhere before including this
**    file for the first time. (Recommended: -D compiler flags)
**
**    #define ZTEST_SHOW_TESTS  1|0
**      Output each TEST as it is run?
**      Default: 1
**
**    #define ZTEST_SHOW_TIMER  1|0
**      Show the time each TEST took to run?
**      Default: 1
**
**    #define ZTEST_SPACE_TESTS 1|0
**      Add spaces in between TESTs in the output?
**      Default: 0
**
**    #define ZTEST_SHOW_PASSES 1|0
**      Show each passing IS() case?
**      Default: 0
**
**    #define ZTEST_SHOW_FAILS 1|0
**      Show each failing IS() case?
**      Default: 1
**
**    #define ZTEST_COLOR_PASS "<ansi code>"
**      Color for passing cases
**      Default: "\033[32m" (green)
**
**    #define ZTEST_COLOR_FAIL "<ansi code>"
**      Color for failing cases
**      Default: "\033[31m" (red)
**
**    #define ZTEST_COLOR_DIM  "<ansi code>"
**      Color for "faded" parts of the output
**      Default: "\033[90m" (grey)
**
**    #define ZTEST_MALLOC my_malloc
**    #define ZTEST_FREE   my_free
**      Use custom malloc/free functions
**      Default: malloc/free
**      Note: If one is defined, the other must also be.
**
*/

#include <stdio.h>
#include <string.h>


/**********************************************************************/
/*
** Configuration
*/

#ifndef ZTEST_SHOW_TESTS
#define ZTEST_SHOW_TESTS 1
#endif

#ifndef ZTEST_SHOW_TIMER
#define ZTEST_SHOW_TIMER 1
#endif

#ifndef ZTEST_SPACE_TESTS
#define ZTEST_SPACE_TESTS 0
#endif

#ifndef ZTEST_SHOW_PASSES
#define ZTEST_SHOW_PASSES 0
#endif

#ifndef ZTEST_SHOW_FAILS
#define ZTEST_SHOW_FAILS 1
#endif

#ifndef ZTEST_COLOR_PASS
#define ZTEST_COLOR_PASS "\033[32m"
#endif

#ifndef ZTEST_COLOR_FAIL
#define ZTEST_COLOR_FAIL "\033[31m"
#endif

#ifndef ZTEST_COLOR_DIM
#define ZTEST_COLOR_DIM "\033[90m"
#endif

#ifndef ZTEST_MALLOC
#include <stdlib.h>
#define ZTEST_MALLOC malloc
#define ZTEST_FREE   free
#endif


/**********************************************************************/
/*
** Public API
*/

#define IS(...) IS_OVERRIDE(__VA_ARGS__, IS_2, IS_1,)(__VA_ARGS__)

#define IS_2(body, desc)                                               \
  if ((body)) { ztest_pass(ZT_TESTARG, desc); }                        \
  else        { ztest_fail(ZT_TESTARG, desc); }                        \

#define IS_1(body)                                                     \
  IS_2(body, #body)                                                    \


#define TEST(_grp_, _name_)                                            \
  extern struct ZTestState ztest_state;                                \
  static void ZT_TESTFUNC_NAME(_grp_, _name_)(ZTestFunc*);             \
  __attribute__((constructor))                                         \
  static void ZT_REGISTER_NAME(_grp_, _name_)(void) {                  \
    ZTestFunc *f = ZTEST_MALLOC(sizeof(ZTestFunc));                    \
    f->fn = ZT_TESTFUNC_NAME(_grp_, _name_);                           \
    f->group = #_grp_;                                                 \
    f->name = #_name_;                                                 \
    if (!ztest_state.head) ztest_state.head = f;                       \
    if (ztest_state.tail) ztest_state.tail->next = f;                  \
    ztest_state.tail = f;                                              \
  }                                                                    \
  static void ZT_TESTFUNC_NAME(_grp_, _name_)(ZTestFunc *ZT_TESTARG)   \


#define ZTEST_INIT()                                                   \
  struct ZTestState ztest_state = {0, 0, 0, 0}                         \

#define ZTEST_MAIN                                                     \
  ZTEST_INIT();                                                        \
  int main(int argc, const char *argv[]) {                             \
    return ztest_runall(argc-1, argv+1);                               \
  }                                                                    \

#ifndef STREQ
# define STREQ(a, b) (0 == strcmp((a), (b)))
#endif


/**********************************************************************/
/*
** Util Macros
*/

#if defined(_MSC_VER)
# define ZT_WEAK __forceinline
#else
# define ZT_WEAK __attribute__((weak))
#endif

#ifdef _MSC_VER
/* MSVC warns about io.h */
# pragma warning(disable : 4820)
# pragma warning(push, 1)
# include <io.h>
# pragma warning(pop)
# define ZT_COLOR_OUTPUT() (_isatty(_fileno(stdout)))
#else
# include <unistd.h>
# define ZT_COLOR_OUTPUT() (isatty(STDOUT_FILENO))
#endif

#define IS_OVERRIDE(_1, _2, NAME, ...) NAME

/**********************************************************************/

#define ZT_FULLNAME_IMPL(pre, name, uniq) pre##_##name##uniq
#define ZT_FULLNAME(pre, name, uniq) ZT_FULLNAME_IMPL(pre, name, uniq)

#define ZT_TESTFUNC_NAME(grp, name) ZT_FULLNAME(z_testfunc, grp##_##name, __LINE__)
#define ZT_REGISTER_NAME(grp, name) ZT_FULLNAME(z_register, grp##_##name, __LINE__)

#define ZT_TESTARG __z_test__

#if ZTEST_SHOW_TESTS && ZTEST_SHOW_FAILS
# define ZT_PRNFAIL(s) \
    printf(" %s├ %sFAIL: %s%s\n", ZT_CLR_DIM, ZT_CLR_RED, s, ZT_CLR_OFF);
#else
# define ZT_PRNFAIL(s) \
    printf(" %sFAIL in %s.%s: %s%s\n", ZT_CLR_RED, t->group, t->name, ZT_CLR_OFF, s);
#endif

#if ZTEST_SHOW_TESTS && ZTEST_SHOW_PASSES
# define ZT_PRNPASS(s) \
    printf(" %s├ %sPASS: %s%s\n", ZT_CLR_DIM, ZT_CLR_GRN, s, ZT_CLR_OFF);
#else
# define ZT_PRNPASS(s) (void)(s)
#endif


/**********************************************************************/
/*
** Runtime
*/

#if ZTEST_SHOW_TIMER
#include <time.h>
#endif

typedef struct ZTestFunc ZTestFunc;
struct ZTestFunc {
  void (*fn)(ZTestFunc*);
  const char *group;
  const char *name;
  unsigned int npass;
  unsigned int nfail;
  ZTestFunc *next;
};


struct ZTestState {
  ZTestFunc *head;
  ZTestFunc *tail;
  int npass;
  int nfail;
};

extern struct ZTestState ztest_state;

const char *ZT_CLR_RED;
const char *ZT_CLR_GRN;
const char *ZT_CLR_DIM;
const char *ZT_CLR_OFF;

#if ZTEST_SHOW_TIMER
ZT_WEAK long ztest_ns() {
  /* TODO: make this more portable */
  struct timespec t;
  timespec_get(&t, TIME_UTC);
  return t.tv_nsec;
}
#endif

ZT_WEAK void ztest_pass(ZTestFunc *t, const char *desc) {
  t->npass++; ztest_state.npass++;
  ZT_PRNPASS(desc);
}

ZT_WEAK void ztest_fail(ZTestFunc *t, const char *desc) {
  t->nfail++; ztest_state.nfail++;
  ZT_PRNFAIL(desc);
}


ZT_WEAK void ztest_run(ZTestFunc *t) {
#if ZTEST_SHOW_TIMER
  long ns;
#endif

#if ZTEST_SHOW_TESTS
  printf(" %s┌─%s%s.%s\n", ZT_CLR_DIM, ZT_CLR_OFF, t->group, t->name);
#endif

#if ZTEST_SHOW_TIMER
  ns = ztest_ns();
#endif

  t->fn(t);

#if ZTEST_SHOW_TIMER
  ns = ztest_ns() - ns;
#endif

#if ZTEST_SHOW_TESTS
# if ZTEST_SHOW_TIMER
    printf(" %s└─DONE in %lins. %i passed.", ZT_CLR_DIM, ns, t->npass);
# else
    printf(" %s└─DONE. %d passed.", ZT_CLR_DIM, t->npass);
# endif
  if (t->nfail) { printf(" %s%d failed.", ZT_CLR_RED, t->nfail); }
  printf("%s\n", ZT_CLR_OFF);
# if ZTEST_SPACE_TESTS
    printf("\n");
# endif
#endif
}


ZT_WEAK int ztest_runall(int groupc, const char *const groupv[]) {
  if (!ztest_state.head) { printf("No tests defined!\n"); return 1; }

  ZT_CLR_RED = ZT_COLOR_OUTPUT() ? ZTEST_COLOR_FAIL : "";
  ZT_CLR_GRN = ZT_COLOR_OUTPUT() ? ZTEST_COLOR_PASS : "";
  ZT_CLR_DIM = ZT_COLOR_OUTPUT() ? ZTEST_COLOR_DIM  : "";
  ZT_CLR_OFF = ZT_COLOR_OUTPUT() ? "\033[m"         : "";

  printf(
    "\n┌──────────────────────────────────────┐"
    "\n│            Starting Tests            │"
    "\n└──────────────────────────────────────┘\n\n"
  );

  ZTestFunc *cur = ztest_state.head;
  if (groupc <= 0) {
    do { ztest_run(cur); } while ((cur = cur->next));
  } else {
    do {
      for (int i=0; i < groupc; i++) {
        if (STREQ(groupv[i], cur->group)) { ztest_run(cur); break; }
      }
    } while((cur = cur->next));
  }

  cur = ztest_state.head;
  do { ZTEST_FREE(cur); } while ((cur = cur->next));

  printf(
    "\n┌──────────────────────────────────────┐"
    "\n│ Testing          ┊    %s%7d Passed%s │"
    "\n│ Complete         ┊    %s%7d Failed%s │"
    "\n└──────────────────────────────────────┘\n\n",
    ZT_CLR_GRN, ztest_state.npass, ZT_CLR_OFF,
    (ztest_state.nfail ? ZT_CLR_RED : ""), ztest_state.nfail, ZT_CLR_OFF
  );

  return (ztest_state.nfail > 0);
}


/**********************************************************************/

#endif /* ZTEST__H */

