#include "PedidosArchivo.h"
#include "Productos.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

PedidosArchivo::PedidosArchivo()
{
}
void PedidosArchivo::limpiarArchivoTemporal()
{
    ofstream ArchivoTemporal("ArchivoDePedidoTemporal.csv");

    if (!ArchivoTemporal.is_open())
    {
        return;
    }

    ArchivoTemporal << "IdProducto, NombreProducto, CantidadSolicitada, PrecioUnitario, stockActual\n";

    ArchivoTemporal.close();
}
int PedidosArchivo::obtenerCantidadDeProductosEnCarrito()
{
    ifstream ArchivoTemporal("ArchivoDePedidoTemporal.csv");

    if (!ArchivoTemporal.is_open())
    {
        return -1;
    }
    int cantidad = 0;

    string linea;
    getline(ArchivoTemporal, linea);

    while(getline(ArchivoTemporal, linea))
    {
        cantidad++;
    }
    ArchivoTemporal.close();
    return cantidad;
}

bool PedidosArchivo::guardarPedidoEnArchivoTemporal(Pedidos &pedido)
{
    ofstream ArchivoTemporal("ArchivoDePedidoTemporal.csv", ios::app);

    if (!ArchivoTemporal.is_open())
    {
        return false;
    }

    ArchivoTemporal << pedido.getIdDelProducto() << ","
                    << pedido.getNombreDelProducto() << ","
                    << pedido.getCantidadSolicitada() << ","
                    << pedido.getPrecioUnitario() << ","
                    << pedido.getStockDelProducto() << "\n";

    ArchivoTemporal.close();
    return true;
}

void PedidosArchivo::leerPedidoEnArchivoTemporal(Pedidos *pedido)
{
    ifstream ArchivoTemporal("ArchivoDePedidoTemporal.csv");

    if (!ArchivoTemporal.is_open())
    {
        return;
    }
    int ubicacionEnArray = 0;
    string linea;
    getline(ArchivoTemporal, linea);

    while(getline(ArchivoTemporal, linea))
    {
        stringstream lineaDelPedido(linea);
        string infoDelPedido;

        getline(lineaDelPedido, infoDelPedido, ',');
        pedido[ubicacionEnArray].setIdDelProducto(infoDelPedido);

        getline(lineaDelPedido, infoDelPedido, ',');
        pedido[ubicacionEnArray].setNombreDelProducto(infoDelPedido);

        getline(lineaDelPedido, infoDelPedido, ',');
        pedido[ubicacionEnArray].setCantidadSolicitada(infoDelPedido);

        getline(lineaDelPedido, infoDelPedido, ',');
        pedido[ubicacionEnArray].setPrecioUnitario(stof(infoDelPedido.c_str()));
        getline(lineaDelPedido, infoDelPedido, ',');
        pedido[ubicacionEnArray].setStockDelProducto(infoDelPedido);
        ubicacionEnArray++;
    }

    ArchivoTemporal.close();
}
///Recibe el n£mero del producto a modificar, su nueva cantidad en caso de que corresponda y caso contrario recibe el booleano que lo elimina
void PedidosArchivo::modificarCantidadDeArticulosCarrito(int numProducto, int cantidadDeArticulos, bool eliminado)
{
    PedidosArchivo PedidoArchivo;
    Pedidos *listaProductos;
    listaProductos = new Pedidos[PedidoArchivo.obtenerCantidadDeProductosEnCarrito()];

    ///Variable importante para tener la cantidad de art¡culos del pedido antes de limpiarlo
    int cantidadDeProductosAntesDeLimpiar = PedidoArchivo.obtenerCantidadDeProductosEnCarrito();

    PedidoArchivo.leerPedidoEnArchivoTemporal(listaProductos);
    numProducto--;

    for (int i = 0; i < cantidadDeProductosAntesDeLimpiar; i++)
    {
        if (i == numProducto)
        {
            listaProductos[i].setCantidadSolicitada(to_string(cantidadDeArticulos));
        }
    }

    PedidoArchivo.limpiarArchivoTemporal();

    for (int i = 0; i < cantidadDeProductosAntesDeLimpiar; i++)
    {
        if (eliminado)
        {
            if (i == numProducto)
            {

            }
            else
            {
                PedidoArchivo.guardarPedidoEnArchivoTemporal(listaProductos[i]);
            }
        }
        else
        {
            PedidoArchivo.guardarPedidoEnArchivoTemporal(listaProductos[i]);
        }
    }

    delete[] listaProductos;
}
bool PedidosArchivo::registrarCompra(Pedidos &pedido)
{
    PedidosArchivo PArchivo;
    if (PArchivo.obtenerCantidadDeProductosEnCarrito() == 0) return false;
    Pedidos *listaProductos;
    listaProductos = new Pedidos[PArchivo.obtenerCantidadDeProductosEnCarrito()];
    PArchivo.leerPedidoEnArchivoTemporal(listaProductos);

    ofstream ArchivoVentas("Ventas.csv", ios::app);
    if (!ArchivoVentas.is_open())
    {
        return false;
    }
    Productos producto;
    for (int i = 0; i < PArchivo.obtenerCantidadDeProductosEnCarrito(); i++)
    {
        int cantidadDeProductos = atoi(listaProductos[i].getCantidadSolicitada().c_str());
        producto.modificarStockActual(listaProductos[i].getIdDelProducto(), cantidadDeProductos);
        ArchivoVentas << pedido.getNumPedido() << ","
                      << pedido.getNumCliente() << ","
                      << pedido.getNumLegajoEmpleado() << ","
                      << listaProductos[i].getIdDelProducto() << ","
                      << listaProductos[i].getNombreDelProducto() << ","
                      << listaProductos[i].getCantidadSolicitada() << ","
                      << listaProductos[i].getPrecioUnitario() << ","
                      << pedido.getAnio() << ","
                      << pedido.getMes() << ","
                      << pedido.getDia() << "\n";

    }
    ArchivoVentas.close();
    delete[] listaProductos;
    return true;
}
int PedidosArchivo::obtenerCantidadDePedidosRealizados()
{
    int cantidadDePedidos = 1;

    ifstream ArchivoVentas("Ventas.csv");
    if (!ArchivoVentas.is_open())
    {
        return -1;
    }

    string linea, datos, datoAComparar = "0";

    getline(ArchivoVentas, linea);

    while (getline(ArchivoVentas, linea))
    {
        stringstream infoPedido(linea);

        getline(infoPedido, datos, ',');

        if (datos != datoAComparar) cantidadDePedidos++;

        datoAComparar = datos;
    }
    return cantidadDePedidos;
}

void PedidosArchivo::generarFactura(Pedidos &pedido)
{
    string nombreArchivo;
    PedidosArchivo PArchivo;
    nombreArchivo = "facturas\\Factura pedido Numero" + to_string(PArchivo.obtenerCantidadDePedidosRealizados()) + ".csv";
    if (PArchivo.obtenerCantidadDeProductosEnCarrito() == 0) return;
    Pedidos *listaProductos;
    listaProductos = new Pedidos[PArchivo.obtenerCantidadDeProductosEnCarrito()];
    PArchivo.leerPedidoEnArchivoTemporal(listaProductos);

    ofstream ArchivoVentas(nombreArchivo, ios::app);
    if (!ArchivoVentas.is_open())
    {
        return;
    }
    Productos producto;
    for (int i = 0; i < PArchivo.obtenerCantidadDeProductosEnCarrito(); i++)
    {
        int cantidadDeProductos = atoi(listaProductos[i].getCantidadSolicitada().c_str());
        producto.modificarStockActual(listaProductos[i].getIdDelProducto(), cantidadDeProductos);
        ArchivoVentas << pedido.getNumPedido() << ","
                      << pedido.getNumCliente() << ","
                      << pedido.getNumLegajoEmpleado() << ","
                      << listaProductos[i].getIdDelProducto() << ","
                      << listaProductos[i].getNombreDelProducto() << ","
                      << listaProductos[i].getCantidadSolicitada() << ","
                      << listaProductos[i].getPrecioUnitario() << ","
                      << pedido.getAnio() << ","
                      << pedido.getMes() << ","
                      << pedido.getDia() << "\n";

    }
    ArchivoVentas.close();
    delete[] listaProductos;
}
