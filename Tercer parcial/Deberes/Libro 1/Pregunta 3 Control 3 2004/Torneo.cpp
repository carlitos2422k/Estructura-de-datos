#include "Torneo.h"
#include <cmath>
#include <iostream>

Torneo::Torneo() {
    raiz = nullptr; // Inicializamos el árbol vacío
}

void Torneo::resultado(std::string x, std::string y) {
    // Agregar lógica para registrar el resultado del partido
}

int Torneo::lugar(std::string x) {
    return lugarRecursivo(x, 1, raiz);
}

int Torneo::lugarRecursivo(std::string x, int n, Nodo* r) {
    if (r == nullptr) return -1;
    if (r->valor == x) return n / 2 + 1;
    return std::max(lugarRecursivo(x, 2 * n, r->izq), lugarRecursivo(x, 2 * n, r->der));
}

std::string Torneo::jugador(int x) {
    // Lógica para obtener los jugadores en el lugar x
}

void Torneo::lugares(Torneo t) {
    std::vector<std::string> jugadores;
    for (int i = 1; i <= 5; ++i) {
        int n = static_cast<int>(pow(2, i)) + 1;
        lugaresRecursivo(n, raiz, jugadores);
        std::cout << n << "º";
        for (const auto& jugador : jugadores) {
            std::cout << jugador << " ";
        }
        std::cout << std::endl;
    }
}

void Torneo::lugaresRecursivo(int n, Nodo* r, std::vector<std::string>& jugadores) {
    if (r == nullptr) return;
    jugadores.push_back(r->valor);
    lugaresRecursivo(2 * n, r->izq, jugadores);
    lugaresRecursivo(2 * n, r->der, jugadores);
}
