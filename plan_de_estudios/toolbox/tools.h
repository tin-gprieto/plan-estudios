#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <signal.h>

#define ERROR -1
#define EXITO 0

#define RESET "\e[0m"

#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define ROSA "\e[35m"
#define CYAN "\e[36m"
#define BLANCO "\e[37m"

#define FVERDE "\e[42m"

#define SI 's'
#define NO 'n'

#define TILDE "✓"
#define CRUZ "✗"

#define MAX_LINES 80
#define MAX_COLS 80

/*
*Imprime por pantalla un array de números enteros de tamaño size
*/
void print_array(int* array, size_t size);

/*
*INCOMPLETA
*/
void print_matrix(int matrix[MAX_LINES][MAX_COLS], size_t lines, size_t cols);

/*
*Imprime por pantalla el porcentaje representado en una barra 
*que representa quantity en relacion al total
*/
void print_porcentage_bar(size_t quantity, size_t total);

/*
*Imprime por pantalla una advertencia según description
*/
void warning(const char * description);

/*
*Imprime por pantalla una prueba con su descripcion
*Si la afirmación no se cumple se considera un error
*/
void test_afirmar(int afirmacion, const char *descripcion);

/*
*Muestra por pantalla el título para un nuevo grupo
*/
void test_nuevo_grupo(const char *descripcion);

/*
*Muestra por pantalla el título y una separación para un
*nuevo subgrupo
*/
void test_nuevo_sub_grupo(const char *descripcion);

/*
*Muestra por pantall la cantidad de pruebas corridas y errores
*/
void test_mostrar_reporte();

#endif /* __TOOLS_H__ */