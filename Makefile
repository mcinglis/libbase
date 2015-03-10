
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
                   -Wno-override-init -Wno-type-limits -Wno-unused-parameter

CFLAGS ?= $(cflags_std) -g $(cflags_warnings)

PYTHON ?= python

RENDER_JINJA_SCRIPT ?= $(DEPS_DIR)/render-jinja/render_jinja.py
RENDER_JINJA ?= $(PYTHON) $(RENDER_JINJA_SCRIPT)

uc = $(shell echo $1 | tr [:lower:] [:upper:])

signed_types   := char schar short int long llong int8 int16 int32 intmax \
                  ptrdiff wchar
unsigned_types := uchar ushort uint ulong ullong uint8 uint16 uint32 \
                  uintmax size
types := bool ptr ptrm $(signed_types) $(unsigned_types)

int8_type    := int8_t
uint8_type   := uint8_t
int16_type   := int16_t
uint16_type  := uint16_t
int32_type   := int32_t
uint32_type  := uint32_t
intmax_type  := intmax_t
uintmax_type := uintmax_t
ptrdiff_type := ptrdiff_t
wchar_type   := wchar_t
size_type    := size_t
ptr_type     := void const *
ptrm_type    := void *

typeclasses_default := BOUNDED EQ ORD ENUM NUM FROM_STR TO_STRM

bool_typeclasses := BOUNDED EQ ORD ENUM FROM_STR TO_STR
ptr_typeclasses  := EQ ORD
ptrm_typeclasses := EQ ORD

char_extra  := CHAR
schar_extra := CHAR
uchar_extra := CHAR

$(foreach t,$(signed_types),$(eval $(t)_num_type := signed))
$(foreach t,$(unsigned_types),$(eval $(t)_num_type := unsigned))

bool_min_bound   := false
bool_max_bound   := true
short_min_bound  := SHRT_MIN
short_max_bound  := SHRT_MAX
ushort_max_bound := USHRT_MAX
$(foreach t,$(unsigned_types),$(eval $(t)_min_bound := 0))

gen_sources := $(addsuffix .c,$(types))
gen_headers := $(addsuffix .h,$(types))

sources := $(wildcard *.c) $(gen_sources)
objects := $(sources:.c=.o)
mkdeps  := $(sources:.c=.dep.mk)



##############################
### BUILDING
##############################


.PHONY: all
all: objects libbase.o


.PHONY: fast
fast: CPPFLAGS += -DNDEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: all


.PHONY: objects
objects: $(objects)


libbase.o: $(objects)
	$(LD) -r $^ -o $@


$(gen_sources): %.c: %.h
$(gen_headers) $(gen_sources): $(RENDER_JINJA_SCRIPT)

$(gen_headers): %.h: header.h.jinja
	$(eval n := $*)
	$(eval N := $(call uc,$n))
	$(RENDER_JINJA) $< "type_def_header=" "extra=$($(n)_extra)" "type=$(or $($(n)_type),$n)" "macroname=$N" "funcname=$n" "typeclasses=$(or $($(n)_typeclasses),$(typeclasses_default))" -o $@

$(gen_sources): %.c: source.c.jinja
	$(eval n := $*)
	$(eval N := $(call uc,$n))
	$(RENDER_JINJA) $< "header_path=$n.h" "extra=$($(n)_extra)" "type=$(or $($(n)_type),$n)" "macroname=$N" "funcname=$n" "typeclasses=$(or $($(n)_typeclasses),$(typeclasses_default))" "num_type=$($(n)_num_type)" "min_bound=$($(n)_min_bound)" "max_bound=$($(n)_max_bound)" -o $@


.PHONY: clean
clean:
	rm -rf $(gen_sources) $(gen_headers) $(objects) libbase.o $(mkdeps)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


-include $(mkdeps)

