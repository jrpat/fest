#ifndef _FEST_H
#define _FEST_H

/*
**
**  Fest
**  ====
**  
**  A `f`eatherweight t`est`ing library for C
**  
**  Fest has no dependencies except:
**  - a C99 compiler
**  - string.h
**  - stdio.h
**  
**  
**  USAGE
**  -----
**  
**  Tests can be spread across multiple compilation units.
**  
**  To define a test, first:
**  
**      #include "fest.h"
**  
**  then:
**  
**      TEST(test_name) {
**        // chars
**        IS_EQc(expected, actual)   //  expected == actual
**        IS_NEc(expected, actual)   //  expected != actual
**        IS_LTc(expected, actual)   //  expected <  actual
**        IS_GTc(expected, actual)   //  expected >  actual
**        IS_LEc(expected, actual)   //  expected <= actual
**        IS_GEc(expected, actual)   //  expected >= actual
**  
**        // ints
**        IS_EQi(expected, actual)   //  expected == actual
**        IS_NEi(expected, actual)   //  expected != actual
**        IS_LTi(expected, actual)   //  expected <  actual
**        IS_GTi(expected, actual)   //  expected >  actual
**        IS_LEi(expected, actual)   //  expected <= actual
**        IS_GEi(expected, actual)   //  expected >= actual
**  
**        // doubles
**        IS_EQd(expected, actual)   //  expected == actual
**        IS_NEd(expected, actual)   //  expected != actual
**        IS_LTd(expected, actual)   //  expected <  actual
**        IS_GTd(expected, actual)   //  expected >  actual
**        IS_LEd(expected, actual)   //  expected <= actual
**        IS_GEd(expected, actual)   //  expected >= actual
**  
**        // pointers
**        IS_EQp(expected, actual)   //  expected == actual
**        IS_NEp(expected, actual)   //  expected != actual
**  
**        // strings
**        IS_EQs(expected, actual)   //  strcmp(expected, actual) == 0
**        IS_NEs(expected, actual)   //  strcmp(expected, actual) != 0
**        
**        // sized strings
**        IS_EQz(exp, actual, len)   //  strncmp(exp, act, len) == 0
**        IS_NEz(exp, actual, len)   //  strncmp(exp, act, len) != 0
**      }
**  
**  
**  In your main compilation unit:
**  
**      FEST_INIT();  // set up global test state
**  
**      int main() {
**        return FEST_RUN();
**      }
**  
**  or use the convenience macro which does the above for you:
**  
**      FEST_MAIN
**  
**  
**  Skip certain tests:
**  
**      SKIP_TEST(name_of_test);  // must be run inside a function
**  
**  
**  CONFIGURATION
**  -------------
**  
**  Set the width of the output to N characters (maximum 60):
**  
**      cc ... -DFEST_WIDTH=N
** 
*/

#include <stdio.h>
#include <string.h>

#define FEST_WIDTH 32

#define PRN(...) fprintf(stderr, __VA_ARGS__)

#define FEST_INIT()                                                    \
  static Test THEAD={0};                                               \
  Fest FEST; static int FEST_RUN() {                                   \
    int tw = FEST_WIDTH;                                               \
    PRN("\n%.*s", tw, FLN);                                            \
    PRN("\n%-*s%s", tw-6, "Test", "Result");                           \
    PRN("\n%.*s", tw, FLN);                                            \
    Test *t = FEST.head; while((t = t->next)){ if (t->skip) continue;  \
      PRN("%s%s %.*s", FEST.n ? "" : "\n", t->s, (tw-t->l-2), FDT);    \
      FEST.n = 0; t->f(); if (!FEST.n) { PRN("✔"); } }                 \
    PRN("\n\n%s\n\n", FEST.N ? "FAILED" : "OK");                       \
    return FEST.N ? 1 : 0;                                             \
  }  Fest FEST = {0,0, &THEAD, &THEAD}                                 \

#define TEST(name)                                                     \
  void test__##name(void);                                             \
  Test t__##name={.s=#name, .l=(int)sizeof(#name)-1, .f=test__##name}; \
  FEST_INITIALIZER(init__##name) {                                     \
    FEST.tail->next = &t__##name; FEST.tail = &t__##name;              \
  } void test__##name(void)                                            \

#define SKIP_TEST(name) extern Test t__##name; t__##name.skip = 1

#define FEST_MAIN  FEST_INIT  int main() { return FEST_RUN(); }


#define IS(x) if (!(x)) { FEST_FAIL(); fputs(#x "\n", stderr); }

#define IS_EQc(e,a)   FEST_IS(==, "'%c'", e,a,((char)(a)))
#define IS_NEc(e,a)   FEST_IS(!=, "'%c'", e,a,((char)(a)))
#define IS_LTc(e,a)   FEST_IS(< , "'%c'", e,a,((char)(a)))
#define IS_GTc(e,a)   FEST_IS(> , "'%c'", e,a,((char)(a)))
#define IS_LEc(e,a)   FEST_IS(<=, "'%c'", e,a,((char)(a)))
#define IS_GEc(e,a)   FEST_IS(>=, "'%c'", e,a,((char)(a)))

#define IS_EQi(e,a)   FEST_IS(==, "%li",  e,a,((long)(a)))
#define IS_NEi(e,a)   FEST_IS(!=, "%li",  e,a,((long)(a)))
#define IS_LTi(e,a)   FEST_IS(< , "%li",  e,a,((long)(a)))
#define IS_GTi(e,a)   FEST_IS(> , "%li",  e,a,((long)(a)))
#define IS_LEi(e,a)   FEST_IS(<=, "%li",  e,a,((long)(a)))
#define IS_GEi(e,a)   FEST_IS(>=, "%li",  e,a,((long)(a)))

#define IS_EQd(e,a)   FEST_IS(==, "%f",   e,a,((double)(a)))
#define IS_NEd(e,a)   FEST_IS(!=, "%f",   e,a,((double)(a)))
#define IS_LTd(e,a)   FEST_IS(< , "%f",   e,a,((double)(a)))
#define IS_GTd(e,a)   FEST_IS(> , "%f",   e,a,((double)(a)))
#define IS_LEd(e,a)   FEST_IS(<=, "%f",   e,a,((double)(a)))
#define IS_GEd(e,a)   FEST_IS(>=, "%f",   e,a,((double)(a)))

#define IS_EQp(e,a)   FEST_IS(==, "%p",   e,a,((void*)(a)))
#define IS_NEp(e,a)   FEST_IS(!=, "%p",   e,a,((void*)(a)))

#define IS_EQs(e,a)   FEST_IS(==, "\"%s\"", 0,strcmp((e),(a)),(a))
#define IS_NEs(e,a)   FEST_IS(!=, "\"%s\"", 0,strcmp((e),(a)),(a))

#define IS_EQz(e,a,n) FEST_IS(==, "\"%s\"", 0,strncmp((e),(a),(n)),(a))
#define IS_NEz(e,a,n) FEST_IS(!=, "\"%s\"", 0,strncmp((e),(a),(n)),(a))

/**********************************************************************/

typedef struct Test Test;
struct Test {const char *s; int l; void(*f)(); Test *next; int skip;};

typedef struct {int N, n; Test *head, *tail;} Fest;
extern Fest FEST;

#define FLN "----------------------------------------------------------"
#define FDT ".........................................................."

#define FEST_FAIL()                                                    \
  if (!FEST.n) { PRN("\n"); } FEST.n++; FEST.N++;                      \
  PRN("  " __FILE__ ":%i: fail: ", __LINE__);                          \

#define FEST_IS(comp, fmt, expected, actual, got)                      \
  if (!((expected) comp (actual))) { FEST_FAIL();                      \
    fputs(#actual " " #comp " " #expected, stderr);                    \
    PRN("  // got " fmt "\n", (got)); }                                \

#if defined(_MSC_VER)
# pragma section(".CRT$XCU",read)
# define FEST_INITIALIZER2_(f,p)                                       \
    static void f(void);                                               \
    __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f;           \
    __pragma(comment(linker,"/include:" p #f "_"))                     \
    static void f(void)
# ifdef _WIN64
#   define FEST_INITIALIZER(f) FEST_INITIALIZER2_(f,"")
# else
#   define FEST_INITIALIZER(f) FEST_INITIALIZER2_(f,"_")
# endif
#else
# define FEST_INITIALIZER(f)                                           \
    static void f(void) __attribute__((constructor));                  \
    static void f(void)
#endif



#endif /* _FEST_H */

