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
void mostrarTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant);
void tareasRealizadas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant);
void liberarMemoria(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant);
void buscarTarea(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant, char *keyword);




int main(){
    int cant;
    char keyword[50];
    Tarea **TareasPendientes = NULL, **TareasRealizadas = NULL;
    printf("cuantas tareas desea cargar:\n");
    scanf("%d",&cant);
    TareasPendientes = malloc(sizeof(Tarea*)*cant);
    TareasRealizadas = malloc(sizeof(Tarea*)*cant);
    for(int i = 1; i < cant; i++){
        TareasRealizadas[i] = NULL; //Inicializar en NULL para que no muestre basura en caso de estar vacio
    }
    cargarTareas(TareasPendientes, cant);
    tareasRealizadas(TareasPendientes, TareasRealizadas, cant);
    mostrarTareas(TareasPendientes, TareasRealizadas, cant);
    puts("Ingrese una palabra");
    fflush(stdin);
    scanf("%s", &keyword);
    buscarTarea(TareasPendientes, TareasRealizadas, cant, keyword);
    liberarMemoria(TareasPendientes, TareasRealizadas, cant);
    
}

void cargarTareas(Tarea **TareasPendientes, int cant){
    char buff[50];
    int i;
    srand(time(NULL));
    for(i = 0; i<cant; i++){
        TareasPendientes[i] = malloc(sizeof(Tarea));
        TareasPendientes[i]->TareaID = i+1;
        printf("Ingrese la descripcion de la tarea %d\n", i+1);
        fflush(stdin);
        gets(buff);
        TareasPendientes[i]->Descripcion = malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(TareasPendientes[i]->Descripcion, buff);
        TareasPendientes[i]->Duracion = rand()%100+10;
    }
}

void mostrarTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant){
    printf("***Tareas Pendientes***\n");
    for(int i = 0; i<cant; i++){ //controlo que el lugar adonde apunta no esté vacio
        if(TareasPendientes[i] != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes[i]->TareaID, TareasPendientes[i]->Descripcion, TareasPendientes[i]->Duracion);
        }
    } 
    printf("***Tareas Realizadas***\n");
    for(int j = 0; j < cant; j++){
        if(TareasRealizadas[j] != NULL){ //controlo que el lugar adonde apunta no esté vacio
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasRealizadas[j]->TareaID, TareasRealizadas[j]->Descripcion, TareasRealizadas[j]->Duracion);
        }
    }
}

void tareasRealizadas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant){
    int i, j = 0;
    for(i = 0; i < cant; i++){
        int realz = 0;
        printf("Realizo la tarea %d (1 Si, 0 No)\n", i+1);
        scanf("%d", &realz);
        if(realz == 1){
            TareasRealizadas[j] = TareasPendientes[i]; //Apunto ambos punteros a la misma posicion
            TareasPendientes[i]= NULL;
            j++;
        }
    }
}

void liberarMemoria(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant){
    int i = 0;
    for(i = 0; i < cant; i++){
        free(TareasPendientes[i]->Descripcion);
        free(TareasRealizadas[i]->Descripcion);
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    free(TareasPendientes);
    free(TareasPendientes);
}

void buscarTarea(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant, char *keyWord){
    int i;
    char *tareaDescripcion1;
    char *tareaDescripcion2;
    for(i = 0; i<cant; i++){
        if(TareasRealizadas[i] != NULL){
            tareaDescripcion1 = strstr(TareasRealizadas[i]->Descripcion, keyWord);
        }
        if(TareasPendientes[i] != NULL){
            tareaDescripcion2 = strstr(TareasPendientes[i]->Descripcion, keyWord);
        }
        printf("\nasd");
        if(tareaDescripcion1 != NULL){
            printf("%s", tareaDescripcion1);
        }
        if(tareaDescripcion2 != NULL){
            printf("%s", tareaDescripcion2);
        }
    }
}