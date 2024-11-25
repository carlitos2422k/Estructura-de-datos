#pragma once
#include "Nodo.h"

template<typename T>
class Lista_Circular {
private:
    Nodo<T>* cabeza;
public:
    Lista_Circular();
    void InsertarPorCabeza(T, T, T, T);
    void InsertarPorCola(T, T, T, T);
    void Mostrar();
    void BuscarPorCedula(T);
};