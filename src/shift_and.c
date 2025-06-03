#include "libs.h"
#include "shift_and.h"

int shift_and_search(const char *text, const char *pattern) {
    int m = strlen(pattern);
    if (m > 31) {
        fprintf(stderr, "El patrón es demasiado largo para Shift-And (máx 31 caracteres)\n");
        return -1;
    }

    unsigned int mask[256] = {0};
    for (int i = 0; i < m; i++) {
        mask[(unsigned char)pattern[i]] |= 1 << i;
    }

    unsigned int R = 0;
    unsigned int last_bit = 1 << (m - 1);
    int count = 0;

    for (int i = 0; text[i]; i++) {
        R = ((R << 1) | 1) & mask[(unsigned char)text[i]];
        if (R & last_bit) {
            count++;
        }
    }

    return count;
}
