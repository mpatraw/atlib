
CC = gcc
CFLAGS = -c -std=c89 -Wall -pedantic -I./lua -I./extern
LDFLAGS = -g -lmingw32 -lm -L./lua -llua51
SOURCES = atlua.c $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = libat.so
LTARGET = at.dll
EXE = at.exe

all: $(SOURCES) $(TARGET) $(LTARGET) $(EXE)

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared $(LDFLAGS) -o $@

$(LTARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared $(LDFLAGS) -o $@

$(EXE): $(OBJECTS)
	$(CC) main.c $(LDFLAGS) -L. -lat -o $@

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	-@rm $(TARGET) $(LTARGET) $(OBJECTS) $(EXE)
