#pragma once
#include "Pedidos.h"
#include <string>

class InformesYGestion
{
    public:
        InformesYGestion();
        void menuInformes();
        void visualizarVentas();
        void mostrarPedidoPorPantalla(Pedidos &pedido, bool primeraVuelta);
        void recaudacionesMensuales(std::string anio);
        void recaudacionAnual();
        void productoMasVendido();
        void productoMenosVendido();
        void clienteConMasCompras();

};
