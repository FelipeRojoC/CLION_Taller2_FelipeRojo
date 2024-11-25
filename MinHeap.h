//
// Created by felip on 19-11-2024.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include "Pedido.h"
#include <queue>

class MinHeap {
private:
    struct NodoHeap {
        Pedido pedido;
        int prioridad;

        NodoHeap(Pedido pedido, int prioridad)
            : pedido(std::move(pedido)), prioridad(prioridad) {}
    };

    std::queue<NodoHeap> heap;

    //Funcion para reorganizar los elementos en forma de MinHeap
    void reorganizar();

public:
    MinHeap() = default;
    void cancelarPedido(int id);
    void insertarPedido(Pedido pedido, int prioridad);
    [[nodiscard]] Pedido extraerMin(); //nodiscard indica que el valor devuelto no debe ignorarse
    [[nodiscard]] bool estaVacio() const;
};

#endif // MINHEAP_H
