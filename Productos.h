#pragma once
#include <string>

class Productos
{
    public:
        ///Constructores
        Productos();
        Productos(std::string sku, std::string codigoDeBarras, std::string _nombreProducto, std::string stockMinimo, std::string stockActual, float precioProducto, std::string categoria);

        ///Setters
        void setSku(std::string sku);
        void setCodigoDeBarras(std::string codigoDeBarras);
        void setNombreProducto(std::string nombre);
        void setStockMinimo(std::string stockMinimo);
        void setStockActual(std::string stockActual);
        void setPrecio(float precio);
        void setCategoria(std::string categoria);
        void setProductoEliminado(bool eliminado);

        ///Getters
        std::string getSku();
        std::string getCodigoDeBarras();
        std::string getNombreProducto();
        std::string getStockMinimo();
        std::string getStockActual();
        float getPrecioProducto();
        std::string getCategoria();
        bool getProductoEliminado();

        ///Funciones
        void menuProductos();
        bool agregarProducto();

    protected:
        std::string _SKU;
        std::string _codigoDeBarras;
        std::string _nombreProducto;
        std::string _stockMinimo;
        std::string _stockActual;
        float _precioProducto;
        std::string _categoriaProducto;
        bool _productoEliminado;
};
