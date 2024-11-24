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
    //Constructor vacio
    Pedido();

    //Constructor de pedido
    Pedido(int id, std::string nombreCliente, std::string apellidoCliente,
           std::list<std::string> productos, std::string horaPedido);

    //Getters y setters
    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getNombreCliente() const;
    [[nodiscard]] const std::string& getApellidoCliente() const;
    [[nodiscard]] const std::list<std::string>& getProductos() const;
    [[nodiscard]] const std::string& getHoraPedido() const;
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
