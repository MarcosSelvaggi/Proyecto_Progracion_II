#pragma once
#include "Productos.h"
#include <string>

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
        void obtenerCategoriaProducto(std::string &categoriaBuscada);

        //¨Funci¢n deprecada?
        int stockPorCategoria(std::string categoriaBuscada);


};

