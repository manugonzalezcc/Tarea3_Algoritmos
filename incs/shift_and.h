#ifndef SHIFT_AND_H
#define SHIFT_AND_H

#include "libs.h"

// Función que realiza la búsqueda del patrón en el texto usando el algoritmo Shift-And
// Retorna la cantidad de ocurrencias encontradas
// Parámetros:
// - text: texto donde se busca
// - pattern: patrón a buscar
// - filename: nombre del archivo (usado para posibles mensajes o logs)
int shift_and_search(const char *text, const char *pattern, const char *filename);

#endif
