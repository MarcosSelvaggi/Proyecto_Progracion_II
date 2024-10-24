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
    ///Este getline se encarga de liberar la primera l¡nea que tiene los datos

    string linea;

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


void ProductosArchivo::cargarProductos(Productos *listaDeProductos, int totalProductos)
{
    ifstream ArchivoCSV("ListaProductos.csv");

    if (!ArchivoCSV.is_open())
    {
        return;
    }

    string linea;
    getline(ArchivoCSV, linea);

    for(int i = 0; i < totalProductos ; i++)
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
        if (producto == "true")
        {
            listaDeProductos[i].setProductoEliminado(true);
        }
        else
        {
            listaDeProductos[i].setProductoEliminado(false);
        }
    }

    ArchivoCSV.close();
}
