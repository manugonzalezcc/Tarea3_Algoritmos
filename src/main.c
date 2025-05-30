#include <stdio.h>
#include <unistd.h>
#include "tokenizer.h"
#include "search.h"
#include "help.h"
#include "boyer_moore.h" // <-- Agrega esta línea

int main(int argc, char *argv[])
{
    int opt;
    char *archivo = NULL;
    int verbose = 0;

    while ((opt = getopt(argc, argv, "f:vh")) != -1)
    {
        switch (opt)
        {
        case 'f':
            archivo = optarg;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'v':
            verbose = 1;
            break;
        default:
            fprintf(stderr, "Uso: %s -f archivo [-v]\n", argv[0]);
            return 1;
        }
    }

    printf("DEBUG: archivo = %s\n", archivo); // <-- agrega esto

    if (archivo == NULL)
    {
        fprintf(stderr, "El parámetro -f archivo es obligatorio\n");
        return 1;
    }

    printf("Archivo: %s\n", archivo);
    if (verbose)
    {
        printf("Modo verbose activado\n");
    }

    // Prueba de Boyer-Moore
    const char *texto = "este es un texto de prueba, texto de ejemplo";
    const char *patron = "texto";
    int ocurrencias = boyer_moore_bad_char(texto, patron);
    printf("Boyer-Moore: El patrón '%s' aparece %d veces en el texto.\n", patron, ocurrencias);

    return 0;
}