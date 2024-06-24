#include "estructuras.h"
#include "objeto.h"
#include "interaccion.h"
#include "sala.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINEA 1024
#define NO_ENCONTRADO -1
  

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
		sala_t *sala = malloc(sizeof(sala_t));
		if(sala==NULL)
			return NULL;

		char linea[MAX_LINEA];

		sala->objetos = NULL;
		sala->cantidad_objetos = 0;

		while(fgets(linea,MAX_LINEA,arc_objeto) != NULL){
			struct objeto **bloque = realloc(sala->objetos,(unsigned long int)(sala->cantidad_objetos+1)*sizeof(struct objeto));
				if(bloque == NULL)
					return NULL;
				bloque[sala->cantidad_objetos] = objeto_crear_desde_string(linea);
				sala->cantidad_objetos++;
				sala->objetos = bloque;
		}
		if(sala->objetos == NULL){
			fclose(arc_objeto);
			fclose(arc_interaccion);
			sala_destruir(sala);
			return NULL;
		}

		sala->interacciones = NULL;
		sala->cantidad_interacciones = 0;
		
		while(fgets(linea,MAX_LINEA,arc_interaccion) != NULL){
			struct interaccion **bloque = realloc(sala->interacciones,(unsigned long int)(sala->cantidad_interacciones+1)*sizeof(struct interaccion));
			if(bloque == NULL)
				return NULL;
			bloque[sala->cantidad_interacciones] = interaccion_crear_desde_string(linea);
			sala->cantidad_interacciones++;
			sala->interacciones = bloque;
			
		}
		if(sala->interacciones == NULL){
			fclose(arc_objeto);
			fclose(arc_interaccion);
			sala_destruir(sala);
			return NULL;
		}
		if(sala->cantidad_interacciones == 0 || sala->cantidad_objetos == 0)
			return NULL;
		
		fclose(arc_objeto);
		fclose(arc_interaccion);

		return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{ 	
		if(sala == NULL){
			*cantidad = -1;
			return NULL;
		}
		char **vector_objetos =malloc((unsigned long int)sala->cantidad_objetos*(sizeof(char*)));
		if (vector_objetos == NULL){
			*cantidad = -1;
			return NULL;
		}

		if(cantidad != NULL)
			(*cantidad) = sala->cantidad_objetos;
		
		for(int i =0 ; i<sala->cantidad_objetos ; i++)
			vector_objetos[i] = sala->objetos[i]->nombre;
		
		return vector_objetos;
}
/*
* La función recibe un vector de interacciones, 
* su respectivo tope y un objeto,
* devuelve la posición del elemento del vector, 
* que coincida con el objeto pasado 'objeto_buscado',
* si no se encuentra ningún elemento, se devolverá -1. 
*/
int buscar_pos_interaccion(struct interaccion **interacciones,int tope,const char *objeto_buscado)
{
		int pos_encontrado = NO_ENCONTRADO;
		bool encontrado = false;
		for(int i =0 ; i<tope ; i++){
			if (!encontrado && strcmp(interacciones[i]->objeto,objeto_buscado)==0){
				pos_encontrado = i;
				encontrado =true;
			}
		}
		return pos_encontrado;
}
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,const char *objeto2)
{	
		if(sala == NULL)
			return NULL;
		
		if(objeto1 == NULL)
			return NULL;
		
		bool es_interaccion_valida = false;
		int pos_encontrada = buscar_pos_interaccion(sala->interacciones,sala->cantidad_interacciones,objeto1);
		if ( pos_encontrada != NO_ENCONTRADO){
			if(strcmp(sala->interacciones[pos_encontrada]->verbo,verbo)== 0  && strcmp(sala->interacciones[pos_encontrada]->objeto_parametro,objeto2)== 0)
				es_interaccion_valida = true;
		}
 
		return es_interaccion_valida;
}

void sala_destruir(sala_t *sala)
{
		for (int i= 0 ; i<sala->cantidad_objetos ;i++)
			free(sala->objetos[i]);
		
		for (int i= 0 ; i<sala->cantidad_interacciones ;i++)
			free(sala->interacciones[i]);
		
		free(sala->objetos);
		free(sala->interacciones);
		free(sala);
}