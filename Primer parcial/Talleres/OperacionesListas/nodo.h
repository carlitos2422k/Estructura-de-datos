#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;

    Nodo(T valor);  // Constructor
};

// Implementación del constructor
template <typename T>
Nodo<T>::Nodo(T valor) : dato(valor), siguiente(nullptr) {}

#endif // NODO_H
