//
// Created by felip on 18-11-2024.
//

#include "SistemaPedido.h"
#include <ctime>
#include <iostream>
#include <ostream>

//Constructor
SistemaPedido::SistemaPedido() {
    std::cout << "Iniciando el sistema de pedidos Grill of Victory \n";
}

//Crear un nuevo pedido
void SistemaPedido::crearPedido(const std::string& nombre, const std::string& apellido, const std::list<std::string>& productos) {
    static int contadorID = 1;
    time_t now = time(nullptr);
    std::string horaPedido = ctime(&now); //Sirve para tener la hora actual

    Pedido nuevoPedido(contadorID++, nombre, apellido, productos, horaPedido);
    avlPedidos.insertarPedido(nuevoPedido);
    heapPrioridad.insertarPedido(nuevoPedido, nuevoPedido.getId());
    std::cout << "Pedido creado exitosamente con ID " << nuevoPedido.getId() << "\n";
}

//Pedidos con mayor prioridad
void SistemaPedido::entregarPedidos() {
    for (int i = 0; i < 5; ++i) {
        if (!heapPrioridad.estaVacio()) {
            Pedido pedido = heapPrioridad.extraerMin();
            avlPedidos.eliminarPedidoRecursivo(pedido.getId());
            std::cout << "Pedido entregado con ID " << pedido.getId() << "\n";
        } else {
            std::cout << "No quedan mas pedidos por entregar \n";
            break;
        }
    }
}

//Cancelar un pedido con su id
void SistemaPedido::cancelarPedido(int id) {
    if (avlPedidos.eliminarPedidoRecursivo(id)) { // AVL
        heapPrioridad.cancelarPedido(id); // MinHeap
        std::cout << "El pedido ha sido cancelado con ID " << id << "\n";
    } else {
        std::cout << "No se encuentra el pedido con ID " << id << "\n";
    }
}

//Buscar un pedido con su id
void SistemaPedido::buscarPedido(int id) const {
    Pedido pedido = avlPedidos.buscarPedido(id);
    if (pedido.getId() != -1) {
        std::cout << "Pedido encontrado con ID " << pedido.getId() << "\n";
        std::cout << "Cliente " << pedido.getNombreCliente() << "q " << pedido.getApellidoCliente() << "\n";
        std::cout << "Productos ";
        for (const auto& producto : pedido.getProductos()) {
            std::cout << producto << ", ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No se encuentra el pedido \n";
    }
}

//Cerrar el sistema para guardar y actualizar archivos asi como para liberar memoria
void SistemaPedido::cerrarSistema() {
    std::cout << "Se ha cerrado la tienda \n";
    //TODO Liberar memoria y guardar en archivos
}

//TODO Falta hacer el menu estadistica

//Menu principal
void SistemaPedido::mostrarMenu() {
    int opcion;
    do {
        try {
            std::cout << "\n----- Sistema de pedidos Grill of Victory -----\n";
            std::cout << "1 Crear Pedido\n";
            std::cout << "2 Entregar Pedidos\n";
            std::cout << "3 Cancelar Pedido\n";
            std::cout << "4 Buscar Pedido\n";
            std::cout << "5 Salir\n";
            std::cout << "Seleccione una opcion ";
            std::cin >> opcion;

            std::string entrada;
            std::cin >> entrada;

            //Convertir un numero la entrada
            try {
                opcion = std::stoi(entrada); //Convierte a un entero
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Entrada no valida, ingresa un numero ");
            } catch (const std::out_of_range&) {
                    throw std::runtime_error("Numero fuera del rango permitido ");
            }

            if (opcion < 1 || opcion > 5) {
                throw std::runtime_error("Opcion no se encuentra en el menu, intente nuvamente ");
            }

            switch (opcion) {
                case 1: {
                    std::cin.ignore(); //Limpiar el buffer
                    std::string nombre, apellido;
                    std::list<std::string> productos;
                    std::string producto;
                    int cantidad;

                    std::cout << "Ingrese el nombre del cliente ";
                    std::getline(std::cin, nombre);
                    std::cout << "Ingrese el apellido del cliente ";
                    std::getline(std::cin, apellido);
                    std::cout << "Ingrese la cantidad de productos ";
                    std::cin >> cantidad;
                    std::cin.ignore();
                    for (int i = 0; i < cantidad; ++i) {
                        std::cout << "Producto " << (i + 1) << " ";
                        std::getline(std::cin, producto);
                        productos.push_back(producto);
                    }
                    crearPedido(nombre, apellido, productos);
                    break;
                }
                case 2:
                    entregarPedidos();
                break;
                case 3: {
                    int id;
                    std::cout << "Ingrese el ID del pedido a cancelar ";
                    std::cin >> id;
                    cancelarPedido(id);
                    break;
                }
                case 4: {
                    int id;
                    std::cout << "Ingrese el ID del pedido a buscar ";
                    std::cin >> id;
                    buscarPedido(id);
                    break;
                }
                case 5:
                    cerrarSistema();
                break;
                default: ;
            }
        } catch (const std::exception& e) {
            std::cout << "ERROR " << e.what() << "\n";
            std::cin.clear();              //Limpia el estado de error de `cin`
            std::cin.ignore(INT_MAX, '\n'); //Descarta cualquier entrada no valida
        }
    } while (opcion != 5);
}
