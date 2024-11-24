//
// Created by felip on 19-11-2024.
//

#ifndef AVL_H
#define AVL_H

#include "Pedido.h"

struct NodoAVL {
    Pedido pedido;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(const Pedido& pedido) : pedido(pedido), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

class AVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo);
    int factorBalance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* balancear(NodoAVL* nodo);
    NodoAVL* insertar(NodoAVL* nodo, const Pedido& pedido);
    NodoAVL* eliminar(NodoAVL* nodo, int id, bool& encontrado);
    NodoAVL* minimoValorNodo(NodoAVL* nodo);
    Pedido buscar(NodoAVL* nodo, int id) const;

    void liberar(NodoAVL* nodo);

public:
    AVL();
    ~AVL();

    void insertarPedido(const Pedido& pedido);
    bool eliminarPedido(int id);
    Pedido buscarPedido(int id) const;
};

#endif // AVL_H
