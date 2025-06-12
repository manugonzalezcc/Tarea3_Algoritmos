#include "tokenizer.h"
#include "libs.h"

void normalizar_token(char *token)
{
    for (int i = 0; token[i]; i++)
    {
        token[i] = tolower(token[i]);
    }
}

TokenList tokenize_text(const char *text)
{
    TokenList result;
    result.tokens = malloc(sizeof(char *) * MAX_TOKENS);
    result.quantity = 0;

    const char *delimiters = " \t\n\r.,;:!?\"()[]{}<>|\\/";

    char *copy = strdup(text);
    char *token = strtok(copy, delimiters);

    while (token && result.quantity < MAX_TOKENS)
    {
        normalizar_token(token);
        result.tokens[result.quantity] = strdup(token);
        result.quantity++;
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return result;
}

void free_tokens(TokenList list)
{
    for (int i = 0; i < list.quantity; i++)
    {
        free(list.tokens[i]);
    }
    free(list.tokens);
}
