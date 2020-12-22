#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include "tools.h"

#define MAX_NOMBRE 50

#define FORMATO_R "%li;%[^;];%c;%i;%[^\n]"
#define FORMATO_W "%li;%s;%c;%i;%s"

#define APROBADA 'A'
#define CURSADA 'C'
#define HABILITADA 'H'
#define PENDIENTE 'P'

//Informacion de lista
typedef struct info{
  long int codigo;
  char nombre[MAX_NOMBRE];
  char estado;
  int nota;
}info_t;

//Nodo lista
typedef struct materia{
  info_t info;
  struct materia* anterior;
  struct materia* proximo;
  struct materia** correlativas;
  size_t cant_correlativas;
} materia_t;

//Lista doblemente enlazada
typedef struct carrera{
  materia_t* origen;
  size_t cantidad_materias;
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
* Busca en una materia según su código y la devuelve como puntero
* Necesita la carrera creada y que el codigo sea válido
* NULL si no exite la carrera o no está la materia
*/
materia_t* buscar_materia(carrera_t* carrera, long int codigo_materia);

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
* Recibe una materia y el usuario modifica estado o nota 
* (cambiar una materia a aprobada o cursada)(reemplazandola en la carrera)
* Necesita la carrera creada y que una materia de la carrera
* ERROR si no exite la carrera o no está la materia
*/
int modificar_materia(carrera_t* carrera, long int codigo_materia);

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

/*
*Itera sobre todos las materias de la carrera y aplica
*la funcion en cada una de ellas. Una vez la funcion 
devuelva falso, cortará la iteracion devolviendo la cantidad
de materias recorridas. La funcion debe un párametro a la materia
y otro a un elemento extra a uso del usuario.
*
*/
size_t iterrar_carrera(carrera_t* carrera, bool (*funcion)(materia_t*, void*), void* extra);


#endif /* __MATERIAS_H__ */
