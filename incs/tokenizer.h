#ifndef TOKENIZER_H
#define TOKENIZER_H
#define MAX_TOKENS 10000
#include "libs.h"

typedef struct
{
    char **tokens;
    int cantidad;
} ListaTokens;

// se devuelve la lista de tokens
ListaTokens tokenizar_texto(const char *texto);

// libera la memoria de la lista de tokens
void liberar_tokens(ListaTokens lista);

#endif