#include <stdio.h>
int main(){
	int numeros_vector[3];
	numeros_vector[0]=56;
	numeros_vector[1]=78;
	numeros_vector[2]=99;
	//aca no es necesario hacer :
	//int *puntero_numeros_vector = &numeros_vector;
	//porque el vector no necesita, porue 
	//el compilador lo toma como un puntero
	int *puntero_numeros_vector = numeros_vector;
	
	
	printf("el segundo numero es = %i\n", numeros_vector[1]);
	printf("el segundo numero puntero es  = %i\n", puntero_numeros_vector[1]);
	
	return 0;
}