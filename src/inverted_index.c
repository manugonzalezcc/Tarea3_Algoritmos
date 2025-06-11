#include "inverted_index.h"

NodoIndice *indiceInvertido[SIZE_IDX] = {0};

int hash_indice(char *palabra)
{
    int hash = 0;
    for (int i = 0; palabra[i]; i++)
    {
        hash = (hash * 31 + palabra[i]) % SIZE_IDX;
    }
    return hash;
}

void agregar_al_indice(const char *palabra, int posicion)
{
    int h = hash_indice((char *)palabra);
    NodoIndice *actual = indiceInvertido[h];
    while (actual)
    {
        if (strcmp(actual->palabra, palabra) == 0)
        {
            if (actual->cantidad == actual->capacidad)
            {
                actual->capacidad *= 2;
                actual->posiciones = realloc(actual->posiciones, actual->capacidad * sizeof(int));
            }
            actual->posiciones[actual->cantidad++] = posicion;
            return;
        }
        actual = actual->siguiente;
    }

    NodoIndice *nuevo = malloc(sizeof(NodoIndice));
    strcpy(nuevo->palabra, palabra);
    nuevo->capacidad = 4;
    nuevo->posiciones = malloc(nuevo->capacidad * sizeof(int));
    nuevo->posiciones[0] = posicion;
    nuevo->cantidad = 1;
    nuevo->siguiente = indiceInvertido[h];
    indiceInvertido[h] = nuevo;
}

void imprimir_indice()
{
    printf(CYAN "\n╔══════════════════════════════╦══════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" RESET "      " YELLOW "PALABRA" RESET "                 " CYAN "║" RESET "          " YELLOW "POSICIONES" RESET "                      " CYAN "║\n" RESET);
    printf(CYAN "╠══════════════════════════════╬══════════════════════════════════════╣\n" RESET);

    for (int i = 0; i < SIZE_IDX; i++)
    {
        NodoIndice *nodo = indiceInvertido[i];
        while (nodo != NULL)
        {
            printf(CYAN "║ " RESET BLUE "%-28s" RESET CYAN " ║ " RESET GREEN, nodo->palabra);
            for (int j = 0; j < nodo->cantidad; j++)
            {
                printf("%d", nodo->posiciones[j]);
                if (j != nodo->cantidad - 1)
                    printf(", ");
            }
            printf(RESET CYAN " ║\n" RESET);
            nodo = nodo->siguiente;
        }
    }

    printf(CYAN "╚══════════════════════════════╩══════════════════════════════════════╝\n\n" RESET);
    printf("\033[1;32m✔ Persistencia en disco:\033[0m índice generado exitosamente en \033[1;34m\"docs/<archivo>.idx\"\033[0m\n");
}

void construir_indice(const char *content)
{
    char palabra[100];
    int pos = 0;

    for (int i = 0; content[i];)
    {
        int j = 0;

        while (content[i] && (isalpha(content[i]) || content[i] == '_'))
        {
            palabra[j++] = tolower(content[i++]);
        }

        if (j > 0)
        {
            palabra[j] = '\0';
            pos++;
            agregar_al_indice(palabra, pos);
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
        NodoIndice *cur = indiceInvertido[i];
        while (cur)
        {
            NodoIndice *next = cur->siguiente;
            free(cur->posiciones);
            free(cur);
            cur = next;
        }
        indiceInvertido[i] = NULL;
    }
}

int word_in_index(const char *palabra)
{
    int h = hash_indice((char *)palabra);
    NodoIndice *cur = indiceInvertido[h];
    while (cur)
    {
        if (strcmp(cur->palabra, palabra) == 0)
            return 1;
        cur = cur->siguiente;
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
        agregar_al_indice(token, offset);
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
        NodoIndice *cur = indiceInvertido[i];
        while (cur)
        {
            fprintf(out, "%s", cur->palabra);
            for (int j = 0; j < cur->cantidad; j++)
                fprintf(out, " %d", cur->posiciones[j]);
            fputc('\n', out);
            cur = cur->siguiente;
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
        char palabra[100];
        strcpy(palabra, pal);

        char *num = strtok(NULL, " \n");
        while (num)
        {
            sscanf(num, "%d", &pos);
            agregar_al_indice(palabra, pos);
            num = strtok(NULL, " \n");
        }
    }
    free(line);
    fclose(in);
    return 1;
}
