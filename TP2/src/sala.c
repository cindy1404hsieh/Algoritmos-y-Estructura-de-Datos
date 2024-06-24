#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "sala.h"
#include "lista.h"
#include "objeto.h"
#include "interaccion.h"
#include "hash.h"

#define MAX_LINEA 1024
#define NO_ENCONTRADO -1

typedef struct vector{
	char **nombres;
	int indice;
}vector_t;

struct sala {
	hash_t *objetos;
	int cantidad_objetos;
	lista_t *interacciones;
	int cantidad_interacciones;

	hash_t *conocidos;
	hash_t *poseidos;
	
	bool pude_escapar;
};


sala_t *inicializar_sala()
{
		sala_t *sala = malloc(sizeof(sala_t));
		if(!sala)
			return NULL;
		sala->objetos = hash_crear(3);
		sala->cantidad_objetos = 0;
		sala->conocidos = hash_crear(3);
		sala->poseidos = hash_crear(3);
		sala->interacciones = lista_crear();
		sala->cantidad_interacciones = 0;
		sala->pude_escapar = false;
		return sala;

}
sala_t *rellenar_sala_objetos(sala_t *sala , FILE *arc_objeto)
{
		char linea[MAX_LINEA];
		while(fgets(linea,MAX_LINEA,arc_objeto) != NULL){

			struct objeto *objeto_aux = objeto_crear_desde_string(linea);
			if(!objeto_aux){
				sala_destruir(sala);
				return NULL;
			}

			hash_insertar(sala->objetos, objeto_aux->nombre, objeto_aux, NULL);
			if(hash_cantidad(sala->conocidos)== 0){
				hash_insertar(sala->conocidos, objeto_aux->nombre, objeto_aux, NULL);
			}
			sala->cantidad_objetos++;
		}
		return sala;
}
sala_t *rellenar_sala_interaccion(sala_t *sala , FILE *arc_interaccion)
{
		char linea[MAX_LINEA];
		while(fgets(linea,MAX_LINEA,arc_interaccion) != NULL){
			
			struct interaccion *interaccion_aux = interaccion_crear_desde_string(linea);
			if(!interaccion_aux){
				sala_destruir(sala);
				return NULL;
			}
			lista_insertar(sala->interacciones, interaccion_aux);
			sala->cantidad_interacciones++;
		}
		return sala;
}
sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{

		FILE *arc_objeto = fopen(objetos,"r");
		if(!arc_objeto)
			return NULL;
	
		FILE *arc_interaccion = fopen(interacciones,"r");
		if(!arc_interaccion){
			fclose(arc_objeto);
			return NULL;
		}
		
		
		sala_t *sala =inicializar_sala();
		if(!sala)
			return NULL;

		rellenar_sala_objetos(sala , arc_objeto);

		rellenar_sala_interaccion(sala , arc_interaccion);
				
		if(!sala->interacciones || !sala->objetos || sala->cantidad_interacciones == 0 || sala->cantidad_objetos == 0){
			fclose(arc_objeto);
			fclose(arc_interaccion);
			sala_destruir(sala);
			return NULL;
		}
		fclose(arc_objeto);
		fclose(arc_interaccion);
		return sala;
}
/*la funcion agrega la clave al vector pasado como void *aux
*/
bool agregar_clave_a_vector(const char *clave, void *valor, void *aux)
{
		vector_t *vector = aux;
		vector->nombres[vector->indice] = (char *)clave;
		vector->indice++;

		return true;
}
/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos del hash pasado por parametro.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **obtener_nombre_generico(sala_t *sala, int *cantidad , hash_t *hash)
{
		
		size_t cantidad_nombre = hash_cantidad(hash);
		if(cantidad)
			(*cantidad) = (int)cantidad_nombre;

		char **bloque = malloc(cantidad_nombre * sizeof(char *));
		if(!bloque){
			if(cantidad)
				*cantidad = -1;
			return NULL;
		}
		vector_t vector;
		vector.nombres = bloque;
		vector.indice = 0;
		hash_con_cada_clave(hash,agregar_clave_a_vector,&vector);
		
		return vector.nombres;
}
char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
		if(!sala){
			if(cantidad)
				*cantidad = -1;
			return NULL;
		}
		return obtener_nombre_generico(sala, cantidad, sala->objetos);
} 

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
		if(!sala){
			if(cantidad)
				*cantidad = -1;
			return NULL;
		}
		return obtener_nombre_generico(sala, cantidad, sala->conocidos);
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{		
		if(!sala){
			if(cantidad)
				*cantidad = -1;
			return NULL;
		}
		return obtener_nombre_generico(sala, cantidad, sala->poseidos);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
		if(!nombre_objeto || !sala)
			return false;

		if(hash_contiene(sala->conocidos, nombre_objeto)){
			struct objeto *objeto_conocido = hash_obtener(sala->conocidos, nombre_objeto);
			if(objeto_conocido->es_asible){
				if(!hash_contiene(sala->poseidos, nombre_objeto)){
					
					void *anterior = NULL;
					hash_insertar(sala->poseidos, objeto_conocido->nombre,objeto_conocido,&anterior);

					
					hash_quitar(sala->conocidos, objeto_conocido->nombre);
					return true;
				}
			}
		}
		return false;
}

char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
		if(!sala || !nombre_objeto)
			return NULL;
		if(hash_contiene(sala->conocidos, nombre_objeto)){
			struct objeto *objeto_encontrado = hash_obtener(sala->conocidos, nombre_objeto);
			return objeto_encontrado->descripcion;
		}else{
			if(hash_contiene(sala->poseidos, nombre_objeto)){
				struct objeto *objeto_encontrado = hash_obtener(sala->poseidos, nombre_objeto);
				return objeto_encontrado->descripcion;
			}
		}
		return NULL;
}

bool se_debe_ejecutar(sala_t *sala, const char *verbo,const char *objeto1, const char *objeto2)
{
		if(sala_es_interaccion_valida(sala, verbo, objeto1,objeto2) &&
			(hash_contiene(sala->conocidos ,objeto1)|| hash_contiene(sala->poseidos , objeto1))){
			return true;
		}
		return false;
}
bool se_debe_descubir(sala_t *sala , struct interaccion *interaccion){
		if(!hash_contiene(sala->conocidos ,interaccion->accion.objeto) &&
			!hash_contiene(sala->poseidos ,interaccion->accion.objeto) &&
			hash_contiene(sala->objetos ,interaccion->accion.objeto))
			return true;
		return false;
}
int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
		int contador_ejecucion = 0;
		if(!sala || !verbo || !objeto1)
			return 0;

		if (se_debe_ejecutar(sala, verbo,objeto1, objeto2) ){

			lista_iterador_t *it = NULL;

			for (it = lista_iterador_crear(sala->interacciones);

		     lista_iterador_tiene_siguiente(it); 

		     lista_iterador_avanzar(it) ){

		     	struct interaccion *interaccion = lista_iterador_elemento_actual(it);

		     	if(strcmp(interaccion->objeto , objeto1)==0){
		     		void *anterior = NULL;
					struct objeto *accion_objeto = hash_obtener(sala->objetos ,interaccion->accion.objeto);

     				switch(interaccion->accion.tipo){

     				//'d'
					case DESCUBRIR_OBJETO:

					if(se_debe_descubir(sala ,interaccion)){

						hash_insertar(sala->conocidos, accion_objeto->nombre, accion_objeto, &anterior);
						contador_ejecucion++;
						if(mostrar_mensaje)
							mostrar_mensaje(interaccion->accion.mensaje,interaccion->accion.tipo,aux);
					}
					break;
					//'e'
					case ELIMINAR_OBJETO:;
					void *quitado1 = hash_quitar(sala->objetos , interaccion->accion.objeto);
					free(quitado1);
					if(hash_contiene(sala->poseidos , interaccion->accion.objeto)){
						hash_quitar(sala->poseidos , interaccion->accion.objeto);
						contador_ejecucion++;
					}
					if(mostrar_mensaje)
						mostrar_mensaje(interaccion->accion.mensaje,interaccion->accion.tipo,aux);
					
					break;
					//'r'
					case REEMPLAZAR_OBJETO:;
						hash_quitar(sala->conocidos , interaccion->objeto_parametro);
						void *quitado = hash_quitar(sala->objetos , interaccion->objeto_parametro);
						free(quitado);
						hash_insertar(sala->conocidos ,accion_objeto->nombre, accion_objeto, &anterior);
						if(mostrar_mensaje)
							mostrar_mensaje(interaccion->accion.mensaje,interaccion->accion.tipo,aux);
						contador_ejecucion++;
					break;
					//'g'
					case ESCAPAR:
						sala->pude_escapar = true;
						if(mostrar_mensaje)
							mostrar_mensaje(interaccion->accion.mensaje,interaccion->accion.tipo,aux);
						contador_ejecucion++;
					break;
					case MOSTRAR_MENSAJE:
						if(mostrar_mensaje) {
							if(hash_contiene(sala->conocidos , interaccion->objeto)){
								mostrar_mensaje(interaccion->accion.mensaje,interaccion->accion.tipo,aux);
							}
							contador_ejecucion++;
						}
					break;
					default:
						lista_iterador_destruir(it);
						return 0;
					}
		     	}
			}
			lista_iterador_destruir(it);
		}
		return contador_ejecucion;
}

/*recibe una interaccion y compara el objeto con el del segundo parametro
si son iguales la funcion devuelve 0, si no -1
*/
int comparador_interaccion(void *interaccion_, void *objeto1_)
{ 
	struct interaccion *interaccion = interaccion_;
	char *objeto1 = objeto1_;
	if(strcmp(interaccion->objeto , objeto1)==0){
		return 0;
	}
	return -1;
}
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,const char *objeto2)
{	
		if(!sala || !objeto1 || !verbo)
			return NULL;
		 
		bool es_interaccion_valida = false;
		
		struct interaccion *interaccion = lista_buscar_elemento(sala->interacciones,comparador_interaccion ,(void *)objeto1);
		if(interaccion){
			if(strcmp(interaccion->verbo,verbo)== 0  && strcmp(interaccion->objeto_parametro,objeto2)== 0){
				es_interaccion_valida = true;
			}
		}
		return es_interaccion_valida;
}

bool sala_escape_exitoso(sala_t *sala)
{
		if(!sala)
			return false;
		return sala->pude_escapar;;
}

void sala_destruir(sala_t *sala)
{
		if(!sala)
			return;
		hash_destruir_todo(sala->objetos, free);
		lista_destruir_todo(sala->interacciones , free);
		
		hash_destruir(sala->conocidos);
		hash_destruir(sala->poseidos);
		
		free(sala);
}