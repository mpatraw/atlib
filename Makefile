
PLATS = mingw linux
PLAT = none

LUAINC =
LUALIB = -llua5.1

CC = gcc
CFLAGS = -std=c89 -Wall -pedantic -I./extern
LDFLAGS = -g -lm
SOURCES = $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXAMPLE_SOURCES = $(wildcard examples/*.c)
EXAMPLE_EXES = $(patsubst %.c,%.exe,$(EXAMPLE_SOURCES))

ifeq ($(PLAT),mingw)
	TARGET = at.dll
endif
ifeq ($(PLAT),linux)
	LDFLAGS := -Wl,-R,'$$ORIGIN'
	TARGET = libat.so
endif

all: $(SOURCES) $(TARGET) $(EXAMPLE_EXES)

.PHONY: clean

$(LTARGET): $(OBJECTS)
	$(CC) atlua.c $(OBJECTS) -shared -fPIC $(LDFLAGS) -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared -fPIC $(LDFLAGS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -I. $< $(LDFLAGS) -L. -lat -o $@

clean:
	-@rm $(TARGET) $(OBJECTS) $(EXAMPLE_EXES)

