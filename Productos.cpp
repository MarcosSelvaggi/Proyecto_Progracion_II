#include "Productos.h"
#include "ProductosArchivo.h"
#include <iostream>


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
    int opcion, posicion;
    Productos producto;
    ProductosArchivo ProArchivo;
    do
    {
        cout << "--------------------------"<< endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Agregar un producto" << endl;
        cout << "2 - Buscar un producto" << endl;
        cout << "3 - Modificar un producto" << endl;
        cout << "4 - Eliminar un producto" << endl;
        cout << "5 - Recuperar un producto" << endl;
        cout << "6 - Listar producto activos" << endl;
        cout << "7 - Listar producto inactivos" << endl;
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


            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            break;
            break;
        case 6:

            break;
        case 7:

            break;
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

    SKU = to_string(PtoArchivo.obtenerCantidadDeProductos() + 1);

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
