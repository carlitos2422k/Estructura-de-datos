#include "Hash.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Insertar valor\n";
    std::cout << "2. Buscar valor\n";
    std::cout << "3. Mostrar tabla\n";
    std::cout << "4. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    system("cls");
    Hash hash;
    int opcion;
    std::string valor;
    int pos;
    
    std::cout << "Seleccione el tipo de hash:\n";
    std::cout << "1. Hash para enteros\n";
    std::cout << "2. Hash para strings\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;
    hash.setHashType(opcion == 1);
    
    std::cout << "Seleccione el metodo de resolucion de colisiones:\n";
    std::cout << "1. Linear Probing\n";
    std::cout << "2. Quadratic Probing\n";
    std::cout << "3. Double Hashing\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    if (opcion == 2) hash.setProbingMethod(true);
    if (opcion == 3) hash.setDoubleHashing(true);
    
    while (true) {
        mostrarMenu();
        std::cin >> opcion;
        
        if (opcion == 1) {
            std::cout << "Ingrese el valor a insertar: ";
            std::cin >> valor;
            if (hash.insert(valor)) {
                std::cout << "Valor insertado correctamente\n";
            }
        } else if (opcion == 2) {
            std::cout << "Ingrese el valor a buscar: ";
            std::cin >> valor;
            pos = hash.findPosition(valor);
            if (pos != -1) {
                std::cout << "Valor encontrado en la posicion: " << pos << "\n";
            } else {
                std::cout << "Valor no encontrado\n";
            }
        } else if (opcion == 3) {
            hash.display();
        } else if (opcion == 4) {
            break;
        } else {
            std::cout << "Opcion no valida\n";
        }
        
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
    }
    return 0;
}
