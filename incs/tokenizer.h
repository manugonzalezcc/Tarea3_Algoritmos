#ifndef TOKENIZER_H
#define TOKENIZER_H
#define MAX_TOKENS 10000
#include "libs.h"

typedef struct
{
    char **tokens;
    int quantity;
} TokenList;

// se devuelve la lista de tokens
TokenList tokenize_text(const char *text);

// libera la memoria de la lista de tokens
void free_tokens(TokenList list);

#endif
