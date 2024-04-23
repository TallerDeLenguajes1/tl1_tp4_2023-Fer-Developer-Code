#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100

typedef struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} tarea;

typedef struct NodoTarea
{
    tarea nuevaTarea;
    nodoTarea *siguiente;
} nodoTarea;

nodoTarea *crearListaVacia();
nodoTarea *crearTarea(int id);
void InsertarNodo(nodoTarea **Start, nodoTarea *NuevoNodo);
void insertarNodoAlFinal(nodoTarea ** start, nodoTarea *NuevoNodo);
void eliminarNodo(nodoTarea ** start, int id);

int main()
{
    nodoTarea *start = crearListaVacia();
    int tareas, pendientes, realizadas;
    printf("Cuantas tareas va a realizar");
    scanf("%d", &tareas);
    
    return 0;
}

nodoTarea *crearTarea(int id)
{
    nodoTarea *nuevaTarea = (nodoTarea *)malloc(sizeof(nodoTarea));
    nuevaTarea->nuevaTarea.TareaID = id;
    nuevaTarea->nuevaTarea.Descripcion = (char *)malloc(sizeof(char) * MAX);
    nuevaTarea->nuevaTarea.Duracion = rand() % 91 + 10;
    nuevaTarea->siguiente = NULL;
    return nuevaTarea;
}

nodoTarea *crearListaVacia()
{
    return NULL;
}

void InsertarNodo(nodoTarea **Start, nodoTarea *NuevoNodo)
{
    NuevoNodo->siguiente = *Start;
    *Start = NuevoNodo;
}