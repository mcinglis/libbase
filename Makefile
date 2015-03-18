
##############################
### VARIABLES
##############################

DEPS_DIR ?= deps

CPPFLAGS += -I$(DEPS_DIR)

CFLAGS ?= -std=c11 -g \
          -Wall -Wextra -pedantic \
          -Wcomments -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
          -Wnested-externs -Wold-style-definition -Wredundant-decls \
          -Wshadow -Wstrict-prototypes -Wunused-macros -Wvla -Wwrite-strings \
          -Wno-missing-field-initializers -Wno-override-init \
          -Wno-unused-parameter

TPLRENDER ?= $(DEPS_DIR)/tplrender/tplrender


test_types   := int uchar ptrm-short

int_type           := int
int_options        := --typeclasses BOUNDED EQ ORD ENUM NUM \
                      --extra num_type=signed

uchar_type         := uchar
uchar_options      := --typeclasses BOUNDED EQ ORD ENUM NUM \
                      --extra char_funcs=true num_type=unsigned

ptrm_short_type    := short *
ptrm_short_options := --typeclasses EQ ORD ENUM

test_gen_sources := $(addsuffix .c,$(test_types))
test_gen_headers := $(test_gen_sources:.c=.h)
test_gen_objects := $(test_gen_sources:.c=.o)
test_binaries := $(basename $(wildcard tests/*.c))

test_gen := $(test_gen_sources) \
            $(test_gen_headers) \
            $(test_gen_objects)

sources := $(wildcard *.c)
objects := $(sources:.c=.o)

mkdeps  := $(objects:.o=.dep.mk) $(test_gen_objects:.o=.dep.mk)



##############################
### BUILDING
##############################

.PHONY: all
all: objects tests

.PHONY: objects
objects: $(objects)

.PHONY: tests
tests: $(test_binaries)

.PHONY: test
test: tests
	./tests/test

.PHONY: clean
clean:
	rm -rf $(objects) $(test_gen) $(test_binaries) $(mkdeps)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


tests/test: $(test_gen_objects)

name_from_path = $(subst -,_,$1)

$(test_gen_headers): %.h: header.h.jinja
	$(eval n := $(call name_from_path,$*))
	$(TPLRENDER) $< "$($(n)_type)" $($(n)_options) -o $@

$(test_gen_sources): %.c: source.c.jinja
	$(eval n := $(call name_from_path,$*))
	$(TPLRENDER) $< "$($(n)_type)" $($(n)_options) -o $@

$(test_gen_objects): %.o: %.h


-include $(mkdeps)

