#include "load.h"

int load_stopwords(const char *ruta, char stopwords[][32], int max)
{
    FILE *file = fopen(ruta, "r");
    if (!file)
    {
        perror("No se pudo abrir stopwords.txt");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%31s", stopwords[count]) == 1 && count < max)
    {
        count++;
    }

    fclose(file);
    return count;
}

int is_stopword(const char *palabra, char stopwords[][32], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(palabra, stopwords[i]) == 0)
            return 1;
    }
    return 0;
}

void delete_stopwords(char *texto, char stopwords[][32], int count)
{
    char *resultado = malloc(strlen(texto) + 1);
    resultado[0] = '\0';

    char *token = strtok(texto, " \n\t");
    while (token != NULL)
    {
        if (!is_stopword(token, stopwords, count))
        {
            strcat(resultado, token);
            strcat(resultado, " ");
        }
        token = strtok(NULL, " \n\t");
    }

    strcpy(texto, resultado);
    free(resultado);
}
