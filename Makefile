UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
  CC = clang
endif
ifeq ($(UNAME),Linux)
  CC = gcc
endif

CFLAGS += -g -O0
CFLAGS += -Wall -Wextra -Werror -pedantic
CFLAGS += -fsanitize=undefined
CFLAGS += -fstrict-aliasing -Wstrict-aliasing=3

example-default: example.c ztest.h
	$(CC) -std=c11 $(CFLAGS) example.c -o example-default
	- ./example-default

example-verbose: example.c ztest.h
	$(CC) -std=c99 $(CFLAGS) example.c -o example-verbose \
		-DZTEST_SHOW_TIMER=0 \
		-DZTEST_SPACE_TESTS=1 \
		-DZTEST_SHOW_PASSES=1
	- ./example-verbose

all: example-default example-verbose

clean:
	-rm example-default example-verbose  2>/dev/null

