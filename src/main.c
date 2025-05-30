#include <stdio.h>
#include "../incs/search.h"

int main()
{
    const char *text = "ABABDABACDABABCABAB";
    const char *pattern = "ABABCABAB";

    printf("Texto: %s\n", text);
    printf("Patrón a buscar: %s\n", pattern);

    int ocurrencias = kmp_search(text, pattern);
    printf("Número total de ocurrencias: %d\n", ocurrencias);

    return 0;
}
