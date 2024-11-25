#include <iostream>
#include "SistemaPedido.h"

int main() {
    //Inicializar el sistemaimpl de sistema pedido
    SistemaPedido sistema;

    //Mostrar el menu principal
    sistema.mostrarMenu();

    std::cout << "Programa finalizado. ¡Gracias por usar el sistema de pedidos!\n";
    return 0;
}