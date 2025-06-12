#include "libs.h"
#include "aux.h"
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

// -------------------- UTILIDADES --------------------
void ensure_index(const char *route_txt, const char *content)
{
    char ruta_idx[PATH_MAX];
    snprintf(ruta_idx, sizeof(ruta_idx), "%s.idx", route_txt);

    if (!load_inverted_index(ruta_idx))
    {
        build_inverted_index(content);
        save_inverted_index(ruta_idx);
    }
}

int valid_file(const char *file)
{
    if (!file)
    {
        fprintf(stderr, RED "\n❌ Debes especificar un archivo usando la opción --file.\n" RESET);
        return 0;
    }
    if (!file_exists(file))
    {
        fprintf(stderr, RED "\n❌ Archivo no encontrado: " RESET "%s\n", file);
        fprintf(stderr, YELLOW "📁 Usa una ruta relativa como: " RESET "docs/doc1.html\n");
        return 0;
    }
    return 1;
}

// -------------------- FUNCIONES DE OPERACIONES --------------------
void exec_kmp(char *content, const char *pattern, const char *word)
{
    fprintf(stdout, "Ejecutando búsqueda con KMP...\n");
    if (pattern)
        normalize_text((char *)pattern);
    if (word)
        normalize_text((char *)word);

    if (pattern)
    {
        int count = kmp_search(content, pattern);
        printf("El patrón '%s' aparece %d veces en el texto (por KMP).\n", pattern, count);
    }
    else
    {
        stopwords(content, "stopwords-es.txt");
        build_hash_table(content);
        int occurrences = word_frequency(word);
        kmp_search(content, word);
        printf("La palabra '%s' aparece %d veces en el texto.\n", word, occurrences);
    }
}

void exec_boyer_moore(char *content, const char *pattern, const char *file)
{
    fprintf(stdout, "Ejecutando búsqueda con Boyer-Moore...\n");
    normalize_text(content);
    normalize_text((char *)pattern);
    int occurrences = boyer_moore_bad_char(content, pattern, file);
    printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, occurrences);
}

int exec_shift_and(char *content, const char *pattern, const char *file)
{
    fprintf(stdout, "Ejecutando búsqueda con Shift-And...\n");
    if (strlen(pattern) > 31)
    {
        fprintf(stderr, "Shift-And solo soporta patrones de hasta 31 caracteres.\n");
        return 0;
    }
    normalize_text(content);
    normalize_text((char *)pattern);
    int occurrences = shift_and_search(content, pattern, file);
    printf("La palabra '%s' aparece %d veces en el texto.\n", pattern, occurrences);
    return 1;
}

void exec_comparate(const char *file1, const char *file2)
{
    char *content1 = load(file1);
    char *content2 = load(file2);

    if (!content1 || !content2)
    {
        fprintf(stderr, RED "[ERROR]" RESET " No se pudo cargar uno de los archivos para comparación.\n");
        return;
    }

    clean_html(content1);
    clean_html(content2);

    TokenList tokens1 = tokenize_text(content1);
    TokenList tokens2 = tokenize_text(content2);

    float similarity = calculate_similarity(tokens1, tokens2);

    printf(CYAN "\n╔══════════════════════════════════════════════╗\n");
    printf("║         RESULTADO DE COMPARACIÓN             ║\n");
    printf("╚══════════════════════════════════════════════╝\n" RESET);
    printf(BLUE "Archivo 1:" RESET " %s\n", file1);
    printf(BLUE "Archivo 2:" RESET " %s\n", file2);
    printf(GREEN "\nSimilitud calculada: " RESET "%.2f%%\n", similarity * 100);

    if (similarity > 0.5)
    {
        printf(YELLOW "▶ Resultado:" RESET " Los textos son " GREEN "bastante similares.\n" RESET);
    }
    else
    {
        printf(YELLOW "▶ Resultado:" RESET " Los textos " RED "no son tan similares.\n" RESET);
    }

    free_tokens(tokens1);
    free_tokens(tokens2);
    free(content1);
    free(content2);
}

void count_top_words(char *content)
{
    stopwords(content, "stopwords-es.txt");
    build_hash_table(content);
    printf_top_from_hash_table();
}

void exec_proximity(char *content, const char *word, int tolerance)
{
    normalize_text((char *)word);
    search_similar_words(content, word, tolerance);
}

void build_and_show_index(char *content)
{
    stopwords(content, "stopwords-es.txt");
    build_index(content);
    printf(CYAN "\n[ Índice de palabras ]\n" RESET);
    print_index();
}

void exec_ranking(const char *word)
{
    int file_number = 0;
    char **archivos = list_valid_files("docs", &file_number);
    normalize_text((char *)word);
    search_in_docs(word, archivos, file_number);

    for (int i = 0; i < file_number; i++)
        free(archivos[i]);
    free(archivos);
}

void tell_joke()
{
    printf(YELLOW "╭────────────────────────────────────────────╮   ╭────────────────────────────────────────────────╮\n");
    printf(YELLOW "│  (・・ )                                   │   │  (╯︵╰,)                                       │\n");
    printf(YELLOW "│  ¿Por qué el algoritmo de búsqueda         │   │  Porque no podía encontrar su mitad.           │\n");
    printf(YELLOW "│  binaria fue a terapia?                    │   │                                                │\n");
    printf(YELLOW "╰────────────────────────────────────────────╯   ╰────────────────────────────────────────────────╯\n");
}