#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definimos estructuras
typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; // Puntero a cadena de caracteres
    int Duracion;      // entre 10 – 100
} Tarea;
typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// funciones
// crear lista enlazada

Nodo *CrearListaVacia();

Nodo *CrearNodo(int id, char *descripcion, int duracion);

void insertarTareaAlfinal(Nodo **lista, Nodo *nodo);

void mostrarTareas(Nodo *lista);

Nodo *buscarNodoPorID(Nodo *lista, int idBuscado);
void buscarPorPalabra(Nodo *lista, char *palabra);

Nodo *QuitarNodo(Nodo **lista, int idBuscado);

// programa principal

int main()
{

    Nodo *TareasRealizadas = CrearListaVacia();
    Nodo *TareasPendientes = CrearListaVacia();
    char descripcion[100];
    int duracion;
    int id = 1000; // ID inicial para las tareas
    printf("Bienvenido al sistema de gestión de tareas\n");
    int opcion;

    do
    {
        printf("\nSeleccione una opción:\n");
        printf("1. Agregar tarea\n");
        printf("2. Agregar tarea a realizada\n");
        printf("3. Mostrar listado de tareas\n");
        printf("4. Buscar tarea por ID o palabra clave\n");
        printf("5. Salir\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
        {
            int continuar;
            do
            {
                printf("Ingrese descripcion de tarea\n");
                while (getchar() != '\n')
                    ; // Limpia el \n del menu anterior
                fgets(descripcion, 100, stdin);
                printf("Ingrese duracion\n");
                scanf("%d", &duracion);
                // Validar que la duración esté entre 10 y 100 y que descripcion no esté vacía
                if (duracion >= 10 && duracion <= 100 && strlen(descripcion) > 0)
                {
                    Nodo *Nuevotarea = CrearNodo(id, descripcion, duracion);
                    insertarTareaAlfinal(&TareasPendientes, Nuevotarea);
                    id++; // Incrementar el ID para la próxima tarea
                    printf("Tarea agregada exitosamente.\n");
                }
                else
                {
                    printf("Datos de tarea inválidos.\n");
                    break;
                }
                printf("Desea agregar otra tarea? (1 para sí, 0 para no): ");
                scanf("%d", &continuar);
            } while (continuar == 1);
        }
        break;
        case 2:
            // agregar tarea a realizada
            mostrarTareas(TareasPendientes);
            printf("Ingrese el ID de la tarea realizada: ");
            int idRealizada;
            scanf("%d", &idRealizada);
            Nodo *tareaRealizada = QuitarNodo(&TareasPendientes, idRealizada);
            if (tareaRealizada != NULL)
            {
                insertarTareaAlfinal(&TareasRealizadas, tareaRealizada);
                printf("Tarea marcada como realizada.\n");
            }
            else
            {
                printf("No se encontró una tarea con el ID proporcionado.\n");
            }

            break;
        case 3:
            printf("Tareas Pendientes:\n");
            // listar tareas pendientes
            mostrarTareas(TareasPendientes);
            // listado de tareas realizadas
            printf("\n");
            printf("Tareas Realizadas:\n");
            mostrarTareas(TareasRealizadas);
            break;
        case 4:
            printf("¿Desea buscar por (1) ID o (2) Palabra Clave?: ");
            int modo;
            scanf("%d", &modo);

            if (modo == 1)
            {
                printf("Ingrese el ID: ");
                int idBuscado;
                scanf("%d", &idBuscado);

                // Buscamos en ambas listas usando tu función buscarNodoPorID
                Nodo *encontrada = buscarNodoPorID(TareasPendientes, idBuscado);
                if (!encontrada)
                    encontrada = buscarNodoPorID(TareasRealizadas, idBuscado);

                if (encontrada)
                {
                    printf("Tarea Encontrada: [%d] %s", encontrada->T.TareaID, encontrada->T.Descripcion);
                }
                else
                {
                    printf("No se encontró el ID.\n");
                }
            }
            else
            {
                char palabra[50];
                printf("Ingrese la palabra clave: ");
                while (getchar() != '\n')
                    ; // Limpiar buffer
                scanf("%s", palabra);

                printf("\n--- Resultados en Pendientes ---\n");
                buscarPorPalabra(TareasPendientes, palabra);

                printf("\n--- Resultados en Realizadas ---\n");
                buscarPorPalabra(TareasRealizadas, palabra);
            }
            break;
        case 5:
            printf("Saliendo del sistema...\n");
            break;
        default:
            printf("Opción no válida. Por favor, seleccione una opción válida.\n");
            break;
        }
    } while (opcion != 5);
    // Liberar memoria antes de salir
    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);
    return 0;
}



Nodo *CrearListaVacia()
{
    return NULL;
}
Nodo *CrearNodo(int id, char *descripcion, int duracion)
{
    // reservar memoria para el nuevo nodo
    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    // inicializamos los campos
    NuevoNodo->T.TareaID = id;
    NuevoNodo->T.Descripcion = strdup(descripcion); // duplicamos la cadena para evitar problemas de memoria
    NuevoNodo->T.Duracion = duracion;
    // hacemos que el siguiente apunte a null
    NuevoNodo->Siguiente = NULL;
    return NuevoNodo;
}

void insertarTareaAlfinal(Nodo **lista, Nodo *nodo)
{
    // Si la lista está vacía, el nuevo nodo se convierte en el primer nodo
    if (*lista == NULL)
    {
        *lista = nodo;
    }
    else
    {
        // Si la lista no está vacía, buscamos el último nodo
        Nodo *aux = *lista;
        // mientras el siguiente del nodo actual no sea null, seguimos avanzando
        while (aux->Siguiente)
        {
            // avanzamos al siguiente nodo
            aux = aux->Siguiente;
        }
        // cuando encontramos el último nodo, hacemos que su siguiente apunte al nuevo nodo
        aux->Siguiente = nodo;
    }
}
void mostrarTareas(Nodo *lista)
{
    // recorremos la lista y mostramos cada tarea
    Nodo *aux = lista;
    if (aux == NULL)
    {
        printf("-------------------------------------\n");
        printf("No hay tareas para mostrar.\n");
        printf("Por favor agregue una nueva tarea.\n");
        printf("-------------------------------------\n");
        return;
    }
    else
    {
        while (aux)
        {
            printf("-------------------------------------\n");
            // mostramos la información de la tarea
            printf("TareaID: [%d] Descripcion: %s Duracion: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
            // avanzamos al siguiente nodo
            aux = aux->Siguiente;
        }
    }
}

// funcion para buscar nodo
Nodo *buscarNodoPorID(Nodo *lista, int idBuscado)
{
    Nodo *aux = lista;
    while (aux && aux->T.TareaID != idBuscado)
    {
        aux = aux->Siguiente;
    }
    return aux;
}
void buscarPorPalabra(Nodo *lista, char *palabra)
{
    Nodo *aux = lista;
    while (aux)
    {
        //si la palabra clave se encuentra en la descripción de la tarea, mostramos la tarea
        if (strstr(aux->T.Descripcion, palabra) != NULL)
        {
            printf("[ID: %d] - Descripcion: %s", aux->T.TareaID, aux->T.Descripcion);
        }
        aux = aux->Siguiente;
    }
}
// funcion para quitar nodo de la lista
Nodo *QuitarNodo(Nodo **lista, int idBuscado)
{
    // inicializamos punteros para recorrer la lista
    Nodo *aux = *lista;
    // puntero para mantener el nodo anterior al nodo encontrado
    Nodo *auxAnt = NULL;
    // mientras no lleguemos al final de la lista y no encontremos el nodo con el ID buscado, seguimos avanzando
    while (aux != NULL && aux->T.TareaID != idBuscado)
    {
        // actualizamos el puntero del nodo anterior al nodo actual
        auxAnt = aux;
        // avanzamos al siguiente nodo
        aux = aux->Siguiente;
    }
    // si aux es diferente de NULL, significa que encontramos el nodo con el ID buscado
    if (aux != NULL)
    {
        // si el nodo encontrado es el primer nodo de la lista, actualizamos el puntero de la lista para que apunte al siguiente nodo
        if (aux == *lista)
        {
            *lista = aux->Siguiente;
        }
        // sino, actualizamos el puntero del nodo anterior para que apunte al siguiente nodo del nodo encontrado
        else
        {
            auxAnt->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL; // Desconectar el nodo encontrado de la lista
    }
    return aux; // Retornar el nodo encontrado (o NULL si no se encontró)
}

void LiberarLista(Nodo *lista)
{
    Nodo *aux = lista;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}