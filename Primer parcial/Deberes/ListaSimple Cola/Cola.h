#pragma once
#include "Nodo.h"

template<typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;
public:
    Cola();
    ~Cola();
    void Encolar(T, T, T, T);
    void Desencolar();
    void Mostrar();
    bool estaVacia();
};
