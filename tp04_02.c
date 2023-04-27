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
    Tarea T;
    struct Nodo *siguiente;
};

typedef struct Nodo* Lista;

Lista crearLista();
Lista crearTarea(Lista TareasPendientes, int num);
void marcarTareaRealizada(Lista *TareasPendientes, Lista *TareasRealizadas, int id);
void mostrarTarea(Lista Tareas);
void buscarTareaID(Lista TareasPendientes, Lista TareasRealizadas, int id);
void buscarTareaKeyword(Lista TareasPendientes, Lista TareasRealizadas, char *keyword);
void eliminarTareas(Lista Tareas, int id);

int main(){
    Lista TareasPendientes, TareasRealizadas, TareasEnProceso;
    int opcion, id, num = 1;
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
        printf("6- Borrar una Tarea\n");
        printf("7- Finalizar Programa\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                TareasPendientes = crearTarea(TareasPendientes, num);
                num = num+1;
                break;
            case 2:
                printf("Ingrese el ID de la tarea a marcar como realizada:\n");
                scanf("%d", &id);
                marcarTareaRealizada(&TareasPendientes, &TareasRealizadas, id);
                break;
            case 3:
                printf("Tareas Pendientes:\n");
                mostrarTarea(TareasPendientes);
                printf("Tareas Realizadas:\n");
                mostrarTarea(TareasRealizadas);
                printf("Tareas en Proceso\n");
                mostrarTarea(TareasEnProceso);
                break;
            case 4:
                printf("Ingrese un ID para buscar\n");
                scanf("%d", &id);
                buscarTareaID(TareasPendientes, TareasRealizadas, id);
                break;
            case 5:
                printf("Ingrese una palabra clave\n");
                char keyword[50];
                scanf("%s", &keyword);
                buscarTareaKeyword(TareasPendientes, TareasRealizadas, keyword);
                break;
            case 6:
                printf("Ingrese un ID para eliminar una tarea");
                scanf("%d", &id);
                eliminarTareas(TareasPendientes, id);          
        }
    }while(opcion != 7);
    return 0;
}

Lista crearLista(){
    Lista L;
    L = NULL;
    return L;
}

Lista crearTarea(Lista TareasPendientes, int num){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    Tarea T;
    char buff[50];

    T.TareaID = num;
    srand(time(NULL));
    T.Duracion = rand()%100+10;
    printf("Ingrese una descripcion\n");
    fflush(stdin);
    gets(buff);
    T.Descripcion = malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(T.Descripcion, buff);

    nuevo->T = T;
    nuevo->siguiente = TareasPendientes;
    TareasPendientes = nuevo;

    return TareasPendientes;
}

void marcarTareaRealizada(Lista *TareasPendientes, Lista *TareasRealizadas, int id){
    struct Nodo *actual, *anterior;
    actual = *TareasPendientes;
    anterior = NULL;

    // Buscamos la tarea por su ID
    while(actual != NULL && actual->T.TareaID != id){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual != NULL){
        // Si encontramos la tarea, la eliminamos de TareasPendientes
        if(anterior == NULL){
            *TareasPendientes = actual->siguiente;
        }else{
            anterior->siguiente = actual->siguiente;
        }

        // Agregamos la tarea a TareasRealizadas
        actual->siguiente = *TareasRealizadas;
        *TareasRealizadas = actual;

        printf("Tarea %d marcada como realizada.\n", id);
    }else{
        printf("No se encontró la tarea con ID %d.\n", id);
    }
}

void mostrarTarea(Lista Tareas){
    while(Tareas != NULL){
        printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", Tareas->T.TareaID, Tareas->T.Descripcion, Tareas->T.Duracion);
        Tareas = Tareas->siguiente;
    }
}

void buscarTareaID(Lista TareasPendientes, Lista TareasRealizadas, int id){
    while(TareasPendientes != NULL){
        if(TareasPendientes->T.TareaID == id){
            printf("Tarea pendiente encontrada:\n");
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes->T.TareaID, TareasPendientes->T.Descripcion, TareasPendientes->T.Duracion);
        }
        TareasPendientes = TareasPendientes->siguiente;
    }
    while(TareasRealizadas != NULL){
        if(TareasRealizadas->T.TareaID == id){
            printf("Tarea realizada encontrada\n");
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasRealizadas->T.TareaID, TareasRealizadas->T.Descripcion, TareasRealizadas->T.Duracion);
            TareasRealizadas = TareasRealizadas->siguiente;
        }
    }
}

void buscarTareaKeyword(Lista TareasPendientes, Lista TareasRealizadas, char *keyword){
    char *tareaDescripcion;
    while(TareasPendientes != NULL){
        tareaDescripcion = strstr(TareasPendientes->T.Descripcion, keyword);
        if(tareaDescripcion != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes->T.TareaID, TareasPendientes->T.Descripcion, TareasPendientes->T.Duracion);
            TareasPendientes = TareasPendientes->siguiente;
        }
        else{
            TareasPendientes = TareasPendientes->siguiente;
        }
    }
    while(TareasRealizadas != NULL){
        tareaDescripcion = strstr(TareasRealizadas->T.Descripcion, keyword);
        if(tareaDescripcion != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasRealizadas->T.TareaID, TareasRealizadas->T.Descripcion, TareasRealizadas->T.Duracion);
            TareasRealizadas = TareasRealizadas->siguiente;
        }
        else{
            TareasRealizadas = TareasRealizadas->siguiente;
        }
    }
}

void eliminarTareas(Lista Tareas, int id){
    Lista actual, anterior;
    actual = Tareas;
    anterior = NULL;

    // Buscamos la tarea por su ID
    while(actual != NULL && actual->T.TareaID != id){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual != NULL){
        // Si encontramos la tarea
        if(anterior == NULL){
            Tareas = actual->siguiente;
        }else{
            anterior->siguiente = actual->siguiente;
        }
    }
    // libero el actual
    free(actual);
}