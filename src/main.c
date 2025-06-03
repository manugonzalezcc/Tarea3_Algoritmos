#include "libs.h"
#include "tokenizer.h"
#include "search.h"
#include "help.h"
#include "boyer_moore.h"
#include "load.h"
#include "kmp.h"
#include "hash.h"

int main(int argc, char *argv[])
{
    int opt;
    char *file = NULL;

    int use_kmp = 0;
    int use_bm = 0;
    int use_algoritmo3 = 0;
    char *pattern = NULL;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"kmp", no_argument, 0, 1},
        {"bm", no_argument, 0, 2},
        {"algoritmo3", no_argument, 0, 3},
        {"pattern", required_argument, 0, 4},
        {0, 0, 0, 0}};

    int long_index = 0;

    while ((opt = getopt_long(argc, argv, "f:vh", long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'f':
            file = optarg;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 1:
            use_kmp = 1;
            break;
        case 2:
            use_bm = 1;
            break;
        case 3:
            use_algoritmo3 = 1;
            break;
        case 4:
            pattern = optarg;
            break;

        default:
            fprintf(stderr, "Uso: %s -f <file> [-kmp | -bm | -algoritmo3]\n", argv[0]);
            return 1;
        }
    }

    if (file == NULL)
    {
        fprintf(stderr, "El parámetro -f file es obligatorio\n");
        return 1;
    }

    if (!use_kmp && !use_bm && !use_algoritmo3)
    {
        fprintf(stderr, "Debes especificar uno de: --kmp, --bm, --algoritmo3\n");
        return 1;
    }

    if ((use_kmp || use_bm) && pattern == NULL)
    {
        fprintf(stderr, "Debes especificar un patrón con --pattern \"palabra\"\n");
        return 1;
    }

    if (use_kmp)
    {
        void build_hash_table(char *text);
        void printf_hash_table(void);
        int word_frequency(const char *word_to_searcj);

        fprintf(stdout, "Ejecutando búsqueda con KMP...\n");

        char *text = load(file);
        if (!text)
        {
            fprintf(stderr, "Error al cargar el archivo.\n");
            return 1;
        }

        printf("Contenido del archivo (normalizado):\n%s\n", text);

        build_hash_table(text);

        normalize_text(pattern);

        printf("Tabla hash con frecuencia de palabras:\n");
        printf_hash_table();

        int ocurrencias = word_frequency(pattern);
        kmp_search(text, pattern);

        printf("La palabara '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);

        free(text);
    }

    else if (use_bm)
    {
        const char *text = "este es un texto de prueba, texto de ejemplo";
        const char *patron = "texto";
        int ocurrencias = boyer_moore_bad_char(text, patron);
        printf("Boyer-Moore: El patrón '%s' aparece %d veces en el texto.\n", patron, ocurrencias);
    }
    else if (use_algoritmo3)
    {
        printf("Ejecutando búsqueda con algoritmo3...\n");
    }

    return 0;
}
