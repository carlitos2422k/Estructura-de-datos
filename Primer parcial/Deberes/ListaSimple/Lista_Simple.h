#pragma once
#include "Nodo.h"

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
public:
    Lista_Simple();
    void Insertar(T, T, T, T);
    void Mostrar();
    void BuscarPorCedula(T);
    
};
