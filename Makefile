
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

TPLRENDER = $(DEPS_DIR)/tplrender/tplrender

gen_sources := int.c uchar.c
gen_headers := $(gen_sources:.c=.h)

sources := ord.c $(gen_sources)
headers := $(sources:.c=.h)
objects := $(sources:.c=.o)
mkdeps  := $(objects:.o=.dep.mk)

test_binaries := tests/test



##############################
### BUILDING
##############################

.PHONY: all
all: objects tests

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
	rm -rf $(objects) $(mkdeps) $(gen_sources) $(gen_headers)


tests/test: CPPFLAGS += -D_DEFAULT_SOURCE
tests/test: int.o uchar.o


int.o: TYPE=int
int.o: TYPECLASSES=BOUNDED EQ ORD ENUM NUM
int.o: EXTRA=num_type=signed

uchar.o: TYPE=uchar
uchar.o: TYPECLASSES=BOUNDED EQ ORD ENUM NUM
uchar.o: EXTRA=char_funcs=true num_type=unsigned

$(gen_headers): %.h: header.h.jinja
	$(TPLRENDER) "$<" "$(TYPE)" $(if $(TYPENAME),--typename $(TYPENAME)) $(if $(FUNCNAME),--funcname $(FUNCNAME)) $(if $(MACRONAME), --macroname $(MACRONAME)) $(if $(FILENAME),--filename $(FILENAME)) --typeclasses $(TYPECLASSES) $(if $(REL_HEADERS),--rel-headers $(REL_HEADERS)) $(if $(SYS_HEADERS),--sys-headers $(SYS_HEADERS)) $(if $(EXTRA),--extra $(EXTRA)) --output $@

$(gen_sources): %.c: source.c.jinja %.h
	$(TPLRENDER) "$<" "$(TYPE)" $(if $(TYPENAME),--typename $(TYPENAME)) $(if $(FUNCNAME),--funcname $(FUNCNAME)) $(if $(MACRONAME), --macroname $(MACRONAME)) $(if $(FILENAME),--filename $(FILENAME)) --typeclasses $(TYPECLASSES) $(if $(REL_HEADERS),--rel-headers $(REL_HEADERS)) $(if $(SYS_HEADERS),--sys-headers $(SYS_HEADERS)) $(if $(EXTRA),--extra $(EXTRA)) --output $@


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


-include $(mkdeps)

