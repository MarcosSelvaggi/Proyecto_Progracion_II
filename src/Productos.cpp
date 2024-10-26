#include "Productos.h"
#include "ProductosArchivo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Productos::Productos()
{
}

Productos::Productos(string sku, string codigoDeBarras, string nombreProducto, string stockMinimo, string stockActual, float precioProducto, string categoria)
{
    _SKU = sku;
    _codigoDeBarras = codigoDeBarras;
    _nombreProducto = nombreProducto;
    _stockMinimo = stockMinimo;
    _stockActual = stockActual;
    _precioProducto = precioProducto;
    _categoriaProducto = categoria;
    _productoEliminado = false;
}

///Setters
void Productos::setSku(string sku)
{
    _SKU = sku;
}
void Productos::setCodigoDeBarras(string codigoDeBarras)
{
    _codigoDeBarras = codigoDeBarras;
}
void Productos::setNombreProducto(string nombre)
{
    _nombreProducto = nombre;
}
void Productos::setStockMinimo(string stockMinimo)
{
    _stockMinimo = stockMinimo;
}
void Productos::setStockActual(string stockActual)
{
    _stockActual = stockActual;
}
void Productos::setPrecio(float precio)
{
    _precioProducto = precio;
}
void Productos::setCategoria(string categoria)
{
    _categoriaProducto = categoria;
}
void Productos::setProductoEliminado(bool eliminado)
{
    _productoEliminado = eliminado;
}

///Getters
string Productos::getSku()
{
    return _SKU;
}
string Productos::getCodigoDeBarras()
{
    return _codigoDeBarras;
}
string Productos::getNombreProducto()
{
    return _nombreProducto;
}
string Productos::getStockMinimo()
{
    return _stockMinimo;
}
string Productos::getStockActual()
{
    return _stockActual;
}
float Productos::getPrecioProducto()
{
    return _precioProducto;
}
string Productos::getCategoria()
{
    return _categoriaProducto;
}
bool Productos::getProductoEliminado()
{
    return _productoEliminado;
}


///FUNCIONES

void Productos::menuProductos()
{
    system("cls");
    int opcion;
    Productos producto;
    ProductosArchivo ProArchivo;
    do
    {
        cout << "--------------------------"<< endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Agregar un producto" << endl;
        cout << "2 - Buscar un producto" << endl;
        cout << "3 - Modificar un producto" << endl;
        cout << "4 - Listar producto activos" << endl;
        cout << "5 - Listar producto inactivos" << endl;
        cout << "0 - Salir" << endl;
        cin >> opcion;


        switch (opcion)
        {
        case 1:
            if (agregarProducto())
            {
                cout << "Se ha agregado el producto de forma correcta" << endl;
            }
            else
            {
                cout << "No se ha podido agregar el producto" << endl;
            }
            break;
        case 2:
        {
            int visualizarInfo;
            string busqueda;
            cout << "¨Desea ver la informaci¢n resumida o completa?" << endl;
            cout << "1- Para ver la informaci¢n resumida, 0 para completa" << endl;
            cin >> visualizarInfo;
            cout << "---------------------------" << endl;
            cout << "   Busqueda del producto   " << endl;
            cin >> busqueda;
            buscarUnProducto(busqueda, visualizarInfo);
            break;
        }
        case 3:
            modificarProducto();
            break;
        case 4:
        {
            int cantidad = 0;
            mostrarProductos(false, cantidad);
            cout << "Cantidad de activos: " << cantidad << endl;
            break;
        }
        case 5:
        {
            int cantidad = 0;
            mostrarProductos(true, cantidad);
            cout << "Cantidad de inactivos: " << cantidad << endl;
            break;
        }

        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Error, eliga una opci¢n valida" << endl;
            break;
        }
    }
    while (opcion != 0);
}

bool Productos::agregarProducto()
{
    ProductosArchivo PtoArchivo;

    string SKU,codigoDeBarras, nombreProducto,stockMinimo,stockActual, categoriaProducto;
    float precioProducto;

    srand(time(NULL));
    int numeroParaSKU = rand() % 10000000;

    SKU = to_string(numeroParaSKU);

    cout << "Ingrese el c¢digo de barras: ";
    cin >> codigoDeBarras;

    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nombreProducto);

    cout << "Ingrese el stock minimo: ";
    cin >> stockMinimo;

    cout << "Ingrese el stock actual: ";
    cin >> stockActual;

    cout << "Ingrese el precio del producto: ";
    cin >> precioProducto;

    cout << "Ingrese la categoria a la que pertenece el producto: ";
    cin >> categoriaProducto;

    Productos producto(SKU, codigoDeBarras, nombreProducto, stockMinimo, stockActual, precioProducto, categoriaProducto);

    return PtoArchivo.agregarProductoAlArchivo(producto);
}

void Productos::buscarUnProducto(string busqueda, int visualizarInfo)
{
    ProductosArchivo ProArchivo;
    Productos *listaProductos;
    int  totalProductos = ProArchivo.obtenerCantidadDeProductos();
    listaProductos = new Productos[totalProductos];

    ProArchivo.leerProductos(listaProductos, totalProductos);

    ///Forma legible que pone todas las letras en minusculas para que no sea case sensitive la busqueda
    for (auto& x : busqueda)
    {
        x = tolower(x);
    }

    for (int i = 0; i < totalProductos; i++)
    {
        string nombreProducto = listaProductos[i].getNombreProducto();
        ///Igual que antes, esto pone el nombre del producto en minusculas para que la busqueda sea case sensitive
        for (auto& x : nombreProducto)
        {
            x = tolower(x);
        }
        ///Comprueba si la busqueda est  dentro del SKU, en caso de que escribamos n£meros
        if(listaProductos[i].getSku().find(busqueda) != string::npos)
        {
            cout << "---------------------------" << endl;
            imprimirElProducto(listaProductos[i], visualizarInfo);
        }
        ///En caso de que no encuentre el SKU nos va a buscar en el nombre del producto
        else if (nombreProducto.find(busqueda) != string::npos)
        {
            cout << "---------------------------" << endl;
            imprimirElProducto(listaProductos[i], visualizarInfo);
        }
    }

    delete[] listaProductos;
}

void Productos::imprimirElProducto(Productos producto, bool infoResumida)
{
    cout << "SKU: " << producto.getSku() << endl;
    cout << "Producto: " << producto.getNombreProducto() << endl;
    cout << "Precio: $" << producto.getPrecioProducto() << endl;
    cout << "Categoria: " << producto.getCategoria() << endl;

    if (!infoResumida)
    {
        cout << "Codigo de barras: " << producto.getCodigoDeBarras() << endl;
        cout << "Stock actual: " << producto.getStockActual() << endl;
        cout << "Stock minimo: " << producto.getStockMinimo() << endl;
        cout << "Estado: " << (producto.getProductoEliminado() ? "Inactivo" : "Activo") << endl;
    }

}

void Productos::modificarProducto()
{
    string busqueda, numBusqueda;
    int numOpcion;
    cout << "Si conoce el SKU del producto, digite 0, caso contrario 1" << endl;
    cin >> numOpcion;

    ///Con 0 buscamos la informaci¢n del producto para que podamos modificarlo
    if (numOpcion == 1)
    {
        cout << "---------------------------" << endl;
        cout << "   Busqueda del producto   " << endl;
        cin >> busqueda;
        buscarUnProducto(busqueda, 1);
    }
    ///Una vez tenemos la informaci¢n del producto, podemos escribir el SKU a buscar
    cout << endl << "Introduzca el SKU" << endl;
    cin >> numBusqueda;

    bool noEncontrado = true; /// Este bool es para revisar si encontr¢ o no al producto

    ProductosArchivo ProArchivo;
    Productos productoNuevo;
    Productos *listaProductos;
    int  totalProductos = ProArchivo.obtenerCantidadDeProductos();
    listaProductos = new Productos[totalProductos];
    ProArchivo.leerProductos(listaProductos, totalProductos);

    for (int i = 0; i < totalProductos; i++)
    {
        if (listaProductos[i].getSku() == numBusqueda)
        {
            buscarUnProducto(numBusqueda, 0);
            int opcion;
            do
            {
                cout << "¨Qu‚ desea modificar?" << endl;
                cout << "1 - Codigo de barras" << endl;
                cout << "2 - Nombre del producto" << endl;
                cout << "3 - Stock m¡nimo" << endl;
                cout << "4 - Stock actual" << endl;
                cout << "5 - Precio del producto" << endl;
                cout << "6 - La categoria" << endl;
                cout << "7 - Activar producto" << endl;
                cout << "8 - Desactivar producto" << endl;
                cout << "0 - Salir" << endl;
                cin >> opcion;

                string valoresACambiar;
                float precioACambiar;
                switch (opcion)
                {
                case 1:
                    cout << "Ingrese el nuevo c¢digo de barras: ";
                    cin >> valoresACambiar;
                    listaProductos[i].setCodigoDeBarras(valoresACambiar);
                    break;
                case 2:
                    cout << "Ingrese el nuevo nombre del producto: ";
                    cin.ignore();
                    getline(cin, valoresACambiar);
                    listaProductos[i].setNombreProducto(valoresACambiar);
                    break;
                case 3:
                    cout << "Ingrese el stock m¡nimo: ";
                    cin >> valoresACambiar;
                    listaProductos[i].setStockMinimo(valoresACambiar);
                    break;
                case 4:
                    cout << "Ingrese el stock actual: ";
                    cin >> valoresACambiar;
                    listaProductos[i].setStockActual(valoresACambiar);
                    break;
                case 5:
                    cout << "Ingrese el nuevo precio del producto: ";
                    cin >> precioACambiar;
                    listaProductos[i].setPrecio(precioACambiar);
                    break;
                case 6:
                    cout << "Ingrese la nueva categoria del producto: ";
                    cin >> valoresACambiar;
                    listaProductos[i].setCategoria(valoresACambiar);
                    break;
                case 7:
                    listaProductos[i].setProductoEliminado(false);
                    break;
                case 8 :
                    listaProductos[i].setProductoEliminado(true);
                    break;
                case 0:
                    break;
                default:
                    cout << "Error, ingrese un valor correcto" << endl;
                    break;
                }
            }
            while (opcion != 0);
            noEncontrado = false;
            break;
        }
    }
    if (noEncontrado)
    {
        cout << "No se encontr¢ ning£n producto con ese SKU" << endl;
    }
    else
    {
        if (ProArchivo.modificarProducto(listaProductos, totalProductos, atoi(numBusqueda.c_str())))
        {
            cout << "Se pudo moficiar el producto" << endl;
        }
        else
        {
            cout << "No se pudo modificar el producto" << endl;
        }
    }

    delete[] listaProductos;
}

void Productos::mostrarProductos(bool estaActivo, int &cantidad)
{
    ProductosArchivo ProArchivo;
    Productos productoNuevo;
    Productos *listaProductos;
    int  totalProductos = ProArchivo.obtenerCantidadDeProductos();
    listaProductos = new Productos[totalProductos];
    ProArchivo.leerProductos(listaProductos, totalProductos);

    for (int i = 0; i < totalProductos; i++)
    {
        if (listaProductos[i].getProductoEliminado() == estaActivo)
        {
            cout << "-----------------------" << endl;
            imprimirElProducto(listaProductos[i], 0);
            cantidad++;
        }
    }
}
///Funci¢n por ahora de adorno, va a ser usada cuando se realice el pedido
void Productos::modificarStockActual(Productos &producto, int cantidadDeProductos)
{
    int stockStringAInt = atoi(producto.getStockActual().c_str());
    cantidadDeProductos = stockStringAInt  - cantidadDeProductos;
    producto.setStockActual(to_string(cantidadDeProductos));
}
