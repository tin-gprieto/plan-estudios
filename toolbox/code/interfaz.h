#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "tools.h"

#define MAX_STRING 100
#define MAX_OPCIONES 10
#define MAX_DESCRIPCION 80
#define MAX_COLOR 8

#define OPCION_SALIR 'S'
#define OPCION_VOLVER 'V'

typedef struct menu{
    char titulo[MAX_DESCRIPCION];
    char color_titulo[MAX_COLOR];
    char opciones[MAX_OPCIONES];
    char descripciones[MAX_OPCIONES][MAX_DESCRIPCION];
    size_t cant_opciones;
}menu_t;

typedef struct interfaz{
    char estado;
    size_t max;
    size_t margen;
    size_t espaciado;
    char color_fondo[MAX_COLOR];
    menu_t* menus;
    size_t cant_menus;
}interfaz_t;

/* 
* Crea la interfaz en memoria dinamica
* Pre : -
* Post: puntero a interfaz lista para usarse o NULL en caso de algún error
*/
interfaz_t* interfaz_crear(size_t max, size_t margen, size_t espaciado);

/* 
* Destruye el espacio asignado a la interfaz y a los menus
* Pre :  Interfaz creada
* Post:  Memoria liberada
*/
void interfaz_destruir(interfaz_t* interfaz);

/* 
* Devuelve el estado actual de la interfaz
* (Modo en el que debe ejecutarse según lo elegido por el usuario)
* Pre : Interfaz creada 
* Post: Elección del usuario
*/
char interfaz_estado(interfaz_t* interfaz);

/*
* 
* Pre :
* Post:
*/
int menu_insertar(interfaz_t* interfaz, char titulo[MAX_DESCRIPCION], char color_titulo[MAX_COLOR]);

/* 
* Dada una interfaz, carga una letra y su descripcion para el menú
* Pre : interfaz creada, menú dentro del rango posible
* Post: Opcion y descripción cargados al final del menu
*/
void menu_cargar_opcion(interfaz_t* interfaz, size_t menu, char opcion, const char* descripcion);

/* 
* Elimina una de las opciones del menu
* Pre : Recibe un vector de menús, el tipo de menú en el que se encuetra
* y la opcion que se desea eliminar
* Post: Eliminar del vector opciones (dentro del menu) a la opcion deseada
*/
void menu_eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion);

/*
* 
* Pre :
* Post:
*/
void menu_mostrar(interfaz_t* interfaz, size_t menu);

/*
* Dado un string constante, imprime por pantalla su mensaje de forma tal que
* el usuario sepa que hay un error
* Pre : Descripcion completa del problema
* Post: Información por pantalla
*/
void reportar_error(interfaz_t* interfaz, const char *descripcion);

/* 
* Dado el máximo de un conjunto, 
* pide al usuario una posicion válida para el mismo
* Pre : Interfaz creada
* Post: Un numero positivo elegido por el usuario
*/
size_t pedir_numero(interfaz_t* interfaz);

/* 
* Pide una ruta de archivo al usuario y devuelve como retorno 
* Pre : Interfaz creada
* Post: ruta válida del archivo (sin fallo de apertura)
*/
char* pedir_archivo_csv(interfaz_t* interfaz);

#endif /* __INTERFAZ_H__ */