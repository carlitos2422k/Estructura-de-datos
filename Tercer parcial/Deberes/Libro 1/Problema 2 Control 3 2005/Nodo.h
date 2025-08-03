#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    int fila;
    int col;
    std::string valor;
    Nodo* sgte;

    Nodo(int f, int c, std::string v) : fila(f), col(c), valor(v), sgte(nullptr) {}
};

#endif
