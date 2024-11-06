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
        void buscarUnProducto(std::string busqueda, bool visualizarInfo);
        void imprimirElProducto(Productos producto, bool infoResumida);
        void modificarProducto();
        void mostrarProductos(bool estaActivo, int &cantidad);
        void modificarStockActual(std::string numProducto, int cantidadDeProductos);

        ///Funci¢n para buscar productos y cargarlos en la lista de compras para los pedidos
        void buscarUnProducto(Productos *listaCompras, std::string busqueda, int &cantidadDeProductosEncontrados);
        void buscarUnProductoConStock(Productos *listaCompras, std::string busqueda, int &cantidadDeProductosEncontrados);



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
