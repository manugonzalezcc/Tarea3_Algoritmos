#include "load.h"
#include "libs.h"

char *load(const char *route)
{
    FILE *file = fopen(route, "r");
    if (!file)
    {
        perror("Error al abrir el file");
        return NULL;
    }

    char *buffer = (char *)malloc(TAM_MAX);
    if (!buffer)
    {
        perror("Error de memoria");
        fclose(file);
        return NULL;
    }

    size_t readed = fread(buffer, 1, TAM_MAX - 1, file);
    buffer[readed] = '\0';

    fclose(file);
    return buffer;
}

void clean_html(char *texto)
{
    char *read = texto;
    char *write = texto;
    int label = 0;

    while (*read)
    {
        if (*read == '<')
        {
            label = 1;
        }
        else if (*read == '>')
        {
            label = 0;
            read++;
            continue;
        }
        else if (!label)
        {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}
