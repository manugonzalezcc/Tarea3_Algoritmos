#ifndef RANKING_H
#define RANKING_H
#include "libs.h"

typedef struct
{
    char file_name[128];
    int quantity_of_appearances;
} Result;

void search_in_docs(char *pattern, char *files[], int files_number);
char **list_valid_files(const char *directory, int *quantity);

#endif
//*