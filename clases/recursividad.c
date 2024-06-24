nodo{
	nodo_t *nodo_inicio;
	int elemento;
}
typedef struct {
	nodo_t *corriente;
}iterador;
iterador_t iteradir_crear(lista_t *lista){
	iterador_t *i = malloc(sizeof(iterador_t));
	i->corriente = lista->inicio;
	return i;
}
int main(){
	lista_t *lista = lista_crear();
	lista_insertar(lista, 1);
	lista_insertar(lista, 2);
	lista_insertar(lista, 3);
	lista_insertar(lista, 4);
	nodo_t *corriente;
	for(corriente = lista->inicio ;
	 corriente != NULL;
	 corriente =corriente->siguiente ){
		printf("Elementoo: %i\n",corriente->elemento);
	}
}