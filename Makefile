
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
          -Wno-type-limits -Wno-unused-parameter

TPLRENDER ?= $(DEPS_DIR)/tplrender/tplrender


libbase_types := uchar int ulong double ptrm_short

uchar_type := uchar
uchar_options := \
    --typeclasses NULL BOUNDED EQ ORD ENUM CHAR NUM INTEGER FROM_STR TO_STRM \
    --extra num_type=unsigned

int_type := int
int_options := \
    --typeclasses NULL BOUNDED EQ ORD ENUM NUM INTEGER FROM_STR TO_STRM \
    --extra num_type=signed

ulong_type := ulong
ulong_options := \
    --typeclasses NULL BOUNDED EQ ORD ENUM NUM INTEGER FROM_STR TO_STRM \
    --extra num_type=unsigned

double_type := double
double_options := \
    --typeclasses NULL EQ ORD NUM FLOAT FROM_STR \
    --extra num_type=float

ptrm_short_type := short *
ptrm_short_options := \
    --typeclasses NULL EQ ORD ENUM

# Generated files:
libbase_sources := $(addsuffix .c,$(libbase_types))
libbase_headers := $(libbase_sources:.c=.h)
libbase_objects := $(libbase_sources:.c=.o)

gen := \
    $(libbase_sources) \
    $(libbase_headers) \
    $(libbase_objects)

# Non-generated files:
sources := ord.c
objects := $(sources:.c=.o)

test_binaries := $(basename $(wildcard tests/*.c))

mkdeps  := $(objects:.o=.dep.mk) $(libbase_objects:.o=.dep.mk)



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
	rm -rf $(objects) $(gen) $(test_binaries) $(mkdeps)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


tests/test: $(libbase_objects)

$(libbase_sources): %.c: source.c.jinja
	$(TPLRENDER) $< "$($(*)_type)" $($(*)_options) -o $@

$(libbase_headers): %.h: header.h.jinja
	$(TPLRENDER) $< "$($(*)_type)" $($(*)_options) -o $@

$(libbase_objects): %.o: %.h


-include $(mkdeps)

