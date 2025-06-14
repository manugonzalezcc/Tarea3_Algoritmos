#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "libs.h"

// Estructura que representa un nodo en el índice invertido
typedef struct IndexNode
{
    char word[100];         // Palabra indexada
    int *positions;         // Arreglo dinámico con posiciones donde aparece la palabra
    int quantity;           // Cantidad actual de posiciones almacenadas
    int capacity;           // Capacidad del arreglo de posiciones
    struct IndexNode *next; // Puntero al siguiente nodo en caso de colisiones (lista enlazada)
} IndexNode;

#define SIZE_IDX 1000                      // Tamaño del arreglo base del índice invertido (hash table)
extern IndexNode *invertedIndex[SIZE_IDX]; // Tabla hash global del índice invertido

// Devuelve el índice hash correspondiente a una palabra
int hash_index(char *word);

// Agrega una palabra con su posición al índice invertido
void add_to_index(const char *word, int position);

// Muestra el índice invertido en consola
void print_index();

// Construye el índice invertido a partir del contenido del texto
void build_index(const char *content);

// Construye el índice invertido desde cero
void build_inverted_index(const char *text);

// Guarda el índice invertido en disco (archivo .idx)
void save_inverted_index(const char *route_idx);

// Carga un índice invertido desde disco (archivo .idx)
int load_inverted_index(const char *route_idx);

// Libera la memoria del índice invertido
void clear_inverted_index(void);

// Verifica si una palabra está en el índice invertido
int word_in_index(const char *word);

#endif
//*