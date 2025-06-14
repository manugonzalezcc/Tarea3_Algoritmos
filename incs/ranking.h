#ifndef RANKING_H
#define RANKING_H

#include "libs.h"

// Estructura que guarda el nombre de un archivo y la cantidad de veces que aparece un patrón
typedef struct
{
    char file_name[128];         // Nombre del archivo
    int quantity_of_appearances; // Cantidad de apariciones del patrón en ese archivo
} Result;

// Busca el patrón en un conjunto de archivos y muestra resultados
void search_in_docs(const char *pattern, char *files[], int files_number);

// Lista los archivos válidos dentro de un directorio dado
// Retorna un arreglo dinámico con los nombres de archivos y actualiza la cantidad
char **list_valid_files(const char *directory, int *quantity);

#endif
//*