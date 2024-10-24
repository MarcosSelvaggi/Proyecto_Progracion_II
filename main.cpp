#include <iostream>
#include "Empleados.h"
#include "Clientes.h"
#include "Productos.h"

using namespace std;

int main()
{
    int opcion;
    do
    {
        system("cls");
        cout << "---------------- Bienvenido ----------------" << endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Gesti¢n de empleados" << endl;
        cout << "2 - Gesti¢n de clientes" << endl;
        cout << "3 - Gesti¢n de inventario" << endl;
        cout << "5 - Gesti¢n de pedidos" << endl;
        cout << "6 - Informes" << endl;
        cout << "0 - Salir " << endl;
        cin >> opcion;

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
