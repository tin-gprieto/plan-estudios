#include "materias.h"

#define SIN_CORRELATIVAS -1
#define DATOS_LEIDOS 5
#define MAX_CODIGOS 10
#define SEPARADOR "."

//Formato de lectura
#define FORMATO_R "%i;%[^;];%c;%i;%[^\n]\n"

//Formato de escritura
#define FORMATO_W "%i;%s;%c;%i;%s\n"

/*
*Recorre recursivamente las materias liberando el espacio
desde la última a la primera y finalmente libera el
espacio de la carrera
*/
void liberar_materias(materia_t* materia){
    if(!materia)
        return;
    liberar_materias(materia->proximo);
    free(materia->correlativas.vector);
    free(materia);
}

//materias.h
bool carrera_vacia(carrera_t* carrera){
    if(!carrera)
        return true;
    return !(carrera->origen);
}

//materias.h
size_t cantidad_materias(carrera_t* carrera){
    if(!carrera || carrera_vacia(carrera))
        return 0;
    return carrera->cantidad_materias;
}

//materias.h
void liberar_carrera(carrera_t* carrera){
    if(!carrera)
        return;
    if(!carrera_vacia(carrera))
        liberar_materias(carrera->origen);
    free(carrera);
}

/*
*Dado un string con números separados por '.', 
*se cargan al vector de códigos todos ellos
*modificando la cantidad
*Pre: string cargado desde archivo 
*/
void conseguir_codigos(char correlativas[], int codigos[], size_t* cantidad){
    char* token=strtok(correlativas, SEPARADOR);
    while(token){
        codigos[*cantidad]=atoi(token);
        (*cantidad) ++;
        token=strtok(NULL, SEPARADOR);
    }
}

/*
*Pre: el codigo debe ser el primero (y último) cargado 
*en el array de códigos
*Post: Devuelve verdadero si el código pasado es distinto a -1
*(convención para indicar que no hay correlativas)
*/
bool tiene_correlativas(int primer_codigo){
    if(primer_codigo == SIN_CORRELATIVAS)
        return false;
    return true;
}

/*
*Compara el código con todos los de las correlativas
*devuelve verdadero si coincide con alguno o Falso
*en caso contrario
*/
bool cotejar_codigo(long int codigo, int* array, size_t tope){
    bool encuentra = false;
    size_t pos = 0;
    while(!encuentra && (pos<tope)){
        if(codigo == array[pos])
            encuentra = true;
        else
            pos++;
    }
    return encuentra;
}

/*
*Recorre recursivamente y para atrás la lista, cargando al aux
*las materias que coincidan con alguno de los códigos.
*Pre: La primera llamada se debe hacer con la materia cuyos
*codigos de las correlativas se encuentran en el vector
*/
void asignar_correlativas(materia_t* corriente, int* codigos, materia_t** aux, size_t tope, int* pos){
    if(!corriente) //se llegó al principio de la lista
        return;
    if((*pos) > (tope-1)) //se cargaron todas las materias
        return;
    if(cotejar_codigo(corriente->info.codigo, codigos, tope)){
        aux[(*pos)] = corriente;
        (*pos)++;
    }
    asignar_correlativas(corriente->anterior, codigos, aux, tope, pos);
}

/* 
*Carga las direcciones de las materias correlativas para cada materia
*/
materia_t** cargar_correlativas(materia_t* materia, char correlativas[]){
    int codigos[MAX_CODIGOS];
    materia->correlativas.cantidad = 0;
    conseguir_codigos(correlativas, codigos, &(materia->correlativas.cantidad));
    if(!tiene_correlativas(codigos[0])){
        materia->correlativas.cantidad = 0;
        return NULL;
    }
    materia_t** aux = calloc(materia->correlativas.cantidad, sizeof(materia_t*));
    if(!aux)
        return NULL;
    int pos = 0;
    asignar_correlativas(materia, codigos, aux, materia->correlativas.cantidad, &pos);
    return aux;
}

void print_materia(materia_t* materia, int leidos){
    printf("Leidos %i", leidos);
    printf("%i : %s : %s ; %c ; %i \n", materia->info.codigo,
                                        materia->info.nombre,
                                        materia->correlativas.str,
                                        materia->info.estado,
                                        materia->info.nota);
}

void enlazar_elementos(materia_t * raiz, materia_t** vector, size_t* cant_materias){
    for(size_t i=0; i < (*cant_materias); i++){
        if(i == 0){
            vector[i]->anterior = NULL;
            raiz = vector[i];
        }else{
            vector[i]->correlativas.vector = cargar_correlativas(vector[i], vector[i]->correlativas.str);
            if(i == (*cant_materias)-1){
                vector[i]->proximo = NULL;
            }else{
                vector[i]->proximo = vector[i+1]; 
            }
            vector[i]->anterior = vector[i-1];
        }   
        
    }
}
/* 
*Carga todas las materias del archivo al vector de la carrera, agrandando en cada insercion
*/
//Iterativo
int cargar_materias(FILE* archivo, materia_t* nodo_raiz, size_t* cant_materias){
    materia_t** vector = malloc(sizeof(materia_t**));
    if(!vector) return ERROR;
    size_t pos = 0;
    vector[pos] = malloc(sizeof(materia_t*));
    if(!vector[pos]) return ERROR;

    int leidos = fscanf(archivo, FORMATO_R, &(vector[pos]->info.codigo),
                                            vector[pos]->info.nombre,
                                            &(vector[pos]->info.estado),
                                            &(vector[pos]->info.nota),
                                            vector[pos]->correlativas.str);
    bool problemas = false;
    materia_t** aux;
    while (!problemas && leidos == DATOS_LEIDOS){
        pos ++;
        aux = realloc(vector, (size_t) ((pos+1) * sizeof(materia_t**)));
        if(!aux){
            problemas = true;
        }else{
            vector = aux;
            vector[pos] = malloc(sizeof(materia_t**));
            if(!vector[pos]){
                problemas = true;
            }else{
                leidos = fscanf(archivo, FORMATO_R, &(vector[pos]->info.codigo),
                                                    vector[pos]->info.nombre,
                                                    &(vector[pos]->info.estado),
                                                    &(vector[pos]->info.nota),
                                                    vector[pos]->correlativas.str);
            }
        }

    }
    (*cant_materias) = pos+1;
    enlazar_elementos(nodo_raiz, vector, cant_materias);
    free(vector);
    return EXITO;
}


/*
//Implementacion recursiva
int cargar_materias(FILE* archivo, materia_t* anterior, materia_t* materia, size_t* cant_materias){
    materia = malloc(sizeof(materia_t*));
    if(!materia)
        return ERROR;
    int leidos = fscanf(archivo, FORMATO_R, &(materia->info.codigo),
                                            materia->info.nombre,
                                            &(materia->info.estado),
                                            &(materia->info.nota),
                                            materia->correlativas.str);
    if(leidos != DATOS_LEIDOS){
        free(materia);
        if (!anterior) //No hay ni un elemento válido en el archivo (Carrera vacia)
            return EXITO;
        anterior->proximo = NULL; //Se llegó al final del archivo
        return EXITO;
    }
    (*cant_materias) ++;
    materia->anterior = anterior;
    if(!anterior){
        materia->correlativas.cantidad = 0; //El primer elemento no puede tener correlativas
        materia->correlativas.vector = NULL;
    }else{
        anterior->proximo = materia;
        materia->correlativas.vector = cargar_correlativas(materia, materia->correlativas.str);
    }
    return cargar_materias(archivo, materia, materia->proximo, cant_materias);
}
*/

//materias.h
carrera_t* crear_carrera(char* ruta_archivo){
    FILE* archivo = fopen(ruta_archivo, "r");
    if(!archivo)
        return NULL;

    carrera_t* carrera = malloc(sizeof(carrera_t));
    if(!carrera)
        return NULL;

    carrera->origen = NULL;
    carrera->cantidad_materias = 0;
    
    int estado = cargar_materias(archivo, carrera->origen, &(carrera->cantidad_materias));
    fclose(archivo);
    if(estado == ERROR){
        liberar_carrera(carrera);
        return NULL;
    }
    return carrera;
}

//materias.h
materia_t* buscar_materia(carrera_t* carrera, long int codigo_materia){
    if (!NULL)
        return NULL;

    return NULL;
}

//materias.h
int modificar_materia(carrera_t* carrera, long int codigo_materia){
     if (carrera == NULL)
        return ERROR;
    
    materia_t* modificar = buscar_materia(carrera, codigo_materia);
    if(!modificar)
        return ERROR;

    return EXITO;
}

//materias.h
int eliminar_materia(carrera_t* carrera, long int codigo_materia){
    if (!carrera)
        return ERROR;
    
    
    materia_t* eliminada = buscar_materia(carrera, codigo_materia);
    if(!eliminada)
        return ERROR;
    

    return EXITO;
}

//materias.h
int agregar_materia(carrera_t* carrera, materia_t materia){
     if (!carrera)
        return ERROR;
    

    return EXITO;
}

//materias.h
void actualizar_carrera(carrera_t* carrera){

}

//materias.h
int guardar_archivo(carrera_t* carrera, char* ruta_archivo){
    return EXITO;
}

/*
*Cumple la función del iterador de manera recursiva
*/
void recorrer_materias(materia_t* corriente, bool (*funcion)(materia_t*, void*), void* extra, size_t* contador, bool* continua){
    if(!corriente)
        return;
    (*continua) = funcion(corriente, extra);
    if(!continua)
        return;
    recorrer_materias(corriente->proximo, funcion, extra, contador, continua);
}

//materias.h
size_t iterrar_carrera(carrera_t* carrera, bool (*funcion)(materia_t*, void*), void* extra){
    if(!carrera || !funcion || carrera_vacia(carrera))
        return 0;
    size_t contador = 0;
    bool estado=true;
    recorrer_materias(carrera->origen, funcion, extra, &contador, &estado);
    return contador;
}
