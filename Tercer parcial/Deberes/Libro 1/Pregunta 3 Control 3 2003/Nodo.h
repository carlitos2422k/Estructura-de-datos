#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    int indice;
    double valor;
    Nodo* sig;

    // Constructor del Nodo
    Nodo(int x, double y, Nodo* z = nullptr) {
        indice = x;
        valor = y;
        sig = z;
    }
};

#endif
