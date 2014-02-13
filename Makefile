
CC = gcc
CFLAGS = -std=c89 -Wall -pedantic -I./lua -I./extern
LDFLAGS = -g -lm
SOURCES = $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = libat.so
LTARGET = at.dll
EXAMPLE_SOURCES = $(wildcard examples/*.c)
EXAMPLE_EXES = $(patsubst %.c,%.exe,$(EXAMPLE_SOURCES))

all: $(SOURCES) $(TARGET) $(EXAMPLE_EXES) $(LTARGET)

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared -fPIC $(LDFLAGS) -o $@

$(LTARGET): $(OBJECTS)
	$(CC) $(OBJECTS) atlua.c -shared -fPIC $(LDFLAGS) -L./lua -llua51 -o $@

.c.o:
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -I. $< $(LDFLAGS) -L. -lat -o $@

clean:
	-@rm $(TARGET) $(LTARGET) $(OBJECTS) $(EXAMPLE_EXES)
