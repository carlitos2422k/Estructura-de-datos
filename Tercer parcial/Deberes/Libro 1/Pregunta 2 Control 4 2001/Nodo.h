#ifndef NODO_H
#define NODO_H
#include <string>

class Nodo {
public:
    std::string valor;
    Nodo* izq;
    Nodo* der;

    // Constructor
    Nodo(std::string x, Nodo* y = nullptr, Nodo* z = nullptr)
        : valor(x), izq(y), der(z) {}

    // Método para verificar si dos árboles son espejos
    static bool espejos(Nodo* x, Nodo* y);
};

#endif
