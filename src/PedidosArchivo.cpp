#include "PedidosArchivo.h"
#include <string>
#include <fstream>
#include <sstream>

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

    ArchivoTemporal << "IdProducto, NombreProducto, CantidadSolicitada, PrecioUnitario \n";

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
                    << pedido.getPrecioUnitario() << "\n";

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
        ubicacionEnArray++;
    }

    ArchivoTemporal.close();
}


void PedidosArchivo::generarFactura(Pedidos &pedido) {}
