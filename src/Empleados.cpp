#include "Empleados.h"
#include "EmpleadosArchivos.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace std;

///Constructores

Empleados::Empleados()
{
}

Empleados::Empleados(char* nombre, char* apellido, char* numTelefono, int dni, int dia, int mes, int anio, int numLegajo)
{
    strcpy(_nombre, nombre);
    strcpy(_apellido, apellido);
    nombre[0] = (char)tolower(nombre[0]);
    apellido[0] = (char)tolower(apellido[0]);
    strcat(_direccionDeMail, nombre);
    strcat(_direccionDeMail, ".");
    strcat(_direccionDeMail, apellido);
    strcat(_direccionDeMail, "@empresa.com");
    strcpy(_numTelefono, numTelefono);
    _dni = dni;
    _legajoEmpleado = numLegajo;
    _diaIngreso = dia;
    _mesIngreso = mes;
    _anioIngreso = anio;
}

///Setters
void Empleados::setDNI(int DNI)
{
    _dni = DNI;
}
void Empleados::setLegajoEmpleado(int legajo)
{
    _legajoEmpleado = legajo;
}
void Empleados::setDiaIngreso(int dia)
{
    _diaIngreso = dia;
}
void Empleados::setMesIngreso(int mes)
{
    _mesIngreso = mes;
}
void Empleados::setAnioIngreso(int anio)
{
    _anioIngreso = anio;
}

///Getters
int Empleados::getLegajoEmpleado()
{
    return _legajoEmpleado;
}
int Empleados::getDNI()
{
    return _dni;
}
int Empleados::getDiaIngreso()
{
    return _diaIngreso;
}
int Empleados::getMesIngreso()
{
    return _mesIngreso;
}
int Empleados::getAnioIngreso()
{
    return _anioIngreso;
}

///Funciones de clientes

void Empleados::menuEmpleados()
{
    int opcion;
    do
    {
        cout << "--------------------------"<< endl;
        cout << "¨Qu‚ desea realizar?" << endl;
        cout << "1 - Agregar un empleado al sistema " << endl;
        cout << "2 - Buscar un empleado en el sistema " << endl;
        cout << "3 - Modificar la informaci¢n de un empleado " << endl;
        cout << "4 - Eliminar un empleado del sistema " << endl;
        cout << "5 - Recuperar a un empleado eliminado" << endl;
        cout << "6 - Listar los empleados activos " << endl;
        cout << "7 - Listas los empleados inactivos" << endl;
        cout << "0 - Salir del menu de empleados " << endl;
        cin >> opcion;

        EmpleadosArchivos Archivo;
        Empleados empleado;
        int legajoABuscar;

        switch(opcion)
        {
        case 1:
            empleado = agregarEmpleado();
            if (Archivo.guardar(empleado))
            {
                cout << "Se guardo el empleado de manera correcta" << endl;
            }
            else
            {
                cout << "No se pudo guardar el empleado" << endl;
            }
            break;
        case 2:
            cout << "Indique el legajo del empleado que desea buscar: ";
            cin >> legajoABuscar;
            legajoABuscar--;
            if (legajoABuscar < Archivo.obtenerCantidadEmpleados())
            {
                empleado = Archivo.leerEmpleado(legajoABuscar);
                mostrarEmpleado(empleado, empleado.getEliminado());
            }
            else
            {
                cout << "No hay ning£n empleado con ese legajo" << endl;
            }
            break;
        case 3:
            cout << "Indique el legajo del empleado que desea modificar: ";
            cin >> legajoABuscar;
            legajoABuscar--;
            if (legajoABuscar < Archivo.obtenerCantidadEmpleados())
            {
                empleado = Archivo.leerEmpleado(legajoABuscar);
                modificarEmpleado(empleado, legajoABuscar);
            }
            else
            {
                cout << "No hay ning£n empleado con ese legajo" << endl;
            }
            break;
        case 4:
            cout << "Indique el legajo del empleado que desea eliminar: ";
            cin >> legajoABuscar;
            legajoABuscar--;
            if (legajoABuscar < Archivo.obtenerCantidadEmpleados())
            {
                empleado = Archivo.leerEmpleado(legajoABuscar);
                empleado.setEliminado(true);
                if (Archivo.modificarEmpleado(empleado, legajoABuscar))
                {
                    cout << "Se ha eliminado al empleado de forma exitosa" << endl;
                }
                else
                {
                    cout << "No se ha podido eliminar al empleado" << endl;
                }
            }
            else
            {
                cout << "No hay ning£n empleado con ese legajo" << endl;
            }
            break;
        case 5:
            cout << "Indique el legajo del empleado que desea recuperar: ";
            cin >> legajoABuscar;
            legajoABuscar--;
            if (legajoABuscar < Archivo.obtenerCantidadEmpleados())
            {
                empleado = Archivo.leerEmpleado(legajoABuscar);
                if (empleado.getEliminado())
                {
                    empleado.setEliminado(false);
                    if (Archivo.modificarEmpleado(empleado, legajoABuscar))
                    {
                        cout << "Se ha eliminado al empleado de forma exitosa" << endl;
                    }
                    else
                    {
                        cout << "No se ha podido eliminar al empleado" << endl;
                    }

                }
                else
                {
                    cout << "El empleado no se encuentra eliminado" << endl;
                }

            }
            else
            {
                cout << "No hay ning£n empleado con ese legajo" << endl;
            }
            break;
        case 6:
            for (int i = 0; i < Archivo.obtenerCantidadEmpleados(); i++)
            {
                empleado = Archivo.leerEmpleado(i);
                cout << "------------------------------" << endl;
                mostrarEmpleado(empleado, true);
            }
            break;
        case 7:
            for (int i = 0; i < Archivo.obtenerCantidadEmpleados(); i++)
            {
                empleado = Archivo.leerEmpleado(i);
                cout << "------------------------------" << endl;
                mostrarEmpleado(empleado, false);
            }
        break;
    case 0:
        cout << "Saliendo... " << endl;
        break;
    default:
        cout << "Error, ingrese un valor correcto " << endl;
        break;
    }
    cout << endl << endl;
}
while (opcion != 0);
}

Empleados Empleados::agregarEmpleado()
{
    EmpleadosArchivos Archivo;
    char nombre[50], apellido[50], numTelefono[25];
    int dni, dia, mes, anio;

    cout << "Ingrese el nombre del empleado: ";
    do
    {
        cin >> nombre;
        if (strlen(nombre)>25) cout << "Error, nombre muy largo, ingrese nuevamente el nombre: ";
    }
    while (strlen(nombre)>25);   ///Comprueba que el nombre no tiene m s de 25 caracteres

    cout << "Ingrese el apellido del empleado: ";
    do
    {
        cin >> apellido;
        if (strlen(apellido)>25) cout << "Error, apellido muy largo, ingrese nuevamente el nombre: ";
    }
    while (strlen(apellido)>25);  ///Comprueba que el apellido no tiene m s de 25 caracteres

    cout << "Ingrese el numero de telefono del empleado: ";
    cin >> numTelefono;
    cout << "Ingrese el DNI del empleado: ";
    cin >> dni;
    cout << "Ingrese la fecha de ingreso del empleado" << endl;
    cout << "D¡a: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;

    int legajo = Archivo.obtenerCantidadEmpleados() + 1;

    if (legajo == 0) legajo = 1;

    return Empleados(nombre, apellido, numTelefono, dni, dia, mes, anio, legajo);
}

void Empleados::mostrarEmpleado(Empleados empleado, bool eliminado)
{
    if (empleado.getEliminado() == eliminado)
    {
        cout << "Nombre: " << empleado.getNombre() << endl;
        cout << "Apellido: " << empleado.getApellido() << endl;
        cout << "DNI: " << empleado.getDNI() << endl;
        cout << "Legajo: " << empleado.getLegajoEmpleado() << endl;
        cout << "N£mero de telefono: " << empleado.getNumTelefono() << endl;
        cout << "Direcccion de email: " << empleado.getMail() << endl;
        cout << "Fecha de ingreso: " << empleado.getDiaIngreso() << "/" << empleado.getMesIngreso() << "/" << empleado.getAnioIngreso() << endl;
    }
}

void Empleados::modificarEmpleado(Empleados empleado, int legajo)
{
    int opcion;
    do
    {
        cout << "¨Qu‚ desea modificar?" << endl;
        cout << "1 - Nombre" << endl;
        cout << "2 - Apellido" << endl;
        cout << "3 - N£mero de telefono" << endl;
        cout << "4 - DNI " << endl;
        cout << "5 - Direcci¢n de mail " << endl;
        cout << "6 - Fecha de ingreso " << endl;
        cout << "0 - Salir " << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            char nombreNuevo[25];
            cout << "Ingrese el nombre nuevo: ";
            cin >> nombreNuevo;
            empleado.setNombre(nombreNuevo);
            break;
        }
        case 2:
        {
            char apellidoNuevo[25];
            cout << "Ingrese el apellido nuevo: ";
            cin >> apellidoNuevo;
            empleado.setApellido(apellidoNuevo);
            break;
        }
        case 3:
        {
            char numTelNuevo[25];
            cout << "Ingrese el nuevo n£mero de telefono: ";
            cin >> numTelNuevo;
            empleado.setNumTelefono(numTelNuevo);
            break;
        }
        case 4:
        {
            int numDNINuevo;
            cout << "Ingrese el nuevo n£mero de DNI: ";
            cin >> numDNINuevo;
            empleado.setDNI(numDNINuevo);
            break;
        }
        case 5:
        {
            char mailNuevo[100];
            cout << "Ingrese la nueva direcci¢n de mail: ";
            cin >> mailNuevo;
            empleado.setMail(mailNuevo);
            break;
        }
        case 6:
        {
            int dia, mes, anio;
            cout << "Ingrese el d¡a: ";
            cin >> dia;
            cout << "Ingrese el mes: ";
            cin >> mes;
            cout << "Ingrese el a¤o: ";
            cin >> anio;
            empleado.setDiaIngreso(dia);
            empleado.setMesIngreso(mes);
            empleado.setAnioIngreso(anio);
        }
        case 0:
            cout << "Saliendo...";
            break;
        default:
            cout << "Error, ingrese un valor correcto" << endl;
            break;
        }
    }
    while (opcion != 0);
    EmpleadosArchivos Archivo;
    system("cls");
    if (Archivo.modificarEmpleado(empleado, legajo))
    {
        cout << "Se modifico la informaci¢n de forma correcta" << endl;
    }
    else
    {
        cout << "No se ha podido modificar la informaci¢n de forma correcta" << endl;
    }
}
