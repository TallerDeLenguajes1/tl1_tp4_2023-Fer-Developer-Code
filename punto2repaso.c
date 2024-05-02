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

Nodo *crearListaVacia();
Nodo *crearNodo(int numTarea);
Nodo *copiarNodo(Tarea tarea);
void insertarNodo(Nodo **start, Nodo *nuevoNodo);
void InsertarNodoTareaHecha(Nodo **start, Nodo **listaTareas, int idTarea);
void eliminarNodo(Nodo **lista, int id);
void buscarPorId(Nodo **lista, int id);
void buscarPorPalabra(Nodo **lista, char *frase);
void mostrarTareas(Nodo **cabeza);
void liberarListas(Nodo **lista);

int main()
{
    srand(time(NULL));
    Nodo *startPendientes = crearListaVacia();
    Nodo *cabezaRealizadas = crearListaVacia();
    int numTarea = 100, opcion, idTarea;
    char *frase = (char *)malloc(MAX * sizeof(char));
    do
    {
        printf("Ingrese la operacion a trabajar, presione 0 para salir\n");
        printf("1. Agregar tarea a pendientes\n");
        printf("2. Cambiar tarea de pendiente a realizada\n");
        printf("3. Mostrar tareas pendientes\n");
        printf("4. Mostrar tareas realizadas\n");
        printf("5. Buscar tarea por ID\n");
        printf("6. Buscar tarea por palabra\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 0:
                printf("Operacion terminada\n");
            break;
        case 1:
            insertarNodo(&startPendientes, crearNodo(numTarea));
            printf("Aniadido con exito\n");
            numTarea++;
            break;
        case 2:
            printf("Inserte el Id de la tarea que va a pasar a 'realizada'\n");
            scanf("%d", &idTarea);
            fflush(stdin);
            InsertarNodoTareaHecha(&cabezaRealizadas, &startPendientes, idTarea);
            break;
        case 3:
            mostrarTareas(&startPendientes);
            break;
        case 4:
            mostrarTareas(&cabezaRealizadas);
            break;
        case 5:
            printf("Inserte el Id a buscar\n");
            scanf("%d", &idTarea);
            printf("En pendientes\n");
            buscarPorId(&startPendientes, idTarea);
            printf("En realizadas\n");
            buscarPorId(&cabezaRealizadas, idTarea);
            break;
        case 6:
            printf("Ingrese una frase para buscar una tarea que coincida con la misma\n");
            scanf("%s", frase);
            fflush(stdin);
            frase = (char *)realloc(frase, (strlen(frase) + 1) * sizeof(char));
            printf("En pendientes:\n");
            buscarPorPalabra(&startPendientes, frase);
            printf("En realizadas:\n");
            buscarPorPalabra(&cabezaRealizadas, frase);
            break;

        default:
            printf("Ingrese un valor valido\n");
            break;
        }
    } while (opcion != 0);
    liberarListas(&startPendientes);
    liberarListas(&cabezaRealizadas);
    free(frase);
    printf("Listas limpias\n");
    mostrarTareas(&startPendientes);
    mostrarTareas(&cabezaRealizadas);
    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(int numTarea)
{
    char *buff = (char *)malloc(MAX * sizeof(char));
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    printf("Ingrese la descripcion de la tarea\n");
    fflush(stdin);
    gets(buff);
    fflush(stdin);
    buff = (char *)realloc(buff, (strlen(buff) + 1) * sizeof(char));
    nuevoNodo->nuevaTarea.TareaID = numTarea;
    nuevoNodo->nuevaTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(nuevoNodo->nuevaTarea.Descripcion, buff);
    nuevoNodo->nuevaTarea.Duracion = rand() % 91 + 10;
    nuevoNodo->siguiente = NULL;
    free(buff);
    return nuevoNodo;
}

Nodo *copiarNodo(Tarea tarea)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->nuevaTarea = tarea;
    return nuevoNodo;
}

void insertarNodo(Nodo **start, Nodo *nuevoNodo)
{
    nuevoNodo->siguiente = *start;
    *start = nuevoNodo;
}

void mostrarTareas(Nodo **cabeza)
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
    free(aux);
}

void InsertarNodoTareaHecha(Nodo **start, Nodo **listaTareas, int idTarea)
{
    Nodo *aux = *listaTareas;
    while (aux != NULL)
    {
        if (aux->nuevaTarea.TareaID == idTarea)
        {
            insertarNodo(start, copiarNodo(aux->nuevaTarea));
            eliminarNodo(listaTareas, idTarea);
        }
        aux = aux->siguiente;
    }
}

void eliminarNodo(Nodo **lista, int id)
{
    Nodo **aux = lista;
    while (*aux != NULL && (*aux)->nuevaTarea.TareaID != id)
    {
        aux = &(*aux)->siguiente;
    }
    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->siguiente;
        free(temp);
    }
}

void buscarPorId(Nodo **lista, int id)
{
    Nodo *aux = *lista;
    while (aux != NULL)
    {
        if (aux->nuevaTarea.TareaID == id)
        {
            printf("----------------------------------------------------------------\n");
            printf("\tID: %d\n", aux->nuevaTarea.TareaID);
            printf("\tDescripcion: %s\n", aux->nuevaTarea.Descripcion);
            printf("\tDuracion: %d\n", aux->nuevaTarea.Duracion);
            printf("----------------------------------------------------------------\n");
        }
        aux = aux->siguiente;
    }
}

void buscarPorPalabra(Nodo **lista, char *frase)
{
    Nodo *aux = *lista;
    while (aux != NULL)
    {
        if (strstr(frase, (aux->nuevaTarea.Descripcion)))
        {
            printf("----------------------------------------------------------------\n");
            printf("\tID: %d\n", aux->nuevaTarea.TareaID);
            printf("\tDescripcion: %s\n", aux->nuevaTarea.Descripcion);
            printf("\tDuracion: %d\n", aux->nuevaTarea.Duracion);
            printf("----------------------------------------------------------------\n");
        }
        aux = aux->siguiente;
    }
}
void liberarListas(Nodo **lista){
    Nodo **aux = lista;
    while (*aux != NULL)
    {
        Nodo *temp = *aux;
        free(temp);
        (*aux) = (*aux)->siguiente;
    }
}