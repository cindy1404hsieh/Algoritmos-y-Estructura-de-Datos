#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NOMBRE 15
   
struct alumno
{
	char nombre[MAX_NOMBRE];
	int padron;	
	int *notas;
	int tope_notas;
};
//devuelve un puntero a un alumno.
//crea un puntero apuntando a 
//un bloque en heap que dentro del bloque hay nombre y 
//padron
struct alumno* alumno_crear_desde_string(char *string){
	char nombre[MAX_NOMBRE];
	int padron;	

	int leido = sscanf(string,"%[;];%[\n]\n");
	if(leido != 2){
		return NULL;
	}
	struct alumno *alumno = malloc(sizeof(struct alumno));
	if(alumno == NULL){
		return NULL;
	}
	//inicializo 
	strcpy(alumno->nombre,nombre);
	alumno->padron = padron;
	//(*alumno).padron = padron;
	alumno->notas = NULL;
	alumno->tope_notas = 0;
	return alumno;
}


void agregar_nota(int **vector,int *tope,int nota_a_agregar){

		int *bloque_aux = realloc(*vector,((*tope)+1)*sizeof(int));
		if(bloque_aux ==NULL ){
			return NULL;
		}
		bloque_aux[*tope]= nota_a_agregar;
		(*tope)++;

		(*vector) = bloque_aux;
}
int main(){
	//crei un puntero apuntando a un bloque de memoria
	struct alumno *cindy = alumno_crear_desde_string("cindy;108051");
	if (cindy == NULL){
		return -1;
	}

	agregar_nota(&cindy->notas, &cindy->tope_notas, 10 );
	free(cindy->notas);
	free(cindy);
	return 0;
}


//struct alumno **alumnos=NULL;
	//int tope=0;
	//inicializar un vector de tipo alumno_t