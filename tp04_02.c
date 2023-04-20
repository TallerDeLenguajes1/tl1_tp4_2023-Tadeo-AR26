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
Lista insertarTarea(Lista Tareas, Lista TareasPendientes);
Lista moverTarea(Lista Tareas, Lista TareasPendientes, int id);
Lista eliminarTareas(Lista Tareas);
void mostrarTareas(Lista TareasPendientes);
void buscarID(Lista Tareas, int id);
void buscarPalabra(Lista Tareas, char *keyword);
void mostrarDatos(Lista Tareas, int *cant, int *tiempo);

int main(){
    Lista Tareas, TareasPendientes, TareasRealizadas, TareasEnProceso, aux;
    int opcion, id = 1, op = 0, opd = 0, list = 0;
    char mover[2];
    Tareas = crearLista();
    TareasPendientes = crearLista();
    TareasRealizadas = crearLista();
    TareasEnProceso = crearLista();
    do{
        printf("\n***MENU***\n");
        printf("1- Crear una nueva Tarea\n");
        printf("2- Marcar tareas como realizadas\n");
        printf("3- Mostrar las Tareas\n");
        printf("4- Buscar una tarea por ID\n");
        printf("5- Buscar una tarea por palabra clave\n");
        printf("6- Finalizar Programa\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                fflush(stdin);
                Tareas = crearTarea(Tareas, id);
                id = id+1;
                break;
            case 2:
                aux = Tareas;
                while(aux != NULL){
                    printf("¿Desea marcar Tarea: %d -- Descripcion: %s -- Duracion: %d como realizada?\n", aux->T->TareaID, aux->T->Descripcion, aux->T->Duracion);
                    fflush(stdin);
                    printf("1- Si\n2- No\n");
                    scanf("%d", &op);
                    if(op == 1){
                        TareasRealizadas = insertarTarea(Tareas, TareasRealizadas);
                        aux = aux->siguiente;  
                    }
                    else{
                        TareasPendientes = insertarTarea(Tareas, TareasPendientes);
                        aux = aux->siguiente;
                    }
                }
                break;
            case 3:
                printf("Tareas\n");
                mostrarTareas(Tareas);
                printf("TareasPendientes:\n");
                mostrarTareas(TareasPendientes);
                printf("TareasRealizadas:\n");
                mostrarTareas(TareasRealizadas);
                break;
            case 4:
                printf("Ingrese un ID para buscar\n");
                int id;
                fflush(stdin);
                scanf("%d", &id);
                buscarID(Tareas, id);
                break;
            case 5:
                printf("Ingrese una palabra clave\n");
                char keyword[50];
                scanf("%s", &keyword);
                buscarPalabra(Tareas, keyword);
                break;
            case 6:
                while(mover != "n"){
                    printf("Tareas\n");
                    mostrarTareas(Tareas);
                    printf("TareasPendientes:\n");
                    mostrarTareas(TareasPendientes);
                    printf("TareasRealizadas:\n");
                    mostrarTareas(TareasRealizadas);
                    printf("Ingrese un ID para seleccionar una tarea\n");
                    scanf("%d", &id);
                    printf("Operacion:\n1- Mover Tarea\n2- Eliminar Tarea\n 3-Nada\n");
                    scanf("%d", &opd);
                    switch(opd){
                        case 1:
                            printf("A qué lista desea moverla?\n1- Pendientes\n2- Realizadas\n3-En Proceso\n");
                            switch(list){
                                case 1:
                                    TareasPendientes = moverTarea(Tareas, TareasPendientes, id);
                                    break;
                                case 2:
                                    TareasRealizadas = moverTarea(Tareas, TareasRealizadas, id);
                                    break;
                                case 3:
                                    TareasEnProceso = moverTarea(Tareas, TareasRealizadas, id);
                                    break;
                            }
                            break;
                        case 2:
                            printf("Eliminar Tarea");
                    }
                    printf("Desea continuar [y/n]");
                    scanf("%c", &mover);
                }
        }
    }while(opcion != 7);

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

void buscarID(Lista Tareas, int id){
    while(Tareas != NULL){
        if(Tareas->T->TareaID == id){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", Tareas->T->TareaID, Tareas->T->Descripcion, Tareas->T->Duracion);
            Tareas = Tareas->siguiente;
        }
        else{
            Tareas = Tareas->siguiente;
        }
    }
}


void buscarPalabra(Lista Tareas, char *keyword){
    while(Tareas != NULL){
        char *tareaDescripcion;
        tareaDescripcion = strstr(Tareas->T->Descripcion, keyword);
        if(tareaDescripcion != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", Tareas->T->TareaID, Tareas->T->Descripcion, Tareas->T->Duracion);
            Tareas = Tareas->siguiente;
        }
        else{
            Tareas = Tareas->siguiente;
        }
    }
}

Lista insertarTarea(Lista Tareas, Lista TareasPendientes){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->T = malloc(sizeof(struct Tarea));
    nuevo->T->Descripcion = Tareas->T->Descripcion;
    nuevo->T->Duracion = Tareas->T->Duracion;
    nuevo->T->TareaID = Tareas->T->TareaID;
    nuevo->siguiente = TareasPendientes;
    TareasPendientes = nuevo;
    
    return TareasPendientes;
}

void mostrarDatos(Lista Tareas, int *cant, int *tiempo){
    *cant = 0;
    *tiempo = 0;
    while(Tareas != NULL){
        *cant = *cant+1;
        *tiempo = *tiempo + Tareas->T->Duracion;
        Tareas = Tareas->siguiente;
    }
}

Lista moverTarea(Lista Tareas, Lista TareasPendientes, int id){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->T = malloc(sizeof(struct Tarea));
    while(Tareas != NULL){
        if(Tareas->T->TareaID = id){
            nuevo->T->Descripcion = Tareas->T->Descripcion;
            nuevo->T->Duracion = Tareas->T->Duracion;
            nuevo->T->TareaID = Tareas->T->TareaID;
            nuevo->siguiente = TareasPendientes;
            TareasPendientes = nuevo;
        }
        Tareas = Tareas->siguiente;
    }
    
    return TareasPendientes;
}