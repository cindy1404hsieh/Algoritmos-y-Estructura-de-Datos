#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#define FALSE "false"
#define TRUE "true"


struct objeto *objeto_crear_desde_string(const char *string)
{
		char nombre[MAX_NOMBRE];
		char descripcion[MAX_TEXTO];
		char es_asible[MAX_TEXTO];
		if(string==NULL){
			return NULL;
		}
		int elemento_leido = sscanf(string,"%[^;];%[^;];%[^\n]\n",nombre,descripcion,es_asible);

		if(elemento_leido != 3)
			return NULL;
		

		struct objeto *objeto = malloc(sizeof(struct objeto));
		if (objeto ==NULL){
			free(objeto);
			return NULL;
		}
		strcpy(objeto->nombre,nombre);
		strcpy(objeto->descripcion,descripcion);
 
		if (strcmp(es_asible,FALSE)==0){
			objeto->es_asible = false;
		}else if(strcmp(es_asible,TRUE)==0){
			objeto->es_asible = true;
		}
		else{
			free(objeto);
			return NULL;
		}

		return objeto;
	
}