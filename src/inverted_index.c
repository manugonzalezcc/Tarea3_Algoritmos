#include "inverted_index.h"

NodoIndice *indiceInvertido[SIZE_IDX] = {0};

int hash_indice(char *palabra)
{
    int hash = 0;
    for (int i = 0; palabra[i]; i++)
    {
        hash = (hash * 31 + palabra[i]) % SIZE_IDX;
    }
    return hash;
}

void agregar_al_indice(const char *palabra, int posicion)
{
    int h = hash_indice((char *)palabra);
    NodoIndice *actual = indiceInvertido[h];
    while (actual)
    {
        if (strcmp(actual->palabra, palabra) == 0)
        {
            if (actual->cantidad == actual->capacidad)
            {
                actual->capacidad *= 2;
                actual->posiciones = realloc(actual->posiciones, actual->capacidad * sizeof(int));
            }
            actual->posiciones[actual->cantidad++] = posicion;
            return;
        }
        actual = actual->siguiente;
    }

    NodoIndice *nuevo = malloc(sizeof(NodoIndice));
    strcpy(nuevo->palabra, palabra);
    nuevo->capacidad = 4;
    nuevo->posiciones = malloc(nuevo->capacidad * sizeof(int));
    nuevo->posiciones[0] = posicion;
    nuevo->cantidad = 1;
    nuevo->siguiente = indiceInvertido[h];
    indiceInvertido[h] = nuevo;
}

void imprimir_indice()
{
    for (int i = 0; i < SIZE_IDX; i++)
    {
        NodoIndice *nodo = indiceInvertido[i];
        while (nodo != NULL)
        {
            printf("%s: ", nodo->palabra);
            for (int j = 0; j < nodo->cantidad; j++)
            {
                printf("%d ", nodo->posiciones[j]);
            }
            printf("\n");
            nodo = nodo->siguiente;
        }
    }
}