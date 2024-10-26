#include "ClientesArchivo.h"
#include "Clientes.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

ClientesArchivo::ClientesArchivo()
{
}

int ClientesArchivo::obtenerCantidadDeClientes()
{
    int total = 0;
    ifstream ArchivoCSV("ClientesArchivo.csv");

    if (!ArchivoCSV.is_open())
    {
        return -1;
    }

    string linea;

    ///Este getline se encarga de liberar la primera l¡nea que tiene los datos
    getline(ArchivoCSV, linea);

    while(getline(ArchivoCSV, linea))
    {
        total++;
    }

    ArchivoCSV.close();

    return total;
}

bool ClientesArchivo::guardarCliente(Clientes &cliente)
{
    ofstream ArchivoCSV("ClientesArchivo.csv", fstream::app);

    if (!ArchivoCSV.is_open())
    {
        return false;
    }


    ArchivoCSV << cliente.getNumCliente() << ","
               << cliente.getNombre() << ","
               << cliente.getApellido() << ","
               << cliente.getMail() << ","
               << cliente.getNumTelefono() << ","
               << cliente.getDireccionDelCliente() << ","
               << "false" << "\n";


    ArchivoCSV.close();
    return true;
}

void ClientesArchivo::leerCliente(Clientes *listaCliente)
{
    ifstream ArchivoCSV("ClientesArchivo.csv");

    if (!ArchivoCSV.is_open())
    {
        return;
    }

    ClientesArchivo ClArchivo;
    string linea;
    char data25[25], data100[100];
    int idABuscar;

    getline(ArchivoCSV, linea);

    for (int i = 0; i < ClArchivo.obtenerCantidadDeClientes(); i++)
    {
        getline(ArchivoCSV, linea);

        ///
        stringstream informacionCliente(linea);
        string clienteString;

        ///Asigna el ID del cliente
        getline(informacionCliente, clienteString, ',');
        idABuscar = atoi(clienteString.c_str());
        listaCliente[i].setNumCliente(idABuscar);

        ///Asigna el nombre del cliente
        getline(informacionCliente, clienteString, ',');
        strcpy(data25,clienteString.c_str());
        listaCliente[i].setNombre(data25);

        ///Asigna el apellido del cliente
        getline(informacionCliente, clienteString, ',');
        strcpy(data25,clienteString.c_str());
        listaCliente[i].setApellido(data25);

        ///Asigna el mail del cliente
        getline(informacionCliente, clienteString, ',');
        strcpy(data100,clienteString.c_str());
        listaCliente[i].setMail(data100);

        ///Asigna el n£mero de telefono del cliente
        getline(informacionCliente, clienteString, ',');
        strcpy(data25,clienteString.c_str());
        listaCliente[i].setNumTelefono(data25);

        ///Asigna la direcci¢n del cliente
        getline(informacionCliente, clienteString, ',');
        strcpy(data100,clienteString.c_str());
        listaCliente[i].setDireccionDelCliente(data100);

        ///Asigna si est  o no eliminado el cliente
        getline(informacionCliente, clienteString, ',');
        clienteString == "true" ? listaCliente[i].setEliminado(true) : listaCliente[i].setEliminado(false);
    }
    ArchivoCSV.close();
}


Clientes ClientesArchivo::buscarCliente(Clientes &cliente,int posicion)
{
    int idABuscar;
    ifstream ArchivoCSV("ClientesArchivo.csv");

    if (!ArchivoCSV.is_open())
    {
        return cliente;
    }
    string linea;

    ///Este getline se encarga de liberar la primera l¡nea que tiene los datos
    getline(ArchivoCSV, linea);

    while(getline(ArchivoCSV, linea))
    {
        stringstream informacionCliente(linea);
        string clienteString;
        getline(informacionCliente, clienteString, ',');

        idABuscar = atoi(clienteString.c_str());
        if (idABuscar == posicion)
        {
            cliente.setNumCliente(posicion);
            char data25[25], data100[100];
            getline(informacionCliente, clienteString, ',');
            strcpy(data25,clienteString.c_str());
            cliente.setNombre(data25);

            getline(informacionCliente, clienteString, ',');
            strcpy(data25,clienteString.c_str());
            cliente.setApellido(data25);

            getline(informacionCliente, clienteString, ',');
            strcpy(data100,clienteString.c_str());
            cliente.setMail(data100);

            getline(informacionCliente, clienteString, ',');
            strcpy(data25,clienteString.c_str());
            cliente.setNumTelefono(data25);

            getline(informacionCliente, clienteString, ',');
            strcpy(data100,clienteString.c_str());
            cliente.setDireccionDelCliente(data100);

            getline(informacionCliente, clienteString, ',');
            clienteString == "true" ? cliente.setEliminado(true) : cliente.setEliminado(false);

            break;
        }
    }

    ArchivoCSV.close();

    return cliente;
}

bool ClientesArchivo::modificarClienteArchivo(Clientes &cliente, int posicion)
{
    ClientesArchivo ClArchivo;
    Clientes *listaClientes;

    listaClientes = new Clientes[ClArchivo.obtenerCantidadDeClientes()];

    ClArchivo.leerCliente(listaClientes);

    int cantidadDeClientes = ClArchivo.obtenerCantidadDeClientes();

    for (int i = 0; i < cantidadDeClientes; i++)
    {
        if(cliente.getNumCliente() == listaClientes[i].getNumCliente())
        {

            //id,nombre,apellido,email,numeroDeTelefono ,direccion,eliminado
            listaClientes[i].setNombre(cliente.getNombre());
            listaClientes[i].setApellido(cliente.getApellido());
            listaClientes[i].setMail(cliente.getMail());
            listaClientes[i].setNumTelefono(cliente.getNumTelefono());
            listaClientes[i].setDireccionDelCliente(cliente.getDireccionDelCliente());
            listaClientes[i].setEliminado(cliente.getEliminado());
            break;
        }
    }

    ofstream ArchivoCSV("ClientesArchivo.csv");

    if (!ArchivoCSV.is_open())
    {
        return false;
    }


    ArchivoCSV << "id,nombre,apellido,email,numeroDeTelefono,direccion,eliminado\n";
    for (int i = 0; i < cantidadDeClientes; i++)
    {
            ArchivoCSV << listaClientes[i].getNumCliente() << ","
                       << listaClientes[i].getNombre() << ","
                       << listaClientes[i].getApellido() << ","
                       << listaClientes[i].getMail() << ","
                       << listaClientes[i].getNumTelefono() << ","
                       << listaClientes[i].getDireccionDelCliente() << ","
                       << (listaClientes[i].getEliminado() ? "true" : "false") << "\n";
    }

    /// Buscar por if ternario

    ArchivoCSV.close();
    delete[] listaClientes;
    return true;
}
