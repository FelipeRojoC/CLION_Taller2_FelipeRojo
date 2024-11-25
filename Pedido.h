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

    //Constructor de pedido default
    Pedido() : id(0), nombreCliente(""), apellidoCliente(""),
               horaPedido(""), enPreparacion(false), completado(false) {}

    //Constructor de pedido
    Pedido(int id, const std::string &nombreCliente, const std::string &apellidoCliente,
           const std::list<std::string> &productos, const std::string &horaPedido,
           bool enPreparacion = false, bool completado = false);

    //Getters y setters
    int getId() const;
    const std::string& getNombreCliente() const;
    const std::string& getApellidoCliente() const;
    const std::list<std::string>& getProductos() const;
    const std::string& getHoraPedido() const;
    bool isEnPreparacion() const;
    bool isCompletado() const;

    void setNombreCliente(const std::string &nombreCliente);
    void setApellidoCliente(const std::string &apellidoCliente);
    void setProductos(const std::list<std::string> &productos);
    void setHoraPedido(const std::string &horaPedido);
    void setEstadoPreparacion(bool estado);
    void setEstadoCompletado(bool estado);
};

#endif // PEDIDO_H
