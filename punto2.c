#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

struct Nodo
{
    Tarea nuevaTarea;
    struct Nodo *siguiente;
};

Nodo **crearListaVacia();
Nodo *crearNodo(int id);
void insertarNodo(Nodo **start, Nodo *tarea);
void mostrarTareasPendientes(Nodo **cabeza);

int main()
{
    srand(time(NULL));
    Nodo **startPendientes = crearListaVacia();
    Nodo **cabezaRealizadas = crearListaVacia();
    int cantTareas, pendientes, realizadas, numTarea = 0, opcion;

    do
    {
        printf("Ingrese la operacion a trabajar, presone 0 para salir\n");
        printf("1. Agregar tarea a pendientes\n");
        printf("2. Cambiar tarea de pendiente a realizada\n");
        printf("3. Mostrar tareas pendientes\n");
        printf("4. Mostrar tareas realizadas\n");
        printf("5. Buscar tarea por ID\n");
        printf("6. Buscar tarea por palabra\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            insertarNodo(startPendientes, crearNodo(numTarea));
            printf("Aniadido con exito\n");
            numTarea++;
            break;
        case 2:
            break;
        case 3:
            mostrarTareasPendientes(startPendientes);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;

        default:
            printf("Ingrese un valor valido\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}

Nodo **crearListaVacia()
{
    Nodo **lista = (Nodo **)malloc(sizeof(Nodo *));
    *lista = NULL;
    return lista;
}

Nodo *crearNodo(int id)
{
    char buff[MAX];
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->nuevaTarea.TareaID = id + 1;
    printf("Ingrese la descripcion de la tarea\n");
    fflush(stdin);
    gets(buff);
    fflush(stdin);
    nuevo->nuevaTarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(nuevo->nuevaTarea.Descripcion, buff);
    nuevo->nuevaTarea.Duracion = rand() % 91 + 10;
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertarNodo(Nodo **start, Nodo *tarea)
{
    tarea->siguiente = *start;
    *start = tarea;
}

void mostrarTareasPendientes(Nodo **cabeza)
{
    Nodo *aux = *cabeza;
    while (aux != NULL)
    {
        printf("----------------------------------------------------------------\n");
        printf("\tID: %d\n", aux->nuevaTarea.TareaID);
        printf("\tDescripcion: %s\n", aux->nuevaTarea.Descripcion);
        printf("\tDuracion: %d\n", aux->nuevaTarea.Duracion);
        printf("----------------------------------------------------------------\n");
        aux = aux->siguiente;
    }
}