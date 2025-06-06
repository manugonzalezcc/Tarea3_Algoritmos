#include "libs.h"
#include "tokenizer.h"
#include "search.h"
#include "help.h"
#include "boyer_moore.h"
#include "shift_and.h"
#include "load.h"
#include "inverted_index.h"
#include "kmp.h"
#include "hash.h"

int main(int argc, char *argv[])
{
    int opt;
    char *file = NULL;
    int verbose = 0;
    char *consulta = NULL;
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

    while ((opt = getopt_long(argc, argv, "f:vhq:", long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'f':
            file = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'q':
            consulta = optarg;
            break;
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
        fprintf(stderr, "El parámetro -f <file> es obligatorio.\n");
        return 1;
    }

    if (!use_kmp && !use_bm && !use_algoritmo3)
    {
        fprintf(stderr, "Debes especificar uno de: --kmp, --bm, --algoritmo3\n");
        return 1;
    }

    char *contenido = load(file);
    if (!contenido)
    {
        fprintf(stderr, "Error al cargar el archivo.\n");
        return 1;
    }

    clean_html(contenido);
    ListaTokens tokens = tokenizar_texto(contenido);

    for (int i = 0; i < tokens.cantidad; i++)
    {
        agregar_al_indice(tokens.tokens[i], i);
    }

    if (verbose)
    {
        printf("\nÍndice invertido:\n");
        imprimir_indice();
    }

    if (consulta != NULL)
    {
        for (int i = 0; consulta[i]; i++)
        {
            consulta[i] = tolower(consulta[i]);
        }

        printf("\nConsulta: '%s'\n", consulta);
        int h = hash_indice(consulta);
        NodoIndice *nodo = indiceInvertido[h];
        int encontrado = 0;

        while (nodo)
        {
            if (strcmp(nodo->palabra, consulta) == 0)
            {
                printf("La palabra '%s' aparece en las posiciones: ", consulta);
                for (int i = 0; i < nodo->cantidad; i++)
                {
                    printf("%d ", nodo->posiciones[i]);
                }
                printf("\n");
                encontrado = 1;
                break;
            }
            nodo = nodo->siguiente;
        }

        if (!encontrado)
        {
            printf("La palabra '%s' no fue encontrada en el índice.\n", consulta);
        }
    }

    if ((use_kmp || use_bm || use_algoritmo3) && pattern == NULL)
    {
        fprintf(stderr, "Debes especificar un patrón con --pattern \"palabra\"\n");
        return 1;
    }

    if (use_kmp)
    {
        void build_hash_table(char *text);
        void printf_hash_table(void);
        int word_frequency(const char *word_to_search);

        fprintf(stdout, "Ejecutando búsqueda con KMP...\n");

        normalize_text(pattern);
        build_hash_table(contenido);

        printf("Tabla hash con frecuencia de palabras:\n");
        printf_hash_table();

        int ocurrencias = word_frequency(pattern);
        kmp_search(contenido, pattern);

        printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);
    }
    else if (use_bm)
    {
        fprintf(stdout, "Ejecutando búsqueda con Boyer-Moore...\n");
        int ocurrencias = boyer_moore_bad_char(contenido, pattern, file);
        printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);
    }
    else if (use_algoritmo3)
    {
        fprintf(stdout, "Ejecutando búsqueda con Shift-And...\n");

        if (strlen(pattern) > 31)
        {
            fprintf(stderr, "Shift-And solo soporta patrones de hasta 31 caracteres.\n");
            return 1;
        }

        int ocurrencias = shift_and_search(contenido, pattern, file);
        printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);
    }

    liberar_tokens(tokens);
    free(contenido);
    return 0;
}
