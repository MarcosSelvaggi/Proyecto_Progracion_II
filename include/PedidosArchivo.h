#pragma once
#include "Pedidos.h"

class PedidosArchivo
{
    public:
        PedidosArchivo();

        ///Revisar si es mejor pasar un pedido con toda la informaci¢n o todo suelto
        /*
        string numPedido, string numCliente, string legajoEmpleado,
        string idProducto, string cantidadAdquirida,
        float precioUnitario, string dia, string mes, string anio
        */

        void limpiarArchivoTemporal();
        int obtenerCantidadDeProductosEnCarrito();
        bool guardarPedidoEnArchivoTemporal(Pedidos &pedido);
        void leerPedidoEnArchivoTemporal(Pedidos *pedido);
        void modificarCantidadDeArticulosCarrito(int numProducto, int cantidadDeArticulos, bool eliminado);
        bool registrarCompra(Pedidos &pedido);
        int obtenerCantidadDePedidosRealizados();

        void generarFactura(Pedidos &pedido);

    protected:
};
