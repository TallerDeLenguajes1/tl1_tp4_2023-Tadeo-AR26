#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; /// entre 10-100
} typedef Tarea;

void cargarTareas(Tarea **TareasPendientes, int cant);
void mostrarTareas(Tarea **TareasPendientes, int cant);



int main(){
    int cant;
    Tarea **TareasPendientes = NULL, **TareasRealizadas = NULL;
    printf("cuantas tareas desea cargar:\n");
    scanf("%d",&cant);
    TareasPendientes = malloc(sizeof(Tarea*)*cant);
    TareasRealizadas = malloc(sizeof(Tarea*)*cant);
    cargarTareas(TareasPendientes, cant);
    printf("asda");
    mostrarTareas(TareasPendientes, cant);
    
}

void cargarTareas(Tarea **TareasPendientes, int cant){
    char buff[50];
    int i;
    srand(time(NULL));
    for(i = 0; i<cant; i++){
        TareasPendientes[i] = malloc(sizeof(Tarea)*cant);
        TareasPendientes[i]->TareaID = i+1;
        printf("Ingrese la descripcion de la tarea %d\n", i+1);
        fflush(stdin);
        gets(buff);
        TareasPendientes[i]->Descripcion = malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(TareasPendientes[i]->Descripcion, buff);
        TareasPendientes[i]->Duracion = rand()%100+10;
    }
}

void mostrarTareas(Tarea **TareasPendientes, int cant){
    printf("asd");
    for(int i = 0; i<cant; i++){
        printf("Tarea Numero: %d\n", TareasPendientes[i]->TareaID);
        printf("Descripcion: %s\n", TareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n", TareasPendientes[i]->Duracion);
    }
}