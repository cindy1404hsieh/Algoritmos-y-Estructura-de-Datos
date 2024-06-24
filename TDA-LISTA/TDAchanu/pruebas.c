#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

int elemento_es_n(void *_elemento, void *ignorado)
{
        char *elemento = _elemento;

        if(elemento && *elemento == 'n')
          return 0;

        return -1;
}
int elemento_es_igual_a(void *_a, void *_b)
{
        char *a = _a;
        char *b = _b;

        if(a && b && *a == *b)
          return 0;

        return -1;
}
bool mostrar_elemento(void *elemento, void *contador)
{
        if (elemento && contador)
          return true;
        return false;
}
void crear_una_lista_me_devuelve_una_lista_con_cantidad_cero_e_inicio_y_fin_nulos(){
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista!=NULL ,"Puedo crear una lista");
        pa2m_afirmar(lista_tamanio(lista) == 0,"Una lista recien creada contiene 0 elementos");
        pa2m_afirmar(lista_vacia(lista),"Una lista recien creada es vacia");
        pa2m_afirmar(!lista_primero(lista),"El primer elemento de una lista vacía es NULL");
        pa2m_afirmar(!lista_ultimo(lista),"El último elemento de una lista vacía es NULL");
        free(lista);
}
void borrar_y_buscar_elementos_en_una_lista_vacia_devuelve_NULL(){
        lista_t *lista = lista_crear();
        
        pa2m_afirmar(!lista_quitar(lista),"Borrar al final de una lista sin elementos devuelve NULL");
        pa2m_afirmar(!lista_quitar_de_posicion(lista, 0),"Borrar en una posicion arbitraria de una lista sin elementos devuelve NULL");
        
        free(lista);
}

void insertar_final_devuelve_lista(){
        char c = 'c',i = 'i',n = 'n';
        pa2m_afirmar(lista_insertar(NULL,&c) == NULL,"Insertar en una lista nula me devuelve null");
        lista_t *lista = lista_crear();
        lista_insertar(lista,&c);
        pa2m_afirmar(lista_tamanio(lista) == 1 ,"La lista tiene 1 elemento");
        pa2m_afirmar(!lista_vacia(lista) ,"La lista no está vacía");
        pa2m_afirmar(lista_primero(lista) == &c ,"El primer elemento de la lista es el correcto");
        lista_insertar(lista,&i);
        pa2m_afirmar(lista_tamanio(lista) == 2 && lista_ultimo(lista) == &i,"Puedo insertar mi segundo elemento");
        lista_insertar(lista,&n);
        pa2m_afirmar(lista_tamanio(lista) == 3 && lista_ultimo(lista) == &n,"Puedo insertar mi tercer elemento");
        lista_destruir(lista);
}

void insertar_en_una_lista_NULL_devuelve_NULL(){
        char d = 'd';
        pa2m_afirmar(!lista_insertar_en_posicion(NULL, &d,3), "Insertar en una lista NULL devuelve NULL");

}
void insertar_al_inicio_en_una_lista_vacia(){
        char c = 'c';
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_insertar_en_posicion(lista, &c,0) && !lista_vacia(lista) ,"Insertar un elemento al inicio devuelve la lista");
        pa2m_afirmar(lista_tamanio(lista) == 1 ,"La lista tiene 1 elemento");
        pa2m_afirmar(lista_primero(lista) == &c ,"El primer elemento de la lista es el correcto");
        lista_destruir(lista);
}
void insertar_al_inicio_en_una_lista_no_vacia(){
        char c = 'c',i = 'i',n = 'n' ,d = 'd',y = 'y';
        lista_t *lista = lista_crear();
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&d);
        lista_insertar(lista,&y);
        pa2m_afirmar(lista_insertar_en_posicion(lista, &c,0) && lista_primero(lista) == &c ,"El primer elemento de la lista es el correcto");
        pa2m_afirmar(lista_insertar_en_posicion(lista, &i,0) && lista_primero(lista) == &i ,"El primer elemento de la lista es el correcto");
        pa2m_afirmar(lista_insertar_en_posicion(lista, &d,0) && lista_primero(lista) == &d ,"El primer elemento de la lista es el correcto");
        lista_destruir(lista);
}

void insertar_con_posicion_existente(){
  char c = 'c',i = 'i',n = 'n' ,d = 'd',y = 'y';
        lista_t *lista = lista_crear();
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&d);
        lista_insertar(lista,&y);
        lista_insertar_en_posicion(lista, &n,2);
        pa2m_afirmar(lista_tamanio(lista)==5,"Insertar un elemento en la posición 2 devuelve la lista con elemento insertado");
        pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_n,NULL) == &n,"El elemento en la posicion 2 es el correcto");
        lista_destruir(lista);
}
void insertar_con_posicion_inexistente_me_lo_inserta_al_final(){
        char c = 'c',i = 'i',n = 'n' ;
        lista_t *lista = lista_crear();
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar_en_posicion(lista, &n,89);
        pa2m_afirmar(lista_tamanio(lista)==3,"Insertar un elemento en la posición 89 devuelve la lista con elemento insertado");
        pa2m_afirmar(lista_ultimo(lista) == &n ,"Insertar un elemento en la posición 89 se lo inserta al final");
        lista_destruir(lista);
}

void eliminar_el_unico_elemento_de_la_lista_queda_vacia(){
  lista_t *lista = lista_crear();
        char c = 'c';
        lista_insertar(lista,&c);
        void *elemento_a_eliminar = lista_quitar(lista);
        pa2m_afirmar(elemento_a_eliminar == &c,"Puedo eliminar el unico elemento de la lista");
        pa2m_afirmar(lista_vacia(lista),"Borrar el único elemento de la lista la deja vacía");
        pa2m_afirmar(lista_tamanio(lista)==0,"Una lista vacía tiene 0 elementos");
        void *elemento_a_eliminar_ = lista_quitar(lista);
        pa2m_afirmar(elemento_a_eliminar_ == NULL,"No se puede borrar de una lista vacía");
        lista_destruir(lista);
  }

void eliminar_final_lista(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&y);
        void *elemento_a_eliminar = lista_quitar(lista);
        pa2m_afirmar(elemento_a_eliminar == &y,"El elemento borrado es el correcto(el ultimo)");
        pa2m_afirmar(lista_tamanio(lista)==3,"Al borrar se resta uno a la cantidad de la lista");
        pa2m_afirmar(lista_ultimo(lista) == &n ,"El ultimo elemento de la lista ahora es el anteultimo");
        lista_destruir(lista);
}

void borrar_con_posicion_inexistente_me_lo_borra_al_final(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&y);
        void *elemento_a_eliminar = lista_quitar_de_posicion(lista, 8);
        pa2m_afirmar(elemento_a_eliminar == &y,"Puedo borrar un elemento en una posición mayor a la cantidad de elementos");
        pa2m_afirmar(lista_tamanio(lista)==3,"Al borrar se resta uno a la cantidad de la lista");
        lista_destruir(lista);
}
void borrar_al_inicio_con_un_unico_elemento_lista_queda_vacia(){
        lista_t *lista = lista_crear();
        char c = 'c';
        lista_insertar(lista,&c);
        void *elemento_a_eliminar = lista_quitar_de_posicion(lista, 0);
        pa2m_afirmar(elemento_a_eliminar == &c,"Puedo borrar el elemento en posición 0");
        pa2m_afirmar(lista_vacia(lista),"Al borrar la lista queda vacia");
        lista_destruir_todo(lista, free);
}
void borrar_al_inicio(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&y);
        void *elemento_a_eliminar = lista_quitar_de_posicion(lista, 0);
        pa2m_afirmar(elemento_a_eliminar == &c,"Puedo borrar el elemento en posición 0");
        pa2m_afirmar(lista_primero(lista) == &i,"El primer elemento de la lista es el correcto luego de borrar");
        pa2m_afirmar(lista_tamanio(lista)==3,"Luego de borrar queda la cantidad correcta de elementos en la lista");
        void *elemento_a_eliminar_1 = lista_quitar_de_posicion(lista, 0);
        pa2m_afirmar(elemento_a_eliminar_1 == &i,"Puedo borrar el elemento en posición 0");
        pa2m_afirmar(lista_primero(lista) == &n,"El primer elemento de la lista es el correcto luego de borrar");
        pa2m_afirmar(lista_tamanio(lista)==2,"Luego de borrar queda la cantidad correcta de elementos en la lista");
        void *elemento_a_eliminar_2 = lista_quitar_de_posicion(lista, 0);
        pa2m_afirmar(elemento_a_eliminar_2 == &n,"Puedo borrar el elemento en posición 0");
        pa2m_afirmar(lista_primero(lista) == &y,"El primer elemento de la lista es el correcto luego de borrar");
        pa2m_afirmar(lista_tamanio(lista)==1,"Luego de borrar queda la cantidad correcta de elementos en la lista");
        void *elemento_a_eliminar_3 = lista_quitar_de_posicion(lista, 0);
        pa2m_afirmar(elemento_a_eliminar_3 == &y,"Puedo borrar el elemento en posición 0");
        pa2m_afirmar(lista_primero(lista) == NULL,"El primer elemento de la lista es el correcto luego de borrar");
        pa2m_afirmar(lista_tamanio(lista)==0 && lista_vacia(lista),"Puedo borrar todos los elementos borrando siempre el primero");
        lista_destruir_todo(lista, free);
}
void borrar_con_posicion_existente(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&y);
        void *elemento_a_eliminar = lista_quitar_de_posicion(lista, 2);
        pa2m_afirmar(elemento_a_eliminar == &n,"Puedo borrar el elemento en medio de la lista");
        pa2m_afirmar(lista_tamanio(lista)==3,"Al borrar se resta uno a la cantidad de la lista");
        lista_destruir(lista);
}
void verificar_una_lista_nula(){
        lista_t *lista = NULL;
        pa2m_afirmar(lista_vacia(lista) && lista_tamanio(lista)==0,"Una lista nula es vacía y contiene 0 elementos");
        pa2m_afirmar(!lista_primero(lista),"El primer elemento de una lista nula es nulo");
        pa2m_afirmar(!lista_ultimo(lista),"El ultimo elemento de una lista nula es nulo");
}
void operar_con_lista_nula(){
        lista_t *lista = NULL;
        char c = 'c';
        pa2m_afirmar(!lista_insertar(lista,&c),"Es un error insertar al final de una lista nula");
        pa2m_afirmar(!lista_insertar_en_posicion(lista ,&c, 2),"Es un error insertar en cualquier posición de una lista nula");
        pa2m_afirmar(!lista_insertar_en_posicion(lista ,&c, 0),"Es un error insertar al inicio de una lista nula");
        pa2m_afirmar(!lista_iterador_crear(lista),"Un iterador de una lista nula es nulo");
        int contador = 0;
        size_t elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento,(void *)&contador);
        pa2m_afirmar(elementos_recorridos==0,"Recorrer una lista nulo con el iterador interno recorre 0 elementos");
}
void iteracion_externa_lista_vacia(){
        lista_t *lista = lista_crear();
        lista_iterador_t *it = lista_iterador_crear(lista);
        pa2m_afirmar(it!= NULL,"Puedo crear un iterador con una lista vacía");
        pa2m_afirmar(!lista_iterador_tiene_siguiente(it),"El iterador de una lista vacía no tiene siguiente");
        pa2m_afirmar(!lista_iterador_elemento_actual(it),"El elemento actual de un iterador de lista vacía siempre es NULL");
        pa2m_afirmar(!lista_iterador_avanzar(it),"El iterador de una lista vacía no puede avanzar");
        lista_iterador_destruir(it);
        lista_destruir(lista);
}
void iteracion_externa_lista_no_vacia(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,d = 'd',y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&d);
        lista_insertar(lista,&y);
        lista_iterador_t *it = lista_iterador_crear(lista);
        pa2m_afirmar(it != NULL,"Puedo crear un iterador con una lista no vacía");
        pa2m_afirmar(lista_iterador_tiene_siguiente(it),"El iterador de una lista no vacía tiene siguiente");
        pa2m_afirmar(lista_iterador_elemento_actual(it) == &c,"El elemento actual de un iterador de lista no vacía es el primer elemento");
        pa2m_afirmar(lista_iterador_avanzar(it),"Puedo avanzar el iterador de una lista no vacía");
        pa2m_afirmar(lista_iterador_elemento_actual(it) == &i,"El elemento actual del iterador es el correcto");
        pa2m_afirmar(lista_iterador_avanzar(it),"Avanzar el iterador devuelve TRUE si no estoy en el último elemento");
        lista_iterador_avanzar(it);
        lista_iterador_avanzar(it);
        pa2m_afirmar(!lista_iterador_avanzar(it),"Avanzar el iterador devuelve FALSE si estoy en el último elemento");
        pa2m_afirmar(lista_iterador_elemento_actual(it) == NULL,"El elemento actual del iterador es NULL");
        lista_iterador_destruir(it);
        lista_destruir(lista);
}

void pruebas_de_creacion_de_lista(){
        crear_una_lista_me_devuelve_una_lista_con_cantidad_cero_e_inicio_y_fin_nulos();
        borrar_y_buscar_elementos_en_una_lista_vacia_devuelve_NULL();

}
void pruebas_de_insercion_de_lista(){
        insertar_final_devuelve_lista();
}
void pruebas_de_insercion_de_lista_en_posicion(){
        insertar_en_una_lista_NULL_devuelve_NULL();
        insertar_al_inicio_en_una_lista_vacia();
        insertar_al_inicio_en_una_lista_no_vacia();
        insertar_con_posicion_existente();
        insertar_con_posicion_inexistente_me_lo_inserta_al_final();
}
void pruebas_de_eliminacion_de_lista(){
        eliminar_el_unico_elemento_de_la_lista_queda_vacia();
        eliminar_final_lista();
}
void pruebas_de_eliminacion_de_lista_en_posicon(){
        borrar_con_posicion_inexistente_me_lo_borra_al_final();
        borrar_al_inicio_con_un_unico_elemento_lista_queda_vacia();
        borrar_al_inicio();
        borrar_con_posicion_existente();
}
void pruebas_con_NULL(){
        verificar_una_lista_nula();
        operar_con_lista_nula();
}

void pruebas_de_iteracion_externa(){
        iteracion_externa_lista_vacia();
        iteracion_externa_lista_no_vacia();
}

void pruebas_de_iteracion_interna(){
        lista_t *lista = lista_crear();
        char c = 'c',i = 'i',n = 'n' ,d = 'd',y = 'y';
        int contador = 0;
        size_t elementos_recorridos = 0;
        elementos_recorridos = lista_con_cada_elemento(lista, NULL,(void *)&contador);
        pa2m_afirmar(elementos_recorridos == 0,"No puedo iterar una lista sin función de iteración");
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&d);
        lista_insertar(lista,&y);
        size_t elementos_recorridos_ = lista_con_cada_elemento(lista, mostrar_elemento,(void *)&contador);
        pa2m_afirmar(elementos_recorridos_== 5,"Se iteraron todos los elementos esperados");
        lista_destruir(lista);
}

void pruebas_de_busqueda(){
        lista_t *lista = lista_crear();
        char *elemento = lista_buscar_elemento(lista, elemento_es_n, NULL);
        pa2m_afirmar(elemento == NULL,"Buscar un elemento en una lista vacía resulta en NULL");
        char c = 'c',i = 'i',n = 'n' ,d = 'd',y = 'y';
        lista_insertar(lista,&c);
        lista_insertar(lista,&i);
        lista_insertar(lista,&n);
        lista_insertar(lista,&d);
        lista_insertar(lista,&y);
        char *elemento_ = lista_buscar_elemento(lista, NULL, NULL);
        pa2m_afirmar(elemento_ == NULL,"Buscar un elemento con una función NULL devuelve NULL");
        char *elemento_n = lista_buscar_elemento(lista, elemento_es_n, NULL);
        pa2m_afirmar(*elemento_n == 'n',"Buscar un elemento la lista encuentra el elemento");
        char buscado = 'h';
        char *elemento_h = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
        pa2m_afirmar( elemento_h == NULL,"Buscar un elemento inexistente la lista devuelve NULL");
        lista_destruir(lista);
}
void pruebas_de_destruccion(){
        lista_t *lista = lista_crear();

        lista_insertar(lista, malloc(sizeof(int)));
        lista_insertar(lista, malloc(sizeof(int)));
        lista_insertar(lista, malloc(sizeof(int)));
        lista_insertar(lista, malloc(sizeof(int)));
        lista_insertar(lista, malloc(sizeof(int)));
        lista_destruir_todo(lista, free);
        pa2m_afirmar(true,"Destruir todo destruye todos los elementos");
}

void pruebas_de_pila(){
        pila_t *pila = pila_crear();
        char *palabra = "CINDIOSA";

        for (int i = 0; palabra[i] != 0; i++){
          pila_apilar(pila, &palabra[i]);
          pa2m_afirmar(pila_tope(pila)== &palabra[i],"El tope de la pila es el esperado");
        }
        pila_desapilar(pila);
        pa2m_afirmar(pila_tope(pila)==&palabra[pila_tamanio(pila)-1],"Puedo desapilar el elemento y es el correcto");
        pila_destruir(pila);
}
void pruebas_de_cola(){
        cola_t *cola = cola_crear();
        int numeros[] = { 1, 2, 3, 4, 5, 6 };

        for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
          cola_encolar(cola, &numeros[i]);
        }
        pa2m_afirmar(cola_tamanio(cola)== 6,"Puedo encolar algunos valores en la cola");
        pa2m_afirmar(cola_desencolar(cola)== &numeros[0],"Puedo encolar y el elemento de la cola es el esperado");
        pa2m_afirmar(cola_frente(cola)== &numeros[1],"El primer elemento de la cola es el esperado");
        cola_destruir(cola);
}

int main() {
        pa2m_nuevo_grupo("Pruebas de creacion de lista");
        pruebas_de_creacion_de_lista();

        pa2m_nuevo_grupo("Pruebas de insercion de lista");
        pruebas_de_insercion_de_lista();

        pa2m_nuevo_grupo("Pruebas de insercion de lista en posicion");
        pruebas_de_insercion_de_lista_en_posicion();

        pa2m_nuevo_grupo("Pruebas de eliminacion de lista");
        pruebas_de_eliminacion_de_lista();

        pa2m_nuevo_grupo("Pruebas de eliminacion de lista en posicon");
        pruebas_de_eliminacion_de_lista_en_posicon();

        pa2m_nuevo_grupo("Pruebas con NULL");
        pruebas_con_NULL();

        pa2m_nuevo_grupo("Pruebas de iteracion externa de lista");
        pruebas_de_iteracion_externa();

        pa2m_nuevo_grupo("Pruebas de iteracion interna de lista");
        pruebas_de_iteracion_interna();

        pa2m_nuevo_grupo("Pruebas de busqueda");
        pruebas_de_busqueda();

        pa2m_nuevo_grupo("Pruebas de destruccion de lista");
        pruebas_de_destruccion();

        pa2m_nuevo_grupo("Pruebas de pila");
        pruebas_de_pila();

        pa2m_nuevo_grupo("Pruebas de cola");
        pruebas_de_cola();

        return pa2m_mostrar_reporte();
}
