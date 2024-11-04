#include "EmpleadosArchivos.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

EmpleadosArchivos::EmpleadosArchivos()
{
}
bool EmpleadosArchivos::guardar(const Empleados &Emp)
{
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

Empleados EmpleadosArchivos::leerEmpleado(int pos)
{
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

bool EmpleadosArchivos::modificarEmpleado(const Empleados &Emp, int pos)
{
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

bool EmpleadosArchivos::listarEmpleados(Empleados emp[], int cantidad)
{
    FILE *pFile;
    bool resultado;
    pFile = fopen("ArchivoEmpleados.dat", "rb");
    ///Esto es para que no genere un warning, se puede sacar
    size_t buscar = cantidad;

    if(pFile == nullptr)
    {
        return false;
    }
    ///No genera warning
    resultado = fread(emp, sizeof(Empleados), cantidad, pFile) == buscar;

    ///Genera warning, pero el programa se ejecuta sin problemas
    //resultado = fread(emp, sizeof(Empleados), cantidad, pFile) == cantidad;
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
///Esta funci¢n retorna que empleado va a armar el pedido
int EmpleadosArchivos::seleccionarEmpleadoParaArmarPedido()
{
    srand(time(NULL));
    EmpleadosArchivos EmArchivos;
    Empleados *listaEmpleados;
    listaEmpleados = new Empleados[EmArchivos.obtenerCantidadEmpleados()];

    int empleadosActivos = 0;
    ///Ac  obtenemos la cantidad de empleados activos
    for (int i = 0; i < EmArchivos.obtenerCantidadEmpleados(); i++)
    {
        listaEmpleados[i] = EmArchivos.leerEmpleado(i);
        if (!listaEmpleados[i].getEliminado())empleadosActivos++;
    }
    ///Esto selecciona a un empleado al azar
    int empleadoSeleccionado = rand()%empleadosActivos + 1, variableAux = 1;

    ///Recorremos la lista de empleados verificando si el empleado no est  eliminado
    for (int i = 0; i < EmArchivos.obtenerCantidadEmpleados(); i++)
    {
        if (!listaEmpleados[i].getEliminado())  //Verificamos que no est  eliminado el empleado
        {
            if (variableAux == empleadoSeleccionado) //Si la variable auxiliar es igual al empleado seleccionado, devuelve  el legajo
            {
                return listaEmpleados[i].getLegajoEmpleado();
            }
            else
            {
                variableAux++; //Caso contrario, suma 1 a la variable auxiliar
            }
        }
    }

    return  -1;
}
