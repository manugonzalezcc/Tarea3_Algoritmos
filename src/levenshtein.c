#include "libs.h"
#include "inverted_index.h"

int min(int a, int b, int c)
{
    if (a < b && a < c)
        return a;
    if (b < c)
        return b;
    return c;
}

int levenshtein(const char *s1, const char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int matriz[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++)
        matriz[i][0] = i;
    for (int j = 0; j <= len2; j++)
        matriz[0][j] = j;

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            int costo = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            matriz[i][j] = min(
                matriz[i - 1][j] + 1,
                matriz[i][j - 1] + 1,
                matriz[i - 1][j - 1] + costo);
        }
    }

    return matriz[len1][len2];
}

void search_similar_words(const char *text, const char *query, int tolerance)
{
    printf("tolerancia %d", tolerance);
    char word[256];
    int pos = 0;
    int index_palabra = 0;
    int total_encontradas = 0;

    printf(MAGENTA "+----------------------+----------------------+-----------+\n" RESET);
    printf(MAGENTA "| Palabra encontrada    | Palabra consulta      | Posición  |\n" RESET);
    printf(MAGENTA "+----------------------+----------------------+-----------+\n" RESET);

    for (int i = 0;; i++)
    {
        char c = text[i];
        if (c == '\0' || isspace(c))
        {
            if (pos > 0)
            {
                word[pos] = '\0';
                if (levenshtein(word, query) <= tolerance)
                {
                    total_encontradas++;
                    printf("| " GREEN "%-20s " RESET "| " YELLOW "%-20s " RESET "| " CYAN "%-9d " RESET "|\n", word, query, index_palabra);
                }
                pos = 0;
            }
            if (c == '\0')
                break;
            index_palabra = i + 1;
        }
        else
        {
            if (pos == 0)
                index_palabra = i;
            if (pos < 255)
                word[pos++] = tolower(c);
        }
    }

    printf(MAGENTA "+----------------------+----------------------+-----------+\n" RESET);

    if (total_encontradas == 0)
    {
        printf(ORANGE "No se encontraron palabras similares a \"%s\" con tolerancia %d.\n" RESET, query, tolerance);
    }
    else
    {
        printf(BLUE "Total de palabras similares encontradas: %d\n" RESET, total_encontradas);
    }
}
//*