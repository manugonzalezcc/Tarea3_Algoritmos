#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

#define TAM_MAX 1000000

char *cargar_archivo(const char *ruta_archivo)
{
    FILE *archivo = fopen(ruta_archivo, "r");
    if (!archivo)
    {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char *buffer = (char *)malloc(TAM_MAX);
    if (!buffer)
    {
        perror("Error de memoria");
        fclose(archivo);
        return NULL;
    }

    size_t leido = fread(buffer, 1, TAM_MAX - 1, archivo);
    buffer[leido] = '\0';

    fclose(archivo);
    return buffer;
}

void limpiar_html(char *texto)
{
    char *lectura = texto;
    char *escritura = texto;
    int dentro_etiqueta = 0;

    while (*lectura)
    {
        if (*lectura == '<')
        {
            dentro_etiqueta = 1;
        }
        else if (*lectura == '>')
        {
            dentro_etiqueta = 0;
            lectura++;
            continue;
        }
        else if (!dentro_etiqueta)
        {
            *escritura++ = *lectura;
        }
        lectura++;
    }
    *escritura = '\0';
}
