#include "help.h"
#include "load.h"
#include "inverted_index.h"
#include "auxiliar.h"

// -------------------- FUNCIÓN PRINCIPAL --------------------
int main(int argc, char *argv[])
{
    int opt, long_index = 0;
    char *file = NULL, *word_to_search = NULL, *word_prox = NULL, *word_ranking = NULL;
    char *pattern = NULL, *word = NULL, *file1 = NULL, *file2 = NULL;
    int use_kmp = 0, use_bm = 0, use_shift = 0, compare = 0, detect = 0;
    int proximity = 0, ranking = 0, index = 0, joke = 0, tolerance = 0;

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
        {"joke", no_argument, 0, 12},
        {0, 0, 0, 0}};

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
            use_shift = 1;
            break;
        case 4:
            word = optarg;
            break;
        case 5:
            pattern = optarg;
            break;
        case 6:
            compare = 1;
            file1 = optarg;
            file2 = argv[optind];
            break;
        case 7:
            detect = 1;
            break;
        case 8:
            proximity = 1;
            word_prox = optarg;
            break;
        case 9:
            tolerance = atoi(optarg);
            break;
        case 10:
            index = 1;
            break;
        case 11:
            ranking = 1;
            word_ranking = optarg;
            break;
        case 12:
            joke = 1;
            break;
        default:
            fprintf(stderr, "Uso: ./run.sh + opciones\n");
            return 1;
        }
    }

    int need_file = word_to_search || use_kmp || use_bm || use_shift || detect || proximity || index;
    char *content = NULL;

    if (need_file)
    {
        if (!valid_file(file))
            return 1;
        content = load(file);
    }

    if (word_to_search)
    {
        normalize_text(word_to_search);
        ensure_index(file, content);

        if (word_in_index(word_to_search))
            printf(GREEN "✔ La palabra \"%s\" " RESET "SI " GREEN "está " RESET "en el texto " CYAN "%s" RESET ".\n", word_to_search, file);
        else
            printf(RED "✘ La palabra \"%s\" " RESET "NO está en el texto " CYAN "%s" RESET ".\n", word_to_search, file);
    }

    if ((use_kmp || use_bm || use_shift) && (!pattern && !word))
    {
        fprintf(stderr, "Debes especificar el patrón o palabra a buscar.\n");
        return 1;
    }

    if (use_kmp)
        exec_kmp(content, pattern, word);
    else if (use_bm)
        exec_boyer_moore(content, pattern, file);
    else if (use_shift && !exec_shift_and(content, pattern, file))
        return 1;

    if (compare)
        exec_comparate(file1, file2);
    if (detect)
        count_top_words(content);
    if (proximity)
        exec_proximity(content, word_prox, tolerance);
    if (index)
        build_and_show_index(content);
    if (ranking)
        exec_ranking(word_ranking);
    if (joke)
        tell_joke();

    free(content);
    return 0;
}
//*