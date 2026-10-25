# pp_lab1 — build file
#
# Requires a C23 compiler: gcc >= 14 or clang >= 18
# (uses <stdckdint.h>, nullptr and [[noreturn]]).
#
#   make          build ./pp_lab1
#   make run      build and run
#   make clean    remove build/ and the binary
#   make rebuild  clean + all
#
# Override anything from the command line, e.g.:
#   make OPT="-O0 -g3 -fsanitize=address,undefined"
#   make STD=c2x CC=clang

TARGET   := pp_lab1
SRCDIR   := src
INCDIR   := include
BUILDDIR := build

# ---- toolchain -------------------------------------------------------------
CC       ?= cc
STD      ?= c23
OPT      ?= -O2

WARN     := -Wall -Wextra -Wpedantic -Wshadow -Wstrict-prototypes -Wvla

CFLAGS   += -std=$(STD) $(OPT) -g $(WARN) -I$(INCDIR)
CPPFLAGS += -MMD -MP
LDFLAGS  +=
# libstb provides the compiled stb_image implementation (Debian: libstb-dev)
LDLIBS   += -lstb -lm

# ---- sources ---------------------------------------------------------------
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ---- rules -----------------------------------------------------------------
.PHONY: all clean rebuild run help

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR):
	@mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

rebuild: clean all

help:
	@echo "targets: all (default), run, clean, rebuild"
	@echo "vars:    CC=$(CC) STD=$(STD) OPT=$(OPT)"
