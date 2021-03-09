#include "../code/interfaz.h"

int main(){
    interfaz_t* interfaz = interfaz_crear(70,20,10);
    if(!interfaz){
        warning("la creación del interfaz");
    }
    if(menu_insertar(interfaz, "FUNCIONES ADMINISTRATIVAS", AZUL) == ERROR){
        interfaz_destruir(interfaz);
        return ERROR;
    }
    cargar_opcion(interfaz, 0, 'A', "Primer_opcion"); 
    cargar_opcion(interfaz, 0, 'B', "Segunda_opcion"); 
    cargar_opcion(interfaz, 0, 'C', "Tercer_opcion");
    cargar_opcion(interfaz, 0, 'D', "Cuarta_opcion");
    menu_mostrar(interfaz, 0);
    printf("        Opción:     %c \n", interfaz_estado(interfaz));
    if(menu_insertar(interfaz, "FUNCIONES DE GESTION", ROJO) == ERROR){
        interfaz_destruir(interfaz);
        return ERROR;
    }
    cargar_opcion(interfaz, 1, 'A', "Primer_opcion"); 
    cargar_opcion(interfaz, 1, 'B', "Segunda_opcion"); 
    cargar_opcion(interfaz, 1, 'C', "Tercer_opcion");
    menu_mostrar(interfaz, 1);
    interfaz_destruir(interfaz);
    return 0;
}