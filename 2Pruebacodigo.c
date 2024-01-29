// Ingrese las librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Coloco la estructura que se va a utilizar

struct InformacionProductos
{
    char nombre[50];
    int cantidad_entrada;
    float precio_entrada;
    float precio_salida;
    int cantidad_salida;
};
// Estas son las funciones que vamos a colocar

void ingresarInformacion(struct InformacionProductos inventario[], int *CantAlumnos);
void mostrarInformacion(struct InformacionProductos inventario[], int CantAlumnos);

int main()
{
    struct InformacionProductos inventario[50];
    int CantClientes = 0;
    int opcion;
    // Menu que se va a mostrar al usuario
    do
    {
        printf("\nBienvenido a Stock Master\n");
        printf("\nMenu De Seleccion:\n");
        printf("1. Ingrese los datos del producto\n");
        printf("2. Mostrar la informacion del producto\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        fflush(stdin);
        // Creamos un Switch para las opciones
        switch (opcion)
        {
        case 1:
            ingresarInformacion(inventario, &CantClientes);
            break;
        case 2:
            mostrarInformacion(inventario, CantClientes);
            break;
        case 3:
            printf("Finalizando el programa.\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    return 0;
}

// Creo la funcion que vamos a utilizar para la introduccion de datos
void ingresarInformacion(struct InformacionProductos inventario[], int *CantClientes)
{
    if (*CantClientes < 50)
    {
        printf("Nombre: ");
        fflush(stdin);
        fgets(inventario[*CantClientes].nombre, 50, stdin);
        inventario[*CantClientes].nombre[strcspn(inventario[*CantClientes].nombre, "\n")] = '\0';

        printf("\nCantidad de productos: ");
        scanf("%d", &inventario[*CantClientes].cantidad_entrada);
        fflush(stdin);

        printf("Precio de entrada: ");
        scanf("%f", &inventario[*CantClientes].precio_entrada);
        fflush(stdin);

        printf("Precio de salida: ");
        scanf("%f", &inventario[*CantClientes].precio_salida);
        fflush(stdin);

        printf("Cantidad de salida de productos : ");
        scanf("%d", &inventario[*CantClientes].cantidad_salida);
        fflush(stdin);

        (*CantClientes)++;
        printf("\tDatos guardados.\n");
    }
    else
    {
        printf("No se pueden añadir mas datos.\n");
    }
}
// Funcion que muesta e imprime en un archivo .txt
void mostrarInformacion(struct InformacionProductos inventario[], int CantClientes)
{
    if (CantClientes > 0)
    {
        // Imprimir títulos
        printf("\n%-25s %-25s %-25s %-25s %-25s\n", "Nombre", "Cantidad de productos", "Precio de entrada", "Precio de salida", "Cantidad de salida de productos");

        for (int i = 0; i < CantClientes; i++)
        {
            // Imprimir datos del alumno en formato horizontal
            printf("%-25s %-25d %-25f %-25f %-25d\n", inventario[i].nombre, inventario[i].cantidad_entrada, inventario[i].precio_entrada, inventario[i].precio_salida, inventario[i].cantidad_salida);
        }
    }
    else
    {
        printf("No hay datos para mostrar.\n");
    }

    // Creo archivo .txt
    FILE *archivo = fopen("Informacion.txt", "a");

    if (archivo != NULL)
    {
        // Imprimir títulos en el archivo
        fprintf(archivo, "%-25s ; %-25s;%-25s;%-25s;%-25s\n", "Nombre", "Cantidad de productos", "Precio de entrada", "Precio de salida", "Cantidad de salida de productos");

        for (int i = 0; i < CantClientes; i++)
        {
            // Imprimir datos del alumno en formato horizontal
            fprintf(archivo, "%-25s;%-25d;%-25f;%-25f;%-25d\n", inventario[i].nombre, inventario[i].cantidad_entrada, inventario[i].precio_entrada, inventario[i].precio_salida, inventario[i].cantidad_salida);
        }

        fclose(archivo);
        printf("Datos guardados en el archivo ");
    }
    else
    {
        printf("Error al abrir el archivo para escritura.\n");
    }
}