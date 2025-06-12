#ifndef LOAD_H
#define LOAD_H
#define TAM_MAX 1000000
#define MAX_STOPWORDS 800
#include "libs.h"

char *load(const char *ruta_archivo);

void clean_html(char *texto);

void normalize_text(char *text);

int load_stopwords(const char *ruta, char stopwords[][32], int max);

int is_stopword(const char *palabra, char stopwords[][32], int count);

void delete_stopwords(char *texto, char stopwords[][32], int count);

void stopwords(char *texto, const char *ruta_stopwords);

int file_exists(const char *name);

#endif
