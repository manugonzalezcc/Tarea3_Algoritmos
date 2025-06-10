#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "libs.h"

typedef struct NodoIndice
{
    char palabra[100];
    int *posiciones;
    int cantidad;
    int capacidad;
    struct NodoIndice *siguiente;
} NodoIndice;

#define SIZE_IDX 1000
extern NodoIndice *indiceInvertido[SIZE_IDX];

int hash_indice(char *palabra);
void agregar_al_indice(const char *palabra, int posicion);
void imprimir_indice();
void construir_indice(const char *content);

#endif
