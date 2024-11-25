//
// Created by felip on 18-11-2024.
//

#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <list>

class Pedido {
private:
    int id;
    std::string nombreCliente;
    std::string apellidoCliente;
    std::list<std::string> productos;
    std::string horaPedido;
    bool enPreparacion;
    bool completado;

public:
    //Constructor predeterminado
    Pedido::Pedido() : id(0), nombreCliente(""), apellidoCliente(""), productos(), horaPedido(""), enPreparacion(false), completado(false) {}

    //Constructor de pedido
    Pedido::Pedido(int id, std::string nombreCliente, std::string apellidoCliente,
               std::list<std::string> productos, std::string horaPedido)
    : id(id), nombreCliente(nombreCliente), apellidoCliente(apellidoCliente),
      productos(productos), horaPedido(horaPedido), enPreparacion(false), completado(false) {}

    //Getters y Setters

    int Pedido::getId() const {
        return id;
    }

    const std::string& Pedido::getNombreCliente() const {
        return nombreCliente;
    }

    const std::string& Pedido::getApellidoCliente() const {
        return apellidoCliente;
    }

    const std::list<std::string>& Pedido::getProductos() const {
        return productos;
    }
    const std::string& Pedido::getHoraPedido() const {
        return horaPedido;
    }
    [[nodiscard]] bool isEnPreparacion() const;
    [[nodiscard]] bool isCompletado() const;

    void setNombreCliente(std::string nombreCliente);
    void setApellidoCliente(std::string apellidoCliente);
    void setProductos(std::list<std::string> productos);
    void setHoraPedido(std::string horaPedido);
    void setEstadoPreparacion(bool estado);
    void setEstadoCompletado(bool estado);
};

#endif // PEDIDO_H
