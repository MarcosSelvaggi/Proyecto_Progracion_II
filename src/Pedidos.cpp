#include <iostream>
#include "Pedidos.h"
#include "PedidosArchivo.h"
#include "Productos.h"
#include "ProductosArchivo.h"
#include "EmpleadosArchivos.h"
#include "Clientes.h"
#include "ClientesArchivo.h"
#include <time.h>
#include <string>
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
string Pedidos::getDireccionDeEntrega()
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
string Pedidos::getStockDelProducto()
{
    return _stockDelProducto;
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
void Pedidos::setDireccionDeEntrega(string direccion)
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
void Pedidos::setStockDelProducto(string stockProducto)
{
    _stockDelProducto = stockProducto;
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
    Pedidos pedido;
    int opcion;
    do
    {
        cout << " ------------------------------------------ " << endl;
        cout << "|          ¨Qu‚ desea realizar?            |" << endl;
        cout << "| 1 - Agregar productos al carrito         |" << endl;
        cout << "| 2 - Mostrar carrito de compras           |" << endl;
        cout << "| 3 - Ajustar la cantidad de un producto   |" << endl;
        cout << "| 4 - Limpiar carrito                      |" << endl;
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
            ///Esto limpia el archivo temporal cada vez que entramos a la parte de realizar un pedido
            PedidoArchivo.limpiarArchivoTemporal();
            break;
        case 5:
        {

            int pedidoRealizado = realizarPago();
            if (pedidoRealizado == 1)
            {
                cout << "Se ha realizado el pago de forma exitosa" << endl;
                PedidoArchivo.limpiarArchivoTemporal();
            }
            else if (pedidoRealizado == 0)
            {
                cout << "Hubo un error al procesar el pago" << endl;
            }
            else if (pedidoRealizado == 2)
            {
                cout << "El cliente se encuentra inactivo" << endl;
            }
            else
            {
                cout << "No hay ning£n usuario registrado con ese mail" << endl;
            }
            break;
        }
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

    producto.buscarUnProductoConStock(listaDeProductos, busqueda, cantidadDeProductosEncontrados);
    for (int i = 0; i < cantidadDeProductosEncontrados; i++)
    {
        cout << "-----------------------------" << endl;
        cout << "Producto Nø: " << i+1 << endl;
        producto.imprimirElProducto(listaDeProductos[i], 1);
        productosNoEncontrados = false;
    }

    ///Si no pudo encontrar el producto en la lista de productos o este tiene stock en 0, va a avisarle al cliente
    ///Y saltearse los pasos para agregar el producto al carrito
    if (productosNoEncontrados)
    {
        cout << "No se ha encontrado ning£n producto :( " << endl;
    }
    else
    {
        cout << "Ingrese el n£mero del producto que desea llevar, si no desea llevar ninguno presione 0 " << endl;
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
            else if (PedidoArchivo.productoEnElCarrito(listaDeProductos[productoSolicitado - 1].getSku()))
            {
                cout << "Ese producto ya se encuentra en el carrito" << endl;
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
                pedido.setStockDelProducto(listaDeProductos[productoSolicitado - 1].getStockActual());
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
    ///Esto se ve feo, ver si se puede cambiar para que se vea mejor
    cout << " --------------------------------------------------------------" << endl;
    cout << "|Productos" << "\t\t  "<< "| Unidades \t|  Precio Unitario \t|" << endl;

    for (int i = 0; i < pedidoArchivo.obtenerCantidadDeProductosEnCarrito(); i++)
    {
        ///Este string nombreProducto es usado para despu‚s agregarle espacios vac¡os para que
        ///todo quede organizado en un cuadro por decirlo de alguna manera
        string nombreProducto = pedidoArray[i].getNombreDelProducto();
        for (int f = nombreProducto.length(); f < 25 ; f++ )
        {
            nombreProducto = nombreProducto + " ";
        }
        cout <<"|"<< nombreProducto <<"|\t" << pedidoArray[i].getCantidadSolicitada() <<"\t|\t $" << pedidoArray[i].getPrecioUnitario() <<"\t"<< "|" << endl;
        cantidadDeProductos = stof(pedidoArray[i].getCantidadSolicitada());
        totalCarrito += (pedidoArray[i].getPrecioUnitario() * cantidadDeProductos);
        carritoVacio = false;
    }

    if (carritoVacio)
    {
        cout << "|El carrito est  vac¡o, intenta agregando m s productos :) \t|" << endl;
    }
    else
    {
        cout << "|Total" << "\t\t\t\t\t\t" << " $"<<  totalCarrito << "\t|" << endl;
    }

    cout << " --------------------------------------------------------------" << endl;

    delete[] pedidoArray;
}
void Pedidos::ajustarCantidadDeProducto()
{
    PedidosArchivo PedidoArchivo;
    if (PedidoArchivo.obtenerCantidadDeProductosEnCarrito() == 0)
    {
        cout << "El carrito est  vac¡o, intenta agregando m s productos :)\t" << endl;
    }
    else
    {
        Pedidos pedido;
        Pedidos *listaProductos;
        listaProductos = new Pedidos[PedidoArchivo.obtenerCantidadDeProductosEnCarrito()];
        PedidoArchivo.leerPedidoEnArchivoTemporal(listaProductos);

        int opcionProducto;
        pedido.mostrarCarritoDeCompras();
        cout << "¨Qu‚ producto quiere modificar?, ingrese el n£mero del producto, caso contrario oprima 0" << endl;
        cin >> opcionProducto;
        if (opcionProducto == 0)
        {
            cout << "Entendido, saliendo" << endl;
        }
        else if (opcionProducto <= -1 || opcionProducto > PedidoArchivo.obtenerCantidadDeProductosEnCarrito())
        {
            cout << "Error, ingrese un valor entre 1 y " << PedidoArchivo.obtenerCantidadDeProductosEnCarrito() << endl;
        }
        else
        {
            int opcionParaModificarProducto = 0;
            do
            {
                cout << "¨Desea eliminarlo o cambiar la cantidad de productos?" << endl;
                cout << "1 - Para cambiar la cantidad items a llevar en el pedido" << endl;
                cout << "2 - Para eliminarlo del carrito" << endl;
                cout << "0 - Para salir" << endl;
                cin >> opcionParaModificarProducto;
                switch (opcionParaModificarProducto)
                {
                case 1:
                {
                    int nuevaCantidadDeArticulos;
                    int stockMaximoDelArticulo = stoi(listaProductos[opcionProducto - 1].getStockDelProducto().c_str());
                    cout << "Ingrese la nueva cantidad art¡culos que desea llevar" << endl;
                    cin >> nuevaCantidadDeArticulos;

                    if (nuevaCantidadDeArticulos == 0)
                    {
                        ///Si el cliente pone 0 art¡culos lo elimina de la lista
                        PedidoArchivo.modificarCantidadDeArticulosCarrito(opcionProducto, 0, true);
                    }
                    else if (stockMaximoDelArticulo < nuevaCantidadDeArticulos)
                    {
                        cout << "Lo sentimos, s¢lo se encuentran disponibles " << stockMaximoDelArticulo << " de articulos" << endl;
                    }
                    else
                    {
                        PedidoArchivo.modificarCantidadDeArticulosCarrito(opcionProducto, nuevaCantidadDeArticulos, false);
                    }
                    ///Con esto salimos del do/while porque ya se termin¢ la operaci¢n
                    opcionParaModificarProducto = 0;
                    break;
                }
                case 2:
                    PedidoArchivo.modificarCantidadDeArticulosCarrito(opcionProducto, 0, true);
                    opcionParaModificarProducto = 0;
                    break;
                case 0:
                    cout << "Entendido, saliendo" << endl;
                    break;
                default:
                    cout << "Error, ingrese un valor correcto" << endl;
                    break;
                }
            }
            while (opcionParaModificarProducto != 0);
        }
    }
}
int Pedidos::realizarPago()
{
    ///Declaraci¢n de variables u objetos
    EmpleadosArchivos EmArchivo;
    PedidosArchivo PArchivo;
    ClientesArchivo ClArchivo;
    Pedidos pedido;
    Clientes *listaClientes;
    listaClientes = new Clientes[ClArchivo.obtenerCantidadDeClientes()];
    ClArchivo.leerCliente(listaClientes);
    ///Este bool es para ver si encontr¢ el mail del cliente o no
    bool encontrado = false;
    ///Entero para buscar despu‚s en el array de clientes
    int clienteEncontrado = 0;
    ///Esta variable se usa para devolver el resultado de si pudo o no realizar el pedido
    int resultadoADevolver = 0;

    ///Ingresamos el mail con el que vamos a realizar la compra
    string mailCliente;
    cout << "Ingrese su mail para poder realizar el pedido" << endl;
    cin >> mailCliente;

    for (int i = 0; i < ClArchivo.obtenerCantidadDeClientes(); i++)
    {
        if (mailCliente == listaClientes[i].getMail())
        {
            pedido.setNumCliente(to_string(listaClientes[i].getNumCliente()));
            encontrado = true;
            clienteEncontrado = i;
            break;
        }
    }
    if (!encontrado)
    {
        resultadoADevolver = -1;
    }
    else if (listaClientes[clienteEncontrado].getEliminado())
    {
        resultadoADevolver = 2;
    }
    else
    {
        ///Con esto asignamos al empleado que armara el pedido
        int cantidadDeEmpleados = EmArchivo.seleccionarEmpleadoParaArmarPedido();

        pedido.setNumPedido(to_string(PArchivo.obtenerCantidadDePedidosRealizados()+ 1));
        pedido.setNumLegajoEmpleado(to_string(cantidadDeEmpleados));
        int opcion;
        cout << "La direcci¢n de entre est  configurada para: " << listaClientes[clienteEncontrado].getDireccionDelCliente() << endl;
        cout << "Si desea cambiar la direcci¢n de entrega ingrese 1, caso contrario 0" << endl;
        cin >> opcion;

        if (opcion == 0)
        {
            pedido.setDireccionDeEntrega(listaClientes[clienteEncontrado].getDireccionDelCliente());
        }
        else
        {
            string direccion;
            cout << "Ingrese la nueva direcci¢n de entrega" << endl;
            cin.ignore();
            getline(cin, direccion);
            pedido.setDireccionDeEntrega(direccion);
        }

        ///Funciones para manejar la fecha, esta se guarda seg£n la fecha de la computadora
        time_t diaActual = time(0);
        tm *ltm = localtime(&diaActual);
        pedido.setDia(to_string(ltm->tm_mday));
        int fecha =  1 + ltm->tm_mon;
        pedido.setMes(to_string(fecha));
        fecha = 1900 + ltm->tm_year;
        pedido.setAnio(to_string(fecha));
        PArchivo.generarFactura(pedido);
        resultadoADevolver = PArchivo.registrarCompra(pedido);
    }

    delete[] listaClientes;
    return resultadoADevolver;
}


