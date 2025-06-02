#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "tokenizer.h"
#include "search.h"
#include "help.h"
#include "boyer_moore.h"

int main(int argc, char *argv[])
{
    int opt;
    char *archivo = NULL;

    int usar_kmp = 0;
    int usar_bm = 0;
    int usar_algoritmo3 = 0;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'}, // -f o --file
        {"verbose", no_argument, 0, 'v'},    // -v o --verbose
        {"help", no_argument, 0, 'h'},       // -h o --help
        {"kmp", no_argument, 0, 1},          // --kmp
        {"bm", no_argument, 0, 2},           // --bm
        {"algoritmo3", no_argument, 0, 3},   // --algoritmo3
        {0, 0, 0, 0}};

    int long_index = 0;

    while ((opt = getopt_long(argc, argv, "f:vh", long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'f':
            archivo = optarg;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 1:
            usar_kmp = 1;
            break;
        case 2:
            usar_bm = 1;
            break;
        case 3:
            usar_algoritmo3 = 1;
            break;
        default:
            fprintf(stderr, "Uso: %s -f <archivo> [-kmp | -bm | -algoritmo3]\n", argv[0]);
            return 1;
        }
    }

    if (archivo == NULL)
    {
        fprintf(stderr, "El parámetro -f archivo es obligatorio\n");
        return 1;
    }

    if (!usar_kmp && !usar_bm && !usar_algoritmo3)
    {
        fprintf(stderr, "Debes especificar uno de: --kmp, --bm, --algoritmo3\n");
        return 1;
    }

    if (usar_kmp)
    {
        printf("Ejecutando búsqueda con KMP...\n");
    }
    else if (usar_bm)
    {
        const char *texto = "este es un texto de prueba, texto de ejemplo";
        const char *patron = "texto";
        int ocurrencias = boyer_moore_bad_char(texto, patron);
        printf("Boyer-Moore: El patrón '%s' aparece %d veces en el texto.\n", patron, ocurrencias);
    }
    else if (usar_algoritmo3)
    {
        printf("Ejecutando búsqueda con algoritmo3...\n");
    }

    return 0;
}
