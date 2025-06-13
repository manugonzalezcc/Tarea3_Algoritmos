#ifndef LOAD_H
#define LOAD_H

#define TAM_MAX 10000     // Tamaño máximo para carga de texto
#define MAX_STOPWORDS 800 // Máximo número de stopwords a cargar

#include "libs.h"

// Carga el contenido de un archivo en memoria y retorna un puntero al texto cargado
char *load(const char *ruta_archivo);

// Limpia el texto HTML eliminando etiquetas y contenido irrelevante
void clean_html(char *texto);

// Normaliza el texto (por ejemplo, convertir a minúsculas, eliminar acentos, etc.)
void normalize_text(char *text);

// Carga las stopwords desde un archivo a una matriz de strings
// Retorna la cantidad de stopwords cargadas
int load_stopwords(const char *ruta, char stopwords[][32], int max);

// Verifica si una palabra es una stopword dentro del arreglo dado
// Retorna 1 si es stopword, 0 si no
int is_stopword(const char *palabra, char stopwords[][32], int count);

// Elimina las stopwords del texto dado usando la lista de stopwords
void delete_stopwords(char *texto, char stopwords[][32], int count);

// Función que carga stopwords y elimina todas las stopwords del texto pasado
void stopwords(char *texto, const char *ruta_stopwords);

// Verifica si un archivo existe en el sistema de archivos
// Retorna 1 si existe, 0 si no
int file_exists(const char *name);

#endif
