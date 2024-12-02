#pragma once
#include "Nodo.h"

template<typename T>
class Pila {
private:
    Nodo<T>* cima;
public:
    Pila();
    ~Pila();
    void Apilar(T, T, T, T);
    void Desapilar();
    void Mostrar();
    bool estaVacia();
};
