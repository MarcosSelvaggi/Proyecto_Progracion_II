#include "InformesYGestion.h"
#include <iostream>
#include "Pedidos.h"
#include "PedidosArchivo.h"
#include "Empleados.h"
#include "EmpleadosArchivos.h"
#include "Clientes.h"
#include "ClientesArchivo.h"
#include "Productos.h"
#include "ProductosArchivo.h"
#include <time.h>
#include <iomanip> ///Para el setprecision
#include <unordered_map>
/*
Para ver m s acerca de los mapas
https://www.youtube.com/watch?v=r01r8mEs9I4
*/

using namespace std;

InformesYGestion::InformesYGestion()
{
}

void InformesYGestion::menuInformes()
{
    int opcion = 0;
    cout << "¨Qu‚ desea realizar?" << endl;
    cout << "1 - Ver la recaudacion mensual de un a¤o en especifico " << endl;
    cout << "2 - Ver la recaudaci¢n por a¤o" << endl;
    cout << "3 - Ver el producto m s vendido" << endl;
    cout << "4 - Ver el producto menos vendido" << endl;
    cout << "5 - Ver la informaci¢n del cliente que m s compro" << endl;
    cout << "0 - Salir" << endl;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
        string anio;
        cout << "Ingrese el a¤o a buscar"<< endl;
        cin >> anio;
        recaudacionesMensuales(anio);
        break;
    }
    case 2:
        recaudacionAnual();
        break;
    case 3:
        productoMasVendido();
        break;
    case 4:
        productoMenosVendido();
        break;
    case 5:
        clienteConMasCompras();
        system("Pause");
        break;
    default:
        cout << "Error, opci¢n incorrecta" << endl;
        break;
    }
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

    ///Variable auxiliar para manejar como se muestran los pedidos
    string pedidoAnterior = "0";

    switch (opcion)
    {
    case 1:
        pedidoAnterior = "0";
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
        pedidoAnterior = "0";
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
            cout << "Total \t \t \t \t \t \t \t \t \t $" << total << endl;
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
        cout << "Producto \t \t \t \t \t    | Unidades \t| Precio unitario " << endl;
    }

    string nombreProducto = pedido.getNombreDelProducto();
    for (int f = nombreProducto.length(); f < 50 ; f++ )
    {
        nombreProducto = nombreProducto + " ";
    }
    cout << nombreProducto <<"\t" << pedido.getCantidadSolicitada() <<"\t|\t $" <<  pedido.getPrecioUnitario() << endl;
}

void InformesYGestion::recaudacionesMensuales(string anio)
{
    PedidosArchivo PArchivos;
    Pedidos *listaPedidos;
    listaPedidos = new Pedidos[PArchivos.cantidadDeVentasGuardadas()];

    PArchivos.cargarDatosDeVentas(listaPedidos);
    float meses[12] {};
    int mes = 0;

    for (int i = 0; i < PArchivos.cantidadDeVentasGuardadas(); i++)
    {
        if (listaPedidos[i].getAnio() == anio){
            mes = stoi(listaPedidos[i].getMes().c_str());
            meses[mes - 1] += listaPedidos[i].getPrecioUnitario() * (stof(listaPedidos[i].getCantidadSolicitada().c_str()));
        }
    }

    for (int i = 0; i < 12; i++)
    {
        cout << "Mes " << i+1 << ", $"<< fixed << setprecision(2) << meses[i] << endl;
    }
    delete[] listaPedidos;
    system("pause");
}

void InformesYGestion::recaudacionAnual()
{
    ///Con esto manejamos el d¡a, lo vamos a usar para mostrar toda la informaci¢n hasta el anio actual
    time_t diaActual = time(0);
    tm *ltm = localtime(&diaActual);
    int fecha =  1 + ltm->tm_mon;
    fecha = 1900 + ltm->tm_year;

    PedidosArchivo PArchivos;
    Pedidos *listaPedidos;
    listaPedidos = new Pedidos[PArchivos.cantidadDeVentasGuardadas()];

    PArchivos.cargarDatosDeVentas(listaPedidos);

    float *anios = new float[fecha];

    for (int i = 0; i < PArchivos.cantidadDeVentasGuardadas(); i++)
    {
        anios[stoi(listaPedidos[i].getAnio().c_str())] += listaPedidos[i].getPrecioUnitario() * stof(listaPedidos[i].getCantidadSolicitada().c_str());
    }
    cout << "A¤o: " << " Total recaudado" << endl;

    ///Al cambiar el valor de i podemos elegir desde que a¤o arrancar a ver los datos
    for (int i = 2018; i <= fecha ; i++)
    {
        cout << i << "\t $" << fixed << setprecision(2) << anios[i] << endl;
    }
    delete[] listaPedidos;
    system("pause");
}

void InformesYGestion::productoMasVendido()
{
    ProductosArchivo ProductoArchivo;
    PedidosArchivo PArchivos;
    //Declaraci¢n de la lista de pedidos
    Pedidos *listaPedidos = new Pedidos[PArchivos.cantidadDeVentasGuardadas()];
    PArchivos.cargarDatosDeVentas(listaPedidos);
    //Declaraci¢n de la lista de productos
    Productos *listaProducto = new Productos[ProductoArchivo.obtenerCantidadDeProductos()];
    ProductoArchivo.leerProductos(listaProducto, ProductoArchivo.obtenerCantidadDeProductos());

    unordered_map<string, int> mapaSKU;
    ///Cargamos el mapa con los SKU's de los productos
    for (int j = 0; j < ProductoArchivo.obtenerCantidadDeProductos(); j++)
    {
        mapaSKU[listaProducto[j].getSku()] = j;
        //En el mapa, cada SKU tiene su propio valor de j hasta la cantidad de productos, esto hace que a la hora de buscar, devuelva el
        //valor que se le asigno anteriormente, esto permite que el SKU 82943 en el array sea 1 o 20, o lo que fuera para buscarlo mejor
    }

    int *productosVendidos = new int[ProductoArchivo.obtenerCantidadDeProductos()]{};

    // Contar productos vendidos
    for (int i = 0; i < ProductoArchivo.obtenerCantidadDeProductos(); i++)
    {
        ///Busca en el mapa el SKU del producto
        int busqueda = mapaSKU[listaPedidos[i].getIdDelProducto()];
        productosVendidos[busqueda] += stoi(listaPedidos[i].getCantidadSolicitada());
    }

    /*Forma obsoleta de recorrer la lista de pedidos, no usar
    for (int i = 0; i < PArchivos.cantidadDeVentasGuardadas();i++)
    {
        for (int j = 0; j < ProductoArchivo.obtenerCantidadDeProductos();j++)
        {
            if (listaPedidos[i].getIdDelProducto() == listaProducto[j].getSku())
            {
                productosVendidos[j] += stoi(listaPedidos[i].getCantidadSolicitada().c_str());
                break;
            }
        }
    }*/

    int cantidadMasVendida = 0;
    string nombreProductoConMasVentas = "";

    for (int i = 0; i < ProductoArchivo.obtenerCantidadDeProductos(); i++)
    {
        if (productosVendidos[i] > cantidadMasVendida)
        {
            cantidadMasVendida = productosVendidos[i];
            nombreProductoConMasVentas = listaProducto[i].getNombreProducto();

        }
    }

    cout << "El producto m s vendido es el " << nombreProductoConMasVentas << " con " << cantidadMasVendida << " de unidades vendidas" << endl;

    delete[] listaProducto;
    delete[] listaPedidos;
    system("pause");
}

void InformesYGestion::productoMenosVendido()
{
    ProductosArchivo ProductoArchivo;
    PedidosArchivo PArchivos;
    Pedidos *listaPedidos;
    listaPedidos = new Pedidos[PArchivos.cantidadDeVentasGuardadas()];
    PArchivos.cargarDatosDeVentas(listaPedidos);
    Productos *listaProducto = new Productos[ProductoArchivo.obtenerCantidadDeProductos()];
    ProductoArchivo.leerProductos(listaProducto, ProductoArchivo.obtenerCantidadDeProductos());

    ///Se crea un array de productos con la cantidad de productos que hay
    int *productosVendidos = new int[ProductoArchivo.obtenerCantidadDeProductos()]{};

    unordered_map<string, int> mapaSKU;
    ///Cargamos el mapa con los SKU's de los productos
    for (int j = 0; j < ProductoArchivo.obtenerCantidadDeProductos(); j++)
    {
        mapaSKU[listaProducto[j].getSku()] = j;
        //En el mapa, cada SKU tiene su propio valor de j hasta la cantidad de productos, esto hace que a la hora de buscar, devuelva el
        //valor que se le asigno anteriormente, esto permite que el SKU 82943 en el array sea 1 o 20, o lo que fuera para buscarlo mejor
    }

    // Contar productos vendidos
    for (int i = 0; i < ProductoArchivo.obtenerCantidadDeProductos(); i++)
    {
        ///Busca en el mapa el SKU del producto
        int busqueda = mapaSKU[listaPedidos[i].getIdDelProducto()];
        productosVendidos[busqueda] += stoi(listaPedidos[i].getCantidadSolicitada());
    }
    /*Funci¢n obsoleta
    ///Este for recorre todos los pedidos y suma al array de enteros la cantidad de productos que hay
    for (int i = 0; i < PArchivos.cantidadDeVentasGuardadas();i++)
    {
        for (int j = 0; j < ProductoArchivo.obtenerCantidadDeProductos();j++)
        {
            if (listaPedidos[i].getIdDelProducto() == listaProducto[j].getSku())
            {
                productosVendidos[j] += stoi(listaPedidos[i].getCantidadSolicitada().c_str());
            }
        }
    }*/

    int cantidadMenosVendida = 0;
    bool primeraComparacion = true;
    string nombreProductoConMenosVentas = "";

    ///Recorre el array de productos vendidos y compara la cantidad, despu‚s pone el nombre en el string de producto con menos venta
    ///Para hacer eso busca el nombre del producto en el array de lista de productos con el mismo indice
    for (int i = 0; i < ProductoArchivo.obtenerCantidadDeProductos(); i++)
    {

        if ((productosVendidos[i] < cantidadMenosVendida || primeraComparacion) && productosVendidos[i] != 0)
        {
            primeraComparacion = false;
            cantidadMenosVendida = productosVendidos[i];
            nombreProductoConMenosVentas = listaProducto[i].getNombreProducto();

        }
    }

    cout << "El producto menos vendido es el " << nombreProductoConMenosVentas << " con " << cantidadMenosVendida << " de unidades vendidas" << endl;

    delete[] listaProducto;
    delete[] listaPedidos;
    delete[] productosVendidos;
    system("pause");
}

void InformesYGestion::clienteConMasCompras()
{
    ClientesArchivo ClArchivo;
    Clientes *listaClientes = new Clientes[ClArchivo.obtenerCantidadDeClientes()];
    ClArchivo.leerCliente(listaClientes);

    PedidosArchivo PedidoArchivo;
    Pedidos *listaPedidos = new Pedidos[PedidoArchivo.cantidadDeVentasGuardadas()];
    PedidoArchivo.cargarDatosDeVentas(listaPedidos);

    float *listaCompras = new float[ClArchivo.obtenerCantidadDeClientes()];

    for(int i = 0; i < PedidoArchivo.cantidadDeVentasGuardadas();i++)
    {
        listaCompras[stoi(listaPedidos[i].getNumPedido().c_str())] += listaPedidos[i].getPrecioUnitario() * stof(listaPedidos[i].getCantidadSolicitada());
    }

    float cantidadMaxima = 0;
    int clienteCompraMaxima = 0;

    for(int i = 0; i < ClArchivo.obtenerCantidadDeClientes(); i++)
    {
        if (listaCompras[i] > cantidadMaxima)
        {
            cantidadMaxima = listaCompras[i];
            clienteCompraMaxima = i;
        }
    }

    cout << "El cliente que m s compro es " << listaClientes[clienteCompraMaxima].getNombre() << " " << listaClientes[clienteCompraMaxima].getApellido() << " con un total de $" << cantidadMaxima << endl;

    delete[] listaClientes;
    delete[] listaPedidos;
    delete[] listaCompras;
}
