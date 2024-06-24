VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -O0
CC = gcc

all: clean valgrind

archivo: src/* escape_pokemon.c
	$(CC) $(CFLAGS) src/*.c escape_pokemon.c  -o archivo 2>&1

valgrind: archivo
	valgrind $(VALGRIND_FLAGS) ./archivo chanu/obj.dat chanu/int.csv 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas chanu/obj.dat chanu/int.csv 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c  pruebas.c -o pruebas 2>&1

clean:
	rm -f archivo *.o pruebas 2>&1


