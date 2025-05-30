#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

void computeLPS(const char *pattern, int M, int *lps)
{
    int len = 0; // prefijo mas grande (tambien sufijo)
    lps[0] = 0;  // primer siempre 0
    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                // no se reinicia a 0, se utiliza el valor previo del lps
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// recorre el texto y, utilizando el array lps, evita comparaciones redundantes
int kmp_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int M = strlen(pattern);
    if (M == 0)
    {
        return 0; // si el patron es vacio, se retornan 0
    }

    // guardamos memoria para el array lps.
    int *lps = (int *)malloc(M * sizeof(int));
    if (lps == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para el array LPS\n");
        return -1;
    }

    // calcular el array de fallos (LPS)
    computeLPS(pattern, M, lps);

    int i = 0; // indice para el texto
    int j = 0; // indice para el patrón
    int count = 0;

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            // se encontro una ocurrencia del patron
            printf("Patrón encontrado en la posición: %d\n", i - j);
            count++;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            // si ocurre una discrepancia y j > 0, se utiliza el LPS para evitar retroceder en i
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    free(lps);
    return count;
}
