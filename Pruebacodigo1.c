#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Kevin Maquis, Rodrigo Andrade, Jorge Ramos
struct Producto
{
    char nombre[50];
    float precioEntrada;
    char fechaIngreso[20];
    int cantidadEntrada;
    float precioVenta;
    char fechaEgreso[20];
    int cantidadSalida;
};
//Creamos una funcion donde nos calcule el impuesta de los productos que el ususario ingrese
float calcularImpuestos(float precio, float impuestoPorcentaje)
{
    return precio * impuestoPorcentaje / 100.0;
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

    fprintf(archivoInventario, "=== Inventario ===\n");

    for (int i = 0; i < numProductos; i++)
    {
        float impuestosProducto = calcularImpuestos(productos[i].precioVenta, 12.0);
        totalImpuestos += impuestosProducto;

        printf("%-10d", i);//Aqui imprime el numero de indice
        printf("%-20s", productos[i].nombre);//Aqui imprime el nombre que se asigno al producto
        printf("%-20.2f", productos[i].precioVenta);//Aqui imprime precio de cada producto
        printf("%-15.2f", impuestosProducto);//Aqui imprime impuesto del producto
        printf("%-12d", productos[i].cantidadEntrada);//Aqui imprime la cantidad de entrada
        printf("%-15s", productos[i].fechaIngreso);//Aqui imprime la fecha que se ingreso el producto
        printf("%-12d", productos[i].cantidadSalida);//Aqui imprime la cantidad de salida
        printf("%-15s", productos[i].fechaEgreso);//Aqui imprime el egreso
        printf("%-20d\n", productos[i].cantidadEntrada - productos[i].cantidadSalida);//Aqui imprime el restante de los productos
        //Aqui agrer un do-while para que imprima "-" y asi poder separar si hay mas de un producto
        int cantidadDeGuiones = 140;
        do
        {
            printf("-");
            cantidadDeGuiones--;
        } while (cantidadDeGuiones != 0);
        printf("\n");

        fprintf(archivoInventario, "\n=== Inventario ===\n");
        fprintf(archivoInventario, "%-10s%-20s%-12s%-15s%-12s%-15s%-20s%-20s%-15s\n", "Indice", "Nombre", "Ingresos", "Fecha", "Egresos", "Fecha", "Cantidad restante", "Precio de venta", "Impuestos");
        fprintf(archivoInventario, "%-10d", i);
        fprintf(archivoInventario, "%-20s", productos[i].nombre);
        fprintf(archivoInventario, "%-12d", productos[i].cantidadEntrada);
        fprintf(archivoInventario, "%-15s", productos[i].fechaIngreso);
        fprintf(archivoInventario, "%-12d", productos[i].cantidadSalida);
        fprintf(archivoInventario, "%-15s", productos[i].fechaEgreso);
        fprintf(archivoInventario, "%-20d", productos[i].cantidadEntrada - productos[i].cantidadSalida);
        fprintf(archivoInventario, "%-20.2f", productos[i].precioVenta);
        fprintf(archivoInventario, "%-15.2f\n", impuestosProducto);
        //Aqui agrer un do-while para que imprima "-" y asi poder separar si hay mas de un producto
        int cantidadDeGuionesarchivo = 140;
        do
        {
            fprintf(archivoInventario, "-");
            cantidadDeGuionesarchivo--;
        } while (cantidadDeGuionesarchivo != 0);
        fprintf(archivoInventario, "\n");
    }
    fprintf(archivoInventario, "Total de impuestos a pagar: %.2f\n", totalImpuestos);//Aqui imprimimos el total a pagar de impuestos de todos los productos
    printf("Total de impuestos a pagar: %.2f\n", totalImpuestos);//Aqui imprimimos el total a pagar de impuestos de todos los productos

    fclose(archivoInventario);
}

void imprimirGuiones(int cantidad)
{
    for (int j = 0; j < cantidad; j++)
    {
        printf("-");
    }
    printf("\n");
}

int main()
{
    const int MAX_PRODUCTOS = 100;
    struct Producto productos[MAX_PRODUCTOS];
    int numProductos = 0;
    int opcion;
    //Aqui esta el menu de opciones del programa donde segun lo que se escoja, el progrmara realizara una funcion
do
{
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
            // Ingreso de producto, esta funcion nos permite pedirle al usuario que ingrese los datos de los productos
            if (numProductos < MAX_PRODUCTOS)
            {
                printf("Ingrese el nombre del producto: ");
                scanf("%s", productos[numProductos].nombre);//Aqui pedimos el nombre del producto que se mostrara en pantalla
                printf("Ingrese el precio de entrada: ");
                scanf("%f", &productos[numProductos].precioEntrada);//Aqui pedimos el precio de mayorista del producto
                printf("Ingrese la fecha de ingreso: ");
                scanf("%s", productos[numProductos].fechaIngreso);//Aqui pedimos la fecha que se ingreso el producto
                printf("Ingrese la cantidad de entrada: ");
                scanf("%d", &productos[numProductos].cantidadEntrada);//Aqui pedimos la cantidad de producto que se ingreso
                printf("Ingrese el precio de venta: ");
                scanf("%f", &productos[numProductos].precioVenta);//Aqui pedimos el precio del producto al que se vendera
                numProductos++;
            }
            else
            {
                printf("No hay espacio para más productos.\n");
            }
            break;

        case 2:
            // Mostrar índice de productos, aqui la funcion practicamente nos permite visualizar el nombre del producto que fueron ingresados para asi poder saber y ir directamente a los egresos segun el programa
            printf("\n=== Indice de productos ===\n");
            for (int i = 0; i < numProductos; i++)
            {
                printf("Indice: %d, Nombre: %s\n", i, productos[i].nombre);
            }
            break;

        case 3:
            // Egreso de producto, pide al usuario agregar lo que se descontara de los productos ya ingresados 
            if (numProductos > 0)
            {
                int indice;
                printf("Ingrese el indice del producto a egresar (0-%d): ", numProductos - 1);
                scanf("%d", &indice);

                if (indice >= 0 && indice < numProductos)
                {
                    printf("Ingrese la fecha de egreso: ");
                    scanf("%s", productos[indice].fechaEgreso);
                    printf("Ingrese la cantidad de salida: ");
                    scanf("%d", &productos[indice].cantidadSalida);
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
                    totalImpuestos += calcularImpuestos(productos[i].precioVenta, 12.0);
                }

                printf("Total de impuestos a pagar: %.2f\n", totalImpuestos);
            }
            else
            {
                printf("No hay productos para calcular impuestos.\n");
            }
            break;

        case 5:
            printf("\n=== Inventario ===\n");
            printf("%-10s%-20s%-20s%-15s%-12s%-15s%-12s%-15s%-20s\n", "Indice", "Nombre", "Precio de venta", "Impuestos", "Ingresos", "Fecha", "Egresos", "Fecha", "Cantidad restante");
            // Mostrar inventario y crear archivo de texto
            if (numProductos > 0)
            {
                mostrarInventario(productos, numProductos);
                int cantidadDeGuiones = 140;
                imprimirGuiones(cantidadDeGuiones);
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
} while (opcion != 6);

    return 0;
}
