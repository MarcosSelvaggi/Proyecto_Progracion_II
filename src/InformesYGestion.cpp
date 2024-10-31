#include "InformesYGestion.h"
#include <iostream>
#include <string>
#include "Pedidos.h"
#include "PedidosArchivo.h"
#include "Empleados.h"
#include "EmpleadosArchivos.h"
#include "Clientes.h"
#include "ClientesArchivo.h"

using namespace std;

InformesYGestion::InformesYGestion()
{
    //ctor
}

void InformesYGestion::visualizarVentas()
{
    ///Declaraci¢n de variables u objetos
    PedidosArchivo PeArchivos;
    Pedidos *listaPedidos;
    listaPedidos = new Pedidos[PeArchivos.cantidadDeVentasGuardadas()];
    PeArchivos.cargarDatosDeVentas(listaPedidos);

    int opcion = 0;
    cout << "¨Desea visualizar todos los pedidos o buscar uno en especial?" << endl;
    cout << "1 - Para ver todos los pedidos" << endl;
    cout << "2 - Para buscar un pedido en especial" << endl;
    cin >> opcion;

    string pedidoAnterior = "0";

    switch (opcion)
    {
    case 1:
        for (int i = 0; i < PeArchivos.cantidadDeVentasGuardadas(); i++)
        {
            if (pedidoAnterior!= listaPedidos[i].getNumPedido())
            {
                mostrarPedidoPorPantalla(listaPedidos[i], true);
            }
            else
            {
                mostrarPedidoPorPantalla(listaPedidos[i], false);
            }
            pedidoAnterior = listaPedidos[i].getNumPedido();
        }
        system("pause");
        break;
    case 2:
    {
        bool noEncontrado = true;
        string pedidoAVisualizar;
        float total = 0;
        cout << "¨Qu‚ pedido desea visualizar?, ingrese el n£mero entre 1 y " << PeArchivos.obtenerCantidadDePedidosRealizados() << endl;
        cin >> pedidoAVisualizar;

        for (int i = 0; i < PeArchivos.cantidadDeVentasGuardadas(); i++)
        {
            if (pedidoAVisualizar == listaPedidos[i].getNumPedido())
            {
                if (pedidoAnterior != listaPedidos[i].getNumPedido())
                {
                    mostrarPedidoPorPantalla(listaPedidos[i], true);
                }
                else
                {
                    mostrarPedidoPorPantalla(listaPedidos[i], false);
                }
                pedidoAnterior = listaPedidos[i].getNumPedido();
                total += listaPedidos[i].getPrecioUnitario() * stof(listaPedidos[i].getCantidadSolicitada().c_str());
                noEncontrado = false;
            }
        }
        if (noEncontrado)
        {
            cout << "No hay ning£n pedido con ese n£mero de orden" << endl;
        }
        else
        {
            cout << "Total \t \t \t \t \t \t $" << total << endl;
        }
        system("pause");
        break;
    }
    default:
        cout << "Error, opci¢n no valida" << endl;
        break;
    }
    delete[] listaPedidos;
}

void InformesYGestion::mostrarPedidoPorPantalla(Pedidos &pedido, bool primeraVuelta)
{

    if (primeraVuelta)
    {
        Empleados emp;
        EmpleadosArchivos empArch;
        Clientes cliente;
        ClientesArchivo ClArchivo;
        int aux = atoi(pedido.getNumLegajoEmpleado().c_str());
        //No olvidar de restarle 1 porque sino no puede encontrar al empleado correcto
        emp = empArch.leerEmpleado(aux - 1);
        aux = stoi(pedido.getNumCliente());
        ClArchivo.buscarCliente(cliente, aux);
        cout << "Pedido Nø  " << pedido.getNumPedido() << endl;
        cout << "Cliente Nø " << pedido.getNumCliente() << endl;
        cout << "Nombre Cliente: " << cliente.getNombre() << endl;
        cout << "Armado por " << emp.getNombre() << " " << emp.getApellido() << endl;
        cout << "Producto \t \t  | Unidades \t| Precio unitario " << endl;
    }

    string nombreProducto = pedido.getNombreDelProducto();
    for (int f = nombreProducto.length(); f < 25 ; f++ )
    {
        nombreProducto = nombreProducto + " ";
    }
    cout <<"|"<< nombreProducto <<"|\t" << pedido.getCantidadSolicitada() <<"\t|\t $" <<  pedido.getPrecioUnitario() << endl;
}
