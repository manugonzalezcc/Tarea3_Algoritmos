#include <stdio.h>
#include <unistd.h>
#include "tokenizer.h"
#include "search.h"
#include "help.h"
#include "boyer_moore.h"
#include "shift_and.h"
#include "load.h"
#include "inverted_index.h"

int main(int argc, char *argv[])
{
    int opt;
    char *archivo = NULL;
    int verbose = 0;
    char *consulta = NULL;

    while ((opt = getopt(argc, argv, "f:vhq:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            archivo = optarg;
            break;
        case 'h':
            print_help(argv[0]);
            return 0;
        case 'v':
            verbose = 1;
            break;
        case 'q':
            consulta = optarg;
            break;
        default:
            fprintf(stderr, "Uso: %s -f archivo [-v] [-q palabra] [-h]\n", argv[0]);
            return 1;
        }
    }

    if (archivo == NULL)
    {
        fprintf(stderr, "El parámetro -f archivo es obligatorio\n");
        return 1;
    }

    printf("Archivo: %s\n", archivo);
    if (verbose)
    {
        printf("Modo verbose activado\n");
    }

    // Cargar y procesar archivo
    char *contenido = load(archivo);
    if (!contenido)
    {
        fprintf(stderr, "Error al cargar el archivo.\n");
        return 1;
    }

    clean_html(contenido);
    ListaTokens tokens = tokenizar_texto(contenido);

    for (int i = 0; i < tokens.cantidad; i++)
    {
        agregar_al_indice(tokens.tokens[i], i);
    }

    if (verbose)
    {
        printf("\nÍndice invertido:\n");
        imprimir_indice();
    }

    if (consulta != NULL)
    {
        // Normalizar la palabra consultada
        for (int i = 0; consulta[i]; i++)
        {
            consulta[i] = tolower(consulta[i]);
        }

        printf("\nConsulta: '%s'\n", consulta);
        int h = hash_indice(consulta);
        NodoIndice *nodo = indiceInvertido[h];
        int encontrado = 0;

        while (nodo)
        {
            if (strcmp(nodo->palabra, consulta) == 0)
            {
                printf("La palabra '%s' aparece en las posiciones: ", consulta);
                for (int i = 0; i < nodo->cantidad; i++)
                {
                    printf("%d ", nodo->posiciones[i]);
                }
                printf("\n");
                encontrado = 1;
                break;
            }
            nodo = nodo->siguiente;
        }

        if (!encontrado)
        {
            printf("La palabra '%s' no fue encontrada en el índice.\n", consulta);
        }
    }

    // Pruebas de búsqueda con texto estático
    const char *texto = "este es un texto de prueba, texto de ejemplo";
    const char *patron = "texto";

    int ocurrencias_bm = boyer_moore_bad_char(texto, patron);
    printf("Boyer-Moore: El patrón '%s' aparece %d veces en el texto.\n", patron, ocurrencias_bm);

    int ocurrencias_sa = shift_and_search(texto, patron);
    printf("Shift-And: El patrón '%s' aparece %d veces en el texto.\n", patron, ocurrencias_sa);

    liberar_tokens(tokens);
    free(contenido);

    return 0;
}
