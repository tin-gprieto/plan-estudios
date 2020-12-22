#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ERROR -1
#define EXITO 0

#define RESET "\e[0m"

#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define ROSA "\e[35m"
#define CYAN "\e[36m"
#define ROJO "\e[31m"

#define FVERDE "\e[42m"

#define SI 's'
#define NO 'n'

#define TILDE "✓"
#define CRUZ "✗"

#define MAX_LINES 80
#define MAX_COLS 80


void print_array(int* array, size_t size);

void print_matrix(int matrix[MAX_LINES][MAX_COLS], size_t lines, size_t cols);

void print_porcentage_bar(size_t quantity, size_t total);

void warning(const char * description);

#endif /* __TOOLS_H__ */