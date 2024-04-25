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
    struct NodoTarea *siguiente;
} nodoTarea;

void mostrarNodosPendientes(nodoTarea *start);
void mostrarNodosRealizados(nodoTarea *start);
nodoTarea *crearListaVacia();
nodoTarea *crearTarea(int id);
void insertarNodo(nodoTarea **Start, nodoTarea *NuevoNodo);
void insertarNodoAlFinal(nodoTarea **start, nodoTarea *NuevoNodo);
void eliminarNodo(nodoTarea **start, int id);

int main()
{
    nodoTarea *start = crearListaVacia();
    int tarea, pendientes, realizadas, i = 0;
    do
    {
        printf("Va a aniadir una tarea?\n1:Para si,0:Para no\n");
        scanf(" %d", &tarea);
        fflush(stdin);
        if (tarea == 1)
        {
            nodoTarea *nuevo = crearTarea(i);
            insertarNodo(&start, nuevo);
            mostrarNodosPendientes(start);
            i++;
        }
    } while (tarea != 0);

    return 0;
}

nodoTarea *crearTarea(int id)
{
    char buffer[MAX];
    nodoTarea *nuevaTarea = (nodoTarea *)malloc(sizeof(nodoTarea));
    nuevaTarea->nuevaTarea.TareaID = id + 1;
    printf("Inserte la descripcion de la tarea\n");
    fgets(buffer, MAX, stdin);
    nuevaTarea->nuevaTarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(nuevaTarea->nuevaTarea.Descripcion, buffer);
    nuevaTarea->nuevaTarea.Duracion = rand() % 91 + 10;
    nuevaTarea->siguiente = NULL;
    return nuevaTarea;
}

nodoTarea *crearListaVacia()
{
    return NULL;
}

void insertarNodo(nodoTarea **Start, nodoTarea *NuevoNodo)
{
    NuevoNodo->siguiente = *Start;
    *Start = NuevoNodo;
}

void mostrarNodosPendientes(nodoTarea *start)
{
    printf("\t--------------------------------------------------------\n");
    printf("\tID: %d\n", start->nuevaTarea.TareaID);
    printf("\tDescripcion:\n \t\t%s", start->nuevaTarea.Descripcion);
    printf("\tDuracion: %d\n", start->nuevaTarea.Duracion);
    printf("\t--------------------------------------------------------\n");
}

void mostrarNodosRealizados(nodoTarea *start){
    
}