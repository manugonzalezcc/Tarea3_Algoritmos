#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include "libs.h"

int min(int a, int b, int c);

int levenshtein(const char *s1, const char *s2);
void search_similar_words(const char *ruta_doc, const char *query, int tolerancia);

#endif