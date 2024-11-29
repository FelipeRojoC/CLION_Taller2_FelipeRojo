//
// Created by felip on 18-11-2024.
//

#ifndef SISTEMAPEDIDO_H
#define SISTEMAPEDIDO_H

#include <string>
#include <list>
#include "AVL.h"
#include "MinHeap.h"
#include <vector>

struct Producto {
    int id;
    std::string nombre;
    int precio;
};

class SistemaPedido {
private:
    AVL avlPedidos;
    MinHeap heapPrioridad;

public:
    SistemaPedido();

    void crearPedido(const std::string &nombre, const std::string &apellido, const std::list<std::string> &productos, int precioTotal);
    void entregarPedidos();
    void cancelarPedido(int id);
    void buscarPedido(int id) const;

    void cerrarSistema();

    //Productos cargados desde el archivo productos
    void cargarProductos(const std::string& nombreArchivo);
    void mostrarProductos();
    void mostrarHistorialPedidos() const;

    //Menu estadisticas requerimientos
    void pedidoMayorCantidadProductos() const;
    void pedidoMayorValor() const;
    void pedidoMayorTiempoEntrega() const;
    void mostrarPedidosCancelados() const;


    //Menu principal
    void mostrarMenu();
    void mostrarEstadisticas();
private:

    std::vector<Producto> productosDisponibles; // Productos disponibles de la lectura de archivos
    std::vector<Pedido> historialPedidos; // Historial de pedidos entregados
    std::vector<Pedido> pedidosCancelados; // Almacena los pedidos cancelados

};

#endif // SISTEMAPEDIDO_H
