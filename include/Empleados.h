#pragma once
#include "Persona.h"

class Empleados:public Persona
{
public:
    /// Constructores
    Empleados();
    Empleados(char* nombre, char* apellido, char* numTelefono, int dni, int dia, int mes, int anio, int numLegajo);

    /// Setters
    void setDNI(int DNI);
    void setLegajoEmpleado(int legajo);
    void setDiaIngreso(int dia);
    void setMesIngreso(int mes);
    void setAnioIngreso(int mes);

    /// Getters
    int getLegajoEmpleado();
    int getDNI();
    int getDiaIngreso();
    int getMesIngreso();
    int getAnioIngreso();

    ///Funciones de Clientes
    void menuEmpleados();
    void mostrarEmpleado(Empleados empleado, bool eliminado);
    void modificarEmpleado(Empleados empleado, int legajo);
    Empleados agregarEmpleado();
    void mostrarEmpleado(Empleados empleado);
    void ordenarEmpleados(Empleados *listaEmpleados, int cantidadEmpleados);

private:
    int _legajoEmpleado;
    int _dni;
    int _diaIngreso;
    int _mesIngreso;
    int _anioIngreso;

};
