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
    printf(CYAN "\n╔══════════════════════════════╦══════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" RESET "      " YELLOW "PALABRA" RESET "                 " CYAN "║" RESET "          " YELLOW "POSICIONES" RESET "                      " CYAN "║\n" RESET);
    printf(CYAN "╠══════════════════════════════╬══════════════════════════════════════╣\n" RESET);

    for (int i = 0; i < SIZE_IDX; i++)
    {
        NodoIndice *nodo = indiceInvertido[i];
        while (nodo != NULL)
        {
            printf(CYAN "║ " RESET BLUE "%-28s" RESET CYAN " ║ " RESET GREEN, nodo->palabra);
            for (int j = 0; j < nodo->cantidad; j++)
            {
                printf("%d", nodo->posiciones[j]);
                if (j != nodo->cantidad - 1)
                    printf(", ");
            }
            printf(RESET CYAN " ║\n" RESET);
            nodo = nodo->siguiente;
        }
    }

    printf(CYAN "╚══════════════════════════════╩══════════════════════════════════════╝\n\n" RESET);
}

void construir_indice(const char *content)
{
    char palabra[100];
    int pos = 0;

    for (int i = 0; content[i];)
    {
        int j = 0;

        while (content[i] && (isalpha(content[i]) || content[i] == '_'))
        {
            palabra[j++] = tolower(content[i++]);
        }

        if (j > 0)
        {
            palabra[j] = '\0';
            pos++;
            agregar_al_indice(palabra, pos);
        }

        while (content[i] && !isalpha(content[i]) && content[i] != '_')
        {
            i++;
        }
    }
}
