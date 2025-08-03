#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    int valor;
    Nodo* izq;
    Nodo* der;

    // Constructor
    Nodo(int x, Nodo* y = nullptr, Nodo* z = nullptr) : valor(x), izq(y), der(z) {}

    // Método para verificar si el árbol es un ABM
    bool esABM(Nodo* x);

    // Método para juntar dos árboles
    static Nodo* juntar(Nodo* x, Nodo* y);
};

#endif
