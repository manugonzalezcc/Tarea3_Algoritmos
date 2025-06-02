#include "help.h"

void print_help(const char *prog_name)
{
    printf("Uso: %s -f <archivo> [-kmp | -bm | -algoritmo3]\n", prog_name);
    printf("Opciones:\n");
    printf("  -f <archivo>       Archivo de texto a procesar (requerido)\n");
    printf("  -kmp               Explica el algoritmo Knuth-Morris-Pratt\n");
    printf("  -bm                Explica el algoritmo Boyer-Moore\n");
    printf("  -algoritmo3        Explica el tercer algoritmo personalizado\n");
    printf("  -h, --help         Mostrar esta ayuda y salir\n");
}
