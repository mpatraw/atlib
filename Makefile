
CC = gcc
CFLAGS = -c -std=c89 -Wall -pedantic -I./lua -I./extern
LDFLAGS = -g -lmingw32 -lm -L./lua -llua51
SOURCES = atlua.c $(wildcard at/*.c) $(wildcard at/*/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = at.dll
EXE = at.exe

all: $(SOURCES) $(TARGET) $(EXE)

.PHONY: clean

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) main.c $(LDFLAGS) -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -shared $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	-@rm at.dll *.o at/*.o at/*/*.o
