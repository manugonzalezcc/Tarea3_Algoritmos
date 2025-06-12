
#ifndef AUX_H
#define AUX_H

#include "libs.h"

// -------------------- UTILIDADES --------------------
void ensure_index(const char *route_txt, const char *content);

int valid_file(const char *file);

// -------------------- FUNCIONES DE OPERACIONES --------------------
void exec_kmp(char *content, const char *pattern, const char *word);

void exec_boyer_moore(char *content, const char *pattern, const char *file);

int exec_shift_and(char *content, const char *pattern, const char *file);

void exec_comparate(const char *file1, const char *file2);

void count_top_words(char *content);

void exec_proximity(char *content, const char *word, int tolerance);

void build_and_show_index(char *content);

void exec_ranking(const char *word);

void tell_joke();

#endif