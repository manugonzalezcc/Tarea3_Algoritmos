#include "search.h"
#include "libs.h"

static int kmp_comparaciones = 0;
static int kmp_accesos_memoria = 0;

void computeLPS(const char *pattern, int M, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M)
    {
        kmp_comparaciones++;
        kmp_accesos_memoria += 2; // pattern[i] y pattern[len]

        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
            kmp_accesos_memoria++; // lps[i]
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
                kmp_accesos_memoria++; // lps[len - 1]
            }
            else
            {
                lps[i] = 0;
                i++;
                kmp_accesos_memoria++; // lps[i]
            }
        }
    }
}

int kmp_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int M = strlen(pattern);
    if (M == 0)
        return 0;

    int *lps = (int *)malloc(M * sizeof(int));
    if (lps == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para LPS\n");
        return -1;
    }

    kmp_comparaciones = 0;
    kmp_accesos_memoria = 0;

    clock_t start = clock();

    computeLPS(pattern, M, lps);

    int i = 0, j = 0, count = 0;

    while (i < n)
    {
        kmp_comparaciones++;
        kmp_accesos_memoria += 2;

        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            printf("Patrón encontrado en la posición: %d\n", i - j);
            count++;
            j = lps[j - 1];
            kmp_accesos_memoria++;
        }
        else if (i < n && pattern[j] != text[i])
        {
            kmp_comparaciones++;
            if (j != 0)
            {
                j = lps[j - 1];
                kmp_accesos_memoria++;
            }
            else
            {
                i++;
            }
        }
    }

    clock_t end = clock();
    double time_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("\n[Análisis de rendimiento - KMP]\n");
    printf("Ocurrencias: %d\n", count);
    printf("Comparaciones: %d\n", kmp_comparaciones);
    printf("Accesos a memoria: %d\n", kmp_accesos_memoria);
    printf("Tiempo de ejecución: %.3f ms\n\n", time_ms);

    FILE *csv = fopen("../resultados_kmp.csv", "a");
    if (!csv)
    {
        perror("No se pudo abrir resultados_kmp.csv");
        free(lps);
        return count;
    }

    fseek(csv, 0, SEEK_END);
    if (ftell(csv) == 0)
    {
        fprintf(csv, "algoritmo,archivo,patron,comparaciones,accesos_memoria,tiempo_ms\n");
    }

    fprintf(csv, "kmp,%s,%s,%d,%d,%.3f\n",
            "resultados_kmp.csv", pattern, kmp_comparaciones, kmp_accesos_memoria, time_ms);

    fclose(csv);

    free(lps);
    return count;
}
