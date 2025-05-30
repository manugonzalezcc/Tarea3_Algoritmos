#include "help.h"

void print_help(const char *prog_name)
{
    printf("Uso: %s [opciones]\n", prog_name);
    printf("Opciones:\n");
    printf("  -f <archivo>   Archivo de texto a procesar (requerido)\n");
    printf("  -v             Modo verbose (mostrar detalles adicionales)\n");
    printf("  -h, --help     Mostrar esta ayuda y salir\n");
}

