#include "materias.h"

#define DATOS_LEIDOS 5
#define MAX_STRING 30
#define MAX_CODIGOS 10
#define SEPARADOR_CORRELAV ","

/*
*Recorre recursivamente las materias liberando el espacio
desde la última a la primera y finalmente libera el
espacio de la carrera
*/
void liberar_materias(materia_t* materia){
    if(!materia->proximo)
        return;
    liberar_materias(materia->proximo);
    free(materia);
}

/*
*Devuelve verdadero si la carrera está vacia
*/
bool carrera_vacia(carrera_t* carrera){
    return !(carrera->origen);
}

void liberar_carrera(carrera_t* carrera){
    if(!carrera)
        return;
    if(!carrera_vacia(carrera))
        liberar_materias(carrera->origen);
    free(carrera);
}
/*
*
*
*/
void conseguir_codigos(char codigos[], int correlativas[], size_t cantidad){

}

/* 
*Carga las direcciones de las materias correlativas para cada materia
*/
materia_t** cargar_correlativas(materia_t* materia, char correlativas[]){
    int codigos[MAX_CODIGOS];
    materia->cant_correlativas = 0;
    conseguir_codigos(correlativas, codigos, materia->cant_correlativas);
    return 0;
}

/* 
*Carga todas las materias del archivo al vector de la carrera, agrandando en cada insercion
*/
int cargar_materias(FILE* archivo, materia_t* anterior, materia_t* materia, size_t* cant_materias){
    materia = malloc(sizeof(materia));
    if(!materia)
        return ERROR;
    char correlativas[MAX_STRING]; 
    int leidos = fscanf(archivo, FORMATO_R, &(materia->info.codigo),
                                            materia->info.nombre,
                                            &(materia->info.estado),
                                            &(materia->info.nota),
                                            correlativas);
    if(leidos != DATOS_LEIDOS){
        anterior->proximo = NULL;
        return EXITO;
    }
    (*cant_materias) ++;
    if(anterior){
        materia->anterior = anterior;
        materia->correlativas = cargar_correlativas(materia, correlativas);
    }else{
        materia->cant_correlativas= 0;
        materia->correlativas = NULL;
    }
    return cargar_materias(archivo, materia, materia->proximo, cant_materias);
}

carrera_t* crear_carrera(char* ruta_archivo){
    FILE* archivo = fopen(ruta_archivo, "r");
    if(!archivo)
        return NULL;

    carrera_t* carrera = malloc(sizeof(carrera_t));
    if(!carrera)
        return NULL;

    carrera->origen = NULL;
    carrera->cantidad_materias = 0;
    
    int estado = cargar_materias(archivo, NULL, carrera->origen, &(carrera->cantidad_materias));
    if(estado == ERROR){
        liberar_carrera(carrera);
        return NULL;
    }
    return carrera;
}

materia_t* buscar_materia(carrera_t* carrera, long int codigo_materia){
    if (!NULL){
        warning("la creacion de la materia");
        return NULL;
    }


    warning("la materia ingresada");
    return NULL;
    
}

int modificar_materia(carrera_t* carrera, long int codigo_materia){
     if (carrera == NULL){
        warning("la creacion de la materia");
        return ERROR;
    }
    
    materia_t* modificar = buscar_materia(carrera, codigo_materia);
    if(!modificar){
        warning("la materia ingresada");
        return ERROR;
    }

    return 0;
}

int eliminar_materia(carrera_t* carrera, long int codigo_materia){
    if (!carrera){
        warning("la creacion de la materia");
        return ERROR;
    }
    
    materia_t* eliminar = buscar_materia(carrera, codigo_materia);
    if(!eliminar){
        warning("la materia ingresada");
        return ERROR;
    }

    return 0;
}

int agregar_materia(carrera_t* carrera, materia_t materia){
     if (!carrera){
        warning("la creacion de la materia");
        return ERROR;
    }

    return 0;
}

void actualizar_carrera(carrera_t* carrera){

}

int guardar_archivo(carrera_t* carrera, char* ruta_archivo){
    return 0;
}

size_t iterrar_carrera(carrera_t* carrera, bool (*funcion)(materia_t*, void*), void* extra){
    return 0;
}
