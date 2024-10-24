#pragma once
#include "Productos.h"

class ProductosArchivo
{
    public:
        ProductosArchivo();
        int obtenerCantidadDeProductos();
        bool agregarProductoAlArchivo(Productos &producto);
        void cargarProductos(Productos *listaDeProductos, int totalProductos);

};

