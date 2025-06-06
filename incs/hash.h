#ifndef HASH_H
#define HASH_H
#include "libs.h"

#define SIZE 1000

typedef struct nodo
{
    char word[100];
    int frequency;
    struct node *next;
} Node;

Node *tablaHash[SIZE];

int hash(char *palabra);
void insert(char *palabra);
void printf_hash_table(void);
void build_hash_table(char *texto);
int word_frequency(const char *palabra_buscada);

#endif
