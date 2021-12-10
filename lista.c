#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
    void *dato;
    struct nodo *siguiente;
} lista_nodo_t;

struct lista{
    lista_nodo_t *primero;
    lista_nodo_t *ultimo;
    size_t largo;
};

struct lista_iter {
	lista_t* lista;
    lista_nodo_t* anterior;
    lista_nodo_t* actual;
};

lista_nodo_t *nodo_crear(void *valor){
    lista_nodo_t *nodo = malloc(sizeof(lista_nodo_t));
    if (!nodo){
        return NULL;
    }

    nodo->dato = valor;
    nodo->siguiente = NULL;
    return nodo;
}

lista_t *lista_crear(void){
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista){
        return NULL;
    }

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *valor){
    lista_nodo_t *nuevo_nodo = nodo_crear(valor);
    if (!nuevo_nodo){
        return false;
    }

    if (lista_esta_vacia(lista)){
        lista->ultimo = nuevo_nodo;
    }
    nuevo_nodo->siguiente = lista->primero;
    lista->primero = nuevo_nodo;
    lista->largo ++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *valor){
    lista_nodo_t *nuevo_nodo = nodo_crear(valor);
    if (!nuevo_nodo){
        return false;
    }

    if (lista_esta_vacia(lista)){
        lista->primero = nuevo_nodo;
    }
    else{
        lista->ultimo->siguiente = nuevo_nodo;
    }
    lista->ultimo = nuevo_nodo;
    lista->largo++;
    return true;
}

void *lista_ver_primero(const lista_t *lista){
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t *lista){
    return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}

void *lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }

    lista_nodo_t *viejo_primero = lista->primero;
    void *viejo_dato_primero = viejo_primero->dato;

    lista->primero = lista->primero->siguiente;
    if (lista_esta_vacia(lista)){
        lista->ultimo = NULL;
    }

    free(viejo_primero);
    lista->largo--;
    return viejo_dato_primero;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while (!lista_esta_vacia(lista)){
        void *dato = lista_borrar_primero(lista);
        if (destruir_dato){
            destruir_dato(dato);
        }
    }
    free(lista);
}

/* *****************************************************************
 *                    ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t *iterador = malloc(sizeof(lista_iter_t));
    if (!iterador){
        return NULL;
    }

    iterador->lista = lista;
    iterador->actual = lista->primero;
    iterador->anterior = NULL;
    return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->siguiente;
    return true;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return !iter->actual;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    return lista_iter_al_final(iter) ? NULL : iter->actual->dato;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    lista_nodo_t *nuevo_nodo = nodo_crear(dato);
    if (!nuevo_nodo){
        return false;
    }

    nuevo_nodo->siguiente = iter->actual;

    // Caso estar al final de la lista.
    if (lista_iter_al_final(iter)){
        iter->lista->ultimo = nuevo_nodo;
    }
    // Caso no hay anterior, es decir, estoy en la primera posicion.
    if (!iter->anterior){
        iter->lista->primero = nuevo_nodo;
    }
    // Cualquiera otra posiscion.
    else{
        iter->anterior->siguiente = nuevo_nodo;
    }

    iter->actual = nuevo_nodo;
    iter->lista->largo += 1;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return NULL;
    }
    
    lista_nodo_t *viejo_actual = iter->actual;
    void *dato_viejo_actual = viejo_actual->dato;
    iter->actual = viejo_actual->siguiente;

    // Caso elimino el ultimo elemento.
    if (lista_iter_al_final(iter)){
        iter->lista->ultimo = iter->anterior;
    }
    // Caso no hay anterior, es decir, estoy en la primera posicon.
    if (!iter->anterior){
        iter->lista->primero = iter->actual;
    }
    // Cualquier otra posicion.
    else{
        iter->anterior->siguiente = iter->actual;
    }

    free(viejo_actual);
    iter->lista->largo -= 1;
    return dato_viejo_actual;
}

/* *****************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    lista_nodo_t *actual = lista->primero;

    while (actual){
        if (visitar(actual->dato, extra) == false){
            break;
        }
        actual = actual->siguiente;
    }
}
