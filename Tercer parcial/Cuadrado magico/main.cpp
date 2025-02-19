#include <iostream>
#include "MagicSquare.h"

int main() {
    int n;

    try {
        std::cout << "Ingrese el tamaño del cuadrado mágico (n >= 3): ";
        std::cin >> n;

        MagicSquare magicSquare(n); // Crea un cuadrado mágico de tamaño n
        std::cout << "Cuadrado mágico de tamaño " << n << ":\n";
        magicSquare.display(); // Muestra el cuadrado mágico

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
