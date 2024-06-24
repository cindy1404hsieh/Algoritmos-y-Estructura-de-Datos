#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
 
#define VACIO ""
struct interaccion *interaccion_crear_desde_string(const char *string)
{		 
		if(string==NULL)
			return NULL;
		
		char objeto[MAX_NOMBRE];
		char verbo[MAX_VERBO];
		char objeto_parametro[MAX_NOMBRE];
		struct accion accion;
		char tipo_accion;
		int elemento_leido = sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n",objeto,verbo,objeto_parametro,&tipo_accion,accion.objeto,accion.mensaje);
		if(elemento_leido != 6)
			return NULL;
		
		struct interaccion *interaccion = malloc(sizeof(struct interaccion));
		if (interaccion ==NULL)
			return NULL;
		
		strcpy(interaccion->objeto,objeto);
		strcpy(interaccion->verbo,verbo);

		if(strcmp(objeto_parametro,"_")==0)
			strcpy(interaccion->objeto_parametro,VACIO);
		else
			strcpy(interaccion->objeto_parametro,objeto_parametro);
		
		if(strcmp(accion.objeto,"_")==0)
			strcpy(interaccion->accion.objeto,VACIO);
		else
			strcpy(interaccion->accion.objeto,accion.objeto);
		
		strcpy(interaccion->accion.mensaje,accion.mensaje);

		switch(tipo_accion){
		case'd':
			interaccion->accion.tipo = DESCUBRIR_OBJETO;
		break;
		case'r':
			interaccion->accion.tipo = REEMPLAZAR_OBJETO;
		break;
		case'e':
			interaccion->accion.tipo = ELIMINAR_OBJETO;
		break;
		case'm':
			interaccion->accion.tipo = MOSTRAR_MENSAJE;
		break;
		case'g':
			interaccion->accion.tipo = ESCAPAR;
		break;
		default:
			interaccion->accion.tipo = ACCION_INVALIDA;
		}
	return interaccion;
}
