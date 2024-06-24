#include<stdio.h>
#include<stdlib.h>
//#define MAX 100

/*void agregar_numeros(int vector[MAX],int *tope,int num_a_agregar){
	
}*/
//// LA VERSION INCORRECTA
void agregar_numeros(int *vector,int *tope,int num_a_agregar){
	vector = malloc(sizeof(int));
	if(vector ==NULL ){
		return NULL;
	}
	vector[*tope]= num_a_agregar;
	(*tope)++;
}
int main(){
	//int numeros[MAX];
	int *numeros=NULL;
	int tope=0;
	agregar_numeros(numeros,&tope,1);
	// aca arriba estas simplemente pasando
	// un COPIA de "numeros"
	// y no le estas pasando 
	// "numeros" EN SI
	//(como lo que deberia hacer con tope)
	// por ende lo que se hace en en agregar_numero
	// dsps se pierde y no llegas a modificar
	// "numeros" 
	return 0;
}
/////////////////////////////////////////////////////////////////////
/*Algo2Mendez: Punteros múltiples y vectores dinámicos
2022年3月30日
1:33:55 explica porque es necesario en este caso 
utilizar el doble punteros
*/
// LA VERSION CORRECTA
void agregar_numeros(int **vector,int *tope,int num_a_agregar){

	int *bloque_aux = malloc(sizeof(int));
	if(bloque_aux ==NULL ){
		return NULL;
	}
	bloque_aux[*tope]= num_a_agregar;
	(*tope)++;

	(*vector) = bloque_aux;
	//este (*vector) a que apunta? 
	//apunta a esta variable int **vector
	//y int **vector a que apunta?
	//apunta a numeros
}
/////////////////////////////////////////////////////////////////
// LA VERSION 1 CORRECTA PARA AGREGAR MAS DE UN NUMERO
void agregar_numeros(int **vector,int *tope,int num_a_agregar){
	if(tope==0){
		int *bloque_aux = malloc(sizeof(int));
		if(bloque_aux ==NULL ){
			return NULL;
		}
		bloque_aux[*tope]= num_a_agregar;
		(*tope)++;

		(*vector) = bloque_aux;
	}
	else{
		int *bloque_aux = realloc(*vector,((*tope)+1)*sizeof(int));
		if(bloque_aux ==NULL ){
			return NULL;
		}
		bloque_aux[*tope]= num_a_agregar;
		(*tope)++;

		(*vector) = bloque_aux;
	}
}
/////////////////////////////////////////////////////////////////
// LA VERSION 2 CORRECTA PARA AGREGAR MAS DE UN NUMERO
void agregar_numeros(int **vector,int *tope,int num_a_agregar){

		int *bloque_aux = realloc(*vector,((*tope)+1)*sizeof(int));
		if(bloque_aux ==NULL ){
			return NULL;
		}
		bloque_aux[*tope]= num_a_agregar;
		(*tope)++;

		(*vector) = bloque_aux;
}
int main(){
	//int numeros[MAX];
	int *numeros=NULL;
	int tope=0;
	agregar_numeros(&numeros,&tope,9);
	free(numeros);
	return 0;
}
