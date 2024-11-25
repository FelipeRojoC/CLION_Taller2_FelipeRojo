//
// Created by felip on 18-11-2024.
//

#ifndef SISTEMAPEDIDO_H
#define SISTEMAPEDIDO_H

#include <string>
#include <list>
#include "AVL.h"
#include "MinHeap.h"

class SistemaPedido {
private:
    AVL avlPedidos;
    MinHeap heapPrioridad;

public:
    SistemaPedido();

    void crearPedido(const std::string& nombre, const std::string& apellido, const std::list<std::string>& productos);
    void entregarPedidos();
    void cancelarPedido(int id);
    void buscarPedido(int id) const;

    static void cerrarSistema();

    //Menu principal
    void mostrarMenu();
};

#endif // SISTEMAPEDIDO_H
