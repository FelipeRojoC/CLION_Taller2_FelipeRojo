//
// Created by felip on 19-11-2024.
//


#include "MinHeap.h"
#include <algorithm> //Funcion std::sort para realizar mov mas eficiente
#include <iostream>
#include <ostream>

//Verificar si el MinHeap esta vacio
[[nodiscard]] bool MinHeap::estaVacio() const {
    return heap.empty();
}

//Inserta un pedido en el MinHeap
void MinHeap::insertarPedido(Pedido pedido, int prioridad) {
    NodoHeap nuevoNodo(std::move(pedido), prioridad);

    // Usamos una cola temporal para reorganizar los elementos
    std::queue<NodoHeap> tempQueue;

    bool insertado = false;
    while (!heap.empty()) {
        NodoHeap actual = heap.front();
        heap.pop();

        if (!insertado && nuevoNodo.prioridad < actual.prioridad) {
            tempQueue.push(nuevoNodo);
            insertado = true;
        }

        tempQueue.push(actual);
    }

    //Si el nodo no ha sido insertado, se agrega
    if (!insertado) {
        tempQueue.push(nuevoNodo);
    }

    //Restauramos la cola ordenada al heap
    heap = std::move(tempQueue);
}

//Extrae el pedido con la minima prioridad
[[nodiscard]] Pedido MinHeap::extraerMin() {
    if (estaVacio()) {
        std::cout << "El MinHeap esta vacio \n"<< std::endl;
        return {}; //Retorna un pedido vacío si no hay elementos
    }

    NodoHeap minNodo = heap.front(); //Nodo con menor prioridad
    heap.pop();                      //Elimina el nodo de la cola

    return minNodo.pedido;
}

void MinHeap::reorganizar() {
    //Pasamos los elementos de la cola a un vector
    std::vector<NodoHeap> elementos;
    while (!heap.empty()) {
        elementos.push_back(heap.front());
        heap.pop();
    }

    //Se ordena el vector segun su prioridad de menor a mayor
    std::ranges::sort(elementos, [](const NodoHeap& a, const NodoHeap& b) {
        return a.prioridad < b.prioridad;
    });

    //Se reconstruye la cola con los elementos ordenados
    for (const auto& nodo : elementos) {
        heap.push(nodo);
    }
}