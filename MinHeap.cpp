//
// Created by felip on 19-11-2024.
//


#include "MinHeap.h"

//Constructor
MinHeap::MinHeap() = default;

//Verifica si el MinHeap esta vacio
bool MinHeap::estaVacio() const {
    return heap.empty();
}

//Inserta un pedido en el MinHeap
void MinHeap::insertarPedido(const Pedido& pedido, int prioridad) {
    NodoHeap nuevoNodo(pedido, prioridad);

    //Usamos una cola temporal para reorganizar los elementos
    std::queue<NodoHeap> tempQueue;

    //Insertamos el nuevo nodo en su posicion
    bool insertado = false;
    while (!heap.empty()) {
        NodoHeap actual = heap.front();
        heap.pop();

        //Insertamos el nuevo nodo de acuerdo a su prioridad
        if (!insertado && nuevoNodo.prioridad < actual.prioridad) {
            tempQueue.push(nuevoNodo);
            insertado = true;
        }

        tempQueue.push(actual);
    }

    //Si no se inserto, se agrega al final
    if (!insertado) {
        tempQueue.push(nuevoNodo);
    }

    //Restauramos la cola ordenada al heap
    heap = tempQueue;
}

//Extrae el pedido con la minima prioridad
Pedido MinHeap::extraerMin() {
    if (estaVacio()) {
        std::cerr << "El MinHeap esta vacio \n";
        return Pedido();
    }

    NodoHeap minNodo = heap.front();
    heap.pop();

    return minNodo.pedido;
}
