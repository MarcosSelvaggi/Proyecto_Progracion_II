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
        bool guardarPedidoEnArchivoTemporal(Pedidos &pedido);

        void generarFactura(Pedidos &pedido);

    protected:
};
