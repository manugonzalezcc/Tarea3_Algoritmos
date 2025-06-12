#include "inverted_index.h"

IndexNode *invertedIndex[SIZE_IDX] = {0};

int hash_index(char *word)
{
    int hash = 0;
    for (int i = 0; word[i]; i++)
    {
        hash = (hash * 31 + word[i]) % SIZE_IDX;
    }
    return hash;
}

void add_to_index(const char *word, int position)
{
    int h = hash_index((char *)word);
    IndexNode *actual = invertedIndex[h];
    while (actual)
    {
        if (strcmp(actual->word, word) == 0)
        {
            if (actual->quantity == actual->capacity)
            {
                actual->capacity *= 2;
                actual->positions = realloc(actual->positions, actual->capacity * sizeof(int));
            }
            actual->positions[actual->quantity++] = position;
            return;
        }
        actual = actual->next;
    }

    IndexNode *new = malloc(sizeof(IndexNode));
    strcpy(new->word, word);
    new->capacity = 4;
    new->positions = malloc(new->capacity * sizeof(int));
    new->positions[0] = position;
    new->quantity = 1;
    new->next = invertedIndex[h];
    invertedIndex[h] = new;
}

void print_index()
{
    printf(CYAN "\n╔══════════════════════════════╦══════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" RESET "      " YELLOW "PALABRA" RESET "                 " CYAN "║" RESET "          " YELLOW "POSICIONES" RESET "                      " CYAN "║\n" RESET);
    printf(CYAN "╠══════════════════════════════╬══════════════════════════════════════╣\n" RESET);

    for (int i = 0; i < SIZE_IDX; i++)
    {
        IndexNode *node = invertedIndex[i];
        while (node != NULL)
        {
            printf(CYAN "║ " RESET BLUE "%-28s" RESET CYAN " ║ " RESET GREEN, node->word);
            for (int j = 0; j < node->quantity; j++)
            {
                printf("%d", node->positions[j]);
                if (j != node->quantity - 1)
                    printf(", ");
            }
            printf(RESET CYAN " ║\n" RESET);
            node = node->next;
        }
    }

    printf(CYAN "╚══════════════════════════════╩══════════════════════════════════════╝\n\n" RESET);
    printf("\033[1;32m✔ Persistencia en disco:\033[0m índice generado exitosamente en \033[1;34m\"docs/<archivo>.idx\"\033[0m\n");
}

void build_index(const char *content)
{
    char word[100];
    int pos = 0;

    for (int i = 0; content[i];)
    {
        int j = 0;

        while (content[i] && (isalpha(content[i]) || content[i] == '_'))
        {
            word[j++] = tolower(content[i++]);
        }

        if (j > 0)
        {
            word[j] = '\0';
            pos++;
            add_to_index(word, pos);
        }

        while (content[i] && !isalpha(content[i]) && content[i] != '_')
        {
            i++;
        }
    }
}

void clear_inverted_index(void)
{
    for (int i = 0; i < SIZE_IDX; i++)
    {
        IndexNode *cur = invertedIndex[i];
        while (cur)
        {
            IndexNode *next = cur->next;
            free(cur->positions);
            free(cur);
            cur = next;
        }
        invertedIndex[i] = NULL;
    }
}

int word_in_index(const char *word)
{
    int h = hash_index((char *)word);
    IndexNode *cur = invertedIndex[h];
    while (cur)
    {
        if (strcmp(cur->word, word) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

void build_inverted_index(const char *texto)
{
    clear_inverted_index();
    const char *delims = " \t\n\r.,;:!?\"()[]{}<>|\\/";
    char *copia = strdup(texto);
    char *token = strtok(copia, delims);
    int offset = 0;

    while (token)
    {
        add_to_index(token, offset);
        offset++;
        token = strtok(NULL, delims);
    }
    free(copia);
}

void save_inverted_index(const char *ruta_idx)
{
    FILE *out = fopen(ruta_idx, "w");
    if (!out)
    {
        perror("save_inverted_index");
        return;
    }

    for (int i = 0; i < SIZE_IDX; i++)
    {
        IndexNode *cur = invertedIndex[i];
        while (cur)
        {
            fprintf(out, "%s", cur->word);
            for (int j = 0; j < cur->quantity; j++)
                fprintf(out, " %d", cur->positions[j]);
            fputc('\n', out);
            cur = cur->next;
        }
    }
    fclose(out);
}

int load_inverted_index(const char *ruta_idx)
{
    FILE *in = fopen(ruta_idx, "r");
    if (!in)
        return 0;

    clear_inverted_index();

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, in) != -1)
    {
        if (line[0] == '\n')
            continue;
        char *pal = strtok(line, " \n");
        int pos;
        while ((pal) && (sscanf(pal, "%d", &pos) != 1))
        {
            break;
        }
        char word[100];
        strcpy(word, pal);

        char *num = strtok(NULL, " \n");
        while (num)
        {
            sscanf(num, "%d", &pos);
            add_to_index(word, pos);
            num = strtok(NULL, " \n");
        }
    }
    free(line);
    fclose(in);
    return 1;
}
