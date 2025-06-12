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
#include "ranking.h"

static void ensure_index(const char *ruta_txt, const char *contenido)
{
    char ruta_idx[PATH_MAX];
    snprintf(ruta_idx, sizeof(ruta_idx), "%s.idx", ruta_txt);

    if (!load_inverted_index(ruta_idx))
    {
        build_inverted_index(contenido);
        save_inverted_index(ruta_idx);
    }
}

int main(int argc, char *argv[])
{
    int opt;
    char *file = NULL;
    char *word_to_search = NULL;
    char *word_to_search_proximity = NULL;
    char *word_to_search_ranking = NULL;
    int use_kmp = 0;
    int use_bm = 0;
    int shift_and = 0;
    int compare = 0;
    int detect = 0;
    int proximity = 0;
    int ranking = 0;
    int index = 0;
    int tolerance;
    char *pattern = NULL;
    char *word = NULL;
    char *file_compare_1 = NULL;
    char *file_compare_2 = NULL;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"in", required_argument, 0, 'i'},
        {"kmp", no_argument, 0, 1},
        {"bm", no_argument, 0, 2},
        {"shift_and", no_argument, 0, 3},
        {"word", required_argument, 0, 4},
        {"pattern", required_argument, 0, 5},
        {"compare", required_argument, 0, 6},
        {"detect", no_argument, 0, 7},
        {"proximity", required_argument, 0, 8},
        {"tolerance", required_argument, 0, 9},
        {"index", no_argument, 0, 10},
        {"ranking", required_argument, 0, 11},

        {0, 0, 0, 0}};

    int long_index = 0;

    while ((opt = getopt_long(argc, argv, "f:vh:", long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'f':
            file = optarg;
            break;
        case 'h':
            print_help();
            return 0;
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
            shift_and = 1;
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
        case 11:
            ranking = 1;
            word_to_search_ranking = optarg;
            break;

        default:
            fprintf(stderr, "Uso: %s -f <file> [-kmp | -bm | -algoritmo3]\n", argv[0]);
            return 1;
        }
    }

    char *content = load(file);

    if (word_to_search)
    {
        normalize_text(word_to_search);

        // Usamos índice persistente
        ensure_index(file, content);

        if (word_in_index(word_to_search))
            printf(GREEN "✔ La palabra \"%s\" " RESET "SI " GREEN "está " RESET "en el texto " CYAN "%s" RESET ".\n",
                   word_to_search, file);
        else
            printf(RED "✘ La palabra \"%s\" " RESET "NO está en el texto " CYAN "%s" RESET ".\n",
                   word_to_search, file);
    }

    if ((use_kmp || use_bm || shift_and) && (pattern == NULL && word == NULL))
    {
        fprintf(stderr, "Debes especificar el patrón o palabra a buscar.");
        return 1;
    }

    if (use_kmp)
    {
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
    }

    else if (use_bm)
    {
        fprintf(stdout, "Ejecutando búsqueda con Boyer-Moore...\n");
        int ocurrencias = boyer_moore_bad_char(content, pattern, file);
        printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, ocurrencias);
    }

    else if (shift_and)
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
            fprintf(stderr, RED "[ERROR]" RESET " No se pudo cargar uno de los archivos para comparación.\n");
            return 1;
        }

        clean_html(content1);
        clean_html(content2);

        ListaTokens tokens1 = tokenizar_texto(content1);
        ListaTokens tokens2 = tokenizar_texto(content2);

        float similitud = calculate_similarity(tokens1, tokens2);
        printf(CYAN "\n╔══════════════════════════════════════════════╗\n");
        printf("║         RESULTADO DE COMPARACIÓN             ║\n");
        printf("╚══════════════════════════════════════════════╝\n" RESET);

        printf(BLUE "Archivo 1:" RESET " %s\n", file_compare_1);
        printf(BLUE "Archivo 2:" RESET " %s\n", file_compare_2);

        printf(GREEN "\nSimilitud calculada: " RESET "%.2f%%\n", similitud * 100);

        if (similitud > 0.5)
        {
            printf(YELLOW "▶ Resultado:" RESET " Los textos son " GREEN "bastante similares.\n" RESET);
        }
        else
        {
            printf(YELLOW "▶ Resultado:" RESET " Los textos " RED "no son tan similares.\n" RESET);
        }

        liberar_tokens(tokens1);
        liberar_tokens(tokens2);
        free(content1);
        free(content2);
    }

    if (detect)
    {
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

    if (ranking)
    {
        int file_number = 0;
        char **archivos = list_valid_files("docs", &file_number);

        normalize_text(word_to_search_ranking);
        search_in_docs(word_to_search_ranking, archivos, file_number);

        for (int i = 0; i < file_number; i++)
            free(archivos[i]);
        free(archivos);
    }

    free(content);
    return 0;
}
