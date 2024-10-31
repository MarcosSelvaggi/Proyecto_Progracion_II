#include "PedidosArchivo.h"
#include "Productos.h"
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

bool PedidosArchivo::productoEnElCarrito(string numProducto)
{
    PedidosArchivo PArchivos;
    Pedidos *pedido;
    pedido = new Pedidos[PArchivos.obtenerCantidadDeProductosEnCarrito()];
    PArchivos.leerPedidoEnArchivoTemporal(pedido);

    for (int i = 0; i < PArchivos.obtenerCantidadDeProductosEnCarrito();i++)
    {
        if (numProducto == pedido[i].getIdDelProducto()) return true;
    }
    return false;
}

int PedidosArchivo::obtenerCantidadDePedidosRealizados()
{
    int cantidadDePedidos = 0;

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

///Metodo auxiliar para obtener la cantidad de l¡neas que tiene el CSV
int PedidosArchivo::cantidadDeVentasGuardadas()
{
    int cantidadDePedidos = 0;

    ifstream ArchivoVentas("Ventas.csv");
    if (!ArchivoVentas.is_open())
    {
        return -1;
    }

    string linea;

    getline(ArchivoVentas, linea);

    while (getline(ArchivoVentas, linea))
    {
         cantidadDePedidos++;

    }
    return cantidadDePedidos;
}

void PedidosArchivo::generarFactura(Pedidos &pedido)
{
    string nombreArchivo;
    PedidosArchivo PArchivo;
    nombreArchivo = "facturas\\Factura pedido Numero " + to_string(PArchivo.obtenerCantidadDePedidosRealizados() + 1) + ".csv";
    if (PArchivo.obtenerCantidadDeProductosEnCarrito() == 0) return;
    Pedidos *listaProductos;
    listaProductos = new Pedidos[PArchivo.obtenerCantidadDeProductosEnCarrito()];
    PArchivo.leerPedidoEnArchivoTemporal(listaProductos);

    ofstream ArchivoVentas(nombreArchivo, ios::app);
    if (!ArchivoVentas.is_open())
    {
        return;
    }
    ArchivoVentas << "IdVenta, IdCliente, IdProducto, nombreProducto, cantidadSolicitada, precioUnitario, anio, mes, dia, direccionDeEntrega \n";
    Productos producto;
    for (int i = 0; i < PArchivo.obtenerCantidadDeProductosEnCarrito(); i++)
    {
        int cantidadDeProductos = atoi(listaProductos[i].getCantidadSolicitada().c_str());
        producto.modificarStockActual(listaProductos[i].getIdDelProducto(), cantidadDeProductos);
        ArchivoVentas << pedido.getNumPedido() << ","
                      << pedido.getNumCliente() << ","
                      << listaProductos[i].getIdDelProducto() << ","
                      << listaProductos[i].getNombreDelProducto() << ","
                      << listaProductos[i].getCantidadSolicitada() << ","
                      << listaProductos[i].getPrecioUnitario() << ","
                      << pedido.getAnio() << ","
                      << pedido.getMes() << ","
                      << pedido.getDia() << ","
                      << pedido.getDireccionDeEntrega() << "\n";

    }
    ArchivoVentas.close();
    delete[] listaProductos;
}

void PedidosArchivo::cargarDatosDeVentas(Pedidos *listaPedidos)
{
    ifstream archivoVentas("Ventas.csv");

    if (!archivoVentas.is_open())
    {
        return;
    }

    string linea, infoPedido;
    //Descartar el encabezado
    getline(archivoVentas, linea);
    int ubicacionDelPedido = 0;

    while (getline(archivoVentas, linea))
    {
        stringstream manejarDatos(linea);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setNumPedido(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setNumCliente(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setNumLegajoEmpleado(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setIdDelProducto(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setNombreDelProducto(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setCantidadSolicitada(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setPrecioUnitario(stof(infoPedido.c_str()));

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setAnio(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setMes(infoPedido);

        getline(manejarDatos, infoPedido, ',');
        listaPedidos[ubicacionDelPedido].setDia(infoPedido);
        ubicacionDelPedido++;
    }

    archivoVentas.close();

}
