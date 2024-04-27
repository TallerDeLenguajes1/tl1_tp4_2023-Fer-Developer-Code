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
void mostrarTareasRealizadas(Nodo **cabeza);
void eliminarNodoTareas(Nodo **cabeza, int id);
Nodo *crearNodoRealizado(Nodo **cabezaPendientes, int id);
Nodo *buscarTarea(Nodo **cabeza, int idBuscado);
Nodo *buscarTareaPorPalabras(Nodo **cabeza, char *frase);

int main()
{
    srand(time(NULL));
    Nodo **startPendientes = crearListaVacia();
    Nodo **cabezaRealizadas = crearListaVacia();
    int numTarea = 100, opcion, idTarea;
    char *frase = (char *)malloc(MAX * sizeof(char));
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
            printf("Inserte el Id de la tarea que va a pasar a 'realizada'\n");
            scanf("%d", &idTarea);
            insertarNodo(cabezaRealizadas, crearNodoRealizado(startPendientes, idTarea));
            break;
        case 3:
            mostrarTareasPendientes(startPendientes);
            break;
        case 4:
            mostrarTareasRealizadas(cabezaRealizadas);
            break;
        case 5:
            buscarTarea(startPendientes, idTarea);
            break;
        case 6:
            printf("Ingrese una frase para buscar una tarea que coincida con la misma\n");
            scanf("%s", frase);
            fflush(stdin);
            frase = (char *)realloc(frase, (strlen(frase) + 1) * sizeof(char));
            buscarTareaPorPalabras(startPendientes, frase);
            break;

        default:
            printf("Ingrese un valor valido\n");
            break;
        }
    } while (opcion != 0);
    free(startPendientes);
    free(cabezaRealizadas);
    free(frase);
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
    free(aux);
}

void mostrarTareasRealizadas(Nodo **cabeza)
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

Nodo *buscarTarea(Nodo **cabeza, int id)
{
    Nodo *aux = *cabeza;
    while (aux && aux->nuevaTarea.TareaID != id)
    {
        aux = aux->siguiente;
    }
    if (aux && aux->nuevaTarea.TareaID == id)
    {
        printf("----------------------------------------------------------------\n");
        printf("\tID: %d\n", aux->nuevaTarea.TareaID);
        printf("\tDescripcion: %s\n", aux->nuevaTarea.Descripcion);
        printf("\tDuracion: %d\n", aux->nuevaTarea.Duracion);
        printf("----------------------------------------------------------------\n");
        return aux;
    }
    else
    {
        return NULL;
    }
}

Nodo *crearNodoRealizado(Nodo **cabezaPendientes, int id)
{
    Nodo *aux = buscarTarea(cabezaPendientes, id);
    if (aux == NULL)
    {
        printf("No se encontró la tarea con el ID especificado.\n");
        return NULL;
    }
    Nodo *nodoRealizado = crearNodo(aux->nuevaTarea.TareaID - 1);
    strcpy(nodoRealizado->nuevaTarea.Descripcion, aux->nuevaTarea.Descripcion);
    nodoRealizado->nuevaTarea.Duracion = aux->nuevaTarea.Duracion;
    eliminarNodoTareas(cabezaPendientes, id);
    return nodoRealizado;
}

void eliminarNodoTareas(Nodo **cabeza, int id)
{
    Nodo **aux = cabeza;
    while (*aux != NULL && (*aux)->nuevaTarea.TareaID != id)
    {
        aux = &(*aux)->siguiente;
        // Si encontramos el nodo con el dato especificado, lo eliminamos.
    }
    if (*aux)
    {
        Nodo *temp = *aux;        // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->siguiente; // Desvinculamos el nodo de la lista.
        free(temp->nuevaTarea.Descripcion);
        free(temp); // Liberamos la memoria ocupada por el nodo.
    }
}