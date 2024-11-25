#pragma once
#include "NodoDoble.h"

template<typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;
public:
    ListaDoble();
    void InsertarPorCabeza(T, T, T, T);
    void InsertarPorCola(T, T, T, T);
    void Mostrar();
    void BuscarPorCedula(T);
};
