#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
#include "libs.h"

typedef struct NodoIndice {
    char palabra[100];
    int *posiciones;
    int cantidad;
    int capacidad;
    struct NodoIndice *siguiente;
} NodoIndice;

#define SIZE_IDX 1000
extern NodoIndice *indiceInvertido[SIZE_IDX];


void build_inverted_index(const char *texto);
void save_inverted_index(const char *ruta_idx);
int  load_inverted_index(const char *ruta_idx);
void clear_inverted_index(void);
int  word_in_index(const char *palabra);


#endif
