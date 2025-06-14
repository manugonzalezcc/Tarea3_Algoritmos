#ifndef LIBS_H
#define LIBS_H

// Librerías estándar de C
#include <stdio.h>     // Entrada/Salida estándar (printf, fopen, etc.)
#include <stdlib.h>    // Funciones generales (malloc, free, atoi, etc.)
#include <string.h>    // Manejo de cadenas (strcpy, strcmp, strtok, etc.)
#include <ctype.h>     // Funciones para caracteres (tolower, isalpha, etc.)
#include <getopt.h>    // Manejo de argumentos de línea de comandos con opciones largas
#include <unistd.h>    // Funciones del sistema POSIX (access, getopt, etc.)
#include <time.h>      // Manejo de fechas y tiempos (time, clock, etc.)
#include <stdbool.h>   // Soporte para tipo booleano (true, false)
#include <dirent.h>    // Acceso a directorios (opendir, readdir, etc.)
#include <sys/types.h> // Tipos usados por el sistema (pid_t, size_t, etc.)
#include <limits.h>    // Constantes como PATH_MAX

// Definiciones de colores ANSI para mejorar la salida en consola
#define RED "\033[1;31m"        // Rojo brillante
#define GREEN "\033[1;32m"      // Verde brillante
#define YELLOW "\033[1;33m"     // Amarillo brillante
#define BLUE "\033[1;34m"       // Azul brillante
#define MAGENTA "\033[1;35m"    // Magenta brillante
#define CYAN "\033[1;36m"       // Cyan brillante
#define RESET "\033[0m"         // Reset de color (vuelve al color por defecto)
#define ORANGE "\033[38;5;208m" // Naranja (colores extendidos ANSI)

#endif
//*