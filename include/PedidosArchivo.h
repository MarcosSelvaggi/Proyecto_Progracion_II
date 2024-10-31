#pragma once
#include "Pedidos.h"
#include <string>

class PedidosArchivo
{
    public:
        PedidosArchivo();
        ///Metodos para el carrito
        void limpiarArchivoTemporal();
        int obtenerCantidadDeProductosEnCarrito();
        bool guardarPedidoEnArchivoTemporal(Pedidos &pedido);
        void leerPedidoEnArchivoTemporal(Pedidos *pedido);
        void modificarCantidadDeArticulosCarrito(int numProducto, int cantidadDeArticulos, bool eliminado);
        bool productoEnElCarrito(std::string numProducto);

        ///Metodos para la compra
        bool registrarCompra(Pedidos &pedido);
        int obtenerCantidadDePedidosRealizados();
        int cantidadDeVentasGuardadas();
        void cargarDatosDeVentas(Pedidos *listaPedidos);
        void generarFactura(Pedidos &pedido);

    protected:
};
