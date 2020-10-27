#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include <stdio.h>
#include <stdbool.h>

#define MAX_MATERIA 40
#define MAX_CODIGOS 5
#define ERROR -1

#define FORMATO_R "%i;%[^;];%c;%i;%[^\n]"
#define FORMATO_W "%i;%s;%c;%i;%s"

#define APROBADA 'A'
#define CURSADA 'C'
#define HABILITADA 'H'
#define PENDIENTE 'P'

#define VERDE "\e[32m"
#define CYAN "\e[36m"
#define AMARILLO "\e[33m"
#define ROJO "\e[31m"
#define RESET "\e[0m"

typedef struct correlativas{
  int codigos[MAX_CODIGOS];
  void* p_correlativas;
  int cantidad_correlativas;
} correlativas_t;

typedef struct materia{
  int codigo;
  char materia[MAX_MATERIA];
  char estado;
  correlativas_t correlativas;
} materia_t;

typedef struct carrera{
  materia_t* materias;
  int cantidad_materias;
} carrera_t;

/*
* Crea la carrera en memoria dinámica a partir de un archivo csv (direccion)
* Devuelve NULL si no puede crearlo
*/
carrera_t* crear_carrera(const char ruta_archivo);

/*
* Libera la memoria reservada para toda la carrera 
*(puntero a materias, puntero de correlativas, carrera)
*/
void liberar_carrera(carrera_t* carrera);

/*
* Recorre toda la carrera y muestra las materias aprobadas
* Necesita la carrera creada
*/
void listar_aprobadas(carrera_t* carrera);

/*
* Recorre toda la carrera y muestra las materias que se pueden cursar
* Necesita la carrera creada
*/
void listar_habilitadas(carrera_t* carrera);

/*
* Busca en una carrera una materia y muestra su estado y todas sus correlativas
* Necesita la carrera creada
* Devuelve ERROR (-1) si no la encuentra o si no existe carrera
*/
int buscar_materia(carrera_t* carrera, const char a_buscar);

/*
* Calcula el promedio según todas las materias aprobadas
* Necesita la carrera creada
*/
void calcular_promedio(carrera_t* carrera);

/*
* Recibe el nombre de una materia a modificar y el usuario la modifica 
*(Primero el estado y luego procede)(reemplazandola en la carrera)
* Necesita la carrera creada
* Devuelve ERROR (-1) si no la encuentra  o si no existe carrera
*/
int modificar_materia(carrera_t* carrera, const char a_modificar);

/*
* Guarda los datos nuevamente en el archivo 
* Preferiblemente que hacer una modifición antes
* Necesita la carrera creada
* Devuelve ERROR (-1) si tuvo problemas para abrir el archivo o si no existe carrera
*/
int guardar_archivo(carrera_t* carrera, const char ruta_archivo);

/*
* Agrega una materia al final del archivo de materias.csv
* con caracteristicas que ingrese el usuario
* Devulve ERROR (-1) si no pudo abrir el archivo
*/
int agregar_materia(const char ruta_archivo);

#endif /* __MATERIAS_H__ */
