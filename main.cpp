#include <iostream>
#include "Empleados.h"
#include "Clientes.h"
#include "Productos.h"
#include "Pedidos.h"
#include <windows.h> ///Si no se cambia el tama¤o de la fuente no es necesario incluir windows.h

/*
    TODO LIST:
        *Crear lista completa con todos los productos
        *Mejorar la forma en como se ven las facturas
        *Metodo para crear los recibos de los cliente
        *Crear los informes

        *"Baja prioridad", realizar si hay tiempo y todo lo de arriba se termino
            *Cambiar la forma en como se manejan los clientes y empleados
                *Todo a string y con csv, en vez de char y archivo dat
*/
using namespace std;

int main()
{
    ///Cambia el tama¤o de la consola
    //system("mode 650");

    ///Pone la consola en pantalla completa
    //HWND consoleWindow = GetConsoleWindow();
    //ShowWindow(consoleWindow, SW_MAXIMIZE);

    ///Cambia el tama¤o de la fuente, toca ver un poco m s
    /*
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 700;
    fontex.dwFontSize.X = 36;
    fontex.dwFontSize.Y = 36; */ ///Cambia el tama¤o de la fuente

    /// Con esto cambia la fuente de la consola, quise poner Calibri pero se ve fea :(
    /*wcscpy(fontex.FaceName, L"Calibri");
    SetCurrentConsoleFontEx(hOut, 0, &fontex);
    */
    int opcion;
    do
    {
        system("cls");
        cout << "---------------- Bienvenido ----------------" << endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Gesti¢n de empleados" << endl;
        cout << "2 - Gesti¢n de clientes" << endl;
        cout << "3 - Gesti¢n de inventario" << endl;
        cout << "4 - Realizar un pedido" << endl;
        cout << "5 - Gesti¢n de pedidos" << endl;
        cout << "6 - Informes" << endl;
        cout << "0 - Salir " << endl;
        cout << "--------------------------------------------" << endl;
        cin >> opcion;
        system("cls");
        switch (opcion)
        {
        case 1:
        {
            Empleados empleado;
            empleado.menuEmpleados();
            break;
        }
        case 2:
        {
            Clientes cliente;
            cliente.menuClientes();
            break;
        }
        case 3:
        {
            Productos producto;
            producto.menuProductos();
            break;
        }
        case 4:
        {
            Pedidos Pedido;
            Pedido.realizarPedido();
            break;
        }
        case 0:
            cout << "Saliendo... " << endl;
            break;
        default:
            cout << "Error, ingrese un valor correcto " << endl;
            break;
        }
    }
    while (opcion != 0);
    return 0;
}
