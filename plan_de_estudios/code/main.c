#include "materias.h"
#include "../../toolbox/code/tools.h"
#include "../../toolbox/code/interfaz.h"

#define AYUDA "--help"
#define MAX_BARRA 10

const int MAX_INTERFAZ               = 80;
const int MARGEN_INTERFAZ            = 20;
const int ESPACIO_INTERFAZ           = 20;

const int PROGRAMA_INICIO            = 0;
const char OPCION_MODIFICAR          = 'A';
const char OPCION_MOSTRAR            = 'B';
const char OPCION_ARCHIVO            = 'C';

const int PROGRAMA_MODIFICAR         = 1;
const char OPCION_AGREGAR            = 'A';
const char OPCION_ELIMINAR           = 'B';
const char OPCION_MODIFICAR          = 'C';
const char OPCION_BUSCAR             = 'D';

const int PROGRAMA_MOSTRAR           = 2;
const char OPCION_LISTAR_CARRERA     = 'A';
const char OPCION_LISTAR_APROBADAS   = 'B';
const char OPCION_LISTAR_HABILITADAS = 'C';

const int PROGRAMA_SALIR = 3;

typedef struct programa{
    int modo_programa;
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
int inicializar_interfaz(interfaz_t* interfaz){
    int estado = EXITO;
    estado = menu_insertar(interfaz, "MENU INICIO", ROJO);
    if(estado == ERROR) return ERROR;
    estado = menu_insertar(interfaz, "MODIFICAR ARCHIVO", CYAN);
    if(estado == ERROR) return ERROR;
    estado = menu_insertar(interfaz, "MOSTRAR MATERIAS", ROSA);
    if(estado == ERROR) return ERROR;
    cargar_opcion(interfaz, 0, OPCION_MODIFICAR, "Modifiar materias del archivo");
    cargar_opcion(interfaz, 0, OPCION_MOSTRAR, "Mostrar por pantalla materias");
    cargar_opcion(interfaz, 0, OPCION_ARCHIVO, "Ingresar la ruta del archivo de materias");
    cargar_opcion(interfaz, 1, OPCION_AGREGAR, "Agregar nueva materia a la carrera");
    cargar_opcion(interfaz, 1, OPCION_ELIMINAR, "Eliminar materia de la carrera");
    cargar_opcion(interfaz, 1, OPCION_MODIFICAR, "Modificar estado o nota de una materia");
    cargar_opcion(interfaz, 1, OPCION_BUSCAR, "Buscar una materia de la carrera (por codigo)");
    cargar_opcion(interfaz, 2, OPCION_LISTAR_CARRERA, "Mostrar todas las materias de la carrera");
    cargar_opcion(interfaz, 2, OPCION_LISTAR_APROBADAS, "Mostrar las materias aprobadas");
    cargar_opcion(interfaz, 2, OPCION_LISTAR_HABILITADAS, "Mostrar las materias habiles para cursar");
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
    programa->interfaz = interfaz_crear(MAX_INTERFAZ, MARGEN_INTERFAZ, ESPACIO_INTERFAZ);
    if(!programa->interfaz){
        programa_destruir(programa);
        return NULL;
    }
    int estado = inicializar_interfaz(programa->interfaz);
    if(estado == ERROR){
        programa_destruir(programa);
        return NULL;
    }
    programa->modo_programa = PROGRAMA_INICIO;
    programa->carrera = NULL;
    return programa;
}
/*
*
* Pre : 
* Post:
*/
void pedir_materia(carrera_t* carrera, materia_t* materia){

}
/*
*
* Pre : 
* Post:
*/
void pedir_codigo(carrera_t* carrera, int* codigo_materia){

}
/*
*
* Pre : 
* Post:
*/
int ejecutar_modificacion (programa_t* programa){
    menu_mostrar(programa->interfaz, PROGRAMA_MODIFICAR);
    if(interfaz_estado(programa->interfaz) == OPCION_AGREGAR){
        materia_t materia;
        pedir_materia(carrera, &materia); 
        estado = agregar_materia(carrera, materia);
    }else if(interfaz_estado(programa->interfaz)== OPCION_MODIFICAR){
        int codigo_materia;
        pedir_codigo(carrera, &codigo_materia);
        estado = modificar_materia(carrera, codigo_materia);
    }else if(interfaz_estado(programa->interfaz) == OPCION_ELIMINAR){
        int codigo_materia;
        pedir_codigo(carrera, &codigo_materia); 
        estado = eliminar_materia(carrera, codigo_materia);
    }

    if(estado != ERROR)
        guardar_archivo(carrera, ruta_archivo);

    return estado;
}

/*
* Muestra una materia por pantalla según su estado
* Pre : Carrera creada
* Post:
*/
bool mostrar_materias(materia_t* materia, void* contador){
    if(materia->info.estado == APROBADA){
        printf( VERDE "%s %i - %s : %i " RESET "\n", TILDE, 
                                                   materia->info.codigo, 
                                                   materia->info.nombre, 
                                                   materia->info.nota);
        (*(size_t*)contador) ++;
    }else if (materia->info.estado == CURSADA){
        printf(AMARILLO "- %i - %s : %i (parcial) " RESET "\n", materia->info.codigo, 
                                                               materia->info.nombre, 
                                                               materia->info.nota);
    }else if (materia->info.estado == HABILITADA){
        printf(". %i - %s \n", materia->info.codigo, materia->info.nombre);
    }else if (materia->info.estado == PENDIENTE){
        printf(NEGRO ". %i - %s" RESET "\n", CRUZ, materia->info.codigo, materia->info.nombre);
    }else{
        printf(CYAN ". %i-%s " ROJO "! TIENE UN ESTADO INVÁLIDO" RESET "\n",materia->info.codigo, 
                                                                             materia->info.nombre);
    }
    return true;
}

/*
* Muestra las materias aprobadas y el promedio entre todas las aprobadas
* Pre : Necesita la carrera creada
* Post:
*/
bool mostrar_aprobadas(materia_t* materia, void* contador){
    if(materia->info.estado == APROBADA){
        (*(size_t *)contador) ++;
        printf( VERDE "%s %i - %s : %i " RESET "\n", TILDE, 
                                                   materia->info.codigo, 
                                                   materia->info.nombre, 
                                                   materia->info.nota);
                        
    }
    return true; 
}

/*
* Muestra las materias que se pueden cursar
* Pre : Necesita la carrera creada
* Post:
*/
bool mostrar_habilitadas(materia_t* materia, void* contador){
    if (materia->info.estado == HABILITADA)
        printf(". %i-%s \n", materia->info.codigo, materia->info.nombre);
    return true;
}

/*
* 
* Pre :
* Post:
*/
int ejecutar_mostrar(programa_t* programa){
    menu_mostrar(programa->interfaz, PROGRAMA_MOSTRAR);
    if(interfaz_estado(programa->interfaz) == OPCION_BUSCAR){
        size_t codigo_materia = pedir_numero(programa->interfaz);
        materia_t* materia = buscar_materia(carrera, codigo_materia);
        while(!materia){
            reportar_error("Código de materia incorrecto");
            codigo_materia = pedir_numero(programa->interfaz);
            materia = buscar_materia(carrera, codigo_materia);
        }
        mostrar_materia(materia);
        return EXITO;
    }
    if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_CARRERA){
        size_t materias_aprobadas = 0;
        iterrar_carrera(carrera, mostrar_materias, (void*)&materias_aprobadas);
        print_porcentage_bar(materias_aprobadas, carrera->cantidad_materias);
    }else if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_APROBADAS){
        size_t materias_aprobadas = 0;
        iterrar_carrera(carrera, mostrar_aprobadas, (void*)&materias_aprobadas);
        print_porcentage_bar(materias_aprobadas, carrera->cantidad_materias);
        //promedio
    }else if(interfaz_estado(programa->interfaz) == OPCION_LISTAR_HABILITADAS){
        iterrar_carrera(carrera, mostrar_habilitadas, NULL);
    }
    
    return EXITO;
}

int main(int argc, char* argv[]){

    if (argc == 1){
        if(strcmp(argv[1], AYUDA) == 0){
            mostrar_ayuda();
            return EXITO;
        }else
            warning("el comando ingresado");
    }
    programa_t* programa = programa_crear();
    if(!programa){
        warning("la creación del programa");
        return ERROR;
    }

    while(interfaz_estado(programa->interfaz) != OPCION_ARCHIVO){
        menu_mostrar(programa->interfaz, PROGRAMA_INICIO);
        if(interfaz_estado(programa->interfaz) != OPCION_ARCHIVO)
            reportar_error("Primero debe ingresarse el archivo");
    }
    programa->ruta_archivo = pedir_archivo_csv(programa->interfaz);
    int carga = cargar_materias(programa->carrera, programa->ruta_archivo);
    if(carga == ERROR){
        programa_destruir(programa);
        printf( ROJO "%s El programa ha terminado por un ERROR" RESET "\n", CRUZ);
        return ERROR;
    }
    menu_eliminar_opcion(programa->interfaz, PROGRAMA_INICIO, OPCION_ARCHIVO);
    menu_mostrar(programa->interfaz, PROGRAMA_INICIO);
    while(interfaz_estado(programa->interfaz) != OPCION_SALIR && programa->modo_programa != ERROR){
        if(interfaz_estado(programa->interfaz) == OPCION_VOLVER)
            menu_mostrar(programa->interfaz, PROGRAMA_INICIO);
        if(interfaz_estado(programa->interfaz) == OPCION_MODIFICAR)
            ejecutar_modificacion(programa);
        if(interfaz_estado(programa->interfaz) == OPCION_MOSTRAR)
            ejecutar_mostrar(programa);
    }
    if(programa->modo_programa == ERROR){
        programa_destruir(programa);
        printf( ROJO "%s El programa ha terminado por un ERROR" RESET "\n", CRUZ);
        return ERROR;
    }     
    programa_destruir(programa);
    return EXITO;
}