#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>
 
#define ERROR 0
#define MAXIMO_FACTOR_CARGA 0.75

typedef struct par{
	char *clave;
	void *valor;
}par_t;

struct hash {
	lista_t **tabla;
	size_t almacenados;
	size_t capacidad;
}; 
/*	recibe un string
*	devuelve un numero
*	random a base del numero
*/
size_t funcion_hash(const char *clave)

{
	    size_t hash, i;
	    for(hash = i = 0; i < strlen(clave); ++i)
	    {
	        hash += (size_t)clave[i];
	        hash += (hash << 10);
	        hash ^= (hash >> 6);
	    }
	    hash += (hash << 3);
	    hash ^= (hash >> 11);
	    hash += (hash << 15);

		return hash;
}
/*	compara las claves 
*	si son iguales devuelve 0
*	si no devuelve -1;
*/
int comparar_claves(void *_par, void *_clave)
{
		par_t *par = _par;
		char **clave = _clave;
		if(par && clave && strcmp(par->clave , *clave)== 0)
			return 0;
		return -1;
}
/*	recibe un string
*	duplica el string
*	y devuelve el string nuevo
*	en caso de error devuelve null
*/
char *duplicar_clave(const char *clave)
{
		if (!clave)
			return NULL;

		char *clave_nueva = malloc(strlen(clave) + 1);
		if (!clave_nueva)
			return NULL;

		strcpy(clave_nueva, clave);
		return clave_nueva;
}
/*	recibe un string
*	y destruye la clave
*/
void destruir_par_clave(par_t *par)
{
		if (!par){
			return;
		}
		free(par->clave);
		free(par);
}
/*
* 	recibe un par como primer parametro
*	y una clave como segundo parametro
*	se comparan entre si y si es la misma clave 
*	devuelve false si no true
*/
bool es_la_clave_buscada(void *_par, void *_clave)
{
		par_t *par = _par;
		char **clave = _clave;
		if(par && clave &&strcmp(par->clave , *clave)== 0)
			return false;
		return true;
}

hash_t *hash_crear(size_t capacidad)
{
	
		if(capacidad <= 3){
			hash_t *hash = malloc(sizeof(hash_t));
			if(!hash)
				return NULL;

			hash->tabla = NULL;
			hash->capacidad = 3;
			hash->almacenados = 0;

			lista_t **bloque = malloc(3*sizeof(lista_t));
			if(!bloque)
				return NULL;
			hash->tabla = bloque;

			for(int i = 0 ; i<3 ; i++){
				hash->tabla[i] = lista_crear();
			}
			return hash;
		}else{
			hash_t *hash = malloc(sizeof(hash_t));
			if(!hash)
				return NULL;

			hash->tabla = NULL;
			hash->capacidad = capacidad;
			hash->almacenados = 0;

			lista_t **bloque = malloc(capacidad*sizeof(lista_t));
			if(!bloque)
				return NULL;
			hash->tabla = bloque;

			for(int i = 0 ; i<capacidad ; i++){
				hash->tabla[i] = lista_crear();
			}
			return hash;
		}
}
/*
* 	quita el par de la posicion
*	e inserta el nuevo par en la posicion que estaba
*	el viejo par
*/
void actualizar_par(hash_t *hash, const char *clave,par_t *par,size_t hasheo)
{
		size_t posicion = lista_con_cada_elemento(hash->tabla[hasheo], es_la_clave_buscada ,&clave) -1 ;
		par_t *par_removido = lista_quitar_de_posicion(hash->tabla[hasheo], posicion);
		free(par_removido->clave);
		free(par_removido);
		lista_insertar_en_posicion(hash->tabla[hasheo], par, posicion);
}
/*
* 	agranda el doble la capacidad del hash recibido
*	y aplica de nuevo la funcion hash a cada par
*	y los coloca de nuevo en la posicion correcta
*	devuelve el hash rehasheado
*/
hash_t *rehash(hash_t *hash)
{
		lista_t **bloque = realloc(hash->tabla , 
						(unsigned long int)(hash->capacidad*2) * sizeof(lista_t));
		if(!bloque)
			return NULL;
		hash->tabla = bloque;

		for(size_t i = hash->capacidad ; i<(hash->capacidad)*2 ; i++){
			hash->tabla[i] = lista_crear();
		}
		hash->capacidad = hash->capacidad*2;
		for(size_t i = 0 ; i<hash->capacidad/2 ;i++){
			size_t j = 0 ;
			while(j<lista_tamanio(hash->tabla[i])){
				par_t *obtenido = lista_elemento_en_posicion(hash->tabla[i] , j);
				size_t hasheo = funcion_hash(obtenido->clave)%hash->capacidad;

				if(hasheo != i){
					lista_quitar_de_posicion(hash->tabla[i] , j);
					lista_insertar(hash->tabla[hasheo] , obtenido);
				}else{
					j++;
				}
			}
		}
		return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
		if(!hash || !clave)
			return NULL;
		size_t hasheo = funcion_hash(clave)%hash->capacidad;

		par_t *par = malloc(sizeof(par_t));
		if(!par)
			return NULL;
		par->clave = duplicar_clave(clave);
		par->valor = elemento;

		if(hash_contiene(hash, clave)){
			if(anterior)
				(*anterior) = hash_obtener(hash , clave);
			actualizar_par(hash,clave,par, hasheo);
		}else{
			if(anterior)
				(*anterior) = NULL;
			float factor_carga = (float)hash->almacenados/(float)hash->capacidad;
			if(factor_carga >= MAXIMO_FACTOR_CARGA)
				hash = rehash(hash);
			size_t hasheo = funcion_hash(clave)%hash->capacidad;
			lista_insertar(hash->tabla[hasheo], par);
			hash->almacenados++;
		}
		return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
		if(!hash || !clave)
			return NULL;
		void *valor_quitado;
		size_t hasheo = funcion_hash(clave)%hash->capacidad;
		size_t posicion = lista_con_cada_elemento(hash->tabla[hasheo], es_la_clave_buscada ,&clave) -1 ;

		par_t *par_quitado = lista_quitar_de_posicion(hash->tabla[hasheo], posicion);
		
		if(par_quitado){
			valor_quitado = par_quitado->valor;
			free(par_quitado->clave);
			free(par_quitado);
			hash->almacenados--;
			return valor_quitado;
		}
		return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
		if(!hash || !clave)
			return NULL;
		size_t hasheo = funcion_hash(clave)%hash->capacidad;
		par_t *obtenido = lista_buscar_elemento(hash->tabla[hasheo], comparar_claves,&clave);
		if(obtenido)
			return obtenido->valor;
		return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
		if(!hash || !clave)
			return NULL;
		size_t hasheo = funcion_hash(clave)%hash->capacidad;
		par_t *obtenido = lista_buscar_elemento(hash->tabla[hasheo], comparar_claves,&clave);
		if(!obtenido)
			return false;
		return true;
}

size_t hash_cantidad(hash_t *hash)
{
		if(!hash)
			return ERROR;
		return hash->almacenados;
}

void hash_destruir(hash_t *hash)
{
		if(hash)
			hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{

		if(!hash)
			return;
		par_t *par;
		if(destructor){
			for(size_t i = 0 ; i< hash->capacidad; i++){
				if(hash->tabla[i]){

					if(hash->tabla[i]->nodo_inicio){
						while(hash->tabla[i]->nodo_inicio){
							nodo_t *aux = hash->tabla[i]->nodo_inicio->siguiente;
							par = hash->tabla[i]->nodo_inicio->elemento;
							if(par)
								destructor(par->valor);
							destruir_par_clave(par);
							free(hash->tabla[i]->nodo_inicio);
							hash->tabla[i]->nodo_inicio = aux;
						}
					}
				}
				lista_destruir(hash->tabla[i]);
			}
		}
		else{
			for(size_t i = 0 ; i< hash->capacidad; i++){
				if(hash->tabla[i]){
					if(hash->tabla[i]->nodo_inicio){
						while(hash->tabla[i]->nodo_inicio){
							nodo_t *aux = hash->tabla[i]->nodo_inicio->siguiente;
							par = hash->tabla[i]->nodo_inicio->elemento;
							destruir_par_clave(par);
							free(hash->tabla[i]->nodo_inicio);
							hash->tabla[i]->nodo_inicio = aux;
						}
					}
				}
				lista_destruir(hash->tabla[i]);
			}
		}
		free(hash->tabla);
		free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
		if(!hash || !f || hash_cantidad(hash)==0)
			return ERROR;
		
		size_t cant_elementos_iterados = 0 ;
		
		for(size_t i = 0 ; i < hash->capacidad ;i++){
			nodo_t *actual = hash->tabla[i]->nodo_inicio;
			if(actual){
				size_t j = 0;
				while(j < hash->tabla[i]->cantidad){
					cant_elementos_iterados++;
					par_t *par = actual->elemento;
					if(!f(par->clave,par->valor,aux)){
						return cant_elementos_iterados;
					}
					actual = actual->siguiente;
					j++;
				}
			}
		}
		
		return cant_elementos_iterados;
	
}
