#include "libs.h"
#include "ranking.h"
#include "load.h"

void search_in_docs(const char *pattern, char *files[], int file_numbers)
{
    Result results[file_numbers];

    for (int i = 0; i < file_numbers; i++)
    {
        FILE *f = fopen(files[i], "r");
        if (!f)
        {
            perror("No se pudo abrir el archivo");
            results[i].quantity_of_appearances = -1;
            continue;
        }

        char text[10000];
        fread(text, 1, sizeof(text) - 1, f);
        fclose(f);

        normalize_text(text);
        clean_html(text);

        int count = 0;
        char *token = strtok(text, " \t\n,.!?;:");
        while (token != NULL)
        {
            if (strcmp(token, pattern) == 0)
            {
                count++;
            }
            token = strtok(NULL, " \t\n,.!?;:");
        }

        strcpy(results[i].file_name, files[i]);
        results[i].quantity_of_appearances = count;
    }

    for (int i = 0; i < file_numbers - 1; i++)
    {
        for (int j = i + 1; j < file_numbers; j++)
        {
            if (results[j].quantity_of_appearances > results[i].quantity_of_appearances)
            {
                Result temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    printf(CYAN "\n╔══════════════════════════════════════════════════════╗\n");
    printf("║" RESET "   " MAGENTA "Ranking de documentos por relevancia de" RESET " '%s'   " CYAN "║\n", pattern);
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║" YELLOW "  Documento" RESET "                         │ " YELLOW "Apariciones" RESET "           " CYAN "║\n");
    printf("╠══════════════════════════════════════════════════════╣\n");

    for (int i = 0; i < file_numbers; i++)
    {
        if (results[i].quantity_of_appearances >= 0)
        {
            printf("║  " GREEN "%-35s" RESET "│  " BLUE "%-20d" RESET CYAN "║\n",
                   results[i].file_name,
                   results[i].quantity_of_appearances);
        }
    }

    printf("╚══════════════════════════════════════════════════════╝\n" RESET);
}

char **list_valid_files(const char *directory, int *quantity)
{
    DIR *dir;
    struct dirent *input;
    char **files = NULL;
    int total = 0;

    dir = opendir(directory);
    if (dir == NULL)
    {
        perror("No se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    while ((input = readdir(dir)) != NULL)
    {
        if (input->d_type == DT_REG)
        {
            const char *nombre = input->d_name;
            const char *ext = strrchr(nombre, '.');

            if (ext && (strcmp(ext, ".html") == 0 || strcmp(ext, ".txt") == 0))
            {
                char ruta_completa[512];
                snprintf(ruta_completa, sizeof(ruta_completa), "docs/%s", nombre);

                files = realloc(files, (total + 1) * sizeof(char *));
                files[total] = strdup(ruta_completa);
                total++;
            }
        }
    }

    closedir(dir);
    *quantity = total;
    return files;
}
