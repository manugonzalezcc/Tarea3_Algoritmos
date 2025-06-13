#include "help.h"
#include "libs.h"

void print_help()
{
    printf(RED "██╗  ██╗███████╗██╗     ██╗      ██████╗ \n");
    printf(ORANGE "██║  ██║██╔════╝██║     ██║     ██╔═══██╗\n");
    printf(YELLOW "███████║█████╗  ██║     ██║     ██║   ██║\n");
    printf(GREEN "██╔══██║██╔══╝  ██║     ██║     ██║   ██║\n");
    printf(CYAN "██║  ██║███████╗███████╗███████╗╚██████╔╝\n");
    printf(BLUE "╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ \n");
    printf(MAGENTA "              ¡Bienvenido al motor de búsqueda!\n" RESET);
    printf(MAGENTA "             OJO (Debe dar permisos para poder usar el ./run.sh: chmod +x run.sh, lo mismo para los tests: chmod +x run_tests.sh)\n" RESET);

    printf("\n");

    printf(YELLOW "        |\\__/,|   (`\\\n");
    printf(YELLOW "      _.|o o  |_   ) )\n");
    printf(YELLOW "    -(((---(((--------\n");
    printf(MAGENTA "       /    " RESET CYAN "HELLO!" RESET MAGENTA "   \\\n");
    printf(RESET);

    printf(CYAN "╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf(CYAN "║" RESET "   " GREEN "Uso del programa:" RESET " ./run.sh + opciones                                                    " CYAN "║\n");
    printf(CYAN "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --in <palabra>" RESET
                "                      Detecta si la palabra está en el texto.                   " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --(kmp/bm/shift_and) --word <palabra>" RESET
                "    Busca la palabra en el texto.                " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --(kmp/bm/shift_and) --pattern \"patrón\"" RESET
                "        Buscar patrón en el texto.                  " CYAN "║\n");

    printf(CYAN "║" RESET "       (el patrón debe ir entre comillas dobles)                                      " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "--compare <archivo1> <archivo2>" RESET
                "                Compara el contenido de dos documentos.              " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --detect" RESET
                "                               Detecta palabras clave dentro del archivo.      " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --proximity <palabra>" RESET
                "                                                  " CYAN "║\n");
    printf(CYAN "║" RESET "            " YELLOW "--tolerance <número>" RESET
                "                Busca palabras cercanas con margen de error.       " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <archivo> --index" RESET
                "                                Muestra índice invertido de palabras.          " CYAN "║\n");
    printf(CYAN "║" RESET "  " YELLOW "--ranking <palabra>" RESET
                "                                Muestra el ranking segun la palabra ingresada, busca en todos los documentos .txt o .html de docs/      " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-h, --help" RESET
                "                                     Mostrar esta ayuda del sistema.            " CYAN "║\n");

    printf(CYAN "╚════════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);
}
//*