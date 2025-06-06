#include "boyer_moore.h"

#define ALPHABET_SIZE 256

void badCharHeuristic(const char *pattern, int size, int badchar[ALPHABET_SIZE], int *accesos) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        badchar[i] = -1;
        (*accesos)++;
    }
    for (int i = 0; i < size; i++) {
        badchar[(unsigned char)pattern[i]] = i;
        (*accesos)++;
    }
}

int boyer_moore_bad_char(const char *text, const char *pattern, const char *filename) {
    int n = strlen(text);
    int m = strlen(pattern);
    int badchar[ALPHABET_SIZE];
    int count = 0;
    int comparaciones = 0;
    int accesos = 0;

    if (m == 0) return 0;

    badCharHeuristic(pattern, m, badchar, &accesos);

    clock_t start = clock();

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0) {
            accesos += 2; // acceso a pattern[j] y text[s+j]
            comparaciones++;
            if (pattern[j] != text[s + j])
                break;
            j--;
        }

        if (j < 0) {
            count++;
            if (s + m < n) {
                accesos++; // acceso a text[s+m]
                s += m - badchar[(unsigned char)text[s + m]];
                accesos++;
            } else {
                s += 1;
            }
        } else {
            accesos++; // acceso a text[s+j]
            int bc = badchar[(unsigned char)text[s + j]];
            accesos++;
            s += (j - bc > 1) ? j - bc : 1;
        }
    }

    clock_t end = clock();
    double tiempo_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("\n[Análisis de rendimiento - Boyer-Moore]\n");
    printf("Ocurrencias: %d\n", count);
    printf("Comparaciones: %d\n", comparaciones);
    printf("Accesos a memoria: %d\n", accesos);
    printf("Tiempo de ejecución: %.3f ms\n\n", tiempo_ms);

    FILE *csv = fopen("resultados_bm.csv", "a");
    if (!csv) {
        perror("No se pudo abrir resultados_bm.csv");
        return count;
    }

    fseek(csv, 0, SEEK_END);
    if (ftell(csv) == 0) {
        fprintf(csv, "algoritmo,archivo,patron,comparaciones,accesos_memoria,tiempo_ms\n");
    }

    fprintf(csv, "boyermoore,%s,%s,%d,%d,%.3f\n", filename, pattern, comparaciones, accesos, tiempo_ms);
    fclose(csv);

    return count;
}
