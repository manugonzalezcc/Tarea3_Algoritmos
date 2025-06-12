#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
#include "libs.h"

typedef struct IndexNode
{
    char word[100];
    int *positions;
    int quantity;
    int capacity;
    struct IndexNode *next;
} IndexNode;

#define SIZE_IDX 1000
extern IndexNode *invertedIndex[SIZE_IDX];

int hash_index(char *word);
void add_to_index(const char *word, int position);
void print_index();
void build_index(const char *content);

void build_inverted_index(const char *text);
void save_inverted_index(const char *route_idx);
int load_inverted_index(const char *route_idx);
void clear_inverted_index(void);
int word_in_index(const char *word);

#endif
