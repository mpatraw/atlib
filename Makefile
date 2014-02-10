
CC = gcc
CFLAGS = -std=c89 -Wall -pedantic -I./lua -I./extern
LDFLAGS = -g -lmingw32 -lm -L./lua -llua51
SOURCES = atlua.c $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = libat.so
LTARGET = at.dll
EXE = at.exe
EXAMPLE_SOURCES = $(wildcard examples/*.c)
EXAMPLE_EXES = $(patsubst %.c,%.exe,$(EXAMPLE_SOURCES))

all: $(SOURCES) $(TARGET) $(LTARGET) $(EXE) $(EXAMPLE_EXES)

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared $(LDFLAGS) -o $@

$(LTARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared $(LDFLAGS) -o $@

$(EXE): $(OBJECTS)
	$(CC) main.c $(LDFLAGS) -L. -lat -o $@

.c.o:
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -I. $< $(LDFLAGS) -L. -lat -o $@

clean:
	-@rm $(TARGET) $(LTARGET) $(OBJECTS) $(EXE)
