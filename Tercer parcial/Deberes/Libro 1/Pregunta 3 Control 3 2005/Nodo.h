#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    void* valor;  // Puede ser un puntero a un objeto Logico o un operador (String)
    Nodo* izq;
    Nodo* der;

    Nodo(void* v) : valor(v), izq(nullptr), der(nullptr) {}
};

#endif
