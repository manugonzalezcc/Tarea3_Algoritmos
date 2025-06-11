#ifndef HASH_H
#define HASH_H
#include "libs.h"

#define SIZE 1000

typedef struct nodo
{
    char word[100];
    int frequency;
    struct nodo *next;
} Node;

extern Node *tablaHash[SIZE];

int hash(char *palabra);
void insert(char *palabra);
void printf_hash_table(void);
void build_hash_table(char *texto);
int word_frequency(const char *palabra_buscada);
int is_in_text(const char *word_to_search);
void clear_hash_table();
void printf_top_from_hash_table(void);

#endif
