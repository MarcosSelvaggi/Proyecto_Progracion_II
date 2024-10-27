#include <iostream>
#include "Pedidos.h"
#include "PedidosArchivo.h"
#include "Productos.h"
#include "ProductosArchivo.h"

using namespace std;

Pedidos::Pedidos()
{
}
///Getters
string Pedidos::getNumPedido()
{
    return _numPedido;
}
string Pedidos::getNumCliente()
{
    return _numCliente;
}
string Pedidos::getNumLegajoEmpleado()
{
    return _numLegajoEmpleado;
}
string Pedidos::getDireccionDeEntre()
{
    return _direccionDeEntrega;
}
string Pedidos::getIdDelProducto()
{
    return _IdDelProducto;
}
string Pedidos::getNombreDelProducto()
{
    return _nombreProducto;
}
string Pedidos::getIdCategoriaProducto()
{
    return _IdCategoria;
}
string Pedidos::getCantidadSolicitada()
{
    return _cantidadSolicitada;
}
float Pedidos::getPrecioUnitario()
{
    return _precioUnitario;
}
string Pedidos::getDia()
{
    return _dia;
}
string Pedidos::getMes()
{
    return _mes;
}
string Pedidos::getAnio()
{
    return _anio;
}

///Setters
void Pedidos::setNumPedido(string numPedido)
{
    _numPedido = numPedido;
}

void Pedidos::setNumCliente(string numCliente)
{
    _numCliente = numCliente;
}
void Pedidos::setNumLegajoEmpleado(string numLegajo)
{
    _numLegajoEmpleado = numLegajo;
}
void Pedidos::setDireccionDeEntre(string direccion)
{
    _direccionDeEntrega = direccion;
}
void Pedidos::setIdDelProducto(string id)
{
    _IdDelProducto = id;
}
void Pedidos::setNombreDelProducto(string nombreProducto)
{
    _nombreProducto = nombreProducto;
}
void Pedidos::setIdCategoriaProducto(string idCategoria)
{
    _IdCategoria = idCategoria;
}
void Pedidos::setCantidadSolicitada(string cantidad)
{
    _cantidadSolicitada = cantidad;
}
void Pedidos::setPrecioUnitario(float precio)
{
    _precioUnitario = precio;
}
void Pedidos::setDia(string dia)
{
    _dia = dia;
}
void Pedidos::setMes(string mes)
{
    _mes = mes;
}
void Pedidos::setAnio(string anio)
{
    _anio = anio;
}

///Metodos
void Pedidos::realizarPedido()
{
    PedidosArchivo PedidoArchivo;
    PedidoArchivo.limpiarArchivoTemporal();
    int opcion;
    Pedidos pedido;
    do
    {
        cout << " ------------------------------------------ " << endl;
        cout << "|          ¨Qu‚ desea realizar?            |" << endl;
        cout << "| 1 - Agregar productos al carrito         |" << endl;
        cout << "| 2 - Mostrar carrito de compras           |" << endl;
        cout << "| 3 - Ajustar la cantidad de un producto   |" << endl;
        cout << "| 4 - Elimiar un producto del carrito      |" << endl;
        cout << "| 5 - Realizar pago                        |" << endl;
        cout << " ------------------------------------------ " << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            agregarProductosAlPedido(pedido);
            break;
        case 2:
            mostrarCarritoDeCompras();
            break;
        case 3:
            ajustarCantidadDeProducto();
            break;
        case 4:
            eliminarUnProductoDelCarrito();
            break;
        case 5:
            realizarPago();
            break;
        case 0:
            break;
        default:
            cout << "Error, ingrese una opci¢n correcta" << endl;
            break;
        }
    }
    while (opcion != 0);
}
void Pedidos::agregarProductosAlPedido(Pedidos pedido)
{
    PedidosArchivo PedidoArchivo;
    ProductosArchivo ProArchivo;
    Productos producto;
    Productos *listaDeProductos;

    int cantidadDeProductosEncontrados = 0, productoSolicitado;

    listaDeProductos = new Productos[ProArchivo.obtenerCantidadDeProductos()];

    string busqueda;
    cout << "Indique el nombre del producto a buscar" << endl;
    cin >> busqueda;

    bool productosNoEncontrados = true;

    producto.buscarUnProducto(listaDeProductos, busqueda, cantidadDeProductosEncontrados);

    for (int i = 0; i < cantidadDeProductosEncontrados; i++)
    {
        int stockActualDelProducto = atoi(listaDeProductos[i].getStockActual().c_str());
        if (stockActualDelProducto != 0)
        {
            cout << "-----------------------------" << endl;
            cout << "Producto Nø: " << i+1 << endl;
            producto.imprimirElProducto(listaDeProductos[i], 1);
            productosNoEncontrados = false;
        }
    }
    ///Si no pudo encontrar el producto en la lista de productos o este tiene stock en 0, va a avisarle al cliente
    ///Y saltearse los pasos para agregar el producto al carrito
    bool variableProvisoria;
    if (productosNoEncontrados)
    {
        cout << "No se ha encontrado ning£n :( " << endl;
    }
    else
    {
        ///Variable provisoria para el while mientras busca el pedido
        cout << "Ingrese el n£mero del producto que desea llevar, si no desea llevar ninguno presione 0" << endl;
        do
        {
            ///Revisar porqeu este if no funciona, sin importar que n£mero ingrese el usuario
            variableProvisoria = false;
            cin >> productoSolicitado;
            if (productoSolicitado == 0) {
                cout << "Entendido" << endl;
            }
            else if (productoSolicitado <= -1 && productoSolicitado > (cantidadDeProductosEncontrados + 1))
            {
                variableProvisoria = true;
                cout << "Error, ingrese un n£mero de producto correcto" << endl;
            }
        }
        while (variableProvisoria == true);

        cout << "Producto solicitado: " << productoSolicitado << " y variable provisoria " << variableProvisoria << endl;
        int cantidadDeUnidades, stockActualDelProducto = atoi(listaDeProductos[productoSolicitado].getStockActual().c_str());
        cout << "Cantidad de art¡culos: ";
        do
        {
            cin >> cantidadDeUnidades;
            if (cantidadDeUnidades > stockActualDelProducto)
            {
                cout << "Lo sentimos, s¢lo se encuentran disponibles " << stockActualDelProducto << " de unidades" << endl;
            }
        }
        while (cantidadDeUnidades > stockActualDelProducto);
        listaDeProductos[productoSolicitado].getStockActual();


        //PedidoArchivo.guardarPedidoEnArchivoTemporal(listaDeProductos[productoSolicitado]);
    }
}

void Pedidos::mostrarCarritoDeCompras() {}
void Pedidos::ajustarCantidadDeProducto() {}
void Pedidos::eliminarUnProductoDelCarrito() {}
bool Pedidos::realizarPago() {}
