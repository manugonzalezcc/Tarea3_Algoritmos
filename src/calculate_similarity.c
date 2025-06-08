#include "libs.h"
#include "similarity.h"
#include "hash.h"

float calculate_similarity(ListaTokens a, ListaTokens b)
{
    clear_hash_table();

    int unique_total = 0;
    int commons = 0;

    for (int i = 0; i < a.cantidad; i++)
    {
        int h = hash(a.tokens[i]);
        Node *temp = tablaHash[h];
        int repetido = 0;
        while (temp)
        {
            if (strcmp(temp->word, a.tokens[i]) == 0)
            {
                repetido = 1;
                break;
            }
            temp = temp->next;
        }
        if (!repetido)
        {
            insert(a.tokens[i]);
            unique_total++;
        }
    }

    for (int i = 0; i < b.cantidad; i++)
    {
        if (is_in_text(b.tokens[i]) == 1)
        {
            commons++;
        }
        else
        {
            insert(b.tokens[i]);
            unique_total++;
        }
    }

    if (unique_total == 0)
        return 0.0f;

    return (float)commons / (float)unique_total;
}