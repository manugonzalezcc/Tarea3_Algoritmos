#include "load.h"
#include "libs.h"

char *load(const char *route)
{
    FILE *file = fopen(route, "r");
    if (!file)
    {
        return NULL;
    }

    char *buffer = (char *)malloc(TAM_MAX);
    if (!buffer)
    {
        perror("Error de memoria");
        fclose(file);
        return NULL;
    }

    size_t readed = fread(buffer, 1, TAM_MAX - 1, file);
    buffer[readed] = '\0';

    fclose(file);

    clean_html(buffer);
    normalize_text(buffer);

    // char stopwords[MAX_STOPWORDS][32];
    // int count = load_stopwords("stopwords-es.txt", stopwords, MAX_STOPWORDS);
    // delete_stopwords(buffer, stopwords, count);

    return buffer;
}

void clean_html(char *texto)
{
    char *read = texto;
    char *write = texto;
    int label = 0;

    while (*read)
    {
        if (*read == '<')
        {
            label = 1;
        }
        else if (*read == '>')
        {
            label = 0;
            read++;
            continue;
        }
        else if (!label)
        {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
}

void normalize_text(char *text)
{
    unsigned char *src = (unsigned char *)text;
    unsigned char *dst = (unsigned char *)text;

    while (*src)
    {
        if (src[0] == 0xC3)
        {
            switch (src[1])
            {
            case 0xA1:
            case 0x81:
                *dst++ = 'a';
                break;
            case 0xA9:
            case 0x89:
                *dst++ = 'e';
                break;
            case 0xAD:
            case 0x8D:
                *dst++ = 'i';
                break;
            case 0xB3:
            case 0x93:
                *dst++ = 'o';
                break;
            case 0xBA:
            case 0x9A:
                *dst++ = 'u';
                break;
            case 0xB1:
            case 0x91:
                *dst++ = 'n';
                break;
            default:
                break;
            }
            src += 2;
        }
        else
        {
            *dst++ = tolower(*src++);
        }
    }

    *dst = '\0';
}
//*