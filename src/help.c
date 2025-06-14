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
    printf(MAGENTA "¡Bienvenido al motor de búsqueda!\n" RESET);
    printf(MAGENTA "OJO (Debe dar permisos para poder usar el ./run.sh: chmod +x run.sh, lo mismo para los tests: chmod +x run_tests.sh)\n" RESET);

    printf(YELLOW "╭────────────╮   ╭──────────────────────────────╮   ╭────────────────────────────────────╮\n");
    printf(YELLOW "│ (•◡•)つ    │   │ (•◡•)つ                      │   │ (¬‿¬)                              │\n");
    printf(YELLOW "│  ¡Hola!    │   │  Bienvenido al código.       │   │  ¿Qué le dijo el puntero nulo      │\n");
    printf(YELLOW "│            │   │                              │   │      a la función?                 │\n");
    printf(YELLOW "│            │   │                              │   │  —¡Sigue sin mí!                   │\n");
    printf(YELLOW "╰────────────╯   ╰──────────────────────────────╯   ╰────────────────────────────────────╯\n");

    printf(CYAN "╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf(CYAN "║" RESET "   " GREEN "Uso del programa:" RESET " ./run.sh + opciones                                                    " CYAN "║\n");
    printf(CYAN "║" RESET "   " GREEN "Ejemplo:" RESET " ./run.sh docs/doc1.html --in hola                                               " CYAN "║\n");
    printf(CYAN "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --in <palabra>" RESET
                "     Detecta si la palabra está en el texto.   " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --kmp --word <palabra>" RESET
                " Busca la palabra en el texto.         " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --(kmp/bm/shift_and) --pattern \"patrón\"" RESET
                "        Buscar patrón " CYAN "║\n");

    printf(CYAN "║" RESET "  en el texto. (el patrón debe ir entre comillas dobles)                                    " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "--compare <ruta_archivo1> <ruta_archivo2>" RESET
                "        Compara el contenido de dos documentos.  " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --detect" RESET
                "     Detecta palabras clave dentro del archivo.      " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --proximity <palabra>" RESET
                "                                        " CYAN "║\n");
    printf(CYAN "║" RESET "            " YELLOW "--tolerance <número>" RESET
                "        Busca palabras cercanas con margen de error.        " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-f <ruta_archivo_desde_raiz> --index" RESET
                "        Muestra índice invertido de palabras.         " CYAN "║\n");
    printf(CYAN "║" RESET "  " YELLOW "--ranking <palabra>" RESET
                " Muestra el ranking segun la palabra ingresada, busca en todos los documentos .txt o .html de docs/" CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "-h, --help" RESET
                "      Mostrar esta ayuda del sistema.                                           " CYAN "║\n");

    printf(CYAN "║" RESET "  " YELLOW "--joke" RESET
                "           Chiste oculto de algoritmos.                                             " CYAN "║\n");

    printf(CYAN "╚════════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);
}
//*