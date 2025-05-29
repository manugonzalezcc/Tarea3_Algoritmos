#include <stdio.h>
#include "../incs/search.h"

int main()
{
    const char *texto = "abracadabra";
    const char *patron = "abra";

    printf("Texto: %s\n", texto);
    printf("Patron a buscar: %s\n", patron);

    int ocurrencias = brute_force_search(texto, patron);

    printf("Numero total de ocurrencias: %d\n", ocurrencias);

    return 0;
}
