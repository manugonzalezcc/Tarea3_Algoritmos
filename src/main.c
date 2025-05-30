#include <stdio.h>
#include <unistd.h>
#include "tokenizer.h"
#include "search.h"
#include "help.h"

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
        case 'h':
            print_help(argv[0]);
            return 0;
            break;
        case 'v':
            verbose = 1;
            break;
        default:
            fprintf(stderr, "Uso: %s -f archivo [-v]\n", argv[0]);
            return 1;
        }
    }

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

    return 0;
}
