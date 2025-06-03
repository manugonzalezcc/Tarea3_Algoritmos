#include "hash.h"
#include "libs.h"

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
    for (int i = 0; i < SIZE; i++)
    {
        Node *temp = tablaHash[i];
        while (temp)
        {
            printf("'%s' -> %d\n", temp->word, temp->frequency);
            temp = temp->next;
        }
    }
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
