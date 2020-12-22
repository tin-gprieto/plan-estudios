#include "tools.h"
#define MAX_BAR 10
void print_array(int* array, size_t size){
    printf("    [");
    for(int i=0; i<size; i++)
        printf(" %i ", array[i]);
    printf("]\n");
}

void print_porcentage_bar(size_t quantity, size_t total){
    if(quantity > total){
        printf(ROJO " ERROR " RESET);
        return; 
    }
    float porcentage = (((float)quantity)/(float)total) * 100;
    char bar[MAX_BAR];
    for(int i = 0; i<(porcentage/10); i++)
        bar[i] = '0';

    printf ("|");
    for(int i = 0; i< MAX_BAR; i++){
        if(bar[i] == '0'){
            printf (FVERDE "  " RESET);
        }else{
            printf ("  ");
        }
            
    }
    printf ("|");
    printf("%.1f \n", porcentage);
}

void warning(const char * description){
    printf(ROJO "%s - Hubo un problema con %s" RESET "\n", CRUZ, description);
}