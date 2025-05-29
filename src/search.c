#include <stdio.h>
#include <string.h>
#include "search.h"

int brute_force_search(const char *T, const char *P)
{
    int n = strlen(T);
    int m = strlen(P);
    int count = 0;

    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (T[i + j] != P[j])
            {
                break;
            }
        }
        if (j == m)
        {
            printf("Patron encontrado en la posicion: %d\n", i);
            count++;
        }
    }
    return count;
}
