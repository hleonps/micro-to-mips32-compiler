CC = gcc
CFLAGS = -std=c99 -Wall
C_SOURCES = $(wildcard ./src/*.c)
C_OBJECTS = $(SOURCES:.c=.o)
INCLUDES = -I./headers
EXECUTABLE = mcc #El archivo ejecutable que se creará.

#Comprueba que los sources sean de la misma versión que el ejecutable
all: link

#Se usa el ensamblador o compilador para crear los archivos objetos. Se usa de entrada los archivos en SOURCES.
link:
	$(CC) $(CFLAGS) $(INCLUDES) $(C_SOURCES) -o ./dist/$(EXECUTABLE)

#Comando para borrar los archivos objetos y el ejecutable
clean:
	rm -rf *.o ./dist/$(EXECUTABLE)

#Comando para correr el ejecutable.
run:
	./$(EXECUTABLE)
