#ifndef __HASH_H__
#define __HASH_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct hash{

}hash_t;

typedef struct hash_iter{

}hash_iterador_t;

typedef void (*hash_destructor)(void *);

/*
*
* Pre :  
* Post:
*/
hash_t *hash_crear(hash_destructor destruir_elemento);

/*
*
* Pre :  
* Post:
*/
bool hash_guardar(hash_t *hash, size_t clave, void *dato);

/*
*
* Pre :  
* Post:
*/
void *hash_borrar(hash_t *hash, size_t clave);

/*
*
* Pre :  
* Post:
*/
void *hash_obtener( hash_t *hash, size_t clave);

/*
*
* Pre :  
* Post:
*/
bool hash_pertenece( hash_t *hash, size_t clave);

/*
*
* Pre :  
* Post:
*/
size_t hash_cantidad( hash_t *hash);

/*
*
* Pre :  
* Post:
*/
void hash_destruir(hash_t *hash);

/*
*
* Pre :  
* Post:
*/
hash_iterador_t *hash_iterador_crear(hash_t *hash);

/*
*
* Pre :  
* Post:
*/
bool hash_iterador_avanzar(hash_iterador_t *iter);

/*
*
* Pre :  
* Post:
*/
size_t hash_iterador_elemento_actual(hash_iterador_t *iter);

/*
*
* Pre :  
* Post:
*/
bool hash_iterador_al_final(hash_iterador_t *iter);

/*
*
* Pre :  
* Post:
*/
void hash_iterador_destruir(hash_iterador_t* iter);

#endif /* __HASH_H__ */


