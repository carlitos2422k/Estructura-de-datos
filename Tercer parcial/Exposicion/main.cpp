#include "BigO.h"
#include <iostream>

void showMenu() {
    std::cout << "\nMenu de Notación O:" << std::endl;
    std::cout << "1. Fundamentos de la Notación O" << std::endl;
    std::cout << "2. Reglas de Manipulación" << std::endl;
    std::cout << "3. Aplicaciones y Comparación de Algoritmos" << std::endl;
    std::cout << "4. Salir" << std::endl;
}

int main() {
    int opcion;
    do {
        showMenu();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        if (opcion == 1) {
            BigO::fundamentals();
        } else if (opcion == 2) {
            BigO::manipulationRules();
        } else if (opcion == 3) {
            BigO::applications();
        }
    } while (opcion != 4);
    
    return 0;
}
