#include "hash.h"
#include "libs.h"

Node *tablaHash[SIZE] = {0};

int hash(char *word)
{
    int hash = 0;
    for (int i = 0; word[i]; i++)
    {
        hash = (hash * 31 + word[i]) % SIZE;
    }
    return hash;
}

void insert(char *word)
{
    int h = hash(word);
    Node *temp = tablaHash[h];
    while (temp)
    {
        if (strcmp(temp->word, word) == 0)
        {
            temp->frequency++;
            return;
        }
        temp = temp->next;
    }

    Node *new = malloc(sizeof(Node));
    strcpy(new->word, word);
    new->frequency = 1;
    new->next = tablaHash[h];
    tablaHash[h] = new;
}
void printf_hash_table()
{
    printf(BLUE "+--------------------------+------------+\n" RESET);
    printf(BLUE "| Palabra                  | Frecuencia |\n" RESET);
    printf(BLUE "+--------------------------+------------+\n" RESET);

    for (int i = 0; i < SIZE; i++)
    {
        Node *temp = tablaHash[i];
        while (temp)
        {
            printf("| " YELLOW "%-24s" RESET " | " CYAN "%10d" RESET " |\n", temp->word, temp->frequency);
            temp = temp->next;
        }
    }

    printf(BLUE "+--------------------------+------------+\n" RESET);
}

void build_hash_table(char *texto)
{
    char *delimiters = " \n\t.,;:!?\"()[]{}<>-";
    char *copy_text = strdup(texto);

    if (!copy_text)
    {
        perror("strdup failed");
        return;
    }

    char *word = strtok(copy_text, delimiters);
    while (word != NULL)
    {
        insert(word);
        word = strtok(NULL, delimiters);
    }

    free(copy_text);
}

int word_frequency(const char *word_to_search)
{
    int h = hash((char *)word_to_search);
    Node *temp = tablaHash[h];

    while (temp)
    {
        if (strcmp(temp->word, word_to_search) == 0)
        {
            return temp->frequency;
        }
        temp = temp->next;
    }

    return 0;
}

int is_in_text(const char *word_to_search)
{
    int h = hash((char *)word_to_search);
    Node *temp = tablaHash[h];

    while (temp)
    {
        if (strcmp(temp->word, word_to_search) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return -1;
}

void clear_hash_table()
{
    for (int i = 0; i < SIZE; i++)
    {
        Node *temp = tablaHash[i];
        while (temp)
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
        tablaHash[i] = NULL;
    }
}

void printf_top_from_hash_table()
{
    Node *nodos[1000];
    int count = 0;
    int limit = 10;

    for (int i = 0; i < SIZE; i++)
    {
        Node *temp = tablaHash[i];
        while (temp && count < 1000)
        {
            nodos[count++] = temp;
            temp = temp->next;
        }
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (nodos[j]->frequency > nodos[i]->frequency)
            {
                Node *tmp = nodos[i];
                nodos[i] = nodos[j];
                nodos[j] = tmp;
            }
        }
    }

    printf(BLUE "+--------------------------+------------+\n" RESET);
    printf(BLUE "| " YELLOW "Top Palabras Clave            " BLUE "         |\n" RESET, limit);
    printf(BLUE "+--------------------------+------------+\n" RESET);
    printf(BLUE "| Palabra                  | Frecuencia |\n" RESET);
    printf(BLUE "+--------------------------+------------+\n" RESET);

    int printed = 0;
    int i = 0;

    while (printed < limit && i < count)
    {
        if (nodos[i]->frequency > 2)
        {
            printf("| " YELLOW "%-24s" RESET " | " CYAN "%10d" RESET " |\n", nodos[i]->word, nodos[i]->frequency);
            printed++;
        }
        i++;
    }

    if (printed == 0)
    {
        printf("| " RED "%-24s" RESET " | " RED "%10s" RESET " |\n", "No hay palabras con freq > 2", "");
    }

    printf(BLUE "+--------------------------+------------+\n" RESET);
}
//*