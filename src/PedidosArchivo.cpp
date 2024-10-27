#include "PedidosArchivo.h"
#include <string>
#include <fstream>

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

    ArchivoTemporal << "IdPedido, NumCliente, LegajoEmpleado, IdProducto, NombreProducto, CantidadSolicitada, PrecioUnitario, Anio, Mes, Dia \n";

    ArchivoTemporal.close();
}
bool PedidosArchivo::guardarPedidoEnArchivoTemporal(Pedidos &pedido)
{
    ofstream ArchivoTemporal("ArchivoDePedidoTemporal.csv", ios::app);

    if (!ArchivoTemporal.is_open())
    {
        return false;
    }

    ArchivoTemporal << pedido.getNumPedido() << ","
                    << pedido.getNumCliente() << ","
                    << pedido.getNumLegajoEmpleado() << ","
                    << pedido.getIdDelProducto() << ","
                    << pedido.getNombreDelProducto() << ","
                    << pedido.getCantidadSolicitada() << ","
                    << pedido.getPrecioUnitario() << ","
                    << pedido.getAnio() << ","
                    << pedido.getMes() << ","
                    << pedido.getDia() << "\n";

    ArchivoTemporal.close();
    return true;
}


void PedidosArchivo::generarFactura(Pedidos &pedido){}
