#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <stdbool.h>

#define MAX_NOMBRE 20
#define MAX_VERBO  20
#define MAX_TEXTO  200
 
enum tipo_accion{
	ACCION_INVALIDA,
	DESCUBRIR_OBJETO,
	REEMPLAZAR_OBJETO,
	ELIMINAR_OBJETO,
	MOSTRAR_MENSAJE
};

struct accion {
	enum tipo_accion tipo;
	char objeto[MAX_NOMBRE];
	char mensaje[MAX_TEXTO];
};

struct interaccion {
	char objeto[MAX_NOMBRE];
	char verbo[MAX_VERBO];
	char objeto_parametro[MAX_NOMBRE];
	struct accion accion;
}; 

struct objeto {
	char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
	bool es_asible;
};

struct sala {
	struct objeto **objetos;
	int cantidad_objetos;
	struct interaccion **interacciones;
	int cantidad_interacciones;
};

#endif // ESTRUCTURAS_H_
