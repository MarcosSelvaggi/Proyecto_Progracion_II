#include <iostream>
#include "Pedidos.h"
#include "PedidosArchivo.h"
#include "Productos.h"
#include "ProductosArchivo.h"
#include <time.h>
/*
Como usar el time.h para obtener el d¡a, mes y anio y poder usarlos en los pedidos
https://www.youtube.com/watch?v=0DtPa0HYQek

*/
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
    /*
    time_t diaActual = time(0);
    tm *ltm = localtime(&diaActual);
    cout << "A¤o: " << 1900 + ltm->tm_year << endl;
    cout << "Mes: " << 1 + ltm->tm_mon << endl;
    cout << "Dia: " << ltm->tm_mday << endl;
    cout << endl;
    */
    PedidosArchivo PedidoArchivo;
    ///Esto limpia el archivo temporal cada vez que entramos a la parte de realizar un pedido
    PedidoArchivo.limpiarArchivoTemporal();
    Pedidos pedido;
    int opcion;
    do
    {
        cout << " ------------------------------------------ " << endl;
        cout << "|          ¨Qu‚ desea realizar?            |" << endl;
        cout << "| 1 - Agregar productos al carrito         |" << endl;
        cout << "| 2 - Mostrar carrito de compras           |" << endl;
        cout << "| 3 - Ajustar la cantidad de un producto   |" << endl;
        cout << "| 4 - Elimiar un producto del carrito      |" << endl;
        cout << "| 5 - Realizar pago                        |" << endl;
        cout << "| 0 - Salir                                |" << endl;
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
    listaDeProductos = new Productos[ProArchivo.obtenerCantidadDeProductos()];

    ///Variables auxiliares para la busqueda de los productos
    int cantidadDeProductosEncontrados = 0, productoSolicitado = 0;
    string busqueda;
    bool productosNoEncontrados = true, variableProvisoria;///Variable con nombre provisorio para el while mientras busca el producto

    cout << "Indique el nombre del producto a buscar" << endl;
    cin >> busqueda;

    producto.buscarUnProducto(listaDeProductos, busqueda, cantidadDeProductosEncontrados);
    for (int i = 0; i < cantidadDeProductosEncontrados; i++)
    {
        int stockActualDelProducto = atoi(listaDeProductos[i].getStockActual().c_str());
        int stockMinimoDelProducto = atoi(listaDeProductos[i].getStockMinimo().c_str());
        if (stockActualDelProducto > stockMinimoDelProducto)
        {
            cout << "-----------------------------" << endl;
            cout << "Producto Nø: " << i+1 << endl;
            producto.imprimirElProducto(listaDeProductos[i], 1);
            productosNoEncontrados = false;
        }
    }

    ///Si no pudo encontrar el producto en la lista de productos o este tiene stock en 0, va a avisarle al cliente
    ///Y saltearse los pasos para agregar el producto al carrito
    if (productosNoEncontrados)
    {
        cout << "No se ha encontrado ning£n :( " << endl;
    }
    else
    {
        cout << "Ingrese el n£mero del producto que desea llevar, si no desea llevar ninguno presione 0" << endl;
        do
        {
            variableProvisoria = false;
            cin >> productoSolicitado;
            if (productoSolicitado == 0)
            {
                cout << "Entendido" << endl;
            }
            else if (productoSolicitado <= -1 || (productoSolicitado > (cantidadDeProductosEncontrados)))
            {
                variableProvisoria = true;
                cout << "Error, ingrese un n£mero de producto correcto" << endl;
            }
            else
            {
                cout << "Cantidad de art¡culos a agregar al carrito: ";
                int cantidadDeUnidades = 0;
                int stockActualDelProducto = atoi(listaDeProductos[productoSolicitado - 1].getStockActual().c_str());
                do
                {
                    cin >> cantidadDeUnidades;
                    if (cantidadDeUnidades > stockActualDelProducto)
                    {
                        cout << "Lo sentimos, s¢lo se encuentran disponibles " << stockActualDelProducto << " de unidades" << endl;
                    }
                }
                while (cantidadDeUnidades > stockActualDelProducto);
                ///Agregando la lista de productos al archivo temporal
                pedido.setIdDelProducto(listaDeProductos[productoSolicitado - 1].getSku());
                pedido.setNombreDelProducto(listaDeProductos[productoSolicitado - 1].getNombreProducto());
                pedido.setCantidadSolicitada(to_string(cantidadDeUnidades));
                pedido.setPrecioUnitario(listaDeProductos[productoSolicitado - 1].getPrecioProducto());
                if (PedidoArchivo.guardarPedidoEnArchivoTemporal(pedido))
                {
                    cout << "Se ha agregado el producto al carrito de compras" << endl;
                }
                else
                {
                    cout << "No se ha podido guardar el producto en el carrito de compras" << endl;
                }
            }
        }
        while (variableProvisoria == true);
    }
    delete[] listaDeProductos;

}

void Pedidos::mostrarCarritoDeCompras()
{
    bool carritoVacio = true;
    PedidosArchivo pedidoArchivo;
    Pedidos *pedidoArray;
    pedidoArray = new Pedidos[pedidoArchivo.obtenerCantidadDeProductosEnCarrito()];
    pedidoArchivo.leerPedidoEnArchivoTemporal(pedidoArray);

    float totalCarrito = 0.f, cantidadDeProductos = 0.f;

    for (int i = 0; i < pedidoArchivo.obtenerCantidadDeProductosEnCarrito(); i++)
    {

        cout << pedidoArray[i].getNombreDelProducto() << " | " << pedidoArray[i].getPrecioUnitario() << endl;
        cantidadDeProductos = stof(pedidoArray[i].getCantidadSolicitada());
        totalCarrito += (pedidoArray[i].getPrecioUnitario() * cantidadDeProductos);
        carritoVacio = false;
    }

    if (carritoVacio)
    {
        cout << "El carrito est  vac¡o, intenta agregando m s productos :)" << endl;
    }
    else
    {
        cout << "Total $"<<  totalCarrito << endl;
    }

    delete[] pedidoArray;
}
void Pedidos::ajustarCantidadDeProducto() {}
void Pedidos::eliminarUnProductoDelCarrito() {}
bool Pedidos::realizarPago()
{
    return true;
}
