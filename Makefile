
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

gen_types := bool char schar uchar short ushort int uint long ulong \
             llong ullong int8 uint8 int16 uint16 int32 uint32 \
             intmax uintmax ptrdiff wchar size
gen_sources := $(addsuffix .c,$(gen_types))
gen_headers := $(addsuffix .h,$(gen_types))

sources := $(wildcard *.c) $(gen_sources)
objects := $(sources:.c=.o)
mkdeps  := $(sources:.c=.dep.mk)



##############################
### BUILDING
##############################

.PHONY: all
all: objects

.PHONY: fast
fast: CPPFLAGS += -DNDEBUG -DNO_ASSERT -DNO_REQUIRE -DNO_DEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: all

.PHONY: objects
objects: $(objects)

$(gen_headers): genheader.py
$(gen_headers):
	$(PYTHON) genheader.py $($(basename $@)_names) --typeclasses $($(basename $@)_typeclasses) -o $@

$(gen_sources): %.c: %.h
$(gen_sources): gensource.py
$(gen_sources):
	$(PYTHON) gensource.py $($(basename $@)_names) $(basename $@) --typeclasses $($(basename $@)_typeclasses) -o $@

bool_names          := bool BOOL bool bool
bool_typeclasses    := BOUNDED:BOOL EQ ORD ENUM READ:BOOL TO_CONSTSTR:BOOL

char_names          := char CHAR char char
char_typeclasses    := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

schar_names         := schar SCHAR schar schar
schar_typeclasses   := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

uchar_names         := uchar UCHAR uchar uchar
uchar_typeclasses   := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

short_names         := short SHORT short short
short_typeclasses   := BOUNDED:SHORT EQ ORD ENUM NUM:SIGNED READ:STRTOL

ushort_names        := ushort USHORT ushort ushort
ushort_typeclasses  := BOUNDED:USHORT EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

int_names           := int INT int int
int_typeclasses     := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

uint_names          := uint UINT uint uint
uint_typeclasses    := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

long_names          := long LONG long long
long_typeclasses    := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

ulong_names         := ulong ULONG ulong ulong
ulong_typeclasses   := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

llong_names         := llong LLONG llong llong
llong_typeclasses   := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOLL

ullong_names        := ullong ULLONG ullong ullong
ullong_typeclasses  := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOULL

int8_names          := int8_t INT8 int8 int8
int8_typeclasses    := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

uint8_names         := uint8_t UINT8 uint8 uint8
uint8_typeclasses   := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

int16_names         := int16_t INT16 int16 int16
int16_typeclasses   := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

uint16_names        := uint16_t UINT16 uint16 uint16
uint16_typeclasses  := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

int32_names         := int32_t INT32 int32 int32
int32_typeclasses   := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOL

uint32_names        := uint32_t UINT32 uint32 uint32
uint32_typeclasses  := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUL

intmax_names        := intmax_t INTMAX intmax intmax
intmax_typeclasses  := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOIMAX

uintmax_names       := uintmax_t UINTMAX uintmax uintmax
uintmax_typeclasses := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUMAX

ptrdiff_names       := ptrdiff_t PTRDIFF ptrdiff ptrdiff
ptrdiff_typeclasses := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOIMAX

wchar_names         := wchar_t WCHAR wchar wchar
wchar_typeclasses   := BOUNDED:SIGNED EQ ORD ENUM NUM:SIGNED READ:STRTOIMAX

size_names          := size_t SIZE size size
size_typeclasses    := BOUNDED:UNSIGNED EQ ORD ENUM NUM:UNSIGNED READ:STRTOUMAX

.PHONY: clean
clean:
	rm -rf $(gen_sources) $(gen_headers) $(objects) $(mkdeps)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@

-include $(mkdeps)


