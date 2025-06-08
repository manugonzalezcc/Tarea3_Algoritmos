#include "help.h"

void print_help(const char *prog_name)
{
    printf("Uso del programa: ./run.sh -f <ruta_archivo> --algoritmo --pattern \"patron a buscar\"\n");
    printf("Opciones:\n");
    printf("  -f <archivo> --in <palabra> Detecta si la palabra esta en el texto a buscar.\n");
    printf("  -f <ruta_archivo> --(kmp/bm/algoritmo3) --word <palabrar> Busca la palabra dentro del texto con el algoritmo elegido.\n");
    printf("  -f <ruta_archivo> --(kmp/bm/algoritmo3) --pattern \"patron a buscar\" Busca el patrón dentro del texto con el algoritmo elegido.\n");
    printf("  --compare <ruta_archivo_1> <ruta_archivo_2> Analiza la similitud entre los documentos.\n");
    printf("  -f <ruta_archivo> --d Detecta palabras clave. (implementando.....)\n");
    printf("  -h, --help         Mostrar esta ayuda y salir\n");
}