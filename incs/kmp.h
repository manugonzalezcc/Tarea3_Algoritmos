#ifndef SEARCH_H
#define SEARCH_H

#include "libs.h"

// Realiza la búsqueda de un patrón en un texto usando el algoritmo KMP.
// Muestra las posiciones donde se encontró el patrón
// y devuelve el número total de apariciones.
int kmp_search(const char *text, const char *pattern);

// Calcula el arreglo LPS (Longest Prefix Suffix) necesario para el algoritmo KMP.
// pattern: el patrón de búsqueda
// M: longitud del patrón
// lps: arreglo donde se guardará el resultado
void computeLPS(const char *pattern, int M, int *lps);

#endif
//*