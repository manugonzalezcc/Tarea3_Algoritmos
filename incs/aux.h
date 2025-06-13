#ifndef AUX_H
#define AUX_H

#include "libs.h"

// -------------------- UTILIDADES --------------------

// Genera el índice invertido si no existe previamente para un archivo dado
void ensure_index(const char *route_txt, const char *content);

// Verifica si el archivo entregado es válido y existe
int valid_file(const char *file);

// -------------------- FUNCIONES DE OPERACIONES --------------------

// Ejecuta la búsqueda utilizando el algoritmo KMP (Knuth-Morris-Pratt)
void exec_kmp(char *content, const char *pattern, const char *word);

// Ejecuta la búsqueda utilizando el algoritmo Boyer-Moore
void exec_boyer_moore(char *content, const char *pattern, const char *file);

// Ejecuta la búsqueda utilizando el algoritmo Shift-And
int exec_shift_and(char *content, const char *pattern, const char *file);

// Compara dos archivos y calcula su similitud
void exec_comparate(const char *file1, const char *file2);

// Muestra las palabras más frecuentes en el texto
void count_top_words(char *content);

// Busca palabras similares dentro de una tolerancia dada (basado en Levenshtein)
void exec_proximity(char *content, const char *word, int tolerance);

// Construye e imprime el índice invertido del texto
void build_and_show_index(char *content);

// Ejecuta la búsqueda con ranking en todos los archivos disponibles
void exec_ranking(const char *word);

// Muestra un chiste relacionado con programación
void tell_joke();

#endif
