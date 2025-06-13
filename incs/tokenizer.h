#ifndef TOKENIZER_H
#define TOKENIZER_H

#define MAX_TOKENS 10000

#include "libs.h"

// Estructura que contiene una lista de tokens y su cantidad
typedef struct
{
    char **tokens; // Arreglo dinámico de cadenas con los tokens
    int quantity;  // Cantidad de tokens almacenados
} TokenList;

// Función que recibe un texto y devuelve una lista de tokens extraídos del texto
TokenList tokenize_text(const char *text);

// Función que libera la memoria asignada a la lista de tokens
void free_tokens(TokenList list);

#endif
