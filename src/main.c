#include "load.h"
#include "tokenizer.h"
#include "libs.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s archivo.txt\n", argv[0]);
        return 1;
    }

    char *texto = load(argv[1]);
    if (!texto)
        return 1;

    clean_html(texto);

    ListaTokens tokens = tokenizar_texto(texto);

    for (int i = 0; i < tokens.cantidad; i++)
    {
        printf("Token %d: %s\n", i + 1, tokens.tokens[i]);
    }

    liberar_tokens(tokens);
    free(texto);
    return 0;
}
