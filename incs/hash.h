#ifndef HASH_H
#define HASH_H
#include "libs.h"

#define SIZE 1000

typedef struct nodo
{
    char palabra[100];
    int frecuencia;
    struct nodo *siguiente;
} Nodo;

Nodo *tablaHash[SIZE];

int hash(char *palabra);
void insertar(char *palabra);
void imprimirTabla();

#endif