#include "hash.h"
#include "libs.h"

int hash(char *palabra)
{
    int hash = 0;
    for (int i = 0; palabra[i]; i++)
    {
        hash = (hash * 31 + palabra[i]) % SIZE;
    }
    return hash;
}

void insertar(char *palabra)
{
    int h = hash(palabra);
    Nodo *temp = tablaHash[h];
    while (temp)
    {
        if (strcmp(temp->palabra, palabra) == 0)
        {
            temp->frecuencia++;
            return;
        }
        temp = temp->siguiente;
    }

    Nodo *nuevo = malloc(sizeof(Nodo));
    strcpy(nuevo->palabra, palabra);
    nuevo->frecuencia = 1;
    nuevo->siguiente = tablaHash[h];
    tablaHash[h] = nuevo;
}

void imprimirTabla()
{
    for (int i = 0; i < SIZE; i++)
    {
        Nodo *temp = tablaHash[i];
        while (temp)
        {
            printf("'%s' -> %d\n", temp->palabra, temp->frecuencia);
            temp = temp->siguiente;
        }
    }
}

void construirTablaHash(char *texto)
{
    char *delimiters = " \n\t.,;:!?\"()[]{}<>-";
    char *palabra = strtok(texto, delimiters);

    while (palabra != NULL)
    {
        insertar(palabra);
        palabra = strtok(NULL, delimiters);
    }
}