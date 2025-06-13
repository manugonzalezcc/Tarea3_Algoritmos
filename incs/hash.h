#ifndef HASH_H
#define HASH_H

#include "libs.h"

#define SIZE 1000 // Tamaño de la tabla hash

// Definición de estructura para los nodos de la tabla hash
typedef struct node
{
    char word[100];    // Palabra almacenada
    int frequency;     // Frecuencia de aparición de la palabra
    struct nodo *next; // Puntero al siguiente nodo (para manejar colisiones)
} Node;

// Declaración de la tabla hash como un arreglo de punteros a nodos
extern Node *tablaHash[SIZE];

// Función hash que convierte una palabra en un índice de la tabla
int hash(char *palabra);

// Inserta una palabra en la tabla hash o incrementa su frecuencia si ya existe
void insert(char *palabra);

// Imprime toda la tabla hash con sus palabras y frecuencias
void printf_hash_table(void);

// Construye la tabla hash a partir de un texto completo
void build_hash_table(char *texto);

// Retorna la frecuencia de una palabra buscada
int word_frequency(const char *palabra_buscada);

// Verifica si una palabra está presente en el texto (usando la tabla hash)
int is_in_text(const char *word_to_search);

// Libera la memoria utilizada por la tabla hash
void clear_hash_table();

// Imprime las palabras más frecuentes de la tabla hash
void printf_top_from_hash_table(void);

#endif
