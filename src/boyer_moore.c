#include "boyer_moore.h"

#define ALPHABET_SIZE 256

// Preprocesa la tabla de carácter malo
void badCharHeuristic(const char *pattern, int size, int badchar[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(unsigned char)pattern[i]] = i;
}

// Implementación de Boyer-Moore con heurística de carácter malo
int boyer_moore_bad_char(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badchar[ALPHABET_SIZE];
    int count = 0;

    if (m == 0) return 0;

    badCharHeuristic(pattern, m, badchar);

    int s = 0; // desplazamiento del patrón sobre el texto
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            count++;
            s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
        } else {
            int bc = badchar[(unsigned char)text[s + j]];
            s += (j - bc > 1) ? j - bc : 1;
        }
    }
    return count;
}