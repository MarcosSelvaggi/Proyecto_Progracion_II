#pragma once
#include "Clientes.h"

class ClientesArchivo
{
    public:
        ClientesArchivo();
        int obtenerCantidadDeClientes();
        bool guardarCliente(Clientes &cliente);
        Clientes buscarCliente(Clientes &cliente,int posicion);
        void leerCliente(Clientes *listaCliente);
        bool modificarClienteArchivo(Clientes &cliente, int posicion);

    private:
};
