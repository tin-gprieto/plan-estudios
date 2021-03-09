#include "../code/materias.h"

const size_t CANT_MATERIAS = 31;

bool mostrar_materias(materia_t* materia, void* contador){
    return true;
}

void probar_iteracion(){
    test_nuevo_grupo("Pruebas iteracion");
    //size_t materias_aprobadas = 0;
    //iterrar_carrera(carrera, mostrar_materias, (void*)&materias_aprobadas);
}
void probar_creacion(){
    test_nuevo_grupo("Pruebas de creación");

    carrera_t* ruta_inexistente = crear_carrera("invalido");
    test_afirmar(!ruta_inexistente, "No se puede crear una carrera con un archivo inexistente");
    liberar_carrera(ruta_inexistente);

    carrera_t* archivo_vacio = crear_carrera("test/txt/vacio.csv");
    test_afirmar(carrera_vacia(archivo_vacio), "Se crea una carrera vacía a partir de un archivo vacio");
    liberar_carrera(archivo_vacio);

    carrera_t* carrera = crear_carrera("test/txt/reducido.csv");
    test_afirmar(!carrera_vacia(carrera), "Se crea exitosamente una carrera no vacía");
    size_t materias = cantidad_materias(carrera);
    test_afirmar(materias == CANT_MATERIAS, "Se creó con la cantidad adecuada");
}

int main(){
    probar_creacion();
    probar_iteracion();
    test_mostrar_reporte();
}
