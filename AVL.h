//
// Created by felip on 19-11-2024.
//

#ifndef AVL_H
#define AVL_H

#include "Pedido.h"
#include <utility>

struct NodoAVL {
    Pedido pedido;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    explicit NodoAVL(Pedido pedido) : pedido(std::move(pedido)), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

class AVL {
private:
    NodoAVL* raiz;

    static int altura(const NodoAVL* nodo);
    static int factorBalance(const NodoAVL* nodo);
    static NodoAVL* rotacionDerecha(NodoAVL* y);
    static NodoAVL* rotacionIzquierda(NodoAVL* x);
    static NodoAVL* minimoValorNodo(NodoAVL* nodo);
    static NodoAVL* balancear(NodoAVL* nodo);
    static NodoAVL* insertarPedido(NodoAVL* nodo, const Pedido& pedido);
    static NodoAVL* eliminarPedido(NodoAVL* nodo, int id, bool& encontrado);
    static void liberar(const NodoAVL* nodo);

public:
    AVL();
    ~AVL();
    void insertarPedido(const Pedido& pedido);
    [[nodiscard]] Pedido buscarPedido(int id) const;
};

#endif // AVL_H
