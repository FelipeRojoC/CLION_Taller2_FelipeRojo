//
// Created by felip on 19-11-2024.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include "Pedido.h"
#include <queue>
#include <iostream>

class MinHeap {
private:
    struct NodoHeap {
        Pedido pedido;
        int prioridad;

        NodoHeap(const Pedido& pedido, int prioridad) : pedido(pedido), prioridad(prioridad) {}
    };

    std::queue<NodoHeap> heap;

    //Funcion para reorganizar los elementos en forma de MinHeap
    void reorganizar();

public:
    MinHeap(); //Constructor vacio

    void insertarPedido(const Pedido& pedido, int prioridad);
    Pedido extraerMin();
    bool estaVacio() const;
};

#endif // MINHEAP_H
