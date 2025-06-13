#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include "libs.h"

int min(int a, int b, int c);

int levenshtein(const char *s1, const char *s2);
void buscar_palabras_similares(const char *ruta_doc, const char *query, int tolerancia);

#endif
//*