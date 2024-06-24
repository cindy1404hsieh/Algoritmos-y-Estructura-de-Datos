CFLAGS=-g -O1 -std=c99 -Wall -Wconversion -Wtype-limits  -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
OBJETOS=ejemplo/objetos.txt
INTERACCIONES=ejemplo/interacciones.txt

valgrind: pruebas
	valgrind ${VFLAGS} ./pruebas ${OBJETOS} ${INTERACCIONES}

sala: escape_pokemon.c src/*.c
	gcc ${CFLAGS} escape_pokemon.c src/*.c -o sala

valgrind-sala: sala
	valgrind ${VFLAGS} ./sala ${OBJETOS} ${INTERACCIONES}

pruebas: pruebas.c src/*.c src/*.h
	gcc ${CFLAGS} pruebas.c src/*.c -o pruebas

clean:
	rm -f sala pruebas
