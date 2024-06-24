#include <stdio.h>
int main(){
	int num = 5;
	int *puntero = &num;
	printf("puntero = %i\n", *puntero);//5 
	*puntero = 6;
	printf("puntero = %i\n", *puntero);//6
	printf("num = %i\n", num);//6
	return 0;
}