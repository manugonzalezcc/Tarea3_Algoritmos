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
#include "similarity.h"
#include "levenshtein.h"

int main(int argc, char *argv[])
{
    int opt;
    char *file = NULL;
    int verbose = 0;
    char *word_to_search = NULL;
    char *word_to_search_proximity = NULL;
    int use_kmp = 0;
    int use_bm = 0;
    int use_algoritmo3 = 0;
    int compare = 0;
    int detect = 0;
    int proximity = 0;
    int index = 0;
    int tolerance;
    int top = 0;
    char *pattern = NULL;
    char *word = NULL;
    char *file_compare_1 = NULL;
    char *file_compare_2 = NULL;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"in", required_argument, 0, 'i'},
        {"kmp", no_argument, 0, 1},
        {"bm", no_argument, 0, 2},
        {"algoritmo3", no_argument, 0, 3},
        {"word", required_argument, 0, 4},
        {"pattern", required_argument, 0, 5},
        {"compare", required_argument, 0, 6},
        {"detect", no_argument, 0, 7},
        {"proximity", required_argument, 0, 8},
        {"tolerance", required_argument, 0, 9},
        {"index", no_argument, 0, 10},

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
            // consulta = optarg;
            break;
        case 'i':
            word_to_search = optarg;
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
            word = optarg;
            break;
        case 5:
            pattern = optarg;
            break;
        case 6:
            compare = 1;
            file_compare_1 = optarg;
            file_compare_2 = argv[optind];
            break;
        case 7:
            detect = 1;
            break;
        case 8:
            proximity = 1;
            word_to_search_proximity = optarg;
            break;
        case 9:
            tolerance = atoi(optarg);
            break;
        case 10:
            index = 1;
            break;

        default:
            fprintf(stderr, "Uso: %s -f <file> [-kmp | -bm | -algoritmo3]\n", argv[0]);
            return 1;
        }
    }

    char *content = load(file);

    if (word_to_search)
    {
        void build_hash_table(char *text);
        int is_in_text(const char *word_to_search);

        normalize_text(word_to_search);
        build_hash_table(content);

        int answer = is_in_text(word_to_search);

        if (answer == -1)
            printf(RED "✘ La palabra \"%s\" " RESET "NO está en el texto " CYAN "%s" RESET ".\n", word_to_search, file);
        else
            printf(GREEN "✔ La palabra \"%s\" " RESET "SI " GREEN "está " RESET "en el texto " CYAN "%s" RESET ".\n", word_to_search, file);
    }
    if (!file)
    {
        perror("No se pudo abrir el archivo!");
    }

    if ((use_kmp || use_bm || use_algoritmo3) && (pattern || word) == NULL)
    {
        fprintf(stderr, "Debes especificar el patrón o palabra a buscar.");
        return 1;
    }
    if (use_kmp)
    {
        void build_hash_table(char *text);
        void printf_hash_table(void);
        int word_frequency(const char *word_to_search);
        int occurrences = 0;

        fprintf(stdout, "Ejecutando búsqueda con KMP...\n");

        if (pattern)
            normalize_text(pattern);
        else
            normalize_text(word);

        if (pattern)
        {
            int count = kmp_search(content, pattern);
            printf("El patrón '%s' aparece %d veces en el texto (por KMP).\n", pattern, count);
        }
        else
        {
            stopwords(content, "stopwords-es.txt");
            build_hash_table(content);
            occurrences = word_frequency(word);
            kmp_search(content, word);
            printf("La palabra '%s' aparece %d veces en el texto.\n", word, occurrences);
        }

        // esto puede ser una opcion extra para mostrar la tabla hash construida
        // stopwords(content, "stopwords-es.txt");
        // build_hash_table(content);

        // printf("Tabla hash con frecuencia de palabras:\n");
        // printf_hash_table();
    }
    else if (use_bm)
    {
        fprintf(stdout, "Ejecutando búsqueda con Boyer-Moore...\n");
        int ocurrencias = boyer_moore_bad_char(content, pattern, file);
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

        int ocurrencias = shift_and_search(content, pattern, file);
        printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);
    }
    if (compare)
    {
        char *content1 = load(file_compare_1);
        char *content2 = load(file_compare_2);

        if (!content1 || !content2)
        {
            fprintf(stderr, "Error al cargar uno de los archivos para comparación.\n");
            return 1;
        }

        clean_html(content1);
        clean_html(content2);

        ListaTokens tokens1 = tokenizar_texto(content1);
        ListaTokens tokens2 = tokenizar_texto(content2);

        float similitud = calculate_similarity(tokens1, tokens2);
        printf("Similitud: %.2f\n", similitud);

        if (similitud > 0.5)
        {
            printf("Los textos son bastante similares.\n");
        }
        else
        {
            printf("Los textos no son tan similares.\n");
        }

        liberar_tokens(tokens1);
        liberar_tokens(tokens2);
        free(content1);
        free(content2);
    }
    if (detect)
    {
        void printf_top_from_hash_table();

        stopwords(content, "stopwords-es.txt");
        build_hash_table(content);
        printf_top_from_hash_table();
    }
    if (proximity)
    {
        normalize_text(word_to_search_proximity);
        buscar_palabras_similares(content, word_to_search_proximity, tolerance);
    }
    if (index)
    {
        stopwords(content, "stopwords-es.txt");
        construir_indice(content);
        printf(CYAN "\n[ Índice de palabras ]\n" RESET);
        imprimir_indice();
    }

    free(content);
    return 0;
}
