//
// Created by felip on 19-11-2024.
//

#include "AVL.h"
#include <algorithm>
#include <iostream>

//Constructor
AVL::AVL() : raiz(nullptr) {}

//Destructor
AVL::~AVL() {
    liberar(raiz);
}

//Liberar memoria recursivamente
void AVL::liberar(NodoAVL* nodo) {
    if (nodo) {
        liberar(nodo->izquierdo);
        liberar(nodo->derecho);
        delete nodo;
    }
}

//Altura de un nodo
int AVL::altura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

//Factor de balance
int AVL::factorBalance(NodoAVL* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}

//Balancear un nodo
NodoAVL* AVL::balancear(NodoAVL* nodo) {
    if (!nodo) return nodo;

    int balance = factorBalance(nodo);

    //Rotacion derecha
    if (balance > 1 && factorBalance(nodo->izquierdo) >= 0) {
        return rotacionDerecha(nodo);
    }

    //Rotacion izquierda
    if (balance < -1 && factorBalance(nodo->derecho) <= 0) {
        return rotacionIzquierda(nodo);
    }

    //Rotacion izquierda-derecha
    if (balance > 1 && factorBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    //Rotacion derecha-izquierda
    if (balance < -1 && factorBalance(nodo->derecho) > 0) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

//Rotacion a la derecha
NodoAVL* AVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = std::max(altura(y->izquierdo), altura(y->derecho)) + 1;
    x->altura = std::max(altura(x->izquierdo), altura(x->derecho)) + 1;

    return x;
}

//Rotacion a la izquierda
NodoAVL* AVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = std::max(altura(x->izquierdo), altura(x->derecho)) + 1;
    y->altura = std::max(altura(y->izquierdo), altura(y->derecho)) + 1;

    return y;
}

//Minimo valor en el Nodo
NodoAVL* AVL::minimoValorNodo(NodoAVL* nodo) {
    while (nodo && nodo->izquierdo) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

//Insertar en AVL
NodoAVL* AVL::insertar(NodoAVL* nodo, const Pedido& pedido) {
    if (!nodo) {
        return new NodoAVL(pedido);
    }

    if (pedido.getId() < nodo->pedido.getId()) {
        nodo->izquierdo = insertar(nodo->izquierdo, pedido);
    } else if (pedido.getId() > nodo->pedido.getId()) {
        nodo->derecho = insertar(nodo->derecho, pedido);
    } else {
        //No se puede tener un id repetido
        return nodo;
    }

    nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));
    return balancear(nodo);
}

void AVL::insertarPedido(const Pedido& pedido) {
    raiz = insertar(raiz, pedido);
}

//Buscar un pedido por su ID
Pedido AVL::buscarPedido(int id) const {
    NodoAVL* nodo = raiz;
    while (nodo) {
        if (id < nodo->pedido.getId()) {
            nodo = nodo->izquierdo;
        } else if (id > nodo->pedido.getId()) {
            nodo = nodo->derecho;
        } else {
            return nodo->pedido;
        }
    }
    return Pedido();
}