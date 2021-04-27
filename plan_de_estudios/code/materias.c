#include "materias.h"

#define SIN_CORRELATIVAS "-1"
#define SEPARADOR_CAMPOS ";"
#define CAMPOS_LEIDOS 5
#define SEPARADOR_CORRELATIVAS "-"
#define MAX_BUFFER 100
#define MAX_NOMBRE 50

typedef struct materia{
  char nombre[MAX_NOMBRE];
  char estado;
  int nota;
  lista_t* codigos_correlativas;
} materia_t;

//Formato de lectura
#define FORMATO_R "%[^;];%[^;];%c;%i;%[^\n]\n"
//                codigo;nombre;estado;nota;correlativas

//Formato de escritura
#define FORMATO_W "%s;%s;%c;%i;%s\n"

/****************************       FUNCIONES AUXILIARES CREAR       ***********************************/

/*
*Recorre recursivamente las materias liberando el espacio
desde la última a la primera y finalmente libera el
espacio de la carrera
*/
void liberar_materia(void* materia){
    if(!materia)
        return;
    materia_t* actual = (materia_t*)materia;
    lista_destruir(actual->codigos_correlativas);
    free(actual);
}
/*
* 
* Pre :
* Post:
*/
bool estado_valido (char estado){
    return estado == MATERIA_APROBADA || estado == MATERIA_CURSADA || estado == MATERIA_HABILITADA || estado == MATERIA_PENDIENTE;
}
/*
* 
* Pre :
* Post:
*/
lista_t* cargar_correlativas(char* codigos_leidos){
    lista_t* correlativas = lista_crear();
    if(!correlativas) return NULL;
    char* codigo_actual = strtok(codigos_leidos, SEPARADOR_CORRELATIVAS);
    if(codigo_actual && strcmp(codigo_actual, SIN_CORRELATIVAS) == 0)
        return correlativas;
    int estado = EXITO;
    while(codigo_actual && estado != ERROR){
        estado = lista_insertar(correlativas, codigo_actual);
        codigo_actual = strtok(NULL, SEPARADOR_CORRELATIVAS);
    }
    if(estado == ERROR){
        lista_destruir(correlativas);
        return NULL;
    }
    return correlativas;
}
/*
* 
* Pre :
* Post:
*/
int cargar_materia(hash_t * carrera, char * linea_leida){
    materia_t* materia = malloc(sizeof(materia_t));
    if(!materia) return ERROR;
    char* codigo = 0;
    char* correlativas = 0;
    int leidos = sscanf(linea_leida, FORMATO_R, codigo, materia->nombre, &(materia->estado), &(materia->nota), correlativas);
    if(leidos != CAMPOS_LEIDOS || !estado_valido(materia->estado)){
        liberar_materia(materia);
        return ERROR;
    }
    materia->codigos_correlativas = cargar_correlativas(correlativas);
    if(!materia->codigos_correlativas){
        liberar_materia(materia);
        return ERROR;
    }
    return hash_insertar(carrera, codigo, materia);
}
/*
* 
* Pre :
* Post:
*/
int cargar_materias_carrera(FILE* plan_de_estudios, hash_t* carrera){
    char buffer[MAX_BUFFER];
    char* linea = leer_linea(buffer, MAX_BUFFER, plan_de_estudios);
    if(!linea) return ERROR;
    int estado = EXITO;
    while(linea && estado != ERROR){
        estado = cargar_materia(carrera, linea);
        if(estado != ERROR)
            linea = leer_linea(buffer, MAX_BUFFER, plan_de_estudios);
    }
    return estado;
}
/****************************       FUNCIONES AUXILIARES MOSTRAR     ***********************************/

/*
* 
* Pre :
* Post:
*/
char* linea_materia(materia_t* materia, char* codigo){
    char* linea = 0;
    if(materia->nota == ERROR)
        sprintf(linea,"%s   -   %s  Nota:   ---", codigo, materia->nombre);
    else
        sprintf(linea,"%s   -   %s  Nota:   %i", codigo, materia->nombre, materia->nota);
    return linea;
}

/*
* 
* Pre :
* Post:
*/
void imprimir_linea_estado(interfaz_t* interfaz, materia_t* materia){
    
    if(materia->estado == MATERIA_APROBADA)
        informacion_imprimir_linea(interfaz, VERDE, "    APROBADA");
    if(materia->estado == MATERIA_CURSADA)
        informacion_imprimir_linea(interfaz, AMARILLO, "    CURSADA");
    if(materia->estado == MATERIA_HABILITADA)
        informacion_imprimir_linea(interfaz, BLANCO, "    HABILITADA");
    if(materia->estado == MATERIA_PENDIENTE)
        informacion_imprimir_linea(interfaz, ROJO, "    PENDIENTE");

}
/*
* 
* Pre :
* Post:
*/
void informar_error(interfaz_t* interfaz, char* codigo){
    char* alerta = calloc(50, sizeof(char));
    if(alerta){
        sprintf(alerta, " %s - CODIGO ERRONEO (No se encuentra en la carrera)", codigo);
        informacion_imprimir_linea(interfaz, ROJO, alerta);
        free(alerta);
    }
}
/*
* 
* Pre :
* Post:
*/
void informar_carrera_realizada(interfaz_t* interfaz, size_t aprobado, size_t total){
    char* porcentaje = barra_porcentaje(aprobado, total, 50);
    if(porcentaje){
        informacion_imprimir_linea(interfaz, VERDE, porcentaje);
        free(porcentaje);
    }
}
/*
* 
* Pre :
* Post:
*/
void informar_promedio(interfaz_t* interfaz, float promedio){
    char* linea = calloc(50, sizeof(char));
    if(linea){
        sprintf(linea, "   PROMEDIO:       %.2f", promedio);
        informacion_imprimir_linea(interfaz, AMARILLO, linea);
        free(linea);
    }
}
/*
* 
* Pre :
* Post:
*/
void mostrar_correlativas(interfaz_t* interfaz, hash_t* carrera, lista_t* lista_correlativas){
    lista_iterador_t * iterador = lista_iterador_crear(lista_correlativas);
    while(lista_iterador_tiene_siguiente(iterador)){
        char* codigo = lista_iterador_elemento_actual(iterador);
        materia_t* actual = hash_obtener(carrera, codigo);
        if(!actual)
            informar_error(interfaz, codigo);
        else{
            char* info_materia = linea_materia(actual, (char *) codigo);
            if(actual->estado == MATERIA_APROBADA)
                informacion_imprimir_linea(interfaz, VERDE, info_materia);
            informacion_imprimir_linea(interfaz, BLANCO, info_materia);
            if(!lista_vacia(actual->codigos_correlativas))
                mostrar_correlativas(interfaz, carrera, actual->codigos_correlativas);
        }
    }
    lista_iterador_destruir(iterador);
}

/****************************       FUNCIONES AUXILIARES EXTRA     ***********************************/

/*
* 
* Pre :
* Post:
*/
bool nota_valida (char* nota){
    if(strlen(nota) > 2)
        return false;
    int numero = atoi(nota);
    if(numero >= -1 && numero <= 10)
        return true;
    return false;
}

/*
* 
* Pre :
* Post:
*/
bool correlativas_aprobadas(hash_t* carrera, lista_t* correlativas){
    if(lista_vacia(correlativas))
        return true;
    lista_iterador_t * iterador = lista_iterador_crear(correlativas);
    bool habilitada = true;
    while(lista_iterador_tiene_siguiente(iterador) && habilitada){
        char* codigo_actual = lista_iterador_elemento_actual(iterador);
        materia_t* correlativa = hash_obtener(carrera, codigo_actual);
        if(correlativa->estado != MATERIA_APROBADA)
            habilitada = false;
        else
            lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    return habilitada;
}

/*
* 
* Pre :
* Post:
*/
char* escribir_correlativas(lista_t* correlativas){
    char* linea_correlativas = 0;
    if(lista_vacia(correlativas))
        return SIN_CORRELATIVAS;
    lista_iterador_t* iterador = lista_iterador_crear(correlativas);
    while(lista_iterador_tiene_siguiente(iterador)){
        char* codigo = lista_iterador_elemento_actual(iterador);
        char auxiliar[MAX_STRING];
        sprintf(auxiliar, "%s%s", codigo, SEPARADOR_CORRELATIVAS);
        strcat(linea_correlativas, auxiliar);
    }
    lista_iterador_destruir(iterador);
    return linea_correlativas;
}

/****************************       FUNCIONES MATERIAS.H       ***********************************/

//materias.h
hash_t* carrera_crear(char* ruta_archivo){
    hash_t* carrera = hash_crear(liberar_materia, 15);
    if(!carrera) return NULL;
    FILE* plan_de_estudios = fopen(ruta_archivo, LECTURA);
    if(!plan_de_estudios){
        hash_destruir(carrera);
        return NULL;
    }
    int estado = cargar_materias_carrera(plan_de_estudios, carrera);
    fclose(plan_de_estudios);
    if(estado == ERROR){
        hash_destruir(carrera);
        return NULL;
    }
    return carrera;
}
//materias.h
void mostrar_materia(interfaz_t* interfaz, void* carrera, void* codigo_materia){
    if(!interfaz || !carrera || !codigo_materia){
        informacion_imprimir_linea(interfaz, ROJO, "   ERROR"); 
        return;
    } 
    materia_t* materia = hash_obtener((hash_t*)carrera, (char *) codigo_materia);
    if(!materia){
        informacion_imprimir_linea(interfaz, ROJO, "   ERROR"); 
        return;
    } 
    informacion_imprimir_linea(interfaz, BLANCO, linea_materia(materia, (char *) codigo_materia));
    informacion_imprimir_linea(interfaz, BLANCO, "");
    imprimir_linea_estado(interfaz, materia);
    informacion_imprimir_linea(interfaz, BLANCO, "");
    informacion_imprimir_linea(interfaz, AMARILLO, "     Correlativas:");
    informacion_imprimir_linea(interfaz, BLANCO, "");
    if(lista_vacia(materia->codigos_correlativas)){
        informacion_imprimir_linea(interfaz, BLANCO, "NO tiene correlativas"); 
        return;   
    }
    mostrar_correlativas(interfaz, carrera, materia->codigos_correlativas);
}
//materias.h
void mostrar_carrera(interfaz_t* interfaz, void* carrera, void* aux){
    if(!interfaz || !carrera){
        informacion_imprimir_linea(interfaz, ROJO, "   ERROR"); 
        return;
    } 
    hash_iterador_t* iterador = hash_iterador_crear((hash_t*)carrera);
    size_t aprobadas = 0;
    while(hash_iterador_tiene_siguiente(iterador)){
        const char* codigo = hash_iterador_siguiente(iterador);
        if(codigo){
            materia_t* actual = hash_obtener((hash_t*)carrera, codigo);
            if(!actual)
                informar_error(interfaz, (char *)codigo);
            else{
                char* info_materia = linea_materia(actual, (char *) codigo);
                if(actual->estado == MATERIA_APROBADA){
                    informacion_imprimir_linea(interfaz, VERDE, info_materia);
                    aprobadas ++;
                }
                if(actual->estado == MATERIA_CURSADA)
                    informacion_imprimir_linea(interfaz, AMARILLO, info_materia);
                if(actual->estado == MATERIA_HABILITADA)
                    informacion_imprimir_linea(interfaz, CELESTE, info_materia);
                if(actual->estado == MATERIA_PENDIENTE)
                    informacion_imprimir_linea(interfaz, BLANCO, info_materia);
                informacion_imprimir_linea(interfaz, ROJO, "ESTADO ERRONEO");
            }
        }
    }
    hash_iterador_destruir(iterador);
    informar_carrera_realizada(interfaz, aprobadas, hash_cantidad((hash_t*)carrera));
}
//materias.h
void mostrar_materias_habilitadas(interfaz_t* interfaz, void* carrera, void* aux){
    if(!interfaz || !carrera){
        informacion_imprimir_linea(interfaz, ROJO, "   ERROR"); 
        return;
    } 
    hash_iterador_t* iterador = hash_iterador_crear((hash_t*)carrera);
    while(hash_iterador_tiene_siguiente(iterador)){
        const char* codigo = hash_iterador_siguiente(iterador);
        if(codigo){
            materia_t* actual = hash_obtener((hash_t*)carrera, codigo);
            if(!actual)
                informar_error(interfaz, (char*) codigo);
            else{
                char* info_materia = linea_materia(actual, (char*) codigo);
                if(actual->estado == MATERIA_HABILITADA)
                    informacion_imprimir_linea(interfaz, BLANCO, info_materia);
                informacion_imprimir_linea(interfaz, ROJO, "MATERIA CON ESTADO ERRONEO");
            }
        }
    }
    hash_iterador_destruir(iterador);
}
//materias.h
void mostrar_materias_aprobadas(interfaz_t* interfaz, void* carrera, void* aux){
    if(!interfaz || !carrera){
        informacion_imprimir_linea(interfaz, ROJO, "   ERROR"); 
        return;
    } 
    size_t aprobadas = 0;
    int notas = 0;
    hash_iterador_t* iterador = hash_iterador_crear((hash_t*)carrera);
    while(hash_iterador_tiene_siguiente(iterador)){
        const char* codigo = hash_iterador_siguiente(iterador);
        if(codigo){
            materia_t* actual = hash_obtener((hash_t*)carrera, codigo);
            if(!actual)
                informar_error(interfaz, (char *)codigo);
            else{
                char* info_materia = linea_materia(actual, (char*)codigo);
                if(actual->estado == MATERIA_APROBADA){
                    informacion_imprimir_linea(interfaz, BLANCO, info_materia);
                    aprobadas++;
                    notas += actual->nota;
                }
                informacion_imprimir_linea(interfaz, ROJO, "ESTADO ERRONEO");
            }
        }
    }
    hash_iterador_destruir(iterador);
    float promedio = (float)notas/(float)aprobadas;
    informar_promedio(interfaz, promedio);
}
//materias.h
char* pedir_codigo(interfaz_t* interfaz, hash_t* carrera){
    char* codigo = interfaz_pedir_string(interfaz, "el código de la materia");
    while(!hash_contiene(carrera, codigo)){
        interfaz_reportar_error(interfaz, "El código ingresado es incorrecto");
        codigo = interfaz_pedir_string(interfaz, "el código de la materia");
    }
    return codigo;
}
//materias.h
void pedir_dato_materia(interfaz_t* interfaz, hash_t* carrera, char* codigo, size_t tipo_dato){
    materia_t* materia = hash_obtener(carrera, codigo);
    if(!materia) return;
    if(tipo_dato == PEDIR_NOTA){
        char* nota = interfaz_pedir_string(interfaz, "la nota");
        while(!nota_valida(nota)){
            interfaz_reportar_error(interfaz, "Nota ingresada inválida");
            nota = interfaz_pedir_string(interfaz, "la nota");
        }
        materia->nota = atoi(nota);
    }else if(tipo_dato == PEDIR_ESTADO){
        char* estado = interfaz_pedir_string(interfaz, "el estado ('A' aprobada ; 'C' cursada ; 'H' Habilitada; 'P' Pendiente)");
        while(strlen(estado) > 1 || !estado_valido(estado[1])){
            interfaz_reportar_error(interfaz, "Nota ingresada inválida");
            estado = interfaz_pedir_string(interfaz, "el estado ('A' aprobada ; 'C' cursada ; 'H' Habilitada; 'P' Pendiente)");
        }
        materia->estado = estado[1];
    }    
}
//materias.h
void actualizar_carrera(hash_t* carrera){
    hash_iterador_t* iterador = hash_iterador_crear((hash_t*)carrera);
    while(hash_iterador_tiene_siguiente(iterador)){
        const char* codigo = hash_iterador_siguiente(iterador);
        if(codigo){
            materia_t* actual = hash_obtener((hash_t*)carrera, codigo);
            if(correlativas_aprobadas(carrera, actual->codigos_correlativas))
                actual->estado = MATERIA_HABILITADA;
        }
    }
    hash_iterador_destruir(iterador);
}
//materias.h
int guardar_archivo(hash_t* carrera, char* ruta_archivo){
    FILE* archivo = fopen("auxiliar.csv", "w");
    if(!archivo)    return ERROR;
    hash_iterador_t* iterador = hash_iterador_crear((hash_t*)carrera);
    while(hash_iterador_tiene_siguiente(iterador)){
        const char* codigo = hash_iterador_siguiente(iterador);
        if(codigo){
           materia_t* actual = hash_obtener((hash_t*)carrera, codigo);
           if(actual){
                char * correlativas = escribir_correlativas(actual->codigos_correlativas);
                fprintf(archivo, FORMATO_W, (char *)codigo, actual->nombre, actual->estado, actual->nota, correlativas); 
           }
        }
    }
    hash_iterador_destruir(iterador);
    return EXITO;
}
