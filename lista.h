#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdbool.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista en el primer lugar. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista en el último lugar. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del último, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t *lista);

// Devuelve el largo de la lista.
// Pre: la lista fue creada
// Post: se devolvió la cantidad de elementos que hay en la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/*******************************************************************
 *                      ITERADORES
 * *****************************************************************/

/* *********************  INTERNO ******************************** */

// Itera toda la lista mientras visitar sea true.
// Pre: la lista fue creada.
// Post: se iteró la lista utilizando visitar en cada elemento.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ********************* EXTERNO  ******************************** */
typedef struct lista_iter lista_iter_t;

// Crea un iterador de la lista.
// Pre: la lista fue creada.
// Post: devuelve un nuevo iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanaza un posicion en la lista en caso de ser posible.
// Pre: el itereador fue creado.
// Post: si el iterador no se encuentra en el final, avanza un posicion.
// sino devuelve false.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato actual que esta el iterador.
// Pre: el iterador fue creado.
// Post: devuelve el dato actual.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve si el iterador esta en el ultimo elemento de la lista.
// Pre: el iterador fue creado.
// Post: devuelve true si esta al final de la lista, false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se destruyó el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento donde se encuentre el iterador.
// Pre: el iterador fue creado y el dato a guardar es pasado por parametro.
// Post: se agregó un elemento en la posicion actual.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento donde se encuentre el iterador.
// Pre: el iterador fue creado.
// Post: se eliminó el elemento en la posicion que estaba el iterador.
void *lista_iter_borrar(lista_iter_t *iter);
/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_estudiante(void);

#endif // LISTA_H
