#pragma once
#include <string>

class Pedidos
{
public:
    Pedidos();

    ///Getters
    std::string getNumPedido();
    std::string getNumCliente();
    std::string getNumLegajoEmpleado();
    std::string getDireccionDeEntre();
    std::string getNombreDelProducto();
    std::string getIdCategoriaProducto();
    float getPrecioUnitario();
    float getPrecioTotal();
    std::string getDia();
    std::string getMes();
    std::string getAnio();

    ///Setters
    void setNumPedido(std::string numPedido);
    void setNumCliente(std::string numCliente);
    void setNumLegajoEmpleado(std::string numLegajo);
    void setDireccionDeEntre(std::string direccion);
    void setNombreDelProducto(std::string nombreProducto);
    void setIdCategoriaProducto(std::string idCategoria);
    void setPrecioUnitario(float precio);
    void setPrecioTotal(float precioTotal);
    void setDia(std::string dia);
    void setMes(std::string mes);
    void setAnio(std::string anio);

    ///Metodos
    void realizarPedido();
    void agregarProductosAlPedido();



protected:
    std::string _numPedido;
    std::string _numCliente;
    std::string _numLegajoEmpleado;
    std::string _direccionDeEntrega;
    std::string _nombreProducto;
    std::string _IdCategoria;
    float _precioUnitario;
    float _precioTotal;
    std::string _dia;
    std::string _mes;
    std::string _anio;



};
