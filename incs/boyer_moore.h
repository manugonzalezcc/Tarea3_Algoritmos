#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include "libs.h"

// Ejecuta la búsqueda de un patrón en un texto utilizando el algoritmo de Boyer-Moore
// con la heurística del carácter incorrecto. Retorna la cantidad de ocurrencias encontradas.
int boyer_moore_bad_char(const char *text, const char *pattern, const char *filename);

#endif
//*