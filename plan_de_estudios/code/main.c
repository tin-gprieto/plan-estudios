#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "materias.h"
#include "../toolbox/tools.h"

#define AYUDA "--help"
#define AYUDA_CSV "--csv"
#define MAX_RUTA 50
#define MAX_BARRA 10

const int AGREGAR = 1;
const int ELIMINAR = 2;
const int MODIFICAR = 3;
const int BUSCAR = 4;
const int LISTAR_CARRERA = 5;
const int LISTAR_APROBADAS = 6;
const int LISTAR_HABILITADAS = 7;
const int SALIR = 0;

/*
*Muestra por pantalla una ayuda básica de como ejecutar correctamente
*/
void mostrar_ayuda(){
    printf("El programa debe ejecutarse de la siguiente manera: \n");
    printf( AMARILLO "  ./carrera <ruta del archivo con las materias> " RESET "\n");
    printf("Si tiene dudas con el formato del archivo de materias: \n");
    printf( AMARILLO "   ./carrera --csv " RESET "\n\n");

}

/*
*Muestra por pantalla una ayuda sobre el archivo a leer
*/
void mostrar_csv_ayuda(){
    printf("El archivo de materias debe contar con el formato: \n");
    printf( AMARILLO "  codigo;nombre;estado;nota;correlativas " RESET "\n");
    printf("* Estado: (A) aprobada, (C) cursada, (H) habilitada para cursar, (P) pendiente \n");
    printf("* Nota: -1 si no cuenta con nota de cursada o de promoción \n");
    printf("* Correlativas: codigos de las materias, separados por '.' \n");
}
/*
* Muestra por pantalla todas las funcionalidades del programa
*/
void mostrar_menu(){
    printf("                   ___________________________________________________\n");
    printf("                  |                                                   |\n");
    printf("                  |" ROSA "               FUNCIONES DEL PROGRAMA              " RESET "|\n");
    printf("                  |" CYAN "                 ------------------                " RESET "|\n");
    printf("                  |" CYAN "               MODIFICACIÓN DE ARCHIVO             " RESET "|\n");
    printf("                  |                                                   |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - AGREGAR una nueva materia                  |\n", AGREGAR);
    printf("                  |" AMARILLO "( %i )" RESET " - ELIMINAR una materia                       |\n", ELIMINAR);
    printf("                  |" AMARILLO "( %i )" RESET " - MODIFICAR una materia                      |\n", MODIFICAR);
    printf("                  |                                                   |\n");
    printf("                  |" CYAN "                  MOSTRAR MATERIAS                 " RESET "|\n");
    printf("                  |                                                   |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - BUSCAR una materia                         |\n", BUSCAR);
    printf("                  |" AMARILLO "( %i )" RESET " - LISTA COMPLETA                             |\n", LISTAR_CARRERA);
    printf("                  |" AMARILLO "( %i )" RESET " - APROBADAS                                  |\n", LISTAR_APROBADAS);
    printf("                  |" AMARILLO "( %i )" RESET " - HABILITADAS PARA CURSAR                    |\n", LISTAR_HABILITADAS);
    printf("                  |                                                   |\n");
    printf("                  |" CYAN "                 ------------------                " RESET "|\n");
    printf("                  |                                                   |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - SALIR del programa                         |\n", SALIR);
    printf("                  |___________________________________________________|\n\n");
    
}
/*
* Chequea que el modo cumpla con alguno de los que hay
*Modo ya pedido al usuario
*/
bool modo_valido(int modo){
    return ((modo == AGREGAR)||(modo == ELIMINAR)||(modo == BUSCAR)||
    (modo == MODIFICAR)||(modo == LISTAR_CARRERA)||(modo == LISTAR_APROBADAS)||
    (modo == LISTAR_HABILITADAS)||(modo == SALIR));
}
/*
* Pide al usuario que ingrese un número válido que representa el modo
*/
void pedir_modo(int* eleccion){
    int aux;
    printf("                  Ingrese una función: ");
    scanf("%i", &aux);
    while (!modo_valido(aux)){
        printf( ROJO "                  Número inválido, igrese nuevamente... \n" RESET);
        printf("                  Ingrese una función: ");
        scanf("%i", &aux);
    }
    (*eleccion) = aux;
}

/*
*Le pregunta al usuario que quiere hacer con el programa
*Establace un numero correspondiente al modo (por constantes)
*/
void determinar_modo(int* modo){
    int eleccion;
    system("clear");
    mostrar_menu();
    pedir_modo(&eleccion);
    system("clear");
    (*modo) = eleccion;
}

/*
*Determina si la eleccion es SI ('s') o NO ('n')
*/
bool eleccion_valida(char eleccion){
    return ((eleccion == SI) || (eleccion == NO));
}
/*
*Le pregunta al usuario si desea continuar haciendo otra funcion
*Pre: Programa ya ejecutado
*Post: Verdadero si continua, Falso si no y modo = SALIR
*/
bool continua_usuario(int* modo){
    char eleccion;
    printf("              Desea continuar con el programa?[%c/%c]: ", SI, NO);
    scanf(" %c", &eleccion);
    while (!eleccion_valida(eleccion)){
        printf( ROJO "              Instrucción inválida, igrese nuevamente... \n" RESET);
        printf("              Desea continuar con el programa?[%c/%c]: ", SI, NO);
        scanf(" %c", &eleccion);
    }

    if (eleccion == NO){
        *modo = SALIR;
        return false;
    }
    return true;
}


void pedir_materia(carrera_t* carrera, materia_t* materia){

}

void pedir_codigo(carrera_t* carrera, int* codigo_materia){

}

int ejecutar_modificacion (int modo, carrera_t* carrera, char* ruta_archivo){
    int estado;

    if(modo == AGREGAR){
        materia_t materia;
        pedir_materia(carrera, &materia); 
        estado = agregar_materia(carrera, materia);
    }else if(modo==MODIFICAR){
        int codigo_materia;
        pedir_codigo(carrera, &codigo_materia);
        estado = modificar_materia(carrera, codigo_materia);
    }else if(modo == ELIMINAR){
        int codigo_materia;
        pedir_codigo(carrera, &codigo_materia); 
        estado = eliminar_materia(carrera, codigo_materia);
    }

    if(estado != ERROR)
        guardar_archivo(carrera, ruta_archivo);

    return estado;
}

/*
*Muestra una materia por pantalla según su estado
*Pre: Carrera creada
*/
bool mostrar_materias(materia_t* materia, void* contador){
    if(materia->info.estado == APROBADA){
        printf( VERDE "%s %i-%s : %i " RESET "\n", TILDE, 
                                                   materia->info.codigo, 
                                                   materia->info.nombre, 
                                                   materia->info.nota);
        (*(size_t*)contador) ++;
    }else if (materia->info.estado == CURSADA){
        printf(AMARILLO "- %i-%s : %i (parcial) " RESET "\n", materia->info.codigo, 
                                                               materia->info.nombre, 
                                                               materia->info.nota);
    }else if (materia->info.estado == HABILITADA){
        printf(". %i-%s \n", materia->info.codigo, materia->info.nombre);
    }else if (materia->info.estado == PENDIENTE){
        printf(ROJO "%s %i-%s" RESET "\n", CRUZ, materia->info.codigo, materia->info.nombre);
    }else{
        printf(CYAN ". %i-%s " ROJO "! TIENE UN ESTADO INVÁLIDO" RESET "\n",materia->info.codigo, 
                                                                             materia->info.nombre);
    }
    return true;
}


/*
* Muestra las materias aprobadas y el promedio entre todas las aprobadas
* Necesita la carrera creada
*/
bool mostrar_aprobadas(materia_t* materia, void* contador){
    if(materia->info.estado == APROBADA){
        (*(size_t *)contador) ++;
        printf( VERDE "%s %i-%s : %i " RESET "\n", TILDE, 
                                                   materia->info.codigo, 
                                                   materia->info.nombre, 
                                                   materia->info.nota);
                        
    }
    return true; 
}

/*
* Muestra las materias que se pueden cursar
* Necesita la carrera creada
*/
bool mostrar_habilitadas(materia_t* materia, void* contador){
    if (materia->info.estado == HABILITADA)
        printf(". %i-%s \n", materia->info.codigo, materia->info.nombre);
    return true;
}

int ejecutar_mostrar(int modo, carrera_t* carrera){

    if(modo == BUSCAR){
        int codigo_materia;
        pedir_codigo(carrera, &codigo_materia);
        materia_t* materia = buscar_materia(carrera, codigo_materia);
        if(!materia)
            return ERROR;
        return EXITO;
    }

    if(modo == LISTAR_CARRERA){
        size_t materias_aprobadas = 0;
        iterrar_carrera(carrera, mostrar_materias, (void*)&materias_aprobadas);
        print_porcentage_bar(materias_aprobadas, carrera->cantidad_materias);
    }else if(modo == LISTAR_APROBADAS){
        size_t materias_aprobadas = 0;
        iterrar_carrera(carrera, mostrar_aprobadas, (void*)&materias_aprobadas);
        print_porcentage_bar(materias_aprobadas, carrera->cantidad_materias);
        //promedio
    }else if(modo == LISTAR_HABILITADAS){
        iterrar_carrera(carrera, mostrar_habilitadas, NULL);
    }
    
    return EXITO;
}

/*
*Determina si el modo es una modificacion de archivo
*/
bool es_modificacion(int modo){
    return ((modo == AGREGAR)||(modo == ELIMINAR)||(modo == MODIFICAR)); 
}
/*
*Corre el programa según el modo
*Pre: Modo preguntado al usuario, carrera creada
*Post: 0 si realizó todo correctamente, ERROR si hubo un problema
*/
int ejecutar_programa(int modo, carrera_t* carrera, char* ruta_archivo){
    
    if(es_modificacion(modo)){
        return ejecutar_modificacion(modo, carrera, ruta_archivo);
    }else{
        return ejecutar_mostrar(modo, carrera);
    }
    return 0;
}

int main(int argc, char* argv[]){

    if (argc == 1){
        printf(ROJO "NO ingresaste ningún comando. '--help' para ayuda" RESET "\n");
        return ERROR;
    }
    if (strcmp(argv[1], AYUDA) == 0){
        mostrar_ayuda();
        return EXITO;
    }
    if (strcmp(argv[1], AYUDA_CSV) == 0){
        mostrar_csv_ayuda();
        return EXITO;
    }

    char ruta_archivo[MAX_RUTA];
    strcpy(ruta_archivo, argv[1]);
    int modo_programa;
    int estado = 0;
    carrera_t* carrera = NULL;
    determinar_modo(&modo_programa);
    if (modo_programa != SALIR){
        carrera = crear_carrera(ruta_archivo);
        if (!carrera)
            return ERROR;
    }
    while((modo_programa != SALIR) && (estado != ERROR)){
        estado = ejecutar_programa(modo_programa, carrera, ruta_archivo);
        if (estado != ERROR)
            if(continua_usuario(&modo_programa))
                determinar_modo(&modo_programa);
    }
    liberar_carrera(carrera);
    if(estado == ERROR){
        printf( ROJO "%s El programa ha terminado por un ERROR" RESET "\n", CRUZ);
        return ERROR;
    }     
    printf( VERDE "%s Ha salido exitosamente del programa" RESET "\n", TILDE);
    return EXITO;
}