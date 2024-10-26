#include "ProductosArchivo.h"
#include "Productos.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ProductosArchivo::ProductosArchivo()
{
}

int ProductosArchivo::obtenerCantidadDeProductos()
{
    int total = 0;

    ifstream ArchivoCSV("ListaProductos.csv");

    if (!ArchivoCSV.is_open())
    {
        return -1;
    }
    string linea;

    ///Este getline se encarga de liberar la primera l¡nea que tiene los datos
    getline(ArchivoCSV, linea);

    while(getline(ArchivoCSV, linea))
    {
        total++;
    }

    ArchivoCSV.close();

    return total;
}

bool ProductosArchivo::agregarProductoAlArchivo(Productos &producto)
{

    ofstream ArchivoCSV("ListaProductos.csv", ios::app);

    if (!ArchivoCSV.is_open())
    {
        return false;
    }

    ArchivoCSV << producto.getSku() << ","
               << producto.getCodigoDeBarras() << ","
               << producto.getNombreProducto() << ","
               << producto.getStockMinimo() << ","
               << producto.getStockActual() << ","
               << producto.getPrecioProducto() << ","
               << producto.getCategoria() << ","
               << "false" << "\n";
    ArchivoCSV.close();
    return true;
}
///VER SI PUEDO USARLO O NO, EN CASO CONTRARIO, DESCARTAR
/*
void ProductosArchivo::leerUnProducto(Productos &producto, int productoABuscar)
{
    ifstream ArchivoCSV("ListaProductos.csv");

    if (!ArchivoCSV.is_open())
    {
        return;
    }
    ProductosArchivo ProArchivo;
    string linea;
    getline(ArchivoCSV, linea);

    int totalProductos = ProArchivo.obtenerCantidadDeProductos();

    for(int i = 0; i < totalProductos; i++)
    {
        getline(ArchivoCSV, linea);
        stringstream informacionProducto(linea);
        string producto;



}
*/

///Esta funci¢n recibe un array din mico de productos y la cantidad de productos para leerlos
void ProductosArchivo::leerProductos(Productos *listaDeProductos, int totalProductos)
{
    ifstream ArchivoCSV("ListaProductos.csv");

    if (!ArchivoCSV.is_open())
    {
        return;
    }

    string linea;
    getline(ArchivoCSV, linea);

    for(int i = 0; i < totalProductos; i++)
    {
        getline(ArchivoCSV, linea);
        stringstream informacionProducto(linea);
        string producto;


        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setSku(producto);

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setCodigoDeBarras(producto);

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setNombreProducto(producto);

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setStockMinimo(producto);

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setStockActual(producto);

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setPrecio(stof(producto.c_str()));

        getline(informacionProducto, producto, ',');
        listaDeProductos[i].setCategoria(producto);

        getline(informacionProducto, producto, ',');
        (producto == "true" ? listaDeProductos[i].setProductoEliminado(true) : listaDeProductos[i].setProductoEliminado(false));

    }

    ArchivoCSV.close();
}
///Va a modificar el producto que le pasemos, hay que pasar la cantidad de productos y el ID del producto
bool ProductosArchivo::modificarProducto(Productos *listaDeProductos, int totalProductos, int idProducto)
{
    ofstream ArchivoCSV("ListaProductos.csv");

    if (!ArchivoCSV.is_open())
    {
        return false;
    }

    ProductosArchivo ProArchivo;

    string idDelProducto = to_string(idProducto);

    ArchivoCSV << "sku,codigoDeBarras,nombreProducto,stockMinimo,StockActual,precioProducto,categoriaProducto,productoEliminado\n";
    ArchivoCSV.close();

    for (int i = 0; i < totalProductos ; i++)
    {
        ProArchivo.agregarProductoAlArchivo(listaDeProductos[i]);
    }

    return true;
}
