
##############################
### VARIABLES
##############################

DEPS_DIR ?= ./deps

CPPFLAGS += -I$(DEPS_DIR)

cflags_std := -std=c11
cflags_warnings := -Wall -Wextra -pedantic \
                   -Wcomments -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
                   -Wnested-externs -Wold-style-definition -Wredundant-decls \
                   -Wshadow -Wstrict-prototypes -Wunused-macros -Wvla \
                   -Wwrite-strings \
                   -Wno-missing-field-initializers -Wno-override-init \
                   -Wno-unused-parameter

CFLAGS ?= $(cflags_std) -g $(cflags_warnings)

TPLRENDER ?= $(DEPS_DIR)/tplrender/tplrender

test_gen_sources := int.c uchar.c ptrm-short.c
test_gen_headers := $(test_gen_sources:.c=.h)
test_gen_objects := $(test_gen_sources:.c=.o)
test_binaries    := tests/test

sources := $(wildcard *.c)
headers := $(sources:.c=.h)
objects := $(sources:.c=.o)

mkdeps  := $(objects:.o=.dep.mk)



##############################
### BUILDING
##############################

.PHONY: all
all: objects

.PHONY: fast
fast: CPPFLAGS += -DNDEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: all

.PHONY: objects
objects: $(objects)

.PHONY: tests
tests: $(test_binaries)

.PHONY: test
test: tests/test
	./tests/test

.PHONY: clean
clean:
	rm -rf $(objects) \
	       $(test_gen_sources) \
	       $(test_gen_headers) \
	       $(test_gen_objects) \
	       $(test_binaries) \
	       $(mkdeps)


tests/test: CPPFLAGS += -D_DEFAULT_SOURCE
tests/test: $(test_gen_objects)


int_type           := int
int_options        := --typeclasses BOUNDED EQ ORD ENUM NUM \
                      --extra num_type=signed

uchar_type         := uchar
uchar_options      := --typeclasses BOUNDED EQ ORD ENUM NUM \
                      --extra char_funcs=true num_type=unsigned

ptrm_short_type    := short *
ptrm_short_options := --typeclasses EQ ORD ENUM

name_from_path = $(subst -,_,$(basename $1))

$(test_gen_headers): %.h: header.h.jinja
	$(eval n := $(call name_from_path,$*))
	$(TPLRENDER) "$<" "$($(n)_type)" $($(n)_options) --output $@

$(test_gen_sources): %.c: source.c.jinja %.h
	$(eval n := $(call name_from_path,$*))
	$(TPLRENDER) "$<" "$($(n)_type)" $($(n)_options) --output $@


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


-include $(mkdeps)

