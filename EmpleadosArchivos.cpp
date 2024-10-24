#include "EmpleadosArchivos.h"
#include <stdio.h>
#include <string.h>

EmpleadosArchivos::EmpleadosArchivos()
{
}
bool EmpleadosArchivos::guardar(const Empleados &Emp){
    FILE *pFile;
    bool resultado;
    pFile = fopen("ArchivoEmpleados.dat", "ab");

    if(pFile == nullptr)
    {
        return false;
    }

    resultado = fwrite(&Emp, sizeof(Empleados), 1, pFile);

    fclose(pFile);

    return resultado;
}

Empleados EmpleadosArchivos::leerEmpleado(int pos){
    FILE *pFile;
    pFile = fopen("ArchivoEmpleados.dat", "rb");
    Empleados empleado;

    if(pFile == nullptr)
    {
        return empleado;
    }

    fseek(pFile, sizeof(Empleados) * pos, SEEK_SET);

    fread(&empleado, sizeof(Empleados), 1, pFile);

    fclose(pFile);

    return empleado;
}

bool EmpleadosArchivos::modificarEmpleado(const Empleados &Emp, int pos){
    FILE *pFile;
    pFile = fopen("ArchivoEmpleados.dat", "rb+");
    bool resultado;
    if(pFile == nullptr)
    {
        return false;
    }
    fseek(pFile, sizeof(Empleados) * pos, SEEK_SET);

    resultado = fwrite(&Emp, sizeof(Empleados), 1, pFile)== 1;

    fclose(pFile);

    return resultado;

}

bool EmpleadosArchivos::listarEmpleados(Empleados emp[], int cantidad){
    FILE *pFile;
    bool resultado;
    pFile = fopen("ArchivoEmpleados.dat", "rb");

    if(pFile == nullptr)
    {
        return false;
    }
    resultado = fread(emp, sizeof(Empleados), cantidad, pFile) == cantidad;

    fclose(pFile);

    return resultado;
}

int EmpleadosArchivos::obtenerCantidadEmpleados()
{
    int cantidadEmpleados;
    FILE *pFile;
    pFile = fopen("ArchivoEmpleados.dat", "rb");

    if(pFile == nullptr)
    {
        return -1;
    }

    fseek(pFile, 0, SEEK_END);
    cantidadEmpleados = ftell(pFile);

    fclose(pFile);

    return cantidadEmpleados / sizeof(Empleados);
}
