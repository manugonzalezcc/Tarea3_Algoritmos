#include "tokenizer.h"
#include "libs.h"

void normalizar_token(char *token)
{
    for (int i = 0; token[i]; i++)
    {
        token[i] = tolower(token[i]);
    }
}

ListaTokens tokenizar_texto(const char *texto)
{
    ListaTokens resultado;
    resultado.tokens = malloc(sizeof(char *) * MAX_TOKENS);
    resultado.cantidad = 0;

    const char *delimitadores = " \t\n\r.,;:!?\"()[]{}<>|\\/";

    char *copia = strdup(texto);
    char *token = strtok(copia, delimitadores);

    while (token && resultado.cantidad < MAX_TOKENS)
    {
        normalizar_token(token);
        resultado.tokens[resultado.cantidad] = strdup(token);
        resultado.cantidad++;
        token = strtok(NULL, delimitadores);
    }

    free(copia);
    return resultado;
}

void liberar_tokens(ListaTokens lista)
{
    for (int i = 0; i < lista.cantidad; i++)
    {
        free(lista.tokens[i]);
    }
    free(lista.tokens);
}
