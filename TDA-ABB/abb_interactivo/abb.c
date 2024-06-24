#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define ERROR 0

abb_t *abb_crear(abb_comparador comparador)
{ 
		if(!comparador)
			return NULL;
		abb_t *arbol = malloc(sizeof(abb_t));
		if(!arbol)
			return NULL;
		arbol->tamanio = 0;
		arbol->nodo_raiz = NULL;
		arbol->comparador = comparador;
		return arbol;
}

nodo_abb_t *abb_insertar_rec(nodo_abb_t *raiz, void *elemento , int (*abb_comparador)(void *, void *))
{
		if(raiz == NULL){
			nodo_abb_t *nueva_hoja = malloc(sizeof(nodo_abb_t));
			if(!nueva_hoja)
				return NULL;
			nueva_hoja->elemento = elemento;
			nueva_hoja->izquierda = NULL;
			nueva_hoja->derecha = NULL;
			
			return nueva_hoja;
		}
		int comparador = abb_comparador(elemento,raiz->elemento);
		if(comparador <= 0)
			raiz->izquierda = abb_insertar_rec(raiz->izquierda, elemento , abb_comparador);
		else
			raiz->derecha = abb_insertar_rec(raiz->derecha, elemento, abb_comparador);
		return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
		if(arbol == NULL)
			return NULL;
		arbol->nodo_raiz = abb_insertar_rec(arbol->nodo_raiz, elemento , arbol->comparador);
		if(arbol->nodo_raiz){
			arbol->tamanio++;
			return arbol;
		}
		return NULL;
}

nodo_abb_t *extraer_mas_derecho(nodo_abb_t *raiz, nodo_abb_t **extraido)
{
		if(raiz->derecha == NULL){
			*extraido = raiz;
			return raiz->izquierda;
		}
		raiz->derecha = extraer_mas_derecho(raiz->derecha , extraido);
		return raiz; 
}
nodo_abb_t *abb_quitar_rec(nodo_abb_t *raiz, void *elemento ,int (*abb_comparador)(void *, void *) , void **a_borrar)
{
		if(raiz == NULL)
			return NULL;
		int comparador = abb_comparador(elemento,raiz->elemento);
		if(comparador == 0){
			*a_borrar = raiz->elemento;
			nodo_abb_t *izquierda = raiz->izquierda;
			nodo_abb_t *derecha = raiz->derecha;
			
			if(izquierda && derecha){
				nodo_abb_t *extraido = NULL;
				raiz->izquierda = extraer_mas_derecho(raiz->izquierda , &extraido);
				raiz->elemento = extraido->elemento;
				free(extraido);
				return raiz;
			}
			if(izquierda){
				free(raiz);
				return izquierda;
			}
			free(raiz);
			return derecha;
		}
		if(comparador < 0)
			raiz->izquierda = abb_quitar_rec(raiz->izquierda, elemento , abb_comparador , a_borrar);
		raiz->derecha = abb_quitar_rec(raiz->derecha, elemento, abb_comparador , a_borrar);
		return raiz;
}
void *abb_quitar(abb_t *arbol, void *elemento)
{
		if(arbol == NULL)
			return NULL;
		void *a_borrar = NULL;
		arbol->nodo_raiz = abb_quitar_rec(arbol->nodo_raiz, elemento , arbol->comparador , &a_borrar);
		if(a_borrar != NULL)
			arbol->tamanio--;
		return a_borrar;
}
void *abb_buscar_rec(nodo_abb_t *raiz, void *buscado , int (*abb_comparador)(void *, void *))
{
		if(raiz == NULL)
			return NULL;
		int comparador = abb_comparador(buscado,raiz->elemento);
		if(comparador == 0)
			return raiz->elemento;
		if(comparador < 0)
			return abb_buscar_rec(raiz->izquierda, buscado , abb_comparador);
		return abb_buscar_rec(raiz->derecha, buscado, abb_comparador);
}
void *abb_buscar(abb_t *arbol, void *buscado)
{
		if(arbol == NULL)
			return NULL;
		void *elemento_encontrado = abb_buscar_rec(arbol->nodo_raiz, buscado , arbol->comparador);
		return elemento_encontrado;
}

bool abb_vacio(abb_t *arbol)
{
		if(!arbol || !arbol->nodo_raiz)
			return true;
		return false;
}

size_t abb_tamanio(abb_t *arbol)
{
		if (arbol)
			return arbol->tamanio;
		return 0;
}
void recorrido_preorden_rec(nodo_abb_t *raiz,size_t *contador, bool (*funcion)(void *, void *), void *aux, int* se_sigue)
{
		if (!raiz)
			return;
		if((*se_sigue) == 0){
			(*contador)++;
			if(!funcion(raiz->elemento,aux)){
				(*se_sigue)= 1;
				return;
			}
		}
		recorrido_preorden_rec(raiz->izquierda,contador, funcion, aux, se_sigue);
		recorrido_preorden_rec(raiz->derecha,contador, funcion, aux , se_sigue);
}
void recorrido_inorden_rec(nodo_abb_t *raiz,size_t *contador, bool (*funcion)(void *, void *), void *aux, int* se_sigue)
{
		if (!raiz)
			return;
		recorrido_inorden_rec(raiz->izquierda,contador, funcion, aux, se_sigue);
		if((*se_sigue) == 0){
			(*contador)++;
			if(!funcion(raiz->elemento,aux)){
				(*se_sigue) = 1;
				return;
			}
		}
		recorrido_inorden_rec(raiz->derecha,contador, funcion, aux, se_sigue);
}
void recorrido_postorden_rec(nodo_abb_t *raiz,size_t *contador, bool (*funcion)(void *, void *), void *aux , int* se_sigue)
{
		if (!raiz)
			return;
		recorrido_postorden_rec(raiz->izquierda,contador, funcion, aux,se_sigue);
		recorrido_postorden_rec(raiz->derecha,contador, funcion, aux,se_sigue);
		if((*se_sigue)== 0){
			(*contador)++;
			if(!funcion(raiz->elemento,aux)){
				(*se_sigue) = 1;
				return;
			}
		}	
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
				     bool (*funcion)(void *, void *), void *aux)
{
		if(!funcion || !arbol)
			return ERROR;
		size_t contador = 0;
		int se_sigue = 0;
		switch (recorrido){
			case PREORDEN:
			recorrido_preorden_rec(arbol->nodo_raiz,&contador, funcion, aux , &se_sigue);
			break;

			case INORDEN:
			se_sigue = 0;
			recorrido_inorden_rec(arbol->nodo_raiz,&contador, funcion, aux , &se_sigue);
			break;

			case POSTORDEN:
			se_sigue = 0;
			recorrido_postorden_rec(arbol->nodo_raiz,&contador, funcion, aux , &se_sigue);
			break;
		}
		return contador;

}
void recorrer_preorden_rec(nodo_abb_t *raiz,void **array,size_t tamanio_array,size_t *contador)
{
		if (!raiz)
			return;
		if(*contador < tamanio_array && raiz){
			array[(*contador)] = raiz->elemento;
			(*contador)++;
		}
		recorrer_preorden_rec(raiz->izquierda,array,tamanio_array,contador);
		recorrer_preorden_rec(raiz->derecha,array,tamanio_array,contador);
}
void recorrer_inorden_rec(nodo_abb_t *raiz,void **array,size_t tamanio_array,size_t *contador)
{
		if (!raiz)
			return;
		recorrer_inorden_rec(raiz->izquierda,array,tamanio_array,contador);
		if(*contador < tamanio_array && raiz){
			array[(*contador)] = raiz->elemento;
			(*contador)++;
		}
		recorrer_inorden_rec(raiz->derecha,array,tamanio_array,contador);
}
void recorrer_postorden_rec(nodo_abb_t *raiz,void **array,size_t tamanio_array,size_t *contador)
{
		if (!raiz)
			return;
		recorrer_postorden_rec(raiz->izquierda,array,tamanio_array,contador);
		recorrer_postorden_rec(raiz->derecha,array,tamanio_array,contador);
		if(*contador < tamanio_array && raiz){
			array[(*contador)] = raiz->elemento;
			(*contador)++;
		}
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,size_t tamanio_array)
{
		if(arbol == NULL)
			return ERROR;
		size_t contador = 0;
		switch (recorrido){
			case PREORDEN:
			recorrer_preorden_rec(arbol->nodo_raiz,array,tamanio_array,&contador);
			break;

			case INORDEN:
			recorrer_inorden_rec(arbol->nodo_raiz,array,tamanio_array,&contador);
			break;

			case POSTORDEN:
			recorrer_postorden_rec(arbol->nodo_raiz,array,tamanio_array,&contador);
			break;
		}
		return contador;
}

void abb_destruir_todo_rec(nodo_abb_t *raiz,void (*destructor)(void *))
{
		if(raiz == NULL)
			return;
		abb_destruir_todo_rec(raiz->izquierda,destructor);
		abb_destruir_todo_rec(raiz->derecha,destructor);
		if(destructor)
			destructor(raiz->elemento);
		free(raiz);
}

void abb_destruir(abb_t *arbol)
{
		if(arbol){
			if(arbol->nodo_raiz)
				abb_destruir_todo_rec(arbol->nodo_raiz,NULL);
			free(arbol);
		}
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
		if(arbol){
			if(arbol->nodo_raiz)
				abb_destruir_todo_rec(arbol->nodo_raiz,destructor);
			free(arbol);
		}
}
