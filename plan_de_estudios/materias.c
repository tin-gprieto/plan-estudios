#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "materias.h"
/*
*Muestra por pantalla un error (se especifica por parámetro)
*/
void advertencia (char* aviso){
    printf( ROJO "%s ERROR " ROJO_CLARO "- Hubo un problema con %s" RESET "\n", CRUZ, aviso);
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

carrera_t* crear_carrera(char* ruta_archivo){
    FILE* archivo = fopen(ruta_archivo, "r");
    if(!archivo){
        advertencia("la apertura del archivo.");
        return NULL;
    }
    carrera_t* aux;
    aux = malloc(sizeof(carrera_t));
    if(!aux){
        advertencia("la memoria dinamica.");
        return NULL;
    }
    return aux;
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

int buscar_materia(carrera_t* carrera, char* a_buscar){
    return 0;
}


int modificar_materia(carrera_t* carrera, char* a_modificar){
    return 0;
}

void actualizar_carrera(carrera_t* carrera){

}

int agregar_materia(carrera_t* carrera, materia_t materia){
    return 0;
}

int eliminar_materia(carrera_t* carrera, long int codigo_materia){
    return 0;
}

int guardar_archivo(carrera_t* carrera, char* ruta_archivo){
    return 0;
}
