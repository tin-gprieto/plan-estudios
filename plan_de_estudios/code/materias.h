#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include <stdio.h>
#include <stdbool.h>

#define MAX_MATERIA 40
#define MAX_CODIGOS 5
#define ERROR -1

#define FORMATO_R "%li;%[^;];%c;%i;%[^\n]"
#define FORMATO_W "%li;%s;%c;%i;%s"

#define APROBADA 'A'
#define CURSADA 'C'
#define HABILITADA 'H'
#define PENDIENTE 'P'

#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define ROSA "\e[35m"
#define CYAN "\e[36m"

#define TILDE "✓"
#define CRUZ "✗"

typedef struct correlativas{
  long int codigos[MAX_CODIGOS];
  void* direcciones[MAX_CODIGOS];
  int cantidad;
} correlativas_t;

typedef struct materia{
  long int codigo;
  char nombre[MAX_MATERIA];
  char estado;
  int nota;
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
carrera_t* crear_carrera(char* ruta_archivo);

/*
* Libera la memoria reservada para toda la carrera 
*(puntero a materias, puntero de correlativas, carrera)
*/
void liberar_carrera(carrera_t* carrera);

/*
* Busca en una carrera una materia y muestra su estado y todas sus correlativas
* Necesita la carrera creada y que el codigo sea válido
* ERROR si no exite la carrera o no está la materia
*/
int buscar_materia(carrera_t* carrera, long int codigo_materia);

/*
* Elimina una materia de la carrera mediante un código por parámetro
* Devulve ERROR (-1) si el código no corresponde a una materia
*/
int eliminar_materia(carrera_t* carrera, long int codigo_materia);

/*
* Agrega una materia al final de la carrera
* con caracteristicas que ingrese el usuario (no puede ser igual a otra materia)
* Debe recibir una materia con todas las caracteristicas dadas
* Devulve ERROR (-1) si el código de materia ya existe
*/
int agregar_materia(carrera_t* carrera, materia_t materia);

/*
* Recibe una materia y el usurio modifica estado o nota 
* (cambiar una materia a aprobada o cursada)(reemplazandola en la carrera)
* Necesita la carrera creada y que una materia de la carrera
* ERROR si no exite la carrera o no está la materia
*/
int modificar_materia(carrera_t* carrera, materia_t materia);

/*
* Busca que todas las materias pendientes no tengan todas las correlativas aprobadas
* Necesita la carrera creada y una modificación para que sea útil actualizar
*/
void actualizar_carrera(carrera_t* carrera);

/*
* Guarda los datos nuevamente en el archivo 
* Preferiblemente que hacer una modifición antes
* Necesita la carrera creada
* Devuelve ERROR (-1) si tuvo problemas para abrir el archivo o si no existe carrera
*/
int guardar_archivo(carrera_t* carrera, char* ruta_archivo);



#endif /* __MATERIAS_H__ */
