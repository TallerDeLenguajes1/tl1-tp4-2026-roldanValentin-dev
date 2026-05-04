#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definimos estructuras
typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;
typedef struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

// funciones
//crear lista enlazada

Nodo *CrearListaVacia(){
    return NULL;

}
Nodo *CrearNodo(int id,char *descripcion , int duracion){
    // reservar memoria para el nuevo nodo
    Nodo *nuevatarea = (Nodo *)malloc(sizeof(Nodo));
    //inicializamos los campos
    nuevatarea->T.TareaID = id;
    nuevatarea->T.Descripcion = descripcion;
    nuevatarea->T.Duracion = duracion;
    //hacemos que el siguiente apunte a null 
    nuevatarea->Siguiente = NULL;
    return nuevatarea;
}

void insertarTareaAlfinal(Nodo *lista , Nodo *nodo){
    Nodo *aux = lista;
    while (aux->Siguiente)
    {
        aux= aux->Siguiente;
    }
    aux->Siguiente = nodo;
    
}


int main()
{

 Nodo *TareasRealizadas = CrearListaVacia();
 Nodo *TareasPendientes = CrearListaVacia();
 int id = 1000; // ID inicial para las tareas
 printf("Bienvenido al sistema de gestión de tareas\n");
 int opcion;

 do
 {
    printf("Seleccione una opción:\n");
    printf("1. Agregar tarea\n");
    printf("2. Marcar tarea como realizada\n");
    printf("3. Mostrar tareas pendientes\n");
    printf("4. Mostrar tareas realizadas\n");
    printf("5. Salir\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
        char descripcion[100];
        int duracion;
        // agregar tarea
        printf("Ingrese descripcion de tarea");
        fflush(stdin);
        fgets(descripcion,100,stdin);
        printf("Ingrese duracion");
        scanf("%d",&duracion);
        // Validar que la duración esté entre 10 y 100 y que descripcion no esté vacía
        if (duracion >= 10 && duracion <= 100 && strlen(descripcion) > 0)
        {
            Nodo *nuevaTarea = CrearNodo(id, descripcion, duracion);
            insertarTareaAlfinal(TareasPendientes, nuevaTarea);
            id++; // Incrementar el ID para la próxima tarea
        }
        else
        {
            printf("Datos de tarea inválidos.\n");
        }

        break;
    case 2:
        // marcar tarea como realizada
        break;
    case 3:
        // listar tareas pendientes
        break;
    case 4:
        // listar tareas realizadas
        break;
    case 5:
        printf("Saliendo del sistema...\n");
        break;
    default:
        printf("Opción no válida. Por favor, seleccione una opción válida.\n");
        break;
    }
 } while (opcion != 5);
 

    return 0;
}



