#pragma once
#include "Empleados.h"

class EmpleadosArchivos
{
    public:
        EmpleadosArchivos();
        bool guardar(const Empleados &Emp);
        bool eliminarEmpleado();
        Empleados leerEmpleado(int pos);
        bool listarEmpleados(Empleados registro[], int cantidad);
        int obtenerCantidadEmpleados();
        bool modificarEmpleado(const Empleados &Emp, int pos);

    protected:

    private:
};
