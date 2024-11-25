//
// Created by felip on 18-11-2024.
//

#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <list>

class Pedido {
private:
    //Atributos
    int id;
    std::string nombreCliente;
    std::string apellidoCliente;
    std::list<std::string> productos;
    std::string horaPedido;
    bool enPreparacion;
    bool completado;

public:
    //Constructor vacio
    Pedido();

    //Constructor de pedido
    Pedido(int id, const std::string &nombreCliente, const std::string &apellidoCliente,
           const std::list<std::string> &productos, const std::string &horaPedido);

    //Getters y setters
    int getId() const;
    const std::string& getNombreCliente() const;
    const std::string& getApellidoCliente() const;
    const std::list<std::string>& getProductos() const;
    const std::string& getHoraPedido() const;
    bool isEnPreparacion() const;
    bool isCompletado() const;

    void setNombreCliente(std::string nombreCliente);
    void setApellidoCliente(std::string apellidoCliente);
    void setProductos(std::list<std::string> productos);
    void setHoraPedido(std::string horaPedido);
    void setEstadoPreparacion(bool estado);
    void setEstadoCompletado(bool estado);
};

#endif // PEDIDO_H
