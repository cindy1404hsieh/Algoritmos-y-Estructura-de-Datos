#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
//corre con "bash test.sh"
int main(int argc, char *argv[])
{
 
		if(argc == 3)
			sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
		
		
		if (sala == NULL){
			sala_destruir(sala);
			printf("Error al crear la sala de escape\n");
			return -1;		
		}

		int cantidad = 0;

		char **nombre_objetos = sala_obtener_nombre_objetos(sala, &cantidad);

		printf("Objetos...\n");
		for (int i=0 ; i<cantidad ; i++)
			printf("%i: %s\n",i,nombre_objetos[i]);
		free(nombre_objetos);

		printf("Interacciones...\n");
		if(sala_es_interaccion_valida(sala,"examinar","habitacion","_"))
			printf("Examinar la habitacion: Valido\n");
		else
			printf("Examinar la habitacion: Invalido\n");
		
		if(sala_es_interaccion_valida(sala,"abrir","pokebola","_"))
			printf("Abrir pokebola: Valido\n");
		else
			printf("Abrir pokebola: Invalido\n");
		
		if(sala_es_interaccion_valida(sala,"usar","llave","cajon"))
			printf("Usar llave en el cajon: Valido\n");
		else
			printf("Usar llave en el cajon: Invalido\n");
		
		if(sala_es_interaccion_valida(sala,"quemar","mesa","_"))
			printf("Quemar la mesa: Valido\n");
		else
			printf("Quemar la mesa: Invalido\n");

		sala_destruir(sala);

		return 0;
}
