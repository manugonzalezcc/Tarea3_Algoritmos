#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include "libs.h"

// Devuelve el mínimo entre tres valores enteros
int min(int a, int b, int c);

// Calcula la distancia de Levenshtein entre dos cadenas de texto
// (número mínimo de operaciones necesarias para transformar una en otra)
int levenshtein(const char *s1, const char *s2);

// Busca palabras similares en un documento según una tolerancia dada
// usando la distancia de Levenshtein
void search_similar_words(const char *route_doc, const char *query, int tolerance);

#endif
