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
    std::string getIdDelProducto();
    std::string getNombreDelProducto();
    std::string getIdCategoriaProducto();
    std::string getCantidadSolicitada();
    std::string getStockDelProducto();
    float getPrecioUnitario();
    std::string getDia();
    std::string getMes();
    std::string getAnio();

    ///Setters
    void setNumPedido(std::string numPedido);
    void setNumCliente(std::string numCliente);
    void setNumLegajoEmpleado(std::string numLegajo);
    void setDireccionDeEntre(std::string direccion);
    void setIdDelProducto(std::string idProducto);
    void setNombreDelProducto(std::string nombreProducto);
    void setIdCategoriaProducto(std::string idCategoria);
    void setCantidadSolicitada(std::string cantidadSolicitada);
    void setStockDelProducto(std::string stockProducto);
    void setPrecioUnitario(float precio);
    void setDia(std::string dia);
    void setMes(std::string mes);
    void setAnio(std::string anio);

    ///Metodos
    void realizarPedido();
    void agregarProductosAlPedido(Pedidos pedido);
    void mostrarCarritoDeCompras();
    void ajustarCantidadDeProducto();
    void eliminarUnProductoDelCarrito();
    int realizarPago();

protected:
    std::string _numPedido;
    std::string _numCliente;
    std::string _numLegajoEmpleado;
    std::string _direccionDeEntrega;
    std::string _IdDelProducto;
    std::string _nombreProducto;
    std::string _cantidadSolicitada;
    std::string _IdCategoria;
    std::string _stockDelProducto;
    float _precioUnitario;
    std::string _dia;
    std::string _mes;
    std::string _anio;




};
