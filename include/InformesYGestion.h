#pragma once
#include "Pedidos.h"
#include <string>

class InformesYGestion
{
    public:
        InformesYGestion();
        void visualizarVentas();
        void mostrarPedidoPorPantalla(Pedidos &pedido, bool primeraVuelta);

};
