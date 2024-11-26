//
// Created by felip on 18-11-2024.
//

#include "Pedido.h"
#include <string>
#include <list>

// Constructor de pedido
Pedido::Pedido(int id, const std::string &nombreCliente, const std::string &apellidoCliente,
               const std::list<std::string> &productos, const std::string &horaPedido,
               bool enPreparacion, bool completado)
    : id(id),
      nombreCliente(nombreCliente),
      apellidoCliente(apellidoCliente),
      productos(productos),
      horaPedido(horaPedido),
      enPreparacion(enPreparacion),
      completado(completado) {}

// Getters y setters
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

bool Pedido::isEnPreparacion() const {
    return enPreparacion;
}

bool Pedido::isCompletado() const {
    return completado;
}

void Pedido::setNombreCliente(const std::string &nombreCliente) {
    this->nombreCliente = nombreCliente;
}

void Pedido::setApellidoCliente(const std::string &apellidoCliente) {
    this->apellidoCliente = apellidoCliente;
}

void Pedido::setProductos(const std::list<std::string> &productos) {
    this->productos = productos;
}

void Pedido::setHoraPedido(const std::string &horaPedido) {
    this->horaPedido = horaPedido;
}

void Pedido::setEstadoPreparacion(bool estado) {
    this->enPreparacion = estado;
}

void Pedido::setEstadoCompletado(bool estado) {
    this->completado = estado;
}

