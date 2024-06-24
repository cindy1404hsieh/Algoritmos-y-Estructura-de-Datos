#include "src/hash.h"
#include "pa2m.h"
#include "src/lista.h"
#include <string.h>
#include <stdlib.h>

typedef struct par{
	char *clave;
	void *valor;
}par_t;

struct hash {
	lista_t **tabla;
	size_t almacenados;
	size_t capacidad;
};
char *duplicar_string(const char *s)
{
	if (!s)
		return NULL;

	char *p = malloc(strlen(s) + 1);
	if (!p)
		return NULL;

	strcpy(p, s);
	return p;
}
void destruir_string(void *elemento)
{
	if (!elemento)
		return;
	free(elemento);
}

bool recorrer_todo(const char *clave, void *valor, void *aux)
{
	if (!clave)
		return false;
	return true;
}
bool es_igual_a_D(const char *clave, void *valor, void *aux)
{
	if (!clave || strcmp(clave , "D")==0)
		return false;
	return true;
}

void pruebas_de_creacion()
{
	hash_t *h = hash_crear(1);
	pa2m_afirmar(h != NULL, "se pudo crear un hash con capacidad 1");
	pa2m_afirmar(h->capacidad == 3, "se pudo crear un hash con capacidad correcto(3)");
	pa2m_afirmar(h->almacenados == 0, "se pudo crear un hash con almacenado correcto");
	hash_destruir(h);
	hash_t *h1 = hash_crear(10);
	pa2m_afirmar(h1 != NULL, "se pudo crear un hash con capacidad 10");
	pa2m_afirmar(h1->capacidad == 10, "se pudo crear un hash con capacidad correcto(10)");
	pa2m_afirmar(h1->almacenados == 0, "se pudo crear un hash con almacenado correcto");
	hash_destruir(h1);
	hash_t *h2 = hash_crear(100);
	pa2m_afirmar(h2 != NULL, "se pudo crear un hash con capacidad 100");
	pa2m_afirmar(h2->capacidad == 100, "se pudo crear un hash con capacidad correcto(100)");
	pa2m_afirmar(h2->almacenados == 0, "se pudo crear un hash con almacenado correcto");
	hash_destruir(h2);

}
void pruebas_de_insercion_no_reemplazos()
{
	hash_t *h1 = hash_crear(3);
	void* anterior=NULL;
	hash_insertar(h1, "A", "1", &anterior);
	pa2m_afirmar(h1->almacenados == 1 , "se pudo agregar un elemento");
	char *valor1 = hash_obtener(h1, "A");
	pa2m_afirmar(strcmp(valor1 , "1")==0, "Busco el valor1 y  lo encuentro");
	hash_insertar(h1, "B", "2", &anterior);
	pa2m_afirmar(h1->almacenados == 2 , "se pudo agregar un elemento");
	char *valor2 = hash_obtener(h1, "B");
	pa2m_afirmar(strcmp(valor2 , "2")==0, "Busco el valor2 y  lo encuentro");
	hash_insertar(h1, "C", "3", &anterior);
	pa2m_afirmar(h1->almacenados == 3 , "se pudo agregar un elemento");
	char *valor3 = hash_obtener(h1, "C");
	pa2m_afirmar(strcmp(valor3 , "3")==0, "Busco el valor3 y  lo encuentro");
	hash_insertar(h1, "D", "4", &anterior);
	pa2m_afirmar(h1->almacenados == 4 , "se pudo agregar un elemento");
	char *valor4 = hash_obtener(h1, "D");
	pa2m_afirmar(strcmp(valor4 , "4")==0, "Busco el valor4 y  lo encuentro");
	
	pa2m_afirmar(hash_contiene(h1, "E") == false, "Busco el valor5 y  no lo encuentro");
	pa2m_afirmar(hash_cantidad(h1) == 4, "cantidad de elementos almacenados en el hash son 4");
	pa2m_afirmar(h1->capacidad == 6, "Se hizo rehash y ahora la capacidad es 6");
	hash_destruir(h1);

}
void pruebas_de_insercion_actualizacion()
{
	size_t capacidad = 3;
	hash_t *h1 = hash_crear(capacidad);
	void* anterior=NULL;
	hash_insertar(h1, "A", "1", &anterior);
	pa2m_afirmar(h1->almacenados == 1 , "se pudo agregar un elemento con valor 1");

	hash_insertar(h1, "A", "2", &anterior);
	pa2m_afirmar(h1->almacenados == 1 , "se agrego un elemento con clave repetida");
	pa2m_afirmar(strcmp((char *)anterior ,"1")==0 , "Se guardo el anterior elemento:(1)");

	hash_insertar(h1, "A", "3", &anterior);
	pa2m_afirmar(h1->almacenados == 1 , "se agrego un elemento con clave repetida");
	pa2m_afirmar(strcmp((char *)anterior ,"2")==0 , "Se guardo el anterior elemento:(2)");

	hash_insertar(h1, "A", "4", &anterior);
	pa2m_afirmar(h1->almacenados == 1 , "se agrego un elemento con clave repetida");
	pa2m_afirmar(strcmp((char *)anterior ,"3")==0 , "Se guardo el anterior elemento:(3)");

	pa2m_afirmar(h1->capacidad == 3, "la capacidad se mantiene en 3");
	hash_insertar(h1, "B", "7", &anterior);
	hash_insertar(h1, "C", "8", &anterior);
	hash_insertar(h1, "D", "9", &anterior);
	hash_insertar(h1, "C", "6", &anterior);
	pa2m_afirmar(strcmp((char *)anterior ,"8")==0 , "Se guardo el anterior elemento:(8)");
	pa2m_afirmar(h1->capacidad == 6, "ahora la capacidad es 6");
	pa2m_afirmar(hash_cantidad(h1) == 4, "cantidad de elementos almacenados en el hash son 4");

	hash_destruir(h1);
}
void pruebas_de_insercion()
{
	pa2m_nuevo_grupo("Pruebas de insercion sin reemplazos");
	pruebas_de_insercion_no_reemplazos();
	pa2m_nuevo_grupo("Pruebas de insercion con actualizacion");
	pruebas_de_insercion_actualizacion();
}
void pruebas_de_eliminacion()
{
	hash_t *h1 = hash_crear(3);
	void* anterior=NULL;
	hash_insertar(h1 , "A", "1", &anterior);
	pa2m_afirmar(h1!= NULL,"inserto A,1");
	char *valor1 = hash_quitar(h1, "A");
	pa2m_afirmar(strcmp((char *)valor1 ,"1")==0 , "Se quita el valor:(1)");
	char *valor2 = hash_quitar(h1, "A");
	pa2m_afirmar(!valor2 , "Se quita el valor:(1) de vuelta devuelve error");
	pa2m_afirmar(hash_cantidad(h1) == 0, "cantidad de elementos almacenados en el hash son 0");
	char *valor3 = hash_obtener(h1, "A");
	pa2m_afirmar(valor3==NULL, "Busco el valor borrado y  devuelve error");
	hash_insertar(h1 , "A", "1", &anterior);
	pa2m_afirmar(h1!= NULL,"inserto A,1");
	hash_insertar(h1 , "A", "3", &anterior);
	pa2m_afirmar(h1!= NULL,"inserto A,3");
	char *valor4 = hash_quitar(h1, "A");
	pa2m_afirmar(strcmp((char *)valor4 ,"3")==0 , "Quito con clave A se quita el valor:(3)");
	pa2m_afirmar(hash_cantidad(h1) == 0, "cantidad de elementos almacenados en el hash son 0");
	hash_destruir(h1);

}
void pruebas_de_iterador()
{
	hash_t *h1 = hash_crear(3);
	void* anterior=NULL;
	
	hash_insertar(h1, "B", "2", &anterior);
	hash_insertar(h1, "C", "3", &anterior);
	hash_insertar(h1, "D", "4", &anterior);
	hash_insertar(h1, "A", "1", &anterior);
	hash_insertar(h1, "E", "5", &anterior);
	hash_insertar(h1, "F", "6", &anterior);
	size_t i =hash_con_cada_clave(h1,recorrer_todo,NULL);
	pa2m_afirmar(i == 6, "se recorrieron todos los elementos(6)");
	size_t j =hash_con_cada_clave(h1,es_igual_a_D,NULL);
	pa2m_afirmar(j == 4, "se recorrieron 4 elementos hasta encontrar a 'D'");
	hash_destruir(h1);

}
void pruebas_de_null()
{
	hash_t *h1 = NULL;
	void* anterior=NULL;
	
	hash_insertar(h1, "B", "2", &anterior);

	pa2m_afirmar(h1 == NULL, "insertar en un hash NULL devuelve null");
	pa2m_afirmar(hash_obtener(h1 , "B") == NULL, "obtener un valor en un hash NULL devuelve null");
	pa2m_afirmar(hash_cantidad(h1) == 0, "un hash null es vacio");
	pa2m_afirmar(hash_quitar(h1 , "B") == NULL, "borrar de un hash null devuelve NULL");
	size_t i  =hash_con_cada_clave(h1,recorrer_todo,NULL);
	pa2m_afirmar(i == 0, "recorrer un hash null devuelve 0");

	hash_t *h2 = hash_crear(3);
	pa2m_afirmar(hash_insertar(h2, NULL, "3", &anterior) == NULL,"insertar con clave null devuelve null");
	pa2m_afirmar(hash_insertar(h2, "D", NULL, &anterior) != NULL,"insertar con valor null NO devuelve null");
	size_t j  =hash_con_cada_clave(h2,NULL,NULL);
	pa2m_afirmar(j == 0, "recorrer un hash con funcion null devuelve 0");
	pa2m_afirmar(hash_quitar(h2 , NULL) == NULL, "borrar de un hash con clave null devuelve NULL");
	hash_destruir(h2);

}
void pruebas_de_destruccion()
{
	hash_t *h1 = hash_crear(3);
	void* anterior=NULL;
	
	hash_insertar(h1, "B", duplicar_string("2"), &anterior);
	hash_insertar(h1, "C", duplicar_string("3"), &anterior);
	hash_insertar(h1, "D", duplicar_string("4"), &anterior);
	hash_insertar(h1, "A", duplicar_string("1"), &anterior);
	hash_insertar(h1, "E", duplicar_string("5"), &anterior);
	hash_insertar(h1, "F", duplicar_string("6"), &anterior);
	pa2m_afirmar(hash_cantidad(h1)==6 ,"se insertaron 6 elementos con valores reservando memoria con malloc");
	hash_destruir_todo(h1 , destruir_string);
	pa2m_afirmar(true ,"se destruyeron todo exitosamente");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de TDA HASH");
	pa2m_nuevo_grupo("Pruebas de creacion");
	pruebas_de_creacion();
	pa2m_nuevo_grupo("Pruebas de insercion");
	pruebas_de_insercion();
	pa2m_nuevo_grupo("Pruebas de eliminacion");
	pruebas_de_eliminacion();
	pa2m_nuevo_grupo("Pruebas de iterador interno");
	pruebas_de_iterador();
	pa2m_nuevo_grupo("Pruebas de destruccion");
	pruebas_de_destruccion();
	pa2m_nuevo_grupo("Pruebas de null");
	pruebas_de_null();
	return pa2m_mostrar_reporte();
}
