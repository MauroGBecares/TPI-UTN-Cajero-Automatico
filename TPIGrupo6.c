/*
Integrantes: 
Bécares, Mauro
Cano, Ludmila
Danyluk, Selene
Gerez, Brian.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define MAX_CLIENTES 10
#define MAX_INTENTOS 3
#define MAX_OPERACIONES 10

// Estructura para almacenar los datos de un cliente
typedef struct
{
    char numeroCuenta[4];
    char contrasena[7];
    char nombre[50];
    double saldo;
    bool estado;
} Cliente;

void cargarClientes(Cliente *clientes);
int validarContrasena(Cliente *clientes, char *passIngresada);
int validarUsuario(Cliente *clientes, char *cuentaIngresada);
void bloquearUsuario(Cliente *clientes, int indice);
int iniciarSesion(Cliente *clientes);
void mostrarInformacion(Cliente *cliente, int cantidadDeOperaciones);
void consultarSaldo(Cliente *cliente);
void extraer(Cliente *cliente);
void depositar(Cliente *cliente);

int main()
{
    int indice, opcion, cantidadDeOperaciones;
    bool cajeroEncendido = true;

    Cliente clientes[MAX_CLIENTES];

    cargarClientes(clientes);

    while (cajeroEncendido)
    {
        system("cls");
        printf("BIENVENIDOS.\n");
        printf("\n----- Inicio de Sesi%cn -----\n", 162);

        indice = iniciarSesion(clientes);

        if (indice >= 0 && clientes[indice].estado == true)
        {
            cantidadDeOperaciones = 0;
            do
            {
                printf("\n----- Men%c de Opciones -----\n", 163);
                printf("1) Dep%csito.\n", 162);
                printf("2) Extracci%cn.\n", 162);
                printf("3) Consultar saldo.\n");
                printf("4) Mostrar informaci%cn.\n", 162);
                printf("5) Salir de sesi%cn.\n", 162);
                printf("Ingrese la opci%cn deseada: ", 162);
                scanf("%d", &opcion);

                switch (opcion)
                {
                case 1:
                    system("cls");
                    depositar(&clientes[indice]);
                    cantidadDeOperaciones++;
                    break;
                case 2:
                    system("cls");
                    extraer(&clientes[indice]);
                    cantidadDeOperaciones++;
                    break;
                case 3:
                    system("cls");
                    consultarSaldo(&clientes[indice]);
                    cantidadDeOperaciones++;
                    break;
                case 4:
                    system("cls");
                    mostrarInformacion(&clientes[indice], cantidadDeOperaciones);
                    break;
                case 5:
                    system("cls");
                    break;
                default:
                    printf("Opci%cn inv%clida.\n", 162, 160);
                }
            } while (cantidadDeOperaciones < MAX_OPERACIONES && opcion != 5);
        }
        else
        {
            printf("Su cuenta se encuentra bloqueada, comun%cquese con la entidad bancaria para su restablecimiento.\n", 161);
            Sleep(3000);
            system("cls");
        }
        if (cantidadDeOperaciones >= MAX_OPERACIONES)
        {
            printf("Llego al limite de operaciones.Fin.Gracias!\n");
            Sleep(3000);
            system("cls");
        }
        if (opcion == 5)
        {
            system("cls");
            printf("Se ha cerrado sesi%cn correctamente.\n", 162);
            Sleep(3000);
        }
    }
    return 0;
}

//-----------------------------------------------CARGA DE DATOS-------------------------------------------------------------

//Funcion que carga los datos de los 10 clientes. 
void cargarClientes(Cliente *clientes)
{
    Cliente clientesDatos[MAX_CLIENTES] = {
        {"111", "1111", "Maria", 5000.0, true},
        {"222", "2222", "Pedro", 10000.0, true},
        {"333", "3333", "Eren", 5000.0, true},
        {"444", "4444", "Dani", 10000.0, true},
        {"555", "5555", "Pepe", 5.0, true},
        {"666", "6666", "Lola", 10000.0, true},
        {"777", "7777", "Marta", 5000.0, true},
        {"888", "8888", "Javier", 10000.0, true},
        {"999", "9999", "Juan", 5000.0, true},
        {"100", "1000", "Matias", 10000.0, true},
    };

    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        clientes[i] = clientesDatos[i];
    }
}

//-----------------------------------------------INICIO DE SESIÓN-------------------------------------------------------------

int iniciarSesion(Cliente *clientes)
{
    char cuentaIngresada[4], passIngresado[7];
    int cantidadDeIntentos = 0, indice;

    do
    {
        printf("Ingrese su n%cmero de cuenta: ", 163);
        scanf("%s", cuentaIngresada);
        printf("Ingrese su contrase%ca: ", 164);
        scanf("%s", passIngresado);

        indice = validarUsuario(clientes, cuentaIngresada);

        if (indice >= 0)
        {
            if (validarContrasena(&clientes[indice], passIngresado) == 1)
            {
                system("cls");
                if (clientes[indice].estado == true)
                    printf("Se inici%c sesi%cn correctamente\n", 162, 162);
                return indice;
            }
            else if (validarContrasena(&clientes[indice], passIngresado) == -1)
            {

                system("cls");
                printf("Contrase%ca incorrecta.\n", 164);
                cantidadDeIntentos++;
            }
        }
        else
        {
            system("cls");
            printf("Usuario y contrase%ca incorrectos.\n", 164);
        }

    } while (indice < 0 || cantidadDeIntentos < MAX_INTENTOS);

    if (cantidadDeIntentos >= MAX_INTENTOS)
    {
        printf("No se permiten m%cs intentos.\n", 160);
        bloquearUsuario(clientes, indice);
        return -1;
    }
}

// Función para validar contraseña
int validarContrasena(Cliente *clientes, char *passIngresada)
{

    if (strcmp(clientes->contrasena, passIngresada) == 0)
    {
        return 1;
    }

    return -1;
}

// Función para validar usuario
int validarUsuario(Cliente *clientes, char *cuentaIngresada)
{
    for (int i = 0; i < MAX_CLIENTES; i++)
    {
        if (strcmp(clientes[i].numeroCuenta, cuentaIngresada) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Función para bloquear usuario
void bloquearUsuario(Cliente *clientes, int indice)
{
    clientes[indice].estado = false;
}
//-----------------------------------------------MENÚ DE OPERACIONES-------------------------------------------------------------

// Función para realizar un depósito
void depositar(Cliente *cliente)
{
    double monto;
    do
    {
        system("cls");
        printf("Ingrese el monto a depositar: ");
        scanf("%lf", &monto);
        if (monto <= 0)
        {
            printf("Monto inv%clido.\n", 160);
            Sleep(3000);
        }
    } while (monto <= 0);

    cliente->saldo += monto;
    printf("Se ha depositado $%.2lf en su cuenta.\n", monto);
}

// Función para realizar una extracción
void extraer(Cliente *cliente)
{
    double monto;

    do
    {
        system("cls");
        printf("Ingrese el monto a extraer: ");
        scanf("%lf", &monto);
        if (monto <= 0)
        {
            printf("Monto inv%clido.\n", 160);
            Sleep(3000);
        }
    } while (monto <= 0);

    if (monto <= cliente->saldo)
    {
        cliente->saldo -= monto;
        printf("Se ha extra%cdo $%.2lf de su cuenta.\n", 161, monto);
    }
    else
    {
        printf("El monto a extraer supera el saldo disponible en su cuenta.\n");
        printf("Tu saldo disponible es: $%.2lf\n", cliente->saldo);
    }
}

// Función para consultar el saldo
void consultarSaldo(Cliente *cliente)
{
    printf("El saldo actual de su cuenta es: $%.2lf\n", cliente->saldo);
}

// Función para mostrar la cantidad de operaciones realizadas y el saldo actual
void mostrarInformacion(Cliente *cliente, int cantidadDeOperaciones)
{
    printf("Cantidad de operaciones realizadas: %i\n", cantidadDeOperaciones);
    printf("Saldo actual de su cuenta: $%.2lf\n", cliente->saldo);
}