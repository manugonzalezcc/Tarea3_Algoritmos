#include "libs.h"
#include "similarity.h"
#include "hash.h"

float calculate_similarity(TokenList a, TokenList b)
{
    clear_hash_table();

    if (a.quantity != b.quantity)
        goto continue_similarity;

    for (int i = 0; i < a.quantity; i++)
    {
        insert(a.tokens[i]);
    }

    for (int i = 0; i < b.quantity; i++)
    {
        if (!is_in_text(b.tokens[i]))
        {
            goto continue_similarity;
        }
    }

    return 1.0f;

continue_similarity:
    clear_hash_table();

    int unique_total = 0;
    int commons = 0;

    for (int i = 0; i < a.quantity; i++)
    {
        int h = hash(a.tokens[i]);
        Node *temp = tablaHash[h];
        int repeated = 0;
        while (temp)
        {
            if (strcmp(temp->word, a.tokens[i]) == 0)
            {
                repeated = 1;
                break;
            }
            temp = temp->next;
        }
        if (!repeated)
        {
            insert(a.tokens[i]);
            unique_total++;
        }
    }

    for (int i = 0; i < b.quantity; i++)
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
//*