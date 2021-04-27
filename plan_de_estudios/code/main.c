#include "materias.h"

#define AYUDA "--help"
#define MAX_BARRA 10

const int MAX_INTERFAZ               = 80;
const int MARGEN_INTERFAZ            = 20;
const int ESPACIO_INTERFAZ           = 20;


const size_t MENU_PRINCIPAL          = 0;
const char OPCION_LISTAR_CARRERA     = 'A';
const char OPCION_LISTAR_APROBADAS   = 'B';
const char OPCION_LISTAR_HABILITADAS = 'C';
const char OPCION_MATERIA            = 'D';
const char OPCION_MODIFICAR          = 'E';

const size_t MENU_MATERIA            = 1;
const char OPCION_ESTADO             = 'A';
const char OPCION_NOTA               = 'B';
 
const int PROGRAMA_PRINCIPAL         = 1;
const int PROGRAMA_MATERIA           = 2;
const int PROGRAMA_SALIR             = 3;

const size_t INFO_INICIO             = 0;
const size_t INFO_CARRERA            = 1;
const size_t INFO_APROBADAS          = 2;
const size_t INFO_HABILITADAS        = 3;
const size_t INFO_MATERIA            = 4;

#define CSV ".csv"

typedef struct programa{
    int estado;
    char* ruta_archivo;
    interfaz_t* interfaz;
    hash_t* carrera; 
}programa_t;

/*
* Muestra por pantalla una ayuda sobre el archivo a leer
* Pre : 
* Post:
*/
void mostrar_ayuda(){
    printf("El archivo de materias debe contar con el formato: \n");
    printf( AMARILLO "  codigo;nombre;estado;nota;correlativas " RESET "\n");
    printf("* Estado: (A) aprobada, (C) cursada, (H) habilitada para cursar, (P) pendiente \n");
    printf("* Nota: -1 si no cuenta con nota de cursada o de promoción \n");
    printf("* Correlativas: codigos de las materias, separados por '.' \n");
}

/*
*
* Pre : 
* Post:
*/
void mostrar_inicio(interfaz_t* interfaz, void* vacio, void* aux_vacio){
    informacion_imprimir_linea(interfaz, ROJO, "Para continuar debe ingresar el archivo del plan de estudios (.csv)");
}

/*
*
* Pre : 
* Post:
*/
int inicializar_interfaz(interfaz_t* interfaz){
    int estado = EXITO;

    estado = menu_insertar(interfaz, "PLAN DE ESTUDIOS");
    if(estado == ERROR) return ERROR;

    estado = menu_insertar(interfaz, "MODIFICAR MATERIA");
    if(estado == ERROR) return ERROR;

    //Menú de opciones
    menu_cargar_opcion(interfaz, MENU_PRINCIPAL, OPCION_LISTAR_CARRERA, "Mostrar todas las materias de la carrera");
    menu_cargar_opcion(interfaz, MENU_PRINCIPAL, OPCION_LISTAR_APROBADAS, "Mostrar las materias aprobadas");
    menu_cargar_opcion(interfaz, MENU_PRINCIPAL, OPCION_LISTAR_HABILITADAS, "Mostrar las materias habiles para cursar");
    menu_cargar_opcion(interfaz, MENU_PRINCIPAL, OPCION_MATERIA, "Buscar una materia de la carrera (por codigo)");
    menu_cargar_opcion(interfaz, MENU_PRINCIPAL, OPCION_MODIFICAR, "Modificar una materia de la carrera");
    
    //Menú para modificar una materia
    menu_cargar_opcion(interfaz, MENU_MATERIA, OPCION_NOTA, "Modificar nota");
    menu_cargar_opcion(interfaz, MENU_MATERIA, OPCION_ESTADO, "Modificar estado");
    
    //Menús Información
    informacion_insertar(interfaz, "REQUISITOS", mostrar_inicio);
    informacion_insertar(interfaz, "Materias de la carrera", mostrar_carrera);
    informacion_insertar(interfaz, "Materias Aprobadas", mostrar_materias_aprobadas);
    informacion_insertar(interfaz, "Materias Habilitadas para cursar", mostrar_materias_habilitadas);
    informacion_insertar(interfaz, "Materia Seleccionada", mostrar_materia);

    return estado;
}
/*
*
* Pre : 
* Post:
*/
void programa_destruir(programa_t* programa){
    if(!programa)
        return;
    interfaz_destruir(programa->interfaz);
    hash_destruir(programa->carrera);
    free(programa);
}
/*
*
* Pre : 
* Post:
*/
programa_t* programa_crear(){
    programa_t* programa = malloc(sizeof(programa_t));
    if(!programa)
        return NULL;
    programa->interfaz = interfaz_crear(set_dimension(70,20,10), set_estetica(FONDO_NEGRO, BLANCO, CELESTE));
    if(!programa->interfaz){
        programa_destruir(programa);
        return NULL;
    }
    int estado = inicializar_interfaz(programa->interfaz);
    if(estado == ERROR){
        programa_destruir(programa);
        return NULL;
    }
    programa->carrera = NULL;
    return programa;
}

/*
* 
* Pre : 
* Post: 
*/
void buscar_materia(programa_t* programa){
    programa->estado = PROGRAMA_MATERIA;
    char* codigo = pedir_codigo(programa->interfaz, programa->carrera);
    informacion_mostrar(programa->interfaz, INFO_MATERIA, programa->carrera, codigo);
    if(interfaz_estado(programa->interfaz) == OPCION_VOLVER)
        programa->estado = PROGRAMA_PRINCIPAL;
}

/*
* 
* Pre : 
* Post: 
*/
void modificar_materia(programa_t* programa){
    programa->estado = PROGRAMA_MATERIA;
    char* codigo = pedir_codigo(programa->interfaz, programa->carrera);
    while(interfaz_estado(programa->interfaz) != OPCION_SALIR && programa->estado == PROGRAMA_MATERIA){
        menu_mostrar(programa->interfaz, MENU_MATERIA);
        if(interfaz_estado(programa->interfaz) == OPCION_ESTADO)
            pedir_dato_materia(programa->interfaz, programa->carrera, codigo, PEDIR_ESTADO);
        else if(interfaz_estado(programa->interfaz) == OPCION_NOTA)
            pedir_dato_materia(programa->interfaz, programa->carrera, codigo, PEDIR_NOTA);
        else if(interfaz_estado(programa->interfaz) == OPCION_VOLVER)
            programa->estado = PROGRAMA_PRINCIPAL;
        
        if(interfaz_estado(programa->interfaz) != OPCION_SALIR && interfaz_estado(programa->interfaz) != OPCION_VOLVER)
            informacion_mostrar(programa->interfaz, INFO_MATERIA, programa->carrera, codigo);
    }
}

/*
* 
* Pre :
* Post:
*/
void ejecutar_programa(programa_t* programa){
    
    while(programa->estado == PROGRAMA_PRINCIPAL){
        menu_mostrar(programa->interfaz, MENU_PRINCIPAL);
        if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_CARRERA)
            informacion_mostrar(programa->interfaz, INFO_CARRERA, programa->carrera, NULL);
        else if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_APROBADAS)
            informacion_mostrar(programa->interfaz, INFO_APROBADAS, programa->carrera, NULL);
        else if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_HABILITADAS)
            informacion_mostrar(programa->interfaz, INFO_HABILITADAS, programa->carrera, NULL);
        else if(interfaz_estado(programa->interfaz) == OPCION_MATERIA)
            buscar_materia(programa);        
        else if(interfaz_estado(programa->interfaz) == OPCION_MODIFICAR)
            modificar_materia(programa);
        
        if(interfaz_estado(programa->interfaz) == OPCION_SALIR)
            programa->estado = PROGRAMA_SALIR;
    }
        
}

void iniciar_programa(programa_t *programa){
    informacion_mostrar(programa->interfaz, INFO_INICIO, NULL, NULL);
    programa->ruta_archivo = interfaz_pedir_archivo(programa->interfaz, CSV, "ruta del archivo");
    programa->carrera = carrera_crear(programa->ruta_archivo);
    if(!programa->carrera){
        programa_destruir(programa);
        interfaz_reportar_error(programa->interfaz, "No se pudo cargar la información de la carrera");
        programa->estado = ERROR;
    }else
        programa->estado = PROGRAMA_PRINCIPAL;
}

int main(int argc, char* argv[]){

    if (argc == 1){
        if(strcmp(argv[1], AYUDA) == 0){
            mostrar_ayuda();
            return EXITO;
        }else
            warning("EL COMANDO INGRESADO");
    }
    programa_t* programa = programa_crear();
    if(!programa){
        warning("LA CREACIÓN DEL PROGRAMA");
        return ERROR;
    }
    iniciar_programa(programa);
    if(programa->estado != ERROR)
        ejecutar_programa(programa); 

    if(programa->estado == ERROR){
        programa_destruir(programa);
        printf( ROJO "%s El programa ha terminado por un ERROR" RESET "\n", CRUZ);
        return ERROR;
    }     
    programa_destruir(programa);
    return EXITO;
}