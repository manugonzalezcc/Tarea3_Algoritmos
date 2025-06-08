#include "help.h"

void print_help(const char *prog_name)
{
    printf("Uso del programa: ./run.sh -f <ruta_archivo> --algoritmo --pattern patron_a_buscar\n");
    printf("Opciones:\n");
    printf("  -f <archivo> --in <palabra> Detecta si la palabra esta en el texto a buscar.\n");
    printf("  -f <ruta_archivo> --(kmp/bm/algoritmo3) --word <palabrar> Busca la palabra dentro del texto con el algoritmo elegido.\n");
    printf("  -f <ruta_archivo> --(kmp/bm/algoritmo3) --pattern <patron_a_buscar> Busca el patrón dentro del texto con el algoritmo elegido.\n");
    printf("  -bm                Usa el algoritmo Boyer-Moore (solo carácter malo)\n");
    printf("  -algoritmo3        Usa el algoritmo Shift-And (máx 31 caracteres)\n");
    printf("  --pattern <str>    Patrón a buscar en el texto\n");
    printf("  -q <palabra>       Consulta una palabra en el índice invertido\n");
    printf("  -v, --verbose      Muestra el índice invertido generado\n");
    printf("  -h, --help         Mostrar esta ayuda y salir\n");
}