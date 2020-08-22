CC = gcc
CFLAGS = -std=c99 -Wall
C_SOURCES = $(wildcard ./src/*.c)
C_OBJECTS = $(SOURCES:.c=.o)
INCLUDES = -I./headers
EXECUTABLE = mcc

all: dist link

dist:
	mkdir dist

link:
	$(CC) $(CFLAGS) $(INCLUDES) $(C_SOURCES) -o ./dist/$(EXECUTABLE)

clean:
	rm -rf *.o ./dist/$(EXECUTABLE)

run:
	./$(EXECUTABLE)
