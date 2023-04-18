#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

struct Nodo{
    Tarea *T;
    struct Nodo *siguiente;
};

typedef struct Nodo* Lista;

Lista crearLista();
Lista crearTarea(Lista TareasPendientes, int id);
void mostrarTareas(Lista TareasPendientes);

int main(){
    Lista TareasPendientes, TareasRealizadas;
    int opcion, id = 1;
    TareasPendientes = crearLista();
    do{
        printf("\n***MENU***\n");
        printf("1- Crear una nueva Tarea\n");
        printf("2- Marcar una tarea como realizada\n");
        printf("3- Mostrar las Tareas\n");
        printf("4- Buscar una tarea por ID\n");
        printf("5- Buscar una tarea por palabra clave\n");
        printf("6- Finalizar Programa\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                fflush(stdin);
                TareasPendientes = crearTarea(TareasPendientes, id);
                id = id+1;
                break;
            case 3:
                mostrarTareas(TareasPendientes);
        }
    }while(opcion != 6);

    return 0;
}

Lista crearLista(){
    Lista L;
    L = NULL;
    return L;
}

Lista crearTarea(Lista TareasPendientes, int id){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->T = malloc(sizeof(struct Tarea));
    char buff[50];
    
    nuevo->T->TareaID = id;
    printf("Ingrese una descripcion:\n");
    fflush(stdin);
    gets(buff);
    nuevo->T->Descripcion = malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(nuevo->T->Descripcion, buff);
    srand(time(NULL));
    nuevo->T->Duracion = rand()%100+10;

    nuevo->siguiente = TareasPendientes;
    TareasPendientes = nuevo;

    return TareasPendientes;
}

void mostrarTareas(Lista TareasPendientes){
    while(TareasPendientes != NULL){
        printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes->T->TareaID, TareasPendientes->T->Descripcion, TareasPendientes->T->Duracion);
        TareasPendientes = TareasPendientes->siguiente;
    }
}

