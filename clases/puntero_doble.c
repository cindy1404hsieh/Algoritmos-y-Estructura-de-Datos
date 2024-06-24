#include <stdio.h>
int main(){
	int num = 5;
	int *puntero1 = &num;//guarda la direccion de memoria donde vive el numero 
	int **puntero2 = &puntero1;
	
	printf("puntero1 = %i\n", *puntero1);//5 
	printf("puntero2 = %i\n", **puntero2);//5
	**puntero2 = 10;
	printf("num cambiado a= %i\n", num);//10
	printf("puntero1 cambiado a= %i\n", *puntero1);//10 
	printf("puntero2 cambiado a= %i\n", **puntero2);//10
	return 0;
}