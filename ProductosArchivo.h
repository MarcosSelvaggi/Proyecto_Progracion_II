#pragma once
#include "Productos.h"

class ProductosArchivo
{
    public:
        ProductosArchivo();
        int obtenerCantidadDeProductos();
        bool agregarProductoAlArchivo(Productos &producto);
        ///Por el momento est  descartada la siguiente funci¢n
        //void leerUnProducto(Productos producto, int productoABuscar);
        void leerProductos(Productos *listaDeProductos, int totalProductos);
        bool modificarProducto(Productos *listaDeProductos, int totalProductos, int idProducto);

};

