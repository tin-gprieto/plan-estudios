#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include "../toolbox/interfaz/interfaz.h"
#include "../toolbox/tools/tools.h"
#include "../toolbox/TDAs/lista/lista.h"
#include "../toolbox/TDAs/hash/hash.h"

#define MAX_STRING 30
#define MAX_CODIGO 5

//Estados
#define MATERIA_APROBADA 'A'
#define MATERIA_CURSADA 'C'
#define MATERIA_HABILITADA 'H'
#define MATERIA_PENDIENTE 'P'

#define PEDIR_NOTA   0
#define PEDIR_ESTADO 1

typedef struct materia materia_t;

/*
* Crea la carrera en memoria dinámica a partir de un archivo csv (direccion)
* Devuelve NULL si no puede crearlo
*/
hash_t* carrera_crear(char* ruta_archivo);

/*
* Funcion_grafica para la interfaz, que muestra la materia junto a sus correlativas
* Pre : Interfaz creada, pasar carrera (hash_t*) y codigo_materia(const char*)
* Post: Funcion gráfica para menú de información
*/
void mostrar_materia(interfaz_t* interfaz, void* carrera, void* codigo_materia);

/*
* Funcion_grafica para la interfaz, que muestra todas las materias de la carrera
* Pre : Interfaz creada, pasar carrera (hash_t*) y aux(NULL)
* Post: Funcion gráfica para menú de información
*/
void mostrar_carrera(interfaz_t* interfaz, void* carrera, void* aux);

/*
* Funcion_grafica para la interfaz, que muestra las materias habilitadas para cursar
* Pre : Interfaz creada, pasar carrera (hash_t*) y aux(NULL)
* Post: Funcion gráfica para menú de información
*/
void mostrar_materias_habilitadas(interfaz_t* interfaz, void* carrera, void* aux);

/*
* Funcion_grafica para la interfaz, que muestra las materias aprobadas
* Pre : Interfaz creada, pasar carrera (hash_t*) y aux(NULL)
* Post: Funcion gráfica para menú de información
*/
void mostrar_materias_aprobadas(interfaz_t* interfaz, void* carrera, void* aux);

/*
* Pide el código de un materia que pertenece o no (según el parámetro)
* a la carrera y lo devuelve
* Pre : 
* Post:
*/
char* pedir_codigo(interfaz_t* interfaz, hash_t* carrera);

/*
* Crea una nueva materia con los datos que ingrese el usuario
* (Nombre, Nota, Estado, Correlativas)
* Pre : 
* Post:
*/
void pedir_dato_materia(interfaz_t* interfaz, hash_t* carrera, char* codigo, size_t tipo_dato);

/*
* Busca que todas las materias pendientes no tengan todas las correlativas aprobadas
* Necesita la carrera creada y una modificación para que sea útil actualizar
*/
void actualizar_carrera(hash_t* carrera);

/*
* Guarda los datos nuevamente en el archivo 
* Preferiblemente que hacer una modifición antes
* Necesita la carrera creada
* Devuelve ERROR (-1) si tuvo problemas para abrir el archivo o si no existe carrera
*/
int guardar_archivo(hash_t* carrera, char* ruta_archivo);


#endif /* __MATERIAS_H__ */
