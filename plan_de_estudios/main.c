#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "materias.h"

#define AYUDA "--help"
#define AYUDA_CSV "--csv"

const int AGREGAR = 0;
const int BUSCAR = 1;
const int MODIFICAR = 2;
const int LISTAR_APROB = 3;
const int LISTAR_HAB = 4;
const int PROMEDIO = 5;
const int SALIR = -1;

/*
*Le pregunta al usuario que quiere hacer con el programa
*Devuelve un numero correspondiente al modo (por constantes)
*/
int determinar_modo(){
    return SALIR;
}

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

    int modo_programa = determinar_modo();
    // carrera_t* carrera = crear_carrera(argv[1]);   
    
    if (modo_programa == SALIR)
        printf( VERDE "Ha salido sin realizar nada" RESET "\n");

    return 0;
}