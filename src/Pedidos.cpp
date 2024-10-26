#include "Pedidos.h"
#include <iostream>

using namespace std;

Pedidos::Pedidos()
{

}

///Getters
string Pedidos::getNumPedido()
{
    return _numPedido;
}
string Pedidos::getNumCliente()
{
    return _numCliente;
}
string Pedidos::getNumLegajoEmpleado()
{
    return _numLegajoEmpleado;
}
string Pedidos::getDireccionDeEntre()
{
    return _direccionDeEntrega ;
}
string Pedidos::getNombreDelProducto()
{
    return _nombreProducto;
}
string Pedidos::getIdCategoriaProducto()
{
    return _IdCategoria;
}
float Pedidos::getPrecioUnitario()
{
    return _precioUnitario;
}
float Pedidos::getPrecioTotal()
{
    return _precioTotal;
}
string Pedidos::getDia()
{
    return _dia;
}
string Pedidos::getMes()
{
    return _mes;
}
string Pedidos::getAnio()
{
    return _anio;
}

///Setters
void Pedidos::setNumPedido(string numPedido)
{
    _numPedido = numPedido;
}
void Pedidos::setNumCliente(string numCliente)
{
    _numCliente = numCliente;
}
void Pedidos::setNumLegajoEmpleado(string numLegajo)
{
    _numLegajoEmpleado = numLegajo;
}
void Pedidos::setDireccionDeEntre(string direccion)
{
    _direccionDeEntrega = direccion;
}
void Pedidos::setNombreDelProducto(string nombreProducto)
{
    _nombreProducto = nombreProducto;
}
void Pedidos::setIdCategoriaProducto(string idCategoria)
{
    _IdCategoria = idCategoria;
}
void Pedidos::setPrecioUnitario(float precio)
{
    _precioUnitario = precio;
}
void Pedidos::setPrecioTotal(float precioTotal)
{
    _precioTotal = precioTotal;
}
void Pedidos::setDia(string dia)
{
    _dia = dia;
}
void Pedidos::setMes(string mes)
{
    _mes = mes;
}
void Pedidos::setAnio(string anio)
{
    _anio = anio;
}

///Metodos
void Pedidos::realizarPedido(){}
void Pedidos::agregarProductosAlPedido(){}
