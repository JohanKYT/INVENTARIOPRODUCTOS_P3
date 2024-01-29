#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROJO_T "\x1b[31m"
#define AZUL_T "\x1b[34m"
#define VERDE_T "\x1b[32m"
#define RESET_T "\x1b[0m"

struct Producto
{
    char nombre[50];
    float precioEntrada;
    char fechaIngreso[11]; // Cambiado a formato DD/MM/YYYY
    int cantidadEntrada;
    float precioVenta;
    char fechaEgreso[11]; // Cambiado a formato DD/MM/YYYY
    int cantidadSalida;
};

float calcularImpuestos(float precio, float impuestoPorcentaje, int cantidadSalida)
{
    return precio * impuestoPorcentaje / 100.0 * cantidadSalida;
}

void mostrarInventario(struct Producto productos[], int numProductos)
{
    FILE *archivoInventario = fopen("inventario.txt", "w");

    if (archivoInventario == NULL)
    {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    float totalImpuestos = 0.0;

    printf(VERDE_T "\n=== Inventario ===\n");
    fprintf(archivoInventario, "=== Inventario ===\n");

    // Imprimir encabezados de la tabla
    printf(ROJO_T "%-8s %-20s %-18s %-18s %-15s %-15s %-15s %-15s %-15s %-15s\n",
           "Indice", "Nombre", "Cant. Entrada", "Precio Entrada", "Fecha Entrada", "Cant. Salida", "Precio Venta", "Fecha Salida", "Cant. Restante", "Impuestos");
    fprintf(archivoInventario, "%-8s %-20s %-18s %-18s %-15s %-15s %-15s %-15s %-15s %-15s\n",
            "Indice", "Nombre", "Cant. Entrada", "Precio Entrada", "Fecha Entrada", "Cant. Salida", "Precio Venta", "Fecha Salida", "Cant. Restante", "Impuestos");

    // Imprimir cada fila de la tabla
    for (int i = 0; i < numProductos; i++)
    {
        float impuestosProducto = calcularImpuestos(productos[i].precioVenta, 12.0, productos[i].cantidadSalida);
        totalImpuestos += impuestosProducto;

        printf(AZUL_T "%-8d %-20s %-18d %-18.2f %-15s %-15d %-15.2f %-15s %-15d %-15.2f\n",
               i, productos[i].nombre, productos[i].cantidadEntrada, productos[i].precioEntrada, productos[i].fechaIngreso,
               productos[i].cantidadSalida, productos[i].precioVenta, productos[i].fechaEgreso, productos[i].cantidadEntrada - productos[i].cantidadSalida, impuestosProducto);

        fprintf(archivoInventario, "%-8d %-20s %-18d %-18.2f %-15s %-15d %-15.2f %-15s %-15d %-15.f\n",
                i, productos[i].nombre, productos[i].cantidadEntrada, productos[i].precioEntrada, productos[i].fechaIngreso,
                productos[i].cantidadSalida, productos[i].precioVenta, productos[i].fechaEgreso, productos[i].cantidadEntrada - productos[i].cantidadSalida, impuestosProducto);
    }

    printf(VERDE_T "\nTotal de impuestos a pagar: %.2f\n" RESET_T, totalImpuestos);

    fclose(archivoInventario);
}

int main()
{
    const int MAX_PRODUCTOS = 100;
    struct Producto productos[MAX_PRODUCTOS];
    int numProductos = 0;

    while (1)
    {
        int opcion;
        printf("\nMenu de opciones:\n");
        printf("1. Ingreso de producto\n");
        printf("2. Indice de productos\n");
        printf("3. Egreso de producto\n");
        printf("4. Impuestos a pagar\n");
        printf("5. Mostrar inventario\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {

        case 1:
            // Ingreso de producto
            if (numProductos < MAX_PRODUCTOS)
            {
                printf("Ingrese el nombre del producto: ");
                scanf("%s", productos[numProductos].nombre);
                printf("Ingrese la cantidad de entrada: ");
                scanf("%d", &productos[numProductos].cantidadEntrada);
                printf("Ingrese el precio de entrada: ");
                scanf("%f", &productos[numProductos].precioEntrada);
                printf("Ingrese la fecha de ingreso (DDMMYYYY): ");
                scanf("%s", productos[numProductos].fechaIngreso);
                printf("Ingrese el precio de venta: ");
                scanf("%f", &productos[numProductos].precioVenta);

                numProductos++;
            }
            else
            {
                printf("No hay espacio para más productos.\n");
            }
            break;

        case 2:
            // Mostrar índice de productos
            printf("\n=== Indice de productos ===\n");
            for (int i = 0; i < numProductos; i++)
            {
                printf("Indice: %d, Nombre: %s\n", i, productos[i].nombre);
            }
            break;

        case 3:
            // Egreso de producto
            if (numProductos > 0)
            {
                int indice;
                printf("Ingrese el indice del producto a egresar (0-%d): ", numProductos - 1);
                scanf("%d", &indice);

                if (indice >= 0 && indice < numProductos)
                {
                    
                    printf("Ingrese la cantidad de salida: ");
                    scanf("%d", &productos[indice].cantidadSalida);
                    printf("Ingrese la fecha de egreso (DD/MM/YYYY): ");
                    scanf("%s", productos[indice].fechaEgreso);
                }
                else
                {
                    printf("Indice invalido.\n");
                }
            }
            else
            {
                printf("No hay productos para egresar.\n");
            }
            break;

        case 4:
            // Impuestos a pagar
            if (numProductos > 0)
            {
                float totalImpuestos = 0.0;

                for (int i = 0; i < numProductos; i++)
                {
                    totalImpuestos += calcularImpuestos(productos[i].precioVenta, 12.0, productos[i].cantidadSalida);
                }

                printf("Total de impuestos a pagar: %.2f\n", totalImpuestos);
            }
            else
            {
                printf("No hay productos para calcular impuestos.\n");
            }
            break;

        case 5:
            // Mostrar inventario y crear archivo de texto
            if (numProductos > 0)
            {
                mostrarInventario(productos, numProductos);
                printf("Inventario guardado en 'inventario.txt'\n");
            }
            else
            {
                printf("No hay productos en el inventario.\n");
            }
            break;

        case 6:
            // Salir del programa
            exit(0);
            break;

        default:
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    }

    return 0;
}