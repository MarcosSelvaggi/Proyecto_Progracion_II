#pragma once
#include "Persona.h"

class Clientes: public Persona
{
    ///Constructores
    public:
        Clientes();
        Clientes(char* nombre, char* apellido, char* numTelefono, char* direccionDelCliente, int numCliente, char* direccionDeMail);
    ///Setters
        void setNumCliente(int numCliente);
        void setDireccionDelCliente(char* direccion);

    ///Getters
        int getNumCliente();
        char* getDireccionDelCliente();

    ///Funciones
        void menuClientes();
        bool agregarCliente();
        bool modificarCliente(Clientes cliente, int posicion);
        void mostrarCliente(Clientes cliente);
        void cambiarEstadoEliminado(Clientes &cliente, bool estado);
        void listarClientes(bool eliminado);


    protected:
        int _numCliente;
        char _direccionDelCliente[100];


};
