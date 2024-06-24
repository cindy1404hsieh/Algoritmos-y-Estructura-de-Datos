#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define ERROR 0 
lista_t *lista_crear()
{
		lista_t *lista = malloc(sizeof(lista_t));
		if(!lista)
			return NULL;
		lista->cantidad = 0;
		lista->nodo_inicio = NULL;
		lista->nodo_fin =NULL;
		return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
		if(!lista){
			return NULL;
		}
		nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
		if(!nodo_nuevo){
			return NULL;
		}
		nodo_nuevo->elemento = elemento;
		nodo_nuevo->siguiente = NULL;

		if(!lista->nodo_inicio){
			lista->nodo_inicio = nodo_nuevo;
			lista->nodo_fin = nodo_nuevo;
		}else{
			lista->nodo_fin->siguiente = nodo_nuevo;
			lista->nodo_fin = nodo_nuevo;
		}
		(lista->cantidad)++;

		return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{	
		if(!lista){
			return NULL;
		}
		nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
		if(!nodo_nuevo){
			return NULL;
		}
		nodo_nuevo->elemento = elemento;
		nodo_t *actual = NULL;
		if(lista->nodo_inicio)
			actual = lista->nodo_inicio;
		nodo_t *nodo_anterior = NULL;

		size_t i = 0;
		bool insertado = false;
	 
	
		if(posicion == 0 && lista_tamanio(lista) != 0){
			nodo_nuevo->siguiente = actual;
			lista->nodo_inicio = nodo_nuevo;
			(lista->cantidad)++;
		}
		else if(posicion >= lista_tamanio(lista)){
			free(nodo_nuevo);
			lista = lista_insertar(lista, elemento);
		}else if (posicion != 0 && posicion < lista_tamanio(lista)){
			while(!insertado){
				if(i < posicion){
					if((i+1) == posicion){
						nodo_anterior = actual;
					}
					actual = actual->siguiente;
					i++;
				}else if(i == posicion){
					nodo_nuevo->siguiente = actual;
					nodo_anterior->siguiente = nodo_nuevo;
					(lista->cantidad)++;
					insertado = true;
				}
			}
		}
		return lista;
}

void *lista_quitar(lista_t *lista)
{	
		if(lista_vacia(lista)){
			return NULL;
		}
		void *elemento_a_eliminar = lista->nodo_fin->elemento;
		size_t i = 0;
		nodo_t *nodo_anterior = NULL;
		bool nodo_anterior_encontrado= false;
		nodo_t *aux = lista->nodo_inicio;
 
		if(lista_tamanio(lista) == 1){
			lista->nodo_inicio= NULL;
			lista->nodo_fin= NULL;
			(lista->cantidad)--;
			free(aux);
			return elemento_a_eliminar;
		}else{
			while(!nodo_anterior_encontrado && i<lista_tamanio(lista)){
				if(i+2 == lista_tamanio(lista)){
					nodo_anterior = aux;
					nodo_anterior_encontrado = true;
				}else{
					i++;
					aux = aux->siguiente;
				}
			}
			aux = lista->nodo_fin;
			lista->nodo_fin = nodo_anterior;
			lista->nodo_fin->siguiente = NULL;
			(lista->cantidad)--;
			free(aux);
		}
		return elemento_a_eliminar;
}
 
void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
		if(lista_vacia(lista)){
			return NULL;
		}
		void *elemento_a_eliminar = NULL;

		size_t i = 0;
		bool eliminado = false;
		nodo_t *anterior = NULL;
		nodo_t *aux = lista->nodo_inicio;
		
		if(posicion >= lista_tamanio(lista)-1 && posicion != 0){
			elemento_a_eliminar = lista_quitar(lista);
		}else if(posicion == 0){
			if(lista->cantidad == 1){
				elemento_a_eliminar = aux->elemento;
				free(aux);
				lista->nodo_inicio = NULL;
				lista->nodo_fin = NULL;
				(lista->cantidad)--;
			}else{
				elemento_a_eliminar = aux->elemento;
				lista->nodo_inicio = aux->siguiente;
				free(aux);
				(lista->cantidad)--;
			}
		}else{
			while(!eliminado){
				if(i<posicion){
					if(i+1 == posicion){
						anterior = aux;
					}
					aux = aux->siguiente;
					i++;
				}else if(i == posicion){
					anterior->siguiente = aux->siguiente;
					elemento_a_eliminar = aux->elemento;
					(lista->cantidad)--;
					free(aux);
					eliminado = true;
				}
			}
		}
		return elemento_a_eliminar;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
		if(!lista){
			return NULL;
		}
		void *elemento;
		bool encontrado = false;
		int i = 0;
		nodo_t *aux = lista->nodo_inicio;

		if(posicion >= (lista_tamanio(lista))){
			return NULL;
		}else{
			while(!encontrado){
				if(i == posicion){
					elemento = aux->elemento;
					encontrado = true;
				}
				else{
					i++;
					aux = aux->siguiente;
				}
				
			}
		}
		return elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
		if(lista_vacia(lista)|| !comparador)
			return NULL;
		void *elemento_buscado;
		nodo_t *aux = lista->nodo_inicio;
		size_t i = 0;
		while(i<lista_tamanio(lista)){
			if(comparador(aux->elemento, contexto) == 0){
				return elemento_buscado = aux->elemento;
			}
			aux = aux->siguiente;
			i++;
		}
		return NULL;
}

void *lista_primero(lista_t *lista)
{
		if (lista_vacia(lista))
			return NULL;
		return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
		if (lista_vacia(lista))
			return NULL;
		return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
		if (!lista || !lista->nodo_inicio)
			return true;
		return false;
}

size_t lista_tamanio(lista_t *lista)
{
		if (lista_vacia(lista))
			return 0;
		return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	
		if(lista){
			if(lista->nodo_inicio){
				nodo_t *aux = lista->nodo_inicio;
				while(lista->cantidad != 0){
					aux = aux->siguiente;
					free(lista->nodo_inicio);
					lista->nodo_inicio = aux;
					lista->cantidad--;
				}
			}
			free(lista);
		}
		
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

		if(funcion){
			if(lista){
				if(lista->nodo_inicio){
					while(lista->nodo_inicio){
						nodo_t *aux = lista->nodo_inicio->siguiente;
						if(lista->nodo_inicio->elemento)
							funcion(lista->nodo_inicio->elemento);
						free(lista->nodo_inicio);
						lista->nodo_inicio = aux;
					}
				}
				free(lista);
			}
		}else{
			lista_destruir(lista);
		}
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
		if(iterador)
			free(iterador);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
		if(!lista){
			return NULL;
		}
		lista_iterador_t *lista_iterador = malloc(sizeof(lista_iterador_t));
		if(!lista_iterador){
			return NULL;
		}
		lista_iterador->lista = lista;
		lista_iterador->corriente = lista_iterador->lista->nodo_inicio;
		return lista_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
		if(!iterador || !iterador->lista)
			return NULL;
		
		if(!iterador->corriente)
			return false;
		return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
		if(!iterador || !iterador->lista){
			return NULL;
		}
		if(!lista_iterador_elemento_actual(iterador) && 
			!lista_iterador_tiene_siguiente(iterador))
			return false;
		iterador->corriente = iterador->corriente->siguiente;
		if(!iterador->corriente){
			return false;
		}
		return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
		if(!iterador || !iterador->lista || !iterador->corriente)
			return NULL;
		return iterador->corriente->elemento;
		
}
 
size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{ 
		if(!lista || !funcion || lista->cantidad== 0){
			return ERROR;
		}
		size_t cant_elementos_iterados = 0;
		nodo_t *aux = lista->nodo_inicio;
		 
		while(cant_elementos_iterados < lista->cantidad){
			cant_elementos_iterados++;
			if(!funcion(aux->elemento,contexto)){
				return cant_elementos_iterados;
			}
			aux = aux->siguiente;
		}
		return cant_elementos_iterados;
}
