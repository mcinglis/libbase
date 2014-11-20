
##############################
### VARIABLES
##############################

DEPS_ROOT ?= ./deps

CPPFLAGS += -I$(DEPS_ROOT)

cflags_std = -std=c11
cflags_warnings = -Wall -Wextra -Wpedantic \
                  -Wcomments -Wformat=2 -Wjump-misses-init -Wlogical-op \
                  -Wmissing-include-dirs -Wnested-externs \
                  -Wold-style-definition -Wredundant-decls -Wshadow \
                  -Wstrict-prototypes -Wunused-macros -Wvla -Wwrite-strings \
                  -Wno-override-init -Wno-unused-parameter
CFLAGS ?= $(cflags_std) -g -Og $(cflags_warnings)

sources = $(wildcard *.c)
objects = $(sources:.c=.o)

mkdeps = $(objects:.o=.dep.mk)

$(shell mkdir -p .make)


##############################
### BUILDING
##############################

.PHONY: all
all: objects

.PHONY: fast
fast: CPPFLAGS += -DNDEBUG -DNO_ASSERT -DNO_REQUIRE -DNO_DEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: objects

.PHONY: objects
objects: $(objects)

%.o: %.c .make/deps
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@

-include $(mkdeps)


##############################
### DEPENDENCIES
##############################

.PHONY: deps
deps: .make/deps
.make/deps: .make/libpp .make/libtypes .make/libmacro
	@touch $@

.PHONY: libpp
libpp: .make/libpp
.make/libpp: dep_path    = libpp
.make/libpp: dep_origin  = ~/projects/libpp
.make/libpp: dep_version = v2.*
.make/libpp: .make/libpp-build
	@touch $@

.PHONY: libtypes
libtypes: .make/libtypes
.make/libtypes: dep_path    = libtypes
.make/libtypes: dep_origin  = ~/projects/libtypes
.make/libtypes: dep_version = v1.*
.make/libtypes: .make/libtypes-build
	@touch $@

.PHONY: libmacro
libmacro: .make/libmacro
.make/libmacro: dep_path    = libmacro
.make/libmacro: dep_origin  = ~/projects/libmacro
.make/libmacro: dep_version = v1.*
.make/libmacro: .make/libmacro-build
	@touch $@

.make/%-clone:
	if [ ! -d $(DEPS_ROOT)/$(dep_path) ]; then \
	    git clone $(dep_origin) $(DEPS_ROOT)/$(dep_path); \
	fi
	@touch $@

.make/%-update: .make/%-clone
	cd $(DEPS_ROOT)/$(dep_path) && \
	  git pull --tags origin master && \
	  t=$$(git tag --list "$(dep_version)" | tail -n 1) && \
	  if [ -z "$$t" ]; then \
	    echo "No tag with the specified pattern."; \
	    false; \
	  fi && \
	  git tag --verify "$$t" && \
	  git checkout "$$t"
	@touch $@

.make/%-build: .make/%-update
	DEPS_ROOT=$(DEPS_ROOT) \
	  $(MAKE) --directory="$(DEPS_ROOT)/$(dep_path)"
	@touch $@


##############################
### CLEANING
##############################

.PHONY: clean
clean:
	rm -rf $(mkdeps) $(objects)

.PHONY: nuke
nuke: clean
	rm -rf .make $(DEPS_ROOT)


##############################
### META
##############################

# Don't delete any files resulting from nested wildcard rules.
.SECONDARY:


