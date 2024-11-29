//
// Created by felip on 18-11-2024.
//

#include "SistemaPedido.h"
#include <ctime>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>


//Constructor
SistemaPedido::SistemaPedido() {
    std::cout << "Iniciando el sistema de pedidos Grill of Victory \n";
    cargarProductos("C:\\Users\\felip\\OneDrive\\Escritorio\\Estructura de Datos\\Taller2\\Taller2_P3\\productos_grill_of_victory.txt");
}

//Crear un nuevo pedido
void SistemaPedido::crearPedido(const std::string& nombre, const std::string& apellido, const std::list<std::string>& productos, int precioTotal) {
    static int contadorID = 1;
    time_t now = time(nullptr);
    std::string horaPedido = ctime(&now);

    Pedido nuevoPedido(contadorID++, nombre, apellido, productos, horaPedido);
    avlPedidos.insertarPedido(nuevoPedido);
    heapPrioridad.insertarPedido(nuevoPedido, nuevoPedido.getId());

    std::cout << "Pedido creado exitosamente con el ID " << nuevoPedido.getId() << "\n";
    std::cout << "Precio total del pedido $" << precioTotal << " \n";
}

//Pedidos con mayor prioridad
void SistemaPedido::entregarPedidos() {
    for (int i = 0; i < 5; ++i) { //Entregar hasta 5 pedidos
        if (!heapPrioridad.estaVacio()) {
            Pedido pedido = heapPrioridad.extraerMin(); //Extraer el pedido con mayor prioridad
            avlPedidos.eliminarPedidoRecursivo(pedido.getId()); //Eliminar del AVL
            historialPedidos.push_back(pedido); //Agregar al historial
            std::cout << "Pedido entregado con ID " << pedido.getId() << "\n";
        } else {
            std::cout << "No quedan mas pedidos por entregar \n";
            break;
        }
    }
}

//Cancelar un pedido con su id
void SistemaPedido::cancelarPedido(int id) {
    Pedido pedido = avlPedidos.buscarPedido(id);
    if (pedido.getId() != -1) { //Si el pedido existe en el AVL
        avlPedidos.eliminarPedidoRecursivo(id);//Eliminar del AVL
        heapPrioridad.cancelarPedido(id); //Eliminar del MinHeap
        pedidosCancelados.push_back(pedido); //Agregar al vector de pedidos cancelados
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
    std::cout << "Guardando estadisticas y cerrando el sistema...\n";

    //Usar la misma ruta que el archivo de productos
    std::string rutaArchivo = "C:/Users/felip/OneDrive/Escritorio/Estructura de Datos/Taller2/Taller2_P3/productos_grill_of_victory.txt";

    //Crear el archivo estadisticas.txt en la misma ruta
    std::ofstream archivo(rutaArchivo.substr(0, rutaArchivo.find_last_of("/\\") + 1) + "estadisticas.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al crear el archivo de estadisticas.\n";
        return;
    }

    archivo << "ID,Cliente,Productos,Valor Total,Hora\n"; //Encabezado

    for (const auto& pedido : historialPedidos) { //Historial de pedidos entregados
        int valorTotal = 0;

        for (const auto& producto : pedido.getProductos()) {
            auto it = std::find_if(productosDisponibles.begin(), productosDisponibles.end(),
                [&producto](const Producto& prod) { return prod.nombre == producto; });

            if (it != productosDisponibles.end()) {
                valorTotal += it->precio;
            }
        }

        archivo << pedido.getId() << ","
                << pedido.getNombreCliente() << " " << pedido.getApellidoCliente() << ","
                << pedido.getProductos().size() << " productos,"
                << valorTotal << " CLP,"
                << pedido.getHoraPedido() << "\n";
    }

    archivo.close();
    std::cout << "Estadisticas guardadas en 'estadisticas.txt'.\n";
}


//Menu principal
void SistemaPedido::mostrarMenu() {
    int opcion = 0;
    do {
        try {
            std::cout << "\n----- Sistema de pedidos Grill of Victory -----\n";
            std::cout << "1 Crear Pedido\n";
            std::cout << "2 Entregar Pedidos\n";
            std::cout << "3 Cancelar Pedido\n";
            std::cout << "4 Buscar Pedido\n";
            std::cout << "5 Salir\n";
            std::cout << "6 Menu de Estadisticas\n";
            std::cout << "7 Ver Historial de Pedidos\n";
            std::cout << "Seleccione una opcion ";
            std::cin >> opcion;

            //Verificar si `std::cin` tiene un error
            if (std::cin.fail()) {
                throw std::runtime_error("Entrada invalida, ingrese un numero.");
            }

            if (opcion < 1 || opcion > 7) {
                throw std::runtime_error("Opcion no se encuentra en el menu, intente nuvamente ");
            }

            switch (opcion) {
                case 1: {
                    std::cin.ignore(); //Limpiar el buffer
                    std::string nombre, apellido;
                    std::list<std::string> productosSeleccionados;
                    int cantidad, opcionProducto;
                    int precioTotal = 0;

                    std::cout << "Ingrese el nombre del cliente ";
                    std::getline(std::cin, nombre);
                    std::cout << "Ingrese el apellido del cliente ";
                    std::getline(std::cin, apellido);

                    std::cout << "Cuantos productos desea agregar? ";
                    std::cin >> cantidad;
                    std::cin.ignore();

                    for (int i = 0; i < cantidad; ++i) {
                        mostrarProductos();
                        std::cout << "Seleccione un producto (por numero) ";
                        std::cin >> opcionProducto;
                        std::cin.ignore();

                        auto it = std::ranges::find_if(productosDisponibles,
                                                       [&opcionProducto](const Producto& prod) { return prod.id == opcionProducto; });

                        if (it != productosDisponibles.end()) {
                            productosSeleccionados.push_back(it->nombre);
                            precioTotal += it->precio; //Sumar el precio al total
                        } else {
                            std::cout << "Opcion inválida, ingrese denuevo\n";
                            --i;
                        }
                    }
                    crearPedido(nombre, apellido, productosSeleccionados, precioTotal);
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
                case 6:
                    mostrarEstadisticas();
                break;
                case 7:
                    mostrarHistorialPedidos();
                break;
                default: ;
            }
        } catch (const std::exception& e) {
            std::cout << "ERROR " << e.what() << "\n";
            std::cin.clear(); //Limpia el estado de error de `cin`
            std::cin.ignore(INT_MAX, '\n'); //Descarta cualquier entrada no valida
        }
    } while (opcion != 5);
}


void SistemaPedido::mostrarEstadisticas() {
    int opcion;
    do {
        std::cout << "\n----- Menu de Estadisticas -----\n";
        std::cout << "1 Pedido con mayor cantidad de productos\n";
        std::cout << "2 Pedido de mayor valor\n";
        std::cout << "3 Pedido que mas se tardO en ser entregado\n";
        std::cout << "4 Mostrar pedidos cancelados\n";
        std::cout << "5 Volver al menu principal\n";
        std::cout << "Seleccione una opcion ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                pedidoMayorCantidadProductos();
                break;
            case 2:
                pedidoMayorValor();
                break;
            case 3:
                pedidoMayorTiempoEntrega();
                break;
            case 4:
                mostrarPedidosCancelados();
                break;
            case 5:
                std::cout << "Volviendo al menu principal \n";
                break;
            default:
                std::cout << "Opcion no valida, ingrese nuevamente \n";
        }
    } while (opcion != 5);
}

void SistemaPedido::cargarProductos(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de productos.\n";
        return;
    }

    std::string linea;
    bool esPrimeraLinea = true;

    while (std::getline(archivo, linea)) {
        if (esPrimeraLinea) {
            esPrimeraLinea = false; //Omitir la primera línea (encabezado)
            continue;
        }

        std::stringstream ss(linea);
        std::string idStr, nombre, precioStr;

        //Dividir la lknea por las comas
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, precioStr, ',');

        //Validar que los campos no estén vacios
        if (idStr.empty() || nombre.empty() || precioStr.empty()) {
            std::cerr << "Línea mal formateada: " << linea << "\n";
            continue;
        }
        Producto producto;
        producto.id = std::stoi(idStr); //Convertir ID a entero
        producto.nombre = nombre; //Almacenar nombre del producto
        producto.precio = std::stoi(precioStr); //Convertir precio a entero
        productosDisponibles.push_back(producto);
    }

    archivo.close();
    std::cout << "Productos cargados correctamente desde el archivo.\n";
}

void SistemaPedido::mostrarProductos() {
    std::cout << "Productos Disponibles:\n";
    for (const auto& producto : productosDisponibles) {
        std::cout << producto.id << ". " << producto.nombre << " - $" << producto.precio << "\n";
    }
}

void SistemaPedido::mostrarHistorialPedidos() const {
    if (historialPedidos.empty()) {
        std::cout << "No hay pedidos en el historial \n";
        return;
    }

    std::cout << "Historial de Pedidos Entregados:\n";
    for (const auto& pedido : historialPedidos) {
        std::cout << "ID: " << pedido.getId() << "\n";
        std::cout << "Cliente: " << pedido.getNombreCliente() << " " << pedido.getApellidoCliente() << "\n";
        std::cout << "Productos:\n";
        for (const auto& producto : pedido.getProductos()) {
            std::cout << "- " << producto << "\n";
        }
        std::cout << "Hora del pedido: " << pedido.getHoraPedido() << "\n";
        std::cout << "-----------------------------\n";
    }
}

void SistemaPedido::pedidoMayorCantidadProductos() const {
    if (historialPedidos.empty()) {
        std::cout << "No hay pedidos entregados en el historial \n";
        return;
    }

    const Pedido* pedidoMayor = nullptr;
    for (const auto& pedido : historialPedidos) {
        if (!pedidoMayor || pedido.getProductos().size() > pedidoMayor->getProductos().size()) {
            pedidoMayor = &pedido;
        }
    }

    if (pedidoMayor) {
        std::cout << "Pedido con mayor cantidad de productos:\n";
        std::cout << "ID: " << pedidoMayor->getId() << "\n";
        std::cout << "Cliente: " << pedidoMayor->getNombreCliente() << " " << pedidoMayor->getApellidoCliente() << "\n";
        std::cout << "Cantidad de productos: " << pedidoMayor->getProductos().size() << "\n";
    }
}

void SistemaPedido::pedidoMayorValor() const {
    if (historialPedidos.empty()) {
        std::cout << "No hay pedidos entregados en el historial \n";
        return;
    }

    const Pedido* pedidoMayor = nullptr;
    int mayorValor = 0;

    for (const auto& pedido : historialPedidos) {
        int valorTotal = 0;
        for (const auto& producto : pedido.getProductos()) {
            auto it = std::find_if(productosDisponibles.begin(), productosDisponibles.end(),
                [&producto](const Producto& prod) { return prod.nombre == producto; });
            if (it != productosDisponibles.end()) {
                valorTotal += it->precio;
            }
        }

        if (valorTotal > mayorValor) {
            mayorValor = valorTotal;
            pedidoMayor = &pedido;
        }
    }

    if (pedidoMayor) {
        std::cout << "Pedido de mayor valor:\n";
        std::cout << "ID: " << pedidoMayor->getId() << "\n";
        std::cout << "Cliente: " << pedidoMayor->getNombreCliente() << " " << pedidoMayor->getApellidoCliente() << "\n";
        std::cout << "Valor total: $" << mayorValor << "\n";
    }
}


void SistemaPedido::pedidoMayorTiempoEntrega() const {
    if (historialPedidos.empty()) {
        std::cout << "No hay pedidos entregados en el historial.\n";
        return;
    }

    const Pedido& ultimoPedido = historialPedidos.back();
    std::cout << "Pedido que mas se tardo en ser entregado:\n";
    std::cout << "ID: " << ultimoPedido.getId() << "\n";
    std::cout << "Cliente: " << ultimoPedido.getNombreCliente() << " " << ultimoPedido.getApellidoCliente() << "\n";
    std::cout << "Hora del pedido: " << ultimoPedido.getHoraPedido() << "\n";
}

void SistemaPedido::mostrarPedidosCancelados() const{
    if (pedidosCancelados.empty()) {
        std::cout << "No hay pedidos cancelados.\n";
        return;
    }

    std::cout << "Pedidos cancelados:\n";
    for (const auto& pedido : pedidosCancelados) {
        std::cout << "ID: " << pedido.getId() << "\n";
        std::cout << "Cliente: " << pedido.getNombreCliente() << " " << pedido.getApellidoCliente() << "\n";
        std::cout << "-----------------------------\n";
    }
}

