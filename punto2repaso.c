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
            fflush(stdin);
            insertarNodo(cabezaRealizadas, crearNodoRealizado(startPendientes, idTarea));
            break;
        case 3:
            mostrarTareasPendientes(startPendientes);
            break;
        case 4:
            mostrarTareasRealizadas(cabezaRealizadas);
            break;
        case 5:
            printf("Inserte el Id a buscar\n");
            scanf("%d", &idTarea);
            printf("En pendientes\n");
            buscarTareaPorId(startPendientes, idTarea);
            printf("En realizadas\n");
            buscarTareaPorId(cabezaRealizadas, idTarea);
            break;
        case 6:
            printf("Ingrese una frase para buscar una tarea que coincida con la misma\n");
            scanf("%s", frase);
            fflush(stdin);
            frase = (char *)realloc(frase, (strlen(frase) + 1) * sizeof(char));
            printf("En pendientes:\n");
            buscarTareaPorPalabra(startPendientes, frase);
            printf("En realizadas:\n");
            buscarTareaPorPalabra(cabezaRealizadas, frase);
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