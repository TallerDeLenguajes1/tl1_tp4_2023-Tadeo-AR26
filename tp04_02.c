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
int mostrarDatos(Lista Tareas);

int main(){
    Lista TareasPendientes, TareasRealizadas, TareasEnProceso;
    int opcion, id, num = 1, t, tiempo, op, fuente, destino;
    char *cont = "y";
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
        printf("8- Operaciones\n");
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
                printf("Ingrese un ID para eliminar una tarea\n");
                scanf("%d", &id);
                eliminarTareas(TareasPendientes, id);
                break;
            case 7:
                printf("Ingrese la lista para obtener el tiempo total asociado (1-Pendientes, 2-Realizadas, 3-En Proceso)\n");
                scanf("%d", &t);
                switch(t){
                    case 1:
                        tiempo = mostrarDatos(TareasPendientes);
                        printf("El tiempo total de Tareas Pendientes es %d\n", tiempo);
                        break;
                    case 2:
                        tiempo = mostrarDatos(TareasRealizadas);
                        printf("El tiempo total de Tareas Realizadas es %d\n", tiempo);
                        break;
                    case 3:
                        tiempo = mostrarDatos(TareasEnProceso);
                        printf("El tiempo total de Tareas en Proceso es %d\n", tiempo);
                        break;
                }
                break;
            case 8:
                while(cont != "n"){
                    printf("Tareas Pendientes:\n");
                    mostrarTarea(TareasPendientes);
                    printf("Tareas Realizadas:\n");
                    mostrarTarea(TareasRealizadas);
                    printf("Tareas en Proceso\n");
                    mostrarTarea(TareasEnProceso);
                    printf("Ingrese el ID de la tarea que desea operar\n");
                    scanf("%d", &id);
                    printf("Ingrese una operacion\n\t1-Mover\n\t2-Eliminar\n");
                    scanf("%d", &op);
                    switch(op){
                        case 1:
                            printf("Ingrese hacia donde desea mover la tarea\n\t1-Pendientes\n\t2-Realizadas\n\t3-Proceso\n");
                            scanf("%d", &destino);
                            if(destino == 1){
                                marcarTareaRealizada(&TareasRealizadas, &TareasPendientes, id);
                                marcarTareaRealizada(&TareasEnProceso, &TareasPendientes, id);
                            }
                            if(destino == 2){
                                marcarTareaRealizada(&TareasPendientes, &TareasRealizadas, id);
                                marcarTareaRealizada(&TareasEnProceso, &TareasRealizadas, id);
                            }
                            if(destino == 3){
                                marcarTareaRealizada(&TareasPendientes, &TareasEnProceso, id);
                                marcarTareaRealizada(&TareasRealizadas, &TareasEnProceso, id);
                            }
                            break;
                        case 2:
                            eliminarTareas(TareasPendientes, id);
                            eliminarTareas(TareasRealizadas, id);
                            eliminarTareas(TareasEnProceso, id);
                            break;
                        }
                    printf("Desea continuar? [y/n]\n");
                    scanf("%s", &cont);
                }
                break;

        }
    }while(opcion != 9);
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

int mostrarDatos(Lista Tareas){
    int tiempo;
    while(Tareas != NULL){
        tiempo += Tareas->T.Duracion;
    }
    return tiempo;
}