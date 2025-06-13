#include "libs.h"
#include "shift_and.h"

int shift_and_search(const char *text, const char *pattern, const char *filename) {
    int m = strlen(pattern);
    if (m > 31) {
        fprintf(stderr, "El patrón es demasiado largo para Shift-And (máx 31 caracteres)\n");
        return -1;
    }

    int comparaciones = 0;
    int accesos = 0;

    unsigned int mask[256] = {0};
    for (int i = 0; i < m; i++) {
        mask[(unsigned char)pattern[i]] |= 1 << i;
        accesos++;
    }

    clock_t start = clock();

    unsigned int R = 0;
    unsigned int last_bit = 1 << (m - 1);
    int count = 0;

    for (int i = 0; text[i]; i++) {
        accesos++;
        R = ((R << 1) | 1) & mask[(unsigned char)text[i]];
        comparaciones++; // simulamos que siempre comparamos
        if (R & last_bit) {
            count++;
        }
    }

    clock_t end = clock();
    double tiempo_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("\n[Análisis de rendimiento - Shift-And]\n");
    printf("Ocurrencias: %d\n", count);
    printf("Comparaciones: %d\n", comparaciones);
    printf("Accesos a memoria: %d\n", accesos);
    printf("Tiempo de ejecución: %.3f ms\n\n", tiempo_ms);

    FILE *csv = fopen("resultados_shiftand.csv", "a");
    if (!csv) {
        perror("No se pudo abrir resultados_shiftand.csv");
        return count;
    }

    fseek(csv, 0, SEEK_END);
    if (ftell(csv) == 0) {
        fprintf(csv, "algoritmo,archivo,patron,comparaciones,accesos_memoria,tiempo_ms\n");
    }

    fprintf(csv, "shiftand,%s,%s,%d,%d,%.3f\n", filename, pattern, comparaciones, accesos, tiempo_ms);
    fclose(csv);

    return count;
}
//*