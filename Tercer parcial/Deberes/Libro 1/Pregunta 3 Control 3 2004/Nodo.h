#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    std::string valor;
    Nodo* izq;
    Nodo* der;

    Nodo(std::string val) : valor(val), izq(nullptr), der(nullptr) {}
};

#endif
