char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{ 
	char* vector_nombres = NULL;
	if(cantidad == NULL ){
		return NULL;
	}
	for (int i = 0 ; i<sala->cantidad_objetos;i++){
		char *bloque_aux = realloc(vector_nombres,((*cantidad)+1)*sizeof(char));
		if(bloque_aux == NULL){
			return NULL;
		}
		strcpy(bloque_aux[*cantidad],sala->objetos[i]->nombre);
		(*cantidad)++;
	}
	(*vector_nombres) = bloque_aux;
	return *vector_nombres;
}