//
// Created by felip on 19-11-2024.
//

#include "AVL.h"
#include <algorithm>
#include <iostream>
#include <stack>

//Constructor
AVL::AVL() : raiz(nullptr) {}

//Destructor
AVL::~AVL() {
    liberar(raiz);
}

//Liberar memoria recursivamente
void AVL::liberar(const NodoAVL* nodo) {
    if (!nodo) return;

    std::stack<const NodoAVL*> pila;
    pila.push(nodo);

    while (!pila.empty()) {
        const NodoAVL* actual = pila.top();
        pila.pop();

        if (actual->izquierdo) pila.push(actual->izquierdo);
        if (actual->derecho) pila.push(actual->derecho);

        delete actual;
    }
}

//Altura de un nodo
int AVL::altura(const NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

//Factor de balance
int AVL::factorBalance(const NodoAVL* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}

//Balancear un nodo
NodoAVL* AVL::balancear(NodoAVL* nodo) {

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

NodoAVL* AVL::minimoValorNodo(NodoAVL* nodo) {
    while (nodo && nodo->izquierdo) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

NodoAVL* AVL::insertarPedido(NodoAVL* nodo, const Pedido& pedido) {
    NodoAVL* padre = nullptr;
    NodoAVL* actual = nodo;

    //Buscar la posicion para insertar el nuevo nodo
    while (actual) {
        padre = actual;
        if (pedido.getId() < actual->pedido.getId()) {
            actual = actual->izquierdo;
        } else if (pedido.getId() > actual->pedido.getId()) {
            actual = actual->derecho;
        } else {
            return nodo;
        }
    }

    //Crear un nuevo nodo el auto funciona para deducir automaticamente
    auto nuevo = new NodoAVL(pedido);
    if (!padre) {
        return nuevo; // El árbol estaba vacío
    } else if (pedido.getId() < padre->pedido.getId()) {
        padre->izquierdo = nuevo;
    } else {
        padre->derecho = nuevo;
    }

    return balancear(nodo);
}



//Metodos publicos
void AVL::insertarPedido(const Pedido& pedido) {
    raiz = insertarPedido(raiz, pedido);
}

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
    return {};
}

//Eliminar el pedido del AVL
auto AVL::eliminarPedido(NodoAVL *nodo, int id, bool &encontrado) -> NodoAVL * {
    NodoAVL* padre = nullptr;
    NodoAVL* actual = nodo;

    //Buscar el nodo para eliminarlo
    while (actual && actual->pedido.getId() != id) {
        padre = actual;
        if (id < actual->pedido.getId()) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecho;
        }
    }

    //Encontar el nodo
    if (!actual) {
        return nodo;
    }
    encontrado = true;

    //Eliminar el nodo encontrado
    if (!actual->izquierdo || !actual->derecho) {
        NodoAVL* nuevoHijo = actual->izquierdo ? actual->izquierdo : actual->derecho;
        if (!padre) {
            delete actual;
            return nuevoHijo; //Eliminar el padre
        }
        if (actual == padre->izquierdo) {
            padre->izquierdo = nuevoHijo;
        } else {
            padre->derecho = nuevoHijo;
        }
        delete actual;
    } else {
        NodoAVL* sucesor = minimoValorNodo(actual->derecho);
        actual->pedido = sucesor->pedido;
        actual->derecho = eliminarPedido(actual->derecho, sucesor->pedido.getId(), encontrado);
    }

    //Actualizar y balancear
    return balancear(nodo);
}

