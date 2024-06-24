#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"
typedef struct cosa {
  int clave;
  char contenido[10];
} cosa;


cosa *crear_cosa(int clave)
{
  cosa *c = (cosa *)malloc(sizeof(cosa));
  if (c)
    c->clave = clave;
  return c;
}

int comparar_cosas(void *c1, void *c2)
{
  cosa *cosa1 = c1;
  cosa *cosa2 = c2;
  return cosa1->clave - cosa2->clave;
}

void destruir_cosa(cosa *c)
{
  free(c);
}
void destructor_de_cosas(void *c)
{
    destruir_cosa(c);
}
bool mostrar_elemento(void *elemento, void *extra)
{
  extra = extra;
  return true;
}
bool mostrar_hasta_5(void *elemento, void *extra)
{
  extra = extra;
  if (((cosa *)elemento)->clave == 5)
    return false;
  return true;
}

void pruebas_de_creacion()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  pa2m_afirmar(arbol != NULL,"Se puede crear un abb");
  pa2m_afirmar(abb_vacio(arbol),"El abb se crea vacío");
  pa2m_afirmar(abb_tamanio(arbol)==0,"La cantidad de elementos es cero");
  pa2m_afirmar(arbol->nodo_raiz == NULL,"El elemento raíz es NULL");
  abb_destruir(arbol);

}
void pruebas_de_insercion()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  pa2m_afirmar(arbol!= NULL,"Puedo insertar un elemento en el abb.");
  pa2m_afirmar(arbol->nodo_raiz->elemento == c4,"El elemento queda como valor raíz");
  pa2m_afirmar(!abb_vacio(arbol),"El abb ya no está vacío.");
  pa2m_afirmar(abb_tamanio(arbol)==1,"La cantidad de elementos es 1");
  abb_insertar(arbol, c2);
  pa2m_afirmar(arbol!= NULL,"Puedo insertar un elemento menor que el primero.");
  pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == c2,"elemento queda a la izquierda de la raíz.");
  pa2m_afirmar(arbol->nodo_raiz->izquierda && !arbol->nodo_raiz->derecha,"abb queda con un hijo izquierdo y sin hijo derecho.");
  pa2m_afirmar(abb_tamanio(arbol)==2,"La cantidad de elementos es 2");
  abb_insertar(arbol, c6);
  pa2m_afirmar(arbol!= NULL,"Puedo insertar un elemento mayor que el primero.");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c6,"elemento queda a la derecha de la raíz.");
  pa2m_afirmar(arbol->nodo_raiz->izquierda && arbol->nodo_raiz->derecha,"abb queda con un hijo izquierdo y un hijo derecho.");
  pa2m_afirmar(abb_tamanio(arbol)==3,"La cantidad de elementos es 3");
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  pa2m_afirmar(abb_tamanio(arbol)==7,"Puedo insertar varios elementos");
  abb_destruir_todo(arbol, destructor_de_cosas);
} 

void pruebas_de_quitar()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);

  pa2m_afirmar(abb_quitar(arbol, c7) == c7,"Puedo borrar un nodo hoja");
  pa2m_afirmar(abb_buscar(arbol, c7) == NULL,"El nodo eliminado no existe mas.");
  pa2m_afirmar(abb_tamanio(arbol)==6,"La cantidad de elementos es 6");

  pa2m_afirmar(abb_quitar(arbol, c6) == c6,"Puedo borrar un nodo no hoja con un hijo");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c5,"El nodo que queda en su lugar es el nodo hijo.");
  pa2m_afirmar(abb_tamanio(arbol)==5,"La cantidad de elementos es 5");

  pa2m_afirmar(abb_quitar(arbol, c2) == c2,"Puedo borrar un nodo con dos hijos.");
  pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == c1,"El nodo que queda en su lugar es el predecesor inorden");
  pa2m_afirmar(abb_tamanio(arbol)==4,"La cantidad de elementos es 4");

  pa2m_afirmar(abb_quitar(arbol, c4) == c4,"Puedo borrar el nodo raíz (con dos hijos).");
  pa2m_afirmar(arbol->nodo_raiz->elemento == c3,"El nodo que queda en su lugar es el predecesor inorden");
  pa2m_afirmar(abb_tamanio(arbol)==3,"La cantidad de elementos es 3");
  pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == c1,"A la izquierda de la raíz queda el elemento esperado.");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c5,"A la derecha de la raíz queda el elemento esperado.");
  abb_quitar(arbol, c5);

  pa2m_afirmar(abb_quitar(arbol, c3) == c3,"Puedo borrar el nodo raíz (con un hijo).");
  pa2m_afirmar(arbol->nodo_raiz->elemento == c1,"El nodo que queda en su lugar es el unico hijo.");
  pa2m_afirmar(abb_quitar(arbol, c1) == c1,"Puedo borrar el nodo raíz (sin hijos).");
  pa2m_afirmar(arbol->nodo_raiz == NULL && abb_vacio(arbol),"No queda nadie en la raíz, abb vacío.");
  pa2m_afirmar(abb_tamanio(arbol)==0,"La cantidad de elementos es 0");
  destruir_cosa(c4);
  destruir_cosa(c2);
  destruir_cosa(c6);
  destruir_cosa(c1);
  destruir_cosa(c3);
  destruir_cosa(c5);
  destruir_cosa(c7);
  abb_destruir(arbol);
}

void pruebas_de_busqueda()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  pa2m_afirmar(abb_buscar(arbol, c6) == c6,"Busco un elemento existente y lo encuentro");
  pa2m_afirmar(abb_buscar(arbol, c4) == c4,"Busco un elemento existente y lo encuentro");
  pa2m_afirmar(abb_buscar(arbol, c2) == c2,"Busco un elemento existente y lo encuentro");
  pa2m_afirmar(abb_buscar(arbol, c3) == c3,"Busco un elemento existente y lo encuentro");
  void *buscado2 = abb_buscar(arbol, c7);
  pa2m_afirmar(buscado2 == NULL,"Buscar un elemento inexistente devuelve NULL.");
  destruir_cosa(c7);
  abb_destruir_todo(arbol, destructor_de_cosas);
 
}
void pruebas_de_recorrer_un_arbol_preorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  cosa *elementos[10];
  pa2m_afirmar(abb_recorrer(arbol, PREORDEN, (void **)elementos,7) == 7,"La función de recorrido devuelve la cantidad de elementos esperados");
  pa2m_afirmar(abb_recorrer(arbol, PREORDEN, (void **)elementos,5) == 5,"Puedo recorrer menos elementos de los existentes para hacer el recorrido.");
  pa2m_afirmar(abb_recorrer(arbol, PREORDEN, (void **)elementos,10) == 7,"Puedo recorrer mas elementos de los existentes para hacer el recorrido.");
  abb_destruir_todo(arbol, destructor_de_cosas);
}
void pruebas_de_recorrer_un_arbol_inorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  cosa *elementos[10];
  pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void **)elementos,7) == 7,"La función de recorrido devuelve la cantidad de elementos esperados");
  pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void **)elementos,5) == 5,"Puedo recorrer menos elementos de los existentes para hacer el recorrido.");
  pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void **)elementos,10) == 7,"Puedo recorrer mas elementos de los existentes para hacer el recorrido.");
  abb_destruir_todo(arbol, destructor_de_cosas);
}
void pruebas_de_recorrer_un_arbol_postorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  cosa *elementos[10];
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, (void **)elementos,7) == 7,"La función de recorrido devuelve la cantidad de elementos esperados");
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, (void **)elementos,5) == 5,"Puedo recorrer menos elementos de los existentes para hacer el recorrido.");
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, (void **)elementos,10) == 7,"Puedo recorrer mas elementos de los existentes para hacer el recorrido.");
  abb_destruir_todo(arbol, destructor_de_cosas);
}
void pruebas_de_iterador_interno_preorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, mostrar_elemento, NULL)==7,"El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
  pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, mostrar_hasta_5, NULL)==6,"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");
  abb_destruir_todo(arbol, destructor_de_cosas);
}
void pruebas_de_iterador_interno_inorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento, NULL)==7,"El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
  pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_hasta_5, NULL)==5,"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");
  abb_destruir_todo(arbol, destructor_de_cosas);
}
void pruebas_de_iterador_interno_postorden()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_elemento, NULL)==7,"El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_hasta_5, NULL)==4,"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");
  abb_destruir_todo(arbol, destructor_de_cosas);

}
void pruebas_de_iterador_interno()
{
  pa2m_nuevo_grupo("Iterador interno preorden");
  pruebas_de_iterador_interno_preorden();
  pa2m_nuevo_grupo("Iterador interno inorden");
  pruebas_de_iterador_interno_inorden();
  pa2m_nuevo_grupo("Iterador interno postorden");
  pruebas_de_iterador_interno_postorden();
}

void pruebas_de_destruccion()
{
  abb_t *arbol = abb_crear(comparar_cosas);
  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  abb_insertar(arbol, c4);
  abb_insertar(arbol, c2);
  abb_insertar(arbol, c6);
  abb_insertar(arbol, c1);
  abb_insertar(arbol, c3);
  abb_insertar(arbol, c5);
  abb_insertar(arbol, c7);
  abb_destruir(NULL);
  pa2m_afirmar(true,"Se está por probar si es posible destruir un abb nulo.");
  abb_destruir_todo(NULL , destructor_de_cosas);
  pa2m_afirmar(true,"Se está por probar si es posible destruir un abb nulo con un destructor válido.");
  abb_destruir_todo(arbol, destructor_de_cosas);
  pa2m_afirmar(true,"Se está por probar si es posible destruir un abb valido con elementos reservados con malloc con un destructor válido.");
}
void pruebas_de_recorrer_un_arbol()
{
  pa2m_nuevo_grupo("Recorrido preorden");
  pruebas_de_recorrer_un_arbol_preorden();
  pa2m_nuevo_grupo("Recorrido inorden");
  pruebas_de_recorrer_un_arbol_inorden();
  pa2m_nuevo_grupo("Recorrido postorden");
  pruebas_de_recorrer_un_arbol_postorden();
}
void pruebas_de_null()
{
  abb_t *arbol = abb_crear(NULL);
  pa2m_afirmar(arbol ==NULL,"Crear un abb con comparador null devuelve null");
  cosa *c4 = crear_cosa(4);
  pa2m_afirmar(abb_insertar(arbol, c4) == NULL,"Insertar en un abb nulo devuelve null");
  destruir_cosa(c4);
  pa2m_afirmar(abb_quitar(arbol, c4) == NULL,"Quitar de un abb nulo devuelve null");
  pa2m_afirmar(abb_buscar(arbol, c4) == NULL,"Buscar en un abb nulo devuelve null");
  pa2m_afirmar(abb_vacio(arbol) == true,"Un abb nulo es un arbol vacio");
  pa2m_afirmar(abb_tamanio(arbol) == 0,"Un abb nulo tiene tamanio 0");
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_hasta_5, NULL)==0,"Iterar un abb nulo devuelve cantidad iterados 0");
  abb_t *arbol1 = abb_crear(comparar_cosas);
  pa2m_afirmar(abb_con_cada_elemento(arbol1, POSTORDEN, NULL, NULL)==0,"Iterar un abb con funcion comparador nulo devuelve cantidad iterados 0");
  abb_destruir(arbol1);
  cosa *elementos[10];
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN,(void **)elementos,7)==0,"recorrer un abb nulo devuelve cantidad recorridos 0");
}
int main()
{
  pa2m_nuevo_grupo("Pruebas de ABB");
  pa2m_nuevo_grupo("Pruebas de creacion");
  pruebas_de_creacion();

  pa2m_nuevo_grupo("Pruebas de insercion");
  pruebas_de_insercion();

  pa2m_nuevo_grupo("Pruebas de quitar");
  pruebas_de_quitar();

  pa2m_nuevo_grupo("Pruebas de busqueda");
  pruebas_de_busqueda();

  pa2m_nuevo_grupo("Pruebas de recorrer un arbol");
  pruebas_de_recorrer_un_arbol();

  pa2m_nuevo_grupo("Pruebas de iterador interno");
  pruebas_de_iterador_interno();

  pa2m_nuevo_grupo("Pruebas de destruccion");
  pruebas_de_destruccion();

  pa2m_nuevo_grupo("Pruebas de NULL");
  pruebas_de_null();

  return pa2m_mostrar_reporte();
}
