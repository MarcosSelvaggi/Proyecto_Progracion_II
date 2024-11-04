#include "Clientes.h"
#include "ClientesArchivo.h"
#include <iostream>
#include <string.h>

using namespace std;

///Constructores
Clientes::Clientes()
{
}

Clientes::Clientes(char* nombre, char* apellido, char* numTelefono, char* direccionDelCliente, int numCliente, char* direccionDeMail)
{
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    strcpy(_direccionDeMail, direccionDeMail);
    strcpy(_direccionDelCliente, direccionDelCliente);
    strcpy(_numTelefono, numTelefono);
    _numCliente = numCliente + 1;
}

///Setters
void Clientes::setNumCliente(int numCliente)
{
    _numCliente = numCliente;
}
void Clientes::setDireccionDelCliente(char* direccion)
{
    strcpy(_direccionDelCliente, direccion);
}

///Getters
int Clientes::getNumCliente()
{
    return _numCliente;
}
char* Clientes::getDireccionDelCliente()
{
    return _direccionDelCliente;
}

///Funciones
void Clientes::menuClientes()
{
    int opcion;
    Clientes cliente;
    ClientesArchivo ClArchivos;
    int posicion;
    do
    {
        cout << "--------------------------"<< endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Agregar un cliente" << endl;
        cout << "2 - Buscar un cliente" << endl;
        cout << "3 - Modificar un cliente" << endl;
        cout << "4 - Eliminar un cliente" << endl;
        cout << "5 - Recuperar un cliente" << endl;
        cout << "6 - Listar clientes activos" << endl;
        cout << "7 - Listar clientes inactivos" << endl;
        cout << "0 - Salir" << endl;
        cin >> opcion;


        switch (opcion)
        {
        case 1:
            if (cliente.agregarCliente())
            {
                cout << "Se ha agregado el cliente" << endl;
            }
            else
            {
                cout << "No se ha podido agregar el cliente" << endl;
            }
            break;
        case 2:
            cout << "Ingrese el ID del cliente a buscar: ";
            cin >> posicion;
            ///Compara el n£mero ingresado con la cantidad de clientes que hay, si el n£mero ingresado es mayor a la cantidad de clientes
            ///devuelve error
            if (posicion <= ClArchivos.obtenerCantidadDeClientes())
            {
                ClArchivos.buscarCliente(cliente, posicion);

                cliente.mostrarCliente(cliente);
            }
            else
            {
                cout << "No hay ning£n cliente con esa ID" << endl;
            }
            break;
        case 3:
            cout << "Ingrese el ID del cliente a modificar: ";
            cin >> posicion;
            if (posicion <= ClArchivos.obtenerCantidadDeClientes())
            {
                ClArchivos.buscarCliente(cliente, posicion);
                if (cliente.modificarCliente(cliente, posicion))
                {
                    cout << "Se ha modificado la informaci¢n del cliente" << endl;
                }
                else
                {
                    cout << "No se ha podido modificar la informaci¢n del cliente" << endl;
                }
            }
            else
            {
                cout << "No hay ning£n cliente con esa ID";
            }
            break;
        case 4:
            cout << "¨Qu‚ cliente desea eliminar?" << endl;
            cin >> posicion;
            if (posicion <= ClArchivos.obtenerCantidadDeClientes())
            {
                ClArchivos.buscarCliente(cliente, posicion);
                cambiarEstadoEliminado(cliente, true);
                if (ClArchivos.modificarClienteArchivo(cliente, posicion))
                {
                    cout << "Se ha modificado la informaci¢n del cliente" << endl;
                }
                else
                {
                    cout << "No se ha podido modificar la informaci¢n del cliente" << endl;
                }
            }
            else
            {
                cout << "No hay ning£n cliente con esa ID";
            }
            break;
        case 5:
            cout << "¨Qu‚ cliente desea eliminar?" << endl;
            cin >> posicion;
            if (posicion <= ClArchivos.obtenerCantidadDeClientes())
            {
                ClArchivos.buscarCliente(cliente, posicion);
                cambiarEstadoEliminado(cliente, false);
                if (ClArchivos.modificarClienteArchivo(cliente, posicion))
                {
                    cout << "Se ha modificado la informaci¢n del cliente" << endl;
                }
                else
                {
                    cout << "No se ha podido modificar la informaci¢n del cliente" << endl;
                }
            }
            else
            {
                cout << "No hay ning£n cliente con esa ID";
            }
            break;
        case 6:
            ///La funci¢n listar puede recibir un booleano, dependiendo si recibe false o true muestra o no las cuentas inactivas
            cliente.listarClientes(false);
            break;
        case 7:
            cliente.listarClientes(true);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Error, eliga una opci¢n valida" << endl;
            break;
        }
    }
    while (opcion != 0);
}
bool Clientes::agregarCliente()
{
    ClientesArchivo ClArchivo;
    int numCliente = ClArchivo.obtenerCantidadDeClientes();
    if (numCliente == -1)
    {
        return false;
    }
    char nombre[25], apellido[25], direccionDelCliente[100], direccionDeMail[100], numTelefono[25];
    string direccionClienteString;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;
    cout << "Ingrese el apellido del cliente: ";
    cin >> apellido;
    cout << "Ingrese su direcci¢n de mail: ";
    cin >> direccionDeMail;
    cout << "Ingrese su direcci¢n: ";
    cin.ignore();
    getline(cin, direccionClienteString);
    cout << "Ingrese su n£mero de telefono: ";
    cin >> numTelefono;

    strcpy(direccionDelCliente, direccionClienteString.c_str());

    Clientes cliente(nombre, apellido, numTelefono, direccionDelCliente, numCliente, direccionDeMail);

    return ClArchivo.guardarCliente(cliente);
}
///Recibe un Cliente y su ID de cliente, luego lo manda para guardar
bool Clientes::modificarCliente(Clientes cliente, int posicion)
{
    ClientesArchivo ClArchivo;
    int atributoAModificar;
    do
    {
        cout << "¨Qu‚ desea modiicar?" << endl;
        cout << "1 - Nombre" << endl;
        cout << "2 - Apellido" << endl;
        cout << "3 - N£mero de telefono" << endl;
        cout << "4 - Direcci¢n del cliente" << endl;
        cout << "5 - Direcci¢n de Mail" << endl;
        cout << "0 - Salir" << endl;
        cin >> atributoAModificar;
        switch (atributoAModificar)
        {
        case 1:
        {
            char nombreNuevo[25];
            cout << "Ingrese el nombre nuevo: ";
            cin >> nombreNuevo;
            cliente.setNombre(nombreNuevo);
            break;
        }
        case 2:
        {
            char apellidoNuevo[25];
            cout << "Ingrese el apellido nuevo: ";
            cin >> apellidoNuevo;
            cliente.setApellido(apellidoNuevo);
            break;
        }
        case 3:
        {
            char numTelNuevo[25];
            cout << "Ingrese el nuevo n£mero de telefono: ";
            cin >> numTelNuevo;
            cliente.setNumTelefono(numTelNuevo);
            break;
        }
        case 4:
        {
            char direccionCliente[100];
            cout << "Ingrese la nueva direcci¢n: ";
            cin >> direccionCliente;
            cliente.setDireccionDelCliente(direccionCliente);
            break;
        }
        case 5:
        {
            char mailNuevo[100];
            cout << "Ingrese la nueva direcci¢n de mail: ";
            cin >> mailNuevo;
            cliente.setMail(mailNuevo);
            break;
        }
        case 0:
            break;
        default:
            cout << "Error, ingrese un valor correcto" << endl;
            break;
        }

    }
    while (atributoAModificar != 0);

    return ClArchivo.modificarClienteArchivo(cliente, posicion);
}

void Clientes::mostrarCliente(Clientes cliente)
{
    cout << "--------------------------------------" << endl;
    cout << "ID del cliente: " << cliente.getNumCliente() << endl;
    cout << "Nombre: " << cliente.getNombre() << endl;
    cout << "Apellido: " << cliente.getApellido() << endl;
    cout << "Mail: " << cliente.getMail() << endl;
    cout << "Numero de tel‚fono: " << cliente.getNumTelefono() << endl;
    cout << "Direcci¢n: " << cliente.getDireccionDelCliente() << endl;
}

void Clientes::cambiarEstadoEliminado(Clientes &cliente, bool estado)
{
    cliente.setEliminado(estado);
}
///Esta funci¢n lista a los clientes, si recibe false, muestra a los activos, si recibe true muestra a los inactivos
void Clientes::listarClientes(bool eliminado)
{
    ClientesArchivo ClArchivo;
    Clientes *listaClientes, cliente;

    listaClientes = new Clientes[ClArchivo.obtenerCantidadDeClientes()];

    ClArchivo.leerCliente(listaClientes);

    int vueltas = 0;
    bool noHayClientes = true;

    for (int i = 0; i < ClArchivo.obtenerCantidadDeClientes(); i++)
    {
        if (eliminado == listaClientes[i].getEliminado())
        {
            noHayClientes = false;
            cliente.mostrarCliente(listaClientes[i]);
            vueltas++;
        }
        else
        {
        }
        if (vueltas == 10)
        {
            int eleccion;
            cout << "¨Desea visualizar m s clientes?" << endl;
            cout << "1 - S¡, 2 - No" << endl;
            cin >> eleccion;
            if (eleccion == 1)
            {
                vueltas = 0;
            }
            else
            {
                break;
            }
        }
    }

    if (noHayClientes) cout << "No hay clientes para mostrar" << endl;
    delete[] listaClientes;
}


