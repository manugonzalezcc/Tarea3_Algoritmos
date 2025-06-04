#include "help.h"

void print_help(const char *prog_name)
{
    printf("Uso del programa: ./run.sh -f <ruta_archivo> --algoritmo --pattern patron_a_buscar\n");
    printf("Opciones:\n");
    printf("  -f <archivo>       Archivo de texto a procesar (requerido)\n");
    printf("  -kmp               Explica el algoritmo Knuth-Morris-Pratt\n");
    printf("  -bm                Explica el algoritmo Boyer-Moore\n");
    printf("  -algoritmo3        Explica el tercer algoritmo personalizado\n");
    printf("  -h, --help         Mostrar esta ayuda y salir\n");
}
