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
Lista marcarRealizada(Lista TareasPendientes, Lista TareasRealizadas);
void buscarID(Lista TareasPendientes, Lista TareasRealizadas, int id);
void buscarPalabra(Lista TareasPendientes, Lista TareasRealizadas, char *keyword);

int main(){
    Lista TareasPendientes, TareasRealizadas;
    int opcion, id = 1;
    TareasPendientes = crearLista();
    TareasRealizadas = crearLista();
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
                TareasPendientes = crearTarea(TareasPendientes, id);
                id = id+1;
                break;
            case 2:
                TareasRealizadas = marcarRealizada(TareasPendientes, TareasRealizadas);
                break;
            case 3:
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
                buscarID(TareasPendientes, TareasRealizadas, id);
                break;
            case 5:
                printf("Ingrese una palabra clave\n");
                char keyword[50];
                scanf("%s", &keyword);
                buscarPalabra(TareasPendientes, TareasRealizadas, keyword);
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

Lista marcarRealizada(Lista TareasPendientes, Lista TareasRealizadas){
    int op = 0;
    while(TareasPendientes != NULL){
        printf("¿Desea marcar Tarea: %d -- Descripcion: %s -- Duracion: %d como realizada?\n", TareasPendientes->T->TareaID, TareasPendientes->T->Descripcion, TareasPendientes->T->Duracion);
        fflush(stdin);
        printf("1- Si\n2- No\n");
        scanf("%d", &op);
        if(op == 1){

            //Copiar las Tareas Pendientes a las Realizadas 
            struct Nodo *nuevo;
            nuevo = malloc(sizeof(struct Nodo));
            nuevo->T = malloc(sizeof(struct Tarea));
            nuevo->T->Descripcion = TareasPendientes->T->Descripcion;
            nuevo->T->Duracion = TareasPendientes->T->Duracion;
            nuevo->T->TareaID = TareasPendientes->T->TareaID;
            nuevo->siguiente = TareasRealizadas;
            TareasRealizadas = nuevo;
            TareasPendientes = TareasPendientes->siguiente;


            //Eliminar las TareasPendientes

            /* struct Nodo *actual, *anterior;
            actual = TareasPendientes;
            anterior = NULL;
            while(actual != NULL){
                if(actual->T->TareaID == TareasPendientes->T->TareaID){
                    if(anterior == NULL){
                        TareasPendientes = actual->siguiente;
                    }else{
                        anterior->siguiente = actual->siguiente;
                    }
                    free(actual->T->Descripcion);
                    free(actual->T);
                    free(actual);
                    break;
                }
                anterior = actual;
                actual = actual->siguiente;
            } */
        }
        else{
            TareasPendientes = TareasPendientes->siguiente;
        }
    }
    return TareasRealizadas;
}

void buscarID(Lista TareasPendientes, Lista TareasRealizadas, int id){
    while(TareasPendientes != NULL){
        if(TareasPendientes->T->TareaID == id){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes->T->TareaID, TareasPendientes->T->Descripcion, TareasPendientes->T->Duracion);
            TareasPendientes = TareasPendientes->siguiente;
        }
        else{
            TareasPendientes = TareasPendientes->siguiente;
        }
    }
    while(TareasRealizadas != NULL){
        if(TareasRealizadas->T->TareaID == id){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasRealizadas->T->TareaID, TareasRealizadas->T->Descripcion, TareasRealizadas->T->Duracion);
            TareasRealizadas = TareasRealizadas->siguiente;
        }
        else{
            TareasRealizadas = TareasRealizadas->siguiente;
        }
    }  
}


void buscarPalabra(Lista TareasPendientes, Lista TareasRealizadas, char *keyword){
    while(TareasPendientes != NULL){
        char *tareaDescripcion;
        tareaDescripcion = strstr(TareasPendientes->T->Descripcion, keyword);
        if(tareaDescripcion != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasPendientes->T->TareaID, TareasPendientes->T->Descripcion, TareasPendientes->T->Duracion);
            TareasPendientes = TareasPendientes->siguiente;
        }
        else{
            TareasPendientes = TareasPendientes->siguiente;
        }
    }
    while(TareasRealizadas != NULL){
        char *tareaDescripcion = NULL;
        tareaDescripcion = strstr(TareasRealizadas->T->Descripcion, keyword);
        if(tareaDescripcion != NULL){
            printf("Tarea: %d -- Descripcion: %s -- Duracion: %d\n", TareasRealizadas->T->TareaID, TareasRealizadas->T->Descripcion, TareasRealizadas->T->Duracion);
            TareasRealizadas = TareasRealizadas->siguiente;
        }
        else{
            TareasRealizadas = TareasRealizadas->siguiente;
        }
    }
}