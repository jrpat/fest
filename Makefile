CFLAGS := -std=c99 -O0 -fPIC -Wall -Wextra -Werror -pedantic

test-src := t/*.c
test-bin := t/test

all: $(test-bin)
	-@$(test-bin) fail
	-@$(test-bin) pass

test-pass: $(test-bin)
	$(test-bin) pass

test-fail: $(test-bin)
	$(test-bin) fail

$(test-bin): fest.h $(test-src)
	$(CC) $(CFLAGS) -I. $(test-src) -o $@

README.md: fest.h $(test-bin) Makefile
	@printf '> This readme is automatically generated ' >$@
	@printf 'from `fest.h` and `t/test`. '             >>$@
	@printf 'See `Makefile`.\n\n'                      >>$@
	@grep '^\*\*' fest.h | sed -e 's/** \{0,2\}//'     >>$@
	@printf "\n\n"                                     >>$@
	@echo 'SAMPLE OUTPUT'                              >>$@
	@echo '-------------'                              >>$@
	@echo                                              >>$@
	@echo 'The output of `make test-pass`:'            >>$@
	@echo '```'                                        >>$@
	@-$(test-bin) pass                                2>>$@
	@echo '```'                                        >>$@
	@echo                                              >>$@
	@echo 'The output of `make test-fail`:'            >>$@
	@echo '```'                                        >>$@
	@-$(test-bin) fail                                2>>$@
	@echo '```'                                        >>$@
	@echo OK

clean:
	@rm -rf $(test-bin)

