#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "materias.h"
/*
*Muestra por pantalla un error (se especifica por parámetro)
*/
void advertencia (char* aviso){
    printf( ROJO "%s ERROR - Hubo un problema con %s" RESET "\n", CRUZ, aviso);
}

/*
*Muestra una materia por pantalla según su estado
*Pre: Carrera creada
*/
void mostrar_materia(materia_t materia){
    if(materia.estado == APROBADA){
        printf( VERDE "%s %li-%s : %i " RESET "\n", TILDE, 
                                                   materia.codigo, 
                                                   materia.nombre, 
                                                   materia.nota);
    }else if (materia.estado == CURSADA){
        printf(AMARILLO "- %li-%s : %i (parcial) " RESET "\n", materia.codigo, 
                                                              materia.nombre, 
                                                              materia.nota);
    }else if (materia.estado == HABILITADA){
        printf(". %li-%s \n", materia.codigo, materia.nombre);
    }else if (materia.estado == PENDIENTE){
        printf(ROJO "%s %li-%s" RESET "\n", CRUZ, materia.codigo, materia.nombre);
    }else{
        printf(CYAN ". %li-%s " ROJO "! TIENE UN ESTADO INVÁLIDO" RESET "\n",materia.codigo, 
                                                                         materia.nombre);
    }
}

/* 
*Carga las direcciones de las materias correlativas para cada materia
*/
int cargar_correlativas(carrera_t* carrera, materia_t* materias){
    return 0;
}

/* 
*Carga los codigos de las materias correlativas a un vector
*teniendo como partida un string con los mismos separados por una ','
*/
void cargar_cod_correlativas(char* string, long int codigos[MAX_CODIGOS], int* cant_codigos){

}

/* 
*Carga todas las materias del archivo al vector de la carrera, agrandando en cada insercion
*/
int cargar_materias(FILE* archivo, materia_t* materias, int* cant_materias){
    return 0;
}

carrera_t* crear_carrera(char* ruta_archivo){
    FILE* archivo = fopen(ruta_archivo, "r");
    if(!archivo){
        advertencia("la apertura del archivo.");
        return NULL;
    }
    carrera_t* carrera;
    carrera = malloc(sizeof(carrera_t));
    if(!carrera){
        advertencia("la memoria dinamica.");
        return NULL;
    }
    (*carrera).materias = malloc(sizeof(materia_t));
    (*carrera).cantidad_materias=0;
    if(!(*carrera).materias){
        free(carrera);
        advertencia("la memoria dinamica.");
        return NULL;
    }
    int estado;
    estado = cargar_materias(archivo, (*carrera).materias, &((*carrera).cantidad_materias));
    if(estado == ERROR){
        free((*carrera).materias);
        free(carrera);
        advertencia("la carga de materias.");
        return NULL;
    }
    estado = cargar_correlativas(carrera, (*carrera).materias);
    if(estado == ERROR){
        free((*carrera).materias);
        free(carrera);
        advertencia("la carga de correlativas.");
        return NULL;
    }
    return carrera;
}

void liberar_carrera(carrera_t* carrera){
    free(carrera);
}

void listar_carrera(carrera_t* carrera){

}

void listar_aprobadas(carrera_t* carrera){

}

void listar_habilitadas(carrera_t* carrera){

}
bool pertence_materia(carrera_t* carrera, long int codigo){
    return false;
}

int buscar_materia(carrera_t* carrera, long int codigo_materia){
    if (carrera == NULL){
        advertencia("la creacion de la materia");
        return ERROR;
    }

    if(!pertence_materia(carrera, codigo_materia)){
        advertencia("la materia ingresada");
        return ERROR;
    }
    
    return 0;
}

int modificar_materia(carrera_t* carrera, long int codigo_materia){
     if (carrera == NULL){
        advertencia("la creacion de la materia");
        return ERROR;
    }
    
    if(!pertence_materia(carrera, codigo_materia)){
        advertencia("la materia ingresada");
        return ERROR;
    }

    return 0;
}

int eliminar_materia(carrera_t* carrera, long int codigo_materia){
    if (carrera == NULL){
        advertencia("la creacion de la materia");
        return ERROR;
    }
    
    if(!pertence_materia(carrera, codigo_materia)){
        advertencia("la materia ingresada");
        return ERROR;
    }

    return 0;
}

int agregar_materia(carrera_t* carrera, materia_t materia){
     if (carrera == NULL){
        advertencia("la creacion de la materia");
        return ERROR;
    }

    return 0;
}

void actualizar_carrera(carrera_t* carrera){

}

int guardar_archivo(carrera_t* carrera, char* ruta_archivo){
    return 0;
}
