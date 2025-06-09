#include "help.h"
#include "libs.h"

void print_help(const char *prog_name)
{
    printf(RED "██╗  ██╗███████╗██╗     ██╗      ██████╗ \n");
    printf(ORANGE "██║  ██║██╔════╝██║     ██║     ██╔═══██╗\n");
    printf(YELLOW "███████║█████╗  ██║     ██║     ██║   ██║\n");
    printf(GREEN "██╔══██║██╔══╝  ██║     ██║     ██║   ██║\n");
    printf(CYAN "██║  ██║███████╗███████╗███████╗╚██████╔╝\n");
    printf(BLUE "╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ \n");
    printf(MAGENTA "              ¡Bienvenido al motor de búsqueda!\n" RESET);
    printf("\n");

    printf(YELLOW "        |\\__/,|   (`\\\n");
    printf(YELLOW "      _.|o o  |_   ) )\n");
    printf(YELLOW "    -(((---(((--------\n");
    printf(MAGENTA "       /    " RESET CYAN "HELLO!" RESET MAGENTA "   \\\n");
    printf(RESET);

    printf(CYAN "╔════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" RESET "   " GREEN "Uso del programa:" RESET " ./run.sh + opciones                                      " CYAN "║\n" RESET);
    printf(CYAN "╠════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --in <palabra>" RESET "         Detecta si la palabra está en el texto.      " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --(kmp/bm/algoritmo3) --word <palabra>" RESET "   Busca palabra con algoritmo. " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --(kmp/bm/algoritmo3) --pattern \"patrón\"" RESET "   Busca patrón con algoritmo.  " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "       (el patrón debe ir entre comillas)                                                " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "--compare <archivo1> <archivo2>" RESET "      Analiza similitud entre documentos.       " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --detect" RESET "                       Detecta palabras clave.   " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --proximity <palabra> --tolerance <numero>" RESET "           Mide la proximidad de la palabra con la tolerancia indicada. .   " CYAN "║\n" RESET);
    printf(CYAN "║" RESET "  " YELLOW "-h, --help" RESET "                            Mostrar esta ayuda y salir.               " CYAN "║\n" RESET);
    printf(CYAN "╚════════════════════════════════════════════════════════════════════════════╝\n" RESET);
}