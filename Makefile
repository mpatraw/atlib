
PLATS = mingw linux
PLAT = none

LUAINC =
LUALIB = -llua5.1

CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -Werror -pedantic -I./extern
LDFLAGS = -g -lm
SOURCES = $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXAMPLE_SOURCES = $(wildcard examples/*.c)
EXAMPLE_EXES = $(patsubst %.c,%.exe,$(EXAMPLE_SOURCES))

ifeq ($(PLAT),mingw)
	TARGET = at.dll
endif
ifeq ($(PLAT),linux)
	LDFLAGS += -Wl,-R,'$$ORIGIN'
	TARGET = libat.so
	CFLAGS += -fPIC
endif

all: $(SOURCES) $(TARGET) $(EXAMPLE_EXES)

.PHONY: clean format

$(LTARGET): $(OBJECTS)
	@echo CC -o $@
	@$(CC) atlua.c $(OBJECTS) -shared -fPIC $(LDFLAGS) -o $@

$(TARGET): $(OBJECTS)
	@echo CC -o $@
	@$(CC) $(OBJECTS) -shared -fPIC $(LDFLAGS) -o $@

.c.o:
	@echo CC -o $@
	@$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

%.exe: %.c
	@echo CC $< -o $@
	@$(CC) $(CFLAGS) -I. $< $(LDFLAGS) -L. -lat -lm -o $@

clean:
	@echo cleaning...
	-@rm $(TARGET) $(OBJECTS) $(EXAMPLE_EXES) 2> /dev/null
	@echo done.

format:
	astyle --options=astylerc -n examples/*.c at/*.h at/*/*.c at/*/*.h
