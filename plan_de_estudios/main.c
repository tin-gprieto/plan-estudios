#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "materias.h"

#define AYUDA "--help"
#define AYUDA_CSV "--csv"
#define MAX_RUTA 50

const int AGREGAR = 1;
const int ELIMINAR = 2;
const int MODIFICAR = 3;
const int BUSCAR = 4;
const int LISTAR_CARRERA = 5;
const int LISTAR_APROBADAS = 6;
const int LISTAR_HABILITADAS = 7;
const int SALIR = 0;

const char SI = 's';
const char NO = 'n';

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
    printf("                   ___________________________________________________________\n");
    printf("                  |                                                           |\n");
    printf("                  |" CYAN "                  FUNCIONES DEL PROGRAMA                   " RESET "|\n");
    printf("                  |                                                           |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - AGREGAR una nueva materia o CREAR un nuevo archivo |\n", AGREGAR);
    printf("                  |" AMARILLO "( %i )" RESET " - ELIMINAR una materia                               |\n", ELIMINAR);
    printf("                  |" AMARILLO "( %i )" RESET " - MODIFICAR una materia                              |\n", MODIFICAR);
    printf("                  |" AMARILLO "( %i )" RESET " - BUSCAR una materia                                 |\n", BUSCAR);
    printf("                  |                                                           |\n");
    printf("                  |" CYAN "                     MOSTRAR MATERIAS                      " RESET "|\n");
    printf("                  |                                                           |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - LISTA COMPLETA                                     |\n", LISTAR_CARRERA);
    printf("                  |" AMARILLO "( %i )" RESET " - APROBADAS                                          |\n", LISTAR_APROBADAS);
    printf("                  |" AMARILLO "( %i )" RESET " - HABILITADAS PARA CURSAR                            |\n", LISTAR_HABILITADAS);
    printf("                  |                                                           |\n");
    printf("                  |" CYAN "                  ----------------------                   " RESET "|\n");
    printf("                  |                                                           |\n");
    printf("                  |" AMARILLO "( %i )" RESET " - SALIR del programa                                 |\n", SALIR);
    printf("                  |___________________________________________________________|\n\n");
    
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
bool si_continua(int* modo){
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
/*
*Corre el programa según el modo
*Pre: Modo preguntado al usuario, carrera creada
*Post: 0 si realizó todo correctamente, ERROR si hubo un problema
*/
int ejecutar_programa(int modo_programa, carrera_t* carrera){
    if(modo_programa == AGREGAR){
        printf(VERDE "AGREGAR" RESET "\n");    
    }else if(modo_programa == ELIMINAR){
        printf(VERDE "ELIMINAR" RESET "\n");
    }else if(modo_programa == MODIFICAR){
        printf(VERDE "MODIFICAR" RESET "\n");
    }else if(modo_programa == BUSCAR){
        printf(VERDE "BUSCAR" RESET "\n");
    }else if(modo_programa == LISTAR_CARRERA){
        printf(VERDE "CARRERA" RESET "\n");
    }else if(modo_programa == LISTAR_APROBADAS){
        printf(VERDE "APROBADAS" RESET "\n");
    }else if(modo_programa == LISTAR_HABILITADAS){
        printf(VERDE "HABILITADAS" RESET "\n");
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
        return 0;
    }

    if (strcmp(argv[1], AYUDA_CSV) == 0){
        mostrar_csv_ayuda();
        return 0;
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
        estado = ejecutar_programa(modo_programa, carrera);
        if (estado != ERROR)
            if(si_continua(&modo_programa))
                determinar_modo(&modo_programa);
    }

    liberar_carrera(carrera);

    if(estado == ERROR){
        printf( ROJO "El programa ha terminado por un ERROR" RESET "\n");
        return ERROR;
    }   
    
    printf( VERDE "Ha salido exitosamente del programa" RESET "\n");
    return 0;
}