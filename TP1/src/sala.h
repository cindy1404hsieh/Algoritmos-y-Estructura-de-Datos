#ifndef SALA_H_
#define SALA_H_

#include <stdbool.h>

typedef struct sala sala_t;

/*
 * Crea una sala de escape a partir de un par de archivos.
 *
 * El string objetos es el path a un archivo con la definicion de los objetos
 * mientras que interacciones es el path a un archivo con la definicion de las
 * interacciones de los objetos.
 *
 * Devuelve una sala de escape creada con los datos leidos de los archivos o
 * NULL en caso de encontrar algún error en el proceso.
 *
 * La sala de escape devuelta debe ser liberada con la función de destrucción de
 * la sala antes de finalizar el programa.
 */
sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones);

/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos existentes en la sala de escape.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad);

/*
 * Devuelve true si existe una interacción válida utilizando el verbo en objeto1
 * y objeto2. Objeto1 siempre es el nombre de un objeto. Objeto2 puede ser un
 * string vacío para interacciones que no necesitan dos objetos.
 *
 * Devuelve false si la interacción no existe o si se encuentra algún error.
 */
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				  const char *objeto2);

/*
 * Destruye la sala de escape liberando toda la memoria reservada.
 */
void sala_destruir(sala_t *sala);

#endif // SALA_H_
