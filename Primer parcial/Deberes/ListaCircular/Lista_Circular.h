#pragma once
#include "Nodo.h"
#include <iostream>
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
    void EliminarNodo(T);  // Eliminar nodo por completo
    void EliminarDatosNodo(T); // Eliminar datos de un nodo
    void Cifrar(char a);
    void setConsoleColor(int color);
    //void EliminarCampoNodo(T);
};
