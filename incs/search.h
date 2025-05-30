#ifndef SEARCH_H
#define SEARCH_H

// muestra las posiciones donde se encontro el patrn y devuelve el número total de apariciones
int kmp_search(const char *text, const char *pattern);
void computeLPS(const char *pattern, int M, int *lps);

#endif
